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
 *  Main source file for the HotmailNotfier project. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "HotmailNotifier.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = 0,

				.DataINEndpointNumber           = CDC_TX_EPNUM,
				.DataINEndpointSize             = CDC_TXRX_EPSIZE,
				.DataINEndpointDoubleBank       = false,

				.DataOUTEndpointNumber          = CDC_RX_EPNUM,
				.DataOUTEndpointSize            = CDC_TXRX_EPSIZE,
				.DataOUTEndpointDoubleBank      = false,

				.NotificationEndpointNumber     = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize       = CDC_NOTIFICATION_EPSIZE,
				.NotificationEndpointDoubleBank = false,
			},
	};

/** Counter for the software PWM */
static volatile uint8_t SoftPWM_Count;

/** Duty cycle for the first software PWM channel */
static volatile uint8_t SoftPWM_Channel1_Duty;

/** Duty cycle for the second software PWM channel */
static volatile uint8_t SoftPWM_Channel2_Duty;

/** Duty cycle for the third software PWM channel */
static volatile uint8_t SoftPWM_Channel3_Duty;


/** Interrupt handler for managing the software PWM channels for the LEDs */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	uint8_t LEDMask = LEDS_ALL_LEDS;

	if (++SoftPWM_Count == 0x1F)
	  SoftPWM_Count = 0;

	if (SoftPWM_Count >= SoftPWM_Channel1_Duty)
	  LEDMask &= ~LEDS_LED1;

	if (SoftPWM_Count >= SoftPWM_Channel2_Duty)
	  LEDMask &= ~LEDS_LED2;

	if (SoftPWM_Count >= SoftPWM_Channel3_Duty)
	  LEDMask &= ~LEDS_LED3;
	  
	LEDs_SetAllLEDs(LEDMask);
}

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs
 */
static FILE USBSerialStream;

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	
	/* Create a regular blocking character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateBlockingStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

	for (;;)
	{
		/* Read in next LED colour command from the host */
		uint8_t ColorUpdate = fgetc(&USBSerialStream);
		
		/* Top 3 bits select the LED, bottom three control the brightness */
		uint8_t Channel = (ColorUpdate & 0b11100000);
		uint8_t Duty    = (ColorUpdate & 0b00011111);
		
		if (Channel & (1 << 5))
		  SoftPWM_Channel1_Duty = Duty;
		
		if (Channel & (1 << 6))
		  SoftPWM_Channel2_Duty = Duty;

		if (Channel & (1 << 7))
		  SoftPWM_Channel3_Duty = Duty;

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
	LEDs_Init();
	USB_Init();
	
	/* Timer Initialization */
	OCR0A  = 100;
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS00);
	TIMSK0 = (1 << OCIE0A);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Unhandled Control Request event. */
void EVENT_USB_Device_UnhandledControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}
