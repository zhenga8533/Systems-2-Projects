all: lab3.zip createThreads parallel1 parallel2 parallel3

lab3.zip: Makefile lab2.c
	zip Makefile createThreads.c parallel1.c parallel2.c parallel3.c

createThreads: createThreads.o
	gcc -o createThreads createThreads.o
createThreads.o: createThreads.c
	gcc -c createThreads.c
	
parallel1: parallel1.o
	gcc -o parallel1 parallel1.o
parallel1.o: parallel1.c
	gcc -c parallel1.c
	
parallel2: parallel2.o
	gcc -o parallel2 parallel2.o
parallel2.o: parallel2.c
	gcc -c parallel2.c

parallel3: parallel3.o
	gcc -o parallel3 parallel3.o
parallel3.o: parallel3.c
	gcc -c parallel3.c

clean:
	rm -rf parallel1 parallel1.o parallel2 parallel2.o parallel3 parallel3.o lab3.zip
