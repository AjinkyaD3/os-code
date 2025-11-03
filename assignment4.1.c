#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

char avbuff[BUFFER_SIZE];
sem_t mutex, empty, full;
int in = 0, out = 0;

void *produce(void *arg) {
    printf("Producer started...\n");
    for (int i = 0; i < 20; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        avbuff[in] = (char)('A' + (i % 26));
        printf("Produced: %c\n", avbuff[in]);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    printf("Producer finished.\n");
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    printf("Consumer started...\n");
    for (int j = 0; j < 20; j++) {
        sem_wait(&full);
        sem_wait(&mutex);
        printf("Consumed: %c\n", avbuff[out]);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    printf("Consumer finished.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Main thread exiting.\n");
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

