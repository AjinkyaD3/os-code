// include headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("[child-program] pid=%d running, got %d args\n", getpid(), argc - 1); // info
    printf("reverse: "); // label
    for (int i = argc - 1; i >= 1; i--) // loop from last to first arg
        printf("%d ", atoi(argv[i])); // print as int
    printf("\n"); // newline
    return 0; // exit ok
}

