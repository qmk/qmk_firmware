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
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** Endpoint address of the first CDC interface's device-to-host data IN endpoint. */
		#define CDC1_TX_EPADDR                 (ENDPOINT_DIR_IN  | 1)

		/** Endpoint address of the first CDC interface's host-to-device data OUT endpoint. */
		#define CDC1_RX_EPADDR                 (ENDPOINT_DIR_OUT | 2)

		/** Endpoint address of the first CDC interface's device-to-host notification IN endpoint. */
		#define CDC1_NOTIFICATION_EPADDR       (ENDPOINT_DIR_IN  | 3)

		/** Endpoint address of the second CDC interface's device-to-host data IN endpoint. */
		#define CDC2_TX_EPADDR                 (ENDPOINT_DIR_IN  | 4)

		/** Endpoint address of the second CDC interface's host-to-device data OUT endpoint. */
		#define CDC2_RX_EPADDR                 (ENDPOINT_DIR_OUT | 5)

		/** Endpoint address of the second CDC interface's device-to-host notification IN endpoint. */
		#define CDC2_NOTIFICATION_EPADDR       (ENDPOINT_DIR_IN  | 6)

		/** Size in bytes of the CDC device-to-host notification IN endpoints. */
		#define CDC_NOTIFICATION_EPSIZE        8

		/** Size in bytes of the CDC data IN and OUT endpoints. */
		#define CDC_TXRX_EPSIZE                16

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;

			// First CDC Control Interface
			USB_Descriptor_Interface_Association_t   CDC1_IAD;
			USB_Descriptor_Interface_t               CDC1_CCI_Interface;
			USB_CDC_Descriptor_FunctionalHeader_t    CDC1_Functional_Header;
			USB_CDC_Descriptor_FunctionalACM_t       CDC1_Functional_ACM;
			USB_CDC_Descriptor_FunctionalUnion_t     CDC1_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC1_ManagementEndpoint;

			// First CDC Data Interface
			USB_Descriptor_Interface_t               CDC1_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC1_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC1_DataInEndpoint;

			// Second CDC Control Interface
			USB_Descriptor_Interface_Association_t   CDC2_IAD;
			USB_Descriptor_Interface_t               CDC2_CCI_Interface;
			USB_CDC_Descriptor_FunctionalHeader_t    CDC2_Functional_Header;
			USB_CDC_Descriptor_FunctionalACM_t       CDC2_Functional_ACM;
			USB_CDC_Descriptor_FunctionalUnion_t     CDC2_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC2_ManagementEndpoint;

			// Second CDC Data Interface
			USB_Descriptor_Interface_t               CDC2_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC2_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC2_DataInEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_CDC1_CCI = 0, /**< CDC1 CCI interface descriptor ID */
			INTERFACE_ID_CDC1_DCI = 1, /**< CDC1 DCI interface descriptor ID */
			INTERFACE_ID_CDC2_CCI = 2, /**< CDC2 CCI interface descriptor ID */
			INTERFACE_ID_CDC2_DCI = 3, /**< CDC2 DCI interface descriptor ID */
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
		};

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

