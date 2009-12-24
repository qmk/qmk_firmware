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
 *  Target-related functions for the PDI Protocol decoder.
 */

#define  INCLUDE_FROM_PDITARGET_C
#include "PDITarget.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Flag to indicate if the USART is currently in Tx or Rx mode. */
volatile bool               IsSending;

#if !defined(XPROG_VIA_HARDWARE_USART)
/** Software USART raw frame bits for transmission/reception. */
volatile uint16_t           SoftUSART_Data;

/** Bits remaining to be sent or received via the software USART - set as a GPIOR for speed. */
#define SoftUSART_BitCount  GPIOR2


/** ISR to manage the software USART when bit-banged USART mode is selected. */
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	/* Toggle CLOCK pin in a single cycle (see AVR datasheet) */
	BITBANG_PDICLOCK_PIN |= BITBANG_PDICLOCK_MASK;

	/* If not sending or receiving, just exit */
	if (!(SoftUSART_BitCount))
	  return;

	/* Check to see if we are at a rising or falling edge of the clock */
	if (BITBANG_PDICLOCK_PORT & BITBANG_PDICLOCK_MASK)
	{
		/* If at rising clock edge and we are in send mode, abort */
		if (IsSending)
		  return;
		  
		/* Wait for the start bit when receiving */
		if ((SoftUSART_BitCount == BITS_IN_PDI_FRAME) && (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK))
		  return;
	
		/* Shift in the bit one less than the frame size in position, so that the start bit will eventually
		 * be discarded leaving the data to be byte-aligned for quick access */
		if (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK)
		  SoftUSART_Data |= (1 << (BITS_IN_PDI_FRAME - 1));

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
	else
	{
		/* If at falling clock edge and we are in receive mode, abort */
		if (!IsSending)
		  return;

		/* Set the data line to the next bit value */
		if (SoftUSART_Data & 0x01)
		  BITBANG_PDIDATA_PORT |=  BITBANG_PDIDATA_MASK;
		else
		  BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;		  

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
}
#endif

/** Enables the target's PDI interface, holding the target in reset until PDI mode is exited. */
void PDITarget_EnableTargetPDI(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);
	
	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	PORTD |= (1 << 3);
	asm volatile ("NOP"::);
	asm volatile ("NOP"::);
	
	/* Set up the synchronous USART for XMEGA communications - 
	   8 data bits, even parity, 2 stop bits */
	UBRR1  = (F_CPU / 1000000UL);
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

	/* Fire timer compare ISR every 100 cycles to manage the software USART */
	OCR1A   = 80;
	TCCR1B  = (1 << WGM12) | (1 << CS10);
	TIMSK1  = (1 << OCIE1A);
	
	/* Send two BREAKs of 12 bits each to enable TPI interface (need at least 16 idle bits) */
	PDITarget_SendBreak();
	PDITarget_SendBreak();
#endif
}

/** Disables the target's PDI interface, exits programming mode and starts the target's application. */
void PDITarget_DisableTargetPDI(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
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
#endif
}

/** Sends a byte via the USART.
 *
 *  \param[in] Byte  Byte to send through the USART
 */
void PDITarget_SendByte(const uint8_t Byte)
{
#if defined(XPROG_VIA_HARDWARE_USART)
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		PORTD  |=  (1 << 3);
		DDRD   |=  (1 << 3);

		UCSR1B |=  (1 << TXEN1);
		UCSR1B &= ~(1 << RXEN1);
		
		IsSending = true;
	}
	
	/* Wait until there is space in the hardware Tx buffer before writing */
	while (!(UCSR1A & (1 << UDRE1)));
	UCSR1A |= (1 << TXC1);
	UDR1    = Byte;
#else
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	{
		BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;

		IsSending = true;
	}

	/* Calculate the new USART frame data here while while we wait for a previous byte (if any) to finish sending */
	uint16_t NewUSARTData = ((1 << 11) | (1 << 10) | (0 << 9) | ((uint16_t)Byte << 1) | (0 << 0));

	/* Compute Even parity - while a bit is still set, chop off lowest bit and toggle parity bit */
	uint8_t ParityData    = Byte;
	while (ParityData)
	{
		NewUSARTData ^= (1 << 9);
		ParityData   &= (ParityData - 1);
	}

	/* Wait until transmitter is idle before writing new data */
	while (SoftUSART_BitCount);

	/* Data shifted out LSB first, START DATA PARITY STOP STOP */
	SoftUSART_Data     = NewUSARTData;
	SoftUSART_BitCount = BITS_IN_PDI_FRAME;
#endif
}

/** Receives a byte via the software USART, blocking until data is received.
 *
 *  \return Received byte from the USART
 */
uint8_t PDITarget_ReceiveByte(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
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
	SoftUSART_BitCount = BITS_IN_PDI_FRAME;
	while (SoftUSART_BitCount);
	
	/* Throw away the parity and stop bits to leave only the data (start bit is already discarded) */
	return (uint8_t)SoftUSART_Data;
#endif
}

/** Sends a BREAK via the USART to the attached target, consisting of a full frame of idle bits. */
void PDITarget_SendBreak(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
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
	for (uint8_t i = 0; i < BITS_IN_PDI_FRAME; i++)
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
	SoftUSART_BitCount = BITS_IN_PDI_FRAME;
#endif
}

/** Busy-waits while the NVM controller is busy performing a NVM operation, such as a FLASH page read or CRC
 *  calculation.
 *
 *  \return Boolean true if the NVM controller became ready within the timeout period, false otherwise
 */
bool PDITarget_WaitWhileNVMBusBusy(void)
{
	TCNT0 = 0;
	TIFR0 = (1 << OCF1A);
			
	uint8_t TimeoutMS = PDI_NVM_TIMEOUT_MS;
	
	/* Poll the STATUS register to check to see if NVM access has been enabled */
	while (TimeoutMS)
	{
		/* Send the LDCS command to read the PDI STATUS register to see the NVM bus is active */
		PDITarget_SendByte(PDI_CMD_LDCS | PDI_STATUS_REG);
		if (PDITarget_ReceiveByte() & PDI_STATUS_NVM)
		  return true;

		if (TIFR0 & (1 << OCF1A))
		{
			TIFR0 = (1 << OCF1A);
			TimeoutMS--;
		}
	}
	
	return false;
}

#endif
