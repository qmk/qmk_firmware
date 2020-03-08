/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Board specific Buttons driver header for the Micropendous series boards.
 *  \copydetails Group_Buttons_MICROPENDOUS_32U2
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_A MICROPENDOUS_A
 *  \brief Board specific Button driver header for the Micropendous A (https://code.google.com/p/micropendous/wiki/MicropendousA).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_1 MICROPENDOUS_1
 *  \brief Board specific Button driver header for the Micropendous 1 (https://code.google.com/p/micropendous/wiki/Micropendous1).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_2 MICROPENDOUS_2
 *  \brief Board specific Button driver header for the Micropendous 2 (https://code.google.com/p/micropendous/wiki/Micropendous2).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_3 MICROPENDOUS_3
 *  \brief Board specific Button driver header for the Micropendous 3 (https://code.google.com/p/micropendous/wiki/Micropendous3).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_4 MICROPENDOUS_4
 *  \brief Board specific Button driver header for the Micropendous 4 (https://code.google.com/p/micropendous/wiki/Micropendous4).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_DIP MICROPENDOUS_DIP
 *  \brief Board specific Button driver header for the Micropendous DIP (https://code.google.com/p/micropendous/wiki/MicropendousDIP).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_REV1 MICROPENDOUS_REV1
 *  \brief Board specific Button driver header for the Micropendous Arduino-like Revision 1 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_REV2 MICROPENDOUS_REV2
 *  \brief Board specific Button driver header for the Micropendous Arduino-like Revision 2 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_Buttons_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_MICROPENDOUS_32U2 MICROPENDOUS_32U2
 *  \brief Board specific Buttons driver header for the Micropendous 32U2.
 *
 *  \note There are multiple supported Micropendous boards, compile with <code>BOARD = MICROPENDOUS_{VERSION}</code>.
 *
 *  Board specific Buttons driver header for the Micropendous 32U2 (https://code.google.com/p/micropendous/wiki/Micropendous_32U2).
 *
 *  <b>BOARD_MICROPENDOUS_1 and BOARD_MICROPENDOUS_32U2</b>:
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>BUTTONS_BUTTON1</td><td>HWB Button</td><td>Low</td><td>PORTD.7</td></tr>
 *  </table>
 *
 *  <b>Other Revisions</b>:
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>BUTTONS_BUTTON1</td><td>HWB Button</td><td>Low</td><td>PORTE.2</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __BUTTONS_MICROPENDOUS_H__
#define __BUTTONS_MICROPENDOUS_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BUTTONS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		#if (BOARD == BOARD_MICROPENDOUS_32U2)
			#define _BOARD_BUTTON1_MASK             (1 << 7)
			#define _BOARD_BUTTON_PORTLETTER        D
		#elif (BOARD == BOARD_MICROPENDOUS_A)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_1)
			#define _BOARD_BUTTON1_MASK             (1 << 7)
			#define _BOARD_BUTTON_PORTLETTER        D
		#elif (BOARD == BOARD_MICROPENDOUS_2)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_3)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_4)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_DIP)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_REV1)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#elif (BOARD == BOARD_MICROPENDOUS_REV2)
			#define _BOARD_BUTTON1_MASK             (1 << 2)
			#define _BOARD_BUTTON_PORTLETTER        E
		#endif

		#define _BOARD_BUTTON_PORT                  CONCAT_EXPANDED(PORT, _BOARD_BUTTON_PORTLETTER)
		#define _BOARD_BUTTON_PIN                   CONCAT_EXPANDED(PIN,  _BOARD_BUTTON_PORTLETTER)
		#define _BOARD_BUTTON_DDR                   CONCAT_EXPANDED(DDR,  _BOARD_BUTTON_PORTLETTER)
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the first button on the board. */
			#define BUTTONS_BUTTON1     _BOARD_BUTTON1_MASK

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Buttons_Init(void)
			{
				_BOARD_BUTTON_DDR  &= ~BUTTONS_BUTTON1;
				_BOARD_BUTTON_PORT |=  BUTTONS_BUTTON1;
			}

			static inline void Buttons_Disable(void)
			{
				_BOARD_BUTTON_DDR  &= ~BUTTONS_BUTTON1;
				_BOARD_BUTTON_PORT &= ~BUTTONS_BUTTON1;
			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
				return ((_BOARD_BUTTON_PIN & BUTTONS_BUTTON1) ^ BUTTONS_BUTTON1);
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */


