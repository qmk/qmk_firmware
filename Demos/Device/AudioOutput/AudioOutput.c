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

#include "AudioOutput.h"

USB_ClassInfo_Audio_t Speaker_Audio_Interface =
	{
		.InterfaceNumber       = 0,

		.DataOUTEndpointNumber = AUDIO_STREAM_EPNUM,
		.DataOUTEndpointSize   = AUDIO_STREAM_EPSIZE,
	};

int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	for (;;)
	{
		if (Speaker_Audio_Interface.InterfaceEnabled)
		  ProcessNextSample();

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
	LEDs_Init();
	USB_Init();
}

void ProcessNextSample(void)
{
	if ((TIFR0 & (1 << OCF0A)) && USB_Audio_IsSampleReceived(&Speaker_Audio_Interface))
	{
		/* Clear the sample reload timer */
		TIFR0 |= (1 << OCF0A);

		/* Retrieve the signed 16-bit left and right audio samples */
		int16_t LeftSample_16Bit  = (int16_t)USB_Audio_ReadSample16();
		int16_t RightSample_16Bit = (int16_t)USB_Audio_ReadSample16();

		/* Massage signed 16-bit left and right audio samples into signed 8-bit */
		int8_t  LeftSample_8Bit   = (LeftSample_16Bit  >> 8);
		int8_t  RightSample_8Bit  = (RightSample_16Bit >> 8);
			
#if defined(AUDIO_OUT_MONO)
		/* Mix the two channels together to produce a mono, 8-bit sample */
		int8_t  MixedSample_8Bit  = (((int16_t)LeftSample_8Bit + (int16_t)RightSample_8Bit) >> 1);

		/* Load the sample into the PWM timer channel */
		OCRxA = ((uint8_t)MixedSample_8Bit ^ (1 << 7));
#elif defined(AUDIO_OUT_STEREO)
		/* Load the dual 8-bit samples into the PWM timer channels */
		OCRxA = ((uint8_t)LeftSample_8Bit  ^ (1 << 7));
		OCRxB = ((uint8_t)RightSample_8Bit ^ (1 << 7));
#elif defined(AUDIO_OUT_PORTC)
		/* Mix the two channels together to produce a mono, 8-bit sample */
		int8_t  MixedSample_8Bit  = (((int16_t)LeftSample_8Bit + (int16_t)RightSample_8Bit) >> 1);

		PORTC = MixedSample_8Bit;
#else
		uint8_t LEDMask = LEDS_NO_LEDS;

		/* Make left channel positive (absolute) */
		if (LeftSample_8Bit < 0)
		  LeftSample_8Bit = -LeftSample_8Bit;

		/* Make right channel positive (absolute) */
		if (RightSample_8Bit < 0)
		  RightSample_8Bit = -RightSample_8Bit;

		/* Set first LED based on sample value */
		if (LeftSample_8Bit < ((128 / 8) * 1))
		  LEDMask |= LEDS_LED2;
		else if (LeftSample_8Bit < ((128 / 8) * 3))
		  LEDMask |= (LEDS_LED1 | LEDS_LED2);
		else
		  LEDMask |= LEDS_LED1;

		/* Set second LED based on sample value */
		if (RightSample_8Bit < ((128 / 8) * 1))
		  LEDMask |= LEDS_LED4;
		else if (RightSample_8Bit < ((128 / 8) * 3))
		  LEDMask |= (LEDS_LED3 | LEDS_LED4);
		else
		  LEDMask |= LEDS_LED3;
		  
		LEDs_SetAllLEDs(LEDMask);
#endif
	}
}

void EVENT_USB_Connect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
	
	/* Sample reload timer initialization */
	OCR0A   = (F_CPU / AUDIO_SAMPLE_FREQUENCY) - 1;
	TCCR0A  = (1 << WGM01);  // CTC mode
	TCCR0B  = (1 << CS00);   // Fcpu speed

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
	TCCRxA  = ((1 << WGMx0) | (1 << COMxA1) | (1 << COMxA0)
							| (1 << COMxB1) | (1 << COMxB0)); // Set on match, clear on TOP
	TCCRxB  = ((1 << WGMx2) | (1 << CSx0));  // Fast 8-Bit PWM, Fcpu speed
#endif	
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and Audio management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	/* Stop the timers */
	TCCR0B = 0;
#if (defined(AUDIO_OUT_MONO) || defined(AUDIO_OUT_STEREO))
	TCCRxB = 0;
#endif		

#if defined(AUDIO_OUT_MONO)
	/* Set speaker as input to reduce current draw */
	DDRC   &= ~(1 << 6);
#elif defined(AUDIO_OUT_STEREO)
	/* Set speakers as inputs to reduce current draw */
	DDRC   &= ~((1 << 6) | (1 << 5));
#elif defined(AUDIO_OUT_PORTC)
	/* Set PORTC low */
	PORTC  = 0x00;
#endif
}

void EVENT_USB_ConfigurationChanged(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
	
	if (!(USB_Audio_ConfigureEndpoints(&Speaker_Audio_Interface)))
	  LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

void EVENT_USB_UnhandledControlPacket(void)
{
	USB_Audio_ProcessControlPacket(&Speaker_Audio_Interface);
}
