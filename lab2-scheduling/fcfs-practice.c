#include<stdio.h>

void findwaitingtime(int processes[],int n,int at[],int bt[],int wt[]){
    int service_time[n];
    service_time[0]=at[0];
    wt[0]=0;

    for(int i=1;i<n;i++){
        service_time[i] = service_time[i-1]+bt[i-1];
        wt[i] = service_time[i] - at[i];
        if(wt[i]<0){
            wt[i]=0;
        }
    }
}

void findturnaroundtime(int processes[],int n,int at[],int bt[],int wt[],int tat[],int ct[]){
    for(int i=0;i<n;i++){
        tat[i]=wt[i]+bt[i];
        ct[i] = (i == 0) ? (at[i] + bt[i]) : (ct[i - 1] > at[i] ? ct[i - 1] + bt[i] : at[i] + bt[i]);
    }
}

void findavgtime(int processes[],int n,int at[],int bt[]){
    int wt[n];
    int tat[n];
    int ct[n];
    int total_wt=0;
    int total_tat=0;

    findwaitingtime(processes,n,at,bt,wt);
    findturnaroundtime(processes,n,at,bt,wt,tat,ct);

    printf("\npid \t at \t bt \t wt \t tat \t ct\n");
    for(int i=0;i<n;i++){
        total_wt+=wt[i];
        total_tat+=tat[i];
        printf("%d \t %d \t %d \t %d \t %d \t %d\n",processes[i],at[i],bt[i],wt[i],tat[i],ct[i]);
    }

    printf("Average wating time = %f\n",(float)total_wt/n);
    printf("Average turn around time=%f\n",(float)total_tat/n);
}

int main(){
    int n;
    printf("Enter the no of processes: ");
    scanf("%d",&n);

    int processes[n];
    int arrival_time[n];
    int burst_time[n];

    for(int i=0;i<n;i++){
        processes[i]=i;
        printf("Enter AT for process %d: ",i);
        scanf("%d",&arrival_time[i]);
        printf("Enter BT for process %d: ",i);
        scanf("%d",&burst_time[i]);
    }

    findavgtime(processes,n,arrival_time,burst_time);
    return 0;
}