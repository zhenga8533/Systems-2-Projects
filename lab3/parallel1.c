#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10

int sum = 0;
int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];

void *threadSum(void *arg) {
	int *id = (int *) arg;
	int start = *id * (ARRAY_SIZE / THREAD_NO);
	int end = start + (ARRAY_SIZE / THREAD_NO);
	
	for (int i = start; i < end; i++) {
		sum += num[*id][i - start];
	}
	
	free(id);
}

int main() {
    srand(100);
    
    // initialize arrays
    for(int i=0; i< THREAD_NO; i++) {
		for(int j=0; j< ARRAY_SIZE/THREAD_NO; j++) {
			num[i][j] = rand() % 100;
		}
    }
    
    // initialize threads
    pthread_t p[THREAD_NO];
    
    for (int i = 0; i < THREAD_NO; i++) {
    	int *id = (int *) malloc(sizeof(int));
    	*id = i;
    	pthread_create(&p[i], NULL, threadSum, id);
    }
    
    for (int i = 0; i < THREAD_NO; i++) {
    	pthread_join(p[i], NULL);
    }

    printf("sum = %d\n", sum);
    return 0;
}
