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
		#include <LUFA/Drivers/USB/USB.h>

		#include "Config/AppConfig.h"

	/* Macros: */
		#if defined(__AVR_AT90USB1287__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x97
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB647__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x96
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB1286__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x97
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB646__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x96
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_ATmega32U4__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x95
			#define AVR_SIGNATURE_3               0x87
		#elif defined(__AVR_ATmega16U4__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x88
		#elif defined(__AVR_ATmega32U2__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x95
			#define AVR_SIGNATURE_3               0x8A
		#elif defined(__AVR_ATmega16U2__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x89
		#elif defined(__AVR_AT90USB162__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_ATmega8U2__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x93
			#define AVR_SIGNATURE_3               0x89
		#elif defined(__AVR_AT90USB82__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x93
			#define AVR_SIGNATURE_3               0x82
		#else
			#error The selected AVR part is not currently supported by this bootloader.
		#endif

		/** Endpoint address for the CDC control interface event notification endpoint. */
		#define CDC_NOTIFICATION_EPADDR        (ENDPOINT_DIR_IN | 2)

		/** Endpoint address for the CDC data interface TX (data IN) endpoint. */
		#define CDC_TX_EPADDR                  (ENDPOINT_DIR_IN | 3)

		/** Endpoint address for the CDC data interface RX (data OUT) endpoint. */
		#define CDC_RX_EPADDR                  (ENDPOINT_DIR_OUT | 4)

		/** Size of the CDC data interface TX and RX data endpoint banks, in bytes. */
		#define CDC_TXRX_EPSIZE                16

		/** Size of the CDC control interface notification endpoint bank, in bytes. */
		#define CDC_NOTIFICATION_EPSIZE        8

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;

			// CDC Control Interface
			USB_Descriptor_Interface_t               CDC_CCI_Interface;
			USB_CDC_Descriptor_FunctionalHeader_t    CDC_Functional_Header;
			USB_CDC_Descriptor_FunctionalACM_t       CDC_Functional_ACM;
			USB_CDC_Descriptor_FunctionalUnion_t     CDC_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;

			// CDC Data Interface
			USB_Descriptor_Interface_t               CDC_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_CDC_CCI = 0, /**< CDC CCI interface descriptor ID */
			INTERFACE_ID_CDC_DCI = 1, /**< CDC DCI interface descriptor ID */
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
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

