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
 *  application by the library (see library documentation for more details on USB events).
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

	puts_P(PSTR(ESC_FG_RED ESC_INVERSE_ON "\r\n**PROGRAM ABORT**" ESC_FG_WHITE));
	for (;;);
}

/** Event handler for the USB_UIDChange event. When fired, the event is logged to the USART. */
void EVENT_USB_UIDChange(void)
{
	char* ModeStrPtr;

	puts_P(PSTR(ESC_FG_RED EVENT_PREFIX "UID Change\r\n"));

	if (USB_CurrentMode == USB_MODE_DEVICE)
	  ModeStrPtr = PSTR("DEVICE");
	else if (USB_CurrentMode == USB_MODE_HOST)
	  ModeStrPtr = PSTR("HOST");
	else
	  ModeStrPtr = PSTR("N/A");

	printf_P(PSTR(" -- New Mode %S\r\n" ESC_FG_WHITE), ModeStrPtr);
}

/**
 *  Event handler for the USB_InitFailure event. When fired, the event is logged to the USART and the program
 *  execution aborted.
 */
void EVENT_USB_InitFailure(const uint8_t ErrorCode)
{
	char* ModeStrPtr;
	
	puts_P(PSTR(ESC_FG_RED EVENT_PREFIX "Power On Fail\r\n"));

	if (USB_CurrentMode == USB_MODE_DEVICE)
	  ModeStrPtr = PSTR("DEVICE");
	else if (USB_CurrentMode == USB_MODE_HOST)
	  ModeStrPtr = PSTR("HOST");
	else
	  ModeStrPtr = PSTR("N/A");
	
	printf_P(PSTR(" -- Mode %S\r\n"
	              " -- Error Code %d\r\n" ESC_FG_WHITE), ModeStrPtr, ErrorCode);

	Abort_Program();
}

/** Event handler for the USB_Device_Connect event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_Connect(void)
{
	puts_P(PSTR(ESC_FG_GREEN EVENT_PREFIX "USB Connect\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Device_Disconnect event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_Disconnect(void)
{
	puts_P(PSTR(ESC_FG_GREEN EVENT_PREFIX "USB Disconnect\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Device_Suspend event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_Suspend(void)
{
	puts_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "USB Sleep\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Device_WakeUp event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_WakeUp(void)
{
	puts_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "USB Wakeup\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Device_Reset event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_Reset(void)
{
	puts_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "USB Reset\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Device_UnhandledControlRequest event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	printf_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "Ctrl Request\r\n"
	                                         " -- Req Data %d\r\n"
	                                         " -- Req Type %d\r\n"
	                                         " -- Req Length %d\r\n" ESC_FG_WHITE), USB_ControlRequest.bRequest,
	                                                                                USB_ControlRequest.bmRequestType,
	                                                                                USB_ControlRequest.wLength);
}

/** Event handler for the USB_Device_ConfigurationChanged event. When fired, the event is logged to the USART. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	puts_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "Configuration Number Changed\r\n" ESC_FG_WHITE));
}

/**
 *  Event handler for the USB_Host_HostError event. When fired, the event is logged to the USART and the program
 *  execution aborted.
 */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	printf_P(PSTR(ESC_FG_RED EVENT_PREFIX "Host Mode Error\r\n"
	                                      " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	Abort_Program();
}

/** Event handler for the USB_Host_DeviceEnumerationFailed event. When fired, the event is logged to the USART. */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED EVENT_PREFIX "Dev Enum Error\r\n"
	                                      " -- Error Code %d\r\n"
	                                      " -- Sub Error Code %d\r\n"
	                                      " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);
}

/** Event handler for the USB_Host_DeviceEnumerationComplete event. When fired, the event is logged to the USART. */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	puts_P(PSTR(ESC_FG_YELLOW EVENT_PREFIX "Device Enumeration Complete\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Host_DeviceAttached event. When fired, the event is logged to the USART. */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR(ESC_FG_GREEN EVENT_PREFIX "Device Attached\r\n" ESC_FG_WHITE));
}

/** Event handler for the USB_Host_DeviceUnattached event. When fired, the event is logged to the USART. */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN EVENT_PREFIX "Device Unattached\r\n" ESC_FG_WHITE));
}
