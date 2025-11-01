#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50  // Maximum number of pages

int *frames;   // Array to store the frames
int *counts;   // Array to store the count for each frame
int num_frames;

// Initialize all frames and counts
void initialize() {
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;   // Empty frame
        counts[i] = 0;    // Count reset
    }
}

// Display current frame contents
void displayFrames() {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

// Find the least frequently used frame
int findLFU() {
    int min = counts[0];
    int lfu_frame = 0;

    for (int i = 1; i < num_frames; i++) {
        if (counts[i] < min) {
            min = counts[i];
            lfu_frame = i;
        }
    }
    return lfu_frame;
}

// Perform LFU page replacement
void LFU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page already in memory
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                counts[j]++;
                printf("Page %d is already in memory (HIT)\n", page);
                break;
            }
        }

        // If not found, replace LFU page
        if (!found) {
            int lfu_frame = findLFU();
            printf("Page %d caused a page fault, loaded in frame %d\n", page, lfu_frame);
            frames[lfu_frame] = page;
            counts[lfu_frame] = 1;
            page_faults++;
        }

        displayFrames();
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

// Main function
int main() {
    int pages[MAX_PAGES];
    int n;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    // Dynamically allocate memory for frames and counts
    frames = (int *)malloc(num_frames * sizeof(int));
    counts = (int *)malloc(num_frames * sizeof(int));

    if (frames == NULL || counts == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    initialize();
    LFU(pages, n);

    // Free allocated memory
    free(frames);
    free(counts);

    return 0;
}
