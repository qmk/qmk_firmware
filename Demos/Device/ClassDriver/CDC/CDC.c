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
 *  Main source file for the CDC demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "CDC.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber     = 0,

				.DataINEndpointNumber       = CDC_TX_EPNUM,
				.DataINEndpointSize         = CDC_TXRX_EPSIZE,

				.DataOUTEndpointNumber      = CDC_RX_EPNUM,
				.DataOUTEndpointSize        = CDC_TXRX_EPSIZE,

				.NotificationEndpointNumber = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize   = CDC_NOTIFICATION_EPSIZE,
			},
	};

#if 0
/* NOTE: Here you can set up a standard stream using the created virtual serial port, so that the standard stream functions in
 *       <stdio.h> can be used on the virtual serial port (e.g. fprintf(&USBSerial, "Test"); to print a string).
 */

static int CDC_putchar(char c, FILE *stream)
{
	CDC_Device_SendByte(&VirtualSerial_CDC_Interface, c);
	return 0;
}

static int CDC_getchar(FILE *stream)
{
	if (!(CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface)))
	  return -1;

	return CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
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
		CheckJoystickMovement();
		
		/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
		while (CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface))
		  CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
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

/** Checks for changes in the position of the board joystick, sending strings to the host upon each change. */
void CheckJoystickMovement(void)
{
	uint8_t     JoyStatus_LCL = Joystick_GetStatus();
	char*       ReportString  = NULL;
	static bool ActionSent    = false;
	
	char* const JoystickStrings[] =
		{
			"Joystick Up\r\n",
			"Joystick Down\r\n",
			"Joystick Left\r\n",
			"Joystick Right\r\n",
			"Joystick Pressed\r\n",
		};

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
	else
	  ActionSent = false;
	  
	if ((ReportString != NULL) && (ActionSent == false))
	{
		ActionSent = true;
		
		CDC_Device_SendString(&VirtualSerial_CDC_Interface, ReportString, strlen(ReportString));		
	}
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Unhandled Control Packet event. */
void EVENT_USB_UnhandledControlPacket(void)
{
	CDC_Device_ProcessControlPacket(&VirtualSerial_CDC_Interface);
}
