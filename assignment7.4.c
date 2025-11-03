#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ 1024

int main() {
    key_t key = 5678;
    int shmid = shmget(key, SHMSZ, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    char *shm = (char *)shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Client reading data from Server:\n");
    for (char *s = shm; *s != '\0'; s++)
        putchar(*s);
    printf("\n");

    shmdt(shm);
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    printf("Client has read, detached, and removed the segment.\n");
    return 0;
}

