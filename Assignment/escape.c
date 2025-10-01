/*
 * escape.c
 *
 * Main entry point for the escape game.
 * Handles command-line arguments, initializes the game,
 * and runs the main game loop.
 */
#include <stdio.h>
#include "game.h"
#include "terminal.h"
#include "newSleep.h"

int main(int argc, char* argv[]) {
    GameState* game;
    char input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    game = create_game_state(argv[1]);
    if (game == NULL) {
        return 1; /* Error message already printed */
    }

    disableBuffer();

    while (game->game_over == 0) {
        print_game_state(game);
        input = getchar();
        process_input(game, input);
        newSleep(0.01f); /* Small delay for better responsiveness */
    }

    enableBuffer();
    
    /* Final win/loss messages and delays are handled in game.c */
    
    free_game_state(game);

    return 0;
}