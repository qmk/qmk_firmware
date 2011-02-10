/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)
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
 *  Main source file for the MagStripe reader program. This file contains the main tasks of
 *  the project and is responsible for the initial application hardware configuration.
 */

#include "Magstripe.h"

/** Bit buffers to hold the read bits for each of the three magnetic card tracks before they are transmitted
 *  to the host as keyboard presses.
 */
static BitBuffer_t TrackDataBuffers[TOTAL_TRACKS];

/** Pointer to the current track buffer being sent to the host. */
static BitBuffer_t* CurrentTrackBuffer = &TrackDataBuffers[TOTAL_TRACKS];

/** Buffer to hold the previously generated Keyboard HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
	{
		.Config =
			{
				.InterfaceNumber            = 0,

				.ReportINEndpointNumber     = KEYBOARD_EPNUM,
				.ReportINEndpointSize       = KEYBOARD_EPSIZE,
				.ReportINEndpointDoubleBank = KEYBOARD_EPSIZE,

				.PrevReportINBuffer         = PrevKeyboardHIDReportBuffer,
				.PrevReportINBufferSize     = sizeof(PrevKeyboardHIDReportBuffer),
			},
	};


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();

	for (uint8_t Buffer = 0; Buffer < TOTAL_TRACKS; Buffer++)
	  BitBuffer_Init(&TrackDataBuffers[Buffer]);

	sei();

	for (;;)
	{
		if (Magstripe_GetStatus() & MAG_CARDPRESENT)
		  ReadMagstripeData();

		HID_Device_USBTask(&Keyboard_HID_Interface);
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
		for (uint8_t Track = 0; Track < TOTAL_TRACKS; Track++)
		{
			bool DataPinLevel      = ((Magstripe_LCL & TrackInfo[Track].DataMask) != 0);
			bool ClockPinLevel     = ((Magstripe_LCL & TrackInfo[Track].ClockMask) != 0);
			bool ClockLevelChanged = (((Magstripe_LCL ^ Magstripe_Prev) & TrackInfo[Track].ClockMask) != 0);

			/* Sample data on rising clock edges from the card reader */
			if (ClockPinLevel && ClockLevelChanged)
			  BitBuffer_StoreNextBit(&TrackDataBuffers[Track], DataPinLevel);
		}

		Magstripe_Prev = Magstripe_LCL;
		Magstripe_LCL  = Magstripe_GetStatus();
	}

	CurrentTrackBuffer = &TrackDataBuffers[0];
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);

	USB_Device_EnableSOFEvents();
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void)
{
	HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID  Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in] ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out] ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out] ReportSize  Number of bytes written in the report (or zero if no report is to be sent
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;

	static bool IsKeyReleaseReport;

	/* Key reports must be interleaved with key release reports, or repeated keys will be ignored */
	IsKeyReleaseReport = !IsKeyReleaseReport;

	if ((IsKeyReleaseReport) || (CurrentTrackBuffer == &TrackDataBuffers[TOTAL_TRACKS]))
	{
		/* No more data to send, or key release report between key presses */
		KeyboardReport->KeyCode[0] = KEY_NONE;
	}
	else if (!(CurrentTrackBuffer->Elements))
	{
		/* End of current track, send an enter press and change to the next track's buffer */
		KeyboardReport->KeyCode[0] = KEY_ENTER;
		CurrentTrackBuffer++;
	}
	else
	{
		/* Still data in the current track; convert next bit to a 1 or 0 keypress */
		KeyboardReport->KeyCode[0] = BitBuffer_GetNextBit(CurrentTrackBuffer) ? KEY_1 : KEY_0;
	}

	*ReportSize = sizeof(USB_KeyboardReport_Data_t);
	return false;
}

/** HID Class driver callback function for the processing of a received HID report from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID interface structure for the HID interface being referenced
 *  \param[in] ReportID          Report ID of the received report from the host
 *  \param[in] ReportType        The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData        Pointer to the report buffer where the received report is stored
 *  \param[in] ReportSize        Size in bytes of the report received from the host
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Ignore keyboard LED reports from the host, but still need to declare the callback routine
}

