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
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // --------- CASE 2: Program called AGAIN via execve (child role) ---------
    // argc > 1 means array elements were passed as command-line arguments
    if(argc > 1) {
        printf("\nChild Process (After execve) - Printing Array in Reverse:\n");

        // Print elements in reverse order
        for(int i = argc - 1; i > 0; i--)
            printf("%s ", argv[i]);

        printf("\n");
        return 0;   // Child done
    }

    // --------- CASE 1: MAIN PROGRAM (Parent role) ---------
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array (simple ascending)
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }

    // Create child process
    pid_t pid = fork();

    if(pid == 0) {  // Child Process
        // Convert sorted integers to strings for execve
        char *args[n+2];
        args[0] = argv[0];  // program name

        for(int i = 0; i < n; i++) {
            args[i+1] = malloc(10);
            sprintf(args[i+1], "%d", arr[i]);
        }
        args[n+1] = NULL;  // end of argument list

        // Replace child with same program --> now argc > 1 so child prints reverse
        execve(argv[0], args, NULL);

        perror("execve failed"); // executes only if execve fails
    }
    else { // Parent Process
        wait(NULL); // Parent waits for child
    }

    return 0;
}
