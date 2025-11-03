// include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// simple bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) { // outer loop
        for (int j = 0; j < n - i - 1; j++) { // inner loop
            if (arr[j] > arr[j + 1]) { // compare
                int t = arr[j]; // swap start
                arr[j] = arr[j + 1];
                arr[j + 1] = t; // swap end
            }
        }
    }
}

// print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) // loop
        printf("%d ", arr[i]); // print value
    printf("\n"); // newline
}

int main() {
    int n; // number of items
    printf("Enter count: "); // ask count
    scanf("%d", &n); // read count

    int arr[n]; // array
    printf("Enter %d integers: ", n); // ask values
    for (int i = 0; i < n; i++) // read loop
        scanf("%d", &arr[i]); // read value

    printf("[parent] pid=%d sorting...\n", getpid()); // info
    bubbleSort(arr, n); // sort
    printf("[parent] sorted: "); // label
    printArray(arr, n); // show sorted

    pid_t pid = fork(); // make child

    if (pid < 0) { // fork error
        printf("fork failed\n"); // error
        return 1; // exit
    } else if (pid == 0) { // child branch
        printf("[child] pid=%d execve('./child') with sorted numbers\n", getpid()); // info
        char *args[n + 2]; // argv array size
        char arg_strings[n][20]; // buffers for numbers

        args[0] = "./child"; // program path
        for (int i = 0; i < n; i++) { // fill args
            sprintf(arg_strings[i], "%d", arr[i]); // int -> string
            args[i + 1] = arg_strings[i]; // set argv
        }
        args[n + 1] = NULL; // argv terminator

        execve(args[0], args, NULL); // replace image
        perror("execve"); // if here, error occurred
        exit(1); // exit error
    } else { // parent branch
        printf("[parent] waiting for child...\n"); // info
        wait(NULL); // wait child
        printf("[parent] child done, exiting\n"); // done
    }

    return 0; // exit ok
}

