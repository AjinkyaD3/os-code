// assignment7.c
// Problem Statement 7:
// Implement the C program for Deadlock Avoidance Algorithm: Banker's Algorithm.
#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes (n) and resource types (m): ");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int finished[n], safeSeq[n], count = 0;
    for (int i = 0; i < n; i++) finished[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                int canRun = 1;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    if (count == n) {
        printf("\n Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\n❌ No Safe Sequence (System is Unsafe)\n");
    }

    return 0;
}
