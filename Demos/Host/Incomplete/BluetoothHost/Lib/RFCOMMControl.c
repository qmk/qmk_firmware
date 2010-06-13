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
 *  RFCOMM multiplexer control layer module. This module handles multiplexer
 *  channel commands to the control DLCI in the RFCOMM layer, to open, configure,
 *  test and close logical RFCOMM channels.
 */

#define  INCLUDE_FROM_RFCOMM_CONTROL_C
#include "RFCOMMControl.h"

void RFCOMM_ProcessControlCommand(const uint8_t* Command, Bluetooth_Channel_t* const Channel)
{
	const RFCOMM_Command_t* CommandHeader  = (const RFCOMM_Command_t*)Command;
	const uint8_t*          CommandData    = (const uint8_t*)Command + sizeof(RFCOMM_Command_t);

	switch (CommandHeader->Command)
	{
		case RFCOMM_Control_Test:
			RFCOMM_ProcessTestCommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_FlowControlEnable:
			RFCOMM_ProcessFCECommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_FlowControlDisable:
			RFCOMM_ProcessFCDCommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_ModemStatus:
			RFCOMM_ProcessMSCommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_RemotePortNegotiation:
			RFCOMM_ProcessRPNCommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_RemoteLineStatus:
			RFCOMM_ProcessRLSCommand(CommandHeader, CommandData);
			break;
		case RFCOMM_Control_DLCParameterNegotiation:
			RFCOMM_ProcessDPNCommand(CommandHeader, CommandData);
			break;
		default:
			BT_RFCOMM_DEBUG(1, "<< Unknown Command");		
			break;
	}
}

static void RFCOMM_ProcessTestCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< TEST Command");
}

static void RFCOMM_ProcessFCECommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< FCE Command");
}

static void RFCOMM_ProcessFCDCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< FCD Command");
}

static void RFCOMM_ProcessMSCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< MS Command");
}

static void RFCOMM_ProcessRPNCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< RPN Command");
}

static void RFCOMM_ProcessRLSCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< RLS Command");
}

static void RFCOMM_ProcessDPNCommand(const RFCOMM_Command_t* CommandHeader, const uint8_t* CommandData)
{
	BT_RFCOMM_DEBUG(1, "<< DPN Command");
	
	/* Skip over the first data byte (Length field) since its size and value are fixed */
	RFCOMM_Channel_t* RFCOMMChannel = RFCOMM_GetChannelData(CommandData[2]);
	
	if (RFCOMMChannel == NULL)
	{
		// TODO: Channel does not exist - create it
	}
	
	RFCOMMChannel->Configured = true;
	
	// TODO: Read in channel data, ACK request
}
