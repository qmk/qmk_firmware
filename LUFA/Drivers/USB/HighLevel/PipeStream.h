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
 *  \brief USB host pipe stream function definitions.
 *
 *  This file contains structures, function prototypes and macros related to the sending and receiving of
 *  arbitrary data streams through the device's data pipes when the library is initialized in USB host mode.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_PipeRW  
 *  @defgroup Group_PipeStreamRW Read/Write of Multi-Byte Streams
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of data streams from
 *  and to pipes.
 *
 *  @{
 */

#ifndef __PIPE_STREAM_H__
#define __PIPE_STREAM_H__

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
			/** Enum for the possible error return codes of the Pipe_*_Stream_* functions. */
			enum Pipe_Stream_RW_ErrorCodes_t
			{
				PIPE_RWSTREAM_NoError            = 0, /**< Command completed successfully, no error. */
				PIPE_RWSTREAM_PipeStalled        = 1, /**< The device stalled the pipe during the transfer. */		
				PIPE_RWSTREAM_DeviceDisconnected = 2, /**< Device was disconnected from the host during
			                                           *   the transfer.
			                                           */		
				PIPE_RWSTREAM_Timeout            = 3, /**< The device failed to accept or send the next packet
				                                       *   within the software timeout period set by the
				                                       *   \ref USB_STREAM_TIMEOUT_MS macro.
				                                       */
				PIPE_RWSTREAM_CallbackAborted    = 4, /**< Indicates that the stream's callback function aborted
			                                           *   the transfer early.
				                                       */
			};

		/* Function Prototypes: */
			/** Reads and discards the given number of bytes from the pipe, discarding fully read packets from the host
			 *  as needed. The last packet is not automatically discarded once the remaining bytes has been read; the
			 *  user is responsible for manually discarding the last packet from the device via the \ref Pipe_ClearIN() macro.
			 *  Between each USB packet, the given stream callback function is executed repeatedly until the next packet is ready,
			 *  allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *  having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Length    Number of bytes to send via the currently selected pipe.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Discard_Stream(uint16_t Length
			                            __CALLBACK_PARAM);

			/** Writes the given number of bytes to the pipe from the given buffer in little endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearOUT() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *  having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_Stream_LE(const void* Buffer,
			                             uint16_t Length
			                             __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Pipe_Write_Stream_LE().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_EStream_LE(const void* Buffer,
			                              uint16_t Length
			                              __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);
			
			/** FLASH buffer source version of \ref Pipe_Write_Stream_LE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_PStream_LE(const void* Buffer,
			                              uint16_t Length
			                              __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Writes the given number of bytes to the pipe from the given buffer in big endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearOUT() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *  having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_Stream_BE(const void* Buffer,
			                             uint16_t Length
			                             __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Pipe_Write_Stream_BE().
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_EStream_BE(const void* Buffer,
			                              uint16_t Length
			                              __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);
			
			/** FLASH buffer source version of \ref Pipe_Write_Stream_BE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer    Pointer to the source data buffer to read from.
			 *  \param[in] Length    Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_PStream_BE(const void* Buffer,
			                              uint16_t Length
			                              __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the pipe into the given buffer in little endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearIN() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *  having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[out] Buffer    Pointer to the source data buffer to write to.
			 *  \param[in]  Length    Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_Stream_LE(void* Buffer,
			                            uint16_t Length
			                            __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Pipe_Read_Stream_LE().
			 *
			 *  \param[out] Buffer    Pointer to the source data buffer to write to.
			 *  \param[in]  Length    Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_EStream_LE(void* Buffer,
			                             uint16_t Length
			                             __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the pipe into the given buffer in big endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearIN() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *	The callback routine should be created according to the information in \ref Group_StreamCallbacks.
			 *  If the token NO_STREAM_CALLBACKS is passed via the -D option to the compiler, stream callbacks are
			 *  disabled and this function has the Callback parameter omitted.
			 *
			 *  The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *  having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[out] Buffer    Pointer to the source data buffer to write to.
			 *  \param[in]  Length    Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_Stream_BE(void* Buffer,
			                            uint16_t Length
			                            __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);
			
			/** EEPROM buffer source version of \ref Pipe_Read_Stream_BE().
			 *
			 *  \param[out] Buffer    Pointer to the source data buffer to write to.
			 *  \param[in]  Length    Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  Callback  Name of a callback routine to call between successive USB packet transfers, NULL if no callback.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_EStream_BE(void* Buffer,
			                             uint16_t Length
			                             __CALLBACK_PARAM) ATTR_NON_NULL_PTR_ARG(1);

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */

