#include<stdio.h>
#include<stdlib.h>

int compare(const void* a, const void* b){
    return *(int *)a - *(int *)b;
}

void fcfs(int requests[],int n,int head){
    int seek_time=0;
    int curr=head;

    printf("%d -> ",curr);
    for(int i=0;i<n;i++){
        seek_time += abs(requests[i]-curr);
        curr = requests[i];
        printf("%d -> ",requests[i]);
    }
    printf("\n");

    printf("Total seek time = %d\n",seek_time);
}

void sstf(int requests[],int n,int head){
    int total_seek_time=0;
    int curr=head;

    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;

    for(int i=0;i<n;i++){
        int min_dist = 1e6;
        int min_idx = -1;

        for(int j=0;j<n;j++){
            if(!visited[j]){
                int dist = abs(requests[i]-curr);
                if(dist<min_dist){
                    min_dist=dist;
                    min_idx=j;
                }
            }
        }

        total_seek_time += min_dist;
        curr=requests[min_idx];
        visited[min_idx]=1;
    }

    printf("total seek time = %d\n",total_seek_time);
}

void scan(int requests[],int n,int head,int disk_size,int direction){
    int total_seek_time=0;  
    int curr=head;

    int left_arr[n];
    int right_arr[n];
    int left_cnt=0;
    int right_cnt=0;

    for(int i=0;i<n;i++){
        if(requests[i]<head){
            left_arr[left_cnt++] = requests[i];
        }
        else{
            right_arr[right_cnt++] = requests[i];
        }
    }

    qsort(left_arr,left_cnt,sizeof(int),compare);
    qsort(right_arr,right_cnt,sizeof(int),compare);

    if(direction==1){
        total_seek_time += 2*abs(disk_size-curr);
        total_seek_time += abs(left_arr[0]-curr);

        for(int i=0;i<right_cnt;i++){
            printf("%d -> ",right_arr[i]);
        }
        printf("%d -> ",disk_size);
        for(int i=left_cnt-1;i>=0;i--){
            printf("%d -> ",left_arr[i]);
        }
    }
    else{
        total_seek_time += 2*abs(curr);
        total_seek_time += abs(right_arr[right_cnt-1]-curr);

        printf("%d -> ",curr);
        for(int i=left_cnt-1;i>=0;i--){
            printf("%d -> ",left_arr[i]);
        }
        printf("%d -> ",0);
        for(int i=0;i<right_cnt;i++){
            printf("%d -> ",right_arr[i]);
        }
    }   
}

int main(){

    return 0;
}