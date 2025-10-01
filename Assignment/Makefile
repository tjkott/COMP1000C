# Makefile for the escape game
#
# --- Usage ---
# To compile the entire program, simply run the command: make
# To remove all generated files, run: make clean

# Compiler and flags
CC = gcc
CFLAGS = -Wall -pedantic -ansi -g

# Executable name
EXEC = escape

# A list of all object files needed for the final executable
OBJS = escape.o game.o map.o linked_list.o terminal.o undo.o color.o newSleep.o

# The default target. Running 'make' will build the executable.
all: $(EXEC)

# Rule to link all the object files into the final executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# --- Rules to compile individual source files into object files ---

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

# The 'clean' rule removes the executable and all object files.
clean:
	rm -f $(EXEC) $(OBJS)