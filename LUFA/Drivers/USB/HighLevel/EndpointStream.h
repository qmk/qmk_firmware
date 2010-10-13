/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief USB device endpoint stream function definitions.
 *
 *  This file contains structures, function prototypes and macros related to the sending and receiving of
 *  arbitrary data streams through the device's data endpoints when the library is initialized in USB device mode.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_EndpointRW  
 *  @defgroup Group_EndpointStreamRW Read/Write of Multi-Byte Streams
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of data streams from
 *  and to endpoints.
 *
 *  @{
 */ 

#ifndef __ENDPOINT_STREAM_H__
#define __ENDPOINT_STREAM_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <avr/eeprom.h>
		#include <stdbool.h>

		#include "../../../Common/Common.h"
		#include "USBTask.h"

		#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			#include "StreamCallbacks.h"
		#endif
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

		#if !defined(NO_STREAM_CALLBACKS) || defined(__DOXYGEN__)
			#define __CALLBACK_PARAM     , StreamCallbackPtr_t Callback
		#else
			#define __CALLBACK_PARAM
		#endif

	/* Public Interface - May be used in end-application: */
		/* Enums: */
			/** Enum for the possible error return codes of the Endpoint_*_Stream_* functions. */
			enum Endpoint_Stream_RW_ErrorCodes_t
			{
				ENDPOINT_RWSTREAM_NoError            = 0, /**< Command completed successfully, no error. */
				ENDPOINT_RWSTREAM_EndpointStalled    = 1, /**< The endpoint was stalled during the stream
				                                           *   transfer by the host or device.
				                                           */
				ENDPOINT_RWSTREAM_DeviceDisconnected = 2, /**< Device was disconnected from the host during
				                                           *   the transfer.
				                                           */
				ENDPOINT_RWSTREAM_BusSuspended       = 3, /**< The USB bus has been suspended by the host and
				                                           *   no USB endpoint traffic can occur until the bus
				                                           *   has resumed.
				                                           */
				ENDPOINT_RWSTREAM_Timeout            = 4, /**< The host failed to accept or send the next packet
				                                           *   within the software timeout period set by the
				                                           *   \ref USB_STREAM_TIMEOUT_MS macro.
				                                           */
				ENDPOINT_RWSTREAM_CallbackAborted    = 5, /**< Indicates that the stream's callback function
			                                               *   aborted the transfer early.
				                                           */
			};
			
			/** Enum for the possible error return codes of the Endpoint_*_Control_Stream_* functions. */
			enum Endpoint_ControlStream_RW_ErrorCodes_t
			{
				ENDPOINT_RWCSTREAM_NoError            = 0, /**< Command completed successfully, no error. */
				ENDPOINT_RWCSTREAM_HostAborted        = 1, /**< The aborted the transfer prematurely. */
				ENDPOINT_RWCSTREAM_DeviceDisconnected = 2, /**< Device was disconnected from the host during
				                                            *   the transfer.
				                                            */
				ENDPOINT_RWCSTREAM_BusSuspended       = 3, /**< The USB bus has been suspended by the host and
				                                            *   no USB endpoint traffic can occur until the bus
				                                            *   has resumed.
				                                            */
			};

		/* Function Prototypes: */
			/** Reads and discards the given number of bytes from the endpoint from the given buffer,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the next
			 *  packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Length    Number of bytes to send via the currently selected endpoint.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Discard_Stream(uint16_t Length
			                                __CALLBACK_PARAM);

			/** Writes the given number of bytes to the endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Endpoint_ClearIN() macro. Between each USB packet, the given stream callback function
			 *  is executed repeatedly until the endpoint is ready to accept the next packet, allowing for early
			 *  aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_LE(const void* Buffer,
			                                 uint16_t Length
			                                 __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Write_Stream_LE().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_EStream_LE(const void* Buffer,
			                                  uint16_t Length
			                                  __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Stream_LE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_PStream_LE(const void* Buffer,
			                                  uint16_t Length
			                                  __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Endpoint_ClearIN() macro. Between each USB packet, the given stream callback function
			 *  is executed repeatedly until the endpoint is ready to accept the next packet, allowing for early
			 *  aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_BE(const void* Buffer,
			                                 uint16_t Length
			                                 __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Write_Stream_BE().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_EStream_BE(const void* Buffer,
			                                  uint16_t Length
			                                  __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Stream_BE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_PStream_BE(const void* Buffer,
			                                  uint16_t Length
			                                  __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the endpoint
			 *  is ready to accept the next packet, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[out] Buffer    Pointer to the destination data buffer to write to.
			 *  \param[in]  Length    Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_LE(void* Buffer,
			                                uint16_t Length
			                                __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Read_Stream_LE().
			 *
			 *  \param[out] Buffer    Pointer to the destination data buffer to write to, located in EEPROM memory space.
			 *  \param[in]  Length    Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_EStream_LE(void* Buffer,
			                                 uint16_t Length
			                                 __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Reads the given number of bytes from the endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro. Between
			 *  each USB packet, the given stream callback function is executed repeatedly until the endpoint
			 *  is ready to accept the next packet, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[out] Buffer    Pointer to the destination data buffer to write to.
			 *  \param[in]  Length    Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_BE(void* Buffer,
			                                uint16_t Length
			                                __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Read_Stream_BE().
			 *
			 *  \param[out] Buffer    Pointer to the destination data buffer to write to, located in EEPROM memory space.
			 *  \param[in]  Length    Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_EStream_BE(void* Buffer,
			                                 uint16_t Length
			                                 __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the setup OUT to
			 *  finalize the transfer via the \ref Endpoint_ClearOUT() macro.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_Stream_LE(const void* Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of Endpoint_Write_Control_Stream_LE.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_EStream_LE(const void* Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Control_Stream_LE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_PStream_LE(const void* Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the setup OUT to
			 *  finalize the transfer via the \ref Endpoint_ClearOUT() macro.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_Stream_BE(const void* Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Write_Control_Stream_BE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_EStream_BE(const void* Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Control_Stream_BE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_PStream_BE(const void* Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  setup IN to finalize the transfer via the \ref Endpoint_ClearIN() macro.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_Stream_LE(void* Buffer,
			                                        uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Read_Control_Stream_LE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_EStream_LE(void* Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  setup IN to finalize the transfer via the \ref Endpoint_ClearIN() macro.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_Stream_BE(void* Buffer,
			                                        uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);
			
			/** EEPROM buffer source version of \ref Endpoint_Read_Control_Stream_BE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_EStream_BE(void* Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */

