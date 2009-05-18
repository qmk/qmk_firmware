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
 *  Main source file for the DualCDC demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */
 
#include "DualCDC.h"

/* Scheduler Task List */
TASK_LIST
{
	{ .Task = USB_USBTask          , .TaskStatus = TASK_STOP },
	{ .Task = CDC1_Task            , .TaskStatus = TASK_STOP },
	{ .Task = CDC2_Task            , .TaskStatus = TASK_STOP },
};

/* Globals: */
/** Contains the current baud rate and other settings of the first virtual serial port. While this demo does not use
 *  the physical USART and thus does not use these settings, they must still be retained and returned to the host
 *  upon request or the host will assume the device is non-functional.
 *
 *  These values are set by the host via a class-specific request, however they are not required to be used accurately.
 *  It is possible to completely ignore these value or use other settings as the host is completely unaware of the physical
 *  serial link characteristics and instead sends and receives data in endpoint streams.
 */
CDC_Line_Coding_t LineCoding1 = { .BaudRateBPS = 9600,
                                  .CharFormat  = OneStopBit,
                                  .ParityType  = Parity_None,
                                  .DataBits    = 8            };

/** Contains the current baud rate and other settings of the second virtual serial port. While this demo does not use
 *  the physical USART and thus does not use these settings, they must still be retained and returned to the host
 *  upon request or the host will assume the device is non-functional.
 *
 *  These values are set by the host via a class-specific request, however they are not required to be used accurately.
 *  It is possible to completely ignore these value or use other settings as the host is completely unaware of the physical
 *  serial link characteristics and instead sends and receives data in endpoint streams.
 */
CDC_Line_Coding_t LineCoding2 = { .BaudRateBPS = 9600,
                                  .CharFormat  = OneStopBit,
                                  .ParityType  = Parity_None,
                                  .DataBits    = 8            };
								  
/** String to print through the first virtual serial port when the joystick is pressed upwards. */
char JoystickUpString[]      = "Joystick Up\r\n";

/** String to print through the first virtual serial port when the joystick is pressed downward. */
char JoystickDownString[]    = "Joystick Down\r\n";

/** String to print through the first virtual serial port when the joystick is pressed left. */
char JoystickLeftString[]    = "Joystick Left\r\n";

/** String to print through the first virtual serial port when the joystick is pressed right. */
char JoystickRightString[]   = "Joystick Right\r\n";

/** String to print through the first virtual serial port when the joystick is pressed inwards. */
char JoystickPressedString[] = "Joystick Pressed\r\n";

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
void EVENT_USB_Connect(void)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and CDC management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Stop running CDC and USB management tasks */
	Scheduler_SetTaskMode(CDC1_Task, TASK_STOP);
	Scheduler_SetTaskMode(CDC2_Task, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management tasks are started.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Setup CDC Notification, Rx and Tx Endpoints for the first CDC */
	Endpoint_ConfigureEndpoint(CDC1_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC1_TX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC1_RX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	/* Setup CDC Notification, Rx and Tx Endpoints for the second CDC */
	Endpoint_ConfigureEndpoint(CDC2_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC2_TX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);

	Endpoint_ConfigureEndpoint(CDC2_RX_EPNUM, EP_TYPE_BULK,
		                       ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
							   
	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);
	
	/* Start CDC tasks */
	Scheduler_SetTaskMode(CDC1_Task, TASK_RUN);
	Scheduler_SetTaskMode(CDC2_Task, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the CDC control commands,
 *  which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	/* Determine which interface's Line Coding data is being set from the wIndex parameter */
	uint8_t* LineCodingData = (USB_ControlRequest.wIndex == 0) ? (uint8_t*)&LineCoding1 : (uint8_t*)&LineCoding2;

	/* Process CDC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{	
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();

				/* Write the line coding data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(LineCodingData, sizeof(CDC_Line_Coding_t));
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearOUT();
			}
			
			break;
		case REQ_SetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();

				/* Read the line coding data in from the host into the global struct */
				Endpoint_Read_Control_Stream_LE(LineCodingData, sizeof(CDC_Line_Coding_t));

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearIN();
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}
	
			break;
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the DualCDC_StatusCodes_t enum
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

/** Function to manage CDC data transmission and reception to and from the host for the first CDC interface, which sends joystick
 *  movements to the host as ASCII strings.
 */
TASK(CDC1_Task)
{
	char*       ReportString    = NULL;
	uint8_t     JoyStatus_LCL   = Joystick_GetStatus();
	static bool ActionSent      = false;

	/* Determine if a joystick action has occurred */
	if (JoyStatus_LCL & JOY_UP)
	  ReportString = JoystickUpString;
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportString = JoystickDownString;
	else if (JoyStatus_LCL & JOY_LEFT)
	  ReportString = JoystickLeftString;
	else if (JoyStatus_LCL & JOY_RIGHT)
	  ReportString = JoystickRightString;
	else if (JoyStatus_LCL & JOY_PRESS)
	  ReportString = JoystickPressedString;

	/* Flag management - Only allow one string to be sent per action */
	if (ReportString == NULL)
	{
		ActionSent = false;
	}
	else if (ActionSent == false)
	{
		ActionSent = true;
		
		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC1_TX_EPNUM);

		/* Write the String to the Endpoint */
		Endpoint_Write_Stream_LE(ReportString, strlen(ReportString));
		
		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Wait until the endpoint is ready for another packet */
		while (!(Endpoint_IsINReady()));
		
		/* Send an empty packet to ensure that the host does not buffer data sent to it */
		Endpoint_ClearIN();
	}

	/* Select the Serial Rx Endpoint */
	Endpoint_SelectEndpoint(CDC1_RX_EPNUM);
	
	/* Throw away any received data from the host */
	if (Endpoint_IsOUTReceived())
	  Endpoint_ClearOUT();
}

/** Function to manage CDC data transmission and reception to and from the host for the second CDC interface, which echoes back
 *  all data sent to it from the host.
 */
TASK(CDC2_Task)
{
	/* Select the Serial Rx Endpoint */
	Endpoint_SelectEndpoint(CDC2_RX_EPNUM);
	
	/* Check to see if any data has been received */
	if (Endpoint_IsOUTReceived())
	{
		/* Create a temp buffer big enough to hold the incoming endpoint packet */
		uint8_t  Buffer[Endpoint_BytesInEndpoint()];
		
		/* Remember how large the incoming packet is */
		uint16_t DataLength = Endpoint_BytesInEndpoint();
	
		/* Read in the incoming packet into the buffer */
		Endpoint_Read_Stream_LE(&Buffer, DataLength);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearOUT();

		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC2_TX_EPNUM);
		
		/* Write the received data to the endpoint */
		Endpoint_Write_Stream_LE(&Buffer, DataLength);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* Wait until the endpoint is ready for the next packet */
		while (!(Endpoint_IsINReady()));

		/* Send an empty packet to prevent host buffering */
		Endpoint_ClearIN();
	}
}
