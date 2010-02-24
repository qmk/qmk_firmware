/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \ingroup Group_USB
 *  @defgroup Group_USBMode USB Mode Tokens
 *
 *  After the inclusion of the master USB driver header, one or more of the following
 *  tokens may be defined, to allow the user code to conditionally enable or disable
 *  code based on the USB controller family and allowable USB modes. These tokens may
 *  be tested against to eliminate code relating to a USB mode which is not enabled for
 *  the given compilation.
 *
 *  @{
 */

#ifndef __USBMODE_H__
#define __USBMODE_H__

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_USB_DRIVER)
			#error Do not include this file directly. Include LUFA/Drivers/USB/USB.h instead.
		#endif
		
	/* Public Interface - May be used in end-application: */
	#if defined(__DOXYGEN__)
		/** Indicates that the target AVR microcontroller belongs to the Series 2 USB controller
		 *  (i.e. AT90USBXXX2 or ATMEGAXXU2) when defined.
		 */
		#define USB_SERIES_2_AVR

		/** Indicates that the target AVR microcontroller belongs to the Series 4 USB controller
		 *  (i.e. ATMEGAXXU4) when defined.
		 */
		#define USB_SERIES_4_AVR

		/** Indicates that the target AVR microcontroller belongs to the Series 6 USB controller
		 *  (i.e. AT90USBXXX6) when defined.
		 */
		#define USB_SERIES_6_AVR

		/** Indicates that the target AVR microcontroller belongs to the Series 7 USB controller
		 *  (i.e. AT90USBXXX7) when defined.
		 */
		#define USB_SERIES_7_AVR

		/** Indicates that the target AVR microcontroller and compilation settings allow for the
		 *  target to be configured in USB Device mode when defined.
		 */
		#define USB_CAN_BE_DEVICE

		/** Indicates that the target AVR microcontroller and compilation settings allow for the
		 *  target to be configured in USB Host mode when defined.
		 */
		#define USB_CAN_BE_HOST

		/** Indicates that the target AVR microcontroller and compilation settings allow for the
		 *  target to be configured in either USB Device or Host mode when defined.
		 */
		#define USB_CAN_BE_BOTH
	#else
		/* Macros: */			
			#if (defined(__AVR_AT90USB162__) || defined(__AVR_AT90USB82__)  || \
			     defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega8U2__))
				#define USB_SERIES_2_AVR
			#elif (defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__))
				#define USB_SERIES_4_AVR
			#elif (defined(__AVR_ATmega32U6__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__))
				#define USB_SERIES_6_AVR
			#elif (defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1287__))
				#define USB_SERIES_7_AVR
			#endif			

			#if !defined(USB_SERIES_7_AVR)		
				#if defined(USB_HOST_ONLY)
					#error USB_HOST_ONLY is not available for the currently selected USB AVR model.
				#endif
				
				#if !defined(USB_DEVICE_ONLY)
					#define USB_DEVICE_ONLY
				#endif
			#endif

			#if (!defined(USB_DEVICE_ONLY) && !defined(USB_HOST_ONLY))
				#define USB_CAN_BE_BOTH
				#define USB_CAN_BE_HOST
				#define USB_CAN_BE_DEVICE
			#elif defined(USB_HOST_ONLY)
				#define USB_CAN_BE_HOST
			#elif defined(USB_DEVICE_ONLY)
				#define USB_CAN_BE_DEVICE
			#endif
			
			#if (defined(USB_HOST_ONLY) && defined(USB_DEVICE_ONLY))
				#error USB_HOST_ONLY and USB_DEVICE_ONLY are mutually exclusive.
			#endif
	#endif
	
#endif

/** @} */