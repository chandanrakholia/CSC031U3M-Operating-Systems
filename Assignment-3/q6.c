#include <stdio.h>
#include <pthread.h>
struct st {
    int* arr;
    size_t size;
    int result;
};
void* findsum(void* arg) {
    struct st* data = (struct st*)arg;
    int sum = 0;
    for (size_t i = 0; i < data->size; ++i) {
        sum += data->arr[i];
    }
    data->result = sum;
    return NULL;
}
int main() {
    int len=10;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t t;
    struct st data = {arr, len, 0};
    pthread_create(&t, NULL, findsum, &data);
    pthread_join(t, NULL);
    printf("Sum of the arr: %d\n", data.result);

    return 0;
}
