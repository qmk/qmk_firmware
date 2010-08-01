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

#define  __INCLUDE_FROM_USB_DRIVER
#include "../../HighLevel/USBMode.h"
#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_CDC_CLASS_DEVICE_C
#define  __INCLUDE_FROM_CDC_DRIVER
#include "CDC.h"

void CDC_Device_Event_Stub(void)
{

}

void CDC_Device_ProcessControlRequest(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != CDCInterfaceInfo->Config.ControlInterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_Control_Stream_LE(&CDCInterfaceInfo->State.LineEncoding, sizeof(CDCInterfaceInfo->State.LineEncoding));
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Read_Control_Stream_LE(&CDCInterfaceInfo->State.LineEncoding, sizeof(CDCInterfaceInfo->State.LineEncoding));
				EVENT_CDC_Device_LineEncodingChanged(CDCInterfaceInfo);
				Endpoint_ClearIN();
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{				
				Endpoint_ClearSETUP();
				
				CDCInterfaceInfo->State.ControlLineStates.HostToDevice = USB_ControlRequest.wValue;
				EVENT_CDC_Device_ControLineStateChanged(CDCInterfaceInfo);

				Endpoint_ClearStatusStage();
			}
	
			break;
		case REQ_SendBreak:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{				
				Endpoint_ClearSETUP();
				
				EVENT_CDC_Device_BreakSent(CDCInterfaceInfo, (uint8_t)USB_ControlRequest.wValue);

				Endpoint_ClearStatusStage();
			}

			break;
	}
}

bool CDC_Device_ConfigureEndpoints(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	memset(&CDCInterfaceInfo->State, 0x00, sizeof(CDCInterfaceInfo->State));

	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber, EP_TYPE_BULK,
							         ENDPOINT_DIR_IN, CDCInterfaceInfo->Config.DataINEndpointSize,
							         CDCInterfaceInfo->Config.DataINEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->Config.DataOUTEndpointNumber, EP_TYPE_BULK,
	                                 ENDPOINT_DIR_OUT, CDCInterfaceInfo->Config.DataOUTEndpointSize,
	                                 CDCInterfaceInfo->Config.DataOUTEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->Config.NotificationEndpointNumber, EP_TYPE_INTERRUPT,
	                                 ENDPOINT_DIR_IN, CDCInterfaceInfo->Config.NotificationEndpointSize,
	                                 CDCInterfaceInfo->Config.NotificationEndpointDoubleBank ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	return true;
}

void CDC_Device_USBTask(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return;
	  
	CDC_Device_Flush(CDCInterfaceInfo);
}

uint8_t CDC_Device_SendString(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                              const char* const Data,
                              const uint16_t Length)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;
	
	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber);
	return Endpoint_Write_Stream_LE(Data, Length, NO_STREAM_CALLBACK);
}

uint8_t CDC_Device_SendByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                            const uint8_t Data)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber);

	if (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearIN();

		uint8_t ErrorCode;

		if ((ErrorCode = Endpoint_WaitUntilReady()) != ENDPOINT_READYWAIT_NoError)
		  return ErrorCode;
	}

	Endpoint_Write_Byte(Data);
	return ENDPOINT_READYWAIT_NoError;
}

uint8_t CDC_Device_Flush(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	uint8_t ErrorCode;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber);

	if (!(Endpoint_BytesInEndpoint()))
	  return ENDPOINT_READYWAIT_NoError;
	
	bool BankFull = !(Endpoint_IsReadWriteAllowed());
	
	Endpoint_ClearIN();
	
	if (BankFull)
	{
		if ((ErrorCode = Endpoint_WaitUntilReady()) != ENDPOINT_READYWAIT_NoError)
		  return ErrorCode;

		Endpoint_ClearIN();
	}
	
	return ENDPOINT_READYWAIT_NoError;
}

uint16_t CDC_Device_BytesReceived(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return 0;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataOUTEndpointNumber);

	if (Endpoint_IsOUTReceived())
	{
		if (!(Endpoint_BytesInEndpoint()))
		{
			Endpoint_ClearOUT();
			return 0;
		}
		else
		{
			return Endpoint_BytesInEndpoint();
		}
	}
	else
	{
		return 0;
	}
}

int16_t CDC_Device_ReceiveByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return -1;

	int16_t ReceivedByte = -1;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataOUTEndpointNumber);
	
	if (Endpoint_IsOUTReceived())
	{
		if (Endpoint_BytesInEndpoint())
		  ReceivedByte = Endpoint_Read_Byte();
	
		if (!(Endpoint_BytesInEndpoint()))
		  Endpoint_ClearOUT();
	}
	
	return ReceivedByte;
}

void CDC_Device_SendControlLineStateChange(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.NotificationEndpointNumber);
	
	USB_Request_Header_t Notification = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = NOTIF_SerialState,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
		};

	Endpoint_Write_Stream_LE(&Notification, sizeof(USB_Request_Header_t), NO_STREAM_CALLBACK);
	Endpoint_Write_Stream_LE(&CDCInterfaceInfo->State.ControlLineStates.DeviceToHost,
	                         sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
	                         NO_STREAM_CALLBACK);
	Endpoint_ClearIN();
}

void CDC_Device_CreateStream(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                             FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(CDC_Device_putchar, CDC_Device_getchar, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, CDCInterfaceInfo);
}

void CDC_Device_CreateBlockingStream(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                                     FILE* const Stream)
{
	*Stream = (FILE)FDEV_SETUP_STREAM(CDC_Device_putchar, CDC_Device_getchar_Blocking, _FDEV_SETUP_RW);
	fdev_set_udata(Stream, CDCInterfaceInfo);
}

static int CDC_Device_putchar(char c,
                              FILE* Stream)
{
	return CDC_Device_SendByte((USB_ClassInfo_CDC_Device_t*)fdev_get_udata(Stream), c) ? _FDEV_ERR : 0;
}

static int CDC_Device_getchar(FILE* Stream)
{
	int16_t ReceivedByte = CDC_Device_ReceiveByte((USB_ClassInfo_CDC_Device_t*)fdev_get_udata(Stream));

	if (ReceivedByte < 0)
	  return _FDEV_EOF;

	return ReceivedByte;
}

static int CDC_Device_getchar_Blocking(FILE* Stream)
{
	int16_t ReceivedByte;
	
	while ((ReceivedByte = CDC_Device_ReceiveByte((USB_ClassInfo_CDC_Device_t*)fdev_get_udata(Stream))) < 0)
	{
		if (USB_DeviceState == DEVICE_STATE_Unattached)
		  return _FDEV_EOF;
	
		CDC_Device_USBTask((USB_ClassInfo_CDC_Device_t*)fdev_get_udata(Stream));
		USB_USBTask();	
	}

	return ReceivedByte;
}

#endif
