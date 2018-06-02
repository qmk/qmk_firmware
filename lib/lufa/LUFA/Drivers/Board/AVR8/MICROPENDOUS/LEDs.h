/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Board specific LED driver header for the Micropendous series boards.
 *  \copydetails Group_LEDs_MICROPENDOUS_32U2
 *
 *  \note This file should not be included directly. It is automatically included as needed by the LEDs driver
 *        dispatch header located in LUFA/Drivers/Board/LEDs.h.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_MICROPENDOUS_REV1 MICROPENDOUS_REV1
 *  \brief Board specific LED driver header for the Micropendous Arduino-like Revision 1 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_LEDs_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_MICROPENDOUS_REV2 MICROPENDOUS_REV2
 *  \brief Board specific LED driver header for the Micropendous Arduino-like Revision 2 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_LEDs_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_LEDs
 *  \defgroup Group_LEDs_MICROPENDOUS_32U2 MICROPENDOUS_32U2
 *  \brief Board specific LED driver header for the Micropendous-32U2.
 *
 *  Board specific LED driver header for the Micropendous 32U2 (https://code.google.com/p/micropendous/wiki/Micropendous_32U2).
 *
 *  <b>BOARD_MICROPENDOUS_32U2</b>:
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>General Indicator</td><td>High</td><td>PORTD.6</td></tr>
 *  </table>
 *
 *  <b>Other Revisions</b>:
 *  <table>
 *    <tr><th>Name</th><th>Color</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>LEDS_LED1</td><td>Green</td><td>General Indicator</td><td>High</td><td>PORTB.1</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __LEDS_MICROPENDOUS_H__
#define __LEDS_MICROPENDOUS_H__

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
		#if (BOARD == BOARD_MICROPENDOUS_32U2)
			#define _BOARD_LED1_MASK                (1 << 6)
			#define _BOARD_LED_PORTLETTER           D
		#elif (BOARD == BOARD_MICROPENDOUS_REV1)
			#define _BOARD_LED1_MASK                (1 << 1)
			#define _BOARD_LED_PORTLETTER           B
		#elif (BOARD == BOARD_MICROPENDOUS_REV2)
			#define _BOARD_LED1_MASK                (1 << 1)
			#define _BOARD_LED_PORTLETTER           B
		#endif

		#define _BOARD_LED_PORT                     CONCAT_EXPANDED(PORT, _BOARD_LED_PORTLETTER)
		#define _BOARD_LED_PIN                      CONCAT_EXPANDED(PIN,  _BOARD_LED_PORTLETTER)
		#define _BOARD_LED_DDR                      CONCAT_EXPANDED(DDR,  _BOARD_LED_PORTLETTER)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        _BOARD_LED1_MASK

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    LEDS_LED1

			/** LED mask for the none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				_BOARD_LED_DDR  |=  LEDS_ALL_LEDS;
				_BOARD_LED_PORT &= ~LEDS_ALL_LEDS;
			}

			static inline void LEDs_Disable(void)
			{
				_BOARD_LED_DDR  &= ~LEDS_ALL_LEDS;
				_BOARD_LED_PORT &= ~LEDS_ALL_LEDS;
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				_BOARD_LED_PORT |= LEDMask;
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				_BOARD_LED_PORT &= ~LEDMask;
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				_BOARD_LED_PORT = ((_BOARD_LED_PORT & ~LEDS_ALL_LEDS) | LEDMask);
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask,
			                                   const uint8_t ActiveMask)
			{
				_BOARD_LED_PORT = ((_BOARD_LED_PORT & ~LEDMask) | ActiveMask);
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				_BOARD_LED_PIN  = LEDMask;
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				return (_BOARD_LED_PORT & LEDS_ALL_LEDS);
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

