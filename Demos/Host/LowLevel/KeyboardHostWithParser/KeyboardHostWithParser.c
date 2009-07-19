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
 *  Main source file for the KeyboardHostWithParser demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "KeyboardHostWithParser.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_RESET ESC_FG_CYAN "Keyboard HID Parser Host Demo running.\r\n" ESC_FG_WHITE));

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
	puts_P(PSTR(ESC_FG_GREEN "Device Attached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "\r\nDevice Unattached.\r\n" ESC_FG_WHITE));
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

	puts_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	puts_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- Sub Error Code %d\r\n"), SubErrorCode);
	printf_P(PSTR(" -- In State %d\r\n" ESC_FG_WHITE), USB_HostState);
	
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  the HID report descriptor and HID reports from the device and display the results onto the board LEDs.
 */
void Keyboard_HID_Task(void)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Config Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR(ESC_FG_RED "Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}

			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)

			{
				puts_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
				
			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			puts_P(PSTR("Processing HID Report.\r\n"));

			/* Get and process the device's first HID report descriptor */
			if ((ErrorCode = GetHIDReportData()) != ParseSuccessful)
			{
				puts_P(PSTR(ESC_FG_RED "Report Parse Error.\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
			
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
				
				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;	
			}

			puts_P(PSTR("Keyboard Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			/* Select and unfreeze keyboard data pipe */
			Pipe_SelectPipe(KEYBOARD_DATAPIPE);	
			Pipe_Unfreeze();

			/* Check to see if a packet has been received */
			if (Pipe_IsINReceived())
			{
				/* Check if data has been received from the attached keyboard */
				if (Pipe_IsReadWriteAllowed())
				{
					/* Create buffer big enough for the report */
					uint8_t KeyboardReport[Pipe_BytesInPipe()];

					/* Load in the keyboard report */
					Pipe_Read_Stream_LE(KeyboardReport, Pipe_BytesInPipe());
				
					/* Process the read in keyboard report from the device */
					ProcessKeyboardReport(KeyboardReport);
				}
				
				/* Clear the IN endpoint, ready for next data packet */
				Pipe_ClearIN();
			}

			/* Freeze keyboard data pipe */
			Pipe_Freeze();
			break;
	}
}

/** Processes a read HID report from an attached keyboard, extracting out elements via the HID parser results
 *  as required and prints pressed characters to the serial port. Each time a key is typed, a board LED is toggled.
 *
 *  \param[in] KeyboardReport  Pointer to a HID report from an attached keyboard device
 */
void ProcessKeyboardReport(uint8_t* KeyboardReport)
{
	/* Check each HID report item in turn, looking for keyboard scan code reports */
	for (uint8_t ReportNumber = 0; ReportNumber < HIDReportInfo.TotalReportItems; ReportNumber++)
	{
		/* Create a temporary item pointer to the next report item */
		HID_ReportItem_t* ReportItem = &HIDReportInfo.ReportItems[ReportNumber];

		/* Check if the current report item is a keyboard scancode */
		if ((ReportItem->Attributes.Usage.Page      == USAGE_PAGE_KEYBOARD) &&
			(ReportItem->Attributes.BitSize         == 8)                   &&
			(ReportItem->Attributes.Logical.Maximum > 1)                    &&
			(ReportItem->ItemType                   == REPORT_ITEM_TYPE_In))
		{
			/* Retrieve the keyboard scancode from the report data retrieved from the device */
			bool FoundData = USB_GetHIDReportItemInfo(KeyboardReport, ReportItem);
			
			/* For multi-report devices - if the requested data was not in the issued report, continue */
			if (!(FoundData))
			  continue;
			
			/* Key code is an unsigned char in length, cast to the appropriate type */
			uint8_t KeyCode = (uint8_t)ReportItem->Value;

			/* If scancode is non-zero, a key is being pressed */
			if (KeyCode)
			{
				/* Toggle status LED to indicate keypress */
				if (LEDs_GetLEDs() & LEDS_LED2)
				  LEDs_TurnOffLEDs(LEDS_LED2);
				else
				  LEDs_TurnOnLEDs(LEDS_LED2);

				char PressedKey = 0;

				/* Convert scancode to printable character if alphanumeric */
				if ((KeyCode >= 0x04) && (KeyCode <= 0x1D))
				  PressedKey = (KeyCode - 0x04) + 'A';
				else if ((KeyCode >= 0x1E) && (KeyCode <= 0x27))
				  PressedKey = (KeyCode - 0x1E) + '0';
				else if (KeyCode == 0x2C)
				  PressedKey = ' ';						
				else if (KeyCode == 0x28)
				  PressedKey = '\n';
					 
				/* Print the pressed key character out through the serial port if valid */
				if (PressedKey)
				  putchar(PressedKey);
			}
			
			/* Once a scancode is found, stop scanning through the report items */
			break;
		}
	}
}
