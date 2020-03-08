/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "Config/AppConfig.h"

	/* Macros: */
		/** Endpoint address of the Mass Storage device-to-host data IN endpoint. */
		#define MASS_STORAGE_IN_EPADDR         (ENDPOINT_DIR_IN  | 3)

		/** Endpoint address of the Mass Storage host-to-device data OUT endpoint. */
		#define MASS_STORAGE_OUT_EPADDR        (ENDPOINT_DIR_OUT | 4)

		/** Size in bytes of the Mass Storage data endpoints. */
		#define MASS_STORAGE_IO_EPSIZE         64

		/** Endpoint address of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN  | 5)

		/** Endpoint address of the CDC device-to-host data IN endpoint. */
		#define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN  | 1)

		/** Endpoint address of the CDC host-to-device data OUT endpoint. */
		#define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 2)

		/** Size in bytes of the CDC device-to-host notification IN endpoint. */
		#define CDC_NOTIFICATION_EPSIZE        8

		/** Size in bytes of the CDC data IN and OUT endpoints. */
		#define CDC_TXRX_EPSIZE                64

		/** Vendor request (0-255) the host should issue to retrieve the
		 *  Microsoft OS Compatibility Descriptors. */
		#define VENDOR_REQUEST_ID_MS_COMPAT    0x01

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t  Config;

			// RNDIS CDC Command Interface
			USB_Descriptor_Interface_Association_t CDC_IAD;
			USB_Descriptor_Interface_t             CDC_CCI_Interface;
			USB_CDC_Descriptor_FunctionalHeader_t  CDC_Functional_Header;
			USB_CDC_Descriptor_FunctionalACM_t     CDC_Functional_ACM;
			USB_CDC_Descriptor_FunctionalUnion_t   CDC_Functional_Union;
			USB_Descriptor_Endpoint_t              CDC_NotificationEndpoint;

			// RNDIS CDC Data Interface
			USB_Descriptor_Interface_t             CDC_DCI_Interface;
			USB_Descriptor_Endpoint_t              RNDIS_DataOutEndpoint;
			USB_Descriptor_Endpoint_t              RNDIS_DataInEndpoint;

			// Mass Storage Interface
			USB_Descriptor_Interface_t             MS_Interface;
			USB_Descriptor_Endpoint_t              MS_DataInEndpoint;
			USB_Descriptor_Endpoint_t              MS_DataOutEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Type define for a Microsoft OS Compatibility 1.0 descriptor. */
		typedef struct
		{
			uint32_t dwLength;
			uint16_t bcdVersion;
			uint16_t wIndex;
			uint8_t  bCount;
			uint8_t  bReserved[7];
			uint8_t  bFirstInterfaceNumber;
			uint8_t  bReserved2;
			char     compatibleID[8];
			char     subCompatibleID[8];
			uint8_t  bReserved3[6];
		} USB_Descriptor_MSCompatibility_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_CDC_CCI     = 0, /**< CDC CCI interface descriptor ID */
			INTERFACE_ID_CDC_DCI     = 1, /**< CDC DCI interface descriptor ID */
			INTERFACE_ID_MassStorage = 2, /**< Mass storage interface descriptor ID */
		};

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum StringDescriptors_t
		{
			STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
			STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
			STRING_ID_Product      = 2, /**< Product string ID */
			STRING_ID_MS_Compat    = 0xEE, /**< MS OS Compatibility string descriptor ID (magic value set by Microsoft) */
		};

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

		void     CheckIfMSCompatibilityDescriptorRequest(void);

#endif

