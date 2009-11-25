/*

	uart_soft

	copyright John Steggall 2009

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

#include <avr/io.h>

/* BITLENGTH is the time for a bit cycle worked out at F_CPU / BAUD. Gives a rough but usable figure. Wouldn't like to try
 * anything faster than 9600! */
#define BITLENGTH 833

#define SFT_TX_EN 7

#define SF_UART_TX	1
#define SF_UART_RX	2

	.section	.data

rxdata:
	.byte	0
txShifter:
	.byte	0
txBitcount:
	.byte	0
rxShifter:
	.byte	0
rxBitcount:
	.byte	0
status:
	.byte	0

	.section	.text

/*********************************************
 * External interrupt
 * 
 * RX pin has gone low.
 */
	.global	INT0_vect

INT0_vect:
	push		r16
	lds		r16,SREG
	push		r16

	lds		r16,PIND
	sbrc		r16,0		// anti glitch
	rjmp		ignore
	nop
	nop
	nop
	nop
	lds		r16,PIND
	sbrc		r16,0		// just make sure
	rjmp		ignore

	push		r17

	// grab timer value
	lds		r16,TCNT3L		
	lds		r17,TCNT3H
	
	// set trigger for RX timer (will need to add a little more though)
	sts		OCR3CH,r17
	sts		OCR3CL,r16
	
	pop		r17

	// set bitcount to 0
	ldi		r16,0
	sts		rxBitcount,r16


	// turn off interrupt, will get annoying.
	cbi		0x1D,0

	// turn on interrupt on compare match
	sbi		0x18,OCF3C
	lds		r16,TIMSK3
	ori		r16,(1<<OCIE3C)
	sts		TIMSK3,r16

ignore:
	pop		r16
	sts		SREG,r16
	pop		r16
	reti


/*********************************************
 * interrupt routine, timer compare match.
 * 
 * TX bit rate timing
 */
	.global	TIMER3_COMPB_vect

TIMER3_COMPB_vect:
	push		r16
	lds		r16,SREG
	push		r16
	push		r17
	push		r18

	// check if the last bit was sent
	lds		r17,txBitcount
	inc		r17
	cpi		r17,0x0A
	sts		txBitcount,r17
	breq		lastBitTX

	lds		r16,txShifter

	lds		r17, PORTD

	sbrs		r16,0
	andi		r17,0xFD
	sbrc		r16,0
	ori		r17,0x02

	sts		PORTD,r17

	lsr		r16
	ori		r16,0x80

txout:
	sts		txShifter,r16
lastBitOut:
	pop		r18
	pop		r17
	pop		r16
	sts		SREG,r16
	pop		r16
	reti

// section handles the last bit (stop bit sent/received and sets the flag to say done //
lastBitTX:
	lds		r17,status		// get status
	ori		r17,SF_UART_TX		// set TXC/DRE flag
	sts		status,r17

	lds		r16,TIMSK3
	andi		r16,~(1<<OCIE3B)
	sts		TIMSK3,r16

	rjmp		lastBitOut		// over and out



/*********************************************
 * interrupt routine, timer compare match.
 * 
 * RX bit rate timing
 */
	.global	TIMER3_COMPC_vect

TIMER3_COMPC_vect:
	push		r16
	lds		r16,SREG
	push		r16
	push		r17
	push		r18

	// check if the last bit has been recieved
	lds		r17,rxBitcount
	inc		r17
	cpi		r17,0x0A
	sts		rxBitcount,r17
	breq		lastBitRX

	cpi		r17,0x01
	breq		rx1stbit

	ldi		r18,3			// set counter to 3
	ldi		r17,0

//	cbi		0x0B,1			// marker

loopGetBit:
	lds		r16,PIND			
	sbrc		r16,0
	inc		r17
	dec		r18
	nop
	nop
	nop
	nop
	brne		loopGetBit

//	sbi		0x0B,1			// marker

	lds		r16,rxShifter
	lsr		r16

	cpi		r17,2
	brlo		skipBitSet
	ori		r16,0x80
skipBitSet:
	sts		rxShifter,r16
	rjmp		lastBitOut

lastBitRX:
	lds		r17,status		// store status
	lds		r16,PIND			// get status of stop bit
	sbrc		r16,0
	ori		r17,0x02			// set flag if stop bit was high
	sts		status,r17

	lds		r16,rxShifter		// get contents of shifter
	sbrc		r17,1			// check if we just received a valid byte
	sts		rxdata,r16		// if valid rxdata = shifter

	// switch interrupt back on to get another go

	sbi		0x1C,0			// clear interrupt flag
	sbi		0x1D,0			// enable external interrupt 0 (RX)

	// switch off rx bit timer
	lds		r16,TIMSK3
	andi		r16,~(1<<OCIE3C)
	sts		TIMSK3,r16

	rjmp		lastBitOut		// loud and clear

rx1stbit:
	lds		r16,TCNT3L
	lds		r17,TCNT3H

	subi		r16,lo8(BITLENGTH / 2)
	sbci		r17,hi8(BITLENGTH / 2)
	brcc		skipOverflow

	subi		r16,lo8(0xFFFF - BITLENGTH)
	sbci		r17,hi8(0xFFFF - BITLENGTH)

skipOverflow:
	sts		OCR3CH,r17
	sts		OCR3CL,r17
	rjmp		lastBitOut

			
/*********************************************
 * void SoftUART_Init(void)
 *
 * initialises software uart and enables transmit
 */
	.global	SoftUART_Init

SoftUART_Init:

	lds		r18,PORTD
	ori		r18,0x02
	sts		PORTD,r18
	lds		r18,DDRD
	ori		r18,0x02
	sts		DDRD,r18

	ldi		r18,(1<<SFT_TX_EN)|SF_UART_TX
	sts		status,r18
	
	ldi		r18,lo8(BITLENGTH)
	ldi		r19,hi8(BITLENGTH)
	sts		OCR3AH,r19
	sts		OCR3AL,r18

	// Start timer 3
	ldi		r18,0b00001001			// ctc count mode, clock div 1
	sts		TCCR3B,r18

	// Interrupt on low level INT0
	sbi		0x1C,0
	sbi		0x1D,0

	ret


/*********************************************
 * char SoftUART_TxByte(char)
 *
 * starts a byte send and returns the byte to be sent
 */
	.global	SoftUART_TxByte

SoftUART_TxByte:
	lds		r18,status
	sbrs		r18,SFT_TX_EN
	rjmp		uart_putchar_end

	andi		r18,0xFE						// clear tx empty flag
	sts		status,r18

	sts		txShifter,r24

	ldi		r18,0
	sts		txBitcount,r18

	// grab timer value

	lds		r18,TCNT3L
	lds		r19,TCNT3H

	// drop down tx line for start bit
	lds		r20, PORTD
	andi		r20,0xFD
	sts		PORTD,r20
	
	// set trigger for tx timer
	cli
	sts		OCR3BH,r19
	sts		OCR3BL,r18
	sei

	// clear interrupt flag and enable tx interrupt
	sbi		0x18,OCF3B
	lds		r18,TIMSK3
	ori		r18,(1<<OCIE3B)
	sts		TIMSK3,r18

uart_putchar_end:
	ret


/*********************************************
 * char SoftUART_RxByte(void)
 *
 * returns the received byte
 */
	.global	SoftUART_RxByte

SoftUART_RxByte:
	lds		r24,rxdata
	lds		r18,status
	andi		r18,0xFD
	sts		status,r18
	ret


/*********************************************
 * char SoftUART_IsReceived(void)
 *
 * checks if there is a byte in the receive buffer
 */
	.global	SoftUART_IsReceived

SoftUART_IsReceived:
	lds		r24,status
	andi		r24,SF_UART_RX
	lsr		r24
	ret


/*********************************************
 * char SoftUART_IsReady(void)
 *
 * Simulates polling UDRE to see if tx buffer is empty and ready
 *
 * returns 1 if empty 0 if not
 */
	.global	SoftUART_IsReady

SoftUART_IsReady:
	lds		r24,status
	andi		r24,SF_UART_TX
	ret
