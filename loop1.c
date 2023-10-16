#include "Main_shell.h"

int main(int argc, char* argv[])
{
    // struct timeval start_time, end_time;
    // gettimeofday(&start_time, NULL);
    long int sum = 0;
    for (int i=0;i<10000;i++)
    {
        sum+=1;
    }
    printf("SUM1: %ld\n", sum);
    // gettimeofday(&end_time, NULL);
    // printf("Time elapsed: %ld\n", end_time.tv_usec-start_time.tv_usec);
}