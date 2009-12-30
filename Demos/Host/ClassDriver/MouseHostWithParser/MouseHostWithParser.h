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
 *  Header file for MouseHost.c.
 */

#ifndef _MOUSE_HOST_H_
#define _MOUSE_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
		#include <avr/power.h>
		#include <stdio.h>

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/Misc/TerminalCodes.h>
		#include <LUFA/Drivers/Peripheral/SerialStream.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/HID.h>
		
	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY        LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING     (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY           (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR           (LEDS_LED1 | LEDS_LED3)

		/** HID Report Descriptor Usage Page value for a toggle button */
		#define USAGE_PAGE_BUTTON           0x09

		/** HID Report Descriptor Usage Page value for a Generic Desktop Control */
		#define USAGE_PAGE_GENERIC_DCTRL    0x01

		/** HID Report Descriptor Usage for a Mouse */
		#define USAGE_MOUSE                 0x02

		/** HID Report Descriptor Usage value for a X axis movement */
		#define USAGE_X                     0x30

		/** HID Report Descriptor Usage value for a Y axis movement */
		#define USAGE_Y                     0x31
		
		/** HID Report Descriptor Usage value for a Scroll Wheel movement */
		#define USAGE_SCROLL_WHEEL          0x38

	/* Function Prototypes: */
		void SetupHardware(void);
	
		void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
		void EVENT_USB_Host_DeviceAttached(void);
		void EVENT_USB_Host_DeviceUnattached(void);
		void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode);
		void EVENT_USB_Host_DeviceEnumerationComplete(void);
		
		bool CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* CurrentItem);
		
#endif
