#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t full;
sem_t empty;
int x=0;

void* producer(){
    while(1){
        if (sem_trywait(&empty) != 0) {  // Check if buffer is full
            printf("Buffer is FULL! Producer is waiting...\n");
            sem_wait(&empty);  // Block until space is available
        }
        sem_wait(&mutex);

        x++;
        printf("producer produced item %d\n",x);

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void* consumer(){
    while(1){
        if(sem_trywait(&full)!=0){
            printf("Buffer is EMPTY! Consumer is waiting...\n");
            sem_wait(&full);
        }
        sem_wait(&mutex);

        printf("Consumer consumed item %d\n",x);
        x--;

        sem_post(&mutex);
        sem_post(&empty);
        sleep(3);
    }
}

int main(){
    int buffer;
    printf("enter the buffer size: ");
    scanf("%d",&buffer);

    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,buffer);

    pthread_t producer_t,consumer_t;

    pthread_create(&producer_t,NULL,producer,NULL);
    pthread_create(&consumer_t,NULL,consumer,NULL);

    pthread_join(producer_t,NULL);
    pthread_join(consumer_t,NULL);

    return 0;
}
