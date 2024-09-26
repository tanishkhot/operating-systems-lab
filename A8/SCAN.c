#include <stdio.h>
#include <stdlib.h>

void SCAN(int requests[], int n, int head, int disk_size, int direction) {
    int seekCount = 0;
    int sequence[n + 2];
    int idx = 0;

    printf("Seek sequence: ");
    
    if (direction == 1) {
        // Sort the requests
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (requests[i] > requests[j]) {
                    int temp = requests[i];
                    requests[i] = requests[j];
                    requests[j] = temp;
                }
            }
        }

        // Service requests to the right of the head
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                sequence[idx++] = requests[i];
                seekCount += abs(requests[i] - head);
                head = requests[i];
            }
        }

        // Move to the end of the disk
        seekCount += abs(disk_size - head);
        head = disk_size;
        sequence[idx++] = disk_size;

        // Reverse and service requests to the left of the head
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                sequence[idx++] = requests[i];
                seekCount += abs(requests[i] - head);
                head = requests[i];
            }
        }
    }

    // Print seek sequence
    for (int i = 0; i < idx; i++) {
        printf("%d ", sequence[i]);
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

    int disk_size;
    printf("Enter disk size (max cylinder): ");
    scanf("%d", &disk_size);

    int direction;
    printf("Enter initial direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    SCAN(requests, n, head, disk_size, direction);

    return 0;
}
