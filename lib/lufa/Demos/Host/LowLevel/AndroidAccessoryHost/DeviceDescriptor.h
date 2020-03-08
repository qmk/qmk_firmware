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
 *  Header file for DeviceDescriptor.c.
 */

#ifndef _DEVICEDESCRIPTOR_H_
#define _DEVICEDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "AndroidAccessoryHost.h"

	/* Enums: */
		/** Enum for the possible return codes of the \ref ProcessDeviceDescriptor() function. */
		enum AndroidHost_GetDeviceDescriptorDataCodes_t
		{
			SuccessfulDeviceRead            = 0, /**< Device Descriptor was processed successfully */
			ControlError                    = 1, /**< A control request to the device failed to complete successfully */
			InvalidDeviceDataReturned       = 2, /**< The device returned an invalid Device Descriptor */
			IncorrectAndroidDevice          = 3, /**< The attached device is not an Android device */
			NonAccessoryModeAndroidDevice   = 4, /**< The attached device is an Android device in non-accessory mode */
			AccessoryModeAndroidDevice      = 5, /**< The attached device is an Android device in accessory mode */
		};

	/* Function Prototypes: */
		uint8_t ProcessDeviceDescriptor(void);

#endif

