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
 *  \brief USB device standard request management.
 *
 *  This file contains the function prototypes necessary for the processing of incoming standard control requests
 *  when the library is in USB device mode.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __DEVICESTDREQ_H__
#define __DEVICESTDREQ_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"
		#include "StdDescriptors.h"
		#include "Events.h"
		#include "StdRequestType.h"
		#include "USBTask.h"
		#include "USBController.h"

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
			#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) || defined(__DOXYGEN__)
				/** Enum for the possible descriptor memory spaces, for the \c MemoryAddressSpace parameter of the
				 *  \ref CALLBACK_USB_GetDescriptor() function. This can be used when none of the \c USE_*_DESCRIPTORS
				 *  compile time options are used, to indicate in which memory space the descriptor is stored.
				 *
				 *  \ingroup Group_Device
				 */
				enum USB_DescriptorMemorySpaces_t
				{
					#if defined(ARCH_HAS_FLASH_ADDRESS_SPACE) || defined(__DOXYGEN__)
					MEMSPACE_FLASH    = 0, /**< Indicates the requested descriptor is located in FLASH memory. */
					#endif
					#if defined(ARCH_HAS_EEPROM_ADDRESS_SPACE) || defined(__DOXYGEN__)
					MEMSPACE_EEPROM   = 1, /**< Indicates the requested descriptor is located in EEPROM memory. */
					#endif
					MEMSPACE_RAM      = 2, /**< Indicates the requested descriptor is located in RAM memory. */
				};
			#endif

		/* Global Variables: */
			/** Indicates the currently set configuration number of the device. USB devices may have several
			 *  different configurations which the host can select between; this indicates the currently selected
			 *  value, or 0 if no configuration has been selected.
			 *
			 *  \attention This variable should be treated as read-only in the user application, and never manually
			 *             changed in value.
			 *
			 *  \ingroup Group_Device
			 */
			extern uint8_t USB_Device_ConfigurationNumber;

			#if !defined(NO_DEVICE_REMOTE_WAKEUP)
				/** Indicates if the host is currently allowing the device to issue remote wakeup events. If this
				 *  flag is cleared, the device should not issue remote wakeup events to the host.
				 *
				 *  \attention This variable should be treated as read-only in the user application, and never manually
				 *             changed in value.
				 *
				 *  \note To reduce FLASH usage of the compiled applications where Remote Wakeup is not supported,
				 *        this global and the underlying management code can be disabled by defining the
				 *        \c NO_DEVICE_REMOTE_WAKEUP token in the project makefile and passing it to the compiler via
				 *        the -D switch.
				 *
				 *  \ingroup Group_Device
				 */
				extern bool USB_Device_RemoteWakeupEnabled;
			#endif

			#if !defined(NO_DEVICE_SELF_POWER)
				/** Indicates if the device is currently being powered by its own power supply, rather than being
				 *  powered by the host's USB supply. This flag should remain cleared if the device does not
				 *  support self powered mode, as indicated in the device descriptors.
				 *
				 *  \ingroup Group_Device
				 */
				extern bool USB_Device_CurrentlySelfPowered;
			#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		#if defined(USE_RAM_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS)
			#error USE_RAM_DESCRIPTORS and USE_EEPROM_DESCRIPTORS are mutually exclusive.
		#elif defined(USE_RAM_DESCRIPTORS) && defined(USE_FLASH_DESCRIPTORS)
			#error USE_RAM_DESCRIPTORS and USE_FLASH_DESCRIPTORS are mutually exclusive.
		#elif defined(USE_FLASH_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS)
			#error USE_FLASH_DESCRIPTORS and USE_EEPROM_DESCRIPTORS are mutually exclusive.
		#elif defined(USE_FLASH_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS) && defined(USE_RAM_DESCRIPTORS)
			#error Only one of the USE_*_DESCRIPTORS modes should be selected.
		#endif

		/* Function Prototypes: */
			void USB_Device_ProcessControlRequest(void);

			#if defined(__INCLUDE_FROM_DEVICESTDREQ_C)
				static void USB_Device_SetAddress(void);
				static void USB_Device_SetConfiguration(void);
				static void USB_Device_GetConfiguration(void);
				static void USB_Device_GetDescriptor(void);
				static void USB_Device_GetStatus(void);
				static void USB_Device_ClearSetFeature(void);

				#if !defined(NO_INTERNAL_SERIAL) && (USE_INTERNAL_SERIAL != NO_DESCRIPTOR)
					static void USB_Device_GetInternalSerialDescriptor(void);
				#endif
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

