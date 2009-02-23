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

#ifndef __USBMODE_H__
#define __USBMODE_H__

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#if ((defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) ||   \
			      defined(__AVR_AT90USB162__)  || defined(__AVR_AT90USB82__)  ||   \
				  defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) ||   \
				  defined(__AVR_ATmega32U6__)) && !defined(USB_DEVICE_ONLY))
				#define USB_DEVICE_ONLY
			#endif
			
			#if (defined(__AVR_AT90USB162__)  || defined(__AVR_AT90USB82__))
				#define USB_LIMITED_CONTROLLER
			#elif (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
				#define USB_MODIFIED_FULL_CONTROLLER
			#else
				#define USB_FULL_CONTROLLER
			#endif			

			#if (!defined(USB_DEVICE_ONLY) && !defined(USB_HOST_ONLY))
				#define USB_CAN_BE_BOTH
				#define USB_CAN_BE_HOST
				#define USB_CAN_BE_DEVICE
			#elif defined(USB_HOST_ONLY)
				#define USB_CAN_BE_HOST
				#define USB_CurrentMode USB_MODE_HOST
			#elif defined(USB_DEVICE_ONLY)
				#define USB_CAN_BE_DEVICE
				#define USB_CurrentMode USB_MODE_DEVICE
			#endif
			
			#if (defined(USB_HOST_ONLY) && defined(USB_DEVICE_ONLY))
				#error USB_HOST_ONLY and USB_DEVICE_ONLY are mutually exclusive.
			#endif

			#if (defined(USB_RAM_DESCRIPTORS) && defined(USE_EEPROM_DESCRIPTORS))
				#error USB_RAM_DESCRIPTORS and USE_EEPROM_DESCRIPTORS are mutually exclusive.
			#endif

			#if defined(USE_STATIC_OPTIONS)
				#define USB_Options USE_STATIC_OPTIONS
			#endif
	#endif
	
#endif
