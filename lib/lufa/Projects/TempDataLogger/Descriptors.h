/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

		#include "TempDataLogger.h"
		#include "Config/AppConfig.h"

	/* Macros: */
		/** Endpoint address of the Mass Storage device-to-host data IN endpoint. */
		#define MASS_STORAGE_IN_EPADDR         (ENDPOINT_DIR_IN  | 3)

		/** Endpoint address of the Mass Storage host-to-device data OUT endpoint. */
		#define MASS_STORAGE_OUT_EPADDR        (ENDPOINT_DIR_OUT | 4)

		/** Size in bytes of the Mass Storage data endpoints. */
		#define MASS_STORAGE_IO_EPSIZE         64

		/** Endpoint address of the Generic HID reporting IN endpoint. */
		#define GENERIC_IN_EPADDR              (ENDPOINT_DIR_IN  | 1)

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

			// Mass Storage Interface
			USB_Descriptor_Interface_t            MS_Interface;
			USB_Descriptor_Endpoint_t             MS_DataInEndpoint;
			USB_Descriptor_Endpoint_t             MS_DataOutEndpoint;

			// Settings Management Generic HID Interface
			USB_Descriptor_Interface_t            HID_Interface;
			USB_HID_Descriptor_HID_t              HID_GenericHID;
			USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_MassStorage = 0, /**< Mass storage interface descriptor ID */
			INTERFACE_ID_HID         = 1, /**< HID interface descriptor ID */
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

