/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the AudioInputHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "AudioInputHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Audio Input Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
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
	puts_P(PSTR(ESC_FG_GREEN "Device Unattached.\r\n" ESC_FG_WHITE));
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

	if ((ErrorCode = USB_Host_SetInterfaceAltSetting(StreamingInterfaceIndex,
	                                                 StreamingInterfaceAltSetting)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Could not set alternative streaming interface setting.\r\n"
		                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_ENDPOINT),
			.bRequest      = AUDIO_REQ_SetCurrent,
			.wValue        = (AUDIO_EPCONTROL_SamplingFreq << 8),
			.wIndex        = StreamingEndpointAddress,
			.wLength       = sizeof(USB_Audio_SampleFreq_t),
		};

	USB_Audio_SampleFreq_t SampleRate = AUDIO_SAMPLE_FREQ(48000);

	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	/* Set the sample rate on the streaming interface endpoint */
	if ((ErrorCode = USB_Host_SendControlRequest(&SampleRate)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Could not set requested Audio sample rate.\r\n"
		                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	/* Sample reload timer initialization */
	TIMSK0  = (1 << OCIE0A);
	OCR0A   = ((F_CPU / 8 / 48000) - 1);
	TCCR0A  = (1 << WGM01);  // CTC mode
	TCCR0B  = (1 << CS01);   // Fcpu/8 speed

	/* Set speaker as output */
	DDRC   |= (1 << 6);

	/* PWM speaker timer initialization */
	TCCR3A  = ((1 << WGM30) | (1 << COM3A1) | (1 << COM3A0)); // Set on match, clear on TOP
	TCCR3B  = ((1 << WGM32) | (1 << CS30));  // Fast 8-Bit PWM, F_CPU speed

	puts_P(PSTR("Microphone Enumerated.\r\n"));
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

/** ISR to handle the reloading of the PWM timer with the next sample. */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	uint8_t PrevPipe = Pipe_GetCurrentPipe();

	Pipe_SelectPipe(AUDIO_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Check if the current pipe can be read from (contains a packet) and the device is sending data */
	if (Pipe_IsINReceived())
	{
		/* Retrieve the signed 16-bit audio sample, convert to 8-bit */
		int8_t Sample_8Bit = (Pipe_Read_16_LE() >> 8);

		/* Check to see if the bank is now empty */
		if (!(Pipe_IsReadWriteAllowed()))
		{
			/* Acknowledge the packet, clear the bank ready for the next packet */
			Pipe_ClearIN();
		}

		/* Load the sample into the PWM timer channel */
		OCR3A = (Sample_8Bit ^ (1 << 7));

		uint8_t LEDMask = LEDS_NO_LEDS;

		/* Turn on LEDs as the sample amplitude increases */
		if (Sample_8Bit > 16)
		  LEDMask = (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4);
		else if (Sample_8Bit > 8)
		  LEDMask = (LEDS_LED1 | LEDS_LED2 | LEDS_LED3);
		else if (Sample_8Bit > 4)
		  LEDMask = (LEDS_LED1 | LEDS_LED2);
		else if (Sample_8Bit > 2)
		  LEDMask = (LEDS_LED1);

		LEDs_SetAllLEDs(LEDMask);
	}

	Pipe_Freeze();
	Pipe_SelectPipe(PrevPipe);
}

