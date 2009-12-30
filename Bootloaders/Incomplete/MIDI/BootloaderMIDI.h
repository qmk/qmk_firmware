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
 *  Header file for AudioOutput.c.
 */
 
#ifndef _AUDIO_OUTPUT_H_
#define _AUDIO_OUTPUT_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/boot.h>
		#include <avr/power.h>
		#include <stdbool.h>

		#include "Descriptors.h"
				
		#include <LUFA/Version.h>
		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/USB/USB.h>

   /* Macros: */
		/** MIDI command for a note on (activation) event */
		#define MIDI_COMMAND_NOTE_ON      0x90

		/** MIDI command for a note off (deactivation) event */
		#define MIDI_COMMAND_NOTE_OFF     0x80

		#define MIDI_CONTROL_CHANNEL      9
		#define MIDI_DATA_CHANNEL         0
		#define CONTROL_DEVICE_READY      0xD1
		#define CONTROL_ENTER_PROG_MODE   0xDC
		#define CONTROL_LEAVE_PROG_MODE   0xDF
		#define CONTROL_GET_PAGE_SIZE     0x01
	
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED1

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED2 | LEDS_LED3)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED2 | LEDS_LED4)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED1 | LEDS_LED3)

	/* Type Defines: */
		/** Type define for a USB MIDI event packet, used to encapsulate sent and received MIDI messages from a USB MIDI interface. */
		typedef struct
		{
			unsigned char Command     : 4; /**< MIDI command being sent or received in the event packet */
			unsigned char CableNumber : 4; /**< Virtual cable number of the event being sent or received in the given MIDI interface */
			
			uint8_t Data1; /**< First byte of data in the MIDI event */
			uint8_t Data2; /**< Second byte of data in the MIDI event */
			uint8_t Data3; /**< Third byte of data in the MIDI event */		
		} USB_MIDI_EventPacket_t;
		
   /* Function Prototypes: */
		void SetupHardware(void);
		void MIDI_Task(void);
   
		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		
#endif
