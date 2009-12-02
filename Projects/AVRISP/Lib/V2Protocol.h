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
		#include "V2ProtocolTarget.h"

	/* Macros: */
		/** Programmer ID string, returned to the host during the CMD_SIGN_ON command processing */
		#define PROGRAMMER_ID                   "AVRISP_MK2"
		
		/** Mask for the reading or writing of the high byte in a FLASH word when issuing a low-level programming command */
		#define READ_WRITE_HIGH_BYTE_MASK       (1 << 3)

		#define PROG_MODE_PAGED_WRITES_MASK     (1 << 0)
		#define PROG_MODE_WORD_TIMEDELAY_MASK   (1 << 1)
		#define PROG_MODE_WORD_VALUE_MASK       (1 << 2)
		#define PROG_MODE_WORD_READYBUSY_MASK   (1 << 3)
		#define PROG_MODE_PAGED_TIMEDELAY_MASK  (1 << 4)
		#define PROG_MODE_PAGED_VALUE_MASK      (1 << 5)
		#define PROG_MODE_PAGED_READYBUSY_MASK  (1 << 6)
		#define PROG_MODE_COMMIT_PAGE_MASK      (1 << 7)

	/* Function Prototypes: */
		void V2Protocol_ProcessCommand(void);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_C)
			static void V2Protocol_UnknownCommand(uint8_t V2Command);
			static void V2Protocol_SignOn(void);
			static void V2Protocol_GetSetParam(uint8_t V2Command);
			static void V2Protocol_ResetProtection(void);
			static void V2Protocol_LoadAddress(void);
			static void V2Protocol_ISP_EnterISPMode(void);
			static void V2Protocol_ISP_LeaveISPMode(void);
			static void V2Protocol_ISP_ProgramMemory(uint8_t V2Command);
			static void V2Protocol_ISP_ReadMemory(uint8_t V2Command);
			static void V2Protocol_ISP_ChipErase(void);
			static void V2Protocol_ISP_ReadFuseLockSigOSCCAL(uint8_t V2Command);
			static void V2Protocol_ISP_WriteFuseLock(uint8_t V2Command);
			static void V2Protocol_ISP_SPIMulti(void);
		#endif

#endif

