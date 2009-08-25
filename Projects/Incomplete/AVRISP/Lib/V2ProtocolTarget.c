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

uint8_t V2Protocol_GetSPIPrescalerMask(void)
{
	static const uint8_t SPIMaskFromSCKDuration[TOTAL_PROGRAMMING_SPEEDS] =
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

uint8_t V2Protocol_WaitForProgComplete(uint8_t ProgrammingMode, uint16_t PollAddress, uint8_t PollValue,
                                       uint8_t DelayMS, uint8_t ReadMemCommand)
{
	uint8_t ProgrammingStatus = STATUS_CMD_OK;

	/* Determine method of Programming Complete check */
	switch (ProgrammingMode & ~(PROG_MODE_PAGED_WRITES_MASK | PROG_MODE_COMMIT_PAGE_MASK))
	{
		case PROG_MODE_WORD_TIMEDELAY_MASK:
		case PROG_MODE_PAGED_TIMEDELAY_MASK:
			V2Protocol_DelayMS(DelayMS);
			break;
		case PROG_MODE_WORD_VALUE_MASK:
		case PROG_MODE_PAGED_VALUE_MASK:
			TCNT0 = 0;

			do
			{
				SPI_SendByte(ReadMemCommand);
				SPI_SendByte(PollAddress >> 8);
				SPI_SendByte(PollAddress & 0xFF);				
			}
			while ((SPI_TransferByte(0x00) != PollValue) && (TCNT0 < TARGET_BUSY_TIMEOUT_MS));

			if (TCNT0 >= TARGET_BUSY_TIMEOUT_MS)
			 ProgrammingStatus = STATUS_RDY_BSY_TOUT;
			
			break;		
		case PROG_MODE_WORD_READYBUSY_MASK:
		case PROG_MODE_PAGED_READYBUSY_MASK:
			ProgrammingStatus = V2Protocol_WaitWhileTargetBusy();
			break;
	}

	return ProgrammingStatus;
}

uint8_t V2Protocol_WaitWhileTargetBusy(void)
{
	TCNT0 = 0;
	
	do
	{
		SPI_SendByte(0xF0);
		SPI_SendByte(0x00);

		SPI_SendByte(0x00);
	}
	while ((SPI_ReceiveByte() & 0x01) && (TCNT0 < TARGET_BUSY_TIMEOUT_MS));

	if (TCNT0 >= TARGET_BUSY_TIMEOUT_MS)
	  return STATUS_RDY_BSY_TOUT;
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
