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
 *  Header file for USBtoSerial.c.
 */

#ifndef _USB_SERIAL_H_
#define _USB_SERIAL_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/interrupt.h>
		#include <avr/power.h>

		#include "Descriptors.h"

		#include "Lib/RingBuff.h"

		#include <LUFA/Version.h>                         // Library Version Information
		#include <LUFA/Drivers/USB/USB.h>                 // USB Functionality
		#include <LUFA/Drivers/Peripheral/Serial.h>       // USART driver
		#include <LUFA/Drivers/Board/LEDs.h>              // LEDs driver
		#include <LUFA/Scheduler/Scheduler.h>             // Simple scheduler for task management

	/* Macros: */
		/** CDC Class specific request to get the current virtual serial port configuration settings. */
		#define REQ_GetLineEncoding          0x21

		/** CDC Class specific request to set the current virtual serial port configuration settings. */
		#define REQ_SetLineEncoding          0x20

		/** CDC Class specific request to set the current virtual serial port handshake line states. */
		#define REQ_SetControlLineState      0x22
		
		/** Notification type constant for a change in the virtual serial port handshake line states, for
		 *  use with a USB_Notification_Header_t notification structure when sent to the host via the CDC 
		 *  notification endpoint.
		 */
		#define NOTIF_SerialState            0x20

		/** Mask for the DTR handshake line for use with the REQ_SetControlLineState class specific request
		 *  from the host, to indicate that the DTR line state should be high.
		 */
		#define CONTROL_LINE_OUT_DTR         (1 << 0)

		/** Mask for the RTS handshake line for use with the REQ_SetControlLineState class specific request
		 *  from the host, to indicate that theRTS line state should be high.
		 */
		#define CONTROL_LINE_OUT_RTS         (1 << 1)
		
		/** Mask for the DCD handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the DCD line state is currently high.
		 */
		#define CONTROL_LINE_IN_DCD          (1 << 0)

		/** Mask for the DSR handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the DSR line state is currently high.
		 */
		#define CONTROL_LINE_IN_DSR          (1 << 1)

		/** Mask for the BREAK handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the BREAK line state is currently high.
		 */
		#define CONTROL_LINE_IN_BREAK        (1 << 2)

		/** Mask for the RING handshake line for use with the a NOTIF_SerialState class specific notification
		 *  from the device to the host, to indicate that the RING line state is currently high.
		 */
		#define CONTROL_LINE_IN_RING         (1 << 3)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a framing error has occurred on the virtual serial port.
		 */
		#define CONTROL_LINE_IN_FRAMEERROR   (1 << 4)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a parity error has occurred on the virtual serial port.
		 */
		#define CONTROL_LINE_IN_PARITYERROR  (1 << 5)

		/** Mask for use with the a NOTIF_SerialState class specific notification from the device to the host,
		 *  to indicate that a data overrun error has occurred on the virtual serial port.
		 */
		#define CONTROL_LINE_IN_OVERRUNERROR (1 << 6)
		
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
		
		/** Type define for a CDC notification, sent to the host via the CDC notification endpoint to indicate a
		 *  change in the device state asynchronously.
		 */
		typedef struct
		{
			uint8_t  NotificationType; /**< Notification type, a mask of REQDIR_*, REQTYPE_* and REQREC_* constants
			                            *   from the library StdRequestType.h header
			                            */
			uint8_t  Notification; /**< Notification value, a NOTIF_* constant */
			uint16_t wValue; /**< Notification wValue, notification-specific */
			uint16_t wIndex; /**< Notification wIndex, notification-specific */
			uint16_t wLength; /**< Notification wLength, notification-specific */
		} USB_Notification_Header_t;
		
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
		enum USBtoSerial_StatusCodes_t
		{
			Status_USBNotReady    = 0, /**< USB is not ready (disconnected from a USB host) */
			Status_USBEnumerating = 1, /**< USB interface is enumerating */
			Status_USBReady       = 2, /**< USB interface is connected and ready */
		};
		
	/* Tasks: */
		TASK(CDC_Task);

	/* Function Prototypes: */
		void EVENT_USB_Connect(void);
		void EVENT_USB_Disconnect(void);
		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);

		void ReconfigureUSART(void);
		void UpdateStatus(uint8_t CurrentStatus);

#endif
