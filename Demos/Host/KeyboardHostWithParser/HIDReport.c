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

#include "HIDReport.h"

/** Size in bytes of the attached device's HID report descriptor */
uint16_t         HIDReportSize;

/** Processed HID report descriptor items structure, containing information on each HID report element */
HID_ReportInfo_t HIDReportInfo;


/** Function to read in the HID report descriptor from the attached device, and process it into easy-to-read
 *  structures via the HID parser routines in the LUFA library.
 *
 *  \return  A value from the KeyboardHostWithParser_GetHIDReportDataCodes_t enum
 */
uint8_t GetHIDReportData(void)
{
	/* Create a buffer big enough to hold the entire returned HID report */
	uint8_t HIDReportData[HIDReportSize];
	
	USB_HostRequest = (USB_Host_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_GetDescriptor,
			.wValue        = (DTYPE_Report << 8),
			.wIndex        = 0,
			.wLength       = HIDReportSize,
		};

	/* Select the control pipe for the request transfer */
	Pipe_SelectPipe(PIPE_CONTROLPIPE);

	/* Send control request to retrieve the HID report from the attached device */
	if (USB_Host_SendControlRequest(HIDReportData) != HOST_SENDCONTROL_Successful)
	  return ParseControlError;

	/* Send the HID report to the parser for processing */
	if (USB_ProcessHIDReport(HIDReportData, HIDReportSize, &HIDReportInfo) != HID_PARSE_Successful)
	  return ParseError;
	
	return ParseSuccessful;
}

