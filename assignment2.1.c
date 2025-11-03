#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n, char* prefix) {
    printf("%s", prefix);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the integers to be sorted: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        printf("[CHILD] Child process sorting the integers...\n");
        bubbleSort(arr, n);
        printArray(arr, n, "[CHILD] Sorted integers by child process: ");
        printf("[CHILD] Child process exiting.\n");
        exit(0);
    } 
    else {
        printf("[PARENT] Parent process sorting its *own* copy of integers...\n");
        bubbleSort(arr, n);
        printf("[PARENT] Parent process waiting for child process to complete...\n");
        wait(NULL);
        printf("[PARENT] Child has completed.\n");
        printArray(arr, n, "[PARENT] Sorted integers by parent process: ");
    }

    return 0;
}

