/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Denver Gingerich (denver [at] ossguy [dot] com)
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
 *  Main source file for the MagStripe application. This file contains the code which drives
 *  the USB keyboard interface from the magnetic card stripe reader device.
 */
 
#include "Magstripe.h"

/* Project Tags, for reading out using the ButtLoad project */
BUTTLOADTAG(ProjName,    "Magstripe Reader");
BUTTLOADTAG(BuildTime,   __TIME__);
BUTTLOADTAG(BuildDate,   __DATE__);
BUTTLOADTAG(LUFAVersion, "LUFA V" LUFA_VERSION_STRING);

/* Scheduler Task List */
TASK_LIST
{
	{ Task: USB_USBTask          , TaskStatus: TASK_STOP },
	{ Task: USB_Keyboard_Report  , TaskStatus: TASK_STOP },
	{ Task: Magstripe_Read       , TaskStatus: TASK_STOP },
};

/* Global Variables */
/** Indicates if the device is using Report Protocol mode, instead of Boot Protocol mode. Boot Protocol mode
 *  is a special reporting mode used by compatible PC BIOS to support USB keyboards before a full OS and USB
 *  driver has been loaded, by using predefined report structures indicated in the USB HID standard.
 */
bool UsingReportProtocol = true;

/** Total idle period in milliseconds set by the host via a SetIdle request, used to silence the report endpoint
 *  until the report data changes or the idle period elapsed. Generally used to implement hardware key repeats, or
 *  by some BIOS to reduce the number of reports when in Boot Protocol mode.
 */
uint8_t IdleCount = 0;

/** Milliseconds remaining counter for the HID class SetIdle and GetIdle requests, used to silence the report
 *  endpoint for an amount of time indicated by the host or until the report changes.
 */
uint16_t IdleMSRemaining = 0;

/** Circular buffer to hold the read bits from track 1 of the inserted magnetic card. */
BitBuffer_t Track1Data;

/** Circular buffer to hold the read bits from track 2 of the inserted magnetic card. */
BitBuffer_t Track2Data;

/** Circular buffer to hold the read bits from track 3 of the inserted magnetic card. */
BitBuffer_t Track3Data;

/** Delay counter between sucessive key strokes. This is to prevent the OS from ignoring multiple keys in a short
 *  period of time due to key repeats. Two milliseconds works for most OSes.
 */
uint8_t KeyDelayRemaining;


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
	Magstripe_Init();
	
	/* Buffer Initialization */
	BitBuffer_Init(&Track1Data);
	BitBuffer_Init(&Track2Data);
	BitBuffer_Init(&Track3Data);
	
	/* Millisecond timer initialization, with output compare interrupt enabled for the idle timing */
	OCR0A  = 0xFA;
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	TIMSK0 = (1 << OCIE0A);
	
	/* Initialize Scheduler so that it can be used */
	Scheduler_Init();

	/* Initialize USB Subsystem */
	USB_Init();
	
	/* Scheduling - routine never returns, so put this last in the main function */
	Scheduler_Start();
}

/** Event handler for the USB_Connect event. This starts the USB task. */
EVENT_HANDLER(USB_Connect)
{
	/* Start USB management task */
	Scheduler_SetTaskMode(USB_USBTask, TASK_RUN);
}

/** Event handler for the USB_Disconnect event. This stops the USB and keyboard report tasks. */
EVENT_HANDLER(USB_Disconnect)
{
	/* Stop running keyboard reporting, card reading and USB management tasks */
	Scheduler_SetTaskMode(USB_Keyboard_Report, TASK_STOP);
	Scheduler_SetTaskMode(USB_USBTask, TASK_STOP);
	Scheduler_SetTaskMode(Magstripe_Read, TASK_STOP);
}

/** Event handler for the USB_ConfigurationChanged event. This configures the device's endpoints ready
 *  to relay reports to the host, and starts the keyboard report task.
 */
EVENT_HANDLER(USB_ConfigurationChanged)
{
	/* Setup Keyboard Keycode Report Endpoint */
	Endpoint_ConfigureEndpoint(KEYBOARD_EPNUM, EP_TYPE_INTERRUPT,
		                       ENDPOINT_DIR_IN, KEYBOARD_EPSIZE,
	                           ENDPOINT_BANK_SINGLE);
	
	/* Default to report protocol on connect */
	UsingReportProtocol = true;

	/* Start Keyboard reporting and card reading tasks */
	Scheduler_SetTaskMode(USB_Keyboard_Report, TASK_RUN);
	Scheduler_SetTaskMode(Magstripe_Read, TASK_RUN);
}

/** Event handler for the USB_UnhandledControlPacket event. This is used to catch standard and class specific
 *  control requests that are not handled internally by the USB library, so that they can be handled appropriately
 *  for the application.
 */
EVENT_HANDLER(USB_UnhandledControlPacket)
{
	/* Handle HID Class specific requests */
	switch (bRequest)
	{
		case REQ_GetReport:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				USB_KeyboardReport_Data_t KeyboardReportData;

				/* Create the next keyboard report for transmission to the host */
				GetNextReport(&KeyboardReportData);

				/* Ignore report type and ID number value */
				Endpoint_Discard_Word();
				
				/* Ignore unused Interface number value */
				Endpoint_Discard_Word();

				/* Read in the number of bytes in the report to send to the host */
				uint16_t wLength = Endpoint_Read_Word_LE();
				
				/* If trying to send more bytes than exist to the host, clamp the value at the report size */
				if (wLength > sizeof(KeyboardReportData))
				  wLength = sizeof(KeyboardReportData);

				Endpoint_ClearSetupReceived();
	
				/* Write the report data to the control endpoint */
				Endpoint_Write_Control_Stream_LE(&KeyboardReportData, wLength);
				
				/* Finalize the stream transfer to send the last packet or clear the host abort */
				Endpoint_ClearSetupOUT();
			}
		
			break;
		case REQ_GetProtocol:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				Endpoint_ClearSetupReceived();
				
				/* Write the current protocol flag to the host */
				Endpoint_Write_Byte(UsingReportProtocol);
				
				/* Send the flag to the host */
				Endpoint_ClearSetupIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();
			}
			
			break;
		case REQ_SetProtocol:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the new protocol mode */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearSetupReceived();

				/* Set or clear the flag depending on what the host indicates that the current Protocol should be */
				UsingReportProtocol = (wValue != 0x0000);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
			
			break;
		case REQ_SetIdle:
			if (bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
			{
				/* Read in the wValue parameter containing the idle period */
				uint16_t wValue = Endpoint_Read_Word_LE();
				
				Endpoint_ClearSetupReceived();
				
				/* Get idle period in MSB */
				IdleCount = (wValue >> 8);
				
				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupINReady()));
				Endpoint_ClearSetupIN();
			}
			
			break;
		case REQ_GetIdle:
			if (bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
			{		
				Endpoint_ClearSetupReceived();
				
				/* Write the current idle duration to the host */
				Endpoint_Write_Byte(IdleCount);
				
				/* Send the flag to the host */
				Endpoint_ClearSetupIN();

				/* Acknowledge status stage */
				while (!(Endpoint_IsSetupOUTReceived()));
				Endpoint_ClearSetupOUT();
			}

			break;
	}
}

/** ISR for the timer 0 compare vector. This ISR fires once each millisecond, and decrements the counter indicating
 *  the number of milliseconds left to idle (not send the host reports) if the device has been instructed to idle
 *  by the host via a SetIdle class specific request.
 */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	/* One millisecond has elapsed, decrement the idle time remaining counter if it has not already elapsed */
	if (IdleMSRemaining)
	  IdleMSRemaining--;
	  
	if (KeyDelayRemaining)
	  KeyDelayRemaining--;
}

/** Constructs a keyboard report indicating the currently pressed keyboard keys to the host.
 *
 *  \param ReportData  Pointer to a USB_KeyboardReport_Data_t report structure where the resulting report should
 *                     be stored
 *
 *  \return Boolean true if the current report is different to the previous report, false otherwise
 */
bool GetNextReport(USB_KeyboardReport_Data_t* ReportData)
{
	static bool OddReport   = false;
	static bool MustRelease = false;
	
	BitBuffer_t* Buffer     = NULL;

	/* Clear the report contents */
	memset(ReportData, 0, sizeof(USB_KeyboardReport_Data_t));

	/* Get the next non-empty track data buffer */
	if (Track1Data.Elements)
	  Buffer = &Track1Data;
	else if (Track2Data.Elements)
	  Buffer = &Track2Data;			
	else if (Track3Data.Elements)
	  Buffer = &Track3Data;

	if (Buffer != NULL)
	{
		/* Toggle the odd report number indicator */
		OddReport   = !OddReport;
		
		/* Set the flag indicating that a null report must eventually be sent to release all pressed keys */
		MustRelease = true;

		/* Only send the next key on odd reports, so that they are interpersed with null reports to release keys */
		if (OddReport)
		{
			/* Set the report key code to the key code for the next data bit */
			ReportData->KeyCode = BitBuffer_GetNextBit(Buffer) ? KEY_1 : KEY_0;
			
			/* If buffer is now empty, a new line must be sent instead of the terminating bit */
			if (!(Buffer->Elements))
			{
				/* Set the keycode to the code for an enter key press */
				ReportData->KeyCode = KEY_ENTER;				
			}
		}

		return true;
	}
	else if (MustRelease)
	{
		/* Leave key code to null (0), to release all pressed keys */
		return true;
	}
	
	return false;
}

/** Task to read out data from inserted magnetic cards and place the seperate track data into their respective
 *  data buffers for later sending to the host as keyboard key presses.
 */
TASK(Magstripe_Read)
{
	/* Arrays to hold the buffer pointers, clock and data bit masks for the seperate card tracks */
	const struct
	{
		BitBuffer_t* Buffer;
		uint8_t      ClockMask;
		uint8_t      DataMask;	
	} TrackInfo[] = {{&Track1Data, MAG_T1_CLOCK, MAG_T1_DATA},
	                 {&Track2Data, MAG_T2_CLOCK, MAG_T2_DATA},
	                 {&Track3Data, MAG_T3_CLOCK, MAG_T3_DATA}};

	/* Previous magnetic card control line' status, for later comparison */
	uint8_t Magstripe_Prev = 0;
	
	/* Buffered current card reader control line' status */
	uint8_t Magstripe_LCL  = Magstripe_GetStatus();

	/* Exit the task early if no card is present in the reader */
	if (!(Magstripe_LCL & MAG_CARDPRESENT))
	  return;

	/* Read out card data while a card is present */
	while (Magstripe_LCL & MAG_CARDPRESENT)
	{
		/* Read out the next bit for each track of the card */
		for (uint8_t Track = 0; Track < 3; Track++)
		{
			/* Current data line status for the current card track */
			bool DataLevel    = ((Magstripe_LCL & TrackInfo[Track].DataMask) != 0);

			/* Current clock line status for the current card track */
			bool ClockLevel   = ((Magstripe_LCL & TrackInfo[Track].ClockMask) != 0);

			/* Current track clock transition check */
			bool ClockChanged = (((Magstripe_LCL ^ Magstripe_Prev) & TrackInfo[Track].ClockMask) != 0);
		
			/* Sample the next bit on the falling edge of the track's clock line, store key code into the track's buffer */
			if (ClockLevel && ClockChanged)
			  BitBuffer_StoreNextBit(TrackInfo[Track].Buffer, DataLevel);
		}

		/* Retain the current card reader control line states for later edge detection */
		Magstripe_Prev = Magstripe_LCL;
		
		/* Retrieve the new card reader control line states */
		Magstripe_LCL  = Magstripe_GetStatus();
	}
	
	/* Add terminators to the end of each track buffer */
	BitBuffer_StoreNextBit(&Track1Data, 0);
	BitBuffer_StoreNextBit(&Track2Data, 0);
	BitBuffer_StoreNextBit(&Track3Data, 0);
}

/** Task for the magnetic card reading and keyboard report generation. This task waits until a card is inserted,
 *  then reads off the card data and sends it to the host as a series of keyboard keypresses via keyboard reports.
 */
TASK(USB_Keyboard_Report)
{
	USB_KeyboardReport_Data_t KeyboardReportData;
	bool                      SendReport = false;
	
	/* Check if the USB system is connected to a host */
	if (USB_IsConnected)
	{
		/* Select the Keyboard Report Endpoint */
		Endpoint_SelectEndpoint(KEYBOARD_EPNUM);

		/* Check if Keyboard Endpoint Ready for Read/Write */
		if (Endpoint_ReadWriteAllowed())
		{
			/* Only fetch the next key to send once the period between key presses has elapsed */
			if (!(KeyDelayRemaining))
			{
				/* Create the next keyboard report for transmission to the host */
				SendReport = GetNextReport(&KeyboardReportData);
			}
			
			/* Check if the idle period is set and has elapsed */
			if (IdleCount && !(IdleMSRemaining))
			{
				/* Idle period elapsed, indicate that a report must be sent */
				SendReport = true;
				
				/* Reset the idle time remaining counter, must multiply by 4 to get the duration in milliseconds */
				IdleMSRemaining = (IdleCount << 2);
			}

			/* Write the keyboard report if a report is to be sent to the host */
			if (SendReport)
			{
				/* Write Keyboard Report Data */
				Endpoint_Write_Stream_LE(&KeyboardReportData, sizeof(USB_KeyboardReport_Data_t));

				/* Finalize the stream transfer to send the last packet */
				Endpoint_ClearCurrentBank();

				/* Reset the key delay period counter */
				KeyDelayRemaining = 2;
			}
		}
	}
}
