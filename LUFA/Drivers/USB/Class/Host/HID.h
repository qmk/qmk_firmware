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
 *  @defgroup Group_USBClassHIDHost HID Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/HID.c
 *    - LUFA/Drivers/USB/Class/Host/HIDParser.c
 *
 *  \section Module Description
 *  Host Mode USB Class driver framework interface, for the HID USB Class driver.
 *
 *  @{
 */

#ifndef __HID_CLASS_HOST_H__
#define __HID_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/HID.h"
		#include "HIDParser.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Error code for some HID Host functions, indicating a logical (and not hardware) error */
			#define HID_ERROR_LOGICAL              0x80
	
		/* Type Defines: */
			/** Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the HID class driver functions as the HIDInterfaceInfo parameter. This
			 *  stores each HID interface's configuration and state information.
			 */
			typedef struct
			{
				const struct
				{
					uint8_t  DataINPipeNumber; /**< Pipe number of the HID interface's IN data pipe */
					bool     DataINPipeDoubleBank; /** Indicates if the HID interface's IN data pipe should use double banking */

					uint8_t  DataOUTPipeNumber; /**< Pipe number of the HID interface's OUT data pipe */
					bool     DataOUTPipeDoubleBank; /** Indicates if the HID interface's OUT data pipe should use double banking */

					uint8_t  HIDInterfaceProtocol; /**< HID interface protocol value to match against if a specific
					                                *   boot subclass protocol is required, either \ref HID_BOOT_MOUSE_PROTOCOL,
													*   \ref HID_BOOT_KEYBOARD_PROTOCOL or \ref HID_NON_BOOT_PROTOCOL if any
													*   HID device should be enumerated by the interface
					                                */
					#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
					HID_ReportInfo_t* HIDParserData; /**< HID parser data to store the parsed HID report data, when boot protocol
					                                  *   is not used
													  *
					                                  *  \note When the HID_HOST_BOOT_PROTOCOL_ONLY compile time token is defined,
					                                  *        this method is unavailable.
					                                  */
					#endif
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref HID_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state
					                */
					uint8_t InterfaceNumber; /**< Interface index of the HID interface within the attached device */

					uint16_t DataINPipeSize; /**< Size in bytes of the HID interface's IN data pipe */
					uint16_t DataOUTPipeSize;  /**< Size in bytes of the HID interface's OUT data pipe */
					
					bool SupportsBootProtocol; /**< Indicates if the current interface instance supports the HID Boot
					                            *   Protocol when enabled via \ref HID_Host_SetBootProtocol()
					                            */
					bool DeviceUsesOUTPipe; /**< Indicates if the current interface instance uses a seperate OUT data pipe for
					                         *   OUT reports, or if OUT reports are sent via the control pipe instead.
					                         */
					bool UsingBootProtocol; /**< Indicates that the interface is currently initialised in Boot Protocol mode */
					uint16_t HIDReportSize; /**< Size in bytes of the HID report descriptor in the device */
					
					uint8_t LargestReportSize; /**< Largest report the device will send, in bytes */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_HID_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref HID_Host_ConfigurePipes() function. */
			enum HIDHost_EnumerationFailure_ErrorCodes_t
			{
				HID_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully */
				HID_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor */
				HID_ENUMERROR_NoHIDInterfaceFound        = 2, /**< A compatible HID interface was not found in the device's Configuration Descriptor */
				HID_ENUMERROR_NoHIDDescriptorFound       = 3, /**< The HID descriptor was not found in the device's HID interface */
				HID_ENUMERROR_EndpointsNotFound          = 4, /**< Compatible HID endpoints were not found in the device's HID interface */
			};
	
		/* Function Prototypes: */
			/** General management task for a given Human Interface Class host class interface, required for the correct operation of
			 *  the interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 */
			void HID_Host_USBTask(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Host interface configuration routine, to configure a given HID host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given HID Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the
			 *  device. This should be called once after the stack has enumerated the attached device, while the host state
			 *  machine is in the Addressed state.
			 *
			 *  \note Once the device pipes are configured, the HID device's reporting protocol <b>must</b> be set via a call
			 *        to either the \ref HID_Host_SetBootProtocol() or \ref HID_Host_SetReportProtocol() function.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *  \param[in] ConfigDescriptorSize  Length of the attached device's Configuration Descriptor
			 *  \param[in] DeviceConfigDescriptor  Pointer to a buffer containing the attached device's Configuration Descriptor
			 *
			 *  \return A value from the \ref HIDHost_EnumerationFailure_ErrorCodes_t enum
			 */
			uint8_t HID_Host_ConfigurePipes(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, uint16_t ConfigDescriptorSize,
			                                void* DeviceConfigDescriptor) ATTR_NON_NULL_PTR_ARG(1, 3);


			/** Receives a HID IN report from the attached HID device, when a report has been received on the HID IN Data pipe.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *  \param[in] Buffer  Buffer to store the received report into
			 *
			 *  \return An error code from the \ref Pipe_Stream_RW_ErrorCodes_t enum
			 */
			uint8_t HID_Host_ReceiveReport(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, void* Buffer) ATTR_NON_NULL_PTR_ARG(1, 2);

			#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			/** Received a HID IN report from the attached device, by the report ID.
			 *
			 *  \note When the HID_HOST_BOOT_PROTOCOL_ONLY compile time token is defined, this method is unavailable.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *  \param[in] ReportID  Report ID of the received report if ControlRequest is false, set by the to the Report ID to fetch
			 *  \param[in] Buffer  Buffer to store the received report into
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum
			 */
			uint8_t HID_Host_ReceiveReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo, const uint8_t ReportID,
			                                   void* Buffer) ATTR_NON_NULL_PTR_ARG(1, 3);
			#endif
			
			/** Sends an OUT report to the currently attached HID device, using the device's OUT pipe if available or the device's
			 *  Control pipe if not.
			 *
			 *  \note When the HID_HOST_BOOT_PROTOCOL_ONLY compile time token is defined, the ReportID parameter is removed
			 *        from the parameter list of this function.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *  \param[in] ReportID  Report ID of the report to send to the device, or 0 if the device does not use report IDs
			 *  \param[in] Buffer  Buffer containing the report to send to the attached device
			 *  \param[in] ReportSize  Report size in bytes to send to the attached device
			 *
			 *  \return An error code from the \ref USB_Host_SendControlErrorCodes_t enum if the DeviceUsesOUTPipe flag is set in
			 *          the interface's state structure, a value from the \ref Pipe_Stream_RW_ErrorCodes_t enum otherwise
			 */
			uint8_t HID_Host_SendReportByID(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo,
			#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			                                const uint8_t ReportID,
			#endif
			                                void* Buffer, const uint16_t ReportSize)
			#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			                                ATTR_NON_NULL_PTR_ARG(1, 3);
			#else
			                                ATTR_NON_NULL_PTR_ARG(1, 2);
			#endif

			/** Determines if a HID IN report has been received from the attached device on the data IN pipe.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *
			 *  \return Boolean true if a report has been received, false otherwise
			 */
			bool HID_Host_IsReportReceived(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Switches the attached HID device's reporting protocol over to the Boot Report protocol mode, on supported devices.
			 *
			 *  \note When the HID_HOST_BOOT_PROTOCOL_ONLY compile time token is defined, this method must still be called
			 *        to explicitly place the attached device into boot protocol mode before use.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *
			 *  \return \ref HID_ERROR_LOGICAL if the device does not support Boot Protocol mode, a value from the
			 *          \ref USB_Host_SendControlErrorCodes_t enum otherwise
			 */
			uint8_t HID_Host_SetBootProtocol(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			#if !defined(HID_HOST_BOOT_PROTOCOL_ONLY)
			/** Switches the attached HID device's reporting protocol over to the standard Report protocol mode. This also retrieves
			 *  and parses the device's HID report descriptor, so that the size of each report can be determined in advance.
			 *
			 *  \note Whether this function is used or not, the \ref CALLBACK_HIDParser_FilterHIDReportItem() callback from the HID
			 *        Report Parser this function references <b>must</b> be implemented in the user code.
			 *
			 *  \note When the HID_HOST_BOOT_PROTOCOL_ONLY compile time token is defined, this method is unavailable.
			 *
			 *  \param[in,out] HIDInterfaceInfo  Pointer to a structure containing a HID Class host configuration and state
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum if an error occurs while retrieving the HID
			 *          Report descriptor or the setting of the Report protocol, \ref HID_ERROR_LOGICAL if the HID interface does
			 *          not have a valid \ref HID_ReportInfo_t structure set in its configuration, a mask of \ref HID_ERROR_LOGICAL
			 *          and a value from the \ref HID_Parse_ErrorCodes_t otherwise
			 */
			uint8_t HID_Host_SetReportProtocol(USB_ClassInfo_HID_Host_t* const HIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			#endif
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define HID_INTERFACE_CLASS             0x03
			
			#define HID_FOUND_DATAPIPE_IN           (1 << 0)
			#define HID_FOUND_DATAPIPE_OUT          (1 << 1)

		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_HID_CLASS_HOST_C)
				static uint8_t DComp_HID_Host_NextHIDInterface(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_NextHID(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DComp_HID_Host_NextHIDInterfaceEndpoint(void* const CurrentDescriptor) ATTR_NON_NULL_PTR_ARG(1);
			#endif	
	#endif	
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
