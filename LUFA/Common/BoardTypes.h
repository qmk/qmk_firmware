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
 *  \brief Supported pre-made board hardware defines.
 *
 *  \copydetails Group_BoardTypes
 *
 *  \note Do not include this file directly, rather include the Common.h header file instead to gain this file's
 *        functionality.
 */

/** \ingroup Group_Common
 *  \defgroup Group_BoardTypes Board Types
 *  \brief Supported pre-made board hardware defines.
 *
 *  Board macros for indicating the chosen physical board hardware to the library. These macros should be used when
 *  defining the \c BOARD token to the chosen hardware via the \c -D switch in the project makefile. If a custom
 *  board is used, the \ref BOARD_NONE or \ref BOARD_USER values should be selected.
 *
 *  @{
 */

#ifndef __LUFA_BOARDTYPES_H__
#define __LUFA_BOARDTYPES_H__

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_COMMON_H)
			#error Do not include this file directly. Include LUFA/Common/Common.h instead to gain this functionality.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Selects the USBKEY specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_USBKEY        0

			/** Selects the STK525 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_STK525        1

			/** Selects the STK526 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_STK526        2

			/** Selects the RZUSBSTICK specific board drivers, including the driver for the boards LEDs. */
			#define BOARD_RZUSBSTICK    3

			/** Selects the ATAVRUSBRF01 specific board drivers, including the driver for the board LEDs. */
			#define BOARD_ATAVRUSBRF01  4

			/** Selects the user-defined board drivers, which should be placed in the user project's folder
			 *  under a directory named \c /Board/. Each board driver should be named identically to the LUFA
			 *  master board driver (i.e., driver in the \c LUFA/Drivers/Board directory) so that the library
			 *  can correctly identify it.
			 */
			#define BOARD_USER          5

			/** Selects the BUMBLEB specific board drivers, using the officially recommended peripheral layout. */
			#define BOARD_BUMBLEB       6

			/** Selects the XPLAIN (Revision 2 or newer) specific board drivers, including LED and Dataflash driver. */
			#define BOARD_XPLAIN        7

			/** Selects the XPLAIN (Revision 1) specific board drivers, including LED and Dataflash driver. */
			#define BOARD_XPLAIN_REV1   8

			/** Selects the EVK527 specific board drivers, including Temperature, Button, Dataflash, Joystick and LED drivers. */
			#define BOARD_EVK527        9

			/** Disables board drivers when operation will not be adversely affected (e.g. LEDs) - use of board drivers
			 *  such as the Joystick driver, where the removal would adversely affect the code's operation is still disallowed. */
			#define BOARD_NONE          10

			/** Selects the Teensy (all versions) specific board drivers, including the driver for the board LEDs. */
			#define BOARD_TEENSY        11

			/** Selects the USBTINY MKII specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USBTINYMKII   12

			/** Selects the Benito specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_BENITO        13

			/** Selects the JM-DB-U2 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_JMDBU2        14

			/** Selects the Olimex AVR-USB-162 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_OLIMEX162     15

			/** Selects the UDIP specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_UDIP          16

			/** Selects the BUI specific board drivers, including the driver for the board LEDs. */
			#define BOARD_BUI           17

			/** Selects the Arduino Uno specific board drivers, including the driver for the board LEDs. */
			#define BOARD_UNO           18

			/** Selects the CUL V3 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_CULV3         19

			/** Selects the Blackcat USB JTAG specific board drivers, including the driver for the board LEDs. */
			#define BOARD_BLACKCAT      20

			/** Selects the Maximus specific board drivers, including the driver for the board LEDs. */
			#define BOARD_MAXIMUS       21

			/** Selects the Minimus specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_MINIMUS       22

			/** Selects the Adafruit U4 specific board drivers, including the Button driver. */
			#define BOARD_ADAFRUITU4    23

			/** Selects the Microsin AVR-USB162 specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_MICROSIN162   24

			/** Selects the Kernel Concepts USBFOO specific board drivers, including the Button and LEDs drivers. */
			#define BOARD_USBFOO        25
			
			/** Selects the Sparkfun ATMEGA8U2 specific board drivers, including the driver for the board LEDs. */
			#define BOARD_SPARKFUN8U2   26

			/** Selects the Atmel EVK1101 specific board drivers, including the Button, Joystick and LED drivers. */
			#define BOARD_EVK1101       27
			
			#if !defined(__DOXYGEN__)
				#define BOARD_          BOARD_NONE

				#if !defined(BOARD)
					#define BOARD       BOARD_NONE
				#endif
			#endif

#endif

/** @} */

