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
 *  \brief Endpoint data stream transmission and reception management for the AVR8 microcontrollers.
 *  \copydetails Group_EndpointStreamRW_AVR8
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_EndpointStreamRW
 *  \defgroup Group_EndpointStreamRW_AVR8 Read/Write of Multi-Byte Streams (AVR8)
 *  \brief Endpoint data stream transmission and reception management for the Atmel AVR8 architecture.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of data streams from
 *  and to endpoints.
 *
 *  @{
 */ 

#ifndef __ENDPOINT_STREAM_AVR8_H__
#define __ENDPOINT_STREAM_AVR8_H__

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

			/** Reads and discards the given number of bytes from the currently selected endpoint's bank,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the endpoint bank becomes empty while there is still data to process (and after the current
			 *  packet has been acknowledged) the BytesProcessed location will be updated with the total number
			 *  of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref ENDPOINT_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Endpoint_Discard_Stream(512, NULL)) != ENDPOINT_RWSTREAM_NoError)
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
			 *  while ((ErrorCode = Endpoint_Discard_Stream(512, &BytesProcessed)) == ENDPOINT_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != ENDPOINT_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Length          Number of bytes to discard via the currently selected endpoint.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Discard_Stream(uint16_t Length,
			                                uint16_t* const BytesProcessed);

			/** Writes a given number of zeroed bytes to the currently selected endpoint's bank, sending
			 *  full packets to the host as needed. The last packet is not automatically sent once the 
			 *  remaining bytes have been written; the user is responsible for manually sending the last
			 *  packet to the host via the \ref Endpoint_ClearIN() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the endpoint bank becomes full while there is still data to process (and after the current
			 *  packet transmission has been initiated) the BytesProcessed location will be updated with the
			 *  total number of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref ENDPOINT_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Endpoint_Null_Stream(512, NULL)) != ENDPOINT_RWSTREAM_NoError)
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
			 *  while ((ErrorCode = Endpoint_Null_Stream(512, &BytesProcessed)) == ENDPOINT_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != ENDPOINT_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Length          Number of zero bytes to send via the currently selected endpoint.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Null_Stream(uint16_t Length,
			                             uint16_t* const BytesProcessed);

			//@}

			/** \name Stream functions for RAM source/destination data */
			//@{
		
			/** Writes the given number of bytes to the endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Endpoint_ClearIN() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the endpoint bank becomes full while there is still data to process (and after the current
			 *  packet transmission has been initiated) the BytesProcessed location will be updated with the
			 *  total number of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref ENDPOINT_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t DataStream[512];
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Endpoint_Write_Stream_LE(DataStream, sizeof(DataStream),
			 *                                            NULL)) != ENDPOINT_RWSTREAM_NoError)
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
			 *  while ((ErrorCode = Endpoint_Write_Stream_LE(DataStream, sizeof(DataStream),
			 *                                               &BytesProcessed)) == ENDPOINT_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *
			 *  if (ErrorCode != ENDPOINT_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_LE(const void* const Buffer,
			                                 uint16_t Length,
			                                 uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The last packet filled is not automatically sent;
			 *  the user is responsible for manually sending the last written packet to the host via the
			 *  \ref Endpoint_ClearIN() macro.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Stream_BE(const void* const Buffer,
			                                 uint16_t Length,
			                                 uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);
			
			/** Reads the given number of bytes from the endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro.
			 *
			 *  If the BytesProcessed parameter is \c NULL, the entire stream transfer is attempted at once,
			 *  failing or succeeding as a single unit. If the BytesProcessed parameter points to a valid
			 *  storage location, the transfer will instead be performed as a series of chunks. Each time
			 *  the endpoint bank becomes empty while there is still data to process (and after the current
			 *  packet has been acknowledged) the BytesProcessed location will be updated with the total number
			 *  of bytes processed in the stream, and the function will exit with an error code of
			 *  \ref ENDPOINT_RWSTREAM_IncompleteTransfer. This allows for any abort checking to be performed
			 *  in the user code - to continue the transfer, call the function again with identical parameters
			 *  and it will resume until the BytesProcessed value reaches the total transfer length.
			 *
			 *  <b>Single Stream Transfer Example:</b>
			 *  \code
			 *  uint8_t DataStream[512];
			 *  uint8_t ErrorCode;
			 *  
			 *  if ((ErrorCode = Endpoint_Read_Stream_LE(DataStream, sizeof(DataStream),
			 *                                           NULL)) != ENDPOINT_RWSTREAM_NoError)
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
			 *  while ((ErrorCode = Endpoint_Read_Stream_LE(DataStream, sizeof(DataStream),
			 *                                              &BytesProcessed)) == ENDPOINT_RWSTREAM_IncompleteTransfer)
			 *  {
			 *      // Stream not yet complete - do other actions here, abort if required
			 *  }
			 *  
			 *  if (ErrorCode != ENDPOINT_RWSTREAM_NoError)
			 *  {
			 *      // Stream failed to complete - check ErrorCode here
			 *  }
			 *  \endcode
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[out] Buffer          Pointer to the destination data buffer to write to.
			 *  \param[in]  Length          Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                              transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_LE(void* const Buffer,
			                                uint16_t Length,
			                                uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The last packet is not automatically
			 *  discarded once the remaining bytes has been read; the user is responsible for manually
			 *  discarding the last packet from the host via the \ref Endpoint_ClearOUT() macro.
			 *
			 *  \note This routine should not be used on CONTROL type endpoints.
			 *
			 *  \param[out] Buffer          Pointer to the destination data buffer to write to.
			 *  \param[in]  Length          Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                              transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Stream_BE(void* const Buffer,
			                                uint16_t Length,
			                                uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in little endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the status OUT packet
			 *  to finalize the transfer's status stage via the \ref Endpoint_ClearOUT() macro.
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
			uint8_t Endpoint_Write_Control_Stream_LE(const void* const Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Writes the given number of bytes to the CONTROL type endpoint from the given buffer in big endian,
			 *  sending full packets to the host as needed. The host OUT acknowledgement is not automatically cleared
			 *  in both failure and success states; the user is responsible for manually clearing the status OUT packet
			 *  to finalize the transfer's status stage via the \ref Endpoint_ClearOUT() macro.
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
			uint8_t Endpoint_Write_Control_Stream_BE(const void* const Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in little endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  status IN packet to finalize the transfer's status stage via the \ref Endpoint_ClearIN() macro.
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
			uint8_t Endpoint_Read_Control_Stream_LE(void* const Buffer,
			                                        uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** Reads the given number of bytes from the CONTROL endpoint from the given buffer in big endian,
			 *  discarding fully read packets from the host as needed. The device IN acknowledgement is not
			 *  automatically sent after success or failure states; the user is responsible for manually sending the
			 *  status IN packet to finalize the transfer's status stage via the \ref Endpoint_ClearIN() macro.
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
			uint8_t Endpoint_Read_Control_Stream_BE(void* const Buffer,
			                                        uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);
			//@}

			/** \name Stream functions for EEPROM source/destination data */
			//@{

			/** EEPROM buffer source version of \ref Endpoint_Write_Stream_LE().
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_EStream_LE(const void* const Buffer,
			                                  uint16_t Length,
			                                  uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Write_Stream_BE().
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_EStream_BE(const void* const Buffer,
			                                  uint16_t Length,
			                                  uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer destination version of \ref Endpoint_Read_Stream_LE().
			 *
			 *  \param[out] Buffer          Pointer to the destination data buffer to write to, located in EEPROM memory space.
			 *  \param[in]  Length          Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                              transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_EStream_LE(void* const Buffer,
			                                 uint16_t Length,
			                                 uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer destination version of \ref Endpoint_Read_Stream_BE().
			 *
			 *  \param[out] Buffer          Pointer to the destination data buffer to write to, located in EEPROM memory space.
			 *  \param[in]  Length          Number of bytes to send via the currently selected endpoint.
			 *  \param[in]  BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                              transaction should be updated, \c NULL if the entire stream should be read at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_EStream_BE(void* const Buffer,
			                                 uint16_t Length,
			                                 uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of Endpoint_Write_Control_Stream_LE.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_EStream_LE(const void* const Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Write_Control_Stream_BE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_EStream_BE(const void* const Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Read_Control_Stream_LE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_EStream_LE(void* const Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);

			/** EEPROM buffer source version of \ref Endpoint_Read_Control_Stream_BE().
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[out] Buffer  Pointer to the destination data buffer to write to.
			 *  \param[in]  Length  Number of bytes to send via the currently selected endpoint.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Read_Control_EStream_BE(void* const Buffer,
			                                         uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);
			//@}

			/** \name Stream functions for PROGMEM source/destination data */
			//@{

			/** FLASH buffer source version of \ref Endpoint_Write_Stream_LE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_PStream_LE(const void* const Buffer,
			                                  uint16_t Length,
			                                  uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Stream_BE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \param[in] Buffer          Pointer to the source data buffer to read from.
			 *  \param[in] Length          Number of bytes to read for the currently selected endpoint into the buffer.
			 *  \param[in] BytesProcessed  Pointer to a location where the total number of bytes processed in the current
			 *                             transaction should be updated, \c NULL if the entire stream should be written at once.
			 *
			 *  \return A value from the \ref Endpoint_Stream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_PStream_BE(const void* const Buffer,
			                                  uint16_t Length,
			                                  uint16_t* const BytesProcessed) ATTR_NON_NULL_PTR_ARG(1);

			/** FLASH buffer source version of \ref Endpoint_Write_Control_Stream_LE().
			 *
			 *  \pre The FLASH data must be located in the first 64KB of FLASH for this function to work correctly.
			 *
			 *  \note This function automatically clears the control transfer's status stage. Do not manually attempt
			 *        to clear the status stage when using this routine in a control transaction.
			 *        \n\n
			 *
			 *  \note This routine should only be used on CONTROL type endpoints.
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_PStream_LE(const void* const Buffer,
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
			 *        \n\n
			 *
			 *  \warning Unlike the standard stream read/write commands, the control stream commands cannot be chained
			 *           together; i.e. the entire stream data must be read or written at the one time.
			 *
			 *  \param[in] Buffer  Pointer to the source data buffer to read from.
			 *  \param[in] Length  Number of bytes to read for the currently selected endpoint into the buffer.
			 *
			 *  \return A value from the \ref Endpoint_ControlStream_RW_ErrorCodes_t enum.
			 */
			uint8_t Endpoint_Write_Control_PStream_BE(const void* const Buffer,
			                                          uint16_t Length) ATTR_NON_NULL_PTR_ARG(1);
			//@}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */

