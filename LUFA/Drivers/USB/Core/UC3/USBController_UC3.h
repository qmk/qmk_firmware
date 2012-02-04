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
 *  \brief USB Controller definitions for the AVR32 UC3 microcontrollers.
 *  \copydetails Group_USBManagement_UC3
 *
 *  \note This file should not be included directly. It is automatically included as needed by the USB driver
 *        dispatch header located in LUFA/Drivers/USB/USB.h.
 */

/** \ingroup Group_USBManagement
 *  \defgroup Group_USBManagement_UC3 USB Interface Management (UC3)
 *  \brief USB Controller definitions for the AVR32 UC3 microcontrollers.
 *
 *  Functions, macros, variables, enums and types related to the setup and management of the USB interface.
 *
 *  @{
 */

#ifndef __USBCONTROLLER_UC3_H__
#define __USBCONTROLLER_UC3_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../USBMode.h"
		#include "../Events.h"
		#include "../USBTask.h"
		#include "../USBInterrupt.h"

		#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
			#include "../Host.h"
			#include "../OTG.h"
			#include "../Pipe.h"
			#include "../HostStandardReq.h"
			#include "../PipeStream.h"
		#endif

		#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
			#include "../Device.h"
			#include "../Endpoint.h"
			#include "../DeviceStandardReq.h"
			#include "../EndpointStream.h"
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks and Defines: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif

		#if !defined(F_USB)
			#error F_USB is not defined. You must define F_USB to the frequency of the clock input to the USB module.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** \name USB Controller Option Masks */
			//@{
			/** Selects one of the system's main clock oscillators as the input clock to the USB Generic Clock source
			 *  generation module. This indicates that an external oscillator should be used directly instead of an
			 *  internal PLL clock source.
			 */
			#define USB_OPT_GCLK_SRC_OSC               (1 << 2)

			/** Selects one of the system's PLL oscillators as the input clock to the USB Generic Clock source
			 *  generation module. This indicates that one of the device's PLL outputs should be used instead of an
			 *  external oscillator source.
			 */
			#define USB_OPT_GCLK_SRC_PLL               (0 << 2)

			/** Selects PLL or External Oscillator 0 as the USB Generic Clock source module input clock. */
			#define USB_OPT_GCLK_CHANNEL_0             (1 << 3)

			/** Selects PLL or External Oscillator 1 as the USB Generic Clock source module input clock. */
			#define USB_OPT_GCLK_CHANNEL_1             (0 << 3)
			//@}

			#if !defined(USB_STREAM_TIMEOUT_MS) || defined(__DOXYGEN__)
				/** Constant for the maximum software timeout period of the USB data stream transfer functions
				 *  (both control and standard) when in either device or host mode. If the next packet of a stream
				 *  is not received or acknowledged within this time period, the stream function will fail.
				 *
				 *  This value may be overridden in the user project makefile as the value of the
				 *  \ref USB_STREAM_TIMEOUT_MS token, and passed to the compiler using the -D switch.
				 */
				#define USB_STREAM_TIMEOUT_MS       100
			#endif

		/* Inline Functions: */
			/** Determines if the VBUS line is currently high (i.e. the USB host is supplying power).
			 *
			 *  \return Boolean \c true if the VBUS line is currently detecting power from a host, \c false otherwise.
			 */
			static inline bool USB_VBUS_GetStatus(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline bool USB_VBUS_GetStatus(void)
			{
				return AVR32_USBB.USBSTA.vbus;
			}

			/** Detaches the device from the USB bus. This has the effect of removing the device from any
			 *  attached host, ceasing USB communications. If no host is present, this prevents any host from
			 *  enumerating the device once attached until \ref USB_Attach() is called.
			 */
			static inline void USB_Detach(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Detach(void)
			{
				AVR32_USBB.UDCON.detach = true;
			}

			/** Attaches the device to the USB bus. This announces the device's presence to any attached
			 *  USB host, starting the enumeration process. If no host is present, attaching the device
			 *  will allow for enumeration once a host is connected to the device.
			 *
			 *  This is inexplicably also required for proper operation while in host mode, to enable the
			 *  attachment of a device to the host. This is despite the bit being located in the device-mode
			 *  register and despite the datasheet making no mention of its requirement in host mode.
			 */
			static inline void USB_Attach(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Attach(void)
			{
				AVR32_USBB.UDCON.detach = false;
			}

		/* Function Prototypes: */
			/** Main function to initialize and start the USB interface. Once active, the USB interface will
			 *  allow for device connection to a host when in device mode, or for device enumeration while in
			 *  host mode.
			 *
			 *  As the USB library relies on interrupts for the device and host mode enumeration processes,
			 *  the user must enable global interrupts before or shortly after this function is called. In
			 *  device mode, interrupts must be enabled within 500ms of this function being called to ensure
			 *  that the host does not time out whilst enumerating the device. In host mode, interrupts may be
			 *  enabled at the application's leisure however enumeration will not begin of an attached device
			 *  until after this has occurred.
			 *
			 *  Calling this function when the USB interface is already initialized will cause a complete USB
			 *  interface reset and re-enumeration.
			 *
			 *  \param[in] Mode     This is a mask indicating what mode the USB interface is to be initialized to, a value
			 *                      from the \ref USB_Modes_t enum.
			 *
			 *  \param[in] Options  Mask indicating the options which should be used when initializing the USB
			 *                      interface to control the USB interface's behaviour. This should be comprised of
			 *                      a \c USB_OPT_REG_* mask to control the regulator, a \c USB_OPT_*_PLL mask to control the
			 *                      PLL, and a \c USB_DEVICE_OPT_* mask (when the device mode is enabled) to set the device
			 *                      mode speed.
			 *
			 *  \note To reduce the FLASH requirements of the library if only device or host mode is required,
			 *        the mode can be statically set in the project makefile by defining the token \c USB_DEVICE_ONLY
			 *        (for device mode) or \c USB_HOST_ONLY (for host mode), passing the token to the compiler
			 *        via the -D switch. If the mode is statically set, this parameter does not exist in the
			 *        function prototype.
			 *        \n\n
			 *
			 *  \note To reduce the FLASH requirements of the library if only fixed settings are are required,
			 *        the options may be set statically in the same manner as the mode (see the Mode parameter of
			 *        this function). To statically set the USB options, pass in the \c USE_STATIC_OPTIONS token,
			 *        defined to the appropriate options masks. When the options are statically set, this
			 *        parameter does not exist in the function prototype.
			 *
			 *  \see \ref Group_Device for the \c USB_DEVICE_OPT_* masks.
			 */
			void USB_Init(
			               #if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
			               const uint8_t Mode
			               #endif

			               #if (defined(USB_CAN_BE_BOTH) && !defined(USE_STATIC_OPTIONS)) || defined(__DOXYGEN__)
			               ,
			               #elif (!defined(USB_CAN_BE_BOTH) && defined(USE_STATIC_OPTIONS))
			               void
			               #endif

			               #if !defined(USE_STATIC_OPTIONS) || defined(__DOXYGEN__)
			               const uint8_t Options
			               #endif
			               );

			/** Shuts down the USB interface. This turns off the USB interface after deallocating all USB FIFO
			 *  memory, endpoints and pipes. When turned off, no USB functionality can be used until the interface
			 *  is restarted with the \ref USB_Init() function.
			 */
			void USB_Disable(void);

			/** Resets the interface, when already initialized. This will re-enumerate the device if already connected
			 *  to a host, or re-enumerate an already attached device when in host mode.
			 */
			void USB_ResetInterface(void);

		/* Global Variables: */
			#if (!defined(USB_HOST_ONLY) && !defined(USB_DEVICE_ONLY)) || defined(__DOXYGEN__)
				/** Indicates the mode that the USB interface is currently initialized to, a value from the
				 *  \ref USB_Modes_t enum.
				 *
				 *  \note This variable should be treated as read-only in the user application, and never manually
				 *        changed in value.
				 *        \n\n
				 *
				 *  \note When the controller is initialized into UID auto-detection mode, this variable will hold the
				 *        currently selected USB mode (i.e. \ref USB_MODE_Device or \ref USB_MODE_Host). If the controller
				 *        is fixed into a specific mode (either through the \c USB_DEVICE_ONLY or \c USB_HOST_ONLY compile time
				 *        options, or a limitation of the USB controller in the chosen device model) this will evaluate to
				 *        a constant of the appropriate value and will never evaluate to \ref USB_MODE_None even when the
				 *        USB interface is not initialized.
				 */
				extern volatile uint8_t USB_CurrentMode;
			#elif defined(USB_HOST_ONLY)
				#define USB_CurrentMode USB_MODE_Host
			#elif defined(USB_DEVICE_ONLY)
				#define USB_CurrentMode USB_MODE_Device
			#endif

			#if !defined(USE_STATIC_OPTIONS) || defined(__DOXYGEN__)
				/** Indicates the current USB options that the USB interface was initialized with when \ref USB_Init()
				 *  was called. This value will be one of the \c USB_MODE_* masks defined elsewhere in this module.
				 *
				 *  \note This variable should be treated as read-only in the user application, and never manually
				 *        changed in value.
				 */
				extern volatile uint8_t USB_Options;
			#elif defined(USE_STATIC_OPTIONS)
				#define USB_Options USE_STATIC_OPTIONS
			#endif

		/* Enums: */
			/** Enum for the possible USB controller modes, for initialization via \ref USB_Init() and indication back to the
			 *  user application via \ref USB_CurrentMode.
			 */
			enum USB_Modes_t
			{
				USB_MODE_None   = 0, /**< Indicates that the controller is currently not initialized in any specific USB mode. */
				USB_MODE_Device = 1, /**< Indicates that the controller is currently initialized in USB Device mode. */
				USB_MODE_Host   = 2, /**< Indicates that the controller is currently initialized in USB Host mode. */
				USB_MODE_UID    = 3, /**< Indicates that the controller should determine the USB mode from the UID pin of the
				                      *   USB connector.
				                      */
			};

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#if defined(USB_SERIES_UC3A3_AVR32) || defined(USB_SERIES_UC3A4_AVR32)
				#define USB_CLOCK_REQUIRED_FREQ  12000000UL
			#else
				#define USB_CLOCK_REQUIRED_FREQ  48000000UL
			#endif

		/* Function Prototypes: */
			#if defined(__INCLUDE_FROM_USB_CONTROLLER_C)
				#if defined(USB_CAN_BE_DEVICE)
				static void USB_Init_Device(void);
				#endif

				#if defined(USB_CAN_BE_HOST)
				static void USB_Init_Host(void);
				#endif
			#endif

		/* Inline Functions: */
			static inline void USB_OTGPAD_On(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTGPAD_On(void)
			{
				AVR32_USBB.USBCON.otgpade = true;
			}

			static inline void USB_OTGPAD_Off(void) ATTR_ALWAYS_INLINE;
			static inline void USB_OTGPAD_Off(void)
			{
				AVR32_USBB.USBCON.otgpade = false;
			}

			static inline void USB_CLK_Freeze(void) ATTR_ALWAYS_INLINE;
			static inline void USB_CLK_Freeze(void)
			{
				AVR32_USBB.USBCON.frzclk = true;
			}

			static inline void USB_CLK_Unfreeze(void) ATTR_ALWAYS_INLINE;
			static inline void USB_CLK_Unfreeze(void)
			{
				AVR32_USBB.USBCON.frzclk = false;
			}

			static inline void USB_Controller_Enable(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Controller_Enable(void)
			{
				AVR32_USBB.USBCON.usbe = true;
			}

			static inline void USB_Controller_Disable(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Controller_Disable(void)
			{
				AVR32_USBB.USBCON.usbe = false;
			}

			static inline void USB_Controller_Reset(void) ATTR_ALWAYS_INLINE;
			static inline void USB_Controller_Reset(void)
			{
				AVR32_USBB.USBCON.usbe = false;
				AVR32_USBB.USBCON.usbe = true;
			}

			#if defined(USB_CAN_BE_BOTH)
			static inline uint8_t USB_GetUSBModeFromUID(void) ATTR_WARN_UNUSED_RESULT ATTR_ALWAYS_INLINE;
			static inline uint8_t USB_GetUSBModeFromUID(void)
			{
				if (AVR32_USBB.USBSTA.id)
				  return USB_MODE_Device;
				else
				  return USB_MODE_Host;
			}
			#endif

	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

