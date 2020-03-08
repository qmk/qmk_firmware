/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Host mode driver for the library USB Still Image Class driver.
 *
 *  Host mode driver for the library USB Still Image Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassSI
 *  \defgroup Group_USBClassStillImageHost Still Image Class Host Mode Driver
 *
 *  \section Sec_USBClassStillImageHost_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/StillImageClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassStillImageHost_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the Still Image USB Class driver.
 *
 *  @{
 */

#ifndef __SI_CLASS_HOST_H__
#define __SI_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/StillImageClassCommon.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_SI_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Error code for some Still Image Host functions, indicating a logical (and not hardware) error. */
			#define SI_ERROR_LOGICAL_CMD_FAILED              0x80

		/* Type Defines: */
			/** \brief Still Image Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the Still Image class driver functions as the \c SIInterfaceInfo parameter. This
			 *  stores each Still Image interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */
					USB_Pipe_Table_t EventsPipe; /**< Event notification IN Pipe configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool     IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                    *   after \ref SI_Host_ConfigurePipes() is called and the Host state machine is in the
					                    *   Configured state.
					                    */
					uint8_t  InterfaceNumber; /**< Interface index of the Still Image interface within the attached device. */

					bool IsSessionOpen; /**< Indicates if a PIMA session is currently open with the attached device. */
					uint32_t TransactionID; /**< Transaction ID for the next transaction to send to the device. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_SI_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref SI_Host_ConfigurePipes() function. */
			enum SI_Host_EnumerationFailure_ErrorCodes_t
			{
				SI_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				SI_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				SI_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible Still Image interface was not found in the device's
				                                              *   Configuration Descriptor.
				                                              */
				SI_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** Host interface configuration routine, to configure a given Still Image host interface instance using the
			 *  Configuration Descriptor read from an attached USB device. This function automatically updates the given Still
			 *  Image Host instance's state values and configures the pipes required to communicate with the interface if it is
			 *  found within the device. This should be called once after the stack has enumerated the attached device, while
			 *  the host state machine is in the Addressed state.
			 *
			 *  \param[in,out] SIInterfaceInfo       Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref SI_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t SI_Host_ConfigurePipes(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                               uint16_t ConfigDescriptorSize,
			                               void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Opens a new PIMA session with the attached device. This should be used before any session-orientated PIMA commands
			 *  are issued to the device. Only one session can be open at the one time.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure.
			 */
			uint8_t SI_Host_OpenSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Closes an already opened PIMA session with the attached device. This should be used after all session-orientated
			 *  PIMA commands have been issued to the device.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure.
			 */
			uint8_t SI_Host_CloseSession(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a raw PIMA block header to the device, filling out the transaction ID automatically. This can be used to send
			 *  arbitrary PIMA blocks to the device with or without parameters.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[in]     PIMAHeader       Pointer to a PIMA container structure that is to be sent.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t SI_Host_SendBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                                PIMA_Container_t* const PIMAHeader) ATTR_NON_NULL_PTR_ARG(1)
			                                ATTR_NON_NULL_PTR_ARG(2);

			/** Receives a raw PIMA block header from the device. This can be used to receive arbitrary PIMA blocks from the device with
			 *  or without parameters.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[out]    PIMAHeader       Pointer to a PIMA container structure where the received block is to be stored.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t SI_Host_ReceiveBlockHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                                   PIMA_Container_t* const PIMAHeader) ATTR_NON_NULL_PTR_ARG(1)
			                                   ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given PIMA command to the attached device, filling out the PIMA command header's Transaction ID automatically.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[in]     Operation        PIMA operation code to issue to the device.
			 *  \param[in]     TotalParams      Total number of 32-bit parameters to send to the device in the issued command block.
			 *  \param[in]     Params           Pointer to an array of 32-bit values containing the parameters to send in the command block.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure.
			 */
			uint8_t SI_Host_SendCommand(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                            const uint16_t Operation,
			                            const uint8_t TotalParams,
			                            uint32_t* const Params) ATTR_NON_NULL_PTR_ARG(1);

			/** Receives and checks a response block from the attached Still Image device, once a command has been issued and all data
			 *  associated with the command has been transferred.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure.
			 */
			uint8_t SI_Host_ReceiveResponse(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Indicates if the device has issued a PIMA event block to the host via the asynchronous events pipe.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *
			 *  \return Boolean \c true if an event is waiting to be read, \c false otherwise.
			 */
			bool SI_Host_IsEventReceived(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Receives an asynchronous event block from the device via the asynchronous events pipe.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[out]    PIMAHeader       Pointer to a PIMA container structure where the event should be stored.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum, or \ref SI_ERROR_LOGICAL_CMD_FAILED if the device
			 *          returned a logical command failure.
			 */
			uint8_t SI_Host_ReceiveEventHeader(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                                   PIMA_Container_t* const PIMAHeader) ATTR_NON_NULL_PTR_ARG(1)
			                                   ATTR_NON_NULL_PTR_ARG(2);

			/** Sends arbitrary data to the attached device, for use in the data phase of PIMA commands which require data
			 *  transfer beyond the regular PIMA command block parameters.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[in]     Buffer           Pointer to a buffer where the data to send has been stored.
			 *  \param[in]     Bytes            Length in bytes of the data in the buffer to send to the attached device.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t SI_Host_SendData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                         const void* Buffer,
			                         const uint16_t Bytes) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Receives arbitrary data from the attached device, for use in the data phase of PIMA commands which require data
			 *  transfer beyond the regular PIMA command block parameters.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 *  \param[out]    Buffer           Pointer to a buffer where the received data is to be stored.
			 *  \param[in]     Bytes            Length in bytes of the data to read.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t SI_Host_ReadData(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo,
			                         void* Buffer,
			                         const uint16_t Bytes) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

		/* Inline Functions: */
			/** General management task for a given Still Image host class interface, required for the correct operation of the
			 *  interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] SIInterfaceInfo  Pointer to a structure containing a Still Image Class host configuration and state.
			 */
			static inline void SI_Host_USBTask(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1) ATTR_ALWAYS_INLINE;
			static inline void SI_Host_USBTask(USB_ClassInfo_SI_Host_t* const SIInterfaceInfo)
			{
				(void)SIInterfaceInfo;
			}

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define SI_COMMAND_DATA_TIMEOUT_MS        10000

		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_STILLIMAGE_HOST_C)
				static uint8_t DCOMP_SI_Host_NextSIInterface(void* const CurrentDescriptor)
				                                             ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_SI_Host_NextSIInterfaceEndpoint(void* const CurrentDescriptor)
				                                                     ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

