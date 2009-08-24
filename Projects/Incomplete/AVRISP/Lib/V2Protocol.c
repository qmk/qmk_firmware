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
 *  V2Protocol handler, to process V2 Protocol commands used in Atmel programmer devices.
 */

#define  INCLUDE_FROM_V2PROTOCOL_C
#include "V2Protocol.h"

void V2Protocol_ProcessCommand(void)
{
	uint8_t V2Command = Endpoint_Read_Byte();
		  
	switch (V2Command)
	{
		case CMD_SIGN_ON:
			V2Protocol_Command_SignOn();
			break;
		case CMD_SET_PARAMETER:
		case CMD_GET_PARAMETER:
			V2Protocol_Command_GetSetParam(V2Command);
			break;
		case CMD_LOAD_ADDRESS:
			V2Protocol_Command_LoadAddress();
			break;
		case CMD_ENTER_PROGMODE_ISP:
			V2Protocol_Command_EnterISPMode();
			break;
		case CMD_LEAVE_PROGMODE_ISP:
			V2Protocol_Command_LeaveISPMode();
			break;
		case CMD_PROGRAM_FLASH_ISP:
		case CMD_PROGRAM_EEPROM_ISP:
			V2Protocol_Command_ProgramMemory(V2Command);			
			break;
		case CMD_READ_FLASH_ISP:
		case CMD_READ_EEPROM_ISP:
			V2Protocol_Command_ReadMemory(V2Command);
			break;
		case CMD_CHIP_ERASE_ISP:
			V2Protocol_Command_ChipErase();
			break;
		case CMD_READ_FUSE_ISP:
		case CMD_READ_LOCK_ISP:
		case CMD_READ_SIGNATURE_ISP:
		case CMD_READ_OSCCAL_ISP:
			V2Protocol_Command_ReadFuseLockSigOSCCAL(V2Command);
			break;
		case CMD_PROGRAM_FUSE_ISP:
		case CMD_PROGRAM_LOCK_ISP:
			V2Protocol_Command_WriteFuseLock(V2Command);
			break;
		case CMD_SPI_MULTI:
			V2Protocol_Command_SPIMulti();
			break;
		default:
			V2Protocol_Command_Unknown(V2Command);
			break;
	}
	
	Endpoint_WaitUntilReady();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_OUT);
}

static void V2Protocol_Command_Unknown(uint8_t V2Command)
{
	/* Discard all incomming data */
	while (Endpoint_BytesInEndpoint() == AVRISP_DATA_EPSIZE)
	{
		Endpoint_ClearOUT();
		Endpoint_WaitUntilReady();
	}

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_UNKNOWN);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_SignOn(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	Endpoint_Write_Byte(CMD_SIGN_ON);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(sizeof(PROGRAMMER_ID) - 1);
	Endpoint_Write_Stream_LE(PROGRAMMER_ID, (sizeof(PROGRAMMER_ID) - 1));
	Endpoint_ClearIN();
}

static void V2Protocol_Command_GetSetParam(uint8_t V2Command)
{
	uint8_t ParamID = Endpoint_Read_Byte();
	uint8_t ParamValue;
	
	if (V2Command == CMD_SET_PARAMETER)
	  ParamValue = Endpoint_Read_Byte();

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(V2Command);
	
	uint8_t ParamPrivs = V2Params_GetParameterPrivellages(ParamID);
	
	if ((V2Command == CMD_SET_PARAMETER) && (ParamPrivs & PARAM_PRIV_WRITE))
	{
		Endpoint_Write_Byte(STATUS_CMD_OK);
		V2Params_SetParameterValue(ParamID, ParamValue);
	}
	else if ((V2Command == CMD_GET_PARAMETER) && (ParamPrivs & PARAM_PRIV_READ))
	{
		Endpoint_Write_Byte(STATUS_CMD_OK);
		Endpoint_Write_Byte(V2Params_GetParameterValue(ParamID));
	}
	else
	{	
		Endpoint_Write_Byte(STATUS_CMD_FAILED);
	}

	Endpoint_ClearIN();
}

static void V2Protocol_Command_LoadAddress(void)
{
	Endpoint_Read_Stream_LE(&CurrentAddress, sizeof(CurrentAddress));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	if (CurrentAddress & (1UL << 31))
	  V2Protocol_LoadExtendedAddress();

	Endpoint_Write_Byte(CMD_LOAD_ADDRESS);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_EnterISPMode(void)
{
	struct
	{
		uint8_t TimeoutMS;
		uint8_t PinStabDelayMS;
		uint8_t ExecutionDelayMS;
		uint8_t SynchLoops;
		uint8_t ByteDelay;
		uint8_t PollValue;
		uint8_t PollIndex;
		uint8_t EnterProgBytes[4];
	} Enter_ISP_Params;
	
	Endpoint_Read_Stream_LE(&Enter_ISP_Params, sizeof(Enter_ISP_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t ResponseStatus = STATUS_CMD_FAILED;
	
	CurrentAddress = 0;

	V2Protocol_DelayMS(Enter_ISP_Params.ExecutionDelayMS);	  
	SPI_Init(V2Protocol_GetSPIPrescalerMask() | SPI_SCK_LEAD_RISING | SPI_SAMPLE_LEADING | SPI_MODE_MASTER);
		
	while (Enter_ISP_Params.SynchLoops-- && (ResponseStatus == STATUS_CMD_FAILED))
	{
		uint8_t ResponseBytes[4];

		V2Protocol_ChangeTargetResetLine(true);
		V2Protocol_DelayMS(Enter_ISP_Params.PinStabDelayMS);

		for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
		{
			V2Protocol_DelayMS(Enter_ISP_Params.ByteDelay);
			ResponseBytes[RByte] = SPI_TransferByte(Enter_ISP_Params.EnterProgBytes[RByte]);
		}
		
		/* Check if polling disabled, or if the polled value matches the expected value */
		if (!Enter_ISP_Params.PollIndex || (ResponseBytes[Enter_ISP_Params.PollIndex - 1] == Enter_ISP_Params.PollValue))
		{
			ResponseStatus = STATUS_CMD_OK;
		}
		else
		{
			V2Protocol_ChangeTargetResetLine(false);
			V2Protocol_DelayMS(Enter_ISP_Params.PinStabDelayMS);
		}
	}

	Endpoint_Write_Byte(CMD_ENTER_PROGMODE_ISP);
	Endpoint_Write_Byte(ResponseStatus);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_LeaveISPMode(void)
{
	struct
	{
		uint8_t PreDelayMS;
		uint8_t PostDelayMS;
	} Leave_ISP_Params;

	Endpoint_Read_Stream_LE(&Leave_ISP_Params, sizeof(Leave_ISP_Params));
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	V2Protocol_DelayMS(Leave_ISP_Params.PreDelayMS);
	V2Protocol_ChangeTargetResetLine(false);
	SPI_ShutDown();
	V2Protocol_DelayMS(Leave_ISP_Params.PostDelayMS);

	Endpoint_Write_Byte(CMD_LEAVE_PROGMODE_ISP);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_ProgramMemory(uint8_t V2Command)
{
	struct
	{
		uint16_t BytesToWrite;
		uint8_t  ProgrammingMode;
		uint8_t  DelayMS;
		uint8_t  ProgrammingCommands[3];
		uint8_t  PollValue1;
		uint8_t  PollValue2;
	} Write_Memory_Params;
	
	uint8_t ProgrammingStatus = STATUS_CMD_OK;
	
	Endpoint_Read_Stream_LE(&Write_Memory_Params, sizeof(Write_Memory_Params));
	Write_Memory_Params.BytesToWrite = SwapEndian_16(Write_Memory_Params.BytesToWrite);
	
	if (Write_Memory_Params.ProgrammingMode & PROG_MODE_PAGED_WRITES_MASK)
	{
		for (uint16_t CurrentByte = 0; CurrentByte < Write_Memory_Params.BytesToWrite; CurrentByte++)
		{
			if ((V2Command == CMD_READ_FLASH_ISP) && (CurrentByte & 0x01))
			  Write_Memory_Params.ProgrammingCommands[0] ^= READ_WRITE_ODD_BYTE_MASK;
			  
			SPI_SendByte(Write_Memory_Params.ProgrammingCommands[0]);
			SPI_SendByte(CurrentAddress >> 8);
			SPI_SendByte(CurrentAddress & 0xFF);
			SPI_SendByte(Endpoint_Read_Byte());
			
			// TODO - Correct Polling

			if (((V2Command == CMD_PROGRAM_FLASH_ISP) && (CurrentByte & 0x01)) || (V2Command == CMD_PROGRAM_EEPROM_ISP))
			  CurrentAddress++;
		}
		
		/* If the current page must be committed, send the PROGRAM PAGE command to the target */
		if (Write_Memory_Params.ProgrammingMode & PROG_MODE_COMMIT_PAGE_MASK)
		{
			SPI_SendByte(Write_Memory_Params.ProgrammingCommands[1]);
			SPI_SendByte(CurrentAddress >> 8);
			SPI_SendByte(CurrentAddress & 0xFF);
			SPI_SendByte(0x00);
		}
	}
	else
	{			
		// TODO - Read in programming data, write to device		
	}
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(ProgrammingStatus);
	
	Endpoint_ClearIN();
}

static void V2Protocol_Command_ReadMemory(uint8_t V2Command)
{
	struct
	{
		uint16_t BytesToRead;
		uint8_t  ReadMemoryCommand;
	} Read_Memory_Params;
	
	Endpoint_Read_Stream_LE(&Read_Memory_Params, sizeof(Read_Memory_Params));
	Read_Memory_Params.BytesToRead = SwapEndian_16(Read_Memory_Params.BytesToRead);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	
	for (uint16_t CurrentByte = 0; CurrentByte < Read_Memory_Params.BytesToRead; CurrentByte++)
	{
		if ((V2Command == CMD_READ_FLASH_ISP) && (CurrentByte & 0x01))
		  Read_Memory_Params.ReadMemoryCommand ^= READ_WRITE_ODD_BYTE_MASK;

		SPI_SendByte(Read_Memory_Params.ReadMemoryCommand);
		SPI_SendByte(CurrentAddress >> 8);
		SPI_SendByte(CurrentAddress & 0xFF);
		Endpoint_Write_Byte(SPI_ReceiveByte());
		
		/* Check if the endpoint bank is currently full */
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			Endpoint_ClearIN();
			Endpoint_WaitUntilReady();
		}
		
		if (((V2Command == CMD_READ_FLASH_ISP) && (CurrentByte & 0x01)) || (V2Command == CMD_READ_EEPROM_ISP))
		  CurrentAddress++;
	}

	Endpoint_Write_Byte(STATUS_CMD_OK);
	
	bool EndpointBankFull = Endpoint_IsReadWriteAllowed();
	Endpoint_ClearIN();
	
	/* Ensure data transfer is terminated by a short packet if the last sent bank was completely full */
	if (EndpointBankFull)
	{
		Endpoint_WaitUntilReady();
		Endpoint_ClearIN();
	}
}

static void V2Protocol_Command_ChipErase(void)
{
	struct
	{
		uint8_t EraseDelayMS;
		uint8_t PollMethod;
		uint8_t EraseCommandBytes[4];
	} Erase_Chip_Params;
	
	Endpoint_Read_Stream_LE(&Erase_Chip_Params, sizeof(Erase_Chip_Params));
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	uint8_t ResponseStatus = STATUS_CMD_OK;
	
	for (uint8_t SByte = 0; SByte < sizeof(Erase_Chip_Params.EraseCommandBytes); SByte++)
	  SPI_SendByte(Erase_Chip_Params.EraseCommandBytes[SByte]);

	if (Erase_Chip_Params.PollMethod == 0)
	  V2Protocol_DelayMS(Erase_Chip_Params.EraseDelayMS);
	else
	  ResponseStatus = V2Protocol_WaitWhileTargetBusy();
	  
	Endpoint_Write_Byte(CMD_CHIP_ERASE_ISP);
	Endpoint_Write_Byte(ResponseStatus);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_ReadFuseLockSigOSCCAL(uint8_t V2Command)
{
	struct
	{
		uint8_t RetByte;
		uint8_t ReadCommandBytes[4];
	} Read_FuseLockSigOSCCAL_Params;
	
	Endpoint_Read_Stream_LE(&Read_FuseLockSigOSCCAL_Params, sizeof(Read_FuseLockSigOSCCAL_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	uint8_t ResponseBytes[4];
		
	for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
	  ResponseBytes[RByte] = SPI_TransferByte(Read_FuseLockSigOSCCAL_Params.ReadCommandBytes[RByte]);
		
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(ResponseBytes[Read_FuseLockSigOSCCAL_Params.RetByte - 1]);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_WriteFuseLock(uint8_t V2Command)
{
	struct
	{
		uint8_t WriteCommandBytes[4];
	} Write_FuseLockSig_Params;
	
	Endpoint_Read_Stream_LE(&Write_FuseLockSig_Params, sizeof(Write_FuseLockSig_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	for (uint8_t SByte = 0; SByte < sizeof(Write_FuseLockSig_Params.WriteCommandBytes); SByte++)
	  SPI_SendByte(Write_FuseLockSig_Params.WriteCommandBytes[SByte]);
		
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_SPIMulti(void)
{
	struct
	{
		uint8_t TxBytes;
		uint8_t RxBytes;
		uint8_t RxStartAddr;
		uint8_t TxData[255];
	} SPI_Multi_Params;
	
	Endpoint_Read_Stream_LE(&SPI_Multi_Params, sizeof(SPI_Multi_Params) -
	                                           sizeof(SPI_Multi_Params.TxData));
	Endpoint_Read_Stream_LE(&SPI_Multi_Params.TxData, SPI_Multi_Params.TxBytes);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	
	Endpoint_Write_Byte(CMD_SPI_MULTI);
	Endpoint_Write_Byte(STATUS_CMD_OK);

	uint8_t CurrTxPos = 0;
	uint8_t CurrRxPos = 0;

	/* Write out bytes to transmit until the start of the bytes to receive is met */
	while (CurrTxPos < SPI_Multi_Params.RxStartAddr)
	{
		if (CurrTxPos < SPI_Multi_Params.TxBytes)
		  SPI_SendByte(SPI_Multi_Params.TxData[CurrTxPos]);
		else
		  SPI_SendByte(0);
		
		CurrTxPos++;
	}

	/* Transmit remaining bytes with padding as needed, read in response bytes */
	while (CurrRxPos < SPI_Multi_Params.RxBytes)
	{
		if (CurrTxPos < SPI_Multi_Params.TxBytes)
		  Endpoint_Write_Byte(SPI_TransferByte(SPI_Multi_Params.TxData[CurrTxPos++]));
		else
		  Endpoint_Write_Byte(SPI_ReceiveByte());
		
		CurrRxPos++;
	}	
	
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}
