#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int size;
    int allocated; // 1 = Allocated, 0 = Not used
} MemoryBlock;

void mvt(MemoryBlock memory_blocks[], int *num_processes, int *free_memory) {
    char choice;

    do {
        int process_size;
        printf("Enter memory required for process %d (in Bytes) -- ", *num_processes + 1);
        scanf("%d", &process_size);

        if (process_size <= *free_memory) {
            memory_blocks[*num_processes].size = process_size;
            memory_blocks[*num_processes].allocated = 1;
            *free_memory -= process_size;
            printf("Memory is allocated for Process %d\n", *num_processes + 1);
        } else {
            printf("Memory is Full. Cannot allocate memory for Process %d\n", *num_processes + 1);
        }

        (*num_processes)++;

        printf("Do you want to continue(y/n) -- ");
        scanf(" %c", &choice);  // Space before %c to consume newline

    } while (choice == 'y' || choice == 'Y');
}

int main() {
    int total_memory, free_memory;
    MemoryBlock memory_blocks[MAX_PROCESSES] = {0};
    int num_processes = 0;

    printf("Enter the total memory available (in Bytes) -- ");
    scanf("%d", &total_memory);
    free_memory = total_memory;

    mvt(memory_blocks, &num_processes, &free_memory);

    printf("\n--- Memory Allocation Summary (MVT) ---\n");
    for (int i = 0; i < num_processes; i++) {
        if (memory_blocks[i].allocated) {
            printf("Process %d: Allocated %d Bytes\n", i + 1, memory_blocks[i].size);
        } else {
            printf("Process %d: Not allocated\n", i + 1);
        }
    }

    printf("\nTotal Internal Fragmentation: 0\n");
    printf("Total External Fragmentation: %d\n", free_memory);

    return 0;
}
