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
 *  \brief Host mode driver for the library USB Printer Class driver.
 *
 *  Host mode driver for the library USB Printer Class driver.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB module driver
 *        dispatch header located in LUFA/Drivers/USB.h.
 */

/** \ingroup Group_USBClassPrinter
 *  \defgroup Group_USBClassPrinterHost Printer Class Host Mode Driver
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/USB/Class/Host/PrinterClassHost.c <i>(Makefile source module name: LUFA_SRC_USBCLASS)</i>
 *
 *  \section Sec_ModDescription Module Description
 *  Host Mode USB Class driver framework interface, for the Printer USB Class driver.
 *
 *  @{
 */

#ifndef __PRINTER_CLASS_HOST_H__
#define __PRINTER_CLASS_HOST_H__

	/* Includes: */
		#include "../../USB.h"
		#include "../Common/PrinterClassCommon.h"

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
			/** \brief Printer Class Host Mode Configuration and State Structure.
			 *
			 *  Class state structure. An instance of this structure should be made within the user application,
			 *  and passed to each of the Printer class driver functions as the \c PRNTInterfaceInfo parameter. This
			 *  stores each Printer interface's configuration and state information.
			 */
			typedef struct
			{
				struct
				{
					USB_Pipe_Table_t DataINPipe; /**< Data IN Pipe configuration table. */
					USB_Pipe_Table_t DataOUTPipe; /**< Data OUT Pipe configuration table. */
				} Config; /**< Config data for the USB class interface within the device. All elements in this section
				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
				           */
				struct
				{
					bool IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
					                *   after \ref PRNT_Host_ConfigurePipes() is called and the Host state machine is in the
					                *   Configured state.
					                */
					uint8_t InterfaceNumber; /**< Interface index of the Printer interface within the attached device. */
					uint8_t AlternateSetting; /**< Alternate setting within the Printer Interface in the attached device. */
				} State; /**< State data for the USB class interface within the device. All elements in this section
						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
						  *   the interface is enumerated.
						  */
			} USB_ClassInfo_PRNT_Host_t;

		/* Enums: */
			/** Enum for the possible error codes returned by the \ref PRNT_Host_ConfigurePipes() function. */
			enum PRNT_Host_EnumerationFailure_ErrorCodes_t
			{
				PRNT_ENUMERROR_NoError                    = 0, /**< Configuration Descriptor was processed successfully. */
				PRNT_ENUMERROR_InvalidConfigDescriptor    = 1, /**< The device returned an invalid Configuration Descriptor. */
				PRNT_ENUMERROR_NoCompatibleInterfaceFound = 2, /**< A compatible Printer interface was not found in the device's Configuration Descriptor. */
				PRNT_ENUMERROR_PipeConfigurationFailed    = 3, /**< One or more pipes for the specified interface could not be configured correctly. */
			};

		/* Function Prototypes: */
			/** Host interface configuration routine, to configure a given Printer host interface instance using the
			 *  Configuration Descriptor read from an attached USB device. This function automatically updates the given Printer
			 *  instance's state values and configures the pipes required to communicate with the interface if it is found within
			 *  the device. This should be called once after the stack has enumerated the attached device, while the host state
			 *  machine is in the Addressed state.
			 *
			 *  \param[in,out] PRNTInterfaceInfo     Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[in]     ConfigDescriptorSize  Length of the attached device's Configuration Descriptor.
			 *  \param[in]     ConfigDescriptorData  Pointer to a buffer containing the attached device's Configuration Descriptor.
			 *
			 *  \return A value from the \ref PRNT_Host_EnumerationFailure_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_ConfigurePipes(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                                 uint16_t ConfigDescriptorSize,
			                                 void* ConfigDescriptorData) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(3);

			/** General management task for a given Printer host class interface, required for the correct operation of
			 *  the interface. This should be called frequently in the main program loop, before the master USB management task
			 *  \ref USB_USBTask().
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 */
			void PRNT_Host_USBTask(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Configures the printer to enable Bidirectional mode, if it is not already in this mode. This should be called
			 *  once the connected device's configuration has been set, to ensure the printer is ready to accept commands.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_SetBidirectionalMode(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Retrieves the status of the virtual Printer port's inbound status lines. The result can then be masked against the
			 *  \c PRNT_PORTSTATUS_* macros to determine the printer port's status.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[out]    PortStatus         Location where the retrieved port status should be stored.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_GetPortStatus(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                                uint8_t* const PortStatus)
			                                ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Soft-resets the attached printer, readying it for new commands.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *
			 *  \return A value from the \ref USB_Host_SendControlErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_SoftReset(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Flushes any data waiting to be sent, ensuring that the send buffer is cleared.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_Flush(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Sends the given null terminated string to the attached printer's input endpoint.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[in]     String             Pointer to a null terminated string to send.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_SendString(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                             const char* const String) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends the given raw data stream to the attached printer's input endpoint. This should contain commands that the
			 *  printer is able to understand - for example, PCL data. Not all printers accept all printer languages; see
			 *  \ref PRNT_Host_GetDeviceID() for details on determining acceptable languages for an attached printer.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[in]     Buffer             Pointer to a buffer containing the raw command stream to send to the printer.
			 *  \param[in]     Length             Size in bytes of the command stream to be sent.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_SendData(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                           const void* Buffer,
			                           const uint16_t Length) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

			/** Sends a given byte to the attached USB device, if connected. If a device is not connected when the function is called, the
			 *  byte is discarded. Bytes will be queued for transmission to the device until either the pipe bank becomes full, or the
			 *  \ref PRNT_Host_Flush() function is called to flush the pending data to the host. This allows for multiple bytes to be
			 *  packed into a single pipe packet, increasing data throughput.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[in]     Data               Byte of data to send to the device.
			 *
			 *  \return A value from the \ref Pipe_WaitUntilReady_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_SendByte(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                           const uint8_t Data) ATTR_NON_NULL_PTR_ARG(1);

			/** Determines the number of bytes received by the printer interface from the device, waiting to be read. This indicates the number
			 *  of bytes in the IN pipe bank only, and thus the number of calls to \ref PRNT_Host_ReceiveByte() which are guaranteed to succeed
			 *  immediately. If multiple bytes are to be received, they should be buffered by the user application, as the pipe bank will not be
			 *  released back to the USB controller until all bytes are read.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *
			 *  \return Total number of buffered bytes received from the device.
			 */
			uint16_t PRNT_Host_BytesReceived(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads a byte of data from the device. If no data is waiting to be read of if a USB device is not connected, the function
			 *  returns a negative value. The \ref PRNT_Host_BytesReceived() function may be queried in advance to determine how many bytes
			 *  are currently buffered in the Printer interface's data receive pipe.
			 *
			 *  \pre This function must only be called when the Host state machine is in the \ref HOST_STATE_Configured state or the
			 *       call will fail.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *
			 *  \return Next received byte from the device, or a negative value if no data received.
			 */
			int16_t PRNT_Host_ReceiveByte(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo) ATTR_NON_NULL_PTR_ARG(1);

			/** Retrieves the attached printer device's ID string, formatted according to IEEE 1284. This string is sent as a
			 *  Unicode string from the device and is automatically converted to an ASCII encoded C string by this function, thus
			 *  the maximum reportable string length is two less than the size given (to accommodate the Unicode string length
			 *  bytes which are removed).
			 *
			 *  This string, when supported, contains the model, manufacturer and acceptable printer languages for the attached device.
			 *
			 *  \param[in,out] PRNTInterfaceInfo  Pointer to a structure containing a Printer Class host configuration and state.
			 *  \param[out]    DeviceIDString     Pointer to a buffer where the Device ID string should be stored, in ASCII format.
			 *  \param[in]     BufferSize         Size in bytes of the buffer allocated for the Device ID string.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t PRNT_Host_GetDeviceID(USB_ClassInfo_PRNT_Host_t* const PRNTInterfaceInfo,
			                              char* const DeviceIDString,
			                              const uint16_t BufferSize) ATTR_NON_NULL_PTR_ARG(1) ATTR_NON_NULL_PTR_ARG(2);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_PRINTER_HOST_C)
				static uint8_t DCOMP_PRNT_Host_NextPRNTInterface(void* const CurrentDescriptor)
				                                                 ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
				static uint8_t DCOMP_PRNT_Host_NextPRNTInterfaceEndpoint(void* const CurrentDescriptor)
				                                                         ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(1);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

