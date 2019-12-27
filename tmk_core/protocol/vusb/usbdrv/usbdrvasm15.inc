/* Name: usbdrvasm15.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: contributed by V. Bosch
 * Creation Date: 2007-08-06
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * Revision: $Id: usbdrvasm15.inc 740 2009-04-13 18:23:31Z cs $
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 15 MHz version of the asssembler part of the USB driver. It
requires a 15 MHz crystal (not a ceramic resonator and not a calibrated RC
oscillator).

See usbdrv.h for a description of the entire driver.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!
*/

;max stack usage: [ret(2), YL, SREG, YH, bitcnt, shift, x1, x2, x3, x4, cnt] = 12 bytes
;nominal frequency: 15 MHz -> 10.0 cycles per bit, 80.0 cycles per byte
; Numbers in brackets are clocks counted from center of last sync bit
; when instruction starts

;----------------------------------------------------------------------------
; order of registers pushed: 
;	YL, SREG [sofError] YH, shift, x1, x2, x3, bitcnt, cnt, x4
;----------------------------------------------------------------------------
USB_INTR_VECTOR:              
    push    YL                   ;2 	push only what is necessary to sync with edge ASAP
    in      YL, SREG             ;1 
    push    YL                   ;2 
;----------------------------------------------------------------------------
; Synchronize with sync pattern:
;
;   sync byte (D-) pattern LSb to MSb: 01010100 [1 = idle = J, 0 = K]
;   sync up with J to K edge during sync pattern -- use fastest possible loops
;The first part waits at most 1 bit long since we must be in sync pattern.
;YL is guarenteed to be < 0x80 because I flag is clear. When we jump to
;waitForJ, ensure that this prerequisite is met.
waitForJ:
    inc     YL
    sbis    USBIN, USBMINUS
    brne    waitForJ        ; just make sure we have ANY timeout
;-------------------------------------------------------------------------------
; The following code results in a sampling window of < 1/4 bit 
;	which meets the spec.
;-------------------------------------------------------------------------------
waitForK:			 ;- 
    sbis    USBIN, USBMINUS      ;1 [00] <-- sample
    rjmp    foundK               ;2 [01]
    sbis    USBIN, USBMINUS	 ;	 <-- sample
    rjmp    foundK
    sbis    USBIN, USBMINUS	 ;	 <-- sample
    rjmp    foundK
    sbis    USBIN, USBMINUS	 ;	 <-- sample
    rjmp    foundK
    sbis    USBIN, USBMINUS	 ;	 <-- sample
    rjmp    foundK
    sbis    USBIN, USBMINUS	 ;	 <-- sample
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
;------------------------------------------------------------------------------
; {3, 5} after falling D- edge, average delay: 4 cycles [we want 5 for 
;	center sampling] 
; 	we have 1 bit time for setup purposes, then sample again. 
;	Numbers in brackets are cycles from center of first sync (double K) 
;	bit after the instruction
;------------------------------------------------------------------------------
foundK:                          ;- [02]
    lds     YL, usbInputBufOffset;2 [03+04]	tx loop
    push    YH                   ;2 [05+06]
    clr     YH                   ;1 [07]
    subi    YL, lo8(-(usbRxBuf)) ;1 [08] 	[rx loop init]
    sbci    YH, hi8(-(usbRxBuf)) ;1 [09] 	[rx loop init]
    push    shift                ;2 [10+11]
    ser	    shift		 ;1 [12]
    sbis    USBIN, USBMINUS      ;1 [-1] [13] <--sample:we want two bits K (sample 1 cycle too early)
    rjmp    haveTwoBitsK         ;2 [00] [14]
    pop     shift                ;2 	 [15+16] undo the push from before
    pop     YH 			 ;2 	 [17+18] undo the push from before
    rjmp    waitForK             ;2 	 [19+20] this was not the end of sync, retry
; The entire loop from waitForK until rjmp waitForK above must not exceed two
; bit times (= 20 cycles).

;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
haveTwoBitsK:			;- [01]
    push    x1              	;2 [02+03]
    push    x2              	;2 [04+05]
    push    x3              	;2 [06+07]
    push    bitcnt              ;2 [08+09]	
    in      x1, USBIN       	;1 [00] [10] <-- sample bit 0
    bst     x1, USBMINUS    	;1 [01]
    bld     shift, 0        	;1 [02]
    push    cnt             	;2 [03+04]
    ldi     cnt, USB_BUFSIZE	;1 [05] 
    push    x4              	;2 [06+07] tx loop
    rjmp    rxLoop          	;2 [08]
;----------------------------------------------------------------------------
; Receiver loop (numbers in brackets are cycles within byte after instr)
;----------------------------------------------------------------------------
unstuff0:               	;- [07] (branch taken)
    andi    x3, ~0x01   	;1 [08]
    mov     x1, x2      	;1 [09] x2 contains last sampled (stuffed) bit
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 1 again
    andi    x2, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 1 
    ori     shift, 0x01 	;1 [03] 0b00000001
    nop				;1 [04]
    rjmp    didUnstuff0 	;2 [05]
;-----------------------------------------------------
unstuff1:               	;- [05] (branch taken)
    mov     x2, x1      	;1 [06] x1 contains last sampled (stuffed) bit
    andi    x3, ~0x02   	;1 [07]
    ori     shift, 0x02 	;1 [08] 0b00000010
    nop                 	;1 [09]
    in      x1, USBIN   	;1 [00] [10] <-- sample bit 2 again
    andi    x1, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 2 
    rjmp    didUnstuff1 	;2 [03]
;-----------------------------------------------------
unstuff2:               	;- [05] (branch taken)
    andi    x3, ~0x04   	;1 [06]
    ori     shift, 0x04 	;1 [07] 0b00000100
    mov     x1, x2      	;1 [08] x2 contains last sampled (stuffed) bit
    nop                 	;1 [09]
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 3
    andi    x2, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 3 
    rjmp    didUnstuff2 	;2 [03]
;-----------------------------------------------------
unstuff3:               	;- [00] [10]  (branch taken)
    in      x2, USBIN   	;1 [01] [11] <-- sample stuffed bit 3 one cycle too late
    andi    x2, USBMASK 	;1 [02]
    breq    se0Hop         	;1 [03] SE0 check for stuffed bit 3 
    andi    x3, ~0x08   	;1 [04]
    ori     shift, 0x08 	;1 [05] 0b00001000
    rjmp    didUnstuff3 	;2 [06]
;----------------------------------------------------------------------------
; extra jobs done during bit interval:
;
; bit 0:    store, clear [SE0 is unreliable here due to bit dribbling in hubs], 
; 		overflow check, jump to the head of rxLoop
; bit 1:    SE0 check
; bit 2:    SE0 check, recovery from delay [bit 0 tasks took too long]
; bit 3:    SE0 check, recovery from delay [bit 0 tasks took too long]
; bit 4:    SE0 check, none
; bit 5:    SE0 check, none
; bit 6:    SE0 check, none
; bit 7:    SE0 check, reconstruct: x3 is 0 at bit locations we changed, 1 at others
;----------------------------------------------------------------------------
rxLoop:				;- [09]
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 1 (or possibly bit 0 stuffed)
    andi    x2, USBMASK 	;1 [01]
    brne    SkipSe0Hop		;1 [02]
se0Hop:				;- [02]
    rjmp    se0         	;2 [03] SE0 check for bit 1 
SkipSe0Hop:			;- [03]
    ser     x3          	;1 [04]
    andi    shift, 0xf9 	;1 [05] 0b11111001
    breq    unstuff0    	;1 [06]
didUnstuff0:			;- [06]
    eor     x1, x2      	;1 [07]
    bst     x1, USBMINUS	;1 [08]
    bld     shift, 1    	;1 [09] 
    in      x1, USBIN   	;1 [00] [10] <-- sample bit 2 (or possibly bit 1 stuffed)
    andi    x1, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 2 
    andi    shift, 0xf3 	;1 [03] 0b11110011
    breq    unstuff1    	;1 [04] do remaining work for bit 1
didUnstuff1:			;- [04]
    eor     x2, x1      	;1 [05]
    bst     x2, USBMINUS	;1 [06]
    bld     shift, 2    	;1 [07]
    nop2			;2 [08+09]
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 3 (or possibly bit 2 stuffed)
    andi    x2, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 3 
    andi    shift, 0xe7 	;1 [03] 0b11100111
    breq    unstuff2    	;1 [04]
didUnstuff2:			;- [04]
    eor     x1, x2      	;1 [05]
    bst     x1, USBMINUS	;1 [06]
    bld     shift, 3    	;1 [07]
didUnstuff3:			;- [07]
    andi    shift, 0xcf 	;1 [08] 0b11001111
    breq    unstuff3    	;1 [09]
    in      x1, USBIN   	;1 [00] [10] <-- sample bit 4
    andi    x1, USBMASK 	;1 [01]
    breq    se0Hop         	;1 [02] SE0 check for bit 4
    eor     x2, x1      	;1 [03]
    bst     x2, USBMINUS	;1 [04]
    bld     shift, 4    	;1 [05]
didUnstuff4:			;- [05]
    andi    shift, 0x9f 	;1 [06] 0b10011111
    breq    unstuff4    	;1 [07]
    nop2			;2 [08+09]
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 5
    andi    x2, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for bit 5
    eor     x1, x2      	;1 [03]
    bst     x1, USBMINUS	;1 [04]
    bld     shift, 5    	;1 [05]
didUnstuff5:			;- [05]
    andi    shift, 0x3f 	;1 [06] 0b00111111
    breq    unstuff5    	;1 [07]
    nop2			;2 [08+09]
    in      x1, USBIN   	;1 [00] [10] <-- sample bit 6
    andi    x1, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for bit 6
    eor     x2, x1      	;1 [03]
    bst     x2, USBMINUS	;1 [04]
    bld     shift, 6   	 	;1 [05]
didUnstuff6:			;- [05]
    cpi     shift, 0x02 	;1 [06] 0b00000010
    brlo    unstuff6    	;1 [07]
    nop2			;2 [08+09]
    in      x2, USBIN   	;1 [00] [10] <-- sample bit 7
    andi    x2, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for bit 7
    eor     x1, x2      	;1 [03]
    bst     x1, USBMINUS	;1 [04]
    bld     shift, 7    	;1 [05]
didUnstuff7:			;- [05] 
    cpi     shift, 0x04 	;1 [06] 0b00000100
    brlo    unstuff7		;1 [07]
    eor     x3, shift   	;1 [08] reconstruct: x3 is 0 at bit locations we changed, 1 at others
    nop				;1 [09]
    in      x1, USBIN   	;1 [00]	[10] <-- sample bit 0
    st      y+, x3      	;2 [01+02] store data
    eor     x2, x1      	;1 [03]
    bst     x2, USBMINUS	;1 [04]
    bld     shift, 0    	;1 [05]
    subi    cnt, 1		;1 [06]
    brcs    overflow	;1 [07]
    rjmp    rxLoop		;2 [08]
;-----------------------------------------------------
unstuff4:               	;- [08] 
    andi    x3, ~0x10   	;1 [09]
    in      x1, USBIN   	;1 [00] [10] <-- sample stuffed bit 4
    andi    x1, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for stuffed bit 4
    ori     shift, 0x10 	;1 [03]
    rjmp    didUnstuff4 	;2 [04]
;-----------------------------------------------------
unstuff5:               	;- [08] 
    ori     shift, 0x20 	;1 [09]
    in      x2, USBIN   	;1 [00] [10] <-- sample stuffed bit 5
    andi    x2, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for stuffed bit 5
    andi    x3, ~0x20   	;1 [03]
    rjmp    didUnstuff5		;2 [04]
;-----------------------------------------------------
unstuff6:               	;- [08] 
    andi    x3, ~0x40   	;1 [09]
    in      x1, USBIN   	;1 [00] [10] <-- sample stuffed bit 6
    andi    x1, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for stuffed bit 6
    ori     shift, 0x40 	;1 [03]
    rjmp    didUnstuff6 	;2 [04]
;-----------------------------------------------------
unstuff7:			;- [08]
    andi    x3, ~0x80   	;1 [09]
    in      x2, USBIN   	;1 [00] [10] <-- sample stuffed bit 7
    andi    x2, USBMASK 	;1 [01]
    breq    se0         	;1 [02] SE0 check for stuffed bit 7
    ori     shift, 0x80 	;1 [03]
    rjmp    didUnstuff7 	;2 [04]
    
macro POP_STANDARD ; 16 cycles
    pop     x4    
    pop     cnt
    pop     bitcnt
    pop     x3
    pop     x2
    pop     x1
    pop     shift
    pop     YH
    endm
macro POP_RETI     ; 5 cycles
    pop     YL
    out     SREG, YL
    pop     YL
    endm

#include "asmcommon.inc"

;---------------------------------------------------------------------------
; USB spec says:
; idle = J
; J = (D+ = 0), (D- = 1)
; K = (D+ = 1), (D- = 0)
; Spec allows 7.5 bit times from EOP to SOP for replies
;---------------------------------------------------------------------------
bitstuffN:		    	;- [04]
    eor     x1, x4          	;1 [05]
    clr	    x2			;1 [06]
    nop				;1 [07]
    rjmp    didStuffN       	;1 [08]
;---------------------------------------------------------------------------    
bitstuff6:		    	;- [04]
    eor     x1, x4          	;1 [05]
    clr	    x2			;1 [06]
    rjmp    didStuff6       	;1 [07]
;---------------------------------------------------------------------------
bitstuff7:		    	;- [02]
    eor     x1, x4          	;1 [03]
    clr	    x2			;1 [06]
    nop			    	;1 [05]
    rjmp    didStuff7       	;1 [06]
;---------------------------------------------------------------------------
sendNakAndReti:			;- [-19]
    ldi     x3, USBPID_NAK  	;1 [-18]
    rjmp    sendX3AndReti   	;1 [-17]
;---------------------------------------------------------------------------
sendAckAndReti:			;- [-17]
    ldi     cnt, USBPID_ACK 	;1 [-16]
sendCntAndReti:			;- [-16]
    mov     x3, cnt         	;1 [-15]
sendX3AndReti:			;- [-15]
    ldi     YL, 20          	;1 [-14] x3==r20 address is 20
    ldi     YH, 0           	;1 [-13]
    ldi     cnt, 2          	;1 [-12]
;   rjmp    usbSendAndReti      fallthrough
;---------------------------------------------------------------------------
;usbSend:
;pointer to data in 'Y'
;number of bytes in 'cnt' -- including sync byte [range 2 ... 12]
;uses: x1...x4, btcnt, shift, cnt, Y
;Numbers in brackets are time since first bit of sync pattern is sent
;We need not to match the transfer rate exactly because the spec demands 
;only 1.5% precision anyway.
usbSendAndReti:             	;- [-13] 13 cycles until SOP
    in      x2, USBDDR      	;1 [-12]
    ori     x2, USBMASK     	;1 [-11]
    sbi     USBOUT, USBMINUS	;2 [-09-10] prepare idle state; D+ and D- must have been 0 (no pullups)
    in      x1, USBOUT      	;1 [-08] port mirror for tx loop
    out     USBDDR, x2      	;1 [-07] <- acquire bus
	; need not init x2 (bitstuff history) because sync starts with 0 
    ldi     x4, USBMASK     	;1 [-06] 	exor mask
    ldi     shift, 0x80     	;1 [-05] 	sync byte is first byte sent
    ldi     bitcnt, 6    	;1 [-04] 
txBitLoop:		    	;- [-04] [06]
    sbrs    shift, 0        	;1 [-03] [07]
    eor     x1, x4          	;1 [-02] [08] 
    ror     shift           	;1 [-01] [09]  
didStuffN:		    	;-       [09]
    out     USBOUT, x1      	;1 [00]  [10] <-- out N
    ror     x2              	;1 [01]
    cpi     x2, 0xfc        	;1 [02]
    brcc    bitstuffN       	;1 [03]
    dec     bitcnt          	;1 [04]
    brne    txBitLoop       	;1 [05]
    sbrs    shift, 0        	;1 [06]
    eor     x1, x4          	;1 [07]
    ror     shift           	;1 [08]
didStuff6:			;- [08]
    nop				;1 [09]
    out     USBOUT, x1      	;1 [00] [10] <-- out 6
    ror     x2              	;1 [01] 
    cpi     x2, 0xfc        	;1 [02]
    brcc    bitstuff6       	;1 [03]
    sbrs    shift, 0        	;1 [04]
    eor     x1, x4          	;1 [05]
    ror     shift           	;1 [06]
    ror     x2              	;1 [07]
didStuff7:			;- [07]
    ldi     bitcnt, 6    	;1 [08]
    cpi     x2, 0xfc        	;1 [09]
    out     USBOUT, x1      	;1 [00] [10] <-- out 7
    brcc    bitstuff7       	;1 [01]
    ld      shift, y+       	;2 [02+03]
    dec     cnt             	;1 [04]
    brne    txBitLoop      	;1 [05]
makeSE0:
    cbr     x1, USBMASK     	;1 [06] 	prepare SE0 [spec says EOP may be 19 to 23 cycles]
    lds     x2, usbNewDeviceAddr;2 [07+08]
    lsl     x2                  ;1 [09] we compare with left shifted address
;2006-03-06: moved transfer of new address to usbDeviceAddr from C-Code to asm:
;set address only after data packet was sent, not after handshake
    out     USBOUT, x1      	;1 [00] [10] <-- out SE0-- from now 2 bits==20 cycl. until bus idle
    subi    YL, 20 + 2          ;1 [01] Only assign address on data packets, not ACK/NAK in x3
    sbci    YH, 0           	;1 [02]
    breq    skipAddrAssign  	;1 [03]
    sts     usbDeviceAddr, x2	;2 [04+05] if not skipped: SE0 is one cycle longer
;----------------------------------------------------------------------------
;end of usbDeviceAddress transfer
skipAddrAssign:				;- [03/04]
    ldi     x2, 1<<USB_INTR_PENDING_BIT	;1 [05] int0 occurred during TX -- clear pending flag
    USB_STORE_PENDING(x2)           ;1 [06]
    ori     x1, USBIDLE     		;1 [07]
    in      x2, USBDDR      		;1 [08]
    cbr     x2, USBMASK     		;1 [09] set both pins to input
    mov     x3, x1          		;1 [10]
    cbr     x3, USBMASK     		;1 [11] configure no pullup on both pins
    ldi     x4, 3           		;1 [12]
se0Delay:				;- [12] [15] 
    dec     x4              		;1 [13] [16] 
    brne    se0Delay        		;1 [14] [17] 
    nop2				;2      [18+19]
    out     USBOUT, x1      		;1      [20] <--out J (idle) -- end of SE0 (EOP sig.)
    out     USBDDR, x2      		;1      [21] <--release bus now
    out     USBOUT, x3      		;1      [22] <--ensure no pull-up resistors are active
    rjmp    doReturn			;1	[23]
;---------------------------------------------------------------------------
