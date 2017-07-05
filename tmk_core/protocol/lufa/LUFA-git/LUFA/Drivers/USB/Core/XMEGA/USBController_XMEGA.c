/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
#define  __INCLUDE_FROM_USB_CONTROLLER_C
#include "../USBController.h"

#if defined(USB_CAN_BE_BOTH)
volatile uint8_t USB_CurrentMode = USB_MODE_None;
#endif

#if !defined(USE_STATIC_OPTIONS)
volatile uint8_t USB_Options;
#endif

/* Ugly workaround to ensure an aligned table, since __BIGGEST_ALIGNMENT__ == 1 for the 8-bit AVR-GCC toolchain */
uint8_t USB_EndpointTable[sizeof(USB_EndpointTable_t) + 1];

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

	uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
	GlobalInterruptDisable();

	NVM.CMD  = NVM_CMD_READ_CALIB_ROW_gc;
	USB.CAL0 = pgm_read_byte(offsetof(NVM_PROD_SIGNATURES_t, USBCAL0));
	USB.CAL1 = pgm_read_byte(offsetof(NVM_PROD_SIGNATURES_t, USBCAL1));
	NVM.CMD  = NVM_CMD_NO_OPERATION_gc;

	/* Ugly workaround to ensure an aligned table, since __BIGGEST_ALIGNMENT__ == 1 for the 8-bit AVR-GCC toolchain */
	USB.EPPTR = ((intptr_t)&USB_EndpointTable[1] & ~(1 << 0));
	USB.CTRLA = (USB_STFRNUM_bm | ((ENDPOINT_TOTAL_ENDPOINTS - 1) << USB_MAXEP_gp));

	if ((USB_Options & USB_OPT_BUSEVENT_PRIHIGH) == USB_OPT_BUSEVENT_PRIHIGH)
	  USB.INTCTRLA = (3 << USB_INTLVL_gp);
	else if ((USB_Options & USB_OPT_BUSEVENT_PRIMED) == USB_OPT_BUSEVENT_PRIMED)
	  USB.INTCTRLA = (2 << USB_INTLVL_gp);
	else
	  USB.INTCTRLA = (1 << USB_INTLVL_gp);

	SetGlobalInterruptMask(CurrentGlobalInt);

	#if defined(USB_CAN_BE_BOTH)
	USB_CurrentMode = Mode;
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

	USB_IsInitialized = false;
}

void USB_ResetInterface(void)
{
	uint8_t PrescalerNeeded;

	#if defined(USB_DEVICE_OPT_FULLSPEED)
	if (USB_Options & USB_DEVICE_OPT_LOWSPEED)
	  PrescalerNeeded = F_USB / 6000000;
	else
	  PrescalerNeeded = F_USB / 48000000;
	#else
	PrescalerNeeded = F_USB / 6000000;
	#endif

	uint8_t DividerIndex = 0;
	while (PrescalerNeeded > 0)
	{
		DividerIndex++;
		PrescalerNeeded >>= 1;
	}

	CLK.USBCTRL = (DividerIndex - 1) << CLK_USBPSDIV_gp;

	if (USB_Options & USB_OPT_PLLCLKSRC)
	  CLK.USBCTRL |= (CLK_USBSRC_PLL_gc   | CLK_USBSEN_bm);
	else
	  CLK.USBCTRL |= (CLK_USBSRC_RC32M_gc | CLK_USBSEN_bm);

	USB_Device_SetDeviceAddress(0);

	USB_INT_DisableAllInterrupts();
	USB_INT_ClearAllInterrupts();

	USB_Controller_Reset();
	USB_Init_Device();
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

	if (USB_Options & USB_DEVICE_OPT_LOWSPEED)
	  USB_Device_SetLowSpeed();
	else
	  USB_Device_SetFullSpeed();

	Endpoint_ConfigureEndpoint(ENDPOINT_CONTROLEP, EP_TYPE_CONTROL,
							   USB_Device_ControlEndpointSize, 1);

	USB_INT_Enable(USB_INT_BUSEVENTI);

	USB_Attach();
}
#endif

#endif
