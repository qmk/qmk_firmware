/*
			 LUFA Library
	 Copyright (C) Dean Camera, 2010.
			  
  dean [at] fourwalledcubicle [dot] com
	  www.fourwalledcubicle.com
*/

/*
  Copyright 2010  David Prentice (david.prentice [at] farming [dot] uk)
  Copyright 2010  Peter Danneger
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
 *  Software UART for both data transmission and reception. This
 *  code continuously monitors the ring buffers set up by the main
 *  project source file and reads/writes data as it becomes available.
 */

#include "SoftUART.h"

static uint8_t TX_BitsRemaining, TX_Data;
static uint8_t RX_BitMask, RX_Data;

void SoftUART_Init(void)
{
	OCR1B  = TCNT1 + 1;						// force first compare
	TCCR1B = (1 << CS10); 					// CLK/1, T1 mode 0
	TCCR1C = (1 << FOC1B);
	TIMSK1 = (1 << OCIE1B);					// enable tx and wait for start
	EICRA  = (1 << ISC01);					// -ve edge
	EIMSK  = (1 << INT0);					// enable INT0 interrupt

	STXPORT |= (1 << STX);					// TX output
	STXDDR  |= (1 << STX);					// TX output
	SRXPORT |= (1 << SRX);					// pullup on INT0
}

/* ISR to detect the start of a bit being sent to the software UART. */
ISR(INT0_vect)
{
	OCR1A = TCNT1 + ((BIT_TIME * 3) / 2) - 1;	// scan 1.5 bits after start

	RX_Data    = 0;							// clear bit storage
	RX_BitMask = (1 << 0);					// bit mask

	TIFR1 = (1 << OCF1A);					// clear pending interrupt

	if (!(SRXPIN & (1 << SRX)))				// still low
	{
		TIMSK1 =  (1 << OCIE1A) | (1 << OCIE1B); // wait for first bit
		EIMSK &= ~(1 << INT0);
	}
}

/* ISR to manage the reception of bits to the software UART. */
ISR(TIMER1_COMPA_vect)
{
	if (RX_BitMask)
	{
		if (SRXPIN & (1 << SRX))
		  RX_Data |= RX_BitMask;

		RX_BitMask <<= 1;

		OCR1A += BIT_TIME;				// next bit slice
	}
	else
	{
		RingBuffer_Insert(&UARTtoUSB_Buffer, RX_Data);

		TIMSK1  = (1 << OCIE1B);			// enable tx and wait for start
		EIMSK  |= (1 << INT0);				// enable START irq
		EIFR    = (1 << INTF0);				// clear any pending
	}
}

/* ISR to manage the transmission of bits via the software UART. */
ISR(TIMER1_COMPB_vect)
{
	OCR1B += BIT_TIME;					// next bit slice

	if (TX_BitsRemaining)
	{
		if (--TX_BitsRemaining != 9)		// no start bit
		{
			if (TX_Data & (1 << 0))			// test inverted data
			  STXPORT &= ~(1 << STX);
			else
			  STXPORT =   (1 << STX);

			TX_Data >>= 1;					// shift zero in from left
		}
		else
		{
			STXPORT &= ~(1 << STX);
		}
	}
	else if (USBtoUART_Buffer.Count)
	{
		TX_Data = ~RingBuffer_Remove(&USBtoUART_Buffer);
		TX_BitsRemaining = 10;
	}
} 
