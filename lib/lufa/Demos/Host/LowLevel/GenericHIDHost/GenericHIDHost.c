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
 *  Main source file for the GenericHIDHost demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "GenericHIDHost.h"

/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	puts_P(PSTR(ESC_FG_CYAN "Generic HID Host Demo running.\r\n" ESC_FG_WHITE));

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		ReadNextReport();

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
	Serial_Init(9600, false);
	LEDs_Init();
	USB_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);
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
	puts_P(PSTR("Getting Config Data.\r\n"));

	uint8_t ErrorCode;

	/* Get and process the configuration descriptor data */
	if ((ErrorCode = ProcessConfigurationDescriptor()) != SuccessfulConfigRead)
	{
		if (ErrorCode == ControlError)
		  puts_P(PSTR(ESC_FG_RED "Control Error (Get Configuration).\r\n"));
		else
		  puts_P(PSTR(ESC_FG_RED "Invalid Device.\r\n"));

		printf_P(PSTR(" -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	/* Set the device configuration to the first configuration (rarely do devices use multiple configurations) */
	if ((ErrorCode = USB_Host_SetDeviceConfiguration(1)) != HOST_SENDCONTROL_Successful)
	{
		printf_P(PSTR(ESC_FG_RED "Control Error (Set Configuration).\r\n"
		                         " -- Error Code: %d\r\n" ESC_FG_WHITE), ErrorCode);

		LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
		return;
	}

	puts_P(PSTR("HID Device Enumerated.\r\n"));
	LEDs_SetAllLEDs(LEDMASK_USB_READY);
}

/** Event handler for the USB_HostError event. This indicates that a hardware error occurred while in host mode. */
void EVENT_USB_Host_HostError(const uint8_t ErrorCode)
{
	USB_Disable();

	printf_P(PSTR(ESC_FG_RED "Host Mode Error\r\n"
	                         " -- Error Code %d\r\n" ESC_FG_WHITE), ErrorCode);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
	for(;;);
}

/** Event handler for the USB_DeviceEnumerationFailed event. This indicates that a problem occurred while
 *  enumerating an attached USB device.
 */
void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                            const uint8_t SubErrorCode)
{
	printf_P(PSTR(ESC_FG_RED "Dev Enum Error\r\n"
	                         " -- Error Code %d\r\n"
	                         " -- Sub Error Code %d\r\n"
	                         " -- In State %d\r\n" ESC_FG_WHITE), ErrorCode, SubErrorCode, USB_HostState);

	LEDs_SetAllLEDs(LEDMASK_USB_ERROR);
}

/** Reads in and processes the next report from the attached device, displaying the report
 *  contents on the board LEDs and via the serial port.
 */
void ReadNextReport(void)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select and unfreeze HID data IN pipe */
	Pipe_SelectPipe(HID_DATA_IN_PIPE);
	Pipe_Unfreeze();

	/* Check to see if a packet has been received */
	if (!(Pipe_IsINReceived()))
	{
		/* Refreeze HID data IN pipe */
		Pipe_Freeze();

		return;
	}

	/* Ensure pipe contains data before trying to read from it */
	if (Pipe_IsReadWriteAllowed())
	{
		uint8_t ReportINData[Pipe_BytesInPipe()];

		/* Read in HID report data */
		Pipe_Read_Stream_LE(&ReportINData, sizeof(ReportINData), NULL);

		/* Print report data through the serial port */
		for (uint16_t CurrByte = 0; CurrByte < sizeof(ReportINData); CurrByte++)
		  printf_P(PSTR("0x%02X "), ReportINData[CurrByte]);

		puts_P(PSTR("\r\n"));
	}

	/* Clear the IN endpoint, ready for next data packet */
	Pipe_ClearIN();

	/* Refreeze HID data IN pipe */
	Pipe_Freeze();
}

/** Writes a report to the attached device.
 *
 *  \param[in] ReportOUTData  Buffer containing the report to send to the device
 *  \param[in] ReportIndex    Index of the report in the device (zero if the device does not use multiple reports)
 *  \param[in] ReportType     Type of report to send, either REPORT_TYPE_OUT or REPORT_TYPE_FEATURE
 *  \param[in] ReportLength   Length of the report to send
 */
void WriteNextReport(uint8_t* ReportOUTData,
                     const uint8_t ReportIndex,
                     const uint8_t ReportType,
                     uint16_t ReportLength)
{
	if (USB_HostState != HOST_STATE_Configured)
	  return;

	/* Select the HID data OUT pipe */
	Pipe_SelectPipe(HID_DATA_OUT_PIPE);

	/* Not all HID devices have an OUT endpoint (some require OUT reports to be sent over the
	 * control endpoint instead) - check to see if the OUT endpoint has been initialized */
	if (Pipe_IsConfigured() && (ReportType == REPORT_TYPE_OUT))
	{
		Pipe_Unfreeze();

		/* Ensure pipe is ready to be written to before continuing */
		if (!(Pipe_IsOUTReady()))
		{
			/* Refreeze the data OUT pipe */
			Pipe_Freeze();

			return;
		}

		/* If the report index is used, send it before the report data */
		if (ReportIndex)
		  Pipe_Write_8(ReportIndex);

		/* Write out HID report data */
		Pipe_Write_Stream_LE(ReportOUTData, ReportLength, NULL);

		/* Clear the OUT endpoint, send last data packet */
		Pipe_ClearOUT();

		/* Refreeze the data OUT pipe */
		Pipe_Freeze();
	}
	else
	{
		/* Class specific request to send a HID report to the device */
		USB_ControlRequest = (USB_Request_Header_t)
			{
				.bmRequestType = (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE),
				.bRequest      = HID_REQ_SetReport,
				.wValue        = ((ReportType << 8) | ReportIndex),
				.wIndex        = 0,
				.wLength       = ReportLength,
			};

		/* Select the control pipe for the request transfer */
		Pipe_SelectPipe(PIPE_CONTROLPIPE);

		/* Send the request to the device */
		USB_Host_SendControlRequest(ReportOUTData);
	}
}

