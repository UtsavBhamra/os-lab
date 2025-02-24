#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,wrt;
int readercount=0;
int count=5;

pthread_t reader1,reader2,writer1,writer2;

void *reader(void *p){
    
}

int main(){
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    while(count--){
        pthread_create(&reader1,NULL,reader,"1");
        pthread_create(&reader2,NULL,reader,"2");
        pthread_create(&writer1,NULL,writer,"1");
        pthread_create(&writer2,NULL,writer,"2");
    }
    return 0;
}