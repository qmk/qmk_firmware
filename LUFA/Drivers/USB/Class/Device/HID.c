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

#include "HID.h"

void USB_HID_ProcessControlPacket(USB_ClassInfo_HID_t* HIDInterfaceInfo)
{
	if (!(Endpoint_IsSETUPReceived()))
	  return;
	  
	if (USB_ControlRequest.wIndex != HIDInterfaceInfo->InterfaceNumber)
	  return;

	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();	

				uint8_t  ReportINData[HIDInterfaceInfo->ReportINBufferSize];
				uint16_t ReportINSize;

				memset(ReportINData, 0, sizeof(ReportINData));

				ReportINSize = CALLBACK_USB_HID_CreateNextHIDReport(HIDInterfaceInfo, ReportINData);

				Endpoint_Write_Control_Stream_LE(ReportINData, ReportINSize);
				Endpoint_ClearOUT();
			}
		
			break;
		case REQ_SetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				uint16_t ReportOUTSize = USB_ControlRequest.wLength;
				uint8_t  ReportOUTData[ReportOUTSize];

				Endpoint_Read_Control_Stream_LE(ReportOUTData, ReportOUTSize);
				Endpoint_ClearIN();
				
				CALLBACK_USB_HID_ProcessReceivedHIDReport(HIDInterfaceInfo, ReportOUTData, ReportOUTSize);
			}
			
			break;
		case REQ_GetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				Endpoint_Write_Byte(HIDInterfaceInfo->UsingReportProtocol);
				Endpoint_ClearIN();

				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();

				HIDInterfaceInfo->UsingReportProtocol = (USB_ControlRequest.wValue != 0x0000);
				
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
			
			break;
		case REQ_SetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				HIDInterfaceInfo->IdleCount = ((USB_ControlRequest.wValue >> 8) << 2);
				
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
			
			break;
		case REQ_GetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{		
				Endpoint_ClearSETUP();
				
				Endpoint_Write_Byte(HIDInterfaceInfo->IdleCount >> 2);
				Endpoint_ClearIN();

				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}

			break;
	}
}

bool USB_HID_ConfigureEndpoints(USB_ClassInfo_HID_t* HIDInterfaceInfo)
{
	HIDInterfaceInfo->UsingReportProtocol = true;

	if (!(Endpoint_ConfigureEndpoint(HIDInterfaceInfo->ReportINEndpointNumber, EP_TYPE_INTERRUPT,
									 ENDPOINT_DIR_IN, HIDInterfaceInfo->ReportINEndpointSize, ENDPOINT_BANK_SINGLE)))
	{
		return false;
	}
	
	if (HIDInterfaceInfo->ReportOUTEndpointNumber)
	{
		if (!(Endpoint_ConfigureEndpoint(HIDInterfaceInfo->ReportOUTEndpointNumber, EP_TYPE_INTERRUPT,
										 ENDPOINT_DIR_OUT, HIDInterfaceInfo->ReportOUTEndpointSize, ENDPOINT_BANK_SINGLE)))
		{
			return false;
		}
	}
	
	return true;
}
		
void USB_HID_USBTask(USB_ClassInfo_HID_t* HIDInterfaceInfo)
{
	if (!(USB_IsConnected))
	  return;

	Endpoint_SelectEndpoint(HIDInterfaceInfo->ReportINEndpointNumber);
	
	if (Endpoint_IsReadWriteAllowed() &&
	    !(HIDInterfaceInfo->IdleCount && HIDInterfaceInfo->IdleMSRemaining))
	{
		if (HIDInterfaceInfo->IdleCount && !(HIDInterfaceInfo->IdleMSRemaining))
		  HIDInterfaceInfo->IdleMSRemaining = HIDInterfaceInfo->IdleCount;

		uint8_t  ReportINData[HIDInterfaceInfo->ReportINBufferSize];
		uint16_t ReportINSize;

		memset(ReportINData, 0, sizeof(ReportINData));

		ReportINSize = CALLBACK_USB_HID_CreateNextHIDReport(HIDInterfaceInfo, ReportINData);

		if (ReportINSize)
		  Endpoint_Write_Stream_LE(ReportINData, ReportINSize, NO_STREAM_CALLBACK);
		
		Endpoint_ClearIN();
	}
	
	if (HIDInterfaceInfo->ReportOUTEndpointNumber)
	{
		Endpoint_SelectEndpoint(HIDInterfaceInfo->ReportOUTEndpointNumber);
		
		if (Endpoint_IsOUTReceived())
		{
			uint16_t ReportOUTSize = Endpoint_BytesInEndpoint();
			uint8_t  ReportOUTData[ReportOUTSize];
			
			if (ReportOUTSize)
			  Endpoint_Read_Stream_LE(ReportOUTData, ReportOUTSize, NO_STREAM_CALLBACK);
			  
			CALLBACK_USB_HID_ProcessReceivedHIDReport(HIDInterfaceInfo, ReportOUTData, ReportOUTSize);
			
			Endpoint_ClearOUT();
		}
	}
}
