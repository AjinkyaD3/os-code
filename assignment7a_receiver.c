#include <stdio.h> // io
#include <stdlib.h> // std
#include <unistd.h> // close, read, write
#include <fcntl.h> // open
#include <sys/stat.h> // mkfifo
#include <ctype.h> // isspace
#include <string.h> // strlen

int main() { // receiver (process 2)
    char *fifo1 = "fifo1"; // pipe 1
    char *fifo2 = "fifo2"; // pipe 2
    mkfifo(fifo1, 0666); // make fifo1
    mkfifo(fifo2, 0666); // make fifo2

    int fdr = open(fifo1, O_RDONLY); // read sentence
    char buf[512]; // buffer
    int n = read(fdr, buf, sizeof(buf) - 1); // read
    close(fdr); // close
    if (n <= 0) return 1; // no data
    buf[n] = '\0'; // terminate

    int chars = 0, words = 0, lines = 0; // counts
    int inWord = 0; // flag
    for (int i = 0; buf[i] != '\0'; i++) { // scan
        chars++; // count char
        if (buf[i] == '\n') lines++; // line
        if (isspace((unsigned char)buf[i])) inWord = 0; // space ends word
        else if (!inWord) { inWord = 1; words++; } // start new word
    }

    FILE *fp = fopen("result.txt", "w"); // open file
    fprintf(fp, "Chars: %d\nWords: %d\nLines: %d\n", chars, words, lines); // write
    fclose(fp); // close file

    int fdw = open(fifo2, O_WRONLY); // open fifo2
    FILE *fr = fopen("result.txt", "r"); // read file
    char out[512]; // buffer
    int m = fread(out, 1, sizeof(out) - 1, fr); // read all
    fclose(fr); // close file
    out[m] = '\0'; // terminate
    write(fdw, out, strlen(out)); // send to sender
    close(fdw); // close
    return 0; // ok
}


