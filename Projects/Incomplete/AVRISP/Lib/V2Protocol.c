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

uint32_t CurrentAddress;


/* Table of masks for SPI_Init() from a given PARAM_SCK_DURATION value */
static const uint8_t SPIMaskFromSCKDuration[] =
	{
		#if (F_CPU == 8000000)
		SPI_SPEED_FCPU_DIV_2,
		#endif
		SPI_SPEED_FCPU_DIV_2, SPI_SPEED_FCPU_DIV_4, SPI_SPEED_FCPU_DIV_8,
		SPI_SPEED_FCPU_DIV_16, SPI_SPEED_FCPU_DIV_32, SPI_SPEED_FCPU_DIV_64
		#if (F_CPU == 16000000)										
		, SPI_SPEED_FCPU_DIV_128
		#endif
	};

static uint8_t V2Protocol_GetSPIPrescalerMask(void)
{
	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);

	if (SCKDuration >= sizeof(SPIMaskFromSCKDuration))
	  SCKDuration = (sizeof(SPIMaskFromSCKDuration) - 1);
	  
	return SPIMaskFromSCKDuration[SCKDuration];
}

static void V2Protocol_ChangeTargetResetLine(bool ResetTarget)
{
	if (ResetTarget)
	{
		RESET_LINE_DDR  |= RESET_LINE_MASK;
		
		if (!(V2Params_GetParameterValue(PARAM_RESET_POLARITY)))
		  RESET_LINE_PORT |= RESET_LINE_MASK;
	}
	else
	{
		RESET_LINE_PORT &= ~RESET_LINE_MASK;	
		RESET_LINE_DDR  &= ~RESET_LINE_MASK;
	}
}

static void V2Protocol_DelayMS(uint8_t MS)
{
	while (MS--)
	  _delay_ms(1);
}

static uint8_t V2Protocol_WaitWhileTargetBusy(void)
{
	uint8_t TimeoutMS = TARGET_BUST_TIMEOUT_MS;
	uint8_t ResponseByte;
	
	do
	{
		V2Protocol_DelayMS(1);
	
		SPI_SendByte(0xF0);
		SPI_SendByte(0x00);

		SPI_SendByte(0x00);
		ResponseByte = SPI_ReceiveByte();
	}
	while ((ResponseByte & 0x01) && (TimeoutMS--));

	if (!(TimeoutMS))
	  return STATUS_CMD_TOUT;
	else
	  return STATUS_CMD_OK;
}

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
	
	printf("COMMAND 0x%02x\r\n", V2Command);

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
	Endpoint_WaitUntilReady();

	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_UNKNOWN);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_SignOn(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();

	Endpoint_Write_Byte(CMD_SIGN_ON);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(sizeof(PROGRAMMER_ID) - 1);
	Endpoint_Write_Stream_LE(PROGRAMMER_ID, (sizeof(PROGRAMMER_ID) - 1));
	Endpoint_ClearIN();
}

static void V2Protocol_Command_GetSetParam(uint8_t V2Command)
{
	struct
	{
		uint8_t ParamID;
		uint8_t ParamValue;
	} Get_Set_Param_Params;
	
	Endpoint_Read_Stream_LE(&Get_Set_Param_Params, sizeof(Get_Set_Param_Params));

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();
	
	uint8_t ParamPrivs = V2Params_GetParameterPrivellages(Get_Set_Param_Params.ParamID);
	
	Endpoint_Write_Byte(V2Command);
	
	if ((V2Command == CMD_SET_PARAMETER) && (ParamPrivs & PARAM_PRIV_WRITE))
	{
		Endpoint_Write_Byte(STATUS_CMD_OK);
		V2Params_SetParameterValue(Get_Set_Param_Params.ParamID, Get_Set_Param_Params.ParamValue);
	}
	else if ((V2Command == CMD_GET_PARAMETER) && (ParamPrivs & PARAM_PRIV_READ))
	{
		Endpoint_Write_Byte(STATUS_CMD_OK);
		Endpoint_Write_Byte(V2Params_GetParameterValue(Get_Set_Param_Params.ParamID));
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
	Endpoint_WaitUntilReady();
	
	// TODO: Check for extended address

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
	Endpoint_WaitUntilReady();

	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);
	uint8_t ResponseStatus = STATUS_CMD_FAILED;

	Enter_ISP_Params.TimeoutMS -= Enter_ISP_Params.ExecutionDelayMS +
	                              Enter_ISP_Params.PinStabDelayMS;
	
	CurrentAddress = 0;

	if (SCKDuration >= sizeof(SPIMaskFromSCKDuration))
	  SCKDuration = (sizeof(SPIMaskFromSCKDuration) - 1);

	V2Protocol_DelayMS(Enter_ISP_Params.ExecutionDelayMS);	  
	SPI_Init(SPIMaskFromSCKDuration[SCKDuration], true);
	V2Protocol_ChangeTargetResetLine(true);
	V2Protocol_DelayMS(Enter_ISP_Params.PinStabDelayMS);
		
	while (Enter_ISP_Params.SynchLoops-- && (ResponseStatus == STATUS_CMD_FAILED))
	{
		uint8_t ResponseBytes[4];
		
		for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
		{
			ResponseBytes[RByte] = SPI_TransferByte(Enter_ISP_Params.EnterProgBytes[RByte]);
			V2Protocol_DelayMS(Enter_ISP_Params.ByteDelay);
			
			if (Enter_ISP_Params.TimeoutMS >= Enter_ISP_Params.ByteDelay)
			  Enter_ISP_Params.TimeoutMS -= Enter_ISP_Params.ByteDelay;
			else
			  ResponseStatus = STATUS_CMD_TOUT;
		}
		
		if (ResponseBytes[Enter_ISP_Params.PollIndex] == Enter_ISP_Params.PollValue)
		  ResponseStatus = STATUS_CMD_OK;
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
	Endpoint_WaitUntilReady();

	V2Protocol_DelayMS(Leave_ISP_Params.PreDelayMS);
	V2Protocol_ChangeTargetResetLine(false);
	SPI_ShutDown();
	V2Protocol_DelayMS(Leave_ISP_Params.PostDelayMS);

	Endpoint_Write_Byte(CMD_LEAVE_PROGMODE_ISP);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
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
	Endpoint_WaitUntilReady();
	
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
	Endpoint_WaitUntilReady();

	uint8_t ResponseBytes[4];
		
	for (uint8_t RByte = 0; RByte < sizeof(ResponseBytes); RByte++)
	  ResponseBytes[RByte] = SPI_TransferByte(Read_FuseLockSigOSCCAL_Params.ReadCommandBytes[RByte]);
		
	Endpoint_Write_Byte(V2Command);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(ResponseBytes[Read_FuseLockSigOSCCAL_Params.RetByte]);
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
	Endpoint_WaitUntilReady();

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
	Endpoint_WaitUntilReady();
	
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
