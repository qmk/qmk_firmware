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
 *  \brief Common USB Device definitions for all architectures.
 *  \copydetails Group_Device
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USB
 *  \defgroup Group_Device Device Management
 *  \brief USB Device management definitions for USB device mode.
 *
 *  USB Device mode related definitions common to all architectures. This module contains definitions which
 *  are used when the USB controller is initialized in device mode.
 *
 *  @{
 */

#ifndef __USBDEVICE_H__
#define __USBDEVICE_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"
		#include "StdDescriptors.h"
		#include "USBInterrupt.h"
		#include "Endpoint.h"

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
			/** Enum for the various states of the USB Device state machine. Only some states are
			 *  implemented in the LUFA library - other states are left to the user to implement.
			 *
			 *  For information on each possible USB device state, refer to the USB 2.0 specification.
			 *
			 *  \see \ref USB_DeviceState, which stores the current device state machine state.
			 */
			enum USB_Device_States_t
			{
				DEVICE_STATE_Unattached                   = 0, /**< Internally implemented by the library. This state indicates
				                                                *   that the device is not currently connected to a host.
				                                                */
				DEVICE_STATE_Powered                      = 1, /**< Internally implemented by the library. This state indicates
				                                                *   that the device is connected to a host, but enumeration has not
				                                                *   yet begun.
				                                                */
				DEVICE_STATE_Default                      = 2, /**< Internally implemented by the library. This state indicates
				                                                *   that the device's USB bus has been reset by the host and it is
				                                                *   now waiting for the host to begin the enumeration process.
				                                                */
				DEVICE_STATE_Addressed                    = 3, /**< Internally implemented by the library. This state indicates
				                                                *   that the device has been addressed by the USB Host, but is not
				                                                *   yet configured.
				                                                */
				DEVICE_STATE_Configured                   = 4, /**< May be implemented by the user project. This state indicates
				                                                *   that the device has been enumerated by the host and is ready
				                                                *   for USB communications to begin.
				                                                */
				DEVICE_STATE_Suspended                    = 5, /**< May be implemented by the user project. This state indicates
				                                                *   that the USB bus has been suspended by the host, and the device
				                                                *   should power down to a minimal power level until the bus is
				                                                *   resumed.
				                                                */
			};

		/* Function Prototypes: */
			/** Function to retrieve a given descriptor's size and memory location from the given descriptor type value,
			 *  index and language ID. This function MUST be overridden in the user application (added with full, identical
			 *  prototype and name so that the library can call it to retrieve descriptor data.
			 *
			 *  \param[in] wValue                  The type of the descriptor to retrieve in the upper byte, and the index in the
			 *                                     lower byte (when more than one descriptor of the given type exists, such as the
			 *                                     case of string descriptors). The type may be one of the standard types defined
			 *                                     in the DescriptorTypes_t enum, or may be a class-specific descriptor type value.
			 *  \param[in] wIndex                  The language ID of the string to return if the \c wValue type indicates
			 *                                     \ref DTYPE_String, otherwise zero for standard descriptors, or as defined in a
			 *                                     class-specific standards.
			 *  \param[out] DescriptorAddress      Pointer to the descriptor in memory. This should be set by the routine to
			 *                                     the address of the descriptor.
			 *  \param[out] DescriptorMemorySpace  A value from the \ref USB_DescriptorMemorySpaces_t enum to indicate the memory
			 *                                     space in which the descriptor is stored. This parameter does not exist when one
			 *                                     of the \c USE_*_DESCRIPTORS compile time options is used, or on architectures which
			 *                                     use a unified address space.
			 *
			 *  \note By default, the library expects all descriptors to be located in flash memory via the \c PROGMEM attribute.
			 *        If descriptors should be located in RAM or EEPROM instead (to speed up access in the case of RAM, or to
			 *        allow the descriptors to be changed dynamically at runtime) either the \c USE_RAM_DESCRIPTORS or the
			 *        \c USE_EEPROM_DESCRIPTORS tokens may be defined in the project makefile and passed to the compiler by the -D
			 *        switch.
			 *
			 *  \return Size in bytes of the descriptor if it exists, zero or \ref NO_DESCRIPTOR otherwise.
			 */
			uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
			                                    const uint16_t wIndex,
			                                    const void** const DescriptorAddress
			#if (defined(ARCH_HAS_MULTI_ADDRESS_SPACE) || defined(__DOXYGEN__)) && \
			    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
			                                    , uint8_t* const DescriptorMemorySpace
			#endif
			                                    ) ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

	/* Architecture Includes: */
		#if (ARCH == ARCH_AVR8)
			#include "AVR8/Device_AVR8.h"
		#elif (ARCH == ARCH_UC3)
			#include "UC3/Device_UC3.h"
		#elif (ARCH == ARCH_XMEGA)
			#include "XMEGA/Device_XMEGA.h"
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

