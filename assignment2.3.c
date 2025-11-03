#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[NEW PROGRAM] Child (PID: %d) is now running './child'.\n", getpid());
    printf("[NEW PROGRAM] Displaying integers in reverse order: ");
    for (int i = argc - 1; i >= 1; i--)
        printf("%d ", atoi(argv[i]));
    printf("\n");
    return 0;
}

