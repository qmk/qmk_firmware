/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for HIDReport.c.
 */

#ifndef _HID_REPORT_H_
#define _HID_REPORT_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include "MouseHostWithParser.h"

	/* Macros: */
		/** HID Report Descriptor Usage for a Mouse. */
		#define USAGE_MOUSE                 0x02

		/** HID Report Descriptor Usage Page value for a toggle button. */
		#define USAGE_PAGE_BUTTON           0x09

		/** HID Report Descriptor Usage Page value for a Generic Desktop Control. */
		#define USAGE_PAGE_GENERIC_DCTRL    0x01

		/** HID Report Descriptor Usage value for a X axis movement. */
		#define USAGE_X                     0x30

		/** HID Report Descriptor Usage value for a Y axis movement. */
		#define USAGE_Y                     0x31

		/** HID Report Descriptor Usage value for a Scroll Wheel movement. */
		#define USAGE_SCROLL_WHEEL          0x38

	/* Enums: */
		/** Enum for the possible return codes of the \ref GetHIDReportData() function. */
		enum MouseHostWithParser_GetHIDReportDataCodes_t
		{
			ParseSuccessful         = 0, /**< HID report descriptor parsed successfully */
			ParseError              = 1, /**< Failed to fully process the HID report descriptor */
			ParseControlError       = 2, /**< Control error occurred while trying to read the device HID descriptor */
		};

	/* External Variables: */
		extern uint16_t         HIDReportSize;
		extern HID_ReportInfo_t HIDReportInfo;

	/* Function Prototypes: */
		uint8_t GetHIDReportData(void);

		bool CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* const CurrentItem);

#endif

