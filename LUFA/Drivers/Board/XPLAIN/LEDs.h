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
 *  Board specific LED driver header for the XPLAIN.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  @defgroup Group_LEDs_XPLAIN XPLAIN
 *
 *  Board specific LED driver header for the XPLAIN.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 *
 *  @{
 */
 
#ifndef __LEDS_XPLAIN_H__
#define __LEDS_XPLAIN_H__

	/* Includes: */
		#include <avr/io.h>

		#include "../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1 << 6)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    LEDS_LED1

			/** LED mask for the none of the board LEDs */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				DDRB  |= LEDS_ALL_LEDS;
				PORTB |= LEDS_ALL_LEDS;
			}
			
			static inline void LEDs_TurnOnLEDs(const uintN_t LEDMask)
			{
				PORTB &= ~LEDMask;
			}

			static inline void LEDs_TurnOffLEDs(const uintN_t LEDMask)
			{
				PORTB |= LEDMask;
			}

			static inline void LEDs_SetAllLEDs(const uintN_t LEDMask)
			{
				PORTB = ((PORTB | LEDS_ALL_LEDS) & ~LEDMask);
			}
			
			static inline void LEDs_ChangeLEDs(const uintN_t LEDMask, const uintN_t ActiveMask)
			{
				PORTB = ((PORTB | (LEDMask & LEDS_ALL_LEDS)) & (~ActiveMask & LEDS_ALL_LEDS));
			}
			
			static inline void LEDs_ToggleLEDs(const uintN_t LEDMask)
			{
				PORTD = (PORTB ^ (LEDMask & LEDS_ALL_LEDS));
			}
			
			static inline uintN_t LEDs_GetLEDs(void)
			{
				return (~PORTB & LEDS_ALL_LEDS);
			}
		#endif
		
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
