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
 *  \brief USB Controller Interrupt definitions for the AVR32 UC3 microcontrollers.
 *
 *  This file contains definitions required for the correct handling of low level USB service routine interrupts
 *  from the USB controller.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __USBINTERRUPT_UC3_H__
#define __USBINTERRUPT_UC3_H__

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
		/* External Variables: */
			extern volatile uint32_t USB_Endpoint_SelectedEndpoint;

		/* Enums: */
			enum USB_Interrupts_t
			{
				USB_INT_VBUSTI  = 0,
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
				#endif
			};

		/* Inline Functions: */
			static inline void USB_INT_Enable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Enable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUSTI:
						AVR32_USBB.USBCON.vbuste      = true;
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						AVR32_USBB.USBCON.idte        = true;
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTESET.wakeupes = true;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTESET.suspes   = true;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTESET.eorstes  = true;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTESET.sofes    = true;
						break;
					case USB_INT_RXSTPI:
						(&AVR32_USBB.UECON0SET)[USB_Endpoint_SelectedEndpoint].rxstpes = true;
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTESET.hsofies  = true;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTESET.dconnies = true;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTESET.ddiscies = true;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTESET.rsties   = true;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBCON.bcerre      = true;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBCON.vberre      = true;
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
					case USB_INT_VBUSTI:
						AVR32_USBB.USBCON.vbuste      = false;
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						AVR32_USBB.USBCON.idte        = false;
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTECLR.wakeupec = true;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTECLR.suspec   = true;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTECLR.eorstec  = true;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTECLR.sofec    = true;
						break;
					case USB_INT_RXSTPI:
						(&AVR32_USBB.UECON0CLR)[USB_Endpoint_SelectedEndpoint].rxstpec = true;
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTECLR.hsofiec  = true;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTECLR.dconniec = true;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTECLR.ddisciec = true;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTECLR.rstiec   = true;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBCON.bcerre      = false;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBCON.vberre      = false;
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
					case USB_INT_VBUSTI:
						AVR32_USBB.USBSTACLR.vbustic = true;
						(void)AVR32_USBB.USBSTACLR;
						break;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						AVR32_USBB.USBSTACLR.idtic   = true;
						(void)AVR32_USBB.USBSTACLR;
						break;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTCLR.wakeupc  = true;
						(void)AVR32_USBB.UDINTCLR;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTCLR.suspc    = true;
						(void)AVR32_USBB.UDINTCLR;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTCLR.eorstc   = true;
						(void)AVR32_USBB.UDINTCLR;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTCLR.sofc     = true;
						(void)AVR32_USBB.UDINTCLR;
						break;
					case USB_INT_RXSTPI:
						(&AVR32_USBB.UESTA0CLR)[USB_Endpoint_SelectedEndpoint].rxstpic = true;
						break;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTCLR.hsofic   = true;
						(void)AVR32_USBB.UHINTCLR;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTCLR.dconnic  = true;
						(void)AVR32_USBB.UHINTCLR;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTCLR.ddiscic  = true;
						(void)AVR32_USBB.UHINTCLR;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTCLR.rstic    = true;
						(void)AVR32_USBB.UHINTCLR;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBSTACLR.bcerric = true;
						(void)AVR32_USBB.USBSTACLR;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBSTACLR.vberric = true;
						(void)AVR32_USBB.USBSTACLR;
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
					case USB_INT_VBUSTI:
						return AVR32_USBB.USBCON.vbuste;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						return AVR32_USBB.USBCON.idte;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						return AVR32_USBB.UDINTE.wakeupe;
					case USB_INT_SUSPI:
						return AVR32_USBB.UDINTE.suspe;
					case USB_INT_EORSTI:
						return AVR32_USBB.UDINTE.eorste;
					case USB_INT_SOFI:
						return AVR32_USBB.UDINTE.sofe;
					case USB_INT_RXSTPI:
						return (&AVR32_USBB.UECON0)[USB_Endpoint_SelectedEndpoint].rxstpe;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						return AVR32_USBB.UHINTE.hsofie;
					case USB_INT_DCONNI:
						return AVR32_USBB.UHINTE.dconnie;
					case USB_INT_DDISCI:
						return AVR32_USBB.UHINTE.ddiscie;
					case USB_INT_RSTI:
						return AVR32_USBB.UHINTE.rstie;
					case USB_INT_BCERRI:
						return AVR32_USBB.USBCON.bcerre;
					case USB_INT_VBERRI:
						return AVR32_USBB.USBCON.vberre;
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
					case USB_INT_VBUSTI:
						return AVR32_USBB.USBSTA.vbusti;
					#if defined(USB_CAN_BE_BOTH)
					case USB_INT_IDTI:
						return AVR32_USBB.USBSTA.idti;
					#endif
					#if defined(USB_CAN_BE_DEVICE)
					case USB_INT_WAKEUPI:
						return AVR32_USBB.UDINT.wakeup;
					case USB_INT_SUSPI:
						return AVR32_USBB.UDINT.susp;
					case USB_INT_EORSTI:
						return AVR32_USBB.UDINT.eorst;
					case USB_INT_SOFI:
						return AVR32_USBB.UDINT.sof;
					case USB_INT_RXSTPI:
						return (&AVR32_USBB.UESTA0)[USB_Endpoint_SelectedEndpoint].rxstpi;
					#endif
					#if defined(USB_CAN_BE_HOST)
					case USB_INT_HSOFI:
						return AVR32_USBB.UHINT.hsofi;
					case USB_INT_DCONNI:
						return AVR32_USBB.UHINT.dconni;
					case USB_INT_DDISCI:
						return AVR32_USBB.UHINT.ddisci;
					case USB_INT_RSTI:
						return AVR32_USBB.UHINT.rsti;
					case USB_INT_BCERRI:
						return AVR32_USBB.USBSTA.bcerri;
					case USB_INT_VBERRI:
						return AVR32_USBB.USBSTA.vberri;
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

	/* Public Interface - May be used in end-application: */
		/* Function Prototypes: */
			#if defined(__DOXYGEN__)
				/** Interrupt service routine handler for the USB controller ISR group. This interrupt routine <b>must</b> be
				 *  linked to the entire USB controller ISR vector group inside the AVR32's interrupt controller peripheral,
				 *  using the user application's preferred USB controller driver.
				 */
				void USB_GEN_vect(void);
			#else
				ISR(USB_GEN_vect);
			#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

