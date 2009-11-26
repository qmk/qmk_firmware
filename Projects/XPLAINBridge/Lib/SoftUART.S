/*

	uart_soft

	v0.2

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
#include "SoftUARTConf.h"


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
	
	.global	status
status:
	.byte	0

	.section	.text


	.global	RX_PIN_INT

/*********************************************
 * External interrupt
 * 
 * RX pin has gone low.
 */
RX_PIN_INT:
	push		r16
	lds		r16,SREG
	push		r16

#if (RXPORT>=32)
	lds		r16,RXPORT
	sbrc		r16,0		// anti glitch

#else
	sbic		RXPORT,0
#endif

	rjmp		ignore
	nop
	nop
	nop
	nop

#if (RXPORT>=32)
	lds		r16,RXPORT
	sbrc		r16,0		// anti glitch

#else
	sbic		RXPORT,0
#endif

	rjmp		ignore

	push		r17

	// grab timer value
	lds		r16,TC_COUNTL		
	lds		r17,TC_COUNTH
	
	// set trigger for RX timer (will need to add a little more though)
	sts		TC_RX_COMPH,r17
	sts		TC_RX_COMPL,r16
	
	pop		r17

	// set bitcount to 0
	ldi		r16,0
	sts		rxBitcount,r16


	// turn off interrupt, will get annoying.
	cbi		EXTI_MASK_REG,EXTI_MASK_BIT

	// turn on interrupt on compare match

	sbi		TC_INTFLAG_REG,TC_RX_IF_BIT	

	lds		r16,TC_INT_MASK_REG
	ori		r16,(1<<TC_RX_COMPEN)
	sts		TC_INT_MASK_REG,r16

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

#if (TXPORT>=32)
	lds		r17, TXPORT
	sbrs		r16,0
	andi		r17,~(1<<TXPIN)
	sbrc		r16,0
	ori		r17,(1<<TXPIN)
	sts		TXPORT,r17

#else
	sbrs		r16,0
	cbi		TXPORT,TXPIN
	sbrc		r16,0
	sbi		TXPORT,TXPIN

#endif
	sec
	ror		r16

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

	lds		r16,TC_INT_MASK_REG
	andi		r16,~(1<<TC_TX_COMPEN)
	sts		TC_INT_MASK_REG,r16

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

#ifdef DEBUG

#if RXPORT>64
	lds		r16,RXPORT
	andi		r16,~(1<<TXPIN)
	sts		TXPORT,r16
#else
	cbi		TXPORT,TXPIN			// marker
#endif
#endif

loopGetBit:

#if (RXPORT>=32)
	lds		r16,RXPORT
	sbrs		r16,RXPIN
#else			
	sbic		RXPORT,RXPIN

#endif

	inc		r17
	dec		r18
	nop
	nop
	nop
	nop
	brne		loopGetBit

#ifdef DEBUG

#if RXPORT>64
	lds		r16,RXPORT
	ori		r16,1<<TXPIN
	sts		r16

#else
	sbi		TXPORT,TXPIN			// marker

#endif
#endif


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

#if (RXPORT>=32)
	lds		r16,RXPORT
	sbrc		r16,RXPIN

#else
	sbic		RXPORT,RXPIN	

#endif

	ori		r17,0x02			// set flag if stop bit was high
	sts		status,r17

	lds		r16,rxShifter		// get contents of shifter
	sbrc		r17,1			// check if we just received a valid byte
	sts		rxdata,r16		// if valid rxdata = shifter

	// switch interrupt back on to get another go

	sbi		EXTI_FLAG_REG,EXTI_MASK_BIT	// clear interrupt flag
	sbi		EXTI_MASK_REG,EXTI_MASK_BIT	// enable external interrupt 0 (RX)

	// switch off rx bit timer
	lds		r16,TC_INT_MASK_REG
	andi		r16,~(1<<TC_RX_COMPEN)
	sts		TC_INT_MASK_REG,r16

	rjmp		lastBitOut		// loud and clear

rx1stbit:
	lds		r16,TC_COUNTL
	lds		r17,TC_COUNTH

	subi		r16,lo8(BITLENGTH / 2)
	sbci		r17,hi8(BITLENGTH / 2)
	brcc		skipOverflow

	subi		r16,lo8(0xFFFF - BITLENGTH)
	sbci		r17,hi8(0xFFFF - BITLENGTH)

skipOverflow:
	sts		TC_RX_COMPH,r17
	sts		TC_RX_COMPL,r17
	rjmp		lastBitOut

			
/*********************************************
 * void SoftUART_Init(void)
 *
 * initialises software uart and enables transmit
 */
	.global	SoftUART_Init

SoftUART_Init:

#if (TXPORT>=32)
	lds		r18,TXPORT
	ori		r18,0x02
	sts		TXPORT,r18

	lds		r18,TXDIR_REG
	ori		r18,0x02
	sts		TXDIR_REG,r18

#else
	sbi		TXPORT,TXPIN
	sbi		TXDIR_REG,TXPIN

#endif

	ldi		r18,(1<<SFT_TX_EN)|SF_UART_TX
	sts		status,r18
	
	ldi		r18,lo8(BITLENGTH)
	ldi		r19,hi8(BITLENGTH)
	sts		OCR3AH,r19
	sts		OCR3AL,r18

	// Start timer 3
	ldi		r18,0b00001001			// ctc count mode, clock div 1
	sts		TC_CTRLB,r18

	// Interrupt on pin change INT0
	sbi		EXTI_FLAG_REG,EXTI_MASK_BIT
	sbi		EXTI_MASK_REG,EXTI_MASK_BIT

	ret


/*********************************************
 * char SoftUART_RxByte(char)
 *
 * starts a byte send and returns the byte to be sent
 */
	.global	SoftUART_TxByte

SoftUART_TxByte:
	lds		r18,status
	sbrs		r18,SFT_TX_EN
	rjmp		SoftUART_TxByte_end

	andi		r18,0xFE						// clear tx empty flag
	sts		status,r18

	sts		txShifter,r24

	ldi		r18,0
	sts		txBitcount,r18

	// grab timer value
	cli									// Atomic section start
	lds		r18,TC_COUNTL
	lds		r19,TC_COUNTH

	// drop down tx line for start bit

#if (TXPORT>=32)
	lds		r20, TXPORT
	andi		r20,~(1<<TXPIN)
	sts		TXPORT,r20

#else
	cbi		TXPORT,TXPIN
#endif

	// set trigger for tx timer
	sts		TC_TX_COMPH,r19
	sts		TC_TX_COMPL,r18
	sei									// Atomic section end

	// clear interrupt flag and enable tx interrupt

	sbi		TC_INTFLAG_REG,TC_TX_IF_BIT

	lds		r18,TC_INT_MASK_REG
	ori		r18,(1<<TC_TX_COMPEN)
	sts		TC_INT_MASK_REG,r18

SoftUART_TxByte_end:
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
