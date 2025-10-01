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

    disable_echo_and_canonical_mode();

    while (game->game_over == 0) {
        print_game_state(game);
        input = getchar();
        process_input(game, input);
    }

    enable_echo_and_canonical_mode();
    print_game_state(game); /* Show final state */

    if (game->game_over == 1) {
        printf("\nYou win!\n");
    } else {
        printf("\nYou lose!\n");
    }
    
    free_game_state(game);

    return 0;
}
