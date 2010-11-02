/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define  __INCLUDE_FROM_CDC_DRIVER
#define  __INCLUDE_FROM_CDC_HOST_C
#include "CDC.h"

uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                                uint16_t ConfigDescriptorSize,
                                void* ConfigDescriptorData)
{
	USB_Descriptor_Endpoint_t*  DataINEndpoint       = NULL;
	USB_Descriptor_Endpoint_t*  DataOUTEndpoint      = NULL;
	USB_Descriptor_Endpoint_t*  NotificationEndpoint = NULL;
	USB_Descriptor_Interface_t* CDCControlInterface  = NULL;

	memset(&CDCInterfaceInfo->State, 0x00, sizeof(CDCInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return CDC_ENUMERROR_InvalidConfigDescriptor;

	while (!(DataINEndpoint) || !(DataOUTEndpoint) || !(NotificationEndpoint))
	{
		if (!(CDCControlInterface) ||
		    USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DCOMP_CDC_Host_NextCDCInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (NotificationEndpoint)
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DCOMP_CDC_Host_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCompatibleInterfaceFound;
				}

				DataINEndpoint  = NULL;
				DataOUTEndpoint = NULL;
			}
			else
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DCOMP_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCompatibleInterfaceFound;
				}

				CDCControlInterface = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Interface_t);

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
		if (PipeNum == CDCInterfaceInfo->Config.DataINPipeNumber)
		{
			Pipe_ConfigurePipe(PipeNum, EP_TYPE_BULK, PIPE_TOKEN_IN,
			                   DataINEndpoint->EndpointAddress, DataINEndpoint->EndpointSize,
			                   CDCInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);

			CDCInterfaceInfo->State.DataINPipeSize = DataINEndpoint->EndpointSize;
		}
		else if (PipeNum == CDCInterfaceInfo->Config.DataOUTPipeNumber)
		{
			Pipe_ConfigurePipe(PipeNum, EP_TYPE_BULK, PIPE_TOKEN_OUT,
			                   DataOUTEndpoint->EndpointAddress, DataOUTEndpoint->EndpointSize,
			                   CDCInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);

			CDCInterfaceInfo->State.DataOUTPipeSize = DataOUTEndpoint->EndpointSize;
		}
		else if (PipeNum == CDCInterfaceInfo->Config.NotificationPipeNumber)
		{
			Pipe_ConfigurePipe(PipeNum, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
			                   NotificationEndpoint->EndpointAddress, NotificationEndpoint->EndpointSize,
			                   CDCInterfaceInfo->Config.NotificationPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
			Pipe_SetInterruptPeriod(NotificationEndpoint->PollingIntervalMS);

			CDCInterfaceInfo->State.NotificationPipeSize = NotificationEndpoint->EndpointSize;
		}
	}

	CDCInterfaceInfo->State.ControlInterfaceNumber = CDCControlInterface->InterfaceNumber;
	CDCInterfaceInfo->State.ControlLineStates.HostToDevice = (CDC_CONTROL_LINE_OUT_RTS | CDC_CONTROL_LINE_OUT_DTR);
	CDCInterfaceInfo->State.ControlLineStates.DeviceToHost = (CDC_CONTROL_LINE_IN_DCD  | CDC_CONTROL_LINE_IN_DSR);
	CDCInterfaceInfo->State.IsActive = true;

	return CDC_ENUMERROR_NoError;
}

static uint8_t DCOMP_CDC_Host_NextCDCControlInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == CDC_CSCP_CDCClass)    &&
		    (Interface->SubClass == CDC_CSCP_ACMSubclass) &&
		    (Interface->Protocol == CDC_CSCP_ATCommandProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_CDC_Host_NextCDCDataInterface(void* const CurrentDescriptor)
{
	USB_Descriptor_Header_t* Header = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Header_t);

	if (Header->Type == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* Interface = DESCRIPTOR_PCAST(CurrentDescriptor, USB_Descriptor_Interface_t);

		if ((Interface->Class    == CDC_CSCP_CDCDataClass)   &&
		    (Interface->SubClass == CDC_CSCP_NoDataSubclass) &&
		    (Interface->Protocol == CDC_CSCP_NoDataProtocol))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}

	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DCOMP_CDC_Host_NextCDCInterfaceEndpoint(void* const CurrentDescriptor)
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

void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.NotificationPipeNumber);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		USB_Request_Header_t Notification;
		Pipe_Read_Stream_LE(&Notification, sizeof(USB_Request_Header_t), NO_STREAM_CALLBACK);

		if ((Notification.bRequest      == CDC_NOTIF_SerialState) &&
		    (Notification.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)))
		{
			Pipe_Read_Stream_LE(&CDCInterfaceInfo->State.ControlLineStates.DeviceToHost,
			                    sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
			                    NO_STREAM_CALLBACK);

			Pipe_ClearIN();

			EVENT_CDC_Host_ControLineStateChanged(CDCInterfaceInfo);
		}
		else
		{
			Pipe_ClearIN();
		}
	}

	Pipe_Freeze();

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	CDC_Host_Flush(CDCInterfaceInfo);
	#endif
}

uint8_t CDC_Host_SetLineEncoding(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = CDC_REQ_SetLineEncoding,
		.wValue        = 0,
		.wIndex        = CDCInterfaceInfo->State.ControlInterfaceNumber,
		.wLength       = sizeof(CDCInterfaceInfo->State.LineEncoding),
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(&CDCInterfaceInfo->State.LineEncoding);
}

uint8_t CDC_Host_SendControlLineStateChange(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = CDC_REQ_SetControlLineState,
		.wValue        = CDCInterfaceInfo->State.ControlLineStates.HostToDevice,
		.wIndex        = CDCInterfaceInfo->State.ControlInterfaceNumber,
		.wLength       = 0,
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t CDC_Host_SendBreak(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                           const uint8_t Duration)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = CDC_REQ_SendBreak,
		.wValue        = Duration,
		.wIndex        = CDCInterfaceInfo->State.ControlInterfaceNumber,
		.wLength       = 0,
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	return USB_Host_SendControlRequest(NULL);
}

uint8_t CDC_Host_SendString(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                            const char* const Data,
                            const uint16_t Length)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);

	Pipe_Unfreeze();
	ErrorCode = Pipe_Write_Stream_LE(Data, Length, NO_STREAM_CALLBACK);
	Pipe_Freeze();

	return ErrorCode;
}

uint8_t CDC_Host_SendByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                          const uint8_t Data)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);
	Pipe_Unfreeze();

	if (!(Pipe_IsReadWriteAllowed()))
	{
		Pipe_ClearOUT();

		if ((ErrorCode = Pipe_WaitUntilReady()) != PIPE_READYWAIT_NoError)
		  return ErrorCode;
	}

	Pipe_Write_Byte(Data);
	Pipe_Freeze();

	return PIPE_READYWAIT_NoError;
}

uint16_t CDC_Host_BytesReceived(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return 0;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);
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

int16_t CDC_Host_ReceiveByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return -1;

	int16_t ReceivedByte = -1;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		if (Pipe_BytesInPipe())
		  ReceivedByte = Pipe_Read_Byte();

		if (!(Pipe_BytesInPipe()))
		  Pipe_ClearIN();
	}

	Pipe_Freeze();

	return ReceivedByte;
}

uint8_t CDC_Host_Flush(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_DeviceDisconnected;

	uint8_t ErrorCode;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);
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

void CDC_Host_CreateStream(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                           FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(CDC_Host_putchar, CDC_Host_getchar, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, CDCInterfaceInfo);
}

void CDC_Host_CreateBlockingStream(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
                                   FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(CDC_Host_putchar, CDC_Host_getchar_Blocking, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, CDCInterfaceInfo);
}

static int CDC_Host_putchar(char c,
                            FILE* Stream)
{
	return CDC_Host_SendByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream), c) ? _FDEV_ERR : 0;
}

static int CDC_Host_getchar(FILE* Stream)
{
	int16_t ReceivedByte = CDC_Host_ReceiveByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream));

	if (ReceivedByte < 0)
	  return _FDEV_EOF;

	return ReceivedByte;
}

static int CDC_Host_getchar_Blocking(FILE* Stream)
{
	int16_t ReceivedByte;

	while ((ReceivedByte = CDC_Host_ReceiveByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream))) < 0)
	{
		if (USB_HostState == HOST_STATE_Unattached)
		  return _FDEV_EOF;

		CDC_Host_USBTask((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream));
		USB_USBTask();
	}

	return ReceivedByte;
}

void CDC_Host_Event_Stub(void)
{

}

#endif

