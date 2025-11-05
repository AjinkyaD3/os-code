
/*
Problem Statement 2:
Implement the C program in which main program accepts the integers to be sorted.
Main program uses FORK to create a child process. Parent sorts and waits for child
using WAIT; child also sorts using any algorithm. Also demonstrate zombie and orphan states.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void bubbleSort(int a[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if(pid == 0) {
        // Child Process
        printf("\n[Child] PID = %d\n", getpid());
        bubbleSort(arr, n);

        printf("[Child] Sorted Array: ");
        for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    }
    else {
        // Parent Process
        printf("\n[Parent] PID = %d\n", getpid());
        bubbleSort(arr, n);

        printf("[Parent] Sorted Array: ");
        for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");

        wait(NULL); // prevents zombie
        printf("[Parent] Child finished. No Zombie in sorting part.\n");
    }

    // ---------------- DEMONSTRATE ZOMBIE ----------------
    pid_t z = fork();

    if(z == 0) {
        printf("\n[Zombie-Child] PID = %d exiting now.\n", getpid());
        exit(0);  // Child exits → parent doesn't wait immediately → zombie
    }
    else {
        printf("[Parent] Created zombie child PID = %d. Sleeping 5 seconds...\n", z);
        printf(">>> Check zombie using: ps -l\n");
        sleep(5); // zombie exists here
        waitpid(z, NULL, 0); // removes zombie
        printf("[Parent] Zombie cleared.\n");
    }

    // ---------------- DEMONSTRATE ORPHAN ----------------
    pid_t o = fork();

    if(o == 0) {
        printf("\n[Orphan-Child] PID = %d sleeping 5 seconds.\n", getpid());
        sleep(5); // parent will exit while child is sleeping
        printf("[Orphan-Child] Now my new PPID = %d (adopted by init)\n", getppid());
        exit(0);
    }
    else {
        printf("[Parent] Exiting now. Orphan child PID = %d will continue.\n", o);
        exit(0); // parent exits → orphan created
    }
}
