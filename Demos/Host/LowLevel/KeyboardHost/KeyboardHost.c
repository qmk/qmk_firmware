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
 *  Main source file for the KeyboardHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "KeyboardHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "Keyboard HID Host Demo running.\r\n" ESC_INVERSE_OFF));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Keyboard_HID_Task();
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
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_DeviceAttached(void)
{
	puts_P(PSTR("Device Attached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_DeviceUnattached(void)
{
	puts_P(PSTR("Device Unattached.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- Sub Error Code %d\r\n"), SubErrorCode);
	printf_P(PSTR(" -- In State %d\r\n"), USB_HostState);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Reads in and processes the next report from the attached device, displaying the report
 *  contents on the board LEDs and via the serial port.
 */
void ReadNextReport(void)
{
	USB_KeyboardReport_Data_t KeyboardReport;
		
	/* Select keyboard data pipe */
	Pipe_SelectPipe(KEYBOARD_DATAPIPE);	

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
		/* Read in keyboard report data */
		Pipe_Read_Stream_LE(&KeyboardReport, sizeof(KeyboardReport));

		/* Indicate if the modifier byte is non-zero (special key such as shift is being pressed) */
		LEDs_ChangeLEDs(LEDS_LED1, (KeyboardReport.Modifier) ? LEDS_LED1 : 0);
		
		/* Check if a key has been pressed */
		if (KeyboardReport.KeyCode)
		{
			/* Toggle status LED to indicate keypress */
			if (LEDs_GetLEDs() & LEDS_LED2)
			  LEDs_TurnOffLEDs(LEDS_LED2);
			else
			  LEDs_TurnOnLEDs(LEDS_LED2);
				  
			char PressedKey = 0;

			/* Retrieve pressed key character if alphanumeric */
			if ((KeyboardReport.KeyCode >= 0x04) && (KeyboardReport.KeyCode <= 0x1D))
			  PressedKey = (KeyboardReport.KeyCode - 0x04) + 'A';
			else if ((KeyboardReport.KeyCode >= 0x1E) && (KeyboardReport.KeyCode <= 0x27))
			  PressedKey = (KeyboardReport.KeyCode - 0x1E) + '0';
			else if (KeyboardReport.KeyCode == 0x2C)
			  PressedKey = ' ';						
			else if (KeyboardReport.KeyCode == 0x28)
			  PressedKey = '\n';
				 
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

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  HID reports from the device and display the results onto the board LEDs.
 */
void Keyboard_HID_Task(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			/* Standard request to set the device configuration to configuration 1 */
			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					.bRequest      = REQ_SetConfiguration,
					.wValue        = 1,
					.wIndex        = 0,
					.wLength       = 0,
				};

			/* Select the control pipe for the request transfer */
			Pipe_SelectPipe(PIPE_CONTROLPIPE);

			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error status */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			puts_P(PSTR("Getting Config Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR("Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR("Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
				
				/* Indicate error status */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
		
			/* HID class request to set the keyboard protocol to the Boot Protocol */
			USB_ControlRequest = (USB_Request_Header_t)
				{
					.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
					.bRequest      = REQ_SetProtocol,
					.wValue        = 0,
					.wIndex        = 0,
					.wLength       = 0,
				};

			/* Select the control pipe for the request transfer */
			Pipe_SelectPipe(PIPE_CONTROLPIPE);

			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Protocol).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error status */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
				
				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			puts_P(PSTR("Keyboard Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			/* If a report has been received, read and process it */
			ReadNextReport();

			break;
	}
}
