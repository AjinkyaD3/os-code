// assignment6.c
#include <stdio.h> // io
#include <stdlib.h> // std

int fifo(int pages[], int n, int frames) { // FIFO
    int q[frames], front = 0, faults = 0; // queue
    for (int i = 0; i < frames; i++) q[i] = -1; // empty
    for (int i = 0; i < n; i++) { // each ref
        int hit = 0; // miss by default
        for (int j = 0; j < frames; j++) if (q[j] == pages[i]) { hit = 1; break; } // check hit
        if (!hit) { q[front] = pages[i]; front = (front + 1) % frames; faults++; } // replace
    }
    return faults; // total
}

int lru(int pages[], int n, int frames) { // LRU
    int f[frames], age[frames], faults = 0; // frames and ages
    for (int i = 0; i < frames; i++) { f[i] = -1; age[i] = 0; } // init
    for (int i = 0; i < n; i++) { // each ref
        int p = pages[i], hit = -1; // page and hit idx
        for (int j = 0; j < frames; j++) if (f[j] == p) { hit = j; break; } // find hit
        for (int j = 0; j < frames; j++) if (f[j] != -1) age[j]++; // age others
        if (hit != -1) { age[hit] = 0; } // reset age on hit
        else { // need replace
            int pos = -1, oldest = -1; // find max age
            for (int j = 0; j < frames; j++) if (f[j] == -1) { pos = j; break; } // empty slot
            if (pos == -1) { for (int j = 0; j < frames; j++) if (age[j] > oldest) { oldest = age[j]; pos = j; } } // evict
            f[pos] = p; age[pos] = 0; faults++; // place
        }
    }
    return faults; // total
}

int optimal(int pages[], int n, int frames) { // Optimal
    int f[frames], faults = 0; // frames
    for (int i = 0; i < frames; i++) f[i] = -1; // init
    for (int i = 0; i < n; i++) { // each ref
        int p = pages[i], hit = 0; // current page
        for (int j = 0; j < frames; j++) if (f[j] == p) { hit = 1; break; } // check hit
        if (hit) continue; // no fault
        int pos = -1; // where to put
        for (int j = 0; j < frames; j++) if (f[j] == -1) { pos = j; break; } // empty slot
        if (pos == -1) { // choose farthest future use
            int farIdx = -1, farDist = -1; // best victim
            for (int j = 0; j < frames; j++) { // for each frame
                int d = 999999; // default if never used again
                for (int k = i + 1; k < n; k++) if (pages[k] == f[j]) { d = k - i; break; } // find next use
                if (d > farDist) { farDist = d; farIdx = j; } // pick farthest
            }
            pos = farIdx; // victim frame
        }
        f[pos] = p; faults++; // place
    }
    return faults; // total
}

int main() { // main
    int n, frames; // inputs
    printf("Enter number of pages and frames (>=3): "); // prompt
    scanf("%d %d", &n, &frames); // read
    if (frames < 3 || n <= 0) return 1; // guard
    int pages[n]; // refs
    printf("Enter reference string (%d integers):\n", n); // prompt
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]); // read
    printf("FIFO faults: %d\n", fifo(pages, n, frames)); // run FIFO
    printf("LRU faults: %d\n", lru(pages, n, frames)); // run LRU
    printf("Optimal faults: %d\n", optimal(pages, n, frames)); // run Optimal
    return 0; // ok
}