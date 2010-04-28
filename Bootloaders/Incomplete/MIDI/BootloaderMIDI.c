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
	USB_Init();
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the MIDI management task started.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Setup MIDI stream endpoints */
	Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPNUM, EP_TYPE_BULK,
	                           ENDPOINT_DIR_OUT, MIDI_STREAM_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
	
	Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPNUM, EP_TYPE_BULK,
	                           ENDPOINT_DIR_IN, MIDI_STREAM_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
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
