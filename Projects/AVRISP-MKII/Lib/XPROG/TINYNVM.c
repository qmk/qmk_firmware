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
 *  Target-related functions for the TINY target's NVM module.
 */

#define  INCLUDE_FROM_TINYNVM_C
#include "TINYNVM.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Sends the given pointer address to the target's TPI pointer register */
static void TINYNVM_SendPointerAddress(const uint16_t AbsoluteAddress)
{
	/* Send the given 16-bit address to the target, LSB first */
	XPROGTarget_SendByte(TPI_CMD_SSTPR | 0);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[0]);
	XPROGTarget_SendByte(TPI_CMD_SSTPR | 1);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[1]);
}

/** Sends a SIN command to the target with the specified I/O address, ready for the data byte to be written.
 *
 *  \param[in] Address  6-bit I/O address to write to in the target's I/O memory space
 */
static void TINYNVM_SendReadNVMRegister(const uint8_t Address)
{
	/* The TPI command for reading from the I/O space uses strange addressing, where the I/O address's upper
	 * two bits of the 6-bit address are shifted left once */
	XPROGTarget_SendByte(TPI_CMD_SIN | ((Address & 0x30) << 1) | (Address & 0x0F));
}

/** Sends a SOUT command to the target with the specified I/O address, ready for the data byte to be read.
 *
 *  \param[in] Address  6-bit I/O address to read from in the target's I/O memory space
 */
static void TINYNVM_SendWriteNVMRegister(const uint8_t Address)
{
	/* The TPI command for writing to the I/O space uses weird addressing, where the I/O address's upper
	 * two bits of the 6-bit address are shifted left once */
	XPROGTarget_SendByte(TPI_CMD_SOUT | ((Address & 0x30) << 1) | (Address & 0x0F));
}

/** Busy-waits while the NVM controller is busy performing a NVM operation, such as a FLASH page read.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool TINYNVM_WaitWhileNVMBusBusy(void)
{
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (TimeoutMSRemaining)
	{
		/* Send the SLDCS command to read the TPI STATUS register to see the NVM bus is active */
		XPROGTarget_SendByte(TPI_CMD_SLDCS | TPI_STATUS_REG);
		if (XPROGTarget_ReceiveByte() & TPI_STATUS_NVM)
		  return true;
	}
	
	return false;
}

/** Waits while the target's NVM controller is busy performing an operation, exiting if the
 *  timeout period expires.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool TINYNVM_WaitWhileNVMControllerBusy(void)
{
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (TimeoutMSRemaining)
	{
		/* Send the SIN command to read the TPI STATUS register to see the NVM bus is busy */
		TINYNVM_SendReadNVMRegister(XPROG_Param_NVMCSRRegAddr);

		/* Check to see if the BUSY flag is still set */
		if (!(XPROGTarget_ReceiveByte() & (1 << 7)))
		  return true;
	}
	
	return false;
}

/** Reads memory from the target's memory spaces.
 *
 *  \param[in]  ReadAddress  Start address to read from within the target's address space
 *  \param[out] ReadBuffer   Buffer to store read data into
 *  \param[in]  ReadSize     Length of the data to read from the device
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_ReadMemory(const uint16_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM control register to the NO OP command for memory reading */
	TINYNVM_SendWriteNVMRegister(XPROG_Param_NVMCMDRegAddr);
	XPROGTarget_SendByte(TINY_NVM_CMD_NOOP);
	
	/* Send the address of the location to read from */
	TINYNVM_SendPointerAddress(ReadAddress);
	
	while (ReadSize--)
	{
		/* Read the byte of data from the target */
		XPROGTarget_SendByte(TPI_CMD_SLD | TPI_POINTER_INDIRECT_PI);
		*(ReadBuffer++) = XPROGTarget_ReceiveByte();
	}
	
	return true;
}

/** Writes word addressed memory to the target's memory spaces.
 *
 *  \param[in] WriteAddress  Start address to write to within the target's address space
 *  \param[in] WriteBuffer   Buffer to source data from
 *  \param[in] WriteLength   Total number of bytes to write to the device (must be an integer multiple of 2)
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_WriteMemory(const uint16_t WriteAddress, uint8_t* WriteBuffer, uint16_t WriteLength)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;
	  
	/* Must have an integer number of words to write - if extra byte, word-align via a dummy high byte */
	if (WriteLength & 0x01)
	  WriteBuffer[WriteLength++] = 0xFF;

	/* Set the NVM control register to the WORD WRITE command for memory reading */
	TINYNVM_SendWriteNVMRegister(XPROG_Param_NVMCMDRegAddr);
	XPROGTarget_SendByte(TINY_NVM_CMD_WORDWRITE);
	
	/* Send the address of the location to write to */
	TINYNVM_SendPointerAddress(WriteAddress);
	
	while (WriteLength)
	{
		/* Write the low byte of data to the target */
		XPROGTarget_SendByte(TPI_CMD_SST | TPI_POINTER_INDIRECT_PI);
		XPROGTarget_SendByte(*(WriteBuffer++));
		
		/* Write the high byte of data to the target */
		XPROGTarget_SendByte(TPI_CMD_SST | TPI_POINTER_INDIRECT_PI);
		XPROGTarget_SendByte(*(WriteBuffer++));

		/* Wait until the NVM controller is no longer busy */
		if (!(TINYNVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Need to decrement the write length twice, since we read out a whole word */
		WriteLength -= 2;
	}
	
	return true;
}

/** Erases the target's memory space.
 *
 *  \param[in] EraseCommand  NVM erase command to send to the device
 *  \param[in] Address       Address inside the memory space to erase
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_EraseMemory(const uint8_t EraseCommand, const uint16_t Address)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM control register to the target memory erase command */
	TINYNVM_SendWriteNVMRegister(XPROG_Param_NVMCMDRegAddr);
	XPROGTarget_SendByte(EraseCommand);

	/* Write to a high byte location within the target address space to start the erase process */
	TINYNVM_SendPointerAddress(Address | 0x0001);
	XPROGTarget_SendByte(TPI_CMD_SST | TPI_POINTER_INDIRECT);
	XPROGTarget_SendByte(0x00);

	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;
	
	return true;
}

#endif
