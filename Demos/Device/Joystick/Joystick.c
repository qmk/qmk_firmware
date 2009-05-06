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
 *  Main source file for the Joystick demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "Joystick.h"

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = USB_USBTask          , .TaskStatus = TASK_STOP },
	{ .Task = USB_Joystick_Report  , .TaskStatus = TASK_STOP },
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
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and joystick reporting tasks.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running joystick reporting and USB management tasks */
	Scheduler_SetTaskMode(USB_Joystick_Report, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the joystick reporting task started.
 */ 
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Joystick Report Endpoint */
	Endpoint_ConfigureEndpoint(JOYSTICK_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, JOYSTICK_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);

	/* Start joystick reporting task */
	Scheduler_SetTaskMode(USB_Joystick_Report, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the HID commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				USB_JoystickReport_Data_t JoystickReportData;
				
				Endpoint_ClearSETUP();

				/* Create the next HID report to send to the host */				
				GetNextReport(&JoystickReportData);
					
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
		
			break;
	}
}

/** Fills the given HID report data structure with the next HID report to send to the host.
 *
 *  \param ReportData  Pointer to a HID report data structure to be filled
 *
 *  \return Boolean true if the new report differs from the last report, false otherwise
 */
bool GetNextReport(USB_JoystickReport_Data_t* ReportData)
{
	static uint8_t PrevJoyStatus = 0;
	uint8_t        JoyStatus_LCL        = Joystick_GetStatus();
	bool           InputChanged         = false;

	/* Clear the report contents */
	memset(ReportData, 0, sizeof(USB_JoystickReport_Data_t));

	if (JoyStatus_LCL & JOY_UP)
	  ReportData->Y = -100;
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportData->Y =  100;

	if (JoyStatus_LCL & JOY_RIGHT)
	  ReportData->X =  100;
	else if (JoyStatus_LCL & JOY_LEFT)
	  ReportData->X = -100;

	if (JoyStatus_LCL & JOY_PRESS)
	  ReportData->Button  = (1 << 1);
	  
	if (Buttons_GetStatus() & BUTTONS_BUTTON1)
	  ReportData->Button |= (1 << 0);
	  
	/* Check if the new report is different to the previous report */
	InputChanged = (uint8_t)(PrevJoyStatus ^ JoyStatus_LCL);

	/* Save the current joystick status for later comparison */
	PrevJoyStatus = JoyStatus_LCL;

	/* Return whether the new report is different to the previous report or not */
	return InputChanged;
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the Joystick_StatusCodes_t enum
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
			LEDMask = (LEDS_LED2 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Function to manage HID report generation and transmission to the host. */
TASK(USB_Joystick_Report)
{
	/* Check if the USB System is connected to a Host */
	if (USB_IsConnected)
	{
		/* Select the Joystick Report Endpoint */
		Endpoint_SelectEndpoint(JOYSTICK_EPNUM);

		/* Check to see if the host is ready for another packet */
		if (Endpoint_IsINReady())
		{
			USB_JoystickReport_Data_t JoystickReportData;
			
			/* Create the next HID report to send to the host */
			GetNextReport(&JoystickReportData);
		
			/* Write Joystick Report Data */
			Endpoint_Write_Stream_LE(&JoystickReportData, sizeof(JoystickReportData));

			/* Finalize the stream transfer to send the last packet */
			Endpoint_ClearIN();
			
			/* Clear the report data afterwards */
			memset(&JoystickReportData, 0, sizeof(JoystickReportData));
		}
	}
}
