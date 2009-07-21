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
 *  Header file for TeensyHID.c.
 */
 
#ifndef _TEENSYHID_H_
#define _TEENSYHID_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <util/delay.h>
		#include <stdbool.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/USB/USB.h>
		
	/* Preprocessor Checks: */
		#if !defined(__AVR_AT90USB162__)
			#error This bootloader is not compatible with the selected AVR model.
		#endif

	/* Macros: */
		/** HID Class specific request to send the next HID report to the device. */
		#define REQ_SetReport             0x09
		
		/** Teensy Bootloader special address to start the user application */
		#define TEENSY_STARTAPPLICATION   0xFFFF
		
	/* Function Prototypes: */
		void SetupHardware(void);

		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);
		
#endif
