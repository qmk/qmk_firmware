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
 *  \brief Board specific information header for the MINIMUS.
 *  \copydetails Group_BoardInfo_MINIMUS
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Board driver
 *        dispatch header located in LUFA/Drivers/Board/Board.h.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MINIMUS MINIMUS
 *  \brief Board specific information header for the MINIMUS.
 *
 *  Board specific information header for the MINIMUS.
 *
 *  @{
 */

#ifndef __BOARD_MINIMUS_H__
#define __BOARD_MINIMUS_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../../Buttons.h"
		#include "../../LEDs.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_BOARD_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Board.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Indicates the board has hardware Buttons mounted. */
			#define BOARD_HAS_BUTTONS

			/** Indicates the board has hardware LEDs mounted. */
			#define BOARD_HAS_LEDS

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

