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
 *  \brief Pipe data stream transmission and reception management.
 *  \copydetails Group_PipeStreamRW
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_PipeRW
 *  \defgroup Group_PipeStreamRW Read/Write of Multi-Byte Streams
 *  \brief Pipe data stream transmission and reception management.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of data streams from
 *  and to pipes.
 *
 *  @{
 */

#ifndef __PIPE_STREAM_H__
#define __PIPE_STREAM_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
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
				PIPE_RWSTREAM_IncompleteTransfer = 4, /**< Indicates that the pipe bank became full/empty before the
				                                       *   complete contents of the stream could be transferred.
				                                       */
			};

	/* Architecture Includes: */
		#if (ARCH == ARCH_AVR8)
			#include "AVR8/PipeStream_AVR8.h"
		#elif (ARCH == ARCH_UC3)
			#include "UC3/PipeStream_UC3.h"
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

