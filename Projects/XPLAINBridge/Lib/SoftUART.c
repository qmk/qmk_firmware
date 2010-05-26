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

/** Total number of bits remaining to be sent in the current frame */
static uint8_t TX_BitsRemaining;

/** Temporary data variable to hold the byte being transmitted as it is shifted out */
static uint8_t TX_Data;

/** Current bit mask of the bit being shifted into the received data byte */
static uint8_t RX_BitMask;

/** Temporary data variable to hold the byte being received as it is shifted in */
static uint8_t RX_Data;

/** Initializes the software UART, ready for data transmission and reception into the global ring buffers. */
void SoftUART_Init(void)
{
	/* Set TX pin to output high, enable RX pullup */
	STXPORT |= (1 << STX);
	STXDDR  |= (1 << STX);
	SRXPORT |= (1 << SRX);

	/* Enable INT0 for the detection of incomming start bits that signal the start of a byte */
	EICRA  = (1 << ISC01);
	EIMSK  = (1 << INT0);

	/* Ensure that when the timer is enabled the transmission ISR runs immediately */
	OCR1B  = TCNT1 + 1;
	
	/* Start timer 1 with transmission channel force-enabled so that it will immediatly fire */
	TCCR1C = (1 << FOC1B);
	TIMSK1 = (1 << OCIE1B);
	TCCR1B = (1 << CS10);
}

/** ISR to detect the start of a bit being sent to the software UART. */
ISR(INT0_vect)
{
	/* Set reception channel to fire 1.5 bits past the beginning of the start bit */
	OCR1A = TCNT1 + ((BIT_TIME * 3) / 2);
	
	/* Clear the received data temporary variable, reset the current received bit position mask */
	RX_Data    = 0;
	RX_BitMask = (1 << 0);

	/* Clear reception channel ISR flag in case it is pending */
	TIFR1 = (1 << OCF1A);

	/* Check that the start bit is still low to prevent noise from triggering a reception */
	if (!(SRXPIN & (1 << SRX)))
	{	
		/* Still low, enable both send and receive channels */
		TIMSK1 =  (1 << OCIE1A) | (1 << OCIE1B);
		
		/* Clear the start bit detection ISR flag if it is pending */
		EIMSK &= ~(1 << INT0);
	}
}

/** ISR to manage the reception of bits to the software UART. */
ISR(TIMER1_COMPA_vect)
{
	/* Move the reception ISR compare position one bit ahead */
	OCR1A += BIT_TIME;

	/* Check if reception has finished */
	if (RX_BitMask)
	{
		/* Store next bit into the received data variable */
		if (SRXPIN & (1 << SRX))
		  RX_Data |= RX_BitMask;

		/* Shift the current received bit mask to the next bit position */
		RX_BitMask <<= 1;
	}
	else
	{
		/* Reception complete, store the received byte */
		RingBuffer_Insert(&UARTtoUSB_Buffer, RX_Data);
	
		/* Disable the reception ISR as all data has now been received, re-enable start bit detection ISR */
		TIMSK1  = (1 << OCIE1B);
		EIMSK  |= (1 << INT0);
		EIFR    = (1 << INTF0);
	}
}

/** ISR to manage the transmission of bits via the software UART. */
ISR(TIMER1_COMPB_vect)
{
	/* Move the transmission ISR compare position one bit ahead */
	OCR1B += BIT_TIME;

	/* Check if transmission has finished */
	if (TX_BitsRemaining)
	{
		/* Check if we are sending a data bit, or the start bit */
		if (--TX_BitsRemaining != 9)
		{
			/* Set the TX line to the value of the next bit in the byte to send */
			if (TX_Data & (1 << 0))
			  STXPORT &= ~(1 << STX);
			else
			  STXPORT |=  (1 << STX);

			/* Shift the transmission byte to move the next bit into position */
			TX_Data >>= 1;
		}
		else
		{
			/* Start bit - keep TX line low */
			STXPORT &= ~(1 << STX);
		}
	}
	else if (USBtoUART_Buffer.Count)
	{
		/* Transmission complete, get the next byte to send (if available) */
		TX_Data = ~RingBuffer_Remove(&USBtoUART_Buffer);
		TX_BitsRemaining = 10;
	}
} 
