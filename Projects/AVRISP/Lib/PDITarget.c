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

#if defined(ENABLE_XPROG_PROTOCOL)

/** \file
 *
 *  Target-related functions for the PDI Protocol decoder.
 */

#define  INCLUDE_FROM_PDITARGET_C
#include "PDITarget.h"

void PDITarget_SendByte(uint8_t Byte)
{
	PDIDATA_LINE_PORT  &= ~PDIDATA_LINE_MASK;

	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;	

	for (uint8_t i = 0; i < 8; i++)
	{
		if (Byte & 0x01)
		  PDIDATA_LINE_PORT |= PDIDATA_LINE_MASK;
		else
		  PDIDATA_LINE_PORT &= ~PDIDATA_LINE_MASK;
		  
		Byte >>= 1;

		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;	
	}

	PDIDATA_LINE_PORT  |= PDIDATA_LINE_MASK;

	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
}

uint8_t PDITarget_ReceiveByte(void)
{
	uint8_t ReceivedByte = 0;

	PDIDATA_LINE_DDR   &= ~PDIDATA_LINE_MASK;

	bool FoundStartBit;

	do
	{
		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
		FoundStartBit = !(PDIDATA_LINE_PIN & PDIDATA_LINE_MASK);
	} while (!FoundStartBit);
	
	for (uint8_t i = 0; i < 8; i++)
	{
		if (PDIDATA_LINE_PIN & PDIDATA_LINE_MASK)
			ReceivedByte |= 0x01;

		ReceivedByte <<= 1;

		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
		PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;	
	}

	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	PDICLOCK_LINE_PORT ^= PDICLOCK_LINE_MASK;
	
	PDIDATA_LINE_DDR   |= PDIDATA_LINE_MASK;
	
	return ReceivedByte;
}

#endif
