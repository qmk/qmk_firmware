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
 *  Header file for XMEGANVM.c.
 */

#ifndef _XMEGA_NVM__
#define _XMEGA_NVM_

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
			#undef ENABLE_TPI_PROTOCOL
			
			#if !defined(ENABLE_PDI_PROTOCOL)
				#define ENABLE_PDI_PROTOCOL
			#endif
		#endif

	/* Defines: */
		#define XMEGA_NVM_BUSY_TIMEOUT_MS            200
		
		#define XMEGA_NVM_REG_ADDR0                  0x00
		#define XMEGA_NVM_REG_ADDR1                  0x01
		#define XMEGA_NVM_REG_ADDR2                  0x02
		#define XMEGA_NVM_REG_DAT0                   0x04
		#define XMEGA_NVM_REG_DAT1                   0x05
		#define XMEGA_NVM_REG_DAT2                   0x06
		#define XMEGA_NVM_REG_CMD                    0x0A
		#define XMEGA_NVM_REG_CTRLA                  0x0B
		#define XMEGA_NVM_REG_CTRLB                  0x0C
		#define XMEGA_NVM_REG_INTCTRL                0x0D
		#define XMEGA_NVM_REG_STATUS                 0x0F
		#define XMEGA_NVM_REG_LOCKBITS               0x10
		
		#define XMEGA_NVM_CMD_NOOP                   0x00
		#define XMEGA_NVM_CMD_CHIPERASE              0x40
		#define XMEGA_NVM_CMD_READNVM                0x43
		#define XMEGA_NVM_CMD_LOADFLASHPAGEBUFF      0x23
		#define XMEGA_NVM_CMD_ERASEFLASHPAGEBUFF     0x26
		#define XMEGA_NVM_CMD_ERASEFLASHPAGE         0x2B
		#define XMEGA_NVM_CMD_WRITEFLASHPAGE         0x2E
		#define XMEGA_NVM_CMD_ERASEWRITEFLASH        0x2F
		#define XMEGA_NVM_CMD_FLASHCRC               0x78
		#define XMEGA_NVM_CMD_ERASEAPPSEC            0x20
		#define XMEGA_NVM_CMD_ERASEAPPSECPAGE        0x22
		#define XMEGA_NVM_CMD_WRITEAPPSECPAGE        0x24
		#define XMEGA_NVM_CMD_ERASEWRITEAPPSECPAGE   0x25
		#define XMEGA_NVM_CMD_APPCRC                 0x38
		#define XMEGA_NVM_CMD_ERASEBOOTSEC           0x68
		#define XMEGA_NVM_CMD_ERASEBOOTSECPAGE       0x2A
		#define XMEGA_NVM_CMD_WRITEBOOTSECPAGE       0x2C
		#define XMEGA_NVM_CMD_ERASEWRITEBOOTSECPAGE  0x2D
		#define XMEGA_NVM_CMD_BOOTCRC                0x39
		#define XMEGA_NVM_CMD_READUSERSIG            0x03
		#define XMEGA_NVM_CMD_ERASEUSERSIG           0x18
		#define XMEGA_NVM_CMD_WRITEUSERSIG           0x1A
		#define XMEGA_NVM_CMD_READCALIBRATION        0x02
		#define XMEGA_NVM_CMD_READFUSE               0x07
		#define XMEGA_NVM_CMD_WRITEFUSE              0x4C
		#define XMEGA_NVM_CMD_WRITELOCK              0x08
		#define XMEGA_NVM_CMD_LOADEEPROMPAGEBUFF     0x33
		#define XMEGA_NVM_CMD_ERASEEEPROMPAGEBUFF    0x36
		#define XMEGA_NVM_CMD_ERASEEEPROM            0x30
		#define XMEGA_NVM_CMD_ERASEEEPROMPAGE        0x32
		#define XMEGA_NVM_CMD_WRITEEEPROMPAGE        0x34
		#define XMEGA_NVM_CMD_ERASEWRITEEEPROMPAGE   0x35
		#define XMEGA_NVM_CMD_READEEPROM             0x06

	/* Function Prototypes: */
		void XMEGANVM_SendNVMRegAddress(const uint8_t Register);
		void XMEGANVM_SendAddress(const uint32_t AbsoluteAddress);
		bool XMEGANVM_WaitWhileNVMControllerBusy(void);
		bool XMEGANVM_GetMemoryCRC(const uint8_t CRCCommand, uint32_t* const CRCDest);
		bool XMEGANVM_ReadMemory(const uint32_t ReadAddress, uint8_t* ReadBuffer, const uint16_t ReadSize);
		bool XMEGANVM_WriteByteMemory(const uint8_t WriteCommand, const uint32_t WriteAddress, const uint8_t* WriteBuffer);
		bool XMEGANVM_WritePageMemory(const uint8_t WriteBuffCommand, const uint8_t EraseBuffCommand,
		                              const uint8_t WritePageCommand, const uint8_t PageMode, const uint32_t WriteAddress,
		                              const uint8_t* WriteBuffer, const uint16_t WriteSize);
		bool XMEGANVM_EraseMemory(const uint8_t EraseCommand, const uint32_t Address);

#endif
