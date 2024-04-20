all: lab5.zip lab5

lab5.zip: Makefile main.c word_count.c word_count.h bounded_buffer.c bounded_buffer.h hashmap.c hashmap.h
	zip lab5 Makefile main.c word_count.c word_count.h bounded_buffer.c bounded_buffer.h hashmap.c hashmap.h
	
lab5: main.o word_count.o bounded_buffer.o hashmap.o
	gcc -std=c99 -o lab5 main.o word_count.o bounded_buffer.o hashmap.o -lpthread -lm

main.o: main.c word_count.h
	gcc -std=c99 -c main.c

word_count.o: word_count.c word_count.h hashmap.h
	gcc -std=c99 -c word_count.c

bounded_buffer.o: bounded_buffer.c bounded_buffer.h
	gcc -std=c99 -c bounded_buffer.c

hashmap.o: hashmap.c hashmap.h
	gcc -std=c99 -c hashmap.c

clean:
	rm -rf lab5 lab5.zip *.o

