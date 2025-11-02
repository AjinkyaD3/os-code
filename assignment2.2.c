#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> // Needed for sprintf

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    printf("[PARENT] Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("[PARENT] Enter the integers to be sorted: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Parent sorts the array *before* forking
    printf("[PARENT] Parent process (PID: %d) sorting the integers...\n", getpid());
    bubbleSort(arr, n);
    
    printf("[PARENT] Parent (PID: %d) sorted integers: ", getpid());
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // --- Child process ---
        printf("[CHILD] Child process (PID: %d) is preparing to execute new program.\n", getpid());

        // We need to convert the integer array into an array of strings
        // to pass as command-line arguments.
        // args[0] is program name, args[1...n] are numbers, args[n+1] is NULL.
        char *args[n + 2];
        
        // Allocate memory for each argument string
        char arg_strings[n][20]; // Buffer to hold the number strings
        
        args[0] = "./child"; // Name of the program to execute
        
        for (i = 0; i < n; i++) {
            sprintf(arg_strings[i], "%d", arr[i]); // Convert int to string
            args[i + 1] = arg_strings[i];          // Point to the string
        }
        args[n + 1] = NULL; // Argument list must be NULL-terminated
        
        // execve replaces the child process with the new program
        execve(args[0], args, NULL);
        
        // If execve returns, it means an error occurred
        perror("execve failed");
        exit(1);
    } 
    else {
        // --- Parent process ---
        printf("[PARENT] Parent (PID: %d) waiting for child to complete...\n", getpid());
        wait(NULL); // Wait for the child (which is now the 'child' program)
        printf("[PARENT] Child process has finished. Parent exiting.\n");
    }

    return 0;
}

