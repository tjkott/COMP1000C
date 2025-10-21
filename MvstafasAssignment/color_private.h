/*
 * color_private.h
 * Contains private constants for ANSI escape codes.
 * Used internally by color_fg.c and color_bg.c.
 */

#ifndef COLOR_PRIVATE_H
#define COLOR_PRIVATE_H

/* Base ANSI codes for color groups */
#define ANSI_FOREGROUND_BASE 30
#define ANSI_BACKGROUND_BASE 40
#define ANSI_FOREGROUND_RESET 39
#define ANSI_BACKGROUND_RESET 49

/* Helper macro to easily generate the full ANSI escape sequence. */
#define ANSI_CODE_STRING(code) "\033[" #code "m"

#endif /* COLOR_PRIVATE_H */
