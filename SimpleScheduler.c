#include "Main_shell.h"

int NCPU;
int TSLICE;
struct Queue *Kyu;

void Signal_time()
{
    printf("hello");
    for (int i=0; i<NCPU; i++)
    {  
        struct Blocks single = Kyu->queue[Kyu->start_index];
        printf("Stopped\n\n");
        if (kill(single.pid, SIGSTOP)==-1)
        {
            Kyu->queue[Kyu->start_index++].status = 3;
        }else{
            Kyu->queue[Kyu->end_index++] = single;
            Kyu->queue[Kyu->start_index++].status = 1;
        }
    }
}

void loop(){
    signal(SIGALRM, Signal_time);

    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = TSLICE*1000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    for (int i=0; i<NCPU; i++)
    {
        if (Kyu->queue[Kyu->start_index+i].status==1)
        {
            kill(Kyu->queue[Kyu->start_index+i].pid, SIGCONT);
            printf("Continued\n\n");
            Kyu->queue[Kyu->start_index+i].status = 2;
        } else if (Kyu->queue[Kyu->start_index+i].status==3)
        {
            printf("Done\n\n");
            Kyu->done++;
        } else
        {
            char* arg[] = {Kyu->queue[Kyu->start_index+i].command, NULL};
            printf("Started i %d \n\n", i);
            int pid = fork();
            if (pid==0)
            {
                execv(arg[0], arg);
            } else{
                Kyu->queue[Kyu->start_index+i].pid = pid;
                Kyu->queue[Kyu->start_index+i].status = 2;
                Kyu->childs++;
            }
        }
    }
}

int main(int argc, char** argv)
{
    // if(argc!=3){
    //     printf("Incorrect number of arguments");
    // }

    Kyu = (struct Queue*) malloc (sizeof(struct Queue));
    Kyu->queue = (struct Blocks*) malloc (200*sizeof(struct Blocks));

    //NCPU = atoi(argv[2]);
    //TSLICE = atoi(argv[3]);

    //default status = 0;
    //when suspended, status  = 1;
    //when continued or started, status = 2;
    //when terminated, status = 3;

    NCPU = 2;
    TSLICE = 50;

    Kyu->start_index = 0;
    Kyu->end_index =0;

    Kyu->childs = 0;
    Kyu->done = 0;

    Kyu->queue[0].command = "./fib";
    Kyu->queue[0].pid = -1;
    Kyu->queue[0].status = 0;
    Kyu->queue[1].command = "./loop1";
    Kyu->queue[1].pid = -1;
    Kyu->queue[1].status = 0;
    Kyu->queue[2].command = "./loop2";
    Kyu->queue[2].pid = -1;
    Kyu->queue[2].status = 0;
    Kyu->queue[3].command = "./loop3";
    Kyu->queue[3].pid = -1;
    Kyu->queue[3].status = 0;
    Kyu->queue[4].command = "./loop4";
    Kyu->queue[4].pid = -1;
    Kyu->queue[4].status = 0;
    Kyu->queue[5].command = "./helloworld";
    Kyu->queue[5].pid = -1;
    Kyu->queue[5].status = 0;
    Kyu->end_index = 6;

    int b = Kyu->end_index;
    int a = Kyu->start_index;

    while (Kyu->done != b-a)
    {
        loop();
    }
    free(Kyu->queue);
}