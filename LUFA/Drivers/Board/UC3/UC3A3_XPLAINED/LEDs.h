/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Board specific LED driver header for the Atmel UC3-A3 Xplained.
 *  \copydetails Group_LEDs_UC3A3_XPLAINED
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_UC3A3_XPLAINED UC3A3_XPLAINED
 *  \brief Board specific LED driver header for the Atmel UC3-A3 Xplained.
 *
 *  Board specific LED driver header for the Atmel UC3-A3 Xplained.
 *
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Yellow</td><td>LED0 LED</td><td>Low</td><td>GPIO35</td></tr>
 *    <tr><td>LEDS_LED2</td><td>Yellow</td><td>LED1 LED</td><td>Low</td><td>GPIO73</td></tr>
 *    <tr><td>LEDS_LED3</td><td>Yellow</td><td>LED2 LED</td><td>Low</td><td>GPIO34</td></tr>
 *    <tr><td>LEDS_LED4</td><td>Yellow</td><td>LED3 LED</td><td>Low</td><td>GPIO38</td></tr>
 *    <tr><td>LEDS_LED5</td><td>Green</td><td>Status</td><td>Low</td><td>GPIO50</td></tr>
 *    <tr><td>LEDS_LED6</td><td>Red</td><td>Power</td><td>High</td><td>GPIO49</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_UC3A3_XPLAINED_H__
#define __LEDS_UC3A3_XPLAINED_H__

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
			#define LEDS_LEDMASK1   ((1UL << 3) | (1UL << 2) | (1UL << 6) | (1UL << 18) | (1UL << 17))
			#define LEDS_LEDMASK3    (1UL << 9)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1UL << 3)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1UL << 9)

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        (1UL << 2)

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        (1UL << 6)

			/** LED mask for the fifth LED on the board. */
			#define LEDS_LED5        (1UL << 18)

			/** LED mask for the sixth LED on the board. */
			#define LEDS_LED6        (1UL << 17)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4 | LEDS_LED5 | LEDS_LED6)

			/** LED mask for the none of the board LEDs */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				AVR32_GPIO.port[1].gpers = LEDS_LEDMASK1;
				AVR32_GPIO.port[1].oders = LEDS_LEDMASK1;
				AVR32_GPIO.port[1].ovrs  = LEDS_LEDMASK1;

				AVR32_GPIO.port[3].gpers = LEDS_LEDMASK3;
				AVR32_GPIO.port[3].oders = LEDS_LEDMASK3;
				AVR32_GPIO.port[3].ovrs  = LEDS_LEDMASK3;
			}

			static inline void LEDs_Disable(void)
			{
				AVR32_GPIO.port[1].gperc = LEDS_LEDMASK1;
				AVR32_GPIO.port[1].oderc = LEDS_LEDMASK1;
				AVR32_GPIO.port[1].ovrc  = LEDS_LEDMASK1;

				AVR32_GPIO.port[3].gperc = LEDS_LEDMASK3;
				AVR32_GPIO.port[3].oderc = LEDS_LEDMASK3;
				AVR32_GPIO.port[3].ovrc  = LEDS_LEDMASK3;
			}

			static inline void LEDs_TurnOnLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[1].ovrc  = (LEDMask & LEDS_LEDMASK1);
				AVR32_GPIO.port[3].ovrc  = (LEDMask & LEDS_LEDMASK3);
			}

			static inline void LEDs_TurnOffLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[1].ovrs  = (LEDMask & LEDS_LEDMASK1);
				AVR32_GPIO.port[3].ovrs  = (LEDMask & LEDS_LEDMASK3);
			}

			static inline void LEDs_SetAllLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[1].ovrs  = LEDS_LEDMASK1;
				AVR32_GPIO.port[1].ovrc  = (LEDMask & LEDS_LEDMASK1);

				AVR32_GPIO.port[3].ovrs  = LEDS_LEDMASK3;
				AVR32_GPIO.port[3].ovrc  = (LEDMask & LEDS_LEDMASK3);
			}

			static inline void LEDs_ChangeLEDs(const uint32_t LEDMask, const uint32_t ActiveMask)
			{
				AVR32_GPIO.port[1].ovrs  = (LEDMask    & LEDS_LEDMASK1);
				AVR32_GPIO.port[1].ovrc  = (ActiveMask & LEDS_LEDMASK1);

				AVR32_GPIO.port[3].ovrs  = (LEDMask    & LEDS_LEDMASK3);
				AVR32_GPIO.port[3].ovrc  = (ActiveMask & LEDS_LEDMASK3);
			}

			static inline void LEDs_ToggleLEDs(const uint32_t LEDMask)
			{
				AVR32_GPIO.port[1].ovrt  = (LEDMask & LEDS_LEDMASK1);
				AVR32_GPIO.port[3].ovrt  = (LEDMask & LEDS_LEDMASK3);
			}

			static inline uint32_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint32_t LEDs_GetLEDs(void)
			{
				return ((~AVR32_GPIO.port[1].ovr & LEDS_LEDMASK1) | (~AVR32_GPIO.port[3].ovr & LEDS_LEDMASK3));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

