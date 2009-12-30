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
#warning TPI Protocol support is currently incomplete and is not suitable for general use.

/** Sends the given pointer address to the target's TPI pointer register */
void TINYNVM_SendPointerAddress(const uint16_t AbsoluteAddress)
{
	/* Send the given 16-bit address to the target, LSB first */
	XPROGTarget_SendByte(TPI_CMD_SSTPR | 0);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[0]);
	XPROGTarget_SendByte(TPI_CMD_SSTPR | 1);
	XPROGTarget_SendByte(((uint8_t*)&AbsoluteAddress)[1]);
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
		/* Send the SIN command to read the TPI STATUS register to see the NVM bus is active */
		XPROGTarget_SendByte(TPI_CMD_SIN | XPROG_Param_NVMCSRRegAddr);
		if (XPROGTarget_ReceiveByte() & (1 << 7))
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
bool TINYNVM_ReadMemory(const uint32_t ReadAddress, uint8_t* ReadBuffer, uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM control register to the NO OP command for memory reading */
	XPROGTarget_SendByte(TPI_CMD_SOUT | XPROG_Param_NVMCMDRegAddr);
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

/** Writes byte addressed memory to the target's memory spaces.
 *
 *  \param[in]  WriteAddress  Start address to write to within the target's address space
 *  \param[in]  WriteBuffer   Buffer to source data from
 *  \param[in]  WriteLength   Total number of bytes to write to the device
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_WriteMemory(const uint32_t WriteAddress, const uint8_t* WriteBuffer, uint16_t WriteLength)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM control register to the WORD WRITE command for memory reading */
	XPROGTarget_SendByte(TPI_CMD_SOUT | XPROG_Param_NVMCMDRegAddr);
	XPROGTarget_SendByte(TINY_NVM_CMD_WORDWRITE);
	
	/* Send the address of the location to write to */
	TINYNVM_SendPointerAddress(WriteAddress);
	
	while (WriteLength--)
	{
		/* Write the byte of data to the target */
		XPROGTarget_SendByte(TPI_CMD_SST | TPI_POINTER_INDIRECT_PI);
		XPROGTarget_SendByte(*(WriteBuffer++));
	}
	
	return true;
}

/** Erases the target's memory space.
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_EraseMemory(void)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(TINYNVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM control register to the CHIP ERASE command to erase the target */
	XPROGTarget_SendByte(TPI_CMD_SOUT | XPROG_Param_NVMCMDRegAddr);
	XPROGTarget_SendByte(TINY_NVM_CMD_CHIPERASE);	

	/* Wait until the NVM bus is ready again */
	if (!(TINYNVM_WaitWhileNVMBusBusy()))
	  return false;
	
	return true;
}

#endif
