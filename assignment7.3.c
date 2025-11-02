#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h> // Added for strlen

#define SHMSZ 1024 // Increased size

int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    char str[100];

    key = 5678; // Unique key for the segment

    // Create the shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Writing message to shared memory
    printf("Enter message from Server to Client: ");
    fgets(str, 100, stdin);

    s = shm;
    for (int i = 0; i < strlen(str); i++) {
        *s++ = str[i];
    }
    
    // CRITICAL FIX: Add the null terminator as a CHAR, not a STRING
    *s = '\0'; // Was "*s = "0";" which is a bug

    printf("Message written to shared memory successfully.\n");
    
    // Wait for the client to read it (just for this example)
    printf("Waiting for client to read (client will detach and remove)...\n");
    
    // Detach from shared memory
    shmdt(shm);

    return 0;
}

