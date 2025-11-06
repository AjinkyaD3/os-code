#include <stdio.h>
#include <stdlib.h>

int fifo(int pages[], int n, int frames) {
    int q[frames], front = 0, faults = 0;
    for (int i = 0; i < frames; i++) q[i] = -1;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) if (q[j] == pages[i]) { hit = 1; break; }
        if (!hit) { q[front] = pages[i]; front = (front + 1) % frames; faults++; }
    }
    return faults;
}

int lru(int pages[], int n, int frames) {
    int f[frames], age[frames], faults = 0;
    for (int i = 0; i < frames; i++) { f[i] = -1; age[i] = 0; }
    for (int i = 0; i < n; i++) {
        int p = pages[i], hit = -1;
        for (int j = 0; j < frames; j++) if (f[j] == p) { hit = j; break; }
        for (int j = 0; j < frames; j++) if (f[j] != -1) age[j]++;
        if (hit != -1) { age[hit] = 0; }
        else {
            int pos = -1, oldest = -1;
            for (int j = 0; j < frames; j++) if (f[j] == -1) { pos = j; break; }
            if (pos == -1) { for (int j = 0; j < frames; j++) if (age[j] > oldest) { oldest = age[j]; pos = j; } }
            f[pos] = p; age[pos] = 0; faults++;
        }
    }
    return faults;
}

int optimal(int pages[], int n, int frames) {
    int f[frames], faults = 0;
    for (int i = 0; i < frames; i++) f[i] = -1;
    for (int i = 0; i < n; i++) {
        int p = pages[i], hit = 0;
        for (int j = 0; j < frames; j++) if (f[j] == p) { hit = 1; break; }
        if (hit) continue;
        int pos = -1;
        for (int j = 0; j < frames; j++) if (f[j] == -1) { pos = j; break; }
        if (pos == -1) {
            int farIdx = -1, farDist = -1;
            for (int j = 0; j < frames; j++) {
                int d = 999999;
                for (int k = i + 1; k < n; k++) if (pages[k] == f[j]) { d = k - i; break; }
                if (d > farDist) { farDist = d; farIdx = j; }
            }
            pos = farIdx;
        }
        f[pos] = p; faults++;
    }
    return faults;
}

int main() {
    int n, frames;
    printf("Enter number of pages and frames (>=3): ");
    scanf("%d %d", &n, &frames);
    if (frames < 3 || n <= 0) return 1;
    int pages[n];
    printf("Enter reference string (%d integers):\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("FIFO faults: %d\n", fifo(pages, n, frames));
    printf("LRU faults: %d\n", lru(pages, n, frames));
    printf("Optimal faults: %d\n", optimal(pages, n, frames));
    return 0;
}

