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
 *  Header file for V2Protocol.c.
 */

#ifndef _V2_PROTOCOL_
#define _V2_PROTOCOL_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Peripheral/SPI.h>
		
		#include "../Descriptors.h"
		#include "V2ProtocolConstants.h"
		#include "V2ProtocolParams.h"
		#include "ISPProtocol.h"
		#include "PDIProtocol.h"

	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Macros: */
		/** Programmer ID string, returned to the host during the CMD_SIGN_ON command processing */
		#define PROGRAMMER_ID             "AVRISP_MK2"

		/** Timeout in milliseconds of target busy-wait loops waiting for a command to complete */
		#define TARGET_BUSY_TIMEOUT_MS    240

	/* Inline Functions: */
		/** Blocking delay for a given number of milliseconds, via a hardware timer.
		 *
		 *  \param[in] DelayMS  Number of milliseconds to delay for
		 */
		static inline void V2Protocol_DelayMS(uint8_t DelayMS)
		{
			TCNT0 = 0;
			TIFR0 = (1 << OCF1A);

			while (DelayMS)
			{
				if (TIFR0 & (1 << OCF1A))
				{
					TIFR0 = (1 << OCF1A);
					DelayMS--;
				}
			}
		}

	/* External Variables: */
		extern uint32_t CurrentAddress;
		extern bool MustSetAddress;

	/* Function Prototypes: */
		void V2Protocol_ProcessCommand(void);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_C)
			static void V2Protocol_UnknownCommand(uint8_t V2Command);
			static void V2Protocol_SignOn(void);
			static void V2Protocol_GetSetParam(uint8_t V2Command);
			static void V2Protocol_ResetProtection(void);
			static void V2Protocol_LoadAddress(void);
		#endif

#endif

