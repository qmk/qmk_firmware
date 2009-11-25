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
 *  RNDIS Device commands, to issue RNDIS commands to the device for
 *  the control and data transfer between the host and RNDIS device.
 */

#include "RNDISCommands.h"

/** Current RNDIS Request ID, for associating sent commands with received data */
uint32_t RequestID = 0;


/** Function to send the given encapsulated RNDIS command to the device.
 *
 *  \param[in] Buffer  Source command data buffer to send to the device
 *  \param[in] Bytes   Number of bytes to send
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
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

	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(Buffer);
}

/** Function to receive the given encapsulated RNDIS response from the device.
 *
 *  \param[out] Buffer  Destination command data buffer to write read data from the device to
 *  \param[in] Bytes   Number of bytes to read
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
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

/** Sends a RNDIS KEEPALIVE command to the device, to ensure that it does not enter standby mode after periods
 *  of long inactivity.
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t RNDIS_SendKeepAlive(void)
{
	uint8_t ErrorCode;

	RNDIS_KeepAlive_Message_t  KeepAliveMessage;
	RNDIS_KeepAlive_Complete_t KeepAliveMessageResponse;
	
	KeepAliveMessage.MessageType     = REMOTE_NDIS_KEEPALIVE_MSG;
	KeepAliveMessage.MessageLength   = sizeof(RNDIS_KeepAlive_Message_t);
	KeepAliveMessage.RequestId       = RequestID++;

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(&KeepAliveMessage,
	                                               sizeof(RNDIS_KeepAlive_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(&KeepAliveMessageResponse,
	                                               sizeof(RNDIS_KeepAlive_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	return HOST_SENDCONTROL_Successful;
}

/** Initializes the attached RNDIS device's RNDIS interface.
 *
 *  \param[in] HostMaxPacketSize  Size of the packet buffer on the host
 *  \param[out] DeviceMaxPacketSize   Pointer to where the packet buffer size of the device is to be stored
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t RNDIS_InitializeDevice(uint16_t HostMaxPacketSize, uint16_t* DeviceMaxPacketSize)
{
	uint8_t ErrorCode;

	RNDIS_Initialize_Message_t  InitMessage;
	RNDIS_Initialize_Complete_t InitMessageResponse;

	InitMessage.MessageType     = REMOTE_NDIS_INITIALIZE_MSG;
	InitMessage.MessageLength   = sizeof(RNDIS_Initialize_Message_t);
	InitMessage.RequestId       = RequestID++;

	InitMessage.MajorVersion    = REMOTE_NDIS_VERSION_MAJOR;
	InitMessage.MinorVersion    = REMOTE_NDIS_VERSION_MINOR;
	InitMessage.MaxTransferSize = HostMaxPacketSize;
	
	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(&InitMessage,
	                                               sizeof(RNDIS_Initialize_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(&InitMessageResponse,
	                                               sizeof(RNDIS_Initialize_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (InitMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;
	  
	*DeviceMaxPacketSize = InitMessageResponse.MaxTransferSize;
	
	return HOST_SENDCONTROL_Successful;
}

/** Sets a given RNDIS property of an attached RNDIS device.
 *
 *  \param[in] Oid  OID number of the parameter to set
 *  \param[in] Buffer  Pointer to where the property data is to be sourced from
 *  \param[in] Length  Length in bytes of the property data to sent to the device
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t RNDIS_SetRNDISProperty(uint32_t Oid, void* Buffer, uint16_t Length)
{
	uint8_t ErrorCode;

	struct
	{
		RNDIS_Set_Message_t SetMessage;
		uint8_t             ContigiousBuffer[Length];
	} SetMessageData;
	
	RNDIS_Set_Complete_t SetMessageResponse;
	
	SetMessageData.SetMessage.MessageType    = REMOTE_NDIS_SET_MSG;
	SetMessageData.SetMessage.MessageLength  = sizeof(RNDIS_Set_Message_t) + Length;
	SetMessageData.SetMessage.RequestId      = RequestID++;
			
	SetMessageData.SetMessage.Oid            = Oid;
	SetMessageData.SetMessage.InformationBufferLength = Length;
	SetMessageData.SetMessage.InformationBufferOffset = (sizeof(RNDIS_Set_Message_t) - sizeof(RNDIS_Message_Header_t));
	SetMessageData.SetMessage.DeviceVcHandle = 0;
	
	memcpy(&SetMessageData.ContigiousBuffer, Buffer, Length);

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

	if (SetMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;
	  
	return HOST_SENDCONTROL_Successful;
}

/** Gets a given RNDIS property of an attached RNDIS device.
 *
 *  \param[in] Oid  OID number of the parameter to get
 *  \param[in] Buffer  Pointer to where the property data is to be written to
 *  \param[in] MaxLength  Length in bytes of the destination buffer size
 *
 *  \return A value from the USB_Host_SendControlErrorCodes_t enum
 */
uint8_t RNDIS_QueryRNDISProperty(uint32_t Oid, void* Buffer, uint16_t MaxLength)
{
	uint8_t ErrorCode;

	RNDIS_Query_Message_t QueryMessage;

	struct
	{
		RNDIS_Query_Complete_t QueryMessageResponse;
		uint8_t                ContigiousBuffer[MaxLength];
	} QueryMessageResponseData;

	QueryMessage.MessageType    = REMOTE_NDIS_QUERY_MSG;
	QueryMessage.MessageLength  = sizeof(RNDIS_Query_Message_t);
	QueryMessage.RequestId      = RequestID++;
			
	QueryMessage.Oid            = Oid;
	QueryMessage.InformationBufferLength = 0;
	QueryMessage.InformationBufferOffset = 0;
	QueryMessage.DeviceVcHandle = 0;

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(&QueryMessage,
	                                               sizeof(RNDIS_Query_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(&QueryMessageResponseData,
	                                               sizeof(QueryMessageResponseData))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (QueryMessageResponseData.QueryMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;

	memcpy(Buffer, &QueryMessageResponseData.ContigiousBuffer, MaxLength);

	return HOST_SENDCONTROL_Successful;
}

/** Retrieves the size of a received packet, discarding the remainder of the RNDIS packet header to leave only the
 *  packet contents for processing by the host.
 *
 *  \param[out] PacketLength  Size of the packet currently in the pipe
 *
 *  \return A value from the Pipe_Stream_RW_ErrorCodes_t enum
 */
uint8_t RNDIS_GetPacketLength(uint16_t* PacketLength)
{
	uint8_t ErrorCode;

	Pipe_SelectPipe(RNDIS_DATAPIPE_IN);
	Pipe_SetPipeToken(PIPE_TOKEN_IN);
	Pipe_Unfreeze();
	
	if (!(Pipe_IsReadWriteAllowed()))
	{
		*PacketLength = 0;
		Pipe_Freeze();
		return PIPE_RWSTREAM_NoError;
	}

	RNDIS_Packet_Message_t DeviceMessage;
	
	if ((ErrorCode = Pipe_Read_Stream_LE(&DeviceMessage, sizeof(RNDIS_Packet_Message_t))) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}

	*PacketLength = (uint16_t)DeviceMessage.DataLength;
	
	Pipe_Discard_Stream(DeviceMessage.DataOffset - (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t)));
	
	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}
