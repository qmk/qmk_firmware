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
 *  \brief USB device mode definitions.
 *
 *  This file contains structures, function prototypes and macros related to USB device mode.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USB
 *  @defgroup Group_Device Device Management
 *
 *  USB Device mode related macros and enums. This module contains macros and enums which are used when
 *  the USB controller is initialized in device mode.
 *
 *  @{
 */

#ifndef __USBDEVICE_H__
#define __USBDEVICE_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/pgmspace.h>
		#include <avr/eeprom.h>

		#include "../../../Common/Common.h"	
		#include "../HighLevel/StdDescriptors.h"
		#include "USBInterrupt.h"
		#include "Endpoint.h"

	/* Preprocessor Checks: */
		#if (defined(USE_RAM_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS))
			#error USE_RAM_DESCRIPTORS and USE_EEPROM_DESCRIPTORS are mutually exclusive.
		#endif

		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif
			
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR) || defined(__DOXYGEN__)
				/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
				 *  USB interface should be initialized in low speed (1.5Mb/s) mode.
				 *
				 *  \note Low Speed mode is not available on all USB AVR models.
				 *        \n\n
				 *
				 *  \note Restrictions apply on the number, size and type of endpoints which can be used
				 *        when running in low speed mode -- refer to the USB 2.0 standard.
				 */
				#define USB_DEVICE_OPT_LOWSPEED            (1 << 0)
			#endif
			
			/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
			 *  USB interface should be initialized in full speed (12Mb/s) mode.
			 */
			#define USB_DEVICE_OPT_FULLSPEED               (0 << 0)

		/* Function Prototypes: */
			/** Sends a Remote Wakeup request to the host. This signals to the host that the device should
			 *  be taken out of suspended mode, and communications should resume.
			 *
			 *  Typically, this is implemented so that HID devices (mice, keyboards, etc.) can wake up the
			 *  host computer when the host has suspended all USB devices to enter a low power state.
			 *
			 *  \note This macro should only be used if the device has indicated to the host that it
			 *        supports the Remote Wakeup feature in the device descriptors, and should only be
			 *        issued if the host is currently allowing remote wakeup events from the device (i.e.,
			 *        the \ref USB_RemoteWakeupEnabled flag is set). When the NO_DEVICE_REMOTE_WAKEUP compile
			 *        time option is used, this macro is unavailable.
			 *        \n
			 *
			 *  \note The USB clock must be running for this function to operate. If the stack is initialized with
			 *        the \ref USB_OPT_MANUAL_PLL option enabled, the user must ensure that the PLL is running
			 *        before attempting to call this function.
			 *
			 *  \see \ref Group_Descriptors for more information on the RMWAKEUP feature and device descriptors.
			 */
			void USB_Device_SendRemoteWakeup(void);
			
		/* Type Defines: */
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
			
		/* Inline Functions: */
			/** Enables the device mode Start Of Frame events. When enabled, this causes the
			 *  \ref EVENT_USB_Device_StartOfFrame() event to fire once per millisecond, synchronized to the USB bus,
			 *  at the start of each USB frame when enumerated in device mode.
			 */
			static inline void USB_Device_EnableSOFEvents(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_EnableSOFEvents(void)
			{
				USB_INT_Enable(USB_INT_SOFI);
			}
				
			/** Disables the device mode Start Of Frame events. When disabled, this stop the firing of the
			 *  \ref EVENT_USB_Device_StartOfFrame() event when enumerated in device mode.
			 */
			static inline void USB_Device_DisableSOFEvents(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_DisableSOFEvents(void)
			{
				USB_INT_Disable(USB_INT_SOFI);
			}
			
		/* Function Prototypes: */
			/** Function to retrieve a given descriptor's size and memory location from the given descriptor type value,
			 *  index and language ID. This function MUST be overridden in the user application (added with full, identical  
			 *  prototype and name so that the library can call it to retrieve descriptor data.
			 *
			 *  \param[in] wValue               The type of the descriptor to retrieve in the upper byte, and the index in the 
			 *                                  lower byte (when more than one descriptor of the given type exists, such as the
			 *                                  case of string descriptors). The type may be one of the standard types defined
			 *                                  in the DescriptorTypes_t enum, or may be a class-specific descriptor type value.
			 *  \param[in] wIndex               The language ID of the string to return if the wValue type indicates DTYPE_String,
			 *                                  otherwise zero for standard descriptors, or as defined in a class-specific
			 *                                  standards.
			 *  \param[out] DescriptorAddress   Pointer to the descriptor in memory. This should be set by the routine to
			 *                                  the address of the descriptor.
			 *  \param[out] MemoryAddressSpace  A value from the \ref USB_DescriptorMemorySpaces_t enum to indicate the memory
			 *                                  space in which the descriptor is stored. This parameter does not exist when one
			 *                                  of the USE_*_DESCRIPTORS compile time options is used.
			 *
			 *  \note By default, the library expects all descriptors to be located in flash memory via the PROGMEM attribute.
			 *        If descriptors should be located in RAM or EEPROM instead (to speed up access in the case of RAM, or to
			 *        allow the descriptors to be changed dynamically at runtime) either the USE_RAM_DESCRIPTORS or the 
			 *        USE_EEPROM_DESCRIPTORS tokens may be defined in the project makefile and passed to the compiler by the -D
			 *        switch.
			 *
			 *  \return Size in bytes of the descriptor if it exists, zero or \ref NO_DESCRIPTOR otherwise.
			 */
			uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
			                                    const uint8_t wIndex,
			                                    void** const DescriptorAddress
			#if !defined(USE_FLASH_DESCRIPTORS) && !defined(USE_EEPROM_DESCRIPTORS) && !defined(USE_RAM_DESCRIPTORS)
			                                    , uint8_t* MemoryAddressSpace
			#endif
			                                    ) ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Inline Functions: */
			#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
			static inline void USB_Device_SetLowSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetLowSpeed(void)
			{
				UDCON |=  (1 << LSM);
			}
			
			static inline void USB_Device_SetFullSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetFullSpeed(void)
			{
				UDCON &= ~(1 << LSM);
			}
			#endif
			
			static inline void USB_Device_SetDeviceAddress(const uint8_t Address) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetDeviceAddress(const uint8_t Address)
			{
				UDADDR = ((1 << ADDEN) | (Address & 0x7F));
			}			
	#endif

#endif

/** @} */
