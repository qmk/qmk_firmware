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

#if defined(ENABLE_PDI_PROTOCOL) || defined(__DOXYGEN__)

/** \file
 *
 *  Target-related functions for the PDI Protocol decoder.
 */

#define  INCLUDE_FROM_PDITARGET_C
#include "PDITarget.h"

/** Writes a given byte to the attached XMEGA device, using a RS232 frame via software through the
 *  PDI interface.
 *
 *  \param[in] Byte  Byte to send to the attached device
 */
void PDITarget_SendByte(uint8_t Byte)
{
	PDIDATA_LINE_PORT &= ~PDIDATA_LINE_MASK;

	TOGGLE_PDI_CLOCK;

	for (uint8_t i = 0; i < 8; i++)
	{
		if (Byte & 0x01)
		  PDIDATA_LINE_PORT |= PDIDATA_LINE_MASK;
		else
		  PDIDATA_LINE_PORT &= ~PDIDATA_LINE_MASK;
		  
		Byte >>= 1;

		TOGGLE_PDI_CLOCK;
	}

	PDIDATA_LINE_PORT |= PDIDATA_LINE_MASK;

	TOGGLE_PDI_CLOCK;
	TOGGLE_PDI_CLOCK;
}

/** Reads a given byte from the attached XMEGA device, encoded in a RS232 frame through the PDI interface.
 *
 *  \return Received byte from the attached device
 */
uint8_t PDITarget_ReceiveByte(void)
{
	uint8_t ReceivedByte = 0;

	PDIDATA_LINE_DDR &= ~PDIDATA_LINE_MASK;

	while (PDIDATA_LINE_PIN & PDIDATA_LINE_MASK);
	  TOGGLE_PDI_CLOCK;
	  
	for (uint8_t i = 0; i < 8; i++)
	{
		if (PDIDATA_LINE_PIN & PDIDATA_LINE_MASK)
			ReceivedByte |= 0x01;

		ReceivedByte <<= 1;

		TOGGLE_PDI_CLOCK;	
	}

	TOGGLE_PDI_CLOCK;
	TOGGLE_PDI_CLOCK;
	
	PDIDATA_LINE_DDR |= PDIDATA_LINE_MASK;
	
	return ReceivedByte;
}

#endif
