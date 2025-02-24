#include <stdio.h>

// Structure to store process details
typedef struct {
    int pid;               // Process ID
    int arrival_time;      // Arrival Time
    int burst_time;        // Burst Time
    int remaining_time;    // Remaining time (used during execution)
    int completion_time;   // Completion Time
    int waiting_time;      // Waiting Time
    int turnaround_time;   // Turnaround Time
} Process;

// Function to implement Round Robin Scheduling
void round_robin(Process proc[], int n, int quantum) {
    int time = 0;          // Current time
    int completed = 0;     // Number of processes completed
    int i, flag;

    // Run the scheduling loop until all processes are completed
    while (completed < n) {
        flag = 0; // Flag to check if any process is executed in this cycle

        for (i = 0; i < n; i++) {
            // Check if process has remaining execution time and has arrived
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time) {
                flag = 1; // At least one process is still executing

                if (proc[i].remaining_time > quantum) {
                    // If remaining time is greater than quantum, execute for quantum
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    // If remaining time is less than or equal to quantum, complete the process
                    time += proc[i].remaining_time;
                    proc[i].completion_time = time;

                    // Calculate Turnaround Time = Completion Time - Arrival Time
                    proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;

                    // Calculate Waiting Time = Turnaround Time - Burst Time
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

                    proc[i].remaining_time = 0; // Mark process as completed
                    completed++; // Increment completed process count
                }
            }
        }

        // If no process was executed in this cycle, increase time to the next arrival
        if (!flag) time++;
    }
}

// Main function
int main() {
    int n, quantum, i;

    // Take input for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n]; // Array of processes

    // Taking input for arrival time and burst time
    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1; // Assign process ID
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &proc[i].burst_time);

        proc[i].remaining_time = proc[i].burst_time; // Initialize remaining time
    }

    // Taking input for time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Call Round Robin Scheduling function
    round_robin(proc, n, quantum);

    // Displaying the scheduling results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }

    return 0;
}
