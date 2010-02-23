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

#ifndef __USBINTERRUPT_H__
#define __USBINTERRUPT_H__

	/* Includes: */
		#if defined(__AVR32__)
			#include <avr32/io.h>
			#include <stdbool.h>
			#include <stdint.h>
		#elif defined(__AVR__)
			#include <avr/io.h>
			#include <stdbool.h>
		#endif
		
		#include "../../../Common/Common.h"
		#include "../LowLevel/LowLevel.h"
		#include "USBMode.h"
		#include "Events.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB.h instead.
		#endif
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define USB_INT_Enable(int)              MACROS{ USB_INT_GET_EN_REG(int)   |=   USB_INT_GET_EN_MASK(int);   }MACROE
			#define USB_INT_Disable(int)             MACROS{ USB_INT_GET_EN_REG(int)   &= ~(USB_INT_GET_EN_MASK(int));  }MACROE
			#define USB_INT_Clear(int)               MACROS{ USB_INT_GET_INT_REG(int)  &= ~(USB_INT_GET_INT_MASK(int)); }MACROE
			#define USB_INT_IsEnabled(int)                 ((USB_INT_GET_EN_REG(int)   &    USB_INT_GET_EN_MASK(int)) ? true : false)
			#define USB_INT_HasOccurred(int)               ((USB_INT_GET_INT_REG(int)  &    USB_INT_GET_INT_MASK(int)) ? true : false)

			#define USB_INT_GET_EN_REG(a, b, c, d)           a
			#define USB_INT_GET_EN_MASK(a, b, c, d)          b
			#define USB_INT_GET_INT_REG(a, b, c, d)          c
			#define USB_INT_GET_INT_MASK(a, b, c, d)         d

			#define USB_INT_VBUS                             USBCON, (1 << VBUSTE) , USBINT, (1 << VBUSTI)
			#define USB_INT_IDTI                             USBCON, (1 << IDTE)   , USBINT, (1 << IDTI)
			#define USB_INT_WAKEUP                           UDIEN , (1 << WAKEUPE), UDINT , (1 << WAKEUPI)
			#define USB_INT_SUSPEND                          UDIEN , (1 << SUSPE)  , UDINT , (1 << SUSPI)
			#define USB_INT_EORSTI                           UDIEN , (1 << EORSTE) , UDINT , (1 << EORSTI)
			#define USB_INT_DCONNI                           UHIEN , (1 << DCONNE) , UHINT , (1 << DCONNI)
			#define USB_INT_DDISCI                           UHIEN , (1 << DDISCE) , UHINT , (1 << DDISCI)
			#define USB_INT_BCERRI                           OTGIEN, (1 << BCERRE) , OTGINT, (1 << BCERRI)
			#define USB_INT_VBERRI                           OTGIEN, (1 << VBERRE) , OTGINT, (1 << VBERRI)
			#define USB_INT_SOFI                             UDIEN,  (1 << SOFE)   , UDINT , (1 << SOFI)
			#define USB_INT_HSOFI                            UHIEN,  (1 << HSOFE)  , UHINT , (1 << HSOFI)
			#define USB_INT_RSTI                             UHIEN , (1 << RSTE)   , UHINT , (1 << RSTI)
			#define USB_INT_SRPI                             OTGIEN, (1 << SRPE)   , OTGINT, (1 << SRPI)
			#define USB_INT_RXSTPI                           UEIENX, (1 << RXSTPE) , UEINTX, (1 << RXSTPI)
	
		/* Function Prototypes: */
			void USB_INT_ClearAllInterrupts(void);
			void USB_INT_DisableAllInterrupts(void);
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif
