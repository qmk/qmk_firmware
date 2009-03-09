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

/*
	Bluetooth Dongle host demo application.
	
	** NOT CURRENTLY FUNCTIONAL - DO NOT USE **
*/

/*
	USB Mode:           Host
	USB Class:          Bluetooth USB Transport Class
	USB Subclass:       Bluetooth HCI USB Transport
	Relevant Standards: Bluetooth 2.0 Standard
	                    Bluetooth 2.0 HCI USB Transport Layer Addendum
						Bluetooth Assigned Numbers (Baseband)
	Usable Speeds:      Full Speed Mode
*/

#include "BluetoothHost.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA BT Host App");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          ,   TaskStatus: TASK_STOP },
	{ Task: USB_Bluetooth_Host   ,   TaskStatus: TASK_STOP },
	{ Task: Bluetooth_Task       ,   TaskStatus: TASK_STOP },
};

Bluetooth_Device_t Bluetooth_DeviceConfiguration =
	{
		Class:   (DEVICE_CLASS_SERVICE_CAPTURING | DEVICE_CLASS_MAJOR_COMPUTER | DEVICE_CLASS_MINOR_COMPUTER_PALM),
		PINCode: "0000",
		Name:    "LUFA Bluetooth Demo"
	};


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

	/* Startup message */
	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "Bluetooth Host Demo running.\r\n" ESC_INVERSE_OFF));
		   
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();
	
	/* Scheduling routine never returns, so put this last in the main function */
	Scheduler_Start();
}

EVENT_HANDLER(USB_DeviceAttached)
{
	puts_P(PSTR("Device Attached.\r\n"));
	UpdateStatus(Status_USBEnumerating);
	
	/* Start USB management task to enumerate the device */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

EVENT_HANDLER(USB_DeviceUnattached)
{
	/* Stop USB management and Bluetooth tasks */
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	Scheduler_SetTaskMode(USB_Bluetooth_Host, TASK_STOP);
	Scheduler_SetTaskMode(Bluetooth_Task, TASK_STOP);
			
	puts_P(PSTR("\r\nDevice Unattached.\r\n"));
	UpdateStatus(Status_USBNotReady);
}

EVENT_HANDLER(USB_DeviceEnumerationComplete)
{
	/* Once device is fully enumerated, start the Bluetooth Host task */
	Scheduler_SetTaskMode(USB_Bluetooth_Host, TASK_RUN);
	Scheduler_SetTaskMode(Bluetooth_Task, TASK_RUN);
			
	UpdateStatus(Status_USBReady);
}

EVENT_HANDLER(USB_HostError)
{
	USB_ShutDown();

	puts_P(PSTR(ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	UpdateStatus(Status_HardwareError);
	for(;;);
}

EVENT_HANDLER(USB_DeviceEnumerationFailed)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
	printf_P(PSTR(" -- In State %d\r\n"), USB_HostState);
	
	UpdateStatus(Status_EnumerationError);
}

TASK(USB_Bluetooth_Host)
{
	uint8_t ErrorCode;

	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Device Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessDeviceDescriptor()) != SuccessfulDeviceRead)
			{
				if (ErrorCode == ControlErrorDuringDeviceRead)
				  puts_P(PSTR("Control Error (Get Device).\r\n"));
				else
				  puts_P(PSTR("Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDS_LED1);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			puts_P(PSTR("Bluetooth Dongle Detected.\r\n"));

			/* Standard request to set the device configuration to configuration 1 */
			USB_HostRequest = (USB_Host_Request_Header_t)
				{
					bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE),
					bRequest:      REQ_SetConfiguration,
					wValue:        1,
					wIndex:        0,
					wLength:       0,
				};
				
			/* Send the request, display error and wait for device detatch if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDS_LED1);

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
				if (ErrorCode == ControlErrorDuringConfigRead)
				  puts_P(PSTR("Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR("Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDS_LED1);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			puts_P(PSTR("Bluetooth Dongle Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Ready;
			break;
		case HOST_STATE_Ready:
			if (Bluetooth_HCIProcessingState != Bluetooth_ProcessEvents)
			{
				UpdateStatus(Status_BluetoothBusy);
			}
			else
			{
				if (Bluetooth_Connection.IsConnected)
				  UpdateStatus(Status_BluetoothConnected);
				else
				  UpdateStatus(Status_USBReady);
			}
			
			break;
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the MouseHostViaInt_StatusCodes_t enum
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
		case Status_BluetoothConnected:
			LEDMask = (LEDS_LED2 | LEDS_LED4);
			break;		
		case Status_BluetoothBusy:
			LEDMask = (LEDS_LED2 | LEDS_LED3 | LEDS_LED4);
			break;		
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}
