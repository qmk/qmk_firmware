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
 *  Main source file for the MouseHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "MouseHost.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA Mouse Host App");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: USB_Mouse_Host       , TaskStatus: TASK_STOP },
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

	/* Startup message */
	puts_P(PSTR(ESC_RESET ESC_BG_WHITE ESC_INVERSE_ON ESC_ERASE_DISPLAY
	       "Mouse Host Demo running.\r\n" ESC_INVERSE_OFF));
		   
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
	/* Stop mouse and USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	Scheduler_SetTaskMode(USB_Mouse_Host, TASK_STOP);

	puts_P(PSTR("Device Unattached.\r\n"));
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
EVENT_HANDLER(USB_DeviceEnumerationComplete)
{
	/* Start Mouse Host task */
	Scheduler_SetTaskMode(USB_Mouse_Host, TASK_RUN);

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

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occured while
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
 *  \param CurrentStatus  Current status of the system, from the MouseHost_StatusCodes_t enum
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
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Reads in and processes the next report from the attached device, displaying the report
 *  contents on the board LEDs and via the serial port.
 */
void ReadNextReport(void)
{
	USB_MouseReport_Data_t MouseReport;
	uint8_t                LEDMask = LEDS_NO_LEDS;

	/* Select mouse data pipe */
	Pipe_SelectPipe(MOUSE_DATAPIPE);	

	#if !defined(INTERRUPT_DATA_PIPE)
	/* Unfreeze mouse data pipe */
	Pipe_Unfreeze();
	#endif

	/* Ensure pipe contains data and is ready to be read before continuing */
	if (!(Pipe_ReadWriteAllowed()))
	{
		#if !defined(INTERRUPT_DATA_PIPE)
		/* Refreeze mouse data pipe */
		Pipe_Freeze();
		#endif

		return;
	}

	/* Read in mouse report data */
	Pipe_Read_Stream_LE(&MouseReport, sizeof(MouseReport));				
		
	/* Clear the IN endpoint, ready for next data packet */
	Pipe_ClearCurrentBank();
		
	/* Alter status LEDs according to mouse X movement */
	if (MouseReport.X > 0)
	  LEDMask |= LEDS_LED1;
	else if (MouseReport.X < 0)
	  LEDMask |= LEDS_LED2;
		
	/* Alter status LEDs according to mouse Y movement */
	if (MouseReport.Y > 0)
	  LEDMask |= LEDS_LED3;
	else if (MouseReport.Y < 0)
	  LEDMask |= LEDS_LED4;

	/* Alter status LEDs according to mouse button position */
	if (MouseReport.Button)
	  LEDMask  = LEDS_ALL_LEDS;
	
	LEDs_SetAllLEDs(LEDMask);
	
	/* Print mouse report data through the serial port */
	printf_P(PSTR("dX:%2d dY:%2d Button:%d\r\n"), MouseReport.X,
												  MouseReport.Y,
												  MouseReport.Button);

	#if !defined(INTERRUPT_DATA_PIPE)
	/* Refreeze mouse data pipe */
	Pipe_Freeze();
	#endif
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  HID reports from the device and display the results onto the board LEDs.
 */
TASK(USB_Mouse_Host)
{
	uint8_t ErrorCode;

	/* Switch to determine what user-application handled host state the host state machine is in */
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

			/* Send the request, display error and wait for device detatch if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Configuration).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error status */
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
				
				/* Indicate error status */
				UpdateStatus(Status_EnumerationError);

				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}
		
			/* HID class request to set the mouse protocol to the Boot Protocol */
			USB_HostRequest = (USB_Host_Request_Header_t)
				{
					bmRequestType: (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
					bRequest:      REQ_SetProtocol,
					wValue:        0,
					wIndex:        0,
					wLength:       0,
				};

			/* Send the request, display error and wait for device detatch if request fails */
			if ((ErrorCode = USB_Host_SendControlRequest(NULL)) != HOST_SENDCONTROL_Successful)
			{
				puts_P(PSTR("Control Error (Set Protocol).\r\n"));
				printf_P(PSTR(" -- Error Code: %d\r\n"), ErrorCode);

				/* Indicate error status */
				UpdateStatus(Status_EnumerationError);
				
				/* Wait until USB device disconnected */
				while (USB_IsConnected);
				break;
			}

			#if defined(INTERRUPT_DATA_PIPE)			
			/* Select and unfreeze mouse data pipe */
			Pipe_SelectPipe(MOUSE_DATAPIPE);	
			Pipe_Unfreeze();
			#endif

			puts_P(PSTR("Mouse Enumerated.\r\n"));
			
			USB_HostState = HOST_STATE_Ready;
			break;
		#if !defined(INTERRUPT_DATA_PIPE)
		case HOST_STATE_Ready:
			/* If a report has been received, read and process it */
			ReadNextReport();

			break;
		#endif
	}
}

#if defined(INTERRUPT_DATA_PIPE)
/** Interrupt handler for the Endpoint/Pipe interrupt vector. This interrupt fires each time an enabled
 *  pipe interrupt occurs on a pipe which has had that interrupt enabled.
 */
ISR(ENDPOINT_PIPE_vect, ISR_BLOCK)
{
	/* Save previously selected pipe before selecting a new pipe */
	uint8_t PrevSelectedPipe = Pipe_GetCurrentPipe();

	/* Check to see if the mouse data pipe has caused the interrupt */
	if (Pipe_HasPipeInterrupted(MOUSE_DATAPIPE))
	{
		/* Clear the pipe interrupt, and select the mouse pipe */
		Pipe_ClearPipeInterrupt(MOUSE_DATAPIPE);
		Pipe_SelectPipe(MOUSE_DATAPIPE);	

		/* Check to see if the pipe IN interrupt has fired */
		if (USB_INT_HasOccurred(PIPE_INT_IN) && USB_INT_IsEnabled(PIPE_INT_IN))
		{
			/* Clear interrupt flag */
			USB_INT_Clear(PIPE_INT_IN);		

			/* Read and process the next report from the device */
			ReadNextReport();
		}
	}

	/* Restore previously selected pipe */
	Pipe_SelectPipe(PrevSelectedPipe);
}
#endif
