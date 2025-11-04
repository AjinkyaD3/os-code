/*
Problem Statement 10:
Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, and C-LOOK
considering the initial head position moving away from the spindle.
*/
#include <stdio.h> // std io
#include <stdlib.h> // std lib
#include <math.h> // abs

int compare(const void *a, const void *b) { // qsort compare
    return (*(int*)a - *(int*)b); // ascending
}

void SSTF() { // shortest seek time first
    int n, initial, totalMove = 0; // inputs and total
    printf("\n--- SSTF Disk Scheduling Algorithm ---\nEnter the number of Requests: "); // prompt
    scanf("%d", &n); // read count
    
    int RQ[n], visited[n]; // requests and flags
    printf("Enter the Requests sequence:\n"); // prompt
    for (int i = 0; i < n; i++) { // read loop
        scanf("%d", &RQ[i]); // read
        visited[i] = 0; // mark not served
    }
    
    printf("Enter initial head position: "); // prompt
    scanf("%d", &initial); // read init
    printf("\nSeek Sequence: %d", initial); // start sequence

    for (int count = 0; count < n; count++) { // serve all
        int min = 999999, index = -1; // best choice
        for (int i = 0; i < n; i++) { // scan
            if (visited[i] == 0) { // not served
                int dist = abs(RQ[i] - initial); // distance
                if (min > dist) { // better
                    min = dist; // update
                    index = i; // store index
                }
            }
        }
        if (index != -1) { // found next
            totalMove += min; // add move
            initial = RQ[index]; // move head
            visited[index] = 1; // mark done
            printf(" -> %d", initial); // print
        } else break; // safety
    }
    printf("\nTotal head movement is %d\n", totalMove); // total
}

void SCAN() { // scan algorithm
    int n, initial, size, move, totalMove = 0; // inputs and total
    printf("\n--- SCAN Disk Scheduling Algorithm ---\nEnter the number of Requests: "); // prompt
    scanf("%d", &n); // read count
    
    int RQ[n]; // requests
    printf("Enter the Requests sequence:\n"); // prompt
    for (int i = 0; i < n; i++) // read loop
        scanf("%d", &RQ[i]); // read rq
    
    printf("Enter initial head position: "); // prompt
    scanf("%d", &initial); // read
    printf("Enter total disk size (e.g., 200): "); // prompt
    scanf("%d", &size); // read size
    printf("Enter the head movement direction (1 for high, 0 for low): "); // prompt
    scanf("%d", &move); // read dir

    qsort(RQ, n, sizeof(int), compare); // sort requests
    
    int index = 0; // find split
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) { // first higher
            index = i; // store index
            break; // stop
        }
    }
    
    printf("\nSeek Sequence: %d", initial); // start
    
    if (move == 1) { // go to high end first
        for (int i = index; i < n; i++) { // up
            totalMove += abs(RQ[i] - initial); // add move
            initial = RQ[i]; // move head
            printf(" -> %d", initial); // print
        }
        totalMove += abs((size - 1) - initial); // to end
        initial = size - 1; // set to end
        printf(" -> %d", initial); // print
        for (int i = index - 1; i >= 0; i--) { // then back
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
    } else { // go to low end first
        for (int i = index - 1; i >= 0; i--) { // down
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
        totalMove += abs(0 - initial); // to zero
        initial = 0; // set to zero
        printf(" -> %d", initial); // print
        for (int i = index; i < n; i++) { // then up
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
    }
    printf("\nTotal head movement is %d\n", totalMove); // total
}

void CLOOK() { // circular look
    int n, initial, move, totalMove = 0; // inputs and total
    printf("\n--- C-LOOK Disk Scheduling Algorithm ---\nEnter the number of Requests: "); // prompt
    scanf("%d", &n); // read count
    
    int RQ[n]; // requests
    printf("Enter the Requests sequence:\n"); // prompt
    for (int i = 0; i < n; i++) // read loop
        scanf("%d", &RQ[i]); // read
    
    printf("Enter initial head position: "); // prompt
    scanf("%d", &initial); // read
    printf("Enter the head movement direction (1 for high, 0 for low): "); // prompt
    scanf("%d", &move); // read
    
    qsort(RQ, n, sizeof(int), compare); // sort

    int index = 0; // split point
    for (int i = 0; i < n; i++) {
        if (initial < RQ[i]) { // first higher
            index = i; // set
            break; // stop
        }
    }

    printf("\nSeek Sequence: %d", initial); // start

    if (move == 1) { // move high direction
        for (int i = index; i < n; i++) { // up
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
        for (int i = 0; i < index; i++) { // jump to lowest and continue
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
    } else { // move low direction
        for (int i = index - 1; i >= 0; i--) { // down
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
        for (int i = n - 1; i >= index; i--) { // jump to highest and continue
            totalMove += abs(RQ[i] - initial); // add
            initial = RQ[i]; // move
            printf(" -> %d", initial); // print
        }
    }
    printf("\nTotal head movement is %d\n", totalMove); // total
}

int main() { // main menu
    int ch; // choice
    do { // loop
        printf("\n\n*********** MENU ***********\n1: SSTF\n2: SCAN\n3: C-LOOK\n4: EXIT\nEnter your choice: "); // menu
        scanf("%d", &ch); // read choice
        switch (ch) { // handle
            case 1: SSTF(); break; // run SSTF
            case 2: SCAN(); break; // run SCAN
            case 3: CLOOK(); break; // run C-LOOK
            case 4: exit(0); // exit
            default: printf("\nInvalid choice! Please try again.\n"); // bad
        }
    } while (ch != 4); // until exit
    return 0; // ok
}

