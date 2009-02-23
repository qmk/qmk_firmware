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

#include "DeviceDescriptor.h"

uint8_t ProcessDeviceDescriptor(void)
{
	USB_Descriptor_Device_t DeviceDescriptor;

	/* Standard request to get the device descriptor */
	USB_HostRequest = (USB_Host_Request_Header_t)
		{
			bmRequestType: (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE),
			bRequest:      REQ_GetDescriptor,
			wValue:        (DTYPE_Device << 8),
			wIndex:        0,
			wLength:       sizeof(USB_Descriptor_Device_t),
		};

	/* Send the request to retrieve the device descriptor */
	if (USB_Host_SendControlRequest((void*)&DeviceDescriptor) != HOST_SENDCONTROL_Successful)
	  return ControlErrorDuringDeviceRead;
	  
	/* Validate returned data - ensure the returned data is a device descriptor */
	if (DeviceDescriptor.Header.Type != DTYPE_Device)
	  return InvalidDeviceDataReturned;
	  
	if ((DeviceDescriptor.Class != BLUETOOTH_DEVICE_CLASS) ||
	    (DeviceDescriptor.SubClass != BLUETOOTH_DEVICE_SUBCLASS) ||
	    (DeviceDescriptor.Protocol != BLUETOOTH_DEVICE_PROTOCOL))
	{
		return IncorrectDevice;
	}
	
	return SuccessfulDeviceRead;
}
