#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

void count_stats(char *sentence, int *chars, int *words, int *lines) {
    *chars = strlen(sentence);
    *words = *lines = 0;
    int in_word = 0;

    for (int i = 0; i < *chars; i++) {
        if (sentence[i] == '\n')
            (*lines)++;
        if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
    if (*chars > 0 && sentence[*chars - 1] != '\n')
        (*lines)++;
}

int main() {
    char sentence[4096], result[1024];
    int chars, words, lines;
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("[Process 2] Waiting for data from Process 1...\n");
    int fd1 = open(FIFO1, O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening FIFO1 for reading");
        exit(1);
    }
    read(fd1, sentence, sizeof(sentence));
    close(fd1);

    printf("[Process 2] Data received. Processing...\n");
    count_stats(sentence, &chars, &words, &lines);

    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("Error opening output.txt");
        exit(1);
    }
    fprintf(fp, "Number of characters: %d\nNumber of words: %d\nNumber of lines: %d\n", chars, words, lines);
    fclose(fp);

    fp = fopen("output.txt", "r");
    if (fp == NULL) {
        perror("Error reading output.txt");
        exit(1);
    }
    fread(result, sizeof(char), sizeof(result) - 1, fp);
    result[sizeof(result) - 1] = '\0';
    fclose(fp);

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

