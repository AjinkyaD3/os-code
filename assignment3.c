#include <stdio.h>
#include <stdlib.h> // For exit

// Struct to hold process details
struct Process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time (for preemptive algorithms)
    int ct;  // Completion Time
    int tat; // Turn Around Time
    int wt;  // Waiting Time
};

// --- Shortest Job First (Preemptive / SRTF) ---
void runSRTF(struct Process p[], int n) {
    printf("\n--- Shortest Job First (Preemptive / SRTF) ---\n");
    
    int completed = 0;
    int current_time = 0;
    int shortest = -1;
    int min_rt = 999999;
    
    // We need a copy of burst times
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    while (completed != n) {
        shortest = -1;
        min_rt = 999999;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        // If no process is found, increment time
        if (shortest == -1) {
            current_time++;
        } else {
            // Process the found job for one time unit
            p[shortest].rt--;
            current_time++;

            // If a process finishes
            if (p[shortest].rt == 0) {
                completed++;
                p[shortest].ct = current_time;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }

    // Calculate and print results
    float total_tat = 0, total_wt = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

// --- Round Robin ---
void runRoundRobin(struct Process p[], int n, int quantum) {
    printf("\n--- Round Robin (Time Quantum = %d) ---\n", quantum);

    int completed = 0;
    int current_time = 0;
    
    // We need a copy of burst times
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    while (completed != n) {
        int all_done = 1; // Flag to check if we looped without doing work
        for (int i = 0; i < n; i++) {
            // Check for processes that have arrived and still have work
            if (p[i].at <= current_time && p[i].rt > 0) {
                all_done = 0; // Work was found
                
                if (p[i].rt > quantum) {
                    // Run for one quantum
                    current_time += quantum;
                    p[i].rt -= quantum;
                } else {
                    // Run for the remaining time (it's <= quantum)
                    current_time += p[i].rt;
                    p[i].rt = 0; // Process is finished
                    
                    completed++;
                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
        // If we went through a whole loop and no process was ready,
        // it means we have a gap. Just increment time.
        if (all_done) {
            current_time++;
        }
    }

    // Calculate and print results
    float total_tat = 0, total_wt = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

int main() {
    int n, quantum;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    if (n <= 0) return 1;

    // We need two copies, one for each algorithm
    struct Process p_srtf[n];
    struct Process p_rr[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i + 1);
        printf("  Arrival Time: ");
        scanf("%d", &p_srtf[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p_srtf[i].bt);
        
        p_srtf[i].pid = i + 1;
        
        // Copy to the Round Robin array
        p_rr[i] = p_srtf[i];
    }

    printf("Enter the Time Quantum for Round Robin: ");
    scanf("%d", &quantum);
    
    // Run the algorithms
    runSRTF(p_srtf, n);
    runRoundRobin(p_rr, n, quantum);

    return 0;
}

