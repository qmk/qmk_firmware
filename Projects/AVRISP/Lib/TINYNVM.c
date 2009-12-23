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

#if defined(ENABLE_TPI_PROTOCOL) || defined(__DOXYGEN__)

/** Sends the given NVM register address to the target.
 *
 *  \param[in] Register  NVM register whose absolute address is to be sent
 */
void TINYNVM_SendNVMRegAddress(const uint8_t Register)
{
	// TODO
}

/** Sends the given 32-bit absolute address to the target.
 *
 *  \param[in] AbsoluteAddress  Absolute address to send to the target
 */
void TINYNVM_SendAddress(const uint32_t AbsoluteAddress)
{
	// TODO
}

/** Waits while the target's NVM controller is busy performing an operation, exiting if the
 *  timeout period expires.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool TINYNVM_WaitWhileNVMControllerBusy(void)
{
	// TODO
	return false;
}

/** Retrieves the CRC value of the given memory space.
 *
 *  \param[in]  CRCCommand  NVM CRC command to issue to the target
 *  \param[out] CRCDest     CRC Destination when read from the target
 *
 *  \return Boolean true if the command sequence complete successfully
 */
bool TINYNVM_GetMemoryCRC(const uint8_t CRCCommand, uint32_t* const CRCDest)
{
	// TODO
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
bool TINYNVM_WriteByteMemory(const uint8_t WriteCommand, const uint32_t WriteAddress, const uint8_t* WriteBuffer)
{
	// TODO
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
bool TINYNVM_WritePageMemory(const uint8_t WriteBuffCommand, const uint8_t EraseBuffCommand,
                               const uint8_t WritePageCommand, const uint8_t PageMode, const uint32_t WriteAddress,
                               const uint8_t* WriteBuffer, const uint16_t WriteSize)
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
