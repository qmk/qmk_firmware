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
 *  Header file for NVMTarget.c.
 */

#ifndef _NVM_TARGET_
#define _NVM_TARGET_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		
		#include <LUFA/Common/Common.h>
		
		#include "PDIProtocol.h"
		#include "PDITarget.h"
	
	/* Preprocessor Checks: */
		#if ((BOARD == BOARD_XPLAIN) || (BOARD == BOARD_XPLAIN_REV1))
			#undef ENABLE_ISP_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#define FLASH_BASE           0x00800000
		#define EPPROM_BASE          0x008C0000
		#define FUSE_BASE            0x008F0020
		#define DATAMEM_BASE         0x01000000
		#define PROD_SIGNATURE_BASE  0x008E0200
		#define USER_SIGNATURE_BASE  0x008E0400
		
		#define NVM_REG_ADDR0        0x00
		#define NVM_REG_ADDR1        0x01
		#define NVM_REG_ADDR2        0x02
		#define NVM_REG_DAT0         0x04
		#define NVM_REG_DAT1         0x05
		#define NVM_REG_DAT2         0x06
		#define NVM_REG_CMD          0x0A
		#define NVM_REG_CTRLA        0x0B
		#define NVM_REG_CTRLB        0x0C
		#define NVM_REG_INTCTRL      0x0D
		#define NVM_REG_STATUS       0x0F
		#define NVM_REG_LOCKBITS     0x10
		
		#define NVM_CMD_APPCRC       0x38
		#define NVM_CMD_BOOTCRC      0x39
		#define NVM_CMD_FLASHCRC     0x78
		#define NVM_CMD_READUSERSIG  0x03
				
	/* Function Prototypes: */
		void NVMTarget_SendNVMRegAddress(uint8_t Register);
		bool     NVMTarget_WaitWhileNVMBusBusy(void);
		void     NVMTarget_WaitWhileNVMControllerBusy(void);
		uint32_t NVMTarget_GetMemoryCRC(uint8_t MemoryCommand);

#endif
