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
 
/* ---   Project Configuration (Choose ONE)   --- */
//#define AUDIO_OUT_MONO
#define AUDIO_OUT_STEREO
//#define AUDIO_OUT_LEDS
//#define AUDIO_OUT_PORTC
/* --- --- --- --- --- --- --- ---  ---  ---  --- */

#include "AudioOutput.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "LUFA AudioOut App");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: USB_Audio_Task       , TaskStatus: TASK_STOP },
};


/** Main program entry point. This routine configures the hardware required by the application, then
 *  starts the scheduler to run the application tasks.
 */
int main(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	
	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();

	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs, and
 *  configures the sample update and PWM timers.
 */
EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);

	/* Indicate USB enumerating */
	UpdateStatus(Status_USBEnumerating);
	
	/* Sample reload timer initialization */
	OCR0A   = (F_CPU / AUDIO_SAMPLE_FREQUENCY);
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
EVENT_HANDLER(USB_Disconnect)
{
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

	/* Stop running audio and USB management tasks */
	Scheduler_SetTaskMode(USB_Audio_Task, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);

	/* Indicate USB not ready */
	UpdateStatus(Status_USBNotReady);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup audio stream endpoint */
	Endpoint_ConfigureEndpoint(AUDIO_STREAM_EPNUM, EP_TYPE_ISOCHRONOUS,
		                       ENDPOINT_DIR_OUT, AUDIO_STREAM_EPSIZE,
	                           ENDPOINT_BANK_DOUBLE);

	/* Indicate USB connected and ready */
	UpdateStatus(Status_USBReady);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library (including the Audio class-specific
 *  requests) so that they can be handled appropriately for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Process General and Audio specific control requests */
	switch (bRequest)
	{
		case REQ_SetInterface:
			/* Set Interface is not handled by the library, as its function is application-specific */
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE))
			{
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearSetupReceived();
				
				/* Check if the host is enabling the audio interface (setting AlternateSetting to 1) */
				if (wValue)
				{
					/* Start audio task */
					Scheduler_SetTaskMode(USB_Audio_Task, TASK_RUN);
				}
				else
				{
					/* Stop audio task */
					Scheduler_SetTaskMode(USB_Audio_Task, TASK_STOP);				
				}
				
				/* Handshake the request */
				Endpoint_ClearSetupIN();
			}

			break;
	}
}

/** Function to manage status updates to the user. This is done via LEDs on the given board, if available, but may be changed to
 *  log to a serial port, or anything else that is suitable for status updates.
 *
 *  \param CurrentStatus  Current status of the system, from the AudioOutput_StatusCodes_t enum
 */
void UpdateStatus(uint8_t CurrentStatus)
{
	uint8_t LEDMask = LEDS_NO_LEDS;
	
	/* Set the LED mask to the appropriate LED mask based on the given status code */
	switch (CurrentStatus)
	{
		case Status_USBNotReady:
			LEDMask = (LEDS_LED1);
			break;
		case Status_USBEnumerating:
			LEDMask = (LEDS_LED1 | LEDS_LED2);
			break;
		case Status_USBReady:
			LEDMask = (LEDS_LED2 | LEDS_LED4);
			break;
	}
	
	/* Set the board LEDs to the new LED mask */
	LEDs_SetAllLEDs(LEDMask);
}

/** Task to manage the Audio interface, reading in audio samples from the host, and outputting them to the speakers/LEDs as
 *  desired.
 */
TASK(USB_Audio_Task)
{
	/* Select the audio stream endpoint */
	Endpoint_SelectEndpoint(AUDIO_STREAM_EPNUM);
	
	/* Check if the current endpoint can be read from (contains a packet) and that the next sample should be read */
	if (Endpoint_ReadWriteAllowed() && (TIFR0 & (1 << OCF0A)))
	{
		/* Clear the sample reload timer */
		TIFR0 |= (1 << OCF0A);

		/* Retreive the signed 16-bit left and right audio samples */
		int16_t LeftSample_16Bit  = (int16_t)Endpoint_Read_Word_LE();
		int16_t RightSample_16Bit = (int16_t)Endpoint_Read_Word_LE();

		/* Check to see if the bank is now empty */
		if (!(Endpoint_ReadWriteAllowed()))
		{
			/* Acknowedge the packet, clear the bank ready for the next packet */
			Endpoint_ClearCurrentBank();
		}

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
