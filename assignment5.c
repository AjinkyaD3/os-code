#include <stdio.h>

struct process {
    int max[10], allocate[10], need[10];
} p[10];

int n, m;

void input(int available[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter the details of process P%d:\n  Enter the allocated resources: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &p[i].allocate[j]);
        printf("  Enter the max resources: ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &p[i].max[j]);
            p[i].need[j] = p[i].max[j] - p[i].allocate[j];
        }
    }
    printf("\nEnter the available resources: ");
    for (int j = 0; j < m; j++)
        scanf("%d", &available[j]);
}

void display() {
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (int i = 0; i < n; i++) {
        printf("\tP%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", p[i].allocate[j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", p[i].max[j]);
        printf("\t\t");
        for (int j = 0; j < m; j++) printf("%d ", p[i].need[j]);
        printf("\n");
    }
}

int safetyAlgorithm(int available[], int safeSequence[]) {
    int work[m], finish[n];
    for (int j = 0; j < m; j++)
        work[j] = available[j];
    for (int i = 0; i < n; i++)
        finish[i] = 0;
    
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (int j = 0; j < m; j++) {
                    if (p[i].need[j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += p[i].allocate[j];
                    finish[i] = 1;
                    safeSequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (found == 0) return 0;
    }
    return 1;
}

int main() {
    printf("Enter No of processes: ");
    scanf("%d", &n);
    printf("Enter no of resources: ");
    scanf("%d", &m);
    
    int available[m], safeSequence[n];
    printf("\n***** Enter details of process *****\n");
    input(available);
    display();
    
    if (safetyAlgorithm(available, safeSequence)) {
        printf("\n\tSYSTEM IS IN SAFE STATE...\nSafe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSYSTEM IS IN UNSAFE STATE!!!\n");
    }
    return 0;
}



