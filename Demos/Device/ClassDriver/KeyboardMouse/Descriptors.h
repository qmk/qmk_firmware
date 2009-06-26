/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
  
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
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/HID.h>

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			USB_Descriptor_Interface_t            KeyboardInterface;
			USB_HID_Descriptor_t                  KeyboardHID;
	        USB_Descriptor_Endpoint_t             KeyboardInEndpoint;
			USB_Descriptor_Interface_t            MouseInterface;
			USB_HID_Descriptor_t                  MouseHID;
	        USB_Descriptor_Endpoint_t             MouseInEndpoint;
		} USB_Descriptor_Configuration_t;
					
	/* Macros: */
		/** Endpoint number of the Keyboard HID reporting IN endpoint. */
		#define KEYBOARD_IN_EPNUM         1

		/** Endpoint number of the Mouse HID reporting IN endpoint. */
		#define MOUSE_IN_EPNUM            3

		/** Size in bytes of each of the HID reporting IN and OUT endpoints. */
		#define HID_EPSIZE                8

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
