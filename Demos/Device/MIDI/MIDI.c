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

#include "MIDI.h"

USB_ClassInfo_MIDI_t Keyboard_MIDI_Interface =
	{
		.InterfaceNumber       = 0,

		.DataINEndpointNumber  = MIDI_STREAM_IN_EPNUM,
		.DataINEndpointSize    = MIDI_STREAM_EPSIZE,

		.DataOUTEndpointNumber = MIDI_STREAM_OUT_EPNUM,
		.DataOUTEndpointSize   = MIDI_STREAM_EPSIZE,
	};
	
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	for (;;)
	{
		CheckJoystickMovement();
	
		USB_USBTask();
	}
}

void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
	
	/* Hardware Initialization */
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	USB_Init();
}

void CheckJoystickMovement(void)
{
	static uint8_t PrevJoystickStatus;

	uint8_t MIDICommand = 0;
	uint8_t MIDIPitch;
	
	/* Get current joystick mask, XOR with previous to detect joystick changes */
	uint8_t JoystickStatus  = Joystick_GetStatus();
	uint8_t JoystickChanges = (JoystickStatus ^ PrevJoystickStatus);
		
	/* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
	uint8_t Channel = ((Buttons_GetStatus() & BUTTONS_BUTTON1) ? MIDI_CHANNEL(10) : MIDI_CHANNEL(1));

	if (JoystickChanges & JOY_LEFT)
	{
		MIDICommand = ((JoystickStatus & JOY_LEFT)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
		MIDIPitch   = 0x3C;
	}

	if (JoystickChanges & JOY_UP)
	{
		MIDICommand = ((JoystickStatus & JOY_UP)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
		MIDIPitch   = 0x3D;
	}

	if (JoystickChanges & JOY_RIGHT)
	{
		MIDICommand = ((JoystickStatus & JOY_RIGHT)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
		MIDIPitch   = 0x3E;
	}
	
	if (JoystickChanges & JOY_DOWN)
	{
		MIDICommand = ((JoystickStatus & JOY_DOWN)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
		MIDIPitch   = 0x3F;
	}

	if (JoystickChanges & JOY_PRESS)
	{
		MIDICommand = ((JoystickStatus & JOY_PRESS)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);
		MIDIPitch   = 0x3B;
	}
	
	if (MIDICommand)
	{
		USB_MIDI_EventPacket_t MIDIEvent = (USB_MIDI_EventPacket_t)
			{
				.CableNumber = 0,
				.Command     = MIDICommand,
				
				.Data1       = (MIDICommand << 4) | Channel,
				.Data2       = MIDIPitch,
				.Data3       = MIDI_STANDARD_VELOCITY,			
			};
			
		USB_MIDI_SendEventPacket(&Keyboard_MIDI_Interface, &MIDIEvent);
	}

	PrevJoystickStatus = JoystickStatus;
}

void EVENT_USB_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
	
	if (!(USB_MIDI_ConfigureEndpoints(&Keyboard_MIDI_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}
