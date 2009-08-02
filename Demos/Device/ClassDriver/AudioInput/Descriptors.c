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

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special 
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.  
 */
 
#include "Descriptors.h"

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(02.00),
	.Class                  = 0x00,
	.SubClass               = 0x00,
	.Protocol               = 0x00,

	.Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

	.VendorID               = 0x03EB,
	.ProductID              = 0x2047,
	.ReleaseNumber          = 0x0000,

	.ManufacturerStrIndex   = 0x01,
	.ProductStrIndex        = 0x02,
	.SerialNumStrIndex      = NO_DESCRIPTOR,

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
			.Header                   = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize   = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces          = 2,

			.ConfigurationNumber      = 1,
			.ConfigurationStrIndex    = NO_DESCRIPTOR,

			.ConfigAttributes         = (USB_CONFIG_ATTR_BUSPOWERED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption      = USB_CONFIG_POWER_MA(100)
		},

	.AudioControlInterface = 
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = 0,
			.AlternateSetting         = 0,
			
			.TotalEndpoints           = 0,

			.Class                    = 0x01,
			.SubClass                 = 0x01,
			.Protocol                 = 0x00,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},

	.AudioControlInterface_SPC = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_Interface_AC_t), .Type = DTYPE_AudioInterface},
			.Subtype                  = DSUBTYPE_Header,

			.ACSpecification          = VERSION_BCD(01.00),
			.TotalLength              = (sizeof(USB_Audio_Interface_AC_t) +
			                             sizeof(USB_Audio_InputTerminal_t) +
			                             sizeof(USB_Audio_OutputTerminal_t)),
			
			.InCollection             = 1,
			.InterfaceNumbers         = {1},
		},

	.InputTerminal = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_InputTerminal_t), .Type = DTYPE_AudioInterface},
			.Subtype                  = DSUBTYPE_InputTerminal,

			.TerminalID               = 0x01,
			.TerminalType             = TERMINAL_IN_MIC,
			.AssociatedOutputTerminal = 0x00,

			.TotalChannels            = 1,
			.ChannelConfig            = 0,

			.ChannelStrIndex          = NO_DESCRIPTOR,
			.TerminalStrIndex         = NO_DESCRIPTOR
		},

	.OutputTerminal = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_OutputTerminal_t), .Type = DTYPE_AudioInterface},
			.Subtype                  = DSUBTYPE_OutputTerminal,

			.TerminalID               = 0x02,
			.TerminalType             = TERMINAL_STREAMING,
			.AssociatedInputTerminal  = 0x00,

			.SourceID                 = 0x01,

			.TerminalStrIndex         = NO_DESCRIPTOR
		},

	.AudioStreamInterface_Alt0 = 
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = 1,
			.AlternateSetting         = 0,

			.TotalEndpoints           = 0,

			.Class                    = 0x01,
			.SubClass                 = 0x02,
			.Protocol                 = 0x00,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},

	.AudioStreamInterface_Alt1 = 
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = 1,
			.AlternateSetting         = 1,

			.TotalEndpoints           = 1,

			.Class                    = 0x01,
			.SubClass                 = 0x02,
			.Protocol                 = 0x00,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},

	.AudioStreamInterface_SPC = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_Interface_AS_t), .Type = DTYPE_AudioInterface},
			.Subtype                  = DSUBTYPE_General,

			.TerminalLink             = 0x02,

			.FrameDelay               = 1,
			.AudioFormat              = 0x0001
		},

	.AudioFormat = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_Format_t), .Type = DTYPE_AudioInterface},
			.Subtype                  = DSUBTYPE_Format,

			.FormatType               = 0x01,
			.Channels                 = 0x01,
			
			.SubFrameSize             = 0x02,
			.BitResolution            = 16,
			.SampleFrequencyType      = (AUDIO_TOTAL_SAMPLE_RATES * sizeof(USB_Audio_SampleFreq_t)),
		
			.SampleFrequencies        = {AUDIO_SAMPLE_FREQ(AUDIO_SAMPLE_FREQUENCY)}
		},
	
	.AudioEndpoint = 
		{
			.Endpoint = 
				{
					.Header              = {.Size = sizeof(USB_Audio_StreamEndpoint_Std_t), .Type = DTYPE_Endpoint},

					.EndpointAddress     = (ENDPOINT_DESCRIPTOR_DIR_IN | AUDIO_STREAM_EPNUM),
					.Attributes          = (EP_TYPE_ISOCHRONOUS | ENDPOINT_ATTR_SYNC | ENDPOINT_USAGE_DATA),
					.EndpointSize        = AUDIO_STREAM_EPSIZE,
					.PollingIntervalMS   = 1
				},
			
			.Refresh                  = 0,
			.SyncEndpointNumber       = 0
		},
		
	.AudioEndpoint_SPC = 
		{
			.Header                   = {.Size = sizeof(USB_Audio_StreamEndpoint_Spc_t), .Type = DTYPE_AudioEndpoint},
			.Subtype                  = DSUBTYPE_General,
			
			.Attributes               = 0x00,
			
			.LockDelayUnits           = 0x00,
			.LockDelay                = 0x0000
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
	.Header                 = {.Size = USB_STRING_LEN(18), .Type = DTYPE_String},

	.UnicodeString          = L"LUFA Audio In Demo"
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
			}
			
			break;
	}
	
	*DescriptorAddress = Address;
	return Size;
}
