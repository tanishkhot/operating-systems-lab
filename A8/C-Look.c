#include <stdio.h>
#include <stdlib.h>

void C_LOOK(int requests[], int n, int head) {
    int seekCount = 0;
    int sequence[n + 1];
    int idx = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("Seek sequence: ");
    
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) {
            sequence[idx++] = requests[i];
            seekCount += abs(requests[i] - head);
            head = requests[i];
        }
    }
   
    seekCount += abs(requests[0] - head);
    head = requests[0];
    sequence[idx++] = head;

    for (int i = 1; i < n; i++) {
        if (requests[i] > head) {
            sequence[idx++] = requests[i];
            seekCount += abs(requests[i] - head);
            head = requests[i];
        }
    }

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

    C_LOOK(requests, n, head);

    return 0;
}
