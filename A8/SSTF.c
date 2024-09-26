#include <stdio.h>
#include <stdlib.h>

int findClosestRequest(int requests[], int n, int head, int visited[]) {
    int minDiff = 10000;  // Large value to find the minimum difference
    int closestIdx = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int diff = abs(requests[i] - head);
            if (diff < minDiff) {
                minDiff = diff;
                closestIdx = i;
            }
        }
    }

    return closestIdx;
}

void SSTF(int requests[], int n, int head) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int seekCount = 0;
    int sequence[n];

    printf("Seek sequence: ");
    for (int i = 0; i < n; i++) {
        int closestIdx = findClosestRequest(requests, n, head, visited);
        visited[closestIdx] = 1;
        seekCount += abs(requests[closestIdx] - head);
        head = requests[closestIdx];
        sequence[i] = head;
        printf("%d ", head);
    }

    printf("\nTotal Seek Time: %d\n", seekCount);
}

int main() {
    int n;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    SSTF(requests, n, head);

    return 0;
}
