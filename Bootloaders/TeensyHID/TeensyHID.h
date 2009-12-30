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
 *  Header file for TeensyHID.c.
 */
 
#ifndef _TEENSYHID_H_
#define _TEENSYHID_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/power.h>
		#include <stdbool.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>
		
	/* Macros: */
		/** HID Class specific request to send the next HID report to the device. */
		#define REQ_SetReport             0x09
		
		/** Teensy Bootloader special address to start the user application */
		#define TEENSY_STARTAPPLICATION   0xFFFF
		
	/* Function Prototypes: */
		void SetupHardware(void);

		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);
		
#endif
