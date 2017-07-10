/*
Copyright 2017 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 *  \brief General driver header for QMK-powered keyboards.
 *  \copydetails Group_BoardInfo_QMK
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Board driver
 *        dispatch header located in LUFA/Drivers/Board/Board.h.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_QMK QMK
 *  \brief General driver header for QMK-powered keyboards.
 *
 *  General driver header for QMK-powered keyboards (http://qmk.fm).
 *
 *  @{
 */

#ifndef __BOARD_QMK_H__
#define __BOARD_QMK_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
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
			/** Indicates the board has hardware LEDs mounted. */
			#define BOARD_HAS_LEDS

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

