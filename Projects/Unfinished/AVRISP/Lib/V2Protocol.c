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

ParameterItem_t ParameterTable[] EEMEM = 
	{
		{ .ParameterID    = PARAM_BUILD_NUMBER_LOW,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_BUILD_NUMBER_HIGH,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_HW_VER,
		  .ParameterValue = 0x01                    },
		{ .ParameterID    = PARAM_SW_MAJOR,
		  .ParameterValue = 0x01                    },
		{ .ParameterID    = PARAM_SW_MINOR,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_VTARGET,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_SCK_DURATION,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_RESET_POLARITY,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_STATUS_TGT_CONN,
		  .ParameterValue = 0x00                    },
		{ .ParameterID    = PARAM_DISCHARGEDELAY,
		  .ParameterValue = 0x00                    },
	};
	
void V2Protocol_ConfigureHardware(void)
{
#if F_CPU == 8000000
	uint8_t SPIMaskFromSCKDuration[] = {SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128,
	                                    SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128};
#else
	uint8_t SPIMaskFromSCKDuration[] = {SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128,
	                                    SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128, SPI_SPEED_FCPU_DIV_128};
#endif

	uint8_t SCKDuration = eeprom_read_byte(&V2Protocol_GetParameterItem(PARAM_SCK_DURATION)->ParameterValue);

	if (SCKDuration > sizeof(SPIMaskFromSCKDuration))
	  SCKDuration = SPIMaskFromSCKDuration;
	  
	SPI_Init(SPIMaskFromSCKDuration[SCKDuration], true);	
}

void V2Protocol_ProcessCommand(void)
{
	uint8_t V2Command = Endpoint_Read_Byte();
		  
	switch (V2Command)
	{
		case CMD_SIGN_ON:
			V2Protocol_ProcessCmdSignOn();
			break;
		case CMD_SET_PARAMETER:
		case CMD_GET_PARAMETER:
			V2Protocol_ProcessCmdGetSetParam(V2Command);
			break;
		case CMD_SPI_MULTI:
			V2Protocol_ProcessCmdSPIMulti();
			break;		
		default:
			while (Endpoint_BytesInEndpoint() == AVRISP_DATA_EPSIZE)
			{
				Endpoint_ClearOUT();
				while (!(Endpoint_IsOUTReceived()));
			}
		
			Endpoint_ClearOUT();
			Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

			Endpoint_Write_Byte(V2Command);
			Endpoint_Write_Byte(STATUS_CMD_UNKNOWN);
			Endpoint_ClearIN();
			break;
	}
	
	printf("COMMAND 0x%02x\r\n", V2Command);

	Endpoint_WaitUntilReady();	
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_OUT);	
}

static ParameterItem_t* V2Protocol_GetParameterItem(uint8_t ParamID)
{
	for (uint8_t TableIndex = 0; TableIndex < (sizeof(ParameterTable) / sizeof(ParameterTable[0])); TableIndex++)
	{
		if (ParamID == eeprom_read_byte(&ParameterTable[TableIndex].ParameterID))
		  return &ParameterTable[TableIndex];
	}
	
	return NULL;
}

static void V2Protocol_ProcessCmdSignOn(void)
{
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();

	V2Protocol_ConfigureHardware();

	Endpoint_Write_Byte(CMD_SIGN_ON);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(PROGRAMMER_ID_LEN);
	Endpoint_Write_Stream_LE(PROGRAMMER_ID, PROGRAMMER_ID_LEN);
	Endpoint_ClearIN();
}

static void V2Protocol_ProcessCmdGetSetParam(uint8_t V2Command)
{
	uint8_t ParamID    = Endpoint_Read_Byte();
	uint8_t ParamValue = Endpoint_Read_Byte();

	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
	Endpoint_WaitUntilReady();
	
	ParameterItem_t* ParameterItem = V2Protocol_GetParameterItem(ParamID);
	
	Endpoint_Write_Byte(V2Command);

	if (ParameterItem != NULL)
	{
		Endpoint_Write_Byte(STATUS_CMD_OK);

		if (V2Command == CMD_SET_PARAMETER)
		  eeprom_write_byte(&ParameterItem->ParameterValue, ParamValue);
		else
		  Endpoint_Write_Byte(eeprom_read_byte(&ParameterItem->ParameterValue));			
	}
	else
	{
		Endpoint_Write_Byte(STATUS_CMD_FAILED);
	}

	Endpoint_ClearIN();
}

static void V2Protocol_ProcessCmdSPIMulti(void)
{
	uint8_t TxBytes = Endpoint_Read_Byte();
	uint8_t RxBytes = Endpoint_Read_Byte();
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

	while (CurrTxPos < RxStartAddr)
	{
		if (CurrTxPos < TxBytes)
		  SPI_SendByte(TxData[CurrTxPos]);
		else
		  SPI_SendByte(0);
		
		CurrTxPos++;
	}

	while (CurrRxPos < RxBytes)
	{
		if (CurrTxPos < TxBytes)
		{
			Endpoint_Write_Byte(SPI_TransferByte(TxData[CurrTxPos]));
			CurrTxPos++;
		}
		else
		{
			Endpoint_Write_Byte(SPI_ReceiveByte());
		}
		
		CurrRxPos++;
	}	
	
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_ClearIN();	
}
