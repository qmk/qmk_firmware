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

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: USB_Keyboard_Host    , TaskStatus: TASK_STOP },
};


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	SerialStream_Init(9600, false);
	LEDs_Init();
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Start-up message */
	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "Keyboard Host Demo running.\r\n" ESC_INVERSE_OFF));
		   
	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
EVENT_HANDLER(USB_DeviceAttached)
{
	puts_P(PSTR("Device Attached.\r\n"));
	UpdateStatus(Status_USBEnumerating);

	/* Start USB management task to enumerate the device */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
EVENT_HANDLER(USB_DeviceUnattached)
{
	/* Stop keyboard and USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	Scheduler_SetTaskMode(USB_Keyboard_Host, TASK_STOP);

	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
EVENT_HANDLER(USB_DeviceEnumerationComplete)
{
	/* Start Keyboard Host task */
	Scheduler_SetTaskMode(USB_Keyboard_Host, TASK_RUN);
	
	/* Indicate device enumeration complete */
	UpdateStatus(Status_USBReady);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
EVENT_HANDLER(USB_HostError)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	UpdateStatus(Status_HardwareError);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
EVENT_HANDLER(USB_DeviceEnumerationFailed)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- Sub Error Code %d\r\n"), SubErrorCode);
	printf_P(PSTR(" -- In State %d\r\n"), USB_HostState);
	
	UpdateStatus(Status_EnumerationError);
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the KeyboardHostWithParser_StatusCodes_t enum
 */
void UpdateStatus(uint8_t CurrentStatus)
{
	uint8_t LEDMask = LEDS_NO_LEDS;
	
	/* Set the LED mask to the appropriate LED mask based on the given status code */
	switch (CurrentStatus)
	{
		case Status_USBNotReady:
			LEDMask = (LEDS_LED1);
			break;
		case Status_USBEnumerating:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
		case Status_USBReady:
			LEDMask = (LEDS_LED2);
			break;
		case Status_EnumerationError:
		case Status_HardwareError:
			LEDMask = (LEDS_LED1 | LEDS_LED3);
			break;
		case Status_Busy:
			LEDMask = (LEDS_LED1 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  the HID report descriptor and HID reports from the device and display the results onto the board LEDs.
 */
TASK(USB_Keyboard_Host)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			/* Standard request to set the device configuration to configuration 1 */
			USB_HostRequest = (USB_Host_Request_Header_t)
				{
					bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					bRequest:      REQ_SetConfiguration,
					wValue:        1,
					wIndex:        0,
					wLength:       0,
				};

			/* Select the control pipe for the request transfer */
			Pipe_SelectPipe(PIPE_CONTROLPIPE);

			/* Send the request, display error and wait for device detach if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error via status LEDs */
				UpdateStatus(Status_EnumerationError);

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
				
				/* Indicate error via status LEDs */
				UpdateStatus(Status_EnumerationError);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
					
			puts_P(PSTR("Processing HID Report.\r\n"));

			/* LEDs one and two on to indicate busy processing */
			UpdateStatus(Status_Busy);

			/* Get and process the device's first HID report descriptor */
			if ((ErrorCode = GetHIDReportData()) != ParseSuccessful)
			{
				puts_P(PSTR("Report Parse Error.\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
			
				/* Indicate error via status LEDs */
				UpdateStatus(Status_EnumerationError);
				
				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;	
			}
			
			/* All LEDs off - ready to indicate key presses */
			UpdateStatus(Status_USBReady);

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
 *  \param KeyboardReport  Pointer to a HID report from an attached keyboard device
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
			bool FoundData = GetReportItemInfo(KeyboardReport, ReportItem);
			
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
