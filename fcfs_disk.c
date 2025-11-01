#include <stdio.h>
#include <stdlib.h>  // for abs()

int main() {
    int n, head, totalMovement = 0, maxTrack;

    printf("Enter the maximum number of tracks on disk: ");
    scanf("%d", &maxTrack);

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &request[i]);

        // validate input
        if (request[i] < 0 || request[i] >= maxTrack) {
            printf("❌ Invalid request! Track number must be between 0 and %d.\n", maxTrack - 1);
            return 1;
        }
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= maxTrack) {
        printf("❌ Invalid head position! It must be between 0 and %d.\n", maxTrack - 1);
        return 1;
    }

    printf("\nDisk Movement Order:\n");
    printf("%d", head);

    for (int i = 0; i < n; i++) {
        printf(" -> %d", request[i]);
        totalMovement += abs(request[i] - head);
        head = request[i];
    }

    printf("\n\nTotal Head Movement: %d\n", totalMovement);
    printf("Average Head Movement: %.2f\n", (float) totalMovement / n);

    return 0;
}
