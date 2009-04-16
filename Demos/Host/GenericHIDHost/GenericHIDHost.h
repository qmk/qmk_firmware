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

/** \file
 *
 *  Header file for MouseHost.c.
 */

#ifndef _GENERICHID_HOST_H_
#define _GENERICHID_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
		#include <avr/interrupt.h>
		#include <avr/power.h>
		#include <stdio.h>

		#include <LUFA/Version.h>                                // Library Version Information
		#include <LUFA/Drivers/Misc/TerminalCodes.h>             // ANSI Terminal Escape Codes
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		#include <LUFA/Drivers/AT90USBXXX/Serial_Stream.h>       // Serial stream driver
		#include <LUFA/Drivers/Board/LEDs.h>                     // LEDs driver
		#include <LUFA/Scheduler/Scheduler.h>                    // Simple scheduler for task management
		
		#include "ConfigDescriptor.h"
		
	/* Macros: */
		/** Pipe number for the HID data IN pipe */
		#define HID_DATA_IN_PIPE                 1
		
		/** Pipe number for the HID data OUT pipe */
		#define HID_DATA_OUT_PIPE                2

		/** HID Class specific request to send a HID report to the device. */
		#define REQ_SetReport                    0x09
		
		/** HID Report type specifier, for output reports to a device */
		#define HID_REPORTTYPE_OUTPUT            0x02
		
		/** HID Report type specifier, for feature reports to a device */
		#define HID_REPORTTYPE_FEATURE           0x03

	/* Task Definitions: */
		TASK(USB_HID_Host);

	/* Enums: */
		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum GenricHIDHost_StatusCodes_t
		{
			Status_USBNotReady      = 0, /**< USB is not ready (disconnected from a USB device) */
			Status_USBEnumerating   = 1, /**< USB interface is enumerating */
			Status_USBReady         = 2, /**< USB interface is connected and ready */
			Status_EnumerationError = 3, /**< Software error while enumerating the attached USB device */
			Status_HardwareError    = 4, /**< Hardware error while enumerating the attached USB device */
		};
		
	/* Event Handlers: */
		HANDLES_EVENT(USB_DeviceAttached);
		HANDLES_EVENT(USB_DeviceUnattached);
		HANDLES_EVENT(USB_DeviceEnumerationComplete);
		HANDLES_EVENT(USB_HostError);
		HANDLES_EVENT(USB_DeviceEnumerationFailed);

	/* Function Prototypes: */
		void UpdateStatus(uint8_t CurrentStatus);
		void ReadNextReport(void);
		void WriteNextReport(uint8_t* ReportOUTData, uint8_t ReportIndex, uint8_t ReportType, uint16_t ReportLength);
		
#endif
