/*
 * terminal.c
 *
 * Implements functions to control terminal settings, specifically for
 * enabling non-canonical mode to read single characters without pressing Enter.
 */

#include <termios.h>
#include <unistd.h>
#include "terminal.h"

static struct termios old_settings, new_settings;

/*
 * Disables character echoing and canonical mode to allow for single-key input.
 */
void disable_echo_and_canonical_mode(void) {
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

/*
 * Restores the original terminal settings.
 */
void enable_echo_and_canonical_mode(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}
