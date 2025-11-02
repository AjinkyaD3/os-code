#include <stdio.h>
#include <stdlib.h> // For atoi
#include <unistd.h> // For getpid

// This program's job is just to print arguments in reverse
// argc = argument count
// argv = argument vector (array of strings)
int main(int argc, char *argv[]) {
    
    // argc includes the program name itself, so (argc - 1) is the number of integers
    int n = argc - 1;
    
    printf("[NEW PROGRAM] Child (PID: %d) is now running './child'.\n", getpid());
    printf("[NEW PROGRAM] Displaying integers in reverse order: ");
    
    // We start at the last argument (n) and go down to the first (1)
    // argv[0] is the program name ("./child")
    for (int i = n; i >= 1; i--) {
        printf("%d ", atoi(argv[i])); // atoi converts string back to integer
    }
    printf("\n");
    
    return 0;
}

