/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../Core/USBMode.h"

#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_RNDIS_DRIVER
#define  __INCLUDE_FROM_RNDIS_HOST_C
#include "RNDIS.h"

uint8_t RNDIS_Host_ConfigurePipes(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                  uint16_t ConfigDescriptorSize,
                                  void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint        = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint       = NULL;
	USB_Descriptor_Endpoint_t*  NotificationEndpoint  = NULL;
	USB_Descriptor_Interface_t* RNDISControlInterface = NULL;

	memset(&RNDISInterfaceInfo->State, 0x00, sizeof(RNDISInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return RNDIS_ENUMERROR_InvalidConfigDescriptor;

	RNDISControlInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

	while (!(DataINEndpoint) || !(DataOUTEndpoint) || !(NotificationEndpoint))
	{
		if (!(RNDISControlInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_RNDIS_Host_NextRNDISInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (NotificationEndpoint)
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
											  DCOMP_RNDIS_Host_NextRNDISDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return RNDIS_ENUMERROR_NoCompatibleInterfaceFound;
				}

				DataINEndpoint  = NULL;
				DataOUTEndpoint = NULL;
			}
			else
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
											  DCOMP_RNDIS_Host_NextRNDISControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return RNDIS_ENUMERROR_NoCompatibleInterfaceFound;
				}

				RNDISControlInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

				NotificationEndpoint = NULL;
			}

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
		{
			if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
			  NotificationEndpoint = EndpointData;
			else
			  DataINEndpoint = EndpointData;
		}
		else
		{
			DataOUTEndpoint = EndpointData;
		}
	}

	for (uint8_t PipeNum = 1; PipeNum < PIPE_TOTAL_PIPES; PipeNum++)
	{
		uint16_t Size;
		uint8_t  Type;
		uint8_t  Token;
		uint8_t  EndpointAddress;
		uint8_t  InterruptPeriod;
		bool     DoubleBanked;

		if (PipeNum == RNDISInterfaceInfo->Config.DataINPipeNumber)
		{
			Size            = DataINEndpoint->EndpointSize;
			EndpointAddress = DataINEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_IN;
			Type            = EP_TYPE_BULK;
			DoubleBanked    = RNDISInterfaceInfo->Config.DataINPipeDoubleBank;
			InterruptPeriod = 0;

			RNDISInterfaceInfo->State.DataINPipeSize = DataINEndpoint->EndpointSize;
		}
		else if (PipeNum == RNDISInterfaceInfo->Config.DataOUTPipeNumber)
		{
			Size            = DataOUTEndpoint->EndpointSize;
			EndpointAddress = DataOUTEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_OUT;
			Type            = EP_TYPE_BULK;
			DoubleBanked    = RNDISInterfaceInfo->Config.DataOUTPipeDoubleBank;
			InterruptPeriod = 0;

			RNDISInterfaceInfo->State.DataOUTPipeSize = DataOUTEndpoint->EndpointSize;
		}
		else if (PipeNum == RNDISInterfaceInfo->Config.NotificationPipeNumber)
		{
			Size            = NotificationEndpoint->EndpointSize;
			EndpointAddress = NotificationEndpoint->EndpointAddress;
			Token           = PIPE_TOKEN_IN;
			Type            = EP_TYPE_INTERRUPT;
			DoubleBanked    = RNDISInterfaceInfo->Config.NotificationPipeDoubleBank;
			InterruptPeriod = NotificationEndpoint->PollingIntervalMS;

			RNDISInterfaceInfo->State.NotificationPipeSize = NotificationEndpoint->EndpointSize;
		}
		else
		{
			continue;
		}
		
		if (!(Pipe_ConfigurePipe(PipeNum, Type, Token, EndpointAddress, Size,
		                         DoubleBanked ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE)))
		{
			return CDC_ENUMERROR_PipeConfigurationFailed;
		}
		
		if (InterruptPeriod)
		  Pipe_SetInterruptPeriod(InterruptPeriod);
	}

	RNDISInterfaceInfo->State.ControlInterfaceNumber = RNDISControlInterface->InterfaceNumber;
	RNDISInterfaceInfo->State.IsActive = true;

	return RNDIS_ENUMERROR_NoError;
}

static uint8_t DCOMP_RNDIS_Host_NextRNDISControlInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == CDC_CSCP_CDCClass)    &&
		    (Interface->SubClass == CDC_CSCP_ACMSubclass) &&
		    (Interface->Protocol == CDC_CSCP_VendorSpecificProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_RNDIS_Host_NextRNDISDataInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                         USB_Descriptor_Interface_t);

		if ((Interface->Class    == CDC_CSCP_CDCDataClass)   &&
		    (Interface->SubClass == CDC_CSCP_NoDataSubclass) &&
		    (Interface->Protocol == CDC_CSCP_NoDataProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_RNDIS_Host_NextRNDISInterfaceEndpoint(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (Endpoint->Attributes & EP_TYPE_MASK);

		if (((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT)) &&
		    !(Pipe_IsEndpointBound(Endpoint->EndpointAddress)))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t RNDIS_SendEncapsulatedCommand(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                             void* Buffer,
                                             const uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = RNDIS_REQ_SendEncapsulatedCommand,
			.wValue        = 0,
			.wIndex        = RNDISInterfaceInfo->State.ControlInterfaceNumber,
			.wLength       = Length,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(Buffer);
}

static uint8_t RNDIS_GetEncapsulatedResponse(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                             void* Buffer,
                                             const uint16_t Length)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = RNDIS_REQ_GetEncapsulatedResponse,
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
	  return RNDIS_ERROR_LOGICAL_CMD_FAILED;

	RNDISInterfaceInfo->State.DeviceMaxPacketSize = InitMessageResponse.MaxTransferSize;

	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_Host_SetRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                    const uint32_t Oid,
                                    void* Buffer,
                                    const uint16_t Length)
{
	uint8_t ErrorCode;

	struct
	{
		RNDIS_Set_Message_t SetMessage;
		uint8_t             ContiguousBuffer[Length];
	} SetMessageData;

	RNDIS_Set_Complete_t SetMessageResponse;

	SetMessageData.SetMessage.MessageType    = REMOTE_NDIS_SET_MSG;
	SetMessageData.SetMessage.MessageLength  = sizeof(RNDIS_Set_Message_t) + Length;
	SetMessageData.SetMessage.RequestId      = RNDISInterfaceInfo->State.RequestID++;

	SetMessageData.SetMessage.Oid            = Oid;
	SetMessageData.SetMessage.InformationBufferLength = Length;
	SetMessageData.SetMessage.InformationBufferOffset = (sizeof(RNDIS_Set_Message_t) - sizeof(RNDIS_Message_Header_t));
	SetMessageData.SetMessage.DeviceVcHandle = 0;

	memcpy(&SetMessageData.ContiguousBuffer, Buffer, Length);

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
	  return RNDIS_ERROR_LOGICAL_CMD_FAILED;

	return HOST_SENDCONTROL_Successful;
}

uint8_t RNDIS_Host_QueryRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                                      const uint32_t Oid,
                                      void* Buffer,
                                      const uint16_t MaxLength)
{
	uint8_t ErrorCode;

	RNDIS_Query_Message_t QueryMessage;

	struct
	{
		RNDIS_Query_Complete_t QueryMessageResponse;
		uint8_t                ContiguousBuffer[MaxLength];
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
	  return RNDIS_ERROR_LOGICAL_CMD_FAILED;

	memcpy(Buffer, &QueryMessageResponseData.ContiguousBuffer, MaxLength);

	return HOST_SENDCONTROL_Successful;
}

bool RNDIS_Host_IsPacketReceived(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	bool PacketWaiting;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return false;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);

	Pipe_Unfreeze();
	PacketWaiting = Pipe_IsINReceived();
	Pipe_Freeze();

	return PacketWaiting;
}

uint8_t RNDIS_Host_ReadPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                              void* Buffer,
                              uint16_t* const PacketLength)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	if (!(Pipe_IsReadWriteAllowed()))
	{
		if (Pipe_IsINReceived())
		  Pipe_ClearIN();

		*PacketLength = 0;
		Pipe_Freeze();
		return PIPE_RWSTREAM_NoError;
	}

	RNDIS_Packet_Message_t DeviceMessage;

	if ((ErrorCode = Pipe_Read_Stream_LE(&DeviceMessage, sizeof(RNDIS_Packet_Message_t),
	                                     NULL)) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}

	*PacketLength = (uint16_t)DeviceMessage.DataLength;

	Pipe_Discard_Stream(DeviceMessage.DataOffset -
	                    (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t)),
	                    NULL);

	Pipe_Read_Stream_LE(Buffer, *PacketLength, NULL);

	if (!(Pipe_BytesInPipe()))
	  Pipe_ClearIN();

	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

uint8_t RNDIS_Host_SendPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
                              void* Buffer,
                              const uint16_t PacketLength)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	RNDIS_Packet_Message_t DeviceMessage;

	memset(&DeviceMessage, 0, sizeof(RNDIS_Packet_Message_t));
	DeviceMessage.MessageType   = REMOTE_NDIS_PACKET_MSG;
	DeviceMessage.MessageLength = (sizeof(RNDIS_Packet_Message_t) + PacketLength);
	DeviceMessage.DataOffset    = (sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t));
	DeviceMessage.DataLength    = PacketLength;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(&DeviceMessage, sizeof(RNDIS_Packet_Message_t),
	                                      NULL)) != PIPE_RWSTREAM_NoError)
	{
		return ErrorCode;
	}

	Pipe_Write_Stream_LE(Buffer, PacketLength, NULL);
	Pipe_ClearOUT();

	Pipe_Freeze();

	return PIPE_RWSTREAM_NoError;
}

#endif

