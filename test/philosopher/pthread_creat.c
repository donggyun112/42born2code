#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_hello(void *data) {
    int thread_num = *((int *)data);
    printf("Hello from thread %d!\n", thread_num);
    return NULL;
}

int main() {
    pthread_t thread_ids[NUM_THREADS];
    int thread_nums[NUM_THREADS];
    int result, i;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i + 1;
        result = pthread_create(&thread_ids[i], NULL, print_hello, (void *)&thread_nums[i]);

        if (result != 0) {
            fprintf(stderr, "Error creating thread %d: %d\n", i + 1, result);
            return 1;
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(thread_ids[i], NULL);
    }

    return 0;
}