#include <stdio.h>

struct Process {
    int pid, arrival_time, burst_time, priority;
    int remaining_time, waiting_time, turnaround_time, completed;
};

void preemptivePriorityScheduling(struct Process processes[], int n) {
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed != n) {
        int highest_priority = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed &&
                processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                selected = i;
            }
        }

        if (selected == -1) {
            current_time++;
            continue;
        }

        printf("| P%d ", processes[selected].pid);

        processes[selected].remaining_time--;
        current_time++;

        if (processes[selected].remaining_time == 0) {
            processes[selected].completed = 1;
            completed++;

            processes[selected].turnaround_time = current_time - processes[selected].arrival_time;
            processes[selected].waiting_time = processes[selected].turnaround_time - processes[selected].burst_time;

            total_wt += processes[selected].waiting_time;
            total_tat += processes[selected].turnaround_time;
        }
    }
    printf("|\n");

    printf("\nPID\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    struct Process processes[] = {
        {1, 0, 8, 2},
        {2, 1, 1, 1},
        {3, 2, 3, 3},
        {4, 3, 2, 4},
        {5, 4, 6, 5}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    preemptivePriorityScheduling(processes, n);

    return 0;
}
