/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief ANSI terminal special escape code macros.
 *
 *  ANSI terminal compatible escape sequences. These escape sequences are designed to be concatenated with existing
 *  strings to modify their display on a compatible terminal application.
 */

/** \ingroup Group_MiscDrivers
 *  \defgroup Group_Terminal ANSI Terminal Escape Codes - LUFA/Drivers/Misc/TerminalCodes.h
 *  \brief ANSI terminal special escape code macros.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Escape code macros for ANSI compliant text terminals.
 *
 *  \note If desired, the macro \c DISABLE_TERMINAL_CODES can be defined in the project makefile and passed to the GCC
 *        compiler via the -D switch to disable the terminal codes without modifying the source, for use with non
 *        compatible terminals (any terminal codes then equate to empty strings).
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      printf("Normal String, "
 *             ESC_BOLD_ON "Bold String, "
 *             ESC_UNDERLINE_ON "Bold and Underlined String"
 *             ESC_RESET ESC_FG_BLUE ESC_BG_YELLOW "Normal Blue-on-Yellow String");
 *  \endcode
 *
 *  @{
 */

#ifndef __TERMINALCODES_H__
#define __TERMINALCODES_H__

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if !defined(DISABLE_TERMINAL_CODES)
				/** Creates an ANSI escape sequence with the specified payload.
				 *
				 *  \param[in] EscapeSeq  Payload to encode as an ANSI escape sequence, a \c ESC_* mask.
				 */
				#define ANSI_ESCAPE_SEQUENCE(EscapeSeq)  "\33[" EscapeSeq
			#else
				#define ANSI_ESCAPE_SEQUENCE(EscapeSeq)
			#endif

			/** \name Text Display Modifier Control Sequences */
			//@{
			/** Turns on bold so that any following text is printed to the terminal in bold. */
			#define ESC_BOLD_ON                     ANSI_ESCAPE_SEQUENCE("1m")

			/** Turns on italics so that any following text is printed to the terminal in italics. */
			#define ESC_ITALICS_ON                  ANSI_ESCAPE_SEQUENCE("3m")

			/** Turns on underline so that any following text is printed to the terminal underlined. */
			#define ESC_UNDERLINE_ON                ANSI_ESCAPE_SEQUENCE("4m")

			/** Turns on inverse so that any following text is printed to the terminal in inverted colours. */
			#define ESC_INVERSE_ON                  ANSI_ESCAPE_SEQUENCE("7m")

			/** Turns on strike-through so that any following text is printed to the terminal with a line through the
			 *  center.
			 */
			#define ESC_STRIKETHROUGH_ON            ANSI_ESCAPE_SEQUENCE("9m")

			/** Turns off bold so that any following text is printed to the terminal in non bold. */
			#define ESC_BOLD_OFF                    ANSI_ESCAPE_SEQUENCE("22m")

			/** Turns off italics so that any following text is printed to the terminal in non italics. */
			#define ESC_ITALICS_OFF                 ANSI_ESCAPE_SEQUENCE("23m")

			/** Turns off underline so that any following text is printed to the terminal non underlined. */
			#define ESC_UNDERLINE_OFF               ANSI_ESCAPE_SEQUENCE("24m")

			/** Turns off inverse so that any following text is printed to the terminal in non inverted colours. */
			#define ESC_INVERSE_OFF                 ANSI_ESCAPE_SEQUENCE("27m")

			/** Turns off strike-through so that any following text is printed to the terminal without a line through
			 *  the center.
			 */
			#define ESC_STRIKETHROUGH_OFF           ANSI_ESCAPE_SEQUENCE("29m")
			//@}

			/** \name Text Colour Control Sequences */
			//@{
			/** Sets the foreground (text) colour to black. */
			#define ESC_FG_BLACK                    ANSI_ESCAPE_SEQUENCE("30m")

			/** Sets the foreground (text) colour to red. */
			#define ESC_FG_RED                      ANSI_ESCAPE_SEQUENCE("31m")

			/** Sets the foreground (text) colour to green. */
			#define ESC_FG_GREEN                    ANSI_ESCAPE_SEQUENCE("32m")

			/** Sets the foreground (text) colour to yellow. */
			#define ESC_FG_YELLOW                   ANSI_ESCAPE_SEQUENCE("33m")

			/** Sets the foreground (text) colour to blue. */
			#define ESC_FG_BLUE                     ANSI_ESCAPE_SEQUENCE("34m")

			/** Sets the foreground (text) colour to magenta. */
			#define ESC_FG_MAGENTA                  ANSI_ESCAPE_SEQUENCE("35m")

			/** Sets the foreground (text) colour to cyan. */
			#define ESC_FG_CYAN                     ANSI_ESCAPE_SEQUENCE("36m")

			/** Sets the foreground (text) colour to white. */
			#define ESC_FG_WHITE                    ANSI_ESCAPE_SEQUENCE("37m")

			/** Sets the foreground (text) colour to the terminal's default. */
			#define ESC_FG_DEFAULT                  ANSI_ESCAPE_SEQUENCE("39m")

			/** Sets the text background colour to black. */
			#define ESC_BG_BLACK                    ANSI_ESCAPE_SEQUENCE("40m")

			/** Sets the text background colour to red. */
			#define ESC_BG_RED                      ANSI_ESCAPE_SEQUENCE("41m")

			/** Sets the text background colour to green. */
			#define ESC_BG_GREEN                    ANSI_ESCAPE_SEQUENCE("42m")

			/** Sets the text background colour to yellow. */
			#define ESC_BG_YELLOW                   ANSI_ESCAPE_SEQUENCE("43m")

			/** Sets the text background colour to blue. */
			#define ESC_BG_BLUE                     ANSI_ESCAPE_SEQUENCE("44m")

			/** Sets the text background colour to magenta. */
			#define ESC_BG_MAGENTA                  ANSI_ESCAPE_SEQUENCE("45m")

			/** Sets the text background colour to cyan. */
			#define ESC_BG_CYAN                     ANSI_ESCAPE_SEQUENCE("46m")

			/** Sets the text background colour to white. */
			#define ESC_BG_WHITE                    ANSI_ESCAPE_SEQUENCE("47m")

			/** Sets the text background colour to the terminal's default. */
			#define ESC_BG_DEFAULT                  ANSI_ESCAPE_SEQUENCE("49m")
			//@}

			/** \name Cursor Positioning Control Sequences */
			//@{
			/** Saves the current cursor position so that it may be restored with \ref ESC_CURSOR_POS_RESTORE. */
			#define ESC_CURSOR_POS_SAVE             ANSI_ESCAPE_SEQUENCE("s")

			/** Restores the cursor position to the last position saved with \ref ESC_CURSOR_POS_SAVE. */
			#define ESC_CURSOR_POS_RESTORE          ANSI_ESCAPE_SEQUENCE("u")

			/** Sets the cursor position to the given line and column.
			 *
			 *  \param[in] Line    Line number to position the cursor at.
			 *  \param[in] Column  Column number to position the cursor at.
			 */
			#define ESC_CURSOR_POS(Line, Column)    ANSI_ESCAPE_SEQUENCE(#Line ";" #Column "H")

			/** Moves the cursor up the given number of lines.
			 *
			 *  \param[in] Lines  Number of lines to move the cursor position
			 */
			#define ESC_CURSOR_UP(Lines)            ANSI_ESCAPE_SEQUENCE(#Lines "A")

			/** Moves the cursor down the given number of lines.
			 *
			 *  \param[in] Lines  Number of lines to move the cursor position
			 */
			#define ESC_CURSOR_DOWN(Lines)          ANSI_ESCAPE_SEQUENCE(#Lines "B")

			/** Moves the cursor to the right the given number of columns.
			 *
			 *  \param[in] Columns  Number of columns to move the cursor position
			 */
			#define ESC_CURSOR_FORWARD(Columns)     ANSI_ESCAPE_SEQUENCE(#Columns "C")

			/** Moves the cursor to the left the given number of columns.
			 *
			 *  \param[in] Columns  Number of columns to move the cursor position
			 */
			#define ESC_CURSOR_BACKWARD(Columns)    ANSI_ESCAPE_SEQUENCE(#Columns "D")
			//@}

			/** \name Miscellaneous Control Sequences */
			//@{
			/** Resets any escape sequence modifiers back to their defaults. */
			#define ESC_RESET                       ANSI_ESCAPE_SEQUENCE("0m")

			/** Erases the entire display, returning the cursor to the top left. */
			#define ESC_ERASE_DISPLAY               ANSI_ESCAPE_SEQUENCE("2J")

			/** Erases the current line, returning the cursor to the far left. */
			#define ESC_ERASE_LINE                  ANSI_ESCAPE_SEQUENCE("K")
			//@}

#endif

/** @} */

