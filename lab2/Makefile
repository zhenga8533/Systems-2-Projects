all: lab2.zip lab2

lab2.zip: Makefile lab2.c
	zip lab2 Makefile lab2.c
	
lab2: lab2.o
	gcc -o lab2 lab2.o

lab2.o: lab2.c
	gcc -c lab2.c

clean:
	rm -rf lab2 lab2.o lab2.zip
