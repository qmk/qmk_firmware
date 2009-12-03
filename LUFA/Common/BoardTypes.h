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
 *  This file contains constants which can be passed to the compiler (via setting the macro BOARD) in the
 *  user project makefile using the -D option to configure the library board-specific drivers.
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality.
 */

/** \ingroup Group_Common
 *  @defgroup Group_BoardTypes Board Types
 *
 *  Macros for indicating the chosen physical board hardware to the library. These macros should be used when
 *  defining the BOARD token to the chosen hardware via the -D switch in the project makefile.
 *
 *  @{
 */
	
#ifndef __BOARDTYPES_H__
#define __BOARDTYPES_H__

	/* Preprocessor Checks: */
		#if !defined(__COMMON_H__)
			#error Do not include this file directly. Include LUFA/Common/Common.h instead to gain this functionality.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Selects the USBKEY specific board drivers, including Dataflash, Joystick and LED drivers. */
			#define BOARD_USBKEY        0

			/** Selects the STK525 specific board drivers, including Dataflash, Joystick and LED drivers. */
			#define BOARD_STK525        1

			/** Selects the STK526 specific board drivers, including Dataflash, Joystick and LED drivers. */
			#define BOARD_STK526        2

			/** Selects the RZUSBSTICK specific board drivers, including the driver for the boards LEDs. */
			#define BOARD_RZUSBSTICK    3
			
			/** Selects the ATAVRUSBRF01 specific board drivers, including the driver for the board LEDs. */
			#define BOARD_ATAVRUSBRF01  4

			/** Selects the user-defined board drivers, which should be placed in the user project's folder
			 *  under a directory named /Board/. Each board driver should be named identically to the LUFA
			 *  master board driver (i.e., driver in the LUFA/Drivers/Board director) so that the library
			 *  can correctly identify it.
			 */
			#define BOARD_USER          5

			/** Selects the BUMBLEB specific board drivers, using the officially recommended peripheral layout. */
			#define BOARD_BUMBLEB       6
			
			/** Selects the XPLAIN (Revision 2 or newer) specific board drivers, including LED and Dataflash driver. */
			#define BOARD_XPLAIN        7

			/** Selects the XPLAIN (Revision 1) specific board drivers, including LED and Dataflash driver. */
			#define BOARD_XPLAIN_REV1   8
			
#endif

/** @} */
