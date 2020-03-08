/*
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2019  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "../../../Common/Common.h"
#if (ARCH == ARCH_AVR8)

#define  __INCLUDE_FROM_SERIAL_C
#include "../Serial.h"

FILE USARTSerialStream;

int Serial_putchar(char DataByte,
                   FILE *Stream)
{
	(void)Stream;

	Serial_SendByte(DataByte);
	return 0;
}

int Serial_getchar(FILE *Stream)
{
	(void)Stream;

	if (!(Serial_IsCharReceived()))
	  return _FDEV_EOF;

	return Serial_ReceiveByte();
}

int Serial_getchar_Blocking(FILE *Stream)
{
	(void)Stream;

	while (!(Serial_IsCharReceived()));
	return Serial_ReceiveByte();
}

void Serial_SendString_P(const char* FlashStringPtr)
{
	uint8_t CurrByte;

	while ((CurrByte = pgm_read_byte(FlashStringPtr)) != 0x00)
	{
		Serial_SendByte(CurrByte);
		FlashStringPtr++;
	}
}

void Serial_SendString(const char* StringPtr)
{
	uint8_t CurrByte;

	while ((CurrByte = *StringPtr) != 0x00)
	{
		Serial_SendByte(CurrByte);
		StringPtr++;
	}
}

void Serial_SendData(const void* Buffer,
                     uint16_t Length)
{
	uint8_t* CurrByte = (uint8_t*)Buffer;

	while (Length--)
	  Serial_SendByte(*(CurrByte++));
}

void Serial_CreateStream(FILE* Stream)
{
	if (!(Stream))
	{
		Stream = &USARTSerialStream;
		stdin  = Stream;
		stdout = Stream;
	}

	*Stream = (FILE)FDEV_SETUP_STREAM(Serial_putchar, Serial_getchar, _FDEV_SETUP_RW);
}

void Serial_CreateBlockingStream(FILE* Stream)
{
	if (!(Stream))
	{
		Stream = &USARTSerialStream;
		stdin  = Stream;
		stdout = Stream;
	}

	*Stream = (FILE)FDEV_SETUP_STREAM(Serial_putchar, Serial_getchar_Blocking, _FDEV_SETUP_RW);
}

#endif
