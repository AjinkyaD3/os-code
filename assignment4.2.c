#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define READERS 5
#define WRITERS 2

pthread_mutex_t mutex;
sem_t rw_mutex;
int readers_count = 0, shared_resource = 0;

void *reader(void *arg) {
    int id = *((int*) arg);
    while (1) {
        sleep(rand() % 3 + 1);
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1)
            sem_wait(&rw_mutex);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading: %d\n", id, shared_resource);

        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0)
            sem_post(&rw_mutex);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int*) arg);
    while (1) {
        sleep(rand() % 5 + 1);
        sem_wait(&rw_mutex);
        shared_resource++;
        printf("Writer %d is writing: %d\n", id, shared_resource);
        sem_post(&rw_mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[READERS], writer_threads[WRITERS];
    int reader_ids[READERS], writer_ids[WRITERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < WRITERS; i++)
        pthread_join(writer_threads[i], NULL);
    for (int i = 0; i < READERS; i++)
        pthread_join(reader_threads[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);
    return 0;
}

