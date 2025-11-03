#include <stdio.h> // io
#include <stdlib.h> // std
#include <sys/ipc.h> // ipc
#include <sys/shm.h> // shm
#include <string.h> // strcpy

int main() { // server creates and writes
    key_t key = ftok(".", 65); // make key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // create seg
    if (shmid < 0) { perror("shmget"); return 1; } // check
    char *data = (char*)shmat(shmid, NULL, 0); // attach
    if (data == (void*)-1) { perror("shmat"); return 1; } // check
    strcpy(data, "Hello from server via SysV shared memory!\n"); // write
    printf("server wrote message. Press Enter after client reads..."); // info
    getchar(); // wait for user
    shmdt(data); // detach
    shmctl(shmid, IPC_RMID, NULL); // remove seg
    return 0; // ok
}


