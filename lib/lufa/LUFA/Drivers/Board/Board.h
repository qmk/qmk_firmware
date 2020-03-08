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
 *  \brief Board hardware information driver.
 *
 *  This file is the master dispatch header file for the board-specific information driver, to give information
 *  on the hardware contained on a specific board.
 *
 *  User code should include this file, which will in turn include the correct board driver header file for the
 *  currently selected board.
 *
 *  If the \c BOARD value is set to \c BOARD_USER, this will include the \c /Board/Board.h file in the user project
 *  directory.
 *
 *  For possible \c BOARD makefile values, see \ref Group_BoardTypes.
 */

/** \ingroup Group_BoardDrivers
 *  \defgroup Group_BoardInfo Board Information Driver - LUFA/Drivers/Board/Board.h
 *  \brief Board hardware information driver.
 *
 *  \section Sec_BoardInfo_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  @{
 */

#ifndef __BOARD_H__
#define __BOARD_H__

	/* Macros: */
		#define __INCLUDE_FROM_BOARD_H

	/* Includes: */
		#include "../../Common/Common.h"

		#if (BOARD == BOARD_USBKEY)
			#include "AVR8/USBKEY/Board.h"
		#elif (BOARD == BOARD_STK525)
			#include "AVR8/STK525/Board.h"
		#elif (BOARD == BOARD_STK526)
			#include "AVR8/STK526/Board.h"
		#elif (BOARD == BOARD_RZUSBSTICK)
			#include "AVR8/RZUSBSTICK/Board.h"
		#elif (BOARD == BOARD_ATAVRUSBRF01)
			#include "AVR8/ATAVRUSBRF01/Board.h"
		#elif ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#include "AVR8/XPLAIN/Board.h"
		#elif (BOARD == BOARD_BUMBLEB)
			#include "AVR8/BUMBLEB/Board.h"
		#elif (BOARD == BOARD_EVK527)
			#include "AVR8/EVK527/Board.h"
		#elif ((BOARD == BOARD_TEENSY) || (BOARD == BOARD_TEENSY2))
			#include "AVR8/TEENSY/Board.h"
		#elif ((BOARD == BOARD_QMK))
			#include "AVR8/QMK/Board.h"
		#elif (BOARD == BOARD_USBTINYMKII)
			#include "AVR8/USBTINYMKII/Board.h"
		#elif (BOARD == BOARD_BENITO)
			#include "AVR8/BENITO/Board.h"
		#elif (BOARD == BOARD_JMDBU2)
			#include "AVR8/JMDBU2/Board.h"
		#elif (BOARD == BOARD_OLIMEX162)
			#include "AVR8/OLIMEX162/Board.h"
		#elif (BOARD == BOARD_USBFOO)
			#include "AVR8/USBFOO/Board.h"
		#elif (BOARD == BOARD_UDIP)
			#include "AVR8/UDIP/Board.h"
		#elif (BOARD == BOARD_BUI)
			#include "AVR8/BUI/Board.h"
		#elif (BOARD == BOARD_UNO)
			#include "AVR8/UNO/Board.h"
		#elif (BOARD == BOARD_CULV3)
			#include "AVR8/CULV3/Board.h"
		#elif (BOARD == BOARD_BLACKCAT)
			#include "AVR8/BLACKCAT/Board.h"
		#elif (BOARD == BOARD_MAXIMUS)
			#include "AVR8/MAXIMUS/Board.h"
		#elif (BOARD == BOARD_MINIMUS)
			#include "AVR8/MINIMUS/Board.h"
		#elif (BOARD == BOARD_ADAFRUITU4)
			#include "AVR8/ADAFRUITU4/Board.h"
		#elif (BOARD == BOARD_MICROSIN162)
			#include "AVR8/MICROSIN162/Board.h"
		#elif (BOARD == BOARD_SPARKFUN8U2)
			#include "AVR8/SPARKFUN8U2/Board.h"
		#elif (BOARD == BOARD_EVK1101)
			#include "UC3/EVK1101/Board.h"
		#elif (BOARD == BOARD_TUL)
			#include "AVR8/TUL/Board.h"
		#elif (BOARD == BOARD_EVK1100)
			#include "UC3/EVK1100/Board.h"
		#elif (BOARD == BOARD_EVK1104)
			#include "UC3/EVK1104/Board.h"
		#elif (BOARD == BOARD_A3BU_XPLAINED)
			#include "XMEGA/A3BU_XPLAINED/Board.h"
		#elif ((BOARD == BOARD_USB2AX) || (BOARD == BOARD_USB2AX_V3) || (BOARD == BOARD_USB2AX_V31))
			#include "AVR8/USB2AX/Board.h"
		#elif ((BOARD == BOARD_MICROPENDOUS_REV1) || (BOARD == BOARD_MICROPENDOUS_REV2) || \
		       (BOARD == BOARD_MICROPENDOUS_32U2) || (BOARD == BOARD_MICROPENDOUS_A) || \
		       (BOARD == BOARD_MICROPENDOUS_1)    || (BOARD == BOARD_MICROPENDOUS_2) || \
		       (BOARD == BOARD_MICROPENDOUS_3)    || (BOARD == BOARD_MICROPENDOUS_4) || \
		       (BOARD == BOARD_MICROPENDOUS_DIP))
			#include "AVR8/MICROPENDOUS/Board.h"
		#elif (BOARD == BOARD_B1_XPLAINED)
			#include "XMEGA/B1_XPLAINED/Board.h"
		#elif (BOARD == BOARD_MULTIO)
			#include "AVR8/MULTIO/Board.h"
		#elif (BOARD == BOARD_BIGMULTIO)
			#include "AVR8/BIGMULTIO/Board.h"
		#elif (BOARD == BOARD_DUCE)
			#include "AVR8/DUCE/Board.h"
		#elif (BOARD == BOARD_OLIMEX32U4)
			#include "AVR8/OLIMEX32U4/Board.h"
		#elif (BOARD == BOARD_OLIMEXT32U4)
			#include "AVR8/OLIMEXT32U4/Board.h"
		#elif (BOARD == BOARD_OLIMEXISPMK2)
			#include "AVR8/OLIMEXISPMK2/Board.h"
		#elif (BOARD == BOARD_LEONARDO)
			#include "AVR8/LEONARDO/Board.h"
		#elif (BOARD == BOARD_UC3A3_XPLAINED)
			#include "UC3/UC3A3_XPLAINED/Board.h"
		#elif (BOARD == BOARD_STANGE_ISP)
			#include "AVR8/STANGE_ISP/Board.h"
		#elif (BOARD == BOARD_C3_XPLAINED)
			#include "XMEGA/C3_XPLAINED/Board.h"
		#elif (BOARD == BOARD_U2S)
			#include "AVR8/U2S/Board.h"
		#elif (BOARD == BOARD_YUN)
			#include "AVR8/YUN/Board.h"
		#elif (BOARD == BOARD_MICRO)
			#include "AVR8/MICRO/Board.h"
		#elif (BOARD == BOARD_POLOLUMICRO)
			#include "AVR8/POLOLUMICRO/Board.h"
		#elif (BOARD == BOARD_XPLAINED_MINI)
			#include "AVR8/XPLAINED_MINI/Board.h"
		#else
			#include "Board/Board.h"
		#endif

#endif

/** @} */

