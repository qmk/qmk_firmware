/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief LED board hardware driver.
 *
 *  This file is the master dispatch header file for the board-specific LED driver, for boards containing user
 *  controllable LEDs.
 *
 *  User code should include this file, which will in turn include the correct LED driver header file for the
 *  currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/LEDs.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_LEDs LEDs Driver - LUFA/Drivers/Board/LEDs.h
 *  \brief LED board hardware driver.
 *
 *  \section Sec_LEDs_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Sec_LEDs_ModDescription Module Description
 *  Hardware LEDs driver. This provides an easy to use driver for the hardware LEDs present on many boards. It
 *  provides an interface to configure, test and change the status of all the board LEDs.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/LEDs.h file in the user project
 *  directory. Otherwise, it will include the appropriate built-in board driver header file. If the BOARD value
 *  is set to \c BOARD_NONE, this driver is silently disabled.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 *
 *  \note To make code as compatible as possible, it is assumed that all boards carry a minimum of four LEDs. If
 *        a board contains less than four LEDs, the remaining LED masks are defined to 0 so as to have no effect.
 *        If other behavior is desired, either alias the remaining LED masks to existing LED masks via the -D
 *        switch in the project makefile, or alias them to nothing in the makefile to cause compilation errors when
 *        a non-existing LED is referenced in application code. Note that this means that it is possible to make
 *        compatible code for a board with no LEDs by making a board LED driver (see \ref Page_WritingBoardDrivers)
 *        which contains only stub functions and defines no LEDs.
 *
 *  \section Sec_LEDs_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the board LED driver before first use
 *      LEDs_Init();
 *
 *      // Turn on each of the four LEDs in turn
 *      LEDs_SetAllLEDs(LEDS_LED1);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED2);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED3);
 *      Delay_MS(500);
 *      LEDs_SetAllLEDs(LEDS_LED4);
 *      Delay_MS(500);
 *
 *      // Turn on all LEDs
 *      LEDs_SetAllLEDs(LEDS_ALL_LEDS);
 *      Delay_MS(1000);
 *
 *      // Turn on LED 1, turn off LED 2, leaving LEDs 3 and 4 in their current state
 *      LEDs_ChangeLEDs((LEDS_LED1 | LEDS_LED2), LEDS_LED1);
 *  \endcode
 *
 *  @{
 */

#ifndef __LEDS_H__
#define __LEDS_H__

	/* Macros: */
		#define __INCLUDE_FROM_LEDS_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_NONE)
			static inline void LEDs_Init(void) {};
			static inline void LEDs_Disable(void) {};
			static inline void LEDs_TurnOnLEDs(const uint_reg_t LEDMask) {};
			static inline void LEDs_TurnOffLEDs(const uint_reg_t LEDMask) {};
			static inline void LEDs_SetAllLEDs(const uint_reg_t LEDMask) {};
			static inline void LEDs_ChangeLEDs(const uint_reg_t LEDMask, const uint_reg_t ActiveMask) {};
			static inline void LEDs_ToggleLEDs(const uint_reg_t LEDMask) {};
			static inline uint_reg_t LEDs_GetLEDs(void) { return 0; }
		#elif (BOARD == BOARD_USBKEY)
			#include "AVR8/USBKEY/LEDs.h"
		#elif (BOARD == BOARD_STK525)
			#include "AVR8/STK525/LEDs.h"
		#elif (BOARD == BOARD_STK526)
			#include "AVR8/STK526/LEDs.h"
		#elif (BOARD == BOARD_RZUSBSTICK)
			#include "AVR8/RZUSBSTICK/LEDs.h"
		#elif (BOARD == BOARD_ATAVRUSBRF01)
			#include "AVR8/ATAVRUSBRF01/LEDs.h"
		#elif ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#include "AVR8/XPLAIN/LEDs.h"
		#elif (BOARD == BOARD_BUMBLEB)
			#include "AVR8/BUMBLEB/LEDs.h"
		#elif (BOARD == BOARD_EVK527)
			#include "AVR8/EVK527/LEDs.h"
		#elif ((BOARD == BOARD_TEENSY) || (BOARD == BOARD_TEENSY2))
			#include "AVR8/TEENSY/LEDs.h"
		#elif (BOARD == BOARD_USBTINYMKII)
			#include "AVR8/USBTINYMKII/LEDs.h"
		#elif (BOARD == BOARD_BENITO)
			#include "AVR8/BENITO/LEDs.h"
		#elif (BOARD == BOARD_JMDBU2)
			#include "AVR8/JMDBU2/LEDs.h"
		#elif (BOARD == BOARD_OLIMEX162)
			#include "AVR8/OLIMEX162/LEDs.h"
		#elif (BOARD == BOARD_USBFOO)
			#include "AVR8/USBFOO/LEDs.h"
		#elif (BOARD == BOARD_UDIP)
			#include "AVR8/UDIP/LEDs.h"
		#elif (BOARD == BOARD_BUI)
			#include "AVR8/BUI/LEDs.h"
		#elif (BOARD == BOARD_UNO)
			#include "AVR8/UNO/LEDs.h"
		#elif (BOARD == BOARD_CULV3)
			#include "AVR8/CULV3/LEDs.h"
		#elif (BOARD == BOARD_BLACKCAT)
			#include "AVR8/BLACKCAT/LEDs.h"
		#elif (BOARD == BOARD_MAXIMUS)
			#include "AVR8/MAXIMUS/LEDs.h"
		#elif (BOARD == BOARD_MINIMUS)
			#include "AVR8/MINIMUS/LEDs.h"
		#elif (BOARD == BOARD_ADAFRUITU4)
			#include "AVR8/ADAFRUITU4/LEDs.h"
		#elif (BOARD == BOARD_MICROSIN162)
			#include "AVR8/MICROSIN162/LEDs.h"
		#elif (BOARD == BOARD_SPARKFUN8U2)
			#include "AVR8/SPARKFUN8U2/LEDs.h"
		#elif (BOARD == BOARD_EVK1101)
			#include "UC3/EVK1101/LEDs.h"
		#elif (BOARD == BOARD_TUL)
			#include "AVR8/TUL/LEDs.h"
		#elif (BOARD == BOARD_EVK1100)
			#include "UC3/EVK1100/LEDs.h"
		#elif (BOARD == BOARD_EVK1104)
			#include "UC3/EVK1104/LEDs.h"
		#elif (BOARD == BOARD_A3BU_XPLAINED)
			#include "XMEGA/A3BU_XPLAINED/LEDs.h"
		#elif ((BOARD == BOARD_USB2AX) || (BOARD == BOARD_USB2AX_V3) || (BOARD == BOARD_USB2AX_V31))
			#include "AVR8/USB2AX/LEDs.h"
		#elif ((BOARD == BOARD_MICROPENDOUS_REV1) || (BOARD == BOARD_MICROPENDOUS_REV2) || \
		       (BOARD == BOARD_MICROPENDOUS_32U2))
			#include "AVR8/MICROPENDOUS/LEDs.h"
		#elif (BOARD == BOARD_B1_XPLAINED)
			#include "XMEGA/B1_XPLAINED/LEDs.h"
		#elif (BOARD == BOARD_MULTIO)
			#include "AVR8/MULTIO/LEDs.h"
		#elif (BOARD == BOARD_BIGMULTIO)
			#include "AVR8/BIGMULTIO/LEDs.h"
		#elif (BOARD == BOARD_DUCE)
			#include "AVR8/DUCE/LEDs.h"
		#elif (BOARD == BOARD_OLIMEX32U4)
			#include "AVR8/OLIMEX32U4/LEDs.h"
		#elif (BOARD == BOARD_OLIMEXT32U4)
			#include "AVR8/OLIMEXT32U4/LEDs.h"
		#elif (BOARD == BOARD_OLIMEXISPMK2)
			#include "AVR8/OLIMEXISPMK2/LEDs.h"
		#elif (BOARD == BOARD_LEONARDO)
			#include "AVR8/LEONARDO/LEDs.h"
		#elif (BOARD == BOARD_UC3A3_XPLAINED)
			#include "UC3/UC3A3_XPLAINED/LEDs.h"
		#elif (BOARD == BOARD_STANGE_ISP)
			#include "AVR8/STANGE_ISP/LEDs.h"
		#elif (BOARD == BOARD_C3_XPLAINED)
			#include "XMEGA/C3_XPLAINED/LEDs.h"
		#elif (BOARD == BOARD_U2S)
			#include "AVR8/U2S/LEDs.h"
		#elif (BOARD == BOARD_YUN)
			#include "AVR8/YUN/LEDs.h"
		#elif (BOARD == BOARD_MICRO)
			#include "AVR8/MICRO/LEDs.h"
		#else
			#include "Board/LEDs.h"
		#endif

	/* Preprocessor Checks: */
		#if !defined(__DOXYGEN__)
			#if !defined(LEDS_NO_LEDS)
				#define LEDS_NO_LEDS   0
			#endif

			#if !defined(LEDS_ALL_LEDS)
				#define LEDS_ALL_LEDS  (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)
			#endif

			#if !defined(LEDS_LED1)
				#define LEDS_LED1      0
			#endif

			#if !defined(LEDS_LED2)
				#define LEDS_LED2      0
			#endif

			#if !defined(LEDS_LED3)
				#define LEDS_LED3      0
			#endif

			#if !defined(LEDS_LED4)
				#define LEDS_LED4      0
			#endif
		#endif

	/* Pseudo-Functions for Doxygen: */
	#if defined(__DOXYGEN__)
		/** Initializes the board LED driver so that the LEDs can be controlled. This sets the appropriate port
		 *  I/O pins as outputs, and sets the LEDs to default to off.
		 *
		 *  This must be called before any LED driver functions are used.
		 */
		static inline void LEDs_Init(void);

		/** Disables the board LED driver, releasing the I/O pins back to their default high-impedance input mode. */
		static inline void LEDs_Disable(void);

		/** Turns on the LEDs specified in the given LED mask.
		 *
		 *  \param[in] LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file).
		 */
		static inline void LEDs_TurnOnLEDs(const uint_reg_t LEDMask);

		/** Turns off the LEDs specified in the given LED mask.
		 *
		 *  \param[in] LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file).
		 */
		static inline void LEDs_TurnOffLEDs(const uint_reg_t LEDMask);

		/** Turns off all LEDs not specified in the given LED mask, and turns on all the LEDs in the given LED
		 *  mask.
		 *
		 *  \param[in] LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file).
		 */
		static inline void LEDs_SetAllLEDs(const uint_reg_t LEDMask);

		/** Turns off all LEDs in the LED mask that are not set in the active mask, and turns on all the LEDs
		 *  specified in both the LED and active masks.
		 *
		 *  \param[in] LEDMask     Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file).
		 *  \param[in] ActiveMask  Mask of whether the LEDs in the LED mask should be turned on or off.
		 */
		static inline void LEDs_ChangeLEDs(const uint_reg_t LEDMask,
		                                   const uint_reg_t ActiveMask);

		/** Toggles all LEDs in the LED mask, leaving all others in their current states.
		 *
		 *  \param[in] LEDMask  Mask of the board LEDs to manipulate (see board-specific LEDs.h driver file).
		 */
		static inline void LEDs_ToggleLEDs(const uint_reg_t LEDMask);

		/** Returns the status of all the board LEDs; set LED masks in the return value indicate that the
		 *  corresponding LED is on.
		 *
		 *  \return Mask of \c LEDS_LED* constants indicating which of the board LEDs are currently turned on.
		 */
		static inline uint_reg_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
	#endif

#endif

/** @} */

