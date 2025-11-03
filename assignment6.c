#include <stdio.h>
#include <stdlib.h>

#define REF_MAX 50

void printFrames(int frames[], int frameSize, int page, char status) {
    printf("%d: [", page);
    for (int k = 0; k < frameSize; k++)
        printf("%d ", frames[k]);
    printf("] %c\n", status);
}

void fifo(int refString[], int n, int frameSize) {
    printf("\n--- FIFO Algorithm ---\n");
    int frames[frameSize], faults = 0, oldest_idx = 0;
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = refString[i], found = 0;
        for (int j = 0; j < frameSize && !found; j++)
            if (frames[j] == page) found = 1;
        
        if (!found) {
            faults++;
            frames[oldest_idx] = page;
            oldest_idx = (oldest_idx + 1) % frameSize;
            printFrames(frames, frameSize, page, 'F');
        } else {
            printFrames(frames, frameSize, page, 'H');
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

void lru(int refString[], int n, int frameSize) {
    printf("\n--- LRU Algorithm ---\n");
    int frames[frameSize], frameTime[frameSize], faults = 0, time = 0;
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        frameTime[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        time++;
        int page = refString[i], found = 0, empty_slot = -1;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = 1;
                frameTime[j] = time;
                break;
            }
            if (frames[j] == -1 && empty_slot == -1)
                empty_slot = j;
        }

        if (!found) {
            faults++;
            if (empty_slot != -1) {
                frames[empty_slot] = page;
                frameTime[empty_slot] = time;
            } else {
                int lru_idx = 0;
                for (int j = 1; j < frameSize; j++)
                    if (frameTime[j] < frameTime[lru_idx])
                        lru_idx = j;
                frames[lru_idx] = page;
                frameTime[lru_idx] = time;
            }
            printFrames(frames, frameSize, page, 'F');
        } else {
            printFrames(frames, frameSize, page, 'H');
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

void optimal(int refString[], int n, int frameSize) {
    printf("\n--- Optimal Algorithm ---\n");
    int frames[frameSize], faults = 0;
    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = refString[i], found = 0, empty_slot = -1;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
            if (frames[j] == -1 && empty_slot == -1)
                empty_slot = j;
        }

        if (!found) {
            faults++;
            if (empty_slot != -1) {
                frames[empty_slot] = page;
            } else {
                int replace_idx = 0, farthest = -1;
                for (int j = 0; j < frameSize; j++) {
                    int dist = 0;
                    for (int k = i + 1; k < n; k++) {
                        if (refString[k] == frames[j]) {
                            dist = k;
                            break;
                        }
                    }
                    if (dist == 0) {
                        replace_idx = j;
                        break;
                    }
                    if (dist > farthest) {
                        farthest = dist;
                        replace_idx = j;
                    }
                }
                frames[replace_idx] = page;
            }
            printFrames(frames, frameSize, page, 'F');
        } else {
            printFrames(frames, frameSize, page, 'H');
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int refString[REF_MAX], frameSize, n = 0, ch;
    printf("Enter the page reference string (e.g., 7 0 1 2...), end with -1:\n");
    while (n < REF_MAX) {
        int page;
        scanf("%d", &page);
        if (page == -1) break;
        refString[n++] = page;
    }

    printf("Enter the size of the frame (must be >= 3): ");
    scanf("%d", &frameSize);
    if (frameSize < 3) frameSize = 3;

    do {
        printf("\nMENU\n1. FIFO\n2. Least Recently Used (LRU)\n3. Optimal\n4. Exit\nYour Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: fifo(refString, n, frameSize); break;
            case 2: lru(refString, n, frameSize); break;
            case 3: optimal(refString, n, frameSize); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again!\n");
        }
    } while (ch != 4);
    return 0;
}
