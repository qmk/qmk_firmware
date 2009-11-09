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
 *  Header file for V2ProtocolParams.c.
 */

#ifndef _V2_PROTOCOL_PARAMS_
#define _V2_PROTOCOL_PARAMS_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/eeprom.h>

		#include <LUFA/Version.h>

		#if defined(ADC)
			#include <LUFA/Drivers/Peripheral/ADC.h>
		#endif
		
		#include "V2Protocol.h"
		#include "V2ProtocolConstants.h"

	/* Macros: */
		/** Parameter privilege mask to allow the host PC to read the parameter's value */
		#define PARAM_PRIV_READ   (1 << 0)

		/** Parameter privilege mask to allow the host PC to change the parameter's value */
		#define PARAM_PRIV_WRITE  (1 << 1)

	/* Type Defines: */
		/** Type define for a parameter table entry indicating a PC readable or writable device parameter. */
		typedef struct
		{
			const uint8_t ParamID; /**< Parameter ID number to uniquely identify the parameter within the device */
			uint8_t ParamValue; /**< Current parameter's value within the device */
			uint8_t ParamPrivileges;  /**< Parameter privileges to allow the host to read or write the parameter's value */
		} ParameterItem_t;

	/* Function Prototypes: */
		void    V2Params_LoadNonVolatileParamValues(void);
		void    V2Params_UpdateParamValues(void);
	
		uint8_t V2Params_GetParameterPrivileges(uint8_t ParamID);
		uint8_t V2Params_GetParameterValue(uint8_t ParamID);
		void    V2Params_SetParameterValue(uint8_t ParamID, uint8_t Value);
		
		#if defined(INCLUDE_FROM_V2PROTOCOL_PARAMS_C)
			static ParameterItem_t* V2Params_GetParamFromTable(uint8_t ParamID);
		#endif

#endif

