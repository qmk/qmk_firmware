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

#define  INCLUDE_FROM_CDC_CLASS_C
#include "CDC.h"

void USB_CDC_Event_Stub(void)
{

}

void USB_CDC_ProcessControlPacket(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != CDCInterfaceInfo->ControlInterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Write_Control_Stream_LE(&CDCInterfaceInfo->LineEncoding, sizeof(CDCInterfaceInfo->LineEncoding));
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_Read_Control_Stream_LE(&CDCInterfaceInfo->LineEncoding, sizeof(CDCInterfaceInfo->LineEncoding));
				Endpoint_ClearIN();

				EVENT_USB_CDC_LineEncodingChanged(CDCInterfaceInfo);
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{				
				Endpoint_ClearSETUP();
				
				CDCInterfaceInfo->ControlLineState = USB_ControlRequest.wValue;
				
				EVENT_USB_CDC_ControLineStateChanged();

				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
	
			break;
	}
}

bool USB_CDC_ConfigureEndpoints(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->DataINEndpointNumber, EP_TYPE_BULK,
							         ENDPOINT_DIR_IN, CDCInterfaceInfo->DataINEndpointSize,
							         ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->DataOUTEndpointNumber, EP_TYPE_BULK,
	                                 ENDPOINT_DIR_OUT, CDCInterfaceInfo->DataOUTEndpointSize,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	if (!(Endpoint_ConfigureEndpoint(CDCInterfaceInfo->NotificationEndpointNumber, EP_TYPE_INTERRUPT,
	                                 ENDPOINT_DIR_IN, CDCInterfaceInfo->NotificationEndpointSize,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}

	return true;
}

void USB_CDC_USBTask(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	if (!(USB_IsConnected))
	  return;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->DataINEndpointNumber);

	if (!(Endpoint_BytesInEndpoint()))
	  return;
	  
	if (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearIN();
		while (!(Endpoint_IsReadWriteAllowed()));
	}	
	
	Endpoint_ClearIN();
}

void USB_CDC_SendString(USB_ClassInfo_CDC_t* CDCInterfaceInfo, char* Data, uint16_t Length)
{
	Endpoint_SelectEndpoint(CDCInterfaceInfo->DataINEndpointNumber);
	Endpoint_Write_Stream_LE(Data, Length, NO_STREAM_CALLBACK);
}

void USB_CDC_SendByte(USB_ClassInfo_CDC_t* CDCInterfaceInfo, uint8_t Data)
{
	if (!(USB_IsConnected))
	  return;

	Endpoint_SelectEndpoint(CDCInterfaceInfo->DataINEndpointNumber);

	if (!(Endpoint_IsReadWriteAllowed()))
	{
		Endpoint_ClearIN();
		while (!(Endpoint_IsReadWriteAllowed()));
	}

	Endpoint_Write_Byte(Data);	
}

uint16_t USB_CDC_BytesReceived(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	Endpoint_SelectEndpoint(CDCInterfaceInfo->DataOUTEndpointNumber);

	return Endpoint_BytesInEndpoint();
}

uint8_t USB_CDC_ReceiveByte(USB_ClassInfo_CDC_t* CDCInterfaceInfo)
{
	Endpoint_SelectEndpoint(CDCInterfaceInfo->DataOUTEndpointNumber);
	
	uint8_t DataByte = Endpoint_Read_Byte();
	
	if (!(Endpoint_BytesInEndpoint()))
	  Endpoint_ClearOUT();
	  
	return DataByte;
}

void USB_CDC_SendSerialLineStateChanged(USB_ClassInfo_CDC_t* CDCInterfaceInfo, uint16_t LineStateMask)
{
	Endpoint_SelectEndpoint(CDCInterfaceInfo->NotificationEndpointNumber);
	
	USB_Request_Header_t Notification = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = NOTIF_SerialState,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = sizeof(uint16_t),
		};

	Endpoint_Write_Stream_LE(&Notification, sizeof(Notification), NO_STREAM_CALLBACK);
	Endpoint_Write_Stream_LE(&LineStateMask, sizeof(LineStateMask), NO_STREAM_CALLBACK);
	Endpoint_ClearIN();
}
