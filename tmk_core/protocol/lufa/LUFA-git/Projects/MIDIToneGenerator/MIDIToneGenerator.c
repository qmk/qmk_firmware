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
 *  Main source file for the MIDI demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MIDIToneGenerator.h"

/** LUFA MIDI Class driver interface configuration and state information. This structure is
 *  passed to all MIDI Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MIDI_Device_t Keyboard_MIDI_Interface =
	{
		.Config =
			{
				.StreamingInterfaceNumber = INTERFACE_ID_AudioStream,
				.DataINEndpoint           =
					{
						.Address          = MIDI_STREAM_IN_EPADDR,
						.Size             = MIDI_STREAM_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint           =
					{
						.Address          = MIDI_STREAM_OUT_EPADDR,
						.Size             = MIDI_STREAM_EPSIZE,
						.Banks            = 1,
					},
			},
	};

/** 8-bit 256 entry Sine Wave lookup table */
static const uint8_t SineTable[256] =
{
	128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171, 174,
	176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216,
	218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245,
	246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247,
	246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220,
	218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179,
	176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134, 131,
	128, 124, 121, 118, 115, 112, 109, 106, 103,  99,  96,  93,  90,  87,  84,  81,
	 79,  76,  73,  70,  67,  64,  62,  59,  56,  54,  51,  49,  46,  44,  42,  39,
	 37,  35,  33,  31,  29,  27,  25,  23,  21,  19,  18,  16,  15,  13,  12,  10,
	  9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   1,   1,   2,   3,   3,   4,   5,   6,   7,   8,
	  9,  10,  12,  13,  15,  16,  18,  19,  21,  23,  25,  27,  29,  31,  33,  35,
	 37,  39,  42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,
	 79,  81,  84,  87,  90,  93,  96,  99, 103, 106, 109, 112, 115, 118, 121, 124,
};

/** Array of structures describing each note being generated */
static DDSNoteData NoteData[MAX_SIMULTANEOUS_NOTES];


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		MIDI_EventPacket_t ReceivedMIDIEvent;
		if (MIDI_Device_ReceiveEventPacket(&Keyboard_MIDI_Interface, &ReceivedMIDIEvent))
		{
			if ((ReceivedMIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON)) && ((ReceivedMIDIEvent.Data1 & 0x0F) == 0))
			{
				DDSNoteData* LRUNoteStruct = &NoteData[0];

				/* Find a free entry in the note table to use for the note being turned on */
				for (uint8_t i = 0; i < MAX_SIMULTANEOUS_NOTES; i++)
				{
					/* Check if the note is unused */
					if (!(NoteData[i].Pitch))
					{
						/* If a note is unused, it's age is essentially infinite - always prefer unused note entries */
						LRUNoteStruct = &NoteData[i];
						break;
					}
					else if (NoteData[i].LRUAge >= LRUNoteStruct->LRUAge)
					{
						/* If an older entry that the current entry has been found, prefer overwriting that one */
						LRUNoteStruct = &NoteData[i];
					}

					NoteData[i].LRUAge++;
				}

				/* Update the oldest note entry with the new note data and reset its age */
				LRUNoteStruct->Pitch          = ReceivedMIDIEvent.Data2;
				LRUNoteStruct->TableIncrement = (uint32_t)(BASE_INCREMENT * SCALE_FACTOR) +
						                         ((uint32_t)(BASE_INCREMENT * NOTE_OCTIVE_RATIO * SCALE_FACTOR) *
						                          (ReceivedMIDIEvent.Data2 - BASE_PITCH_INDEX));
				LRUNoteStruct->TablePosition  = 0;
				LRUNoteStruct->LRUAge         = 0;

				/* Turn on indicator LED to indicate note generation activity */
				LEDs_SetAllLEDs(LEDS_LED1);
			}
			else if ((ReceivedMIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_OFF)) && ((ReceivedMIDIEvent.Data1 & 0x0F) == 0))
			{
				bool FoundActiveNote = false;

				/* Find the note in the note table to turn off */
				for (uint8_t i = 0; i < MAX_SIMULTANEOUS_NOTES; i++)
				{
					if (NoteData[i].Pitch == ReceivedMIDIEvent.Data2)
					  NoteData[i].Pitch = 0;
					else if (NoteData[i].Pitch)
					  FoundActiveNote   = true;
				}

				/* If all notes off, turn off the indicator LED */
				if (!(FoundActiveNote))
				  LEDs_SetAllLEDs(LEDS_NO_LEDS);
			}
		}

		MIDI_Device_USBTask(&Keyboard_MIDI_Interface);
		USB_USBTask();
	}
}

/** ISR to handle the reloading of the PWM timer with the next sample. */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	uint16_t MixedSample = 0;

	/* Sum together all the active notes to form a single sample */
	for (uint8_t i = 0; i < MAX_SIMULTANEOUS_NOTES; i++)
	{
		/* A non-zero pitch indicates the note is active */
		if (NoteData[i].Pitch)
		{
			/* Use the top 8 bits of the table position as the sample table index */
			uint8_t TableIndex = (NoteData[i].TablePosition >> 24);

			/* Add the new tone sample to the accumulator and increment the table position */
			MixedSample += SineTable[TableIndex];
			NoteData[i].TablePosition += NoteData[i].TableIncrement;
		}
	}

	/* Output clamped mixed sample value to the PWM */
	OCR3A = (MixedSample <= 0xFF) ? MixedSample : 0xFF;
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#endif

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();

	/* Sample reload timer initialization */
	TIMSK0  = (1 << OCIE0A);
	OCR0A   = (VIRTUAL_SAMPLE_TABLE_SIZE / 8);
	TCCR0A  = (1 << WGM01);  // CTC mode
	TCCR0B  = (1 << CS01);   // Fcpu/8 speed

	/* Set speaker as output */
	DDRC |= (1 << 6);

	/* PWM speaker timer initialization */
	TCCR3A  = ((1 << WGM31) | (1 << COM3A1) | (1 << COM3A0)); // Set on match, clear on TOP
	TCCR3B  = ((1 << WGM32) | (1 << CS30));  // Fast 8-Bit PWM, Fcpu speed
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Set speaker as output */
	DDRC |= (1 << 6);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	/* Disable any notes currently being played */
	for (uint8_t i = 0; i < MAX_SIMULTANEOUS_NOTES; i++)
	  NoteData[i].Pitch = 0;

	/* Set speaker as input to reduce current draw */
	DDRC &= ~(1 << 6);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= MIDI_Device_ConfigureEndpoints(&Keyboard_MIDI_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request event. */
void EVENT_USB_Device_ControlRequest(void)
{
	MIDI_Device_ProcessControlRequest(&Keyboard_MIDI_Interface);
}

