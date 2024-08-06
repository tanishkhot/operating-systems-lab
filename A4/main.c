#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define NUM_THREADS 2 

void *thread_function(void *arg);
char message[] = "Hello World";
char message2[] = "Yo bro";


typedef struct {
    char *message;
} ThreadData;

void twoThreads(){
	int res;
	pthread_t a_thread, b_thread;
	void *thread_result;
	
	res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
	if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish...\n");	
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned %s\n", (char *)thread_result);
	printf("Message is now %s\n", message);	
	
	
	int res2;
	res2 = pthread_create(&b_thread, NULL, thread_function, (void *)message2);
	if (res != 0) {
		perror("Thread-2 creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread-2 to finish...\n");	
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread-2 joined, it returned %s\n", (char *)thread_result);
	printf("Message is now %s\n", message2);	
	
	exit(EXIT_SUCCESS);
}
void *thread_function2(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    printf("Thread received message: %s\n", data->message);
    pthread_exit((void *)data->message);
}

void tenThreads(){
    int res;
    pthread_t threads[NUM_THREADS];
    void *thread_result;
    char *messages = {"Arg1", "Arg2"};
    ThreadData *thread_data[NUM_THREADS];
    
    for (int i = 0; i < 2; i++) {
        thread_data[i].message = messages[i];
        res = pthread_create(&threads[i], NULL, thread_function, messages[i]);
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Waiting for thread-%d to finish...\n", i + 1);
        res = pthread_join(threads[i], &thread_result);
        if (res != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
        printf("Thread-%d joined, it returned %s\n", i + 1, (char *)thread_result);
    }

    exit(EXIT_SUCCESS);
}

int main() {		
	tenThreads();
	return 0;
}


void *thread_function(void *arg) {
	printf("thread_function is running. Argument was %s\n", (char *)arg);
	sleep(3);
	strcpy(message, "Bye!");
	pthread_exit("Thank you for the CPU time");
}
