/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief Common USB Host definitions for all architectures.
 *  \copydetails Group_Host
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USB
 *  \defgroup Group_Host Host Management
 *  \brief USB Host management definitions for USB host mode.
 *
 *  USB Host mode related macros and enums. This module contains macros and enums which are used when
 *  the USB controller is initialized in host mode.
 *
 *  @{
 */

#ifndef __USBHOST_H__
#define __USBHOST_H__

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
			/** Enum for the various states of the USB Host state machine.
			 *
			 *  For information on each possible USB host state, refer to the USB 2.0 specification.
			 *  Several of the USB host states are broken up further into multiple smaller sub-states,
			 *  so that they can be internally implemented inside the library in an efficient manner.
			 *
			 *  \see \ref USB_HostState, which stores the current host state machine state.
			 */
			enum USB_Host_States_t
			{
				HOST_STATE_WaitForDevice                = 0,  /**< This state indicates that the stack is waiting for an interval
				                                               *   to elapse before continuing with the next step of the device
				                                               *   enumeration process.
				                                               */
				HOST_STATE_Unattached                   = 1,  /**< This state indicates that the host state machine is waiting for
				                                               *   a device to be attached so that it can start the enumeration process.
				                                               */
				HOST_STATE_Powered                      = 2,  /**< This state indicates that a device has been attached, and the
				                                               *   library's internals are being configured to begin the enumeration
				                                               *   process.
				                                               */
				HOST_STATE_Powered_WaitForDeviceSettle  = 3,  /**< This state indicates that the stack is waiting for the initial
				                                               *   settling period to elapse before beginning the enumeration process.
				                                               */
				HOST_STATE_Powered_WaitForConnect       = 4,  /**< This state indicates that the stack is waiting for a connection event
				                                               *   from the USB controller to indicate a valid USB device has been attached
				                                               *   to the bus and is ready to be enumerated.
				                                               */
				HOST_STATE_Powered_DoReset              = 5,  /**< This state indicates that a valid USB device has been attached, and that
				                                               *   it will now be reset to ensure it is ready for enumeration.
				                                               */
				HOST_STATE_Powered_ConfigPipe           = 6,  /**< This state indicates that the attached device is currently powered and
				                                               *   reset, and that the control pipe is now being configured by the stack.
				                                               */
				HOST_STATE_Default                      = 7,  /**< This state indicates that the stack is currently retrieving the control
				                                               *   endpoint's size from the device, so that the control pipe can be altered
				                                               *   to match.
				                                               */
				HOST_STATE_Default_PostReset            = 8,  /**< This state indicates that the control pipe is being reconfigured to match
				                                               *   the retrieved control endpoint size from the device, and the device's USB
				                                               *   bus address is being set.
				                                               */
				HOST_STATE_Default_PostAddressSet       = 9,  /**< This state indicates that the device's address has now been set, and the
				                                               *   stack is has now completed the device enumeration process. This state causes
				                                               *   the stack to change the current USB device address to that set for the
				                                               *   connected device, before progressing to the \ref HOST_STATE_Addressed state
				                                               *   ready for use in the user application.
				                                               */
				HOST_STATE_Addressed                    = 10, /**< Indicates that the device has been enumerated and addressed, and is now waiting
				                                               *   for the user application to configure the device ready for use.
				                                               */
				HOST_STATE_Configured                   = 11, /**< Indicates that the device has been configured into a valid device configuration,
				                                               *   ready for general use by the user application.
				                                               */
			};

	/* Architecture Includes: */
		#if (ARCH == ARCH_AVR8)
			#include "AVR8/Host_AVR8.h"
		#elif (ARCH == ARCH_UC3)
			#include "UC3/Host_UC3.h"
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

