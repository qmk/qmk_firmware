/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

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
		#elif defined(__AVR_ATmega32U6__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x95
			#define AVR_SIGNATURE_3               0x88
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
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB82__)
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x93
			#define AVR_SIGNATURE_3               0x89
		#else
			#error The selected AVR part is not currently supported by this bootloader.
		#endif

		/** Endpoint number for the CDC control interface event notification endpoint. */
		#define CDC_NOTIFICATION_EPNUM         2

		/** Endpoint number for the CDC data interface TX (data IN) endpoint. */
		#define CDC_TX_EPNUM                   3

		/** Endpoint number for the CDC data interface RX (data OUT) endpoint. */
		#define CDC_RX_EPNUM                   4

		/** Size of the CDC data interface TX and RX data endpoint banks, in bytes. */
		#define CDC_TXRX_EPSIZE                16

		/** Size of the CDC control interface notification endpoint bank, in bytes. */
		#define CDC_NOTIFICATION_EPSIZE        8

	/* Type Defines: */
		/** Type define for a CDC class-specific functional header descriptor. This indicates to the host that the device
		 *  contains one or more CDC functional data descriptors, which give the CDC interface's capabilities and configuration.
		 *  See the CDC class specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between CDC class-specific descriptors. */
			uint16_t                CDCSpecification; /**< Version number of the CDC specification implemented by the device,
			                                           *   encoded in BCD format.
			                                           */
		} USB_Descriptor_CDC_FunctionalHeader_t;

		/** Type define for a CDC class-specific functional ACM descriptor. This indicates to the host that the CDC interface
		 *  supports the CDC ACM subclass of the CDC specification. See the CDC class specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between CDC class-specific descriptors. */
			uint8_t                 Capabilities; /**< Capabilities of the ACM interface, given as a bit mask. */
		} USB_Descriptor_CDC_FunctionalACM_t;

		/** Type define for a CDC class-specific functional Union descriptor. This indicates to the host that specific
		 *  CDC control and data interfaces are related. See the CDC class specification for more details.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between CDC class-specific descriptors. */
			uint8_t                 MasterInterfaceNumber; /**< Interface number of the CDC Control interface. */
			uint8_t                 SlaveInterfaceNumber; /**< Interface number of the CDC Data interface. */
		} USB_Descriptor_CDC_FunctionalUnion_t;

		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;
			USB_Descriptor_Interface_t               CDC_CCI_Interface;
			USB_Descriptor_CDC_FunctionalHeader_t    CDC_Functional_Header;
			USB_Descriptor_CDC_FunctionalACM_t       CDC_Functional_ACM;
			USB_Descriptor_CDC_FunctionalUnion_t     CDC_Functional_Union;
			USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;
			USB_Descriptor_Interface_t               CDC_DCI_Interface;
			USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
			USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
		} USB_Descriptor_Configuration_t;

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

