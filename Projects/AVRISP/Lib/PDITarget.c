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

#if !defined(PDI_VIA_HARDWARE_USART)
volatile bool     IsSending;
volatile uint16_t DataBits;
volatile uint8_t  BitCount;

ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	BITBANG_PDICLOCK_PORT ^= BITBANG_PDICLOCK_MASK;

	/* If not sending or receiving, just exit */
	if (!(BitCount))
	  return;
	
	/* Check to see if the current clock state is on the rising or falling edge */
	bool IsRisingEdge = (BITBANG_PDICLOCK_PORT & BITBANG_PDICLOCK_MASK);

	if (IsSending && !IsRisingEdge)
	{
		if (DataBits & 0x01)
		  BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;
		else
		  BITBANG_PDIDATA_PORT |=  BITBANG_PDIDATA_MASK;		  

		DataBits >>= 1;
		BitCount--;
	}
	else if (!IsSending && IsRisingEdge)
	{
		/* Wait for the start bit when receiving */
		if ((BitCount == BITS_IN_FRAME) && (BITBANG_PDIDATA_PORT & BITBANG_PDIDATA_MASK))
		  return;
	
		if (BITBANG_PDIDATA_PORT & BITBANG_PDIDATA_MASK)
		  DataBits |= (1 << (BITS_IN_FRAME - 1));

		DataBits >>= 1;
		BitCount--;
	}
}

void PDITarget_EnableTargetPDI(void)
{
	/* Set DATA and CLOCK lines to outputs */
	BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR |= BITBANG_PDICLOCK_MASK;
	
	/* Set DATA line high for 90ns to disable /RESET functionality */
	BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
	asm volatile ("NOP"::);
	asm volatile ("NOP"::);

	/* Fire timer compare ISR every 160 cycles */
	OCR0A   = 20;
	TCCR0A  = (1 << WGM01);
	TCCR0B  = (1 << CS01);
	TIMSK0  = (1 << OCIE0A);
}

void PDITarget_DisableTargetPDI(void)
{
	/* Set DATA and CLOCK lines to inputs */
	BITBANG_PDIDATA_DDR   &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR  &= ~BITBANG_PDICLOCK_MASK;
	
	/* Tristate DATA and CLOCK lines */
	BITBANG_PDIDATA_PORT  &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_PORT &= ~BITBANG_PDICLOCK_MASK;

	TCCR0B  = 0;
}

void PDITarget_SendByte(uint8_t Byte)
{
	bool IsOddBitsSet = false;
	
	/* Compute Even parity bit */
	for (uint8_t i = 0; i < 8; i++)
	{
		if (Byte & (1 << i))
		  IsOddBitsSet = !(IsOddBitsSet);
	}

	/* Data shifted out LSB first, START DATA PARITY STOP STOP */
	DataBits  = ((uint16_t)IsOddBitsSet << 10) | ((uint16_t)Byte << 1) | (1 << 0);

	BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
	BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;

	IsSending = true;
	BitCount  = BITS_IN_FRAME;
	while (BitCount);

	BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDIDATA_DDR  &= ~BITBANG_PDIDATA_MASK;
}

uint8_t PDITarget_ReceiveByte(void)
{
	IsSending = false;
	BitCount  = BITS_IN_FRAME;
	while (BitCount);

	return (DataBits >> 1);
}

void PDITarget_SendBreak(void)
{
	DataBits  = 0;

	BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
	BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;

	IsSending = true;
	BitCount  = BITS_IN_FRAME;
	while (BitCount);

	BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDIDATA_DDR  &= ~BITBANG_PDIDATA_MASK;
}
#else
void PDITarget_EnableTargetPDI(void)
{
	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);
	
	/* Set DATA line high for 90ns to disable /RESET functionality */
	PORTD |= (1 << 3);
	asm volatile ("NOP"::);
	asm volatile ("NOP"::);
	
	/* Set up the synchronous USART for XMEGA communications - 
	   8 data bits, even parity, 2 stop bits */
	UBRR1  = 10;
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);

	/* Send two BREAKs of 12 bits each to enable PDI interface (need at least 16 idle bits) */
	PDITarget_SendBreak();
	PDITarget_SendBreak();
}

void PDITarget_DisableTargetPDI(void)
{
	/* Turn of receiver and transmitter of the USART, clear settings */
	UCSR1B = 0;
	UCSR1C = 0;

	/* Set all USART lines as input, tristate */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));
}

void PDITarget_SendByte(uint8_t Byte)
{
	UCSR1B &= ~(1 << RXEN1);
	UCSR1B |=  (1 << TXEN1);

	UDR1 = Byte;

	while (!(UCSR1A & (1 << TXC1)));
	UCSR1A |=  (1 << TXC1);
}

uint8_t PDITarget_ReceiveByte(void)
{
	UCSR1B &= ~(1 << TXEN1);
	UCSR1B |=  (1 << RXEN1);

	while (!(UCSR1A & (1 << RXC1)));
	UCSR1A |=  (1 << RXC1);
	
	return UDR1;
}

void PDITarget_SendBreak(void)
{
	UCSR1B &= ~(1 << RXEN1);
	UCSR1B |=  (1 << TXEN1);

	for (uint8_t i = 0; i <= BITS_IN_FRAME; i++)
	{
		/* Wait for rising edge of clock */
		while (PIND & (1 << 5));
		
		/* Wait for falling edge of clock */
		while (!(PIND & (1 << 5)));
	}
}
#endif

#endif
