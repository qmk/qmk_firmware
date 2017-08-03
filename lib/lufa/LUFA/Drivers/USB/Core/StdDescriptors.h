/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common standard USB Descriptor definitions for all architectures.
 *  \copydetails Group_StdDescriptors
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USB
 *  \defgroup Group_StdDescriptors USB Descriptors
 *  \brief Standard USB Descriptor definitions.
 *
 *  Standard USB device descriptor defines and retrieval routines, for USB devices. This module contains
 *  structures and macros for the easy creation of standard USB descriptors in USB device projects.
 *
 *  @{
 */

#ifndef __USBDESCRIPTORS_H__
#define __USBDESCRIPTORS_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"
		#include "Events.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Indicates that a given descriptor does not exist in the device. This can be used inside descriptors
			 *  for string descriptor indexes, or may be use as a return value for GetDescriptor when the specified
			 *  descriptor does not exist.
			 */
			#define NO_DESCRIPTOR                     0

			/** Macro to calculate the power value for the configuration descriptor, from a given number of milliamperes.
			 *
			 *  \param[in] mA  Maximum number of milliamps the device consumes when the given configuration is selected.
			 */
			#define USB_CONFIG_POWER_MA(mA)           ((mA) >> 1)

			/** Macro to calculate the Unicode length of a string with a given number of Unicode characters.
			 *  Should be used in string descriptor's headers for giving the string descriptor's byte length.
			 *
			 *  \param[in] UnicodeChars  Number of Unicode characters in the string text.
			 */
			#define USB_STRING_LEN(UnicodeChars)      (sizeof(USB_Descriptor_Header_t) + ((UnicodeChars) << 1))

			/** Convenience macro to easily create \ref USB_Descriptor_String_t instances from a wide character string.
			 *
			 *  \note This macro is for little-endian systems only.
			 *
			 *  \param[in] String  String to initialize a USB String Descriptor structure with.
			 */
			#define USB_STRING_DESCRIPTOR(String)     { .Header = {.Size = sizeof(USB_Descriptor_Header_t) + (sizeof(String) - 2), .Type = DTYPE_String}, .UnicodeString = String }

			/** Convenience macro to easily create \ref USB_Descriptor_String_t instances from an array of characters.
			 *
			 *  \param[in] ...  Characters to initialize a USB String Descriptor structure with.
			 */
			#define USB_STRING_DESCRIPTOR_ARRAY(...)  { .Header = {.Size = sizeof(USB_Descriptor_Header_t) + sizeof((uint16_t){__VA_ARGS__}), .Type = DTYPE_String}, .UnicodeString = {__VA_ARGS__} }

			/** Macro to encode a given major/minor/revision version number into Binary Coded Decimal format for descriptor
			 *  fields requiring BCD encoding, such as the USB version number in the standard device descriptor.
			 *
			 *  \note This value is automatically converted into Little Endian, suitable for direct use inside device
			 *        descriptors on all architectures without endianness conversion macros.
			 *
			 *  \param[in]  Major     Major version number to encode.
			 *  \param[in]  Minor     Minor version number to encode.
			 *  \param[in]  Revision  Revision version number to encode.
			 */
			#define VERSION_BCD(Major, Minor, Revision) \
			                                          CPU_TO_LE16( ((Major & 0xFF) << 8) | \
			                                                       ((Minor & 0x0F) << 4) | \
			                                                       (Revision & 0x0F) )

			/** String language ID for the English language. Should be used in \ref USB_Descriptor_String_t descriptors
			 *  to indicate that the English language is supported by the device in its string descriptors.
			 */
			#define LANGUAGE_ID_ENG                   0x0409

			/** \name USB Configuration Descriptor Attribute Masks */
			//@{
			/** Mask for the reserved bit in the Configuration Descriptor's \c ConfigAttributes field, which must be set on all
			 *  devices for historical purposes.
			 */
			#define USB_CONFIG_ATTR_RESERVED          0x80

			/** Can be masked with other configuration descriptor attributes for a \ref USB_Descriptor_Configuration_Header_t
			 *  descriptor's \c ConfigAttributes value to indicate that the specified configuration can draw its power
			 *  from the device's own power source.
			 */
			#define USB_CONFIG_ATTR_SELFPOWERED       0x40

			/** Can be masked with other configuration descriptor attributes for a \ref USB_Descriptor_Configuration_Header_t
			 *  descriptor's \c ConfigAttributes value to indicate that the specified configuration supports the
			 *  remote wakeup feature of the USB standard, allowing a suspended USB device to wake up the host upon
			 *  request.
			 */
			#define USB_CONFIG_ATTR_REMOTEWAKEUP      0x20
			//@}

			/** \name Endpoint Descriptor Attribute Masks */
			//@{
			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is not synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_NO_SYNC             (0 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is asynchronous.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ASYNC               (1 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is adaptive.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_ADAPTIVE            (2 << 2)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is synchronized.
			 *
			 *  \see The USB specification for more details on the possible Endpoint attributes.
			 */
			#define ENDPOINT_ATTR_SYNC                (3 << 2)
			//@}

			/** \name Endpoint Descriptor Usage Masks */
			//@{
			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is used for data transfers.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_DATA               (0 << 4)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is used for feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_FEEDBACK           (1 << 4)

			/** Can be masked with other endpoint descriptor attributes for a \ref USB_Descriptor_Endpoint_t descriptor's
			 *  \c Attributes value to indicate that the specified endpoint is used for implicit feedback.
			 *
			 *  \see The USB specification for more details on the possible Endpoint usage attributes.
			 */
			#define ENDPOINT_USAGE_IMPLICIT_FEEDBACK  (2 << 4)
			//@}

		/* Enums: */
			/** Enum for the possible standard descriptor types, as given in each descriptor's header. */
			enum USB_DescriptorTypes_t
			{
				DTYPE_Device                    = 0x01, /**< Indicates that the descriptor is a device descriptor. */
				DTYPE_Configuration             = 0x02, /**< Indicates that the descriptor is a configuration descriptor. */
				DTYPE_String                    = 0x03, /**< Indicates that the descriptor is a string descriptor. */
				DTYPE_Interface                 = 0x04, /**< Indicates that the descriptor is an interface descriptor. */
				DTYPE_Endpoint                  = 0x05, /**< Indicates that the descriptor is an endpoint descriptor. */
				DTYPE_DeviceQualifier           = 0x06, /**< Indicates that the descriptor is a device qualifier descriptor. */
				DTYPE_Other                     = 0x07, /**< Indicates that the descriptor is of other type. */
				DTYPE_InterfacePower            = 0x08, /**< Indicates that the descriptor is an interface power descriptor. */
				DTYPE_InterfaceAssociation      = 0x0B, /**< Indicates that the descriptor is an interface association descriptor. */
				DTYPE_CSInterface               = 0x24, /**< Indicates that the descriptor is a class specific interface descriptor. */
				DTYPE_CSEndpoint                = 0x25, /**< Indicates that the descriptor is a class specific endpoint descriptor. */
			};

			/** Enum for possible Class, Subclass and Protocol values of device and interface descriptors. */
			enum USB_Descriptor_ClassSubclassProtocol_t
			{
				USB_CSCP_NoDeviceClass          = 0x00, /**< Descriptor Class value indicating that the device does not belong
				                                         *   to a particular class at the device level.
				                                         */
				USB_CSCP_NoDeviceSubclass       = 0x00, /**< Descriptor Subclass value indicating that the device does not belong
				                                         *   to a particular subclass at the device level.
				                                         */
				USB_CSCP_NoDeviceProtocol       = 0x00, /**< Descriptor Protocol value indicating that the device does not belong
				                                         *   to a particular protocol at the device level.
				                                         */
				USB_CSCP_VendorSpecificClass    = 0xFF, /**< Descriptor Class value indicating that the device/interface belongs
				                                         *   to a vendor specific class.
				                                         */
				USB_CSCP_VendorSpecificSubclass = 0xFF, /**< Descriptor Subclass value indicating that the device/interface belongs
				                                         *   to a vendor specific subclass.
				                                         */
				USB_CSCP_VendorSpecificProtocol = 0xFF, /**< Descriptor Protocol value indicating that the device/interface belongs
				                                         *   to a vendor specific protocol.
				                                         */
				USB_CSCP_IADDeviceClass         = 0xEF, /**< Descriptor Class value indicating that the device belongs to the
				                                         *   Interface Association Descriptor class.
				                                         */
				USB_CSCP_IADDeviceSubclass      = 0x02, /**< Descriptor Subclass value indicating that the device belongs to the
				                                         *   Interface Association Descriptor subclass.
				                                         */
				USB_CSCP_IADDeviceProtocol      = 0x01, /**< Descriptor Protocol value indicating that the device belongs to the
				                                         *   Interface Association Descriptor protocol.
				                                         */
			};

		/* Type Defines: */
			/** \brief Standard USB Descriptor Header (LUFA naming conventions).
			 *
             *  Type define for all descriptors' standard header, indicating the descriptor's length and type. This structure
			 *  uses LUFA-specific element names to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Header_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t Size; /**< Size of the descriptor, in bytes. */
				uint8_t Type; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				               *   given by the specific class.
				               */
			} ATTR_PACKED USB_Descriptor_Header_t;

			/** \brief Standard USB Descriptor Header (USB-IF naming conventions).
			 *
			 *  Type define for all descriptors' standard header, indicating the descriptor's length and type. This structure
			 *  uses the relevant standard's given element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Header_t for the version of this type with non-standard LUFA specific element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t bLength; /**< Size of the descriptor, in bytes. */
				uint8_t bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                          *   given by the specific class.
				                          */
			} ATTR_PACKED USB_StdDescriptor_Header_t;

			/** \brief Standard USB Device Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Device Descriptor. This structure uses LUFA-specific element names to make each
			 *  element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Device_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint16_t USBSpecification; /**< BCD of the supported USB specification.
				                            *
				                            *   \see \ref VERSION_BCD() utility macro.
				                            */
				uint8_t  Class; /**< USB device class. */
				uint8_t  SubClass; /**< USB device subclass. */
				uint8_t  Protocol; /**< USB device protocol. */

				uint8_t  Endpoint0Size; /**< Size of the control (address 0) endpoint's bank in bytes. */

				uint16_t VendorID; /**< Vendor ID for the USB product. */
				uint16_t ProductID; /**< Unique product ID for the USB product. */
				uint16_t ReleaseNumber; /**< Product release (version) number.
				                         *
				                         *   \see \ref VERSION_BCD() utility macro.
				                         */
				uint8_t  ManufacturerStrIndex; /**< String index for the manufacturer's name. The
				                                *   host will request this string via a separate
				                                *   control request for the string descriptor.
				                                *
				                                *   \note If no string supplied, use \ref NO_DESCRIPTOR.
				                                */
				uint8_t  ProductStrIndex; /**< String index for the product name/details.
				                           *
				                           *  \see ManufacturerStrIndex structure entry.
				                           */
				uint8_t  SerialNumStrIndex; /**< String index for the product's globally unique hexadecimal
				                             *   serial number, in uppercase Unicode ASCII.
				                             *
				                             *  \note On some microcontroller models, there is an embedded serial number
				                             *        in the chip which can be used for the device serial number.
				                             *        To use this serial number, set this to \c USE_INTERNAL_SERIAL.
				                             *        On unsupported devices, this will evaluate to \ref NO_DESCRIPTOR
				                             *        and will cause the host to generate a pseudo-unique value for the
				                             *        device upon insertion.
				                             *
				                             *  \see \c ManufacturerStrIndex structure entry.
				                             */
				uint8_t  NumberOfConfigurations; /**< Total number of configurations supported by
				                                  *   the device.
				                                  */
			} ATTR_PACKED USB_Descriptor_Device_t;

			/** \brief Standard USB Device Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Device Descriptor. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Device_t for the version of this type with non-standard LUFA specific element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t  bLength; /**< Size of the descriptor, in bytes. */
				uint8_t  bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                              *   given by the specific class.
				                              */
				uint16_t bcdUSB; /**< BCD of the supported USB specification.
				                  *
				                  *   \see \ref VERSION_BCD() utility macro.
				                  */
				uint8_t  bDeviceClass; /**< USB device class. */
				uint8_t  bDeviceSubClass; /**< USB device subclass. */
				uint8_t  bDeviceProtocol; /**< USB device protocol. */
				uint8_t  bMaxPacketSize0; /**< Size of the control (address 0) endpoint's bank in bytes. */
				uint16_t idVendor; /**< Vendor ID for the USB product. */
				uint16_t idProduct; /**< Unique product ID for the USB product. */
				uint16_t bcdDevice; /**< Product release (version) number.
				                     *
				                     *   \see \ref VERSION_BCD() utility macro.
				                     */
				uint8_t  iManufacturer; /**< String index for the manufacturer's name. The
				                         *   host will request this string via a separate
				                         *   control request for the string descriptor.
				                         *
				                         *   \note If no string supplied, use \ref NO_DESCRIPTOR.
				                         */
				uint8_t  iProduct; /**< String index for the product name/details.
				                    *
				                    *  \see ManufacturerStrIndex structure entry.
				                    */
				uint8_t iSerialNumber; /**< String index for the product's globally unique hexadecimal
				                        *   serial number, in uppercase Unicode ASCII.
				                        *
				                        *  \note On some microcontroller models, there is an embedded serial number
				                        *        in the chip which can be used for the device serial number.
				                        *        To use this serial number, set this to \c USE_INTERNAL_SERIAL.
				                        *        On unsupported devices, this will evaluate to \ref NO_DESCRIPTOR
				                        *        and will cause the host to generate a pseudo-unique value for the
				                        *        device upon insertion.
				                        *
				                        *  \see \c ManufacturerStrIndex structure entry.
				                        */
				uint8_t  bNumConfigurations; /**< Total number of configurations supported by
				                              *   the device.
				                              */
			} ATTR_PACKED USB_StdDescriptor_Device_t;

			/** \brief Standard USB Device Qualifier Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Device Qualifier Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_DeviceQualifier_t for the version of this type with standard element names.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint16_t USBSpecification; /**< BCD of the supported USB specification.
				                            *
				                            *   \see \ref VERSION_BCD() utility macro.
				                            */
				uint8_t  Class; /**< USB device class. */
				uint8_t  SubClass; /**< USB device subclass. */
				uint8_t  Protocol; /**< USB device protocol. */

				uint8_t  Endpoint0Size; /**< Size of the control (address 0) endpoint's bank in bytes. */
				uint8_t  NumberOfConfigurations; /**< Total number of configurations supported by
				                                  *   the device.
				                                  */
				uint8_t  Reserved; /**< Reserved for future use, must be 0. */
			} ATTR_PACKED USB_Descriptor_DeviceQualifier_t;

			/** \brief Standard USB Device Qualifier Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Device Qualifier Descriptor. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_DeviceQualifier_t for the version of this type with non-standard LUFA specific element names.
			 */
			typedef struct
			{
				uint8_t  bLength; /**< Size of the descriptor, in bytes. */
				uint8_t  bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                           *   given by the specific class.
				                           */
				uint16_t bcdUSB; /**< BCD of the supported USB specification.
				                  *
				                  *   \see \ref VERSION_BCD() utility macro.
				                  */
				uint8_t  bDeviceClass; /**< USB device class. */
				uint8_t  bDeviceSubClass; /**< USB device subclass. */
				uint8_t  bDeviceProtocol; /**< USB device protocol. */
				uint8_t  bMaxPacketSize0; /**< Size of the control (address 0) endpoint's bank in bytes. */
				uint8_t  bNumConfigurations; /**< Total number of configurations supported by
				                              *   the device.
				                              */
				uint8_t  bReserved; /**< Reserved for future use, must be 0. */
			} ATTR_PACKED USB_StdDescriptor_DeviceQualifier_t;

			/** \brief Standard USB Configuration Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Configuration Descriptor header. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Configuration_Header_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint16_t TotalConfigurationSize; /**< Size of the configuration descriptor header,
				                                  *   and all sub descriptors inside the configuration.
				                                  */
				uint8_t  TotalInterfaces; /**< Total number of interfaces in the configuration. */

				uint8_t  ConfigurationNumber; /**< Configuration index of the current configuration. */
				uint8_t  ConfigurationStrIndex; /**< Index of a string descriptor describing the configuration. */

				uint8_t  ConfigAttributes; /**< Configuration attributes, comprised of a mask of \c USB_CONFIG_ATTR_* masks.
				                            *   On all devices, this should include USB_CONFIG_ATTR_RESERVED at a minimum.
				                            */

				uint8_t  MaxPowerConsumption; /**< Maximum power consumption of the device while in the
				                               *   current configuration, calculated by the \ref USB_CONFIG_POWER_MA()
				                               *   macro.
				                               */
			} ATTR_PACKED USB_Descriptor_Configuration_Header_t;

			/** \brief Standard USB Configuration Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Configuration Descriptor header. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Device_t for the version of this type with non-standard LUFA specific element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t  bLength; /**< Size of the descriptor, in bytes. */
				uint8_t  bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                           *   given by the specific class.
				                           */
				uint16_t wTotalLength; /**< Size of the configuration descriptor header,
				                           *   and all sub descriptors inside the configuration.
				                           */
				uint8_t  bNumInterfaces; /**< Total number of interfaces in the configuration. */
				uint8_t  bConfigurationValue; /**< Configuration index of the current configuration. */
				uint8_t  iConfiguration; /**< Index of a string descriptor describing the configuration. */
				uint8_t  bmAttributes; /**< Configuration attributes, comprised of a mask of \c USB_CONFIG_ATTR_* masks.
				                        *   On all devices, this should include USB_CONFIG_ATTR_RESERVED at a minimum.
				                        */
				uint8_t  bMaxPower; /**< Maximum power consumption of the device while in the
				                     *   current configuration, calculated by the \ref USB_CONFIG_POWER_MA()
				                     *   macro.
				                     */
			} ATTR_PACKED USB_StdDescriptor_Configuration_Header_t;

			/** \brief Standard USB Interface Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Interface Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Interface_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t InterfaceNumber; /**< Index of the interface in the current configuration. */
				uint8_t AlternateSetting; /**< Alternate setting for the interface number. The same
				                           *   interface number can have multiple alternate settings
				                           *   with different endpoint configurations, which can be
				                           *   selected by the host.
				                           */
				uint8_t TotalEndpoints; /**< Total number of endpoints in the interface. */

				uint8_t Class; /**< Interface class ID. */
				uint8_t SubClass; /**< Interface subclass ID. */
				uint8_t Protocol; /**< Interface protocol ID. */

				uint8_t InterfaceStrIndex; /**< Index of the string descriptor describing the interface. */
			} ATTR_PACKED USB_Descriptor_Interface_t;

			/** \brief Standard USB Interface Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Interface Descriptor. This structure uses the relevant standard's given element names
			 *  to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Interface_t for the version of this type with non-standard LUFA specific element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t bLength; /**< Size of the descriptor, in bytes. */
				uint8_t bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                          *   given by the specific class.
				                          */
				uint8_t bInterfaceNumber; /**< Index of the interface in the current configuration. */
				uint8_t bAlternateSetting; /**< Alternate setting for the interface number. The same
				                            *   interface number can have multiple alternate settings
				                            *   with different endpoint configurations, which can be
				                            *   selected by the host.
				                            */
				uint8_t bNumEndpoints; /**< Total number of endpoints in the interface. */
				uint8_t bInterfaceClass; /**< Interface class ID. */
				uint8_t bInterfaceSubClass; /**< Interface subclass ID. */
				uint8_t bInterfaceProtocol; /**< Interface protocol ID. */
				uint8_t iInterface; /**< Index of the string descriptor describing the
				                     *   interface.
				                     */
			} ATTR_PACKED USB_StdDescriptor_Interface_t;

			/** \brief Standard USB Interface Association Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Interface Association Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  This descriptor has been added as a supplement to the USB2.0 standard, in the ECN located at
			 *  <a>http://www.usb.org/developers/docs/InterfaceAssociationDescriptor_ecn.pdf</a>. It allows composite
			 *  devices with multiple interfaces related to the same function to have the multiple interfaces bound
			 *  together at the point of enumeration, loading one generic driver for all the interfaces in the single
			 *  function. Read the ECN for more information.
			 *
			 *  \see \ref USB_StdDescriptor_Interface_Association_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t FirstInterfaceIndex; /**< Index of the first associated interface. */
				uint8_t TotalInterfaces; /**< Total number of associated interfaces. */

				uint8_t Class; /**< Interface class ID. */
				uint8_t SubClass; /**< Interface subclass ID. */
				uint8_t Protocol; /**< Interface protocol ID. */

				uint8_t IADStrIndex; /**< Index of the string descriptor describing the
				                      *   interface association.
				                      */
			} ATTR_PACKED USB_Descriptor_Interface_Association_t;

			/** \brief Standard USB Interface Association Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Interface Association Descriptor. This structure uses the relevant standard's given
			 *  element names to ensure compatibility with the standard.
			 *
			 *  This descriptor has been added as a supplement to the USB2.0 standard, in the ECN located at
			 *  <a>http://www.usb.org/developers/docs/InterfaceAssociationDescriptor_ecn.pdf</a>. It allows composite
			 *  devices with multiple interfaces related to the same function to have the multiple interfaces bound
			 *  together at the point of enumeration, loading one generic driver for all the interfaces in the single
			 *  function. Read the ECN for more information.
			 *
			 *  \see \ref USB_Descriptor_Interface_Association_t for the version of this type with non-standard LUFA specific
			 *       element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t bLength; /**< Size of the descriptor, in bytes. */
				uint8_t bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
				                          *   given by the specific class.
				                          */
				uint8_t bFirstInterface; /**< Index of the first associated interface. */
				uint8_t bInterfaceCount; /**< Total number of associated interfaces. */
				uint8_t bFunctionClass; /**< Interface class ID. */
				uint8_t bFunctionSubClass; /**< Interface subclass ID. */
				uint8_t bFunctionProtocol; /**< Interface protocol ID. */
				uint8_t iFunction; /**< Index of the string descriptor describing the
				                    *   interface association.
				                    */
			} ATTR_PACKED USB_StdDescriptor_Interface_Association_t;

			/** \brief Standard USB Endpoint Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard Endpoint Descriptor. This structure uses LUFA-specific element names
			 *  to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_Endpoint_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				uint8_t  EndpointAddress; /**< Logical address of the endpoint within the device for the current
				                           *   configuration, including direction mask.
				                           */
				uint8_t  Attributes; /**< Endpoint attributes, comprised of a mask of the endpoint type (EP_TYPE_*)
				                      *   and attributes (ENDPOINT_ATTR_*) masks.
				                      */
				uint16_t EndpointSize; /**< Size of the endpoint bank, in bytes. This indicates the maximum packet
				                        *   size that the endpoint can receive at a time.
				                        */
				uint8_t  PollingIntervalMS; /**< Polling interval in milliseconds for the endpoint if it is an INTERRUPT
				                             *   or ISOCHRONOUS type.
				                             */
			} ATTR_PACKED USB_Descriptor_Endpoint_t;

			/** \brief Standard USB Endpoint Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard Endpoint Descriptor. This structure uses the relevant standard's given
			 *  element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_Endpoint_t for the version of this type with non-standard LUFA specific
			 *       element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t  bLength; /**< Size of the descriptor, in bytes. */
				uint8_t  bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a
				                           *   value given by the specific class.
				                           */
				uint8_t  bEndpointAddress; /**< Logical address of the endpoint within the device for the current
				                            *   configuration, including direction mask.
				                            */
				uint8_t  bmAttributes; /**< Endpoint attributes, comprised of a mask of the endpoint type (EP_TYPE_*)
				                        *   and attributes (ENDPOINT_ATTR_*) masks.
				                        */
				uint16_t wMaxPacketSize; /**< Size of the endpoint bank, in bytes. This indicates the maximum packet size
				                          *   that the endpoint can receive at a time.
				                          */
				uint8_t  bInterval; /**< Polling interval in milliseconds for the endpoint if it is an INTERRUPT or
				                     *   ISOCHRONOUS type.
				                     */
			} ATTR_PACKED USB_StdDescriptor_Endpoint_t;

			/** \brief Standard USB String Descriptor (LUFA naming conventions).
			 *
			 *  Type define for a standard string descriptor. Unlike other standard descriptors, the length
			 *  of the descriptor for placement in the descriptor header must be determined by the \ref USB_STRING_LEN()
			 *  macro rather than by the size of the descriptor structure, as the length is not fixed.
			 *
			 *  This structure should also be used for string index 0, which contains the supported language IDs for
			 *  the device as an array.
			 *
			 *  This structure uses LUFA-specific element names to make each element's purpose clearer.
			 *
			 *  \see \ref USB_StdDescriptor_String_t for the version of this type with standard element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

				#if (((ARCH == ARCH_AVR8) || (ARCH == ARCH_XMEGA)) && !defined(__DOXYGEN__))
				wchar_t  UnicodeString[];
				#else
				uint16_t UnicodeString[]; /**< String data, as unicode characters (alternatively,
				                           *   string language IDs). If normal ASCII characters are
				                           *   to be used, they must be added as an array of characters
				                           *   rather than a normal C string so that they are widened to
				                           *   Unicode size.
				                           *
				                           *   Under GCC, strings prefixed with the "L" character (before
				                           *   the opening string quotation mark) are considered to be
				                           *   Unicode strings, and may be used instead of an explicit
				                           *   array of ASCII characters on little endian devices with
				                           *   UTF-16-LE \c wchar_t encoding.
				                           */
				#endif
			} ATTR_PACKED USB_Descriptor_String_t;

			/** \brief Standard USB String Descriptor (USB-IF naming conventions).
			 *
			 *  Type define for a standard string descriptor. Unlike other standard descriptors, the length
			 *  of the descriptor for placement in the descriptor header must be determined by the \ref USB_STRING_LEN()
			 *  macro rather than by the size of the descriptor structure, as the length is not fixed.
			 *
			 *  This structure should also be used for string index 0, which contains the supported language IDs for
			 *  the device as an array.
			 *
			 *  This structure uses the relevant standard's given element names to ensure compatibility with the standard.
			 *
			 *  \see \ref USB_Descriptor_String_t for the version of this type with with non-standard LUFA specific
			 *       element names.
			 *
			 *  \note Regardless of CPU architecture, these values should be stored as little endian.
			 */
			typedef struct
			{
				uint8_t bLength; /**< Size of the descriptor, in bytes. */
				uint8_t bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t
				                          *   or a value given by the specific class.
				                          */
				uint16_t bString[]; /**< String data, as unicode characters (alternatively, string language IDs).
				                     *   If normal ASCII characters are to be used, they must be added as an array
				                     *   of characters rather than a normal C string so that they are widened to
				                     *   Unicode size.
				                     *
				                     *   Under GCC, strings prefixed with the "L" character (before the opening string
				                     *   quotation mark) are considered to be Unicode strings, and may be used instead
				                     *   of an explicit array of ASCII characters.
				                     */
			} ATTR_PACKED USB_StdDescriptor_String_t;


	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

