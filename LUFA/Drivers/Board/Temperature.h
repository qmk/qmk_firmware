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
 *  Temperature sensor board driver for the USB boards which contain a temperature sensor.
 */

/** \ingroup Group_BoardDrivers
 *  @defgroup Group_Temperature Temperature Driver - LUFA/Drivers/Board/Temperature.h
 *
 *  \section Sec_Dependencies Module Source Dependencies
 *  The following files must be built with any user project that uses this module:
 *    - LUFA/Drivers/Board/Temperature.c
 *
 *  \section Module Description
 *  Functions, macros, variables, enums and types related to the control of board temperature sensors.
 *
 *  @{
 */

#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

	/* Macros: */
	#if !defined(__DOXYGEN__)
		#define INCLUDE_FROM_BOARD_DRIVER
	#endif
	
	/* Includes: */
		#include <avr/pgmspace.h>

		#include "../../Common/Common.h"
		#include "../Peripheral/ADC.h"
	
		#if !defined(BOARD)
			#error #error BOARD must be set in makefile to a value specified in BoardTypes.h.	
		#elif (BOARD != BOARD_USBKEY) && (BOARD != BOARD_STK525) && (BOARD != BOARD_STK526)
			#error The selected board does not contain a temperature sensor.
		#endif

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** ADC channel number for the temperature sensor. */
			#define TEMP_ADC_CHANNEL   0
			
			/** Minimum returnable temperature from the Temperature_GetTemperature() function. */
			#define TEMP_MIN_TEMP      TEMP_TABLE_OFFSET

			/** Maximum returnable temperature from the Temperature_GetTemperature() function. */
			#define TEMP_MAX_TEMP      ((TEMP_TABLE_SIZE - 1) + TEMP_TABLE_OFFSET)
		
		/* Psuedo-Functions: */
			#if defined(__DOXYGEN__)
				/** Initializes the temperature sensor driver, including setting up the appropriate ADC channel.
				 *  This must be called before any other temperature sensor routines.
				 *
				 *  The ADC itself (not the ADC channel) must be configured separately before calling the temperature
				 *  sensor functions.
				 */
				static inline void Temperature_Init(void);
			#else
				#define Temperature_Init() ADC_SetupChannel(TEMP_ADC_CHANNEL);
			#endif

		/* Function Prototypes: */
			/** Performs a complete ADC on the temperature sensor channel, and converts the result into a
			 *  valid temperature between TEMP_MIN_TEMP and TEMP_MAX_TEMP in degrees Celsius.
			 *
			 *  \return Signed temperature in degrees Celsius
			 */
			int8_t Temperature_GetTemperature(void) ATTR_WARN_UNUSED_RESULT;

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define TEMP_TABLE_SIZE   (sizeof(Temperature_Lookup) / sizeof(Temperature_Lookup[0]))
			#define TEMP_TABLE_OFFSET -21
	#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
