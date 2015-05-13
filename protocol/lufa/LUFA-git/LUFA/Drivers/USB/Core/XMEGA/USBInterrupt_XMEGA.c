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

#include "../../../../Common/Common.h"
#if (ARCH == ARCH_XMEGA)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBInterrupt.h"

void USB_INT_DisableAllInterrupts(void)
{
	USB.INTCTRLA    &= USB_INTLVL_gm;
	USB.INTCTRLB     = 0;
}

void USB_INT_ClearAllInterrupts(void)
{
	USB.INTFLAGSACLR = 0xFF;
	USB.INTFLAGSBCLR = 0xFF;
}

ISR(USB_BUSEVENT_vect)
{
	#if !defined(NO_SOF_EVENTS)
	if (USB_INT_HasOccurred(USB_INT_SOFI) && USB_INT_IsEnabled(USB_INT_SOFI))
	{
		USB_INT_Clear(USB_INT_SOFI);

		EVENT_USB_Device_StartOfFrame();
	}
	#endif

	if (USB_INT_HasOccurred(USB_INT_BUSEVENTI_Suspend))
	{
		USB_INT_Clear(USB_INT_BUSEVENTI_Suspend);

		#if !defined(NO_LIMITED_CONTROLLER_CONNECT)
		USB_DeviceState = DEVICE_STATE_Unattached;
		EVENT_USB_Device_Disconnect();
		#else
		USB_DeviceState = DEVICE_STATE_Suspended;
		EVENT_USB_Device_Suspend();
		#endif
	}

	if (USB_INT_HasOccurred(USB_INT_BUSEVENTI_Resume))
	{
		USB_INT_Clear(USB_INT_BUSEVENTI_Resume);

		if (USB_Device_ConfigurationNumber)
		  USB_DeviceState = DEVICE_STATE_Configured;
		else
		  USB_DeviceState = (USB_Device_IsAddressSet()) ? DEVICE_STATE_Addressed : DEVICE_STATE_Powered;

		#if !defined(NO_LIMITED_CONTROLLER_CONNECT)
		EVENT_USB_Device_Connect();
		#else
		EVENT_USB_Device_WakeUp();
		#endif
	}

	if (USB_INT_HasOccurred(USB_INT_BUSEVENTI_Reset))
	{
		USB_INT_Clear(USB_INT_BUSEVENTI_Reset);

		USB_DeviceState                = DEVICE_STATE_Default;
		USB_Device_ConfigurationNumber = 0;

		USB_Device_EnableDeviceAddress(0);

		Endpoint_ClearEndpoints();
		Endpoint_ConfigureEndpoint(ENDPOINT_CONTROLEP, EP_TYPE_CONTROL,
		                           USB_Device_ControlEndpointSize, 1);

		EVENT_USB_Device_Reset();
	}
}

#endif
