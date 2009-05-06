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
 *  This file is the master dispatch header file for the board-specific Buttons driver, for boards containing
 *  physical pushbuttons connected to the AVR's GPIO pins.
 *
 *  User code should include this file, which will in turn include the correct Button driver header file for the
 *  currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Buttons.h file in the user project
 *  directory.
 */

/** \ingroup Group_BoardDrivers
 *  @defgroup Group_Buttons Buttons Driver - LUFA/Drivers/Board/Buttons.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Module Description
 *  Functions, macros, variables, enums and types related to the control of physical board GPIO buttons.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Dataflash.h file in the user project
 *  directory. Otherwise, it will include the appropriate built in board driver header file.
 *
 *  @{
 */

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_BUTTONS_H
		#define INCLUDE_FROM_BOARD_DRIVER
	#endif

	/* Includes: */
	#include "../../Common/Common.h"
	
	#if !defined(BOARD)
		#error BOARD must be set in makefile to a value specified in BoardTypes.h.
	#elif (BOARD == BOARD_USBKEY)
		#include "USBKEY/BUTTONS.h"
	#elif (BOARD == BOARD_STK525)
		#include "STK525/BUTTONS.h"
	#elif (BOARD == BOARD_STK526)
		#include "STK526/BUTTONS.h"
	#elif (BOARD == BOARD_ATAVRUSBRF01)
		#include "ATAVRUSBRF01/BUTTONS.h"
	#elif (BOARD == BOARD_USER)
		#include "Board/BUTTONS.h"		
	#else
		#error The selected board does not contain any GPIO buttons.
	#endif
	
	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the BUTTONS driver, so that the current button position can be read. This sets the appropriate
		 *  I/O pins to an inputs with pull-ups enabled.
		 *
		 *  This must be called before any Button driver functions are used.
		 */
		static inline void Buttons_Init(void);
		
		/** Returns a mask indicating which board buttons are currently pressed.
		 *
		 *  \return Mask indicating which board buttons are currently pressed
		 */
		static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	#endif

#endif

/** @} */
