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
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "Config/AppConfig.h"

	/* Macros: */
		/** Descriptor type value for a DFU class functional descriptor. */
		#define DTYPE_DFUFunctional               0x21

		/** DFU attribute mask, indicating that the DFU device will detach and re-attach when a DFU_DETACH
		 *  command is issued, rather than the host issuing a USB Reset.
		 */
		#define ATTR_WILL_DETATCH                 (1 << 3)

		/** DFU attribute mask, indicating that the DFU device can communicate during the manifestation phase
		 *  (memory programming phase).
		 */
		#define ATTR_MANEFESTATION_TOLLERANT      (1 << 2)

		/** DFU attribute mask, indicating that the DFU device can accept DFU_UPLOAD requests to send data from
		 *  the device to the host.
		 */
		#define ATTR_CAN_UPLOAD                   (1 << 1)

		/** DFU attribute mask, indicating that the DFU device can accept DFU_DNLOAD requests to send data from
		 *  the host to the device.
		 */
		#define ATTR_CAN_DOWNLOAD                 (1 << 0)

		#if defined(__AVR_AT90USB1287__)
			#define PRODUCT_ID_CODE               0x2FFB
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x97
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB647__)
			#define PRODUCT_ID_CODE               0x2FF9
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x96
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB1286__)
			#define PRODUCT_ID_CODE               0x2FFB
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x97
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_AT90USB646__)
			#define PRODUCT_ID_CODE               0x2FF9
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x96
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_ATmega32U4__)
			#define PRODUCT_ID_CODE               0x2FF4
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x95
			#define AVR_SIGNATURE_3               0x87
		#elif defined(__AVR_ATmega16U4__)
			#define PRODUCT_ID_CODE               0x2FF3
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x88
		#elif defined(__AVR_ATmega32U2__)
			#define PRODUCT_ID_CODE               0x2FF0
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x95
			#define AVR_SIGNATURE_3               0x8A
		#elif defined(__AVR_ATmega16U2__)
			#define PRODUCT_ID_CODE               0x2FEF
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x89
		#elif defined(__AVR_AT90USB162__)
			#define PRODUCT_ID_CODE               0x2FFA
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x94
			#define AVR_SIGNATURE_3               0x82
		#elif defined(__AVR_ATmega8U2__)
			#define PRODUCT_ID_CODE               0x2FEE
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x93
			#define AVR_SIGNATURE_3               0x89
		#elif defined(__AVR_AT90USB82__)
			#define PRODUCT_ID_CODE               0x2FF7
			#define AVR_SIGNATURE_1               0x1E
			#define AVR_SIGNATURE_2               0x93
			#define AVR_SIGNATURE_3               0x82
		#else
			#error The selected AVR part is not currently supported by this bootloader.
		#endif

		#if !defined(PRODUCT_ID_CODE)
			#error Current AVR model is not supported by this bootloader.
		#endif

	/* Type Defines: */
		/** Type define for a DFU class function descriptor. This descriptor gives DFU class information
		 *  to the host when read, indicating the DFU device's capabilities.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Standard descriptor header structure */

			uint8_t                 Attributes; /**< DFU device attributes, a mask comprising of the
			                                     *  ATTR_* macros listed in this source file
			                                     */
			uint16_t                DetachTimeout; /**< Timeout in milliseconds between a USB_DETACH
			                                        *  command being issued and the device detaching
			                                        *  from the USB bus
			                                        */
			uint16_t                TransferSize; /**< Maximum number of bytes the DFU device can accept
			                                       *  from the host in a transaction
			                                       */
			uint16_t                DFUSpecification; /**< BCD packed DFU specification number this DFU
			                                           *  device complies with
			                                           */
		} USB_Descriptor_DFU_Functional_t;

		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;

			// DFU Interface
			USB_Descriptor_Interface_t            DFU_Interface;
			USB_Descriptor_DFU_Functional_t       DFU_Functional;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_DFU = 0, /**< DFU interface descriptor ID */
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

