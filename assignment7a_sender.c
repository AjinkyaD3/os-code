#include <stdio.h> // io
#include <stdlib.h> // std
#include <unistd.h> // close, read, write
#include <fcntl.h> // open
#include <sys/stat.h> // mkfifo
#include <string.h> // strlen

int main() { // sender (process 1)
    char *fifo1 = "fifo1"; // pipe 1
    char *fifo2 = "fifo2"; // pipe 2
    mkfifo(fifo1, 0666); // make fifo1
    mkfifo(fifo2, 0666); // make fifo2

    char line[256]; // input buffer
    printf("Enter a sentence (single line): "); // prompt
    fgets(line, sizeof(line), stdin); // read line

    int fdw = open(fifo1, O_WRONLY); // open fifo1 for write
    write(fdw, line, strlen(line)); // write sentence
    close(fdw); // close

    int fdr = open(fifo2, O_RDONLY); // open fifo2 for read
    char out[512]; // output buffer
    int n = read(fdr, out, sizeof(out) - 1); // read result file content
    if (n > 0) { out[n] = '\0'; printf("\nResult from receiver:\n%s", out); } // print
    close(fdr); // close
    return 0; // ok
}


