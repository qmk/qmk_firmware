/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
#if (ARCH == ARCH_UC3)

#define  __INCLUDE_FROM_USB_DRIVER
#define  __INCLUDE_FROM_USB_CONTROLLER_C
#include "../USBController.h"

#if defined(USB_CAN_BE_BOTH)
volatile uint8_t USB_CurrentMode = USB_MODE_None;
#endif

#if !defined(USE_STATIC_OPTIONS)
volatile uint8_t USB_Options;
#endif

void USB_Init(
               #if defined(USB_CAN_BE_BOTH)
               const uint8_t Mode
               #endif

               #if (defined(USB_CAN_BE_BOTH) && !defined(USE_STATIC_OPTIONS))
               ,
               #elif (!defined(USB_CAN_BE_BOTH) && defined(USE_STATIC_OPTIONS))
               void
               #endif

               #if !defined(USE_STATIC_OPTIONS)
               const uint8_t Options
               #endif
               )
{
	#if !defined(USE_STATIC_OPTIONS)
	USB_Options = Options;
	#endif

	#if defined(USB_CAN_BE_BOTH)
	if (Mode == USB_MODE_UID)
	{
		AVR32_USBB.USBCON.uide = true;
		USB_INT_Enable(USB_INT_IDTI);
		USB_CurrentMode = USB_GetUSBModeFromUID();
	}
	else
	{
		AVR32_USBB.USBCON.uide = false;
		USB_CurrentMode = Mode;
	}
	#else
	AVR32_USBB.USBCON.uide = false;
	#endif

	USB_IsInitialized = true;

	USB_ResetInterface();
}

void USB_Disable(void)
{
	USB_INT_DisableAllInterrupts();
	USB_INT_ClearAllInterrupts();

	USB_Detach();
	USB_Controller_Disable();

	USB_OTGPAD_Off();

	#if defined(USB_CAN_BE_BOTH)
	USB_CurrentMode = USB_MODE_None;
	#endif

	AVR32_PM.GCCTRL[3].cen = false;

	USB_IsInitialized = false;
}

void USB_ResetInterface(void)
{
	#if defined(USB_CAN_BE_BOTH)
	bool UIDModeSelectEnabled = AVR32_USBB.USBCON.uide;
	#endif

	AVR32_PM.GCCTRL[AVR32_PM_GCLK_USBB].pllsel = !(USB_Options & USB_OPT_GCLK_SRC_OSC);
	AVR32_PM.GCCTRL[AVR32_PM_GCLK_USBB].oscsel = !(USB_Options & USB_OPT_GCLK_CHANNEL_0);
	AVR32_PM.GCCTRL[AVR32_PM_GCLK_USBB].diven  = (F_USB != USB_CLOCK_REQUIRED_FREQ);
	AVR32_PM.GCCTRL[AVR32_PM_GCLK_USBB].div    = (F_USB == USB_CLOCK_REQUIRED_FREQ) ? 0 : (uint32_t)((F_USB / USB_CLOCK_REQUIRED_FREQ / 2) - 1);
	AVR32_PM.GCCTRL[AVR32_PM_GCLK_USBB].cen    = true;

	USB_INT_DisableAllInterrupts();
	USB_INT_ClearAllInterrupts();

	USB_Controller_Reset();

	#if defined(USB_CAN_BE_BOTH)
	if (UIDModeSelectEnabled)
	  USB_INT_Enable(USB_INT_IDTI);
	#endif

	USB_CLK_Unfreeze();

	if (USB_CurrentMode == USB_MODE_Device)
	{
		#if defined(USB_CAN_BE_DEVICE)
		AVR32_USBB.USBCON.uimod = true;

		USB_Init_Device();
		#endif
	}
	else if (USB_CurrentMode == USB_MODE_Host)
	{
		#if defined(INVERTED_VBUS_ENABLE_LINE)
		AVR32_USBB.USBCON.vbuspo = true;
		#endif
		
		#if defined(USB_CAN_BE_HOST)
		AVR32_USBB.USBCON.uimod = false;

		USB_Init_Host();
		#endif
	}

	USB_OTGPAD_On();
}

#if defined(USB_CAN_BE_DEVICE)
static void USB_Init_Device(void)
{
	USB_DeviceState                 = DEVICE_STATE_Unattached;
	USB_Device_ConfigurationNumber  = 0;

	#if !defined(NO_DEVICE_REMOTE_WAKEUP)
	USB_Device_RemoteWakeupEnabled  = false;
	#endif

	#if !defined(NO_DEVICE_SELF_POWER)
	USB_Device_CurrentlySelfPowered = false;
	#endif

	#if !defined(FIXED_CONTROL_ENDPOINT_SIZE)
	USB_Descriptor_Device_t* DeviceDescriptorPtr;

	if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DeviceDescriptorPtr) != NO_DESCRIPTOR)
	  USB_Device_ControlEndpointSize = DeviceDescriptorPtr->Endpoint0Size;
	#endif

	if (USB_Options & USB_DEVICE_OPT_LOWSPEED)
	{
		USB_Device_SetLowSpeed();
	}
	else
	{
		#if defined(USB_DEVICE_OPT_HIGHSPEED)
		if (USB_Options & USB_DEVICE_OPT_HIGHSPEED)
		  USB_Device_SetHighSpeed();
		else
		  USB_Device_SetFullSpeed();
		#else
		USB_Device_SetFullSpeed();
		#endif
	}

	USB_INT_Enable(USB_INT_VBUSTI);

	Endpoint_ConfigureEndpoint(ENDPOINT_CONTROLEP, EP_TYPE_CONTROL,
							   USB_Device_ControlEndpointSize, 1);

	USB_INT_Clear(USB_INT_SUSPI);
	USB_INT_Enable(USB_INT_SUSPI);
	USB_INT_Enable(USB_INT_EORSTI);

	USB_Attach();
}
#endif

#if defined(USB_CAN_BE_HOST)
static void USB_Init_Host(void)
{
	USB_HostState                = HOST_STATE_Unattached;
	USB_Host_ConfigurationNumber = 0;
	USB_Host_ControlPipeSize     = PIPE_CONTROLPIPE_DEFAULT_SIZE;

	USB_Host_HostMode_On();

	USB_Host_VBUS_Auto_On();

	USB_INT_Enable(USB_INT_DCONNI);
	USB_INT_Enable(USB_INT_BCERRI);

	USB_Attach();
}
#endif

#endif
