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
		#include <stdbool.h>
		
		#include "../LowLevel/LowLevel.h"
		#include "Events.h"
		#include "StdRequestType.h"
		#include "StdDescriptors.h"
		#include "USBMode.h"

		#if defined(USB_CAN_BE_DEVICE)
			#include "../LowLevel/DevChapter9.h"
		#endif

		#if defined(USB_CAN_BE_HOST)
			#include "../LowLevel/HostChapter9.h"
		#endif
		
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif
		
	/* Public Interface - May be used in end-application: */
		/* Global Variables: */
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
			 *  inside of the \ref EVENT_USB_Device_UnhandledControlRequest() event, or for filling up with a control request to issue when
			 *  in Host mode before calling \ref USB_Host_SendControlRequest().
			 *
			 *  \ingroup Group_USBManagement
			 */
			 extern USB_Request_Header_t USB_ControlRequest;
			
			#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
				#if !defined(HOST_STATE_AS_GPIOR1) || defined(__DOXYGEN__)
					/** Indicates the current host state machine state. When in host mode, this indicates the state
					 *  via one of the values of the \ref USB_Host_States_t enum values.
					 *
					 *  This value may be altered by the user application to implement the \ref HOST_STATE_Addressed,
					 *  \ref HOST_STATE_Configured and \ref HOST_STATE_Suspended states which are not implemented by
					 *  the library.
					 *
					 *  To reduce program size and speed up checks of this global, it can be placed into one of the AVR's
					 *  GPIOR hardware registers instead of RAM by defining the HOST_STATE_AS_GPIOR token to a value 
					 *  between 0 and 2 in the project makefile and passing it to the compiler via the -D switch. When
					 *  defined, the corresponding GPIOR register should not be used in the user application except
					 *  implicitly via the library APIs.
					 *
					 *  \note This global is only present if the user application can be a USB host.
					 *
					 *  \see \ref USB_Host_States_t for a list of possible device states
					 *
					 *  \ingroup Group_Host
					 */
					extern volatile uint8_t USB_HostState;
				#else
					#define _GET_HOST_GPIOR_NAME2(y) GPIOR ## y
					#define _GET_HOST_GPIOR_NAME(x)  _GET_HOST_GPIOR_NAME2(x)
					#define USB_HostState _GET_HOST_GPIOR_NAME(HOST_STATE_AS_GPIOR)
				#endif
			#endif

			#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
				#if !defined(DEVICE_STATE_AS_GPIOR) || defined(__DOXYGEN__)
					/** Indicates the current device state machine state. When in device mode, this indicates the state
					 *  via one of the values of the \ref USB_Device_States_t enum values.
					 *
					 *  This value should not be altered by the user application as it is handled automatically by the
					 *  library. The only exception to this rule is if the NO_LIMITED_CONTROLLER_CONNECT token is used
					 *  (see \ref EVENT_USB_Device_Connect() and \ref EVENT_USB_Device_Disconnect() events).
					 *
					 *  To reduce program size and speed up checks of this global, it can be placed into one of the AVR's
					 *  GPIOR hardware registers instead of RAM by defining the DEVICE_STATE_AS_GPIOR token to a value 
					 *  between 0 and 2 in the project makefile and passing it to the compiler via the -D switch. When
					 *  defined, the corresponding GPIOR register should not be used in the user application except
					 *  implicitly via the library APIs.
					 *
					 *  \note This global is only present if the user application can be a USB device.
					 *
					 *  \note This variable should be treated as read-only in the user application, and never manually
					 *        changed in value except in the circumstances outlined above.
					 *
					 *  \see \ref USB_Device_States_t for a list of possible device states
					 *
					 *  \ingroup Group_Device
					 */
					extern volatile uint8_t USB_DeviceState;
				#else
					#define _GET_DEVICE_GPIOR_NAME2(y) GPIOR ## y
					#define _GET_DEVICE_GPIOR_NAME(x)  _GET_DEVICE_GPIOR_NAME2(x)
					#define USB_DeviceState _GET_DEVICE_GPIOR_NAME(DEVICE_STATE_AS_GPIOR)
				#endif
			#endif

		/* Function Prototypes: */
			/** This is the main USB management task. The USB driver requires that this task be executed
			 *  continuously when the USB system is active (device attached in host mode, or attached to a host
			 *  in device mode) in order to manage USB communications. This task may be executed inside an RTOS,
			 *  fast timer ISR or the main user application loop.
			 *
			 *  The USB task must be serviced within 30ms while in device mode, or within 1ms while in host mode.
			 *  The task may be serviced at all times, or (for minimum CPU consumption):
			 *
			 *    - In device mode, it may be disabled at start-up, enabled on the firing of the \ref EVENT_USB_Device_Connect() 
			 *      event and disabled again on the firing of the \ref EVENT_USB_Device_Disconnect() event.
			 *
			 *    - In host mode, it may be disabled at start-up, enabled on the firing of the \ref EVENT_USB_Host_DeviceAttached()
			 *      event and disabled again on the firing of the \ref EVENT_USB_Host_DeviceEnumerationComplete() or
			 *      \ref EVENT_USB_Host_DeviceEnumerationFailed() events.
			 *
			 *  If in device mode (only), the control endpoint can instead be managed via interrupts entirely by the library
			 *  by defining the INTERRUPT_CONTROL_ENDPOINT token and passing it to the compiler via the -D switch.
			 *
			 *  \see \ref Group_Events for more information on the USB events.
			 *
			 *  \ingroup Group_USBManagement
			 */
			void USB_USBTask(void);

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
