/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define  INCLUDE_FROM_RNDIS_CLASS_HOST_C
#include "RNDIS.h"

uint8_t RNDIS_Host_ConfigurePipes(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo, uint16_t ConfigDescriptorSize,
                                void* ConfigDescriptorData)
{
	uint8_t FoundEndpoints = 0;

	memset(&RNDISInterfaceInfo->State, 0x00, sizeof(RNDISInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return RNDIS_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_RNDIS_Host_NextRNDISControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return RNDIS_ENUMERROR_NoRNDISInterfaceFound;
	}
	
	RNDISInterfaceInfo->State.ControlInterfaceNumber = DESCRIPTOR_CAST(ConfigDescriptorData, USB_Descriptor_Interface_t).InterfaceNumber;

	while (FoundEndpoints != (RNDIS_FOUND_NOTIFICATION_IN | RNDIS_FOUND_DATAPIPE_IN | RNDIS_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_RNDIS_Host_NextRNDISInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (FoundEndpoints & RNDIS_FOUND_NOTIFICATION_IN)
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, 
				                              DComp_RNDIS_Host_NextRNDISDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return RNDIS_ENUMERROR_NoRNDISInterfaceFound;
				}
			}
			else
			{
				FoundEndpoints = 0;

				Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataOUTPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(RNDISInterfaceInfo->Config.NotificationPipeNumber);
				Pipe_DisablePipe();
			
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DComp_RNDIS_Host_NextRNDISControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return RNDIS_ENUMERROR_NoRNDISInterfaceFound;
				}
			}

			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DComp_RNDIS_Host_NextRNDISInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return RNDIS_ENUMERROR_EndpointsNotFound;
			}
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(RNDISInterfaceInfo->Config.NotificationPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   RNDISInterfaceInfo->Config.NotificationPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				RNDISInterfaceInfo->State.NotificationPipeSize = EndpointData->EndpointSize;

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				FoundEndpoints |= RNDIS_FOUND_NOTIFICATION_IN;
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				if (Pipe_IsEndpointBound(EndpointData->EndpointAddress))
				{
					RNDISInterfaceInfo->State.BidirectionalDataEndpoints = true;
					Pipe_DisablePipe();
				}

				Pipe_ConfigurePipe(RNDISInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
				                   EndpointData->EndpointAddress, EndpointData->EndpointSize, 
				                   RNDISInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				RNDISInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

				FoundEndpoints |= RNDIS_FOUND_DATAPIPE_IN;
			}
			else
			{
				if (Pipe_IsEndpointBound(EndpointData->EndpointAddress))
				{
					RNDISInterfaceInfo->State.BidirectionalDataEndpoints = true;
				}
				else
				{
					Pipe_ConfigurePipe(RNDISInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
					                   EndpointData->EndpointAddress, EndpointData->EndpointSize, 
					                   RNDISInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				}
				
				RNDISInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;
				
				FoundEndpoints |= RNDIS_FOUND_DATAPIPE_OUT;
			}
		}
	}

	RNDISInterfaceInfo->State.IsActive = true;
	return RNDIS_ENUMERROR_NoError;
}

static uint8_t DComp_RNDIS_Host_NextRNDISControlInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == RNDIS_CONTROL_CLASS)    &&
		    (CurrentInterface->SubClass == RNDIS_CONTROL_SUBCLASS) &&
			(CurrentInterface->Protocol == RNDIS_CONTROL_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_RNDIS_Host_NextRNDISDataInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == RNDIS_DATA_CLASS)    &&
		    (CurrentInterface->SubClass == RNDIS_DATA_SUBCLASS) &&
			(CurrentInterface->Protocol == RNDIS_DATA_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_RNDIS_Host_NextRNDISInterfaceEndpoint(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);
	
		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);
	
		if ((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void RNDIS_Host_USBTask(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	(void)RNDISInterfaceInfo;
}

static uint8_t RNDIS_SendEncapsulatedCommand(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                             void* Buffer, uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_SendEncapsulatedCommand,
			.wValue        = 0,
			.wIndex        = RNDISInterfaceInfo->State.ControlInterfaceNumber,
			.wLength       = Length,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(Buffer);
}

static uint8_t RNDIS_GetEncapsulatedResponse(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                             void* Buffer, uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = REQ_GetEncapsulatedResponse,
			.wValue        = 0,
			.wIndex        = RNDISInterfaceInfo->State.ControlInterfaceNumber,
			.wLength       = Length,
		};
	
	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(Buffer);
}

uint8_t RNDIS_Host_SendKeepAlive(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	uint8_t ErrorCode;

	RNDIS_KeepAlive_Message_t  KeepAliveMessage;
	RNDIS_KeepAlive_Complete_t KeepAliveMessageResponse;
	
	KeepAliveMessage.MessageType     = REMOTE_NDIS_KEEPALIVE_MSG;
	KeepAliveMessage.MessageLength   = sizeof(RNDIS_KeepAlive_Message_t);
	KeepAliveMessage.RequestId       = RNDISInterfaceInfo->State.RequestID++;

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(RNDISInterfaceInfo, &KeepAliveMessage,
	                                               sizeof(RNDIS_KeepAlive_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(RNDISInterfaceInfo, &KeepAliveMessageResponse,
	                                               sizeof(RNDIS_KeepAlive_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_Host_InitializeDevice(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	uint8_t ErrorCode;

	RNDIS_Initialize_Message_t  InitMessage;
	RNDIS_Initialize_Complete_t InitMessageResponse;

	InitMessage.MessageType     = REMOTE_NDIS_INITIALIZE_MSG;
	InitMessage.MessageLength   = sizeof(RNDIS_Initialize_Message_t);
	InitMessage.RequestId       = RNDISInterfaceInfo->State.RequestID++;

	InitMessage.MajorVersion    = REMOTE_NDIS_VERSION_MAJOR;
	InitMessage.MinorVersion    = REMOTE_NDIS_VERSION_MINOR;
	InitMessage.MaxTransferSize = RNDISInterfaceInfo->Config.HostMaxPacketSize;
	
	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(RNDISInterfaceInfo, &InitMessage,
	                                               sizeof(RNDIS_Initialize_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(RNDISInterfaceInfo, &InitMessageResponse,
	                                               sizeof(RNDIS_Initialize_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (InitMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;
	  
	RNDISInterfaceInfo->State.DeviceMaxPacketSize = InitMessageResponse.MaxTransferSize;
	
	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_Host_SetRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo, uint32_t Oid, void* Buffer, uint16_t Length)
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
	SetMessageData.SetMessage.RequestId      = RNDISInterfaceInfo->State.RequestID++;
			
	SetMessageData.SetMessage.Oid            = Oid;
	SetMessageData.SetMessage.InformationBufferLength = Length;
	SetMessageData.SetMessage.InformationBufferOffset = (sizeof(RNDIS_Set_Message_t) - sizeof(RNDIS_Message_Header_t));
	SetMessageData.SetMessage.DeviceVcHandle = 0;
	
	memcpy(&SetMessageData.ContigiousBuffer, Buffer, Length);

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(RNDISInterfaceInfo, &SetMessageData,
	                                               SetMessageData.SetMessage.MessageLength)) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(RNDISInterfaceInfo, &SetMessageResponse,
	                                               sizeof(RNDIS_Set_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (SetMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;
	  
	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_Host_QueryRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo, uint32_t Oid, void* Buffer, uint16_t MaxLength)
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
	QueryMessage.RequestId      = RNDISInterfaceInfo->State.RequestID++;
			
	QueryMessage.Oid            = Oid;
	QueryMessage.InformationBufferLength = 0;
	QueryMessage.InformationBufferOffset = 0;
	QueryMessage.DeviceVcHandle = 0;

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(RNDISInterfaceInfo, &QueryMessage,
	                                               sizeof(RNDIS_Query_Message_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}
	
	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(RNDISInterfaceInfo, &QueryMessageResponseData,
	                                               sizeof(QueryMessageResponseData))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (QueryMessageResponseData.QueryMessageResponse.Status != REMOTE_NDIS_STATUS_SUCCESS)
	  return RNDIS_COMMAND_FAILED;

	memcpy(Buffer, &QueryMessageResponseData.ContigiousBuffer, MaxLength);

	return HOST_SENDCONTROL_Successful;
}

bool RNDIS_Host_IsPacketReceived(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	bool PacketWaiting;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return false;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);
	Pipe_SetPipeToken(PIPE_TOKEN_IN);
	
	Pipe_Unfreeze();

	PacketWaiting = Pipe_IsINReceived();
	
	Pipe_Freeze();
	
	return PacketWaiting;
}

uint8_t RNDIS_Host_ReadPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo, void* Buffer, uint16_t* PacketLength)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);
	Pipe_SetPipeToken(PIPE_TOKEN_IN);
	Pipe_Unfreeze();
	
	if (!(Pipe_IsReadWriteAllowed()))
	{
		*PacketLength = 0;
		Pipe_Freeze();
		return PIPE_RWSTREAM_NoError;
	}

	RNDIS_Packet_Message_t DeviceMessage;
	
	if ((ErrorCode = Pipe_Read_Stream_LE(&DeviceMessage, sizeof(RNDIS_Packet_Message_t),
	                                     NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}

	*PacketLength = (uint16_t)DeviceMessage.DataLength;
	
	Pipe_Discard_Stream(DeviceMessage.DataOffset - (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t)),
	                    NO_STREAM_CALLBACK);
						
	Pipe_Read_Stream_LE(Buffer, *PacketLength, NO_STREAM_CALLBACK);
	Pipe_ClearIN();

	Pipe_Freeze();
	
	return PIPE_RWSTREAM_NoError;
}

uint8_t RNDIS_Host_SendPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo, void* Buffer, uint16_t PacketLength)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	if (RNDISInterfaceInfo->State.BidirectionalDataEndpoints)
	{
		Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);
		Pipe_SetPipeToken(PIPE_TOKEN_OUT);
	}
	else
	{
		Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataOUTPipeNumber);	
	}

	Pipe_Unfreeze();

	RNDIS_Packet_Message_t DeviceMessage;
	
	DeviceMessage.MessageType = REMOTE_NDIS_PACKET_MSG;
	DeviceMessage.MessageLength = (sizeof(RNDIS_Packet_Message_t) + PacketLength);
	DeviceMessage.DataOffset = (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t));
	DeviceMessage.DataLength = PacketLength;
	
	if ((ErrorCode = Pipe_Write_Stream_LE(&DeviceMessage, sizeof(RNDIS_Packet_Message_t),
	                                      NO_STREAM_CALLBACK)) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}
	
	Pipe_Write_Stream_LE(Buffer, PacketLength, NO_STREAM_CALLBACK);
	Pipe_ClearOUT();

	Pipe_Freeze();
	
	if (RNDISInterfaceInfo->State.BidirectionalDataEndpoints)
	  Pipe_SetPipeToken(PIPE_TOKEN_IN);
	
	return PIPE_RWSTREAM_NoError;
}

#endif
