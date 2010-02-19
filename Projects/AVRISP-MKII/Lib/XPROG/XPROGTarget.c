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
 *  Target-related functions for the PDI Protocol decoder.
 */

#define  INCLUDE_FROM_XPROGTARGET_C
#include "XPROGTarget.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Flag to indicate if the USART is currently in Tx or Rx mode. */
volatile bool               IsSending;

#if !defined(XPROG_VIA_HARDWARE_USART)
/** Software USART raw frame bits for transmission/reception. */
volatile uint16_t           SoftUSART_Data;

/** Bits remaining to be sent or received via the software USART - set as a GPIOR for speed. */
#define SoftUSART_BitCount  GPIOR2


/** ISR to manage the rising edge of the PDI/TPI software USART when bit-banged USART mode is selected. */
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	/* Toggle CLOCK pin in a single cycle (see AVR datasheet) */
	BITBANG_PDICLOCK_PIN |= BITBANG_PDICLOCK_MASK;
	TIFR1 |= (1 << OCF1B);
	TIMSK1 = (1 << OCIE1B);

	/* If not sending or receiving, just exit */
	if (!(SoftUSART_BitCount))
	  return;

	/* If at rising clock edge and we are in send mode, abort */
	if (IsSending)
	  return;
	  
	/* Wait for the start bit when receiving */
	if ((SoftUSART_BitCount == BITS_IN_USART_FRAME) && (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK))
	  return;

	/* Shift in the bit one less than the frame size in position, so that the start bit will eventually
	 * be discarded leaving the data to be byte-aligned for quick access (subtract 9 as we are ORing to the MSB) */
	if (BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK)
	  ((uint8_t*)&SoftUSART_Data)[1] |= (1 << (BITS_IN_USART_FRAME - 9));

	SoftUSART_Data >>= 1;
	SoftUSART_BitCount--;
}

/** ISR to manage the falling edge of the PDI/TPI software USART when bit-banged USART mode is selected. */
ISR(TIMER1_COMPB_vect, ISR_BLOCK)
{
	/* Toggle CLOCK pin in a single cycle (see AVR datasheet) */
	BITBANG_PDICLOCK_PIN |= BITBANG_PDICLOCK_MASK;
	TIFR1 |= (1 << OCF1A);
	TIMSK1 = (1 << OCIE1A);

	/* If not sending or receiving, just exit */
	if (!(SoftUSART_BitCount))
	  return;

	/* If at falling clock edge and we are in receive mode, abort */
	if (!IsSending)
	  return;

	/* Set the data line to the next bit value */
	if (((uint8_t*)&SoftUSART_Data)[0] & 0x01)
	  BITBANG_PDIDATA_PORT |=  BITBANG_PDIDATA_MASK;
	else
	  BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;		  

	SoftUSART_Data >>= 1;
	SoftUSART_BitCount--;
}

/** ISR to manage the TPI software USART when bit-banged TPI USART mode is selected. */
ISR(TIMER1_CAPT_vect, ISR_BLOCK)
{
	/* Toggle CLOCK pin in a single cycle (see AVR datasheet) */
	BITBANG_TPICLOCK_PIN |= BITBANG_TPICLOCK_MASK;

	/* If not sending or receiving, just exit */
	if (!(SoftUSART_BitCount))
	  return;

	/* Check to see if we are at a rising or falling edge of the clock */
	if (BITBANG_TPICLOCK_PORT & BITBANG_TPICLOCK_MASK)
	{
		/* If at rising clock edge and we are in send mode, abort */
		if (IsSending)
		  return;
		  
		/* Wait for the start bit when receiving */
		if ((SoftUSART_BitCount == BITS_IN_USART_FRAME) && (BITBANG_TPIDATA_PIN & BITBANG_TPIDATA_MASK))
		  return;
	
		/* Shift in the bit one less than the frame size in position, so that the start bit will eventually
		 * be discarded leaving the data to be byte-aligned for quick access (subtract 9 as we are ORing to the MSB) */
		if (BITBANG_TPIDATA_PIN & BITBANG_TPIDATA_MASK)
		 ((uint8_t*)&SoftUSART_Data)[1] |= (1 << (BITS_IN_USART_FRAME - 9));

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
	else
	{
		/* If at falling clock edge and we are in receive mode, abort */
		if (!IsSending)
		  return;

		/* Set the data line to the next bit value */
		if (((uint8_t*)&SoftUSART_Data)[0] & 0x01)
		  BITBANG_TPIDATA_PORT |=  BITBANG_TPIDATA_MASK;
		else
		  BITBANG_TPIDATA_PORT &= ~BITBANG_TPIDATA_MASK;		  

		SoftUSART_Data >>= 1;
		SoftUSART_BitCount--;
	}
}
#endif

/** Enables the target's PDI interface, holding the target in reset until PDI mode is exited. */
void XPROGTarget_EnableTargetPDI(void)
{
	IsSending = false;

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);
	
	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	PORTD |= (1 << 3);
	_delay_us(1);
	
	/* Set up the synchronous USART for XMEGA communications - 
	   8 data bits, even parity, 2 stop bits */
	UBRR1  = (F_CPU / 500000UL);
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);
#else
	/* Set DATA and CLOCK lines to outputs */
	BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR |= BITBANG_PDICLOCK_MASK;
	
	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
	_delay_us(1);

	/* Fire timer compare channel A ISR to manage the software USART */
	OCR1A   = BITS_BETWEEN_USART_CLOCKS;
	OCR1B   = BITS_BETWEEN_USART_CLOCKS;
	TCCR1B  = (1 << WGM12) | (1 << CS10);
	TCCR1C  = (1 << FOC1B);
	TIMSK1  = (1 << OCIE1A);
#endif

	/* Send two BREAKs of 12 bits each to enable PDI interface (need at least 16 idle bits) */
	XPROGTarget_SendBreak();
	XPROGTarget_SendBreak();
}

/** Enables the target's TPI interface, holding the target in reset until TPI mode is exited. */
void XPROGTarget_EnableTargetTPI(void)
{
	IsSending = false;

	/* Set /RESET line low for at least 400ns to enable TPI functionality */
	AUX_LINE_DDR  |=  AUX_LINE_MASK;
	AUX_LINE_PORT &= ~AUX_LINE_MASK;
	_delay_us(1);

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);
		
	/* Set up the synchronous USART for TINY communications - 
	   8 data bits, even parity, 2 stop bits */
	UBRR1  = (F_CPU / 500000UL);
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);
#else
	/* Set DATA and CLOCK lines to outputs */
	BITBANG_TPIDATA_DDR  |= BITBANG_TPIDATA_MASK;
	BITBANG_TPICLOCK_DDR |= BITBANG_TPICLOCK_MASK;
	
	/* Set DATA line high for idle state */
	BITBANG_TPIDATA_PORT |= BITBANG_TPIDATA_MASK;

	/* Fire timer capture channel ISR to manage the software USART */
	ICR1    = BITS_BETWEEN_USART_CLOCKS;
	TCCR1B  = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
	TIMSK1  = (1 << ICIE1);
#endif

	/* Send two BREAKs of 12 bits each to enable TPI interface (need at least 16 idle bits) */
	XPROGTarget_SendBreak();
	XPROGTarget_SendBreak();
}

/** Disables the target's PDI interface, exits programming mode and starts the target's application. */
void XPROGTarget_DisableTargetPDI(void)
{
	/* Switch to Rx mode to ensure that all pending transmissions are complete */
	XPROGTarget_SetRxMode();

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Set /RESET high for a one millisecond to ensure target device is restarted */
	PORTD |= (1 << 5);
	_delay_ms(1);

	/* Turn off receiver and transmitter of the USART, clear settings */
	UCSR1A |= (1 << TXC1) | (1 << RXC1);
	UCSR1B  = 0;
	UCSR1C  = 0;

	/* Set all USART lines as input, tristate */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));
#else
	/* Turn off software USART management timer */
	TCCR1B = 0;
	TCCR1C = 0;

	/* Set /RESET high for a one millisecond to ensure target device is restarted */
	BITBANG_PDICLOCK_PORT |= BITBANG_PDICLOCK_MASK;
	_delay_ms(1);

	/* Set DATA and CLOCK lines to inputs */
	BITBANG_PDIDATA_DDR   &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_DDR  &= ~BITBANG_PDICLOCK_MASK;
	
	/* Tristate DATA and CLOCK lines */
	BITBANG_PDIDATA_PORT  &= ~BITBANG_PDIDATA_MASK;
	BITBANG_PDICLOCK_PORT &= ~BITBANG_PDICLOCK_MASK;	
#endif
}

/** Disables the target's TPI interface, exits programming mode and starts the target's application. */
void XPROGTarget_DisableTargetTPI(void)
{
	/* Switch to Rx mode to ensure that all pending transmissions are complete */
	XPROGTarget_SetRxMode();

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Turn off receiver and transmitter of the USART, clear settings */
	UCSR1A |= (1 << TXC1) | (1 << RXC1);
	UCSR1B  = 0;
	UCSR1C  = 0;

	/* Set all USART lines as input, tristate */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));
#else
	/* Turn off software USART management timer */
	TCCR1B = 0;

	/* Set DATA and CLOCK lines to inputs */
	BITBANG_TPIDATA_DDR   &= ~BITBANG_TPIDATA_MASK;
	BITBANG_TPICLOCK_DDR  &= ~BITBANG_TPICLOCK_MASK;
	
	/* Tristate DATA and CLOCK lines */
	BITBANG_TPIDATA_PORT  &= ~BITBANG_TPIDATA_MASK;
	BITBANG_TPICLOCK_PORT &= ~BITBANG_TPICLOCK_MASK;
#endif

	/* Tristate target /RESET line */
	AUX_LINE_DDR  &= ~AUX_LINE_MASK;
	AUX_LINE_PORT &= ~AUX_LINE_MASK;
}

/** Sends a byte via the USART.
 *
 *  \param[in] Byte  Byte to send through the USART
 */
void XPROGTarget_SendByte(const uint8_t Byte)
{
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	  XPROGTarget_SetTxMode();
	  
#if defined(XPROG_VIA_HARDWARE_USART)
	/* Wait until there is space in the hardware Tx buffer before writing */
	while (!(UCSR1A & (1 << UDRE1)));
	UCSR1A |= (1 << TXC1);
	UDR1    = Byte;
#else
	/* Calculate the new USART frame data here while while we wait for a previous byte (if any) to finish sending */
	uint16_t NewUSARTData = ((1 << 11) | (1 << 10) | (0 << 9) | ((uint16_t)Byte << 1) | (0 << 0));

	/* Compute Even parity - while a bit is still set, chop off lowest bit and toggle parity bit */
	uint8_t ParityData = Byte;
	while (ParityData)
	{
		NewUSARTData ^= (1 << 9);
		ParityData   &= (ParityData - 1);
	}

	/* Wait until transmitter is idle before writing new data */
	while (SoftUSART_BitCount);

	/* Data shifted out LSB first, START DATA PARITY STOP STOP */
	SoftUSART_Data     = NewUSARTData;
	SoftUSART_BitCount = BITS_IN_USART_FRAME;
#endif
}

/** Receives a byte via the software USART, blocking until data is received.
 *
 *  \return Received byte from the USART
 */
uint8_t XPROGTarget_ReceiveByte(void)
{
	/* Switch to Rx mode if currently in Tx mode */
	if (IsSending)
	  XPROGTarget_SetRxMode();

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Wait until a byte has been received before reading */
	uint8_t TimeoutMSRemaining = 100;
	while (!(UCSR1A & (1 << RXC1)) && TimeoutMSRemaining)
	{
		/* Manage software timeout */
		if (TIFR0 & (1 << OCF0A))
		{
			TIFR0 |= (1 << OCF0A);
			TimeoutMSRemaining--;
		}	
	}
	
	return UDR1;
#else
	/* Wait until a byte has been received before reading */
	SoftUSART_BitCount = BITS_IN_USART_FRAME;
	uint8_t TimeoutMSRemaining = 100;
	while (SoftUSART_BitCount && TimeoutMSRemaining)
	{
		/* Manage software timeout */
		if (TIFR0 & (1 << OCF0A))
		{
			TIFR0 |= (1 << OCF0A);
			TimeoutMSRemaining--;
		}
	}

	/* Throw away the parity and stop bits to leave only the data (start bit is already discarded) */
	return (uint8_t)SoftUSART_Data;
#endif
}

/** Sends a BREAK via the USART to the attached target, consisting of a full frame of idle bits. */
void XPROGTarget_SendBreak(void)
{
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	  XPROGTarget_SetTxMode();

#if defined(XPROG_VIA_HARDWARE_USART)
	/* Need to do nothing for a full frame to send a BREAK */
	for (uint8_t i = 0; i < BITS_IN_USART_FRAME; i++)
	{
		/* Wait for a full cycle of the clock */
		while (PIND & (1 << 5));
		while (!(PIND & (1 << 5)));
	}
#else
	while (SoftUSART_BitCount);

	/* Need to do nothing for a full frame to send a BREAK */
	SoftUSART_Data     = 0x0FFF;
	SoftUSART_BitCount = BITS_IN_USART_FRAME;
#endif
}

static void XPROGTarget_SetTxMode(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
	/* Wait for a full cycle of the clock */
	while (PIND & (1 << 5));
	while (!(PIND & (1 << 5)));

	PORTD  |=  (1 << 3);
	DDRD   |=  (1 << 3);

	UCSR1B &= ~(1 << RXEN1);
	UCSR1B |=  (1 << TXEN1);
		
	IsSending = true;
#else
	while (SoftUSART_BitCount);

	/* Wait for a full cycle of the clock */
	SoftUSART_Data     = 0x0001;
	SoftUSART_BitCount = 1;
	while (SoftUSART_BitCount);

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		BITBANG_PDIDATA_PORT |= BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_DDR  |= BITBANG_PDIDATA_MASK;
	}
	else
	{
		BITBANG_TPIDATA_PORT |= BITBANG_TPIDATA_MASK;
		BITBANG_TPIDATA_DDR  |= BITBANG_TPIDATA_MASK;	
	}
#endif

	IsSending = true;
}

static void XPROGTarget_SetRxMode(void)
{
#if defined(XPROG_VIA_HARDWARE_USART)
	while (!(UCSR1A & (1 << TXC1)));
	UCSR1A |=  (1 << TXC1);

	UCSR1B &= ~(1 << TXEN1);
	UCSR1B |=  (1 << RXEN1);

	DDRD   &= ~(1 << 3);
	PORTD  &= ~(1 << 3);
#else
	while (SoftUSART_BitCount);

	if (XPROG_SelectedProtocol == XPRG_PROTOCOL_PDI)
	{
		BITBANG_PDIDATA_DDR  &= ~BITBANG_PDIDATA_MASK;
		BITBANG_PDIDATA_PORT &= ~BITBANG_PDIDATA_MASK;
	}
	else
	{
		BITBANG_TPIDATA_DDR  &= ~BITBANG_TPIDATA_MASK;
		BITBANG_TPIDATA_PORT &= ~BITBANG_TPIDATA_MASK;	
	}
	
	/* Wait until DATA line has been pulled up to idle by the target */
	uint8_t TimeoutMSRemaining = 100;
	while (!(BITBANG_PDIDATA_PIN & BITBANG_PDIDATA_MASK) && TimeoutMSRemaining)
	{
		/* Manage software timeout */
		if (TIFR0 & (1 << OCF0A))
		{
			TIFR0 |= (1 << OCF0A);
			TimeoutMSRemaining--;
		}
	}	
#endif

	IsSending = false;
}

#endif
