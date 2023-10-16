#include "Main_shell.h"

int sig_terminate = 0;
struct History_command command_history[100];
int history_index=-1;
int NCPU;
int TSLICE;
struct Queue* Kyu;
int count=0;

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

    if (strcmp(argv[0], "Submit"))
    {
        char NCPU_[20];
        char TSLICE_[20];
        snprintf(NCPU_, sizeof(NCPU_), "%d", NCPU);
        snprintf(TSLICE_, sizeof(TSLICE_), "%d", TSLICE);
        argv[i++] = NCPU_;
        argv[i++] = TSLICE_;
    }

    argv[i] = NULL;
    return argv;
}

void child_process(char* command)
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
    }else if (strcmp(argv[0], "ps")==0)
    {
        execv("/usr/bin/ps", argv);
    }else if (strcmp(argv[0], "touch")==0)
    {
        execv("/usr/bin/touch", argv);
    }else if (strcmp(argv[0], "free")==0)
    {
        execv("/usr/bin/free", argv);
    }else if (strcmp(argv[0], "pwd")==0)
    {
        execv("/usr/bin/pwd", argv);
    }else if (strcmp(argv[0], "submit")==0)
    {
        execv("SimpleScheduler", argv);
    }
    else {
        printf("Command not registered\n");
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
    } else if (strcmp(command ,"history")==0){
        history_display(1);
        time(&(command_history[history_index].end_time_of_execution));
        command_history[history_index].duration_of_execution = (command_history[history_index].end_time_of_execution - command_history[history_index].current_time_of_execution);
        command_history[history_index].pid=getpid();
        status = 1;
    }else
    {
        if (strcmp("submit", command)==0 && count>1)
        {
            Kyu->queue[Kyu->end_index].command = command;
            Kyu->queue[Kyu->end_index++].pid = -1;
        } else 
        {
            if (strcmp("submit", command)==0 && count==1)
            {
                Kyu->queue[Kyu->end_index].command = command;
                Kyu->queue[Kyu->end_index++].pid = -1;
            }

            int child_pid = fork();
            if (child_pid==-1)
            {
                printf("Error: 101 - child process was not able to form\n");
            } else if (child_pid == 0) {
                child_process(command);
            } else{
                command_history[history_index].pid=child_pid;
                waitpid(child_pid, &child_status, 0);
                time(&(command_history[history_index].end_time_of_execution));
                command_history[history_index].duration_of_execution = (command_history[history_index].end_time_of_execution - command_history[history_index].current_time_of_execution);
            }
            status = 1;
        }
    }
    return status;
}

void shell_loop()
{
    int status;
    do {
        printf("Simple_Shell@OS-Assignment2:~$ ");
        char* command = read_user_input();
        status = launch(command);
    } while(status);
}

int main(int argc, char* argv[])
{
    Kyu = setup();

    NCPU = atoi(argv[1]);
    TSLICE = atoi(argv[2]);
    
    //Kyu->queue = (struct Blocks*) malloc (200*sizeof(struct Blocks));

    Kyu->start_index = 0;
    Kyu->end_index = 0;
    shell_loop();

    cleanup();
    return 0;
}