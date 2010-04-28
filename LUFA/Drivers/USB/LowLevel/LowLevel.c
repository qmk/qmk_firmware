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
#include "LowLevel.h"

#if (!defined(USB_HOST_ONLY) && !defined(USB_DEVICE_ONLY))
volatile uint8_t USB_CurrentMode = USB_MODE_NONE;
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
	#if defined(USB_CAN_BE_BOTH)
	USB_CurrentMode = Mode;
	#endif

	#if !defined(USE_STATIC_OPTIONS)
	USB_Options = Options;
	#endif

	#if defined(USB_CAN_BE_HOST)
	USB_ControlPipeSize = PIPE_CONTROLPIPE_DEFAULT_SIZE;
	#endif
	
	#if defined(USB_DEVICE_ONLY) && (defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
	UHWCON |= (1 << UIMOD);
	#elif defined(USB_HOST_ONLY)
	UHWCON &= ~(1 << UIMOD);
	#elif defined(USB_CAN_BE_BOTH)
	if (Mode == USB_MODE_UID)
	{
		UHWCON |=  (1 << UIDE);

		USB_INT_Clear(USB_INT_IDTI);
		USB_INT_Enable(USB_INT_IDTI);
		
		USB_CurrentMode = USB_GetUSBModeFromUID();
	}
	else if (Mode == USB_MODE_DEVICE)
	{
		UHWCON |=  (1 << UIMOD);
	}
	else if (Mode == USB_MODE_HOST)			
	{
		UHWCON &= ~(1 << UIMOD);
	}
	else
	{
		EVENT_USB_InitFailure(USB_INITERROR_NoUSBModeSpecified);
		return;
	}
	#endif
	
	USB_ResetInterface();

	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USB_OTGPAD_On();
	#endif

	USB_IsInitialized = true;
}

void USB_ShutDown(void)
{
	USB_ResetInterface();
	USB_Detach();
	USB_Controller_Disable();
	
	USB_INT_DisableAllInterrupts();
	USB_INT_ClearAllInterrupts();

	#if defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	UHWCON &= ~(1 << UIMOD);
	#endif
	
	if (!(USB_Options & USB_OPT_MANUAL_PLL))
	  USB_PLL_Off();
	
	USB_REG_Off();

	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USB_OTGPAD_Off();
	#endif

	#if defined(USB_CAN_BE_BOTH)
	UHWCON &= ~(1 << UIDE);
	#endif

	USB_IsInitialized = false;

	#if defined(USB_CAN_BE_BOTH)
	USB_CurrentMode = USB_MODE_NONE;
	#endif
}

void USB_ResetInterface(void)
{
	USB_INT_DisableAllInterrupts();
	USB_INT_ClearAllInterrupts();
	
	#if defined(USB_CAN_BE_HOST)
	USB_HostState   = HOST_STATE_Unattached;
	#endif
	
	#if defined(USB_CAN_BE_DEVICE)
	USB_DeviceState = DEVICE_STATE_Unattached;
	USB_ConfigurationNumber  = 0;

	#if !defined(NO_DEVICE_REMOTE_WAKEUP)
	USB_RemoteWakeupEnabled  = false;
	#endif
	
	#if !defined(NO_DEVICE_SELF_POWER)
	USB_CurrentlySelfPowered = false;
	#endif
	#endif
	
	if (!(USB_Options & USB_OPT_MANUAL_PLL))
	{
		#if defined(USB_SERIES_4_AVR)
		PLLFRQ = ((1 << PLLUSB) | (1 << PDIV3) | (1 << PDIV1));
		#endif

		USB_PLL_On();
		while (!(USB_PLL_IsReady()));
	}
	
	USB_Controller_Reset();
	
	#if defined(USB_CAN_BE_BOTH)
	if (UHWCON & (1 << UIDE))
	{
		USB_INT_Clear(USB_INT_IDTI);
		USB_INT_Enable(USB_INT_IDTI);
		USB_CurrentMode = USB_GetUSBModeFromUID();
	}
	#endif
		
	if (!(USB_Options & USB_OPT_REG_DISABLED))
	  USB_REG_On();
	else
	  USB_REG_Off();
	
	USB_CLK_Unfreeze();

	#if (defined(USB_CAN_BE_DEVICE) && (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)))
	if (USB_CurrentMode == USB_MODE_DEVICE)
	{
		if (USB_Options & USB_DEVICE_OPT_LOWSPEED)
		  USB_Device_SetLowSpeed();
		else
		  USB_Device_SetFullSpeed();
	}
	#endif
	
	#if (defined(USB_CAN_BE_DEVICE) && !defined(FIXED_CONTROL_ENDPOINT_SIZE))
	if (USB_CurrentMode == USB_MODE_DEVICE)
	{
		USB_Descriptor_Device_t* DeviceDescriptorPtr;

		if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DeviceDescriptorPtr) != NO_DESCRIPTOR)
		{		  
			#if defined(USE_RAM_DESCRIPTORS)
			USB_ControlEndpointSize = DeviceDescriptorPtr->Endpoint0Size;
			#elif defined(USE_EEPROM_DESCRIPTORS)
			USB_ControlEndpointSize = eeprom_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
			#else
			USB_ControlEndpointSize = pgm_read_byte(&DeviceDescriptorPtr->Endpoint0Size);
			#endif
		}
	}
	#endif

	USB_Attach();
	
	#if defined(USB_DEVICE_ONLY)
	USB_INT_Clear(USB_INT_SUSPEND);
	USB_INT_Enable(USB_INT_SUSPEND);
	USB_INT_Clear(USB_INT_EORSTI);
	USB_INT_Enable(USB_INT_EORSTI);

	#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
	USB_INT_Enable(USB_INT_VBUS);
	#endif
	#elif defined(USB_HOST_ONLY)
	USB_Host_HostMode_On();
	
	USB_Host_VBUS_Auto_Off();
	USB_OTGPAD_Off();

	USB_Host_VBUS_Manual_Enable();
	USB_Host_VBUS_Manual_On();
	
	USB_INT_Enable(USB_INT_SRPI);
	USB_INT_Enable(USB_INT_BCERRI);
	#else
	if (USB_CurrentMode == USB_MODE_DEVICE)
	{
		USB_INT_Clear(USB_INT_SUSPEND);
		USB_INT_Enable(USB_INT_SUSPEND);
		USB_INT_Clear(USB_INT_EORSTI);
		USB_INT_Enable(USB_INT_EORSTI);

		#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR)
		USB_INT_Enable(USB_INT_VBUS);
		#endif

		#if defined(CONTROL_ONLY_DEVICE)
		UENUM = ENDPOINT_CONTROLEP;
		#endif
	}
	else if (USB_CurrentMode == USB_MODE_HOST)
	{
		USB_Host_HostMode_On();
		
		USB_Host_VBUS_Auto_Off();
		USB_OTGPAD_Off();

		USB_Host_VBUS_Manual_Enable();
		USB_Host_VBUS_Manual_On();
		
		USB_INT_Enable(USB_INT_SRPI);
		USB_INT_Enable(USB_INT_BCERRI);
	}
	#endif
}
