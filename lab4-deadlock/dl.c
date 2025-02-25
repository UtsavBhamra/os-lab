#include <stdio.h>

#define MAX 100  // Maximum number of processes/resources

int allocation[MAX][MAX];  // Resources currently allocated to processes
int request[MAX][MAX];     // Additional resources requested by processes
int available[MAX];        // Available resources
int finished[MAX];         // Tracks if a process has finished

// Function to check for deadlock
void detectDeadlock(int p, int r) {
    int work[MAX];  // Work array to track available resources
    int deadlocked[MAX];  // Stores deadlocked process IDs
    int deadlock_count = 0;

    // Initialize work = available
    for (int i = 0; i < r; i++) {
        work[i] = available[i];
    }

    // Initialize finished array (0 = not finished)
    for (int i = 0; i < p; i++) {
        finished[i] = 0;
    }

    int progress = 1; // Flag to track progress in each iteration

    while (progress) {
        progress = 0;  // Reset progress for each loop iteration

        for (int i = 0; i < p; i++) {
            if (!finished[i]) {  // If process is not finished
                int j;
                for (j = 0; j < r; j++) {
                    if (request[i][j] > work[j]) {  // If request cannot be satisfied
                        break;
                    }
                }

                if (j == r) {  // If all requests can be satisfied
                    for (int k = 0; k < r; k++) {
                        work[k] += allocation[i][k];  // Release resources
                    }
                    finished[i] = 1;  // Mark process as completed
                    progress = 1;  // Set flag to indicate progress
                }
            }
        }
    }

    // Check for unfinished processes (indicating deadlock)
    for (int i = 0; i < p; i++) {
        if (!finished[i]) {
            deadlocked[deadlock_count++] = i;
        }
    }

    if (deadlock_count > 0) {
        printf("Deadlock detected! Processes involved: ");
        for (int i = 0; i < deadlock_count; i++) {
            printf("%d ", deadlocked[i]);
        }
        printf("\n");
    } else {
        printf("No deadlock detected. System is safe.\n");
    }
}

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input request matrix
    printf("Enter request matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &available[i]);
    }

    // Detect deadlock
    detectDeadlock(p, r);

    return 0;
}
