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

/** Library events module. This module contains macros and functions relating to the management of library
 *  events, which are small pieces of code similar to ISRs which are run when a given condition is met. Each
 *  event can be fired from multiple places in the user or library code, which may or may not be inside an ISR,
 *  thus each handler should be written to be as small and fast as possible to prevent possible problems.
 *
 *  Events can be hooked by the user application using the EVENT_HANDLER() and HANDLES_EVENT() macros. If an
 *  event with no associated handler is fired within the library, it by default fires an internal empty stub
 *  function. This is achieved through the use of the GCC compiler's "alias" attribute.
 *
 *  Each event must only have one associated event handler, but can be raised by multiple sources.
 */

/** \ingroup Group_USB
 *  @defgroup Group_Events USB Events
 *
 *  Functions, macros, variables, enums and types related to the management of events from the USB kernel.
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
		/* Macros: */
			/** Raises a given event name, with the specified parameters. For events with no parameters the
			 *  only argument to the macro is the event name, events with parameters list the parameter values
			 *  after the name as a comma separated list.
			 *
			 *  When a given event is fired, its corresponding event handler code is executed.
			 *
			 *  Usage Examples:
			 *  \code
			 *  // Raise the USB_VBUSChange event, which takes no parameters
			 *  RAISE_EVENT(USB_VBUSChange);
			 *
			 *  // Raise the USB_UnhandledControlPacket event which takes two parameters
			 *  RAISE_EVENT(USB_UnhandledControlPacket, 0, 1);
			 *  \endcode
			 *
			 *  \see RAISES_EVENT()
			 */
			#define RAISE_EVENT(e, ...)                 Event_ ## e (__VA_ARGS__)

			/** Indicates that a given module can raise a given event. This is the equivalent of putting the
			 *  event function's prototype into the module, but in a cleaner way. Each event which may be
			 *  fired via the RAISE_EVENT macro in the module should have an accompanying RAISES_EVENT
			 *  prototype in the module's header file.
			 *
			 *  Usage Examples:
			 *  \code
			 *  // Module can raise the USB_VBUSChange event
			 *  RAISES_EVENT(USB_VBUSChange);
			 *
			 *  // ...
			 *  // Inside a block of code in a function of the module, raise the USB_VBUSChange event
			 *  RAISE_EVENT(USB_VBUSChange);
			 *  \endcode
			 *
			 *  \see RAISE_EVENT()
			 */
			#define RAISES_EVENT(e)                     HANDLES_EVENT(e)

			/** Defines an event handler for the given event. Event handlers should be short in length, as they
			 *  may be raised from inside an ISR. The user application can react to each event as it sees fit,
			 *  such as logging the event, indicating the change to the user or performing some other action.
			 *
			 *  Only one event handler may be defined in any user project for each individual event. Events may
			 *  or may not have parameters - for each event, refer to its documentation elsewhere in this module
			 *  to determine the presence and purpose of any event parameters.
			 *
			 *  Usage Example:
			 *  \code
			 *  // Create an event handler for the USB_VBUSChange event
			 *  EVENT_HANDLER(USB_VBUSChange)
			 *  {
			 *      // Code to execute when the VBUS level changes
			 *  }
			 *  \endcode
			 *
			 *  \see HANDLES_EVENT()
			 */
			#define EVENT_HANDLER(e)                    void Event_ ## e e ## _P
			
			/** Indicates that a given module handles an event. This is the equivalent of putting the
			 *  event function's prototype into the module, but in a cleaner way. Each event which may be
			 *  handled via the EVENT_HANDLER macro in the module should have an accompanying HANDLES_EVENT
			 *  prototype in the module's header file.
			 *
			 *  Usage Examples:
			 *  \code
			 *  // Module handles the USB_VBUSChange event
			 *  HANDLES_EVENT(USB_VBUSChange);
			 *
			 *  // Create the USB_VBUSChange event handler
			 *  EVENT_HANDLER(USB_VBUSChange)
			 *  {
			 *      // Event handler code here
			 *  }
			 *  \endcode
			 *
			 *  \see EVENT_HANDLER()
			 */
			#define HANDLES_EVENT(e)                    EVENT_HANDLER(e)
			
		/* Pseudo-Functions for Doxygen: */
		#if defined(__DOXYGEN__)
			/** Event for VBUS level change. This event fires when the VBUS line of the USB AVR changes from
			 *  high to low or vice-versa.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void USB_VBUSChange(void);

			/** Event for VBUS attachment. This event fires when the VBUS line of the USB AVR changes from
			 *  low to high, signalling the attachment of the USB device to a host, before the enumeration
			 *  process has begun.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void USB_VBUSConnect(void);

			/** Event for VBUS detachment. This event fires when the VBUS line of the USB AVR changes from
			 *  high to low, signalling the USB device has been removed from a host whether it has been enumerated
			 *  or not.
			 *
			 *  \note This event is only available on USB AVR models which support VBUS notification interrupts.
			 */
			void USB_VBUSDisconnect(void);

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
			 *        and disconnection events may be manually fired by RAISE_EVENT(), and the USB_IsConnected global changed manually.
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void USB_Connect(void);

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
			 *        and disconnection events may be manually fired by RAISE_EVENT(), and the USB_IsConnected global changed manually.
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void USB_Disconnect(void);
			
			/** Event for USB device power on failure. This event fires when the USB interface fails to
			 *  initialize correctly due to a hardware or software fault.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in USB_PowerOnErrorCodes_t
			 *                    located in LowLevel.h.
			 */
			void USB_PowerOnFail(const uint8_t ErrorCode);

			/** Event for USB mode pin level change. This event fires when the USB interface is set to dual role
			 *  mode, and the UID pin level has changed to indicate a new mode (device or host). This event fires
			 *  before the mode is switched to the newly indicated mode.
			 *
			 *  \note This event only exists on USB AVR models which support dual role modes.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY or USB_HOST_ONLY tokens have been supplied
			 *        to the compiler (see LowLevel.h documentation).
			 */
			void USB_UIDChange(void);

			/** Event for USB host error. This event fires when a hardware fault has occurred whilst the USB
			 *  interface is in host mode.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in USB_Host_ErrorCodes_t
			 *                    located in Host.h.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 */
			void USB_HostError(const uint8_t ErrorCode);
			
			/** Event for USB device attachment. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been connected to the USB interface. This is interrupt driven, thus fires before
			 *  the standard USB_DeviceConnect event and so can be used to programmatically start the USB management
			 *  task to reduce CPU consumption.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void USB_DeviceAttached(void);

			/** Event for USB device removal. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been removed the USB interface whether or not it has been enumerated. This
			 *  can be used to programmatically stop the USB management task to reduce CPU consumption.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 *
			 *  \see USBTask.h for more information on the USB management task and reducing CPU usage.
			 */
			void USB_DeviceUnattached(void);
			
			/** Event for USB device enumeration failure. This event fires when a the USB interface is
			 *  in host mode, and an attached USB device has failed to enumerate completely.
			 *
			 *  \param ErrorCode  Error code indicating the failure reason, a value in 
			 *                    USB_Host_EnumerationErrorCodes_t located in Host.h.
			 *
			 *  \param SubErrorCode  Sub error code indicating the reason for failure - for example, if the
			 *                       ErrorCode parameter indicates a control error, this will give the error
			 *                       code returned by the USB_Host_SendControlRequest() function.
			 *
			 *  \note This event only exists on USB AVR models which supports host mode.
			 *
			 *  \note This event does not exist if the USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 */
			void USB_DeviceEnumerationFailed(const uint8_t ErrorCode, const uint8_t SubErrorCode);

			/** Event for USB device enumeration completion. This event fires when a the USB interface is
			 *  in host mode and an attached USB device has been completely enumerated and is ready to be
			 *  controlled by the user application, or when the library is in device mode, and the Host
			 *  has finished enumerating the device.
			 */
			void USB_DeviceEnumerationComplete(void);

			/** Event for unhandled control requests. This event fires when a the USB host issues a control
			 *  request to the control endpoint (address 0) that the library does not handle. This may either
			 *  be a standard request that the library has no handler code for, or a class specific request
			 *  issued to the device which must be handled appropriately. Due to the strict timing requirements
			 *  on control transfers, interrupts are disabled during control request processing.
			 *
			 *  \param bRequest       Request value, indicating what command the host has issued.
			 *  \param bmRequestType  Mask indicating the request data direction (if any), type and recipient.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 *
			 *  \note Requests should be handled in the same manner as described in the USB 2.0 Specification,
			 *        or appropriate class' specification. In all instances, the library has already read the
			 *        request bmRequestType and bRequest values out (into the Request and RequestType parameters
			 *        respectively) so that it can correctly determine if it is able to handle the request
			 *        internally, or hand off the request to the user application via this event. Other request
			 *        parameters (wValue, wIndex, wLength, and Data) remain in the control endpoint bank until
			 *        read out by the user application for processing.
			 */
			void USB_UnhandledControlPacket(const uint8_t bRequest, const uint8_t bmRequestType);

			/** Event for USB configuration number changed. This event fires when a the USB host changes the
			 *  selected configuration number while in device mode. This event should be hooked in device
			 *  applications to create the endpoints and configure the device for the selected configuration.
			 *
			 *  This event fires after the value of USB_ConfigurationNumber has been changed.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 */
			void USB_ConfigurationChanged(void);

			/** Event for USB suspend. This event fires when a the USB host suspends the device by halting its
			 *  transmission of Start Of Frame pulses to the device. This is generally hooked in order to move
			 *  the device over to a low power state until the host wakes up the device.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 *
			 *  \see USB_WakeUp() event for accompanying Wake Up event.
			 */
			void USB_Suspend(void);

			/** Event for USB wake up. This event fires when a the USB interface is suspended while in device
			 *  mode, and the host wakes up the device by supplying Start Of Frame pulses. This is generally
			 *  hooked to pull the user application out of a lowe power state and back into normal operating
			 *  mode.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 *
			 *  \see USB_Suspend() event for accompanying Suspend event.
			 */
			void USB_WakeUp(void);

			/** Event for USB interface reset. This event fires when a the USB interface is in device mode, and
			 *  a the USB host requests that the device reset its interface. This is generally hooked so that
			 *  the USB control endpoint can be switched to interrupt driven mode, by selecting it and calling
			 *  USB_INT_Enable(ENDPOINT_INT_SETUP). Before this event fires, all device endpoints are reset and
			 *  disabled.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 */
			void USB_Reset(void);
			
			/** Event for USB device mode error. This event fires when the USB interface is in device mode,
			 *  and an error occurs which prevents it from operating normally.
			 *
			 *  \param ErrorCode  Error code indicating the source of the error. One of the values in the
			 *                    USB_Device_ErrorCodes_t enum located in Device.h.
			 *
			 *  \note This event does not exist if the USB_HOST_ONLY token is supplied to the compiler (see
			 *        LowLevel.h documentation).
			 */
			void USB_DeviceError(const uint8_t ErrorCode);
		#endif
		
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define ALIAS_STUB(e)                       EVENT_HANDLER(e) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub)
		
			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER)
				#define USB_VBUSChange_P                (void)
				#define USB_VBUSConnect_P               (void)
				#define USB_VBUSDisconnect_P            (void)
			#endif
			
			#define USB_Connect_P                       (void)
			#define USB_Disconnect_P                    (void)
			#define USB_DeviceEnumerationComplete_P     (void)
			
			#if defined(USB_CAN_BE_BOTH)
				#define USB_PowerOnFail_P               (const uint8_t ErrorCode)
				#define USB_UIDChange_P                 (void)
			#endif

			#if defined(USB_CAN_BE_HOST)
				#define USB_HostError_P                 (const uint8_t ErrorCode)
				#define USB_DeviceAttached_P            (void)
				#define USB_DeviceUnattached_P          (void)
				#define USB_DeviceEnumerationFailed_P   (const uint8_t ErrorCode, const uint8_t SubErrorCode)
			#endif
			
			#if defined(USB_CAN_BE_DEVICE)
				#define USB_UnhandledControlPacket_P    (const uint8_t bRequest, const uint8_t bmRequestType)
				#define USB_ConfigurationChanged_P      (void)
				#define USB_Suspend_P                   (void)
				#define USB_WakeUp_P                    (void)
				#define USB_Reset_P                     (void)
				#define USB_DeviceError_P               (const uint8_t ErrorCode)
			#endif

		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_EVENTS_C)
				void USB_Event_Stub (void) ATTR_CONST;

				#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER)
					ALIAS_STUB(USB_VBUSChange);
					ALIAS_STUB(USB_VBUSConnect);
					ALIAS_STUB(USB_VBUSDisconnect);
				#endif
				
				ALIAS_STUB(USB_Connect);
				ALIAS_STUB(USB_Disconnect);
				ALIAS_STUB(USB_DeviceEnumerationComplete);
				
				#if defined(USB_CAN_BE_BOTH)
					ALIAS_STUB(USB_PowerOnFail);
					ALIAS_STUB(USB_UIDChange);
				#endif
				
				#if defined(USB_CAN_BE_HOST)
					ALIAS_STUB(USB_HostError);
					ALIAS_STUB(USB_DeviceAttached);
					ALIAS_STUB(USB_DeviceUnattached);
					ALIAS_STUB(USB_DeviceEnumerationFailed);
				#endif

				#if defined(USB_CAN_BE_DEVICE)
					ALIAS_STUB(USB_UnhandledControlPacket);
					ALIAS_STUB(USB_ConfigurationChanged);
					ALIAS_STUB(USB_Suspend);
					ALIAS_STUB(USB_WakeUp);
					ALIAS_STUB(USB_Reset);
					ALIAS_STUB(USB_DeviceError);
				#endif
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
