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
 
#ifndef __USBTASK_H__
#define __USBTASK_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <util/atomic.h>
		#include <stdbool.h>
		#include <stddef.h>
		
		#include "../../../Scheduler/Scheduler.h"
		#include "../LowLevel/LowLevel.h"
		#include "StdRequestType.h"
		#include "USBMode.h"
		#include "Events.h"
		#include "StdDescriptors.h"

		#if defined(USB_CAN_BE_HOST)
			#include "../LowLevel/HostChapter9.h"
		#endif		
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Global Variables: */
			/** Indicates if the USB interface is currently connected to a host if in device mode, or to a
			 *  device while running in host mode.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 *
			 *  \note For the smaller USB AVRs (AT90USBXX2) with limited USB controllers, VBUS is not available to the USB controller.
			 *        this means that the current connection state is derived from the bus suspension and wake up events by default,
			 *        which is not always accurate (host may suspend the bus while still connected). If the actual connection state
			 *        needs to be determined, VBUS should be routed to an external pin, and the auto-detect behaviour turned off by
			 *        passing the NO_LIMITED_CONTROLLER_CONNECT token to the compiler via the -D switch at compile time. The connection
			 *        and disconnection events may be manually fired, and the \ref USB_IsConnected global changed manually.
			 *
			 *  \ingroup Group_USBManagement
			 */
			extern volatile bool USB_IsConnected;

			/** Indicates if the USB interface is currently initialized but not necessarily connected to a host
			 *  or device (i.e. if \ref USB_Init() has been run). If this is false, all other library globals are invalid.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 *
			 *  \ingroup Group_USBManagement
			 */
			extern volatile bool USB_IsInitialized;

			/** Structure containing the last received Control request when in Device mode (for use in user-applications
			 *  inside of the \ref EVENT_USB_UnhandledControlPacket() event, or for filling up with a control request to issue when
			 *  in Host mode before calling \ref USB_Host_SendControlRequest().
			 *
			 *  \ingroup Group_USBManagement
			 */
			 extern USB_Request_Header_t USB_ControlRequest;
			
			#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
			/** Indicates if the USB interface is currently suspended by the host when in device mode. When suspended,
			 *  the device should consume minimal power, and cannot communicate to the host. If Remote Wakeup is
			 *  supported by the device and \ref USB_RemoteWakeupEnabled is true, suspension can be terminated by the device
			 *  by issuing a Remote Wakeup request.
			 *
			 *  \note This global is only present if the user application can be a USB device.
			 *
			 *  \note This variable should be treated as read-only in the user application, and never manually
			 *        changed in value.
			 *
			 *  \ingroup Group_Device
			 */
			extern volatile bool USB_IsSuspended;
			#endif

			#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
			/** Indicates the current host state machine state. When in host mode, this indicates the state
			 *  via one of the values of the \ref USB_Host_States_t enum values in Host.h.
			 *
			 *  This value may be altered by the user application to implement the \ref HOST_STATE_Addressed,
			 *  \ref HOST_STATE_Configured, \ref HOST_STATE_Ready and \ref HOST_STATE_Suspended states which
			 *  are not implemented by the library.
			 *
			 *  \note This global is only present if the user application can be a USB host.
			 *
			 *  \ingroup Group_Host
			 */
			extern volatile uint8_t USB_HostState;
			#endif

		/* Tasks: */
			/** This is the main USB management task. The USB driver requires that this task be executed
			 *  continuously when the USB system is active (device attached in host mode, or attached to a host
			 *  in device mode) in order to manage USB communications. This task may be executed inside an RTOS,
			 *  scheduler (e.g. the simple LUFA Scheduler), fast timer ISR or the main user application loop.
			 *
			 *  The USB task must be serviced within 30ms while in device mode, or within 1ms while in host mode.
			 *  The task may be serviced at all times, or (for minimum CPU consumption):
			 *
			 *    - In device mode, it may be disabled at start-up, enabled on the firing of the \ref EVENT_USB_Connect() event
			 *    and disabled again on the firing of the \ref EVENT_USB_Disconnect() event.
			 *
			 *    - In host mode, it may be disabled at start-up, enabled on the firing of the \ref EVENT_USB_DeviceAttached()
			 *    event and disabled again on the firing of the \ref EVENT_USB_DeviceEnumerationComplete() or
			 *    \ref EVENT_USB_DeviceEnumerationFailed() events.
			 *
			 *  If in device mode (only), the control endpoint can instead be managed via interrupts entirely by the library
			 *  by defining the INTERRUPT_CONTROL_ENDPOINT token and passing it to the compiler via the -D switch.
			 *
			 *  \see \ref Group_Events for more information on the USB events.
			 *
			 *  \ingroup Group_USBManagement
			 */
			TASK(USB_USBTask);

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Function Prototypes: */
			#if defined(INCLUDE_FROM_USBTASK_C)
				#if defined(USB_CAN_BE_HOST)
					static void USB_HostTask(void);
				#endif
				
				#if defined(USB_CAN_BE_DEVICE)
					static void USB_DeviceTask(void);
				#endif
			#endif
			
		/* Macros: */
			#define HOST_TASK_NONBLOCK_WAIT(duration, nextstate) {USB_HostState = HOST_STATE_WaitForDevice; WaitMSRemaining = duration; PostWaitState = nextstate; }
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif
