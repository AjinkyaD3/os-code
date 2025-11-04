/*
Problem Statement 5:
Thread synchronization using counting semaphores. Application to demonstrate
producer-consumer problem with counting semaphores and mutex.
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF 5        // Buffer size
#define NITEMS 10    // Number of items to produce/consume

int buffer[BUF];
int in = 0, out = 0;

sem_t emptySlots, filledSlots;
pthread_mutex_t lock;

void *producer(void *arg) {
    for(int i = 1; i <= NITEMS; i++) {
        sem_wait(&emptySlots);            // Wait for empty slot
        pthread_mutex_lock(&lock);        // Lock buffer

        buffer[in] = i;
        printf("Producer produced %d at index %d\n", i, in);
        in = (in + 1) % BUF;

        pthread_mutex_unlock(&lock);      // Unlock buffer
        sem_post(&filledSlots);           // Signal consumer
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for(int i = 1; i <= NITEMS; i++) {
        sem_wait(&filledSlots);           // Wait for available item
        pthread_mutex_lock(&lock);        // Lock buffer

        int x = buffer[out];
        printf("Consumer consumed %d from index %d\n", x, out);
        out = (out + 1) % BUF;

        pthread_mutex_unlock(&lock);      // Unlock buffer
        sem_post(&emptySlots);            // Signal producer
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&emptySlots, 0, BUF);
    sem_init(&filledSlots, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);
    pthread_mutex_destroy(&lock);

    return 0;
}
