#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("[PARENT] Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("[PARENT] Enter the integers to be sorted: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("[PARENT] Parent process (PID: %d) sorting the integers...\n", getpid());
    bubbleSort(arr, n);
    printf("[PARENT] Parent (PID: %d) sorted integers: ", getpid());
    printArray(arr, n);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        printf("[CHILD] Child process (PID: %d) is preparing to execute new program.\n", getpid());
        char *args[n + 2];
        char arg_strings[n][20];
        
        args[0] = "./child";
        for (int i = 0; i < n; i++) {
            sprintf(arg_strings[i], "%d", arr[i]);
            args[i + 1] = arg_strings[i];
        }
        args[n + 1] = NULL;
        
        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } 
    else {
        printf("[PARENT] Parent (PID: %d) waiting for child to complete...\n", getpid());
        wait(NULL);
        printf("[PARENT] Child process has finished. Parent exiting.\n");
    }

    return 0;
}

