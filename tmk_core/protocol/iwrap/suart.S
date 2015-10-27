;---------------------------------------------------------------------------;
; Software implemented UART module                                          ;
; (C)ChaN, 2005 (http://elm-chan.org/)                                      ;
;---------------------------------------------------------------------------;
; Bit rate settings:
;
;            1MHz  2MHz  4MHz  6MHz  8MHz  10MHz  12MHz  16MHz  20MHz
;   2.4kbps   138     -     -     -     -      -      -      -      -
;   4.8kbps    68   138     -     -     -      -      -      -      -
;   9.6kbps    33    68   138   208     -      -      -      -      -
;  19.2kbps     -    33    68   102   138    173    208      -      -
;  38.4kbps     -     -    33    50    68     85    102    138    172
;  57.6kbps     -     -    21    33    44     56     68     91    114
; 115.2kbps     -     -     -     -    21     27     33     44     56

.nolist
#include <avr/io.h>
.list

#define	BPS	102 	/* Bit delay. (see above table) */
#define	BIDIR	0	/* 0:Separated Tx/Rx, 1:Shared Tx/Rx */

#define	OUT_1		sbi _SFR_IO_ADDR(SUART_OUT_PORT), SUART_OUT_BIT	/* Output 1 */
#define	OUT_0		cbi _SFR_IO_ADDR(SUART_OUT_PORT), SUART_OUT_BIT	/* Output 0 */
#define	SKIP_IN_1	sbis _SFR_IO_ADDR(SUART_IN_PIN), SUART_IN_BIT	/* Skip if 1 */
#define	SKIP_IN_0	sbic _SFR_IO_ADDR(SUART_IN_PIN), SUART_IN_BIT	/* Skip if 0 */



#ifdef SPM_PAGESIZE
.macro	_LPMI	reg
	lpm	\reg, Z+
.endm
.macro	_MOVW	dh,dl, sh,sl
	movw	\dl, \sl
.endm
#else
.macro	_LPMI	reg
	lpm
	mov	\reg, r0
	adiw	ZL, 1
.endm
.macro	_MOVW	dh,dl, sh,sl
	mov	\dl, \sl
	mov	\dh, \sh
.endm
#endif



;---------------------------------------------------------------------------;
; Transmit a byte in serial format of N81
;
;Prototype: void xmit (uint8_t data);
;Size: 16 words

.global xmit
.func xmit
xmit:
#if BIDIR
	ldi	r23, BPS-1	;Pre-idle time for bidirectional data line
5:	dec	r23     	;
	brne	5b		;/
#endif
	in	r0, _SFR_IO_ADDR(SREG)	;Save flags

	com	r24		;C = start bit
	ldi	r25, 10		;Bit counter
	cli			;Start critical section

1:	ldi	r23, BPS-1	;----- Bit transferring loop 
2:	dec	r23     	;Wait for a bit time
	brne	2b		;/
	brcs	3f		;MISO = bit to be sent
	OUT_1			;
3:	brcc	4f		;
	OUT_0			;/
4:	lsr	r24     	;Get next bit into C
	dec	r25     	;All bits sent?
	brne	1b	     	;  no, coutinue

	out	_SFR_IO_ADDR(SREG), r0	;End of critical section
	ret
.endfunc



;---------------------------------------------------------------------------;
; Receive a byte
;
;Prototype: uint8_t rcvr (void);
;Size: 19 words

.global rcvr
.func rcvr
rcvr:
	in	r0, _SFR_IO_ADDR(SREG)	;Save flags

	ldi	r24, 0x80	;Receiving shift reg
	cli			;Start critical section

1:	SKIP_IN_1		;Wait for idle
	rjmp	1b
2:	SKIP_IN_0		;Wait for start bit
	rjmp	2b
	ldi	r25, BPS/2	;Wait for half bit time
3:	dec	r25
	brne	3b

4:	ldi	r25, BPS	;----- Bit receiving loop
5:	dec	r25     	;Wait for a bit time
	brne	5b		;/
	lsr	r24     	;Next bit
	SKIP_IN_0		;Get a data bit into r24.7
	ori	r24, 0x80
	brcc	4b	     	;All bits received?  no, continue

	out	_SFR_IO_ADDR(SREG), r0	;End of critical section
	ret
.endfunc


; Not wait for start bit. This should be called after detecting start bit.
.global recv
.func recv
recv:
	in	r0, _SFR_IO_ADDR(SREG)	;Save flags

	ldi	r24, 0x80	;Receiving shift reg
	cli			;Start critical section

;1:	SKIP_IN_1		;Wait for idle
;	rjmp	1b
;2:	SKIP_IN_0		;Wait for start bit
;	rjmp	2b
	ldi	r25, BPS/2	;Wait for half bit time
3:	dec	r25
	brne	3b

4:	ldi	r25, BPS	;----- Bit receiving loop
5:	dec	r25     	;Wait for a bit time
	brne	5b		;/
	lsr	r24     	;Next bit
	SKIP_IN_0		;Get a data bit into r24.7
	ori	r24, 0x80
	brcc	4b	     	;All bits received?  no, continue

	ldi	r25, BPS/2	;Wait for half bit time
6:	dec	r25
	brne	6b
7:	SKIP_IN_1		;Wait for stop bit
	rjmp	7b

	out	_SFR_IO_ADDR(SREG), r0	;End of critical section
	ret
.endfunc
