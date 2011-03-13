/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common USB Pipe definitions for all architectures.
 *  \copydetails Group_PipeManagement
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_PipeManagement
 *  \defgroup Group_PipeRW Pipe Data Reading and Writing
 *  \brief Pipe data read/write definitions.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing from and to pipes.
 */

/** \ingroup Group_PipeRW
 *  \defgroup Group_PipePrimitiveRW Read/Write of Primitive Data Types
 *  \brief Pipe data primative read/write definitions.
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of primitive data types
 *  from and to pipes.
 */

/** \ingroup Group_PipeManagement
 *  \defgroup Group_PipePacketManagement Pipe Packet Management
 *  \brief Pipe packet management definitions.
 *
 *  Functions, macros, variables, enums and types related to packet management of pipes.
 */

/** \ingroup Group_PipeManagement
 *  \defgroup Group_PipeControlReq Pipe Control Request Management
 *  \brief Pipe control request definitions.
 *
 *  Module for host mode request processing. This module allows for the transmission of standard, class and
 *  vendor control requests to the default control endpoint of an attached device while in host mode.
 *
 *  \see Chapter 9 of the USB 2.0 specification.
 */

/** \ingroup Group_USB
 *  \defgroup Group_PipeManagement Pipe Management
 *  \brief Pipe management definitions.
 *
 *  This module contains functions, macros and enums related to pipe management when in USB Host mode. This
 *  module contains the pipe management macros, as well as pipe interrupt and data send/receive functions
 *  for various data types.
 *
 *  @{
 */

#ifndef __PIPE_H__
#define __PIPE_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"		

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Pipe address for the default control pipe, which always resides in address 0. This is
			 *  defined for convenience to give more readable code when used with the pipe macros.
			 */
			#define PIPE_CONTROLPIPE                0

			/** Pipe number mask, for masking against pipe addresses to retrieve the pipe's numerical address
			 *  in the device.
			 */
			#define PIPE_PIPENUM_MASK               0x07

			/** Endpoint number mask, for masking against endpoint addresses to retrieve the endpoint's
			 *  numerical address in the attached device.
			 */
			#define PIPE_EPNUM_MASK                 0x0F

			/** Endpoint direction mask, for masking against endpoint addresses to retrieve the endpoint's
			 *  direction for comparing with the \c ENDPOINT_DESCRIPTOR_DIR_* masks.
			 */
			#define PIPE_EPDIR_MASK                 0x80

	/* Architecture Includes: */
		#if (ARCH == ARCH_AVR8)
			#include "AVR8/Pipe_AVR8.h"
		#elif (ARCH == ARCH_UC3)
			#include "UC3/Pipe_UC3.h"
		#endif

#endif

/** @} */

