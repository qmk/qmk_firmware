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
 *  \brief Device mode driver for the library USB Printer Class driver.
 *
 *  Device mode driver for the library USB Printer Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassPrinter
 *  \defgroup Group_USBClassPrinterDevice Printer Class Device Mode Driver
 *
 *  \section Sec_USBClassPrinterDevice_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Device/PrinterClassDevice.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_USBClassPrinterDevice_ModDescription Module Description
 *  Device Mode USB Class driver framework interface, for the Printer USB Class driver.
 *
 *  @{
 */

#ifndef _PRINTER_CLASS_DEVICE_H_
#define _PRINTER_CLASS_DEVICE_H_

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/PrinterClassCommon.h"

		#include <stdio.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_PRINTER_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Type Defines: */
			/** \brief Printer Class Device Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made for each Printer interface
			 *  within the user application, and passed to each of the Printer class driver functions as the
			 *  PRNTInterfaceInfo parameter. This stores each Printer interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					uint8_t InterfaceNumber; /**< Interface number of the Printer interface within the device. */

					USB_Endpoint_Table_t DataINEndpoint; /**< Data IN endpoint configuration table. */
					USB_Endpoint_Table_t DataOUTEndpoint; /**< Data OUT endpoint configuration table. */

					char* IEEE1284String; /**< IEEE 1284 identification string, sent to the host during enumeration
					                       *   to identify the printer model, manufacturer and other characteristics.
					                       */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					uint8_t PortStatus; /**< Current status of the Printer virtual port, a collection of \c PRNT_PORTSTATUS_*
					                     *   bitmask values.
					                     */

					volatile bool IsPrinterReset; /**< Flag indicating that the host has requested that the Printer interface be reset
											       *   and that all current Mass Storage operations should immediately abort.
											       */
				} State; /**< State data for the USB class interface within the device. All elements in this section
				          *   are reset to their defaults when the interface is enumerated.
				          */
			} USB_ClassInfo_PRNT_Device_t;

		/* Function Prototypes: */
			/** Configures the endpoints of a given Printer interface, ready for use. This should be linked to the library
			 *  \ref EVENT_USB_Device_ConfigurationChanged() event so that the endpoints are configured when the configuration containing
			 *  the given Printer interface is selected.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *
			 *  \return Boolean \c true if the endpoints were successfully configured, \c false otherwise.
			 */
			bool PRNT_Device_ConfigureEndpoints(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Processes incoming control requests from the host, that are directed to the given Printer class interface. This should be
			 *  linked to the library \ref EVENT_USB_Device_ControlRequest() event.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 */
			void PRNT_Device_ProcessControlRequest(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** General management task for a given Printer class interface, required for the correct operation of the interface. This should
			 *  be called frequently in the main program loop, before the master USB management task \ref USB_USBTask().
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 */
			void PRNT_Device_USBTask(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Printer class driver event for a soft reset request on a Printer interface. This event fires each time the host
			 *  requests a reset of the printer interface's internal state, and may be hooked in the user program by declaring a
			 *  handler function with the same name and parameters listed here.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 */
			void EVENT_PRNT_Device_SoftReset(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends a given data buffer to the attached USB host, if connected. If a host is not connected when the function is
			 *  called, the string is discarded. Bytes will be queued for transmission to the host until either the endpoint bank
			 *  becomes full, or the \ref PRNT_Device_Flush() function is called to flush the pending data to the host. This allows
			 *  for multiple bytes to be packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *  \param[in]     Buffer            Pointer to a buffer containing the data to send to the device.
			 *  \param[in]     Length            Length of the data to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Device_SendData(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
			                             const void* const Buffer,
			                             const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given null terminated string to the attached USB host, if connected. If a host is not connected when
			 *  the function is called, the string is discarded. Bytes will be queued for transmission to the host until either
			 *  the endpoint bank becomes full, or the \ref PRNT_Device_Flush() function is called to flush the pending data to
			 *  the host. This allows for multiple bytes to be packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *  \param[in]     String            Pointer to the null terminated string to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Device_SendString(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
			                               const char* const String) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given byte to the attached USB host, if connected. If a host is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the host until either the endpoint bank becomes full, or the
			 *  \ref PRNT_Device_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be
			 *  packed into a single endpoint packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *  \param[in]     Data              Byte of data to send to the host.
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Device_SendByte(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
			                             const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the Printer interface from the host, waiting to be read. This indicates the number
			 *  of bytes in the OUT endpoint bank only, and thus the number of calls to \ref PRNT_Device_ReceiveByte() which are guaranteed to
			 *  succeed immediately. If multiple bytes are to be received, they should be buffered by the user application, as the endpoint
			 *  bank will not be released back to the USB controller until all bytes are read.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *
			 *  \return Total number of buffered bytes received from the host.
			 */
			uint16_t PRNT_Device_BytesReceived(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the host. If no data is waiting to be read of if a USB host is not connected, the function
			 *  returns a negative value. The \ref PRNT_Device_BytesReceived() function may be queried in advance to determine how many
			 *  bytes are currently buffered in the Printer interface's data receive endpoint bank, and thus how many repeated calls to this
			 *  function which are guaranteed to succeed.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *
			 *  \return Next received byte from the host, or a negative value if no data received.
			 */
			int16_t PRNT_Device_ReceiveByte(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \pre This function must only be called when the Device state machine is in the \ref DEVICE_STATE_Configured state or
			 *       the call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *
			 *  \return A value from the \ref Endpoint_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Device_Flush(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			#if defined(FDEV_SETUP_STREAM) || defined(__DOXYGEN__)
			/** Creates a standard character stream for the given Printer Device instance so that it can be used with all the regular
			 *  functions in the standard <stdio.h> library that accept a \c FILE stream as a destination (e.g. \c fprintf()). The created
			 *  stream is bidirectional and can be used for both input and output functions.
			 *
			 *  Reading data from this stream is non-blocking, i.e. in most instances, complete strings cannot be read in by a single
			 *  fetch, as the endpoint will not be ready at some point in the transmission, aborting the transfer. However, this may
			 *  be used when the read data is processed byte-per-bye (via \c getc()) or when the user application will implement its own
			 *  line buffering.
			 *
			 *  \note The created stream can be given as \c stdout if desired to direct the standard output from all \c <stdio.h> functions
			 *        to the given Printer interface.
			 *        \n\n
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void PRNT_Device_CreateStream(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
			                              FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Identical to \ref PRNT_Device_CreateStream(), except that reads are blocking until the calling stream function terminates
			 *  the transfer. While blocking, the USB and Printer service tasks are called repeatedly to maintain USB communications.
			 *
			 *  \note This function is not available on all microcontroller architectures.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class configuration and state.
			 *  \param[in,out] Stream            Pointer to a FILE structure where the created stream should be placed.
			 */
			void PRNT_Device_CreateBlockingStream(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo,
			                                      FILE* const Stream) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);
			#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_PRINTER_DEVICE_C)
				#if defined(FDEV_SETUP_STREAM)
				static int PRNT_Device_putchar(char c,
				                               FILE* Stream) ATTR_NON_NULL_PTR_ARG(2);
				static int PRNT_Device_getchar(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				static int PRNT_Device_getchar_Blocking(FILE* Stream) ATTR_NON_NULL_PTR_ARG(1);
				#endif

				void PRNT_Device_Event_Stub(void) ATTR_CONST;

				void EVENT_PRNT_Device_SoftReset(USB_ClassInfo_PRNT_Device_t* const PRNTInterfaceInfo)
				                                 ATTR_WEAK ATTR_NON_NULL_PTR_ARG(1) ATTR_ALIAS(PRNT_Device_Event_Stub);

			#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

