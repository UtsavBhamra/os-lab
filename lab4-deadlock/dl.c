#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES]; // Allocation matrix
int request[MAX_PROCESSES][MAX_RESOURCES];    // Request matrix
int available[MAX_RESOURCES];                 // Available resources
bool finish[MAX_PROCESSES];                   // Process finish status

int n, m; // n = number of processes, m = number of resources

// Function to check for deadlock
void detectDeadlock() {
    int work[MAX_RESOURCES];
    for (int i = 0; i < m; i++) {
        work[i] = available[i]; // Initialize work with available resources
    }

    for (int i = 0; i < n; i++) {
        finish[i] = false; // Mark all processes as unfinished
    }

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) { // If process is not finished
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) { // If process needs more than available
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) { // If process can finish, update available resources
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress); // Repeat until no progress can be made

    // Check for deadlock
    bool deadlock = false;
    printf("Deadlocked Processes: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock) {
        printf("None (No Deadlock Detected)");
    }
    printf("\n");
}

int main() {
    // Input the number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Request Matrix
    printf("Enter request matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Call Deadlock Detection Function
    detectDeadlock();

    return 0;
}


