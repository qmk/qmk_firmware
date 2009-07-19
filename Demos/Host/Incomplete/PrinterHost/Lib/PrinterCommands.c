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

#include "PrinterCommands.h"

uint8_t Printer_GetDeviceID(Device_ID_String_t* DeviceIDString)
{
	uint8_t  ErrorCode = HOST_SENDCONTROL_Successful;
	uint16_t DeviceIDStringLength;

	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      GET_DEVICE_ID,
			wValue:        0,
			wIndex:        0,
			wLength:       sizeof(DeviceIDString->Length),
		};

	if ((ErrorCode = USB_Host_SendControlRequest(DeviceIDString)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	
	DeviceIDStringLength = SwapEndian_16(DeviceIDString->Length);

	/* Protect against overflow for the null terminator if the string length is equal to or larger than the buffer */
	if (DeviceIDStringLength >= sizeof(DeviceIDString->String))
	  DeviceIDStringLength = sizeof(DeviceIDString->String) - 1;

	USB_ControlRequest.wLength = DeviceIDStringLength;
	
	if ((ErrorCode = USB_Host_SendControlRequest(DeviceIDString)) != HOST_SENDCONTROL_Successful)
	  return ErrorCode;
	
	DeviceIDString->String[DeviceIDStringLength] = 0x00;
	
	return HOST_SENDCONTROL_Successful;
}

uint8_t Printer_GetPortStatus(uint8_t* PortStatus)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      GET_PORT_STATUS,
			wValue:        0,
			wIndex:        0,
			wLength:       sizeof(uint8_t),
		};

	return USB_Host_SendControlRequest(PortStatus);
}

uint8_t Printer_SoftReset(void)
{
	USB_ControlRequest = (USB_Request_Header_t)
		{
			bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			bRequest:      SOFT_RESET,
			wValue:        0,
			wIndex:        0,
			wLength:       0,
		};

	return USB_Host_SendControlRequest(NULL);
}

