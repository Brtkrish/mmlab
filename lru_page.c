#include <stdio.h>

struct frames {
    int content;
    int recent;   // holds "last used time"
} frame[100];

void main() {
    int i, j, k, p, f, page[100], time = 0, min, pf = 0, id = 0;

    printf("ENTER THE NUMBER OF PAGES : ");
    scanf("%d", &p);

    printf("ENTER THE REFERENCING STRING : ");
    for (i = 0; i < p; i++) {
        scanf("%d", &page[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES : ");
    scanf("%d", &f);

    // Initialize all frames
    for (i = 0; i < f; i++) {
        frame[i].content = -1;
        frame[i].recent = 0;
    }

    printf("\nREFERENCING PAGE\tSTATUS\t\tFRAME CONTENT\n\n");

    for (i = 0; i < p; i++) {
        printf("\t%d\t\t", page[i]);
        int found = 0;

        // Check if page already exists in frames
        for (j = 0; j < f; j++) {
            if (frame[j].content == page[i]) {
                found = 1;
                frame[j].recent = ++time;  // update access time
                printf("HIT\t\t");
                break;
            }
        }

        if (!found) {
            printf("MISS\t\t");
            // If there’s empty frame, use it
            if (id < f) {
                frame[id].content = page[i];
                frame[id].recent = ++time;
                id++;
            } else {
                // Find least recently used page (smallest recent value)
                min = 0;
                for (k = 1; k < f; k++) {
                    if (frame[k].recent < frame[min].recent)
                        min = k;
                }
                frame[min].content = page[i];
                frame[min].recent = ++time;
            }
            pf++;
        }

        // Display frames
        for (j = 0; j < f; j++) {
            if (frame[j].content != -1)
                printf("%d\t", frame[j].content);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("\nPAGE FAULTS : %d\n", pf);
}
