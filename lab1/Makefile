all: lab1.zip lab1

lab1.zip: Makefile lab1.c
	zip lab1 Makefile lab1.c
	
lab1: lab1.o
	gcc -o lab1 lab1.o

lab1.o: lab1.c
	gcc -c lab1.c

clean:
	rm -rf lab1 lab1.zip
