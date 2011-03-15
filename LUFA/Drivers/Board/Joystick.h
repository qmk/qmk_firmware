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
 *  \brief Digital joystick board hardware driver.
 *
 *  This file is the master dispatch header file for the board-specific Joystick driver, for boards containing a
 *  digital joystick.
 *
 *  User code should include this file, which will in turn include the correct joystick driver header file for the
 *  currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Joystick.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_Joystick Joystick Driver - LUFA/Drivers/Board/Joystick.h
 *  \brief Digital joystick board hardware driver.
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_ModDescription Module Description
 *  Hardware Joystick driver. This module provides an easy to use interface to control the hardware digital Joystick
 *  located on many boards.
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
 *      // Initialise the board Joystick driver before first use
 *      Joystick_Init();
 *
 *      printf("Waiting for joystick movement...\r\n");
 *
 *      // Loop until a the joystick has been moved
 *      uint8_t JoystickMovement;
 *      while (!(JoystickMovement = Joystick_GetStatus())) {};
 *
 *      // Display which direction the joystick was moved in
 *      printf("Joystick moved:\r\n");
 *      
 *      if (JoystickMovement & (JOY_UP | JOY_DOWN))
 *        printf("%s ", (JoystickMovement & JOY_UP) ? "Up" : "Down");
 *
 *      if (JoystickMovement & (JOY_LEFT | JOY_RIGHT))
 *        printf("%s ", (JoystickMovement & JOY_LEFT) ? "Left" : "Right");
 *
 *      if (JoystickMovement & JOY_PRESSED)
 *        printf("Pressed");
 *  \endcode
 *
 *  @{
 */

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

	/* Macros: */
		#define __INCLUDE_FROM_JOYSTICK_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_NONE)
			#error The Board Joystick driver cannot be used if the makefile BOARD option is not set.
		#elif (BOARD == BOARD_USBKEY)
			#include "USBKEY/Joystick.h"
		#elif (BOARD == BOARD_STK525)
			#include "STK525/Joystick.h"
		#elif (BOARD == BOARD_STK526)
			#include "STK526/Joystick.h"
		#elif (BOARD == BOARD_BUMBLEB)
			#include "BUMBLEB/Joystick.h"
		#elif (BOARD == BOARD_EVK527)
			#include "EVK527/Joystick.h"
		#elif (BOARD == BOARD_EVK1101)
			#include "EVK1101/Joystick.h"
		#else
			#include "Board/Joystick.h"
		#endif

		/* Pseudo-Functions for Doxygen: */
		#if defined(__DOXYGEN__)
			/** Initialises the joystick driver so that the joystick position can be read. This sets the appropriate
			 *  I/O pins to inputs with their pull-ups enabled.
			 */
			static inline void Joystick_Init(void);

			/** Returns the current status of the joystick, as a mask indicating the direction the joystick is
			 *  currently facing in (multiple bits can be set).
			 *
			 *  \return Mask indicating the joystick direction - see corresponding board specific Joystick.h file
			 *          for direction masks.
			 */
			static inline uint_reg_t Joystick_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
		#endif

#endif

/** @} */

