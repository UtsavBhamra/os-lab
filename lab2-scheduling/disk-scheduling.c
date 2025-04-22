#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void fcfs(int requests[], int n, int head) {
    int seek_count = 0;
    int distance;
    int current_track = head;
    
    for (int i = 0; i < n; i++) {
        distance = abs(current_track - requests[i]);
        seek_count += distance;
        current_track = requests[i];
    }
    
    printf("FCFS Total Seek Time: %d\n", seek_count);
}

void sstf(int requests[], int n, int head) {
    int seek_count = 0;
    int distance, index;
    int current_track = head;
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = false;
    
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                distance = abs(current_track - requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    index = j;
                }
            }
        }
        seek_count += min_distance;
        current_track = requests[index];
        visited[index] = true;
    }
    
    printf("SSTF Total Seek Time: %d\n", seek_count);
}

void scan(int requests[], int n, int head, int disk_size, int direction) {
    int seek_count = 0;
    int left[n+1], right[n+1], l_size = 0, r_size = 0;
    
    if (direction) right[r_size++] = disk_size - 1;
    else left[l_size++] = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) left[l_size++] = requests[i];
        if (requests[i] > head) right[r_size++] = requests[i];
    }
    
    qsort(left, l_size, sizeof(int), (int (*)(const void *, const void *)) strcmp);
    qsort(right, r_size, sizeof(int), (int (*)(const void *, const void *)) strcmp);
    
    int sequence[n+1], seq_size = 0;
    if (direction) {
        for (int i = 0; i < r_size; i++) sequence[seq_size++] = right[i];
        for (int i = l_size - 1; i >= 0; i--) sequence[seq_size++] = left[i];
    } else {
        for (int i = l_size - 1; i >= 0; i--) sequence[seq_size++] = left[i];
        for (int i = 0; i < r_size; i++) sequence[seq_size++] = right[i];
    }
    
    int current_track = head;
    for (int i = 0; i < seq_size; i++) {
        seek_count += abs(sequence[i] - current_track);
        current_track = sequence[i];
    }
    
    printf("SCAN Total Seek Time: %d\n", seek_count);
}

void cscan(int requests[], int n, int head, int disk_size) {
    int seek_count = 0;
    int left[n+1], right[n+1], l_size = 0, r_size = 0;
    right[r_size++] = disk_size - 1;
    left[l_size++] = 0;
    
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) left[l_size++] = requests[i];
        if (requests[i] > head) right[r_size++] = requests[i];
    }
    
    qsort(left, l_size, sizeof(int), (int (*)(const void *, const void *)) strcmp);
    qsort(right, r_size, sizeof(int), (int (*)(const void *, const void *)) strcmp);
    
    int sequence[n+1], seq_size = 0;
    for (int i = 0; i < r_size; i++) sequence[seq_size++] = right[i];
    for (int i = 0; i < l_size; i++) sequence[seq_size++] = left[i];
    
    int current_track = head;
    for (int i = 0; i < seq_size; i++) {
        seek_count += abs(sequence[i] - current_track);
        current_track = sequence[i];
    }
    
    printf("C-SCAN Total Seek Time: %d\n", seek_count);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 53;
    int disk_size = 200;
    
    printf("Disk Scheduling Algorithms:\n");
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, 1);
    cscan(requests, n, head, disk_size);
    
    return 0;
}
