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
 *  This file is the master dispatch header file for the device-specific ADC driver, for AVRs containing an ADC.
 *
 *  User code should include this file, which will in turn include the correct ADC driver header file for the
 *  currently selected AVR model.
 */

/** \ingroup Group_SubsystemDrivers
 *  @defgroup Group_ADC ADC Driver - LUFA/Drivers/AT90USBXXX/ADC.h
 */
 
#ifndef __ADC_H__
#define __ADC_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_ADC_H
		#define INCLUDE_FROM_CHIP_DRIVER
	#endif

	/* Includes: */
		#if (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || \
		     defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB647__) || \
			 defined(__AVR_ATmega16U4__)  || defined(__AVR_ATmega32U4__) || \
			 defined(__AVR_ATmega32U6__))
			#include "AT90USBXXX67/ADC.h"
		#else
			#error "ADC is not available for the currently selected AVR model."
		#endif

	/* Public Interface - May be used in end-application: */
		/* Inline Functions: */
			/** Starts the reading of the given channel, but does not wait until the conversion has completed.
			 *  Once executed, the conversion status can be determined via the ADC_IsReadingComplete() macro and
			 *  the result read via the ADC_GetResult() macro.
			 *
			 *  \param MUXMask  Mask comprising of an ADC channel number, reference mask and adjustment mask
			 */
			static inline void ADC_StartReading(const uint8_t MUXMask);

			/** Performs a complete single reading from channel, including a polling spinloop to wait for the
			 *  conversion to complete, and the returning of the converted value.
			 *
			 *  \param MUXMask  Mask comprising of an ADC channel number, reference mask and adjustment mask
			 */
			static inline uint16_t ADC_GetChannelReading(const uint8_t MUXMask) ATTR_WARN_UNUSED_RESULT;

			/** Configures the given ADC channel, ready for ADC conversions. This function sets the
			 *  associated port pin as an input and disables the digital portion of the I/O to reduce
			 *  power consumption.
			 *
			 *  \param Channel  ADC channel number to set up for conversions
			 */
			static inline void ADC_SetupChannel(const uint8_t Channel);
			
#endif
