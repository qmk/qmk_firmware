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
static const uint8_t SPIMaskFromSCKDuration[MAX_SPI_SETTINGS] =
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

static void V2Protocol_ReconfigureSPI(void)
{
	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);

	if (SCKDuration >= MAX_SPI_SETTINGS)
	  SCKDuration = (MAX_SPI_SETTINGS - 1);
	  
	SPI_Init(SPIMaskFromSCKDuration[SCKDuration], true);	
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

	V2Protocol_ReconfigureSPI();
	CurrentAddress = 0;

	Endpoint_Write_Byte(CMD_SIGN_ON);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(PROGRAMMER_ID_LEN);
	Endpoint_Write_Stream_LE(PROGRAMMER_ID, PROGRAMMER_ID_LEN);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_GetSetParam(uint8_t V2Command)
{
	uint8_t ParamID    = Endpoint_Read_Byte();
	uint8_t ParamValue = Endpoint_Read_Byte();

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();
	
	uint8_t ParamPrivs = V2Params_GetParameterPrivellages(ParamID);
	
	Endpoint_Write_Byte(V2Command);
	
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
	CurrentAddress = Endpoint_Read_DWord_LE();

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();

	Endpoint_Write_Byte(CMD_LOAD_ADDRESS);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();
}

static void V2Protocol_Command_SPIMulti(void)
{
	uint8_t TxBytes     = Endpoint_Read_Byte();
	uint8_t RxBytes     = Endpoint_Read_Byte();
	uint8_t RxStartAddr = Endpoint_Read_Byte();
	uint8_t TxData[255];
	
	Endpoint_Read_Stream_LE(TxData, TxBytes);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();
	
	Endpoint_Write_Byte(CMD_SPI_MULTI);
	Endpoint_Write_Byte(STATUS_CMD_OK);

	uint8_t CurrTxPos = 0;
	uint8_t CurrRxPos = 0;

	/* Write out bytes to transmit until the start of the bytes to receive is met */
	while (CurrTxPos < RxStartAddr)
	{
		if (CurrTxPos < TxBytes)
		  SPI_SendByte(TxData[CurrTxPos]);
		else
		  SPI_SendByte(0);
		
		CurrTxPos++;
	}

	/* Transmit remaining bytes with padding as needed, read in response bytes */
	while (CurrRxPos < RxBytes)
	{
		if (CurrTxPos < TxBytes)
		  Endpoint_Write_Byte(SPI_TransferByte(TxData[CurrTxPos++]));
		else
		  Endpoint_Write_Byte(SPI_ReceiveByte());
		
		CurrRxPos++;
	}	
	
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();	
}
