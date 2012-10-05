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
 *  \brief USB Event management definitions.
 *  \copydetails Group_Events
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USB
 *  \defgroup Group_Events USB Events
 *  \brief USB Event management definitions.
 *
 *  This module contains macros and functions relating to the management of library events, which are small
 *  pieces of code similar to ISRs which are run when a given condition is met. Each event can be fired from
 *  multiple places in the user or library code, which may or may not be inside an ISR, thus each handler
 *  should be written to be as small and fast as possible to prevent possible problems.
 *
 *  Events can be hooked by the user application by declaring a handler function with the same name and parameters
 *  listed here. If an event with no user-associated handler is fired within the library, it by default maps to an
 *  internal empty stub function.
 *
 *  Each event must only have one associated event handler, but can be raised by multiple sources by calling the
 *  event handler function (with any required event parameters).
 *
 *  @{
 */

#ifndef __USBEVENTS_H__
#define __USBEVENTS_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include "USBMode.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Pseudo-Functions for Doxygen: */
		#if !defined(__INCLUDE_FROM_EVENTS_C) || defined(__DOXYGEN__)
			/** Event for USB mode pin level change. This event fires when the USB interface is set to dual role
			 *  mode, and the UID pin level has changed to indicate a new mode (device or host). This event fires
			 *  before the mode is switched to the newly indicated mode but after the \ref EVENT_USB_Device_Disconnect
			 *  event has fired (if disconnected before the role change).
			 *
			 *  \note This event only exists on microcontrollers that support dual role USB modes.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY or \c USB_HOST_ONLY tokens have been supplied
			 *        to the compiler (see \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_UIDChange(void);

			/** Event for USB host error. This event fires when a hardware fault has occurred whilst the USB
			 *  interface is in host mode.
			 *
			 *  \param[in] ErrorCode  Error code indicating the failure reason, a value in \ref USB_Host_ErrorCodes_t.
			 *
			 *  \note This event only exists on microcontrollers that supports USB host mode.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Host_HostError(const uint8_t ErrorCode);

			/** Event for USB device attachment. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been connected to the USB interface. This is interrupt driven, thus fires before
			 *  the standard \ref EVENT_USB_Device_Connect() event and so can be used to programmatically start the USB
			 *  management task to reduce CPU consumption.
			 *
			 *  \note This event only exists on microcontrollers that supports USB host mode.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref USB_USBTask() for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Host_DeviceAttached(void);

			/** Event for USB device removal. This event fires when a the USB interface is in host mode, and
			 *  a USB device has been removed the USB interface whether or not it has been enumerated. This
			 *  can be used to programmatically stop the USB management task to reduce CPU consumption.
			 *
			 *  \note This event only exists on microcontrollers that supports USB host mode.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *
			 *  \see \ref USB_USBTask() for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Host_DeviceUnattached(void);

			/** Event for USB device enumeration failure. This event fires when a the USB interface is
			 *  in host mode, and an attached USB device has failed to enumerate completely.
			 *
			 *  \param[in] ErrorCode     Error code indicating the failure reason, a value in
			 *                           \ref USB_Host_EnumerationErrorCodes_t.
			 *
			 *  \param[in] SubErrorCode  Sub error code indicating the reason for failure - for example, if the
			 *                           ErrorCode parameter indicates a control error, this will give the error
			 *                           code returned by the \ref USB_Host_SendControlRequest() function.
			 *
			 *  \note This event only exists on microcontrollers that supports USB host mode.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
			                                            const uint8_t SubErrorCode);

			/** Event for USB device enumeration completion. This event fires when a the USB interface is
			 *  in host mode and an attached USB device has been completely enumerated and is ready to be
			 *  controlled by the user application.
			 *
			 *  This event is time-critical; exceeding OS-specific delays within this event handler (typically of around
			 *  1 second) when a transaction is waiting to be processed by the device will prevent break communications
			 *  and cause the host to reset the USB bus.
			 *
			 *  \note This event only exists on microcontrollers that supports USB host mode.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Host_DeviceEnumerationComplete(void);

			/** Event for USB Start Of Frame detection, when enabled. This event fires at the start of each USB
			 *  frame, once per millisecond, and is synchronized to the USB bus. This can be used as an accurate
			 *  millisecond timer source when the USB bus is not suspended while in host mode.
			 *
			 *  This event is time-critical; it is run once per millisecond and thus long handlers will significantly
			 *  degrade device performance. This event should only be enabled when needed to reduce device wake-ups.
			 *
			 *  \note This event is not normally active - it must be manually enabled and disabled via the
			 *        \ref USB_Host_EnableSOFEvents() and \ref USB_Host_DisableSOFEvents() commands after enumeration of
			 *        a USB device.
			 *        \n\n
			 *
			 *  \note This event does not exist if the \c USB_DEVICE_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Host_StartOfFrame(void);

			/** Event for USB device connection. This event fires when the microcontroller is in USB Device mode
			 *  and the device is connected to a USB host, beginning the enumeration process measured by a rising
			 *  level on the microcontroller's VBUS sense pin.
			 *
			 *  This event is time-critical; exceeding OS-specific delays within this event handler (typically of around
			 *  two seconds) will prevent the device from enumerating correctly.
			 *
			 *  \attention This event may fire multiple times during device enumeration on the microcontrollers with limited USB controllers
			 *             if \c NO_LIMITED_CONTROLLER_CONNECT is not defined.
			 *
			 *  \note For the microcontrollers with limited USB controller functionality, VBUS sensing is not available.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behavior turned off by
			 *        passing the \c NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired, and the \ref USB_DeviceState global changed manually.
			 *        \n\n
			 *
			 *  \see \ref Group_USBManagement for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Device_Connect(void);

			/** Event for USB device disconnection. This event fires when the microcontroller is in USB Device mode and the device is
			 *  disconnected from a host, measured by a falling level on the microcontroller's VBUS sense pin.
			 *
			 *  \attention This event may fire multiple times during device enumeration on the microcontrollers with limited USB controllers
			 *             if \c NO_LIMITED_CONTROLLER_CONNECT is not defined.
			 *
			 *  \note For the microcontrollers with limited USB controllers, VBUS sense is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behavior turned off by
			 *        passing the \c NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired, and the \ref USB_DeviceState global changed manually.
			 *        \n\n
			 *
			 *  \see \ref Group_USBManagement for more information on the USB management task and reducing CPU usage.
			 */
			void EVENT_USB_Device_Disconnect(void);

			/** Event for control requests. This event fires when a the USB host issues a control request
			 *  to the mandatory device control endpoint (of address 0). This may either be a standard
			 *  request that the library may have a handler code for internally, or a class specific request
			 *  issued to the device which must be handled appropriately. If a request is not processed in the
			 *  user application via this event, it will be passed to the library for processing internally
			 *  if a suitable handler exists.
			 *
			 *  This event is time-critical; each packet within the request transaction must be acknowledged or
			 *  sent within 50ms or the host will abort the transfer.
			 *
			 *  The library internally handles all standard control requests with the exceptions of SYNC FRAME,
			 *  SET DESCRIPTOR and SET INTERFACE. These and all other non-standard control requests will be left
			 *  for the user to process via this event if desired. If not handled in the user application or by
			 *  the library internally, unknown requests are automatically STALLed.
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *        \n\n
			 *
			 *  \note Requests should be handled in the same manner as described in the USB 2.0 Specification,
			 *        or appropriate class specification. In all instances, the library has already read the
			 *        request SETUP parameters into the \ref USB_ControlRequest structure which should then be used
			 *        by the application to determine how to handle the issued request.
			 */
			void EVENT_USB_Device_ControlRequest(void);

			/** Event for USB configuration number changed. This event fires when a the USB host changes the
			 *  selected configuration number while in device mode. This event should be hooked in device
			 *  applications to create the endpoints and configure the device for the selected configuration.
			 *
			 *  This event is time-critical; exceeding OS-specific delays within this event handler (typically of around
			 *  one second) will prevent the device from enumerating correctly.
			 *
			 *  This event fires after the value of \ref USB_Device_ConfigurationNumber has been changed.
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Device_ConfigurationChanged(void);

			/** Event for USB suspend. This event fires when a the USB host suspends the device by halting its
			 *  transmission of Start Of Frame pulses to the device. This is generally hooked in order to move
			 *  the device over to a low power state until the host wakes up the device. If the USB interface is
			 *  enumerated with the \ref USB_OPT_AUTO_PLL option set, the library will automatically suspend the
			 *  USB PLL before the event is fired to save power.
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *        \n\n
			 *
			 *  \note This event does not exist on the microcontrollers with limited USB VBUS sensing abilities
			 *        when the \c NO_LIMITED_CONTROLLER_CONNECT compile time token is not set - see
			 *        \ref EVENT_USB_Device_Disconnect.
			 *
			 *  \see \ref EVENT_USB_Device_WakeUp() event for accompanying Wake Up event.
			 */
			void EVENT_USB_Device_Suspend(void);

			/** Event for USB wake up. This event fires when a the USB interface is suspended while in device
			 *  mode, and the host wakes up the device by supplying Start Of Frame pulses. This is generally
			 *  hooked to pull the user application out of a low power state and back into normal operating
			 *  mode. If the USB interface is enumerated with the \ref USB_OPT_AUTO_PLL option set, the library
			 *  will automatically restart the USB PLL before the event is fired.
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 *        \n\n
			 *
			 *  \note This event does not exist on the microcontrollers with limited USB VBUS sensing abilities
			 *        when the \c NO_LIMITED_CONTROLLER_CONNECT compile time token is not set - see
			 *        \ref EVENT_USB_Device_Disconnect.
			 *
			 *  \see \ref EVENT_USB_Device_Suspend() event for accompanying Suspend event.
			 */
			void EVENT_USB_Device_WakeUp(void);

			/** Event for USB interface reset. This event fires when the USB interface is in device mode, and
			 *  a the USB host requests that the device reset its interface. This event fires after the control
			 *  endpoint has been automatically configured by the library.
			 *
			 *  This event is time-critical; exceeding OS-specific delays within this event handler (typically of around
			 *  two seconds) will prevent the device from enumerating correctly.
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Device_Reset(void);

			/** Event for USB Start Of Frame detection, when enabled. This event fires at the start of each USB
			 *  frame, once per millisecond, and is synchronized to the USB bus. This can be used as an accurate
			 *  millisecond timer source when the USB bus is enumerated in device mode to a USB host.
			 *
			 *  This event is time-critical; it is run once per millisecond and thus long handlers will significantly
			 *  degrade device performance. This event should only be enabled when needed to reduce device wake-ups.
			 *
			 *  \pre This event is not normally active - it must be manually enabled and disabled via the
			 *       \ref USB_Device_EnableSOFEvents() and \ref USB_Device_DisableSOFEvents() commands after enumeration.
			 *       \n\n
			 *
			 *  \note This event does not exist if the \c USB_HOST_ONLY token is supplied to the compiler (see
			 *        \ref Group_USBManagement documentation).
			 */
			void EVENT_USB_Device_StartOfFrame(void);
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_EVENTS_C)
				void USB_Event_Stub(void) ATTR_CONST;

				#if defined(USB_CAN_BE_BOTH)
					void EVENT_USB_UIDChange(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif

				#if defined(USB_CAN_BE_HOST)
					void EVENT_USB_Host_HostError(const uint8_t ErrorCode) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Host_DeviceAttached(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Host_DeviceUnattached(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Host_DeviceEnumerationComplete(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Host_DeviceEnumerationFailed(const uint8_t ErrorCode,
                                                                const uint8_t SubErrorCode)
					                                            ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Host_StartOfFrame(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif

				#if defined(USB_CAN_BE_DEVICE)
					void EVENT_USB_Device_Connect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_Disconnect(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_ControlRequest(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_ConfigurationChanged(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_Suspend(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_WakeUp(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_Reset(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
					void EVENT_USB_Device_StartOfFrame(void) ATTR_WEAK ATTR_ALIAS(USB_Event_Stub);
				#endif
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

