/*
			 LUFA Library
	 Copyright (C) Dean Camera, 2009.
			  
  dean [at] fourwalledcubicle [dot] com
	  www.fourwalledcubicle.com
*/

/*
  Copyright 2009  David Prentice (david.prentice [at] farming [dot] uk)
  Copyright 2009  Peter Danneger
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

#include "SoftUART.h"

volatile uint8_t srx_done, stx_count;
volatile uint8_t srx_data, srx_mask, srx_tmp, stx_data;

unsigned char SoftUART_IsReady(void)
{
	return !(stx_count);
}

unsigned char SoftUART_TxByte(unsigned char c)
{
	while (stx_count);

	stx_data  = ~c;
	stx_count = 10;

	return c;
}

unsigned char SoftUART_IsReceived(void)
{
	return srx_done;
}

unsigned char SoftUART_RxByte(void)
{
	while (!(srx_done));

	srx_done = 0;

	return srx_data;
}

void SoftUART_Init(void)
{
	OCR2B  = TCNT2 + 1;						// force first compare
	TCCR2A = (1 << COM2B1) | (1 << COM2B0);	// T1 mode 0
	TCCR2B = (1 << FOC2B)  | (1 << CS21); 	// CLK/8, T1 mode 0
	TIMSK2 = (1 << OCIE2B);					// enable tx and wait for start
	EICRA  = (1 << ISC01);					// -ve edge
	EIMSK  = (1 << INT0);					// enable INT0 interrupt

	stx_count = 0;							// nothing to send
	srx_done = 0;							// nothing received
	STXPORT |= 1 << STX;					// TX output
	STXDDR  |= 1 << STX;					// TX output
	SRXPORT |= (1 << SRX);					// pullup on INT0
}

/* ISR to detect the start of a bit being sent from the transmitter. */
ISR(INT0_vect)
{
	OCR2A = TCNT2 + (BIT_TIME / 8 * 3 / 2);	// scan 1.5 bits after start

	srx_tmp = 0;							// clear bit storage
	srx_mask = 1;							// bit mask

	TIFR2 = (1 << OCF2A);					// clear pending interrupt

	if (!(SRXPIN & (1 << SRX)))				// still low
	{
		TIMSK2 = (1 << OCIE2A) | (1 << OCIE2B); // wait for first bit
		EIMSK &= ~(1 << INT0);
	}
}

/* ISR to manage the reception of bits to the transmitter. */
ISR(TIMER2_COMPA_vect)
{
	if (srx_mask)
	{
		if (SRXPIN & (1 << SRX))
		  srx_tmp |= srx_mask;

		srx_mask <<= 1;

		OCR2A += BIT_TIME / 8;				// next bit slice
	}
	else
	{
		srx_done  = 1;						// mark rx data valid
		srx_data  = srx_tmp;				// store rx data
		TIMSK2    = (1 << OCIE2B);			// enable tx and wait for start
		EIMSK    |= (1 << INT0);			// enable START irq
		EIFR      = (1 << INTF0);			// clear any pending
	}
}

/* ISR to manage the transmission of bits to the receiver. */
ISR(TIMER2_COMPB_vect)
{
	OCR2B += BIT_TIME / 8;					// next bit slice

	if (stx_count)
	{
		if (--stx_count != 9)				// no start bit
		{
			if (!(stx_data & 1))			// test inverted data
			  TCCR2A = (1 << COM2B1) | (1 << COM2B0);
			else
			  TCCR2A = (1 << COM2B1);

			stx_data >>= 1;					// shift zero in from left
		}
		else
		{
			TCCR2A = (1 << COM2B1);			// START bit
		}
	}
} 
