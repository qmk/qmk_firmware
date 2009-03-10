/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
      Based on code by Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the KeyboardViaInt demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */
 
#include "KeyboardViaInt.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA KeyboardI App");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
};

/* Global Variables */
/** Indicates what report mode the host has requested, true for normal HID reporting mode, false for special boot
 *  protocol reporting mode.
 */
bool UsingReportProtocol = true;

/** Current Idle period. This is set by the host via a Set Idle HID class request to silence the device's reports
 *  for either the entire idle duration, or until the report status changes (e.g. the user moves the mouse).
 */
uint8_t IdleCount = 0;

/** Current Idle period remaining. When the IdleCount value is set, this tracks the remaining number of idle
 *  milliseconds. This is seperate to the IdleCount timer and is incremented and compared as the host may request 
 *  the current idle period via a Get Idle HID class request, thus its value must be preserved.
 */
uint16_t IdleMSRemaining = 0;


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the USB management task.
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
	
	/* Millisecond timer initialization, with output compare interrupt enabled for the idle timing */
	OCR0A  = 0x7D;
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	TIMSK0 = (1 << OCIE0A);

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

	/* Default to report protocol on connect */
	UsingReportProtocol = true;
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management task.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running keyboard reporting and USB management tasks */
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration
 *  of the USB device after enumeration, and configures the keyboard device endpoints.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Keyboard Keycode Report Endpoint */
	Endpoint_ConfigureEndpoint(KEYBOARD_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, KEYBOARD_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Enable the endpoint IN interrupt ISR for the report endpoint */
	USB_INT_Enable(ENDPOINT_INT_IN);

	/* Setup Keyboard LED Report Endpoint */
	Endpoint_ConfigureEndpoint(KEYBOARD_LEDS_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_OUT, KEYBOARD_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Enable the endpoint OUT interrupt ISR for the LED report endpoint */
	USB_INT_Enable(ENDPOINT_INT_OUT);

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the HID commands, which are
 *  all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Handle HID Class specific requests */
	switch (bRequest)
	{
		case REQ_GetReport:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				USB_KeyboardReport_Data_t KeyboardReportData;

				/* Create the next keyboard report for transmission to the host */
				GetNextReport(&KeyboardReportData);

				/* Ignore report type and ID number value */
				Endpoint_Discard_Word();
				
				/* Ignore unused Interface number value */
				Endpoint_Discard_Word();

				/* Read in the number of bytes in the report to send to the host */
				uint16_t wLength = Endpoint_Read_Word_LE();
				
				/* If trying to send more bytes than exist to the host, clamp the value at the report size */
				if (wLength > sizeof(KeyboardReportData))
				  wLength = sizeof(KeyboardReportData);

				Endpoint_ClearSetupReceived();
	
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&KeyboardReportData, wLength);
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearSetupOUT();
			}
		
			break;
		case REQ_SetReport:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();
				
				/* Wait until the LED report has been sent by the host */
				while (!(Endpoint_IsSetupOUTReceived()));

				/* Read in the LED report from the host */
				uint8_t LEDStatus = Endpoint_Read_Byte();

				/* Process the incomming LED report */
				ProcessLEDReport(LEDStatus);
			
				/* Clear the endpoint data */
				Endpoint_ClearSetupOUT();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
			
			break;
		case REQ_GetProtocol:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();
				
				/* Write the current protocol flag to the host */
				Endpoint_Write_Byte(UsingReportProtocol);
				
				/* Send the flag to the host */
				Endpoint_ClearSetupIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();
			}
			
			break;
		case REQ_SetProtocol:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the new protocol mode */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearSetupReceived();

				/* Set or clear the flag depending on what the host indicates that the current Protocol should be */
				UsingReportProtocol = (wValue != 0x0000);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
			
			break;
		case REQ_SetIdle:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the idle period */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearSetupReceived();
				
				/* Get idle period in MSB */
				IdleCount = (wValue >> 8);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
			
			break;
		case REQ_GetIdle:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{		
				Endpoint_ClearSetupReceived();
				
				/* Write the current idle duration to the host */
				Endpoint_Write_Byte(IdleCount);
				
				/* Send the flag to the host */
				Endpoint_ClearSetupIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();
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
 *  \param ReportData  Pointer to a HID report data structure to be filled
 *
 *  \return Boolean true if the new report differs from the last report, false otherwise
 */
bool GetNextReport(USB_KeyboardReport_Data_t* ReportData)
{
	static uint8_t PrevJoyStatus = 0;
	uint8_t        JoyStatus_LCL = Joystick_GetStatus();
	bool           InputChanged  = false;

	/* Clear the report contents */
	memset(ReportData, 0, sizeof(USB_KeyboardReport_Data_t));

	if (JoyStatus_LCL & JOY_UP)
	  ReportData->KeyCode[0] = 0x04; // A
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportData->KeyCode[0] = 0x05; // B

	if (JoyStatus_LCL & JOY_LEFT)
	  ReportData->KeyCode[0] = 0x06; // C
	else if (JoyStatus_LCL & JOY_RIGHT)
	  ReportData->KeyCode[0] = 0x07; // D

	if (JoyStatus_LCL & JOY_PRESS)
	  ReportData->KeyCode[0] = 0x08; // E
	  
	/* Check if the new report is different to the previous report */
	InputChanged = (uint8_t)(PrevJoyStatus ^ JoyStatus_LCL);

	/* Save the current joystick status for later comparison */
	PrevJoyStatus = JoyStatus_LCL;

	/* Return whether the new report is different to the previous report or not */
	return InputChanged;
}

/** Processes a given LED report mask from the host and sets the board LEDs to match.
 *
 *  \param LEDReport  LED mask from the host, containing a mask of what LEDs are set
 */
void ProcessLEDReport(uint8_t LEDReport)
{
	uint8_t LEDMask   = LEDS_LED2;
	
	if (LEDReport & 0x01) // NUM Lock
	  LEDMask |= LEDS_LED1;
	
	if (LEDReport & 0x02) // CAPS Lock
	  LEDMask |= LEDS_LED3;

	if (LEDReport & 0x04) // SCROLL Lock
	  LEDMask |= LEDS_LED4;

	/* Set the status LEDs to the current Keyboard LED status */
	LEDs_SetAllLEDs(LEDMask);
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the KeyboardViaInt_StatusCodes_t enum
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

/** ISR for the general Pipe/Endpoint interrupt vector. This ISR fires when an endpoint's status changes (such as
 *  a packet has been received) on an endpoint with its corresponding ISR enabling bits set. This is used to send
 *  HID packets to the host each time the HID interrupt endpoints polling period elapses, as managed by the USB
 *  controller.
 */
ISR(ENDPOINT_PIPE_vect, ISR_BLOCK)
{
	/* Save previously selected endpoint before selecting a new endpoint */
	uint8_t PrevSelectedEndpoint = Endpoint_GetCurrentEndpoint();

	/* Check if keyboard endpoint has interrupted */
	if (Endpoint_HasEndpointInterrupted(KEYBOARD_EPNUM))
	{
		USB_KeyboardReport_Data_t KeyboardReportData;
		bool                      SendReport;

		/* Select the Keyboard Report Endpoint */
		Endpoint_SelectEndpoint(KEYBOARD_EPNUM);

		/* Clear the endpoint IN interrupt flag */
		USB_INT_Clear(ENDPOINT_INT_IN);

		/* Clear the Keyboard Report endpoint interrupt */
		Endpoint_ClearEndpointInterrupt(KEYBOARD_EPNUM);

		/* Create the next keyboard report for transmission to the host */
		SendReport = GetNextReport(&KeyboardReportData);
	
		/* Check if the idle period is set and has elapsed */
		if (IdleCount && !(IdleMSRemaining))
		{
			/* Idle period elapsed, indicate that a report must be sent */
			SendReport = true;
			
			/* Reset the idle time remaining counter, must multiply by 4 to get the duration in milliseconds */
			IdleMSRemaining = (IdleCount << 2);
		}
	
		/* Check to see if a report should be issued */
		if (SendReport)
		{
			/* Write Keyboard Report Data */
			Endpoint_Write_Stream_LE(&KeyboardReportData, sizeof(KeyboardReportData));
		}

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearCurrentBank();
	}

	/* Check if Keyboard LED status Endpoint has interrupted */
	if (Endpoint_HasEndpointInterrupted(KEYBOARD_LEDS_EPNUM))
	{
		/* Select the Keyboard LED Report Endpoint */
		Endpoint_SelectEndpoint(KEYBOARD_LEDS_EPNUM);

		/* Clear the endpoint OUT interrupt flag */
		USB_INT_Clear(ENDPOINT_INT_OUT);

		/* Clear the Keyboard LED Report endpoint interrupt */
		Endpoint_ClearEndpointInterrupt(KEYBOARD_LEDS_EPNUM);

		/* Read in the LED report from the host */
		uint8_t LEDStatus = Endpoint_Read_Byte();

		/* Process the incomming LED report */
		ProcessLEDReport(LEDStatus);

		/* Handshake the OUT Endpoint - clear endpoint and ready for next report */
		Endpoint_ClearCurrentBank();
	}
	
	/* Restore previously selected endpoint */
	Endpoint_SelectEndpoint(PrevSelectedEndpoint);
}

