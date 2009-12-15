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
 *  \return Boolean true if the command sequence complete successfully
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

	/* Wait until the NVM bus is ready again */
	if (!(PDITarget_WaitWhileNVMBusBusy()))
	  return false;

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
 *  \return Boolean true if the command sequence complete successfully
 */
bool NVMTarget_ReadMemory(uint32_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;
	
	/* Send the READNVM command to the NVM controller for reading of an arbitrary location */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(NVM_CMD_READNVM);

	/* Load the PDI pointer register with the start address we want to read from */
	PDITarget_SendByte(PDI_CMD_ST | (PDI_POINTER_DIRECT << 2) | PDI_DATSIZE_4BYTES);
	NVMTarget_SendAddress(ReadAddress);

	/* Send the REPEAT command with the specified number of bytes to read */
	PDITarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_1BYTE);
	PDITarget_SendByte(ReadSize - 1);
		
	/* Send a LD command with indirect access and postincrement to read out the bytes */
	PDITarget_SendByte(PDI_CMD_LD | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
	for (uint16_t i = 0; i < ReadSize; i++)
	  *(ReadBuffer++) = PDITarget_ReceiveByte();
	
	return true;
}

/** Writes byte addressed memory to the target's memory spaces.
 *
 *  \param[in]  WriteCommand  Command to send to the device to write each memory byte
 *  \param[in]  WriteAddress  Start address to write to within the target's address space
 *  \param[in]  WriteBuffer   Buffer to source data from
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool NVMTarget_WriteByteMemory(uint8_t WriteCommand, uint32_t WriteAddress, uint8_t* WriteBuffer)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(NVMTarget_WaitWhileNVMControllerBusy()))
	  return false;

	/* Send the memory write command to the target */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
	PDITarget_SendByte(WriteCommand);
	
	/* Send new memory byte to the memory to the target */
	PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	NVMTarget_SendAddress(WriteAddress++);
	PDITarget_SendByte(*(WriteBuffer++));
	
	return true;
}

/** Writes page addressed memory to the target's memory spaces.
 *
 *  \param[in]  WriteBuffCommand  Command to send to the device to write a byte to the memory page buffer
 *  \param[in]  EraseBuffCommand  Command to send to the device to erase the memory page buffer
 *  \param[in]  WritePageCommand  Command to send to the device to write the page buffer to the destination memory
 *  \param[in]  PageMode          Bitfield indicating what operations need to be executed on the specified page
 *  \param[in]  WriteAddress      Start address to write the page data to within the target's address space
 *  \param[in]  WriteBuffer       Buffer to source data from
 *  \param[in]  WriteSize         Number of bytes to write
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool NVMTarget_WritePageMemory(uint8_t WriteBuffCommand, uint8_t EraseBuffCommand, uint8_t WritePageCommand,
                               uint8_t PageMode, uint32_t WriteAddress, uint8_t* WriteBuffer, uint16_t WriteSize)
{
	if (PageMode & XPRG_PAGEMODE_ERASE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(NVMTarget_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer erase command to the target */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
		PDITarget_SendByte(EraseBuffCommand);

		/* Set CMDEX bit in NVM CTRLA register to start the buffer erase */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_CTRLA);
		PDITarget_SendByte(1 << 0);
	}

	if (WriteSize)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(NVMTarget_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer write command to the target */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
		PDITarget_SendByte(WriteBuffCommand);

		/* Load the PDI pointer register with the start address we want to write to */
		PDITarget_SendByte(PDI_CMD_ST | (PDI_POINTER_DIRECT << 2) | PDI_DATSIZE_4BYTES);
		NVMTarget_SendAddress(WriteAddress);

		/* Send the REPEAT command with the specified number of bytes to write */
		PDITarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_1BYTE);
		PDITarget_SendByte(WriteSize - 1);
			
		/* Send a ST command with indirect access and postincrement to write the bytes */
		PDITarget_SendByte(PDI_CMD_ST | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
		for (uint16_t i = 0; i < WriteSize; i++)
		  PDITarget_SendByte(*(WriteBuffer++));
	}
	
	if (PageMode & XPRG_PAGEMODE_WRITE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(NVMTarget_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory write command to the target */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendNVMRegAddress(NVM_REG_CMD);
		PDITarget_SendByte(WritePageCommand);
		
		/* Send the address of the first page location to write the memory page */
		PDITarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		NVMTarget_SendAddress(WriteAddress);
		PDITarget_SendByte(0x00);
	}

	return true;
}

/** Erases a specific memory space of the target.
 *
 *  \param[in] EraseCommand  NVM erase command to send to the device
 *  \param[in] Address  Address inside the memory space to erase
 *
 *  \return Boolean true if the command sequence complete successfully
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
	
	/* Chip erase is handled separately, since it's procedure is different to other erase types */
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
