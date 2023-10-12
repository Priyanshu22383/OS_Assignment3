#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

struct history_command{
    char* nam[100];
    char* string;
    int pid;
    int priority;
    time_t start_time;
    time_t current_time_of_execution;
    time_t end_time_of_execution;
    time_t duration_of_execution;
    time_t wait_time;
};

int sig_terminate = 0;
struct history_command command_history[100];
int history_index=-1;

/////////////
struct history_command que[4];
int job_num[4];
int curr_prior = 1;
int NCPU = 1;
int TSLICE = 1000;

/////////////

void history_display(int mode)
{
    if (mode == 1)
    {
        for (int i=1;i<history_index;i++)
        {
            printf("Command: %s\n", command_history[i].string);
        }
    } else
    {
        for (int i=1;i<history_index;i++)
        {
            printf("Command: %s\n", command_history[i].string);
            printf("PID :%d\n", command_history[i].pid);
            printf("Start time: %ld\n", command_history[i].start_time);
            printf("Current time: %ld\n", command_history[i].current_time_of_execution);
            printf("Duration of execution: %ld\n", command_history[i].duration_of_execution);
            printf("----------------------------------------------------------\n");
        }
    }
}

void sig_termination(){
    sig_terminate = 1;
}

void clean(char* command){
    free(command);
}

char* read_user_input()
{
    void (*function_pointer)();
    function_pointer = sig_termination;
    signal(SIGINT, function_pointer);
    char* input = (char*) malloc (200*sizeof(char));
    fgets(input, 200, stdin);
    command_history[++history_index].string=input;

    if (sig_terminate)
    {
        input = "TERMINATE";
    } else
    {
        time(&(command_history[history_index].current_time_of_execution));
        int len = strlen(input);
        input[len-1] = '\0';
        strcpy(command_history[history_index].string, input);
    }
    return input;
}

char** command_line_array(char* command)
{
    int i=0;
    char** argv = (char**) malloc (50*sizeof(char**));
    char seperator[] = " ";
    char *words = strtok(command, seperator);
    argv[i++] = words;
    while (words != NULL) {
        words = strtok(NULL, seperator);
        argv[i++] = words;
    }
    argv[i] = NULL;
    return argv;
}

void child_process(char* command , int pipe_fds[])
{
    char** argv = command_line_array(command);

    if (strcmp(argv[0], "ls")==0)
    {
        execv("/usr/bin/ls", argv);
    }else if (strcmp(argv[0], "echo")==0)
    {
        execv("/usr/bin/echo", argv);
    }else if (strcmp(argv[0], "wc")==0)
    {
        execv("/usr/bin/wc", argv);
    }else if (strcmp(argv[0], "grep")==0)
    {
        execv("/usr/bin/grep", argv);
    }else if (strcmp(argv[0], "sort")==0)
    {
        execv("/usr/bin/sort", argv);
    }else if (strcmp(argv[0], "uniq")==0)
    {
        execv("/usr/bin/uniq", argv);
    }else if (strcmp(argv[0], "cat")==0)
    {
        execv("/usr/bin/cat", argv);
    }
    else if (pipe_fds != -1){
        dup2(pipe_fds, STDIN_FILENO);
    }
    else{
        printf("Command not registered\n");
    }
}

void pipeling(char* command){
    int child_status;
    if(strcmp(command , "|")){
        int child_pid = fork();
        int child_pidd = fork();
        int pipe_fds[2];
        int in_fd =0;
        int n = 0;
        char* commands[n];
        for(int i=0;i<=10;i++){
            n = i++;
            commands[n];
        }
        if (pipe(pipe_fds) ==-1)
        {
            printf("Fork Process");
        } else if (child_pid == 0) {
            dup2(in_fd,0);
            for (int i =0; i==1;i++){
            child_process(strtok(command , "|"), pipe(pipe_fds[i]));
            }
            launch(commands[n]);
        } else {
            if (child_pidd== 0){
                child_process(strtok(NULL, "|"), -1);
            }
            else{
                for (int i =0; i<=1; i++){
                    close(pipe_fds[i]);
                }
                waitpid(child_pid, &child_status, 0);
                waitpid(child_pidd, &child_status, 0);
                time(&(command_history[history_index].end_time_of_execution));
                command_history[history_index].duration_of_execution = (command_history[history_index].end_time_of_execution - command_history[history_index].current_time_of_execution);
            }
        }
    }
    
}


int launch(char *command)
{
    int status;
    int child_status;
    if (strcmp(command ,"TERMINATE")==0)
    {
        history_display(0);
        status = 0;
    } 
    else if (strcmp(command ,"history")==0){
        history_display(1);
        time(&(command_history[history_index].end_time_of_execution));
        command_history[history_index].duration_of_execution = (command_history[history_index].end_time_of_execution - command_history[history_index].current_time_of_execution);
        command_history[history_index].pid=getpid();
        status = 1;
    }
    else
    {
        int child_pid = fork();
        if (child_pid==-1)
        {
            printf("Error: 101 - child process was not able to form\n");
        } else if (child_pid == 0) {
            child_process(command , NULL);
        } else{
            command_history[history_index].pid=child_pid;
            waitpid(child_pid, &child_status, 0);
            time(&(command_history[history_index].end_time_of_execution));
            command_history[history_index].duration_of_execution = (command_history[history_index].end_time_of_execution - command_history[history_index].current_time_of_execution);
        }
        status = 1;
    }
    return status;
}
void background(){

}

////////
void add_job(const char* command, int priority) {
    int priority = 1;
    int index = priority - 1;
    if (job_num[index] >= NCPU) {
        printf("Priority %d queue is full, cannot add job: %s\n", priority, command);
    }
    else if (job_num[index] < NCPU){
        strcpy_s(que[index].nam, command);
        que[index].priority = priority;
        job_num[index]++;
        priority++;
    }
    else{
        printf("ERROR");
    }
}
void execute_job() {
    int index2 =curr_prior- 1;
    if (job_num[index2] > 0) {
        pid_t child_pid = fork();
        if (job_num[index2] > 0 && child_pid == 0) {
            execlp("/bin/sh", "sh", "-c", que[index2].nam, (char *)NULL);//
            printf("Error");//
            exit(EXIT_FAILURE);
        } 
        else if (child_pid != 0 || child_pid != -1) {
            que[curr_prior-1].pid = child_pid;
            time_t start_time;
            time(&start_time);
            waitpid(child_pid, NULL, 0);
            time_t end_time;
            time(&end_time);
            que[curr_prior -1].wait_time += start_time-end_time;
            que[curr_prior-1].duration_of_execution += end_time - start_time;
            job_num[curr_prior-1] = job_num[curr_prior-1] -1;
        }
        else{
            printf("ERRROR");
        }
    }
    else{
        printf("ERRROR");
    }
}

void switch_priority(int signal) {
    int prio = curr_prior % 4;
    curr_prior = prio + 1;
    alarm(TSLICE);//
}

////////


void shell_loop(int NCPU, int TSLICE)
{
    int pipe_fds[2];
    int prev_pipe_fds[2] = {-1 , -1};
    int status;
    do {
        printf("Simple_Shell@OS-Assignment2:~$ ");
        char* command = read_user_input();
        status = launch(command);
        //while (prev_pipe_fds [0] != -1){
            //prev_pipe_fds[0] = pipe_fds[0];
            //prev_pipe_fds[1] = pipe_fds[1];
        //}
    } while(status);
}

int main(int argc, char* argv[])
{
    int NCPU;
    int TSLICE;
    if (argc ==4){
        int NCPU = atoi(argv[1]);
        int TSLICE = atoi(argv[2]);
        int priority = atoi(argv[3]);
        if (sscanf(argv[1], "%d", &NCPU) != 1 || sscanf(argv[2], "%d", &TSLICE) != 1) {
            printf("ERROR");
        }
    }
    else{
        printf("Error");
    }

    int i=0;
    while(i<4){
        job_num[1]=0;
        i++;
    }

    if (signal(SIGINT, switch_priority) == SIG_ERR) {
        printf("ERROR");
    }
    else{
        signal(SIGALRM, switch_priority);
        alarm(TSLICE);
    }

    // while(1){
    //     char command[100];
    //     getchar();
    //     fgets(command , 100 , stdin);

    //     }
    shell_loop(NCPU,TSLICE);
    return 0;
}

// ls
// ls /home
// echo you should be aware of the plagiarism policy
// wc -l fib.c
// wc -c fib.c
// grep printf helloworld.c
// ls -R
// ls -l
// ./fib 40
// ./helloworld
// sort fib.c
// uniq file.txt
// cat fib.c | wc -l
// cat helloworld.c | grep print | wc -l
