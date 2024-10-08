#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t wsem;
sem_t x;
int data, readcount;

void *writer(void *arg)
{
    while (1)
    {
        sem_wait(&wsem);
        printf("Writer %ld entering Critical Section\n", (long)arg);
        data = 10;
        printf("Writer %ld wrote Data: %d\n", (long)arg, data);
        sem_post(&wsem);
        printf("Writer %ld exiting Critical Section\n", (long)arg);
        sleep(3);
    }
    return NULL;
}

void *reader(void *arg)
{
    while (1)
    {
        sem_wait(&x);
        readcount++;
        if (readcount == 1)
        {
            sem_wait(&wsem);
        }
        sem_post(&x);
        printf("Reader %ld entering Critical Section\n", (long)arg);
        printf("Reader %ld read Data: %d\n", (long)arg, data);
        sem_wait(&x);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&wsem);
        }
        sem_post(&x);
        printf("Reader %ld exiting Critical Section\n", (long)arg);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int i;

    sem_init(&wsem, 0, 1);
    sem_init(&x, 0, 1);
    readcount = 0;

    for (i = 0; i < NUM_WRITERS; i++)
    {
        pthread_create(&writers[i], NULL, writer, (void *)(long)i);
    }

    for (i = 0; i < NUM_READERS; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)(long)i);
    }

    // Wait for all threads to finish (they run indefinitely in this example)
    for (i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    for (i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Cleanup semaphores
    sem_destroy(&wsem);
    sem_destroy(&x);

    return 0;
}
