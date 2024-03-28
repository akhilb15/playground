/**
 * @file test_with_mutex.c
 * @author Akhil Bharanidhar
 * @brief Test mutex implementation to see if its the same as pthread_mutex
 * @version 0.1
 * @date 2024-03-25
 * 
 */


#include "mutex.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10

mutex_t m = MUTEX_INITIALIZER;
pthread_mutex_t pm = PTHREAD_MUTEX_INITIALIZER;
int num = 0;

void *increment(void *arg) {
    for (int i = 0; i < 10000; i++) {
        // pthread_mutex_lock(&pm);
        mutex_acquire(&m);
        num++;
        // pthread_mutex_unlock(&pm);
        mutex_release(&m);
    }
    return arg;
}



int main() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("num = %d\n", num);
    assert(num == NUM_THREADS * 10000);
    return 0;
}