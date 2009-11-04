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
 *  Main source file for the MouseHostWithParser demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */
 
#include "MouseHostWithParser.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Mouse HID Parser Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);

	for (;;)
	{
		Mouse_HID_Task();
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
	SerialStream_Init(9600, false);
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_DeviceAttached event. This indicates that a device has been attached to the host, and
 *  starts the library USB task to begin the enumeration and USB management process.
 */
void EVENT_USB_Host_DeviceAttached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "Device Attached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_DeviceUnattached event. This indicates that a device has been removed from the host, and
 *  stops the library USB task management process.
 */
void EVENT_USB_Host_DeviceUnattached(void)
{
	puts_P(PSTR(ESC_FG_GREEN "Device Unattached.\r\n" ESC_FG_WHITE));
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_DeviceEnumerationComplete event. This indicates that a device has been successfully
 *  enumerated by the host and is now ready to be used by the application.
 */
void EVENT_USB_Host_DeviceEnumerationComplete(void)
{
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_ShutDown();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);
	
	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Task to set the configuration of the attached device after it has been enumerated, and to read and process
 *  the HID report descriptor and HID reports from the device and display the results onto the board LEDs.
 */
void Mouse_HID_Task(void)
{
	uint8_t ErrorCode;

	/* Switch to determine what user-application handled host state the host state machine is in */
	switch (USB_HostState)
	{
		case HOST_STATE_Addressed:
			puts_P(PSTR("Getting Config Data.\r\n"));
		
			/* Get and process the configuration descriptor data */
			if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
			{
				if (ErrorCode == ControlError)
				  puts_P(PSTR(ESC_FG_RED "Control Error (Get Configuration).\r\n"));
				else
				  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

				printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
				
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);

				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
		
			/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
			if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
			{
				printf_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"
				                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
				
				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			printf_P(PSTR("Processing HID Report (Size %d Bytes).\r\n"), HIDReportSize);

			/* Get and process the device's first HID report descriptor */
			if ((ErrorCode = GetHIDReportData()) != ParseSuccessful)
			{
				puts_P(PSTR(ESC_FG_RED "Report Parse Error.\r\n"));

				if (!(HIDReportInfo.TotalReportItems))
					puts_P(PSTR("Not a valid Mouse." ESC_FG_WHITE));
				else
					printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);
			
				/* Indicate error via status LEDs */
				LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
				
				/* Wait until USB device disconnected */
				USB_HostState = HOST_STATE_WaitForDeviceRemoval;
				break;
			}
			
			printf("Total Reports: %d\r\n", HIDReportInfo.TotalDeviceReports);

			for (uint8_t i = 0; i < HIDReportInfo.TotalDeviceReports; i++)
			{
				HID_ReportSizeInfo_t* CurrReportIDInfo = &HIDReportInfo.ReportIDSizes[i];
				
				uint8_t ReportSizeInBits      = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_In];
				uint8_t ReportSizeOutBits     = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_Out];
				uint8_t ReportSizeFeatureBits = CurrReportIDInfo->ReportSizeBits[REPORT_ITEM_TYPE_Feature];

				/* Print out the byte sizes of each report within the device */
				printf_P(PSTR("  + Report ID %d - In: %d bytes, Out: %d bytes, Feature: %d bytes\r\n"),
				         CurrReportIDInfo->ReportID,
				         ((ReportSizeInBits      >> 3) + ((ReportSizeInBits      & 0x07) != 0)),
				         ((ReportSizeOutBits     >> 3) + ((ReportSizeOutBits     & 0x07) != 0)),
				         ((ReportSizeFeatureBits >> 3) + ((ReportSizeFeatureBits & 0x07) != 0)));
			}

			puts_P(PSTR("Mouse Enumerated.\r\n"));

			USB_HostState = HOST_STATE_Configured;
			break;
		case HOST_STATE_Configured:
			/* Select and unfreeze mouse data pipe */
			Pipe_SelectPipe(MOUSE_DATAPIPE);	
			Pipe_Unfreeze();
			
			/* Check to see if a packet has been received */
			if (Pipe_IsINReceived())
			{
				/* Check if data has been received from the attached mouse */
				if (Pipe_IsReadWriteAllowed())
				{
					/* Create buffer big enough for the report */
					uint8_t MouseReport[Pipe_BytesInPipe()];

					/* Load in the mouse report */
					Pipe_Read_Stream_LE(MouseReport, Pipe_BytesInPipe());
				
					/* Process the read in mouse report from the device */
					ProcessMouseReport(MouseReport);
				}
				
				/* Clear the IN endpoint, ready for next data packet */
				Pipe_ClearIN();
			}

			/* Freeze mouse data pipe */
			Pipe_Freeze();
			break;
	}
}

/** Processes a read HID report from an attached mouse, extracting out elements via the HID parser results
 *  as required and displays movement and button presses on the board LEDs.
 *
 *  \param[in] MouseReport  Pointer to a HID report from an attached mouse device
 */
void ProcessMouseReport(uint8_t* MouseReport)
{
	uint8_t LEDMask = LEDS_NO_LEDS;

	/* Check each HID report item in turn, looking for mouse X/Y/button reports */
	for (uint8_t ReportNumber = 0; ReportNumber < HIDReportInfo.TotalReportItems; ReportNumber++)
	{
		/* Create a temporary item pointer to the next report item */
		HID_ReportItem_t* ReportItem = &HIDReportInfo.ReportItems[ReportNumber];
		
		bool FoundData;

		if ((ReportItem->Attributes.Usage.Page        == USAGE_PAGE_BUTTON) &&
			(ReportItem->ItemType                     == REPORT_ITEM_TYPE_In))
		{
			/* Get the mouse button value */
			FoundData = USB_GetHIDReportItemInfo(MouseReport, ReportItem);
			
			/* For multi-report devices - if the requested data was not in the issued report, continue */
			if (!(FoundData))
			  continue;

			/* If button is pressed, all LEDs are turned on */
			if (ReportItem->Value)
			  LEDMask = LEDS_ALL_LEDS;
		}
		else if ((ReportItem->Attributes.Usage.Page   == USAGE_PAGE_GENERIC_DCTRL) &&
				 (ReportItem->Attributes.Usage.Usage  == USAGE_SCROLL_WHEEL)       &&
				 (ReportItem->ItemType                == REPORT_ITEM_TYPE_In))
		{
			/* Get the mouse wheel value if it is contained within the current 
			 * report, if not, skip to the next item in the parser list
			 */
			if (!(USB_GetHIDReportItemInfo(MouseReport, ReportItem)))
			  continue;							  

			int16_t WheelDelta = (int16_t)(ReportItem->Value << (16 - ReportItem->Attributes.BitSize));
			
			if (WheelDelta)
			  LEDMask = (LEDS_LED1 | LEDS_LED2 | ((WheelDelta > 0) ? LEDS_LED3 : LEDS_LED4));
		}
		else if ((ReportItem->Attributes.Usage.Page   == USAGE_PAGE_GENERIC_DCTRL) &&
				 ((ReportItem->Attributes.Usage.Usage == USAGE_X)                  ||
				  (ReportItem->Attributes.Usage.Usage == USAGE_Y))                 &&
				 (ReportItem->ItemType                == REPORT_ITEM_TYPE_In))
		{
			/* Get the mouse relative position value */
			FoundData = USB_GetHIDReportItemInfo(MouseReport, ReportItem);
			
			/* For multi-report devices - if the requested data was not in the issued report, continue */
			if (!(FoundData))
			  continue;
			  
			int16_t DeltaMovement = (int16_t)(ReportItem->Value << (16 - ReportItem->Attributes.BitSize));
			
			/* Determine if the report is for the X or Y delta movement */
			if (ReportItem->Attributes.Usage.Usage == USAGE_X)
			{
				/* Turn on the appropriate LED according to direction if the delta is non-zero */
				if (DeltaMovement)
				  LEDMask |= ((DeltaMovement > 0) ? LEDS_LED1 : LEDS_LED2);
			}
			else
			{
				/* Turn on the appropriate LED according to direction if the delta is non-zero */
				if (DeltaMovement)
				  LEDMask |= ((DeltaMovement > 0) ? LEDS_LED3 : LEDS_LED4);
			}
		}
	}
	
	/* Display the button information on the board LEDs */
	LEDs_SetAllLEDs(LEDMask);
}