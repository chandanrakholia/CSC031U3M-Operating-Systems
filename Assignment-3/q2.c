#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t pid1, pid2;
    pid1 = fork();

    if (pid1 == 0)
    {
        printf("P1 process (PID: %d) created by parent P (PID: %d)\n", getpid(), getppid());
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("P2 process (PID: %d) created by parent P1 (PID: %d)\n", getpid(), getppid());
        }
    }
    else
    {
        printf("Parent P process (PID: %d)\n", getpid());
    }

    return 0;
}