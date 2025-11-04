/*
Problem Statement 6:
Thread synchronization and mutual exclusion using mutex. Application to demonstrate
Reader-Writer problem with reader priority.
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int readCount = 0;
pthread_mutex_t readCountLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resourceLock = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 3; i++) {

        pthread_mutex_lock(&readCountLock);
        readCount++;
        if(readCount == 1)
            pthread_mutex_lock(&resourceLock); // First reader blocks writer
        pthread_mutex_unlock(&readCountLock);

        printf("Reader %d is reading\n", id);
        usleep(100000);

        pthread_mutex_lock(&readCountLock);
        readCount--;
        if(readCount == 0)
            pthread_mutex_unlock(&resourceLock); // Last reader allows writer
        pthread_mutex_unlock(&readCountLock);

        usleep(80000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int*)arg;
    for(int i = 0; i < 3; i++) {
        pthread_mutex_lock(&resourceLock);
        printf("Writer %d is writing\n", id);
        usleep(150000);
        pthread_mutex_unlock(&resourceLock);
        usleep(120000);
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1,2,3};
    int wid[2] = {1,2};

    for(int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, &rid[i]);
    for(int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &wid[i]);

    for(int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for(int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    return 0;
}
