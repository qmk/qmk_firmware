/*

	soft_uart

	v0.2

	Copyright John Steggall 2009

*/

/*
  Copyright 2009  John Steggall (steggall.j@gmail.com)

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

#ifndef UART_SOFT_CONF
#define UART_SOFT_CONF

	#define BITLENGTH 833						// Length of data bit, worked out by F_CPU/desired baud

	#define TXPIN 1								// Port pin TX is connected to
	#define RXPIN 0								// Port pin RX is connected to

	/* PORT setup */
	#define RXPORT			0x09				// RX port selection
	#define TXPORT 		0x0B					// TX port selection
	#define TXDIR_REG 		0x0A				// Data direction port for TX pin

	/* RX pin setup */
	#define EXTI_FLAG_REG 	0x1C
	#define EXTI_MASK_REG 	0x1D
	#define EXTI_MASK_BIT 	0

	#define RX_PIN_INT		INT0_vect			// external interrupt vector for RX pin
	#define RX_INT_vect		TIMER3_COMPC_vect	// interrupt vector for OCRnC
	#define TX_INT_vect		TIMER3_COMPB_vect	// interrupt vector for OCRnB

	#define TC_INT_MASK_REG	TIMSK3				// interrupt timer mask register for timer(n)
	#define TC_COUNTL		TCNT3L				// count high register for timer(n)
	#define TC_COUNTH		TCNT3H				// count low register for timer(n)

	/* Reciever setup */
	#define TC_RX_COMPEN	OCIE3C				// interrupt enable for OCRnC (RX bit timer)
	#define TC_RX_COMPH		OCR3CH				// OCRnC compare match high register
	#define TC_RX_COMPL		OCR3CL				// OCRnC compare match high register

	/* Transmitter setup */
	#define TC_TX_COMPEN	OCIE3B				// interrupt enable for OCRnB (TX bit timer)
	#define TC_TX_COMPH		OCR3BH				// OCRnB compare match high register
	#define TC_TX_COMPL		OCR3BL				// OCRnB compare match low register

	#define TC_CTRLB		TCCR3B				// timer(n) control register B

	#define TC_INTFLAG_REG	0x18				// timer(n) interupt flag register
	#define TC_TX_IF_BIT	OCIE3B				// timer(n) interrupt flag bit for OCRnB
	#define TC_RX_IF_BIT	OCIE3C				// timer(n) interrupt flag bit for OCRnC

#endif
