//Producer Consumer Problem
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

// Buffer and related variables
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores
sem_t empty; // Counts the number of empty slots in the buffer
sem_t full; // Counts the number of full slots in the buffer
sem_t mutex; // Mutex for mutual exclusion on buffer

void print_buffer()
{
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        if (i == in && i == out)
        {
            printf("[%d*] ", buffer[i]); // Mark the current in and out indices
        }
        else if (i == in)
        {
            printf("[%d<] ", buffer[i]); // Mark the current in index
        }
        else if (i == out)
        {
            printf("[%d>] ", buffer[i]); // Mark the current out index
        }
        else
        {
            printf("[%d] ", buffer[i]); // Regular slot
        }
    }
    printf("\n");
}
void* producer(void* arg)
{
    int id = *((int*)arg);
    free(arg); // Free the dynamically allocated memory
    while (1)
    {
        sleep(rand() % 3); // Simulate variable time for producing an item
        int item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Enter critical section
        // Put the item into the buffer
        buffer[in] = item;
        printf("Producer %d produced %d at index %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;
        print_buffer(); // Print buffer state
        sem_post(&mutex); // Exit critical section
        sem_post(&full); // Signal that buffer has new data
    }
    return NULL;
}

void* consumer(void* arg)
{
    int id = *((int*)arg);
    free(arg); // Free the dynamically allocated memory
    while (1)
    {
        sem_wait(&full); // Wait for a full slot
        sem_wait(&mutex); // Enter critical section
        // Take the item from the buffer
        int item = buffer[out];
        printf("Consumer %d consumed %d from index %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;
        print_buffer(); // Print buffer state
        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that buffer has an empty slot
        sleep(rand() % 3); // Simulate variable time for consuming an item
    }
    return NULL;
}

int main()
{
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer is initially empty
    sem_init(&full, 0, 0); // No items to consume initially
    sem_init(&mutex, 0, 1); // Mutex is initially unlocked

    // Initialize buffer with -1 (indicating empty slots)
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        buffer[i] = -1;
    }

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        int* id = malloc(sizeof(int)); // Dynamically allocate memory for the ID
        *id = i; // Assign thread ID
        pthread_create(&producers[i], NULL, producer, id); // Pass the dynamically allocated ID
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        int* id = malloc(sizeof(int)); // Dynamically allocate memory for the ID
        *id = i; // Assign thread ID
        pthread_create(&consumers[i], NULL, consumer, id); // Pass the dynamically allocated ID
    }

    // Wait for threads to finish (they won't in this example)
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}
