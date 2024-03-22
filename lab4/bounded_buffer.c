#include "bounded_buffer.h"
#include <stdio.h>
#include <stdlib.h>

/*Do not use any global variables for implementation*/

void bounded_buffer_init(struct bounded_buffer *buffer, int size) {
	buffer->buffet = (void **) malloc(size * sizeof(void *));
	if ((buffer->buffet) == NULL) {
		perror("bounded_buffer_init memory allocation failed!");
		exit(1);
	}
	
	buffer->size = size;
	buffer->count = 0;
	buffer->head = 0;
	buffer->tail = 0;
	pthread_mutex_init(&(buffer->mutex), NULL);
	pthread_cond_init(&(buffer->full), NULL);
	pthread_cond_init(&(buffer->empty), NULL);
}

void bounded_buffer_push(struct bounded_buffer *buffer, void *item) {
	pthread_mutex_lock(&(buffer->mutex));
	while (buffer->count == buffer->size) {
		pthread_cond_wait(&(buffer->full), &(buffer->mutex));
	}
	
	buffer->buffet[buffer->tail] = item;
	buffer->tail = (buffer->tail + 1) % buffer->size;
	buffer->count++;
	pthread_cond_signal(&(buffer->empty));
	pthread_mutex_unlock(&(buffer->mutex));
}

void* bounded_buffer_pop(struct bounded_buffer *buffer) {
	pthread_mutex_lock(&(buffer->mutex));
	while (buffer->count == 0) {
		pthread_cond_wait(&(buffer->empty), &(buffer->mutex));
	}
	
	buffer->head = (buffer->head + 1) % buffer->size;
	buffer->count--;
	pthread_cond_signal(&(buffer->full));
	pthread_mutex_unlock(&(buffer->mutex));

    return buffer->buffet[buffer->head];
}

void bounded_buffer_destroy(struct bounded_buffer *buffer) {
	pthread_mutex_destroy(&(buffer->mutex));
	pthread_cond_destroy(&(buffer->full));
	pthread_cond_destroy(&(buffer->empty));
}
