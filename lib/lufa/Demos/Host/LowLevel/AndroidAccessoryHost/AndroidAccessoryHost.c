/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the AndroidAccessoryHost demo. This file contains the main tasks
 *  of the demo and is responsible for the initial application hardware configuration.
 */

#include "AndroidAccessoryHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Android Accessory Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		AndroidHost_Task();
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

/** Task to set the configuration of the attached device after it has been enumerated. */
void AndroidHost_Task(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select the data IN pipe */
	Pipe_SelectPipe(ANDROID_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Check to see if a packet has been received */
	if (Pipe_IsINReceived())
	{
		/* Re-freeze IN pipe after the packet has been received */
		Pipe_Freeze();

		/* Check if data is in the pipe */
		if (Pipe_IsReadWriteAllowed())
		{
			uint8_t NextReceivedByte = Pipe_Read_8();
			uint8_t LEDMask          = LEDS_NO_LEDS;

			if (NextReceivedByte & 0x01)
			  LEDMask |= LEDS_LED1;

			if (NextReceivedByte & 0x02)
			  LEDMask |= LEDS_LED2;

			if (NextReceivedByte & 0x04)
			  LEDMask |= LEDS_LED3;

			if (NextReceivedByte & 0x08)
			  LEDMask |= LEDS_LED4;

			LEDs_SetAllLEDs(LEDMask);
		}
		else
		{
			/* Clear the pipe after all data in the packet has been read, ready for the next packet */
			Pipe_ClearIN();
		}
	}

	/* Re-freeze IN pipe after use */
	Pipe_Freeze();
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
	puts_P(PSTR("Getting Device Data.\r\n"));

	/* Get and process the configuration descriptor data */
	uint8_t ErrorCode = ProcessDeviceDescriptor();

	bool RequiresModeSwitch = (ErrorCode == NonAccessoryModeAndroidDevice);

	/* Error out if the device is not an Android device or an error occurred */
	if ((ErrorCode != AccessoryModeAndroidDevice) && (ErrorCode != NonAccessoryModeAndroidDevice))
	{
		if (ErrorCode == ControlError)
		  puts_P(PSTR(ESC_FG_RED "Control Error (Get Device).\r\n"));
		else
		  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

		printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	printf_P(PSTR("Android Device Detected - %sAccessory mode.\r\n"), (RequiresModeSwitch ? "Non-" : ""));

	/* Check if a valid Android device was attached, but it is not current in Accessory mode */
	if (RequiresModeSwitch)
	{
		uint16_t AndroidProtocol;

		/* Fetch the version of the Android Accessory Protocol supported by the device */
		if ((ErrorCode = Android_GetAccessoryProtocol(&AndroidProtocol)) != HOST_SENDCONTROL_Successful)
		{
			printf_P(PSTR(ESC_FG_RED "Control Error (Get Protocol).\r\n"
			                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

			LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
			return;
		}

		/* Validate the returned protocol version */
		if (AndroidProtocol != AOA_PROTOCOL_AccessoryV1)
		{
			puts_P(PSTR(ESC_FG_RED "Accessory Mode Not Supported."));

			LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
			return;
		}

		/* Send the device strings and start the Android Accessory Mode */
		Android_SendString(AOA_STRING_Manufacturer, "Dean Camera");
		Android_SendString(AOA_STRING_Model,        "LUFA Android Demo");
		Android_SendString(AOA_STRING_Description,  "LUFA Android Demo");
		Android_SendString(AOA_STRING_Version,      "1.0");
		Android_SendString(AOA_STRING_URI,          "http://www.lufa-lib.org");
		Android_SendString(AOA_STRING_Serial,       "0000000012345678");

		Android_StartAccessoryMode();
		return;
	}

	puts_P(PSTR("Getting Config Data.\r\n"));

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

	puts_P(PSTR("Accessory Mode Android Enumerated.\r\n"));
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

