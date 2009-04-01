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
 *  This file is the master dispatch header file for the board-specific HWB driver, for boards containing a
 *  physical pushbutton connected to the AVR's HWB IO pin.
 *
 *  User code should include this file, which will in turn include the correct HWB driver header file for the
 *  currently selected board.
 *
 *  If the BOARD value is set to BOARD_USER, this will include the /Board/HWB.h file in the user project
 *  directory.
 */
 
#ifndef __HWB_H__
#define __HWB_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_HWB_H
		#define INCLUDE_FROM_BOARD_DRIVER
	#endif

	/* Includes: */
	#include "../../Common/Common.h"
	
	#if !defined(BOARD)
		#error BOARD must be set in makefile to a value specified in BoardTypes.h.
	#elif (BOARD == BOARD_USBKEY)
		#include "USBKEY/HWB.h"
	#elif (BOARD == BOARD_STK525)
		#include "STK525/HWB.h"
	#elif (BOARD == BOARD_STK526)
		#include "STK526/HWB.h"
	#elif (BOARD == BOARD_ATAVRUSBRF01)
		#include "ATAVRUSBRF01/HWB.h"
	#elif (BOARD == BOARD_USER)
		#include "Board/HWB.h"		
	#else
		#error The selected board does not contain a HWB.
	#endif
	
	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the HWB driver, so that the current button position can be read. This sets the appropriate
		 *  I/O pin to an input with pull-up enabled.
		 *
		 *  This must be called before any HWB functions are used.
		 */
		static inline void HWB_Init(void);
		
		/** Returns the current position of the HWB button on the board.
		 *
		 *  \return Boolean true if the button is currently pressed, false otherwise
		 */
		static inline bool HWB_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
	#endif

#endif
