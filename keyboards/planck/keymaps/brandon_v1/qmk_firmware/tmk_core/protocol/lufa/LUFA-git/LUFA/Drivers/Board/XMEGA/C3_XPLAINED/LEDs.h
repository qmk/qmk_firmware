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
 *  \brief Board specific LED driver header for the Atmel XMEGA C3 Xplained.
 *  \copydetails Group_LEDs_C3_XPLAINED
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_C3_XPLAINED C3_XPLAINED
 *  \brief Board specific LED driver header for the Atmel XMEGA C3 Xplained.
 *
 *  Board specific LED driver header for the Atmel XMEGA C3 Xplained.
 *
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Yellow</td><td>LED0 LED</td><td>Low</td><td>PORTR.0</td></tr>
 *    <tr><td>LEDS_LED2</td><td>Yellow</td><td>LED1 LED</td><td>Low</td><td>PORTR.1</td></tr>
 *    <tr><td>LEDS_LED3</td><td>Red</td><td>Status Bicolour Red LED</td><td>Low</td><td>PORTD.4</td></tr>
 *    <tr><td>LEDS_LED4</td><td>Green</td><td>Status Bicolour Green LED</td><td>High</td><td>PORTD.5</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_C3_XPLAINED_H__
#define __LEDS_C3_XPLAINED_H__

	/* Includes: */
		#include <avr/io.h>

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
			#define LEDS_PORTR_LEDS       (LEDS_LED1 | LEDS_LED2)
			#define LEDS_PORTD_LEDS       (LEDS_LED3 | LEDS_LED4)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1 << 0)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1 << 1)

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        (1 << 4)

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        (1 << 5)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)

			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				PORTR.DIRSET    = LEDS_PORTR_LEDS;
				PORTR.OUTCLR    = LEDS_PORTR_LEDS;

				PORTCFG.MPCMASK = LEDS_PORTR_LEDS;
				PORTR.PIN0CTRL  = PORT_INVEN_bm;

				PORTD.DIRSET    = LEDS_PORTD_LEDS;
				PORTD.OUTCLR    = LEDS_PORTD_LEDS;

				PORTD.PIN4CTRL  = PORT_INVEN_bm;
			}

			static inline void LEDs_Disable(void)
			{
				PORTR.DIRCLR    = LEDS_PORTR_LEDS;
				PORTR.OUTCLR    = LEDS_PORTR_LEDS;

				PORTCFG.MPCMASK = 0;
				PORTR.PIN0CTRL  = LEDS_PORTR_LEDS;

				PORTD.DIRCLR    = LEDS_PORTD_LEDS;
				PORTD.OUTCLR    = LEDS_PORTD_LEDS;

				PORTD.PIN4CTRL  = 0;
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				PORTR_OUTSET = LEDMask & LEDS_PORTR_LEDS;
				PORTD_OUTSET = LEDMask & LEDS_PORTD_LEDS;
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				PORTR_OUTCLR = LEDMask & LEDS_PORTR_LEDS;
				PORTD_OUTCLR = LEDMask & LEDS_PORTD_LEDS;
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				PORTR_OUTCLR = LEDS_PORTR_LEDS;
				PORTD_OUTCLR = LEDS_PORTD_LEDS;

				PORTR_OUTSET = (LEDMask & LEDS_PORTR_LEDS);
				PORTD_OUTSET = (LEDMask & LEDS_PORTD_LEDS);
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
			                                   const uint8_t ActiveMask)
			{
				PORTR_OUTCLR = (LEDMask & LEDS_PORTR_LEDS);
				PORTD_OUTCLR = (LEDMask & LEDS_PORTD_LEDS);

				PORTR_OUTSET = (ActiveMask & LEDS_PORTR_LEDS);
				PORTD_OUTSET = (ActiveMask & LEDS_PORTD_LEDS);
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				PORTR_OUTTGL = (LEDMask & LEDS_PORTR_LEDS);
				PORTD_OUTTGL = (LEDMask & LEDS_PORTD_LEDS);
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				return ((PORTR_OUT & LEDS_PORTR_LEDS) | (PORTD_OUT & LEDS_PORTD_LEDS));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

