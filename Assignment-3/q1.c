#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid1,pid2,pid3;

    pid1=fork();
    // printf("%d\n", pid1);
    if(pid1==0){
        printf("child 1 with pid=%d and ppid=%d\n",getpid(),getppid());
    }
    else{
        pid2=fork();
        if(pid2==0){
            printf("child 2 with pid=%d and ppid=%d\n",getpid(),getppid());
        }
        else{
            pid3=fork();
            if(pid3==0){
                printf("child 3 with pid=%d and ppid=%d\n",getpid(),getppid());
            }
            else{
                sleep(3);
                printf("pid of parent is %d\n",getpid());
            }
        }
    }
}