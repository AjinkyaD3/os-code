#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    char buffer[4096] = {0}, result[1024];
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter sentences (press Ctrl+D on a new line to end):\n");
    int n;
    while ((n = read(STDIN_FILENO, buffer + strlen(buffer), 1024)) > 0);
    
    printf("\n[Process 1] Sending text to Process 2...\n");
    int fd1 = open(FIFO1, O_WRONLY);
    if (fd1 < 0) {
        perror("Error opening FIFO1 for writing");
        exit(1);
    }
    write(fd1, buffer, strlen(buffer) + 1);
    close(fd1);

    printf("[Process 1] Waiting for stats from Process 2...\n");
    int fd2 = open(FIFO2, O_RDONLY);
    if (fd2 < 0) {
        perror("Error opening FIFO2 for reading");
        exit(1);
    }
    read(fd2, result, sizeof(result));
    close(fd2);

    printf("\n[Process 1] Received processed output from Process 2:\n%s\n", result);
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}

