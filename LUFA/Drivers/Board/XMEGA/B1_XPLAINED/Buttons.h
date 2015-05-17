/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Board specific Buttons driver header for the Atmel XMEGA B1 Xplained.
 *  \copydetails Group_Buttons_B1_XPLAINED
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_B1_XPLAINED B1_XPLAINED
 *  \brief Board specific Buttons driver header for the Atmel XMEGA B1 Xplained.
 *
 *  Board specific Buttons driver header for the Atmel XMEGA B1 Xplained.
 *
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>BUTTONS_BUTTON1</td><td>Touch CS0 Button</td><td>Low</td><td>PORTE.0</td></tr>
 *    <tr><td>BUTTONS_BUTTON2</td><td>Touch CS1 Button</td><td>Low</td><td>PORTE.1</td></tr>
 *    <tr><td>BUTTONS_BUTTON3</td><td>Touch CS2 Button</td><td>Low</td><td>PORTE.2</td></tr>
 *    <tr><td>BUTTONS_BUTTON4</td><td>Touch CS3 Button</td><td>Low</td><td>PORTE.3</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __BUTTONS_B1_XPLAINED_H__
#define __BUTTONS_B1_XPLAINED_H__

	/* Includes: */
		#include <avr/io.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BUTTONS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Buttons.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the first button on the board. */
			#define BUTTONS_BUTTON1          (1 << 0)

			/** Button mask for the second button on the board. */
			#define BUTTONS_BUTTON2          (1 << 1)

			/** Button mask for the third button on the board. */
			#define BUTTONS_BUTTON3          (1 << 2)

			/** Button mask for the fourth button on the board. */
			#define BUTTONS_BUTTON4          (1 << 3)

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Buttons_Init(void)
			{
				PORTE.OUTSET    = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4);

				PORTCFG.MPCMASK = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4);
				PORTE.PIN0CTRL  = (PORT_INVEN_bm | PORT_OPC_PULLUP_gc);
			}

			static inline void Buttons_Disable(void)
			{
				PORTE.OUTCLR    = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4);

				PORTCFG.MPCMASK = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4);
				PORTE.PIN0CTRL  = 0;
			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
				return (PORTE_IN & (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

