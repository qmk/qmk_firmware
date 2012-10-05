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
 *  \brief USB Controller Interrupt definitions for the AVR8 microcontrollers.
 *
 *  This file contains definitions required for the correct handling of low level USB service routine interrupts
 *  from the USB controller.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __USBINTERRUPT_AVR8_H__
#define __USBINTERRUPT_AVR8_H__

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
				#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR) || defined(__DOXYGEN__))
				USB_INT_VBUSTI  = 0,
				#endif
				#if (defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__))
				USB_INT_IDTI    = 1,
				#endif
				#if (defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__))
				USB_INT_WAKEUPI = 2,
				USB_INT_SUSPI   = 3,
				USB_INT_EORSTI  = 4,
				USB_INT_SOFI    = 5,
				USB_INT_RXSTPI  = 6,
				#endif
				#if (defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__))
				USB_INT_HSOFI   = 7,
				USB_INT_DCONNI  = 8,
				USB_INT_DDISCI  = 9,
				USB_INT_RSTI    = 10,
				USB_INT_BCERRI  = 11,
				USB_INT_VBERRI  = 12,
				USB_INT_SRPI    = 13,
				#endif
			};

		/* Inline Functions: */
			static inline void USB_INT_Enable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Enable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
					case USB_INT_VBUSTI:
						USBCON |= (1 << VBUSTE);
						break;
					#endif
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						USBCON |= (1 << IDTE);
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						UDIEN  |= (1 << WAKEUPE);
						break;
					case USB_INT_SUSPI:
						UDIEN  |= (1 << SUSPE);
						break;
					case USB_INT_EORSTI:
						UDIEN  |= (1 << EORSTE);
						break;
					case USB_INT_SOFI:
						UDIEN  |= (1 << SOFE);
						break;
					case USB_INT_RXSTPI:
						UEIENX |= (1 << RXSTPE);
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						UHIEN  |= (1 << HSOFE);
						break;
					case USB_INT_DCONNI:
						UHIEN  |= (1 << DCONNE);
						break;
					case USB_INT_DDISCI:
						UHIEN  |= (1 << DDISCE);
						break;
					case USB_INT_RSTI:
						UHIEN  |= (1 << RSTE);
						break;
					case USB_INT_BCERRI:
						OTGIEN |= (1 << BCERRE);
						break;
					case USB_INT_VBERRI:
						OTGIEN |= (1 << VBERRE);
						break;
					case USB_INT_SRPI:
						OTGIEN |= (1 << SRPE);
						break;
					#endif
					default:
						break;
				}
			}

			static inline void USB_INT_Disable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Disable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
					case USB_INT_VBUSTI:
						USBCON &= ~(1 << VBUSTE);
						break;
					#endif
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						USBCON &= ~(1 << IDTE);
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						UDIEN  &= ~(1 << WAKEUPE);
						break;
					case USB_INT_SUSPI:
						UDIEN  &= ~(1 << SUSPE);
						break;
					case USB_INT_EORSTI:
						UDIEN  &= ~(1 << EORSTE);
						break;
					case USB_INT_SOFI:
						UDIEN  &= ~(1 << SOFE);
						break;
					case USB_INT_RXSTPI:
						UEIENX &= ~(1 << RXSTPE);
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						UHIEN  &= ~(1 << HSOFE);
						break;
					case USB_INT_DCONNI:
						UHIEN  &= ~(1 << DCONNE);
						break;
					case USB_INT_DDISCI:
						UHIEN  &= ~(1 << DDISCE);
						break;
					case USB_INT_RSTI:
						UHIEN  &= ~(1 << RSTE);
						break;
					case USB_INT_BCERRI:
						OTGIEN &= ~(1 << BCERRE);
						break;
					case USB_INT_VBERRI:
						OTGIEN &= ~(1 << VBERRE);
						break;
					case USB_INT_SRPI:
						OTGIEN &= ~(1 << SRPE);
						break;
					#endif
					default:
						break;
				}
			}

			static inline void USB_INT_Clear(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Clear(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
					case USB_INT_VBUSTI:
						USBINT &= ~(1 << VBUSTI);
						break;
					#endif
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						USBINT &= ~(1 << IDTI);
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						UDINT  &= ~(1 << WAKEUPI);
						break;
					case USB_INT_SUSPI:
						UDINT  &= ~(1 << SUSPI);
						break;
					case USB_INT_EORSTI:
						UDINT  &= ~(1 << EORSTI);
						break;
					case USB_INT_SOFI:
						UDINT  &= ~(1 << SOFI);
						break;
					case USB_INT_RXSTPI:
						UEINTX &= ~(1 << RXSTPI);
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						UHINT  &= ~(1 << HSOFI);
						break;
					case USB_INT_DCONNI:
						UHINT  &= ~(1 << DCONNI);
						break;
					case USB_INT_DDISCI:
						UHINT  &= ~(1 << DDISCI);
						break;
					case USB_INT_RSTI:
						UHINT  &= ~(1 << RSTI);
						break;
					case USB_INT_BCERRI:
						OTGINT &= ~(1 << BCERRI);
						break;
					case USB_INT_VBERRI:
						OTGINT &= ~(1 << VBERRI);
						break;
					case USB_INT_SRPI:
						OTGINT &= ~(1 << SRPI);
						break;
					#endif
					default:
						break;
				}
			}

			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
					case USB_INT_VBUSTI:
						return (USBCON & (1 << VBUSTE));
					#endif
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						return (USBCON & (1 << IDTE));
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						return (UDIEN  & (1 << WAKEUPE));
					case USB_INT_SUSPI:
						return (UDIEN  & (1 << SUSPE));
					case USB_INT_EORSTI:
						return (UDIEN  & (1 << EORSTE));
					case USB_INT_SOFI:
						return (UDIEN  & (1 << SOFE));
					case USB_INT_RXSTPI:
						return (UEIENX & (1 << RXSTPE));
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						return (UHIEN  & (1 << HSOFE));
					case USB_INT_DCONNI:
						return (UHIEN  & (1 << DCONNE));
					case USB_INT_DDISCI:
						return (UHIEN  & (1 << DDISCE));
					case USB_INT_RSTI:
						return (UHIEN  & (1 << RSTE));
					case USB_INT_BCERRI:
						return (OTGIEN & (1 << BCERRE));
					case USB_INT_VBERRI:
						return (OTGIEN & (1 << VBERRE));
					case USB_INT_SRPI:
						return (OTGIEN & (1 << SRPE));
					#endif
					default:
						return false;
				}
			}

			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					#if (defined(USB_SERIES_4_AVR) || defined(USB_SERIES_6_AVR) || defined(USB_SERIES_7_AVR))
					case USB_INT_VBUSTI:
						return (USBINT & (1 << VBUSTI));
					#endif
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						return (USBINT & (1 << IDTI));
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						return (UDINT  & (1 << WAKEUPI));
					case USB_INT_SUSPI:
						return (UDINT  & (1 << SUSPI));
					case USB_INT_EORSTI:
						return (UDINT  & (1 << EORSTI));
					case USB_INT_SOFI:
						return (UDINT  & (1 << SOFI));
					case USB_INT_RXSTPI:
						return (UEINTX & (1 << RXSTPI));
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						return (UHINT  & (1 << HSOFI));
					case USB_INT_DCONNI:
						return (UHINT  & (1 << DCONNI));
					case USB_INT_DDISCI:
						return (UHINT  & (1 << DDISCI));
					case USB_INT_RSTI:
						return (UHINT  & (1 << RSTI));
					case USB_INT_BCERRI:
						return (OTGINT & (1 << BCERRI));
					case USB_INT_VBERRI:
						return (OTGINT & (1 << VBERRI));
					case USB_INT_SRPI:
						return (OTGINT & (1 << SRPI));
					#endif
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

