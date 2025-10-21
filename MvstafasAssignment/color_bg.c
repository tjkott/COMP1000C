/*
 * color_bg.c
 * Implements the setBackground function using standard ANSI escape codes.
 * This function changes the color of the cell/background printed *after* it's called.
 */

#include <stdio.h>
#include <string.h>
#include "color.h"
#include "color_private.h"

/**
 * @brief Sets the terminal's background color.
 * * It writes the appropriate ANSI escape sequence to stdout.
 *
 * @param color A string representing the desired color (e.g., "blue", "reset").
 */
void setBackground(char * color)
{
    /* Map color names to their respective ANSI codes */
    if(strcmp(color, "black") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 0));
    }
    else if(strcmp(color, "red") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 1));
    }
    else if(strcmp(color, "green") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 2));
    }
    else if(strcmp(color, "yellow") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 3));
    }
    else if(strcmp(color, "blue") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 4));
    }
    else if(strcmp(color, "magenta") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 5));
    }
    else if(strcmp(color, "cyan") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 6));
    }
    else if(strcmp(color, "white") == 0)
    {
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_BASE + 7));
    }
    else if(strcmp(color, "reset") == 0)
    {
        /* Reset background to default terminal color */
        printf(ANSI_CODE_STRING(ANSI_BACKGROUND_RESET));
    }
}

