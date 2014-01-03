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
 *  \brief Host mode driver for the library USB CDC Class driver.
 *
 *  Host mode driver for the library USB CDC Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassCDC
 *  \defgroup Group_USBClassCDCHost CDC Class Host Mode Driver
 *
 *  \section Sec_USBClassCDCHost_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/CDCClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassCDCHost_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the CDC USB Class driver.
 *
 *  @{
 */

#ifndef __CDC_CLASS_HOST_H__
#define __CDC_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/CDCClassCommon.h"

		#include <stdio.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_CDC_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief CDC Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the CDC class driver functions as the \c CDCInterfaceInfo parameter. This
			 *  stores each CDC interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */
					USB_Pipe_Table_t NotificationPipe; /**< Notification IN Pipe configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref CDC_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state.
					                */
					uint8_t  ControlInterfaceNumber; /**< Interface index of the CDC-ACM control interface within the attached device. */

					struct
					{
						uint16_t HostToDevice; /**< Control line states from the host to device, as a set of \c CDC_CONTROL_LINE_OUT_*
						                        *   masks - to notify the device of changes to these values, call the
						                        *   \ref CDC_Host_SendControlLineStateChange() function.
						                        */
						uint16_t DeviceToHost; /**< Control line states from the device to host, as a set of \c CDC_CONTROL_LINE_IN_*
						                        *   masks. This value is updated each time \ref CDC_Host_USBTask() is called.
						                        */
					} ControlLineStates; /**< Current states of the virtual serial port's control lines between the device and host. */

					CDC_LineEncoding_t LineEncoding; /**< Line encoding used in the virtual serial port, for the device's information.
					                                  *   This is generally only used if the virtual serial port data is to be
					                                  *   reconstructed on a physical UART. When set by the host application, the
					                                  *   \ref CDC_Host_SetLineEncoding() function must be called to push the changes
					                                  *   to the device.
					                                  */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_CDC_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref CDC_Host_ConfigurePipes() function. */
			enum CDC_Host_EnumerationFailure_ErrorCodes_t
			{
				CDC_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				CDC_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				CDC_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible CDC interface was not found in the device's Configuration Descriptor. */
				CDC_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** General management task for a given CDC host class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing an CDC Class host configuration and state.
			 */
			void CDC_Host_USBTask(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Host interface configuration routine, to configure a given CDC host interface instance using the Configuration
			 *  Descriptor read from an attached USB device. This function automatically updates the given CDC Host instance's
			 *  state values and configures the pipes required to communicate with the interface if it is found within the device.
			 *  This should be called once after the stack has enumerated the attached device, while the host state machine is in
			 *  the Addressed state.
			 *
			 *  \param[in,out] CDCInterfaceInfo      Pointer to a structure containing an CDC Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref CDC_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t CDC_Host_ConfigurePipes(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                                uint16_t ConfigDescriptorSize,
			                                void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** Sets the line encoding for the attached device's virtual serial port. This should be called when the \c LineEncoding
			 *  values of the interface have been changed to push the new settings to the USB device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SetLineEncoding(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a Serial Control Line State Change notification to the device. This should be called when the virtual serial
			 *  control lines (DTR, RTS, etc.) have changed states. Line states persist until they are cleared via a second
			 *  notification. This should be called each time the CDC class driver's \c ControlLineStates.HostToDevice value is updated
			 *  to push the new states to the USB device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SendControlLineStateChange(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a Send Break request to the device. This is generally used to separate data or to indicate a special condition
			 *  to the receiving device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *  \param[in]     Duration          Duration of the break, in milliseconds.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SendBreak(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                           const uint8_t Duration) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given data buffer to the attached USB device, if connected. If a device is not connected when the function is
			 *  called, the data will be discarded. Bytes will be queued for transmission to the device until either the pipe bank
			 *  becomes full, or the \ref CDC_Host_Flush() function is called to flush the pending data to the device. This allows for
			 *  multiple bytes to be packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *  \param[in]     Buffer            Pointer to a buffer containing the data to send to the device.
			 *  \param[in]     Length            Length of the data to send to the device.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SendData(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                          const void* const Buffer,
			                          const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given null-terminated string to the attached USB device, if connected. If a device is not connected when the
			 *  function is called, the string is discarded. Bytes will be queued for transmission to the device until either the pipe
			 *  bank becomes full, or the \ref CDC_Host_Flush() function is called to flush the pending data to the device. This allows
			 *  for multiple bytes to be packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *  \param[in]     String            Pointer to the null terminated string to send to the device.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SendString(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                            const char* const String) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given byte to the attached USB device, if connected. If a device is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the device until either the pipe bank becomes full, or the
			 *  \ref CDC_Host_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be
			 *  packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *  \param[in]     Data              Byte of data to send to the device.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t CDC_Host_SendByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                          const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the CDC interface from the device, waiting to be read. This indicates the number
			 *  of bytes in the IN pipe bank only, and thus the number of calls to \ref CDC_Host_ReceiveByte() which are guaranteed to succeed
			 *  immediately. If multiple bytes are to be received, they should be buffered by the user application, as the pipe bank will not be
			 *  released back to the USB controller until all bytes are read.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *
			 *  \return Total number of buffered bytes received from the device.
			 */
			uint16_t CDC_Host_BytesReceived(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the device. If no data is waiting to be read of if a USB device is not connected, the function
			 *  returns a negative value. The \ref CDC_Host_BytesReceived() function may be queried in advance to determine how many bytes
			 *  are currently buffered in the CDC interface's data receive pipe.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *
			 *  \return Next received byte from the device, or a negative value if no data received.
			 */
			int16_t CDC_Host_ReceiveByte(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t CDC_Host_Flush(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			#if defined(FDEV_SETUP_STREAM) || defined(__DOXYGEN__)
			/** Creates a standard character stream for the given CDC Device instance so that it can be used with all the regular
			 *  functions in the standard \c <stdio.h> library that accept a \c FILE stream as a destination (e.g. \c fprintf). The created
			 *  stream is bidirectional and can be used for both input and output functions.
			 *
			 *  Reading data from this stream is non-blocking, i.e. in most instances, complete strings cannot be read in by a single
			 *  fetch, as the endpoint will not be ready at some point in the transmission, aborting the transfer. However, this may
			 *  be used when the read data is processed byte-per-bye (via \c getc()) or when the user application will implement its own
			 *  line buffering.
			 *
			 *  \note The created stream can be given as \c stdout if desired to direct the standard output from all \c <stdio.h> functions
			 *        to the given CDC interface.
			 *        \n\n
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void CDC_Host_CreateStream(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                           FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Identical to \ref CDC_Host_CreateStream(), except that reads are blocking until the calling stream function terminates
			 *  the transfer. While blocking, the USB and CDC service tasks are called repeatedly to maintain USB communications.
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void CDC_Host_CreateBlockingStream(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo,
			                                   FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1)  ATTR_NON_NULL_PTR_ARG(2);
			#endif

			/** CDC class driver event for a control line state change on a CDC host interface. This event fires each time the device notifies
			 *  the host of a control line state change (containing the virtual serial control line states, such as DCD) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new control line states
			 *  are available in the \c ControlLineStates.DeviceToHost value inside the CDC host interface structure passed as a parameter, set as
			 *  a mask of \c CDC_CONTROL_LINE_IN_* masks.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class host configuration and state.
			 */
			void EVENT_CDC_Host_ControLineStateChanged(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_CDC_HOST_C)
				#if defined(FDEV_SETUP_STREAM)
				static int CDC_Host_putchar(char c,
				                            FILE* Stream) ATTR_NON_NULL_PTR_ARG(2);
				static int CDC_Host_getchar(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				static int CDC_Host_getchar_Blocking(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				#endif

				void CDC_Host_Event_Stub(void) ATTR_CONST;

				void EVENT_CDC_Host_ControLineStateChanged(USB_ClassInfo_CDC_Host_t* const CDCInterfaceInfo)
				                                           ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Host_Event_Stub);

				static uint8_t DCOMP_CDC_Host_NextCDCControlInterface(void* const CurrentDescriptor)
				                                                      ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_CDC_Host_NextCDCDataInterface(void* const CurrentDescriptor)
				                                                   ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_CDC_Host_NextCDCInterfaceEndpoint(void* const CurrentDescriptor)
				                                                       ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

