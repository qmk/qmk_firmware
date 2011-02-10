/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
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
 *  Main source file for the AudioOutput demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "AudioOutput.h"

/** LUFA Audio Class driver interface configuration and state information. This structure is
 *  passed to all Audio Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_Audio_Device_t Speaker_Audio_Interface =
	{
		.Config =
			{
				.StreamingInterfaceNumber = 1,

				.DataOUTEndpointNumber    = AUDIO_STREAM_EPNUM,
				.DataOUTEndpointSize      = AUDIO_STREAM_EPSIZE,
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	sei();

	for (;;)
	{
		Audio_Device_USBTask(&Speaker_Audio_Interface);
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
}

/** ISR to handle the reloading of the PWM timer with the next sample. */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	uint8_t PrevEndpoint = Endpoint_GetCurrentEndpoint();

	if (Audio_Device_IsSampleReceived(&Speaker_Audio_Interface))
	{
		/* Retrieve the signed 16-bit left and right audio samples, convert to 8-bit */
		int8_t LeftSample_8Bit  = (Audio_Device_ReadSample16(&Speaker_Audio_Interface) >> 8);
		int8_t RightSample_8Bit = (Audio_Device_ReadSample16(&Speaker_Audio_Interface) >> 8);

		/* Mix the two channels together to produce a mono, 8-bit sample */
		int8_t MixedSample_8Bit = (((int16_t)LeftSample_8Bit + (int16_t)RightSample_8Bit) >> 1);

		#if defined(AUDIO_OUT_MONO)
		/* Load the sample into the PWM timer channel */
		OCR3A = (MixedSample_8Bit ^ (1 << 7));
		#elif defined(AUDIO_OUT_STEREO)
		/* Load the dual 8-bit samples into the PWM timer channels */
		OCR3A = (LeftSample_8Bit  ^ (1 << 7));
		OCR3B = (RightSample_8Bit ^ (1 << 7));
		#elif defined(AUDIO_OUT_PORTC)
		/* Load the 8-bit mixed sample into PORTC */
		PORTC = MixedSample_8Bit;
		#endif

		uint8_t LEDMask = LEDS_NO_LEDS;

		/* Turn on LEDs as the sample amplitude increases */
		if (MixedSample_8Bit > 16)
		  LEDMask = (LEDS_LED1 | LEDS_LED2 | LEDS_LED3 | LEDS_LED4);
		else if (MixedSample_8Bit > 8)
		  LEDMask = (LEDS_LED1 | LEDS_LED2 | LEDS_LED3);
		else if (MixedSample_8Bit > 4)
		  LEDMask = (LEDS_LED1 | LEDS_LED2);
		else if (MixedSample_8Bit > 2)
		  LEDMask = (LEDS_LED1);

		LEDs_SetAllLEDs(LEDMask);
	}
	
	Endpoint_SelectEndpoint(PrevEndpoint);	
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Sample reload timer initialization */
	TIMSK0  = (1 << OCIE0A);
	OCR0A   = ((F_CPU / 8 / AUDIO_SAMPLE_FREQUENCY) - 1);
	TCCR0A  = (1 << WGM01);  // CTC mode
	TCCR0B  = (1 << CS01);   // Fcpu/8 speed

	#if defined(AUDIO_OUT_MONO)
	/* Set speaker as output */
	DDRC   |= (1 << 6);
	#elif defined(AUDIO_OUT_STEREO)
	/* Set speakers as outputs */
	DDRC   |= ((1 << 6) | (1 << 5));
	#elif defined(AUDIO_OUT_PORTC)
	/* Set PORTC as outputs */
	DDRC   |= 0xFF;
	#endif

	#if (defined(AUDIO_OUT_MONO) || defined(AUDIO_OUT_STEREO))
	/* PWM speaker timer initialization */
	TCCR3A  = ((1 << WGM30) | (1 << COM3A1) | (1 << COM3A0)
	        | (1 << COM3B1) | (1 << COM3B0)); // Set on match, clear on TOP
	TCCR3B  = ((1 << WGM32) | (1 << CS30));  // Fast 8-Bit PWM, F_CPU speed
	#endif
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	/* Stop the sample reload timer */
	TCCR0B = 0;

	#if (defined(AUDIO_OUT_MONO) || defined(AUDIO_OUT_STEREO))
	/* Stop the PWM generation timer */
	TCCR3B = 0;
	#endif

	#if defined(AUDIO_OUT_MONO)
	/* Set speaker as input to reduce current draw */
	DDRC  &= ~(1 << 6);
	#elif defined(AUDIO_OUT_STEREO)
	/* Set speakers as inputs to reduce current draw */
	DDRC  &= ~((1 << 6) | (1 << 5));
	#elif defined(AUDIO_OUT_PORTC)
	/* Set PORTC low */
	PORTC = 0x00;
	#endif
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= Audio_Device_ConfigureEndpoints(&Speaker_Audio_Interface);

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	Audio_Device_ProcessControlRequest(&Speaker_Audio_Interface);
}

