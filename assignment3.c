#include <stdio.h> // standard input/output
#include <stdlib.h> // standard library

struct Process { // simple process structure
    int pid, at, bt, rt, ct, tat, wt; // ids and times
};

void printResults(struct Process p[], int n) { // print table and averages
    float total_tat = 0, total_wt = 0; // totals
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n"); // header
    for (int i = 0; i < n; i++) { // loop rows
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt); // row
        total_tat += p[i].tat; // add tat
        total_wt += p[i].wt; // add wt
    }
    printf("Average TAT: %.2f\nAverage WT: %.2f\n", total_tat / n, total_wt / n); // averages
}

void runSRTF(struct Process p[], int n) { // SJF preemptive (SRTF)
    printf("\n--- Shortest Job First (Preemptive / SRTF) ---\n"); // title
    int completed = 0, current_time = 0; // counters
    
    for (int i = 0; i < n; i++) // init remaining time
        p[i].rt = p[i].bt; // rt = bt

    while (completed < n) { // run until all done
        int shortest = -1, min_rt = 999999; // find shortest ready
        for (int i = 0; i < n; i++) { // scan all
            if (p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt) { // ready and smaller
                min_rt = p[i].rt; // update min
                shortest = i; // store index
            }
        }
        
        if (shortest == -1) { // if none ready
            current_time++; // idle one unit
        } else { // run 1 unit
            p[shortest].rt--; // reduce remaining
            current_time++; // time moves
            if (p[shortest].rt == 0) { // finished now
                completed++; // count done
                p[shortest].ct = current_time; // completion time
                p[shortest].tat = p[shortest].ct - p[shortest].at; // turnaround
                p[shortest].wt = p[shortest].tat - p[shortest].bt; // waiting
            }
        }
    }
    printResults(p, n); // show results
}

void runRoundRobin(struct Process p[], int n, int quantum) { // Round Robin
    printf("\n--- Round Robin (Time Quantum = %d) ---\n", quantum); // title
    int completed = 0, current_time = 0; // counters
    
    for (int i = 0; i < n; i++) // init remaining
        p[i].rt = p[i].bt; // rt = bt

    while (completed < n) { // until all done
        int all_done = 1; // assume idle
        for (int i = 0; i < n; i++) { // simple round scan
            if (p[i].at <= current_time && p[i].rt > 0) { // ready to run
                all_done = 0; // not idle
                if (p[i].rt > quantum) { // needs full quantum
                    current_time += quantum; // advance time
                    p[i].rt -= quantum; // reduce remaining
                } else { // finish within quantum
                    current_time += p[i].rt; // advance by remaining
                    p[i].rt = 0; // now done
                    completed++; // count done
                    p[i].ct = current_time; // completion time
                    p[i].tat = p[i].ct - p[i].at; // turnaround
                    p[i].wt = p[i].tat - p[i].bt; // waiting
                }
            }
        }
        if (all_done) current_time++; // if none ready, idle
    }
    printResults(p, n); // show results
}

int main() { // main function
    int n, quantum; // inputs
    printf("Enter total number of processes: "); // ask n
    scanf("%d", &n); // read n
    if (n <= 0) return 1; // guard

    struct Process p_srtf[n], p_rr[n]; // two copies
    printf("Enter Arrival Time and Burst Time for each process:\n"); // prompt
    for (int i = 0; i < n; i++) { // read loop
        printf("Process P%d:\n  Arrival Time: ", i + 1); // ask at
        scanf("%d", &p_srtf[i].at); // read at
        printf("  Burst Time: "); // ask bt
        scanf("%d", &p_srtf[i].bt); // read bt
        p_srtf[i].pid = i + 1; // set pid
        p_rr[i] = p_srtf[i]; // copy for RR
    }

    printf("Enter the Time Quantum for Round Robin: "); // ask quantum
    scanf("%d", &quantum); // read quantum
    runSRTF(p_srtf, n); // run SRTF
    runRoundRobin(p_rr, n, quantum); // run RR
    return 0; // exit ok
}

