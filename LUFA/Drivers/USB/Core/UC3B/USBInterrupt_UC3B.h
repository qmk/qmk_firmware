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
 *  \brief USB Controller Interrupt definitions for the AVR32 UC3B microcontrollers.
 *
 *  This file contains definitions required for the correct handling of low level USB service routine interrupts
 *  from the USB controller.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

#ifndef __USBINTERRUPT_UC3B_H__
#define __USBINTERRUPT_UC3B_H__

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
		/* Macros: */
			enum USB_Interrupts_t
			{
				USB_INT_VBUS    = 0,
				USB_INT_IDTI    = 1,
				USB_INT_WAKEUPI = 2,
				USB_INT_SUSPI   = 3,
				USB_INT_EORSTI  = 4,
				USB_INT_DCONNI  = 5,
				USB_INT_DDISCI  = 6,
				USB_INT_BCERRI  = 7,
				USB_INT_VBERRI  = 8,
				USB_INT_SOFI    = 9,
				USB_INT_HSOFI   = 10,
				USB_INT_RSTI    = 11,
				USB_INT_SRPI    = 12,
				USB_INT_RXSTPI  = 13,
			};
			
			static inline void USB_INT_Enable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Enable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUS:
						AVR32_USBB.USBCON.vbuste      = true;
						break;
					case USB_INT_IDTI:
						AVR32_USBB.USBCON.idte        = true;
						break;
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTESET.wakeupes = true;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTESET.suspes   = true;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTESET.eorstes  = true;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTESET.dconnies = true;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTESET.ddiscies = true;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBCON.bcerre      = true;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBCON.vberre      = true;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTESET.sofes    = true;
						break;
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTESET.hsofies  = true;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTESET.rsties   = true;
						break;
					case USB_INT_SRPI:
					case USB_INT_RXSTPI:
						// TODO
						return;
				}
			}

			static inline void USB_INT_Disable(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Disable(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUS:
						AVR32_USBB.USBCON.vbuste      = false;
						break;
					case USB_INT_IDTI:
						AVR32_USBB.USBCON.idte        = false;
						break;
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTECLR.wakeupec = true;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTECLR.suspec   = true;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTECLR.eorstec  = true;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTECLR.dconniec = true;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTECLR.ddisciec = true;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBCON.bcerre      = false;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBCON.vberre      = false;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTECLR.sofec    = true;
						break;
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTECLR.hsofiec  = true;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTECLR.rstiec   = true;
						break;
					case USB_INT_SRPI:
					case USB_INT_RXSTPI:
						// TODO
						return;
				}
			}
			
			static inline void USB_INT_Clear(const uint8_t Interrupt) ATTR_ALWAYS_INLINE;
			static inline void USB_INT_Clear(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUS:
						AVR32_USBB.USBSTACLR.vbustic = true;
						break;
					case USB_INT_IDTI:
						AVR32_USBB.USBSTACLR.idtic   = true;
						break;
					case USB_INT_WAKEUPI:
						AVR32_USBB.UDINTCLR.wakeupc  = true;
						break;
					case USB_INT_SUSPI:
						AVR32_USBB.UDINTCLR.suspc    = true;
						break;
					case USB_INT_EORSTI:
						AVR32_USBB.UDINTCLR.eorstc   = true;
						break;
					case USB_INT_DCONNI:
						AVR32_USBB.UHINTCLR.dconnic  = true;
						break;
					case USB_INT_DDISCI:
						AVR32_USBB.UHINTCLR.ddiscic  = true;
						break;
					case USB_INT_BCERRI:
						AVR32_USBB.USBSTACLR.bcerric = true;
						break;
					case USB_INT_VBERRI:
						AVR32_USBB.USBSTACLR.vberric = true;
						break;
					case USB_INT_SOFI:
						AVR32_USBB.UDINTCLR.sofc     = true;
						break;
					case USB_INT_HSOFI:
						AVR32_USBB.UHINTCLR.hsofic   = true;
						break;
					case USB_INT_RSTI:
						AVR32_USBB.UHINTCLR.rstic    = true;
						break;
					case USB_INT_SRPI:
					case USB_INT_RXSTPI:
						// TODO
						return;
				}
			}
			
			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_IsEnabled(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUS:
						return AVR32_USBB.USBCON.vbuste;
					case USB_INT_IDTI:
						return AVR32_USBB.USBCON.idte;
					case USB_INT_WAKEUPI:
						return AVR32_USBB.UDINTE.wakeupe;
					case USB_INT_SUSPI:
						return AVR32_USBB.UDINTE.suspe;
					case USB_INT_EORSTI:
						return AVR32_USBB.UDINTE.eorste;
					case USB_INT_DCONNI:
						return AVR32_USBB.UHINTE.dconnie;
					case USB_INT_DDISCI:
						return AVR32_USBB.UHINTE.ddiscie;
					case USB_INT_BCERRI:
						return AVR32_USBB.USBCON.bcerre;
					case USB_INT_VBERRI:
						return AVR32_USBB.USBCON.vberre;
					case USB_INT_SOFI:
						return AVR32_USBB.UDINTE.sofe;
					case USB_INT_HSOFI:
						return AVR32_USBB.UHINTE.hsofie;
					case USB_INT_RSTI:
						return AVR32_USBB.UHINTE.rstie;
					case USB_INT_SRPI:
					case USB_INT_RXSTPI:
						// TODO
						return false;
				}
				
				return false;
			}
		
			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline bool USB_INT_HasOccurred(const uint8_t Interrupt)
			{
				switch (Interrupt)
				{
					case USB_INT_VBUS:
						return AVR32_USBB.USBSTA.vbusti;
					case USB_INT_IDTI:
						return AVR32_USBB.USBSTA.idti;
					case USB_INT_WAKEUPI:
						return AVR32_USBB.UDINT.wakeup;
					case USB_INT_SUSPI:
						return AVR32_USBB.UDINT.susp;
					case USB_INT_EORSTI:
						return AVR32_USBB.UDINT.eorst;
					case USB_INT_DCONNI:
						return AVR32_USBB.UHINT.dconni;
					case USB_INT_DDISCI:
						return AVR32_USBB.UHINT.ddisci;
					case USB_INT_BCERRI:
						return AVR32_USBB.USBSTA.bcerri;
					case USB_INT_VBERRI:
						return AVR32_USBB.USBSTA.vberri;
					case USB_INT_SOFI:
						return AVR32_USBB.UDINT.sof;
					case USB_INT_HSOFI:
						return AVR32_USBB.UHINT.hsofi;
					case USB_INT_RSTI:
						return AVR32_USBB.UHINT.rsti;
					case USB_INT_SRPI:
					case USB_INT_RXSTPI:
						// TODO
						return false;
				}

				return false;
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

