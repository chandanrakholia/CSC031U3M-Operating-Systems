#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    pid1 = fork();
    if(pid1 == 0) {
        sleep(2);
        exit(0);
    } 
    else{
        pid2 = fork();
        if(pid2 == 0) {
            sleep(3);
            exit(0);
        }
        else{
            wait(NULL); //block the parent process until any of its children has finished
            wait(NULL); // parent process will wait for both pid1 and pid2 to finissh.
            printf("My children finished the task\n");
        }
    }
    return 0;
}
