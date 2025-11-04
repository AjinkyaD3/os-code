/*
Problem Statement 5:
Thread synchronization using counting semaphores. Application to demonstrate
producer-consumer problem with counting semaphores and mutex.
*/
#include <stdio.h> // io
#include <stdlib.h> // std
#include <pthread.h> // threads
#include <semaphore.h> // semaphores
#include <unistd.h> // sleep

#define BUF 5 // buffer size
#define NITEMS 10 // total items to produce

int buffer[BUF]; // circular buffer
int in = 0, out = 0; // indices
sem_t emptySlots, filledSlots; // counting semaphores
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // mutex for buffer

void *producer(void *arg) { // producer thread
    for (int i = 1; i <= NITEMS; i++) { // produce NITEMS
        sem_wait(&emptySlots); // wait for empty slot
        pthread_mutex_lock(&lock); // lock buffer
        buffer[in] = i; // put item
        printf("produced %d at %d\n", i, in); // log
        in = (in + 1) % BUF; // move in
        pthread_mutex_unlock(&lock); // unlock
        sem_post(&filledSlots); // signal filled
        usleep(100000); // small delay
    }
    return NULL; // done
}

void *consumer(void *arg) { // consumer thread
    for (int c = 0; c < NITEMS; c++) { // consume NITEMS
        sem_wait(&filledSlots); // wait filled
        pthread_mutex_lock(&lock); // lock
        int x = buffer[out]; // get item
        printf("consumed %d from %d\n", x, out); // log
        out = (out + 1) % BUF; // move out
        pthread_mutex_unlock(&lock); // unlock
        sem_post(&emptySlots); // signal empty
        usleep(150000); // small delay
    }
    return NULL; // done
}

int main() { // main
    pthread_t pt, ct; // thread ids
    sem_init(&emptySlots, 0, BUF); // start with BUF empty
    sem_init(&filledSlots, 0, 0); // none filled
    pthread_create(&pt, NULL, producer, NULL); // start producer
    pthread_create(&ct, NULL, consumer, NULL); // start consumer
    pthread_join(pt, NULL); // wait producer
    pthread_join(ct, NULL); // wait consumer
    sem_destroy(&emptySlots); // cleanup
    sem_destroy(&filledSlots); // cleanup
    return 0; // ok
}


