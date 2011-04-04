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

#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_CDC_DRIVER
#define  __INCLUDE_FROM_CDC_DEVICE_C
#include "CDC.h"

void CDC_Device_ProcessControlRequest(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;

	if (USB_ControlRequest.wIndex != CDCInterfaceInfo->Config.ControlInterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case CDC_REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_Control_Stream_LE(&CDCInterfaceInfo->State.LineEncoding, sizeof(CDCInterfaceInfo->State.LineEncoding));
				Endpoint_ClearOUT();
			}

			break;
		case CDC_REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Read_Control_Stream_LE(&CDCInterfaceInfo->State.LineEncoding, sizeof(CDCInterfaceInfo->State.LineEncoding));
				Endpoint_ClearIN();

				EVENT_CDC_Device_LineEncodingChanged(CDCInterfaceInfo);
			}

			break;
		case CDC_REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				CDCInterfaceInfo->State.ControlLineStates.HostToDevice = USB_ControlRequest.wValue;

				EVENT_CDC_Device_ControLineStateChanged(CDCInterfaceInfo);
			}

			break;
		case CDC_REQ_SendBreak:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				EVENT_CDC_Device_BreakSent(CDCInterfaceInfo, (uint8_t)USB_ControlRequest.wValue);
			}

			break;
	}
}

bool CDC_Device_ConfigureEndpoints(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	memset(&CDCInterfaceInfo->State, 0x00, sizeof(CDCInterfaceInfo->State));

	for (uint8_t EndpointNum = 1; EndpointNum < ENDPOINT_TOTAL_ENDPOINTS; EndpointNum++)
	{
		uint16_t Size;
		uint8_t  Type;
		uint8_t  Direction;
		bool     DoubleBanked;

		if (EndpointNum == CDCInterfaceInfo->Config.DataINEndpointNumber)
		{
			Size         = CDCInterfaceInfo->Config.DataINEndpointSize;
			Direction    = ENDPOINT_DIR_IN;
			Type         = EP_TYPE_BULK;
			DoubleBanked = CDCInterfaceInfo->Config.DataINEndpointDoubleBank;
		}
		else if (EndpointNum == CDCInterfaceInfo->Config.DataOUTEndpointNumber)
		{
			Size         = CDCInterfaceInfo->Config.DataOUTEndpointSize;
			Direction    = ENDPOINT_DIR_OUT;
			Type         = EP_TYPE_BULK;
			DoubleBanked = CDCInterfaceInfo->Config.DataOUTEndpointDoubleBank;
		}
		else if (EndpointNum == CDCInterfaceInfo->Config.NotificationEndpointNumber)
		{
			Size         = CDCInterfaceInfo->Config.NotificationEndpointSize;
			Direction    = ENDPOINT_DIR_IN;
			Type         = EP_TYPE_INTERRUPT;
			DoubleBanked = CDCInterfaceInfo->Config.NotificationEndpointDoubleBank;
		}
		else
		{
			continue;
		}

		if (!(Endpoint_ConfigureEndpoint(EndpointNum, Type, Direction, Size,
		                                 DoubleBanked ? ENDPOINT_BANK_DOUBLE : ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}

	return true;
}

void CDC_Device_USBTask(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return;

	#if !defined(NO_CLASS_DRIVER_AUTOFLUSH)
	CDC_Device_Flush(CDCInterfaceInfo);
	#endif
}

uint8_t CDC_Device_SendString(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                              const char* const String)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber);
	return Endpoint_Write_Stream_LE(String, strlen(String), NULL);
}

uint8_t CDC_Device_SendData(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
                            const char* const Buffer,
                            const uint16_t Length)
{
	if ((USB_DeviceState != DEVICE_STATE_Configured) || !(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS))
	  return ENDPOINT_RWSTREAM_DeviceDisconnected;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->Config.DataINEndpointNumber);
	return Endpoint_Write_Stream_LE(Buffer, Length, NULL);
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

	Endpoint_Write_8(Data);
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
		  ReceivedByte = Endpoint_Read_8();

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
			.bRequest      = CDC_NOTIF_SerialState,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
		};

	Endpoint_Write_Stream_LE(&Notification, sizeof(USB_Request_Header_t), NULL);
	Endpoint_Write_Stream_LE(&CDCInterfaceInfo->State.ControlLineStates.DeviceToHost,
	                         sizeof(CDCInterfaceInfo->State.ControlLineStates.DeviceToHost),
	                         NULL);
	Endpoint_ClearIN();
}

#if defined(FDEV_SETUP_STREAM)
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

void CDC_Device_Event_Stub(void)
{

}

#endif

