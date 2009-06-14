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

/** \ingroup Group_USBClassHID
 *  @{
 */
 
#ifndef _HID_CLASS_COMMON_H_
#define _HID_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Macros: */
		/** HID Class Specific Request to get the current HID report from the device. */
		#define REQ_GetReport      0x01

		/** HID Class Specific Request to get the current device idle count. */
		#define REQ_GetIdle        0x02

		/** HID Class Specific Request to set the current HID report to the device. */
		#define REQ_SetReport      0x09

		/** HID Class Specific Request to set the device's idle count. */
		#define REQ_SetIdle        0x0A

		/** HID Class Specific Request to get the current HID report protocol mode. */
		#define REQ_GetProtocol    0x03

		/** HID Class Specific Request to set the current HID report protocol mode. */
		#define REQ_SetProtocol    0x0B

		/** Descriptor header type value, to indicate a HID class HID descriptor. */
		#define DTYPE_HID          0x21
		
		/** Descriptor header type value, to indicate a HID class HID report descriptor. */
		#define DTYPE_Report       0x22
		
	/* Type Defines: */
		/** Type define for the HID class specific HID descriptor, to describe the HID device's specifications. Refer to the HID
		 *  specification for details on the structure elements.
		 */
		typedef struct
		{
			USB_Descriptor_Header_t               Header;
				
			uint16_t                              HIDSpec;
			uint8_t                               CountryCode;
		
			uint8_t                               TotalReportDescriptors;

			uint8_t                               HIDReportType;
			uint16_t                              HIDReportLength;
		} USB_Descriptor_HID_t;

		/** Type define for the data type used to store HID report descriptor elements. */
		typedef uint8_t USB_Descriptor_HIDReport_Datatype_t;

		/** Class state structure. An instance of this structure should be made for each HID interface
		 *  within the user application, and passed to each of the HID class driver functions as the
		 *  HIDInterfaceInfo parameter. The contents of this structure should be set to their correct
		 *  values when used, or ommitted to force the library to use default values.
		 *
		 *  Note that for the HID class driver, host-to-device reports are received via HID class requests
		 *  rather than a dedicated endpoint to simplify the driver and its interface.
		 */
		typedef struct
		{
			uint8_t  InterfaceNumber; /**< Interface number of the HID interface within the device */

			uint8_t  ReportINEndpointNumber; /**< Endpoint number of the HID interface's IN report endpoint */
			uint16_t ReportINEndpointSize; /**< Size in bytes of the HID interface's IN report endpoint */
			
			uint8_t  ReportINBufferSize; /**< Size of the largest possible report to send to the host, for buffer allocation purposes */

			bool     UsingReportProtocol; /**< Indicates if the HID interface is set to Boot or Report protocol mode */
			uint16_t IdleCount; /**< Report idle period, in ms, set by the host */
			uint16_t IdleMSRemaining; /**< Total number of ms remaining before the idle period elapses */
		} USB_ClassInfo_HID_t;

#endif

/** @} */
