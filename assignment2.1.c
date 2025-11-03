// include standard input/output
#include <stdio.h>
// include standard library (for exit)
#include <stdlib.h>
// include POSIX for fork, getpid, sleep
#include <unistd.h>
// include wait for wait, waitpid
#include <sys/wait.h>

// simple bubble sort function
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) { // loop n-1 times
        for (int j = 0; j < n - i - 1; j++) { // inner loop
            if (arr[j] > arr[j + 1]) { // compare adjacent
                int temp = arr[j]; // swap start
                arr[j] = arr[j + 1];
                arr[j + 1] = temp; // swap end
            }
        }
    }
}

// print array with a small label
void printArray(int arr[], int n, char *label) {
    printf("%s", label); // print label
    for (int i = 0; i < n; i++) // loop over array
        printf("%d ", arr[i]); // print value
    printf("\n"); // new line
}

int main() {
    int n; // number of elements
    printf("Enter count: "); // ask for count
    scanf("%d", &n); // read count

    int arr[n]; // input array (VLA for simplicity)
    printf("Enter %d integers: ", n); // ask for numbers
    for (int i = 0; i < n; i++) // read loop
        scanf("%d", &arr[i]); // read value

    pid_t pid = fork(); // create child for sorting

    if (pid < 0) { // fork error
        printf("fork failed\n"); // print error
        return 1; // exit with error
    } else if (pid == 0) { // child process
        printf("[child] pid=%d sorting...\n", getpid()); // child info
        bubbleSort(arr, n); // child sorts
        printArray(arr, n, "[child] sorted: "); // show child result
        printf("[child] done\n"); // child done
        exit(0); // child exit
    } else { // parent process
        printf("[parent] pid=%d sorting its copy...\n", getpid()); // parent info
        bubbleSort(arr, n); // parent sorts
        printf("[parent] waiting for child...\n"); // wait info
        wait(NULL); // wait for child
        printArray(arr, n, "[parent] sorted: "); // show parent result
    }

    // --- Demonstrate ZOMBIE state ---
    pid_t z = fork(); // make a short-lived child
    if (z == 0) { // zombie child
        printf("[z-child] pid=%d exiting now (becomes zombie until reaped)\n", getpid()); // info
        exit(0); // exit immediately -> zombie until parent waits
    } else { // parent side
        printf("[parent] created z-child pid=%d, sleeping 3s to let zombie exist...\n", z); // info
        sleep(3); // give time to observe zombie in ps
        waitpid(z, NULL, 0); // reap zombie
        printf("[parent] reaped z-child (zombie cleared)\n"); // done
    }

    // --- Demonstrate ORPHAN state ---
    pid_t o = fork(); // make a child that outlives parent
    if (o == 0) { // orphan child
        printf("[o-child] pid=%d sleeping 3s, parent will exit -> I become orphan\n", getpid()); // info
        sleep(3); // wait for parent to exit
        printf("[o-child] now my ppid=%d (adopted by init)\n", getppid()); // show new parent
        exit(0); // exit
    } else { // parent will not wait here
        printf("[parent] exiting now to create orphan (child pid=%d)\n", o); // info
        return 0; // parent exits, child continues as orphan
    }
}

