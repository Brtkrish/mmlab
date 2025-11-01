#include <stdio.h>

struct Process {
    int processNo;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int isCompleted;
};

// Function to find the highest priority process that has arrived and not completed
int findHighestPriority(struct Process proc[], int n, int currentTime) {
    int highestPriority = -1;
    int minPriority = 999999;  // Smallest number = highest priority

    for (int i = 0; i < n; i++) {
        if (!proc[i].isCompleted && proc[i].arrivalTime <= currentTime) {
            if (proc[i].priority < minPriority) {
                minPriority = proc[i].priority;
                highestPriority = i;
            }
            // Optional tie-breaker: earlier arrival gets preference
            else if (proc[i].priority == minPriority && proc[i].arrivalTime < proc[highestPriority].arrivalTime) {
                highestPriority = i;
            }
        }
    }
    return highestPriority;
}

void calculateTimes(struct Process proc[], int n) {
    int currentTime = 0;
    int completed = 0;

    for (int i = 0; i < n; i++)
        proc[i].isCompleted = 0;

    while (completed != n) {
        int idx = findHighestPriority(proc, n, currentTime);

        if (idx == -1) {
            // No process has arrived yet
            currentTime++;
            continue;
        }

        // Run the process completely (Non-Preemptive)
        currentTime += proc[idx].burstTime;
        proc[idx].completionTime = currentTime;
        proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
        proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
        proc[idx].isCompleted = 1;
        completed++;

        printf("Time %d - %d: P%d executed (Priority %d)\n",
               currentTime - proc[idx].burstTime,
               currentTime,
               proc[idx].processNo,
               proc[idx].priority);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter process details (arrival time, burst time, priority):\n");
    for (int i = 0; i < n; i++) {
        proc[i].processNo = i + 1;
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
    }

    calculateTimes(proc, n);

    // Calculate averages
    float total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        total_waiting += proc[i].waitingTime;
        total_turnaround += proc[i].turnaroundTime;
    }
    float avg_waiting = total_waiting / n;
    float avg_turnaround = total_turnaround / n;

    // Display results
    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               proc[i].processNo,
               proc[i].arrivalTime,
               proc[i].burstTime,
               proc[i].priority,
               proc[i].waitingTime,
               proc[i].turnaroundTime,
               proc[i].completionTime);
    }
    printf("--------------------------------------------------------------------------\n");
    printf("Average Waiting Time   : %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}
