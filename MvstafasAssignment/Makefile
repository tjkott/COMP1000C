# Makefile for the escape game (Refactored Version)
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
OBJS = escape.o game.o game_move.o game_trap.o game_water.o game_end.o \
       map.o map_loader.o map_utils.o map_memory.o \
       linked_list.o terminal.o \
       undo.o undo_save.o undo_restore.o \
       color_fg.o color_bg.o newSleep.o

# The default target. Running 'make' will build the executable.
all: $(EXEC)

# Rule to link all the object files into the final executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# --- Rules to compile individual source files into object files ---

escape.o: escape.c game.h terminal.h newSleep.h
	$(CC) $(CFLAGS) -c escape.c

# Game Core
game.o: game.c game.h map.h linked_list.h undo.h color.h newSleep.h
	$(CC) $(CFLAGS) -c game.c

# Game Logic Split
game_move.o: game_move.c game.h map.h
	$(CC) $(CFLAGS) -c game_move.c
game_trap.o: game_trap.c game.h map.h
	$(CC) $(CFLAGS) -c game_trap.c
game_water.o: game_water.c game.h map.h
	$(CC) $(CFLAGS) -c game_water.c
game_end.o: game_end.c game.h color.h newSleep.h
	$(CC) $(CFLAGS) -c game_end.c

# Map Core
map.o: map.c map.h color.h
	$(CC) $(CFLAGS) -c map.c

# Map Logic Split
map_loader.o: map_loader.c map.h
	$(CC) $(CFLAGS) -c map_loader.c
map_utils.o: map_utils.c map.h
	$(CC) $(CFLAGS) -c map_utils.c
map_memory.o: map_memory.c map.h
	$(CC) $(CFLAGS) -c map_memory.c

# Linked List
linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

# Terminal I/O
terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

# Undo Core
undo.o: undo.c undo.h game.h map.h
	$(CC) $(CFLAGS) -c undo.c

# Undo Logic Split
undo_save.o: undo_save.c undo.h game.h map.h
	$(CC) $(CFLAGS) -c undo_save.c
undo_restore.o: undo_restore.c undo.h game.h map.h linked_list.h
	$(CC) $(CFLAGS) -c undo_restore.c

# Color Split
color_fg.o: color_fg.c color.h color_private.h
	$(CC) $(CFLAGS) -c color_fg.c
color_bg.o: color_bg.c color.h color_private.h
	$(CC) $(CFLAGS) -c color_bg.c

# Sleep
newSleep.o: newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

# The 'clean' rule removes the executable and all object files.
clean:
	rm -f $(EXEC) $(OBJS)