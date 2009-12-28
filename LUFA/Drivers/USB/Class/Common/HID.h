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

/** \ingroup Group_USBClassHID
 *  @defgroup Group_USBClassHIDCommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  HID Class.
 *
 *  @{
 */
 
#ifndef _HID_CLASS_COMMON_H_
#define _HID_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Macros: */
		/** HID Class Specific Request to get the current HID report from the device. */
		#define REQ_GetReport                0x01

		/** HID Class Specific Request to get the current device idle count. */
		#define REQ_GetIdle                  0x02

		/** HID Class Specific Request to set the current HID report to the device. */
		#define REQ_SetReport                0x09

		/** HID Class Specific Request to set the device's idle count. */
		#define REQ_SetIdle                  0x0A

		/** HID Class Specific Request to get the current HID report protocol mode. */
		#define REQ_GetProtocol              0x03

		/** HID Class Specific Request to set the current HID report protocol mode. */
		#define REQ_SetProtocol              0x0B

		/** Descriptor header type value, to indicate a HID class HID descriptor. */
		#define DTYPE_HID                    0x21
		
		/** Descriptor header type value, to indicate a HID class HID report descriptor. */
		#define DTYPE_Report                 0x22
		
		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface does not support
		 *  any HID class boot protocol (see HID Class Specification).
		 */
		#define HID_NON_BOOT_PROTOCOL        0x00

		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface supports the
		 *  HID class Keyboard boot protocol (see HID Class Specification).
		 */
		#define HID_BOOT_KEYBOARD_PROTOCOL   0x01

		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface supports the
		 *  HID class Mouse boot protocol (see HID Class Specification).
		 */
		#define HID_BOOT_MOUSE_PROTOCOL      0x02

	/* Type Defines: */
		/** Enum for the different types of HID reports. */
		enum HID_ReportItemTypes_t
		{
			REPORT_ITEM_TYPE_In                   = 0, /**< Indicates that the item is an IN report type. */
			REPORT_ITEM_TYPE_Out                  = 1, /**< Indicates that the item is an OUT report type. */
			REPORT_ITEM_TYPE_Feature              = 2, /**< Indicates that the item is a FEATURE report type. */
		};

		/** Type define for the HID class specific HID descriptor, to describe the HID device's specifications. Refer to the HID
		 *  specification for details on the structure elements.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t  Header;
				
			uint16_t                 HIDSpec;
			uint8_t                  CountryCode;
		
			uint8_t                  TotalReportDescriptors;

			uint8_t                  HIDReportType;
			uint16_t                 HIDReportLength;
		} USB_HID_Descriptor_t;

		/** Type define for a standard Boot Protocol Mouse report */
		typedef struct
		{
			uint8_t Button; /**< Button mask for currently pressed buttons in the mouse */
			int8_t  X; /**< Current delta X movement of the mouse */
			int8_t  Y; /**< Current delta Y movement on the mouse */
		} USB_MouseReport_Data_t;
		
		/** Type define for a standard Boot Protocol Keyboard report */
		typedef struct
		{
			uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (such as Shift, Control, etc.) */
			uint8_t Reserved; /**< Reserved for OEM use, always set to 0 */
			uint8_t KeyCode[6]; /**< Key codes of the currently pressed keys */
		} USB_KeyboardReport_Data_t;

		/** Type define for the data type used to store HID report descriptor elements. */
		typedef uint8_t USB_Descriptor_HIDReport_Datatype_t;

#endif

/** @} */
