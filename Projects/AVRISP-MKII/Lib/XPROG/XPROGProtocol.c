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
 *  XPROG Protocol handler, to process V2 Protocol wrapped XPROG commands used in Atmel programmer devices.
 */

#define  INCLUDE_FROM_XPROGPROTOCOL_C
#include "XPROGProtocol.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)
/** Base absolute address for the target's NVM controller for PDI programming */
uint32_t XPROG_Param_NVMBase = 0x010001C0;

/** Size in bytes of the target's EEPROM page */
uint16_t XPROG_Param_EEPageSize;

/** Address of the TPI device's NVMCMD register for TPI programming */
uint8_t  XPROG_Param_NVMCMDRegAddr;

/** Address of the TPI device's NVMCSR register for TPI programming */
uint8_t  XPROG_Param_NVMCSRRegAddr;

/** Currently selected XPROG programming protocol */
uint8_t  XPROG_SelectedProtocol = XPRG_PROTOCOL_PDI;

/** Handler for the CMD_XPROG_SETMODE command, which sets the programmer-to-target protocol used for PDI/TPI
 *  programming.
 */
void XPROGProtocol_SetMode(void)
{
	struct
	{
		uint8_t Protocol;
	} SetMode_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&SetMode_XPROG_Params, sizeof(SetMode_XPROG_Params), NO_STREAM_CALLBACK);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	XPROG_SelectedProtocol = SetMode_XPROG_Params.Protocol;
	
	Endpoint_Write_Byte(CMD_XPROG_SETMODE);
	Endpoint_Write_Byte((SetMode_XPROG_Params.Protocol != XPRG_PROTOCOL_JTAG) ? STATUS_CMD_OK : STATUS_CMD_FAILED);
	Endpoint_ClearIN();	
}

/** Handler for the CMD_XPROG command, which wraps up XPROG commands in a V2 wrapper which need to be
 *  removed and processed so that the underlying XPROG command can be handled.
 */
void XPROGProtocol_Command(void)
{
	uint8_t XPROGCommand = Endpoint_Read_Byte();
	
	switch (XPROGCommand)
	{
		case XPRG_CMD_ENTER_PROGMODE:
			XPROGProtocol_EnterXPROGMode();
			break;
		case XPRG_CMD_LEAVE_PROGMODE:
			XPROGProtocol_LeaveXPROGMode();
			break;
		case XPRG_CMD_ERASE:
			XPROGProtocol_Erase();
			break;
		case XPRG_CMD_WRITE_MEM:
			XPROGProtocol_WriteMemory();
			break;
		case XPRG_CMD_READ_MEM:
			XPROGProtocol_ReadMemory();
			break;
		case XPRG_CMD_CRC:
			XPROGProtocol_ReadCRC();
			break;
		case XPRG_CMD_SET_PARAM:
			XPROGProtocol_SetParam();
			break;
	}
}

/** Handler for the XPROG ENTER_PROGMODE command to establish a connection with the attached device. */
static void XPROGProtocol_EnterXPROGMode(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	bool NVMBusEnabled;

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		/* Enable PDI programming mode with the attached target */
		XPROGTarget_EnableTargetPDI();
		
		/* Store the RESET key into the RESET PDI register to keep the XMEGA in reset */
		XPROGTarget_SendByte(PDI_CMD_STCS | PDI_RESET_REG);	
		XPROGTarget_SendByte(PDI_RESET_KEY);

		/* Lower direction change guard time to 0 USART bits */
		XPROGTarget_SendByte(PDI_CMD_STCS | PDI_CTRL_REG);	
		XPROGTarget_SendByte(0x07);

		/* Enable access to the XPROG NVM bus by sending the documented NVM access key to the device */
		XPROGTarget_SendByte(PDI_CMD_KEY);	
		for (uint8_t i = sizeof(PDI_NVMENABLE_KEY); i > 0; i--)
		  XPROGTarget_SendByte(PDI_NVMENABLE_KEY[i - 1]);

		/* Wait until the NVM bus becomes active */
		NVMBusEnabled = XMEGANVM_WaitWhileNVMBusBusy();
	}
	else
	{
		/* Enable TPI programming mode with the attached target */
		XPROGTarget_EnableTargetTPI();
		
		/* Lower direction change guard time to 0 USART bits */
		XPROGTarget_SendByte(TPI_CMD_SSTCS | TPI_CTRL_REG);
		XPROGTarget_SendByte(0x07);
		
		/* Enable access to the XPROG NVM bus by sending the documented NVM access key to the device */
		XPROGTarget_SendByte(TPI_CMD_SKEY);	
		for (uint8_t i = sizeof(TPI_NVMENABLE_KEY); i > 0; i--)
		  XPROGTarget_SendByte(TPI_NVMENABLE_KEY[i - 1]);

		/* Wait until the NVM bus becomes active */
		NVMBusEnabled = TINYNVM_WaitWhileNVMBusBusy();
	}
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_ENTER_PROGMODE);
	Endpoint_Write_Byte(NVMBusEnabled ? XPRG_ERR_OK : XPRG_ERR_FAILED);
	Endpoint_ClearIN();
}

/** Handler for the XPROG LEAVE_PROGMODE command to terminate the PDI programming connection with
 *  the attached device.
 */
static void XPROGProtocol_LeaveXPROGMode(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		/* Clear the RESET key in the RESET PDI register to allow the XMEGA to run */
		XPROGTarget_SendByte(PDI_CMD_STCS | PDI_RESET_REG);	
		XPROGTarget_SendByte(0x00);

		XPROGTarget_DisableTargetPDI();
	}
	else
	{
		/* Clear the NVMEN bit in the TPI CONTROL register to disable TPI mode */
		XPROGTarget_SendByte(TPI_CMD_SSTCS | TPI_CTRL_REG);	
		XPROGTarget_SendByte(0x00);
	
		XPROGTarget_DisableTargetTPI();
	}
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_LEAVE_PROGMODE);
	Endpoint_Write_Byte(XPRG_ERR_OK);
	Endpoint_ClearIN();
}

/** Handler for the XPRG ERASE command to erase a specific memory address space in the attached device. */
static void XPROGProtocol_Erase(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint32_t Address;
	} Erase_XPROG_Params;

	Endpoint_Read_Stream_LE(&Erase_XPROG_Params, sizeof(Erase_XPROG_Params), NO_STREAM_CALLBACK);
	Erase_XPROG_Params.Address = SwapEndian_32(Erase_XPROG_Params.Address);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	uint8_t EraseCommand;

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{	
		/* Determine which NVM command to send to the device depending on the memory to erase */
		switch (Erase_XPROG_Params.MemoryType)
		{
			case XPRG_ERASE_CHIP:
				EraseCommand = XMEGA_NVM_CMD_CHIPERASE;
				break;
			case XPRG_ERASE_APP:
				EraseCommand = XMEGA_NVM_CMD_ERASEAPPSEC;
				break;
			case XPRG_ERASE_BOOT:
				EraseCommand = XMEGA_NVM_CMD_ERASEBOOTSEC;
				break;
			case XPRG_ERASE_EEPROM:
				EraseCommand = XMEGA_NVM_CMD_ERASEEEPROM;
				break;
			case XPRG_ERASE_APP_PAGE:
				EraseCommand = XMEGA_NVM_CMD_ERASEAPPSECPAGE;
				break;
			case XPRG_ERASE_BOOT_PAGE:
				EraseCommand = XMEGA_NVM_CMD_ERASEBOOTSECPAGE;
				break;
			case XPRG_ERASE_EEPROM_PAGE:
				EraseCommand = XMEGA_NVM_CMD_ERASEEEPROMPAGE;
				break;
			case XPRG_ERASE_USERSIG:
				EraseCommand = XMEGA_NVM_CMD_ERASEUSERSIG;
				break;
			default:
				EraseCommand = XMEGA_NVM_CMD_NOOP;
				break;
		}
		
		/* Erase the target memory, indicate timeout if ocurred */
		if (!(XMEGANVM_EraseMemory(EraseCommand, Erase_XPROG_Params.Address)))
		  ReturnStatus = XPRG_ERR_TIMEOUT;
	}
	else
	{
		if (Erase_XPROG_Params.MemoryType == XPRG_ERASE_CHIP)
		  EraseCommand = TINY_NVM_CMD_CHIPERASE;
		else
		  EraseCommand = TINY_NVM_CMD_SECTIONERASE;
	
		/* Erase the target memory, indicate timeout if ocurred */
		if (!(TINYNVM_EraseMemory(EraseCommand, Erase_XPROG_Params.Address)))
		  ReturnStatus = XPRG_ERR_TIMEOUT;
	}
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_ERASE);
	Endpoint_Write_Byte(ReturnStatus);
	Endpoint_ClearIN();	
}

/** Handler for the XPROG WRITE_MEMORY command to write to a specific memory space within the attached device. */
static void XPROGProtocol_WriteMemory(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint8_t  PageMode;
		uint32_t Address;
		uint16_t Length;
		uint8_t  ProgData[256];
	} WriteMemory_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&WriteMemory_XPROG_Params, (sizeof(WriteMemory_XPROG_Params) -
	                                                    sizeof(WriteMemory_XPROG_Params).ProgData), NO_STREAM_CALLBACK);
	WriteMemory_XPROG_Params.Address = SwapEndian_32(WriteMemory_XPROG_Params.Address);
	WriteMemory_XPROG_Params.Length  = SwapEndian_16(WriteMemory_XPROG_Params.Length);
	Endpoint_Read_Stream_LE(&WriteMemory_XPROG_Params.ProgData, WriteMemory_XPROG_Params.Length, NO_STREAM_CALLBACK);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		/* Assume FLASH page programming by default, as it is the common case */
		uint8_t WriteCommand     = XMEGA_NVM_CMD_WRITEFLASHPAGE;
		uint8_t WriteBuffCommand = XMEGA_NVM_CMD_LOADFLASHPAGEBUFF;
		uint8_t EraseBuffCommand = XMEGA_NVM_CMD_ERASEFLASHPAGEBUFF;
		bool    PagedMemory      = true;
		
		switch (WriteMemory_XPROG_Params.MemoryType)
		{
			case XPRG_MEM_TYPE_APPL:
				WriteCommand     = XMEGA_NVM_CMD_WRITEAPPSECPAGE;
				break;
			case XPRG_MEM_TYPE_BOOT:
				WriteCommand     = XMEGA_NVM_CMD_WRITEBOOTSECPAGE;
				break;
			case XPRG_MEM_TYPE_EEPROM:
				WriteCommand     = XMEGA_NVM_CMD_WRITEEEPROMPAGE;
				WriteBuffCommand = XMEGA_NVM_CMD_LOADEEPROMPAGEBUFF;
				EraseBuffCommand = XMEGA_NVM_CMD_ERASEEEPROMPAGEBUFF;			
				break;
			case XPRG_MEM_TYPE_USERSIG:
				/* User signature is paged, but needs us to manually indicate the mode bits since the host doesn't set them */
				WriteMemory_XPROG_Params.PageMode = (XPRG_PAGEMODE_ERASE | XPRG_PAGEMODE_WRITE);
				WriteCommand     = XMEGA_NVM_CMD_WRITEUSERSIG;
				break;
			case XPRG_MEM_TYPE_FUSE:
				WriteCommand     = XMEGA_NVM_CMD_WRITEFUSE;
				PagedMemory      = false;
				break;
			case XPRG_MEM_TYPE_LOCKBITS:
				WriteCommand     = XMEGA_NVM_CMD_WRITELOCK;
				PagedMemory      = false;
				break;
		}
		
		/* Send the appropriate memory write commands to the device, indicate timeout if occurred */
		if ((PagedMemory && !(XMEGANVM_WritePageMemory(WriteBuffCommand, EraseBuffCommand, WriteCommand, 
													   WriteMemory_XPROG_Params.PageMode, WriteMemory_XPROG_Params.Address,
													   WriteMemory_XPROG_Params.ProgData, WriteMemory_XPROG_Params.Length))) ||
		   (!PagedMemory && !(XMEGANVM_WriteByteMemory(WriteCommand, WriteMemory_XPROG_Params.Address,
													   WriteMemory_XPROG_Params.ProgData[0]))))
		{
			ReturnStatus = XPRG_ERR_TIMEOUT;
		}
	}
	else
	{
		/* Send write command to the TPI device, indicate timeout if occurred */
		if (!(TINYNVM_WriteMemory(WriteMemory_XPROG_Params.Address, WriteMemory_XPROG_Params.ProgData,
		      WriteMemory_XPROG_Params.Length)))
		{
			ReturnStatus = XPRG_ERR_TIMEOUT;
		}
	}
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_WRITE_MEM);
	Endpoint_Write_Byte(ReturnStatus);	
	Endpoint_ClearIN();
}

/** Handler for the XPROG READ_MEMORY command to read data from a specific address space within the
 *  attached device.
 */
static void XPROGProtocol_ReadMemory(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint32_t Address;
		uint16_t Length;
	} ReadMemory_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&ReadMemory_XPROG_Params, sizeof(ReadMemory_XPROG_Params), NO_STREAM_CALLBACK);
	ReadMemory_XPROG_Params.Address = SwapEndian_32(ReadMemory_XPROG_Params.Address);
	ReadMemory_XPROG_Params.Length  = SwapEndian_16(ReadMemory_XPROG_Params.Length);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t ReadBuffer[256];
	
	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		/* Read the PDI target's memory, indicate timeout if occurred */
		if (!(XMEGANVM_ReadMemory(ReadMemory_XPROG_Params.Address, ReadBuffer, ReadMemory_XPROG_Params.Length)))
		  ReturnStatus = XPRG_ERR_TIMEOUT;
	}
	else
	{
		/* Read the TPI target's memory, indicate timeout if occurred */
		if (!(TINYNVM_ReadMemory(ReadMemory_XPROG_Params.Address, ReadBuffer, ReadMemory_XPROG_Params.Length)))
		  ReturnStatus = XPRG_ERR_TIMEOUT;
	}

	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_READ_MEM);
	Endpoint_Write_Byte(ReturnStatus);
	
	if (ReturnStatus == XPRG_ERR_OK)
	  Endpoint_Write_Stream_LE(ReadBuffer, ReadMemory_XPROG_Params.Length, NO_STREAM_CALLBACK);
	
	Endpoint_ClearIN();
}

/** Handler for the XPROG CRC command to read a specific memory space's CRC value for comparison between the
 *  attached device's memory and a data set on the host.
 */
static void XPROGProtocol_ReadCRC(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;
	
	struct
	{
		uint8_t CRCType;
	} ReadCRC_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&ReadCRC_XPROG_Params, sizeof(ReadCRC_XPROG_Params), NO_STREAM_CALLBACK);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	uint32_t MemoryCRC;

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		uint8_t CRCCommand;

		/* Determine which NVM command to send to the device depending on the memory to CRC */
		switch (ReadCRC_XPROG_Params.CRCType)
		{
			case XPRG_CRC_APP:
				CRCCommand = XMEGA_NVM_CMD_APPCRC;
				break;
			case XPRG_CRC_BOOT:
				CRCCommand = XMEGA_NVM_CMD_BOOTCRC;
				break;
			default:
				CRCCommand = XMEGA_NVM_CMD_FLASHCRC;
				break;
		}
		
		/* Perform and retrieve the memory CRC, indicate timeout if occurred */
		if (!(XMEGANVM_GetMemoryCRC(CRCCommand, &MemoryCRC)))
		  ReturnStatus = XPRG_ERR_TIMEOUT;
	}
	else
	{
		/* TPI does not support memory CRC */
		ReturnStatus = XPRG_ERR_FAILED;
	}
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_CRC);
	Endpoint_Write_Byte(ReturnStatus);
	
	if (ReturnStatus == XPRG_ERR_OK)
	{
		Endpoint_Write_Byte(MemoryCRC >> 16);
		Endpoint_Write_Word_LE(MemoryCRC & 0xFFFF);		
	}
	
	Endpoint_ClearIN();	
}

/** Handler for the XPROG SET_PARAM command to set a XPROG parameter for use when communicating with the
 *  attached device.
 */
static void XPROGProtocol_SetParam(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	uint8_t XPROGParam = Endpoint_Read_Byte();
	
	/* Determine which parameter is being set, store the new parameter value */
	switch (XPROGParam)
	{
		case XPRG_PARAM_NVMBASE:
			XPROG_Param_NVMBase = Endpoint_Read_DWord_BE();
			break;
		case XPRG_PARAM_EEPPAGESIZE:
			XPROG_Param_EEPageSize = Endpoint_Read_Word_BE();
			break;
		case XPRG_PARAM_NVMCMD_REG:
			XPROG_Param_NVMCMDRegAddr = Endpoint_Read_Byte();
			break;
		case XPRG_PARAM_NVMCSR_REG:
			XPROG_Param_NVMCSRRegAddr = Endpoint_Read_Byte();
			break;
		default:
			ReturnStatus = XPRG_ERR_FAILED;
			break;
	}

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
		  
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_SET_PARAM);
	Endpoint_Write_Byte(ReturnStatus);
	Endpoint_ClearIN();
}

#endif
