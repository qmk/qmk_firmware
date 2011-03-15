/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2010  David Prentice (david.prentice [at] farming [dot] uk)
  Copyright 2010  Peter Danneger
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** Total number of bits remaining to be received in the current frame */
static uint8_t RX_BitsRemaining;

/** Temporary data variable to hold the byte being received as it is shifted in */
static uint8_t RX_Data;


/** Initialises the software UART, ready for data transmission and reception into the global ring buffers. */
void SoftUART_Init(void)
{
	/* Set TX pin to output high, enable RX pull-up */
	STXPORT |= (1 << STX);
	STXDDR  |= (1 << STX);
	SRXPORT |= (1 << SRX);

	/* Enable INT0 for the detection of incoming start bits that signal the start of a byte */
	EICRA  = (1 << ISC01);
	EIMSK  = (1 << INT0);

	/* Set the transmission and reception timer compare values for the default baud rate */
	SoftUART_SetBaud(9600);

	/* Setup reception timer compare ISR */
	TIMSK1 = (1 << OCIE1A);

	/* Setup transmission timer compare ISR and start the timer */
	TIMSK3 = (1 << OCIE3A);
	TCCR3B = ((1 << CS30) | (1 << WGM32));
}

/** ISR to detect the start of a bit being sent to the software UART. */
ISR(INT0_vect, ISR_BLOCK)
{
	/* Reset the number of reception bits remaining counter */
	RX_BitsRemaining = 8;

	/* Reset the bit reception timer to -(1/2) of the total bit time, so that the first data bit is
	 * sampled mid way through the total bit time, making reception more robust.
	 */
	TCNT1 = -(OCR1A >> 1);

	/* Check to see that the pin is still low (prevents glitches from starting a frame reception) */
	if (!(SRXPIN & (1 << SRX)))
	{
		/* Disable start bit detection ISR while the next byte is received */
		EIMSK = 0;

		/* Start the reception timer */
		TCCR1B = ((1 << CS10) | (1 << WGM12));
	}
}

/** ISR to manage the reception of bits to the software UART. */
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	/* Cache the current RX pin value for later checking */
	uint8_t SRX_Cached = (SRXPIN & (1 << SRX));

	/* Check if reception has finished */
	if (RX_BitsRemaining)
	{
		/* Shift the current received bit mask to the next bit position */
		RX_Data >>= 1;
		RX_BitsRemaining--;

		/* Store next bit into the received data variable */
		if (SRX_Cached)
		  RX_Data |= (1 << 7);
	}
	else
	{
		/* Disable the reception timer as all data has now been received, re-enable start bit detection ISR */
		TCCR1B = 0;
		EIFR   = (1 << INTF0);
		EIMSK  = (1 << INT0);

		/* Reception complete, store the received byte if stop bit valid */
		if (SRX_Cached)
		  RingBuffer_Insert(&UARTtoUSB_Buffer, RX_Data);
	}
}

/** ISR to manage the transmission of bits via the software UART. */
ISR(TIMER3_COMPA_vect, ISR_BLOCK)
{
	/* Check if transmission has finished */
	if (TX_BitsRemaining)
	{
		/* Set the TX line to the value of the next bit in the byte to send */
		if (TX_Data & (1 << 0))
		  STXPORT &= ~(1 << STX);
		else
		  STXPORT |=  (1 << STX);

		/* Shift the transmission byte to move the next bit into position and decrement the bits remaining counter */
		TX_Data >>= 1;
		TX_BitsRemaining--;
	}
	else if (!(RX_BitsRemaining) && !(RingBuffer_IsEmpty(&USBtoUART_Buffer)))
	{
		/* Start bit - TX line low */
		STXPORT &= ~(1 << STX);

		/* Transmission complete, get the next byte to send (if available) */
		TX_Data          = ~RingBuffer_Remove(&USBtoUART_Buffer);
		TX_BitsRemaining = 9;
	}
}

