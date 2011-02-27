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
 *  \brief USB Device definitions for the AVR32 UC3B microcontrollers.
 *  \copydetails Group_Device_UC3B
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_Device
 *  \defgroup Group_Device_UC3B Device Management (UC3B)
 *  \brief USB Device definitions for the AVR32 UC3B microcontrollers.
 *
 *  Architecture specific USB Device definitions for the Atmel 32-bit UC3B AVR microcontrollers.
 *
 *  @{
 */

#ifndef __USBDEVICE_UC3B_H__
#define __USBDEVICE_UC3B_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../StdDescriptors.h"
		#include "../USBInterrupt.h"
		#include "../Endpoint.h"
		
	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name USB Device Mode Option Masks */
			//@{
			#if defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR) || defined(__DOXYGEN__)
				/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
				 *  USB interface should be initialized in low speed (1.5Mb/s) mode.
				 *
				 *  \note Low Speed mode is not available on all USB AVR models.
				 *        \n
				 *
				 *  \note Restrictions apply on the number, size and type of endpoints which can be used
				 *        when running in low speed mode - refer to the USB 2.0 specification.
				 */
				#define USB_DEVICE_OPT_LOWSPEED            (1 << 0)
			#endif

			/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
			 *  USB interface should be initialized in full speed (12Mb/s) mode.
			 */
			#define USB_DEVICE_OPT_FULLSPEED               (0 << 0)
			//@}
			
			/** String descriptor index for the device's unique serial number string descriptor within the device.
			 *  This unique serial number is used by the host to associate resources to the device (such as drivers or COM port
			 *  number allocations) to a device regardless of the port it is plugged in to on the host. Some USB AVRs contain
			 *  a unique serial number internally, and setting the device descriptors serial number string index to this value
			 *  will cause it to use the internal serial number.
			 *
			 *  On unsupported devices, this will evaluate to \ref NO_DESCRIPTOR and so will force the host to create a pseudo-serial
			 *  number for the device.
			 */
			#define USE_INTERNAL_SERIAL                    NO_DESCRIPTOR
			
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
			 *        the \ref USB_RemoteWakeupEnabled flag is set). When the \c NO_DEVICE_REMOTE_WAKEUP compile
			 *        time option is used, this macro is unavailable.
			 *        \n\n
			 *
			 *  \note The USB clock must be running for this function to operate. If the stack is initialized with
			 *        the \ref USB_OPT_MANUAL_PLL option enabled, the user must ensure that the PLL is running
			 *        before attempting to call this function.
			 *
			 *  \see \ref Group_StdDescriptors for more information on the RMWAKEUP feature and device descriptors.
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
			/** Returns the current USB frame number, when in device mode. Every millisecond the USB bus is active (i.e. enumerated to a host)
			 *  the frame number is incremented by one.
			 */
			static inline uint16_t USB_Device_GetFrameNumber(void)
			{
				return AVR32_USBB.UDFNUM.fnum;
			}

			#if !defined(NO_SOF_EVENTS)
				/** Enables the device mode Start Of Frame events. When enabled, this causes the
				 *  \ref EVENT_USB_Device_StartOfFrame() event to fire once per millisecond, synchronized to the USB bus,
				 *  at the start of each USB frame when enumerated in device mode.
				 *
				 *  \note Not available when the \c NO_SOF_EVENTS compile time token is defined.
				 */
				static inline void USB_Device_EnableSOFEvents(void) ATTR_ALWAYS_INLINE;
				static inline void USB_Device_EnableSOFEvents(void)
				{
					USB_INT_Enable(USB_INT_SOFI);
				}

				/** Disables the device mode Start Of Frame events. When disabled, this stops the firing of the
				 *  \ref EVENT_USB_Device_StartOfFrame() event when enumerated in device mode.
				 *
				 *  \note Not available when the \c NO_SOF_EVENTS compile time token is defined.
				 */
				static inline void USB_Device_DisableSOFEvents(void) ATTR_ALWAYS_INLINE;
				static inline void USB_Device_DisableSOFEvents(void)
				{
					USB_INT_Disable(USB_INT_SOFI);
				}
			#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Inline Functions: */
			#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
			static inline void USB_Device_SetLowSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetLowSpeed(void)
			{
				AVR32_USBB.UDCON.ls = true;
			}

			static inline void USB_Device_SetFullSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetFullSpeed(void)
			{
				AVR32_USBB.UDCON.ls = false;
			}
			#endif

			static inline void USB_Device_SetDeviceAddress(const uint8_t Address) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetDeviceAddress(const uint8_t Address)
			{
				AVR32_USBB.UDCON.uadd  = Address;
				AVR32_USBB.UDCON.adden = true;
			}

			static inline bool USB_Device_IsAddressSet(void) ATTR_ALWAYS_INLINE;
			static inline bool USB_Device_IsAddressSet(void)
			{
				return AVR32_USBB.UDCON.adden;
			}
	#endif

#endif

/** @} */

