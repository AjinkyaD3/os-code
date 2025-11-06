#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if(argc > 1) {
        printf("\nChild Process (After execve) - Printing Array in Reverse:\n");
        for(int i = argc - 1; i > 0; i--)
            printf("%s ", argv[i]);

        printf("\n");
        return 0;
    }

    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }

    pid_t pid = fork();

    if(pid == 0) {
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
    else {
        wait(NULL);
    }

    return 0;
}
