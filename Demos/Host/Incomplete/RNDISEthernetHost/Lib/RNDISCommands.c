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
 *  RNDOS Device commands, to issue RNDIS commands to the device for
 *  the control and data transfer between the host and RNDIS device.
 */

#include "RNDISCommands.h"

uint32_t RequestID = 0;

uint8_t RNDIS_SendEncapsulatedCommand(void* Buffer, uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_SendEncapsulatedCommand,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = Length,
		};
	
	printf("==== RNDIS CONTROL REQUEST ====\r\n");
	uint8_t* Data = Buffer;
	for (uint16_t i = 0; i < Length / 8; i++)
	{
		for (uint16_t j = 0; (j < 8) && i*8+j < Length; j++)
			printf("%02X ", *(Data++));
			
		printf("\r\n");
	}
	printf("==== ********************* ====\r\n");

	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}

uint8_t RNDIS_GetEncapsulatedResponse(void* Buffer, uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetEncapsulatedResponse,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = Length,
		};
	
	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}

uint8_t RNDIS_InitializeDevice(uint16_t MaxPacketSize, RNDIS_Initialize_Complete_t* InitMessageResponse)
{
	uint8_t ErrorCode;

	RNDIS_Initialize_Message_t InitMessage;

	InitMessage.MessageType     = REMOTE_NDIS_INITIALIZE_MSG;
	InitMessage.MessageLength   = sizeof(RNDIS_Initialize_Message_t);
	InitMessage.RequestId       = RequestID++;
	InitMessage.MajorVersion    = REMOTE_NDIS_VERSION_MAJOR;
	InitMessage.MinorVersion    = REMOTE_NDIS_VERSION_MINOR;
	InitMessage.MaxTransferSize = sizeof(RNDIS_Packet_Message_t) + MaxPacketSize;
	
	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(&InitMessage,
	                                               sizeof(RNDIS_Initialize_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(InitMessageResponse,
	                                               sizeof(RNDIS_Initialize_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_SetRNDISProperty(uint32_t Oid, void* Buffer, uint16_t Length)
{
	uint8_t ErrorCode;

	struct
	{
		RNDIS_Set_Message_t SetMessage;
		uint8_t             ContigiousBuffer[Length];
	} SetMessageData;
	
	RNDIS_Set_Complete_t SetMessageResponse;
	
	SetMessageData.SetMessage.MessageType   = REMOTE_NDIS_SET_MSG;
	SetMessageData.SetMessage.MessageLength = sizeof(RNDIS_Set_Message_t) + Length;
	SetMessageData.SetMessage.RequestId     = RequestID++;
			
	SetMessageData.SetMessage.Oid           = Oid;
	SetMessageData.SetMessage.InformationBufferLength = Length;
	SetMessageData.SetMessage.InformationBufferOffset = 0;
	SetMessageData.SetMessage.DeviceVcHandle = 0;


	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(&SetMessageData,
	                                               SetMessageData.SetMessage.MessageLength)) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(&SetMessageResponse,
	                                               sizeof(RNDIS_Set_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	return HOST_SENDCONTROL_Successful;
}
