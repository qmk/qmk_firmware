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

/** \ingroup Group_USBDeviceClassDrivers
 *  @defgroup Group_USBClassHIDDevice HID Device Class Driver - LUFA/Drivers/Class/Device/HID.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/HID.c
 *
 *  \section Module Description
 *  Functions, macros, variables, enums and types related to the management of USB HID Class interfaces
 *  within a USB device.
 *
 *  @{
 */
 
#ifndef _HID_CLASS_H_
#define _HID_CLASS_H_

	/* Includes: */
		#include "../../USB.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

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

	/* Function Prototypes: */
		/** Configures the endpoints of a given HID interface, ready for use. This should be linked to the library
		 *  \ref EVENT_USB_ConfigurationChanged() event so that the endpoints are configured when the configuration
		 *  containing the given HID interface is selected.
		 *
		 *  \param HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state.
		 *
		 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
		 */
		bool USB_HID_ConfigureEndpoints(USB_ClassInfo_HID_t* HIDInterfaceInfo);
		
		/** Processes incomming control requests from the host, that are directed to the given HID class interface. This should be
		 *  linked to the library \ref EVENT_USB_UnhandledControlPacket() event.
		 *
		 *  \param HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state.
		 */		
		void USB_HID_ProcessControlPacket(USB_ClassInfo_HID_t* HIDInterfaceInfo);

		/** General management task for a given HID class interface, required for the correct operation of the interface. This should
		 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
		 *
		 *  \param HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state.
		 */
		void USB_HID_USBTask(USB_ClassInfo_HID_t* HIDInterfaceInfo);
		
		/** HID class driver callback for the user creation of a HID input report. This callback may fire in response to either
		 *  HID class control requests from the host, or by the normal HID endpoint polling procedure. Inside this callback the
		 *  user is responsible for the creation of the next HID input report to be sent to the host.
		 *
		 *  \param HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state.
		 *  \param ReportID  If preset to a non-zero value, this is the report ID being requested by the host. If zero, this should
		 *                   be set to the report ID of the generated HID input report. If multiple reports are not sent via the
		 *                   given HID interface, this parameter should be ignored.
		 *  \param ReportData  Pointer to a buffer where the generated HID report should be stored.
		 *
		 *  \return  Number of bytes in the generated input report, or zero if no report is to be sent
		 */
		uint16_t CALLBACK_USB_HID_CreateNextHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, uint8_t* ReportID, void* ReportData);

		/** HID class driver callback for the user processing of a received HID input report. This callback may fire in response to
		 *  either HID class control requests from the host, or by the normal HID endpoint polling procedure. Inside this callback
		 *  the user is responsible for the processing of the received HID output report from the host.
		 *
		 *  \param HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state.
		 *  \param ReportID  Report ID of the received output report. If multiple reports are not received via the given HID
		 *                   interface, this parameter should be ignored.
		 *  \param ReportData  Pointer to a buffer where the received HID report is stored.
		 */
		void CALLBACK_USB_HID_ProcessReceivedHIDReport(USB_ClassInfo_HID_t* HIDInterfaceInfo, uint8_t ReportID, void* ReportData, uint16_t ReportSize);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
