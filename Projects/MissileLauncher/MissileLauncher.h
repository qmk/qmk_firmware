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
 *  Header file for MissileLauncher.c.
 */

#ifndef _MISSILELAUNCHER_HOST_H_
#define _MISSILELAUNCHER_HOST_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/pgmspace.h>
		#include <avr/interrupt.h>
		#include <avr/power.h>
		#include <string.h>
		#include <stdio.h>

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/Buttons.h>
		#include <LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		
		#include "ConfigDescriptor.h"
		
	/* Macros: */
		/** Pipe number for the HID data IN pipe */
		#define HID_DATA_IN_PIPE          1
		
		/** Pipe number for the HID data OUT pipe */
		#define HID_DATA_OUT_PIPE         2

		/** HID Class specific request to send a HID report to the device. */
		#define REQ_SetReport             0x09

		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)
		
		/** Size of the Launcher report command buffer */
		#define LAUNCHER_CMD_BUFFER_SIZE 64
		
	/* Function Prototypes: */
		void SetupHardware(void);

		void Read_Joystick_Status(void);
        void Send_Command_Report(uint8_t* Report, uint16_t ReportSize);
        void Send_Command(uint8_t* Command);

		void HID_Host_Task(void);

		void EVENT_USB_Host_HostError(const uint8_t ErrorCode);
		void EVENT_USB_Host_DeviceAttached(void);
		void EVENT_USB_Host_DeviceUnattached(void);
		void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode);
		void EVENT_USB_Host_DeviceEnumerationComplete(void);

		void DiscardNextReport(void);
		void WriteNextReport(uint8_t* ReportOUTData, uint16_t ReportLength);
		
#endif
