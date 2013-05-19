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
 *  Main source file for the KeyboardHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "KeyboardHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Keyboard HID Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		KeyboardHost_Task();

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

	/* HID class request to set the keyboard protocol to the Boot Protocol */
	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
			.bRequest      = HID_REQ_SetProtocol,
			.wValue        = 0,
			.wIndex        = 0,
			.wLength       = 0,
		};

	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	/* Send the request, display error and wait for device detach if request fails */
	if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Control Error (Set Protocol).\r\n"
		                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		USB_Host_SetDeviceConfiguration(0);
		return;
	}

	puts_P(PSTR("Keyboard Enumerated.\r\n"));
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

/** Task to read in and processes the next report from the attached device, displaying the report
 *  contents on the board LEDs and via the serial port.
 */
void KeyboardHost_Task(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select keyboard data pipe */
	Pipe_SelectPipe(KEYBOARD_DATA_IN_PIPE);

	/* Unfreeze keyboard data pipe */
	Pipe_Unfreeze();

	/* Check to see if a packet has been received */
	if (!(Pipe_IsINReceived()))
	{
		/* Refreeze HID data IN pipe */
		Pipe_Freeze();

		return;
	}

	/* Ensure pipe contains data before trying to read from it */
	if (Pipe_IsReadWriteAllowed())
	{
		USB_KeyboardReport_Data_t KeyboardReport;

		/* Read in keyboard report data */
		Pipe_Read_Stream_LE(&KeyboardReport, sizeof(KeyboardReport), NULL);

		/* Indicate if the modifier byte is non-zero (special key such as shift is being pressed) */
		LEDs_ChangeLEDs(LEDS_LED1, (KeyboardReport.Modifier) ? LEDS_LED1 : 0);

		uint8_t KeyCode = KeyboardReport.KeyCode[0];

		/* Check if a key has been pressed */
		if (KeyCode)
		{
			/* Toggle status LED to indicate keypress */
			LEDs_ToggleLEDs(LEDS_LED2);

			char PressedKey = 0;

			/* Retrieve pressed key character if alphanumeric */
			if ((KeyCode >= HID_KEYBOARD_SC_A) && (KeyCode <= HID_KEYBOARD_SC_Z))
			{
				PressedKey = (KeyCode - HID_KEYBOARD_SC_A) + 'A';
			}
			else if ((KeyCode >= HID_KEYBOARD_SC_1_AND_EXCLAMATION) &
					 (KeyCode  < HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS))
			{
				PressedKey = (KeyCode - HID_KEYBOARD_SC_1_AND_EXCLAMATION) + '1';
			}
			else if (KeyCode == HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS)
			{
				PressedKey = '0';
			}
			else if (KeyCode == HID_KEYBOARD_SC_SPACE)
			{
				PressedKey = ' ';
			}
			else if (KeyCode == HID_KEYBOARD_SC_ENTER)
			{
				PressedKey = '\n';
			}

			/* Print the pressed key character out through the serial port if valid */
			if (PressedKey)
			  putchar(PressedKey);
		}
	}

	/* Clear the IN endpoint, ready for next data packet */
	Pipe_ClearIN();

	/* Refreeze keyboard data pipe */
	Pipe_Freeze();
}

