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

void V2Protocol_ProcessCommand(void)
{
	uint8_t V2Command = Endpoint_Read_Byte();
		  
	printf("COMMAND %d\r\n", V2Command);

	switch (V2Command)
	{
		case CMD_SIGN_ON:
			V2Protocol_ProcessCmdSignOn();
			break;
		case CMD_SET_PARAMETER:
			V2Protocol_ProcessCmdSetParam();
			break;
		case CMD_GET_PARAMETER:
			V2Protocol_ProcessCmdGetParam();
			break;
		default:
			Endpoint_ClearOUT();
			Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
			Endpoint_Write_Byte(STATUS_CMD_UNKNOWN);
			Endpoint_ClearIN();
			break;
	}
	
	/* Reset Endpoint direction to OUT ready for next command */
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
	
	Endpoint_Write_Byte(CMD_SIGN_ON);
	Endpoint_Write_Byte(STATUS_CMD_OK);
	Endpoint_Write_Byte(PROGRAMMER_ID_LEN);
	Endpoint_Write_Stream_LE(PROGRAMMER_ID, PROGRAMMER_ID_LEN);
	Endpoint_ClearIN();
}

static void V2Protocol_ProcessCmdSetParam(void)
{
	uint8_t ParamID    = Endpoint_Read_Byte();
	uint8_t ParamValue = Endpoint_Read_Byte();

	ParameterItem_t* ParameterItem = V2Protocol_GetParameterItem(ParamID);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	if (ParameterItem != NULL)
	{
		eeprom_write_byte(&ParameterItem->ParameterValue, ParamValue);

		Endpoint_Write_Byte(CMD_SET_PARAMETER);
		Endpoint_Write_Byte(STATUS_CMD_OK);	
	}
	else
	{
		Endpoint_Write_Byte(STATUS_CMD_FAILED);
	}

	Endpoint_ClearIN();
}

static void V2Protocol_ProcessCmdGetParam(void)
{
	uint8_t ParamID    = Endpoint_Read_Byte();

	ParameterItem_t* ParameterItem = V2Protocol_GetParameterItem(ParamID);
	
	Endpoint_ClearOUT();
	Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);

	if (ParameterItem != NULL)
	{
		Endpoint_Write_Byte(CMD_GET_PARAMETER);
		Endpoint_Write_Byte(STATUS_CMD_OK);
		Endpoint_Write_Byte(eeprom_read_byte(&ParameterItem->ParameterValue));	
	}
	else
	{
		Endpoint_Write_Byte(STATUS_CMD_FAILED);
	}

	Endpoint_ClearIN();	
}
