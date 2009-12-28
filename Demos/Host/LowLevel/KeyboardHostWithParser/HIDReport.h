/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  Header file for HIDReport.c.
 */

#ifndef _HID_REPORT_H_
#define _HID_REPORT_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Drivers/USB/Class/Host/HIDParser.h>
		
		#include "KeyboardHostWithParser.h"

	/* Macros: */
		/** HID Report Descriptor Usage Page value for a desktop keyboard */
		#define USAGE_PAGE_KEYBOARD             0x07

	/* Enums: */
		/** Enum for the possible return codes of the GetHIDReportData() function. */
		enum KeyboardHostWithParser_GetHIDReportDataCodes_t
		{
			ParseSuccessful         = 0, /**< HID report descriptor parsed successfully */
			ParseError              = 1, /**< Failed to fully process the HID report descriptor */
			ParseControlError       = 2, /**< Control error occurred while trying to read the device HID descriptor */
		};
		
	/* Type Defines: */
		/** Type define for a HID descriptor. */
		typedef struct
		{
			USB_Descriptor_Header_t  Header; /**< Regular descriptor header containing the descriptor's type and length */
				
			uint16_t                 HIDSpec; /**< Implemented HID class specification, in BCD encoded format */
			uint8_t                  CountryCode; /**< Country code value for localized hardware */
		
			uint8_t                  TotalHIDDescriptors; /**< Total number of HID report descriptors in the current interface */

			uint8_t                  HIDReportType; /**< HID report type of the first HID report descriptor */
			uint16_t                 HIDReportLength; /**< Total size in bytes of the first HID report descriptor */
		} USB_Descriptor_HID_t;

	/* External Variables: */
		extern uint16_t         HIDReportSize;
		extern HID_ReportInfo_t HIDReportInfo;

	/* Function Prototypes: */
		uint8_t GetHIDReportData(void);

		bool CALLBACK_HIDParser_FilterHIDReportItem(HID_ReportItem_t* CurrentItemAttributes);
		
#endif
