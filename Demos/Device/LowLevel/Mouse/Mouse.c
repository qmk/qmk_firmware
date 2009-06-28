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
 *  Main source file for the Mouse demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */
 
#include "Mouse.h"

/* Global Variables */
/** Indicates what report mode the host has requested, true for normal HID reporting mode, false for special boot
 *  protocol reporting mode.
 */
bool UsingReportProtocol = true;

/** Current Idle period. This is set by the host via a Set Idle HID class request to silence the device's reports
 *  for either the entire idle duration, or until the report status changes (e.g. the user moves the mouse).
 */
uint16_t IdleCount = HID_IDLE_CHANGESONLY;

/** Current Idle period remaining. When the IdleCount value is set, this tracks the remaining number of idle
 *  milliseconds. This is separate to the IdleCount timer and is incremented and compared as the host may request 
 *  the current idle period via a Get Idle HID class request, thus its value must be preserved.
 */
uint16_t IdleMSRemaining = 0;


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	SetupHardware();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Mouse_Task();
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
	Joystick_Init();
	LEDs_Init();
	Buttons_Init();
	USB_Init();
	
	/* Millisecond timer initialization, with output compare interrupt enabled for the idle timing */
	OCR0A  = 0x7D;
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	TIMSK0 = (1 << OCIE0A);
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Default to report protocol on connect */
	UsingReportProtocol = true;
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and Mouse reporting tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the mouse reporting task started.
 */ 
void EVENT_USB_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
	
	/* Setup Mouse Report Endpoint */
	if (!(Endpoint_ConfigureEndpoint(MOUSE_EPNUM, EP_TYPE_INTERRUPT,
		                             ENDPOINT_DIR_IN, MOUSE_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the HID commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	/* Handle HID Class specific requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetReport:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				USB_MouseReport_Data_t MouseReportData;

				Endpoint_ClearSETUP();

				/* Create the next mouse report for transmission to the host */
				CreateMouseReport(&MouseReportData);
	
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&MouseReportData, sizeof(MouseReportData));
				
				/* Clear the report data afterwards */
				memset(&MouseReportData, 0, sizeof(MouseReportData));

				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
		
			break;
		case REQ_GetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Write the current protocol flag to the host */
				Endpoint_Write_Byte(UsingReportProtocol);
				
				/* Send the flag to the host */
				Endpoint_ClearIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetProtocol:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Set or clear the flag depending on what the host indicates that the current Protocol should be */
				UsingReportProtocol = (USB_ControlRequest.wValue != 0);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
			
			break;
		case REQ_SetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Get idle period in MSB */
				IdleCount = (USB_ControlRequest.wValue >> 8);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
			
			break;
		case REQ_GetIdle:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{		
				Endpoint_ClearSETUP();
				
				/* Write the current idle duration to the host */
				Endpoint_Write_Byte(IdleCount);
				
				/* Send the flag to the host */
				Endpoint_ClearIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearOUT();
			}

			break;
	}
}

/** ISR for the timer 0 compare vector. This ISR fires once each millisecond, and increments the
 *  scheduler elapsed idle period counter when the host has set an idle period.
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	/* One millisecond has elapsed, decrement the idle time remaining counter if it has not already elapsed */
	if (IdleMSRemaining)
	  IdleMSRemaining--;
}

/** Fills the given HID report data structure with the next HID report to send to the host.
 *
 *  \param[out] ReportData  Pointer to a HID report data structure to be filled
 */
void CreateMouseReport(USB_MouseReport_Data_t* ReportData)
{
	uint8_t JoyStatus_LCL    = Joystick_GetStatus();
	uint8_t ButtonStatus_LCL = Buttons_GetStatus();
	
	/* Clear the report contents */
	memset(ReportData, 0, sizeof(USB_MouseReport_Data_t));

	if (JoyStatus_LCL & JOY_UP)
	  ReportData->Y = -1;
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportData->Y =  1;

	if (JoyStatus_LCL & JOY_RIGHT)
	  ReportData->X =  1;
	else if (JoyStatus_LCL & JOY_LEFT)
	  ReportData->X = -1;

	if (JoyStatus_LCL & JOY_PRESS)
	  ReportData->Button  = (1 << 0);
	  
	if (ButtonStatus_LCL & BUTTONS_BUTTON1)
	  ReportData->Button |= (1 << 1);
}

/** Sends the next HID report to the host, via the keyboard data endpoint. */
void SendNextReport(void)
{
	static USB_MouseReport_Data_t PrevMouseReportData;
	USB_MouseReport_Data_t        MouseReportData;
	bool                          SendReport;
	
	/* Create the next mouse report for transmission to the host */
	CreateMouseReport(&MouseReportData);
	
	/* Check to see if the report data has changed - if so a report MUST be sent */
	SendReport = (memcmp(&PrevMouseReportData, &MouseReportData, sizeof(USB_MouseReport_Data_t)) != 0);
	
	/* Override the check if the Y or X values are non-zero - we want continuous movement while the joystick
	 * is being held down (via continuous reports), otherwise the cursor will only move once per joystick toggle */
	if ((MouseReportData.Y != 0) || (MouseReportData.X != 0))
	  SendReport = true;
	
	/* Save the current report data for later comparison to check for changes */
	PrevMouseReportData = MouseReportData;
	
	/* Check if the idle period is set and has elapsed */
	if ((IdleCount != HID_IDLE_CHANGESONLY) && (!(IdleMSRemaining)))
	{
		/* Reset the idle time remaining counter, must multiply by 4 to get the duration in milliseconds */
		IdleMSRemaining = (IdleCount << 2);
		
		/* Idle period is set and has elapsed, must send a report to the host */
		SendReport = true;
	}
	
	/* Select the Mouse Report Endpoint */
	Endpoint_SelectEndpoint(MOUSE_EPNUM);

	/* Check if Mouse Endpoint Ready for Read/Write and if we should send a new report */
	if (Endpoint_IsReadWriteAllowed() && SendReport)
	{
		/* Write Mouse Report Data */
		Endpoint_Write_Stream_LE(&MouseReportData, sizeof(MouseReportData));
		
		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();
	}
}

/** Task to manage HID report generation and transmission to the host, when in report mode. */
void Mouse_Task(void)
{
	/* Check if the USB system is connected to a host */
	if (USB_IsConnected)
	{
		/* Send the next mouse report to the host */
		SendNextReport();
	}
}
