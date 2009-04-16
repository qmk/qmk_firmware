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
 *  Header file for TestEvents.c.
 */

#ifndef _TESTEVENTS_H_
#define _TESTEVENTS_H_

	/* Includes: */
		#include <avr/io.h>

		#include <LUFA/Common/Common.h>                          // Commonly used macros
		#include <LUFA/Drivers/USB/USB.h>                        // USB Functionality
		#include <LUFA/Drivers/Board/LEDs.h>                     // LED driver
		#include <LUFA/Drivers/Peripheral/Serial_Stream.h>       // USART Stream driver
		#include <LUFA/Drivers/Misc/TerminalCodes.h>             // ANSI Terminal Escape Codes
		#include <LUFA/Scheduler/Scheduler.h>                    // Simple scheduler for task management

	/* Event Catch List: */
		/** Indicates that this module will catch the USB_VBUSChange event when thrown by the library. */
		HANDLES_EVENT(USB_VBUSChange);

		/** Indicates that this module will catch the USB_VBUSConnect event when thrown by the library. */
		HANDLES_EVENT(USB_VBUSConnect);

		/** Indicates that this module will catch the USB_VBUSDisconnect event when thrown by the library. */
		HANDLES_EVENT(USB_VBUSDisconnect);

		/** Indicates that this module will catch the USB_Connect event when thrown by the library. */
		HANDLES_EVENT(USB_Connect);

		/** Indicates that this module will catch the USB_Disconnect event when thrown by the library. */
		HANDLES_EVENT(USB_Disconnect);

		/** Indicates that this module will catch the USB_Suspend event when thrown by the library. */
		HANDLES_EVENT(USB_Suspend);

		/** Indicates that this module will catch the USB_WakeUp event when thrown by the library. */
		HANDLES_EVENT(USB_WakeUp);

		/** Indicates that this module will catch the USB_Reset event when thrown by the library. */
		HANDLES_EVENT(USB_Reset);

		/** Indicates that this module will catch the USB_UIDChange event when thrown by the library. */
		HANDLES_EVENT(USB_UIDChange);

		/** Indicates that this module will catch the USB_PowerOnFail event when thrown by the library. */
		HANDLES_EVENT(USB_PowerOnFail);

		/** Indicates that this module will catch the USB_HostError event when thrown by the library. */
		HANDLES_EVENT(USB_HostError);

		/** Indicates that this module will catch the USB_DeviceEnumerationFailed event when thrown by the library. */
		HANDLES_EVENT(USB_DeviceEnumerationFailed);

		/** Indicates that this module will catch the USB_DeviceError event when thrown by the library. */
		HANDLES_EVENT(USB_DeviceError);

		/** Indicates that this module will catch the USB_UnhandledControlPacket event when thrown by the library. */
		HANDLES_EVENT(USB_UnhandledControlPacket);

		/** Indicates that this module will catch the USB_ConfigurationChanged event when thrown by the library. */
		HANDLES_EVENT(USB_ConfigurationChanged);

		/** Indicates that this module will catch the USB_DeviceAttached event when thrown by the library. */
		HANDLES_EVENT(USB_DeviceAttached);

		/** Indicates that this module will catch the USB_DeviceUnattached event when thrown by the library. */
		HANDLES_EVENT(USB_DeviceUnattached);

	/* Macros: */
		/** Prefix sent through the USART when an even fires before the actual event message. */
		#define EVENT_PREFIX ESC_INVERSE_ON "EVENT:" ESC_INVERSE_OFF " "

	/* Function Prototypes: */
		#if defined(INCLUDE_FROM_TESTEVENTS_C) || defined(__DOXYGEN__)
			static void Abort_Program(void) ATTR_NO_RETURN;
		#endif

#endif
