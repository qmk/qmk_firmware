/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common definitions and declarations for the library USB HID Class driver.
 *
 *  Common definitions and declarations for the library USB HID Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the class driver
 *        dispatch header located in LUFA/Drivers/USB/Class/HID.h.
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

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_HID_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/Class/HID.h instead.
		#endif
		
	/* Macros: */
		/** HID class-specific Request to get the current HID report from the device. */
		#define REQ_GetReport                   0x01

		/** HID class-specific Request to get the current device idle count. */
		#define REQ_GetIdle                     0x02

		/** HID class-specific Request to set the current HID report to the device. */
		#define REQ_SetReport                   0x09

		/** HID class-specific Request to set the device's idle count. */
		#define REQ_SetIdle                     0x0A

		/** HID class-specific Request to get the current HID report protocol mode. */
		#define REQ_GetProtocol                 0x03

		/** HID class-specific Request to set the current HID report protocol mode. */
		#define REQ_SetProtocol                 0x0B

		/** Descriptor header type value, to indicate a HID class HID descriptor. */
		#define DTYPE_HID                       0x21
		
		/** Descriptor header type value, to indicate a HID class HID report descriptor. */
		#define DTYPE_Report                    0x22
		
		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface does not support
		 *  any HID class boot protocol (see HID Class Specification).
		 */
		#define HID_NON_BOOT_PROTOCOL           0x00

		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface supports the
		 *  HID class Keyboard boot protocol (see HID Class Specification).
		 */
		#define HID_BOOT_KEYBOARD_PROTOCOL      0x01

		/** Constant for the protocol value of a HID interface descriptor, indicating that the interface supports the
		 *  HID class Mouse boot protocol (see HID Class Specification).
		 */
		#define HID_BOOT_MOUSE_PROTOCOL         0x02
		
		/** Constant for a keyboard report modifier byte, indicating that the keyboard's left control key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_LEFTCTRL   (1 << 0)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's left shift key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_LEFTSHIFT  (1 << 1)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's left alt key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_LEFTALT    (1 << 2)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's left GUI key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_LEFTGUI    (1 << 3)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's right control key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_RIGHTCTRL  (1 << 4)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's right shift key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_RIGHTSHIFT (1 << 5)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's right alt key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_RIGHTALT   (1 << 6)

		/** Constant for a keyboard report modifier byte, indicating that the keyboard's right GUI key is currently pressed. */
		#define HID_KEYBOARD_MODIFER_RIGHTGUI   (1 << 7)
		
		/** Constant for a keyboard output report LED byte, indicating that the host's NUM LOCK mode is currently set. */
		#define HID_KEYBOARD_LED_NUMLOCK        (1 << 0)
		
		/** Constant for a keyboard output report LED byte, indicating that the host's CAPS LOCK mode is currently set. */
		#define HID_KEYBOARD_LED_CAPSLOCK       (1 << 1)

		/** Constant for a keyboard output report LED byte, indicating that the host's SCROLL LOCK mode is currently set. */
		#define HID_KEYBOARD_LED_SCROLLLOCK     (1 << 2)

		/** Constant for a keyboard output report LED byte, indicating that the host's KATANA mode is currently set. */
		#define HID_KEYBOARD_LED_KATANA         (1 << 3)

	/* Type Defines: */
		/** Enum for the different types of HID reports. */
		enum HID_ReportItemTypes_t
		{
			REPORT_ITEM_TYPE_In                   = 0, /**< Indicates that the item is an IN report type. */
			REPORT_ITEM_TYPE_Out                  = 1, /**< Indicates that the item is an OUT report type. */
			REPORT_ITEM_TYPE_Feature              = 2, /**< Indicates that the item is a FEATURE report type. */
		};

		/** \brief HID class-specific HID Descriptor.
		 *
		 *  Type define for the HID class-specific HID descriptor, to describe the HID device's specifications. Refer to the HID
		 *  specification for details on the structure elements.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t  Header; /**< Regular descriptor header containing the descriptor's type and length. */
				
			uint16_t                 HIDSpec; /**< BCD encoded version that the HID descriptor and device complies to. */
			uint8_t                  CountryCode; /**< Country code of the localized device, or zero if universal. */
		
			uint8_t                  TotalReportDescriptors; /**< Total number of HID report descriptors for the interface. */

			uint8_t                  HIDReportType; /**< Type of HID report, set to \ref DTYPE_Report. */
			uint16_t                 HIDReportLength; /**< Length of the associated HID report descriptor, in bytes. */
		} USB_HID_Descriptor_t;

		/** \brief Standard HID Boot Protocol Mouse Report.
		 *
		 *  Type define for a standard Boot Protocol Mouse report
		 */
		typedef struct
		{
			uint8_t Button; /**< Button mask for currently pressed buttons in the mouse. */
			int8_t  X; /**< Current delta X movement of the mouse. */
			int8_t  Y; /**< Current delta Y movement on the mouse. */
		} USB_MouseReport_Data_t;
		
		/** \brief Standard HID Boot Protocol Keyboard Report.
		 *
		 *  Type define for a standard Boot Protocol Keyboard report
		 */
		typedef struct
		{
			uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (a combination of
			                   *   HID_KEYBOARD_MODIFER_* masks).
			                   */
			uint8_t Reserved; /**< Reserved for OEM use, always set to 0. */
			uint8_t KeyCode[6]; /**< Key codes of the currently pressed keys. */
		} USB_KeyboardReport_Data_t;

		/** Type define for the data type used to store HID report descriptor elements. */
		typedef uint8_t USB_Descriptor_HIDReport_Datatype_t;

#endif

/** @} */
