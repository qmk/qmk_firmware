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

volatile bool     IsSending;

#if !defined(PDI_VIA_HARDWARE_USART)
volatile uint16_t SoftUSART_Data;
volatile uint8_t  SoftUSART_BitCount;

ISR(TIMER0_COMPA_vect, ISR_BLOCK)
{
	/* Toggle CLOCK pin in a single cycle (see AVR datasheet) */
	BITBANG_PDICLOCK_PIN |= BITBANG_PDICLOCK_MASK;

	/* If not sending or receiving, just exit */
	if (!(SoftUSART_BitCount))
	  return;

	/* Check to see if the current clock state is on the rising or falling edge */
	bool IsRisingEdge = (BITBANG_PDICLOCK_PORT & BITBANG_PDICLOCK_MASK);

	if (IsSending && !IsRisingEdge)
	{
		if (SoftUSART_Data & 0x01)
		  BITBANG_PDIDATA_PORT |=  BITBANG_PDIDATA_MASK;
		else
		  BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;		  

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
	else if (!IsSending && IsRisingEdge)
	{
		/* Wait for the start bit when receiving */
		if ((SoftUSART_BitCount == BITS_IN_FRAME) && (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK))
		  return;
	
		if (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK)
		  SoftUSART_Data |= (1 << BITS_IN_FRAME);

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
}
#endif

void PDITarget_EnableTargetPDI(void)
{
#if defined(PDI_VIA_HARDWARE_USART)
	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);
	
	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	PORTD |= (1 << 3);
	asm volatile ("NOP"::);
	asm volatile ("NOP"::);
	
	/* Set up the synchronous USART for XMEGA communications - 
	   8 data bits, even parity, 2 stop bits */
	UBRR1  = 10;
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);

	/* Send two BREAKs of 12 bits each to enable PDI interface (need at least 16 idle bits) */
	PDITarget_SendBreak();
	PDITarget_SendBreak();
#else
	/* Set DATA and CLOCK lines to outputs */
	BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR |= BITBANG_PDICLOCK_MASK;
	
	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
	asm volatile ("NOP"::);
	asm volatile ("NOP"::);

	/* Fire timer compare ISR every 50 cycles to manage the software USART */
	OCR0A   = 50;
	TCCR0A  = (1 << WGM01);
	TCCR0B  = (1 << CS00);
	TIMSK0  = (1 << OCIE0A);
	
	PDITarget_SendBreak();
	PDITarget_SendBreak();
#endif
}

void PDITarget_DisableTargetPDI(void)
{
#if defined(PDI_VIA_HARDWARE_USART)
	/* Turn off receiver and transmitter of the USART, clear settings */
	UCSR1A |= (1 << TXC1) | (1 << RXC1);
	UCSR1B  = 0;
	UCSR1C  = 0;

	/* Set all USART lines as input, tristate */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));
#else
	/* Set DATA and CLOCK lines to inputs */
	BITBANG_PDIDATA_DDR   &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR  &= ~BITBANG_PDICLOCK_MASK;
	
	/* Tristate DATA and CLOCK lines */
	BITBANG_PDIDATA_PORT  &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_PORT &= ~BITBANG_PDICLOCK_MASK;

	TCCR0B  = 0;
#endif
}

void PDITarget_SendByte(uint8_t Byte)
{
#if defined(PDI_VIA_HARDWARE_USART)
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		PORTD  |=  (1 << 3);
		DDRD   |=  (1 << 3);

		UCSR1B &= ~(1 << RXEN1);
		UCSR1B |=  (1 << TXEN1);
		
		IsSending = true;
	}
	
	/* Wait until there is space in the hardware Tx buffer before writing */
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = Byte;
#else
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;

		IsSending = true;
	}

	bool    EvenParityBit = false;
	uint8_t ParityData    = Byte;

	/* Compute Even parity bit */
	for (uint8_t i = 0; i < 8; i++)
	{
		EvenParityBit ^= ParityData & 0x01;
		ParityData    >>= 1;
	}

	while (SoftUSART_BitCount);

	/* Data shifted out LSB first, START DATA PARITY STOP STOP */
	SoftUSART_Data     = ((uint16_t)EvenParityBit << 9) | ((uint16_t)Byte << 1) | (1 << 10) | (1 << 11);
	SoftUSART_BitCount = BITS_IN_FRAME;
#endif
}

uint8_t PDITarget_ReceiveByte(void)
{
#if defined(PDI_VIA_HARDWARE_USART)
	/* Switch to Rx mode if currently in Tx mode */
	if (IsSending)
	{
		while (!(UCSR1A & (1 << TXC1)));
		UCSR1A |=  (1 << TXC1);

		UCSR1B &= ~(1 << TXEN1);
		UCSR1B |=  (1 << RXEN1);

		DDRD   &= ~(1 << 3);
		PORTD  &= ~(1 << 3);
		
		IsSending = false;
	}

	/* Wait until a byte has been received before reading */
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
#else
	/* Switch to Rx mode if currently in Tx mode */
	if (IsSending)
	{
		while (SoftUSART_BitCount);

		BITBANG_PDIDATA_DDR  &= ~BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;

		IsSending = false;
	}

	/* Wait until a byte has been received before reading */
	SoftUSART_BitCount = BITS_IN_FRAME;
	while (SoftUSART_BitCount);
	
	/* Throw away the start, parity and stop bits to leave only the data */
	return (uint8_t)(SoftUSART_Data >> 1);
#endif
}

void PDITarget_SendBreak(void)
{
#if defined(PDI_VIA_HARDWARE_USART)
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		PORTD  |=  (1 << 3);
		DDRD   |=  (1 << 3);

		UCSR1B &= ~(1 << RXEN1);
		UCSR1B |=  (1 << TXEN1);
		
		IsSending = true;
	}

	/* Need to do nothing for a full frame to send a BREAK */
	for (uint8_t i = 0; i <= BITS_IN_FRAME; i++)
	{
		/* Wait for a full cycle of the clock */
		while (PIND & (1 << 5));
		while (!(PIND & (1 << 5)));
	}
#else
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;

		IsSending = true;
	}
	
	while (SoftUSART_BitCount);

	/* Need to do nothing for a full frame to send a BREAK */
	SoftUSART_Data     = 0x0FFF;
	SoftUSART_BitCount = BITS_IN_FRAME;
#endif
}

void PDITarget_SendAddress(uint32_t Address)
{
	PDITarget_SendByte(Address >> 24);
	PDITarget_SendByte(Address >> 26);
	PDITarget_SendByte(Address >> 8);
	PDITarget_SendByte(Address &  0xFF);
}

bool PDITarget_WaitWhileNVMBusBusy(void)
{
	uint8_t AttemptsRemaining = 255;

	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (AttemptsRemaining--)
	{
		PDITarget_SendByte(PDI_CMD_LDCS | PDI_STATUS_REG);
		if (PDITarget_ReceiveByte() & PDI_STATUS_NVM)
		  return true;
	}
	
	return false;
}

void PDITarget_WaitWhileNVMControllerBusy(void)
{
	/* Poll the NVM STATUS register to check to see if NVM controller is busy */
	for (;;)
	{
		PDITarget_SendByte(PDI_CMD_LDS | (PDI_DATSIZE_1BYTE << 2));
		PDITarget_SendAddress(DATAMEM_BASE | DATAMEM_NVM_BASE | 0x0F);
		
		if (!(PDITarget_ReceiveByte() & (1 << 7)))
		  return;
	}
}

#endif
