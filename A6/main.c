#include <stdio.h> 
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

void fifo(int pages, int frame, int inputs[]){
    printf("Incoming Frame 1 Frame 2 Frame 3\n");
    int temp[frame];
    int pagefault = 0;
    for (int i = 0; i < frame; i++)
    {
        temp[i] = -1;
    }
    for (int i = 0; i < pages; i++)
    {
        int s = 0;
        for (int j = 0; j < frame; j++)
        {
            if (temp[j] == inputs[i])
            {
                s++;
                pagefault--;
            }
        }
        pagefault++;
        if (pagefault <= frame && s == 0)
        {
            temp[i % frame] = inputs[i];
        }
        else if (s == 0)
        {
            temp[(pagefault - 1) % frame] = inputs[i];
        }
        printf("%d\t", inputs[i]);
        for (int j = 0; j < frame; j++)
        {
            if (temp[j] != -1)
                printf(" %d\t", temp[j]);
            else
                printf(" - \t");
        }
        printf("\n");
    }
    printf("Total Page Faults:\t%d\n", pagefault);
}


int checkHit(int page, int queue[], int occupied){
    for (int i = 0; i < occupied; i++)
    {
        if (queue[i] == page)
        {
            return 1;
        }
    }
    return 0;
}
void printFrame(int queue[], int occupied, int currentPage){
    printf("%d\t", currentPage);
    for (int i = 0; i < occupied; i++)
    {
        if (queue[i] != -1)
            printf(" %d\t", queue[i]);
        else
            printf(" - \t");
    }
    printf("\n");
}
void lru(int pages, int frames, int incomingStream[]){
    int queue[frames];
    int occupied = 0;
    int pagefault = 0;
    int distance[frames];
    printf("\nIncoming Frame 1 Frame 2 Frame 3\n");
    for (int i = 0; i < pages; i++)
    {
        if (checkHit(incomingStream[i], queue, occupied))
        {
            printFrame(queue, occupied, incomingStream[i]);
            continue;
        }
        if (occupied < frames)
        {
            queue[occupied] = incomingStream[i];
            pagefault++;
            occupied++;
            printFrame(queue, occupied, incomingStream[i]);
        }
        else
        {
            int max = INT_MIN;
            int index = 0;
            for (int j = 0; j < frames; j++)
            {

                distance[j] = 0;
                for (int k = i - 1; k >= 0; k--)
                {
                    distance[j]++;
                    if (queue[j] == incomingStream[k])
                        break;
                }
                if (distance[j] > max)
                {
                    max = distance[j];
                    index = j;
                }
            }
            queue[index] = incomingStream[i]; // Replace LRU page pagefault++;
            printFrame(queue, occupied, incomingStream[i]);
        }
    }
    printf("Total Page Faults: %d\n", pagefault);
}
bool search(int key, int fr[], int size){
    for (int i = 0; i < size; i++)
        if (fr[i] == key)
            return true;
    return false;
}
int predict(int pg[], int fr[], int pn, int index, int fn){
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimal(int pg[], int pn, int fn){
    int fr[fn];
    int pagefault = 0;
    int occupied = 0;
    printf("\nIncoming Frame 1 Frame 2 Frame 3\n");
    for (int i = 0; i < pn; i++)
    {
        if (search(pg[i], fr, occupied))
        {
            printFrame(fr, occupied, pg[i]);
            continue;
        }
        if (occupied < fn)
        {
            fr[occupied] = pg[i];
            pagefault++;
            occupied++;
            printFrame(fr, occupied, pg[i]);
        }
        else
        {
            int j = predict(pg, fr, pn, i + 1, fn);
            fr[j] = pg[i];
            pagefault++;
            printFrame(fr, occupied, pg[i]);
        }
    }
    printf("Total Page Faults: %d\n", pagefault);
}
int main(){
    int pages;
    int frames;
    int op;
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
    int arr[pages];
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    for (int i = 0; i < pages; i++)
    {
        printf("Enter the input %d: ", i + 1);

        scanf("%d", &arr[i]);
    }
    do
    {
        printf("\n=================================\n");
        printf("1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        printf("Enter the option: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nFirst In First Out\n");
            fifo(pages, frames, arr);
            break;
        case 2:
            printf("\nLeast Recently Used\n");
            lru(pages, frames, arr);
            break;
        case 3:
            printf("\nOptimal Page Replacement\n");
            optimal(arr, pages, frames);
            break;
        case 4:
            break;
        default:
            printf("Enter a valid option\n");
        }
    } while (op != 4);
    return 0;
}