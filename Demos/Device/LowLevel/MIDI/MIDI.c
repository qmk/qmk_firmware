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
 *  Main source file for the MIDI input demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "MIDI.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		MIDI_Task();
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
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

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
void EVENT_USB_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and MIDI management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the MIDI management task started.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Setup MIDI stream endpoints */
	Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, MIDI_STREAM_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, MIDI_STREAM_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Task to handle the generation of MIDI note change events in response to presses of the board joystick, and send them
 *  to the host.
 */
void MIDI_Task(void)
{
	static uint8_t PrevJoystickStatus;

	/* Select the MIDI IN stream */
	Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPNUM);

	/* Check if endpoint is ready to be written to */
	if (Endpoint_IsINReady())
	{
		/* Get current joystick mask, XOR with previous to detect joystick changes */
		uint8_t JoystickStatus  = Joystick_GetStatus();
		uint8_t JoystickChanges = (JoystickStatus ^ PrevJoystickStatus);
		
		/* Get board button status - if pressed use channel 10 (percussion), otherwise use channel 1 */
		uint8_t Channel = ((Buttons_GetStatus() & BUTTONS_BUTTON1) ? MIDI_CHANNEL(10) : MIDI_CHANNEL(1));

		if (JoystickChanges & JOY_LEFT)
		  SendMIDINoteChange(0x3C, (JoystickStatus & JOY_LEFT), 0, Channel);

		if (JoystickChanges & JOY_UP)
		  SendMIDINoteChange(0x3D, (JoystickStatus & JOY_UP), 0, Channel);

		if (JoystickChanges & JOY_RIGHT)
		  SendMIDINoteChange(0x3E, (JoystickStatus & JOY_RIGHT), 0, Channel);

		if (JoystickChanges & JOY_DOWN)
		  SendMIDINoteChange(0x3F, (JoystickStatus & JOY_DOWN), 0, Channel);

		if (JoystickChanges & JOY_PRESS)
		  SendMIDINoteChange(0x3B, (JoystickStatus & JOY_PRESS), 0, Channel);

		/* Save previous joystick value for next joystick change detection */
		PrevJoystickStatus = JoystickStatus;
	}

	/* Select the MIDI OUT stream */
	Endpoint_SelectEndpoint(MIDI_STREAM_OUT_EPNUM);

	/* Check if endpoint is ready to be read from, if so discard its (unused) data */
	if (Endpoint_IsOUTReceived())
	  Endpoint_ClearOUT();
}

/** Sends a MIDI note change event (note on or off) to the MIDI output jack, on the given virtual cable ID and channel.
 *
 *  \param Pitch    Pitch of the note to turn on or off
 *  \param OnOff    Set to true if the note is on (being held down), or false otherwise
 *  \param CableID  ID of the virtual cable to send the note change to
 *  \param Channel  MIDI channel number to send the note change event to
 */
void SendMIDINoteChange(const uint8_t Pitch, const bool OnOff, const uint8_t CableID, const uint8_t Channel)
{
	/* Wait until endpoint ready for more data */
	while (!(Endpoint_IsReadWriteAllowed()));

	/* Check if the message should be a Note On or Note Off command */
	uint8_t Command = ((OnOff)? MIDI_COMMAND_NOTE_ON : MIDI_COMMAND_NOTE_OFF);

	/* Write the Packet Header to the endpoint */
	Endpoint_Write_Byte((CableID << 4) | (Command >> 4));

	/* Write the Note On/Off command with the specified channel, pitch and velocity */
	Endpoint_Write_Byte(Command | Channel);
	Endpoint_Write_Byte(Pitch);
	Endpoint_Write_Byte(MIDI_STANDARD_VELOCITY);
	
	/* Send the data in the endpoint to the host */
	Endpoint_ClearIN();
}
