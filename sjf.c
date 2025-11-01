#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int done;
};

void sjfNonPreemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;
    int gantt[100], ganttTime[100], gCount = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = 99999;

        // Find process with min burst among arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        // If no process has arrived, increment time
        if (idx == -1) {
            time++;
            continue;
        }

        // Record Gantt chart data
        gantt[gCount] = p[idx].pid;
        ganttTime[gCount] = time;
        gCount++;

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].done = 1;
        completed++;

        totalWT += p[idx].waiting;
        totalTAT += p[idx].turnaround;
    }

    ganttTime[gCount] = time;

    // Display process table
    printf("\n---------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].arrival, p[i].burst, 
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
    printf("---------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    // Gantt chart
    printf("\nGANTT CHART:\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < gCount; i++)
        printf("   P%d   ", gantt[i]);
    printf("\n---------------------------------------------------------------\n");
    for (int i = 0; i <= gCount; i++)
        printf("%-7d", ganttTime[i]);
    printf("\n---------------------------------------------------------------\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
        p[i].done = 0;
    }

    printf("\n--- Non-Preemptive Shortest Job First (SJF) Scheduling ---\n");
    sjfNonPreemptive(p, n);
    return 0;
}
