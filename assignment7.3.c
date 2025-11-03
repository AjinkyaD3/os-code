#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMSZ 1024

int main() {
    key_t key = 5678;
    char str[100];

    int shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    char *shm = (char *)shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Enter message from Server to Client: ");
    fgets(str, 100, stdin);

    for (int i = 0; i < strlen(str); i++)
        shm[i] = str[i];
    shm[strlen(str)] = '\0';

    printf("Message written to shared memory successfully.\nWaiting for client to read (client will detach and remove)...\n");
    shmdt(shm);
    return 0;
}

