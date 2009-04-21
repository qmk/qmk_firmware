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
	uint8_t bmRequestType  = Endpoint_Read_Byte();
	uint8_t bRequest       = Endpoint_Read_Byte();
	bool    RequestHandled = false;	
	
	switch (bRequest)
	{
		case REQ_GetStatus:
			if ((bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE)) ||
			    (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT)))
			{
				USB_Device_GetStatus(bmRequestType);
				RequestHandled = true;
			}

			break;
#if !defined(FEATURELESS_CONTROL_ONLY_DEVICE)
		case REQ_ClearFeature:
		case REQ_SetFeature:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_ENDPOINT))
			{
				USB_Device_ClearSetFeature(bRequest, bmRequestType);
				RequestHandled = true;
			}

			break;
#endif
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
	  RAISE_EVENT(USB_UnhandledControlPacket, bRequest, bmRequestType);
	  
	if (Endpoint_IsSETUPReceived())
	{
		Endpoint_StallTransaction();
		Endpoint_ClearSETUP();		
	}
}

static void USB_Device_SetAddress(void)
{
	uint8_t wValue_LSB = Endpoint_Read_Byte();

	Endpoint_ClearSETUP();
	
	while (!(Endpoint_IsINReady()));
	
	Endpoint_ClearIN();
	
	while (!(Endpoint_IsINReady()));

	UDADDR = ((1 << ADDEN) | (wValue_LSB & 0x7F));

	return;
}

static void USB_Device_SetConfiguration(void)
{
	uint8_t wValue_LSB        = Endpoint_Read_Byte();
	bool    AlreadyConfigured = (USB_ConfigurationNumber != 0);

#if defined(USE_SINGLE_DEVICE_CONFIGURATION)
	if (wValue_LSB > 1)
#else
	USB_Descriptor_Device_t* DevDescriptorPtr;

	if ((USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DevDescriptorPtr) == NO_DESCRIPTOR) ||
	#if defined(USE_RAM_DESCRIPTORS)
	    (wValue_LSB > DevDescriptorPtr->NumberOfConfigurations))
	#elif defined (USE_EEPROM_DESCRIPTORS)
	    (wValue_LSB > eeprom_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
	#else
	    (wValue_LSB > pgm_read_byte(&DevDescriptorPtr->NumberOfConfigurations)))
	#endif
#endif
	{
		return;
	}
	
	Endpoint_ClearSETUP();

	USB_ConfigurationNumber = wValue_LSB;

	Endpoint_ClearIN();

	if (!(AlreadyConfigured) && USB_ConfigurationNumber)
	  RAISE_EVENT(USB_DeviceEnumerationComplete);

	RAISE_EVENT(USB_ConfigurationChanged);
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
	uint16_t wValue  = Endpoint_Read_Word_LE();
	uint16_t wIndex  = Endpoint_Read_Word_LE();
	uint16_t wLength = Endpoint_Read_Word_LE();
	
	void*    DescriptorPointer;
	uint16_t DescriptorSize;
	
	bool     SendZLP;
	
	if ((DescriptorSize = USB_GetDescriptor(wValue, wIndex, &DescriptorPointer)) == NO_DESCRIPTOR)
	  return;
	
	Endpoint_ClearSETUP();	
	
	if (wLength > DescriptorSize)
	  wLength = DescriptorSize;
	
	while (wLength)
	{
		while (!(Endpoint_IsINReady()))
		{
			if (Endpoint_IsOUTReceived())
			{
				Endpoint_ClearOUT();
				return;
			}		
		}
		
		while (wLength && (Endpoint_BytesInEndpoint() < USB_ControlEndpointSize))
		{
			#if defined(USE_RAM_DESCRIPTORS)
			Endpoint_Write_Byte(*((uint8_t*)DescriptorPointer++));
			#elif defined (USE_EEPROM_DESCRIPTORS)
			Endpoint_Write_Byte(eeprom_read_byte(DescriptorPointer++));			
			#else
			Endpoint_Write_Byte(pgm_read_byte(DescriptorPointer++));
			#endif
			
			wLength--;
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
	Endpoint_ClearOUT();
}

static void USB_Device_GetStatus(const uint8_t bmRequestType)
{
	uint8_t CurrentStatus = 0;

	Endpoint_Discard_Word();

#if !defined(FEATURELESS_CONTROL_ONLY_DEVICE)
	uint8_t wIndex_LSB = Endpoint_Read_Byte();
#endif
	
	switch (bmRequestType)
	{
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE):
			if (USB_CurrentlySelfPowered)
			  CurrentStatus |= FEATURE_SELFPOWERED_ENABLED;
			
			if (USB_RemoteWakeupEnabled)
			  CurrentStatus |= FEATURE_REMOTE_WAKEUP_ENABLED;
			
			break;
#if !defined(FEATURELESS_CONTROL_ONLY_DEVICE)
		case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_ENDPOINT):
			Endpoint_SelectEndpoint(wIndex_LSB);

			CurrentStatus = Endpoint_IsStalled();

			break;
#endif
	}
	
	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);			  
	Endpoint_ClearSETUP();

	Endpoint_Write_Word_LE(CurrentStatus);

	Endpoint_ClearIN();
	
	while (!(Endpoint_IsOUTReceived()));
	Endpoint_ClearOUT();
}

#if !defined(FEATURELESS_CONTROL_ONLY_DEVICE)
static void USB_Device_ClearSetFeature(const uint8_t bRequest, const uint8_t bmRequestType)
{
	uint16_t wValue = Endpoint_Read_Word_LE();
	uint16_t wIndex = Endpoint_Read_Word_LE();
	
	switch (bmRequestType & CONTROL_REQTYPE_RECIPIENT)
	{
		case REQREC_ENDPOINT:
			if (wValue == FEATURE_ENDPOINT_HALT)
			{
				uint8_t EndpointIndex = (wIndex & ENDPOINT_EPNUM_MASK);
				
				if (EndpointIndex != ENDPOINT_CONTROLEP)
				{
					Endpoint_SelectEndpoint(EndpointIndex);

					if (Endpoint_IsEnabled())
					{				
						if (bRequest == REQ_ClearFeature)
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

					Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);
					Endpoint_ClearSETUP();
					Endpoint_ClearIN();
				}
			}
			
			break;
	}
}
#endif

#endif
