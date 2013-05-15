/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
		#include <LUFA/Drivers/Board/LEDs.h>

		#include "Config/AppConfig.h"

	/* Preprocessor Checks: */
		#if defined(LIBUSB_DRIVER_COMPAT) && defined(RESET_TOGGLES_LIBUSB_COMPAT)
			#error LIBUSB_DRIVER_COMPAT and RESET_TOGGLES_LIBUSB_COMPAT are mutually exclusive.
		#endif

	/* Macros: */
		/** Endpoint address of the AVRISP data OUT endpoint. */
		#define AVRISP_DATA_OUT_EPADDR         (ENDPOINT_DIR_OUT | 2)

		/** Endpoint address of the AVRISP data IN endpoint, when in Jungo driver compatibility mode. */
		#define AVRISP_DATA_IN_EPADDR_JUNGO    (ENDPOINT_DIR_IN  | 2)

		/** Endpoint address of the AVRISP data IN endpoint, when in LibUSB driver compatibility mode. */
		#define AVRISP_DATA_IN_EPADDR_LIBUSB   (ENDPOINT_DIR_IN  | 3)

		#if defined(RESET_TOGGLES_LIBUSB_COMPAT)
			#define AVRISP_DATA_IN_EPADDR      AVRISP_CurrDataINEndpointAddress
		#elif defined(LIBUSB_DRIVER_COMPAT)
			#define AVRISP_DATA_IN_EPADDR      AVRISP_DATA_IN_EPADDR_LIBUSB
		#else
			/** Endpoint address of the AVRISP data IN endpoint. */
			#define AVRISP_DATA_IN_EPADDR      AVRISP_DATA_IN_EPADDR_JUNGO
		#endif

		/** Size in bytes of the AVRISP data endpoint. */
		#define AVRISP_DATA_EPSIZE             64

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;

			// Atmel AVRISP-MKII Interface
			USB_Descriptor_Interface_t               AVRISP_Interface;
			USB_Descriptor_Endpoint_t                AVRISP_DataInEndpoint;
			USB_Descriptor_Endpoint_t                AVRISP_DataOutEndpoint;
		} AVRISP_USB_Descriptor_Configuration_t;

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum AVRISP_StringDescriptors_t
		{
		    AVRISP_STRING_ID_Language      = 0, /**< Supported Languages string descriptor ID (must be zero) */
		    AVRISP_STRING_ID_Manufacturer  = 1, /**< Manufacturer string ID */
		    AVRISP_STRING_ID_Product       = 2, /**< Product string ID */
		    AVRISP_STRING_ID_Serial        = 3, /**< Serial number string ID */
		};

	/* External Variables: */
		#if defined(RESET_TOGGLES_LIBUSB_COMPAT)
			extern uint8_t AVRISP_CurrDataINEndpointAddress;
		#endif

	/* Function Prototypes: */
		uint16_t AVRISP_GetDescriptor(const uint16_t wValue,
		                              const uint8_t wIndex,
		                              const void** const DescriptorAddress,
		                              uint8_t* const DescriptorMemorySpace)
		                              ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3) ATTR_NON_NULL_PTR_ARG(4);

		#if defined(RESET_TOGGLES_LIBUSB_COMPAT)
		void CheckExternalReset(void) ATTR_NAKED ATTR_INIT_SECTION(3);
		void UpdateCurrentCompatibilityMode(void);
		#endif

#endif

