/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief USB Device definitions for the AVR32 UC3 microcontrollers.
 *  \copydetails Group_Device_UC3
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_Device
 *  \defgroup Group_Device_UC3 Device Management (UC3)
 *  \brief USB Device definitions for the AVR32 UC3 microcontrollers.
 *
 *  Architecture specific USB Device definitions for the Atmel 32-bit UC3 AVR microcontrollers.
 *
 *  @{
 */

#ifndef __USBDEVICE_UC3_H__
#define __USBDEVICE_UC3_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../USBController.h"
		#include "../StdDescriptors.h"
		#include "../USBInterrupt.h"
		#include "../Endpoint.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name USB Device Mode Option Masks */
			//@{
			/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
			 *  USB interface should be initialized in low speed (1.5Mb/s) mode.
			 *
			 *  \note Restrictions apply on the number, size and type of endpoints which can be used
			 *        when running in low speed mode - please refer to the USB 2.0 specification.
			 */
			#define USB_DEVICE_OPT_LOWSPEED                (1 << 0)

			/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
			 *  USB interface should be initialized in full speed (12Mb/s) mode.
			 */
			#define USB_DEVICE_OPT_FULLSPEED               (0 << 0)

			#if defined(USB_SERIES_UC3A3_AVR32) || defined(USB_SERIES_UC3A4_AVR32) || defined(__DOXYGEN__)
				/** Mask for the Options parameter of the \ref USB_Init() function. This indicates that the
				 *  USB interface should be initialized in high speed (480Mb/s) mode.
				 */
				#define USB_DEVICE_OPT_HIGHSPEED           (1 << 1)
			#endif
			//@}

			#if (!defined(NO_INTERNAL_SERIAL) && \
			     (defined(USB_SERIES_UC3A3_AVR32) || defined(USB_SERIES_UC3A4_AVR32) || \
				  defined(__DOXYGEN__)))
				/** String descriptor index for the device's unique serial number string descriptor within the device.
				 *  This unique serial number is used by the host to associate resources to the device (such as drivers or COM port
				 *  number allocations) to a device regardless of the port it is plugged in to on the host. Some microcontrollers contain
				 *  a unique serial number internally, and setting the device descriptors serial number string index to this value
				 *  will cause it to use the internal serial number.
				 *
				 *  On unsupported devices, this will evaluate to \ref NO_DESCRIPTOR and so will force the host to create a pseudo-serial
				 *  number for the device.
				 */
				#define USE_INTERNAL_SERIAL             0xDC

				/** Length of the device's unique internal serial number, in bits, if present on the selected microcontroller
				 *  model.
				 */
				#define INTERNAL_SERIAL_LENGTH_BITS     120

				/** Start address of the internal serial number, in the appropriate address space, if present on the selected microcontroller
				 *  model.
				 */
				#define INTERNAL_SERIAL_START_ADDRESS   0x80800204
			#else
				#define USE_INTERNAL_SERIAL             NO_DESCRIPTOR

				#define INTERNAL_SERIAL_LENGTH_BITS     0
				#define INTERNAL_SERIAL_START_ADDRESS   0
			#endif

		/* Function Prototypes: */
			/** Sends a Remote Wakeup request to the host. This signals to the host that the device should
			 *  be taken out of suspended mode, and communications should resume.
			 *
			 *  Typically, this is implemented so that HID devices (mice, keyboards, etc.) can wake up the
			 *  host computer when the host has suspended all USB devices to enter a low power state.
			 *
			 *  \note This function should only be used if the device has indicated to the host that it
			 *        supports the Remote Wakeup feature in the device descriptors, and should only be
			 *        issued if the host is currently allowing remote wakeup events from the device (i.e.,
			 *        the \ref USB_Device_RemoteWakeupEnabled flag is set). When the \c NO_DEVICE_REMOTE_WAKEUP
			 *        compile time option is used, this function is unavailable.
			 *
			 *  \note The USB clock must be running for this function to operate. If the stack is initialized with
			 *        the \ref USB_OPT_MANUAL_PLL option enabled, the user must ensure that the PLL is running
			 *        before attempting to call this function.
			 *
			 *  \see \ref Group_StdDescriptors for more information on the RMWAKEUP feature and device descriptors.
			 */
			void USB_Device_SendRemoteWakeup(void);

		/* Inline Functions: */
			/** Returns the current USB frame number, when in device mode. Every millisecond the USB bus is active (i.e. enumerated to a host)
			 *  the frame number is incremented by one.
			 *
			 *  \return Current USB frame number from the USB controller.
			 */
			static inline uint16_t USB_Device_GetFrameNumber(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
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
			static inline void USB_Device_SetLowSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetLowSpeed(void)
			{
				AVR32_USBB.UDCON.ls      = true;
			}

			static inline void USB_Device_SetFullSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetFullSpeed(void)
			{
				AVR32_USBB.UDCON.ls      = false;
				#if defined(USB_DEVICE_OPT_HIGHSPEED)
				AVR32_USBB.UDCON.spdconf = 3;
				#endif
			}

			#if defined(USB_DEVICE_OPT_HIGHSPEED)
			static inline void USB_Device_SetHighSpeed(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetHighSpeed(void)
			{
				AVR32_USBB.UDCON.ls      = false;
				AVR32_USBB.UDCON.spdconf = 0;
			}
			#endif

			static inline void USB_Device_SetDeviceAddress(const uint8_t Address) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_SetDeviceAddress(const uint8_t Address)
			{
				AVR32_USBB.UDCON.uadd  = Address;
			}

			static inline void USB_Device_EnableDeviceAddress(const uint8_t Address) ATTR_ALWAYS_INLINE;
			static inline void USB_Device_EnableDeviceAddress(const uint8_t Address)
			{
				(void)Address;

				AVR32_USBB.UDCON.adden = true;
			}

			static inline bool USB_Device_IsAddressSet(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_Device_IsAddressSet(void)
			{
				return AVR32_USBB.UDCON.adden;
			}

			#if (USE_INTERNAL_SERIAL != NO_DESCRIPTOR)
			static inline void USB_Device_GetSerialString(uint16_t* const UnicodeString) ATTR_NON_NULL_PTR_ARG(1);
			static inline void USB_Device_GetSerialString(uint16_t* const UnicodeString)
			{
				uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
				GlobalInterruptDisable();

				uint8_t* SigReadAddress = (uint8_t*)INTERNAL_SERIAL_START_ADDRESS;

				for (uint8_t SerialCharNum = 0; SerialCharNum < (INTERNAL_SERIAL_LENGTH_BITS / 4); SerialCharNum++)
				{
					uint8_t SerialByte = *SigReadAddress;

					if (SerialCharNum & 0x01)
					{
						SerialByte >>= 4;
						SigReadAddress++;
					}

					SerialByte &= 0x0F;

					UnicodeString[SerialCharNum] = cpu_to_le16((SerialByte >= 10) ?
															   (('A' - 10) + SerialByte) : ('0' + SerialByte));
				}

				SetGlobalInterruptMask(CurrentGlobalInt);
			}
			#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

