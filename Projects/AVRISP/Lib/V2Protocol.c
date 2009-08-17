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

char ProgrammerID[] = "AVRISP_MK2";

#include "V2Protocol.h"

void V2Protocol_ProcessCommand(void)
{
	uint8_t V2Command = Endpoint_Read_Byte();
	
	switch (V2Command)
	{
		case CMD_SIGN_ON:
			Endpoint_ClearOUT();
			Endpoint_SetEndpointDirection(ENDPOINT_DIR_IN);
			
			Endpoint_Write_Byte(CMD_SIGN_ON);
			Endpoint_Write_Byte(STATUS_CMD_OK);
			Endpoint_Write_Byte((sizeof(ProgrammerID) - 1));
			Endpoint_Write_Stream_LE(ProgrammerID, (sizeof(ProgrammerID) - 1));			
			Endpoint_ClearIN();
			break;
	}
}

