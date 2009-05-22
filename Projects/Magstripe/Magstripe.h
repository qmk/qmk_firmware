/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
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
 *  Header file for Magstripe.c.
 */

#ifndef _MAGSTRIPE_H_
#define _MAGSTRIPE_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/interrupt.h>
		#include <avr/power.h>
		#include <stdbool.h>
		#include <string.h>

		#include "Descriptors.h"
		#include "MagstripeHW.h"
		#include "CircularBitBuffer.h"

		#include <LUFA/Version.h>                    // Library Version Information
		#include <LUFA/Drivers/USB/USB.h>            // USB Functionality
		#include <LUFA/Scheduler/Scheduler.h>        // Simple scheduler for task management

		
	/* Task Definitions: */
		/** Task definition for the keyboard and magnetic card reading task. */
		TASK(USB_Keyboard_Report);
		
		TASK(Magstripe_Read);

	/* Macros: */
		/** HID Class Specific Request to get the current HID report from the device. */
		#define REQ_GetReport      0x01

		/** HID Class Specific Request to get the current device idle count. */
		#define REQ_GetIdle        0x02

		/** HID Class Specific Request to set the current HID report to the device. */
		#define REQ_SetReport      0x09

		/** HID Class Specific Request to set the device's idle count. */
		#define REQ_SetIdle        0x0A

		/** HID Class Specific Request to get the current HID report protocol mode. */
		#define REQ_GetProtocol    0x03

		/** HID Class Specific Request to set the current HID report protocol mode. */
		#define REQ_SetProtocol    0x0B
		
		/** HID keyboard keycode to indicate that the "1" key is currently pressed. */
		#define KEY_1              30

		/** HID keyboard keycode to indicate that the "0" key is currently pressed. */
		#define KEY_0              39

		/** HID keyboard keycode to indicate that the enter key is currently pressed. */
		#define KEY_ENTER          40
		
	/* Type Defines: */
		/** Type define for the keyboard report structure. This structure matches the report layout
		 *  given to the host in the HID Report descriptor, as well as matches the boot protocol report
		 *  structure. This means that this one report structure can be used in both Report and Boot Protocol
		 *  modes. */
		typedef struct
		{
			uint8_t Modifier; /**< Modifier byte, indicating pressed modifier keys such as CTRL or ALT */
			uint8_t Reserved; /**< Reserved for OEM use, always set to 0 */
			uint8_t KeyCode; /**< Key code array for pressed keys - up to six can be given simultaneously */
		} USB_KeyboardReport_Data_t;
	
	/* Function Prototypes: */
		void EVENT_USB_Connect(void);
		void EVENT_USB_Disconnect(void);
		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);
	
		bool GetNextReport(USB_KeyboardReport_Data_t* ReportData);
		
#endif
