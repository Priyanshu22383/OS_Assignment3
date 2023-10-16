#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/time.h>

struct Blocks{
    char* command;
    int pid;
    int status;
};

struct Queue{
    struct Blocks *queue;
    int start_index;
    int end_index;
    int childs;
    int done;
};

struct History_command{
    char* string;
    int *pid;
    time_t current_time_of_execution;
    time_t end_time_of_execution;
    time_t duration_of_execution;
};