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
 *  Header file for V2ProtocolTarget.c.
 */

#ifndef _V2_PROTOCOL_TARGET_
#define _V2_PROTOCOL_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <util/delay.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SPI.h>
		
		#include "../Descriptors.h"
		#include "V2ProtocolConstants.h"
		#include "V2ProtocolParams.h"

	/* Macros: */
		/** Total number of allowable ISP programming speeds supported by the device */
		#define TOTAL_PROGRAMMING_SPEEDS  7

		/** Timeout in milliseconds of target busy-wait loops waiting for a command to complete */
		#define TARGET_BUSY_TIMEOUT_MS    240
		
	/* External Variables: */
		extern uint32_t CurrentAddress;

	/* Inline Functions: */
		/** Blocking delay for a given number of milliseconds, via a hardware timer.
		 *
		 *  \param[in] DelayMS  Number of milliseconds to delay for
		 */
		static inline void V2Protocol_DelayMS(uint8_t DelayMS)
		{
			TCNT0 = 0;
			while (TCNT0 < DelayMS);
		}

	/* Function Prototypes: */
			uint8_t V2Protocol_GetSPIPrescalerMask(void);
			void    V2Protocol_ChangeTargetResetLine(bool ResetTarget);
			void    V2Protocol_DelayMS(uint8_t MS);
			uint8_t V2Protocol_WaitForProgComplete(uint8_t ProgrammingMode, uint16_t PollAddress, uint8_t PollValue,
                                                   uint8_t DelayMS, uint8_t ReadMemCommand);
			uint8_t V2Protocol_WaitWhileTargetBusy(void);
			void    V2Protocol_LoadExtendedAddress(void);

#endif
