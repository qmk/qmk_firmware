/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for Mouse.c.
 */

#ifndef _MOUSE_H_
#define _MOUSE_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <stdbool.h>
		#include <string.h>
		
		#include "Descriptors.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Board/Buttons.h>

	/* Macros: */
		/** Idle period indicating that reports should be sent only when the inputs have changed */
		#define HID_IDLE_CHANGESONLY      0
	
		/** HID Class specific request to get the next HID report from the device. */
		#define REQ_GetReport             0x01

		/** HID Class specific request to get the idle timeout period of the device. */
		#define REQ_GetIdle               0x02

		/** HID Class specific request to send the next HID report to the device. */
		#define REQ_SetReport             0x09

		/** HID Class specific request to set the idle timeout period of the device. */
		#define REQ_SetIdle               0x0A

		/** HID Class specific request to get the current HID protocol in use, either report or boot. */
		#define REQ_GetProtocol           0x03

		/** HID Class specific request to set the current HID protocol in use, either report or boot. */
		#define REQ_SetProtocol           0x0B

		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)
		
	/* Type Defines: */
		/** Type define for the mouse HID report structure, for creating and sending HID reports to the host PC.
		 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
		 */
		typedef struct
		{
			uint8_t Button; /**< Bit mask of the currently pressed mouse buttons */
			int8_t  X; /**< Current mouse delta X movement, as a signed 8-bit integer */
			int8_t  Y; /**< Current mouse delta Y movement, as a signed 8-bit integer */
		} USB_MouseReport_Data_t;
			
	/* Function Prototypes: */
		void SetupHardware(void);
		void Mouse_Task(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		void CreateMouseReport(USB_MouseReport_Data_t* ReportData);

#endif
