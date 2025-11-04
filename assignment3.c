/*
Problem Statement 3:
Implement the C program in which main program accepts an array. Main uses FORK
to create a child process. Parent sorts and passes the sorted array to child via
EXECVE command line. Child uses EXECVE to load the same program which displays
array in reverse order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // Case 2: Child executed via execve → print array reverse
    if(argc > 1) {
        printf("Child (after execve) prints array in reverse:\n");
        for(int i = argc - 1; i > 0; i--)
            printf("%s ", argv[i]);
        printf("\n");
        return 0;
    }

    // Case 1: Original parent process
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }

    pid_t pid = fork();

    if(pid == 0) {  // Child
        // Convert sorted array to string arguments
        char *args[n+2];
        args[0] = argv[0];
        for(int i = 0; i < n; i++) {
            args[i+1] = malloc(10);
            sprintf(args[i+1], "%d", arr[i]);
        }
        args[n+1] = NULL;

        execve(argv[0], args, NULL);
        perror("execve failed");
    }
    else { // Parent
        wait(NULL);
    }

    return 0;
}
