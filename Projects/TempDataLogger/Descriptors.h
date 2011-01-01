/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "TempDataLogger.h"

	/* Macros: */
		/** Endpoint number of the Mass Storage device-to-host data IN endpoint. */
		#define MASS_STORAGE_IN_EPNUM          3

		/** Endpoint number of the Mass Storage host-to-device data OUT endpoint. */
		#define MASS_STORAGE_OUT_EPNUM         4

		/** Size in bytes of the Mass Storage data endpoints. */
		#define MASS_STORAGE_IO_EPSIZE         64

		/** Endpoint number of the Generic HID reporting IN endpoint. */
		#define GENERIC_IN_EPNUM               1

		/** Size in bytes of the Generic HID reporting endpoint. */
		#define GENERIC_EPSIZE                 16

		/** Size in bytes of the Generic HID reports (including report ID byte). */
		#define GENERIC_REPORT_SIZE            sizeof(Device_Report_t)

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            MS_Interface;
			USB_Descriptor_Endpoint_t             MS_DataInEndpoint;
			USB_Descriptor_Endpoint_t             MS_DataOutEndpoint;
			USB_Descriptor_Interface_t            HID_Interface;
			USB_HID_Descriptor_HID_t              HID_GenericHID;
			USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

