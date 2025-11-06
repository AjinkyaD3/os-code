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
        printf("\n[Child] PID = %d\n", getpid());
        bubbleSort(arr, n);

        printf("[Child] Sorted Array: ");
        for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    }
    else {
        printf("\n[Parent] PID = %d\n", getpid());
        bubbleSort(arr, n);

        printf("[Parent] Sorted Array: ");
        for(int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");

        wait(NULL);
        printf("[Parent] Child finished. No Zombie in sorting part.\n");
    }

    pid_t z = fork();

    if(z == 0) {
        printf("\n[Zombie-Child] PID = %d exiting now.\n", getpid());
        exit(0);
    }
    else {
        printf("[Parent] Created zombie child PID = %d. Sleeping 5 seconds...\n", z);
        printf(">>> Check zombie using: ps -l\n");
        sleep(5);
        waitpid(z, NULL, 0);
        printf("[Parent] Zombie cleared.\n");
    }

    pid_t o = fork();

    if(o == 0) {
        printf("\n[Orphan-Child] PID = %d sleeping 5 seconds.\n", getpid());
        sleep(5);
        printf("[Orphan-Child] Now my new PPID = %d (adopted by init)\n", getppid());
        exit(0);
    }
    else {
        printf("[Parent] Exiting now. Orphan child PID = %d will continue.\n", o);
        exit(0);
    }
}
