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

  The author disclaim all warranties with regard to this
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
#define  __INCLUDE_FROM_USB_CONTROLLER_C
#include "../USBController.h"

#if (!defined(USB_HOST_ONLY) && !defined(USB_DEVICE_ONLY))
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

	if (!(USB_Options & USB_OPT_REG_DISABLED))
	  USB_REG_On();
	else
	  USB_REG_Off();

	if (!(USB_Options & USB_OPT_MANUAL_PLL))
	{
		#if defined(USB_SERIES_4_AVR)
		PLLFRQ = (1 << PDIV2);
		#endif
	}

	#if defined(USB_CAN_BE_BOTH)
	if (Mode == USB_MODE_UID)
	{
		UHWCON |=  (1 << UIDE);
		USB_INT_Enable(USB_INT_IDTI);
		USB_CurrentMode = USB_GetUSBModeFromUID();
	}
	else
	{
		UHWCON &= ~(1 << UIDE);
		USB_CurrentMode = Mode;
	}
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

	if (!(USB_Options & USB_OPT_MANUAL_PLL))
	  USB_PLL_Off();

	USB_REG_Off();

	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USB_OTGPAD_Off();
	#endif

	#if defined(USB_CAN_BE_BOTH)
	USB_CurrentMode = USB_MODE_None;
	#endif

	USB_IsInitialized = false;
}

void USB_ResetInterface(void)
{
	#if defined(USB_CAN_BE_BOTH)
	bool UIDModeSelectEnabled = ((UHWCON & (1 << UIDE)) != 0);
	#endif

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
		#if (defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
		UHWCON |=  (1 << UIMOD);
		#endif

		if (!(USB_Options & USB_OPT_MANUAL_PLL))
		{
			#if defined(USB_SERIES_2_AVR)
			USB_PLL_On();
			while (!(USB_PLL_IsReady()));
			#else
			USB_PLL_Off();
			#endif
		}

		USB_Init_Device();
		#endif
	}
	else if (USB_CurrentMode == USB_MODE_Host)
	{
		#if defined(USB_CAN_BE_HOST)
		UHWCON &= ~(1 << UIMOD);

		if (!(USB_Options & USB_OPT_MANUAL_PLL))
		{
			#if defined(USB_CAN_BE_HOST)
			USB_PLL_On();
			while (!(USB_PLL_IsReady()));
			#endif
		}

		USB_Init_Host();
		#endif
	}

	#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
	USB_OTGPAD_On();
	#endif
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

	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	uint8_t DescriptorAddressSpace;

	if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DeviceDescriptorPtr, &DescriptorAddressSpace) != NO_DESCRIPTOR)
	{
		if (DescriptorAddressSpace == MEMSPACE_FLASH)
		  USB_Device_ControlEndpointSize = pgm_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
		else if (DescriptorAddressSpace == MEMSPACE_EEPROM)
		  USB_Device_ControlEndpointSize = eeprom_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
		else
		  USB_Device_ControlEndpointSize = DeviceDescriptorPtr->Endpoint0Size;
	}
	#else
	if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DeviceDescriptorPtr) != NO_DESCRIPTOR)
	{
		#if defined(USE_RAM_DESCRIPTORS)
		USB_Device_ControlEndpointSize = DeviceDescriptorPtr->Endpoint0Size;
		#elif defined(USE_EEPROM_DESCRIPTORS)
		USB_Device_ControlEndpointSize = eeprom_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
		#else
		USB_Device_ControlEndpointSize = pgm_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
		#endif
	}
	#endif
	#endif

	#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
	if (USB_Options & USB_DEVICE_OPT_LOWSPEED)
	  USB_Device_SetLowSpeed();
	else
	  USB_Device_SetFullSpeed();

	USB_INT_Enable(USB_INT_VBUSTI);
	#endif

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

	USB_Host_VBUS_Auto_Off();
	USB_Host_VBUS_Manual_Enable();
	USB_Host_VBUS_Manual_On();

	USB_INT_Enable(USB_INT_SRPI);
	USB_INT_Enable(USB_INT_BCERRI);

	USB_Attach();
}
#endif

#endif
