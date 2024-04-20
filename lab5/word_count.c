#include <stdio.h>
#include "word_count.h"
#include "hashmap.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int print_result(char *key, int value);

typedef struct {
    int id;
    char** documents;
    int num_docs;
    map_t* word_counts;
    pthread_mutex_t* mutex;
} mapper_thread_t;

typedef struct {
    int id;
    map_t* word_counts;
    pthread_mutex_t* mutex;
} reducer_thread_t;

// Mapper function
void* mapper_thread(void* arg) {
    mapper_thread_t* mapper = (mapper_thread_t*) arg;
    map_t* word_counts = mapper->word_counts;
    pthread_mutex_t* mutex = mapper->mutex;
    const char delimiter[2] = " ";

    for (int i = 0; i < mapper->num_docs; i++) {
        char* document = mapper->documents[i];
        char* token = strtok(document, delimiter);

        while (token != NULL) {
            int count;
            pthread_mutex_lock(mutex);
            printf("Mapping Token: %s\n", token);
            if (hashmap_get(*word_counts, token, &count) == MAP_OK)
                hashmap_put(*word_counts, token, count + 1);
            else
                hashmap_put(*word_counts, token, 1);
            pthread_mutex_unlock(mutex);
            
            token = strtok(NULL, delimiter);
        }
    }

    pthread_exit(NULL);
}

// Reducer function
void* reducer_thread(void* arg) {
    reducer_thread_t* reducer = (reducer_thread_t*) arg;
    map_t* word_counts = reducer->word_counts;
    pthread_mutex_t* mutex = reducer->mutex;
    
    pthread_mutex_lock(mutex);
    printf("Reducer %d: Word counts:\n", reducer->id);
    hashmap_iterate(*word_counts, print_result);
    pthread_mutex_unlock(mutex);

    pthread_exit(NULL);
}

void word_count(int m, int r, char **text) {
    map_t word_counts = hashmap_new();
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t mapper_threads[m];
    mapper_thread_t mapper_args[m];
    int docs_per_mapper = m > 0 ? (int)(ceil((double)r / m)) : 0;

    for (int i = 0; i < m; i++) {
        mapper_args[i].id = i;
        mapper_args[i].documents = &text[i * docs_per_mapper];
        mapper_args[i].num_docs = (i == m) ? r - i * docs_per_mapper : docs_per_mapper;
        mapper_args[i].word_counts = &word_counts;
        mapper_args[i].mutex = &mutex;
        pthread_create(&mapper_threads[i], NULL, mapper_thread, &mapper_args[i]);
    }

    for (int i = 0; i < m; i++) {
        pthread_join(mapper_threads[i], NULL);
    }

    pthread_t reducer_threads[r];
    reducer_thread_t reducer_args[r];

    for (int i = 0; i < r; i++) {
        reducer_args[i].id = i;
        reducer_args[i].word_counts = &word_counts;
        reducer_args[i].mutex = &mutex;
        pthread_create(&reducer_threads[i], NULL, reducer_thread, &reducer_args[i]);
    }

    for (int i = 0; i < r; i++) {
        pthread_join(reducer_threads[i], NULL);
    }

    hashmap_free(word_counts);
}

int print_result(char *key, int value) {
    printf("count of %s = %d\n", key, value);
    return 0;
}
