#include <stdio.h>
#include <stdlib.h> // For exit
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h> // For sleep

#define BUFFER_SIZE 10

char avbuff[BUFFER_SIZE];
sem_t mutex, empty, full;
int in = 0;
int out = 0;

void *produce(void *arg) {
    int i;
    printf("Producer started...\n");
    for (i = 0; i < 20; i++) { // Produce 20 items
        sem_wait(&empty); // Wait if buffer is full
        sem_wait(&mutex); // Lock critical section

        // Produce item
        avbuff[in] = (char)('A' + (i % 26));
        printf("Produced: %c\n", avbuff[in]);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Unlock critical section
        sem_post(&full);  // Signal that buffer is no longer empty
        
        sleep(1); // Simulate time to produce
    }
    printf("Producer finished.\n");
    pthread_exit(NULL); // Use NULL in C
}

void *consumer(void *arg) {
    int j;
    char item;
    printf("Consumer started...\n");
    for (j = 0; j < 20; j++) { // Consume 20 items
        sem_wait(&full);  // Wait if buffer is empty
        sem_wait(&mutex); // Lock critical section

        // Consume item
        item = avbuff[out];
        printf("Consumed: %c\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Unlock critical section
        sem_post(&empty); // Signal that buffer is no longer full
        
        sleep(2); // Simulate time to consume
    }
    printf("Consumer finished.\n");
    pthread_exit(NULL); // Use NULL in C
}

int main() {
    pthread_t tid1, tid2;

    // Initialize semaphores
    // empty = BUFFER_SIZE (all slots are empty)
    // full = 0 (no slots are full)
    // mutex = 1 (binary semaphore for mutual exclusion)
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1); // 0 for thread-sharing, 1 for process-sharing

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Main thread exiting.\n");
    
    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}

