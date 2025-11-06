#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int rc = 0;
pthread_mutex_t rc_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t w_lock  = PTHREAD_MUTEX_INITIALIZER;

void* reader(void* id){
    int r = *(int*)id;
    for(int i=0;i<3;i++){

        pthread_mutex_lock(&rc_lock);
        if(++rc == 1) pthread_mutex_lock(&w_lock);
        pthread_mutex_unlock(&rc_lock);

        printf("R%d reading\n", r);
        usleep(80000);

        pthread_mutex_lock(&rc_lock);
        if(--rc == 0) pthread_mutex_unlock(&w_lock);
        pthread_mutex_unlock(&rc_lock);
    }
}

void* writer(void* id){
    int w = *(int*)id;
    for(int i=0;i<3;i++){
        pthread_mutex_lock(&w_lock);
        printf("W%d writing\n", w);
        pthread_mutex_unlock(&w_lock);
        usleep(100000);
    }
}

int main(){
    pthread_t r[3], w[2];
    int ri[]={1,2,3}, wi[]={1,2};

    for(int i=0;i<3;i++) pthread_create(&r[i],0,reader,&ri[i]);
    for(int i=0;i<2;i++) pthread_create(&w[i],0,writer,&wi[i]);

    for(int i=0;i<3;i++) pthread_join(r[i],0);
    for(int i=0;i<2;i++) pthread_join(w[i],0);
}