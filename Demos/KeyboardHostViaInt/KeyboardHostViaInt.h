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
 *  Header file for KeyboardHostViaInt.c.
 */
 
#ifndef _KEYBOARD_HOST_VIA_INT_H_
#define _KEYBOARD_HOST_VIA_INT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <avr/interrupt.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <stdio.h>

		#include <LUFA/Version.h>                                // Library Version Information
		#include <LUFA/Common/ButtLoadTag.h>                     // PROGMEM tags readable by the ButtLoad project
		#include <LUFA/Drivers/Misc/TerminalCodes.h>             // ANSI Terminal Escape Codes
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		#include <LUFA/Drivers/AT90USBXXX/Serial_Stream.h>       // Serial stream driver
		#include <LUFA/Drivers/Board/LEDs.h>                     // LEDs driver
		#include <LUFA/Scheduler/Scheduler.h>                    // Simple scheduler for task management
		
		#include "ConfigDescriptor.h"
		
	/* Macros: */
		/** Pipe number for the keyboard data IN pipe */
		#define KEYBOARD_DATAPIPE              1

		/** HID Class Specific request to set the report protocol mode */
		#define REQ_SetProtocol             0x0B

	/* Type Defines: */
		/** Type define for a standard Boot Protocol Keyboard report */
		typedef struct
		{
			uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (such as Shift, Control, etc.) */
			uint8_t RESERVED; /**< Reserved for OEM use, always set to 0 */
			uint8_t KeyCode; /**< Key code of the currently pressed key */
		} USB_KeyboardReport_Data_t;

		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum KeyboardHostViaInt_StatusCodes_t
		{
			Status_USBNotReady      = 0, /**< USB is not ready (disconnected from a USB device) */
			Status_USBEnumerating   = 1, /**< USB interface is enumerating */
			Status_USBReady         = 2, /**< USB interface is connected and ready */
			Status_EnumerationError = 3, /**< Software error while enumerating the attached USB device */
			Status_HardwareError    = 4, /**< Hardware error while enumerating the attached USB device */
		};
		
	/* Task Definitions: */
		TASK(USB_Keyboard_Host);

	/* Event Handlers: */
		HANDLES_EVENT(USB_DeviceAttached);
		HANDLES_EVENT(USB_DeviceUnattached);
		HANDLES_EVENT(USB_DeviceEnumerationComplete);
		HANDLES_EVENT(USB_HostError);
		HANDLES_EVENT(USB_DeviceEnumerationFailed);

	/* Function Prototypes: */
		void UpdateStatus(uint8_t CurrentStatus);
		
#endif
