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

#include "../HighLevel/USBMode.h"

#if defined(USB_CAN_BE_DEVICE)

#define  INCLUDE_FROM_DEVCHAPTER9_C
#include "DevChapter9.h"

uint8_t USB_ConfigurationNumber;
bool    USB_RemoteWakeupEnabled;
bool    USB_CurrentlySelfPowered;

void USB_Device_ProcessControlPacket(void)
{
	bool     RequestHandled = false;
	uint8_t* RequestHeader  = (uint8_t*)&USB_ControlRequest;
	
	for (uint8_t RequestHeaderByte = 0; RequestHeaderByte < sizeof(USB_Request_Header_t); RequestHeaderByte++)
	  *(RequestHeader++) = Endpoint_Read_Byte();
	  
	uint8_t bmRequestType = USB_ControlRequest.bmRequestType;
	
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetStatus:
			if ((bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE)) ||
			    (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT)))
			{
				USB_Device_GetStatus();
				RequestHandled = true;
			}

			break;
		case REQ_ClearFeature:
		case REQ_SetFeature:
			if ((bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE)) ||
			    (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT)))
			{
				USB_Device_ClearSetFeature();
				RequestHandled = true;
			}

			break;
		case REQ_SetAddress:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE))
			{
				USB_Device_SetAddress();
				RequestHandled = true;
			}

			break;
		case REQ_GetDescriptor:
			if ((bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE)) ||
			    (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE)))
			{
				USB_Device_GetDescriptor();
				RequestHandled = true;
			}
			
			break;
		case REQ_GetConfiguration:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE))
			{
				USB_Device_GetConfiguration();
				RequestHandled = true;
			}

			break;
		case REQ_SetConfiguration:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE))
			{
				USB_Device_SetConfiguration();
				RequestHandled = true;
			}

			break;
	}

	if (!(RequestHandled))
	  EVENT_USB_UnhandledControlPacket();
	  
	if (Endpoint_IsSETUPReceived())
	{
		Endpoint_StallTransaction();
		Endpoint_ClearSETUP();		
	}
}

static void USB_Device_SetAddress(void)
{
	Endpoint_ClearSETUP();
	
	Endpoint_ClearIN();
	
	while (!(Endpoint_IsINReady()));

	UDADDR = ((1 << ADDEN) | ((uint8_t)USB_ControlRequest.wValue & 0x7F));

	return;
}

static void USB_Device_SetConfiguration(void)
{
	bool AlreadyConfigured = (USB_ConfigurationNumber != 0);

#if defined(USE_SINGLE_DEVICE_CONFIGURATION)
	if ((uint8_t)USB_ControlRequest.wValue > 1)
#else
	USB_Descriptor_Device_t* DevDescriptorPtr;

	if ((CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DevDescriptorPtr) == NO_DESCRIPTOR) ||
	#if defined(USE_RAM_DESCRIPTORS)
	    ((uint8_t)USB_ControlRequest.wValue > DevDescriptorPtr->NumberOfConfigurations))
	#elif defined (USE_EEPROM_DESCRIPTORS)
	    ((uint8_t)USB_ControlRequest.wValue > eeprom_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
	#else
	    ((uint8_t)USB_ControlRequest.wValue > pgm_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
	#endif
#endif
	{
		return;
	}
	
	Endpoint_ClearSETUP();

	USB_ConfigurationNumber = (uint8_t)USB_ControlRequest.wValue;

	Endpoint_ClearIN();

	if (!(AlreadyConfigured) && USB_ConfigurationNumber)
	  EVENT_USB_DeviceEnumerationComplete();

	EVENT_USB_ConfigurationChanged();
}

void USB_Device_GetConfiguration(void)
{
	Endpoint_ClearSETUP();

	Endpoint_Write_Byte(USB_ConfigurationNumber);
	
	Endpoint_ClearIN();

	while (!(Endpoint_IsOUTReceived()));
	Endpoint_ClearOUT();
}

static void USB_Device_GetDescriptor(void)
{
	void*    DescriptorPointer;
	uint16_t DescriptorSize;
	
	#if !defined(NO_INTERNAL_SERIAL) && (defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
	if (USB_ControlRequest.wValue == ((DTYPE_String << 8) | USE_INTERNAL_SERIAL))
	{
		struct
		{
			USB_Descriptor_Header_t Header;
			int16_t                 UnicodeString[12];
		} SignatureDescriptor;

		#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES)
			SignatureDescriptor.Header.Size            = sizeof(SignatureDescriptor);
			SignatureDescriptor.Header.Type            = DTYPE_String;
		#else
			SignatureDescriptor.Header.bLength         = sizeof(SignatureDescriptor);
			SignatureDescriptor.Header.bDescriptorType = DTYPE_String;
		#endif
		
		uint8_t  SigReadAddress  = 0x0E;		
		bool     OddRead         = false;

		for (uint8_t SerialCharNum = 0; SerialCharNum < 12; SerialCharNum++)
		{
			uint8_t SerialByte = boot_signature_byte_get(SigReadAddress);
			
			if (OddRead)
			{
				SerialByte >>= 4;
				SigReadAddress++;
			}
			else
			{
				SerialByte &= 0x0F;
			}
			
			OddRead = !(OddRead);

			if (SerialByte < 0x0A)
			  SerialByte += '0';
			else
			  SerialByte += ('A' - 0x0A);

			SignatureDescriptor.UnicodeString[SerialCharNum] = SerialByte;
		}
		
		Endpoint_ClearSETUP();
		Endpoint_Write_Control_Stream_LE(&SignatureDescriptor, sizeof(SignatureDescriptor));
		Endpoint_ClearOUT();

		return;
	}
	#endif
	
	if ((DescriptorSize = CALLBACK_USB_GetDescriptor(USB_ControlRequest.wValue, USB_ControlRequest.wIndex,
	                                                 &DescriptorPointer)) == NO_DESCRIPTOR)
	{
		return;
	}
	
	Endpoint_ClearSETUP();

	#if defined(USE_RAM_DESCRIPTORS)
	Endpoint_Write_Control_Stream_LE(DescriptorPointer, DescriptorSize);
	#else
	bool SendZLP;
	
	if (USB_ControlRequest.wLength > DescriptorSize)
	  USB_ControlRequest.wLength = DescriptorSize;
	
	while (USB_ControlRequest.wLength)
	{
		while (!(Endpoint_IsINReady()))
		{
			if (Endpoint_IsOUTReceived())
			{
				Endpoint_ClearOUT();
				return;
			}		
		}
		
		while (USB_ControlRequest.wLength && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			#if defined (USE_EEPROM_DESCRIPTORS)
			Endpoint_Write_Byte(eeprom_read_byte(DescriptorPointer++));		
			#else
			Endpoint_Write_Byte(pgm_read_byte(DescriptorPointer++));
			#endif
			
			USB_ControlRequest.wLength--;
		}
		
		SendZLP = (Endpoint_BytesInEndpoint() == USB_ControlEndpointSize);
		Endpoint_ClearIN();
	}
	
	if (SendZLP)
	{
		while (!(Endpoint_IsINReady()));
		Endpoint_ClearIN();
	}

	while (!(Endpoint_IsOUTReceived()));
	#endif
	
	Endpoint_ClearOUT();
}

static void USB_Device_GetStatus(void)
{
	uint8_t CurrentStatus = 0;

	switch (USB_ControlRequest.bmRequestType)
	{
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE):
			if (USB_CurrentlySelfPowered)
			  CurrentStatus |= FEATURE_SELFPOWERED_ENABLED;
			
			if (USB_RemoteWakeupEnabled)
			  CurrentStatus |= FEATURE_REMOTE_WAKEUP_ENABLED;
			
			break;
#if !defined(CONTROL_ONLY_DEVICE)
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT):
			Endpoint_SelectEndpoint((uint8_t)USB_ControlRequest.wIndex);

			CurrentStatus = Endpoint_IsStalled();

			Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);			  

			break;
#endif
	}

	Endpoint_ClearSETUP();

	Endpoint_Write_Word_LE(CurrentStatus);

	Endpoint_ClearIN();
	
	while (!(Endpoint_IsOUTReceived()));
	Endpoint_ClearOUT();
}

static void USB_Device_ClearSetFeature(void)
{	
	switch (USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_RECIPIENT)
	{
		case REQREC_DEVICE:
			if ((uint8_t)USB_ControlRequest.wValue == FEATURE_REMOTE_WAKEUP)
			  USB_RemoteWakeupEnabled = (USB_ControlRequest.bRequest == REQ_SetFeature);
			else
			  return;
			
			break;			
#if !defined(CONTROL_ONLY_DEVICE)
		case REQREC_ENDPOINT:
			if ((uint8_t)USB_ControlRequest.wValue == FEATURE_ENDPOINT_HALT)
			{
				uint8_t EndpointIndex = ((uint8_t)USB_ControlRequest.wIndex & ENDPOINT_EPNUM_MASK);
				
				if (EndpointIndex == ENDPOINT_CONTROLEP)
				  return;

				Endpoint_SelectEndpoint(EndpointIndex);

				if (Endpoint_IsEnabled())
				{				
					if (USB_ControlRequest.bRequest == REQ_ClearFeature)
					{
						Endpoint_ClearStall();
						Endpoint_ResetFIFO(EndpointIndex);
						Endpoint_ResetDataToggle();
					}
					else
					{
						Endpoint_StallTransaction();
					}
				}
			}
			
			break;
#endif
	}

	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);

	Endpoint_ClearSETUP();

	Endpoint_ClearIN();
}

#endif
