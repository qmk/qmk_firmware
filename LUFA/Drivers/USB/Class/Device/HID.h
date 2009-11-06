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
 *  @defgroup Group_USBClassHIDDevice HID Class Device Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/HID.c
 *
 *  \section Module Description
 *  Device Mode USB Class driver framework interface, for the HID USB Class driver.
 *
 *  @{
 */
 
#ifndef _HID_CLASS_DEVICE_H_
#define _HID_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/HID.h"

		#include <string.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made for each HID interface
			 *  within the user application, and passed to each of the HID class driver functions as the
			 *  HIDInterfaceInfo parameter. This stores each HID interface's configuration and state information.
			 *
			 *  \note Due to technical limitations, the HID device class driver does not utilize a seperate OUT
			 *        endpoint for host->device communications. Instead, the host->device data (if any) is sent to
			 *        the device via the control endpoint.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  InterfaceNumber; /**< Interface number of the HID interface within the device */

					uint8_t  ReportINEndpointNumber; /**< Endpoint number of the HID interface's IN report endpoint */
					uint16_t ReportINEndpointSize; /**< Size in bytes of the HID interface's IN report endpoint */					
					bool     ReportINEndpointDoubleBank; /** Indicates if the HID interface's IN report endpoint should use double banking */
					
					void*    PrevReportINBuffer; /**< Pointer to a buffer where the previously created HID input report can be
					                              *  stored by the driver, for comparison purposes to detect report changes that
					                              *  must be sent immediately to the host. This should point to a buffer big enough
					                              *  to hold the largest HID input report sent from the HID interface. If this is set
												  *  to NULL, it is up to the user to force transfers when needed in the 
												  *  \ref CALLBACK_HID_Device_CreateHIDReport() callback function.
												  *
												  *  \note Due to the single buffer, the internal driver can only correctly compare
												  *        subsequent reports with identical report IDs. In multiple report devices,
												  *        this buffer should be set to NULL and the decision to send reports made
												  *        by the user application instead.
					                              */
					uint8_t  PrevReportINBufferSize; /**< Size in bytes of the given input report buffer. This is used to create a
					                                  *  second buffer of the same size within the driver so that subsequent reports
					                                  *  can be compared.
					                                  */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */										 
				struct
				{
					bool     UsingReportProtocol; /**< Indicates if the HID interface is set to Boot or Report protocol mode */
					uint16_t IdleCount; /**< Report idle period, in milliseconds, set by the host */
					uint16_t IdleMSRemaining; /**< Total number of milliseconds remaining before the idle period elapsed - this 
											   *   should be decremented by the user application if non-zero each millisecond */	
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_HID_Device_t;
	
		/* Function Prototypes: */
			/** Configures the endpoints of a given HID interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given HID interface is selected.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 *
			 *  \return Boolean true if the endpoints were sucessfully configured, false otherwise
			 */
			bool HID_Device_ConfigureEndpoints(USB_ClassInfo_HID_Device_t* HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Processes incomming control requests from the host, that are directed to the given HID class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_UnhandledControlRequest() event.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 */		
			void HID_Device_ProcessControlRequest(USB_ClassInfo_HID_Device_t* HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given HID class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 */
			void HID_Device_USBTask(USB_ClassInfo_HID_Device_t* HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Indicates that a millisecond of idle time has elapsed on the given HID interface, and the interface's idle count should be
			 *  decremented. This should be called once per millisecond so that hardware key-repeats function correctly. It is recommended
			 *  that this be called by the \ref EVENT_USB_Device_StartOfFrame() event, once SOF events have been enabled via
			 *  \ref USB_Device_EnableSOFEvents();.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 */
			void HID_Device_MillisecondElapsed(USB_ClassInfo_HID_Device_t* HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** HID class driver callback for the user creation of a HID IN report. This callback may fire in response to either
			 *  HID class control requests from the host, or by the normal HID endpoint polling procedure. Inside this callback the
			 *  user is responsible for the creation of the next HID input report to be sent to the host.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 *  \param[in,out] ReportID  If preset to a non-zero value, this is the report ID being requested by the host. If zero, this should
			 *                 be set to the report ID of the generated HID input report (if any). If multiple reports are not sent via the
			 *                 given HID interface, this parameter should be ignored.
			 *  \param[out] ReportData  Pointer to a buffer where the generated HID report should be stored.
			 *  \param[out] ReportSize  Number of bytes in the generated input report, or zero if no report is to be sent
			 *
			 *  \return Boolean true to force the sending of the report even if it is identical to the previous report and still within
			 *          the idle period (useful for devices which report relative movement), false otherwise
			 */
			bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
                                                     void* ReportData, uint16_t* ReportSize) ATTR_NON_NULL_PTR_ARG(1, 2, 3, 4);
			
			/** HID class driver callback for the user processing of a received HID OUT report. This callback may fire in response to
			 *  either HID class control requests from the host, or by the normal HID endpoint polling procedure. Inside this callback
			 *  the user is responsible for the processing of the received HID output report from the host.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class configuration and state
			 *  \param[in] ReportID  Report ID of the received output report. If multiple reports are not received via the given HID
			 *                   interface, this parameter should be ignored.
			 *  \param[in] ReportData  Pointer to a buffer where the received HID report is stored.
			 *  \param[in] ReportSize  Size in bytes of the received report from the host.
			 */
			void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID,
			                                          const void* ReportData, const uint16_t ReportSize) ATTR_NON_NULL_PTR_ARG(1, 3);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
