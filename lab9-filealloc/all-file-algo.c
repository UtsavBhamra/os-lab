#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100 // Total number of disk blocks

int memory[MAX_BLOCKS]; // Memory array to track block allocation (0 = free, 1 = allocated)

// Function to reset the memory (mark all blocks as free)
void reset_memory() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        memory[i] = 0;
}

// Sequential Allocation: Allocate contiguous blocks starting from a given index
void sequential_allocation() {
    int start, length;

    printf("Enter starting block and length of the file: ");
    scanf("%d %d", &start, &length);

    // Check for memory overflow
    if (start + length > MAX_BLOCKS) {
        printf("Allocation exceeds memory limit.\n");
        return;
    }

    // Check if all blocks in the range are free
    for (int i = start; i < start + length; i++) {
        if (memory[i] == 1) {
            printf("Block %d already allocated. Sequential allocation failed.\n", i);
            return;
        }
    }

    // Mark blocks as allocated
    for (int i = start; i < start + length; i++)
        memory[i] = 1;

    printf("File allocated from block %d to %d.\n", start, start + length - 1);
}

// Linked Allocation: Allocate blocks randomly and link them
void linked_allocation() {
    int blocks, block_num;

    printf("Enter the number of blocks needed: ");
    scanf("%d", &blocks);

    // Dynamically allocate memory to store the block numbers
    int *allocated = (int *)malloc(blocks * sizeof(int));
    if (!allocated) {
        printf("Memory allocation error.\n");
        return;
    }

    printf("Enter the block numbers:\n");
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &block_num);

        // Check if block is valid and not already allocated
        if (block_num < 0 || block_num >= MAX_BLOCKS || memory[block_num] == 1) {
            printf("Block %d is invalid or already allocated. Linked allocation failed.\n", block_num);
            free(allocated);
            return;
        }

        allocated[i] = block_num;
    }

    // Mark all given blocks as allocated
    for (int i = 0; i < blocks; i++)
        memory[allocated[i]] = 1;

    // Print the linked blocks
    printf("File linked across blocks: ");
    for (int i = 0; i < blocks; i++)
        printf("%d -> ", allocated[i]);
    printf("NULL\n");

    free(allocated); // Free dynamically allocated memory
}

// Indexed Allocation: Allocate an index block and point it to other blocks
void indexed_allocation() {
    int index_block, blocks, block_num;

    printf("Enter index block: ");
    scanf("%d", &index_block);

    // Validate the index block
    if (index_block < 0 || index_block >= MAX_BLOCKS || memory[index_block] == 1) {
        printf("Invalid index block. Indexed allocation failed.\n");
        return;
    }

    printf("Enter the number of blocks needed: ");
    scanf("%d", &blocks);

    // Dynamically allocate memory to store the block numbers
    int *allocated = (int *)malloc(blocks * sizeof(int));
    if (!allocated) {
        printf("Memory allocation error.\n");
        return;
    }

    printf("Enter the block numbers:\n");
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &block_num);

        // Validate each block and check that it's not the index block
        if (block_num < 0 || block_num >= MAX_BLOCKS || memory[block_num] == 1 || block_num == index_block) {
            printf("Block %d is invalid or already allocated. Indexed allocation failed.\n", block_num);
            free(allocated);
            return;
        }

        allocated[i] = block_num;
    }

    memory[index_block] = 1; // Allocate the index block

    for (int i = 0; i < blocks; i++)
        memory[allocated[i]] = 1;

    // Print index and allocated blocks
    printf("Index block: %d\n", index_block);
    printf("Blocks allocated: ");
    for (int i = 0; i < blocks; i++)
        printf("%d ", allocated[i]);
    printf("\n");

    free(allocated); // Free the temporary memory
}

// Menu-driven main program
int main() {
    int choice;

    while (1) {
        printf("\n📂 File Allocation Methods Menu\n");
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
