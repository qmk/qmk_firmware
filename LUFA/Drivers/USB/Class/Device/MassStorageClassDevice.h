/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Device mode driver for the library USB Mass Storage Class driver.
 *
 *  Device mode driver for the library USB Mass Storage Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassMS
 *  \defgroup Group_USBClassMSDevice Mass Storage Class Device Mode Driver
 *
 *  \section Sec_USBClassMSDevice_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/MassStorageClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassMSDevice_ModDescription Module Description
 *  Device Mode USB Class driver framework interface, for the Mass Storage USB Class driver.
 *
 *  @{
 */

#ifndef _MS_CLASS_DEVICE_H_
#define _MS_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/MassStorageClassCommon.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_MS_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief Mass Storage Class Device Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made for each Mass Storage interface
			 *  within the user application, and passed to each of the Mass Storage class driver functions as the
			 *  \c MSInterfaceInfo parameter. This stores each Mass Storage interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					uint8_t  InterfaceNumber; /**< Interface number of the Mass Storage interface within the device. */

					USB_Endpoint_Table_t DataINEndpoint; /**< Data IN endpoint configuration table. */
					USB_Endpoint_Table_t DataOUTEndpoint; /**< Data OUT endpoint configuration table. */

					uint8_t  TotalLUNs; /**< Total number of logical drives in the Mass Storage interface. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					MS_CommandBlockWrapper_t  CommandBlock; /**< Mass Storage class command block structure, stores the received SCSI
															 *   command from the host which is to be processed.
															 */
					MS_CommandStatusWrapper_t CommandStatus; /**< Mass Storage class command status structure, set elements to indicate
															  *   the issued command's success or failure to the host.
															  */
					volatile bool IsMassStoreReset; /**< Flag indicating that the host has requested that the Mass Storage interface be reset
											         *   and that all current Mass Storage operations should immediately abort.
											         */
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_MS_Device_t;

		/* Function Prototypes: */
			/** Configures the endpoints of a given Mass Storage interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given Mass Storage interface is selected.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 *
			 *  \return Boolean \c true if the endpoints were successfully configured, \c false otherwise.
			 */
			bool MS_Device_ConfigureEndpoints(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incoming control requests from the host, that are directed to the given Mass Storage class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_ControlRequest() event.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 */
			void MS_Device_ProcessControlRequest(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given Mass Storage class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a Mass Storage configuration and state.
			 */
			void MS_Device_USBTask(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Mass Storage class driver callback for the user processing of a received SCSI command. This callback will fire each time the
			 *  host sends a SCSI command which requires processing by the user application. Inside this callback the user is responsible
			 *  for the processing of the received SCSI command from the host. The SCSI command is available in the CommandBlock structure
			 *  inside the Mass Storage class state structure passed as a parameter to the callback function.
			 *
			 *  \param[in,out] MSInterfaceInfo  Pointer to a structure containing a Mass Storage Class configuration and state.
			 *
			 *  \return Boolean \c true if the SCSI command was successfully processed, \c false otherwise.
			 */
			bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_MASSSTORAGE_DEVICE_C)
				static void MS_Device_ReturnCommandStatus(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
				static bool MS_Device_ReadInCommandBlock(USB_ClassInfo_MS_Device_t* const MSInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);
			#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

