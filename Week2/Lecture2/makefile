CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = calculation.o main.o io.o
EXEC = myProgram

$(EXEC)

myProgram: calculation.o main.o io.o
	gcc -o myProgram calculation.o main.o io.o

calculation.o: calculation.c calculation.h
	gcc -Wall -ansi -pedantic calculation.c -c

main.o: main.c calculation.h io.h
	gcc -Wall -ansi -pedantic main.c -c

io.o : io.c io.h
	gcc -Wall -ansi -pedantic io.c -c

clean:
	rm calculation.o main.o io.o myProgram
