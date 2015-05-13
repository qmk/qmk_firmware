/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

#define  __INCLUDE_FROM_PRINTER_DRIVER
#define  __INCLUDE_FROM_PRINTER_HOST_C
#include "PrinterClassHost.h"

uint8_t PRNT_Host_ConfigurePipes(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                                 uint16_t ConfigDescriptorSize,
							     void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint   = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint  = NULL;
	USB_Descriptor_Interface_t* PrinterInterface = NULL;

	memset(&PRNTInterfaceInfo->State, 0x00, sizeof(PRNTInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return PRNT_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint))
	{
		if (!(PrinterInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_PRNT_Host_NextPRNTInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DCOMP_PRNT_Host_NextPRNTInterface) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return PRNT_ENUMERROR_NoCompatibleInterfaceFound;
			}

			PrinterInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

			DataINEndpoint  = NULL;
			DataOUTEndpoint = NULL;

			continue;
		}

		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->EndpointAddress & ENDPOINT_DIR_MASK) == ENDPOINT_DIR_IN)
		  DataINEndpoint  = EndpointData;
		else
		  DataOUTEndpoint = EndpointData;
	}

	PRNTInterfaceInfo->Config.DataINPipe.Size  = le16_to_cpu(DataINEndpoint->EndpointSize);
	PRNTInterfaceInfo->Config.DataINPipe.EndpointAddress = DataINEndpoint->EndpointAddress;
	PRNTInterfaceInfo->Config.DataINPipe.Type  = EP_TYPE_BULK;

	PRNTInterfaceInfo->Config.DataOUTPipe.Size = le16_to_cpu(DataOUTEndpoint->EndpointSize);
	PRNTInterfaceInfo->Config.DataOUTPipe.EndpointAddress = DataOUTEndpoint->EndpointAddress;
	PRNTInterfaceInfo->Config.DataOUTPipe.Type = EP_TYPE_BULK;

	if (!(Pipe_ConfigurePipeTable(&PRNTInterfaceInfo->Config.DataINPipe, 1)))
	  return PRNT_ENUMERROR_PipeConfigurationFailed;

	if (!(Pipe_ConfigurePipeTable(&PRNTInterfaceInfo->Config.DataOUTPipe, 1)))
	  return PRNT_ENUMERROR_PipeConfigurationFailed;

	PRNTInterfaceInfo->State.InterfaceNumber  = PrinterInterface->InterfaceNumber;
	PRNTInterfaceInfo->State.AlternateSetting = PrinterInterface->AlternateSetting;
	PRNTInterfaceInfo->State.IsActive = true;

	return PRNT_ENUMERROR_NoError;
}

static uint8_t DCOMP_PRNT_Host_NextPRNTInterface(void* CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == PRNT_CSCP_PrinterClass)    &&
		    (Interface->SubClass == PRNT_CSCP_PrinterSubclass) &&
		    (Interface->Protocol == PRNT_CSCP_BidirectionalProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_PRNT_Host_NextPRNTInterfaceEndpoint(void* CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* Endpoint = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Endpoint_t);

		uint8_t EndpointType = (Endpoint->Attributes & EP_TYPE_MASK);

		if (EndpointType == EP_TYPE_BULK)
		  return DESCRIPTOR_SEARCH_Found;
	}
	else if (Header->Type == DTYPE_Interface)
	{
		return DESCRIPTOR_SEARCH_Fail;
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

void PRNT_Host_USBTask(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return;

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	PRNT_Host_Flush(PRNTInterfaceInfo);
	#endif
}

uint8_t PRNT_Host_SetBidirectionalMode(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if (PRNTInterfaceInfo->State.AlternateSetting)
	{
		uint8_t ErrorCode;

		if ((ErrorCode = USB_Host_SetInterfaceAltSetting(PRNTInterfaceInfo->State.InterfaceNumber,
		                                                 PRNTInterfaceInfo->State.AlternateSetting)) != HOST_SENDCONTROL_Successful)
		{
			return ErrorCode;
		}
	}

	return HOST_SENDCONTROL_Successful;
}

uint8_t PRNT_Host_GetPortStatus(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                                uint8_t* const PortStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = PRNT_REQ_GetPortStatus,
			.wValue        = 0,
			.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength       = sizeof(uint8_t),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(PortStatus);
}

uint8_t PRNT_Host_SoftReset(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = PRNT_REQ_SoftReset,
			.wValue        = 0,
			.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength       = 0,
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	return USB_Host_SendControlRequest(NULL);
}

uint8_t PRNT_Host_Flush(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if (!(Pipe_BytesInPipe()))
	  return PIPE_READYWAIT_NoError;

	bool BankFull = !(Pipe_IsReadWriteAllowed());

	Pipe_ClearOUT();

	if (BankFull)
	{
		if ((ErrorCode = Pipe_WaitUntilReady()) != PIPE_READYWAIT_NoError)
		  return ErrorCode;

		Pipe_ClearOUT();
	}

	Pipe_Freeze();

	return PIPE_READYWAIT_NoError;
}

uint8_t PRNT_Host_SendByte(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                           const uint8_t Data)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if (!(Pipe_IsReadWriteAllowed()))
	{
		Pipe_ClearOUT();

		if ((ErrorCode = Pipe_WaitUntilReady()) != PIPE_READYWAIT_NoError)
		  return ErrorCode;
	}

	Pipe_Write_8(Data);
	Pipe_Freeze();

	return PIPE_READYWAIT_NoError;
}

uint8_t PRNT_Host_SendString(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                             const char* const String)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(String, strlen(String), NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();

	ErrorCode = Pipe_WaitUntilReady();

	Pipe_Freeze();

	return ErrorCode;
}

uint8_t PRNT_Host_SendData(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                           const void* Buffer,
                           const uint16_t Length)
{
	uint8_t ErrorCode;

	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataOUTPipe.Address);
	Pipe_Unfreeze();

	if ((ErrorCode = Pipe_Write_Stream_LE(Buffer, Length, NULL)) != PIPE_RWSTREAM_NoError)
	  return ErrorCode;

	Pipe_ClearOUT();

	ErrorCode = Pipe_WaitUntilReady();

	Pipe_Freeze();

	return ErrorCode;
}

uint16_t PRNT_Host_BytesReceived(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return 0;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataINPipe.Address);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		if (!(Pipe_BytesInPipe()))
		{
			Pipe_ClearIN();
			Pipe_Freeze();
			return 0;
		}
		else
		{
			Pipe_Freeze();
			return Pipe_BytesInPipe();
		}
	}
	else
	{
		Pipe_Freeze();

		return 0;
	}
}

int16_t PRNT_Host_ReceiveByte(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(PRNTInterfaceInfo->State.IsActive))
	  return PIPE_RWSTREAM_DeviceDisconnected;

	int16_t ReceivedByte = -1;

	Pipe_SelectPipe(PRNTInterfaceInfo->Config.DataINPipe.Address);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		if (Pipe_BytesInPipe())
		  ReceivedByte = Pipe_Read_8();

		if (!(Pipe_BytesInPipe()))
		  Pipe_ClearIN();
	}

	Pipe_Freeze();

	return ReceivedByte;
}

uint8_t PRNT_Host_GetDeviceID(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
                              char* const DeviceIDString,
                              const uint16_t BufferSize)
{
	uint8_t  ErrorCode;
	uint16_t DeviceIDStringLength = 0;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = PRNT_REQ_GetDeviceID,
			.wValue        = 0,
			.wIndex        = PRNTInterfaceInfo->State.InterfaceNumber,
			.wLength       = sizeof(DeviceIDStringLength),
		};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	if ((ErrorCode = USB_Host_SendControlRequest(&DeviceIDStringLength)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	if (!(DeviceIDStringLength))
	{
		DeviceIDString[0] = 0x00;
		return HOST_SENDCONTROL_Successful;
	}

	DeviceIDStringLength = be16_to_cpu(DeviceIDStringLength);

	if (DeviceIDStringLength > BufferSize)
	  DeviceIDStringLength = BufferSize;

	USB_ControlRequest.wLength = DeviceIDStringLength;

	if ((ErrorCode = USB_Host_SendControlRequest(DeviceIDString)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;

	memmove(&DeviceIDString[0], &DeviceIDString[2], DeviceIDStringLength - 2);

	DeviceIDString[DeviceIDStringLength - 2] = 0x00;

	return HOST_SENDCONTROL_Successful;
}

#endif

