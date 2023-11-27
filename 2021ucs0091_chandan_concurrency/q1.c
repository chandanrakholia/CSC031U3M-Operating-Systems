#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;

void *mythread(void* arg)
{
    printf("%s: begin\n", (char*) arg);
    int i;
    for (i = 0; i < 1000000; i++) {
        counter = counter + 1;
    }
    printf("%s: done\n", (char*) arg);
    return NULL;
}

int main(int argc, char* argv[]){
	pthread_t p1,p2;
	printf("main: begin (counter=%d)\n",counter);
	pthread_create(&p1,NULL,mythread,"A");
	pthread_create(&p2,NULL,mythread,"B");

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("main: done with both (counter=%d)\n",counter);
	return 0;
}

/*
counter=counter+1 in assembly language
register1 = counter 
register1 = register1 + 1 
counter = register1

after executing line 31 by thread1, it is executing line 32,and in line 33 
when it loads value of register1 to memory, thread2 incremented value of counter

so due to asynchronous behaviour of threads we are getting value in between
1000000 to 2000000
*/