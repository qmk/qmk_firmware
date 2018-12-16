/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

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

/** \file
 *
 *  Target-related functions for the PDI Protocol decoder.
 */

#define  INCLUDE_FROM_XPROGTARGET_C
#include "XPROGTarget.h"

#if defined(ENABLE_XPROG_PROTOCOL) || defined(__DOXYGEN__)

/** Flag to indicate if the USART is currently in Tx or Rx mode. */
bool IsSending;

/** Enables the target's PDI interface, holding the target in reset until PDI mode is exited. */
void XPROGTarget_EnableTargetPDI(void)
{
	IsSending = false;

	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);

	/* Set DATA line high for at least 90ns to disable /RESET functionality */
	PORTD |= (1 << 3);
	_delay_us(100);

	/* Set up the synchronous USART for XMEGA communications - 8 data bits, even parity, 2 stop bits */
	UBRR1  = ((F_CPU / 2 / XPROG_HARDWARE_SPEED) - 1);
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);

	/* Send two IDLEs of 12 bits each to enable PDI interface (need at least 16 idle bits) */
	XPROGTarget_SendIdle();
	XPROGTarget_SendIdle();
}

/** Enables the target's TPI interface, holding the target in reset until TPI mode is exited. */
void XPROGTarget_EnableTargetTPI(void)
{
	IsSending = false;

	/* Set /RESET line low for at least 400ns to enable TPI functionality */
	AUX_LINE_DDR  |=  AUX_LINE_MASK;
	AUX_LINE_PORT &= ~AUX_LINE_MASK;
	_delay_us(100);

	/* Set Tx and XCK as outputs, Rx as input */
	DDRD |=  (1 << 5) | (1 << 3);
	DDRD &= ~(1 << 2);

	/* Set up the synchronous USART for TPI communications - 8 data bits, even parity, 2 stop bits */
	UBRR1  = ((F_CPU / 2 / XPROG_HARDWARE_SPEED) - 1);
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UMSEL10) | (1 << UPM11) | (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (1 << UCPOL1);

	/* Send two IDLEs of 12 bits each to enable TPI interface (need at least 16 idle bits) */
	XPROGTarget_SendIdle();
	XPROGTarget_SendIdle();
}

/** Disables the target's PDI interface, exits programming mode and starts the target's application. */
void XPROGTarget_DisableTargetPDI(void)
{
	/* Switch to Rx mode to ensure that all pending transmissions are complete */
	if (IsSending)
	  XPROGTarget_SetRxMode();

	/* Turn off receiver and transmitter of the USART, clear settings */
	UCSR1A  = ((1 << TXC1) | (1 << RXC1));
	UCSR1B  = 0;
	UCSR1C  = 0;

	/* Tristate all pins */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));
}

/** Disables the target's TPI interface, exits programming mode and starts the target's application. */
void XPROGTarget_DisableTargetTPI(void)
{
	/* Switch to Rx mode to ensure that all pending transmissions are complete */
	if (IsSending)
	  XPROGTarget_SetRxMode();

	/* Turn off receiver and transmitter of the USART, clear settings */
	UCSR1A |= (1 << TXC1) | (1 << RXC1);
	UCSR1B  = 0;
	UCSR1C  = 0;

	/* Set all USART lines as inputs, tristate */
	DDRD  &= ~((1 << 5) | (1 << 3));
	PORTD &= ~((1 << 5) | (1 << 3) | (1 << 2));

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

	/* Wait until there is space in the hardware Tx buffer before writing */
	while (!(UCSR1A & (1 << UDRE1)));
	UCSR1A |= (1 << TXC1);
	UDR1    = Byte;
}

/** Receives a byte via the hardware USART, blocking until data is received or timeout expired.
 *
 *  \return Received byte from the USART
 */
uint8_t XPROGTarget_ReceiveByte(void)
{
	/* Switch to Rx mode if currently in Tx mode */
	if (IsSending)
	  XPROGTarget_SetRxMode();

	/* Wait until a byte has been received before reading */
	while (!(UCSR1A & (1 << RXC1)) && TimeoutTicksRemaining);

	return UDR1;
}

/** Sends an IDLE via the USART to the attached target, consisting of a full frame of idle bits. */
void XPROGTarget_SendIdle(void)
{
	/* Switch to Tx mode if currently in Rx mode */
	if (!(IsSending))
	  XPROGTarget_SetTxMode();

	/* Need to do nothing for a full frame to send an IDLE */
	for (uint8_t i = 0; i < BITS_IN_USART_FRAME; i++)
	{
		/* Wait for a full cycle of the clock */
		while (PIND & (1 << 5));
		while (!(PIND & (1 << 5)));
		while (PIND & (1 << 5));
	}
}

static void XPROGTarget_SetTxMode(void)
{
	/* Wait for a full cycle of the clock */
	while (PIND & (1 << 5));
	while (!(PIND & (1 << 5)));
	while (PIND & (1 << 5));

	PORTD  |=  (1 << 3);
	DDRD   |=  (1 << 3);

	UCSR1B &= ~(1 << RXEN1);
	UCSR1B |=  (1 << TXEN1);

	IsSending = true;
}

static void XPROGTarget_SetRxMode(void)
{
	while (!(UCSR1A & (1 << TXC1)));
	UCSR1A |=  (1 << TXC1);

	UCSR1B &= ~(1 << TXEN1);
	UCSR1B |=  (1 << RXEN1);

	DDRD   &= ~(1 << 3);
	PORTD  &= ~(1 << 3);

	IsSending = false;
}

#endif

