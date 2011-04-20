/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
#include "USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#define  __INCLUDE_FROM_DEVICESTDREQ_C
#include "DeviceStandardReq.h"

uint8_t USB_ConfigurationNumber;

#if !defined(NO_DEVICE_SELF_POWER)
bool    USB_CurrentlySelfPowered;
#endif

#if !defined(NO_DEVICE_REMOTE_WAKEUP)
bool    USB_RemoteWakeupEnabled;
#endif

void USB_Device_ProcessControlRequest(void)
{
	USB_ControlRequest.bmRequestType = Endpoint_Read_8();
	USB_ControlRequest.bRequest      = Endpoint_Read_8();
	USB_ControlRequest.wValue        = Endpoint_Read_16_LE();
	USB_ControlRequest.wIndex        = Endpoint_Read_16_LE();
	USB_ControlRequest.wLength       = Endpoint_Read_16_LE();

	EVENT_USB_Device_ControlRequest();

	if (Endpoint_IsSETUPReceived())
	{
		uint8_t bmRequestType = USB_ControlRequest.bmRequestType;

		switch (USB_ControlRequest.bRequest)
		{
			case REQ_GetStatus:
				if ((bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE)) ||
					(bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT)))
				{
					USB_Device_GetStatus();
				}

				break;
			case REQ_ClearFeature:
			case REQ_SetFeature:
				if ((bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE)) ||
					(bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT)))
				{
					USB_Device_ClearSetFeature();
				}

				break;
			case REQ_SetAddress:
				if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE))
				  USB_Device_SetAddress();

				break;
			case REQ_GetDescriptor:
				if ((bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE)) ||
					(bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE)))
				{
					USB_Device_GetDescriptor();
				}

				break;
			case REQ_GetConfiguration:
				if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE))
				  USB_Device_GetConfiguration();

				break;
			case REQ_SetConfiguration:
				if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE))
				  USB_Device_SetConfiguration();

				break;
		}
	}

	if (Endpoint_IsSETUPReceived())
	{
		Endpoint_StallTransaction();
		Endpoint_ClearSETUP();
	}
}

static void USB_Device_SetAddress(void)
{
	uint8_t    DeviceAddress    = (USB_ControlRequest.wValue & 0x7F);
	uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
	GlobalInterruptDisable();
				
	Endpoint_ClearSETUP();

	Endpoint_ClearStatusStage();

	while (!(Endpoint_IsINReady()));

	USB_Device_SetDeviceAddress(DeviceAddress);
	USB_DeviceState = (DeviceAddress) ? DEVICE_STATE_Addressed : DEVICE_STATE_Default;
	
	SetGlobalInterruptMask(CurrentGlobalInt);
}

static void USB_Device_SetConfiguration(void)
{
	#if defined(FIXED_NUM_CONFIGURATIONS)
	if ((uint8_t)USB_ControlRequest.wValue > FIXED_NUM_CONFIGURATIONS)
	  return;
	#else
	USB_Descriptor_Device_t* DevDescriptorPtr;

	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE)
		#if defined(USE_FLASH_DESCRIPTORS)
			#define MemoryAddressSpace  MEMSPACE_FLASH
		#elif defined(USE_EEPROM_DESCRIPTORS)
			#define MemoryAddressSpace  MEMSPACE_EEPROM
		#elif defined(USE_SRAM_DESCRIPTORS)
			#define MemoryAddressSpace  MEMSPACE_SRAM
		#else
			uint8_t MemoryAddressSpace;
		#endif
	#endif
	
	if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DevDescriptorPtr
	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	                               , &MemoryAddressSpace
	#endif
	                               ) == NO_DESCRIPTOR)
	{
		return;
	}

	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE)
	if (MemoryAddressSpace == MEMSPACE_FLASH)
	{
		if (((uint8_t)USB_ControlRequest.wValue > pgm_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
		  return;
	}
	else if (MemoryAddressSpace == MEMSPACE_EEPROM)
	{
		if (((uint8_t)USB_ControlRequest.wValue > eeprom_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
		  return;
	}
	else
	{
		if ((uint8_t)USB_ControlRequest.wValue > DevDescriptorPtr->NumberOfConfigurations)
		  return;
	}
	#else
	if ((uint8_t)USB_ControlRequest.wValue > DevDescriptorPtr->NumberOfConfigurations)
	  return;	
	#endif
	#endif

	Endpoint_ClearSETUP();

	USB_ConfigurationNumber = (uint8_t)USB_ControlRequest.wValue;

	Endpoint_ClearStatusStage();

	if (USB_ConfigurationNumber)
	  USB_DeviceState = DEVICE_STATE_Configured;
	else
	  USB_DeviceState = (USB_Device_IsAddressSet()) ? DEVICE_STATE_Configured : DEVICE_STATE_Powered;

	EVENT_USB_Device_ConfigurationChanged();
}

static void USB_Device_GetConfiguration(void)
{
	Endpoint_ClearSETUP();

	Endpoint_Write_8(USB_ConfigurationNumber);
	Endpoint_ClearIN();

	Endpoint_ClearStatusStage();
}

#if !defined(NO_INTERNAL_SERIAL) && (USE_INTERNAL_SERIAL != NO_DESCRIPTOR)
static void USB_Device_GetInternalSerialDescriptor(void)
{
	struct
	{
		USB_Descriptor_Header_t Header;
		uint16_t                UnicodeString[INTERNAL_SERIAL_LENGTH_BITS / 4];
	} SignatureDescriptor;

	SignatureDescriptor.Header.Type = DTYPE_String;
	SignatureDescriptor.Header.Size = USB_STRING_LEN(INTERNAL_SERIAL_LENGTH_BITS / 4);
	
	USB_Device_GetSerialString(SignatureDescriptor.UnicodeString);

	Endpoint_ClearSETUP();

	Endpoint_Write_Control_Stream_LE(&SignatureDescriptor, sizeof(SignatureDescriptor));
	Endpoint_ClearOUT();
}
#endif

static void USB_Device_GetDescriptor(void)
{
	const void* DescriptorPointer;
	uint16_t    DescriptorSize;

	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	uint8_t DescriptorAddressSpace;
	#endif

	#if !defined(NO_INTERNAL_SERIAL) && (USE_INTERNAL_SERIAL != NO_DESCRIPTOR)
	if (USB_ControlRequest.wValue == ((DTYPE_String << 8) | USE_INTERNAL_SERIAL))
	{
		USB_Device_GetInternalSerialDescriptor();
		return;
	}
	#endif

	if ((DescriptorSize = CALLBACK_USB_GetDescriptor(USB_ControlRequest.wValue, USB_ControlRequest.wIndex,
	                                                 &DescriptorPointer
	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	                                                 , &DescriptorAddressSpace
	#endif
													 )) == NO_DESCRIPTOR)
	{
		return;
	}

	Endpoint_ClearSETUP();

	#if defined(USE_RAM_DESCRIPTORS) || !defined(ARCH_HAS_MULTI_ADDRESS_SPACE)
	Endpoint_Write_Control_Stream_LE(DescriptorPointer, DescriptorSize);
	#elif defined(USE_EEPROM_DESCRIPTORS)
	Endpoint_Write_Control_EStream_LE(DescriptorPointer, DescriptorSize);
	#elif defined(USE_FLASH_DESCRIPTORS)
	Endpoint_Write_Control_PStream_LE(DescriptorPointer, DescriptorSize);
	#else
	if (DescriptorAddressSpace == MEMSPACE_FLASH)
	  Endpoint_Write_Control_PStream_LE(DescriptorPointer, DescriptorSize);
	else if (DescriptorAddressSpace == MEMSPACE_EEPROM)
	  Endpoint_Write_Control_EStream_LE(DescriptorPointer, DescriptorSize);
	else
	  Endpoint_Write_Control_Stream_LE(DescriptorPointer, DescriptorSize);
	#endif

	Endpoint_ClearOUT();
}

static void USB_Device_GetStatus(void)
{
	uint8_t CurrentStatus = 0;

	switch (USB_ControlRequest.bmRequestType)
	{
		#if !defined(NO_DEVICE_SELF_POWER) || !defined(NO_DEVICE_REMOTE_WAKEUP)
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE):
			#if !defined(NO_DEVICE_SELF_POWER)
			if (USB_CurrentlySelfPowered)
			  CurrentStatus |= FEATURE_SELFPOWERED_ENABLED;
			#endif

			#if !defined(NO_DEVICE_REMOTE_WAKEUP)
			if (USB_RemoteWakeupEnabled)
			  CurrentStatus |= FEATURE_REMOTE_WAKEUP_ENABLED;
			#endif
			break;
		#endif
		#if !defined(CONTROL_ONLY_DEVICE)
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT):
			Endpoint_SelectEndpoint((uint8_t)USB_ControlRequest.wIndex & ENDPOINT_EPNUM_MASK);

			CurrentStatus = Endpoint_IsStalled();

			Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);

			break;
		#endif
		default:
			return;
	}

	Endpoint_ClearSETUP();

	Endpoint_Write_16_LE(CurrentStatus);
	Endpoint_ClearIN();

	Endpoint_ClearStatusStage();
}

static void USB_Device_ClearSetFeature(void)
{
	switch (USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_RECIPIENT)
	{
		#if !defined(NO_DEVICE_REMOTE_WAKEUP)
		case REQREC_DEVICE:
			if ((uint8_t)USB_ControlRequest.wValue == FEATURE_SEL_DeviceRemoteWakeup)
			  USB_RemoteWakeupEnabled = (USB_ControlRequest.bRequest == REQ_SetFeature);
			else
			  return;

			break;
		#endif
		#if !defined(CONTROL_ONLY_DEVICE)
		case REQREC_ENDPOINT:
			if ((uint8_t)USB_ControlRequest.wValue == FEATURE_SEL_EndpointHalt)
			{
				uint8_t EndpointIndex = ((uint8_t)USB_ControlRequest.wIndex & ENDPOINT_EPNUM_MASK);

				if (EndpointIndex == ENDPOINT_CONTROLEP)
				  return;

				Endpoint_SelectEndpoint(EndpointIndex);

				if (Endpoint_IsEnabled())
				{
					if (USB_ControlRequest.bRequest == REQ_SetFeature)
					{
						Endpoint_StallTransaction();
					}
					else
					{
						Endpoint_ClearStall();
						Endpoint_ResetEndpoint(EndpointIndex);
						Endpoint_ResetDataToggle();
					}
				}
			}

			break;
		#endif
		default:
			return;
	}

	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);

	Endpoint_ClearSETUP();

	Endpoint_ClearStatusStage();
}

#endif

