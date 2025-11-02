#include <stdio.h>
#include <stdlib.h> // For exit

#define FRAME_MAX 20
#define REF_MAX 50

// --- First-In, First-Out (FIFO) ---
void fifo(int refString[], int n, int frameSize) {
    printf("\n--- FIFO Algorithm ---\n");
    int frames[frameSize];
    int frameAge[frameSize]; // To track which is oldest
    int faults = 0;
    
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1; // -1 indicates empty
        frameAge[i] = 0;
    }

    int oldest_idx = 0; // Index of the frame to replace

    for (int i = 0; i < n; i++) {
        int page = refString[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }
        
        printf("%d: [", page);
        if (found == 0) { // Page Fault
            faults++;
            frames[oldest_idx] = page;
            // Move the "oldest" index to the next position, wrapping around
            oldest_idx = (oldest_idx + 1) % frameSize;
            
            // Print frames and fault
            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] F\n");
        } else {
            // Print frames and no fault
            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] H\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

// --- Least Recently Used (LRU) ---
void lru(int refString[], int n, int frameSize) {
    printf("\n--- LRU Algorithm ---\n");
    int frames[frameSize];
    int frameTime[frameSize]; // Tracks *when* a frame was last used
    int faults = 0;
    
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1; // -1 indicates empty
        frameTime[i] = 0;
    }

    int time = 0; // A counter for "time"
    
    for (int i = 0; i < n; i++) {
        time++;
        int page = refString[i];
        int found = 0;
        int empty_slot = -1;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = 1;
                frameTime[j] = time; // Update its last-used time
                break;
            }
            if (frames[j] == -1 && empty_slot == -1) {
                empty_slot = j;
            }
        }

        printf("%d: [", page);
        if (found == 0) { // Page Fault
            faults++;
            
            if (empty_slot != -1) {
                // Use the empty slot
                frames[empty_slot] = page;
                frameTime[empty_slot] = time;
            } else {
                // Find the LRU page (one with the smallest time)
                int lru_idx = 0;
                for (int j = 1; j < frameSize; j++) {
                    if (frameTime[j] < frameTime[lru_idx]) {
                        lru_idx = j;
                    }
                }
                // Replace the LRU page
                frames[lru_idx] = page;
                frameTime[lru_idx] = time;
            }

            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] F\n");
        } else {
            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] H\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}

// --- Optimal Algorithm ---
void optimal(int refString[], int n, int frameSize) {
    printf("\n--- Optimal Algorithm ---\n");
    int frames[frameSize];
    int faults = 0;

    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = refString[i];
        int found = 0;
        int empty_slot = -1;

        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
            if (frames[j] == -1 && empty_slot == -1) {
                empty_slot = j;
            }
        }

        printf("%d: [", page);
        if (found == 0) { // Page Fault
            faults++;
            
            if (empty_slot != -1) {
                frames[empty_slot] = page;
            } else {
                // Find the page to replace (farthest-in-future)
                int replace_idx = 0;
                int farthest = -1; // Farthest distance
                
                for (int j = 0; j < frameSize; j++) {
                    int current_page = frames[j];
                    int dist = 0;
                    // Look for the page in the future
                    for (int k = i + 1; k < n; k++) {
                        if (refString[k] == current_page) {
                            dist = k; // Found it at time k
                            break;
                        }
                    }
                    
                    if (dist == 0) { // Page is not used again
                        replace_idx = j;
                        farthest = 99999; // Replace this one immediately
                        break;
                    }
                    
                    if (dist > farthest) {
                        farthest = dist;
                        replace_idx = j;
                    }
                }
                // Replace the chosen page
                frames[replace_idx] = page;
            }
            
            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] F\n");
        } else {
            for(int k=0; k<frameSize; k++) printf("%d ", frames[k]);
            printf("] H\n");
        }
    }
    printf("Total Page Faults: %d\n", faults);
}


int main() {
    int refString[REF_MAX];
    int frameSize, n = 0, ch;

    printf("Enter the page reference string (e.g., 7 0 1 2...), end with -1:\n");
    while (n < REF_MAX) {
        int page;
        scanf("%d", &page);
        if (page == -1) {
            break;
        }
        refString[n] = page;
        n++;
    }

    printf("Enter the size of the frame (must be >= 3): ");
    scanf("%d", &frameSize);
    if (frameSize < 3) frameSize = 3;

    do {
        printf("\nMENU\n");
        printf("1. FIFO\n");
        printf("2. Least Recently Used (LRU)\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                fifo(refString, n, frameSize);
                break;
            case 2:
                lru(refString, n, frameSize);
                break;
            case 3:
                optimal(refString, n, frameSize);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again!\n");
        }
    } while (ch != 4);
    
    return 0;
}

