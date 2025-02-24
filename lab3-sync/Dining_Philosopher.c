#include <pthread.h>   // For pthreads (thread management)
#include <semaphore.h> // For semaphores (mutex and fork control)
#include <stdio.h>     // For input/output functions
#include <unistd.h>    // For sleep function

// Number of philosophers
#define N 5

// Philosopher states
#define THINKING 2
#define HUNGRY 1
#define EATING 0

// Macros to determine the left and right fork for a philosopher
#define LEFT (phnum + 4) % N   // Left neighbor
#define RIGHT (phnum + 1) % N  // Right neighbor

// Shared data structures
int state[N];        // Array to track each philosopher's state
int phil[N] = { 0, 1, 2, 3, 4 }; // Philosopher IDs

sem_t mutex;         // Mutex to protect critical section (shared data)
sem_t S[N];          // Array of semaphores, one per philosopher

/**
 * Function to check if a hungry philosopher can start eating
 * It ensures that both the left and right forks are available.
 */
void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING; // Change state to EATING
        sleep(2); // Simulate eating time

        // Print which philosopher is eating and which forks are being used
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);

        sem_post(&S[phnum]); // Signal that the philosopher can eat
    }
}

/**
 * Function to handle picking up forks.
 * A philosopher will try to take both forks (left & right) before eating.
 */
void take_fork(int phnum) {
    sem_wait(&mutex); // Lock the critical section, sem_wait is used to block a waiting thread and is used before entering a critical section

    state[phnum] = HUNGRY; // Mark philosopher as hungry
    printf("Philosopher %d is Hungry\n", phnum + 1);

    test(phnum); // Try to pick up forks and start eating

    sem_post(&mutex); // Unlock the critical section
    sem_wait(&S[phnum]); // Wait until forks are available
    sleep(1); // Simulate the action of picking up forks
}

/**
 * Function to handle putting down forks after eating.
 * It also signals the left and right neighbors that they can eat.
 */
void put_fork(int phnum) {
    sem_wait(&mutex); // Lock the critical section

    state[phnum] = THINKING; // Mark philosopher as thinking
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);  // Check if left neighbor can now eat
    test(RIGHT); // Check if right neighbor can now eat

    sem_post(&mutex); // Unlock the critical section
}

/**
 * Function representing each philosopher.
 * Philosophers alternate between thinking and eating in an infinite loop.
 */
void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1); // Thinking
        take_fork(*i); // Try to take forks and eat
        sleep(0); // Eating duration (effectively instant)
        put_fork(*i); // Put down forks after eating
    }
}

/**
 * Main function: Initializes semaphores, creates philosopher threads, and waits for them.
 */
int main() {
    int i;
    pthread_t thread_id[N]; // Array to store philosopher thread IDs

    sem_init(&mutex, 0, 1); // Initialize the mutex with value 1

    // Initialize semaphores for each philosopher (binary semaphores)
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    // Wait for all threads to finish (this never actually happens)
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL); 

    return 0;
}
