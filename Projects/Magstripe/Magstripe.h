/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
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
 *  Header file for Magstripe.c.
 */

#ifndef _MAGSTRIPE_H_
#define _MAGSTRIPE_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>

		#include "Descriptors.h"
		#include "Lib/MagstripeHW.h"
		#include "Lib/CircularBitBuffer.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/HID.h>

	/* Macros: */
		/** Total number of tracks which can be read from the card, between 1 and 3. */
		#define TOTAL_TRACKS       3
	
		/** HID keyboard keycode to indicate that no is currently pressed. */
		#define KEY_NONE           0
	
		/** HID keyboard keycode to indicate that the "1" key is currently pressed. */
		#define KEY_1              30

		/** HID keyboard keycode to indicate that the "0" key is currently pressed. */
		#define KEY_0              39

		/** HID keyboard keycode to indicate that the enter key is currently pressed. */
		#define KEY_ENTER          40
	
	/* Function Prototypes: */
		void SetupHardware(void);
		void ReadMagstripeData(void);
		
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
                                                 const uint8_t ReportType, void* ReportData, uint16_t* ReportSize);
		void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID, 
		                                          const void* ReportData, const uint16_t ReportSize);
														  
#endif
