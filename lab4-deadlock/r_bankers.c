#include <stdio.h>

#define MAX 100  // Maximum size for arrays

int available[MAX];
int maximum[MAX][MAX];
int allocation[MAX][MAX];
int need[MAX][MAX];
int finished[MAX];

void calculateNeed(int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int processes, int resources) {
    int work[MAX];
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        finished[i] = 0;
    }

    int safeSequence[MAX];
    int count = 0;

    while (count < processes) {
        int found = 0;
        for (int i = 0; i < processes; i++) {
            if (!finished[i]) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state!\n");
            return 0;
        }
    }

    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int processes, resources;
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum resources matrix: \n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter allocation matrix: \n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    calculateNeed(processes, resources);
    isSafe(processes, resources);
    
    return 0;
}
