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

/* Scheduler Task List */
TASK_LIST
{
	#if !defined(INTERRUPT_CONTROL_ENDPOINT)
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	#endif
	
	#if !defined(INTERRUPT_DATA_ENDPOINT)
	{ Task: USB_Mouse_Report     , TaskStatus: TASK_STOP },
	#endif
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
 *  milliseconds. This is separate to the IdleCount timer and is incremented and compared as the host may request 
 *  the current idle period via a Get Idle HID class request, thus its value must be preserved.
 */
uint16_t IdleMSRemaining = 0;


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
	HWB_Init();
	
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
	#if !defined(INTERRUPT_CONTROL_ENDPOINT)
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
	#endif
	
	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);

	/* Default to report protocol on connect */
	UsingReportProtocol = true;
}

/** Event handler for the USB_Reset event. This fires when the USB interface is reset by the USB host, before the
 *  enumeration process begins, and enables the control endpoint interrupt so that control requests can be handled
 *  asynchronously when they arrive rather than when the control endpoint is polled manually.
 */
EVENT_HANDLER(USB_Reset)
{
	#if defined(INTERRUPT_CONTROL_ENDPOINT)
	/* Select the control endpoint */
	Endpoint_SelectEndpoint(ENDPOINT_CONTROLEP);

	/* Enable the endpoint SETUP interrupt ISR for the control endpoint */
	USB_INT_Enable(ENDPOINT_INT_SETUP);
	#endif
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and Mouse reporting tasks.
 */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running mouse reporting and USB management tasks */
	#if !defined(INTERRUPT_DATA_ENDPOINT)
	Scheduler_SetTaskMode(USB_Mouse_Report, TASK_STOP);
	#endif

	#if !defined(INTERRUPT_CONTROL_ENDPOINT)
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	#endif

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host sets the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the mouse reporting task started.
 */ 
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Mouse Report Endpoint */
	Endpoint_ConfigureEndpoint(MOUSE_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, MOUSE_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	#if defined(INTERRUPT_DATA_ENDPOINT)
	/* Enable the endpoint IN interrupt ISR for the report endpoint */
	USB_INT_Enable(ENDPOINT_INT_IN);
	#endif

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);

	#if !defined(INTERRUPT_DATA_ENDPOINT)
	/* Start running mouse reporting task */
	Scheduler_SetTaskMode(USB_Mouse_Report, TASK_RUN);
	#endif
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
				USB_MouseReport_Data_t MouseReportData;

				/* Create the next mouse report for transmission to the host */
				CreateMouseReport(&MouseReportData);

				/* Ignore report type and ID number value */
				Endpoint_Discard_Word();
				
				/* Ignore unused Interface number value */
				Endpoint_Discard_Word();

				/* Read in the number of bytes in the report to send to the host */
				uint16_t wLength = Endpoint_Read_Word_LE();
				
				/* If trying to send more bytes than exist to the host, clamp the value at the report size */
				if (wLength > sizeof(MouseReportData))
				  wLength = sizeof(MouseReportData);

				Endpoint_ClearControlSETUP();
	
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&MouseReportData, wLength);
				
				/* Clear the report data afterwards */
				memset(&MouseReportData, 0, sizeof(MouseReportData));

				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearControlOUT();
			}
		
			break;
		case REQ_GetProtocol:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearControlSETUP();
				
				/* Write the current protocol flag to the host */
				Endpoint_Write_Byte(UsingReportProtocol);
				
				/* Send the flag to the host */
				Endpoint_ClearControlIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearControlOUT();
			}
			
			break;
		case REQ_SetProtocol:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the new protocol mode */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearControlSETUP();
				
				/* Set or clear the flag depending on what the host indicates that the current Protocol should be */
				UsingReportProtocol = (wValue != 0x0000);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearControlIN();
			}
			
			break;
		case REQ_SetIdle:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the idle period */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearControlSETUP();
				
				/* Get idle period in MSB */
				IdleCount = (wValue >> 8);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearControlIN();
			}
			
			break;
		case REQ_GetIdle:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{		
				Endpoint_ClearControlSETUP();
				
				/* Write the current idle duration to the host */
				Endpoint_Write_Byte(IdleCount);
				
				/* Send the flag to the host */
				Endpoint_ClearControlIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsOUTReceived()));
				Endpoint_ClearControlOUT();
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
 */
void CreateMouseReport(USB_MouseReport_Data_t* ReportData)
{
	uint8_t JoyStatus_LCL = Joystick_GetStatus();
	
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
	  
	if (HWB_GetStatus())
	  ReportData->Button |= (1 << 1);
}

/** Sends the next HID report to the host, via the keyboard data endpoint. */
static inline void SendNextReport(void)
{
	static USB_MouseReport_Data_t PrevMouseReportData;
	USB_MouseReport_Data_t        MouseReportData;
	bool                          SendReport = true;
	
	/* Create the next mouse report for transmission to the host */
	CreateMouseReport(&MouseReportData);
	
	/* Check if the idle period is set*/
	if (IdleCount)
	{
		/* Determine if the idle period has elapsed */
		if (!(IdleMSRemaining))
		{
			/* Reset the idle time remaining counter, must multiply by 4 to get the duration in milliseconds */
			IdleMSRemaining = (IdleCount << 2);		
		}
		else
		{
			/* Idle period not elapsed, indicate that a report must not be sent unless the report has changed */
			SendReport = (memcmp(&PrevMouseReportData, &MouseReportData, sizeof(USB_MouseReport_Data_t)) != 0);
		}
	}

	/* Save the current report data for later comparison to check for changes */
	PrevMouseReportData = MouseReportData;
	
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

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the Mouse_StatusCodes_t enum
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

#if !defined(INTERRUPT_DATA_ENDPOINT)
/** Task to manage HID report generation and transmission to the host, when in report mode. */
TASK(USB_Mouse_Report)
{
	/* Check if the USB system is connected to a host */
	if (USB_IsConnected)
	{
		/* Send the next mouse report to the host */
		SendNextReport();
	}
}
#endif

/** ISR for the general Pipe/Endpoint interrupt vector. This ISR fires when an endpoint's status changes (such as
 *  a packet has been received) on an endpoint with its corresponding ISR enabling bits set. This is used to send
 *  HID packets to the host each time the HID interrupt endpoints polling period elapses, as managed by the USB
 *  controller. It is also used to respond to standard and class specific requests send to the device on the control
 *  endpoint, by handing them off to the LUFA library when they are received.
 */
ISR(ENDPOINT_PIPE_vect, ISR_BLOCK)
{
	#if defined(INTERRUPT_CONTROL_ENDPOINT)
	/* Check if the control endpoint has received a request */
	if (Endpoint_HasEndpointInterrupted(ENDPOINT_CONTROLEP))
	{
		/* Clear the endpoint interrupt */
		Endpoint_ClearEndpointInterrupt(ENDPOINT_CONTROLEP);

		/* Process the control request */
		USB_USBTask();

		/* Handshake the endpoint setup interrupt - must be after the call to USB_USBTask() */
		USB_INT_Clear(ENDPOINT_INT_SETUP);
	}
	#endif
	
	#if defined(INTERRUPT_DATA_ENDPOINT)
	/* Check if mouse endpoint has interrupted */
	if (Endpoint_HasEndpointInterrupted(MOUSE_EPNUM))
	{
		/* Select the Mouse Report Endpoint */
		Endpoint_SelectEndpoint(MOUSE_EPNUM);

		/* Clear the endpoint IN interrupt flag */
		USB_INT_Clear(ENDPOINT_INT_IN);

		/* Clear the Mouse Report endpoint interrupt and select the endpoint */
		Endpoint_ClearEndpointInterrupt(MOUSE_EPNUM);

		/* Send the next mouse report to the host */
		SendNextReport();
	}
	#endif
}
