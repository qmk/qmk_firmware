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

#include "Serial.h"

void Serial_Init(const uint32_t BaudRate, const bool DoubleSpeed)
{
	UCSR1A = ((DoubleSpeed) ? (1 << U2X1) : 0);
	UCSR1B = ((1 << RXEN1)  | (1 << TXEN1));
	UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10));
	
	DDRD  |= (1 << 3);	
	PORTD |= (1 << 2);
	
	UBRR1  = SERIAL_UBBRVAL(BaudRate);
}

void Serial_TxString_P(const char *FlashStringPtr)
{
	uint8_t CurrByte;

	while ((CurrByte = pgm_read_byte(FlashStringPtr)) != 0x00)
	{
		Serial_TxByte(CurrByte);
		FlashStringPtr++;
	}
}

void Serial_TxString(const char *StringPtr)
{
	uint8_t CurrByte;

	while ((CurrByte = *StringPtr) != 0x00)
	{
		Serial_TxByte(CurrByte);
		StringPtr++;
	}
}
