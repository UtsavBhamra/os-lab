#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declare semaphores for synchronization
sem_t mutex, wrt;  // `mutex` for controlling access to `readercount`, `wrt` for writer exclusivity
int readercount = 0; // Tracks the number of active readers
int count = 5; // Number of iterations for creating reader and writer threads

// Thread variables
pthread_t reader1, reader2, writer1, writer2;

// Function prototypes
void *reader(void *);
void *writer(void *);

int main()
{
    // Initialize semaphores
    sem_init(&mutex, 0, 1); // `mutex` initialized to 1, used for reader count protection
    sem_init(&wrt, 0, 1);   // `wrt` initialized to 1, allows exclusive access for writers

    while (count--)  // Loop to create multiple reader and writer threads
    {
        pthread_create(&reader1, NULL, reader, "1"); // Create reader thread with argument "1"
        pthread_create(&reader2, NULL, reader, "2"); // Create reader thread with argument "2"
        pthread_create(&writer1, NULL, writer, "1"); // Create writer thread with argument "1"
        pthread_create(&writer2, NULL, writer, "2"); // Create writer thread with argument "2"
    }

    return 0; // Program exits without waiting for threads to complete (should use pthread_join)
}

// Reader function
void *reader(void *p)
{
    sem_wait(&mutex); // Lock access to `readercount`
    readercount++;    // Increment reader count

    if (readercount == 1) 
        sem_wait(&wrt); // If first reader, block writers by acquiring `wrt`

    sem_post(&mutex); // Unlock access to `readercount`

    // Critical section (reading)
    printf("Reader %s is Reading\n", (char *)p);

    sem_wait(&mutex); // Lock access to `readercount`
    printf("Reader %s Completed Reading\n", (char *)p);
    readercount--;    // Decrement reader count

    if (readercount == 0) 
        sem_post(&wrt); // If last reader, release writer lock

    sem_post(&mutex); // Unlock access to `readercount`
}

// Writer function
void *writer(void *p)
{
    printf("Writer %s is Waiting\n", (char *)p);

    sem_wait(&wrt); // Acquire exclusive write lock

    // Critical section (writing)
    printf("Writer %s is writing\n", (char *)p);
    
    sem_post(&wrt); // Release write lock
    printf("Writing %s Completed\n", (char *)p);
}
