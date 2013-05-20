/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the MIDIHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MIDIHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "MIDI Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		MIDIHost_Task();

		USB_USBTask();
	}
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
	Serial_Init(9600, false);
	LEDs_Init();
	Buttons_Init();
	Joystick_Init();
	USB_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "Device Attached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "\r\nDevice Unattached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	puts_P(PSTR("Getting Config Data.\r\n"));

	uint8_t ErrorCode;

	/* Get and process the configuration descriptor data */
	if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
	{
		if (ErrorCode == ControlError)
		  puts_P(PSTR(ESC_FG_RED "Control Error (Get Configuration).\r\n"));
		else
		  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

		printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
	if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"
		                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	puts_P(PSTR("MIDI Device Enumerated.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_Disable();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                            const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Task to read in note on/off messages from the attached MIDI device and print it to the serial port.
 *  When the board joystick or buttons are pressed, note on/off messages are sent to the attached device.
 */
void MIDIHost_Task(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	Pipe_SelectPipe(MIDI_DATA_IN_PIPE);
	Pipe_Unfreeze();

	if (Pipe_IsINReceived())
	{
		MIDI_EventPacket_t MIDIEvent;

		Pipe_Read_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

		if (!(Pipe_BytesInPipe()))
		  Pipe_ClearIN();

		bool NoteOnEvent  = (MIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON));
		bool NoteOffEvent = (MIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_OFF));

		if (NoteOnEvent || NoteOffEvent)
		{
			printf_P(PSTR("MIDI Note %s - Channel %d, Pitch %d, Velocity %d\r\n"), NoteOnEvent ? "On" : "Off",
																				   ((MIDIEvent.Data1 & 0x0F) + 1),
																				   MIDIEvent.Data2, MIDIEvent.Data3);
		}
	}

	Pipe_Freeze();

	Pipe_SelectPipe(MIDI_DATA_OUT_PIPE);
	Pipe_Unfreeze();

	if (Pipe_IsOUTReady())
	{
		uint8_t MIDICommand = 0;
		uint8_t MIDIPitch;

		static uint8_t PrevJoystickStatus;
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

		/* Check if a MIDI command is to be sent */
		if (MIDICommand)
		{
			MIDI_EventPacket_t MIDIEvent = (MIDI_EventPacket_t)
				{
					.Event       = MIDI_EVENT(0, MIDICommand),

					.Data1       = MIDICommand | Channel,
					.Data2       = MIDIPitch,
					.Data3       = MIDI_STANDARD_VELOCITY,
				};

			/* Write the MIDI event packet to the pipe */
			Pipe_Write_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

			/* Send the data in the pipe to the device */
			Pipe_ClearOUT();
		}

		Pipe_Freeze();

		/* Save previous joystick value for next joystick change detection */
		PrevJoystickStatus = JoystickStatus;
	}
}

