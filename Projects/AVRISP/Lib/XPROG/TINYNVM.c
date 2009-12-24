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
 *  Target-related functions for the TINY target's NVM module.
 */

#define  INCLUDE_FROM_TINYNVM_C
#include "TINYNVM.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Busy-waits while the NVM controller is busy performing a NVM operation, such as a FLASH page read.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool TINYNVM_WaitWhileNVMBusBusy(void)
{
	TCNT0 = 0;
	TIFR0 = (1 << OCF1A);
			
	uint8_t TimeoutMS = TINY_NVM_BUSY_TIMEOUT_MS;
	
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (TimeoutMS)
	{
		/* Send the SLDCS command to read the TPI STATUS register to see the NVM bus is active */
		XPROGTarget_SendByte(TPI_CMD_SLDCS | TPI_STATUS_REG);
		if (XPROGTarget_ReceiveByte() & TPI_STATUS_NVM)
		  return true;

		if (TIFR0 & (1 << OCF1A))
		{
			TIFR0 = (1 << OCF1A);
			TimeoutMS--;
		}
	}
	
	return false;
}

/** Reads memory from the target's memory spaces.
 *
 *  \param[in]  ReadAddress  Start address to read from within the target's address space
 *  \param[out] ReadBuffer   Buffer to store read data into
 *  \param[in]  ReadSize     Number of bytes to read
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_ReadMemory(const uint32_t ReadAddress, uint8_t* ReadBuffer, const uint16_t ReadSize)
{
	// TODO
	
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
bool TINYNVM_WriteMemory(const uint8_t WriteCommand, const uint32_t WriteAddress, const uint8_t* WriteBuffer)
{
	// TODO
	
	return true;
}

/** Erases a specific memory space of the target.
 *
 *  \param[in] EraseCommand  NVM erase command to send to the device
 *  \param[in] Address  Address inside the memory space to erase
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_EraseMemory(const uint8_t EraseCommand, const uint32_t Address)
{
	// TODO
	
	return true;
}

#endif
