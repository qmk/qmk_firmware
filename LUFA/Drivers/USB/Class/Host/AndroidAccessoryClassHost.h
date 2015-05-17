/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Host mode driver for the library USB Android Open Accessory Class driver.
 *
 *  Host mode driver for the library USB Android Open Accessory Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassAOA
 *  \defgroup Group_USBClassAndroidAccessoryHost Android Open Accessory Class Host Mode Driver
 *
 *  \section Sec_USBClassAndroidAccessoryHost_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/AndroidAccessoryClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassAndroidAccessoryHost_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the Android Open Accessory USB Class driver.
 *
 *  @{
 */

#ifndef __AOA_CLASS_HOST_H__
#define __AOA_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/AndroidAccessoryClassCommon.h"

		#include <stdio.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_AOA_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Error code for some Android Open Accessory Host functions, indicating a logical (and not hardware) error. */
			#define AOA_ERROR_LOGICAL_CMD_FAILED              0x80

		/* Type Defines: */
			/** \brief Android Open Accessory Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the Android Open Accessory class driver functions as the \c AOAInterfaceInfo
			 *  parameter. This stores each Android Open Accessory interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */

					char*    PropertyStrings[AOA_STRING_TOTAL_STRINGS]; /**< Android Accessory property strings, sent to identify the accessory when the
					                                                     *   Android device is switched into Open Accessory mode. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref AOA_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state.
					                */
					uint8_t  InterfaceNumber; /**< Interface index of the AOA interface within the attached device. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_AOA_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref AOA_Host_ConfigurePipes() function. */
			enum AOA_Host_EnumerationFailure_ErrorCodes_t
			{
				AOA_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				AOA_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				AOA_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible Android Open Accessory interface was not found in the device's Configuration Descriptor. */
				AOA_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** General management task for a given Android Open Accessory host class interface, required for the correct operation of the interface.
			 *  This should be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing an Android Open Accessory Class host configuration and state.
			 */
			void AOA_Host_USBTask(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Validates a device descriptor, to check if the device is a valid Android device, and if it is currently in Android Open Accessory mode.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing an AOA Class host configuration and state.
			 *  \param[in]     DeviceDescriptor  Pointer a buffer containing the attached device's Device Descriptor.
			 *  \param[out]    NeedModeSwitch    Pointer to a boolean where the mode switch requirement of the attached device is to be stored.
			 *
			 *  \return Boolean \c true if the attached device is a valid Android device, \c false otherwise.
			 */
			bool AOA_Host_ValidateAccessoryDevice(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
                                                  const USB_Descriptor_Device_t* const DeviceDescriptor,
			                                      bool* const NeedModeSwitch) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2) ATTR_NON_NULL_PTR_ARG(3);

			/** Host interface configuration routine, to configure a given Android Open Accessory host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given Android Open Accessory Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the device. This should be
			 *  called once after the stack has enumerated the attached device, while the host state machine is in the Addressed state.
			 *
			 *  \param[in,out] AOAInterfaceInfo      Pointer to a structure containing an AOA Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref AOA_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t AOA_Host_ConfigurePipes(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                                uint16_t ConfigDescriptorSize,
			                                void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Starts Accessory Mode in the attached Android device. This function will validate the device's Android Open Accessory protocol
			 *  version, send the configured property strings, and request a switch to Android Open Accessory mode.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing an AOA Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum, or \ref AOA_ERROR_LOGICAL_CMD_FAILED if a logical error occurred..
			 */
			uint8_t AOA_Host_StartAccessoryMode(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given data buffer to the attached USB device, if connected. If a device is not connected when the function is
			 *  called, the data will be discarded. Bytes will be queued for transmission to the device until either the pipe bank
			 *  becomes full, or the \ref AOA_Host_Flush() function is called to flush the pending data to the device. This allows for
			 *  multiple bytes to be packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *  \param[in]     Buffer            Pointer to a buffer containing the data to send to the device.
			 *  \param[in]     Length            Length of the data to send to the device.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t AOA_Host_SendData(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                          const void* const Buffer,
			                          const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given null-terminated string to the attached USB device, if connected. If a device is not connected when the
			 *  function is called, the string is discarded. Bytes will be queued for transmission to the device until either the pipe
			 *  bank becomes full, or the \ref AOA_Host_Flush() function is called to flush the pending data to the device. This allows
			 *  for multiple bytes to be packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *  \param[in]     String            Pointer to the null terminated string to send to the device.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t AOA_Host_SendString(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                            const char* const String) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given byte to the attached USB device, if connected. If a device is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the device until either the pipe bank becomes full, or the
			 *  \ref AOA_Host_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be
			 *  packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *  \param[in]     Data              Byte of data to send to the device.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t AOA_Host_SendByte(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                          const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the AOA interface from the device, waiting to be read. This indicates the number
			 *  of bytes in the IN pipe bank only, and thus the number of calls to \ref AOA_Host_ReceiveByte() which are guaranteed to succeed
			 *  immediately. If multiple bytes are to be received, they should be buffered by the user application, as the pipe bank will not be
			 *  released back to the USB controller until all bytes are read.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *
			 *  \return Total number of buffered bytes received from the device.
			 */
			uint16_t AOA_Host_BytesReceived(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the device. If no data is waiting to be read of if a USB device is not connected, the function
			 *  returns a negative value. The \ref AOA_Host_BytesReceived() function may be queried in advance to determine how many bytes
			 *  are currently buffered in the AOA interface's data receive pipe.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *
			 *  \return Next received byte from the device, or a negative value if no data received.
			 */
			int16_t AOA_Host_ReceiveByte(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t AOA_Host_Flush(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Creates a standard character stream for the given AOA Device instance so that it can be used with all the regular
			 *  functions in the standard \c <stdio.h> library that accept a \c FILE stream as a destination (e.g. \c fprintf). The created
			 *  stream is bidirectional and can be used for both input and output functions.
			 *
			 *  Reading data from this stream is non-blocking, i.e. in most instances, complete strings cannot be read in by a single
			 *  fetch, as the endpoint will not be ready at some point in the transmission, aborting the transfer. However, this may
			 *  be used when the read data is processed byte-per-bye (via \c getc()) or when the user application will implement its own
			 *  line buffering.
			 *
			 *  \note The created stream can be given as \c stdout if desired to direct the standard output from all \c <stdio.h> functions
			 *        to the given AOA interface.
			 *        \n\n
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void AOA_Host_CreateStream(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                           FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Identical to \ref AOA_Host_CreateStream(), except that reads are blocking until the calling stream function terminates
			 *  the transfer. While blocking, the USB and AOA service tasks are called repeatedly to maintain USB communications.
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] AOAInterfaceInfo  Pointer to a structure containing a AOA Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void AOA_Host_CreateBlockingStream(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                                   FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_ANDROIDACCESSORY_HOST_C)
				#if defined(FDEV_SETUP_STREAM)
				static int AOA_Host_putchar(char c,
				                            FILE* Stream) ATTR_NON_NULL_PTR_ARG(2);
				static int AOA_Host_getchar(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				static int AOA_Host_getchar_Blocking(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				#endif

				static uint8_t AOA_Host_GetAccessoryProtocol(uint16_t* const Protocol) ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t AOA_Host_SendPropertyString(USB_ClassInfo_AOA_Host_t* const AOAInterfaceInfo,
			                                               const uint8_t StringIndex) ATTR_NON_NULL_PTR_ARG(1);

				static uint8_t DCOMP_AOA_Host_NextAndroidAccessoryInterface(void* const CurrentDescriptor)
				                                                            ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_AOA_Host_NextInterfaceBulkEndpoint(void* const CurrentDescriptor)
				                                                        ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */


