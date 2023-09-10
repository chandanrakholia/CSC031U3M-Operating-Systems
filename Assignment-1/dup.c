#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int main()
{
    int oldFd, newFd;
    oldFd = open("test.txt", O_RDWR);
    printf("Old File descriptor is %d\n", oldFd);
    newFd = dup(oldFd);
    printf("New file descriptor is %d\n", newFd);
}