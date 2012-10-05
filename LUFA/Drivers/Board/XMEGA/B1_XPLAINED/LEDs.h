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
 *  \brief Board specific LED driver header for the Atmel XMEGA B1 Xplained.
 *  \copydetails Group_LEDs_B1_XPLAINED
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_B1_XPLAINED B1_XPLAINED
 *  \brief Board specific LED driver header for the Atmel XMEGA B1 Xplained.
 *
 *  Board specific LED driver header for the Atmel XMEGA B1 Xplained.
 *
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Yellow</td><td>LED0 LED</td><td>High</td><td>PORTB.4</td></tr>
 *    <tr><td>LEDS_LED2</td><td>Yellow</td><td>LED1 LED</td><td>High</td><td>PORTB.5</td></tr>
 *    <tr><td>LEDS_LED3</td><td>Yellow</td><td>LED2 LED</td><td>High</td><td>PORTB.6</td></tr>
 *    <tr><td>LEDS_LED4</td><td>Yellow</td><td>LED3 LED</td><td>High</td><td>PORTB.7</td></tr>
 *    <tr><td>LEDS_LED5</td><td>Green</td><td>USB LED</td><td>Low</td><td>PORTE.4</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_B1_XPLAINED_H__
#define __LEDS_B1_XPLAINED_H__

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
			#define LEDS_PORTB_LEDS        (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4)
			#define LEDS_PORTE_LEDS        LEDS_LED5

			#define LEDS_PORTE_MASK_SHIFT  1
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1 << 4)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1 << 5)

			/** LED mask for the third LED on the board. */
			#define LEDS_LED3        (1 << 6)

			/** LED mask for the fourth LED on the board. */
			#define LEDS_LED4        (1 << 7)

			/** LED mask for the fifth LED on the board. */
			#define LEDS_LED5       ((1 << 4) >> LEDS_PORTE_MASK_SHIFT)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4 | LEDS_LED5)

			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				PORTB.DIRSET    = LEDS_PORTB_LEDS;
				PORTB.OUTCLR    = LEDS_PORTB_LEDS;

				PORTCFG.MPCMASK = LEDS_PORTB_LEDS;
				PORTB.PIN0CTRL  = PORT_INVEN_bm;

				PORTE.DIRSET    = (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT);
				PORTE.OUTCLR    = (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_Disable(void)
			{
				PORTB.DIRCLR    = LEDS_PORTB_LEDS;
				PORTB.OUTCLR    = LEDS_PORTB_LEDS;
				
				PORTCFG.MPCMASK = 0;
				PORTB.PIN0CTRL  = LEDS_PORTB_LEDS;

				PORTE.DIRCLR    = (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT);
				PORTE.OUTCLR    = (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				PORTB_OUTSET = (LEDMask & LEDS_PORTB_LEDS);
				PORTE_OUTSET = ((LEDMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				PORTB_OUTCLR = (LEDMask & LEDS_PORTB_LEDS);
				PORTE_OUTCLR = ((LEDMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				PORTB_OUTCLR = LEDS_PORTB_LEDS;
				PORTE_OUTCLR = (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT);

				PORTB_OUTSET = (LEDMask & LEDS_PORTB_LEDS);
				PORTE_OUTSET = ((LEDMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
			{
				PORTB_OUTCLR =  (LEDMask & LEDS_PORTB_LEDS);
				PORTE_OUTCLR = ((LEDMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			
				PORTB_OUTSET =  (ActiveMask & LEDS_PORTB_LEDS);
				PORTE_OUTSET = ((ActiveMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				PORTB_OUTTGL = (LEDMask & LEDS_PORTB_LEDS);
				PORTE_OUTTGL = ((LEDMask & LEDS_PORTE_LEDS) << LEDS_PORTE_MASK_SHIFT);
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				return ((PORTB_OUT & LEDS_PORTB_LEDS) | (PORTE_OUT & (LEDS_PORTE_LEDS << LEDS_PORTE_MASK_SHIFT)));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

