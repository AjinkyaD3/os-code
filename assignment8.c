#include <stdio.h>
#include <stdlib.h>
#include <math.h> // For abs()

// Helper function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// --- SSTF (Shortest Seek Time First) ---
void SSTF() {
    int n, initial, totalMove = 0;
    printf("\n--- SSTF Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n];
    int visited[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
        visited[i] = 0; // 0 = not visited
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    
    printf("\nSeek Sequence: %d", initial);

    int count = 0;
    while (count < n) {
        int min = 999999;
        int index = -1;
        
        // Find the request with the minimum seek time
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                int dist = abs(RQ[i] - initial);
                if (min > dist) {
                    min = dist;
                    index = i;
                }
            }
        }
        
        if (index != -1) {
            totalMove += min;
            initial = RQ[index];
            visited[index] = 1; // Mark as visited
            count++;
            printf(" -> %d", initial);
        } else {
            // Should not happen if count < n
            break; 
        }
    }
    printf("\nTotal head movement is %d\n", totalMove);
}

// --- SCAN (Elevator Algorithm) ---
void SCAN() {
    int n, initial, size, move, totalMove = 0;
    printf("\n--- SCAN Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size (e.g., 200): ");
    scanf("%d", &size);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    // Sort the request queue
    qsort(RQ, n, sizeof(int), compare);
    
    // Find the split point
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }
    
    printf("\nSeek Sequence: %d", initial);
    
    // FIXED 'if (move = 1)' bug
    if (move == 1) { // Move right (toward higher values)
        // Service requests to the right
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        // Go to the end of the disk
        totalMove += abs((size - 1) - initial);
        initial = size - 1;
        printf(" -> %d", initial);
        
        // Service requests on the way back (left)
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    } else { // Move left (toward lower values)
        // Service requests to the left
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        // Go to the beginning of the disk
        totalMove += abs(0 - initial);
        initial = 0;
        printf(" -> %d", initial);
        
        // Service requests on the way back (right)
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    }
    printf("\nTotal head movement is %d\n", totalMove);
}

// --- C-LOOK ---
void CLOOK() {
    int n, initial, move, totalMove = 0;
    printf("\n--- C-LOOK Disk Scheduling Algorithm ---\n");
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);
    
    // Sort the request queue
    qsort(RQ, n, sizeof(int), compare);

    // Find the split point
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    printf("\nSeek Sequence: %d", initial);

    // FIXED 'if (move1)' bug
    if (move == 1) { // Move right
        // Service requests to the right
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        // "Look" back to the first request on the "other side"
        // (No movement added for the "jump")
        // Service requests from the beginning
        for (int i = 0; i < index; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    } else { // Move left
        // Service requests to the left
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        // "Look" back to the last request on the "other side"
        // (No movement added for the "jump")
        // Service requests from the end
        for (int i = n - 1; i >= index; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    }
    printf("\nTotal head movement is %d\n", totalMove);
}


int main() {
    int ch;
    do {
        printf("\n\n*********** MENU ***********\n");
        printf("1: SSTF\n");
        printf("2: SCAN\n");
        printf("3: C-LOOK\n");
        printf("4: EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: SSTF(); break;
            case 2: SCAN(); break;
            case 3: CLOOK(); break;
            case 4: exit(0);
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (ch != 4);
    
    return 0;
}

