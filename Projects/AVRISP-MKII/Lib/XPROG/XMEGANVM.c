/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
	XPROGTarget_SendByte(AbsoluteAddress &  0xFF);
	XPROGTarget_SendByte(AbsoluteAddress >> 8);
	XPROGTarget_SendByte(AbsoluteAddress >> 16);
	XPROGTarget_SendByte(AbsoluteAddress >> 24);
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
 *  \return Boolean \c true if the NVM controller became ready within the timeout period, \c false otherwise
 */
bool XMEGANVM_WaitWhileNVMBusBusy(void)
{
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	for (;;)
	{
		/* Send the LDCS command to read the PDI STATUS register to see the NVM bus is active */
		XPROGTarget_SendByte(PDI_CMD_LDCS(PDI_REG_STATUS));

		uint8_t StatusRegister = XPROGTarget_ReceiveByte();

		/* We might have timed out waiting for the status register read response, check here */
		if (!(TimeoutTicksRemaining))
		  return false;

		/* Check the status register read response to see if the NVM bus is enabled */
		if (StatusRegister & PDI_STATUS_NVM)
		  return true;
	}
}

/** Waits while the target's NVM controller is busy performing an operation, exiting if the
 *  timeout period expires.
 *
 *  \return Boolean \c true if the NVM controller became ready within the timeout period, \c false otherwise
 */
bool XMEGANVM_WaitWhileNVMControllerBusy(void)
{
	/* Preload the pointer register with the NVM STATUS register address to check the BUSY flag */
	XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_DIRECT, PDI_DATASIZE_4BYTES));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_STATUS);

	/* Poll the NVM STATUS register while the NVM controller is busy */
	for (;;)
	{
		/* Fetch the current status value via the pointer register (without auto-increment afterwards) */
		XPROGTarget_SendByte(PDI_CMD_LD(PDI_POINTER_INDIRECT, PDI_DATASIZE_1BYTE));

		uint8_t StatusRegister = XPROGTarget_ReceiveByte();

		/* We might have timed out waiting for the status register read response, check here */
		if (!(TimeoutTicksRemaining))
		  return false;

		/* Check to see if the BUSY flag is still set */
		if (!(StatusRegister & (1 << 7)))
		  return true;
	}
}

/** Enables the physical PDI interface on the target and enables access to the internal NVM controller.
 *
 *  \return Boolean \c true if the PDI interface was enabled successfully, \c false otherwise
 */
bool XMEGANVM_EnablePDI(void)
{
	/* Enable PDI programming mode with the attached target */
	XPROGTarget_EnableTargetPDI();

	/* Store the RESET key into the RESET PDI register to keep the XMEGA in reset */
	XPROGTarget_SendByte(PDI_CMD_STCS(PDI_REG_RESET));
	XPROGTarget_SendByte(PDI_RESET_KEY);

	/* Lower direction change guard time to 32 USART bits */
	XPROGTarget_SendByte(PDI_CMD_STCS(PDI_REG_CTRL));
	XPROGTarget_SendByte(0x02);

	/* Enable access to the XPROG NVM bus by sending the documented NVM access key to the device */
	XPROGTarget_SendByte(PDI_CMD_KEY);
	for (uint8_t i = sizeof(PDI_NVMENABLE_KEY); i > 0; i--)
	  XPROGTarget_SendByte(PDI_NVMENABLE_KEY[i - 1]);

	/* Wait until the NVM bus becomes active */
	return XMEGANVM_WaitWhileNVMBusBusy();
}

/** Removes access to the target's NVM controller and physically disables the target's physical PDI interface. */
void XMEGANVM_DisablePDI(void)
{
	XMEGANVM_WaitWhileNVMBusBusy();

	/* Clear the RESET key in the RESET PDI register to allow the XMEGA to run - must perform this until the
	 * change takes effect, as in some cases it takes multiple writes (silicon bug?).
	 */
	do
	{
		/* Clear reset register */
		XPROGTarget_SendByte(PDI_CMD_STCS(PDI_REG_RESET));
		XPROGTarget_SendByte(0x00);

		/* Read back the reset register, check to see if it took effect */
		XPROGTarget_SendByte(PDI_CMD_LDCS(PDI_REG_RESET));
	} while (XPROGTarget_ReceiveByte() != 0x00);

	XPROGTarget_DisableTargetPDI();
}

/** Retrieves the CRC value of the given memory space.
 *
 *  \param[in]  CRCCommand  NVM CRC command to issue to the target
 *  \param[out] CRCDest     CRC Destination when read from the target
 *
 *  \return Boolean \c true if the command sequence complete successfully
 */
bool XMEGANVM_GetMemoryCRC(const uint8_t CRCCommand,
                           uint32_t* const CRCDest)
{
	*CRCDest = 0;

	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Set the NVM command to the correct CRC read command */
	XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(CRCCommand);

	/* Set CMDEX bit in NVM CTRLA register to start the CRC generation */
	XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
	XPROGTarget_SendByte(XMEGA_NVM_BIT_CTRLA_CMDEX);

	/* Wait until the NVM bus is ready again */
	if (!(XMEGANVM_WaitWhileNVMBusBusy()))
	  return false;

	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Load the PDI pointer register with the DAT0 register start address */
	XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_DIRECT, PDI_DATASIZE_4BYTES));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_DAT0);

	/* Send the REPEAT command to grab the CRC bytes */
	XPROGTarget_SendByte(PDI_CMD_REPEAT(PDI_DATASIZE_1BYTE));
	XPROGTarget_SendByte(XMEGA_CRC_LENGTH_BYTES - 1);

	/* Read in the CRC bytes from the target */
	XPROGTarget_SendByte(PDI_CMD_LD(PDI_POINTER_INDIRECT_PI, PDI_DATASIZE_1BYTE));
	for (uint8_t i = 0; i < XMEGA_CRC_LENGTH_BYTES; i++)
	  ((uint8_t*)CRCDest)[i] = XPROGTarget_ReceiveByte();

	return (TimeoutTicksRemaining > 0);
}

/** Reads memory from the target's memory spaces.
 *
 *  \param[in]  ReadAddress  Start address to read from within the target's address space
 *  \param[out] ReadBuffer   Buffer to store read data into
 *  \param[in]  ReadSize     Number of bytes to read
 *
 *  \return Boolean \c true if the command sequence complete successfully
 */
bool XMEGANVM_ReadMemory(const uint32_t ReadAddress,
                         uint8_t* ReadBuffer,
                         uint16_t ReadSize)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Send the READNVM command to the NVM controller for reading of an arbitrary location */
	XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(XMEGA_NVM_CMD_READNVM);

	if (ReadSize > 1)
	{
		/* Load the PDI pointer register with the start address we want to read from */
		XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_DIRECT, PDI_DATASIZE_4BYTES));
		XMEGANVM_SendAddress(ReadAddress);

		/* Send the REPEAT command with the specified number of bytes to read */
		XPROGTarget_SendByte(PDI_CMD_REPEAT(PDI_DATASIZE_1BYTE));
		XPROGTarget_SendByte(ReadSize - 1);

		/* Send a LD command with indirect access and post-increment to read out the bytes */
		XPROGTarget_SendByte(PDI_CMD_LD(PDI_POINTER_INDIRECT_PI, PDI_DATASIZE_1BYTE));
		while (ReadSize-- && TimeoutTicksRemaining)
		  *(ReadBuffer++) = XPROGTarget_ReceiveByte();
	}
	else
	{
		/* Send a LDS command with the read address to read out the requested byte */
		XPROGTarget_SendByte(PDI_CMD_LDS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendAddress(ReadAddress);
		*(ReadBuffer++) = XPROGTarget_ReceiveByte();
	}

	return (TimeoutTicksRemaining > 0);
}

/** Writes byte addressed memory to the target's memory spaces.
 *
 *  \param[in]  WriteCommand  Command to send to the device to write each memory byte
 *  \param[in]  WriteAddress  Address to write to within the target's address space
 *  \param[in]  Byte          Byte to write to the target
 *
 *  \return Boolean \c true if the command sequence complete successfully
 */
bool XMEGANVM_WriteByteMemory(const uint8_t WriteCommand,
                              const uint32_t WriteAddress,
                              const uint8_t Byte)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* Send the memory write command to the target */
	XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
	XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
	XPROGTarget_SendByte(WriteCommand);

	/* Send new memory byte to the memory of the target */
	XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
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
 *  \return Boolean \c true if the command sequence complete successfully
 */
bool XMEGANVM_WritePageMemory(const uint8_t WriteBuffCommand,
                              const uint8_t EraseBuffCommand,
                              const uint8_t WritePageCommand,
                              const uint8_t PageMode,
                              const uint32_t WriteAddress,
                              const uint8_t* WriteBuffer,
                              uint16_t WriteSize)
{
	if (PageMode & XPROG_PAGEMODE_ERASE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(EraseBuffCommand);

		/* Set CMDEX bit in NVM CTRLA register to start the buffer erase */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(XMEGA_NVM_BIT_CTRLA_CMDEX);
	}

	if (WriteSize)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory buffer write command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(WriteBuffCommand);

		/* Load the PDI pointer register with the start address we want to write to */
		XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_DIRECT, PDI_DATASIZE_4BYTES));
		XMEGANVM_SendAddress(WriteAddress);

		/* Send the REPEAT command with the specified number of bytes to write */
		XPROGTarget_SendByte(PDI_CMD_REPEAT(PDI_DATASIZE_1BYTE));
		XPROGTarget_SendByte(WriteSize - 1);

		/* Send a ST command with indirect access and post-increment to write the bytes */
		XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_INDIRECT_PI, PDI_DATASIZE_1BYTE));
		while (WriteSize--)
		  XPROGTarget_SendByte(*(WriteBuffer++));
	}

	if (PageMode & XPROG_PAGEMODE_WRITE)
	{
		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the memory write command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(WritePageCommand);

		/* Send the address of the first page location to write the memory page */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendAddress(WriteAddress);
		XPROGTarget_SendByte(0x00);
	}

	return true;
}

/** Erases a specific memory space of the target.
 *
 *  \param[in] EraseCommand  NVM erase command to send to the device
 *  \param[in] Address       Address inside the memory space to erase
 *
 *  \return Boolean \c true if the command sequence complete successfully
 */
bool XMEGANVM_EraseMemory(const uint8_t EraseCommand,
                          const uint32_t Address)
{
	/* Wait until the NVM controller is no longer busy */
	if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
	  return false;

	/* EEPROM and Chip erasures are triggered differently to FLASH section erasures */
	if (EraseCommand == XMEGA_NVM_CMD_CHIPERASE)
	{
		/* Send the memory erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(EraseCommand);

		/* Set CMDEX bit in NVM CTRLA register to start the erase sequence */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(XMEGA_NVM_BIT_CTRLA_CMDEX);
	}
	else if (EraseCommand == XMEGA_NVM_CMD_ERASEEEPROM)
	{
		/* Send the EEPROM page buffer erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(XMEGA_NVM_CMD_ERASEEEPROMPAGEBUFF);

		/* Set CMDEX bit in NVM CTRLA register to start the buffer erase */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(XMEGA_NVM_BIT_CTRLA_CMDEX);

		/* Wait until the NVM controller is no longer busy */
		if (!(XMEGANVM_WaitWhileNVMControllerBusy()))
		  return false;

		/* Send the EEPROM memory buffer write command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(XMEGA_NVM_CMD_LOADEEPROMPAGEBUFF);

		/* Load the PDI pointer register with the EEPROM page start address */
		XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_DIRECT, PDI_DATASIZE_4BYTES));
		XMEGANVM_SendAddress(Address);

		/* Send the REPEAT command with the specified number of bytes to write */
		XPROGTarget_SendByte(PDI_CMD_REPEAT(PDI_DATASIZE_1BYTE));
		XPROGTarget_SendByte(XPROG_Param_EEPageSize - 1);

		/* Send a ST command with indirect access and post-increment to tag each byte in the EEPROM page buffer */
		XPROGTarget_SendByte(PDI_CMD_ST(PDI_POINTER_INDIRECT_PI, PDI_DATASIZE_1BYTE));
		for (uint8_t PageByte = 0; PageByte < XPROG_Param_EEPageSize; PageByte++)
		  XPROGTarget_SendByte(0x00);

		/* Send the memory erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(EraseCommand);

		/* Set CMDEX bit in NVM CTRLA register to start the EEPROM erase sequence */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CTRLA);
		XPROGTarget_SendByte(XMEGA_NVM_BIT_CTRLA_CMDEX);
	}
	else
	{
		/* Send the memory erase command to the target */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendNVMRegAddress(XMEGA_NVM_REG_CMD);
		XPROGTarget_SendByte(EraseCommand);

		/* Other erase modes just need us to address a byte within the target memory space */
		XPROGTarget_SendByte(PDI_CMD_STS(PDI_DATASIZE_4BYTES, PDI_DATASIZE_1BYTE));
		XMEGANVM_SendAddress(Address);
		XPROGTarget_SendByte(0x00);
	}

	/* Wait until the NVM bus is ready again */
	if (!(XMEGANVM_WaitWhileNVMBusBusy()))
	  return false;

	return true;
}

#endif

