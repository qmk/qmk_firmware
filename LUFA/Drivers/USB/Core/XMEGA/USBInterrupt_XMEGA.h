/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief USB Controller Interrupt definitions for the AVR XMEGA microcontrollers.
 *
 *  This file contains definitions required for the correct handling of low level USB service routine interrupts
 *  from the USB controller.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __USBINTERRUPT_XMEGA_H__
#define __USBINTERRUPT_XMEGA_H__

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

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Enums: */
			enum USB_Interrupts_t
			{
				USB_INT_BUSEVENTI         = 1,
				USB_INT_BUSEVENTI_Suspend = 2,
				USB_INT_BUSEVENTI_Resume  = 3,
				USB_INT_BUSEVENTI_Reset   = 4,
				USB_INT_SOFI              = 5,
			};

		/* Inline Functions: */
			static inline void USB_INT_Enable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Enable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_BUSEVENTI:
						USB.INTCTRLA |= USB_BUSEVIE_bm;
						break;
					case USB_INT_SOFI:
						USB.INTCTRLA |= USB_SOFIE_bm;
						break;
					default:
						break;
				}
			}

			static inline void USB_INT_Disable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Disable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_BUSEVENTI:
						USB.INTCTRLA &= ~USB_BUSEVIE_bm;
						break;
					case USB_INT_SOFI:
						USB.INTCTRLA &= ~USB_SOFIE_bm;
						break;
					default:
						break;
				}
			}

			static inline void USB_INT_Clear(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Clear(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_BUSEVENTI_Suspend:
						USB.INTFLAGSACLR = USB_SUSPENDIF_bm;
						break;
					case USB_INT_BUSEVENTI_Resume:
						USB.INTFLAGSACLR = USB_RESUMEIF_bm;
						break;
					case USB_INT_BUSEVENTI_Reset:
						USB.INTFLAGSACLR = USB_RSTIF_bm;
						break;
					case USB_INT_SOFI:
						USB.INTFLAGSACLR = USB_SOFIF_bm;
						break;
					default:
						break;
				}
			}

			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_BUSEVENTI:
						return ((USB.INTCTRLA & USB_BUSEVIE_bm) ? true : false);
					case USB_INT_SOFI:
						return ((USB.INTCTRLA & USB_SOFIE_bm) ? true : false);
					default:
						return false;
				}
			}

			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_BUSEVENTI_Suspend:
						return ((USB.INTFLAGSACLR & USB_SUSPENDIF_bm) ? true : false);
					case USB_INT_BUSEVENTI_Resume:
						return ((USB.INTFLAGSACLR & USB_RESUMEIF_bm) ? true : false);
					case USB_INT_BUSEVENTI_Reset:
						return ((USB.INTFLAGSACLR & USB_RSTIF_bm) ? true : false);
					case USB_INT_SOFI:
						return ((USB.INTFLAGSACLR & USB_SOFIF_bm) ? true : false);
					default:
						return false;
				}
			}

		/* Includes: */
			#include "../USBMode.h"
			#include "../Events.h"
			#include "../USBController.h"

		/* Function Prototypes: */
			void USB_INT_ClearAllInterrupts(void);
			void USB_INT_DisableAllInterrupts(void);
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

