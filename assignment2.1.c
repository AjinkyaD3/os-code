#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Simple bubble sort
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
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the integers to be sorted: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // fork failed
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        // --- Child process ---
        printf("[CHILD] Child process sorting the integers...\n");
        bubbleSort(arr, n);
        printf("[CHILD] Sorted integers by child process: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("[CHILD] Child process exiting.\n");
        exit(0); // Child exits
    } 
    else {
        // --- Parent process ---
        printf("[PARENT] Parent process sorting its *own* copy of integers...\n");
        // Note: The parent's `arr` is a separate copy from the child's.
        bubbleSort(arr, n); 
        
        printf("[PARENT] Parent process waiting for child process to complete...\n");
        wait(NULL); // Wait for the child process to complete
        
        printf("[PARENT] Child has completed.\n");
        printf("[PARENT] Sorted integers by parent process: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}

