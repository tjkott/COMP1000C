/*
 * game_trap.c
 *
 * Implements the logic for triggering the water trap.
 */
#include "game.h"

/**
 * @brief Activates the game's water trap mechanism.
 * * Sets the trap_triggered flag and removes the trap elements from the map.
 * This is a private helper function originally, now a standalone module function.
 * * @param game A pointer to the current GameState.
 */
void triggerTrap(GameState* game) {
    /* Set the flag so water starts spreading on subsequent moves */
    game->trap_triggered = 1;
    
    /* Remove the trap trigger '@' from the map */
    replace_char(game->map, '@', ' ');
    
    /* Remove the 'X' blockers that were holding the water */
    replace_char(game->map, 'X', ' ');
}
