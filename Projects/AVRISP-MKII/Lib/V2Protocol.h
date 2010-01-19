/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
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
		#include "ISP/ISPProtocol.h"
		#include "XPROG/XPROGProtocol.h"

	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_XPROG_PROTOCOL)
				#define ENABLE_XPROG_PROTOCOL
			#endif
		#endif

	/* Macros: */
		/** Programmer ID string, returned to the host during the CMD_SIGN_ON command processing */
		#define PROGRAMMER_ID       "AVRISP_MK2"
		
		/** Timeout period for each issued command from the host before it is aborted */
		#define COMMAND_TIMEOUT_MS   200
		
		/** Command timeout counter register, GPIOR for speed */
		#define TimeoutMSRemaining   GPIOR0

	/* External Variables: */
		extern uint32_t CurrentAddress;
		extern bool     MustSetAddress;

	/* Function Prototypes: */
		void V2Protocol_Init(void);
		void V2Protocol_ProcessCommand(void);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_C)
			static void V2Protocol_UnknownCommand(uint8_t V2Command);
			static void V2Protocol_SignOn(void);
			static void V2Protocol_GetSetParam(uint8_t V2Command);
			static void V2Protocol_ResetProtection(void);
			static void V2Protocol_LoadAddress(void);
		#endif

#endif

