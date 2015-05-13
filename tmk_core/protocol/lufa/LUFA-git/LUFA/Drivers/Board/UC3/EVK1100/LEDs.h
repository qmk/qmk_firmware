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
 *  \brief Board specific LED driver header for the Atmel EVK1100.
 *  \copydetails Group_LEDs_EVK1100
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_EVK1100 EVK1100
 *  \brief Board specific LED driver header for the Atmel EVK1100.
 *
 *  Board specific LED driver header for the Atmel EVK1100.
 *
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>LED0 LED</td><td>Low</td><td>GPIO51</td></tr>
 *    <tr><td>LEDS_LED2</td><td>Green</td><td>LED1 LED</td><td>Low</td><td>GPIO52</td></tr>
 *    <tr><td>LEDS_LED3</td><td>Green</td><td>LED2 LED</td><td>Low</td><td>GPIO53</td></tr>
 *    <tr><td>LEDS_LED4</td><td>Green</td><td>LED3 LED</td><td>Low</td><td>GPIO54</td></tr>
 *    <tr><td>LEDS_LED5</td><td>Green</td><td>LED4 LED</td><td>Low</td><td>GPIO59</td></tr>
 *    <tr><td>LEDS_LED6</td><td>Green</td><td>LED5 LED</td><td>Low</td><td>GPIO60</td></tr>
 *    <tr><td>LEDS_LED7</td><td>Green</td><td>LED6 LED</td><td>Low</td><td>GPIO61</td></tr>
 *    <tr><td>LEDS_LED8</td><td>Green</td><td>LED7 LED</td><td>Low</td><td>GPIO62</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_EVK1100_H__
#define __LEDS_EVK1100_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define LEDS_PORT        1
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1UL << 19)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1UL << 20)

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        (1UL << 21)

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        (1UL << 22)

			/** LED mask for the fifth LED on the board. */
			#define LEDS_LED5        (1UL << 27)

			/** LED mask for the sixth LED on the board. */
			#define LEDS_LED6        (1UL << 28)

			/** LED mask for the seventh LED on the board. */
			#define LEDS_LED7        (1UL << 29)

			/** LED mask for the eighth LED on the board. */
			#define LEDS_LED8        (1UL << 30)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4 \
			                          LEDS_LED5 | LEDS_LED6 | LEDS_LED7 | LEDS_LED8)

			/** LED mask for the none of the board LEDs */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				AVR32_GPIO.port[LEDS_PORT].gpers = LEDS_ALL_LEDS;
				AVR32_GPIO.port[LEDS_PORT].oders = LEDS_ALL_LEDS;
				AVR32_GPIO.port[LEDS_PORT].ovrs  = LEDS_ALL_LEDS;
			}

			static inline void LEDs_Disable(void)
			{
				AVR32_GPIO.port[LEDS_PORT].gperc = LEDS_ALL_LEDS;
				AVR32_GPIO.port[LEDS_PORT].oderc = LEDS_ALL_LEDS;
				AVR32_GPIO.port[LEDS_PORT].ovrc  = LEDS_ALL_LEDS;
			}

			static inline void LEDs_TurnOnLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[LEDS_PORT].ovrc  = LEDMask;
			}

			static inline void LEDs_TurnOffLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[LEDS_PORT].ovrs  = LEDMask;
			}

			static inline void LEDs_SetAllLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[LEDS_PORT].ovrs  = LEDS_ALL_LEDS;
				AVR32_GPIO.port[LEDS_PORT].ovrc  = LEDMask;
			}

			static inline void LEDs_ChangeLEDs(const uint32_t LEDMask, const uint32_t ActiveMask)
			{
				AVR32_GPIO.port[LEDS_PORT].ovrs  = LEDMask;
				AVR32_GPIO.port[LEDS_PORT].ovrc  = ActiveMask;
			}

			static inline void LEDs_ToggleLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[LEDS_PORT].ovrt  = LEDMask;
			}

			static inline uint32_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint32_t LEDs_GetLEDs(void)
			{
				return (~AVR32_GPIO.port[LEDS_PORT].ovr & LEDS_ALL_LEDS);
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

