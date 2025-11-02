#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1" // FIFO for writing from process1 to process2
#define FIFO2 "fifo2" // FIFO for writing from process2 to process1

// Function to count characters, words, and lines
void count_stats(char *sentence, int *chars, int *words, int *lines) {
    *chars = strlen(sentence);
    *words = 0;
    *lines = 0;
    int in_word = 0;

    for (int i = 0; i < *chars; i++) {
        if (sentence[i] == '\n') { // Fixed '=' to '=='
            (*lines)++;
        }
        
        // A word is bounded by space, tab, or newline
        if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
    
    // If the text doesn't end with a newline, the last line isn't counted
    if (*chars > 0 && sentence[*chars - 1] != '\n') {
        (*lines)++;
    }
}

int main() {
    char sentence[4096];
    int chars, words, lines;
    char result[1024];

    // Create FIFOs just in case process 2 is run first
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("[Process 2] Waiting for data from Process 1...\n");
    
    // Read the sentence from FIFO1
    int fd1 = open(FIFO1, O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening FIFO1 for reading");
        exit(1);
    }
    read(fd1, sentence, sizeof(sentence));
    close(fd1);

    printf("[Process 2] Data received. Processing...\n");
    
    // Count characters, words, and lines
    count_stats(sentence, &chars, &words, &lines);

    // Write the statistics to a file
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) { // Fixed '=='
        perror("Error opening output.txt");
        exit(1);
    }
    fprintf(fp, "Number of characters: %d\n", chars);
    fprintf(fp, "Number of words: %d\n", words);
    fprintf(fp, "Number of lines: %d\n", lines);
    fclose(fp);

    // Read the result from the file back into a string
    fp = fopen("output.txt", "r");
    if (fp == NULL) {
        perror("Error reading output.txt");
        exit(1);
    }
    // Read the entire file content into the 'result' string
    fread(result, sizeof(char), sizeof(result) - 1, fp);
    result[sizeof(result) - 1] = '\0'; // Ensure null-termination
    fclose(fp);

    // Write the result string to FIFO2
    int fd2 = open(FIFO2, O_WRONLY);
    if (fd2 < 0) {
        perror("Error opening FIFO2 for writing");
        exit(1);
    }
    write(fd2, result, strlen(result) + 1);
    close(fd2);
    
    printf("[Process 2] Stats computed and sent back. Exiting.\n");
    return 0;
}

