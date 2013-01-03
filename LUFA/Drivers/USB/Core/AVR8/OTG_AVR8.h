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
 *  \brief USB OTG definitions for the AVR8 microcontrollers.
 *  \copydetails Group_OTG_AVR8
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_OTG
 *  \defgroup Group_OTG_AVR8 USB On The Go (OTG) Management (AVR8)
 *  \brief USB OTG definitions for the AVR8 microcontrollers.
 *
 *  Architecture specific USB OTG definitions for the Atmel 8-bit AVR microcontrollers.
 *
 *  @{
 */

#ifndef __USBOTG_AVR8_H__
#define __USBOTG_AVR8_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

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
			/** Mask for the VBUS pulsing method of SRP, supported by some OTG devices.
			 *
			 *  \see \ref USB_OTG_Device_InitiateSRP().
			 */
			#define USB_OTG_SRP_VBUS                   (1 << SRPSEL)

			/** Mask for the Data + pulsing method of SRP, supported by some OTG devices.
			 *
			 *  \see \ref USB_OTG_Device_InitiateSRP().
			 */
			#define USB_OTG_STP_DATA                   0

		/* Inline Functions: */
			/** Initiate a Host Negotiation Protocol request. This indicates to the other connected device
			 *  that the device wishes to change device/host roles.
			 */
			static inline void USB_OTG_Device_RequestHNP(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTG_Device_RequestHNP(void)
			{
				OTGCON |=  (1 << HNPREQ);
			}

			/** Cancel a Host Negotiation Protocol request. This stops a pending HNP request to the other
			 *  connected device.
			 */
			static inline void USB_OTG_Device_CancelHNPRequest(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTG_Device_CancelHNPRequest(void)
			{
				OTGCON &= ~(1 << HNPREQ);
			}

			/** Determines if the device is currently sending a HNP to an attached host.
			 *
			 *  \return Boolean \c true if currently sending a HNP to the other connected device, \c false otherwise
			 */
			static inline bool USB_OTG_Device_IsSendingHNP(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_OTG_Device_IsSendingHNP(void)
			{
				return ((OTGCON & (1 << HNPREQ)) ? true : false);
			}

			/** Initiates a Session Request Protocol request. Most OTG devices turn off VBUS when the USB
			 *  interface is not in use, to conserve power. Sending a SRP to a USB OTG device running in
			 *  host mode indicates that VBUS should be applied and a session started.
			 *
			 *  There are two different methods of sending a SRP - either pulses on the VBUS line, or by
			 *  pulsing the Data + line via the internal pull-up resistor.
			 *
			 *  \param[in] SRPTypeMask  Mask indicating the type of SRP to use, either \ref USB_OTG_SRP_VBUS or
			 *                          \ref USB_OTG_STP_DATA.
			 */
			static inline void USB_OTG_Device_InitiateSRP(const uint8_t SRPTypeMask) ATTR_ALWAYS_INLINE;
			static inline void USB_OTG_Device_InitiateSRP(const uint8_t SRPTypeMask)
			{
				OTGCON = ((OTGCON & ~(1 << SRPSEL)) | (SRPTypeMask | (1 << SRPREQ)));
			}

			/** Accepts a HNP from a connected device, indicating that both devices should exchange
			 *  device/host roles.
			 */
			static inline void USB_OTG_Host_AcceptHNP(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTG_Host_AcceptHNP(void)
			{
				OTGCON |=  (1 << HNPREQ);
			}

			/** Rejects a HNP from a connected device, indicating that both devices should remain in their
			 *  current device/host roles.
			 */
			static inline void USB_OTG_Host_RejectHNP(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTG_Host_RejectHNP(void)
			{
				OTGCON &= ~(1 << HNPREQ);
			}

			/** Indicates if the connected device is currently sending a HNP request.
			 *
			 *  \return Boolean \c true if a HNP is currently being issued by the connected device, \c false otherwise.
			 */
			static inline bool USB_OTG_Host_IsHNPReceived(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_OTG_Host_IsHNPReceived(void)
			{
				return ((OTGCON & (1 << HNPREQ)) ? true : false);
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

