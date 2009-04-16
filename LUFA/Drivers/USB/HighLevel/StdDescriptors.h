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
 *  Standard USB device descriptor defines and retrieval routines, for USB devices. This module contains
 *  structures and macros for the easy creation of standard USB descriptors in USB device projects.
 *
 *  All standard descriptors have their elements named in an identical manner to the official USB specification,
 *  however slightly more verbose alternate (non-standard) names are also supplied if the macro
 *  USE_NONSTANDARD_DESCRIPTOR_NAMES is defined in the user project makefile and passed to the compiler at
 *  compilation time using the -D option.
 *
 *  The non-standard names are documented here - if USE_NONSTANDARD_DESCRIPTOR_NAMES is not defined, then all
 *  descriptors will contain elements named identically to the official USB specification. The alternately
 *  named descriptor elements are placed in the same order inside the descriptor structures as their officially
 *  named counterparts, thus they can be correlated easily with the official USB specification.
 */

/** \ingroup Group_USB
 *  @defgroup Group_Descriptors USB Descriptors
 *
 *  Functions, macros, variables, enums and types related to standard USB descriptors.
 *
 *  @{
 */
 
#ifndef __USBDESCRIPTORS_H__
#define __USBDESCRIPTORS_H__

	/* Includes: */
		#include <avr/pgmspace.h>
		#include <stdbool.h>

		#include "../../../Common/Common.h"
		#include "USBMode.h"
		#include "Events.h"
		
		#if defined(USB_CAN_BE_DEVICE)
			#include "../LowLevel/Device.h"
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Indicates that a given descriptor does not exist in the device. This can be used inside descriptors
			 *  for string descriptor indexes, or may be use as a return value for GetDescriptor when the specified
			 *  descriptor does not exist.
			 */
			#define NO_DESCRIPTOR                     0
			
			/** Macro to calculate the power value for the device descriptor, from a given number of milliamps. */
			#define USB_CONFIG_POWER_MA(x)            (x >> 1)

			/** Macro to calculate the Unicode length of a string with a given number of Unicode characters.
			 *  Should be used in string descriptor's headers for giving the string descriptor's byte length.
			 */
			#define USB_STRING_LEN(x)                 (sizeof(USB_Descriptor_Header_t) + (x << 1))
			
			/** Macro to encode a given four digit floating point version number (e.g. 01.23) into Binary Coded
			 *  Decimal format for descriptor fields requiring BCD encoding, such as the USB version number in the
			 *  standard device descriptor.
			 */
			#define VERSION_BCD(x)                    ((((VERSION_TENS(x) << 4) | VERSION_ONES(x)) << 8) | \
			                                          ((VERSION_TENTHS(x) << 4) | VERSION_HUNDREDTHS(x)))

			/** String language ID for the English language. Should be used in USB_Descriptor_Language_t descriptors
			 *  to indicate that the English language is supported by the device in its string descriptors.
			 */
			#define LANGUAGE_ID_ENG                   0x0409

			/** Can be masked with an endpoint address for a USB_Descriptor_Endpoint_t endpoint descriptor's
			 *  EndpointAddress value to indicate to the host that the endpoint is of the IN direction (i.e, from
			 *  device to host).
			 */
			#define ENDPOINT_DESCRIPTOR_DIR_IN        0x80

			/** Can be masked with an endpoint address for a USB_Descriptor_Endpoint_t endpoint descriptor's
			 *  EndpointAddress value to indicate to the host that the endpoint is of the OUT direction (i.e, from
			 *  host to device).
			 */
			#define ENDPOINT_DESCRIPTOR_DIR_OUT       0x00		

			/** Can be masked with other configuration descriptor attributes for a USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration can draw its power
			 *  from the host's VBUS line.
			 */
			#define USB_CONFIG_ATTR_BUSPOWERED        0x80

			/** Can be masked with other configuration descriptor attributes for a USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration can draw its power
			 *  from the device's own power source.
			 */
			#define USB_CONFIG_ATTR_SELFPOWERED       0xC0

			/** Can be masked with other configuration descriptor attributes for a USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration supports the
			 *  remote wakeup feature of the USB standard, allowing a suspended USB device to wake up the host upon
			 *  request.
			 */
			#define USB_CONFIG_ATTR_REMOTEWAKEUP      0xA0

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is not synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_NO_SYNC             (0 << 2)

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is asynchronous.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ASYNC               (1 << 2)

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is adaptive.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ADAPTIVE            (2 << 2)

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_SYNC                (3 << 2)
			
			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for data transfers.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_DATA               (0 << 4)

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_FEEDBACK           (1 << 4)

			/** Can be masked with other endpoint descriptor attributes for a USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for implicit feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_IMPLICIT_FEEDBACK  (2 << 4)

			/** Gives a void pointer to the specified descriptor (of any type). */
			#define DESCRIPTOR_ADDRESS(Descriptor)    ((void*)&Descriptor)

		/* Events: */
			#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
				/** This module raises the Device Error event while in device mode, if the USB_GetDescriptor()
				 *  routine is not hooked in the user application to properly return descriptors to the library.
				 *
				 *  \see Events.h for more information on this event.
				 */
				RAISES_EVENT(USB_DeviceError);
			#endif
			
		/* Enums: */
			/** Enum for the possible standard descriptor types, as given in each descriptor's header. */
			enum USB_DescriptorTypes_t
			{
				DTYPE_Device               = 0x01, /**< Indicates that the descriptor is a device descriptor. */
				DTYPE_Configuration        = 0x02, /**< Indicates that the descriptor is a configuration descriptor. */
				DTYPE_String               = 0x03, /**< Indicates that the descriptor is a string descriptor. */
				DTYPE_Interface            = 0x04, /**< Indicates that the descriptor is an interface descriptor. */
				DTYPE_Endpoint             = 0x05, /**< Indicates that the descriptor is an endpoint descriptor. */
				DTYPE_DeviceQualifier      = 0x06, /**< Indicates that the descriptor is a device qualifier descriptor. */
				DTYPE_Other                = 0x07, /**< Indicates that the descriptor is of other type. */
				DTYPE_InterfacePower       = 0x08, /**< Indicates that the descriptor is an interface power descriptor. */
				DTYPE_InterfaceAssociation = 0x0B, /**< Indicates that the descriptor is an interface association descriptor. */
			};

		/* Type Defines: */
			/** Type define for all descriptor's header, indicating the descriptor's length and type.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				uint8_t Size; /**< Size of the descriptor, in bytes. */
				uint8_t Type; /**< Type of the descriptor, either a value in DescriptorTypes_t or a value
				               *   given by the specific class.
				               */
				#else
				uint8_t bLength;
				uint8_t bDescriptorType;
				#endif
			} USB_Descriptor_Header_t;
			
			/** Type define for a standard device descriptor.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint16_t                USBSpecification; /**< BCD of the supported USB specification. */
				uint8_t                 Class; /**< USB device class. */
				uint8_t                 SubClass; /**< USB device subclass. */
				uint8_t                 Protocol; /**< USB device protocol. */
				
				uint8_t                 Endpoint0Size; /**< Size of the control (address 0) endpoint's bank in bytes. */
				
				uint16_t                VendorID; /**< Vendor ID for the USB product. */
				uint16_t                ProductID; /**< Unique product ID for the USB product. */
				uint16_t                ReleaseNumber; /**< Product release (version) number. */
				
				uint8_t                 ManufacturerStrIndex; /**< String index for the manufacturer's name. The
                                                               *   host will request this string via a separate
			                                                   *   control request for the string descriptor.
				                                               *
				                                               *   \note If no string supplied, use NO_DESCRIPTOR.
				                                               */
				uint8_t                 ProductStrIndex; /**< String index for the product name/details.
				                                          *
				                                          *  \see ManufacturerStrIndex structure entry.
				                                          */
				uint8_t                 SerialNumStrIndex; /**< String index for the product's globally unique hexadecimal
				                                            *   serial number, in uppercase Unicode ASCII.
				                                            *
				                                            *  \see ManufacturerStrIndex structure entry.
				                                            */

				uint8_t                 NumberOfConfigurations; /**< Total number of configurations supported by
				                                                 *   the device.
				                                                 */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				uint16_t                bcdUSB;
				uint8_t                 bDeviceClass;
				uint8_t                 bDeviceSubClass;
				uint8_t                 bDeviceProtocol;
				uint8_t                 bMaxPacketSize0;
				uint16_t                idVendor;
				uint16_t                idProduct;
				uint16_t                bcdDevice;
				uint8_t                 iManufacturer;
				uint8_t                 iProduct;
				uint8_t                 iSerialNumber;
				uint8_t                 bNumConfigurations;
				#endif
			} USB_Descriptor_Device_t;

			/** Type define for a standard configuration descriptor.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
			
				uint16_t                TotalConfigurationSize; /**< Size of the configuration descriptor header,
				                                                 *   and all sub descriptors inside the configuration.
				                                                 */
				uint8_t                 TotalInterfaces; /**< Total number of interfaces in the configuration. */

				uint8_t                 ConfigurationNumber; /**< Configuration index of the current configuration. */
				uint8_t                 ConfigurationStrIndex; /**< Index of a string descriptor describing the configuration. */
				
				uint8_t                 ConfigAttributes; /**< Configuration attributes, comprised of a mask of zero or
				                                           *   more USB_CONFIG_ATTR_* masks.
				                                           */
				
				uint8_t                 MaxPowerConsumption; /**< Maximum power consumption of the device while in the
				                                              *   current configuration, calculated by the USB_CONFIG_POWER_MA()
				                                              *   macro.
				                                              */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				uint16_t                wTotalLength;
				uint8_t                 bNumInterfaces;
				uint8_t                 bConfigurationValue;
				uint8_t                 iConfiguration;
				uint8_t                 bmAttributes;
				uint8_t                 bMaxPower;
				#endif
			} USB_Descriptor_Configuration_Header_t;

			/** Type define for a standard interface descriptor.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t                 InterfaceNumber; /**< Index of the interface in the current configuration. */
				uint8_t                 AlternateSetting; /**< Alternate setting for the interface number. The same
				                                           *   interface number can have multiple alternate settings
				                                           *   with different endpoint configurations, which can be
				                                           *   selected by the host.
				                                           */
				uint8_t                 TotalEndpoints; /**< Total number of endpoints in the interface. */
				
				uint8_t                 Class; /**< Interface class ID. */
				uint8_t                 SubClass; /**< Interface subclass ID. */
				uint8_t                 Protocol; /**< Interface protocol ID. */

				uint8_t                 InterfaceStrIndex; /**< Index of the string descriptor describing the
				                                            *   interface.
				                                            */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				uint8_t                 bInterfaceNumber;
				uint8_t                 bAlternateSetting;
				uint8_t                 bNumEndpoints;
				uint8_t                 bInterfaceClass;
				uint8_t                 bInterfaceSubClass;
				uint8_t                 bInterfaceProtocol;
				uint8_t                 iInterface;
				#endif
			} USB_Descriptor_Interface_t;

			/** Type define for a standard interface association descriptor.
			 *
			 *  This descriptor has been added as a supplement to the USB2.0 standard, in the ECN located at
			 *  <a>http://www.usb.org/developers/docs/InterfaceAssociationDescriptor_ecn.pdf</a>. It allows compound
			 *  devices with multiple interfaces related to the same function to have the multiple interfaces bound
			 *  together at the point of enumeration, loading one generic driver for all the interfaces in the single
			 *  function. Read the ECN for more information.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
				
				uint8_t                 FirstInterfaceIndex; /**< Index of the first associated interface. */
				uint8_t                 TotalInterfaces; /** Total number of associated interfaces. */

				uint8_t                 Class; /**< Interface class ID. */
				uint8_t                 SubClass; /**< Interface subclass ID. */
				uint8_t                 Protocol; /**< Interface protocol ID. */

				uint8_t                 IADStrIndex; /**< Index of the string descriptor describing the
				                                      *   interface association.
				                                      */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				uint8_t                 bFirstInterface;
				uint8_t                 bInterfaceCount;
				uint8_t                 bFunctionClass;
				uint8_t                 bFunctionSubClass;
				uint8_t                 bFunctionProtocol;
				uint8_t                 iFunction;
				#endif
			} USB_Descriptor_Interface_Association_t;

			/** Type define for a standard endpoint descriptor.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			*/
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t                 EndpointAddress; /**< Logical address of the endpoint within the device
				                                          *   for the current configuration, including direction
				                                          *   mask.
				                                          */
				uint8_t                 Attributes; /**< Endpoint attributes, comprised of a mask of the
				                                     *   endpoint type (EP_TYPE_*) and attributes (ENDPOINT_ATTR_*)
				                                     *   masks.
				                                     */
				uint16_t                EndpointSize; /**< Size of the endpoint bank, in bytes. This indicates the
				                                       *   maximum packet size that the endpoint can receive at a time.
				                                       */
				
				uint8_t                 PollingIntervalMS; /**< Polling interval in milliseconds for the endpoint
				                                            *   if it is an INTERRUPT or ISOCHRONOUS type.
				                                            */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				uint8_t                 bEndpointAddress;
				uint8_t                 bmAttributes;
				uint16_t                wMaxPacketSize;
				uint8_t                 bInterval;
				#endif
			} USB_Descriptor_Endpoint_t;

			/** Type define for a standard string descriptor. Unlike other standard descriptors, the length
			 *  of the descriptor for placement in the descriptor header must be determined by the USB_STRING_LEN()
			 *  macro rather than by the size of the descriptor structure, as the length is not fixed.
			 *
			 *  This structure should also be used for string index 0, which contains the supported language IDs for
			 *  the device as an array.
			 *
			 *  \note The non-standard structure element names are documented here - see the StdDescriptors.h file
			 *        documentation for more information on the two descriptor naming schemes. If the
			 *        USE_NONSTANDARD_DESCRIPTOR_NAMES token is not set, this structure contains elements with names
			 *        identical to those listed in the USB standard.
			 */
			typedef struct
			{
				#if defined(USE_NONSTANDARD_DESCRIPTOR_NAMES) || defined(__DOXYGEN__)
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
				
				int16_t                 UnicodeString[]; /**< String data, as unicode characters (alternatively,
				                                          *   string language IDs). If normal ASCII characters are
				                                          *   to be used, they must be added as an array of characters
				                                          *   rather than a normal C string so that they are widened to
				                                          *   Unicode size.
				                                          *
				                                          *   Under GCC, strings prefixed with the "L" character (before
				                                          *   the opening string quotation mark) are considered to be
				                                          *   Unicode strings, and may be used instead of an explicit
				                                          *   array of ASCII characters.
				                                          */
				#else
				uint8_t                 bLength;
				uint8_t                 bDescriptorType;
				int16_t                 bString[];
				#endif
			} USB_Descriptor_String_t;

		/* Function Prototypes: */
			/** Function to retrieve a given descriptor's size and memory location from the given descriptor type value,
			 *  index and language ID. This function MUST be overridden in the user application (added with full, identical  
			 *  prototype and name except for the ATTR_WEAK attribute) so that the library can call it to retrieve descriptor 
			 *  data.
			 *
			 *  \param wValue             The type of the descriptor to retrieve in the upper byte, and the index in the 
			 *                            lower byte (when more than one descriptor of the given type exists, such as the
			 *                            case of string descriptors). The type may be one of the standard types defined
			 *                            in the DescriptorTypes_t enum, or may be a class-specific descriptor type value.
			 *  \param wIndex             The language ID of the string to return if the wValue type indicates DTYPE_String,
			 *                            otherwise zero for standard descriptors, or as defined in a class-specific
			 *                            standards.
			 *  \param DescriptorAddress  Pointer to the descriptor in memory. This should be set by the routine to
			 *                            the location of the descriptor, found by the DESCRIPTOR_ADDRESS macro.
			 *
			 *  \note By default, the library expects all descriptors to be located in flash memory via the PROGMEM attribute.
			 *        If descriptors should be located in RAM or EEPROM instead (to speed up access in the case of RAM, or to
			 *        allow the descriptors to be changed dynamically at runtime) either the USE_RAM_DESCRIPTORS or the 
			 *        USE_EEPROM_DESCRIPTORS tokens may be defined in the project makefile and passed to the compiler by the -D
			 *        switch.
			 *
			 *  \return Size in bytes of the descriptor if it exists, zero or NO_DESCRIPTOR otherwise
			 */
			uint16_t USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
									   ATTR_WARN_UNUSED_RESULT ATTR_WEAK ATTR_NON_NULL_PTR_ARG(3);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define VERSION_TENS(x)                   (int)(x / 10)
			#define VERSION_ONES(x)                   (int)(x - (10 * VERSION_TENS(x)))
			#define VERSION_TENTHS(x)                 (int)((x - (int)x) * 10)
			#define VERSION_HUNDREDTHS(x)             (int)(((x - (int)x) * 100) - (10 * VERSION_TENTHS(x)))
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
