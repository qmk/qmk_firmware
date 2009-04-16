/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  ANSI terminal compatible escape sequences. These escape sequences are designed to be concatenated with existing
 *  strings to modify their display on a compatible terminal application.
 *
 *  \note If desired, the macro DISABLE_TERMINAL_CODES can be defined in the project makefile and passed to the GCC
 *        compiler via the -D switch to disable the terminal codes without modifying the source, for use with non
 *        compatible terminals (any terminal code then equate to empty strings).
 *
 *  Example Usage:
 *  \code
 *      printf("Some String, " ESC_BOLD_ON " Some bold string");
 *  \endcode
 */
 
/** \ingroup Group_MiscDrivers
 *  @defgroup Group_Terminal ANSI Terminal Escape Codes - LUFA/Drivers/Misc/TerminalCodes.h
 *
 *  Escape code macros for ANSI compliant text terminals.
 *
 *  @{
 */
 
#ifndef __TERMINALCODES_H__
#define __TERMINALCODES_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if !defined(DISABLE_TERMINAL_CODES)
				/** Creates an ANSII escape sequence with the payload specified by "c". */
				#define ANSI_ESCAPE_SEQUENCE(c)  "\33[" c
			#else
				#define ANSI_ESCAPE_SEQUENCE(c)
			#endif

			/** Resets any escape sequence modifiers back to their defaults. */
			#define ESC_RESET                ANSI_ESCAPE_SEQUENCE("0m")

			/** Turns on bold so that any following text is printed to the terminal in bold. */
			#define ESC_BOLD_ON              ANSI_ESCAPE_SEQUENCE("1m")

			/** Turns on italics so that any following text is printed to the terminal in italics. */
			#define ESC_ITALICS_ON           ANSI_ESCAPE_SEQUENCE("3m")

			/** Turns on underline so that any following text is printed to the terminal underlined. */
			#define ESC_UNDERLINE_ON         ANSI_ESCAPE_SEQUENCE("4m")

			/** Turns on inverse so that any following text is printed to the terminal in inverted colours. */
			#define ESC_INVERSE_ON           ANSI_ESCAPE_SEQUENCE("7m")

			/** Turns on strikethrough so that any following text is printed to the terminal with a line through the
			 *  center.
			 */
			#define ESC_STRIKETHROUGH_ON     ANSI_ESCAPE_SEQUENCE("9m")

			/** Turns off bold so that any following text is printed to the terminal in non bold. */
			#define ESC_BOLD_OFF             ANSI_ESCAPE_SEQUENCE("22m")

			/** Turns off italics so that any following text is printed to the terminal in non italics. */
			#define ESC_ITALICS_OFF          ANSI_ESCAPE_SEQUENCE("23m")
			
			/** Turns off underline so that any following text is printed to the terminal non underlined. */			
			#define ESC_UNDERLINE_OFF        ANSI_ESCAPE_SEQUENCE("24m")

			/** Turns off inverse so that any following text is printed to the terminal in non inverted colours. */
			#define ESC_INVERSE_OFF          ANSI_ESCAPE_SEQUENCE("27m")

			/** Turns off strikethrough so that any following text is printed to the terminal without a line through
			 *  the center.
			 */
			#define ESC_STRIKETHROUGH_OFF    ANSI_ESCAPE_SEQUENCE("29m")

			/** Sets the foreground (text) colour to black. */
			#define ESC_FG_BLACK             ANSI_ESCAPE_SEQUENCE("30m")

			/** Sets the foreground (text) colour to red. */
			#define ESC_FG_RED               ANSI_ESCAPE_SEQUENCE("31m")

			/** Sets the foreground (text) colour to green. */
			#define ESC_FG_GREEN             ANSI_ESCAPE_SEQUENCE("32m")

			/** Sets the foreground (text) colour to yellow. */
			#define ESC_FG_YELLOW            ANSI_ESCAPE_SEQUENCE("33m")

			/** Sets the foreground (text) colour to blue. */
			#define ESC_FG_BLUE              ANSI_ESCAPE_SEQUENCE("34m")

			/** Sets the foreground (text) colour to magenta. */
			#define ESC_FG_MAGENTA           ANSI_ESCAPE_SEQUENCE("35m")

			/** Sets the foreground (text) colour to cyan. */
			#define ESC_FG_CYAN              ANSI_ESCAPE_SEQUENCE("36m")

			/** Sets the foreground (text) colour to white. */
			#define ESC_FG_WHITE             ANSI_ESCAPE_SEQUENCE("37m")

			/** Sets the foreground (text) colour to the terminal's default. */
			#define ESC_FG_DEFAULT           ANSI_ESCAPE_SEQUENCE("39m")

			/** Sets the text background colour to black. */
			#define ESC_BG_BLACK             ANSI_ESCAPE_SEQUENCE("40m")

			/** Sets the text background colour to red. */
			#define ESC_BG_RED               ANSI_ESCAPE_SEQUENCE("41m")

			/** Sets the text background colour to green. */
			#define ESC_BG_GREEN             ANSI_ESCAPE_SEQUENCE("42m")

			/** Sets the text background colour to yellow. */
			#define ESC_BG_YELLOW            ANSI_ESCAPE_SEQUENCE("43m")

			/** Sets the text background colour to blue. */
			#define ESC_BG_BLUE              ANSI_ESCAPE_SEQUENCE("44m")

			/** Sets the text background colour to magenta. */
			#define ESC_BG_MAGENTA           ANSI_ESCAPE_SEQUENCE("45m")

			/** Sets the text background colour to cyan. */
			#define ESC_BG_CYAN              ANSI_ESCAPE_SEQUENCE("46m")

			/** Sets the text background colour to white. */
			#define ESC_BG_WHITE             ANSI_ESCAPE_SEQUENCE("47m")

			/** Sets the text background colour to the terminal's default. */
			#define ESC_BG_DEFAULT           ANSI_ESCAPE_SEQUENCE("49m")
			
			/** Sets the cursor position to the given line and column. */
			#define ESC_CURSOR_POS(L, C)     ANSI_ESCAPE_SEQUENCE(#L ";" #C "H")

			/** Moves the cursor up the given number of lines. */
			#define ESC_CURSOR_UP(L)         ANSI_ESCAPE_SEQUENCE(#L "A")

			/** Moves the cursor down the given number of lines. */
			#define ESC_CURSOR_DOWN(L)       ANSI_ESCAPE_SEQUENCE(#L "B")

			/** Moves the cursor to the right the given number of columns. */
			#define ESC_CURSOR_FORWARD(C)    ANSI_ESCAPE_SEQUENCE(#C "C")

			/** Moves the cursor to the left the given number of columns. */
			#define ESC_CURSOR_BACKWARD(C)   ANSI_ESCAPE_SEQUENCE(#C "D")

			/** Saves the current cursor position so that it may be restored with ESC_CURSOR_POS_RESTORE. */
			#define ESC_CURSOR_POS_SAVE      ANSI_ESCAPE_SEQUENCE("s")

			/** Restores the cursor position to the last position saved with ESC_CURSOR_POS_SAVE. */
			#define ESC_CURSOR_POS_RESTORE   ANSI_ESCAPE_SEQUENCE("u")
			
			/** Erases the entire display, returning the cursor to the top left. */
			#define ESC_ERASE_DISPLAY        ANSI_ESCAPE_SEQUENCE("2J")

			/** Erases the current line, returning the cursor to the far left. */
			#define ESC_ERASE_LINE           ANSI_ESCAPE_SEQUENCE("K")

#endif

/** @} */
