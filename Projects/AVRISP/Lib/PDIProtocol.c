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

#if defined(ENABLE_XPROG_PROTOCOL)

/** \file
 *
 *  PDI Protocol handler, to process V2 Protocol wrapped PDI commands used in Atmel programmer devices.
 */

#define  INCLUDE_FROM_XPROG_C
#include "PDIProtocol.h"

uint32_t XPROG_Param_NVMBase;
uint32_t XPROG_Param_EEPageSize;

/** Handler for the CMD_XPROG_SETMODE command, which sets the programmer-to-target protocol used for PDI
 *  XMEGA programming (either PDI or JTAG). Only PDI programming is supported.
 */
void PDIProtocol_XPROG_SetMode(void)
{
	struct
	{
		uint8_t Protocol;
	} SetMode_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&SetMode_XPROG_Params, sizeof(SetMode_XPROG_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(CMD_XPROG_SETMODE);
	Endpoint_Write_Byte(SetMode_XPROG_Params.Protocol ? STATUS_CMD_FAILED : STATUS_CMD_OK);
	Endpoint_ClearIN();	
}

void PDIProtocol_XPROG_Command(void)
{
	uint8_t XPROGCommand = Endpoint_Read_Byte();

	switch (XPROGCommand)
	{
		case XPRG_CMD_ENTER_PROGMODE:
			PDIProtocol_EnterXPROGMode();
			break;
		case XPRG_CMD_LEAVE_PROGMODE:
			PDIProtocol_LeaveXPROGMode();
			break;
		case XPRG_CMD_ERASE:
			PDIProtocol_EraseChip();
			break;
		case XPRG_CMD_WRITE_MEM:
			PDIProtocol_WriteMemory();
			break;
		case XPRG_CMD_READ_MEM:
			PDIProtocol_ReadMemory();
			break;
		case XPRG_CMD_CRC:
			PDIProtocol_ReadCRC();
			break;
		case XPRG_CMD_SET_PARAM:
			PDIProtocol_SetParam();
			break;
	}
}

static void PDIProtocol_EraseChip(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint32_t Address;
	} Erase_XPROG_Params;

	Endpoint_Read_Stream_LE(&Erase_XPROG_Params, sizeof(Erase_XPROG_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	// TODO: Send erase command here via PDI protocol
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_ERASE);
	Endpoint_Write_Byte(ReturnStatus);
	Endpoint_ClearIN();	
}

static void PDIProtocol_WriteMemory(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint32_t Address;
		uint16_t Length;
		uint8_t  ProgData[256];
	} WriteMemory_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&WriteMemory_XPROG_Params, (sizeof(WriteMemory_XPROG_Params) -
	                                                    sizeof(WriteMemory_XPROG_Params).ProgData));
	WriteMemory_XPROG_Params.Address = SwapEndian_32(WriteMemory_XPROG_Params.Address);
	WriteMemory_XPROG_Params.Length  = SwapEndian_16(WriteMemory_XPROG_Params.Length);
	Endpoint_Read_Stream_LE(&WriteMemory_XPROG_Params.ProgData, WriteMemory_XPROG_Params.Length);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	// TODO: Send program command here via PDI protocol
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_READ_MEM);
	Endpoint_Write_Byte(ReturnStatus);	
	Endpoint_ClearIN();
}

static void PDIProtocol_ReadMemory(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	struct
	{
		uint8_t  MemoryType;
		uint32_t Address;
		uint16_t Length;
	} ReadMemory_XPROG_Params;
	
	Endpoint_Read_Stream_LE(&ReadMemory_XPROG_Params, sizeof(ReadMemory_XPROG_Params));
	ReadMemory_XPROG_Params.Address = SwapEndian_32(ReadMemory_XPROG_Params.Address);
	ReadMemory_XPROG_Params.Length  = SwapEndian_16(ReadMemory_XPROG_Params.Length);

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	// TODO: Send read command here via PDI protocol
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_READ_MEM);
	Endpoint_Write_Byte(ReturnStatus);

	// START TEMP
	uint8_t ProgData[256];
	for (uint16_t i = 0; i < ReadMemory_XPROG_Params.Length; i++)
	  ProgData[i] = i;
	Endpoint_Write_Stream_LE(ProgData, ReadMemory_XPROG_Params.Length);

	if (!Endpoint_IsReadWriteAllowed())
	{
		Endpoint_ClearIN();	
		while(!(Endpoint_IsReadWriteAllowed()));
	}
	// END TEMP
	
	Endpoint_ClearIN();
}

static void PDIProtocol_ReadCRC(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	uint8_t CRCType = Endpoint_Read_Byte();
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	uint32_t MemoryCRC = 0;
	
	// TODO: Read device CRC for desired memory via PDI protocol
	
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

static void PDIProtocol_EnterXPROGMode(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	// TODO: Enter device programming mode here via PDI protocol
	
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_ENTER_PROGMODE);
	Endpoint_Write_Byte(ReturnStatus);
	Endpoint_ClearIN();
}

static void PDIProtocol_LeaveXPROGMode(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	// TODO: Exit device programming mode here via PDI protocol

	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_LEAVE_PROGMODE);
	Endpoint_Write_Byte(XPRG_ERR_OK);
	Endpoint_ClearIN();
}

static void PDIProtocol_SetParam(void)
{
	uint8_t ReturnStatus = XPRG_ERR_OK;

	uint8_t XPROGParam = Endpoint_Read_Byte();
	
	if (XPROGParam == XPRG_PARAM_NVMBASE)
	  XPROG_Param_NVMBase = Endpoint_Read_DWord_LE();
	else if (XPROGParam == XPRG_PARAM_EEPPAGESIZE)
	  XPROG_Param_EEPageSize = Endpoint_Read_Word_LE();
	else
	  ReturnStatus = XPRG_ERR_FAILED;
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
		  
	Endpoint_Write_Byte(CMD_XPROG);
	Endpoint_Write_Byte(XPRG_CMD_SET_PARAM);
	Endpoint_Write_Byte(ReturnStatus);
	Endpoint_ClearIN();
}

#endif
