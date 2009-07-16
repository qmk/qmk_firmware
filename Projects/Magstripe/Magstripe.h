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
		#include <avr/power.h>

		#include "Descriptors.h"
		#include "Lib/MagstripeHW.h"
		#include "Lib/CircularBitBuffer.h"

		#include <LUFA/Version.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/HID.h>

	/* Macros: */
		/** HID keyboard keycode to indicate that no is currently pressed. */
		#define KEY_NONE           0
	
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
		void SetupHardware(void);
		void ReadMagstripeData(void);
		
		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);

		uint16_t CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
		                                             void* ReportData);
		void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID,
                                                  const void* ReportData, const uint16_t ReportSize);
														  
#endif
