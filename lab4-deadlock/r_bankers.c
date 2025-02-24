#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int available[R] = {3, 3, 2}; // Available instances of resources
int maximum[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
}; // Maximum demand of each process
int allocation[P][R] = {
    {0, 1, 0},
    {4, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
}; // Resources currently allocated to each process
int need[P][R]; // Remaining resource need of each process

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[R];
    bool finish[P] = {false};

    // Initialize work array with available resources
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // Find an index i such that both conditions are satisfied:
    // 1. finish[i] == false
    // 2. need[i] <= work
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    // Release the resources after the process completes
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            // No such process found, system is not in a safe state
            return false;
        }
    }
    // All processes finished, system is in a safe state
    return true;
}

bool requestResources(int process, int request[R]) {
    // Check if the request is less than or equal to the need
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if the request is less than or equal to the available resources
    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    // Try to allocate the resources temporarily
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is still in a safe state
    if (isSafe()) {
        printf("Request granted. System is in a safe state.\n");
        return true;
    } else {
        // Rollback the allocation
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    calculateNeed();

    // Example request: Process 1 requests [1, 0, 2] resources
    int request[R] = {1, 0, 2};
    int process = 1;

    if (requestResources(process, request)) {
        printf("Resources allocated successfully.\n");
    } else {
        printf("Resources could not be allocated.\n");
    }

    return 0;
}

