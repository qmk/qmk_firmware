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

#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_HOST)

#define  INCLUDE_FROM_CDC_CLASS_HOST_C
#include "CDC.h"

uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, uint16_t ConfigDescriptorSize,
                                void* ConfigDescriptorData)
{
	uint8_t FoundEndpoints = 0;

	memset(&CDCInterfaceInfo->State, 0x00, sizeof(CDCInterfaceInfo->State));

	if (DESCRIPTOR_TYPE(ConfigDescriptorData) != DTYPE_Configuration)
	  return CDC_ENUMERROR_InvalidConfigDescriptor;
	
	if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
	                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
	{
		return CDC_ENUMERROR_NoCDCInterfaceFound;
	}
	
	CDCInterfaceInfo->State.ControlInterfaceNumber = DESCRIPTOR_CAST(ConfigDescriptorData, USB_Descriptor_Interface_t).InterfaceNumber;

	while (FoundEndpoints != (CDC_FOUND_NOTIFICATION_IN | CDC_FOUND_DATAPIPE_IN | CDC_FOUND_DATAPIPE_OUT))
	{
		if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
		                              DComp_CDC_Host_NextCDCInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
		{
			if (FoundEndpoints & CDC_FOUND_NOTIFICATION_IN)
			{
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData, 
				                              DComp_CDC_Host_NextCDCDataInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCDCInterfaceFound;
				}
			}
			else
			{
				FoundEndpoints = 0;

				Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);
				Pipe_DisablePipe();
				Pipe_SelectPipe(CDCInterfaceInfo->Config.NotificationPipeNumber);
				Pipe_DisablePipe();
			
				if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
				                              DComp_CDC_Host_NextCDCControlInterface) != DESCRIPTOR_SEARCH_COMP_Found)
				{
					return CDC_ENUMERROR_NoCDCInterfaceFound;
				}
			}

			if (USB_GetNextDescriptorComp(&ConfigDescriptorSize, &ConfigDescriptorData,
			                              DComp_CDC_Host_NextCDCInterfaceEndpoint) != DESCRIPTOR_SEARCH_COMP_Found)
			{
				return CDC_ENUMERROR_EndpointsNotFound;
			}
		}
		
		USB_Descriptor_Endpoint_t* EndpointData = DESCRIPTOR_PCAST(ConfigDescriptorData, USB_Descriptor_Endpoint_t);

		if ((EndpointData->Attributes & EP_TYPE_MASK) == EP_TYPE_INTERRUPT)
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{							   
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.NotificationPipeNumber, EP_TYPE_INTERRUPT, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize,
								   CDCInterfaceInfo->Config.NotificationPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.NotificationPipeSize = EndpointData->EndpointSize;

				Pipe_SetInterruptPeriod(EndpointData->PollingIntervalMS);
				
				FoundEndpoints |= CDC_FOUND_NOTIFICATION_IN;
			}
		}
		else
		{
			if (EndpointData->EndpointAddress & ENDPOINT_DESCRIPTOR_DIR_IN)
			{
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.DataINPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_IN,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, 
								   CDCInterfaceInfo->Config.DataINPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.DataINPipeSize = EndpointData->EndpointSize;

				FoundEndpoints |= CDC_FOUND_DATAPIPE_IN;
			}
			else
			{
				Pipe_ConfigurePipe(CDCInterfaceInfo->Config.DataOUTPipeNumber, EP_TYPE_BULK, PIPE_TOKEN_OUT,
								   EndpointData->EndpointAddress, EndpointData->EndpointSize, 
								   CDCInterfaceInfo->Config.DataOUTPipeDoubleBank ? PIPE_BANK_DOUBLE : PIPE_BANK_SINGLE);
				CDCInterfaceInfo->State.DataOUTPipeSize = EndpointData->EndpointSize;
				
				FoundEndpoints |= CDC_FOUND_DATAPIPE_OUT;
			}
		}
	}

	CDCInterfaceInfo->State.ControlLineStates.HostToDevice = (CDC_CONTROL_LINE_OUT_RTS | CDC_CONTROL_LINE_OUT_DTR);
	CDCInterfaceInfo->State.ControlLineStates.DeviceToHost = (CDC_CONTROL_LINE_IN_DCD  | CDC_CONTROL_LINE_IN_DSR);
	CDCInterfaceInfo->State.IsActive = true;
	return CDC_ENUMERROR_NoError;
}

static uint8_t DComp_CDC_Host_NextCDCControlInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == CDC_CONTROL_CLASS)    &&
		    (CurrentInterface->SubClass == CDC_CONTROL_SUBCLASS) &&
			(CurrentInterface->Protocol == CDC_CONTROL_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_CDC_Host_NextCDCDataInterface(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Interface)
	{
		USB_Descriptor_Interface_t* CurrentInterface = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                                USB_Descriptor_Interface_t);
	
		if ((CurrentInterface->Class    == CDC_DATA_CLASS)    &&
		    (CurrentInterface->SubClass == CDC_DATA_SUBCLASS) &&
			(CurrentInterface->Protocol == CDC_DATA_PROTOCOL))
		{
			return DESCRIPTOR_SEARCH_Found;
		}
	}
	
	return DESCRIPTOR_SEARCH_NotFound;
}

static uint8_t DComp_CDC_Host_NextCDCInterfaceEndpoint(void* const CurrentDescriptor)
{
	if (DESCRIPTOR_TYPE(CurrentDescriptor) == DTYPE_Endpoint)
	{
		USB_Descriptor_Endpoint_t* CurrentEndpoint = DESCRIPTOR_PCAST(CurrentDescriptor,
		                                                              USB_Descriptor_Endpoint_t);
	
		uint8_t EndpointType = (CurrentEndpoint->Attributes & EP_TYPE_MASK);
	
		if (((EndpointType == EP_TYPE_BULK) || (EndpointType == EP_TYPE_INTERRUPT)) &&
		    !(Pipe_IsEndpointBound(CurrentEndpoint->EndpointAddress)))
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
		
		if ((Notification.bRequest      == NOTIF_SerialState) &&
		    (Notification.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)))
		{
			Pipe_Read_Stream_LE(&CDCInterfaceInfo->State.ControlLineStates.DeviceToHost,
			                    sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
			                    NO_STREAM_CALLBACK);
			
		}

		Pipe_ClearIN();

		EVENT_CDC_Host_ControLineStateChanged(CDCInterfaceInfo);
	}
	
	Pipe_Freeze();
}

uint8_t CDC_Host_SetLineEncoding(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	USB_ControlRequest = (USB_Request_Header_t)
	{
		.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
		.bRequest      = REQ_SetLineEncoding,
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
		.bRequest      = REQ_SetControlLineState,
		.wValue        = CDCInterfaceInfo->State.ControlLineStates.HostToDevice,
		.wIndex        = CDCInterfaceInfo->State.ControlInterfaceNumber,
		.wLength       = 0,
	};

	Pipe_SelectPipe(PIPE_CONTROLPIPE);
	
	return USB_Host_SendControlRequest(NULL);
}

uint8_t CDC_Host_SendString(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, char* Data, const uint16_t Length)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_NoError;

	uint8_t ErrorCode;

	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataOUTPipeNumber);	
	Pipe_Unfreeze();
	ErrorCode = Pipe_Write_Stream_LE(Data, Length, NO_STREAM_CALLBACK);
	Pipe_Freeze();
	
	return ErrorCode;
}

uint8_t CDC_Host_SendByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo, const uint8_t Data)
{
	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return PIPE_READYWAIT_NoError;;
	  
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
	uint16_t BytesInPipe = 0;

	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return BytesInPipe;
	
	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);	
	Pipe_Unfreeze();

	if (Pipe_IsINReceived() && !(Pipe_BytesInPipe()))
	  Pipe_ClearIN();
	
	BytesInPipe = Pipe_BytesInPipe();
	Pipe_Freeze();
	
	return BytesInPipe;
}

uint8_t CDC_Host_ReceiveByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
{
	uint8_t ReceivedByte = 0;

	if ((USB_HostState != HOST_STATE_Configured) || !(CDCInterfaceInfo->State.IsActive))
	  return ReceivedByte;
	  
	Pipe_SelectPipe(CDCInterfaceInfo->Config.DataINPipeNumber);	
	Pipe_Unfreeze();

	ReceivedByte = Pipe_Read_Byte();
	
	if (!(Pipe_BytesInPipe()))
	  Pipe_ClearIN();
	
	Pipe_Freeze();
	
	return ReceivedByte;
}

void CDC_Host_CreateStream(USB_ClassInfo_CDC_Host_t* CDCInterfaceInfo, FILE* Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(CDC_Host_putchar, CDC_Host_getchar, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, CDCInterfaceInfo);
}

static int CDC_Host_putchar(char c, FILE* Stream)
{
	return CDC_Host_SendByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream), c) ? _FDEV_ERR : 0;
}

static int CDC_Host_getchar(FILE* Stream)
{
	if (!(CDC_Host_BytesReceived((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream))))
	  return _FDEV_EOF;

	return CDC_Host_ReceiveByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream));
}

static int CDC_Host_getchar_Blocking(FILE* Stream)
{
	while (!(CDC_Host_BytesReceived((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream))))
	{
		CDC_Host_USBTask((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream));
		USB_USBTask();
	}

	return CDC_Host_ReceiveByte((USB_ClassInfo_CDC_Host_t*)fdev_get_udata(Stream));
}

void CDC_Host_Event_Stub(void)
{

}

#endif
