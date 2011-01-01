/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
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

#include "HIDReport.h"

/** Size in bytes of the attached device's HID report descriptor */
uint16_t         HIDReportSize;

/** Processed HID report descriptor items structure, containing information on each HID report element */
HID_ReportInfo_t HIDReportInfo;


/** Function to read in the HID report descriptor from the attached device, and process it into easy-to-read
 *  structures via the HID parser routines in the LUFA library.
 *
 *  \return  A value from the MouseHostWithParser_GetHIDReportDataCodes_t enum
 */
uint8_t GetHIDReportData(void)
{
	/* Create a buffer big enough to hold the entire returned HID report */
	uint8_t HIDReportData[HIDReportSize];

	USB_ControlRequest = (USB_Request_Header_t)
		{
			.bmRequestType = (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE),
			.bRequest      = REQ_GetDescriptor,
			.wValue        = (HID_DTYPE_Report << 8),
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

/** Callback for the HID Report Parser. This function is called each time the HID report parser is about to store
 *  an IN, OUT or FEATURE item into the HIDReportInfo structure. To save on RAM, we are able to filter out items
 *  we aren't interested in (preventing us from being able to extract them later on, but saving on the RAM they would
 *  have occupied).
 *
 *  \param[in] CurrentItem  Pointer to the item the HID report parser is currently working with
 *
 *  \return Boolean true if the item should be stored into the HID report structure, false if it should be discarded
 */
bool CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* const CurrentItem)
{
	bool IsMouse = false;

	/* Iterate through the item's collection path, until either the root collection node or a collection with the
	 * Mouse Usage is found - this prevents Joysticks, which use identical descriptors except for the Joystick usage
	 * parent node, from being erroneously treated as a mouse
	 */
	for (HID_CollectionPath_t* CurrPath = CurrentItem->CollectionPath; CurrPath != NULL; CurrPath = CurrPath->Parent)
	{
		if ((CurrPath->Usage.Page  == USAGE_PAGE_GENERIC_DCTRL) &&
		    (CurrPath->Usage.Usage == USAGE_MOUSE))
		{
			IsMouse = true;
			break;
		}
	}

	/* If a collection with the mouse usage was not found, indicate that we are not interested in this item */
	if (!IsMouse)
	  return false;

	/* Check the attributes of the current mouse item - see if we are interested in it or not;
	 * only store BUTTON and GENERIC_DESKTOP_CONTROL items into the Processed HID Report
	 * structure to save RAM and ignore the rest
	 */
	return ((CurrentItem->Attributes.Usage.Page == USAGE_PAGE_BUTTON) ||
	        (CurrentItem->Attributes.Usage.Page == USAGE_PAGE_GENERIC_DCTRL));
}

