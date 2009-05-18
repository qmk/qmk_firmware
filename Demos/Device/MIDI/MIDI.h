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
 *  Header file for AudioOutput.c.
 */
 
#ifndef _AUDIO_OUTPUT_H_
#define _AUDIO_OUTPUT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <stdbool.h>

		#include "Descriptors.h"
				
		#include <LUFA/Version.h>                            // Library Version Information
		#include <LUFA/Drivers/USB/USB.h>                    // USB Functionality
		#include <LUFA/Drivers/Board/Joystick.h>             // Joystick driver
		#include <LUFA/Drivers/Board/LEDs.h>                 // LEDs driver
		#include <LUFA/Drivers/Board/Buttons.h>              // Board Buttons driver
		#include <LUFA/Scheduler/Scheduler.h>                // Simple scheduler for task management

   /* Macros: */
		/** MIDI command for a note on (activation) event */
		#define MIDI_COMMAND_NOTE_ON         0x90

		/** MIDI command for a note off (deactivation) event */
		#define MIDI_COMMAND_NOTE_OFF        0x80

		/** Standard key press velocity value used for all note events, as no pressure sensor is mounted */
		#define MIDI_STANDARD_VELOCITY       64
		
		/** Convenience macro. MIDI channels are numbered from 1-10 (natural numbers) however the logical channel
		 *  addresses are zero-indexed. This converts a natural MIDI channel number into the logical channel address.
		 *
		 *  \param channel  MIDI channel number to address
		 */
		#define MIDI_CHANNEL(channel)        (channel - 1)

	/* Enums: */
		/** Enum for the possible status codes for passing to the UpdateStatus() function. */
		enum MIDI_StatusCodes_t
		{
			Status_USBNotReady    = 0, /**< USB is not ready (disconnected from a USB host) */
			Status_USBEnumerating = 1, /**< USB interface is enumerating */
			Status_USBReady       = 2, /**< USB interface is connected and ready */
		};

	/* Task Definitions: */
		TASK(USB_MIDI_Task);

   /* Function Prototypes: */
		void EVENT_USB_Connect(void);
		void EVENT_USB_Disconnect(void);
		void EVENT_USB_ConfigurationChanged(void);

		void SendMIDINoteChange(const uint8_t Pitch, const bool OnOff,
		                        const uint8_t CableID, const uint8_t Channel);		
		void UpdateStatus(uint8_t CurrentStatus);
		
#endif
