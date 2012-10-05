/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Host mode driver for the library USB RNDIS Class driver.
 *
 *  Host mode driver for the library USB RNDIS Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassRNDIS
 *  \defgroup Group_USBClassRNDISHost RNDIS Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/RNDISClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the Microsoft RNDIS Ethernet
 *  USB Class driver.
 *
 *  @{
 */

#ifndef __RNDIS_CLASS_HOST_H__
#define __RNDIS_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/RNDISClassCommon.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_RNDIS_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief RNDIS Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the RNDIS class driver functions as the \c RNDISInterfaceInfo parameter. This
			 *  stores each RNDIS interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */
					USB_Pipe_Table_t NotificationPipe; /**< Notification IN Pipe configuration table. */

					uint32_t HostMaxPacketSize; /**< Maximum size of a packet which can be buffered by the host. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref RNDIS_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state.
					                */
					uint8_t ControlInterfaceNumber; /**< Interface index of the RNDIS control interface within the attached device. */

					uint32_t DeviceMaxPacketSize; /**< Maximum size of a packet which can be buffered by the attached RNDIS device. */

					uint32_t RequestID; /**< Request ID counter to give a unique ID for each command/response pair. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_RNDIS_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref RNDIS_Host_ConfigurePipes() function. */
			enum RNDIS_Host_EnumerationFailure_ErrorCodes_t
			{
				RNDIS_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				RNDIS_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				RNDIS_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible RNDIS interface was not found in the device's Configuration Descriptor. */
				RNDIS_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** Host interface configuration routine, to configure a given RNDIS host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given RNDIS Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the device.
			 *  This should be called once after the stack has enumerated the attached device, while the host state machine is in
			 *  the Addressed state.
			 *
			 *  \param[in,out] RNDISInterfaceInfo    Pointer to a structure containing an RNDIS Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref RNDIS_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t RNDIS_Host_ConfigurePipes(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
			                                  uint16_t ConfigDescriptorSize,
			                                  void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Sends a RNDIS KEEPALIVE command to the device, to ensure that it does not enter standby mode after periods
			 *  of long inactivity.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum or \ref RNDIS_ERROR_LOGICAL_CMD_FAILED if the device returned a
			 *          logical command failure.
			 */
			uint8_t RNDIS_Host_SendKeepAlive(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Initializes the attached RNDIS device's RNDIS interface. This should be called after the device's pipes have been
			 *  configured via the call to \ref RNDIS_Host_ConfigurePipes().
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum or \ref RNDIS_ERROR_LOGICAL_CMD_FAILED if the
			 *          device returned a logical command failure.
			 */
			uint8_t RNDIS_Host_InitializeDevice(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sets a given RNDIS property of an attached RNDIS device.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *  \param[in]     Oid                 OID number of the parameter to set.
			 *  \param[in]     Buffer              Pointer to where the property data is to be sourced from.
			 *  \param[in]     Length              Length in bytes of the property data to sent to the device.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum or \ref RNDIS_ERROR_LOGICAL_CMD_FAILED if the
			 *          device returned a logical command failure.
			 */
			uint8_t RNDIS_Host_SetRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
			                                    const uint32_t Oid,
			                                    void* Buffer,
			                                    const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Gets a given RNDIS property of an attached RNDIS device.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *  \param[in]     Oid                 OID number of the parameter to get.
			 *  \param[in]     Buffer              Pointer to where the property data is to be written to.
			 *  \param[in]     MaxLength           Length in bytes of the destination buffer size.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum or \ref RNDIS_ERROR_LOGICAL_CMD_FAILED if the
			 *          device returned a logical command failure.
			 */
			uint8_t RNDIS_Host_QueryRNDISProperty(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
			                                      const uint32_t Oid,
			                                      void* Buffer,
			                                      const uint16_t MaxLength) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Determines if a packet is currently waiting for the host to read in and process.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *
			 *  \return Boolean \c true if a packet is waiting to be read in by the host, \c false otherwise.
			 */
			bool RNDIS_Host_IsPacketReceived(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Retrieves the next pending packet from the device, discarding the remainder of the RNDIS packet header to leave
			 *  only the packet contents for processing by the host in the nominated buffer.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *  \param[out]    Buffer              Pointer to a buffer where the packer data is to be written to.
			 *  \param[out]    PacketLength        Pointer to where the length in bytes of the read packet is to be stored.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t RNDIS_Host_ReadPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
			                              void* Buffer,
			                              uint16_t* const PacketLength) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2)
			                              ATTR_NON_NULL_PTR_ARG(3);

			/** Sends the given packet to the attached RNDIS device, after adding a RNDIS packet message header.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 *  \param[in]     Buffer              Pointer to a buffer where the packer data is to be read from.
			 *  \param[in]     PacketLength        Length in bytes of the packet to send.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t RNDIS_Host_SendPacket(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
			                              void* Buffer,
			                              const uint16_t PacketLength) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

		/* Inline Functions: */
			/** General management task for a given RNDIS host class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class host configuration and state.
			 */
			static inline void RNDIS_Host_USBTask(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void RNDIS_Host_USBTask(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo)
			{
				(void)RNDISInterfaceInfo;
			}

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_RNDIS_HOST_C)
				static uint8_t RNDIS_SendEncapsulatedCommand(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
				                                             void* Buffer,
				                                             const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1)
				                                             ATTR_NON_NULL_PTR_ARG(2);
				static uint8_t RNDIS_GetEncapsulatedResponse(USB_ClassInfo_RNDIS_Host_t* const RNDISInterfaceInfo,
				                                             void* Buffer,
				                                             const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1)
				                                             ATTR_NON_NULL_PTR_ARG(2);

				static uint8_t DCOMP_RNDIS_Host_NextRNDISControlInterface(void* const CurrentDescriptor)
				                                                          ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_RNDIS_Host_NextRNDISDataInterface(void* const CurrentDescriptor)
				                                                       ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_RNDIS_Host_NextRNDISInterfaceEndpoint(void* const CurrentDescriptor)
				                                                           ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

