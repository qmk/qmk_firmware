/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for DeviceDescriptor.c.
 */

#ifndef _DEVICEDESCRIPTOR_H_
#define _DEVICEDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		
		#include "BluetoothHost.h"
		
	/* Macros: */
		/** Device Class value for the Bluetooth Device class */
		#define BLUETOOTH_DEVICE_CLASS           0xE0

		/** Device Subclass value for the Bluetooth Device class */
		#define BLUETOOTH_DEVICE_SUBCLASS        0x01

		/** Device Protocol value for the Bluetooth Device class */
		#define BLUETOOTH_DEVICE_PROTOCOL        0x01

	/* Enums: */
		enum BluetoothHost_GetDeviceDescriptorDataCodes_t
		{
			SuccessfulDeviceRead            = 0, /**< Device Descriptor was processed successfully */
			ControlError                    = 1, /**< A control request to the device failed to complete successfully */
			InvalidDeviceDataReturned       = 2, /**< The device returned an invalid Device Descriptor */
			IncorrectBTDevice               = 3, /**< The attached device is not a Bluetooth class device */
		};

	/* Function Prototypes: */
		uint8_t ProcessDeviceDescriptor(void);	

#endif
