// assignment7.c
// Problem Statement 7:
// Implement the C program for Deadlock Avoidance Algorithm: Banker's Algorithm.
#include <stdio.h> // io
#include <stdlib.h> // std

int main() { // banker
    int n, m; // n processes, m resources
    printf("Enter processes (n) and resource types (m): "); // prompt
    scanf("%d %d", &n, &m); // read
    if (n <= 0 || m <= 0) return 1; // guard

    int alloc[n][m], max[n][m], need[n][m]; // matrices
    int avail[m]; // available

    printf("Enter Allocation matrix (n x m):\n"); // prompt
    for (int i = 0; i < n; i++) // rows
        for (int j = 0; j < m; j++) // cols
            scanf("%d", &alloc[i][j]); // read

    printf("Enter Max matrix (n x m):\n"); // prompt
    for (int i = 0; i < n; i++) // rows
        for (int j = 0; j < m; j++) // cols
            scanf("%d", &max[i][j]); // read

    printf("Enter Available vector (m): "); // prompt
    for (int j = 0; j < m; j++) // read m
        scanf("%d", &avail[j]); // read

    // --- This is the "Magic" ---
    for (int i = 0; i < n; i++) // compute need
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j]; // need = max - alloc

    int finished[n]; // finish flags
    for (int i = 0; i < n; i++) finished[i] = 0; // init
    int safeSeq[n], idx = 0; // sequence

    int madeProgress = 1; // loop flag
    while (idx < n && madeProgress) { // try to find order
        madeProgress = 0; // reset
        for (int i = 0; i < n; i++) { // try each process
            if (finished[i]) continue; // skip done
            int canRun = 1; // assume ok
            for (int j = 0; j < m; j++) // check need <= avail
                if (need[i][j] > avail[j]) { canRun = 0; break; } // not ok
            
            if (canRun) { // can run now
                for (int j = 0; j < m; j++) // release resources
                    avail[j] += alloc[i][j]; // add back
                safeSeq[idx++] = i; // record
                finished[i] = 1; // mark
                madeProgress = 1; // progress
            }
        }
    }
    // --- End of "Magic" ---

    if (idx == n) { // safe
        printf("Safe sequence: "); // print
        for (int i = 0; i < n; i++) printf("P%d ", safeSeq[i]); // P indices
        printf("\n"); // newline
    } else { // unsafe
        printf("No safe sequence (system is in unsafe state)\n"); // info
    }
    return 0; // ok
}
