#include <stdio.h>

struct Process {
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
    int done;   // Flag to mark completion
};

// Function to sort processes by Arrival Time (if equal, sort by Burst Time)
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at || (p[j].at == p[j + 1].at && p[j].bt > p[j + 1].bt)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sjfScheduling(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1, minBT = 1e9; // Large initial value for minBT

        // Find the shortest job available at the current time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= currentTime) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // No process is available, move time forward
            currentTime++;
            continue;
        }

        // Process execution
        p[idx].ct = currentTime + p[idx].bt; // Completion Time
        p[idx].tat = p[idx].ct - p[idx].at; // Turnaround Time
        p[idx].wt = p[idx].tat - p[idx].bt; // Waiting Time
        p[idx].done = 1; // Mark as completed

        // Update time and completed count
        currentTime = p[idx].ct;
        completed++;

        // Add to total waiting time and turnaround time
        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
    }

    // Print results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1; // Assign Process ID
        p[i].done = 0;     // Mark all processes as not done initially
    }

    // Sort processes by arrival time
    sortByArrival(p, n);

    // Execute SJF Scheduling
    sjfScheduling(p, n);

    return 0;
}
