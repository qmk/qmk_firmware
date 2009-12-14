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
 *  Target-related functions for the target's NVM module.
 */

#define  INCLUDE_FROM_NVMTARGET_C
#include "NVMTarget.h"

#if defined(ENABLE_PDI_PROTOCOL) || defined(__DOXYGEN__)

void NVMTarget_SendNVMRegAddress(uint8_t Register)
{
	uint32_t Address = XPROG_Param_NVMBase | Register;

	PDITarget_SendByte(Address >> 24);
	PDITarget_SendByte(Address >> 26);
	PDITarget_SendByte(Address >> 8);
	PDITarget_SendByte(Address &  0xFF);
}

bool NVMTarget_WaitWhileNVMBusBusy(void)
{
	uint8_t AttemptsRemaining = 255;

	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (AttemptsRemaining--)
	{
		PDITarget_SendByte(PDI_CMD_LDCS | PDI_STATUS_REG);
		if (PDITarget_ReceiveByte() & PDI_STATUS_NVM)
		  return true;
	}
	
	return false;
}

void NVMTarget_WaitWhileNVMControllerBusy(void)
{
	/* Poll the NVM STATUS register while the NVM controller is busy */
	for (;;)
	{
		PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_1BYTE << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_STATUS);
		
		if (!(PDITarget_ReceiveByte() & (1 << 7)))
		  return;
	}
}

uint32_t NVMTarget_GetMemoryCRC(uint8_t MemoryCommand)
{
	uint32_t MemoryCRC;

	/* Set the NVM command to the correct CRC read command */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_1BYTE << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(MemoryCommand);

	/* Set CMDEX bit in NVM CTRLA register to start the CRC generation */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_1BYTE << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CTRLA);
	PDITarget_SendByte(1 << 0);

	/* Wait until the NVM bus and controller is no longer busy */
	NVMTarget_WaitWhileNVMBusBusy();
	NVMTarget_WaitWhileNVMControllerBusy();
	
	/* Read the three byte generated CRC value */
	PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_3BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_DAT0);
	MemoryCRC  = PDITarget_ReceiveByte();
	MemoryCRC |= ((uint16_t)PDITarget_ReceiveByte() << 8);
	MemoryCRC |= ((uint32_t)PDITarget_ReceiveByte() << 16);
	
	return MemoryCRC;
}

#endif
