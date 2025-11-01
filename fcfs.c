#include <stdio.h>

typedef struct {
    int name;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].name = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Sort processes by arrival time (FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival > processes[j].arrival) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int currenttime = 0;
    printf("\nGantt Chart:\n");
    printf("Time  | Process\n");
    printf("-----------------\n");

    // Calculate Completion, Turnaround, and Waiting Times
    for (int i = 0; i < n; i++) {
        if (currenttime < processes[i].arrival) {
            currenttime = processes[i].arrival; // CPU idle time handling
        }

        currenttime += processes[i].burst;
        processes[i].completion = currenttime;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;

        printf("%-5d |  P%d\n", currenttime, processes[i].name);
    }

    // Display final results
    float avgwt = 0.0, avgtat = 0.0;
    printf("\nProcess | Arrival | Burst | Completion | Waiting | Turnaround\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%-6d %8d %8d %12d %10d %12d\n",
               processes[i].name,
               processes[i].arrival,
               processes[i].burst,
               processes[i].completion,
               processes[i].waiting,
               processes[i].turnaround);

        avgwt += processes[i].waiting;
        avgtat += processes[i].turnaround;
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nAverage Waiting Time   : %.2f", avgwt);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat);

    return 0;
}
