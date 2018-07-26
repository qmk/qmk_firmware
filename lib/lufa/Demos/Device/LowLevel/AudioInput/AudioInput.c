/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Main source file for the Audio Input demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include "AudioInput.h"

/** Flag to indicate if the streaming audio alternative interface has been selected by the host. */
static bool StreamingAudioInterfaceSelected = false;

/** Current audio sampling frequency of the streaming audio endpoint. */
static uint32_t CurrentAudioSampleFrequency = 48000;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
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
	LEDs_Init();
	Buttons_Init();
	ADC_Init(ADC_FREE_RUNNING | ADC_PRESCALE_32);
	ADC_SetupChannel(MIC_IN_ADC_CHANNEL);
	USB_Init();

	/* Start the ADC conversion in free running mode */
	ADC_StartReading(ADC_REFERENCE_AVCC | ADC_RIGHT_ADJUSTED | ADC_GET_CHANNEL_MASK(MIC_IN_ADC_CHANNEL));
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs, and
 *  configures the sample update and PWM timers.
 */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);

	/* Sample reload timer initialization */
	TIMSK0  = (1 << OCIE0A);
	OCR0A   = ((F_CPU / 8 / CurrentAudioSampleFrequency) - 1);
	TCCR0A  = (1 << WGM01);  // CTC mode
	TCCR0B  = (1 << CS01);   // Fcpu/8 speed
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs, disables the sample update and PWM output timers and stops the USB and Audio management tasks.
 */
void EVENT_USB_Device_Disconnect(void)
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
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup Audio Stream Endpoint */
	ConfigSuccess &= Endpoint_ConfigureEndpoint(AUDIO_STREAM_EPADDR, EP_TYPE_ISOCHRONOUS, AUDIO_STREAM_EPSIZE, 2);

	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	/* Process General and Audio specific control requests */
	switch (USB_ControlRequest.bRequest)
	{
		case REQ_SetInterface:
			/* Set Interface is not handled by the library, as its function is application-specific */
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();

				/* Check if the host is enabling the audio interface (setting AlternateSetting to 1) */
				StreamingAudioInterfaceSelected = ((USB_ControlRequest.wValue) != 0);
			}

			break;
		case AUDIO_REQ_GetStatus:
			/* Get Status request can be directed at either the interface or endpoint, neither is currently used
			 * according to the latest USB Audio 1.0 standard, but must be ACKed with no data when requested */
			if ((USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE)) ||
			    (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_ENDPOINT)))
			{
				Endpoint_ClearSETUP();
				Endpoint_ClearStatusStage();
			}

			break;
		case AUDIO_REQ_SetCurrent:
			if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Extract out the relevant request information to get the target Endpoint address and control being set */
				uint8_t EndpointAddress = (uint8_t)USB_ControlRequest.wIndex;
				uint8_t EndpointControl = (USB_ControlRequest.wValue >> 8);

				/* Only handle SET CURRENT requests to the audio endpoint's sample frequency property */
				if ((EndpointAddress == AUDIO_STREAM_EPADDR) && (EndpointControl == AUDIO_EPCONTROL_SamplingFreq))
				{
					uint8_t SampleRate[3];

					Endpoint_ClearSETUP();
					Endpoint_Read_Control_Stream_LE(SampleRate, sizeof(SampleRate));
					Endpoint_ClearIN();

					/* Set the new sampling frequency to the value given by the host */
					CurrentAudioSampleFrequency = (((uint32_t)SampleRate[2] << 16) | ((uint32_t)SampleRate[1] << 8) | (uint32_t)SampleRate[0]);

					/* Adjust sample reload timer to the new frequency */
					OCR0A = ((F_CPU / 8 / CurrentAudioSampleFrequency) - 1);
				}
			}

			break;
		case AUDIO_REQ_GetCurrent:
			if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT))
			{
				/* Extract out the relevant request information to get the target Endpoint address and control being retrieved */
				uint8_t EndpointAddress = (uint8_t)USB_ControlRequest.wIndex;
				uint8_t EndpointControl = (USB_ControlRequest.wValue >> 8);

				/* Only handle GET CURRENT requests to the audio endpoint's sample frequency property */
				if ((EndpointAddress == AUDIO_STREAM_EPADDR) && (EndpointControl == AUDIO_EPCONTROL_SamplingFreq))
				{
					uint8_t SampleRate[3];

					/* Convert the sampling rate value into the 24-bit format the host expects for the property */
					SampleRate[2] = (CurrentAudioSampleFrequency >> 16);
					SampleRate[1] = (CurrentAudioSampleFrequency >> 8);
					SampleRate[0] = (CurrentAudioSampleFrequency &  0xFF);

					Endpoint_ClearSETUP();
					Endpoint_Write_Control_Stream_LE(SampleRate, sizeof(SampleRate));
					Endpoint_ClearOUT();
				}
			}

			break;
	}
}

/** ISR to handle the reloading of the data endpoint with the next sample. */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	uint8_t PrevEndpoint = Endpoint_GetCurrentEndpoint();

	/* Select the audio stream endpoint */
	Endpoint_SelectEndpoint(AUDIO_STREAM_EPADDR);

	/* Check if the current endpoint can be written to and that the audio interface is enabled */
	if (Endpoint_IsINReady() && StreamingAudioInterfaceSelected)
	{
		int16_t AudioSample;

		#if defined(USE_TEST_TONE)
			static uint8_t SquareWaveSampleCount;
			static int16_t CurrentWaveValue;

			/* In test tone mode, generate a square wave at 1/256 of the sample rate */
			if (SquareWaveSampleCount++ == 0xFF)
			  CurrentWaveValue ^= 0x8000;

			/* Only generate audio if the board button is being pressed */
			AudioSample = (Buttons_GetStatus() & BUTTONS_BUTTON1) ? CurrentWaveValue : 0;
		#else
			/* Audio sample is ADC value scaled to fit the entire range */
			AudioSample = ((SAMPLE_MAX_RANGE / ADC_MAX_RANGE) * ADC_GetResult());

			#if defined(MICROPHONE_BIASED_TO_HALF_RAIL)
			/* Microphone is biased to half rail voltage, subtract the bias from the sample value */
			AudioSample -= (SAMPLE_MAX_RANGE / 2);
			#endif
		#endif

		/* Write the sample to the buffer */
		Endpoint_Write_16_LE(AudioSample);

		/* Check to see if the bank is now full */
		if (!(Endpoint_IsReadWriteAllowed()))
		{
			/* Send the full packet to the host */
			Endpoint_ClearIN();
		}
	}

	Endpoint_SelectEndpoint(PrevEndpoint);
}

