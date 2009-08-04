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
 *  Main source file for the CDC demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "CDC.h"

/* Globals: */
/** Contains the current baud rate and other settings of the virtual serial port. While this demo does not use
 *  the physical USART and thus does not use these settings, they must still be retained and returned to the host
 *  upon request or the host will assume the device is non-functional.
 *
 *  These values are set by the host via a class-specific request, however they are not required to be used accurately.
 *  It is possible to completely ignore these value or use other settings as the host is completely unaware of the physical
 *  serial link characteristics and instead sends and receives data in endpoint streams.
 */
CDC_Line_Coding_t LineEncoding = { .BaudRateBPS = 0,
                                   .CharFormat  = OneStopBit,
                                   .ParityType  = Parity_None,
                                   .DataBits    = 8            };

#if 0
/* NOTE: Here you can set up a standard stream using the created virtual serial port, so that the standard stream functions in
 *       <stdio.h> can be used on the virtual serial port (e.g. fprintf(&USBSerial, "Test"); to print a string).
 */
	
static int CDC_putchar(char c, FILE *stream)
{	  
	Endpoint_SelectEndpoint(CDC_TX_EPNUM);

	if (!(LineEncoding.BaudRateBPS))
	  return -1;
	
	while (!(Endpoint_IsReadWriteAllowed()))
	{
		if (USB_DeviceState != DEVICE_STATE_Configured)
		  return -1;
	}

	Endpoint_Write_Byte(c);
	Endpoint_ClearIN();
	
	return 0;
}

static int CDC_getchar(FILE *stream)
{
	int c;

	if (!(LineEncoding.BaudRateBPS))
	  return -1;

	Endpoint_SelectEndpoint(CDC_RX_EPNUM);
	
	for (;;)
	{
		while (!(Endpoint_IsReadWriteAllowed()))
		{
			if (USB_DeviceState != DEVICE_STATE_Configured)
			  return -1;
		}
	
		if (!(Endpoint_BytesInEndpoint()))
		{
			Endpoint_ClearOUT();
		}
		else
		{
			c = Endpoint_Read_Byte();
			break;
		}
	}
	
	return c;
}

static FILE USBSerial = FDEV_SETUP_STREAM(CDC_putchar, CDC_getchar, _FDEV_SETUP_RW);
#endif

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		CDC_Task();
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
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs and stops the USB management and CDC management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured and the CDC management task started.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup CDC Notification, Rx and Tx Endpoints */
	if (!(Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPNUM, EP_TYPE_INTERRUPT,
		                             ENDPOINT_DIR_IN, CDC_NOTIFICATION_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
	
	if (!(Endpoint_ConfigureEndpoint(CDC_TX_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_IN, CDC_TXRX_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
	
	if (!(Endpoint_ConfigureEndpoint(CDC_RX_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_OUT, CDC_TXRX_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the CDC control commands,
 *  which are all issued via the control endpoint), so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	/* Process CDC specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_GetLineEncoding:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{	
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();

				/* Write the line coding data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&LineEncoding, sizeof(CDC_Line_Coding_t));
				
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
				Endpoint_Read_Control_Stream_LE(&LineEncoding, sizeof(CDC_Line_Coding_t));

				/* Finalize the stream transfer to clear the last packet from the host */
				Endpoint_ClearIN();
			}
	
			break;
		case REQ_SetControlLineState:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Acknowledge the SETUP packet, ready for data transfer */
				Endpoint_ClearSETUP();
				
				/* NOTE: Here you can read in the line state mask from the host, to get the current state of the output handshake
				         lines. The mask is read in from the wValue parameter in USB_ControlRequest, and can be masked against the
						 CONTROL_LINE_OUT_* masks to determine the RTS and DTR line states using the following code:
				*/
				
				Endpoint_ClearStatusStage();
			}
	
			break;
	}
}

/** Function to manage CDC data transmission and reception to and from the host. */
void CDC_Task(void)
{
	char*       ReportString    = NULL;
	uint8_t     JoyStatus_LCL   = Joystick_GetStatus();
	static bool ActionSent      = false;
	char*       JoystickStrings[] =
					{
						"Joystick Up\r\n",
						"Joystick Down\r\n",
						"Joystick Left\r\n",
						"Joystick Right\r\n",
						"Joystick Pressed\r\n",
					};
	
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;
	  
#if 0
	/* NOTE: Here you can use the notification endpoint to send back line state changes to the host, for the special RS-232
	 *       handshake signal lines (and some error states), via the CONTROL_LINE_IN_* masks and the following code:
	 */
	USB_Notification_Header_t Notification = (USB_Notification_Header_t)
		{
			.NotificationType = (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE),
			.Notification     = NOTIF_SerialState,
			.wValue           = 0,
			.wIndex           = 0,
			.wLength          = sizeof(uint16_t),
		};
		
	uint16_t LineStateMask;
	
	// Set LineStateMask here to a mask of CONTROL_LINE_IN_* masks to set the input handshake line states to send to the host
	
	Endpoint_SelectEndpoint(CDC_NOTIFICATION_EPNUM);
	Endpoint_Write_Stream_LE(&Notification, sizeof(Notification));
	Endpoint_Write_Stream_LE(&LineStateMask, sizeof(LineStateMask));
	Endpoint_ClearIN();
#endif

	/* Determine if a joystick action has occurred */
	if (JoyStatus_LCL & JOY_UP)
	  ReportString = JoystickStrings[0];
	else if (JoyStatus_LCL & JOY_DOWN)
	  ReportString = JoystickStrings[1];
	else if (JoyStatus_LCL & JOY_LEFT)
	  ReportString = JoystickStrings[2];
	else if (JoyStatus_LCL & JOY_RIGHT)
	  ReportString = JoystickStrings[3];
	else if (JoyStatus_LCL & JOY_PRESS)
	  ReportString = JoystickStrings[4];

	/* Flag management - Only allow one string to be sent per action */
	if (ReportString == NULL)
	{
		ActionSent = false;
	}
	else if ((ActionSent == false) && LineEncoding.BaudRateBPS)
	{
		ActionSent = true;

		/* Select the Serial Tx Endpoint */
		Endpoint_SelectEndpoint(CDC_TX_EPNUM);

		/* Write the String to the Endpoint */
		Endpoint_Write_Stream_LE(ReportString, strlen(ReportString));
		
		/* Remember if the packet to send completely fills the endpoint */
		bool IsFull = (Endpoint_BytesInEndpoint() == CDC_TXRX_EPSIZE);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();

		/* If the last packet filled the endpoint, send an empty packet to release the buffer on 
		 * the receiver (otherwise all data will be cached until a non-full packet is received) */
		if (IsFull)
		{
			/* Wait until the endpoint is ready for another packet */
			while (!(Endpoint_IsINReady()))
			{
				if (USB_DeviceState == DEVICE_STATE_Unattached)
				  return;
			}
			
			/* Send an empty packet to ensure that the host does not buffer data sent to it */
			Endpoint_ClearIN();
		}
	}

	/* Select the Serial Rx Endpoint */
	Endpoint_SelectEndpoint(CDC_RX_EPNUM);
	
	/* Throw away any received data from the host */
	if (Endpoint_IsOUTReceived())
	  Endpoint_ClearOUT();
}
