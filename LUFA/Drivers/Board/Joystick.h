/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *
 *  This file is the master dispatch header file for the board-specific Joystick driver, for boards containing a
 *  5-way joystick.
 *
 *  User code should include this file, which will in turn include the correct joystick driver header file for the
 *  currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Joystick.h file in the user project
 *  directory.
 */
 
/** \ingroup Group_BoardDrivers
 *  @defgroup Group_Joystick Joystick Driver - LUFA/Drivers/Board/Joystick.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Module Description
 *  Hardware Joystick driver. This module provides an easy to use interface to control the hardware digital Joystick
 *  located on many boards.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/Dataflash.h file in the user project
 *  directory. Otherwise, it will include the appropriate built in board driver header file.
 *
 *  @{
 */

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_JOYSTICK_H
	#endif

	/* Includes: */
	#include "../../Common/Common.h"
	
	#if !defined(BOARD)
		#error BOARD must be set in makefile to a value specified in BoardTypes.h.
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
	#elif (BOARD == BOARD_USER)
		#include "Board/Joystick.h"
	#else
		#error The selected board does not contain a joystick.
	#endif

	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the joystick driver so that the joystick position can be read. This sets the appropriate
		 *  I/O pins to inputs with their pull-ups enabled.
		 */
		static inline void Joystick_Init(void);

		/** Returns the current status of the joystick, as a mask indicating the direction the joystick is
		 *  currently facing in (multiple bits can be set).
		 *
		 *  \return Mask indicating the joystick direction - see corresponding board specific Joystick.h file
		 *          for direction masks
		 */
		static inline uint8_t Joystick_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	#endif

#endif

/** @} */
