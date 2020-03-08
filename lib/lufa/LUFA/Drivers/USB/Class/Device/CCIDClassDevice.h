/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2019  Filipe Rodrigues (filipepazrodrigues [at] gmail [dot] com)

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
 *  \brief Device mode driver for the library USB CCID Class driver.
 *
 *  Device mode driver for the library USB CCID Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassCCID
 *  \defgroup Group_USBClassCCIDDevice CCID Class Device Mode Driver
 *
 *  \section Sec_USBClassCCIDDevice_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/CCIDClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassCCIDDevice_ModDescription Module Description
 *  Device Mode USB Class driver framework interface, for the CCID USB Class driver.
 *
 *  @{
 */

#ifndef _CCID_CLASS_DEVICE_H_
#define _CCID_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/CCIDClassCommon.h"

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief CCID Class Device Mode Configuration and State Structure.
			 *
			 *	Class state structure. An instance of this structure should be made for each CCID interface
			 *	within the user application, and passed to each of the CCID class driver functions as the
			 *	CCIDInterfaceInfo parameter. This stores each CCID interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					uint8_t InterfaceNumber; /**< Interface number of the CCID interface within the device. */
					uint8_t TotalSlots; /**< Total of slots no this device. */
					USB_Endpoint_Table_t DataINEndpoint; /**< Data IN endpoint configuration table. */
					USB_Endpoint_Table_t DataOUTEndpoint; /**< Data OUT endpoint configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool    Aborted; //< Set if host has started an abort process
					uint8_t AbortedSeq; //< Sequence number for the current abort process
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
				USB_CCID_ProtocolData_T0_t ProtocolData;
			} USB_ClassInfo_CCID_Device_t;

	/* Function Prototypes: */
			/** Configures the endpoints of a given CCID interface, ready for use. This should be linked to the library
			 *	\ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration containing
			 *	the given CCID interface is selected.
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration.
			 *
			 *	\return Boolean \c true if the endpoints were successfully configured, \c false otherwise.
			 */
			bool CCID_Device_ConfigureEndpoints(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incoming control requests from the host, that are directed to the given CCID class interface. This should be
			 *	linked to the library \ref EVENT_USB_Device_ControlRequest() event.
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 */
			void CCID_Device_ProcessControlRequest(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given CCID class interface, required for the correct operation of the interface. This should
			 *	be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 */
			void CCID_Device_USBTask(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for PC_TO_RDR_IccPowerOn CCID message
			 *  When the ICC is inserted into a slot of a CCID, the CCID can activate the ICC, and the ICC will respond with an ATR
			 *  (answer to reset)
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 *  \param[in]     Slot 				The slot ID currently being powered on.
			 *  \param[in,out] Atr					Pointer to an array containing the Power On ATR being sent to the device.
			 *  \param[out]    AtrSize				The size of the ATR being sent (up to 15 bytes maximum).
			 *  \param[out]    Error				The result of the operation, or error.
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_IccPowerOn(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
			                                 const uint8_t Slot,
			                                 uint8_t* const Atr,
			                                 uint8_t* const AtrSize,
			                                 uint8_t* const Error) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for PC_TO_RDR_IccPowerOff CCID message
			 *  Turns off the ICC
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 *  \param[in]     Slot 				The slot ID currently being powered off.
			 *  \param[out]    Error				The result of the operation, or error.
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_IccPowerOff(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
			                                  const uint8_t Slot,
			                                  uint8_t* const Error) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for PC_TO_RDR_GetSlotStatus CCID message
			 *  Retrieves the current status of a given slot
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 *  \param[in]     Slot 				The slot ID from which we want to retrieve the status.
			 *  \param[out]    Error				The result of the operation, or error.
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_GetSlotStatus(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
			                                    const uint8_t Slot,
			                                    uint8_t* const Error) ATTR_NON_NULL_PTR_ARG(1);


			/** CCID class driver callback for PC_TO_RDR_SetParameters CCID message for T=0
			 *  Sets the current parameters of a given slot
			 *
			 *  \param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration, state and protocol data.
			 *  \param[in]     Slot 				The slot ID from which we want to retrieve the status.
			 *  \param[out]    Error				The result of the operation, or error.
			 *  \param[out]    T0 					Pointer to a buffer containing the new parameters
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_SetParameters_T0(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
												   const uint8_t Slot,
												   uint8_t* const Error,
												   USB_CCID_ProtocolData_T0_t* const T0) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for PC_TO_RDR_SetParameters CCID message for T=0
			 *  Retrieves the current parameters of a given slot
			 *
			 *  \param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration, state and protocol data.
			 *  \param[in]     Slot 				The slot ID from which we want to retrieve the status.
			 *  \param[out]    Error				The result of the operation, or error.
			 *  \param[out]    ProtocolNum			The CCID protocol ID of the parameter being retrieved.
			 *  \param[out]    T0 					Pointer to a buffer where the parameters will be returned
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_GetParameters_T0(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
												   const uint8_t Slot,
												   uint8_t* const Error,
												   uint8_t* const ProtocolNum,
												   USB_CCID_ProtocolData_T0_t* const T0) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for PC_TO_RDR_XfrBlock CCID message
			 *  Send a block of bytes from the host to a slot in the device
			 *  and also received a block of bytes as a response
			 *
			 *  \param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 *  \param[in]     Slot 				The slot ID from which we want to retrieve the status.
			 *  \param[in]     ReceivedBuffer 		Pointer to an array holding the received block of bytes
			 *  \param[in]     ReceivedBufferSize 	The size of the received block of bytes
			 *  \param[out]    SendBuffer 			Pointer to a buffer which will hold the bytes being sent back to the host
			 *  \param[out]    SentBufferSize 		The size of the block of bytes being sent back to the host
			 *  \param[out]    Error				The result of the operation, or error.
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_XfrBlock(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
										   const uint8_t Slot,
										   const uint8_t* ReceivedBuffer,
										   const uint8_t ReceivedBufferSize,
										   uint8_t* const SendBuffer,
										   uint8_t* const SentBufferSize,
										   uint8_t* const Error) ATTR_NON_NULL_PTR_ARG(1);

			/** CCID class driver callback for CCID_PC_to_RDR_Abort CCID message
			 *  Aborts a BULK out message previously sent to a slot
			 *
			 *	\param[in,out] CCIDInterfaceInfo	Pointer to a structure containing a CCID Class configuration and state.
			 *  \param[in]     Slot 				The slot ID to where the message being aborted was sent to.
			 *  \param[in]     Seq 					The current sequence number for this message. Must be checked against
			 *	               						the current abort message being sent at the control pipe.
			 *  \param[out]    Error				The result of the operation, or error.
			 *
			 *  \return	The command result code.
			 */
			uint8_t CALLBACK_CCID_Abort(USB_ClassInfo_CCID_Device_t* const CCIDInterfaceInfo,
			                            const uint8_t Slot,
			                            const uint8_t Seq,
			                            uint8_t* const Error) ATTR_NON_NULL_PTR_ARG(1);


#endif

/** @} */
