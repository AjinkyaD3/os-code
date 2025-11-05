/*
Problem Statement 6:
Thread synchronization and mutual exclusion using mutex. Application to demonstrate
Reader-Writer problem with reader priority.
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int rc=0;
pthread_mutex_t rlock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wlock=PTHREAD_MUTEX_INITIALIZER;

void* reader(void *id){
  for(int i=0;i<3;i++){
    pthread_mutex_lock(&rlock);
    rc++;
    if(rc==1) pthread_mutex_lock(&wlock);
    pthread_mutex_unlock(&rlock);

    printf("R%d reading\n", *(int*)id);
    usleep(80000);

    pthread_mutex_lock(&rlock);
    rc--;
    if(rc==0) pthread_mutex_unlock(&wlock);
    pthread_mutex_unlock(&rlock);
  }
}

void* writer(void *id){
  for(int i=0;i<3;i++){
    pthread_mutex_lock(&wlock);
    printf("W%d writing\n", *(int*)id);
    pthread_mutex_unlock(&wlock);
    usleep(100000);
  }
}

int main(){
  pthread_t r[3], w[2];
  int ri[3]={1,2,3}, wi[2]={1,2};
  for(int i=0;i<3;i++) pthread_create(&r[i],NULL,reader,&ri[i]);
  for(int i=0;i<2;i++) pthread_create(&w[i],NULL,writer,&wi[i]);
  for(int i=0;i<3;i++) pthread_join(r[i],NULL);
  for(int i=0;i<2;i++) pthread_join(w[i],NULL);
}