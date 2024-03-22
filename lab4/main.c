#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct bounded_buffer queue;

void *producer(void *ptr);
void *consumer(void *ptr);

int main() {
    /* initialize the queue */
    bounded_buffer_init(&queue, 5);

    /* create producer threads */
    pthread_t producers[3];
    for (int i = 0; i < 3; i++) {
    	pthread_create(&producers[i], NULL, producer, NULL);
    }
    
    /* create consumer threads */
    pthread_t consumers[2];
    for (int i = 0; i < 2; i++) {
    	pthread_create(&consumers[i], NULL, consumer, NULL);
    }
    
    /* prevent thread genocide, replace in lab 5 :) */
	sleep(5);
	bounded_buffer_destroy(&queue);
	
    return 0;
}

/* this is the function executed by the producer thread. 
   It should generate a number of messages and push them into the queue */
void *producer(void *ptr) {
	for (int i = 0; i < 10; i++) {
		int *message = (int *) malloc(sizeof(int));
		if (message == NULL) {
			perror("producer memory allocation failed!");
			exit(1);
		}
		
		*message = i;
		bounded_buffer_push(&queue, message);
		printf("Producer %lu produced message: %d\n", pthread_self(), *message);
	}

	pthread_exit(NULL);
}

/* this is the function executed by the consumer thread. 
   It should pop messages from the queue and print them */
void *consumer(void *ptr) {
	while (1) {
		int *message = (int *) bounded_buffer_pop(ptr);
		printf("Consumer %lu consumed message: %d\n", pthread_self(), *message);
		free(message);
	}

	pthread_exit(NULL);
}
