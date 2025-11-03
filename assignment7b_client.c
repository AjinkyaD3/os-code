#include <stdio.h> // io
#include <stdlib.h> // std
#include <sys/ipc.h> // ipc
#include <sys/shm.h> // shm

int main() { // client reads and shows
    key_t key = ftok(".", 65); // same key
    int shmid = shmget(key, 1024, 0666); // get seg
    if (shmid < 0) { perror("shmget"); return 1; } // check
    char *data = (char*)shmat(shmid, NULL, 0); // attach
    if (data == (void*)-1) { perror("shmat"); return 1; } // check
    printf("client read: %s", data); // show
    shmdt(data); // detach
    return 0; // ok
}


