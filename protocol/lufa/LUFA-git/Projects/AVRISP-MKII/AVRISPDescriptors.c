/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "AVRISPDescriptors.h"

#if defined(RESET_TOGGLES_LIBUSB_COMPAT) || defined(__DOXYGEN__)
	/** Indicates if an external reset has occurred and the compatibility mode needs to be altered */
	static bool AVRISP_NeedCompatibilitySwitch ATTR_NO_INIT;

	/** Current AVRISP data IN endpoint address. */
	uint8_t AVRISP_CurrDataINEndpointAddress;

	/** Saved AVRISP data IN endpoint address in EEPROM. */
	uint8_t AVRISP_CurrDataINEndpointAddress_EEPROM EEMEM;
#endif

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM AVRISP_DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(1,1,0),
	.Class                  = USB_CSCP_VendorSpecificClass,
	.SubClass               = USB_CSCP_NoDeviceSubclass,
	.Protocol               = USB_CSCP_NoDeviceProtocol,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03EB,
	.ProductID              = 0x2104,
	.ReleaseNumber          = VERSION_BCD(2,0,0),

	.ManufacturerStrIndex   = AVRISP_STRING_ID_Manufacturer,
	.ProductStrIndex        = AVRISP_STRING_ID_Product,
	.SerialNumStrIndex      = AVRISP_STRING_ID_Serial,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
AVRISP_USB_Descriptor_Configuration_t AVRISP_ConfigurationDescriptor =
{
	.Config =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize = sizeof(AVRISP_USB_Descriptor_Configuration_t),
			.TotalInterfaces        = 1,

			.ConfigurationNumber    = 1,
			.ConfigurationStrIndex  = NO_DESCRIPTOR,

			.ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption    = USB_CONFIG_POWER_MA(100)
		},

	.AVRISP_Interface =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber        = INTERFACE_ID_AVRISP,
			.AlternateSetting       = 0,

			.TotalEndpoints         = 2,

			.Class                  = USB_CSCP_VendorSpecificClass,
			.SubClass               = USB_CSCP_NoDeviceSubclass,
			.Protocol               = USB_CSCP_NoDeviceProtocol,

			.InterfaceStrIndex      = NO_DESCRIPTOR
		},

	.AVRISP_DataInEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

#if defined(RESET_TOGGLES_LIBUSB_COMPAT)
			.EndpointAddress        = 0,
#else
			.EndpointAddress        = AVRISP_DATA_IN_EPADDR,
#endif
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = AVRISP_DATA_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},

	.AVRISP_DataOutEndpoint =
		{
			.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

			.EndpointAddress        = AVRISP_DATA_OUT_EPADDR,
			.Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize           = AVRISP_DATA_EPSIZE,
			.PollingIntervalMS      = 0x0A
		},
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM AVRISP_LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM AVRISP_ManufacturerString = USB_STRING_DESCRIPTOR(L"ATMEL");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM AVRISP_ProductString = USB_STRING_DESCRIPTOR(L"AVRISP mkII");

/** Serial number string. This is a Unicode string containing the device's unique serial number, expressed as a
 *  series of uppercase hexadecimal digits.
 */
USB_Descriptor_String_t AVRISP_SerialString = USB_STRING_DESCRIPTOR(L"000200012345\0"
    // Note: Real AVRISP-MKII has the embedded NUL byte, bug in firmware?
);

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t AVRISP_GetDescriptor(const uint16_t wValue,
                              const uint8_t wIndex,
                              const void** const DescriptorAddress,
                              uint8_t* DescriptorMemorySpace)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	*DescriptorMemorySpace = MEMSPACE_FLASH;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &AVRISP_DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			*DescriptorMemorySpace = MEMSPACE_RAM;
			#if defined(RESET_TOGGLES_LIBUSB_COMPAT)
				/* Update the configuration descriptor with the current endpoint address */
				AVRISP_ConfigurationDescriptor.AVRISP_DataInEndpoint.EndpointAddress = AVRISP_CurrDataINEndpointAddress;
			#endif

			Address = &AVRISP_ConfigurationDescriptor;
			Size    = sizeof(AVRISP_USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case AVRISP_STRING_ID_Language:
					Address = &AVRISP_LanguageString;
					Size    = pgm_read_byte(&AVRISP_LanguageString.Header.Size);
					break;
				case AVRISP_STRING_ID_Manufacturer:
					Address = &AVRISP_ManufacturerString;
					Size    = pgm_read_byte(&AVRISP_ManufacturerString.Header.Size);
					break;
				case AVRISP_STRING_ID_Product:
					Address = &AVRISP_ProductString;
					Size    = pgm_read_byte(&AVRISP_ProductString.Header.Size);
					break;
				case AVRISP_STRING_ID_Serial:
					Address = &AVRISP_SerialString;
					Size    = AVRISP_SerialString.Header.Size;

					/* Update serial number to have a different serial based on the current endpoint address */
					((uint16_t*)&AVRISP_SerialString.UnicodeString)[6] = cpu_to_le16('0' + (AVRISP_DATA_IN_EPADDR & ENDPOINT_EPNUM_MASK));

					*DescriptorMemorySpace = MEMSPACE_RAM;
					break;
			}

			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

#if defined(RESET_TOGGLES_LIBUSB_COMPAT) || defined(__DOXYGEN__)
/** Checks the state of the system status register MCUSR and indicates via a flag if
 *  the current AVRISP driver compatibility mode needs to be reset.
 *
 *  When the \c RESET_TOGGLES_LIBUSB_COMPAT compile time option is enabled, pulling
 *  the reset line of the AVR low will toggle between Jungo and libUSB compatibility
 *  modes. Other forms of reset (such as power on or watchdog) will not force a mode
 *  change.
 */
void CheckExternalReset(void)
{
	/* If an external reset occurred, we need to change compatibility mode */
	AVRISP_NeedCompatibilitySwitch = (MCUSR == (1 << EXTRF));

	MCUSR = 0;
}

/** Updates the device descriptors so that the correct compatibility mode is used
 *  when the \c RESET_TOGGLES_LIBUSB_COMPAT compile time option is enabled. This
 *  configures the programmer for either Jungo or libUSB driver compatibility. Each
 *  time the AVR is reset via pulling the reset line low the compatibility mode will
 *  be toggled. The current mode is stored in EEPROM and preserved through power
 *  cycles of the AVR.
 */
void UpdateCurrentCompatibilityMode(void)
{
	/* Load the current IN endpoint address stored in EEPROM */
	AVRISP_CurrDataINEndpointAddress = eeprom_read_byte(&AVRISP_CurrDataINEndpointAddress_EEPROM);

	/* Check if we need to switch compatibility modes */
	if (AVRISP_NeedCompatibilitySwitch)
	{
		/* Toggle between compatibility modes */
		AVRISP_CurrDataINEndpointAddress = (AVRISP_CurrDataINEndpointAddress == AVRISP_DATA_IN_EPADDR_LIBUSB) ?
				AVRISP_DATA_IN_EPADDR_JUNGO : AVRISP_DATA_IN_EPADDR_LIBUSB;

		/* Save the new mode into EEPROM */
		eeprom_update_byte(&AVRISP_CurrDataINEndpointAddress_EEPROM, AVRISP_CurrDataINEndpointAddress);
	}

	LEDs_SetAllLEDs(LEDS_NO_LEDS);

	/* Validate IN endpoint address and indicate current mode via LED flashes */
	switch (AVRISP_CurrDataINEndpointAddress)
	{
		default:
			/* Default to Jungo compatibility mode if saved EEPROM is invalid */
			AVRISP_CurrDataINEndpointAddress = AVRISP_DATA_IN_EPADDR_JUNGO;
		case AVRISP_DATA_IN_EPADDR_JUNGO:
			/* Two flashes for Jungo compatibility mode */
			for (uint8_t i = 0; i < 4; i++)
			{
				LEDs_ToggleLEDs(LEDS_ALL_LEDS);
				Delay_MS(100);
			}
			break;
		case AVRISP_DATA_IN_EPADDR_LIBUSB:
			/* Five flashes for libUSB compatibility mode */
			for (uint8_t i = 0; i < 10; i++)
			{
				LEDs_ToggleLEDs(LEDS_ALL_LEDS);
				Delay_MS(100);
			}
			break;
	}

	Delay_MS(500);
}
#endif
