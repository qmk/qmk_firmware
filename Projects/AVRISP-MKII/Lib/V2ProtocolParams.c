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
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = (LUFA_VERSION_INTEGER >> 8)        },

		{ .ParamID          = PARAM_BUILD_NUMBER_HIGH,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = (LUFA_VERSION_INTEGER & 0xFF),     },

		{ .ParamID          = PARAM_HW_VER,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = 0x00                               },

		{ .ParamID          = PARAM_SW_MAJOR,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = 0x01                               },

		{ .ParamID          = PARAM_SW_MINOR,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = 0x0D                               },

		{ .ParamID          = PARAM_VTARGET,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = 0x32                               },

		{ .ParamID          = PARAM_SCK_DURATION,
		  .ParamPrivileges  = PARAM_PRIV_READ | PARAM_PRIV_WRITE,
		  .ParamValue       = (TOTAL_ISP_PROGRAMMING_SPEEDS - 1) },

		{ .ParamID          = PARAM_RESET_POLARITY,
		  .ParamPrivileges  = PARAM_PRIV_WRITE,
		  .ParamValue       = 0x00                               },

		{ .ParamID          = PARAM_STATUS_TGT_CONN,
		  .ParamPrivileges  = PARAM_PRIV_READ,
		  .ParamValue       = STATUS_ISP_READY                   },

		{ .ParamID          = PARAM_DISCHARGEDELAY,
		  .ParamPrivileges  = PARAM_PRIV_WRITE,
		  .ParamValue       = 0x00                               },
	};


/** Loads saved non-volatile parameter values from the EEPROM into the parameter table, as needed. */
void V2Params_LoadNonVolatileParamValues(void)
{
	/* Target RESET line polarity is a non-volatile value, retrieve current parameter value from EEPROM -
	 *   NB: Cannot call V2Protocol_SetParameterValue() here, as that will cause another EEPROM write! */
	V2Params_GetParamFromTable(PARAM_RESET_POLARITY)->ParamValue = eeprom_read_byte(&EEPROM_Rest_Polarity);
}

/** Updates any parameter values that are sourced from hardware rather than explicitly set by the host, such as
 *  VTARGET levels from the ADC on supported AVR models.
 */
void V2Params_UpdateParamValues(void)
{
	#if (defined(ADC) && !defined(NO_VTARGET_DETECT))
	/* Update VTARGET parameter with the latest ADC conversion of VTARGET on supported AVR models */
	V2Params_GetParamFromTable(PARAM_VTARGET)->ParamValue = ((5 * 10 * ADC_GetResult()) / 1024);
	#endif
}

/** Retrieves the host PC read/write privileges for a given parameter in the parameter table. This should
 *  be called before calls to \ref V2Params_GetParameterValue() or \ref V2Params_SetParameterValue() when
 *  getting or setting parameter values in response to requests from the host.
 *
 *  \param[in] ParamID  Parameter ID whose privileges are to be retrieved from the table
 *
 *  \return Privileges for the requested parameter, as a mask of PARAM_PRIV_* masks
 */ 
uint8_t V2Params_GetParameterPrivileges(const uint8_t ParamID)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);
	
	if (ParamInfo == NULL)
	  return 0;

	return ParamInfo->ParamPrivileges;
}

/** Retrieves the current value for a given parameter in the parameter table.
 *
 *  \param[in] ParamID  Parameter ID whose value is to be retrieved from the table
 *
 *  \return Current value of the parameter in the table, or 0 if not found
 */ 
uint8_t V2Params_GetParameterValue(const uint8_t ParamID)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);
	
	if (ParamInfo == NULL)
	  return 0;
	
	return ParamInfo->ParamValue;
}

/** Sets the value for a given parameter in the parameter table.
 *
 *  \param[in] ParamID  Parameter ID whose value is to be set in the table
 *  \param[in] Value    New value to set the parameter to
 *
 *  \return Pointer to the associated parameter information from the parameter table if found, NULL otherwise
 */
void V2Params_SetParameterValue(const uint8_t ParamID, const uint8_t Value)
{
	ParameterItem_t* ParamInfo = V2Params_GetParamFromTable(ParamID);

	if (ParamInfo == NULL)
	  return;

	ParamInfo->ParamValue = Value;

	/* The target RESET line polarity is a non-volatile parameter, save to EEPROM when changed */
	if (ParamID == PARAM_RESET_POLARITY)
	  eeprom_write_byte(&EEPROM_Rest_Polarity, Value);  
}

/** Retrieves a parameter entry (including ID, value and privileges) from the parameter table that matches the given
 *  parameter ID.
 *
 *  \param[in] ParamID  Parameter ID to find in the table
 *
 *  \return Pointer to the associated parameter information from the parameter table if found, NULL otherwise
 */
static ParameterItem_t* V2Params_GetParamFromTable(const uint8_t ParamID)
{
	ParameterItem_t* CurrTableItem = ParameterTable;

	/* Find the parameter in the parameter table if present */
	for (uint8_t TableIndex = 0; TableIndex < TABLE_PARAM_COUNT; TableIndex++)
	{
		if (ParamID == CurrTableItem->ParamID)
		  return CurrTableItem;
		
		CurrTableItem++;
	}

	return NULL;
}
