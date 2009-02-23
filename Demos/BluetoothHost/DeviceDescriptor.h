/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
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

#ifndef _DEVICEDESCRIPTOR_H_
#define _DEVICEDESCRIPTOR_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		
		#include "BluetoothHost.h"
		
	/* Macros: */
		#define BLUETOOTH_DEVICE_CLASS           0xE0
		#define BLUETOOTH_DEVICE_SUBCLASS        0x01
		#define BLUETOOTH_DEVICE_PROTOCOL        0x01

	/* Enums: */
		enum BluetoothHost_GetDeviceDescriptorDataCodes_t
		{
			SuccessfulDeviceRead                 = 0,
			ControlErrorDuringDeviceRead         = 1,
			InvalidDeviceDataReturned            = 2,
			IncorrectDevice                      = 3,
		};

	/* Function Prototypes: */
		uint8_t ProcessDeviceDescriptor(void);	

#endif
