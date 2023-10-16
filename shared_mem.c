#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    int a;
    printf("Number of ele");
    scanf("%d" , &a);

    void *virtual_mem = mmap(NULL, 200, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    int *virtual_me = virtual_mem;
    char code[a][200];
    int i =0;
    printf("Enter codes\n");
    while(i<a){
        scanf("%s",code[i]);
        virtual_me[i] = virtual_me[i] + atoi(code[i]);
        i++;
    }

    printf("Total num %d\n",a);

    
    if (fork() == 0) {
        char *argv[a+1];
        for (int i=0;i<a;i++){
            printf("%d\n",virtual_me[i]);
            (argv[i] == virtual_me[i]);
        }
        argv [a] = NULL;
        execvp(argv[0],argv);
        exit(0);
    } else {
        wait(NULL);
    }
    
}