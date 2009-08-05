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

/*
   This is a stub driver header file, for implementing custom board
   layout hardware with compatible LUFA board specific drivers. If
   the library is configured to use the BOARD_USER board mode, this
   driver file should be completed and copied into the "/Board/" folder
   inside the application's folder.

   This stub is for the board-specific component of the LUFA LEDs driver,
   for the LEDs (up to four) mounted on most USB AVR boards.
*/

#ifndef __LEDS_USER_H__
#define __LEDS_USER_H__

	/* Includes: */
		#include <avr/io.h>

		// TODO: Add any required includes here

/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        // TODO: Add mask for first board LED here

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        // TODO: Add mask for second board LED here

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        // TODO: Add mask for third board LED here

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        // TODO: Add mask for fourth board LED here

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)

			/** LED mask for the none of the board LEDs */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				// TODO: Add code to initialize LED port pins as outputs here
			}
			
			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				// TODO: Add code to turn on LEDs given in the LEDMask mask here, leave others as-is
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				// TODO: Add code to turn off LEDs given in the LEDMask mask here, leave others as-is
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				// TODO: Add code to turn on only LEDs given in the LEDMask mask here, all others off
			}
			
			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
			{
				// TODO: Add code to set the Leds in the given LEDMask to the status given in ActiveMask here
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				// TODO: Add code to toggle the Leds in the given LEDMask, ignoring all others
			}
			
			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				// TODO: Add code to return the current LEDs status' here which can be masked against LED_LED* macros
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif
