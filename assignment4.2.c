#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h> // For rand()

#define READERS 5
#define WRITERS 2

pthread_mutex_t mutex;
sem_t rw_mutex; // Renamed from "sem_trw"
int readers_count = 0; // Fixed variable name
int shared_resource = 0;

void *reader(void *arg) {
    int id = *((int*) arg);
    while (1) {
        sleep(rand() % 3 + 1); // Read every 1-3 seconds

        // Entry section
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1) { // Fixed '=='
            sem_wait(&rw_mutex); // If I'm the first reader, lock out writers
        }
        pthread_mutex_unlock(&mutex);

        // --- Critical Section (Reading) ---
        printf("Reader %d is reading: %d\n", id, shared_resource);
        // --- End of Critical Section ---

        // Exit section
        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) { // Fixed '=='
            sem_post(&rw_mutex); // If I'm the last reader, allow writers
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int*) arg);
    while (1) {
        sleep(rand() % 5 + 1); // Write every 1-5 seconds

        // Entry section
        sem_wait(&rw_mutex); // Lock for writing

        // --- Critical Section (Writing) ---
        shared_resource++;
        printf("Writer %d is writing: %d\n", id, shared_resource);
        // --- End of Critical Section ---

        // Exit section
        sem_post(&rw_mutex); // Fixed "sem post"
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[READERS], writer_threads[WRITERS];
    int reader_ids[READERS], writer_ids[WRITERS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1); // 0 for thread-sharing, 1 initial value

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    
    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Join threads (this program will run forever, so this is illustrative)
    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }
    for (int i = 0; i < READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

