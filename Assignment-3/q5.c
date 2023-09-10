#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *create_file(void *arg) {
    FILE *file = fopen("mythread.txt", "w");
    if (file == NULL) {
        exit(0);
    }
    fclose(file);
    pthread_exit(NULL);
}
void *write_to_file(void *arg) {
    FILE *file = fopen("mythread.txt", "a");
    if (file == NULL) {
        exit(0);
    }
    fprintf(file, "Hello, I am writing in the file created by you.\n");
    fclose(file);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_t1, thread_t2; //Thread is a sequential flow of tasks within a process
    if (pthread_create(&thread_t2, NULL, create_file, NULL) != 0) {
        perror("Error creating thread T2");
    }
    if (pthread_create(&thread_t1, NULL, write_to_file, NULL) != 0) {
        perror("Error creating thread T1");
    }
    pthread_join(thread_t2, NULL);
    pthread_join(thread_t1, NULL);

    return 0;
}
