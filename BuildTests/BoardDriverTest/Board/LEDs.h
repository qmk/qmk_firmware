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
 *  \brief LUFA Custom Board LED Hardware Driver (Template)
 *
 *  This is a stub driver header file, for implementing custom board
 *  layout hardware with compatible LUFA board specific drivers. If
 *  the library is configured to use the BOARD_USER board mode, this
 *  driver file should be completed and copied into the "/Board/" folder
 *  inside the application's folder.
 *
 *  This stub is for the board-specific component of the LUFA LEDs driver,
 *  for the LEDs (up to four) mounted on most development boards.
*/

#ifndef __LEDS_USER_H__
#define __LEDS_USER_H__

	/* Includes: */
		// TODO: Add any required includes here

/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

		#define BOARD_DUMMY_LEDS_IMPLEMENTATION

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1 << 0)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1 << 1)

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        (1 << 2)

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        (1 << 3)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)

			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{

			}

			static inline void LEDs_Disable(void)
			{

			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{

			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{

			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{

			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
			{

			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{

			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				return 0;
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

