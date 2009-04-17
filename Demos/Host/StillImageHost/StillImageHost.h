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
 *  Header file for StillImageHost.c.
 */

#ifndef _STILL_IMAGE_HOST_H_
#define _STILL_IMAGE_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <stdio.h>
		
		#include "ConfigDescriptor.h"
		#include "PIMACodes.h"
		#include "StillImageCommands.h"

		#include <LUFA/Drivers/Misc/TerminalCodes.h>             // ANSI Terminal Escape Codes
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		#include <LUFA/Drivers/Peripheral/SerialStream.h>        // Serial stream driver
		#include <LUFA/Drivers/Board/LEDs.h>                     // LED driver
		#include <LUFA/Scheduler/Scheduler.h>                    // Simple scheduler for task management

	/* Enums: */
		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum StillImageHost_StatusCodes_t
		{
			Status_USBNotReady      = 0, /**< USB is not ready (disconnected from a USB device) */
			Status_USBEnumerating   = 1, /**< USB interface is enumerating */
			Status_USBReady         = 2, /**< USB interface is connected and ready */
			Status_EnumerationError = 3, /**< Software error while enumerating the attached USB device */
			Status_HardwareError    = 4, /**< Hardware error while enumerating the attached USB device */
			Status_Busy             = 5, /**< Busy reading or writing to the attached Still Image device */
			Status_PIMACommandError = 6, /**< Error while sending or receiving a PIM command to the attached device */
		};

	/* Task Definitions: */
		TASK(USB_SImage_Host);

	/* Event Handlers: */
		HANDLES_EVENT(USB_DeviceAttached);
		HANDLES_EVENT(USB_DeviceUnattached);
		HANDLES_EVENT(USB_DeviceEnumerationComplete);
		HANDLES_EVENT(USB_HostError);
		HANDLES_EVENT(USB_DeviceEnumerationFailed);
		
	/* Function Prototypes: */
		void UnicodeToASCII(uint8_t* restrict UnicodeString, char* restrict Buffer);
		void ShowCommandError(uint8_t ErrorCode, bool ResponseCodeError);
		void UpdateStatus(uint8_t CurrentStatus);
		
#endif
