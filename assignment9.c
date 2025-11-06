#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int c,char *v[]){
    key_t k = ftok(".",65);
    int id = shmget(k,1024,0666|IPC_CREAT);
    char *p = shmat(id,0,0);

    if(c>1 && !strcmp(v[1],"--server")){
        printf("[Server] enter message: ");
        fgets(p,1024,stdin);
        getchar();
        shmdt(p); 
        shmctl(id,IPC_RMID,0);
    } 
    else if(c>1 && !strcmp(v[1],"--client")){
        puts(p);
        shmdt(p);
    }
}
