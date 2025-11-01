#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 20

int *frames;
int num_frames;
int rear = -1;

void initialize() {
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
}

void displayFrames() {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void FIFO(int pages[], int n) {
    int page_faults = 0;
    int front = 0;
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }
        if (!found) {
            page_faults++;
            if (rear < num_frames - 1) {
                rear++;
            } else {
                rear = 0;
            }
            frames[rear] = page;
        }
        displayFrames();
    }
    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];
    int n;

    printf("Enter number of frames: ");
    scanf("%d", &num_frames);

    // Allocate memory for frames based on input
    frames = (int *)malloc(num_frames * sizeof(int));
    if (frames == NULL) {
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
    FIFO(pages, n);

    // Free the dynamically allocated memory
    free(frames);

    return 0;
}
