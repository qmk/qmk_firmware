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

#include "Descriptors.h"

USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	Header:                 {Size: sizeof(USB_Descriptor_Device_t), Type: DTYPE_Device},
		
	USBSpecification:       VERSION_BCD(02.00),
	Class:                  0x00,
	SubClass:               0x00,
	Protocol:               0x00,
				
	Endpoint0Size:          8,
		
	VendorID:               0x03EB,
	ProductID:              0x2040,
	ReleaseNumber:          0x0001,
		
	ManufacturerStrIndex:   0x01,
	ProductStrIndex:        0x02,
	SerialNumStrIndex:      0x03,
		
	NumberOfConfigurations: 1
};
	
USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			Header:                 {Size: sizeof(USB_Descriptor_Configuration_Header_t), Type: DTYPE_Configuration},

			TotalConfigurationSize: sizeof(USB_Descriptor_Configuration_t),
			TotalInterfaces:        1,
				
			ConfigurationNumber:    1,
			ConfigurationStrIndex:  NO_DESCRIPTOR,
				
			ConfigAttributes:       (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELFPOWERED),
			
			MaxPowerConsumption:    USB_CONFIG_POWER_MA(100)
		},
		
	.SSHOW_Interface =
		{
			Header:                 {Size: sizeof(USB_Descriptor_Interface_t), Type: DTYPE_Interface},

			InterfaceNumber:        0,
			AlternateSetting:       0,
			
			TotalEndpoints:         2,
				
			Class:                  0xFF,
			SubClass:               0x00,
			Protocol:               0x00,
				
			InterfaceStrIndex:      NO_DESCRIPTOR
		},

	.SSHOW_DataInEndpoint =
		{
			Header:                 {Size: sizeof(USB_Descriptor_Endpoint_t), Type: DTYPE_Endpoint},

			EndpointAddress:        (ENDPOINT_DESCRIPTOR_DIR_IN | SIDESHOW_IN_EPNUM),
			Attributes:             EP_TYPE_BULK,
			EndpointSize:           SIDESHOW_IO_EPSIZE,
			PollingIntervalMS:      0x00
		},

	.SSHOW_DataOutEndpoint =
		{
			Header:                 {Size: sizeof(USB_Descriptor_Endpoint_t), Type: DTYPE_Endpoint},

			EndpointAddress:        (ENDPOINT_DESCRIPTOR_DIR_OUT | SIDESHOW_OUT_EPNUM),
			Attributes:             EP_TYPE_BULK,
			EndpointSize:           SIDESHOW_IO_EPSIZE,
			PollingIntervalMS:      0x00
		}
};

USB_Descriptor_String_t PROGMEM LanguageString =
{
	Header:                 {Size: USB_STRING_LEN(1), Type: DTYPE_String},
		
	UnicodeString:          {LANGUAGE_ID_ENG}
};

USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	Header:                 {Size: USB_STRING_LEN(11), Type: DTYPE_String},
		
	UnicodeString:          L"Dean Camera"
};

USB_Descriptor_String_t PROGMEM ProductString =
{
	Header:                 {Size: USB_STRING_LEN(22), Type: DTYPE_String},
		
	UnicodeString:          L"LUFA Sideshow Demo"
};

USB_Descriptor_String_t PROGMEM SerialNumberString =
{
	Header:                 {Size: USB_STRING_LEN(12), Type: DTYPE_String},
		
	UnicodeString:          L"000000000000"
};

USB_OSDescriptor_t PROGMEM OSDescriptorString =
{
	Header:                 {Size: sizeof(USB_OSDescriptor_t), Type: DTYPE_String},
	
	Signature:              L"MSFT100",
	VendorCode:             REQ_GetOSFeatureDescriptor
};

USB_OSCompatibleIDDescriptor_t PROGMEM DevCompatIDs =
{
	TotalLength:            sizeof(USB_OSCompatibleIDDescriptor_t),
	Version:                0x0100,
	Index:                  EXTENDED_COMPAT_ID_DESCRIPTOR,
	TotalSections:          1,
	
	SideshowCompatID:       {FirstInterfaceNumber: 0x00,
	                         CompatibleID: "SIDESHW",
	                         SubCompatibleID: "UNIV1"}
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*    Address = NULL;
	uint16_t Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = (void*)&DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = (void*)&ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = (void*)&LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = (void*)&ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = (void*)&ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
				case 0x03:
					Address = (void*)&SerialNumberString;
					Size    = pgm_read_byte(&SerialNumberString.Header.Size);
					break;
				case 0xEE:
					/* A Microsoft-proprietary extention. String address 0xEE is used by Windows for
					   "OS Descriptors", which in this case allows us to indicate that our device is
					   Sideshow compatible regardless of VID/PID values. */
					Address = (void*)&OSDescriptorString;
					Size    = pgm_read_byte(&OSDescriptorString.Header.Size);
					break;
			}
			
			break;
	}
	
	*DescriptorAddress = Address;		
	return Size;
}

bool USB_GetOSFeatureDescriptor(const uint16_t wValue, const uint8_t wIndex,
                                void** const DescriptorAddress, uint16_t* const DescriptorSize)
{
	void*    Address = NULL;
	uint16_t Size    = 0;

	/* Check if a device level OS feature descriptor is being requested */
	if (wValue == 0x0000)
	{
		/* Only the Extended Device Compatibility descriptor is supported */
		if (wIndex == EXTENDED_COMPAT_ID_DESCRIPTOR)
		{
			Address = (void*)&DevCompatIDs;
			Size    = sizeof(USB_OSCompatibleIDDescriptor_t);
		}
	}

	if (Address != NULL)
	{
		*DescriptorAddress = Address;
		*DescriptorSize    = Size;

		return true;
	}
		
	return false;
}