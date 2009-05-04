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
 *  @defgroup Group_USBManagement USB Interface Management
 *
 *  Functions, macros, variables, enums and types related to the setup and management of the USB interface.
 *
 *  @{
 */

#ifndef __USBLOWLEVEL_H__
#define __USBLOWLEVEL_H__

	/* Includes: */
		#include <avr/io.h>
		#include <avr/interrupt.h>
		#include <stdbool.h>
		
		#include "../HighLevel/USBMode.h"

		#include "../../../Common/Common.h"
		#include "../HighLevel/USBMode.h"
		#include "../HighLevel/Events.h"
		#include "../HighLevel/USBTask.h"
		#include "../HighLevel/USBInterrupt.h"
		
		#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
			#include "Host.h"
			#include "Pipe.h"
			#include "OTG.h"
		#endif
		
		#if defined(USB_CAN_BE_DEVICE) || defined(__DOXYGEN__)
			#include "Device.h"
			#include "Endpoint.h"
			#include "DevChapter9.h"
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks and Defines: */
		#if !defined(F_CLOCK)
			#error F_CLOCK is not defined. You must device F_CLOCK to the frequency of the unprescaled input clock in your project makefile.
		#endif
	
		#if (F_CLOCK == 8000000)
			#if (defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__))
				#define USB_PLL_PSC                0
			#elif (defined(__AVR_AT90USB646__)  || defined(__AVR_AT90USB647__)  || \
			       defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || \
				   defined(__AVR_ATmega32U6__))
				#define USB_PLL_PSC                ((1 << PLLP1) | (1 << PLLP0))
			#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				#define USB_PLL_PSC                0
			#endif
		#elif (F_CLOCK == 16000000)
			#if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_ATmega32U6__))
				#define USB_PLL_PSC                ((1 << PLLP2) | (1 << PLLP1))
			#elif (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__))
				#define USB_PLL_PSC                ((1 << PLLP2) | (1 << PLLP0))
			#elif (defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__))
				#define USB_PLL_PSC                (1 << PLLP0)
			#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				#define USB_PLL_PSC                (1 << PINDIV)
			#endif
		#endif
		
		#if !defined(USB_PLL_PSC)
			#error No PLL prescale value available for chosen F_CPU value and AVR model.
		#endif
		
	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mode mask for the \ref USB_CurrentMode global. This indicates that the USB interface is currently not
			 *  initialized into any mode.
			 */
			#define USB_MODE_NONE                      0

			/** Mode mask for the \ref USB_CurrentMode global and the \ref USB_Init() function. This indicates that the
			 *  USB interface is or should be initialized in the USB device mode.
			 */
			#define USB_MODE_DEVICE                    1

			#if defined(USB_CAN_BE_HOST) || defined(__DOXYGEN__)
				/** Mode mask for the \ref USB_CurrentMode global and the \ref USB_Init() function. This indicates that the
				 *  USB interface is or should be initialized in the USB host mode.
				 *
				 *  \note This token is not available on AVR models which do not support host mode.
				 */
				#define USB_MODE_HOST                  2
			#endif
			
			#if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
				/** Mode mask for the the \ref USB_Init() function. This indicates that the USB interface should be
				 *  initialized into whatever mode the UID pin of the USB AVR indicates, and that the device
				 *  should swap over its mode when the level of the UID pin changes during operation.
				 *
				 *  \note This token is not available on AVR models which do not support both host and device modes.
				 */
				#define USB_MODE_UID                       3
			#endif
			
			/** Regulator disable option mask for \ref USB_Init(). This indicates that the internal 3.3V USB data pad
			 *  regulator should be enabled to regulate the data pin voltages to within the USB standard.
			 *
			 *  \note See USB AVR data sheet for more information on the internal pad regulator.
			 */
			#define USB_OPT_REG_DISABLED               (1 << 1)

			/** Regulator enable option mask for \ref USB_Init(). This indicates that the internal 3.3V USB data pad
			 *  regulator should be disabled and the AVR's VCC level used for the data pads.
			 *
			 *  \note See USB AVR data sheet for more information on the internal pad regulator.
			 */
			#define USB_OPT_REG_ENABLED                (0 << 1)
			
			/** Manual PLL control option mask for \ref USB_Init(). This indicates to the library that the user application
			 *  will take full responsibility for controlling the AVR's PLL (used to generate the high frequency clock
			 *  that the USB controller requires) and ensuring that it is locked at the correct frequency for USB operations.
			 */
			#define USB_OPT_MANUAL_PLL                 (1 << 2)

			/** Automatic PLL control option mask for \ref USB_Init(). This indicates to the library that the library should
			 *  take full responsibility for controlling the AVR's PLL (used to generate the high frequency clock
			 *  that the USB controller requires) and ensuring that it is locked at the correct frequency for USB operations.
			 */
			#define USB_OPT_AUTO_PLL                   (0 << 2)

			/** Mask for a CONTROL type endpoint or pipe.
			 *
			 *  \note See \ref Group_EndpointManagement and \ref Group_PipeManagement for endpoint/pipe functions.
			 */
			#define EP_TYPE_CONTROL                    0x00

			/** Mask for an ISOCHRONOUS type endpoint or pipe.
			 *
			 *  \note See \ref Group_EndpointManagement and \ref Group_PipeManagement for endpoint/pipe functions.
			 */
			#define EP_TYPE_ISOCHRONOUS                0x01

			/** Mask for a BULK type endpoint or pipe.
			 *
			 *  \note See \ref Group_EndpointManagement and \ref Group_PipeManagement for endpoint/pipe functions.
			 */
			#define EP_TYPE_BULK                       0x02

			/** Mask for an INTERRUPT type endpoint or pipe.
			 *
			 *  \note See \ref Group_EndpointManagement and \ref Group_PipeManagement for endpoint/pipe functions.
			 */
			#define EP_TYPE_INTERRUPT                  0x03

			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER) || defined(__DOXYGEN__)
				/** Returns boolean true if the VBUS line is currently high (i.e. the USB host is supplying power),
				 *  otherwise returns false.
				 *
				 *  \note This token is not available on some AVR models which do not support hardware VBUS monitoring.
				 */
				#define USB_VBUS_GetStatus()             ((USBSTA & (1 << VBUS)) ? true : false)
			#endif

			/** Detaches the device from the USB bus. This has the effect of removing the device from any
			 *  host if, ceasing USB communications. If no host is present, this prevents any host from
			 *  enumerating the device once attached until \ref USB_Attach() is called.
			 */
			#define USB_Detach()                    MACROS{ UDCON  |=  (1 << DETACH);  }MACROE

			/** Attaches the device to the USB bus. This announces the device's presence to any attached
			 *  USB host, starting the enumeration process. If no host is present, attaching the device
			 *  will allow for enumeration once a host is connected to the device.
			 *
			 *  This is inexplicably also required for proper operation while in host mode, to enable the
			 *  attachment of a device to the host. This is despite the bit being located in the device-mode
			 *  register and despite the datasheet making no mention of its requirement in host mode.
			 */
			#define USB_Attach()                    MACROS{ UDCON  &= ~(1 << DETACH);  }MACROE
			
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

		/* Function Prototypes: */
			/** Main function to initialize and start the USB interface. Once active, the USB interface will
			 *  allow for device connection to a host when in device mode, or for device enumeration while in
			 *  host mode.
			 *
			 *  As the USB library relies on USB interrupts for some of its functionality, this routine will
			 *  enable global interrupts.
			 *
			 *  Calling this function when the USB interface is already initialized will cause a complete USB
			 *  interface reset and re-enumeration.
			 *
			 *  \param Mode     This is a mask indicating what mode the USB interface is to be initialized to.
			 *                  Valid mode masks are \ref USB_MODE_DEVICE, \ref USB_MODE_HOST or \ref USB_MODE_UID.
			 *
			 *  \param Options  Mask indicating the options which should be used when initializing the USB
			 *                  interface to control the USB interface's behaviour. This should be comprised of
			 *                  a USB_OPT_REG_* mask to control the regulator, a USB_OPT_*_PLL mask to control the
			 *                  PLL, and a USB_DEVICE_OPT_* mask (when the device mode is enabled) to set the device
			 *                  mode speed.
			 *
			 *  \note To reduce the FLASH requirements of the library if only device or host mode is required, 
			 *        this can be statically set via defining the token USB_DEVICE_ONLY for device mode or 
			 *        USB_HOST_ONLY for host mode in the use project makefile, passing the token to the compiler 
			 *        via the -D switch. If the mode is statically set, this parameter does not exist in the
			 *        function prototype.
			 *
			 *  \note To reduce the FLASH requirements of the library if only fixed settings are are required,
			 *        the options may be set statically in the same manner as the mode (see the Mode parameter of 
			 *        this function). To statically set the USB options, pass in the USE_STATIC_OPTIONS token,
			 *        defined to the appropriate options masks. When the options are statically set, this
			 *        parameter does not exist in the function prototype.
			 *        
			 *  \note The mode parameter does not exist on devices where only one mode is possible, such as USB 
			 *        AVR models which only implement the USB device mode in hardware.
			 *
			 *  \see Device.h for the USB_DEVICE_OPT_* masks.
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
			void USB_ShutDown(void);

			/** Resets the interface, when already initialized. This will re-enumerate the device if already connected
			 *  to a host, or re-enumerate an already attached device when in host mode.
			 */
			void USB_ResetInterface(void);

		/* Enums: */
			/** Enum for error codes relating to the powering on of the USB interface. These error codes are
			 *  used in the ErrorCode parameter value of the \ref USB_InitFailure event.
			 */
			enum USB_InitErrorCodes_t
			{
				USB_INITERROR_NoUSBModeSpecified       = 0, /**< Indicates that \ref USB_Init() was called with an
			                                                 *   invalid or missing Mode parameter.
			                                                 */
			};

		/* Global Variables: */
			#if (!defined(USB_HOST_ONLY) && !defined(USB_DEVICE_ONLY)) || defined(__DOXYGEN__)
				/** Indicates the mode that the USB interface is currently initialized to. This value will be
				 *  one of the USB_MODE_* masks defined elsewhere in this module.
				 *
				 *  \note This variable should be treated as read-only in the user application, and never manually
				 *        changed in value.
				 */
				extern volatile uint8_t USB_CurrentMode;
			#endif
			
			#if !defined(USE_STATIC_OPTIONS) || defined(__DOXYGEN__)
				/** Indicates the current USB options that the USB interface was initialized with when \ref USB_Init()
				 *  was called. This value will be one of the USB_MODE_* masks defined elsewhere in this module.
				 *
				 *  \note This variable should be treated as read-only in the user application, and never manually
				 *        changed in value.
				 */
				extern volatile uint8_t USB_Options;
			#endif

		/* Throwable Events: */
			/** This module raises the \ref USB_Disconnect event if the USB interface is reset (such as during a mode
			 *  change while in UID mode) while the USB interface is connected to a device when in host mode, or
			 *  a host while in device mode.
			 *
			 *  \see Events.h for more information on this event.
			 */
			RAISES_EVENT(USB_Disconnect);
			
			#if defined(USB_CAN_BE_BOTH) || defined(__DOXYGEN__)
				/** This module raises the Power On Failure event when an error occurs while initializing the USB
				 *  interface.
				 *
				 *  \see Events.h for more information on this event.
				 */
				RAISES_EVENT(USB_InitFailure);
			#endif
			
	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define USB_PLL_On()               MACROS{ PLLCSR   =  USB_PLL_PSC; PLLCSR |= (1 << PLLE); }MACROE
			#define USB_PLL_Off()              MACROS{ PLLCSR   =  0;                           }MACROE
			#define USB_PLL_IsReady()                ((PLLCSR  &   (1 << PLOCK)) ? true : false)

			#if defined(USB_FULL_CONTROLLER) || defined(USB_MODIFIED_FULL_CONTROLLER)		
				#define USB_REG_On()           MACROS{ UHWCON  |=  (1 << UVREGE);               }MACROE
				#define USB_REG_Off()          MACROS{ UHWCON  &= ~(1 << UVREGE);               }MACROE
			#else
				#define USB_REG_On()           MACROS{ REGCR   &= ~(1 << REGDIS);               }MACROE
				#define USB_REG_Off()          MACROS{ REGCR   |=  (1 << REGDIS);               }MACROE			
			#endif
			
			#define USB_OTGPAD_On()            MACROS{ USBCON  |=  (1 << OTGPADE);              }MACROE
			#define USB_OTGPAD_Off()           MACROS{ USBCON  &= ~(1 << OTGPADE);              }MACROE

			#define USB_CLK_Freeze()           MACROS{ USBCON  |=  (1 << FRZCLK);               }MACROE
			#define USB_CLK_Unfreeze()         MACROS{ USBCON  &= ~(1 << FRZCLK);               }MACROE

			#define USB_Interface_Enable()     MACROS{ USBCON  |=  (1 << USBE);                 }MACROE
			#define USB_Interface_Disable()    MACROS{ USBCON  &= ~(1 << USBE);                 }MACROE
			#define USB_Interface_Reset()      MACROS{ uint8_t Temp = USBCON; USBCON = (Temp & ~(1 << USBE)); \
			                                           USBCON = (Temp | (1 << USBE));           }MACROE
	
		/* Inline Functions: */
			#if defined(USB_CAN_BE_BOTH)
			static inline uint8_t USB_GetUSBModeFromUID(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t USB_GetUSBModeFromUID(void)
			{
				if (USBSTA & (1 << ID))
				  return USB_MODE_DEVICE;
				else
				  return USB_MODE_HOST;
			}
			#endif
			
	#endif
	
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
			
#endif

/** @} */
