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
#if (ARCH == ARCH_AVR8)

#define  __INCLUDE_FROM_USB_DRIVER
#include "../USBInterrupt.h"

void USB_INT_DisableAllInterrupts(void)
{
	#if defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USBCON &= ~((1 << VBUSTE) | (1 << IDTE));
	#elif defined(USB_SERIES_4_AVR)
	USBCON &= ~(1 << VBUSTE);
	#endif

	#if defined(USB_CAN_BE_BOTH)
	OTGIEN  = 0;
	#endif

	#if defined(USB_CAN_BE_HOST)
	UHIEN   = 0;
	#endif

	#if defined(USB_CAN_BE_DEVICE)
	UDIEN   = 0;
	#endif
}

void USB_INT_ClearAllInterrupts(void)
{
	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USBINT = 0;
	#endif

	#if defined(USB_CAN_BE_BOTH)
	OTGINT = 0;
	#endif

	#if defined(USB_CAN_BE_HOST)
	UHINT  = 0;
	#endif

	#if defined(USB_CAN_BE_DEVICE)
	UDINT  = 0;
	#endif
}

ISR(USB_GEN_vect, ISR_BLOCK)
{
	#if defined(USB_CAN_BE_DEVICE)
	#if !defined(NO_SOF_EVENTS)
	if (USB_INT_HasOccurred(USB_INT_SOFI) && USB_INT_IsEnabled(USB_INT_SOFI))
	{
		USB_INT_Clear(USB_INT_SOFI);

		EVENT_USB_Device_StartOfFrame();
	}
	#endif

	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	if (USB_INT_HasOccurred(USB_INT_VBUSTI) && USB_INT_IsEnabled(USB_INT_VBUSTI))
	{
		USB_INT_Clear(USB_INT_VBUSTI);

		if (USB_VBUS_GetStatus())
		{
			if (!(USB_Options & USB_OPT_MANUAL_PLL))
			{
				USB_PLL_On();
				while (!(USB_PLL_IsReady()));
			}

			USB_DeviceState = DEVICE_STATE_Powered;
			EVENT_USB_Device_Connect();
		}
		else
		{
			if (!(USB_Options & USB_OPT_MANUAL_PLL))
			  USB_PLL_Off();

			USB_DeviceState = DEVICE_STATE_Unattached;
			EVENT_USB_Device_Disconnect();
		}
	}
	#endif

	if (USB_INT_HasOccurred(USB_INT_SUSPI) && USB_INT_IsEnabled(USB_INT_SUSPI))
	{
		USB_INT_Disable(USB_INT_SUSPI);
		USB_INT_Enable(USB_INT_WAKEUPI);

		USB_CLK_Freeze();

		if (!(USB_Options & USB_OPT_MANUAL_PLL))
		  USB_PLL_Off();

		#if defined(USB_SERIES_2_AVR) && !defined(NO_LIMITED_CONTROLLER_CONNECT)
		USB_DeviceState = DEVICE_STATE_Unattached;
		EVENT_USB_Device_Disconnect();
		#else
		USB_DeviceState = DEVICE_STATE_Suspended;
		EVENT_USB_Device_Suspend();
		#endif
	}

	if (USB_INT_HasOccurred(USB_INT_WAKEUPI) && USB_INT_IsEnabled(USB_INT_WAKEUPI))
	{
		if (!(USB_Options & USB_OPT_MANUAL_PLL))
		{
			USB_PLL_On();
			while (!(USB_PLL_IsReady()));
		}

		USB_CLK_Unfreeze();

		USB_INT_Clear(USB_INT_WAKEUPI);

		USB_INT_Disable(USB_INT_WAKEUPI);
		USB_INT_Enable(USB_INT_SUSPI);

		if (USB_Device_ConfigurationNumber)
		  USB_DeviceState = DEVICE_STATE_Configured;
		else
		  USB_DeviceState = (USB_Device_IsAddressSet()) ? DEVICE_STATE_Addressed : DEVICE_STATE_Powered;

		#if defined(USB_SERIES_2_AVR) && !defined(NO_LIMITED_CONTROLLER_CONNECT)
		EVENT_USB_Device_Connect();
		#else
		EVENT_USB_Device_WakeUp();
		#endif
	}

	if (USB_INT_HasOccurred(USB_INT_EORSTI) && USB_INT_IsEnabled(USB_INT_EORSTI))
	{
		USB_INT_Clear(USB_INT_EORSTI);

		USB_DeviceState                = DEVICE_STATE_Default;
		USB_Device_ConfigurationNumber = 0;

		USB_INT_Clear(USB_INT_SUSPI);
		USB_INT_Disable(USB_INT_SUSPI);
		USB_INT_Enable(USB_INT_WAKEUPI);

		Endpoint_ConfigureEndpoint(ENDPOINT_CONTROLEP, EP_TYPE_CONTROL,
		                           USB_Device_ControlEndpointSize, 1);

		#if defined(INTERRUPT_CONTROL_ENDPOINT)
		USB_INT_Enable(USB_INT_RXSTPI);
		#endif

		EVENT_USB_Device_Reset();
	}
	#endif

	#if defined(USB_CAN_BE_HOST)
	#if !defined(NO_SOF_EVENTS)
	if (USB_INT_HasOccurred(USB_INT_HSOFI) && USB_INT_IsEnabled(USB_INT_HSOFI))
	{
		USB_INT_Clear(USB_INT_HSOFI);

		EVENT_USB_Host_StartOfFrame();
	}
	#endif

	if (USB_INT_HasOccurred(USB_INT_DDISCI) && USB_INT_IsEnabled(USB_INT_DDISCI))
	{
		USB_INT_Clear(USB_INT_DDISCI);
		USB_INT_Clear(USB_INT_DCONNI);
		USB_INT_Disable(USB_INT_DDISCI);

		EVENT_USB_Host_DeviceUnattached();

		USB_ResetInterface();
	}

	if (USB_INT_HasOccurred(USB_INT_VBERRI) && USB_INT_IsEnabled(USB_INT_VBERRI))
	{
		USB_INT_Clear(USB_INT_VBERRI);

		USB_Host_VBUS_Manual_Off();
		USB_Host_VBUS_Auto_Off();

		EVENT_USB_Host_HostError(HOST_ERROR_VBusVoltageDip);
		EVENT_USB_Host_DeviceUnattached();

		USB_HostState = HOST_STATE_Unattached;
	}

	if (USB_INT_HasOccurred(USB_INT_SRPI) && USB_INT_IsEnabled(USB_INT_SRPI))
	{
		USB_INT_Clear(USB_INT_SRPI);
		USB_INT_Disable(USB_INT_SRPI);

		EVENT_USB_Host_DeviceAttached();

		USB_INT_Enable(USB_INT_DDISCI);

		USB_HostState = HOST_STATE_Powered;
	}

	if (USB_INT_HasOccurred(USB_INT_BCERRI) && USB_INT_IsEnabled(USB_INT_BCERRI))
	{
		USB_INT_Clear(USB_INT_BCERRI);

		EVENT_USB_Host_DeviceEnumerationFailed(HOST_ENUMERROR_NoDeviceDetected, 0);
		EVENT_USB_Host_DeviceUnattached();

		USB_ResetInterface();
	}
	#endif

	#if defined(USB_CAN_BE_BOTH)
	if (USB_INT_HasOccurred(USB_INT_IDTI) && USB_INT_IsEnabled(USB_INT_IDTI))
	{
		USB_INT_Clear(USB_INT_IDTI);

		if (USB_DeviceState != DEVICE_STATE_Unattached)
		  EVENT_USB_Device_Disconnect();

		if (USB_HostState != HOST_STATE_Unattached)
		  EVENT_USB_Host_DeviceUnattached();

		USB_CurrentMode = USB_GetUSBModeFromUID();
		USB_ResetInterface();

		EVENT_USB_UIDChange();
	}
	#endif
}

#if defined(INTERRUPT_CONTROL_ENDPOINT) && defined(USB_CAN_BE_DEVICE)
ISR(USB_COM_vect, ISR_BLOCK)
{
	uint8_t PrevSelectedEndpoint = Endpoint_GetCurrentEndpoint();

	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);
	USB_INT_Disable(USB_INT_RXSTPI);

	GlobalInterruptEnable();

	USB_Device_ProcessControlRequest();

	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);
	USB_INT_Enable(USB_INT_RXSTPI);
	Endpoint_SelectEndpoint(PrevSelectedEndpoint);
}
#endif

#endif

