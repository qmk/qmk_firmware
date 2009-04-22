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
 *  This file contains dummy handlers for all the possible USB events passed to the
 *  application by the library (see Events.h documentation for more details on USB events).
 *
 *  Each event is caught and printed to the USART so that they may be monitored.
 */
 
#define  INCLUDE_FROM_TESTEVENTS_C
#include "TestEvents.h"

/** Simple routine which aborts the program execution when a fatal error occurs, and is passed to the
 *  application via an event. When run, this function shuts down the USB interface, indicates an error
 *  via the board LEDs, prints an error message to the USART and then enters an infinite loop, preventing
 *  any more application code (other than interrupts) from executing.
 */
static void Abort_Program(void)
{
	USB_ShutDown();

	LEDs_SetAllLEDs(LEDS_LED1 | LEDS_LED3);

	puts_P(PSTR(ESC_INVERSE_ON "\r\n**PROGRAM ABORT**"));
	for (;;);
}

/** Event handler for the USB_VBUSChange event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_VBUSChange)
{
	puts_P(PSTR(EVENT_PREFIX "VBUS Change\r\n"));
}

/** Event handler for the USB_VBUSConnect event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_VBUSConnect)
{
	puts_P(PSTR(EVENT_PREFIX "VBUS +\r\n"));
}

/** Event handler for the USB_VBUSDisconnect event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_VBUSDisconnect)
{
	puts_P(PSTR(EVENT_PREFIX "VBUS -\r\n"));
}

/**
 *  Event handler for the USB_Connect event. When fired, the event is logged to the USART and the
 *  USB task started.
 */
EVENT_HANDLER(USB_Connect)
{
	puts_P(PSTR(EVENT_PREFIX "USB  +\r\n"));
	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED3 | LEDS_LED4);
	
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

/**
 *  Event handler for the USB_Disconnect event. When fired, the event is logged to the USART and the
 *  USB task stopped.
 */
EVENT_HANDLER(USB_Disconnect)
{
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	puts_P(PSTR(EVENT_PREFIX "USB  -\r\n"));
	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED3 | LEDS_LED3);
}

/** Event handler for the USB_Suspend event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_Suspend)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_YELLOW "USB Sleep\r\n"));
	LEDs_SetAllLEDs(LEDS_ALL_LEDS);
}

/** Event handler for the USB_WakeUp event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_WakeUp)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_GREEN "USB Wakeup\r\n"));
	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED4);
}

/** Event handler for the USB_Reset event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_Reset)
{
	puts_P(PSTR(EVENT_PREFIX "USB Reset\r\n"));
}

/** Event handler for the USB_UIDChange event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_UIDChange)
{
	char* ModeStrPtr;

	puts_P(PSTR(EVENT_PREFIX "UID Change\r\n"));

	if (USB_CurrentMode == USB_MODE_DEVICE)
	  ModeStrPtr = PSTR("HOST");
	else if (USB_CurrentMode == USB_MODE_HOST)
	  ModeStrPtr = PSTR("DEVICE");
	else
	  ModeStrPtr = PSTR("N/A");
	
	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED3);

	printf_P(PSTR(" -- New Mode %S\r\n"), ModeStrPtr);
}

/**
 *  Event handler for the USB_PowerOnFail event. When fired, the event is logged to the USART and the program
 *  execution aborted.
 */
EVENT_HANDLER(USB_PowerOnFail)
{
	char* ModeStrPtr;
	
	puts_P(PSTR(EVENT_PREFIX ESC_BG_RED "Power On Fail\r\n"));

	if (USB_CurrentMode == USB_MODE_DEVICE)
	  ModeStrPtr = PSTR("DEVICE");
	else if (USB_CurrentMode == USB_MODE_HOST)
	  ModeStrPtr = PSTR("HOST");
	else
	  ModeStrPtr = PSTR("N/A");
	
	printf_P(PSTR(" -- Mode %S\r\n"), ModeStrPtr);
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	Abort_Program();
}

/**
 *  Event handler for the USB_HostError event. When fired, the event is logged to the USART and the program
 *  execution aborted.
 */
EVENT_HANDLER(USB_HostError)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_RED "Host Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	Abort_Program();
}

/** Event handler for the USB_DeviceEnumerationFailed event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_DeviceEnumerationFailed)
{
	puts_P(PSTR(ESC_BG_RED "Dev Enum Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);
}

/**
 *  Event handler for the USB_DeviceError event. When fired, the event is logged to the USART and the program
 *  execution aborted.
 */
EVENT_HANDLER(USB_DeviceError)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_RED "Device Mode Error\r\n"));
	printf_P(PSTR(" -- Error Code %d\r\n"), ErrorCode);

	Abort_Program();
}

/** Event handler for the USB_UnhandledControlPacket event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	puts_P(PSTR(EVENT_PREFIX "Ctrl Request\r\n"));
	printf_P(PSTR(" -- Req Data %d\r\n"), USB_ControlRequest.bRequest);
	printf_P(PSTR(" -- Req Type %d\r\n"), USB_ControlRequest.bmRequestType);
	printf_P(PSTR(" -- Req Length %d\r\n"), USB_ControlRequest.wLength);
}

/** Event handler for the USB_ConfigurationChanged event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	puts_P(PSTR(EVENT_PREFIX "Configuration Number Changed\r\n"));

	LEDs_SetAllLEDs(LEDS_LED2 | LEDS_LED4);
}

/** Event handler for the USB_DeviceAttached event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_DeviceAttached)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_GREEN "Device +\r\n"));

	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

/** Event handler for the USB_DeviceUnattached event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_DeviceUnattached)
{
	puts_P(PSTR(EVENT_PREFIX ESC_BG_YELLOW "Device -\r\n"));
}

/** Event handler for the USB_DeviceEnumerationComplete event. When fired, the event is logged to the USART. */
EVENT_HANDLER(USB_DeviceEnumerationComplete)
{
	puts_P(PSTR(EVENT_PREFIX "Device Enumeration Complete\r\n"));
}
