#include <stdio.h>
#include <limits.h>  // For using INT_MIN or INT_MAX if needed

// ---------------- FIFO (First-In-First-Out) ---------------- //

void fifo(int pages[], int n, int size) {
    int frames[size];  // Holds the pages in memory
    int front = 0;     // Points to the next frame to be replaced
    int page_faults = 0;

    // Initialize all frames as empty (-1)
    for (int i = 0; i < size; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in a frame (page hit)
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found, it's a page fault
        if (!found) {
            // Replace the oldest page (FIFO)
            frames[front] = pages[i];
            front = (front + 1) % size;
            page_faults++;
        }
    }

    printf("FIFO Page Faults: %d\n", page_faults);
}

// ---------------- LRU (Least Recently Used) ---------------- //

// Helper to find least recently used page's index
int findLRU(int time[], int size) {
    int min = time[0], pos = 0;

    for (int i = 1; i < size; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }

    return pos;
}

void lru(int pages[], int n, int size) {
    int frames[size], time[size];  // `time` tracks usage time
    int count = 0, page_faults = 0;

    // Initialize frames and time
    for (int i = 0; i < size; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Page hit check
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                count++;
                time[j] = count;  // Update recent usage time
                break;
            }
        }

        // Page fault
        if (!found) {
            int pos = -1;

            // Find an empty frame
            for (int j = 0; j < size; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, replace least recently used
            if (pos == -1)
                pos = findLRU(time, size);

            // Insert the page and update time
            frames[pos] = pages[i];
            count++;
            time[pos] = count;
            page_faults++;
        }
    }

    printf("LRU Page Faults: %d\n", page_faults);
}

// ---------------- LFU (Least Frequently Used) ---------------- //

// Helper to find least frequently used page
int findLFU(int freq[], int size) {
    int min = freq[0], pos = 0;

    for (int i = 1; i < size; i++) {
        if (freq[i] < min) {
            min = freq[i];
            pos = i;
        }
    }

    return pos;
}

void lfu(int pages[], int n, int size) {
    int frames[size], freq[size];  // `freq` tracks how many times a page is used
    int page_faults = 0;

    // Initialize frames and frequency counts
    for (int i = 0; i < size; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Page hit: increase frequency
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found) {
            int pos = -1;

            // Try to find an empty frame
            for (int j = 0; j < size; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If all frames are full, replace least frequently used
            if (pos == -1)
                pos = findLFU(freq, size);

            // Replace and reset frequency to 1
            frames[pos] = pages[i];
            freq[pos] = 1;
            page_faults++;
        }
    }

    printf("LFU Page Faults: %d\n", page_faults);
}

// ---------------- Optimal Page Replacement ---------------- //

// Helper to predict the farthest used page in future
int predict(int pages[], int frames[], int n, int index, int size) {
    int res = -1, farthest = index;

    for (int i = 0; i < size; i++) {
        int j;

        // Look ahead in future for current page usage
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If not found at all, best to replace this
        if (j == n)
            return i;
    }

    return (res == -1) ? 0 : res;
}

void optimal(int pages[], int n, int size) {
    int frames[size], page_faults = 0;

    // Initialize frames
    for (int i = 0; i < size; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Page hit check
        for (int j = 0; j < size; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found) {
            int pos = -1;

            // Try to find empty frame
            for (int j = 0; j < size; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If all frames full, predict future use
            if (pos == -1)
                pos = predict(pages, frames, n, i + 1, size);

            frames[pos] = pages[i];
            page_faults++;
        }
    }

    printf("Optimal Page Faults: %d\n", page_faults);
}

// ---------------- Main Function ---------------- //

int main() {
    // Sample page reference string
    int pages[] = {1, 3, 0, 3, 5, 6, 3, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);  // Total number of references
    int frame_size = 3;  // Number of page frames in memory

    // Call each page replacement algorithm
    fifo(pages, n, frame_size);
    lru(pages, n, frame_size);
    lfu(pages, n, frame_size);
    optimal(pages, n, frame_size);

    return 0;
}
