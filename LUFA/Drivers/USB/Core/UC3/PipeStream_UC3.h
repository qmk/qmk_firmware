/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.
              
  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Pipe data stream transmission and reception management for the AVR32 UC3 microcontrollers.
 *  \copydetails Group_PipeStreamRW_UC3
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_PipeStreamRW
 *  \defgroup Group_PipeStreamRW_UC3 Read/Write of Multi-Byte Streams (UC3)
 *  \brief Pipe data stream transmission and reception management for the Atmel AVR32 UC3 architecture.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of data streams from
 *  and to pipes.
 *
 *  @{
 */

#ifndef __PIPE_STREAM_UC3_H__
#define __PIPE_STREAM_UC3_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../USBMode.h"
		#include "../USBTask.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif
		
	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			/** \name Stream functions for null data */
			//@{

			/** Reads and discards the given number of bytes from the pipe, discarding fully read packets from the host
			 *  as needed. The last packet is not automatically discarded once the remaining bytes has been read; the
			 *  user is responsible for manually discarding the last packet from the device via the \ref Pipe_ClearIN() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once, failing or
			 *  succeeding as a single unit. If the BytesProcessed parameter points to a valid storage location, the transfer
			 *  will instead be performed as a series of chunks. Each time the pipe bank becomes empty while there is still data
			 *  to process (and after the current packet has been acknowledged) the BytesProcessed location will be updated with
			 *  the total number of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref PIPE_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed in the user code - to
			 *  continue the transfer, call the function again with identical parameters and it will resume until the BytesProcessed
			 *  value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Pipe_Discard_Stream(512, NULL)) != PIPE_RWSTREAM_NoError)
			 *  {
			 *       // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *  
			 *  <b>Partial Stream Transfers Example:</b>
			 *  \code
			 *  uint8_t  ErrorCode;
			 *  uint16_t BytesProcessed;
			 *  
			 *  BytesProcessed = 0;
			 *  while ((ErrorCode = Pipe_Discard_Stream(512, &BytesProcessed)) == PIPE_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != PIPE_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Length          Number of bytes to discard via the currently selected pipe.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                             updated, \c NULL if the entire stream should be processed at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Discard_Stream(uint16_t Length,
			                            uint16_t* const BytesProcessed);

			/** Writes a given number of zeroed bytes to the pipe, sending full pipe packets from the host to the device
			 *  as needed. The last packet is not automatically sent once the remaining bytes has been written; the
			 *  user is responsible for manually discarding the last packet from the device via the \ref Pipe_ClearOUT() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once, failing or
			 *  succeeding as a single unit. If the BytesProcessed parameter points to a valid storage location, the transfer
			 *  will instead be performed as a series of chunks. Each time the pipe bank becomes full while there is still data
			 *  to process (and after the current packet transmission has been initiated) the BytesProcessed location will be
			 *  updated with the total number of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref PIPE_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed in the user code - to
			 *  continue the transfer, call the function again with identical parameters and it will resume until the BytesProcessed
			 *  value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Pipe_Null_Stream(512, NULL)) != PIPE_RWSTREAM_NoError)
			 *  {
			 *       // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  <b>Partial Stream Transfers Example:</b>
			 *  \code
			 *  uint8_t  ErrorCode;
			 *  uint16_t BytesProcessed;
			 *  
			 *  BytesProcessed = 0;
			 *  while ((ErrorCode = Pipe_Null_Stream(512, &BytesProcessed)) == PIPE_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != PIPE_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Length          Number of zero bytes to write via the currently selected pipe.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                             updated, \c NULL if the entire stream should be processed at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Null_Stream(uint16_t Length,
			                         uint16_t* const BytesProcessed);

			//@}

			/** \name Stream functions for RAM source/destination data */
			//@{
			
			/** Writes the given number of bytes to the pipe from the given buffer in little endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearOUT() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the pipe bank becomes full while there is still data to process (and after the current
			 *  packet transmission has been initiated) the BytesProcessed location will be updated with the
			 *  total number of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref PIPE_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t DataStream[512];
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Pipe_Write_Stream_LE(DataStream, sizeof(DataStream),
			 *                                        NULL)) != PIPE_RWSTREAM_NoError)
			 *  {
			 *       // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  <b>Partial Stream Transfers Example:</b>
			 *  \code
			 *  uint8_t  DataStream[512];
			 *  uint8_t  ErrorCode;
			 *  uint16_t BytesProcessed;
			 *  
			 *  BytesProcessed = 0;
			 *  while ((ErrorCode = Pipe_Write_Stream_LE(DataStream, sizeof(DataStream),
			 *                                           &BytesProcessed)) == PIPE_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != PIPE_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                             updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_Stream_LE(const void* const Buffer,
			                             uint16_t Length,
			                             uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the pipe from the given buffer in big endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearOUT() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected pipe into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                             updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Write_Stream_BE(const void* const Buffer,
			                             uint16_t Length,
			                             uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the pipe into the given buffer in little endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearIN() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the pipe bank becomes empty while there is still data to process (and after the current
			 *  packet has been acknowledged) the BytesProcessed location will be updated with the total number
			 *  of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref PIPE_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t DataStream[512];
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Pipe_Read_Stream_LE(DataStream, sizeof(DataStream),
			 *                                       NULL)) != PIPE_RWSTREAM_NoError)
			 *  {
			 *       // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  <b>Partial Stream Transfers Example:</b>
			 *  \code
			 *  uint8_t  DataStream[512];
			 *  uint8_t  ErrorCode;
			 *  uint16_t BytesProcessed;
			 *  
			 *  BytesProcessed = 0;
			 *  while ((ErrorCode = Pipe_Read_Stream_LE(DataStream, sizeof(DataStream),
			 *                                          &BytesProcessed)) == PIPE_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != PIPE_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[out] Buffer          Pointer to the source data buffer to write to.
			 *  \param[in]  Length          Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                              updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_Stream_LE(void* const Buffer,
			                            uint16_t Length,
			                            uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the pipe into the given buffer in big endian,
			 *  sending full packets to the device as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Pipe_ClearIN() macro. Between each USB packet, the given stream callback function is
			 *  executed repeatedly until the next packet is ready, allowing for early aborts of stream transfers.
			 *
			 *  \note The pipe token is set automatically, thus this can be used on bi-directional pipes directly without
			 *        having to explicitly change the data direction with a call to \ref Pipe_SetPipeToken().
			 *
			 *  \param[out] Buffer          Pointer to the source data buffer to write to.
			 *  \param[in]  Length          Number of bytes to read for the currently selected pipe to read from.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes already processed should
			 *                              updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Pipe_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Pipe_Read_Stream_BE(void* const Buffer,
			                            uint16_t Length,
			                            uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);
			//@}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */

