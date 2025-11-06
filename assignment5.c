#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
int buf[N], in=0, out=0;

sem_t empty, full;
pthread_mutex_t m;

void* producer(){
  for(int x=1;x<=10;x++){
    sem_wait(&empty);
    pthread_mutex_lock(&m);

    buf[in]=x;
    printf("P → %d\n", x);
    in=(in+1)%N;

    pthread_mutex_unlock(&m);
    sem_post(&full);
    usleep(80000);
  }
}

void* consumer(){
  for(int i=1;i<=10;i++){
    sem_wait(&full);
    pthread_mutex_lock(&m);

    int x=buf[out];
    printf("C ← %d\n", x);
    out=(out+1)%N;

    pthread_mutex_unlock(&m);
    sem_post(&empty);
    usleep(90000);
  }
}

int main(){
  pthread_t p,c;
  sem_init(&empty,0,N);
  sem_init(&full,0,0);
  pthread_mutex_init(&m,NULL);

  pthread_create(&p,NULL,producer,NULL);
  pthread_create(&c,NULL,consumer,NULL);
  pthread_join(p,NULL);
  pthread_join(c,NULL);
  return 0;
}