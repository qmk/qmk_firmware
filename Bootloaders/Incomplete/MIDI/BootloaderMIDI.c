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
 *  Main source file for the MIDI bootloader. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "BootloaderMIDI.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
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
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and MIDI management tasks.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the MIDI management task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup MIDI stream endpoints */
	if (!(Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_OUT, MIDI_STREAM_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}	
	
	if (!(Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_IN, MIDI_STREAM_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Task to handle the generation of MIDI note change events in response to presses of the board joystick, and send them
 *  to the host.
 */
void MIDI_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Select the MIDI OUT stream */
	Endpoint_SelectEndpoint(MIDI_STREAM_OUT_EPNUM);

	if (Endpoint_IsOUTReceived())
	{
		USB_MIDI_EventPacket_t InPacket;
		Endpoint_Read_Stream_LE(&InPacket, sizeof(InPacket));
			
		LEDs_SetAllLEDs(InPacket.Data2 > 64 ? LEDS_LED1 : LEDS_LED2);	
		Endpoint_ClearOUT();

		uint8_t Channel = InPacket.Data1;
		uint8_t Data    = ((InPacket.Data2 & 0x7F) | ((InPacket.Data3 == 64) ? 0x80 : 0x00));
	
		if ((Channel == MIDI_CONTROL_CHANNEL) && (Data == CONTROL_ENTER_PROG_MODE))
		{
			USB_MIDI_EventPacket_t MIDIIn = (USB_MIDI_EventPacket_t)
				{
					.CableNumber = 0,
					.Command     = (MIDI_COMMAND_NOTE_ON >> 4),
					
					.Data1       = MIDI_COMMAND_NOTE_ON | MIDI_CONTROL_CHANNEL,
					.Data2       = CONTROL_DEVICE_READY,
					.Data3       = 32,			
				};
				
			Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPNUM);
			Endpoint_Write_Stream_LE(&MIDIIn, sizeof(MIDIIn));
			Endpoint_ClearIN();
		}
	}
}
