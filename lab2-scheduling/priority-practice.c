#include <stdio.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

// Sort by Priority (Lower Value = Higher Priority), then by Arrival Time
void sortbypriority(struct process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority || 
                (p[i].priority == p[j].priority && p[i].arrival_time > p[j].arrival_time)) {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Calculate Completion Time, Turnaround Time, and Waiting Time
void calculatetimes(struct process p[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) {
            time = p[i].arrival_time;  // Adjust CPU idle time
        }
        p[i].completion_time = time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        time = p[i].completion_time;  // Move to next process
    }
}

// Print Process Table and Averages
void print(struct process p[], int n) {
    int total_tat = 0, total_wt = 0;

    printf("\nPID\tAT\tBT\tP\tCT\tTAT\tWT\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, 
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;  // Change PID to start from 1
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
    }

    sortbypriority(p, n);
    calculatetimes(p, n);
    print(p, n);

    return 0;
}
