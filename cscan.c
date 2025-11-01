#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RQ[100], i, j, n, TotalHeadMovement = 0, initial, size, move;
    int order[200], ordIndex = 0; // For Gantt chart order
    
    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the Requests sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    printf("Enter total disk size: ");
    scanf("%d", &size);

    printf("Enter head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    // Sort request sequence
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    // Find the index where head position fits
    int index = n;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }

    // Move towards higher end first
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(RQ[i] - initial);
            order[ordIndex++] = RQ[i];
            initial = RQ[i];
        }

        // Go to end (size - 1)
        TotalHeadMovement += abs((size - 1) - initial);
        order[ordIndex++] = size - 1;

        // Jump to 0 (no seek time counted for jump)
        order[ordIndex++] = 0;
        initial = 0;

        for (i = 0; i < index; i++)
        {
            TotalHeadMovement += abs(RQ[i] - initial);
            order[ordIndex++] = RQ[i];
            initial = RQ[i];
        }
    }

    // Move towards lower end first
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(RQ[i] - initial);
            order[ordIndex++] = RQ[i];
            initial = RQ[i];
        }

        // Go to start (0)
        TotalHeadMovement += abs(initial - 0);
        order[ordIndex++] = 0;

        // Jump to end (size - 1)
        order[ordIndex++] = size - 1;
        initial = size - 1;

        for (i = n - 1; i >= index; i--)
        {
            TotalHeadMovement += abs(RQ[i] - initial);
            order[ordIndex++] = RQ[i];
            initial = RQ[i];
        }
    }

    // Print result
    printf("\nTotal Head Movement = %d\n", TotalHeadMovement);

    // Print Gantt Chart
    printf("\n--- GANTT CHART (C-SCAN Disk Scheduling) ---\n");
    printf("Head Movement Order:\n");
    printf("Start -> ");
    for (i = 0; i < ordIndex; i++)
    {
        if (i == ordIndex - 1)
            printf("%d", order[i]);
        else
            printf("%d -> ", order[i]);
    }
    printf("\n");

    return 0;
}
