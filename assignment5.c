#include <stdio.h>

struct process {
    int max[10];
    int allocate[10];
    int need[10];
} p[10];

int n, m; // n = processes, m = resources

// Function to get input
void input(int available[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("Enter the details of process P%d: \n", i);
        printf("  Enter the allocated resources: ");
        for (j = 0; j < m; j++) {
            scanf("%d", &p[i].allocate[j]);
        }
        printf("  Enter the max resources: ");
        for (j = 0; j < m; j++) {
            scanf("%d", &p[i].max[j]);
            // Calculate need
            p[i].need[j] = p[i].max[j] - p[i].allocate[j];
        }
    }
    
    printf("\nEnter the available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }
}

// Function to display the current state
void display() {
    int i, j;
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (i = 0; i < n; i++) {
        printf("\tP%d\t", i);
        // Allocate
        for (j = 0; j < m; j++)
            printf("%d ", p[i].allocate[j]);
        printf("\t\t");
        // Max
        for (j = 0; j < m; j++)
            printf("%d ", p[i].max[j]);
        printf("\t\t");
        // Need
        for (j = 0; j < m; j++)
            printf("%d ", p[i].need[j]);
        printf("\n");
    }
}

// The core safety algorithm
int safetyAlgorithm(int available[], int safeSequence[]) {
    int i, j;
    int work[m];
    int finish[n];
    
    // 1. Initialize Work = Available
    for (j = 0; j < m; j++) {
        work[j] = available[j];
    }
    
    // Initialize Finish = false for all processes
    for (i = 0; i < n; i++) {
        finish[i] = 0; // 0 = false
    }
    
    int count = 0; // Count of finished processes
    while (count < n) {
        int found = 0; // Flag to check if we found a process
        for (i = 0; i < n; i++) {
            // 2. Find a process i such that:
            //    a) Finish[i] == false
            if (finish[i] == 0) {
                //    b) Need[i] <= Work
                int can_allocate = 1;
                for (j = 0; j < m; j++) {
                    if (p[i].need[j] > work[j]) {
                        can_allocate = 0; // Can't allocate
                        break;
                    }
                }
                
                // If we found such a process
                if (can_allocate) {
                    // 3. Work = Work + Allocation[i]
                    for (j = 0; j < m; j++) {
                        work[j] += p[i].allocate[j];
                    }
                    // Finish[i] = true
                    finish[i] = 1;
                    // Add to safe sequence
                    safeSequence[count] = i;
                    count++;
                    found = 1; // Mark that we found one
                }
            }
        }
        
        // 4. If no such process exists, the system is unsafe
        if (found == 0) {
            return 0; // Not safe
        }
    }
    
    // If we finished all processes, the system is safe
    return 1; // Safe
}

int main() {
    printf("Enter No of processes: ");
    scanf("%d", &n);
    printf("Enter no of resources: ");
    scanf("%d", &m);
    
    int available[m];
    int safeSequence[n];
    
    printf("\n***** Enter details of process *****\n");
    input(available);
    display();
    
    if (safetyAlgorithm(available, safeSequence)) {
        printf("\n\tSYSTEM IS IN SAFE STATE...\n");
        printf("Safe sequence is: ");
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

