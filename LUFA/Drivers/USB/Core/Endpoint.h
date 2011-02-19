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
 *  \brief USB device endpoint management definitions.
 *
 *  This file contains structures, function prototypes and macros related to the management of the device's
 *  data endpoints when the library is initialized in USB device mode.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_EndpointManagement
 *  \defgroup Group_EndpointRW Endpoint Data Reading and Writing
 *
 *  Functions, macros, variables, enums and types related to data reading and writing from and to endpoints.
 */

/** \ingroup Group_EndpointRW
 *  \defgroup Group_EndpointPrimitiveRW Read/Write of Primitive Data Types
 *
 *  Functions, macros, variables, enums and types related to data reading and writing of primitive data types
 *  from and to endpoints.
 */

/** \ingroup Group_EndpointManagement
 *  \defgroup Group_EndpointPacketManagement Endpoint Packet Management
 *
 *  Functions, macros, variables, enums and types related to packet management of endpoints.
 */

/** \ingroup Group_USB
 *  \defgroup Group_EndpointManagement Endpoint Management
 *
 *  Functions, macros and enums related to endpoint management when in USB Device mode. This
 *  module contains the endpoint management macros, as well as endpoint interrupt and data
 *  send/receive functions for various data types.
 *
 *  @{
 */

#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

	/* Includes: */
		#include "../../../Common/Common.h"

		#if (ARCH == ARCH_AVR8)
			#include "AVR8/Endpoint.h"
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

#endif

/** @} */

