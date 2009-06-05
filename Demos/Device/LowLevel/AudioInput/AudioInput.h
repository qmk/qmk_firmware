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
 *  Header file for AudioInput.c.
 */
 
#ifndef _AUDIO_INPUT_H_
#define _AUDIO_INPUT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>

		#include "Descriptors.h"
				
		#include <LUFA/Version.h>                      // Library Version Information
		#include <LUFA/Drivers/USB/USB.h>              // USB Functionality
		#include <LUFA/Drivers/Board/LEDs.h>           // LEDs driver
		#include <LUFA/Drivers/Peripheral/ADC.h>       // ADC driver
		#include <LUFA/Scheduler/Scheduler.h>          // Simple scheduler for task management

	/* Macros: */
		/** ADC channel number for the microphone input. */
		#define MIC_IN_ADC_CHANNEL               2
		
		/** Maximum ADC sample value for the microphone input. */
		#define SAMPLE_MAX_RANGE                 0xFFFF

		/** Maximum ADC range for the microphone input. */
		#define ADC_MAX_RANGE                    0x3FF

	/* Enums: */
		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum AudioInput_StatusCodes_t
		{
			Status_USBNotReady    = 0, /**< USB is not ready (disconnected from a USB host) */
			Status_USBEnumerating = 1, /**< USB interface is enumerating */
			Status_USBReady       = 2, /**< USB interface is connected and ready */
		};

	/* Task Definitions: */
		TASK(USB_Audio_Task);

	/* Function Prototypes: */
		void EVENT_USB_Connect(void);
		void EVENT_USB_Disconnect(void);
		void EVENT_USB_ConfigurationChanged(void);
		void EVENT_USB_UnhandledControlPacket(void);

		void UpdateStatus(uint8_t CurrentStatus);
		
#endif
