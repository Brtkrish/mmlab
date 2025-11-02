#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int in_queue; // flag to avoid re-adding to queue
};

#define MAX 100

// Queue implementation
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int pid) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = pid;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

int isQueueEmpty() {
    return (front == -1 || front > rear);
}

void resetQueue() {
    front = rear = -1;
}

// Round Robin function
void roundRobin(struct Process p[], int n, int time_quantum) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    resetQueue();

    // Push first available processes
    for (int i = 0; i < n; ++i) {
        if (p[i].arrival_time <= time && !p[i].in_queue) {
            enqueue(i);
            p[i].in_queue = 1;
        }
    }

    while (completed < n) {
        if (isQueueEmpty()) {
            time++;
            for (int i = 0; i < n; ++i) {
                if (p[i].arrival_time <= time && !p[i].in_queue) {
                    enqueue(i);
                    p[i].in_queue = 1;
                }
            }
            continue;
        }

        int idx = dequeue();

        if (p[idx].remaining_time <= time_quantum) {
            time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
            completed++;

            printf("P%d completed at time %d | WT = %d | TAT = %d\n",
                   p[idx].id, time, p[idx].waiting_time, p[idx].turnaround_time);
        } else {
            time += time_quantum;
            p[idx].remaining_time -= time_quantum;
        }

        // Add new arrivals
        for (int i = 0; i < n; ++i) {
            if (p[i].arrival_time <= time && !p[i].in_queue && p[i].remaining_time > 0) {
                enqueue(i);
                p[i].in_queue = 1;
            }
        }

        // If process still needs time, re-enqueue it
        if (p[idx].remaining_time > 0) {
            enqueue(idx);
        } else {
            p[idx].in_queue = 0; // Mark completed
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        printf("Enter arrival time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].in_queue = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\n--- Round Robin Scheduling (with Arrival Time) ---\n");
    roundRobin(p, n, tq);

    return 0;
}
