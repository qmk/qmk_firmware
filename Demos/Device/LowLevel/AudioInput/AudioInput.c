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
 *  Main source file for the Audio Input demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "AudioInput.h"

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
	ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_32);
	ADC_SetupChannel(MIC_IN_ADC_CHANNEL);
	USB_Init();
	
	/* Start the ADC conversion in free running mode */
	ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | MIC_IN_ADC_CHANNEL);
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
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and Audio management tasks.
 */
void EVENT_USB_Disconnect(void)
{
	/* Stop the sample reload timer */
	TCCR0B = 0;

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
		                             ENDPOINT_DIR_IN, AUDIO_STREAM_EPSIZE,
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
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsINReady()));
				Endpoint_ClearIN();
			}

			break;
	}
}

/** Task to manage the Audio interface, reading in ADC samples from the microphone, and them to the host. */
void USB_Audio_Task(void)
{
	/* Check to see if the streaming interface is selected, if not the host is not receiving audio */
	if (!(StreamingAudioInterfaceSelected))
	  return;

	/* Select the audio stream endpoint */
	Endpoint_SelectEndpoint(AUDIO_STREAM_EPNUM);
	
	/* Check if the current endpoint can be written to and that the next sample should be stored */
	if (Endpoint_IsINReady() && (TIFR0 & (1 << OCF0A)))
	{
		/* Clear the sample reload timer */
		TIFR0 |= (1 << OCF0A);

		/* Audio sample is ADC value scaled to fit the entire range */
		int16_t AudioSample = ((SAMPLE_MAX_RANGE / ADC_MAX_RANGE) * ADC_GetResult());
		
#if defined(MICROPHONE_BIASED_TO_HALF_RAIL)
		/* Microphone is biased to half rail voltage, subtract the bias from the sample value */
		AudioSample -= (SAMPLE_MAX_RANGE / 2));
#endif

		/* Write the sample to the buffer */
		Endpoint_Write_Word_LE(AudioSample);

		/* Check to see if the bank is now full */
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			/* Send the full packet to the host */
			Endpoint_ClearIN();
		}
	}
}
