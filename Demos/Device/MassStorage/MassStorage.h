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
 *  Header file for MassStorage.c.
 */

#ifndef _MASS_STORAGE_H_
#define _MASS_STORAGE_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>

		#include "Descriptors.h"

		#include "Lib/SCSI.h"
		#include "Lib/DataflashManager.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Board/Buttons.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/Device/MassStorage.h>

	/* Macros: */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)
		#define LEDMASK_USB_BUSY          LEDS_LED2
		
		#define TOTAL_LUNS                2
		
		/** Blocks in each LUN, calculated from the total capacity divided by the total number of Logical Units in the device. */
		#define LUN_MEDIA_BLOCKS         (VIRTUAL_MEMORY_BLOCKS / TOTAL_LUNS)
		
	/* Function Prototypes: */
		void SetupHardware(void);

		void EVENT_USB_Connect(void);
		void EVENT_USB_Disconnect(void);
		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);

		bool CALLBACK_USB_MS_SCSICommandReceived(USB_ClassInfo_MS_t* MSInterfaceInfo);

#endif
