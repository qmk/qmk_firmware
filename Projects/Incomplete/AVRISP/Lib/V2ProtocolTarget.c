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
 *  Target-related functions for the V2 Protocol decoder.
 */

#include "V2ProtocolTarget.h"

/** Current memory address for FLASH/EEPROM memory read/write commands */
uint32_t CurrentAddress;

/** Table of masks for SPI_Init() from a given PARAM_SCK_DURATION value */
static const uint8_t SPIMaskFromSCKDuration[] =
	{
		#if (F_CPU == 8000000)
		SPI_SPEED_FCPU_DIV_2,
		#endif
		SPI_SPEED_FCPU_DIV_2, SPI_SPEED_FCPU_DIV_4, SPI_SPEED_FCPU_DIV_8,
		SPI_SPEED_FCPU_DIV_16, SPI_SPEED_FCPU_DIV_32, SPI_SPEED_FCPU_DIV_64
		#if (F_CPU == 16000000)										
		, SPI_SPEED_FCPU_DIV_128
		#endif
	};
	

uint8_t V2Protocol_GetSPIPrescalerMask(void)
{
	uint8_t SCKDuration = V2Params_GetParameterValue(PARAM_SCK_DURATION);

	if (SCKDuration >= sizeof(SPIMaskFromSCKDuration))
	  SCKDuration = (sizeof(SPIMaskFromSCKDuration) - 1);
	  
	return SPIMaskFromSCKDuration[SCKDuration];
}

void V2Protocol_ChangeTargetResetLine(bool ResetTarget)
{
	if (ResetTarget)
	{
		RESET_LINE_DDR  |= RESET_LINE_MASK;
		
		if (!(V2Params_GetParameterValue(PARAM_RESET_POLARITY)))
		  RESET_LINE_PORT |= RESET_LINE_MASK;
	}
	else
	{
		RESET_LINE_PORT &= ~RESET_LINE_MASK;	
		RESET_LINE_DDR  &= ~RESET_LINE_MASK;
	}
}

void V2Protocol_DelayMS(uint8_t MS)
{
	while (MS--)
	  _delay_ms(1);
}

uint8_t V2Protocol_WaitWhileTargetBusy(void)
{
	uint8_t TimeoutMS = TARGET_BUSY_TIMEOUT_MS;
	uint8_t ResponseByte;
	
	do
	{
		V2Protocol_DelayMS(1);
	
		SPI_SendByte(0xF0);
		SPI_SendByte(0x00);

		SPI_SendByte(0x00);
		ResponseByte = SPI_ReceiveByte();
	}
	while ((ResponseByte & 0x01) && (TimeoutMS--));

	if (!(TimeoutMS))
	  return STATUS_CMD_TOUT;
	else
	  return STATUS_CMD_OK;
}

void V2Protocol_LoadExtendedAddress(void)
{
	SPI_SendByte(0x4D);
	SPI_SendByte(0x00);
	SPI_SendByte((CurrentAddress & 0x00FF0000) >> 16);
	SPI_SendByte(0x00);	
}
