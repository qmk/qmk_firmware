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
 *  Main source file for the Audio Output demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */
 
#include "AudioOutput.h"

/** Flag to indicate if the streaming audio alternative interface has been selected by the host. */
bool StreamingAudioInterfaceSelected = false;

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	
	for (;;)
	{
		USB_Audio_Task();
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

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs, and
 *  configures the sample update and PWM timers.
 */
void EVENT_USB_Connect(void)
{
	/* Indicate USB enumerating */
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
	TCCR3A  = ((1 << WGM30) | (1 << COM3A1) | (1 << COM3A0)
	                        | (1 << COM3B1) | (1 << COM3B0)); // Set on match, clear on TOP
	TCCR3B  = ((1 << WGM32) | (1 << CS30));  // Fast 8-Bit PWM, Fcpu speed
#endif	
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and Audio management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Stop the timers */
	TCCR0B = 0;
#if (defined(AUDIO_OUT_MONO) || defined(AUDIO_OUT_STEREO))
	TCCR3B = 0;
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

	/* Indicate streaming audio interface not selected */
	StreamingAudioInterfaceSelected = false;

	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured.
 */
void EVENT_USB_ConfigurationChanged(void)
{
	/* Indicate USB connected and ready */
	LEDs_SetAllLEDs(LEDMASK_USB_READY);

	/* Setup audio stream endpoint */
	if (!(Endpoint_ConfigureEndpoint(AUDIO_STREAM_EPNUM, EP_TYPE_ISOCHRONOUS,
		                             ENDPOINT_DIR_OUT, AUDIO_STREAM_EPSIZE,
	                                 ENDPOINT_BANK_DOUBLE)))
	{
		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	}
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the Audio class-specific
 *  requests) so that they can be handled appropriately for the application.
 */
void EVENT_USB_UnhandledControlPacket(void)
{
	/* Process General and Audio specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SetInterface:
			/* Set Interface is not handled by the library, as its function is application-specific */
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				
				/* Check if the host is enabling the audio interface (setting AlternateSetting to 1) */
				StreamingAudioInterfaceSelected = ((USB_ControlRequest.wValue) != 0);
				
				Endpoint_ClearStatusStage();
			}

			break;
	}
}

/** Task to manage the Audio interface, reading in audio samples from the host, and outputting them to the speakers/LEDs as
 *  desired.
 */
void USB_Audio_Task(void)
{
	/* Device must be connected and configured for the task to run */
	if (USB_DeviceState != DEVICE_STATE_Configured)
	  return;

	/* Check to see if the streaming interface is selected, if not the host is not receiving audio */
	if (!(StreamingAudioInterfaceSelected))
	  return;	

	/* Select the audio stream endpoint */
	Endpoint_SelectEndpoint(AUDIO_STREAM_EPNUM);
	
	/* Check if the current endpoint can be read from (contains a packet) and that the next sample should be read */
	if (Endpoint_IsOUTReceived() && (TIFR0 & (1 << OCF0A)))
	{
		/* Clear the sample reload timer */
		TIFR0 |= (1 << OCF0A);

		/* Retrieve the signed 16-bit left and right audio samples */
		int16_t LeftSample_16Bit  = (int16_t)Endpoint_Read_Word_LE();
		int16_t RightSample_16Bit = (int16_t)Endpoint_Read_Word_LE();

		/* Check to see if the bank is now empty */
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			/* Acknowledge the packet, clear the bank ready for the next packet */
			Endpoint_ClearOUT();
		}

		/* Massage signed 16-bit left and right audio samples into signed 8-bit */
		int8_t  LeftSample_8Bit   = (LeftSample_16Bit  >> 8);
		int8_t  RightSample_8Bit  = (RightSample_16Bit >> 8);
			
#if defined(AUDIO_OUT_MONO)
		/* Mix the two channels together to produce a mono, 8-bit sample */
		int8_t  MixedSample_8Bit  = (((int16_t)LeftSample_8Bit + (int16_t)RightSample_8Bit) >> 1);

		/* Load the sample into the PWM timer channel */
		OCR3A = ((uint8_t)MixedSample_8Bit ^ (1 << 7));
#elif defined(AUDIO_OUT_STEREO)
		/* Load the dual 8-bit samples into the PWM timer channels */
		OCR3A = ((uint8_t)LeftSample_8Bit  ^ (1 << 7));
		OCR3B = ((uint8_t)RightSample_8Bit ^ (1 << 7));
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
