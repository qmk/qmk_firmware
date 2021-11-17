/* Name: usbdrvasm18.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Lukas Schrittwieser (based on 20 MHz usbdrvasm20.inc by Jeroen Benschop)
 * Creation Date: 2009-01-20
 * Tabsize: 4
 * Copyright: (c) 2008 by Lukas Schrittwieser and OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * Revision: $Id: usbdrvasm18-crc.inc 740 2009-04-13 18:23:31Z cs $
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 18 MHz version of the asssembler part of the USB driver. It
requires a 18 MHz crystal (not a ceramic resonator and not a calibrated RC
oscillator).

See usbdrv.h for a description of the entire driver.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!
*/


;max stack usage: [ret(2), YL, SREG, YH, [sofError], bitcnt(x5), shift, x1, x2, x3, x4, cnt, ZL, ZH] = 14 bytes
;nominal frequency: 18 MHz -> 12 cycles per bit
; Numbers in brackets are clocks counted from center of last sync bit
; when instruction starts
;register use in receive loop to receive the data bytes:
; shift assembles the byte currently being received
; x1 holds the D+ and D- line state
; x2 holds the previous line state
; cnt holds the number of bytes left in the receive buffer
; x3 holds the higher crc byte (see algorithm below)
; x4 is used as temporary register for the crc algorithm
; x5 is used for unstuffing: when unstuffing the last received bit is inverted in shift (to prevent further
;    unstuffing calls. In the same time the corresponding bit in x5 is cleared to mark the bit as beening iverted
; zl lower crc value and crc table index
; zh used for crc table accesses

;--------------------------------------------------------------------------------------------------------------
; CRC mods:
;  table driven crc checker, Z points to table in prog space
;   ZL is the lower crc byte, x3 is the higher crc byte
;	x4 is used as temp register to store different results
;	the initialization of the crc register is not 0xFFFF but 0xFE54. This is because during the receipt of the
;	first data byte an virtual zero data byte is added to the crc register, this results in the correct initial
;	value of 0xFFFF at beginning of the second data byte before the first data byte is added to the crc.
;	The magic number 0xFE54 results form the crc table: At tabH[0x54] = 0xFF = crcH (required) and
;	tabL[0x54] = 0x01  ->  crcL = 0x01 xor 0xFE = 0xFF
;  bitcnt is renamed to x5 and is used for unstuffing purposes, the unstuffing works like in the 12MHz version
;--------------------------------------------------------------------------------------------------------------
; CRC algorithm:
;	The crc register is formed by x3 (higher byte) and ZL (lower byte). The algorithm uses a 'reversed' form
;	i.e. that it takes the least significant bit first and shifts to the right. So in fact the highest order
;	bit seen from the polynomial devision point of view is the lsb of ZL. (If this sounds strange to you i
;	propose a research on CRC :-) )
;	Each data byte received is xored to ZL, the lower crc byte. This byte now builds the crc
;	table index. Next the new high byte is loaded from the table and stored in x4 until we have space in x3
;	(its destination).
;	Afterwards the lower table is loaded from the table and stored in ZL (the old index is overwritten as
;	we don't need it anymore. In fact this is a right shift by 8 bits.) Now the old crc high value is xored
;	to ZL, this is the second shift of the old crc value. Now x4 (the temp reg) is moved to x3 and the crc
; 	calculation is done.
;	Prior to the first byte the two CRC register have to be initialized to 0xFFFF (as defined in usb spec)
;	however the crc engine also runs during the receipt of the first byte, therefore x3 and zl are initialized
;	to a magic number which results in a crc value of 0xFFFF after the first complete byte.
;
;	This algorithm is split into the extra cycles of the different bits:
;	bit7:	XOR the received byte to ZL
;	bit5:	load the new high byte to x4
;	bit6:	load the lower xor byte from the table, xor zl and x3, store result in zl (=the new crc low value)
;			move x4 (the new high byte) to x3, the crc value is ready
;


macro POP_STANDARD ; 18 cycles
    pop		ZH
    pop		ZL
	pop     cnt
    pop     x5
    pop     x3
    pop     x2
    pop     x1
    pop     shift
    pop     x4
    endm
macro POP_RETI     ; 7 cycles
    pop     YH
    pop     YL
    out     SREG, YL
    pop     YL
    endm

macro CRC_CLEANUP_AND_CHECK
	; the last byte has already been xored with the lower crc byte, we have to do the table lookup and xor
	; x3 is the higher crc byte, zl the lower one
	ldi		ZH, hi8(usbCrcTableHigh);[+1] get the new high byte from the table
	lpm		x2, Z				;[+2][+3][+4]
	ldi		ZH, hi8(usbCrcTableLow);[+5] get the new low xor byte from the table
	lpm		ZL, Z				;[+6][+7][+8]
	eor		ZL, x3				;[+7] xor the old high byte with the value from the table, x2:ZL now holds the crc value
	cpi		ZL, 0x01			;[+8] if the crc is ok we have a fixed remainder value of 0xb001 in x2:ZL (see usb spec)
	brne	ignorePacket		;[+9] detected a crc fault -> paket is ignored and retransmitted by the host
	cpi		x2, 0xb0			;[+10]
	brne	ignorePacket		;[+11] detected a crc fault -> paket is ignored and retransmitted by the host
    endm


USB_INTR_VECTOR:
;order of registers pushed: YL, SREG, YH, [sofError], x4, shift, x1, x2, x3, x5, cnt, ZL, ZH
    push    YL                  ;[-28] push only what is necessary to sync with edge ASAP
    in      YL, SREG            ;[-26]
    push    YL                  ;[-25]
    push    YH                  ;[-23]
;----------------------------------------------------------------------------
; Synchronize with sync pattern:
;----------------------------------------------------------------------------
;sync byte (D-) pattern LSb to MSb: 01010100 [1 = idle = J, 0 = K]
;sync up with J to K edge during sync pattern -- use fastest possible loops
;The first part waits at most 1 bit long since we must be in sync pattern.
;YL is guarenteed to be < 0x80 because I flag is clear. When we jump to
;waitForJ, ensure that this prerequisite is met.
waitForJ:
    inc     YL
    sbis    USBIN, USBMINUS
    brne    waitForJ        ; just make sure we have ANY timeout
waitForK:
;The following code results in a sampling window of < 1/4 bit which meets the spec.
    sbis    USBIN, USBMINUS     ;[-17]
    rjmp    foundK              ;[-16]
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
    sbis    USBIN, USBMINUS
    rjmp    foundK
#if USB_COUNT_SOF
    lds     YL, usbSofCount
    inc     YL
    sts     usbSofCount, YL
#endif  /* USB_COUNT_SOF */
#ifdef USB_SOF_HOOK
    USB_SOF_HOOK
#endif
    rjmp    sofError
foundK:                         ;[-15]
;{3, 5} after falling D- edge, average delay: 4 cycles
;bit0 should be at 30  (2.5 bits) for center sampling. Currently at 4 so 26 cylces till bit 0 sample
;use 1 bit time for setup purposes, then sample again. Numbers in brackets
;are cycles from center of first sync (double K) bit after the instruction
    push    x4                  ;[-14]
;   [---]                       ;[-13]
    lds     YL, usbInputBufOffset;[-12] used to toggle the two usb receive buffers
;   [---]                       ;[-11]
    clr     YH                  ;[-10]
    subi    YL, lo8(-(usbRxBuf));[-9] [rx loop init]
    sbci    YH, hi8(-(usbRxBuf));[-8] [rx loop init]
    push    shift               ;[-7]
;   [---]                       ;[-6]
    ldi		shift, 0x80			;[-5] the last bit is the end of byte marker for the pid receiver loop
    clc			      	      	;[-4] the carry has to be clear for receipt of pid bit 0
    sbis    USBIN, USBMINUS     ;[-3] we want two bits K (sample 3 cycles too early)
    rjmp    haveTwoBitsK        ;[-2]
    pop     shift               ;[-1] undo the push from before
    pop     x4                  ;[1]
    rjmp    waitForK            ;[3] this was not the end of sync, retry
; The entire loop from waitForK until rjmp waitForK above must not exceed two
; bit times (= 24 cycles).

;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
haveTwoBitsK:
    push    x1                  ;[0]
    push    x2                  ;[2]
    push    x3                  ;[4] crc high byte
    ldi     x2, 1<<USBPLUS      ;[6] [rx loop init] current line state is K state. D+=="1", D-=="0"
    push    x5                  ;[7]
    push    cnt                 ;[9]
    ldi     cnt, USB_BUFSIZE    ;[11]


;--------------------------------------------------------------------------------------------------------------
; receives the pid byte
; there is no real unstuffing algorithm implemented here as a stuffing bit is impossible in the pid byte.
; That's because the last four bits of the byte are the inverted of the first four bits. If we detect a
; unstuffing condition something went wrong and abort
; shift has to be initialized to 0x80
;--------------------------------------------------------------------------------------------------------------

; pid bit 0 - used for even more register saving (we need the z pointer)
	in      x1, USBIN           ;[0] sample line state
    andi    x1, USBMASK         ;[1] filter only D+ and D- bits
    eor		x2, x1				;[2] generate inverted of actual bit
	sbrc	x2, USBMINUS		;[3] if the bit is set we received a zero
	sec							;[4]
	ror		shift				;[5] we perform no unstuffing check here as this is the first bit
	mov		x2, x1				;[6]
	push	ZL					;[7]
								;[8]
	push	ZH					;[9]
								;[10]
	ldi		x3, 0xFE			;[11] x3 is the high order crc value


bitloopPid:						
	in      x1, USBIN           ;[0] sample line state
   	andi    x1, USBMASK         ;[1] filter only D+ and D- bits
    breq    nse0                ;[2] both lines are low so handle se0	
	eor		x2, x1				;[3] generate inverted of actual bit
	sbrc	x2, USBMINUS		;[4] set the carry if we received a zero
	sec							;[5]
	ror		shift				;[6]
	ldi		ZL, 0x54			;[7] ZL is the low order crc value
	ser		x4					;[8] the is no bit stuffing check here as the pid bit can't be stuffed. if so
								; some error occured. In this case the paket is discarded later on anyway.
	mov		x2, x1				;[9] prepare for the next cycle
	brcc	bitloopPid			;[10] while 0s drop out of shift we get the next bit
	eor		x4, shift			;[11] invert all bits in shift and store result in x4

;--------------------------------------------------------------------------------------------------------------
; receives data bytes and calculates the crc
; the last USBIN state has to be in x2
; this is only the first half, due to branch distanc limitations the second half of the loop is near the end
; of this asm file
;--------------------------------------------------------------------------------------------------------------

rxDataStart:
    in      x1, USBIN           ;[0] sample line state (note: a se0 check is not useful due to bit dribbling)
    ser		x5					;[1] prepare the unstuff marker register
    eor		x2, x1             	;[2] generates the inverted of the actual bit
    bst		x2, USBMINUS       	;[3] copy the bit from x2
    bld		shift, 0	        ;[4] and store it in shift
    mov		x2, shift	     	;[5] make a copy of shift for unstuffing check
    andi	x2, 0xF9	      	;[6] mask the last six bits, if we got six zeros (which are six ones in fact)
    breq	unstuff0	      	;[7] then Z is set now and we branch to the unstuffing handler
didunstuff0:
	subi    cnt, 1         		;[8] cannot use dec because it doesn't affect the carry flag
    brcs    nOverflow    		;[9] Too many bytes received. Ignore packet							
    st		Y+, x4				;[10] store the last received byte
								;[11] st needs two cycles

; bit1							
	in		x2, USBIN			;[0] sample line state
    andi	x1, USBMASK			;[1] check for se0 during bit 0
    breq	nse0				;[2]
    andi	x2, USBMASK			;[3] check se0 during bit 1
    breq	nse0				;[4]
	eor		x1, x2				;[5]
    bst		x1, USBMINUS		;[6]
    bld 	shift, 1	 		;[7]
    mov		x1, shift			;[8]
    andi	x1, 0xF3			;[9]
    breq	unstuff1			;[10]
didunstuff1:
	nop							;[11]	

; bit2
	in      x1, USBIN           ;[0] sample line state
    andi	x1, USBMASK			;[1] check for se0 (as there is nothing else to do here
	breq	nOverflow	 		;[2]
    eor		x2, x1              ;[3] generates the inverted of the actual bit
    bst		x2, USBMINUS		;[4]
    bld		shift, 2			;[5] store the bit
    mov		x2, shift			;[6]
    andi	x2, 0xE7			;[7] if we have six zeros here (which means six 1 in the stream)
    breq	unstuff2			;[8] the next bit is a stuffing bit
didunstuff2:
	nop2						;[9]
								;[10]
	nop							;[11]					
					
; bit3							
	in		x2, USBIN			;[0] sample line state
    andi	x2, USBMASK			;[1] check for se0
    breq	nOverflow           ;[2]
    eor		x1, x2				;[3]
    bst		x1, USBMINUS		;[4]
    bld 	shift, 3	 		;[5]
    mov		x1, shift			;[6]
    andi	x1, 0xCF			;[7]
    breq	unstuff3			;[8]
didunstuff3:
	nop							;[9]
	rjmp 	rxDataBit4			;[10]
								;[11]				

; the avr branch instructions allow an offset of +63 insturction only, so we need this
; 'local copy' of se0
nse0:		
	rjmp	se0					;[4]
								;[5]
; the same same as for se0 is needed for overflow and StuffErr
nOverflow:
stuffErr:
	rjmp	overflow


unstuff0:						;[8] this is the branch delay of breq unstuffX
	andi	x1, USBMASK			;[9] do an se0 check here (if the last crc byte ends with 5 one's we might end up here
	breq	didunstuff0			;[10] event tough the message is complete -> jump back and store the byte
	ori		shift, 0x01			;[11] invert the last received bit to prevent furhter unstuffing
	in		x2, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	andi	x5, 0xFE			;[1] mark this bit as inverted (will be corrected before storing shift)
	eor		x1, x2				;[2] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x1, USBMASK			;[3] mask the interesting bits
	breq	stuffErr			;[4] if the stuff bit is a 1-bit something went wrong
	mov 	x1, x2				;[5] the next bit expects the last state to be in x1
	rjmp 	didunstuff0			;[6]
								;[7] jump delay of rjmp didunstuffX	

unstuff1:						;[11] this is the jump delay of breq unstuffX
	in		x1, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	ori		shift, 0x02			;[1] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xFD			;[2] mark this bit as inverted (will be corrected before storing shift)
	eor		x2, x1				;[3] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x2, USBMASK			;[4] mask the interesting bits
	breq	stuffErr			;[5] if the stuff bit is a 1-bit something went wrong
	mov 	x2, x1				;[6] the next bit expects the last state to be in x2
	nop2						;[7]
								;[8]
	rjmp 	didunstuff1			;[9]
								;[10] jump delay of rjmp didunstuffX		

unstuff2:						;[9] this is the jump delay of breq unstuffX
	ori		shift, 0x04			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xFB			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x2, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x1, x2				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x1, USBMASK			;[2] mask the interesting bits
	breq	stuffErr			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x1, x2				;[4] the next bit expects the last state to be in x1
	nop2						;[5]
								;[6]
	rjmp 	didunstuff2			;[7]
								;[8] jump delay of rjmp didunstuffX	

unstuff3:						;[9] this is the jump delay of breq unstuffX
	ori		shift, 0x08			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xF7			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x1, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x2, x1				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x2, USBMASK			;[2] mask the interesting bits
	breq	stuffErr			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x2, x1				;[4] the next bit expects the last state to be in x2
	nop2						;[5]
								;[6]
	rjmp 	didunstuff3			;[7]
								;[8] jump delay of rjmp didunstuffX			



; the include has to be here due to branch distance restirctions
#define __USE_CRC__
#include "asmcommon.inc"

	

; USB spec says:
; idle = J
; J = (D+ = 0), (D- = 1)
; K = (D+ = 1), (D- = 0)
; Spec allows 7.5 bit times from EOP to SOP for replies
; 7.5 bit times is 90 cycles. ...there is plenty of time


sendNakAndReti:
    ldi     x3, USBPID_NAK  ;[-18]
    rjmp    sendX3AndReti   ;[-17]
sendAckAndReti:
    ldi     cnt, USBPID_ACK ;[-17]
sendCntAndReti:
    mov     x3, cnt         ;[-16]
sendX3AndReti:
    ldi     YL, 20          ;[-15] x3==r20 address is 20
    ldi     YH, 0           ;[-14]
    ldi     cnt, 2          ;[-13]
;   rjmp    usbSendAndReti      fallthrough

;usbSend:
;pointer to data in 'Y'
;number of bytes in 'cnt' -- including sync byte [range 2 ... 12]
;uses: x1...x4, btcnt, shift, cnt, Y
;Numbers in brackets are time since first bit of sync pattern is sent

usbSendAndReti:             ; 12 cycles until SOP
    in      x2, USBDDR      ;[-12]
    ori     x2, USBMASK     ;[-11]
    sbi     USBOUT, USBMINUS;[-10] prepare idle state; D+ and D- must have been 0 (no pullups)
    in      x1, USBOUT      ;[-8] port mirror for tx loop
    out     USBDDR, x2      ;[-6] <- acquire bus
	ldi		x2, 0			;[-6] init x2 (bitstuff history) because sync starts with 0
    ldi     x4, USBMASK     ;[-5] exor mask
    ldi     shift, 0x80     ;[-4] sync byte is first byte sent
txByteLoop:
    ldi     bitcnt, 0x40    ;[-3]=[9]     binary 01000000
txBitLoop:					; the loop sends the first 7 bits of the byte
    sbrs    shift, 0        ;[-2]=[10] if we have to send a 1 don't change the line state
    eor     x1, x4          ;[-1]=[11]
    out     USBOUT, x1      ;[0]
    ror     shift           ;[1]
    ror     x2              ;[2] transfers the last sent bit to the stuffing history
didStuffN:
    nop	                    ;[3]
    nop                     ;[4]
    cpi     x2, 0xfc        ;[5] if we sent six consecutive ones
    brcc    bitstuffN       ;[6]
    lsr     bitcnt          ;[7]
    brne    txBitLoop       ;[8] restart the loop while the 1 is still in the bitcount

; transmit bit 7
    sbrs    shift, 0        ;[9]
    eor     x1, x4          ;[10]
didStuff7:
    ror     shift           ;[11]
	out     USBOUT, x1      ;[0] transfer bit 7 to the pins
    ror     x2              ;[1] move the bit into the stuffing history	
    cpi     x2, 0xfc        ;[2]
    brcc    bitstuff7       ;[3]
    ld      shift, y+       ;[4] get next byte to transmit
    dec     cnt             ;[5] decrement byte counter
    brne    txByteLoop      ;[7] if we have more bytes start next one
    						;[8] branch delay
    						
;make SE0:
    cbr     x1, USBMASK     ;[8] 		prepare SE0 [spec says EOP may be 25 to 30 cycles]
    lds     x2, usbNewDeviceAddr;[9]
    lsl     x2              ;[11] 		we compare with left shifted address
    out     USBOUT, x1      ;[0] 		<-- out SE0 -- from now 2 bits = 24 cycles until bus idle
    subi    YL, 20 + 2      ;[1] 		Only assign address on data packets, not ACK/NAK in x3
    sbci    YH, 0           ;[2]
;2006-03-06: moved transfer of new address to usbDeviceAddr from C-Code to asm:
;set address only after data packet was sent, not after handshake
    breq    skipAddrAssign  ;[3]
    sts     usbDeviceAddr, x2		; if not skipped: SE0 is one cycle longer
skipAddrAssign:
;end of usbDeviceAddress transfer
    ldi     x2, 1<<USB_INTR_PENDING_BIT;[5] int0 occurred during TX -- clear pending flag
    USB_STORE_PENDING(x2)   ;[6]
    ori     x1, USBIDLE     ;[7]
    in      x2, USBDDR      ;[8]
    cbr     x2, USBMASK     ;[9] set both pins to input
    mov     x3, x1          ;[10]
    cbr     x3, USBMASK     ;[11] configure no pullup on both pins
    ldi     x4, 4           ;[12]
se0Delay:
    dec     x4              ;[13] [16] [19] [22]
    brne    se0Delay        ;[14] [17] [20] [23]
    out     USBOUT, x1      ;[24] <-- out J (idle) -- end of SE0 (EOP signal)
    out     USBDDR, x2      ;[25] <-- release bus now
    out     USBOUT, x3      ;[26] <-- ensure no pull-up resistors are active
    rjmp    doReturn

bitstuffN:
    eor     x1, x4          ;[8] generate a zero
    ldi     x2, 0           ;[9] reset the bit stuffing history
    nop2                    ;[10]
    out     USBOUT, x1      ;[0] <-- send the stuffing bit
    rjmp    didStuffN       ;[1]

bitstuff7:
    eor     x1, x4          ;[5]
    ldi     x2, 0           ;[6] reset bit stuffing history
    clc						;[7] fill a zero into the shift register
    rol     shift           ;[8] compensate for ror shift at branch destination
    rjmp    didStuff7       ;[9]
    						;[10] jump delay

;--------------------------------------------------------------------------------------------------------------
; receives data bytes and calculates the crc
; second half of the data byte receiver loop
; most parts of the crc algorithm are here
;--------------------------------------------------------------------------------------------------------------

nOverflow2:
	rjmp overflow

rxDataBit4:
	in      x1, USBIN           ;[0] sample line state
    andi	x1, USBMASK			;[1] check for se0
    breq	nOverflow2			;[2]
    eor		x2, x1              ;[3]
    bst		x2, USBMINUS		;[4]
    bld		shift, 4			;[5]
    mov		x2, shift			;[6]
    andi	x2, 0x9F			;[7]
    breq	unstuff4			;[8]
didunstuff4:
	nop2						;[9][10]
	nop							;[11]

; bit5							
	in		x2, USBIN			;[0] sample line state
    ldi		ZH, hi8(usbCrcTableHigh);[1] use the table for the higher byte
    eor		x1, x2				;[2]
    bst		x1, USBMINUS		;[3]
    bld 	shift, 5	 		;[4]
    mov		x1, shift			;[5]
    andi	x1, 0x3F			;[6]
    breq	unstuff5			;[7]
didunstuff5:
	lpm		x4, Z				;[8] load the higher crc xor-byte and store it for later use
								;[9] lpm needs 3 cycles
								;[10]			
	ldi		ZH, hi8(usbCrcTableLow);[11] load the lower crc xor byte adress

; bit6	    					
	in      x1, USBIN           ;[0] sample line state
    eor		x2, x1              ;[1]
    bst		x2, USBMINUS		;[2]
    bld		shift, 6			;[3]
    mov		x2, shift			;[4]
    andi	x2, 0x7E			;[5]
    breq	unstuff6			;[6]
didunstuff6:
	lpm		ZL, Z				;[7] load the lower xor crc byte
								;[8] lpm needs 3 cycles
	    						;[9]
	eor		ZL, x3				;[10] xor the old high crc byte with the low xor-byte
	mov		x3, x4				;[11] move the new high order crc value from temp to its destination
			
; bit7							
	in		x2, USBIN			;[0] sample line state
    eor		x1, x2				;[1]
    bst		x1, USBMINUS		;[2]
    bld 	shift, 7	 		;[3] now shift holds the complete but inverted data byte
    mov		x1, shift			;[4]
    andi	x1, 0xFC			;[5]
    breq	unstuff7			;[6]
didunstuff7:
	eor		x5, shift			;[7] x5 marks all bits which have not been inverted by the unstuffing subs
	mov		x4, x5				;[8] keep a copy of the data byte it will be stored during next bit0
	eor		ZL, x4				;[9] feed the actual byte into the crc algorithm
	rjmp	rxDataStart			;[10] next byte
								;[11] during the reception of the next byte this one will be fed int the crc algorithm

unstuff4:						;[9] this is the jump delay of rjmp unstuffX
	ori		shift, 0x10			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xEF			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x2, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x1, x2				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x1, USBMASK			;[2] mask the interesting bits
	breq	stuffErr2			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x1, x2				;[4] the next bit expects the last state to be in x1
	nop2						;[5]
								;[6]
	rjmp 	didunstuff4			;[7]
								;[8] jump delay of rjmp didunstuffX	

unstuff5:						;[8] this is the jump delay of rjmp unstuffX
	nop							;[9]
	ori		shift, 0x20			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xDF			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x1, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x2, x1				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x2, USBMASK			;[2] mask the interesting bits
	breq	stuffErr2			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x2, x1				;[4] the next bit expects the last state to be in x2
	nop							;[5]
	rjmp 	didunstuff5			;[6]
								;[7] jump delay of rjmp didunstuffX													

unstuff6:						;[7] this is the jump delay of rjmp unstuffX
	nop2						;[8]
								;[9]
	ori		shift, 0x40			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0xBF			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x2, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x1, x2				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x1, USBMASK			;[2] mask the interesting bits
	breq	stuffErr2			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x1, x2				;[4] the next bit expects the last state to be in x1
	rjmp 	didunstuff6			;[5]
								;[6] jump delay of rjmp didunstuffX	

unstuff7:						;[7] this is the jump delay of rjmp unstuffX
	nop							;[8]
	nop							;[9]
	ori		shift, 0x80			;[10] invert the last received bit to prevent furhter unstuffing
	andi	x5, 0x7F			;[11] mark this bit as inverted (will be corrected before storing shift)
	in		x1, USBIN			;[0] we have some free cycles so we could check for bit stuffing errors
	eor		x2, x1				;[1] x1 and x2 have to be different because the stuff bit is always a zero
	andi	x2, USBMASK			;[2] mask the interesting bits
	breq	stuffErr2			;[3] if the stuff bit is a 1-bit something went wrong
	mov 	x2, x1				;[4] the next bit expects the last state to be in x2
	rjmp 	didunstuff7			;[5]
								;[6] jump delay of rjmp didunstuff7

; local copy of the stuffErr desitnation for the second half of the receiver loop
stuffErr2:
	rjmp	stuffErr

;--------------------------------------------------------------------------------------------------------------
; The crc table follows. It has to be aligned to enable a fast loading of the needed bytes.
; There are two tables of 256 entries each, the low and the high byte table.
; Table values were generated with the following C code:
/*
#include <stdio.h>
int main (int argc, char **argv)
{
	int i, j;
	for (i=0; i<512; i++){
		unsigned short crc = i & 0xff;
		for(j=0; j<8; j++) crc = (crc >> 1) ^ ((crc & 1) ? 0xa001 : 0);
		if((i & 7) == 0) printf("\n.byte ");
		printf("0x%02x, ", (i > 0xff ? (crc >> 8) : crc) & 0xff);
		if(i == 255) printf("\n");
	}
	return 0;
}

// Use the following algorithm to compute CRC values:
ushort computeCrc(uchar *msg, uchar msgLen)
{
    uchar i;
	ushort crc = 0xffff;
	for(i = 0; i < msgLen; i++)
		crc = usbCrcTable16[lo8(crc) ^ msg[i]] ^ hi8(crc);
    return crc;
}
*/

.balign 256
usbCrcTableLow:	
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41
.byte 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40

; .balign 256
usbCrcTableHigh:
.byte 0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2
.byte 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04
.byte 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E
.byte 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8
.byte 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A
.byte 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC
.byte 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6
.byte 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10
.byte 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32
.byte 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4
.byte 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE
.byte 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38
.byte 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA
.byte 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C
.byte 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26
.byte 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0
.byte 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62
.byte 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4
.byte 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE
.byte 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68
.byte 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA
.byte 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C
.byte 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76
.byte 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0
.byte 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92
.byte 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54
.byte 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E
.byte 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98
.byte 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A
.byte 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C
.byte 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86
.byte 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40	

