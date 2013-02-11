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
 *  \brief Board specific LED driver header for the Paranoid Studio USB2AX.
 *  \copydetails Group_LEDs_USB2AX
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */
 
/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_USB2AX_V3 USB2AX_V3
 *  \brief Board specific LED driver header for the Paranoid Studio USB2AX revision 3.
 *
 *  See \ref Group_LEDs_USB2AX for more details.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_USB2AX USB2AX
 *  \brief Board specific LED driver header for the Paranoid Studio USB2AX.
 *
 *  \note For version 3 USB2AX boards, compile with <code>BOARD = USB2AX_V3</code>.
 *
 *  Board specific LED driver header for the Paranoid Studio USB2AX (http://paranoidstudio.assembla.com/wiki/show/paranoidstudio/USB2AX).
 *
 *  <b>USB2AX</b>:
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>General Indicator</td><td>High</td><td>PORTC.6</td></tr>
 *  </table>
 *
 *  <b>USB2AX_V3</b>:
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>General Indicator</td><td>High</td><td>PORTD.1</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_USB2AX_H__
#define __LEDS_USB2AX_H__

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
			#if (BOARD == BOARD_USB2AX)
				#define USB2AX_LEDS_LED1   (1 << 6)
			#else
				#define USB2AX_LEDS_LED1   (1 << 1)			
			#endif
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        USB2AX_LEDS_LED1

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    LEDS_LED1

			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				#if (BOARD == BOARD_USB2AX)
				DDRC  |=  LEDS_ALL_LEDS;
				PORTC &= ~LEDS_ALL_LEDS;				
				#else
				DDRD  |=  LEDS_ALL_LEDS;
				PORTD &= ~LEDS_ALL_LEDS;				
				#endif				
			}

			static inline void LEDs_Disable(void)
			{
				#if (BOARD == BOARD_USB2AX)
				DDRC  &= ~LEDS_ALL_LEDS;
				PORTC &= ~LEDS_ALL_LEDS;				
				#else
				DDRD  &= ~LEDS_ALL_LEDS;
				PORTD &= ~LEDS_ALL_LEDS;				
				#endif				
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				#if (BOARD == BOARD_USB2AX)
				PORTC |= LEDMask;				
				#else
				PORTD |= LEDMask;
				#endif
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				#if (BOARD == BOARD_USB2AX)
				PORTC &= ~LEDMask;
				#else
				PORTD &= ~LEDMask;
				#endif
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				#if (BOARD == BOARD_USB2AX)
				PORTC = ((PORTC & ~LEDS_ALL_LEDS) | LEDMask);				
				#else
				PORTD = ((PORTD & ~LEDS_ALL_LEDS) | LEDMask);
				#endif
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
			                                   const uint8_t ActiveMask)
			{
				#if (BOARD == BOARD_USB2AX)
				PORTC = ((PORTC & ~LEDMask) | ActiveMask);				
				#else
				PORTD = ((PORTD & ~LEDMask) | ActiveMask);
				#endif
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				#if (BOARD == BOARD_USB2AX)
				PINC  = LEDMask;				
				#else
				PIND  = LEDMask;
				#endif
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				#if (BOARD == BOARD_USB2AX)
				return (PORTC & LEDS_ALL_LEDS);				
				#else
				return (PORTD & LEDS_ALL_LEDS);
				#endif
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */


