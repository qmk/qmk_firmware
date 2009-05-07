/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
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

/** \file
 *
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Type Defines: */
		/** Type define for the HID class specific HID descriptor. A HID descriptor is used in HID class devices
		 *  to give information about the HID device, including the HID specification used, and the report descriptors
		 *  the device contains to describe how the HID device should be controlled.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Standard USB descriptor header */
				
			uint16_t                HIDSpec; /**< HID specification implemented by the device, in BCD form */
			uint8_t                 CountryCode; /**< Country code for the country the HID device is localised for */
		
			uint8_t                 TotalHIDDescriptors; /**< Total number of HID reports linked to this HID interface */

			uint8_t                 HIDReportType; /**< Type of the first HID report descriptor */
			uint16_t                HIDReportLength; /**< Length of the first HID report descriptor */
		} USB_Descriptor_HID_t;

		/** Type define for the data type used for the HID Report descriptor data elements. A HID report
		 *  descriptor contains an array of this data type, indicating how the reports from and to the
		 *  device are formatted and how the report data is to be used by the host.
		 */
		typedef uint8_t USB_Descriptor_HIDReport_Datatype_t;

		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config; /**< Configuration descriptor header structure */
			USB_Descriptor_Interface_t            Interface; /**< Keyboard interface descriptor */
			USB_Descriptor_HID_t                  KeyboardHID; /**< Keyboard HID descriptor */
	        USB_Descriptor_Endpoint_t             KeyboardEndpoint; /**< Keyboard key report endpoint descriptor */
		} USB_Descriptor_Configuration_t;
					
	/* Macros: */
		/** Endpoint number of the keyboard key press reporting endpoint. */
		#define KEYBOARD_EPNUM               1
		
		/** Size of the keyboard report endpoints, in bytes. */
		#define KEYBOARD_EPSIZE              8

		/** Descriptor type value for a HID descriptor. */
		#define DTYPE_HID                    0x21

		/** Descriptor type value for a HID report. */
		#define DTYPE_Report                 0x22

	/* Function Prototypes: */
		uint16_t USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
		                           ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
