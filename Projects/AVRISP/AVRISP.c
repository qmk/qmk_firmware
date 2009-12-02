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
 *  Main source file for the AVRISP project. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "AVRISP.h"

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	V2Params_LoadNonVolatileParamValues();
	
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Process_AVRISP_Commands();
		
		V2Params_UpdateParamValues();
		
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
	LEDs_Init();
	USB_Init();
	SerialStream_Init(9600, true);

	#if defined(ADC)
	/* Initialize the ADC converter for VTARGET level detection on supported AVR models */
	ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_128);
	ADC_SetupChannel(VTARGET_ADC_CHANNEL);
	ADC_StartReading(VTARGET_ADC_CHANNEL | ADC_RIGHT_ADJUSTED | ADC_REFERENCE_AVCC);
	#endif
	
	/* Millisecond timer initialization for timeouts and delays */
	OCR0A  = ((F_CPU / 64) / 1000);
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup AVRISP data Endpoints */
	if (!(Endpoint_ConfigureEndpoint(AVRISP_DATA_EPNUM, EP_TYPE_BULK,
		                             ENDPOINT_DIR_OUT, AVRISP_DATA_EPSIZE,
	                                 ENDPOINT_BANK_SINGLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Processes incoming V2 Protocol commands from the host, returning a response when required. */
void Process_AVRISP_Commands(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	Endpoint_SelectEndpoint(AVRISP_DATA_EPNUM);
	
	/* Check to see if a V2 Protocol command has been received */
	if (Endpoint_IsOUTReceived())
	{
		LEDs_SetAllLEDs(LEDMASK_BUSY);

		/* Pass off processing of the V2 Protocol command to the V2 Protocol handler */
		V2Protocol_ProcessCommand();

		LEDs_SetAllLEDs(LEDMASK_USB_READY);
	}
}

