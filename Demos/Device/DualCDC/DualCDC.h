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
 *  Header file for DualCDC.c.
 */

#ifndef _DUAL_CDC_H_
#define _DUAL_CDC_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <string.h>

		#include "Descriptors.h"

		#include <LUFA/Version.h>                        // Library Version Information
		#include <LUFA/Common/ButtLoadTag.h>             // PROGMEM tags readable by the ButtLoad project
		#include <LUFA/Drivers/USB/USB.h>                // USB Functionality
		#include <LUFA/Drivers/Board/Joystick.h>         // Joystick driver
		#include <LUFA/Drivers/Board/LEDs.h>             // LEDs driver
		#include <LUFA/Scheduler/Scheduler.h>            // Simple scheduler for task management

	/* Macros: */
		/** CDC Class specific request to get the current virtual serial port configuration settings. */
		#define REQ_GetLineEncoding          0x21

		/** CDC Class specific request to set the current virtual serial port configuration settings. */
		#define REQ_SetLineEncoding          0x20

		/** CDC Class specific request to set the current virtual serial port handshake line states. */
		#define REQ_SetControlLineState      0x22

	/* Event Handlers: */
		/** Indicates that this module will catch the USB_Connect event when thrown by the library. */
		HANDLES_EVENT(USB_Connect);

		/** Indicates that this module will catch the USB_Disconnect event when thrown by the library. */
		HANDLES_EVENT(USB_Disconnect);

		/** Indicates that this module will catch the USB_ConfigurationChanged event when thrown by the library. */
		HANDLES_EVENT(USB_ConfigurationChanged);

		/** Indicates that this module will catch the USB_UnhandledControlPacket event when thrown by the library. */
		HANDLES_EVENT(USB_UnhandledControlPacket);
		
	/* Type Defines: */
		/** Type define for the virtual serial port line encoding settings, for storing the current USART configuration
		 *  as set by the host via a class specific request.
		 */
		typedef struct
		{
			uint32_t BaudRateBPS; /**< Baud rate of the virtual serial port, in bits per second */
			uint8_t  CharFormat; /**< Character format of the virtual serial port, a value from the
			                      *   CDCDevice_CDC_LineCodingFormats_t enum
			                      */
			uint8_t  ParityType; /**< Parity setting of the virtual serial port, a value from the
			                      *   CDCDevice_LineCodingParity_t enum
			                      */
			uint8_t  DataBits; /**< Bits of data per character of the virtual serial port */
		} CDC_Line_Coding_t;
		
	/* Enums: */
		/** Enum for the possible line encoding formats of a virtual serial port. */
		enum CDCDevice_CDC_LineCodingFormats_t
		{
			OneStopBit          = 0, /**< Each frame contains one stop bit */
			OneAndAHalfStopBits = 1, /**< Each frame contains one and a half stop bits */
			TwoStopBits         = 2, /**< Each frame contains two stop bits */
		};
		
		/** Enum for the possible line encoding parity settings of a virtual serial port. */
		enum CDCDevice_LineCodingParity_t
		{
			Parity_None         = 0, /**< No parity bit mode on each frame */
			Parity_Odd          = 1, /**< Odd parity bit mode on each frame */
			Parity_Even         = 2, /**< Even parity bit mode on each frame */
			Parity_Mark         = 3, /**< Mark parity bit mode on each frame */
			Parity_Space        = 4, /**< Space parity bit mode on each frame */
		};

		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum DualCDC_StatusCodes_t
		{
			Status_USBNotReady    = 0, /**< USB is not ready (disconnected from a USB host) */
			Status_USBEnumerating = 1, /**< USB interface is enumerating */
			Status_USBReady       = 2, /**< USB interface is connected and ready */
		};

	/* Tasks: */
		TASK(CDC1_Task);
		TASK(CDC2_Task);

	/* Function Prototypes: */
		void UpdateStatus(uint8_t CurrentStatus);
		
#endif
