#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;   // Binary semaphore for mutual exclusion
sem_t full;    // Counts the number of full slots
sem_t empty;   // Counts the number of empty slots
int x = 0;     // Item count (simulating buffer)

void* producer(void* arg) {
    while (1) {
        sem_wait(&empty);  // Decrement empty count (wait if buffer is full)
        sem_wait(&mutex);  // Lock critical section

        x++;
        printf("Producer produced item %d\n", x);

        sem_post(&mutex);  // Unlock critical section
        sem_post(&full);   // Increment full count (signal consumer)

        sleep(1);  // Simulate production delay
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);   // Decrement full count (wait if buffer is empty)
        sem_wait(&mutex);  // Lock critical section

        printf("Consumer consumed item %d\n", x);
        x--;

        sem_post(&mutex);  // Unlock critical section
        sem_post(&empty);  // Increment empty count (signal producer)

        sleep(1);  // Simulate consumption delay
    }
}

int main() {
    int buffer_size;
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);

    // Initialize semaphores
    sem_init(&mutex, 0, 1);        // Binary semaphore for mutual exclusion
    sem_init(&full, 0, 0);         // Initially, buffer is empty
    sem_init(&empty, 0, buffer_size); // Initially, buffer has 'buffer_size' empty slots

    pthread_t prod_thread, cons_thread;

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish (they won't since it's an infinite loop)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores (this will never be reached in this case)
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
