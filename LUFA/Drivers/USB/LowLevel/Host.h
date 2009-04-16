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

/** \file
 *
 *  USB Host mode related macros and enums. This module contains macros and enums which are used when
 *  the USB controller is initialized in host mode.
 */

/** \ingroup Group_USB
 *  @defgroup Group_Host Host Management
 *
 *  Functions, macros, variables, enums and types related to the management of a USB host when in Host mode.
 *
 *  @{
 */
 
#ifndef __USBHOST_H__
#define __USBHOST_H__

	/* Includes: */
		#include <avr/io.h>
		#include <stdbool.h>
		#include <util/delay.h>

		#include "../../../Common/Common.h"
		#include "../HighLevel/USBInterrupt.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Indicates the fixed USB device address which any attached device is enumerated to when in
			 *  host mode. As only one USB device may be attached to the AVR in host mode at any one time
			 *  and that the address used is not important (other than the fact that it is non-zero), a
			 *  fixed value is specified by the library.
			 */
			#define USB_HOST_DEVICEADDRESS             1

			#if !defined(USB_HOST_TIMEOUT_MS) || defined(__DOXYGEN__)
				/** Constant for the maximum software timeout period of sent USB control transactions to an attached
				 *  device. If a device fails to respond to a sent control request within this period, the
				 *  library will return a timeout error code.
				 *
				 *  This value may be overridden in the user project makefile as the value of the 
				 *  USB_HOST_TIMEOUT_MS token, and passed to the compiler using the -D switch.
				 */
				#define USB_HOST_TIMEOUT_MS                1000
			#endif
			
			#if !defined(HOST_DEVICE_SETTLE_DELAY_MS) || defined(__DOXYGEN__)
				/** Constant for the delay in milliseconds after a device is connected before the library
				 *  will start the enumeration process. Some devices require a delay of up to 5 seconds
				 *  after connection before the enumeration process can start or incorrect operation will
				 *  occur.
				 *
				 *  This value may be overridden in the user project makefile as the value of the 
				 *  HOST_DEVICE_SETTLE_DELAY_MS token, and passed to the compiler using the -D switch.
				 */
				#define HOST_DEVICE_SETTLE_DELAY_MS        1500
			#endif
		
		/* Psuedo-Function Macros: */
			#if defined(__DOXYGEN__)
				/** Resets the USB bus, including the endpoints in any attached device and pipes on the AVR host.
				 *  USB bus resets leave the default control pipe configured (if already configured).
				 *
				 *  If the USB bus has been suspended prior to issuing a bus reset, the attached device will be
				 *  woken up automatically and the bus resumed after the reset has been correctly issued.
				 */
				static inline void USB_Host_ResetBus(void);

				/** Determines if a previously issued bus reset (via the USB_Host_ResetBus() macro) has
				 *  completed.
				 *
				 *  \return Boolean true if no bus reset is currently being sent, false otherwise.
				 */
				static inline void USB_Host_IsBusResetComplete(void);

				/** Resumes USB communications with an attached and enumerated device, by resuming the transmission
				 *  of the 1MS Start Of Frame messages to the device. When resumed, USB communications between the
				 *  host and attached device may occur.
				 */
				static inline void USB_Host_ResumeBus(void);

				/** Suspends the USB bus, preventing any communications from occurring between the host and attached
				 *  device until the bus has been resumed. This stops the transmission of the 1MS Start Of Frame
				 *  messages to the device.
				 */
				static inline void USB_Host_SuspendBus(void);
				
				/** Determines if the USB bus has been suspended via the use of the USB_Host_SuspendBus() macro,
				 *  false otherwise. While suspended, no USB communications can occur until the bus is resumed,
				 *  except for the Remote Wakeup event from the device if supported.
				 *
				 *  \return Boolean true if the bus is currently suspended, false otherwise
				 */
				 static inline bool USB_Host_IsBusSuspended(void);
				 
				/** Determines if the attached device is currently enumerated in Full Speed mode (12Mb/s), or
				 *  false if the attached device is enumerated in Low Speed mode (1.5Mb/s).
				 *
				 *  \return Boolean true if the attached device is enumerated in Full Speed mode, false otherwise
				 */
				static inline bool USB_Host_IsDeviceFullSpeed(void);

				/** Determines if the attached device is currently issuing a Remote Wakeup request, requesting
				 *  that the host resume the USB bus and wake up the device, false otherwise.
				 *
				 *  \return Boolean true if the attached device has sent a Remote Wakeup request, false otherwise
				 */
				static inline bool USB_Host_IsRemoteWakeupSent(void);

				/** Clears the flag indicating that a Remote Wakeup request has been issued by an attached device. */
				static inline void USB_Host_ClearRemoteWakeupSent(void);

				/** Accepts a Remote Wakeup request from an attached device. This must be issued in response to
				 *  a device's Remote Wakeup request within 2ms for the request to be accepted and the bus to
				 *  be resumed.
				 */
				static inline void USB_Host_ResumeFromWakeupRequest(void);
				
				/** Determines if a resume from Remote Wakeup request is currently being sent to an attached
				 *  device.
				 *
				 *  \return Boolean true if no resume request is currently being sent, false otherwise
				 */
				static inline bool USB_Host_IsResumeFromWakeupRequestSent(void);
			#else
				#define USB_Host_ResetBus()                MACROS{ UHCON |=  (1 << RESET);          }MACROE

				#define USB_Host_IsBusResetComplete()      ((UHCON &   (1 << RESET)) ? false : true)

				#define USB_Host_ResumeBus()               MACROS{ UHCON |=  (1 << SOFEN);          }MACROE 

				#define USB_Host_SuspendBus()              MACROS{ UHCON &= ~(1 << SOFEN);          }MACROE 
				
				#define USB_Host_IsBusSuspended()                ((UHCON &   (1 << SOFEN)) ? false : true)
			
				#define USB_Host_IsDeviceFullSpeed()             ((USBSTA &  (1 << SPEED)) ? true : false)

				#define USB_Host_IsRemoteWakeupSent()            ((UHINT &   (1 << RXRSMI)) ? true : false)

				#define USB_Host_ClearRemoteWakeupSent()   MACROS{ UHINT &= ~(1 << RXRSMI);         }MACROE

				#define USB_Host_ResumeFromWakeupRequest() MACROS{ UHCON |=  (1 << RESUME);         }MACROE
				
				#define USB_Host_IsResumeFromWakeupRequestSent() ((UHCON &   (1 << RESUME)) ? false : true)
			#endif

		/* Enums: */
			/** Enum for the various states of the USB Host state machine. Only some states are
			 *  implemented in the LUFA library - other states are left to the user to implement.
			 *
			 *  For information on each state, refer to the USB 2.0 specification. Some states have
			 *
			 *  \see USBTask.h for information on the global variable USB_HostState, which stores the
			 *       current host state machine state.
			 */
			enum USB_Host_States_t
			{
				HOST_STATE_WaitForDevice                = 0,  /**< Internally implemented by the library. */
				HOST_STATE_Unattached                   = 1,  /**< Internally implemented by the library. */
				HOST_STATE_Attached                     = 2,  /**< Internally implemented by the library. */
				HOST_STATE_Attached_WaitForDeviceSettle = 3,  /**< Internally implemented by the library. */
				HOST_STATE_Attached_WaitForConnect      = 4,  /**< Internally implemented by the library. */
				HOST_STATE_Attached_DoReset             = 5,  /**< Internally implemented by the library. */
				HOST_STATE_Powered                      = 6,  /**< Internally implemented by the library. */
				HOST_STATE_Default                      = 7,  /**< Internally implemented by the library. */
				HOST_STATE_Default_PostReset            = 8,  /**< Internally implemented by the library. */
				HOST_STATE_Default_PostAddressSet       = 9,  /**< Internally implemented by the library. */
				HOST_STATE_Addressed                    = 10, /**< May be implemented by the user project. */
				HOST_STATE_Configured                   = 11, /**< May be implemented by the user project. */
				HOST_STATE_Ready                        = 12, /**< May be implemented by the user project. */
				HOST_STATE_Suspended                    = 13, /**< May be implemented by the user project. */
			};
			
			/** Enum for the error codes for the USB_HostError event.
			 *
			 *  \see Events.h for more information on this event.
			 */
			enum USB_Host_ErrorCodes_t
			{
				HOST_ERROR_VBusVoltageDip       = 0, /**< VBUS voltage dipped to an unacceptable level. This
				                                      *  error may be the result of an attached device drawing
				                                      *   too much current from the VBUS line, or due to the
				                                      *   AVR's power source being unable to supply sufficient
				                                      *   current.
				                                      */
			};
			
			/** Enum for the error codes for the USB_DeviceEnumerationFailed event.
			 *
			 *  \see Events.h for more information on this event.
			 */
			enum USB_Host_EnumerationErrorCodes_t
			{
				HOST_ENUMERROR_NoError          = 0, /**< No error occurred. Used internally, this is not a valid
				                                      *   ErrorCode parameter value for the USB_DeviceEnumerationFailed
				                                      *   event.
				                                      */
				HOST_ENUMERROR_WaitStage        = 1, /**< One of the delays between enumeration steps failed
				                                      *   to complete successfully, due to a timeout or other
				                                      *   error.
				                                      */
				HOST_ENUMERROR_NoDeviceDetected = 2, /**< No device was detected, despite the USB data lines
				                                      *   indicating the attachment of a device.
				                                      */
				HOST_ENUMERROR_ControlError     = 3, /**< One of the enumeration control requests failed to
				                                      *   complete successfully.
													  */
				HOST_ENUMERROR_PipeConfigError  = 4, /**< The default control pipe (address 0) failed to
				                                      *   configure correctly.
				                                      */
			};

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define USB_Host_HostMode_On()          MACROS{ USBCON |=  (1 << HOST);           }MACROE
			#define USB_Host_HostMode_Off()         MACROS{ USBCON &= ~(1 << HOST);           }MACROE

			#define USB_Host_VBUS_Auto_Enable()     MACROS{ OTGCON &= ~(1 << VBUSHWC); UHWCON |=  (1 << UVCONE);                    }MACROE
			#define USB_Host_VBUS_Manual_Enable()   MACROS{ OTGCON |=  (1 << VBUSHWC); UHWCON &= ~(1 << UVCONE); DDRE |= (1 << 7); }MACROE

			#define USB_Host_VBUS_Auto_On()         MACROS{ OTGCON |= (1 << VBUSREQ);         }MACROE
			#define USB_Host_VBUS_Manual_On()       MACROS{ PORTE  |= (1 << 7);               }MACROE

			#define USB_Host_VBUS_Auto_Off()        MACROS{ OTGCON |=  (1 << VBUSRQC);        }MACROE
			#define USB_Host_VBUS_Manual_Off()      MACROS{ PORTE  &= ~(1 << 7);              }MACROE

			#define USB_Host_SetDeviceAddress(addr) MACROS{ UHADDR  =  (addr & 0x7F);         }MACROE

		/* Enums: */
			enum USB_Host_WaitMSErrorCodes_t
			{
				HOST_WAITERROR_Successful       = 0,
				HOST_WAITERROR_DeviceDisconnect = 1,
				HOST_WAITERROR_PipeError        = 2,
				HOST_WAITERROR_SetupStalled     = 3,
			};

		/* Function Prototypes: */
			uint8_t USB_Host_WaitMS(uint8_t MS);
			void    USB_Host_ResetDevice(void);
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
	
#endif

/** @} */
