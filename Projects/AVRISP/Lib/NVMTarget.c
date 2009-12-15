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

/** Sends the given NVM register address to the target.
 *
 *  \param[in] Register  NVM register whose absolute address is to be sent
 */
void NVMTarget_SendNVMRegAddress(uint8_t Register)
{
	/* Determine the absolute register address from the NVM base memory address and the NVM register address */
	uint32_t Address = XPROG_Param_NVMBase | Register;

	/* Send the calculated 32-bit address to the target, LSB first */
	PDITarget_SendByte(Address &  0xFF);
	PDITarget_SendByte(Address >> 8);
	PDITarget_SendByte(Address >> 16);
	PDITarget_SendByte(Address >> 24);
}

/** Sends the given 32-bit absolute address to the target.
 *
 *  \param[in] AbsoluteAddress  Absolute address to send to the target
 */
void NVMTarget_SendAddress(uint32_t AbsoluteAddress)
{
	/* Send the given 32-bit address to the target, LSB first */
	PDITarget_SendByte(AbsoluteAddress &  0xFF);
	PDITarget_SendByte(AbsoluteAddress >> 8);
	PDITarget_SendByte(AbsoluteAddress >> 16);
	PDITarget_SendByte(AbsoluteAddress >> 24);
}

/** Waits while the target's NVM controller is busy performing an operation, exiting if the
 *  timeout period expires.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool NVMTarget_WaitWhileNVMControllerBusy(void)
{
	TCNT0 = 0;

	/* Poll the NVM STATUS register while the NVM controller is busy */
	while (TCNT0 < NVM_BUSY_TIMEOUT_MS)
	{
		/* Send a LDS command to read the NVM STATUS register to check the BUSY flag */
		PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_STATUS);
		
		/* Check to see if the BUSY flag is still set */
		if (!(PDITarget_ReceiveByte() & (1 << 7)))
		  return true;
	}
	
	return false;
}

/** Retrieves the CRC value of the given memory space.
 *
 *  \param[in]  CRCCommand  NVM CRC command to issue to the target
 *  \param[out] CRCDest     CRC Destination when read from the target
 *
 *  \return Boolean true if the command sequence complete sucessfully
 */
bool NVMTarget_GetMemoryCRC(uint8_t CRCCommand, uint32_t* CRCDest)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;
	  
	/* Set the NVM command to the correct CRC read command */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(CRCCommand);

	/* Set CMDEX bit in NVM CTRLA register to start the CRC generation */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CTRLA);
	PDITarget_SendByte(1 << 0);

	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;
	
	*CRCDest = 0;
	
	/* Read the first generated CRC byte value */
	PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_DAT0);
	*CRCDest  = PDITarget_ReceiveByte();

	/* Read the second generated CRC byte value */
	PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_DAT1);
	*CRCDest |= ((uint16_t)PDITarget_ReceiveByte() << 8);

	/* Read the third generated CRC byte value */
	PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_DAT2);
	*CRCDest |= ((uint32_t)PDITarget_ReceiveByte() << 16);
	
	return true;
}

/** Reads memory from the target's memory spaces.
 *
 *  \param[in]  ReadAddress  Start address to read from within the target's address space
 *  \param[out] ReadBuffer   Buffer to store read data into
 *  \param[in]  ReadSize     Number of bytes to read
 *
 *  \return Boolean true if the command sequence complete sucessfully
 */
bool NVMTarget_ReadMemory(uint32_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;
	
	/* Send the READNVM command to the NVM controller for reading of an aribtrary location */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(NVM_CMD_READNVM);

	/* Send the address of the first location to read from - this also primes the internal address
	 * counters so that we can use the REPEAT command later to save on overhead for multiple bytes */
	PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendAddress(ReadAddress);
	*ReadBuffer = PDITarget_ReceiveByte();

	/* Check to see if we are reading more than a single byte */
	if (ReadSize > 1)
	{
		/* Send the REPEAT command with the specified number of bytes remaining to read */
		PDITarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_2BYTES);
		PDITarget_SendByte(ReadSize &  0xFF);
		PDITarget_SendByte(ReadSize >> 8);
		
		/* Send a LD command with indirect access and postincrement to read out the remaining bytes */
		PDITarget_SendByte(PDI_CMD_LD | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
		for (uint16_t i = 0; i < ReadSize; i++)
		  *(ReadBuffer++) = PDITarget_ReceiveByte();
	}
	
	return true;
}

/** Erases a specific memory space of the target.
 *
 *  \param[in] EraseCommand  NVM erase command to send to the device
 *  \param[in] Address  Address inside the memory space to erase
 *
 *  \return Boolean true if the command sequence complete sucessfully
 */
bool NVMTarget_EraseMemory(uint8_t EraseCommand, uint32_t Address)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;
	  
	/* Send the memory erase command to the target */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(EraseCommand);
	
	/* Chip erase is handled seperately, since it's procedure is different to other erase types */
	if (EraseCommand == NVM_CMD_CHIPERASE)
	{
		/* Set CMDEX bit in NVM CTRLA register to start the chip erase */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_CTRLA);
		PDITarget_SendByte(1 << 0);		
	}
	else
	{
		/* Other erase modes just need us to address a byte within the target memory space */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendAddress(Address);	
		PDITarget_SendByte(0x00);
	}
	
	/* Wait until the NVM bus is ready again */
	if (!(PDITarget_WaitWhileNVMBusBusy()))
	  return false;
	  
	return true;
}

#endif
