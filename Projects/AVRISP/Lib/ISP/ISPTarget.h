/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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
 *
 *  Header file for ISPTarget.c.
 */

#ifndef _ISP_TARGET_
#define _ISP_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <util/delay.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SPI.h>
		
		#include "../V2ProtocolParams.h"

	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Macros: */
		/** Total number of allowable ISP programming speeds supported by the device */
		#define TOTAL_ISP_PROGRAMMING_SPEEDS  7

		/** Timeout in milliseconds of target busy-wait loops waiting for a command to complete */
		#define TARGET_BUSY_TIMEOUT_MS        100

	/* Function Prototypes: */
		uint8_t ISPTarget_GetSPIPrescalerMask(void);
		void    ISPTarget_ChangeTargetResetLine(const bool ResetTarget);
		uint8_t ISPTarget_WaitForProgComplete(const uint8_t ProgrammingMode, const uint16_t PollAddress,
		                                      const uint8_t PollValue, const uint8_t DelayMS,
		                                      const uint8_t ReadMemCommand);
		uint8_t ISPTarget_WaitWhileTargetBusy(void);
		void    ISPTarget_LoadExtendedAddress(void);

#endif
