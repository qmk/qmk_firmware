/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
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

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special 
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.  
 */
 
#include "Descriptors.h"

/** HID report descriptor. This is a HID class specific descriptor, which defines the structure of the
 *  reports sent and received by the HID device to and from the USB host. It indicates what data is sent,
 *  where in the report each element is located and exactly how the data should be interpreted and used.
 *
 *  See the HID class specification for more information on HID report descriptors.
 */
USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] =
{
	0x05, 0x01,          /* Usage Page (Generic Desktop)                    */
	0x09, 0x06,          /* Usage (Keyboard)                                */
	0xa1, 0x01,          /* Collection (Application)                        */
	0x05, 0x07,          /*   Usage Page (Key Codes)                        */
	0x19, 0xe0,          /*   Usage Minimum (Keyboard LeftControl)          */
	0x29, 0xe7,          /*   Usage Maximum (Keyboard Right GUI)            */
	0x15, 0x00,          /*   Logical Minimum (0)                           */
	0x25, 0x01,          /*   Logical Maximum (1)                           */
	0x75, 0x01,          /*   Report Size (1)                               */
	0x95, 0x08,          /*   Report Count (8)                              */
	0x81, 0x02,          /*   Input (Data, Variable, Absolute)              */
	0x95, 0x01,          /*   Report Count (1)                              */
	0x75, 0x08,          /*   Report Size (8)                               */
	0x81, 0x03,          /*   Input (Const, Variable, Absolute)             */
	0x95, 0x01,          /*   Report Count (1)                              */
	0x75, 0x08,          /*   Report Size (8)                               */
	0x15, 0x00,          /*   Logical Minimum (0)                           */
	0x25, 0x65,          /*   Logical Maximum (101)                         */
	0x05, 0x07,          /*   Usage Page (Keyboard)                         */
	0x19, 0x00,          /*   Usage Minimum (Reserved (no event indicated)) */
	0x29, 0x65,          /*   Usage Maximum (Keyboard Application)          */
	0x81, 0x00,          /*   Input (Data, Array, Absolute)                 */
	0xc0                 /* End Collection                                  */
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
		
	.USBSpecification       = VERSION_BCD(01.10),
	.Class                  = 0x00,
	.SubClass               = 0x00,
	.Protocol               = 0x00,
				
	.Endpoint0Size          = 8,
		
	.VendorID               = 0x03EB,
	.ProductID              = 0x2042,
	.ReleaseNumber          = 0x0000,
		
	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,
		
	.NumberOfConfigurations = 1
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,
				
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
				
			.ConfigAttributes       = (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELFPOWERED),
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},
		
	.Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0x00,
			.AlternateSetting       = 0x00,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = 0x01,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.KeyboardHID = 
		{  
			.Header                 = {.Size = sizeof(USB_Descriptor_HID_t), .Type = DTYPE_HID},
			
			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalHIDReports        = 0x01,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(KeyboardReport)
		},
		
	.KeyboardEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | KEYBOARD_EPNUM),
			.Attributes             = EP_TYPE_INTERRUPT,
			.EndpointSize           = KEYBOARD_EPSIZE,
			.PollingIntervalMS      = 0x04
		},
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors. */ 
USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
		
	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(32), .Type = DTYPE_String},
		
	.UnicodeString          = L"Dean Camera and Denver Gingerich"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(20), .Type = DTYPE_String},
		
	.UnicodeString          = L"Magnetic Card Reader"
};

/** This function is called by the library when in device mode, and must be overridden (see StdDescriptors.h
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*    Address = NULL;
	uint16_t Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = DESCRIPTOR_ADDRESS(DeviceDescriptor);
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = DESCRIPTOR_ADDRESS(ConfigurationDescriptor);
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case 0x00:
					Address = DESCRIPTOR_ADDRESS(LanguageString);
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case 0x01:
					Address = DESCRIPTOR_ADDRESS(ManufacturerString);
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case 0x02:
					Address = DESCRIPTOR_ADDRESS(ProductString);
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}
			
			break;
		case DTYPE_HID:
			Address = DESCRIPTOR_ADDRESS(ConfigurationDescriptor.KeyboardHID);
			Size    = sizeof(USB_Descriptor_HID_t);
			break;
		case DTYPE_Report:
			Address = DESCRIPTOR_ADDRESS(KeyboardReport);
			Size    = sizeof(KeyboardReport);
			break;
	}
	
	*DescriptorAddress = Address;
	return Size;
}
