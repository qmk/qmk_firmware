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
 *  \brief Device mode driver for the library USB CDC Class driver.
 *
 *  Device mode driver for the library USB CDC Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassCDC
 *  \defgroup Group_USBClassCDCDevice CDC Class Device Mode Driver
 *
 *  \section Sec_USBClassCDCDevice_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/CDCClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassCDCDevice_ModDescription Module Description
 *  Device Mode USB Class driver framework interface, for the CDC USB Class driver.
 *
 *  \note There are several major drawbacks to the CDC-ACM standard USB class, however
 *        it is very standardized and thus usually available as a built-in driver on
 *        most platforms, and so is a better choice than a proprietary serial class.
 *
 *        One major issue with CDC-ACM is that it requires two Interface descriptors,
 *        which will upset most hosts when part of a multi-function "Composite" USB
 *        device. This is because each interface will be loaded into a separate driver
 *        instance, causing the two interfaces be become unlinked. To prevent this, you
 *        should use the "Interface Association Descriptor" addendum to the USB 2.0 standard
 *        which is available on most OSes when creating Composite devices.
 *
 *        Another major oversight is that there is no mechanism for the host to notify the
 *        device that there is a data sink on the host side ready to accept data. This
 *        means that the device may try to send data while the host isn't listening, causing
 *        lengthy blocking timeouts in the transmission routines. It is thus highly recommended
 *        that the virtual serial line DTR (Data Terminal Ready) signal be used where possible
 *        to determine if a host application is ready for data.
 *
 *  @{
 */

#ifndef _CDC_CLASS_DEVICE_H_
#define _CDC_CLASS_DEVICE_H_

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
			/** \brief CDC Class Device Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made for each CDC interface
			 *  within the user application, and passed to each of the CDC class driver functions as the
			 *  CDCInterfaceInfo parameter. This stores each CDC interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					uint8_t ControlInterfaceNumber; /**< Interface number of the CDC control interface within the device. */

					USB_Endpoint_Table_t DataINEndpoint; /**< Data IN endpoint configuration table. */
					USB_Endpoint_Table_t DataOUTEndpoint; /**< Data OUT endpoint configuration table. */
					USB_Endpoint_Table_t NotificationEndpoint; /**< Notification IN Endpoint configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					struct
					{
						uint16_t HostToDevice; /**< Control line states from the host to device, as a set of \c CDC_CONTROL_LINE_OUT_*
											    *   masks. This value is updated each time \ref CDC_Device_USBTask() is called.
											    */
						uint16_t DeviceToHost; /**< Control line states from the device to host, as a set of \c CDC_CONTROL_LINE_IN_*
											    *   masks - to notify the host of changes to these values, call the
											    *   \ref CDC_Device_SendControlLineStateChange() function.
											    */
					} ControlLineStates; /**< Current states of the virtual serial port's control lines between the device and host. */

					CDC_LineEncoding_t LineEncoding; /**< Line encoding used in the virtual serial port, for the device's information.
					                                  *   This is generally only used if the virtual serial port data is to be
					                                  *   reconstructed on a physical UART.
					                                  */
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_CDC_Device_t;

		/* Function Prototypes: */
			/** Configures the endpoints of a given CDC interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration containing
			 *  the given CDC interface is selected.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *
			 *  \return Boolean \c true if the endpoints were successfully configured, \c false otherwise.
			 */
			bool CDC_Device_ConfigureEndpoints(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incoming control requests from the host, that are directed to the given CDC class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_ControlRequest() event.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 */
			void CDC_Device_ProcessControlRequest(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given CDC class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 */
			void CDC_Device_USBTask(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** CDC class driver event for a line encoding change on a CDC interface. This event fires each time the host requests a
			 *  line encoding change (containing the serial parity, baud and other configuration information) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new line encoding
			 *  settings are available in the \c LineEncoding structure inside the CDC interface structure passed as a parameter.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 */
			void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** CDC class driver event for a control line state change on a CDC interface. This event fires each time the host requests a
			 *  control line state change (containing the virtual serial control line states, such as DTR) and may be hooked in the
			 *  user program by declaring a handler function with the same name and parameters listed here. The new control line states
			 *  are available in the \c ControlLineStates.HostToDevice value inside the CDC interface structure passed as a parameter, set as
			 *  a mask of \c CDC_CONTROL_LINE_OUT_* masks.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 */
			void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** CDC class driver event for a send break request sent to the device from the host. This is generally used to separate
			 *  data or to indicate a special condition to the receiving device.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in]     Duration          Duration of the break that has been sent by the host, in milliseconds.
			 */
			void EVENT_CDC_Device_BreakSent(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                                const uint8_t Duration) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given data buffer to the attached USB host, if connected. If a host is not connected when the function is
			 *  called, the string is discarded. Bytes will be queued for transmission to the host until either the endpoint bank
			 *  becomes full, or the \ref CDC_Device_Flush() function is called to flush the pending data to the host. This allows
			 *  for multiple bytes to be packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in]     Buffer            Pointer to a buffer containing the data to send to the device.
			 *  \param[in]     Length            Length of the data to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t CDC_Device_SendData(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                            const void* const Buffer,
			                            const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given null terminated string to the attached USB host, if connected. If a host is not connected when
			 *  the function is called, the string is discarded. Bytes will be queued for transmission to the host until either
			 *  the endpoint bank becomes full, or the \ref CDC_Device_Flush() function is called to flush the pending data to
			 *  the host. This allows for multiple bytes to be packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in]     String            Pointer to the null terminated string to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t CDC_Device_SendString(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                              const char* const String) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given byte to the attached USB host, if connected. If a host is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the host until either the endpoint bank becomes full, or the
			 *  \ref CDC_Device_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be
			 *  packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in]     Data              Byte of data to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t CDC_Device_SendByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                            const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the CDC interface from the host, waiting to be read. This indicates the number
			 *  of bytes in the OUT endpoint bank only, and thus the number of calls to \ref CDC_Device_ReceiveByte() which are guaranteed to
			 *  succeed immediately. If multiple bytes are to be received, they should be buffered by the user application, as the endpoint
			 *  bank will not be released back to the USB controller until all bytes are read.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *
			 *  \return Total number of buffered bytes received from the host.
			 */
			uint16_t CDC_Device_BytesReceived(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the host. If no data is waiting to be read of if a USB host is not connected, the function
			 *  returns a negative value. The \ref CDC_Device_BytesReceived() function may be queried in advance to determine how many
			 *  bytes are currently buffered in the CDC interface's data receive endpoint bank, and thus how many repeated calls to this
			 *  function which are guaranteed to succeed.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *
			 *  \return Next received byte from the host, or a negative value if no data received.
			 */
			int16_t CDC_Device_ReceiveByte(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t CDC_Device_Flush(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a Serial Control Line State Change notification to the host. This should be called when the virtual serial
			 *  control lines (DCD, DSR, etc.) have changed states, or to give BREAK notifications to the host. Line states persist
			 *  until they are cleared via a second notification. This should be called each time the CDC class driver's
			 *  \c ControlLineStates.DeviceToHost value is updated to push the new states to the USB host.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 */
			void CDC_Device_SendControlLineStateChange(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			#if defined(FDEV_SETUP_STREAM) || defined(__DOXYGEN__)
			/** Creates a standard character stream for the given CDC Device instance so that it can be used with all the regular
			 *  functions in the standard <stdio.h> library that accept a \c FILE stream as a destination (e.g. \c fprintf()). The created
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
			void CDC_Device_CreateStream(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                             FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Identical to \ref CDC_Device_CreateStream(), except that reads are blocking until the calling stream function terminates
			 *  the transfer. While blocking, the USB and CDC service tasks are called repeatedly to maintain USB communications.
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] CDCInterfaceInfo  Pointer to a structure containing a CDC Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void CDC_Device_CreateBlockingStream(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
			                                     FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);
			#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_CDC_DEVICE_C)
				#if defined(FDEV_SETUP_STREAM)
				static int CDC_Device_putchar(char c,
				                              FILE* Stream) ATTR_NON_NULL_PTR_ARG(2);
				static int CDC_Device_getchar(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				static int CDC_Device_getchar_Blocking(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				#endif

				void CDC_Device_Event_Stub(void) ATTR_CONST;

				void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
				                                          ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Device_Event_Stub);
				void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
				                                             ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(CDC_Device_Event_Stub);
				void EVENT_CDC_Device_BreakSent(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo,
				                                const uint8_t Duration) ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1)
				                                ATTR_ALIAS(CDC_Device_Event_Stub);
			#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

