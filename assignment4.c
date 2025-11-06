#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, at, bt, rt, ct, tat, wt;
};

void printResults(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average TAT: %.2f\nAverage WT: %.2f\n", total_tat / n, total_wt / n);
}

void runSRTF(struct Process p[], int n) {
    printf("\n--- Shortest Job First (Preemptive / SRTF) ---\n");
    int completed = 0, current_time = 0;
    
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int shortest = -1, min_rt = 999999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }
        if (shortest == -1) {
            current_time++;
        } else {
            p[shortest].rt--;
            current_time++;
            if (p[shortest].rt == 0) {
                completed++;
                p[shortest].ct = current_time;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }
    printResults(p, n);
}

void runRoundRobin(struct Process p[], int n, int quantum) {
    printf("\n--- Round Robin (Time Quantum = %d) ---\n", quantum);
    int completed = 0, current_time = 0;
    
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                all_done = 0;
                if (p[i].rt > quantum) {
                    current_time += quantum;
                    p[i].rt -= quantum;
                } else {
                    current_time += p[i].rt;
                    p[i].rt = 0;
                    completed++;
                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
        if (all_done) current_time++;
    }
    printResults(p, n);
}

int main() {
    int n, quantum;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    if (n <= 0) return 1;

    struct Process p_srtf[n], p_rr[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n  Arrival Time: ", i + 1);
        scanf("%d", &p_srtf[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p_srtf[i].bt);
        p_srtf[i].pid = i + 1;
        p_rr[i] = p_srtf[i];
    }

    printf("Enter the Time Quantum for Round Robin: ");
    scanf("%d", &quantum);
    runSRTF(p_srtf, n);
    runRoundRobin(p_rr, n, quantum);
    return 0;
}
