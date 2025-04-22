#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

int compare(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

void fcfs(int requests[],int n,int head){
    int seek_time=0;
    int curr=head;

    printf("%d -> ",curr);
    for(int i=0;i<n;i++){
        seek_time += abs(requests[i]-curr);
        curr=requests[i];
        printf("%d -> ",curr);
    }

    printf("\nTotal seek time=%d\n",seek_time);
}

void sstf(int requests[],int n,int head){
    int seek_time=0;
    int curr=head;
    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;

    printf("%d -> ",curr);
    for(int i=0;i<n;i++){
        int min_dist=INT_MAX;
        int min_idx=-1;

        for(int j=0;j<n;j++){
            if(visited[j]==0){
                int dist = abs(requests[j]-curr);
                if(dist<min_dist){
                    min_dist=dist;
                    min_idx=j;
                }
            }
        }

        seek_time += min_dist;
        curr = requests[min_idx];
        visited[min_idx] = 1;
        printf("%d -> ", curr);
    }

    printf("\nThe total seek time is %d\n",seek_time);
}

void scan(int requests[],int n,int head,int disk_size,int direction){
    int seek_time=0;
    int curr=head;

    int left_arr[n];
    int right_arr[n];
    int left_cnt=0;
    int right_cnt=0;

    for(int i=0;i<n;i++){
        if(requests[i]>=head){
            right_arr[right_cnt++]=requests[i];
        }
        else{
            left_arr[left_cnt++]=requests[i];
        }
    }

    qsort(left_arr,left_cnt,sizeof(int),compare);
    qsort(right_arr,right_cnt,sizeof(int),compare);

    if(direction==1){
        for(int i=0;i<right_cnt;i++){
            seek_time += abs(right_arr[i]-curr);
            curr=right_arr[i];
            printf("%d -> ",curr);
        }

        for(int i=left_cnt-1;i>=0;i--){
            seek_time += abs(left_arr[i]-curr);
            curr = left_arr[i];
            printf("%d -> ",curr);
        }
    }
    else{
        for(int i=left_cnt-1;i>=0;i--){
            seek_time += abs(left_arr[i]-curr);
            curr = left_arr[i];
            printf("%d -> ",curr);
        }

        for(int i=0;i<right_cnt;i++){
            seek_time += abs(right_arr[i]-curr);
            curr = right_arr[i];
            printf("%d -> ",right_arr[i]);
        }
    }

    printf("\nSCAN total seek time: %d\n",seek_time);
}

void cscan(int requests[],int n,int head,int disk_size){
    int seek_time=0;
    int curr=head;

    int left_arr[n];
    int right_arr[n];
    int left_cnt=0;
    int right_cnt=0;

    for(int i=0;i<n;i++){
        if(requests[i]>=head){
            right_arr[right_cnt++]=requests[i];
        }
        else{
            left_arr[left_cnt++]=requests[i];
        }
    }

    qsort(left_arr,left_cnt,sizeof(int),compare);
    qsort(right_arr,right_cnt,sizeof(int),compare);

    for(int i=0;i<right_cnt;i++){
        seek_time += abs(right_arr[i]-curr);
        curr=right_arr[i];
        printf("%d -> ",curr);
    }

    seek_time += abs(curr - 0);
    curr=0;

    for(int i=0;i<left_cnt;i++){
        seek_time += abs(curr-left_arr[i]);
        curr = left_arr[i];
        printf("%d -> ",curr);
    }

    printf("\nSCAN total seek time: %d\n",seek_time);
}

int main(){
    int n, disk_size, head, direction;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter SCAN direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    printf("\n--- Disk Scheduling Algorithms ---\n\n");

    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    cscan(requests, n, head, disk_size);

    return 0;
}