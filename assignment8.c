#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void SSTF() {
    int n, initial, totalMove = 0;
    printf("\n--- SSTF Disk Scheduling Algorithm ---\nEnter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n], visited[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
        visited[i] = 0;
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("\nSeek Sequence: %d", initial);

    for (int count = 0; count < n; count++) {
        int min = 999999, index = -1;
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
            visited[index] = 1;
            printf(" -> %d", initial);
        } else break;
    }
    printf("\nTotal head movement is %d\n", totalMove);
}

void SCAN() {
    int n, initial, size, move, totalMove = 0;
    printf("\n--- SCAN Disk Scheduling Algorithm ---\nEnter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter total disk size (e.g., 200): ");
    scanf("%d", &size);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    qsort(RQ, n, sizeof(int), compare);
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }
    
    printf("\nSeek Sequence: %d", initial);
    
    if (move == 1) {
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        totalMove += abs((size - 1) - initial);
        initial = size - 1;
        printf(" -> %d", initial);
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        totalMove += abs(0 - initial);
        initial = 0;
        printf(" -> %d", initial);
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    }
    printf("\nTotal head movement is %d\n", totalMove);
}

void CLOOK() {
    int n, initial, move, totalMove = 0;
    printf("\n--- C-LOOK Disk Scheduling Algorithm ---\nEnter the number of Requests: ");
    scanf("%d", &n);
    
    int RQ[n];
    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    
    printf("Enter initial head position: ");
    scanf("%d", &initial);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);
    
    qsort(RQ, n, sizeof(int), compare);

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }

    printf("\nSeek Sequence: %d", initial);

    if (move == 1) {
        for (int i = index; i < n; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
        for (int i = 0; i < index; i++) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            totalMove += abs(RQ[i] - initial);
            initial = RQ[i];
            printf(" -> %d", initial);
        }
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
        printf("\n\n*********** MENU ***********\n1: SSTF\n2: SCAN\n3: C-LOOK\n4: EXIT\nEnter your choice: ");
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

