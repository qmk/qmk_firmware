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
 *  This file is the master dispatch header file for the board-specific LED driver, for boards containing user
 *  controllable LEDs.
 *
 *  User code should include this file, which will in turn include the correct LED driver header file for the
 *  currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/LEDs.h file in the user project
 *  directory.
 */
 
#ifndef __LEDS_H__
#define __LEDS_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_LEDS_H
		#define INCLUDE_FROM_BOARD_DRIVER
	#endif
	
	/* Includes: */
	#include "../../Common/Common.h"

	#if !defined(BOARD)
		#error BOARD must be set in makefile to a value specified in BoardTypes.h.
	#elif (BOARD == BOARD_USBKEY)
		#include "USBKEY/LEDs.h"
	#elif (BOARD == BOARD_STK525)
		#include "STK525/LEDs.h"
	#elif (BOARD == BOARD_STK526)
		#include "STK526/LEDs.h"
	#elif (BOARD == BOARD_RZUSBSTICK)
		#include "RZUSBSTICK/LEDs.h"
	#elif (BOARD == BOARD_ATAVRUSBRF01)
		#include "ATAVRUSBRF01/LEDs.h"
	#elif (BOARD == BOARD_USER)
		#include "Board/LEDs.h"
	#endif
	
	/* Psudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the board LED driver so that the LEDs can be controlled. This sets the appropriate port
		 *  I/O pins as outputs, and sets the LEDs to default to off.
		 */
		static inline void LEDs_Init(void);

		/** Turns on the LEDs specified in the given LED mask.
		 *
		 *  \param LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file)
		 */
		static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask);

		/** Turns off the LEDs specified in the given LED mask.
		 *
		 *  \param LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file)
		 */
		static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask);

		/** Turns off all LEDs not specified in the given LED mask, and turns on all the LEDs in the given LED
		 *  mask.
		 *
		 *  \param LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file)
		 */
		static inline void LEDs_SetAllLEDs(const uint8_t LEDMask);

		/** Turns off all LEDs in the LED mask that are not set in the active mask, and turns on all the LEDs
		 *  specified in both the LED and active masks.
		 *
		 *  \param LEDMask     Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file)
		 *  \param ActiveMask  Mask of whether the LEDs in the LED mask should be turned on or off
		 */
		static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask);

		/** Returns the status of all the board LEDs; set LED masks in the return value indicate that the
		 *  corresponding LED is on.
		 *
		 *  \return Mask of the board LEDs which are currently turned on
		 */
		static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
	#endif

#endif
