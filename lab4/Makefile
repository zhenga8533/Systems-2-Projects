all: lab4.zip lab4

lab4.zip: Makefile main.c bounded_buffer.c bounded_buffer.h
	zip lab4 Makefile main.c bounded_buffer.c bounded_buffer.h
	
lab4: main.o bounded_buffer.o
	gcc -o lab4 main.o bounded_buffer.o

main.o: main.c bounded_buffer.h
	gcc -c main.c

bounded_buffer.o: bounded_buffer.c bounded_buffer.h
	gcc -c bounded_buffer.c

clean:
	rm -rf lab4 lab4.zip *.o
