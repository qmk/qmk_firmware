/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
		#include <avr/pgmspace.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>

		#include "Descriptors.h"
		#include "Config/AppConfig.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Platform/Platform.h>

	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

		/** Scale factor used to convert the floating point frequencies and ratios into a fixed point number */
		#define SCALE_FACTOR               65536

		/** Base (lowest) allowable MIDI note frequency */
		#define BASE_FREQUENCY             27.5

		/** Ratio between each note in an octave */
		#define NOTE_OCTIVE_RATIO          1.05946

		/** Lowest valid MIDI pitch index */
		#define BASE_PITCH_INDEX           21

		/** Number of samples in the virtual sample table (can be expanded to lower maximum frequency, but allow for
		 *  more simultaneous notes due to the reduced amount of processing time needed when the samples are spaced out)
		 */
		#define VIRTUAL_SAMPLE_TABLE_SIZE  512

		/** Sample table increments per period for the base MIDI note frequency */
		#define BASE_INCREMENT             (((F_CPU / VIRTUAL_SAMPLE_TABLE_SIZE / 2) / BASE_FREQUENCY))

	/* Type Defines: */
		typedef struct
		{
			uint8_t  LRUAge;
			uint8_t  Pitch;
			uint32_t TableIncrement;
			uint32_t TablePosition;
		} DDSNoteData;

	/* Function Prototypes: */
		void SetupHardware(void);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_UnhandledControlRequest(void);

#endif

