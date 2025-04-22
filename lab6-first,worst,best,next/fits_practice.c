#include<stdio.h>

typedef struct {
    int size;
    int original_size;
    int allocated;
} Block;

typedef struct {
    int size;
    int block_index;
} Process;

void first_fit(Block blocks[],int m, Process processes[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!blocks[j].allocated && processes[i].size<=blocks[j].size){
                blocks[j].size -= processes[i].size;
                blocks[j].allocated=1;
                processes[i].block_index=j;
                break;
            }
        }
    }

    for(int i=0;i<n;i++){
        if(processes[i].block_index!=-1){
            printf("Process %d was allocated to block with index %d\n",i,processes[i].block_index);
        }
        else{
            printf("Process %d was not allocated\n",i);
        }
    }
}

void best_fit(Block blocks[],int m,Process processes[],int n){
    for(int i=0;i<n;i++){
        int min_block_idx=-1;
        for(int j=0;j<m;j++){
            if(!blocks[j].allocated && blocks[j].size>=processes[i].size){
                if(min_block_idx==-1 || blocks[min_block_idx].size>=blocks[j].size){
                    min_block_idx=j;
                }
            }
        }

        if(min_block_idx!=-1){
            blocks[min_block_idx].allocated=1;
            blocks[min_block_idx].size-=processes[i].size;
            processes[i].block_index=min_block_idx;
            printf("Process %d was allocated to block with idx %d\n",i,min_block_idx);
        }
        else{
            printf("Process %d was not allocated\n",i);
        }
    }
}

void worst_fit(Block blocks[],int m, Process processes[],int n){
    for(int i=0;i<n;i++){
        int max_block_idx=-1;
        for(int j=0;j<m;j++){
            if(!blocks[j].allocated && blocks[j].size>=processes[i].size){
                if(max_block_idx==-1 || blocks[j].size>=blocks[max_block_idx].size){
                    max_block_idx=j;
                }
            }
        }

        if(max_block_idx!=-1){
            blocks[max_block_idx].allocated=1;
            blocks[max_block_idx].size-=processes[i].size;
            processes[i].block_index=max_block_idx;
            printf("Process %d was allocated to block %d\n",i,max_block_idx);
        }
        else{
            printf("process %d was not allocated\n",i);
        }
    }
}

void next_fit(Block blocks[],int m, Process processes[],int n){
    
    int last_idx=-1;
    for(int i=0;i<n;i++){
        int count=0;
        int j=last_idx;
        while(count<m){
            if(!blocks[j].allocated && blocks[j].size>=processes[i].size){
                processes[i].block_index=j;
                blocks[j].allocated=1;
                blocks[j].size-=processes[i].size;
                last_idx=(j+1)%m;
                break;
            }
            j=(j+1)%m;
            count++;
        }
    }


    for(int i=0;i<n;i++){
        if(processes[i].block_index!=-1){
            printf("process %d was allocated to block %d\n",i,processes[i].block_index);
        }
        else{
            printf("Process %d was not allocated\n",i);
        }
    }
}

int main(){
    int m,n;
    printf("enter the number of blocks: ");
    scanf("%d",&m);
    Block blocks[m];
    for(int i=0;i<m;i++){
        printf("Enter block %d size: ",i);
        scanf("%d",&blocks[i].original_size);
        blocks[i].size=blocks[i].original_size;
        blocks[i].allocated=0;
    }

    printf("Enter the number of processes: ");
    scanf("%d",&n);

    Process processes[n];
    for(int i=0;i<n;i++){
        printf("Enter the size of process %d: ",i);
        scanf("%d",&processes[i].size);
        processes[i].block_index=-1;
    }

    // first_fit(blocks,m,processes,n);
    // worst_fit(blocks,m,processes,n);
    // best_fit(blocks,m,processes,n);
    next_fit(blocks,m,processes,n);

    return 0;
}