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

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special 
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.  
 */

#include "Descriptors.h"

/* On some devices, there is a factory set internal serial number which can be automatically sent to the host as
 * the device's serial number when the Device Descriptor's .SerialNumStrIndex entry is set to USE_INTERNAL_SERIAL.
 * This allows the host to track a device across insertions on different ports, allowing them to retain allocated
 * resources like COM port numbers and drivers. On demos using this feature, give a warning on unsupported devices
 * so that the user can supply their own serial number descriptor instead or remove the USE_INTERNAL_SERIAL value
 * from the Device Descriptor (forcing the host to generate a serial number for each device from the VID, PID and
 * port location).
 */
#if (USE_INTERNAL_SERIAL == NO_DESCRIPTOR)
	#warning USE_INTERNAL_SERIAL is not available on this AVR - please manually construct a device serial descriptor.
#endif

/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] =
{
	0x05, 0x01,          /* Usage Page (Generic Desktop)             */
	0x09, 0x02,          /* Usage (Mouse)                            */
	0xA1, 0x01,          /* Collection (Application)                 */
	0x09, 0x01,          /*   Usage (Pointer)                        */
	0xA1, 0x00,          /*   Collection (Application)               */
	0x95, 0x03,          /*     Report Count (3)                     */
	0x75, 0x01,          /*     Report Size (1)                      */
	0x05, 0x09,          /*     Usage Page (Button)                  */
	0x19, 0x01,          /*     Usage Minimum (Button 1)             */
	0x29, 0x03,          /*     Usage Maximum (Button 3)             */
	0x15, 0x00,          /*     Logical Minimum (0)                  */
	0x25, 0x01,          /*     Logical Maximum (1)                  */
	0x81, 0x02,          /*     Input (Data, Variable, Absolute)     */
	0x95, 0x01,          /*     Report Count (1)                     */
	0x75, 0x05,          /*     Report Size (5)                      */
	0x81, 0x01,          /*     Input (Constant)                     */
	0x75, 0x08,          /*     Report Size (8)                      */
	0x95, 0x02,          /*     Report Count (2)                     */
	0x05, 0x01,          /*     Usage Page (Generic Desktop Control) */
	0x09, 0x30,          /*     Usage X                              */
	0x09, 0x31,          /*     Usage Y                              */
	0x15, 0x81,          /*     Logical Minimum (-127)               */
	0x25, 0x7F,          /*     Logical Maximum (127)                */
	0x81, 0x06,          /*     Input (Data, Variable, Relative)     */
	0xC0,                /*   End Collection                         */
	0xC0                 /* End Collection                           */
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
	.Class                  = 0xEF,
	.SubClass               = 0x02,
	.Protocol               = 0x01,
	
	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,
	
	.VendorID               = 0x03EB,
	.ProductID              = 0x2062,
	.ReleaseNumber          = 0x0000,
	
	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = USE_INTERNAL_SERIAL,
	
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
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
			.TotalInterfaces        = 3,
			
			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,
			
			.ConfigAttributes       = (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELFPOWERED),
			
			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.CDC_IAD = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_Association_t), .Type = DTYPE_InterfaceAssociation},

			.FirstInterfaceIndex    = 0,
			.TotalInterfaces        = 2,

			.Class                  = 0x02,
			.SubClass               = 0x02,
			.Protocol               = 0x01,

			.IADStrIndex            = NO_DESCRIPTOR
		},
		
	.CDC_CCI_Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 0,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
			
			.Class                  = 0x02,
			.SubClass               = 0x02,
			.Protocol               = 0x01,
			
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.CDC_Functional_IntHeader = 
		{
			.Header                 = {.Size = sizeof(CDC_FUNCTIONAL_DESCRIPTOR(2)), .Type = 0x24},
			.SubType                = 0x00,
			
			.Data                   = {0x01, 0x10}
		},

	.CDC_Functional_AbstractControlManagement = 
		{
			.Header                 = {.Size = sizeof(CDC_FUNCTIONAL_DESCRIPTOR(1)), .Type = 0x24},
			.SubType                = 0x02,
			
			.Data                   = {0x06}
		},
		
	.CDC_Functional_Union = 
		{
			.Header                 = {.Size = sizeof(CDC_FUNCTIONAL_DESCRIPTOR(2)), .Type = 0x24},
			.SubType                = 0x06,
			
			.Data                   = {0x00, 0x01}
		},

	.CDC_ManagementEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			
			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | CDC_NOTIFICATION_EPNUM),
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_NOTIFICATION_EPSIZE,
			.PollingIntervalMS      = 0xFF
		},

	.CDC_DCI_Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 1,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 2,
				
			.Class                  = 0x0A,
			.SubClass               = 0x00,
			.Protocol               = 0x00,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.CDC_DataOutEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			
			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_OUT | CDC_RX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x00
		},
		
	.CDC_DataInEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			
			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | CDC_TX_EPNUM),
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = CDC_TXRX_EPSIZE,
			.PollingIntervalMS      = 0x00
		},

	.HID_Interface = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = 2,
			.AlternateSetting       = 0,
			
			.TotalEndpoints         = 1,
				
			.Class                  = 0x03,
			.SubClass               = 0x01,
			.Protocol               = HID_BOOT_MOUSE_PROTOCOL,
				
			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.HID_MouseHID = 
		{
			.Header                 = {.Size = sizeof(USB_HID_Descriptor_t), .Type = DTYPE_HID},

			.HIDSpec                = VERSION_BCD(01.11),
			.CountryCode            = 0x00,
			.TotalReportDescriptors = 1,
			.HIDReportType          = DTYPE_Report,
			.HIDReportLength        = sizeof(MouseReport)
		},

	.HID_ReportINEndpoint = 
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = (ENDPOINT_DESCRIPTOR_DIR_IN | MOUSE_EPNUM),
			.Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = MOUSE_EPSIZE,
			.PollingIntervalMS      = 0x0A
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
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
	.Header                 = {.Size = USB_STRING_LEN(11), .Type = DTYPE_String},

	.UnicodeString          = L"Dean Camera"
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(23), .Type = DTYPE_String},

	.UnicodeString          = L"LUFA CDC and Mouse Demo"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void*          Address = NULL;
	uint16_t       Size    = NO_DESCRIPTOR;

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
			}
			
			break;
		case DTYPE_HID: 
			Address = (void*)&ConfigurationDescriptor.HID_MouseHID;
			Size    = sizeof(USB_HID_Descriptor_t);
			break;
		case DTYPE_Report: 
			Address = (void*)&MouseReport;
			Size    = sizeof(MouseReport);
			break;
	}
	
	*DescriptorAddress = Address;
	return Size;
}
