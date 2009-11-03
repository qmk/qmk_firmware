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

/** \ingroup Group_PeripheralDrivers
 *  @defgroup Group_ADC ADC Driver - LUFA/Drivers/Peripheral/ADC.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - None
 *
 *  \section Module Description
 *  Hardware ADC driver. This module provides an easy to use driver for the hardware
 *  ADC present on many AVR models, for the conversion of analogue signals into the
 *  digital domain.
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
			#include "AVRU4U6U7/ADC.h"
		#else
			#error "ADC is not available for the currently selected AVR model."
		#endif
			
#endif
