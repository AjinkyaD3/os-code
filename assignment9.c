/*
Problem Statement 9:
Programs in which server process creates a shared memory segment and writes the
message to the shared memory segment. Client process reads the message from the
shared memory segment and displays it to the screen.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int server_mode() {
    key_t key = ftok(".", 65);              // generate key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // create shared memory
    if (shmid < 0) { perror("shmget"); return 1; }

    char *data = (char*)shmat(shmid, NULL, 0); // attach
    if (data == (void*)-1) { perror("shmat"); return 1; }

    strcpy(data, "Hello from server via Shared Memory!\n"); // write message
    printf("Server wrote message. Press Enter after client reads...");
    getchar();

    shmdt(data);                       // detach
    shmctl(shmid, IPC_RMID, NULL);     // remove shared memory
    return 0;
}

int client_mode() {
    key_t key = ftok(".", 65);              // same key
    int shmid = shmget(key, 1024, 0666);    // get shared memory
    if (shmid < 0) { perror("shmget"); return 1; }

    char *data = (char*)shmat(shmid, NULL, 0); // attach
    if (data == (void*)-1) { perror("shmat"); return 1; }

    printf("Client read: %s", data);  // read message

    shmdt(data);   // detach
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--server") == 0)
        return server_mode();
    if (argc > 1 && strcmp(argv[1], "--client") == 0)
        return client_mode();

    printf("Usage: %s --server | --client\n", argv[0]);
    return 0;
}
