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
 *  Main source file for the MagStripe reader program. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */
 
#include "Magstripe.h"

/** Bit buffers to hold the read bits for each of the three magnetic card tracks before they are transmitted
 *  to the host as keyboard presses.
 */
BitBuffer_t TrackDataBuffers[3];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_t Keyboard_HID_Interface =
	{
		.InterfaceNumber         = 0,

		.ReportINEndpointNumber  = KEYBOARD_EPNUM,
		.ReportINEndpointSize    = KEYBOARD_EPSIZE,
		
		.ReportINBufferSize      = sizeof(USB_KeyboardReport_Data_t),
	};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	
	for (uint8_t Buffer = 0; Buffer < 3; Buffer++)
	  BitBuffer_Init(&TrackDataBuffers[Buffer]);

	for (;;)
	{
		if (Magstripe_GetStatus() & MAG_CARDPRESENT)
		  ReadMagstripeData();

		USB_HID_USBTask(&Keyboard_HID_Interface);
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
	Magstripe_Init();
	USB_Init();

	/* Millisecond timer initialization, with output compare interrupt enabled for the idle timing */
	OCR0A  = ((F_CPU / 64) / 1000);
	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS01) | (1 << CS00));
	TIMSK0 = (1 << OCIE0A);
}

/** Determines if a card has been inserted, and if so reads in each track's contents into the bit buffers
 *  until they are read out to the host as a series of keyboard presses.
 */
void ReadMagstripeData(void)
{
	/* Arrays to hold the buffer pointers, clock and data bit masks for the separate card tracks */
	const struct
	{
		uint8_t ClockMask;
		uint8_t DataMask;	
	} TrackInfo[] = {{MAG_T1_CLOCK, MAG_T1_DATA},
	                 {MAG_T2_CLOCK, MAG_T2_DATA},
	                 {MAG_T3_CLOCK, MAG_T3_DATA}};

	uint8_t Magstripe_Prev = 0;
	uint8_t Magstripe_LCL  = Magstripe_GetStatus();

	while (Magstripe_LCL & MAG_CARDPRESENT)
	{
		for (uint8_t Track = 0; Track < 3; Track++)
		{
			bool DataPinLevel      = ((Magstripe_LCL & TrackInfo[Track].DataMask) != 0);
			bool ClockPinLevel     = ((Magstripe_LCL & TrackInfo[Track].ClockMask) != 0);
			bool ClockLevelChanged = (((Magstripe_LCL ^ Magstripe_Prev) & TrackInfo[Track].ClockMask) != 0);
		
			if (ClockPinLevel && ClockLevelChanged)
			  BitBuffer_StoreNextBit(&TrackDataBuffers[Track], DataPinLevel);
		}

		Magstripe_Prev = Magstripe_LCL;
		Magstripe_LCL  = Magstripe_GetStatus();
	}
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_ConfigurationChanged(void)
{
	USB_HID_ConfigureEndpoints(&Keyboard_HID_Interface);
}

/** Event handler for the library USB Unhandled Control Packet event. */
void EVENT_USB_UnhandledControlPacket(void)
{
	USB_HID_ProcessControlPacket(&Keyboard_HID_Interface);
}

/** Timer 0 CTC ISR, firing once each millisecond to keep track of elapsed idle time in the HID interface. */
ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	if (Keyboard_HID_Interface.IdleMSRemaining)
	  Keyboard_HID_Interface.IdleMSRemaining--;
}

/** HID Class driver callback function for the creation of a HID report for the host.
 *
 *  \param HIDInterfaceInfo  Pointer to the HID interface structure for the HID interface being referenced
 *  \param ReportData  Pointer to the preallocated report buffer where the created report should be stored
 *
 *  \return Number of bytes in the created report
 */
uint16_t CALLBACK_USB_HID_CreateNextHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, void* ReportData)
{
	static bool IsKeyReleaseReport;
	static bool IsNewlineReport;

	BitBuffer_t*               Buffer         = NULL;
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
		
	/* Key reports must be interleaved with 0 Key Code reports to release the keys, or repeated keys will be ignored */
	IsKeyReleaseReport = !IsKeyReleaseReport;	

	if (IsKeyReleaseReport)
	{
		KeyboardReport->KeyCode = 0;
	}
	else if (IsNewlineReport)
	{
		IsNewlineReport = false;
		KeyboardReport->KeyCode = KEY_ENTER;
	}
	else
	{
		if (TrackDataBuffers[0].Elements)
		  Buffer = &TrackDataBuffers[0];
		else if (TrackDataBuffers[1].Elements)
		  Buffer = &TrackDataBuffers[1];			
		else if (TrackDataBuffers[2].Elements)
		  Buffer = &TrackDataBuffers[2];
		else
		  return 0;

		KeyboardReport->KeyCode = BitBuffer_GetNextBit(Buffer) ? KEY_1 : KEY_0;
		
		/* If buffer now empty, next report must be a newline to seperate track data */
		if (!(Buffer->Elements))
		  IsNewlineReport = true;
	}
	
	return sizeof(USB_KeyboardReport_Data_t);
}

/** HID Class driver callback function for the processing of a received HID report from the host.
 *
 *  \param HIDInterfaceInfo  Pointer to the HID interface structure for the HID interface being referenced
 *  \param ReportData  Pointer to the report buffer where the received report is stored
 *  \param ReportSize  Size in bytes of the report received from the host
 */
void CALLBACK_USB_HID_ProcessReceivedHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, void* ReportData, uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}
