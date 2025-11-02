#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 1024

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678; // Same key as used by the server

    // Locate the segment created by server
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to our data space
    if ((shm = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Client reading data from Server:\n");
    
    // Read from shared memory
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    // The original didn't print a newline, so it looked weird.
    // If the server's message had one, this isn't needed.
    // But if it didn't, this ensures a clean output.
    printf("\n");

    // Detach from shared memory
    shmdt(shm);

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    
    printf("Client has read, detached, and removed the segment.\n");

    return 0;
}

