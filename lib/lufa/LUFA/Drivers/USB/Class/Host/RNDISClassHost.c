/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
#include "RNDISClassHost.h"

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

		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
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

	RNDISInterfaceInfo->Config.DataINPipe.Size  = le16_to_cpu(DataINEndpoint->EndpointSize);
	RNDISInterfaceInfo->Config.DataINPipe.EndpointAddress = DataINEndpoint->EndpointAddress;
	RNDISInterfaceInfo->Config.DataINPipe.Type  = EP_TYPE_BULK;

	RNDISInterfaceInfo->Config.DataOUTPipe.Size = le16_to_cpu(DataOUTEndpoint->EndpointSize);
	RNDISInterfaceInfo->Config.DataOUTPipe.EndpointAddress = DataOUTEndpoint->EndpointAddress;
	RNDISInterfaceInfo->Config.DataOUTPipe.Type = EP_TYPE_BULK;

	RNDISInterfaceInfo->Config.NotificationPipe.Size = le16_to_cpu(NotificationEndpoint->EndpointSize);
	RNDISInterfaceInfo->Config.NotificationPipe.EndpointAddress = NotificationEndpoint->EndpointAddress;
	RNDISInterfaceInfo->Config.NotificationPipe.Type = EP_TYPE_INTERRUPT;

	if (!(Pipe_ConfigurePipeTable(&RNDISInterfaceInfo->Config.DataINPipe, 1)))
	  return RNDIS_ENUMERROR_PipeConfigurationFailed;

	if (!(Pipe_ConfigurePipeTable(&RNDISInterfaceInfo->Config.DataOUTPipe, 1)))
	  return RNDIS_ENUMERROR_PipeConfigurationFailed;

	if (!(Pipe_ConfigurePipeTable(&RNDISInterfaceInfo->Config.NotificationPipe, 1)))
	  return RNDIS_ENUMERROR_PipeConfigurationFailed;

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

	KeepAliveMessage.MessageType     = CPU_TO_LE32(REMOTE_NDIS_KEEPALIVE_MSG);
	KeepAliveMessage.MessageLength   = CPU_TO_LE32(sizeof(RNDIS_KeepAlive_Message_t));
	KeepAliveMessage.RequestId       = cpu_to_le32(RNDISInterfaceInfo->State.RequestID++);

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

	InitMessage.MessageType     = CPU_TO_LE32(REMOTE_NDIS_INITIALIZE_MSG);
	InitMessage.MessageLength   = CPU_TO_LE32(sizeof(RNDIS_Initialize_Message_t));
	InitMessage.RequestId       = cpu_to_le32(RNDISInterfaceInfo->State.RequestID++);

	InitMessage.MajorVersion    = CPU_TO_LE32(REMOTE_NDIS_VERSION_MAJOR);
	InitMessage.MinorVersion    = CPU_TO_LE32(REMOTE_NDIS_VERSION_MINOR);
	InitMessage.MaxTransferSize = cpu_to_le32(RNDISInterfaceInfo->Config.HostMaxPacketSize);

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

	if (InitMessageResponse.Status != CPU_TO_LE32(REMOTE_NDIS_STATUS_SUCCESS))
	  return RNDIS_ERROR_LOGICAL_CMD_FAILED;

	RNDISInterfaceInfo->State.DeviceMaxPacketSize = le32_to_cpu(InitMessageResponse.MaxTransferSize);

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

	SetMessageData.SetMessage.MessageType    = CPU_TO_LE32(REMOTE_NDIS_SET_MSG);
	SetMessageData.SetMessage.MessageLength  = cpu_to_le32(sizeof(RNDIS_Set_Message_t) + Length);
	SetMessageData.SetMessage.RequestId      = cpu_to_le32(RNDISInterfaceInfo->State.RequestID++);

	SetMessageData.SetMessage.Oid            = cpu_to_le32(Oid);
	SetMessageData.SetMessage.InformationBufferLength = cpu_to_le32(Length);
	SetMessageData.SetMessage.InformationBufferOffset = CPU_TO_LE32(sizeof(RNDIS_Set_Message_t) - sizeof(RNDIS_Message_Header_t));
	SetMessageData.SetMessage.DeviceVcHandle = CPU_TO_LE32(0);

	memcpy(&SetMessageData.ContiguousBuffer, Buffer, Length);

	if ((ErrorCode = RNDIS_SendEncapsulatedCommand(RNDISInterfaceInfo, &SetMessageData,
	                                               (sizeof(RNDIS_Set_Message_t) + Length))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if ((ErrorCode = RNDIS_GetEncapsulatedResponse(RNDISInterfaceInfo, &SetMessageResponse,
	                                               sizeof(RNDIS_Set_Complete_t))) != HOST_SENDCONTROL_Successful)
	{
		return ErrorCode;
	}

	if (SetMessageResponse.Status != CPU_TO_LE32(REMOTE_NDIS_STATUS_SUCCESS))
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

	QueryMessage.MessageType    = CPU_TO_LE32(REMOTE_NDIS_QUERY_MSG);
	QueryMessage.MessageLength  = CPU_TO_LE32(sizeof(RNDIS_Query_Message_t));
	QueryMessage.RequestId      = cpu_to_le32(RNDISInterfaceInfo->State.RequestID++);

	QueryMessage.Oid            = cpu_to_le32(Oid);
	QueryMessage.InformationBufferLength = CPU_TO_LE32(0);
	QueryMessage.InformationBufferOffset = CPU_TO_LE32(0);
	QueryMessage.DeviceVcHandle = CPU_TO_LE32(0);

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

	if (QueryMessageResponseData.QueryMessageResponse.Status != CPU_TO_LE32(REMOTE_NDIS_STATUS_SUCCESS))
	  return RNDIS_ERROR_LOGICAL_CMD_FAILED;

	memcpy(Buffer, &QueryMessageResponseData.ContiguousBuffer, MaxLength);

	return HOST_SENDCONTROL_Successful;
}

bool RNDIS_Host_IsPacketReceived(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
{
	bool PacketWaiting;

	if ((USB_HostState != HOST_STATE_Configured) || !(RNDISInterfaceInfo->State.IsActive))
	  return false;

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipe.Address);

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

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataINPipe.Address);
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

	*PacketLength = (uint16_t)le32_to_cpu(DeviceMessage.DataLength);

	Pipe_Discard_Stream(le32_to_cpu(DeviceMessage.DataOffset) -
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
	DeviceMessage.MessageType   = CPU_TO_LE32(REMOTE_NDIS_PACKET_MSG);
	DeviceMessage.MessageLength = CPU_TO_LE32(sizeof(RNDIS_Packet_Message_t) + PacketLength);
	DeviceMessage.DataOffset    = CPU_TO_LE32(sizeof(RNDIS_Packet_Message_t) - sizeof(RNDIS_Message_Header_t));
	DeviceMessage.DataLength    = cpu_to_le32(PacketLength);

	Pipe_SelectPipe(RNDISInterfaceInfo->Config.DataOUTPipe.Address);
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

