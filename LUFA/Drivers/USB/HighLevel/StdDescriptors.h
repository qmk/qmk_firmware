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

/** \ingroup Group_USB
 *  @defgroup Group_Descriptors USB Descriptors
 *
 *  Standard USB device descriptor defines and retrieval routines, for USB devices. This module contains
 *  structures and macros for the easy creation of standard USB descriptors in USB device projects.
 *
 *  @{
 */
 
#ifndef __USBDESCRIPTORS_H__
#define __USBDESCRIPTORS_H__

	/* Includes: */
		#include <avr/pgmspace.h>
		#include <stdbool.h>
		#include <stddef.h>

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

			#if (!defined(NO_INTERNAL_SERIAL) && (defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))) || defined(__DOXYGEN__)
				/** String descriptor index for the device's unique serial number string descriptor within the device.
				 *  This unique serial number is used by the host to associate resources to the device (such as drivers or COM port
				 *  number allocations) to a device regardless of the port it is plugged in to on the host. Some USB AVRs contain
				 *  a unique serial number internally, and setting the device descriptors serial number string index to this value
				 *  will cause it to use the internal serial number.
				 *
				 *  On unsupported devices, this will evaluate to NO_DESCRIPTOR and so will force the host to create a pseudo-serial
				 *  number for the device.
				 */
				#define USE_INTERNAL_SERIAL           0xDC
			#else
				#define USE_INTERNAL_SERIAL           NO_DESCRIPTOR
			#endif
			
			/** Macro to calculate the power value for the device descriptor, from a given number of milliamps. */
			#define USB_CONFIG_POWER_MA(mA)           (mA >> 1)

			/** Macro to calculate the Unicode length of a string with a given number of Unicode characters.
			 *  Should be used in string descriptor's headers for giving the string descriptor's byte length.
			 */
			#define USB_STRING_LEN(str)               (sizeof(USB_Descriptor_Header_t) + (str << 1))
			
			/** Macro to encode a given four digit floating point version number (e.g. 01.23) into Binary Coded
			 *  Decimal format for descriptor fields requiring BCD encoding, such as the USB version number in the
			 *  standard device descriptor.
			 */
			#define VERSION_BCD(x)                    ((((VERSION_TENS(x) << 4) | VERSION_ONES(x)) << 8) | \
			                                          ((VERSION_TENTHS(x) << 4) | VERSION_HUNDREDTHS(x)))

			/** String language ID for the English language. Should be used in \ref USB_Descriptor_String_t descriptors
			 *  to indicate that the English language is supported by the device in its string descriptors.
			 */
			#define LANGUAGE_ID_ENG                   0x0409

			/** Can be masked with an endpoint address for a \ref USB_Descriptor_Endpoint_t endpoint descriptor's
			 *  EndpointAddress value to indicate to the host that the endpoint is of the IN direction (i.e, from
			 *  device to host).
			 */
			#define ENDPOINT_DESCRIPTOR_DIR_IN        0x80

			/** Can be masked with an endpoint address for a \ref USB_Descriptor_Endpoint_t endpoint descriptor's
			 *  EndpointAddress value to indicate to the host that the endpoint is of the OUT direction (i.e, from
			 *  host to device).
			 */
			#define ENDPOINT_DESCRIPTOR_DIR_OUT       0x00		

			/** Can be masked with other configuration descriptor attributes for a \ref USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration can draw its power
			 *  from the host's VBUS line.
			 */
			#define USB_CONFIG_ATTR_BUSPOWERED        0x80

			/** Can be masked with other configuration descriptor attributes for a \ref USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration can draw its power
			 *  from the device's own power source.
			 */
			#define USB_CONFIG_ATTR_SELFPOWERED       0xC0

			/** Can be masked with other configuration descriptor attributes for a \ref USB_Descriptor_Configuration_Header_t
			 *  descriptor's ConfigAttributes value to indicate that the specified configuration supports the
			 *  remote wakeup feature of the USB standard, allowing a suspended USB device to wake up the host upon
			 *  request.
			 */
			#define USB_CONFIG_ATTR_REMOTEWAKEUP      0xA0

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is not synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_NO_SYNC             (0 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is asynchronous.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ASYNC               (1 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is adaptive.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ADAPTIVE            (2 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_SYNC                (3 << 2)
			
			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for data transfers.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_DATA               (0 << 4)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_FEEDBACK           (1 << 4)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  Attributes value to indicate that the specified endpoint is used for implicit feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_IMPLICIT_FEEDBACK  (2 << 4)

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
			/** Type define for all descriptors standard header, indicating the descriptor's length and type. This structure
			 *  uses LUFA-specific element names to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Header_t for the version of this define with standard element names
			 */
			typedef struct
			{
				uint8_t     Size; /**< Size of the descriptor, in bytes. */
				uint8_t     Type; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                   *   given by the specific class.
				                   */
			} USB_Descriptor_Header_t;
			
			/** Type define for all descriptors standard header, indicating the descriptor's length and type. This structure
			 *  uses the relevant standard's given element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Header_t for the version of this define with non-standard LUFA specific element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
			} USB_StdDescriptor_Header_t;
			
			/** Type define for a standard Device Descriptor. This structure uses LUFA-specific element names to make each
			 *  element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Device_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint16_t    USBSpecification; /**< BCD of the supported USB specification. */
				uint8_t     Class; /**< USB device class. */
				uint8_t     SubClass; /**< USB device subclass. */
				uint8_t     Protocol; /**< USB device protocol. */
				
				uint8_t     Endpoint0Size; /**< Size of the control (address 0) endpoint's bank in bytes. */
				
				uint16_t    VendorID; /**< Vendor ID for the USB product. */
				uint16_t    ProductID; /**< Unique product ID for the USB product. */
				uint16_t    ReleaseNumber; /**< Product release (version) number. */
				
				uint8_t     ManufacturerStrIndex; /**< String index for the manufacturer's name. The
				                                   *   host will request this string via a separate
				                                   *   control request for the string descriptor.
				                                   *
				                                   *   \note If no string supplied, use \ref NO_DESCRIPTOR.
				                                   */
				uint8_t     ProductStrIndex; /**< String index for the product name/details.
				                              *
				                              *  \see ManufacturerStrIndex structure entry.
				                              */
				uint8_t     SerialNumStrIndex; /**< String index for the product's globally unique hexadecimal
				                                *   serial number, in uppercase Unicode ASCII.
				                                *
				                                *  \note On some AVR models, there is an embedded serial number
				                                *        in the chip which can be used for the device serial number.
				                                *        To use this serial number, set this to USE_INTERNAL_SERIAL.
				                                *        On unsupported devices, this will evaluate to 0 and will cause
				                                *        the host to generate a pseudo-unique value for the device upon
				                                *        insertion.
				                                *
				                                *  \see ManufacturerStrIndex structure entry.
				                                */
				uint8_t     NumberOfConfigurations; /**< Total number of configurations supported by
				                                     *   the device.
				                                     */
			} USB_Descriptor_Device_t;

			/** Type define for a standard Device Descriptor. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Device_t for the version of this define with non-standard LUFA specific element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint16_t    bcdUSB; /**< BCD of the supported USB specification. */
				uint8_t     bDeviceClass; /**< USB device class. */
				uint8_t     bDeviceSubClass; /**< USB device subclass. */
				uint8_t     bDeviceProtocol; /**< USB device protocol. */
				uint8_t     bMaxPacketSize0; /**< Size of the control (address 0) endpoint's bank in bytes. */
				uint16_t    idVendor; /**< Vendor ID for the USB product. */
				uint16_t    idProduct; /**< Unique product ID for the USB product. */
				uint16_t    bcdDevice; /**< Product release (version) number. */
				uint8_t     iManufacturer; /**< String index for the manufacturer's name. The
				                            *   host will request this string via a separate
				                            *   control request for the string descriptor.
				                            *
				                            *   \note If no string supplied, use \ref NO_DESCRIPTOR.
				                            */
				uint8_t     iProduct; /**< String index for the product name/details.
				                       *
				                       *  \see ManufacturerStrIndex structure entry.
				                       */
				uint8_t     iSerialNumber; /**< String index for the product's globally unique hexadecimal
				                            *   serial number, in uppercase Unicode ASCII.
				                            *
				                            *  \note On some AVR models, there is an embedded serial number
				                            *        in the chip which can be used for the device serial number.
				                            *        To use this serial number, set this to USE_INTERNAL_SERIAL.
				                            *        On unsupported devices, this will evaluate to 0 and will cause
				                            *        the host to generate a pseudo-unique value for the device upon
				                            *        insertion.
				                            *
				                            *  \see ManufacturerStrIndex structure entry.
				                             */
				uint8_t     bNumConfigurations; /**< Total number of configurations supported by
				                                 *   the device.
				                                 */
			} USB_StdDescriptor_Device_t;

			/** Type define for a standard Configuration Descriptor header. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Configuration_Header_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
			
				uint16_t    TotalConfigurationSize; /**< Size of the configuration descriptor header,
				                                     *   and all sub descriptors inside the configuration.
				                                     */
				uint8_t     TotalInterfaces; /**< Total number of interfaces in the configuration. */

				uint8_t     ConfigurationNumber; /**< Configuration index of the current configuration. */
				uint8_t     ConfigurationStrIndex; /**< Index of a string descriptor describing the configuration. */
				
				uint8_t     ConfigAttributes; /**< Configuration attributes, comprised of a mask of zero or
				                               *   more USB_CONFIG_ATTR_* masks.
				                               */
				
				uint8_t     MaxPowerConsumption; /**< Maximum power consumption of the device while in the
				                                  *   current configuration, calculated by the \ref USB_CONFIG_POWER_MA()
				                                  *   macro.
				                                  */
			} USB_Descriptor_Configuration_Header_t;
			
			/** Type define for a standard Configuration Descriptor header. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Device_t for the version of this define with non-standard LUFA specific element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint16_t    wTotalLength; /**< Size of the configuration descriptor header,
				                           *   and all sub descriptors inside the configuration.
				                           */
				uint8_t     bNumInterfaces; /**< Total number of interfaces in the configuration. */
				uint8_t     bConfigurationValue; /**< Configuration index of the current configuration. */
				uint8_t     iConfiguration; /**< Index of a string descriptor describing the configuration. */
				uint8_t     bmAttributes; /**< Configuration attributes, comprised of a mask of zero or
				                           *   more USB_CONFIG_ATTR_* masks.
				                           */
				uint8_t     bMaxPower; /**< Maximum power consumption of the device while in the
				                        *   current configuration, calculated by the \ref USB_CONFIG_POWER_MA()
				                        *   macro.
				                        */
			} USB_StdDescriptor_Configuration_Header_t;

			/** Type define for a standard Interface Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Interface_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t     InterfaceNumber; /**< Index of the interface in the current configuration. */
				uint8_t     AlternateSetting; /**< Alternate setting for the interface number. The same
				                               *   interface number can have multiple alternate settings
				                               *   with different endpoint configurations, which can be
				                               *   selected by the host.
				                               */
				uint8_t     TotalEndpoints; /**< Total number of endpoints in the interface. */
				
				uint8_t     Class; /**< Interface class ID. */
				uint8_t     SubClass; /**< Interface subclass ID. */
				uint8_t     Protocol; /**< Interface protocol ID. */

				uint8_t     InterfaceStrIndex; /**< Index of the string descriptor describing the
				                                *   interface.
				                                */
			} USB_Descriptor_Interface_t;
			
			/** Type define for a standard Interface Descriptor. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Interface_t for the version of this define with non-standard LUFA specific element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint8_t     bInterfaceNumber; /**< Index of the interface in the current configuration. */
				uint8_t     bAlternateSetting; /**< Alternate setting for the interface number. The same
				                                *   interface number can have multiple alternate settings
				                                *   with different endpoint configurations, which can be
				                                *   selected by the host.
				                                */
				uint8_t     bNumEndpoints; /**< Total number of endpoints in the interface. */
				uint8_t     bInterfaceClass; /**< Interface class ID. */
				uint8_t     bInterfaceSubClass; /**< Interface subclass ID. */
				uint8_t     bInterfaceProtocol; /**< Interface protocol ID. */
				uint8_t     iInterface; /**< Index of the string descriptor describing the
				                         *   interface.
				                         */
			} USB_StdDescriptor_Interface_t;

			/** Type define for a standard Interface Association Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  This descriptor has been added as a supplement to the USB2.0 standard, in the ECN located at
			 *  <a>http://www.usb.org/developers/docs/InterfaceAssociationDescriptor_ecn.pdf</a>. It allows compound
			 *  devices with multiple interfaces related to the same function to have the multiple interfaces bound
			 *  together at the point of enumeration, loading one generic driver for all the interfaces in the single
			 *  function. Read the ECN for more information.
			 *
			 *  \see \ref USB_StdDescriptor_Interface_Association_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
				
				uint8_t     FirstInterfaceIndex; /**< Index of the first associated interface. */
				uint8_t     TotalInterfaces; /** Total number of associated interfaces. */

				uint8_t     Class; /**< Interface class ID. */
				uint8_t     SubClass; /**< Interface subclass ID. */
				uint8_t     Protocol; /**< Interface protocol ID. */

				uint8_t     IADStrIndex; /**< Index of the string descriptor describing the
				                          *   interface association.
				                          */
			} USB_Descriptor_Interface_Association_t;
				
			/** Type define for a standard Interface Association Descriptor. This structure uses the relevant standard's given
			 *  element names to ensure compatibility with the standard.
			 *
			 *  This descriptor has been added as a supplement to the USB2.0 standard, in the ECN located at
			 *  <a>http://www.usb.org/developers/docs/InterfaceAssociationDescriptor_ecn.pdf</a>. It allows compound
			 *  devices with multiple interfaces related to the same function to have the multiple interfaces bound
			 *  together at the point of enumeration, loading one generic driver for all the interfaces in the single
			 *  function. Read the ECN for more information.
			 *
			 *  \see \ref USB_Descriptor_Interface_Association_t for the version of this define with non-standard LUFA specific
			 *       element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint8_t     bFirstInterface; /**< Index of the first associated interface. */
				uint8_t     bInterfaceCount; /** Total number of associated interfaces. */
				uint8_t     bFunctionClass; /**< Interface class ID. */
				uint8_t     bFunctionSubClass; /**< Interface subclass ID. */
				uint8_t     bFunctionProtocol; /**< Interface protocol ID. */
				uint8_t     iFunction; /**< Index of the string descriptor describing the
				                        *   interface association.
				                        */
			} USB_StdDescriptor_Interface_Association_t;

			/** Type define for a standard Endpoint Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Endpoint_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t     EndpointAddress; /**< Logical address of the endpoint within the device
				                              *   for the current configuration, including direction
				                              *   mask.
				                              */
				uint8_t     Attributes; /**< Endpoint attributes, comprised of a mask of the
				                         *   endpoint type (EP_TYPE_*) and attributes (ENDPOINT_ATTR_*)
				                         *   masks.
				                         */
				uint16_t    EndpointSize; /**< Size of the endpoint bank, in bytes. This indicates the
				                           *   maximum packet size that the endpoint can receive at a time.
				                           */
				
				uint8_t     PollingIntervalMS; /**< Polling interval in milliseconds for the endpoint
				                                *   if it is an INTERRUPT or ISOCHRONOUS type.
				                                */
			} USB_Descriptor_Endpoint_t;
				
			/** Type define for a standard Endpoint Descriptor. This structure uses the relevant standard's given
			 *  element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Endpoint_t for the version of this define with non-standard LUFA specific
			 *       element names
			 */
			typedef struct
			{
				uint8_t     bLength; /**< Size of the descriptor, in bytes. */
				uint8_t     bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint8_t     bEndpointAddress; /**< Logical address of the endpoint within the device
				                               *   for the current configuration, including direction
				                               *   mask.
				                               */
				uint8_t     bmAttributes; /**< Endpoint attributes, comprised of a mask of the
				                           *   endpoint type (EP_TYPE_*) and attributes (ENDPOINT_ATTR_*)
				                           *   masks.
				                           */
				uint16_t    wMaxPacketSize; /**< Size of the endpoint bank, in bytes. This indicates the
				                             *   maximum packet size that the endpoint can receive at a time.
				                             */
				uint8_t     bInterval; /**< Polling interval in milliseconds for the endpoint
				                        *   if it is an INTERRUPT or ISOCHRONOUS type.
				                        */
			} USB_StdDescriptor_Endpoint_t;

			/** Type define for a standard string descriptor. Unlike other standard descriptors, the length
			 *  of the descriptor for placement in the descriptor header must be determined by the \ref USB_STRING_LEN()
			 *  macro rather than by the size of the descriptor structure, as the length is not fixed.
			 *
			 *  This structure should also be used for string index 0, which contains the supported language IDs for
			 *  the device as an array.
			 *
			 *  This structure uses LUFA-specific element names to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_String_t for the version of this define with standard element names
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
				
				wchar_t UnicodeString[];  /**< String data, as unicode characters (alternatively,
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
			} USB_Descriptor_String_t;

			/** Type define for a standard string descriptor. Unlike other standard descriptors, the length
			 *  of the descriptor for placement in the descriptor header must be determined by the \ref USB_STRING_LEN()
			 *  macro rather than by the size of the descriptor structure, as the length is not fixed.
			 *
			 *  This structure should also be used for string index 0, which contains the supported language IDs for
			 *  the device as an array.
			 *
			 *  This structure uses the relevant standard's given element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_String_t for the version of this define with with non-standard LUFA specific
			 *       element names
			 */
			typedef struct
			{
					uint8_t                 bLength; /**< Size of the descriptor, in bytes. */
					uint8_t                 bDescriptorType; /**< Type of the descriptor, either a value in
					                                          *   \ref USB_DescriptorTypes_t or a value
				                                              *   given by the specific class.
				                                              */
					int16_t                 bString[]; /**< String data, as unicode characters (alternatively,
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
			} USB_StdDescriptor_String_t;

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
