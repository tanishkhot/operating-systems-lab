#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
int *buffer; // Dynamic buffer
int buffer_size;
int in = 0, out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
void print_buffer()
{
    printf("Buffer: [ ");
    for (int i = 0; i < buffer_size; i++)
    {
        if (i == in && i == out)
        {
            printf("I&O ");
        }
        else if (i == in)
        {
            printf("I ");
        }
        else if (i == out)
        {
            printf("O ");
        }
        else if (i < in && i >= out)
        {
            printf("%d ", buffer[i]);
        }
        else if (in < out && (i >= out || i < in))
        {
            printf("%d ", buffer[i]);
        }
        else
        {
            printf("E ");
        }
    }
    printf("]\n");
}
void *producer(void *arg)
{
    int item_count = *((int *)arg);
    int item;
    for (int i = 0; i < item_count; i++)
    {
        item = rand() % 100;        // Produce a random item
        sem_wait(&empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % buffer_size;
        printf("Producer produced: %d\n", item);
        print_buffer();
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);              // Signal that there is a full slot
        sleep(1);                     // Simulate time taken to produce an item
    }
    pthread_exit(NULL);
}
void *consumer(void *arg)
{
    int item_count = *((int *)arg);
    int item;
    for (int i = 0; i < item_count; i++)
    {
        sem_wait(&full);            // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        // Remove item from the buffer
        item = buffer[out];
        buffer[out] = 0; // Optional: Clear the consumed slot
        out = (out + 1) % buffer_size;
        printf("Consumer consumed: %d\n", item);
        print_buffer();
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty);             // Signal that there is an empty slot
        sleep(1);                     // Simulate time taken to consume an item
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t prod_thread, cons_thread;
    int produce_count, consume_count;
    // Get user input for buffer size, produce count, and consume count
    printf("Enter the buffer size: ");
    scanf("%d", &buffer_size);
    printf("Enter the number of items to produce: ");
    scanf("%d", &produce_count);
    printf("Enter the number of items to consume: ");
    scanf("%d", &consume_count);
    // Allocate buffer dynamically
    buffer = (int *)malloc(buffer_size * sizeof(int));
    // Initialize the buffer with empty slots
    for (int i = 0; i < buffer_size; i++)
    {
        buffer[i] = 0;
    }
    // Initialize the semaphores and mutex
    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, &produce_count);
    pthread_create(&cons_thread, NULL, consumer, &consume_count);
    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    // Free the dynamically allocated buffer
    free(buffer);
    return 0;
}