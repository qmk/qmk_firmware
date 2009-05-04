/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

/** \ingroup Group_USB
 *  @defgroup Group_USBInterrupt Endpoint and Pipe Interrupts
 *
 *  This module manages the main USB interrupt vector, for handling such events as VBUS interrupts
 *  (on supported USB AVR models), device connections and disconnections, etc. as well as providing
 *  easy to use macros for the management of the unified Endpoint/Pipe interrupt vector.
 *
 *  @{
 */

#ifndef __USBINTERRUPT_H__
#define __USBINTERRUPT_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		
		#include "../../../Common/Common.h"
		#include "../LowLevel/LowLevel.h"
		#include "USBMode.h"
		#include "Events.h"
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Vector name for the common endpoint and pipe vector. This can be used to write an ISR handler
			 *  for the endpoint and pipe events, to make certain USB functions interrupt rather than poll
			 *  driven.
			 */
			#define ENDPOINT_PIPE_vect                       USB_COM_vect
	
			/** Enables the given USB interrupt vector (such as the ENDPOINT_INT_* and PIPE_INT_* vectors in
			 *  Endpoint.h and Pipe.h).
			 */
			#define USB_INT_Enable(int)              MACROS{ USB_INT_GET_EN_REG(int)   |=   USB_INT_GET_EN_MASK(int);   }MACROE

			/** Disables the given USB interrupt vector.
			 *
			 *  \see \ref USB_INT_Enable()
			 */
			#define USB_INT_Disable(int)             MACROS{ USB_INT_GET_EN_REG(int)   &= ~(USB_INT_GET_EN_MASK(int));  }MACROE

			/** Resets the given USB interrupt flag, so that the interrupt is re-primed for the next firing. */
			#define USB_INT_Clear(int)               MACROS{ USB_INT_GET_INT_REG(int)  &= ~(USB_INT_GET_INT_MASK(int)); }MACROE
			
			/** Returns boolean false if the given USB interrupt is disabled, or true if the interrupt is currently
			 *  enabled.
			 */
			#define USB_INT_IsEnabled(int)                 ((USB_INT_GET_EN_REG(int)   &    USB_INT_GET_EN_MASK(int)) ? true : false)

			/** Returns boolean true if the given interrupt flag is set (i.e. the condition for the interrupt has occurred,
			 *  but the interrupt vector is not necessarily enabled), otherwise returns false.
			 */
			#define USB_INT_HasOccurred(int)               ((USB_INT_GET_INT_REG(int)  &    USB_INT_GET_INT_MASK(int)) ? true : false)
		
		/* Throwable Events: */
			/** This module raises the USB Connected interrupt when the AVR is attached to a host while in device
			 *  USB mode.
			 *
			 *  \note For the smaller USB AVRs (AT90USBXX2) with limited USB controllers, VBUS is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behaviour turned off by
			 *        passing the NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired by \ref RAISE_EVENT(), and the USB_IsConnected global changed manually.
			 */
			RAISES_EVENT(USB_Connect);

			/** This module raises the USB Disconnected interrupt when the AVR is removed from a host while in
			 *  device USB mode.
			 *
			 *  \note For the smaller USB AVRs (AT90USBXX2) with limited USB controllers, VBUS is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behaviour turned off by
			 *        passing the NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired by \ref RAISE_EVENT(), and the USB_IsConnected global changed manually.
			 */
			RAISES_EVENT(USB_Disconnect);

			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER) || defined(__DOXYGEN__)
				/** This module raises the VBUS Change event when the current VBUS status (present or not present) has
				 *  changed.
				 *
				 *  \note Not all USB AVR models support VBUS interrupts; this event only exists on supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_VBUSChange);

				/** This module raises the VBUS Connect event when the VBUS line is powered.
				 *
				 *  \note Not all USB AVR models support VBUS interrupts; this event only exists on supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_VBUSConnect);

				/** This module raises the VBUS Disconnect event when power is removed from the VBUS line.
				 *
				 *  \note Not all USB AVR models support VBUS interrupts; this event only exists on supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_VBUSDisconnect);
			#endif

			#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
				/** This module raises the Suspended event when the host suspends the USB interface of the AVR
				 *  whilst running in device mode.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_Suspend);

				/** This module raises the Wake Up event when the host resumes the USB interface of the AVR
				 *  whilst running in device mode.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_WakeUp);

				/** This module raises the USB Reset event when the host resets the USB interface of the AVR
				 *  whilst running in device mode.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_Reset);
			#endif
			
			#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
				/** This module raises the Host Error event when the VBUS line voltage dips below the minimum threshold
				 *  while running in host mode.
				 *
				 *  \note Not all USB AVR models support host mode; this event only exists on supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_HostError);

				/** This module raises the Device Unattached event when an attached device is removed from the AVR whilst
				 *  running in host mode.
				 *
				 *  \note Not all USB AVR models support host mode; this event only exists on supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_DeviceUnattached);
			#endif

			#if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
				/** This module raises the UID Change event when the UID line changes in value on dual-role devices.
				 *
				 *  \note Not all USB AVR models support host mode and thus the UID pin; this event only exists on
				 *        supported AVRs.
				 *
				 *  \see \ref Group_Events for more information on this event.
				 */
				RAISES_EVENT(USB_UIDChange);
			#endif
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
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
	
		/* Function Prototypes: */
			void USB_INT_ClearAllInterrupts(void);
			void USB_INT_DisableAllInterrupts(void);
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
