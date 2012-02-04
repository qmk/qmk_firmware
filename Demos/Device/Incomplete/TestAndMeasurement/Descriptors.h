/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.
              
  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Peter Lawrence (majbthrd [at] gmail [dot] com)

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
		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
		/** Endpoint number of the TMC notification IN endpoint. */
		#define TMC_NOTIFICATION_EPNUM  2	

		/** Endpoint number of the TMC device-to-host data IN endpoint. */
		#define TMC_IN_EPNUM            3	

		/** Endpoint number of the TMC host-to-device data OUT endpoint. */
		#define TMC_OUT_EPNUM           4	

		/** Size in bytes of the TMC data endpoints. */
		#define TMC_IO_EPSIZE           64

		/** Size in bytes of the TMC notification endpoint. */
		#define TMC_NOTIFICATION_EPSIZE 8

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t Config;
			
			// Test and Measurement Interface
			USB_Descriptor_Interface_t            TM_Interface;
			USB_Descriptor_Endpoint_t             TM_DataOutEndpoint;
			USB_Descriptor_Endpoint_t             TM_DataInEndpoint;
			USB_Descriptor_Endpoint_t             TM_NotificationEndpoint;
		} USB_Descriptor_Configuration_t;

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint8_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

