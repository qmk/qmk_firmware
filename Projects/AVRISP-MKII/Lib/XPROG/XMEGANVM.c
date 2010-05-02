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
 *  Target-related functions for the XMEGA target's NVM module.
 */

#define  INCLUDE_FROM_XMEGA_NVM_C
#include "XMEGANVM.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Sends the given 32-bit absolute address to the target.
 *
 *  \param[in] AbsoluteAddress  Absolute address to send to the target
 */
static void XMEGANVM_SendAddress(const uint32_t AbsoluteAddress)
{
	/* Send the given 32-bit address to the target, LSB first */
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[0]);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[1]);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[2]);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[3]);
}

/** Sends the given NVM register address to the target.
 *
 *  \param[in] Register  NVM register whose absolute address is to be sent
 */
static void XMEGANVM_SendNVMRegAddress(const uint8_t Register)
{
	/* Determine the absolute register address from the NVM base memory address and the NVM register address */
	uint32_t Address = XPROG_Param_NVMBase | Register;

	/* Send the calculated 32-bit address to the target, LSB first */
	XMEGANVM_SendAddress(Address);
}

/** Busy-waits while the NVM controller is busy performing a NVM operation, such as a FLASH page read or CRC
 *  calculation.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool XMEGANVM_WaitWhileNVMBusBusy(void)
{
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (TimeoutMSRemaining)
	{
		/* Send the LDCS command to read the PDI STATUS register to see the NVM bus is active */
		XPROGTarget_SendByte(PDI_CMD_LDCS | PDI_STATUS_REG);
		
		uint8_t StatusRegister = XPROGTarget_ReceiveByte();
		
		/* We might have timed out waiting for the status register read response, check here */
		if (!(TimeoutMSRemaining))
		  return false;
		
		/* Check the status register read response to see if the NVM bus is enabled */
		if (StatusRegister & PDI_STATUS_NVM)
		{
			TimeoutMSRemaining = COMMAND_TIMEOUT_MS;
			return true;
		}
	}
	
	return false;
}

/** Waits while the target's NVM controller is busy performing an operation, exiting if the
 *  timeout period expires.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool XMEGANVM_WaitWhileNVMControllerBusy(void)
{
	/* Poll the NVM STATUS register while the NVM controller is busy */
	while (TimeoutMSRemaining)
	{
		/* Send a LDS command to read the NVM STATUS register to check the BUSY flag */
		XPROGTarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_STATUS);
		
		uint8_t StatusRegister = XPROGTarget_ReceiveByte();

		/* We might have timed out waiting for the status register read response, check here */
		if (!(TimeoutMSRemaining))
		  return false;

		/* Check to see if the BUSY flag is still set */
		if (!(StatusRegister & (1 << 7)))
		{
			TimeoutMSRemaining = COMMAND_TIMEOUT_MS;
			return true;
		}
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
bool XMEGANVM_GetMemoryCRC(const uint8_t CRCCommand, uint32_t* const CRCDest)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;
	  
	/* Set the NVM command to the correct CRC read command */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(CRCCommand);

	/* Set CMDEX bit in NVM CTRLA register to start the CRC generation */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
	XPROGTarget_SendByte(1 << 0);

	/* Wait until the NVM bus is ready again */
	if (!(XMEGANVM_WaitWhileNVMBusBusy()))
	  return false;

	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;
	
	/* Load the PDI pointer register with the DAT0 register start address */
	XPROGTarget_SendByte(PDI_CMD_ST | (PDI_POINTER_DIRECT << 2) | PDI_DATSIZE_4BYTES);
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_DAT0);

	/* Send the REPEAT command to grab the CRC bytes */
	XPROGTarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_1BYTE);
	XPROGTarget_SendByte(XMEGA_CRC_LENGTH - 1);
	
	/* Read in the CRC bytes from the target */
	XPROGTarget_SendByte(PDI_CMD_LD | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
	for (uint8_t i = 0; i < XMEGA_CRC_LENGTH; i++)
	  ((uint8_t*)CRCDest)[i] = XPROGTarget_ReceiveByte();
	
	return (TimeoutMSRemaining != 0);
}

/** Reads memory from the target's memory spaces.
 *
 *  \param[in]  ReadAddress  Start address to read from within the target's address space
 *  \param[out] ReadBuffer   Buffer to store read data into
 *  \param[in]  ReadSize     Number of bytes to read
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool XMEGANVM_ReadMemory(const uint32_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;
	
	/* Send the READNVM command to the NVM controller for reading of an arbitrary location */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(XMEGA_NVM_CMD_READNVM);

	/* Load the PDI pointer register with the start address we want to read from */
	XPROGTarget_SendByte(PDI_CMD_ST | (PDI_POINTER_DIRECT << 2) | PDI_DATSIZE_4BYTES);
	XMEGANVM_SendAddress(ReadAddress);

	/* Send the REPEAT command with the specified number of bytes to read */
	XPROGTarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_1BYTE);
	XPROGTarget_SendByte(ReadSize - 1);
		
	/* Send a LD command with indirect access and postincrement to read out the bytes */
	XPROGTarget_SendByte(PDI_CMD_LD | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
	while (ReadSize-- && TimeoutMSRemaining)
	  *(ReadBuffer++) = XPROGTarget_ReceiveByte();
	
	return (TimeoutMSRemaining != 0);
}

/** Writes byte addressed memory to the target's memory spaces.
 *
 *  \param[in]  WriteCommand  Command to send to the device to write each memory byte
 *  \param[in]  WriteAddress  Address to write to within the target's address space
 *  \param[in]  Byte          Byte to write to the target
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool XMEGANVM_WriteByteMemory(const uint8_t WriteCommand, const uint32_t WriteAddress, const uint8_t Byte)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Send the memory write command to the target */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(WriteCommand);
	
	/* Send new memory byte to the memory to the target */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendAddress(WriteAddress);
	XPROGTarget_SendByte(Byte);
	
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
bool XMEGANVM_WritePageMemory(const uint8_t WriteBuffCommand, const uint8_t EraseBuffCommand,
                              const uint8_t WritePageCommand, const uint8_t PageMode, const uint32_t WriteAddress,
                              const uint8_t* WriteBuffer, uint16_t WriteSize)
{
	if (PageMode & XPRG_PAGEMODE_ERASE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(EraseBuffCommand);

		/* Set CMDEX bit in NVM CTRLA register to start the buffer erase */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(1 << 0);
	}

	if (WriteSize)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer write command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(WriteBuffCommand);

		/* Load the PDI pointer register with the start address we want to write to */
		XPROGTarget_SendByte(PDI_CMD_ST | (PDI_POINTER_DIRECT << 2) | PDI_DATSIZE_4BYTES);
		XMEGANVM_SendAddress(WriteAddress);

		/* Send the REPEAT command with the specified number of bytes to write */
		XPROGTarget_SendByte(PDI_CMD_REPEAT | PDI_DATSIZE_1BYTE);
		XPROGTarget_SendByte(WriteSize - 1);
			
		/* Send a ST command with indirect access and postincrement to write the bytes */
		XPROGTarget_SendByte(PDI_CMD_ST | (PDI_POINTER_INDIRECT_PI << 2) | PDI_DATSIZE_1BYTE);
		while (WriteSize--)
		  XPROGTarget_SendByte(*(WriteBuffer++));
	}
	
	if (PageMode & XPRG_PAGEMODE_WRITE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory write command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(WritePageCommand);
		
		/* Send the address of the first page location to write the memory page */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendAddress(WriteAddress);
		XPROGTarget_SendByte(0x00);
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
bool XMEGANVM_EraseMemory(const uint8_t EraseCommand, const uint32_t Address)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;
	  
	/* Send the memory erase command to the target */
	XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(EraseCommand);
	
	/* Chip erase is handled separately, since it's procedure is different to other erase types */
	if (EraseCommand == XMEGA_NVM_CMD_CHIPERASE)
	{
		/* Set CMDEX bit in NVM CTRLA register to start the chip erase */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(1 << 0);		
	}
	else
	{
		/* Other erase modes just need us to address a byte within the target memory space */
		XPROGTarget_SendByte(PDI_CMD_STS | (PDI_DATSIZE_4BYTES << 2));
		XMEGANVM_SendAddress(Address);
		XPROGTarget_SendByte(0x00);
	}
	
	/* Wait until the NVM bus is ready again */
	if (!(XMEGANVM_WaitWhileNVMBusBusy()))
	  return false;
	  
	return true;
}

#endif
