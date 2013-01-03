/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Board specific Buttons driver header for the Atmel EVK1101.
 *  \copydetails Group_Buttons_EVK1101
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Buttons driver
 *        dispatch header located in LUFA/Drivers/Board/Buttons.h.
 */

/** \ingroup Group_Buttons
 *  \defgroup Group_Buttons_EVK1101 EVK1101
 *  \brief Board specific Buttons driver header for the Atmel EVK1101.
 *
 *  Board specific Buttons driver header for the Atmel EVK1101.
 *
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Active Level</th><th>Port Pin</th></tr>
 *    <tr><td>BUTTONS_BUTTON1</td><td>SW0 Button</td><td>Low</td><td>GPIO34</td></tr>
 *    <tr><td>BUTTONS_BUTTON2</td><td>SW1 Button</td><td>Low</td><td>GPIO35</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __BUTTONS_EVK1101_H__
#define __BUTTONS_EVK1101_H__

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
		/* Macros: */
			#define BUTTONS_PORT          1
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mask of the first button on the board */
			#define BUTTONS_BUTTON1       (1UL << 2)

			/** Mask of the second button on the board */
			#define BUTTONS_BUTTON2       (1UL << 3)

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Buttons_Init(void)
			{
				AVR32_GPIO.port[BUTTONS_PORT].gpers = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2);
				AVR32_GPIO.port[BUTTONS_PORT].puers = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2);
			}

			static inline void Buttons_Disable(void)
			{
				AVR32_GPIO.port[BUTTONS_PORT].gperc = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2);
				AVR32_GPIO.port[BUTTONS_PORT].puerc = (BUTTONS_BUTTON1 | BUTTONS_BUTTON2);
			}

			static inline uint32_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint32_t Buttons_GetStatus(void)
			{
				return (~(AVR32_GPIO.port[BUTTONS_PORT].pvr & (BUTTONS_BUTTON1 | BUTTONS_BUTTON2)));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

