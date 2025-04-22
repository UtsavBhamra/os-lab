#include <stdio.h>

#define MAX 100

typedef struct {
    int size;
    int original_size;
    int allocated; // 0 = free, 1 = allocated
} Block;

typedef struct {
    int size;
    int block_index; // -1 if not allocated
} Process;

void resetBlocks(Block blocks[], int m) {
    for (int i = 0; i < m; i++) {
        blocks[i].size = blocks[i].original_size;
        blocks[i].allocated = 0;
    }
}

void resetProcesses(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].block_index = -1;
    }
}

void firstFit(Block blocks[], int m, Process processes[], int n) {
    resetBlocks(blocks, m);
    resetProcesses(processes, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                processes[i].block_index = j;
                blocks[j].size -= processes[i].size;
                blocks[j].allocated = 1;
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processes[i].block_index != -1)
            printf("Process %d of size %d allocated to block %d\n", i+1, processes[i].size, processes[i].block_index + 1);
        else
            printf("Process %d of size %d not allocated\n", i+1, processes[i].size);
    }
}

void nextFit(Block blocks[], int m, Process processes[], int n) {
    resetBlocks(blocks, m);
    resetProcesses(processes, n);

    int last_index = 0;
    for (int i = 0; i < n; i++) {
        int count = 0, j = last_index;
        while (count < m) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                processes[i].block_index = j;
                blocks[j].size -= processes[i].size;
                blocks[j].allocated = 1;
                last_index = (j + 1) % m;
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    printf("\nNext Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processes[i].block_index != -1)
            printf("Process %d of size %d allocated to block %d\n", i+1, processes[i].size, processes[i].block_index + 1);
        else
            printf("Process %d of size %d not allocated\n", i+1, processes[i].size);
    }
}

void bestFit(Block blocks[], int m, Process processes[], int n) {
    resetBlocks(blocks, m);
    resetProcesses(processes, n);

    for (int i = 0; i < n; i++) {
        int best_idx = -1;
        for (int j = 0; j < m; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                if (best_idx == -1 || blocks[j].size < blocks[best_idx].size)
                    best_idx = j;
            }
        }
        if (best_idx != -1) {
            processes[i].block_index = best_idx;
            blocks[best_idx].size -= processes[i].size;
            blocks[best_idx].allocated = 1;
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processes[i].block_index != -1)
            printf("Process %d of size %d allocated to block %d\n", i+1, processes[i].size, processes[i].block_index + 1);
        else
            printf("Process %d of size %d not allocated\n", i+1, processes[i].size);
    }
}

void worstFit(Block blocks[], int m, Process processes[], int n) {
    resetBlocks(blocks, m);
    resetProcesses(processes, n);

    for (int i = 0; i < n; i++) {
        int worst_idx = -1;
        for (int j = 0; j < m; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                if (worst_idx == -1 || blocks[j].size > blocks[worst_idx].size)
                    worst_idx = j;
            }
        }
        if (worst_idx != -1) {
            processes[i].block_index = worst_idx;
            blocks[worst_idx].size -= processes[i].size;
            blocks[worst_idx].allocated = 1;
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processes[i].block_index != -1)
            printf("Process %d of size %d allocated to block %d\n", i+1, processes[i].size, processes[i].block_index + 1);
        else
            printf("Process %d of size %d not allocated\n", i+1, processes[i].size);
    }
}

int main() {
    int m, n;
    Block blocks[MAX];
    Process processes[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d blocks:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &blocks[i].size);
        blocks[i].original_size = blocks[i].size;
        blocks[i].allocated = 0;
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].size);
        processes[i].block_index = -1;
    }

    int choice;
    do {
        printf("\nChoose Allocation Strategy:\n");
        printf("1. First Fit\n2. Next Fit\n3. Best Fit\n4. Worst Fit\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: firstFit(blocks, m, processes, n); break;
            case 2: nextFit(blocks, m, processes, n); break;
            case 3: bestFit(blocks, m, processes, n); break;
            case 4: worstFit(blocks, m, processes, n); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
    