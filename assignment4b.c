/*
Problem Statement 6:
Thread synchronization and mutual exclusion using mutex. Application to demonstrate
Reader-Writer problem with reader priority.
*/
#include <stdio.h> // io
#include <stdlib.h> // std
#include <pthread.h> // threads
#include <unistd.h> // sleep

int readCount = 0; // number of active readers
pthread_mutex_t readCountLock = PTHREAD_MUTEX_INITIALIZER; // protects readCount
pthread_mutex_t resourceLock = PTHREAD_MUTEX_INITIALIZER; // controls writers/readers

void *reader(void *arg) { // reader thread
    int id = *(int*)arg; // reader id
    for (int k = 0; k < 3; k++) { // read a few times
        pthread_mutex_lock(&readCountLock); // lock readCount
        readCount++; // one more reader
        if (readCount == 1) pthread_mutex_lock(&resourceLock); // first reader locks resource
        pthread_mutex_unlock(&readCountLock); // unlock counter

        printf("reader %d reading\n", id); // simulate read
        usleep(100000); // delay

        pthread_mutex_lock(&readCountLock); // lock counter
        readCount--; // leaving
        if (readCount == 0) pthread_mutex_unlock(&resourceLock); // last reader unlocks resource
        pthread_mutex_unlock(&readCountLock); // unlock counter
        usleep(80000); // small gap
    }
    return NULL; // done
}

void *writer(void *arg) { // writer thread
    int id = *(int*)arg; // writer id
    for (int k = 0; k < 3; k++) { // write a few times
        pthread_mutex_lock(&resourceLock); // exclusive access
        printf("writer %d writing\n", id); // simulate write
        usleep(150000); // delay
        pthread_mutex_unlock(&resourceLock); // release
        usleep(120000); // gap
    }
    return NULL; // done
}

int main() { // main
    pthread_t r[3], w[2]; // threads
    int ri[3] = {1,2,3}; // ids
    int wi[2] = {1,2}; // ids
    for (int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, &ri[i]); // start readers
    for (int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &wi[i]); // start writers
    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL); // wait readers
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL); // wait writers
    return 0; // ok
}


