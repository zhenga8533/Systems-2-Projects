#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "word_count.h"
#include "hashmap.h"

int print_result(char*, int);

void word_count(int m, int r, char **text){
    /* Here I am providing a sequential version.
       You need to change it into a map reduce version*/
    const char delimiter[2] = " ";
    char *token;
    map_t mymap;
    int error;
    /* I am using the hashmap implemented by Peter Warden.
       https://github.com/petewarden/c_hashmap */
    mymap = hashmap_new();
    for(int i=0; i<m; i++){
        /*strtok can extract one word from a string.
	  Note it is not thread-safe. Try to find out
	  why and the thread-safe version.*/
	token = strtok(text[i], delimiter);
	while( token != NULL ) {
	    int count;
	    /* If there exists a count for this word,
	       add the count by 1. Otherwise, set count
	       to 1*/
	    error = hashmap_get(mymap, token, &count);
	    if(error==MAP_OK)
		hashmap_put(mymap, token, count+1);
	    else
		hashmap_put(mymap, token, 1);
      	    token = strtok(NULL, delimiter);
   	}
    }
    printf("Result:\n");
    hashmap_iterate(mymap, print_result);	
	
}

int print_result(char *key, int value){
    printf("count of %s = %d\n", key, value);
    return 0;
}


