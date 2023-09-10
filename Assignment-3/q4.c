#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    printf("process ID of Parent (P): %d\n", getpid());
    pid = fork();

    if (pid == 0) {
        printf("process ID of Child (P1): %d\n", getpid());
        printf("parent ID of Child P1: %d\n", getppid());
    }
    else{
        // wait(NULL); 
        //comment line 17 for A B C D
        //uncomment line 17 for A C D B
        printf("ID of P's Child (P1): %d\n", pid);
    }

    return 0;
}
