/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
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
 *  \brief Digital button board hardware driver.
 *
 *  This file is the master dispatch header file for the board-specific Buttons driver, for boards containing
 *  physical pushbuttons connected to the microcontroller's GPIO pins.
 *
 *  User code should include this file, which will in turn include the correct Button driver header file for the
 *  currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Buttons.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_Buttons Buttons Driver - LUFA/Drivers/Board/Buttons.h
 *  \brief Digital button board hardware driver.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Hardware buttons driver. This provides an easy to use driver for the hardware buttons present on many boards.
 *  It provides a way to easily configure and check the status of all the buttons on the board so that appropriate
 *  actions can be taken.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Dataflash.h file in the user project
 *  directory. Otherwise, it will include the appropriate built in board driver header file.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialise the button driver before first use
 *      Buttons_Init();
 *
 *      printf("Waiting for button press...\r\n");
 *
 *      // Loop until a board button has been pressed
 *      uint8_t ButtonPress;
 *      while (!(ButtonPress = Buttons_GetStatus())) {};
 *
 *      // Display which button was pressed (assuming two board buttons)
 *      printf("Button pressed: %s\r\n", (ButtonPress == BUTTONS_BUTTON1) ? "Button 1" : "Button 2");
 *  \endcode
 * 
 *  @{
 */

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

	/* Macros: */
		#define __INCLUDE_FROM_BUTTONS_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_NONE)
			#error The Board Buttons driver cannot be used if the makefile BOARD option is not set.
		#elif (BOARD == BOARD_USBKEY)
			#include "USBKEY/Buttons.h"
		#elif (BOARD == BOARD_STK525)
			#include "STK525/Buttons.h"
		#elif (BOARD == BOARD_STK526)
			#include "STK526/Buttons.h"
		#elif (BOARD == BOARD_ATAVRUSBRF01)
			#include "ATAVRUSBRF01/Buttons.h"
		#elif (BOARD == BOARD_BUMBLEB)
			#include "BUMBLEB/Buttons.h"
		#elif (BOARD == BOARD_EVK527)
			#include "EVK527/Buttons.h"
		#elif (BOARD == BOARD_USBTINYMKII)
			#include "USBTINYMKII/Buttons.h"
		#elif (BOARD == BOARD_BENITO)
			#include "BENITO/Buttons.h"
		#elif (BOARD == BOARD_JMDBU2)
			#include "JMDBU2/Buttons.h"
		#elif (BOARD == BOARD_OLIMEX162)
			#include "OLIMEX162/Buttons.h"
		#elif (BOARD == BOARD_USBFOO)
			#include "USBFOO/Buttons.h"
		#elif (BOARD == BOARD_UDIP)
			#include "UDIP/Buttons.h"
		#elif (BOARD == BOARD_CULV3)
			#include "CULV3/Buttons.h"
		#elif (BOARD == BOARD_MINIMUS)
			#include "MINIMUS/Buttons.h"
		#elif (BOARD == BOARD_MICROSIN162)
			#include "MICROSIN162/Buttons.h"
		#elif (BOARD == BOARD_EVK1101)
			#include "EVK1101/Buttons.h"
		#else
			#include "Board/Buttons.h"
		#endif

		/* Pseudo-Functions for Doxygen: */
		#if defined(__DOXYGEN__)
			/** Initialises the BUTTONS driver, so that the current button position can be read. This sets the appropriate
			 *  I/O pins to an inputs with pull-ups enabled.
			 *
			 *  This must be called before any Button driver functions are used.
			 */
			static inline void Buttons_Init(void);

			/** Returns a mask indicating which board buttons are currently pressed.
			 *
			 *  \return Mask indicating which board buttons are currently pressed.
			 */
			static inline uint_reg_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
		#endif

#endif

/** @} */

