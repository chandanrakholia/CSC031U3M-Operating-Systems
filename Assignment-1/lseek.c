#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
    int n, f;
    char buff[10];
    f = open("test2.txt", O_RDWR);
    read(f, buff, 10);
    write(1, buff, 10);
    printf("\n");
    lseek(f, -10, SEEK_END);
    read(f, buff, 10);
    write(1, buff, 10);
    printf("\n");
}