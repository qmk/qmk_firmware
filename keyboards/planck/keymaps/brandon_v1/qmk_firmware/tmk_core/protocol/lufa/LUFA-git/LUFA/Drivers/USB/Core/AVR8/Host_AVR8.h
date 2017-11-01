/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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
 *  \brief USB Host definitions for the AVR8 microcontrollers.
 *  \copydetails Group_Host_AVR8
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_Host
 *  \defgroup Group_Host_AVR8 Host Management (AVR8)
 *  \brief USB Host definitions for the AVR8 microcontrollers.
 *
 *  Architecture specific USB Host definitions for the Atmel 8-bit AVR microcontrollers.
 *
 *  @{
 */

#ifndef __USBHOST_AVR8_H__
#define __USBHOST_AVR8_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../StdDescriptors.h"
		#include "../Pipe.h"
		#include "../USBInterrupt.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

		#if defined(INVERTED_VBUS_ENABLE_LINE) && !defined(NO_AUTO_VBUS_MANAGEMENT)
			#error The INVERTED_VBUS_ENABLE_LINE compile option requires NO_AUTO_VBUS_MANAGEMENT for the AVR8 architecture.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Indicates the fixed USB device address which any attached device is enumerated to when in
			 *  host mode. As only one USB device may be attached to the AVR in host mode at any one time
			 *  and that the address used is not important (other than the fact that it is non-zero), a
			 *  fixed value is specified by the library.
			 */
			#define USB_HOST_DEVICEADDRESS                 1

			#if !defined(HOST_DEVICE_SETTLE_DELAY_MS) || defined(__DOXYGEN__)
				/** Constant for the delay in milliseconds after a device is connected before the library
				 *  will start the enumeration process. Some devices require a delay of up to 5 seconds
				 *  after connection before the enumeration process can start or incorrect operation will
				 *  occur.
				 *
				 *  The default delay value may be overridden in the user project makefile by defining the
				 *  \c HOST_DEVICE_SETTLE_DELAY_MS token to the required delay in milliseconds, and passed to the
				 *  compiler using the -D switch.
				 */
				#define HOST_DEVICE_SETTLE_DELAY_MS        1000
			#endif

			/** Enum for the error codes for the \ref EVENT_USB_Host_HostError() event.
			 *
			 *  \see \ref Group_Events for more information on this event.
			 */
			enum USB_Host_ErrorCodes_t
			{
				HOST_ERROR_VBusVoltageDip       = 0, /**< VBUS voltage dipped to an unacceptable level. This
				                                      *   error may be the result of an attached device drawing
				                                      *   too much current from the VBUS line, or due to the
				                                      *   AVR's power source being unable to supply sufficient
				                                      *   current.
				                                      */
			};

			/** Enum for the error codes for the \ref EVENT_USB_Host_DeviceEnumerationFailed() event.
			 *
			 *  \see \ref Group_Events for more information on this event.
			 */
			enum USB_Host_EnumerationErrorCodes_t
			{
				HOST_ENUMERROR_NoError          = 0, /**< No error occurred. Used internally, this is not a valid
				                                      *   ErrorCode parameter value for the \ref EVENT_USB_Host_DeviceEnumerationFailed()
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

		/* Inline Functions: */
			/** Returns the current USB frame number, when in host mode. Every millisecond the USB bus is active (i.e. not suspended)
			 *  the frame number is incremented by one.
			 *
			 *  \return Current USB frame number from the USB controller.
			 */
			static inline uint16_t USB_Host_GetFrameNumber(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint16_t USB_Host_GetFrameNumber(void)
			{
				return UHFNUM;
			}

			#if !defined(NO_SOF_EVENTS)
				/** Enables the host mode Start Of Frame events. When enabled, this causes the
				 *  \ref EVENT_USB_Host_StartOfFrame() event to fire once per millisecond, synchronized to the USB bus,
				 *  at the start of each USB frame when a device is enumerated while in host mode.
				 *
				 *  \note This function is not available when the \c NO_SOF_EVENTS compile time token is defined.
				 */
				static inline void USB_Host_EnableSOFEvents(void) ATTR_ALWAYS_INLINE;
				static inline void USB_Host_EnableSOFEvents(void)
				{
					USB_INT_Enable(USB_INT_HSOFI);
				}

				/** Disables the host mode Start Of Frame events. When disabled, this stops the firing of the
				 *  \ref EVENT_USB_Host_StartOfFrame() event when enumerated in host mode.
				 *
				 *  \note This function is not available when the \c NO_SOF_EVENTS compile time token is defined.
				 */
				static inline void USB_Host_DisableSOFEvents(void) ATTR_ALWAYS_INLINE;
				static inline void USB_Host_DisableSOFEvents(void)
				{
					USB_INT_Disable(USB_INT_HSOFI);
				}
			#endif

			/** Resets the USB bus, including the endpoints in any attached device and pipes on the AVR host.
			 *  USB bus resets leave the default control pipe configured (if already configured).
			 *
			 *  If the USB bus has been suspended prior to issuing a bus reset, the attached device will be
			 *  woken up automatically and the bus resumed after the reset has been correctly issued.
			 */
			static inline void USB_Host_ResetBus(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_ResetBus(void)
			{
				UHCON |=  (1 << RESET);
			}

			/** Determines if a previously issued bus reset (via the \ref USB_Host_ResetBus() macro) has
			 *  completed.
			 *
			 *  \return Boolean \c true if no bus reset is currently being sent, \c false otherwise.
			 */
			static inline bool USB_Host_IsBusResetComplete(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_Host_IsBusResetComplete(void)
			{
				return ((UHCON & (1 << RESET)) ? false : true);
			}

			/** Resumes USB communications with an attached and enumerated device, by resuming the transmission
			 *  of the 1MS Start Of Frame messages to the device. When resumed, USB communications between the
			 *  host and attached device may occur.
			 */
			static inline void USB_Host_ResumeBus(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_ResumeBus(void)
			{
				UHCON |=  (1 << SOFEN);
			}

			/** Suspends the USB bus, preventing any communications from occurring between the host and attached
			 *  device until the bus has been resumed. This stops the transmission of the 1MS Start Of Frame
			 *  messages to the device.
			 *
			 *  \attention While the USB bus is suspended, all USB interrupt sources are also disabled; this means that
			 *             some events (such as device disconnections) will not fire until the bus is resumed.
			 */
			static inline void USB_Host_SuspendBus(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_SuspendBus(void)
			{
				UHCON &= ~(1 << SOFEN);
			}

			/** Determines if the USB bus has been suspended via the use of the \ref USB_Host_SuspendBus() macro,
			 *  false otherwise. While suspended, no USB communications can occur until the bus is resumed,
			 *  except for the Remote Wakeup event from the device if supported.
			 *
			 *  \return Boolean \c true if the bus is currently suspended, \c false otherwise.
			 */
			static inline bool USB_Host_IsBusSuspended(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_Host_IsBusSuspended(void)
			{
				return ((UHCON & (1 << SOFEN)) ? false : true);
			}

			/** Determines if the attached device is currently enumerated in Full Speed mode (12Mb/s), or
			 *  false if the attached device is enumerated in Low Speed mode (1.5Mb/s).
			 *
			 *  \return Boolean \c true if the attached device is enumerated in Full Speed mode, \c false otherwise.
			 */
			static inline bool USB_Host_IsDeviceFullSpeed(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_Host_IsDeviceFullSpeed(void)
			{
				return ((USBSTA & (1 << SPEED)) ? true : false);
			}

			/** Determines if the attached device is currently issuing a Remote Wakeup request, requesting
			 *  that the host resume the USB bus and wake up the device, \c false otherwise.
			 *
			 *  \return Boolean \c true if the attached device has sent a Remote Wakeup request, \c false otherwise.
			 */
			static inline bool USB_Host_IsRemoteWakeupSent(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_Host_IsRemoteWakeupSent(void)
			{
				return ((UHINT & (1 << RXRSMI)) ? true : false);
			}

			/** Clears the flag indicating that a Remote Wakeup request has been issued by an attached device. */
			static inline void USB_Host_ClearRemoteWakeupSent(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_ClearRemoteWakeupSent(void)
			{
				UHINT &= ~(1 << RXRSMI);
			}

			/** Accepts a Remote Wakeup request from an attached device. This must be issued in response to
			 *  a device's Remote Wakeup request within 2ms for the request to be accepted and the bus to
			 *  be resumed.
			 */
			static inline void USB_Host_ResumeFromWakeupRequest(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_ResumeFromWakeupRequest(void)
			{
				UHCON |=  (1 << RESUME);
			}

			/** Determines if a resume from Remote Wakeup request is currently being sent to an attached
			 *  device.
			 *
			 *  \return Boolean \c true if no resume request is currently being sent, \c false otherwise.
			 */
			static inline bool USB_Host_IsResumeFromWakeupRequestSent(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_Host_IsResumeFromWakeupRequestSent(void)
			{
				return ((UHCON & (1 << RESUME)) ? false : true);
			}

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			static inline void USB_Host_HostMode_On(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_HostMode_On(void)
			{
				USBCON |=  (1 << HOST);
			}

			static inline void USB_Host_HostMode_Off(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_HostMode_Off(void)
			{
				USBCON &= ~(1 << HOST);
			}

			static inline void USB_Host_VBUS_Auto_Enable(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Auto_Enable(void)
			{
				OTGCON &= ~(1 << VBUSHWC);
				UHWCON |=  (1 << UVCONE);
			}

			static inline void USB_Host_VBUS_Manual_Enable(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Manual_Enable(void)
			{
				OTGCON |=  (1 << VBUSHWC);
				UHWCON &= ~(1 << UVCONE);

				DDRE   |=  (1 << 7);
			}

			static inline void USB_Host_VBUS_Auto_On(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Auto_On(void)
			{
				OTGCON |=  (1 << VBUSREQ);
			}

			static inline void USB_Host_VBUS_Manual_On(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Manual_On(void)
			{
				#if defined(INVERTED_VBUS_ENABLE_LINE)
				PORTE  &= ~(1 << 7);
				#else
				PORTE  |=  (1 << 7);
				#endif
			}

			static inline void USB_Host_VBUS_Auto_Off(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Auto_Off(void)
			{
				OTGCON |=  (1 << VBUSRQC);
			}

			static inline void USB_Host_VBUS_Manual_Off(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_VBUS_Manual_Off(void)
			{
				#if defined(INVERTED_VBUS_ENABLE_LINE)
				PORTE  |=  (1 << 7);
				#else
				PORTE  &= ~(1 << 7);
				#endif
			}

			static inline void USB_Host_SetDeviceAddress(const uint8_t Address) ATTR_ALWAYS_INLINE;
			static inline void USB_Host_SetDeviceAddress(const uint8_t Address)
			{
				UHADDR  =  (Address & 0x7F);
			}

		/* Enums: */
			enum USB_Host_WaitMSErrorCodes_t
			{
				HOST_WAITERROR_Successful       = 0,
				HOST_WAITERROR_DeviceDisconnect = 1,
				HOST_WAITERROR_PipeError        = 2,
				HOST_WAITERROR_SetupStalled     = 3,
			};

		/* Function Prototypes: */
			void    USB_Host_ProcessNextHostState(void);
			uint8_t USB_Host_WaitMS(uint8_t MS);

			#if defined(__INCLUDE_FROM_HOST_C)
				static void USB_Host_ResetDevice(void);
			#endif
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

