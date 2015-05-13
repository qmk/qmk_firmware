/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Device mode driver for the library USB RNDIS Class driver.
 *
 *  Device mode driver for the library USB RNDIS Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassRNDIS
 *  \defgroup Group_USBClassRNDISDevice RNDIS Class Device Mode Driver
 *
 *  \section Sec_USBClassRNDISDevice_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/RNDISClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassRNDISDevice_ModDescription Module Description
 *  Device Mode USB Class driver framework interface, for the RNDIS USB Class driver.
 *
 *  @{
 */

#ifndef _RNDIS_CLASS_DEVICE_H_
#define _RNDIS_CLASS_DEVICE_H_

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
			/** \brief RNDIS Class Device Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made for each RNDIS interface
			 *  within the user application, and passed to each of the RNDIS class driver functions as the
			 *  \c RNDISInterfaceInfo parameter. This stores each RNDIS interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					uint8_t  ControlInterfaceNumber; /**< Interface number of the RNDIS control interface within the device. */

					USB_Endpoint_Table_t DataINEndpoint; /**< Data IN endpoint configuration table. */
					USB_Endpoint_Table_t DataOUTEndpoint; /**< Data OUT endpoint configuration table. */
					USB_Endpoint_Table_t NotificationEndpoint; /**< Notification IN Endpoint configuration table. */

					char*         AdapterVendorDescription; /**< String description of the adapter vendor. */
					MAC_Address_t AdapterMACAddress; /**< MAC address of the adapter. */

					uint8_t*      MessageBuffer; /**< Buffer where RNDIS messages can be stored by the internal driver. This
					                              *   should be at least 132 bytes in length for minimal functionality. */
					uint16_t      MessageBufferLength; /**< Length in bytes of the \ref MessageBuffer RNDIS buffer. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool     ResponseReady; /**< Internal flag indicating if a RNDIS message is waiting to be returned to the host. */
					uint8_t  CurrRNDISState; /**< Current RNDIS state of the adapter, a value from the \ref RNDIS_States_t enum. */
					uint32_t CurrPacketFilter; /**< Current packet filter mode, used internally by the class driver. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_RNDIS_Device_t;

		/* Function Prototypes: */
			/** Configures the endpoints of a given RNDIS interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration
			 *  containing the given RNDIS interface is selected.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 *
			 *  \return Boolean \c true if the endpoints were successfully configured, \c false otherwise.
			 */
			bool RNDIS_Device_ConfigureEndpoints(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incoming control requests from the host, that are directed to the given RNDIS class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_ControlRequest() event.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */
			void RNDIS_Device_ProcessControlRequest(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given RNDIS class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing a RNDIS Class configuration and state.
			 */
			void RNDIS_Device_USBTask(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines if a packet is currently waiting for the device to read in and process.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class configuration and state.
			 *
			 *  \return Boolean \c true if a packet is waiting to be read in by the host, \c false otherwise.
			 */
			bool RNDIS_Device_IsPacketReceived(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Retrieves the next pending packet from the device, discarding the remainder of the RNDIS packet header to leave
			 *  only the packet contents for processing by the device in the nominated buffer.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class configuration and state.
			 *  \param[out]    Buffer              Pointer to a buffer where the packer data is to be written to.
			 *  \param[out]    PacketLength        Pointer to where the length in bytes of the read packet is to be stored.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t RNDIS_Device_ReadPacket(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo,
											void* Buffer,
											uint16_t* const PacketLength) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends the given packet to the attached RNDIS device, after adding a RNDIS packet message header.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] RNDISInterfaceInfo  Pointer to a structure containing an RNDIS Class configuration and state.
			 *  \param[in]     Buffer              Pointer to a buffer where the packer data is to be read from.
			 *  \param[in]     PacketLength        Length in bytes of the packet to send.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t RNDIS_Device_SendPacket(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo,
											void* Buffer,
											const uint16_t PacketLength) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define RNDIS_DEVICE_MIN_MESSAGE_BUFFER_LENGTH  sizeof(AdapterSupportedOIDList) + sizeof(RNDIS_Query_Complete_t)

		/* Function Prototypes: */
		#if defined(__INCLUDE_FROM_RNDIS_DEVICE_C)
			static void RNDIS_Device_ProcessRNDISControlMessage(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo)
			                                                    ATTR_NON_NULL_PTR_ARG(1);
			static bool RNDIS_Device_ProcessNDISQuery(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo,
			                                          const uint32_t OId,
                                                      void* const QueryData,
                                                      const uint16_t QuerySize,
										              void* ResponseData,
                                                      uint16_t* const ResponseSize) ATTR_NON_NULL_PTR_ARG(1)
			                                          ATTR_NON_NULL_PTR_ARG(5) ATTR_NON_NULL_PTR_ARG(6);
			static bool RNDIS_Device_ProcessNDISSet(USB_ClassInfo_RNDIS_Device_t* const RNDISInterfaceInfo,
                                                    const uint32_t OId,
			                                        const void* SetData,
                                                    const uint16_t SetSize) ATTR_NON_NULL_PTR_ARG(1)
			                                        ATTR_NON_NULL_PTR_ARG(3);
		#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

