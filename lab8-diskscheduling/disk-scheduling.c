#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Compare function for qsort (ascending order)
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// First-Come-First-Serve (FCFS)
void fcfs(int requests[], int n, int head) {
    int seek_count = 0;
    int current_track = head;

    printf("FCFS Sequence: %d", head);
    for (int i = 0; i < n; i++) {
        seek_count += abs(current_track - requests[i]);
        current_track = requests[i];
        printf(" -> %d", current_track);
    }

    printf("\nFCFS Total Seek Time: %d\n\n", seek_count);
}

// Shortest Seek Time First (SSTF)
void sstf(int requests[], int n, int head) {
    int seek_count = 0;
    int current_track = head;
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    printf("SSTF Sequence: %d", head);
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int index = -1;

        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(current_track - requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }

        seek_count += min_distance;
        current_track = requests[index];
        visited[index] = true;
        printf(" -> %d", current_track);
    }

    printf("\nSSTF Total Seek Time: %d\n\n", seek_count);
}

// SCAN (Elevator Algorithm)
void scan(int requests[], int n, int head, int disk_size, int direction) {
    int seek_count = 0;
    int current_track = head;
    int i;

    // Separate requests into left and right of the head
    int left[n], right[n], l_size = 0, r_size = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] < head) left[l_size++] = requests[i];
        else right[r_size++] = requests[i];
    }

    // Sort both sides
    qsort(left, l_size, sizeof(int), compare);
    qsort(right, r_size, sizeof(int), compare);

    printf("SCAN Sequence: %d", head);

    // If moving right
    if (direction == 1) {
        // Move to the right first
        for (i = 0; i < r_size; i++) {
            seek_count += abs(current_track - right[i]);
            current_track = right[i];
            printf(" -> %d", current_track);
        }
        // Go to the end of disk (if not already there)
        if (current_track != disk_size - 1) {
            seek_count += abs(current_track - (disk_size - 1));
            current_track = disk_size - 1;
        }
        // Reverse to the left
        for (i = l_size - 1; i >= 0; i--) {
            seek_count += abs(current_track - left[i]);
            current_track = left[i];
            printf(" -> %d", current_track);
        }
    } else { // moving left first
        for (i = l_size - 1; i >= 0; i--) {
            seek_count += abs(current_track - left[i]);
            current_track = left[i];
            printf(" -> %d", current_track);
        }
        if (current_track != 0) {
            seek_count += abs(current_track - 0);
            current_track = 0;
        }
        for (i = 0; i < r_size; i++) {
            seek_count += abs(current_track - right[i]);
            current_track = right[i];
            printf(" -> %d", current_track);
        }
    }

    printf("\nSCAN Total Seek Time: %d\n\n", seek_count);
}

// C-SCAN (Circular SCAN)
void cscan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0;
    int current_track = head;
    int i;

    int left[n], right[n], l_size = 0, r_size = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] < head) left[l_size++] = requests[i];
        else right[r_size++] = requests[i];
    }

    qsort(left, l_size, sizeof(int), compare);
    qsort(right, r_size, sizeof(int), compare);

    printf("C-SCAN Sequence: %d", head);

    // Move right first
    for (i = 0; i < r_size; i++) {
        seek_count += abs(current_track - right[i]);
        current_track = right[i];
        printf(" -> %d", current_track);
    }

    // Go to end of disk
    if (current_track != disk_size - 1) {
        seek_count += abs(current_track - (disk_size - 1));
        current_track = disk_size - 1;
    }

    // Jump to start of disk
    seek_count += abs(current_track - 0);
    current_track = 0;

    // Move to left side requests
    for (i = 0; i < l_size; i++) {
        seek_count += abs(current_track - left[i]);
        current_track = left[i];
        printf(" -> %d", current_track);
    }

    printf("\nC-SCAN Total Seek Time: %d\n\n", seek_count);
}

int main() {
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
