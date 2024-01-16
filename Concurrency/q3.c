#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 3

sem_t mutex;
sem_t full;
sem_t empty;

int buffer[N];
int in = 0;
int out = 0;

void *producer(void* arg){
    int item;
    while(1){
        item=rand();
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in]=item;
        in=(in+1)%N;
        printf("produced: %d\n",item);
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}
void *consumer(void* arg){
    int item;
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
        item=buffer[out];
        out=(out+1)%N;
        printf("consumed: %d\n",item);
        sem_post(&mutex);
        sem_post(&empty); 
        // sleep(1);   
    }
}
int main(){
    pthread_t producer_thread, consumer_thread;

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}