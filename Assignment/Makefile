# Makefile for the escape game, following the lecture's recommended format.
#
# --- Usage ---
# To compile: make
# To clean:   make clean

# --- Variables ---

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall:      Enable all warnings
# -pedantic:  Enforce strict ISO C compliance
# -ansi:      Use the C89 standard
# -g:         Include debugging information
CFLAGS = -Wall -pedantic -ansi -g

# The final executable file name
EXEC = escape

# A list of all object files required to build the executable
OBJS = escape.o game.o map.o linked_list.o terminal.o undo.o

# --- Targets ---

# The 'all' target is the default. It depends on the final executable.
# Running 'make' will invoke this target.
all: $(EXEC)

# Rule for linking all object files (.o) into the final executable.
# This target depends on all the object files listed in $(OBJS).
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# --- Compilation Rules ---

# Rule to compile escape.c into escape.o
# It depends on the source file and all header files it includes.
escape.o: escape.c game.h terminal.h
	$(CC) $(CFLAGS) -c escape.c

# Rule to compile game.c into game.o
game.o: game.c game.h map.h undo.h
	$(CC) $(CFLAGS) -c game.c

# Rule to compile map.c into map.o
map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

# Rule to compile linked_list.c into linked_list.o
linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

# Rule to compile terminal.c into terminal.o
terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

# Rule to compile undo.c into undo.o
undo.o: undo.c undo.h game.h map.h linked_list.h
	$(CC) $(CFLAGS) -c undo.c

# --- Housekeeping ---

# The 'clean' rule removes all compiled files.
# It does not depend on any other files.
clean:
	rm -f $(EXEC) $(OBJS)

