#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 10

sem_t mutex;
sem_t full;
sem_t empty;

void* consumer(void* arg){
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
            //operations
            printf("Consumed an item \n");
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    return NULL;
}


void* producer(void* arg){
    while(1){
        sem_wait(&empty);
        sem_wait(&mutex);
            //operations;
            printf("Produced an item \n");
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    };
}


int main(){
    pthread_t prod, cons;

    if(sem_init(&mutex, 0 , 1) != 0){
        perror("sem_init");
        return 1;
    }
    if(sem_init(&full, 0 , 0) != 0){
        perror("sem_init");
        return 1;
    }
    
    if(sem_init(&empty, 0 , BUFFER_SIZE) != 0){
        perror("sem_init");
        return 1;
    }


    if (pthread_create(&prod, NULL, producer, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    if(pthread_create(&cons, NULL, consumer, NULL) != 0){
        perror("pthread_create");
        return 1;
    }

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
