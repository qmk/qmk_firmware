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

#ifndef _SIDESHOW_H_
#define _SIDESHOW_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>

		#include "Descriptors.h"
		#include "SideshowCommands.h"

		#include <LUFA/Version.h>                    // Library Version Information
		#include <LUFA/Common/ButtLoadTag.h>         // PROGMEM tags readable by the ButtLoad project
		#include <LUFA/Drivers/USB/USB.h>            // USB Functionality
		#include <LUFA/Drivers/Board/HWB.h>          // HWB button driver
		#include <LUFA/Drivers/Board/LEDs.h>         // LEDs driver
		#include <LUFA/Drivers/Board/Dataflash.h>    // Dataflash chip driver
		#include <LUFA/Scheduler/Scheduler.h>        // Simple scheduler for task management
		#include <LUFA/Drivers/AT90USBXXX/Serial_Stream.h> // Serial stream driver

	/* Macros: */
		#define REQ_GetOSFeatureDescriptor        0x01
		
		#define EXTENDED_COMPAT_ID_DESCRIPTOR     0x0004

	/* Task Definitions: */
		TASK(USB_Sideshow);
		
	/* Event Handlers: */
		HANDLES_EVENT(USB_Connect);
		HANDLES_EVENT(USB_Disconnect);
		HANDLES_EVENT(USB_ConfigurationChanged);
		HANDLES_EVENT(USB_UnhandledControlPacket);

#endif
