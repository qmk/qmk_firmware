;---------------------------------------------------------------------------;
; Extended itoa, puts, printf and atoi                     (C)ChaN, 2011
;---------------------------------------------------------------------------;

				// Base size is 152 bytes
#define	CR_CRLF		0	// Convert \n to \r\n (+10 bytes)
#define USE_XPRINTF	1	// Enable xprintf function (+194 bytes)
#define USE_XSPRINTF	0	// Add xsprintf function (+78 bytes)
#define USE_XFPRINTF	0	// Add xfprintf function (+54 bytes)
#define USE_XATOI	0	// Enable xatoi function (+182 bytes)


#if FLASHEND > 0x1FFFF
#error xitoa module does not support 256K devices
#endif

.nolist
#include <avr/io.h>	// Include device specific definitions.
.list

#ifdef SPM_PAGESIZE	// Recent devices have "lpm Rd,Z+" and "movw".
.macro	_LPMI	reg
	lpm	\reg, Z+
.endm
.macro	_MOVW	dh,dl, sh,sl
	movw	\dl, \sl
.endm
#else			// Earlier devices do not have "lpm Rd,Z+" nor "movw".
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



;---------------------------------------------------------------------------
; Stub function to forward to user output function
;
;Prototype: void xputc (char chr	// a character to be output
;			);
;Size: 12/12 words

.section .bss
.global xfunc_out	; xfunc_out must be initialized before using this module.
xfunc_out:	.ds.w	1
.section .text


.func xputc
.global xputc
xputc:
#if CR_CRLF
	cpi	r24, 10		;LF --> CRLF
	brne	1f		;
	ldi	r24, 13		;
	rcall	1f		;
	ldi	r24, 10		;/
1:
#endif
	push	ZH
	push	ZL
	lds	ZL, xfunc_out+0	;Pointer to the registered output function.
	lds	ZH, xfunc_out+1	;/
	sbiw	ZL, 0		;Skip if null
	breq	2f		;/
	icall
2:	pop	ZL
	pop	ZH
	ret
.endfunc



;---------------------------------------------------------------------------
; Direct ROM string output
;
;Prototype: void xputs (const char *str_p // rom string to be output
;			);

.func xputs
.global xputs
xputs:
	_MOVW	ZH,ZL, r25,r24	; Z = pointer to rom string
1:	_LPMI	r24
	cpi	r24, 0
	breq	2f
	rcall	xputc
	rjmp	1b
2:	ret
.endfunc


;---------------------------------------------------------------------------
; Extended direct numeral string output (32bit version)
;
;Prototype: void xitoa (long value,	// value to be output
;                       char radix,	// radix
;                       char width);	// minimum width
;

.func xitoa
.global xitoa
xitoa:
				;r25:r22 = value, r20 = base, r18 = digits
	clr	r31		;r31 = stack level
	ldi	r30, ' '	;r30 = sign
	ldi	r19, ' '	;r19 = filler
	sbrs	r20, 7		;When base indicates signd format and the value
	rjmp	0f		;is minus, add a '-'.
	neg	r20		;
	sbrs	r25, 7		;
	rjmp	0f		;
	ldi	r30, '-'	;
	com	r22		;
	com	r23		;
	com	r24		;
	com	r25		;
	adc	r22, r1		;
	adc	r23, r1		;
	adc	r24, r1		;
	adc	r25, r1		;/
0:	sbrs	r18, 7		;When digits indicates zero filled,
	rjmp	1f		;filler is '0'.
	neg	r18		;
	ldi	r19, '0'	;/
				;----- string conversion loop
1:	ldi	r21, 32		;r26 = r25:r22 % r20
	clr	r26		;r25:r22 /= r20
2:	lsl	r22		;
	rol	r23		;
	rol	r24		;
	rol	r25		;
	rol	r26		;
	cp	r26, r20	;
	brcs	3f		;
	sub	r26, r20	;
	inc	r22		;
3:	dec	r21		;
	brne	2b		;/
	cpi	r26, 10		;r26 is a numeral digit '0'-'F'
	brcs	4f		;
	subi	r26, -7		;
4:	subi	r26, -'0'	;/
	push	r26		;Stack it
	inc	r31		;/
	cp	r22, r1		;Repeat until r25:r22 gets zero
	cpc	r23, r1		;
	cpc	r24, r1		;
	cpc	r25, r1		;
	brne	1b		;/

	cpi	r30, '-'	;Minus sign if needed
	brne	5f		;
	push	r30		;
	inc	r31		;/
5:	cp	r31, r18	;Filler
	brcc	6f		;
	push	r19		;
	inc	r31		;
	rjmp	5b		;/

6:	pop	r24		;Flush stacked digits and exit
	rcall	xputc		;
	dec	r31		;
	brne	6b		;/

	ret
.endfunc



;---------------------------------------------------------------------------;
; Formatted string output (16/32bit version)
;
;Prototype:
; void __xprintf (const char *format_p, ...);
; void __xsprintf(char*, const char *format_p, ...);
; void __xfprintf(void(*func)(char), const char *format_p, ...);
;

#if USE_XPRINTF

.func xvprintf
xvprintf:
	ld	ZL, Y+		;Z = pointer to format string
	ld	ZH, Y+		;/

0:	_LPMI	r24		;Get a format char
	cpi	r24, 0		;End of format string?
	breq	90f		;/
	cpi	r24, '%'	;Is format?
	breq	20f		;/
1:	rcall	xputc		;Put a normal character
	rjmp	0b		;/
90:	ret

20:	ldi	r18, 0		;r18: digits
	clt			;T: filler
	_LPMI	r21		;Get flags
	cpi	r21, '%'	;Is a %?
	breq	1b		;/
	cpi	r21, '0'	;Zero filled?
	brne	23f		;
	set			;/
22:	_LPMI	r21		;Get width
23:	cpi	r21, '9'+1	;
	brcc	24f		;
	subi	r21, '0'	;
	brcs	90b		;
	lsl	r18		;
	mov	r0, r18		;
	lsl	r18		;
	lsl	r18		;
	add	r18, r0		;
	add	r18, r21	;
	rjmp	22b		;/

24:	brtc	25f		;get value (low word)
	neg	r18		;
25:	ld	r24, Y+		;
	ld	r25, Y+		;/
	cpi	r21, 'c'	;Is type character?
	breq	1b		;/
	cpi	r21, 's'	;Is type RAM string?
	breq	50f		;/
	cpi	r21, 'S'	;Is type ROM string?
	breq	60f		;/
	_MOVW	r23,r22,r25,r24	;r25:r22 = value
	clr	r24		;
	clr	r25		;
	clt			;/
	cpi	r21, 'l'	;Is long int?
	brne	26f		;
	ld	r24, Y+		;get value (high word)
	ld	r25, Y+		;
	set			;
	_LPMI	r21		;/
26:	cpi	r21, 'd'	;Is type signed decimal?
	brne	27f		;/
	ldi	r20, -10	;
	brts	40f		;
	sbrs	r23, 7		;
	rjmp	40f		;
	ldi	r24, -1		;
	ldi	r25, -1		;
	rjmp	40f		;/
27:	cpi	r21, 'u'	;Is type unsigned decimal?
	ldi	r20, 10		;
	breq	40f		;/
	cpi	r21, 'X'	;Is type hexdecimal?
	ldi	r20, 16		;
	breq	40f		;/
	cpi	r21, 'b'	;Is type binary?
	ldi	r20, 2		;
	breq	40f		;/
	ret			;abort
40:	push	ZH		;Output the value
	push	ZL		;
	rcall	xitoa		;
42:	pop	ZL		;
	pop	ZH		;
	rjmp	0b		;/

50:	push	ZH		;Put a string on the RAM
	push	ZL
	_MOVW	ZH,ZL, r25,r24
51:	ld	r24, Z+
	cpi	r24, 0
	breq	42b
	rcall	xputc
	rjmp	51b

60:	push	ZH		;Put a string on the ROM
	push	ZL
	rcall	xputs
	rjmp	42b
.endfunc


.func __xprintf
.global __xprintf
__xprintf:
	push	YH
	push	YL
	in	YL, _SFR_IO_ADDR(SPL)
#ifdef SPH
	in	YH, _SFR_IO_ADDR(SPH)
#else
	clr	YH
#endif
	adiw	YL, 5		;Y = pointer to arguments
	rcall	xvprintf
	pop	YL
	pop	YH
	ret
.endfunc


#if USE_XSPRINTF

.func __xsprintf
putram:
	_MOVW	ZH,ZL, r15,r14
	st	Z+, r24
	_MOVW	r15,r14, ZH,ZL
	ret
.global __xsprintf
__xsprintf:
	push	YH
	push	YL
	in	YL, _SFR_IO_ADDR(SPL)
#ifdef SPH
	in	YH, _SFR_IO_ADDR(SPH)
#else
	clr	YH
#endif
	adiw	YL, 5		;Y = pointer to arguments
	lds	ZL, xfunc_out+0	;Save registered output function
	lds	ZH, xfunc_out+1	;
	push	ZL		;
	push	ZH		;/
	ldi	ZL, lo8(pm(putram));Set local output function
	ldi	ZH, hi8(pm(putram));
	sts	xfunc_out+0, ZL	;
	sts	xfunc_out+1, ZH	;/
	push	r15		;Initialize pointer to string buffer
	push	r14		;
	ld	r14, Y+		;
	ld	r15, Y+		;/
	rcall	xvprintf
	_MOVW	ZH,ZL, r15,r14	;Terminate string
	st	Z, r1		;
	pop	r14		;
	pop	r15		;/
	pop	ZH		;Restore registered output function
	pop	ZL		;
	sts	xfunc_out+0, ZL	;
	sts	xfunc_out+1, ZH	;/
	pop	YL
	pop	YH
	ret
.endfunc
#endif


#if USE_XFPRINTF
.func __xfprintf
.global __xfprintf
__xfprintf:
	push	YH
	push	YL
	in	YL, _SFR_IO_ADDR(SPL)
#ifdef SPH
	in	YH, _SFR_IO_ADDR(SPH)
#else
	clr	YH
#endif
	adiw	YL, 5		;Y = pointer to arguments
	lds	ZL, xfunc_out+0	;Save registered output function
	lds	ZH, xfunc_out+1	;
	push	ZL		;
	push	ZH		;/
	ld	ZL, Y+		;Set output function
	ld	ZH, Y+		;
	sts	xfunc_out+0, ZL	;
	sts	xfunc_out+1, ZH	;/
	rcall	xvprintf
	pop	ZH		;Restore registered output function
	pop	ZL		;
	sts	xfunc_out+0, ZL	;
	sts	xfunc_out+1, ZH	;/
	pop	YL
	pop	YH
	ret
.endfunc
#endif

#endif



;---------------------------------------------------------------------------
; Extended numeral string input
;
;Prototype:
; char xatoi (           /* 1: Successful, 0: Failed */
;      const char **str, /* pointer to pointer to source string */
;      long *res         /* result */
; );
;


#if USE_XATOI
.func xatoi
.global xatoi
xatoi:
	_MOVW	r1, r0, r23, r22
	_MOVW	XH, XL, r25, r24
	ld	ZL, X+
	ld	ZH, X+
	clr	r18		;r21:r18 = 0;
	clr	r19		;
	clr	r20		;
	clr	r21		;/
	clt			;T = 0;

	ldi	r25, 10		;r25 = 10;
	rjmp	41f		;/
40:	adiw	ZL, 1		;Z++;
41:	ld	r22, Z		;r22 = *Z;
	cpi	r22, ' '	;if(r22 == ' ') continue
	breq	40b		;/
	brcs	70f		;if(r22 < ' ') error;
	cpi	r22, '-'	;if(r22 == '-') {
	brne	42f		; T = 1;
	set			; continue;
	rjmp	40b		;}
42:	cpi	r22, '9'+1	;if(r22 > '9') error;
	brcc	70f		;/
	cpi	r22, '0'	;if(r22 < '0') error;
	brcs	70f		;/
	brne	51f		;if(r22 > '0') cv_start;
	ldi	r25, 8		;r25 = 8;
	adiw	ZL, 1		;r22 = *(++Z);
	ld	r22, Z		;/
	cpi	r22, ' '+1	;if(r22 <= ' ') exit;
	brcs	80f		;/
	cpi	r22, 'b'	;if(r22 == 'b') {
	brne	43f		; r25 = 2;
	ldi	r25, 2		; cv_start;
	rjmp	50f		;}
43:	cpi	r22, 'x'	;if(r22 != 'x') error;
	brne	51f		;/
	ldi	r25, 16		;r25 = 16;

50:	adiw	ZL, 1		;Z++;
	ld	r22, Z		;r22 = *Z;
51:	cpi	r22, ' '+1	;if(r22 <= ' ') break;
	brcs	80f		;/
	cpi	r22, 'a'	;if(r22 >= 'a') r22 =- 0x20;
	brcs	52f		;
	subi	r22, 0x20	;/
52:	subi	r22, '0'	;if((r22 -= '0') < 0) error;
	brcs	70f		;/
	cpi	r22, 10		;if(r22 >= 10) {
	brcs	53f		; r22 -= 7;
	subi	r22, 7		; if(r22 < 10) 
	cpi	r22, 10		;
	brcs	70f		;}
53:	cp	r22, r25	;if(r22 >= r25) error;
	brcc	70f		;/
60:	ldi	r24, 33		;r21:r18 *= r25;
	sub	r23, r23	;
61:	brcc	62f		;
	add	r23, r25	;
62:	lsr	r23		;
	ror	r21		;
	ror	r20		;
	ror	r19		;
	ror	r18		;
	dec	r24		;
	brne	61b		;/
	add	r18, r22	;r21:r18 += r22;
	adc	r19, r24	;
	adc	r20, r24	;
	adc	r21, r24	;/
	rjmp	50b		;repeat

70:	ldi	r24, 0
	rjmp	81f
80:	ldi	r24, 1
81:	brtc	82f
	clr	r22
	com	r18
	com	r19
	com	r20
	com	r21
	adc	r18, r22
	adc	r19, r22
	adc	r20, r22
	adc	r21, r22
82:	st	-X, ZH
	st	-X, ZL
	_MOVW	XH, XL, r1, r0
	st	X+, r18
	st	X+, r19
	st	X+, r20
	st	X+, r21
	clr	r1
	ret
.endfunc
#endif


