#include<stdio.h>
#include<stdlib.h>
#define MAX_BLOCKS 100

int memory[MAX_BLOCKS];

void sequential_allocation(){
    int start;
    int len;
    printf("Enter the starting block and the length of the file: ");
    scanf("%d %d",&start,&len);

    if(start+len>MAX_BLOCKS){
        printf("Allocation exceeds mem limit\n");
    }

    for(int i=start;i<start+len;i++){
        if(memory[i]==1){
            printf("Block %d is already allocated\n",i);
            return;
        }
    }

    for(int i=start;i<start+len;i++){
        memory[i]=1;
    }

    printf("File allocation successful\n");
}

void linked_allocation(){
    int block_num;
    printf("Enter the no of blocks needed: ");
    scanf("%d",&block_num);

    int allocated[block_num];

    for(int i=0;i<block_num;i++){
        int temp;
        printf("Enter the allocated block no: ");
        scanf("%d",&temp);

        if(temp<0 || temp>=MAX_BLOCKS || memory[temp]==1){
            printf("Could not allocate the block\n");
            return;
        }

        allocated[i]=temp;
    }

    for(int i=0;i<block_num;i++){
        memory[allocated[i]]=1;
    }

    printf("File linked accross blocks: \n");
    for(int i=0;i<block_num;i++){
        printf("%d -> ",allocated[i]);
    }
}

void indexed_allocation(){
    int idx_block;
    int no_of_blocks;

    printf("Enter the idx_block: ");
    scanf("%d",&idx_block);

    if(idx_block<0 || idx_block>=MAX_BLOCKS || memory[idx_block]==1){
        printf("index block could not be allocated\n");
        return;
    }

    printf("Enter the no of blocks: ");
    scanf("%d",&no_of_blocks);

    int allocated[no_of_blocks];

    for(int i=0;i<no_of_blocks;i++){
        int block;
        printf("Enter the block number: ");
        scanf("%d",&block);

        if(block<0 || block>=MAX_BLOCKS || memory[block]==1 || block==idx_block){
            printf("Block could not be allocated\n");
            return;
        }

        allocated[i]=block;
    }

    memory[idx_block]=1;
    for(int i=0;i<no_of_blocks;i++){
        memory[allocated[i]]=1;
    }

    printf("File allocated successfully \n");
}

void reset_memory() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        memory[i] = 0;
}

int main(){
    int choice;

    while (1) {
        printf("\n File Allocation Methods Menu\n");
        printf("1. Sequential Allocation\n");
        printf("2. Linked Allocation\n");
        printf("3. Indexed Allocation\n");
        printf("4. Reset Memory\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sequential_allocation();
                break;
            case 2:
                linked_allocation();
                break;
            case 3:
                indexed_allocation();
                break;
            case 4:
                reset_memory();
                printf("Memory reset. All blocks are free.\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}