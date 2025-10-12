/*
 * terminal.c
 *
 * Implements non-canonical mode to read single characters without having to pressing Enter.
 */

#include <termios.h> /* Terminal i/O interface. */
#include <unistd.h> /* For input*/
#include "terminal.h"

/* Static struct to hold the original terminal settings - store copy of terminal's original settings.  */
static struct termios oldsettings;

/*
 * Disables character echoing and canonical mode (buffered input).
 * It saves the original terminal settings before modifying them.
 */
void disableBuffer(void) 
{
    struct termios newsettings; /* new struct to hold modified settings*/
    tcgetattr(STDIN_FILENO, &oldsettings); /* gets current terminal settings and store them */
    newsettings = oldsettings;
    /* Modify flags to disable echo and canonical mode */
    newsettings.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newsettings); /* Apply the new settings immediately */
}

/*
 * Restores the original terminal settings.
 */
void enableBuffer(void)
{
    /* Restore the exact settings that were saved by disableBuffer */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldsettings);
}
