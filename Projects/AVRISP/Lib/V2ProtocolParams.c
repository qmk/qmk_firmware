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
 *  V2Protocol parameter handler, to process V2 Protocol device parameters.
 */

#define  INCLUDE_FROM_V2PROTOCOL_PARAMS_C
#include "V2ProtocolParams.h"

/* Non-Volatile Parameter Values for EEPROM storage */
uint8_t EEMEM EEPROM_Rest_Polarity = 0x00;

/* Volatile Parameter Values for RAM storage */
static ParameterItem_t ParameterTable[] = 
	{
		{ .ParamID          = PARAM_BUILD_NUMBER_LOW,
		  .ParamValue       = (LUFA_VERSION_INTEGER >> 8),
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_BUILD_NUMBER_HIGH,
		  .ParamValue       = (LUFA_VERSION_INTEGER & 0xFF),
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_HW_VER,
		  .ParamValue       = 0x00,
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_SW_MAJOR,
		  .ParamValue       = 0x01,
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_SW_MINOR,
		  .ParamValue       = 0x0C,
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_VTARGET,
		  .ParamValue       = 0x32,
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_SCK_DURATION,
		  .ParamValue       = (TOTAL_PROGRAMMING_SPEEDS - 1),
		  .ParamPrivellages = PARAM_PRIV_READ | PARAM_PRIV_WRITE },

		{ .ParamID          = PARAM_RESET_POLARITY,
		  .ParamValue       = 0x00,
		  .ParamPrivellages = PARAM_PRIV_WRITE                   },

		{ .ParamID          = PARAM_STATUS_TGT_CONN,
		  .ParamValue       = 0x00,
		  .ParamPrivellages = PARAM_PRIV_READ                    },

		{ .ParamID          = PARAM_DISCHARGEDELAY,
		  .ParamValue       = 0x00,
		  .ParamPrivellages = PARAM_PRIV_WRITE                   },
	};


/** Loads saved non-volatile parameter values from the EEPROM into the parameter table, as needed. */
void V2Params_LoadNonVolatileParamValues(void)
{
	/* Target RESET line polarity is a non-volatile value, retrieve current parameter value from EEPROM -
	 *   NB: Cannot call V2Protocol_SetParameterValue() here, as that will cause another EEPROM write!
	 */
	V2Params_GetParamFromTable(PARAM_RESET_POLARITY)->ParamValue = eeprom_read_byte(&EEPROM_Rest_Polarity);
}

/** Updates any parameter values that are sourced from hardware rather than explicitly set by the host, such as
 *  VTARGET levels from the ADC on supported AVR models.
 */
void V2Params_UpdateParamValues(void)
{
	#if defined(ADC)
	/* Update VTARGET parameter with the latest ADC conversion of VTARGET on supported AVR models */
	V2Params_GetParamFromTable(PARAM_VTARGET)->ParamValue = ((5 * 10 * ADC_GetResult()) / 1024);
	#endif
}

/** Retrieves the host PC read/write privellages for a given parameter in the parameter table. This should
 *  be called before calls to \ref V2Params_GetParameterValue() or \ref V2Params_SetParameterValue() when
 *  getting or setting parameter values in response to requests from the host.
 *
 *  \param ParamID  Parameter ID whose privellages are to be retrieved from the table
 *
 *  \return Privellages for the requested parameter, as a mask of PARAM_PRIV_* masks
 */ 
uint8_t V2Params_GetParameterPrivellages(uint8_t ParamID)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);
	
	if (ParamInfo == NULL)
	  return 0;

	return ParamInfo->ParamPrivellages;
}

/** Retrieves the current value for a given parameter in the parameter table.
 *
 *  \param ParamID  Parameter ID whose value is to be retrieved from the table
 *
 *  \return Current value of the parameter in the table, or 0 if not found
 */ 
uint8_t V2Params_GetParameterValue(uint8_t ParamID)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);
	
	if (ParamInfo == NULL)
	  return 0;
	
	return ParamInfo->ParamValue;
}

/** Sets the value for a given parameter in the parameter table.
 *
 *  \param ParamID  Parameter ID whose value is to be set in the table
 *  \param Value  New value to set the parameter to
 *
 *  \return Pointer to the associated parameter information from the parameter table if found, NULL otherwise
 */
void V2Params_SetParameterValue(uint8_t ParamID, uint8_t Value)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);

	if (ParamInfo == NULL)
	  return;

	ParamInfo->ParamValue = Value;

	/* The target RESET line polarity is a non-volatile parameter, save to EEPROM when changed */
	if (ParamID == PARAM_RESET_POLARITY)
	  eeprom_write_byte(&EEPROM_Rest_Polarity, Value);  
}

/** Retrieves a parameter entry (including ID, value and privellages) from the parameter table that matches the given
 *  parameter ID.
 *
 *  \param ParamID  Parameter ID to find in the table
 *
 *  \return Pointer to the associated parameter information from the parameter table if found, NULL otherwise
 */
static ParameterItem_t* V2Params_GetParamFromTable(uint8_t ParamID)
{
	/* Find the parameter in the parameter table if present */
	for (uint8_t TableIndex = 0; TableIndex < (sizeof(ParameterTable) / sizeof(ParameterTable[0])); TableIndex++)
	{
		if (ParamID == ParameterTable[TableIndex].ParamID)
		  return &ParameterTable[TableIndex];
	}
	
	return NULL;
}
