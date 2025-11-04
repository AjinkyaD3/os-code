/*
Problem Statement 3:
Implement the C program in which main program accepts an array. Main uses FORK
to create a child process. Parent sorts and passes the sorted array to child via
EXECVE command line. Child uses EXECVE to load the same program which displays
array in reverse order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ; // for execve env

void bubbleSort(int *a, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) { int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }
}

int run_child_mode(int argc, char **argv) { // argv[1] == "child"
    printf("[child-program] printing reverse: ");
    for (int i = argc - 1; i >= 2; i--) printf("%d ", atoi(argv[i]));
    printf("\n");
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) return run_child_mode(argc, argv);

    int n; printf("Enter count: "); scanf("%d", &n);
    int arr[n]; printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    bubbleSort(arr, n); // parent sorts first

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    else if (pid == 0) {
        // prepare args: argv[0] same program, argv[1] = "child", then numbers
        char *args[n + 3];
        char nums[n][20];
        args[0] = argv[0];
        args[1] = "child";
        for (int i = 0; i < n; i++) { sprintf(nums[i], "%d", arr[i]); args[i + 2] = nums[i]; }
        args[n + 2] = NULL;
        execve(args[0], args, environ);
        perror("execve");
        exit(1);
                } else {
        wait(NULL);
    }
    return 0;
}

