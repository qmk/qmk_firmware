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
 *  @defgroup Group_Events USB Events
 *
 *  This module contains macros and functions relating to the management of library events, which are small
 *  pieces of code similar to ISRs which are run when a given condition is met. Each event can be fired from
 *  multiple places in the user or library code, which may or may not be inside an ISR, thus each handler
 *  should be written to be as small and fast as possible to prevent possible problems.
 *
 *  Events can be hooked by the user application by declaring a handler function with the same name and parameters
 *  listed here. If an event with no user-associated handler is fired within the library, it by default maps to an
 *  internal empty stub function. This is achieved through the use of the GCC compiler's "alias" attribute.
 *
 *  Each event must only have one associated event handler, but can be raised by multiple sources.
 *
 *  @{
 */
 
#ifndef __USBEVENTS_H__
#define __USBEVENTS_H__

	/* Includes: */
		#include <avr/io.h>
		
		#include "../../../Common/Common.h"
		#include "USBMode.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */			
		/* Pseudo-Functions for Doxygen: */
		#if !defined(INCLUDE_FROM_EVENTS_C) || defined(__DOXYGEN__)
			/** Event for VBUS level change. This event fires when the VBUS line of the USB AVR changes from
			 *  high to low or vice-versa.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void EVENT_USB_VBUSChange(void);

			/** Event for VBUS attachment. This event fires when the VBUS line of the USB AVR changes from
			 *  low to high, signalling the attachment of the USB device to a host, before the enumeration
			 *  process has begun.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void EVENT_USB_VBUSConnect(void);

			/** Event for VBUS detachment. This event fires when the VBUS line of the USB AVR changes from
			 *  high to low, signalling the USB device has been removed from a host whether it has been enumerated
			 *  or not.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void EVENT_USB_VBUSDisconnect(void);

			/** Event for USB device connection. This event fires when the AVR is in USB host mode and a device
			 *  has been attached (but not yet fully enumerated), or when in device mode and the device is connected
			 *  to a host, beginning the enumeration process.
			 *
			 *  When in device mode, this can be used to programmatically start the USB management task to reduce
			 *  CPU usage.
			 *
			 *  \note For the smaller USB AVRs (AT90USBXX2) with limited USB controllers, VBUS is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behaviour turned off by
			 *        passing the NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired, and the \ref USB_IsConnected global changed manually.
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Connect(void);

			/** Event for USB device disconnection. This event fires when the AVR is in USB host mode and an
			 *  attached and enumerated device has been disconnected, or when in device mode and the device is
			 *  disconnected from the host.
			 *
			 *  When in device mode, this can be used to programmatically stop the USB management task to reduce
			 *  CPU usage.
			 *
			 *  \note For the smaller USB AVRs (AT90USBXX2) with limited USB controllers, VBUS is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behaviour turned off by
			 *        passing the NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired, and the \ref USB_IsConnected global changed manually.
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Disconnect(void);
			
			/** Event for USB initialization failure. This event fires when the USB interface fails to
			 *  initialize correctly due to a hardware or software fault.
			 *
			 *  \note This event only exists on USB AVR models which support dual role modes.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in \ref USB_InitErrorCodes_t
			 */
			void EVENT_USB_InitFailure(const uint8_t ErrorCode);

			/** Event for USB mode pin level change. This event fires when the USB interface is set to dual role
			 *  mode, and the UID pin level has changed to indicate a new mode (device or host). This event fires
			 *  before the mode is switched to the newly indicated mode.
			 *
			 *  \note This event only exists on USB AVR models which support dual role modes.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY or USB_HOST_ONLY tokens have been supplied
			 *        to the compiler (see \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_UIDChange(void);

			/** Event for USB host error. This event fires when a hardware fault has occurred whilst the USB
			 *  interface is in host mode.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in \ref USB_Host_ErrorCodes_t
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_HostError(const uint8_t ErrorCode);
			
			/** Event for USB device attachment. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been connected to the USB interface. This is interrupt driven, thus fires before
			 *  the standard \ref EVENT_USB_Connect event and so can be used to programmatically start the USB management
			 *  task to reduce CPU consumption.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref TASK(USB_USBTask) for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_DeviceAttached(void);

			/** Event for USB device removal. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been removed the USB interface whether or not it has been enumerated. This
			 *  can be used to programmatically stop the USB management task to reduce CPU consumption.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref TASK(USB_USBTask) for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_DeviceUnattached(void);
			
			/** Event for USB device enumeration failure. This event fires when a the USB interface is
			 *  in host mode, and an attached USB device has failed to enumerate completely.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in 
			 *                    \ref USB_Host_EnumerationErrorCodes_t
			 *
			 *  \param SubErrorCode  Sub error code indicating the reason for failure - for example, if the
			 *                       ErrorCode parameter indicates a control error, this will give the error
			 *                       code returned by the \ref USB_Host_SendControlRequest() function.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode);

			/** Event for USB device enumeration completion. This event fires when a the USB interface is
			 *  in host mode and an attached USB device has been completely enumerated and is ready to be
			 *  controlled by the user application, or when the library is in device mode, and the Host
			 *  has finished enumerating the device.
			 */
			void EVENT_USB_DeviceEnumerationComplete(void);

			/** Event for unhandled control requests. This event fires when a the USB host issues a control
			 *  request to the control endpoint (address 0) that the library does not handle. This may either
			 *  be a standard request that the library has no handler code for, or a class specific request
			 *  issued to the device which must be handled appropriately. Due to the strict timing requirements
			 *  on control transfers, interrupts are disabled during control request processing.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \note Requests should be handled in the same manner as described in the USB 2.0 Specification,
			 *        or appropriate class specification. In all instances, the library has already read the
			 *        request SETUP parameters into the \ref USB_ControlRequest structure which should then be used
			 *        by the application to determine how to handle the issued request.
			 */
			void EVENT_USB_UnhandledControlPacket(void);

			/** Event for USB configuration number changed. This event fires when a the USB host changes the
			 *  selected configuration number while in device mode. This event should be hooked in device
			 *  applications to create the endpoints and configure the device for the selected configuration.
			 *
			 *  This event fires after the value of \ref USB_ConfigurationNumber has been changed.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_ConfigurationChanged(void);

			/** Event for USB suspend. This event fires when a the USB host suspends the device by halting its
			 *  transmission of Start Of Frame pulses to the device. This is generally hooked in order to move
			 *  the device over to a low power state until the host wakes up the device.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref EVENT_USB_WakeUp() event for accompanying Wake Up event.
			 */
			void EVENT_USB_Suspend(void);

			/** Event for USB wake up. This event fires when a the USB interface is suspended while in device
			 *  mode, and the host wakes up the device by supplying Start Of Frame pulses. This is generally
			 *  hooked to pull the user application out of a lowe power state and back into normal operating
			 *  mode.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref EVENT_USB_Suspend() event for accompanying Suspend event.
			 */
			void EVENT_USB_WakeUp(void);

			/** Event for USB interface reset. This event fires when a the USB interface is in device mode, and
			 *  a the USB host requests that the device reset its interface. This is generally hooked so that
			 *  the USB control endpoint can be switched to interrupt driven mode, by selecting it and calling
			 *  USB_INT_Enable(ENDPOINT_INT_SETUP). Before this event fires, all device endpoints are reset and
			 *  disabled.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Reset(void);
			
			/** Event for USB device mode error. This event fires when the USB interface is in device mode,
			 *  and an error occurs which prevents it from operating normally.
			 *
			 *  \param ErrorCode  Error code indicating the source of the error, a value in
			 *                    \ref USB_Device_ErrorCodes_t
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_DeviceError(const uint8_t ErrorCode);
		#endif
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_EVENTS_C)
				void USB_Event_Stub(void) ATTR_CONST;

				#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER)
					void EVENT_USB_VBUSChange(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_VBUSConnect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_VBUSDisconnect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif
					
				void EVENT_USB_Connect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_Disconnect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_DeviceEnumerationComplete(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				
				#if defined(USB_CAN_BE_BOTH)
					void EVENT_USB_InitFailure(const uint8_t ErrorCode) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_UIDChange(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif
				
				#if defined(USB_CAN_BE_HOST)
					void EVENT_USB_HostError(const uint8_t ErrorCode) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_DeviceAttached(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_DeviceUnattached(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode)
					                                       ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif

				void EVENT_USB_UnhandledControlPacket(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_ConfigurationChanged(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_Suspend(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_WakeUp(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_Reset(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				void EVENT_USB_DeviceError(const uint8_t ErrorCode) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
