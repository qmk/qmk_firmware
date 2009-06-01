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
 
#include "DualCDC.h"

USB_ClassInfo_CDC_t VirtualSerial1_CDC_Interface =
	{
		.ControlInterfaceNumber     = 0,

		.DataINEndpointNumber       = CDC1_TX_EPNUM,
		.DataINEndpointSize         = CDC_TXRX_EPSIZE,

		.DataOUTEndpointNumber      = CDC1_RX_EPNUM,
		.DataOUTEndpointSize        = CDC_TXRX_EPSIZE,

		.NotificationEndpointNumber = CDC1_NOTIFICATION_EPNUM,
		.NotificationEndpointSize   = CDC_NOTIFICATION_EPSIZE,
	};

USB_ClassInfo_CDC_t VirtualSerial2_CDC_Interface =
	{
		.ControlInterfaceNumber     = 0,

		.DataINEndpointNumber       = CDC2_TX_EPNUM,
		.DataINEndpointSize         = CDC_TXRX_EPSIZE,

		.DataOUTEndpointNumber      = CDC2_RX_EPNUM,
		.DataOUTEndpointSize        = CDC_TXRX_EPSIZE,

		.NotificationEndpointNumber = CDC2_NOTIFICATION_EPNUM,
		.NotificationEndpointSize   = CDC_NOTIFICATION_EPSIZE,
	};

int main(void)
{
	SetupHardware();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		CheckJoystickMovement();

		uint16_t BytesToDiscard = USB_CDC_BytesReceived(&VirtualSerial1_CDC_Interface);
		while (BytesToDiscard--)
		  USB_CDC_ReceiveByte(&VirtualSerial1_CDC_Interface);

		uint16_t BytesToEcho = USB_CDC_BytesReceived(&VirtualSerial2_CDC_Interface);
		while (BytesToEcho--)
		  USB_CDC_SendByte(&VirtualSerial2_CDC_Interface, USB_CDC_ReceiveByte(&VirtualSerial2_CDC_Interface));
		  
		USB_CDC_USBTask(&VirtualSerial1_CDC_Interface);
		USB_CDC_USBTask(&VirtualSerial2_CDC_Interface);
		USB_USBTask();
	}
}

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

void CheckJoystickMovement(void)
{
	uint8_t     JoyStatus_LCL = Joystick_GetStatus();
	char*       ReportString  = NULL;
	static bool ActionSent = false;

	char* JoystickStrings[] =
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
		
		USB_CDC_SendString(&VirtualSerial1_CDC_Interface, ReportString, strlen(ReportString));		
	}
}

void EVENT_USB_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

void EVENT_USB_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

void EVENT_USB_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	if (!(USB_CDC_ConfigureEndpoints(&VirtualSerial1_CDC_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

	if (!(USB_CDC_ConfigureEndpoints(&VirtualSerial2_CDC_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_UnhandledControlPacket(void)
{
	USB_CDC_ProcessControlPacket(&VirtualSerial1_CDC_Interface);
	USB_CDC_ProcessControlPacket(&VirtualSerial2_CDC_Interface);
}
