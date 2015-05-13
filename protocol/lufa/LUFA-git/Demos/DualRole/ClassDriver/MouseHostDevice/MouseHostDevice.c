/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
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
 *  Main source file for the MouseHostDevice demo. This file contains the main tasks of
 *  the demo and is responsible for the overall control flow of the demo.
 */

#include "MouseHostDevice.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Mouse Host/Device Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		/* Determine which USB mode we are currently in */
		if (USB_CurrentMode == USB_MODE_Host)
		{
			MouseHost_Task();
			HID_Host_USBTask(&Mouse_HID_Host_Interface);
		}
		else
		{
			HID_Device_USBTask(&Mouse_HID_Device_Interface);
		}

		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#endif

	/* Hardware Initialization */
	Serial_Init(9600, false);
	LEDs_Init();
	Joystick_Init();
	Buttons_Init();
	USB_Init(USB_MODE_UID);

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);
}

/** Event handler for the library USB mode change event. */
void EVENT_USB_UIDChange(void)
{
	printf_P(PSTR(ESC_FG_YELLOW "UID Change to %S mode\r\n" ESC_FG_WHITE),
	         (USB_CurrentMode == USB_MODE_Device) ? PSTR("Device") : PSTR("Host"));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

