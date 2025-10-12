# Makefile for the escape game

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -ansi -g

# Executable name
EXEC = escape

# Object files
OBJS = escape.o game.o map.o linked_list.o terminal.o undo.o color.o newSleep.o

# Targets
all: $(EXEC)

# Default target. 
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Compilation rules

escape.o: escape.c game.h terminal.h newSleep.h
	$(CC) $(CFLAGS) -c escape.c

game.o: game.c game.h map.h linked_list.h undo.h color.h newSleep.h
	$(CC) $(CFLAGS) -c game.c

map.o: map.c map.h color.h
	$(CC) $(CFLAGS) -c map.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

undo.o: undo.c undo.h game.h map.h linked_list.h
	$(CC) $(CFLAGS) -c undo.c

color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c

newSleep.o: newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

# Housekeeping
clean:
	rm -f $(EXEC) $(OBJS)