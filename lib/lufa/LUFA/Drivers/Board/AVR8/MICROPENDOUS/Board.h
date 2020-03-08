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
 *  \brief Board specific information header for the Micropendous series boards.
 *  \copydetails Group_BoardInfo_MICROPENDOUS_32U2
 *
 *  \note This file should not be included directly. It is automatically included as needed by the Board driver
 *        dispatch header located in LUFA/Drivers/Board/Board.h.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_A MICROPENDOUS_A
 *  \brief Board specific information header for the Micropendous A (https://code.google.com/p/micropendous/wiki/MicropendousA).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_1 MICROPENDOUS_1
 *  \brief Board specific information header for the Micropendous 1 (https://code.google.com/p/micropendous/wiki/Micropendous1).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_2 MICROPENDOUS_2
 *  \brief Board specific information header for the Micropendous 2 (https://code.google.com/p/micropendous/wiki/Micropendous2).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_3 MICROPENDOUS_3
 *  \brief Board specific information header for the Micropendous 3 (https://code.google.com/p/micropendous/wiki/Micropendous3).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_4 MICROPENDOUS_4
 *  \brief Board specific information header for the Micropendous 4 (https://code.google.com/p/micropendous/wiki/Micropendous4).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_DIP MICROPENDOUS_DIP
 *  \brief Board specific information header for the Micropendous DIP (https://code.google.com/p/micropendous/wiki/MicropendousDIP).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_REV1 MICROPENDOUS_REV1
 *  \brief Board specific information header for the Micropendous Arduino-like Revision 1 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_REV2 MICROPENDOUS_REV2
 *  \brief Board specific information header for the Micropendous Arduino-like Revision 2 (https://code.google.com/p/micropendous/wiki/Micropendous).
 *
 *  See \ref Group_BoardInfo_MICROPENDOUS_32U2 for more details.
 */

/** \ingroup Group_BoardInfo
 *  \defgroup Group_BoardInfo_MICROPENDOUS_32U2 MICROPENDOUS_32U2
 *  \brief Board specific information header for the Micropendous series boards.
 *
 *  Board specific information header for the Micropendous series boards (https://code.google.com/p/micropendous).
 *
 *  @{
 */

#ifndef __BOARD_MICROPENDOUS_H__
#define __BOARD_MICROPENDOUS_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

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
			#if ((BOARD == BOARD_MICROPENDOUS_32U2) || (BOARD == BOARD_MICROPENDOUS_A) || \
			     (BOARD == BOARD_MICROPENDOUS_1)    || (BOARD == BOARD_MICROPENDOUS_2) || \
			     (BOARD == BOARD_MICROPENDOUS_3)    || (BOARD == BOARD_MICROPENDOUS_4) || \
			     (BOARD == BOARD_MICROPENDOUS_REV1) || (BOARD == BOARD_MICROPENDOUS_REV2) || \
			     (BOARD == BOARD_MICROPENDOUS_DIP) || defined(__DOXYGEN__))
				#include "../../Buttons.h"

				/** Indicates the board has hardware Buttons mounted. */
				#define BOARD_HAS_BUTTONS
			#endif

			#if ((BOARD == BOARD_MICROPENDOUS_REV1) || (BOARD == BOARD_MICROPENDOUS_REV2) || \
			     (BOARD == BOARD_MICROPENDOUS_32U2) || defined(__DOXYGEN__))
				#include "../../LEDs.h"

				/** Indicates the board has hardware LEDs mounted. */
				#define BOARD_HAS_LEDS
			#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

