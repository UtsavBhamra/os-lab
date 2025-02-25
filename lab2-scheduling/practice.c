#include<stdio.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int wait_time;
};

void sortbyarrival(struct process p[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(p[i].priority<p[j].priority || (p[i].priority==p[j].priority && p[i].arrival_time>p[j].arrival_time)){
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculatetimes(struct process p[],int n){
    int total_wt=0;
    int total_tat=0;

    int time=0;

    for(int i=0;i<n;i++){
        if(time<p[i].arrival_time){
            time = p[i].arrival_time;
        }
        p[i].completion_time = time+p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].wait_time = p[i].turnaround_time-p[i].burst_time;

        total_wt += p[i].wait_time;
        total_tat += p[i].turnaround_time;

        time = p[i].completion_time;
    }

    printf("PID \t AT \t BT \t P \t WT \t TAT \t CT\n");
    for(int i=0;i<n;i++){
        printf("%d \t %d \t %d \t %d \t %d \t %d \t %d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].priority,p[i].wait_time,p[i].turnaround_time,p[i].completion_time);
    }

    printf("Avg wait time = %f\n",(float)total_wt/n);
    printf("Avg tat = %f\n",(float)total_tat/n);  
}

int main(){
    int n;
    printf("Enter the no of processes: ");
    scanf("%d",&n);

    struct process p[n];

    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("Enter the AT of process %d: ",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter the BT of process %d: ",i+1);
        scanf("%d",&p[i].burst_time);
        printf("Enter the priority of process %d: ",i+1);
        scanf("%d",&p[i].priority);
    }

    sortbyarrival(p,n);
    calculatetimes(p,n);
}