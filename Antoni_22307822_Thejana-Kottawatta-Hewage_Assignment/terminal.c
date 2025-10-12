#include <termios.h>
#include <unistd.h>
#include "terminal.h"

static struct termios old_settings;

/*
 * Disables character echoing and canonical mode (buffered input).
 * It saves the original terminal settings before modifying them.
 */
void disableBuffer(void)
{
    struct termios new_settings;
    /* Get current terminal settings and save them in our static struct */
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    /* Modify flags to disable echo and canonical mode */
    new_settings.c_lflag &= ~(ECHO | ICANON);
    /* Apply the new settings immediately */
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

/*
 * Restores the original terminal settings.
 */
void enableBuffer(void)
{
    /* Restore the exact settings that were saved by disableBuffer */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}
