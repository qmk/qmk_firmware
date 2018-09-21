/* Name: usbdrvasm20.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Jeroen Benschop
 * Based on usbdrvasm16.inc from Christian Starkjohann
 * Creation Date: 2008-03-05
 * Tabsize: 4
 * Copyright: (c) 2008 by Jeroen Benschop and OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 20 MHz version of the asssembler part of the USB driver. It
requires a 20 MHz crystal (not a ceramic resonator and not a calibrated RC
oscillator).

See usbdrv.h for a description of the entire driver.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!
*/

#define leap2   x3
#ifdef __IAR_SYSTEMS_ASM__
#define nextInst    $+2
#else
#define nextInst    .+0
#endif

;max stack usage: [ret(2), YL, SREG, YH, bitcnt, shift, x1, x2, x3, x4, cnt] = 12 bytes
;nominal frequency: 20 MHz -> 13.333333 cycles per bit, 106.666667 cycles per byte
; Numbers in brackets are clocks counted from center of last sync bit
; when instruction starts
;register use in receive loop:
; shift assembles the byte currently being received
; x1 holds the D+ and D- line state
; x2 holds the previous line state
; x4 (leap)  is used to add a leap cycle once every three bytes received
; X3 (leap2) is used to add a leap cycle once every three stuff bits received
; bitcnt is used to determine when a stuff bit is due
; cnt holds the number of bytes left in the receive buffer

USB_INTR_VECTOR:
;order of registers pushed: YL, SREG YH, [sofError], bitcnt, shift, x1, x2, x3, x4, cnt
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
    sbis    USBIN, USBMINUS     ;[-19]
    rjmp    foundK              ;[-18]
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
foundK:                         ;[-16]
;{3, 5} after falling D- edge, average delay: 4 cycles
;bit0 should be at 34 for center sampling. Currently at 4 so 30 cylces till bit 0 sample
;use 1 bit time for setup purposes, then sample again. Numbers in brackets
;are cycles from center of first sync (double K) bit after the instruction
    push    bitcnt              ;[-16]
;   [---]                       ;[-15]
    lds     YL, usbInputBufOffset;[-14]
;   [---]                       ;[-13]
    clr     YH                  ;[-12]
    subi    YL, lo8(-(usbRxBuf));[-11] [rx loop init]
    sbci    YH, hi8(-(usbRxBuf));[-10] [rx loop init]
    push    shift               ;[-9]
;   [---]                       ;[-8]
    ldi     shift,0x40          ;[-7] set msb to "1" so processing bit7 can be detected
    nop2                        ;[-6]
;   [---]                       ;[-5]
    ldi     bitcnt, 5           ;[-4] [rx loop init]
    sbis    USBIN, USBMINUS     ;[-3] we want two bits K (sample 3 cycles too early)
    rjmp    haveTwoBitsK        ;[-2]
    pop     shift               ;[-1] undo the push from before
    pop     bitcnt              ;[1] 
    rjmp    waitForK            ;[3] this was not the end of sync, retry
; The entire loop from waitForK until rjmp waitForK above must not exceed two
; bit times (= 27 cycles).

;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
haveTwoBitsK:
    push    x1                  ;[0]
    push    x2                  ;[2]
    push    x3                  ;[4] (leap2)
    ldi     leap2, 0x55         ;[6] add leap cycle on 2nd,5th,8th,... stuff bit
    push    x4                  ;[7] == leap
    ldi     leap, 0x55          ;[9] skip leap cycle on 2nd,5th,8th,... byte received
    push    cnt                 ;[10]
    ldi     cnt, USB_BUFSIZE    ;[12] [rx loop init]
    ldi     x2, 1<<USBPLUS      ;[13] current line state is K state. D+=="1", D-=="0"
bit0:       
    in      x1, USBIN           ;[0] sample line state
    andi    x1, USBMASK         ;[1] filter only D+ and D- bits
    rjmp    handleBit           ;[2] make bit0 14 cycles long

;----------------------------------------------------------------------------
; Process bit7. However, bit 6 still may need unstuffing.
;----------------------------------------------------------------------------

b6checkUnstuff:
    dec     bitcnt              ;[9]
    breq    unstuff6            ;[10]
bit7:
    subi    cnt, 1              ;[11] cannot use dec becaus it does not affect the carry flag
    brcs    overflow            ;[12] Too many bytes received. Ignore packet
    in      x1, USBIN           ;[0] sample line state
    andi    x1, USBMASK         ;[1] filter only D+ and D- bits
    cpse    x1, x2              ;[2] when previous line state equals current line state, handle "1"
    rjmp    b7handle0           ;[3] when line state differs, handle "0"
    sec                         ;[4]
    ror     shift               ;[5] shift "1" into the data
    st      y+, shift           ;[6] store the data into the buffer
    ldi     shift, 0x40         ;[7] reset data for receiving the next byte
    subi    leap, 0x55          ;[9] trick to introduce a leap cycle every 3 bytes
    brcc    nextInst            ;[10 or 11] it will fail after 85 bytes. However low speed can only receive 11
    dec     bitcnt              ;[11 or 12]
    brne    bit0                ;[12 or 13]
    ldi     x1, 1               ;[13 or 14] unstuffing bit 7
    in      bitcnt, USBIN       ;[0] sample stuff bit
    rjmp    unstuff             ;[1]

b7handle0:
    mov     x2,x1               ;[5] Set x2 to current line state
    ldi     bitcnt, 6           ;[6]
    lsr     shift               ;[7] shift "0" into the data
    st      y+, shift           ;[8] store data into the buffer
    ldi     shift, 0x40         ;[10] reset data for receiving the next byte
    subi    leap, 0x55          ;[11] trick to introduce a leap cycle every 3 bytes
    brcs    bit0                ;[12] it will fail after 85 bytes. However low speed can only receive 11
    rjmp    bit0                ;[13]


;----------------------------------------------------------------------------
; Handle unstuff
; x1==0xFF indicate unstuffing bit6
;----------------------------------------------------------------------------

unstuff6:
    ldi     x1,0xFF             ;[12] indicate unstuffing bit 6
    in      bitcnt, USBIN       ;[0]  sample stuff bit
    nop                         ;[1]  fix timing
unstuff:                        ;b0-5  b6   b7
    mov     x2,bitcnt           ;[3]  [2]  [3]  Set x2 to match line state
    subi    leap2, 0x55         ;[4]  [3]  [4]  delay loop
    brcs    nextInst            ;[5]  [4]  [5]  add one cycle every three stuff bits
    sbci    leap2,0             ;[6]  [5]  [6]
    ldi     bitcnt,6            ;[7]  [6]  [7]  reset bit stuff counter
    andi    x2, USBMASK         ;[8]  [7]  [8] only keep D+ and D-
    cpi     x1,0                ;[9]  [8]  [9]
    brmi    bit7                ;[10] [9]  [10] finished unstuffing bit6 When x1<0
    breq    bitloop             ;[11] ---  [11] finished unstuffing bit0-5 when x1=0
    nop                         ;---  ---  [12]
    in      x1, USBIN           ;---  ---  [0] sample line state for bit0
    andi    x1, USBMASK         ;---  ---  [1] filter only D+ and D- bits
    rjmp    handleBit           ;---  ---  [2] make bit0 14 cycles long

;----------------------------------------------------------------------------
; Receiver loop (numbers in brackets are cycles within byte after instr)
;----------------------------------------------------------------------------
bitloop:
    in      x1, USBIN           ;[0] sample line state
    andi    x1, USBMASK         ;[1] filter only D+ and D- bits
    breq    se0                 ;[2] both lines are low so handle se0
handleBit:
    cpse    x1, x2              ;[3] when previous line state equals current line state, handle "1"
    rjmp    handle0             ;[4] when line state differs, handle "0"
    sec                         ;[5]
    ror     shift               ;[6] shift "1" into the data
    brcs    b6checkUnstuff      ;[7] When after shift C is set, next bit is bit7
    nop2                        ;[8]
    dec     bitcnt              ;[10]
    brne    bitloop             ;[11]
    ldi     x1,0                ;[12] indicate unstuff for bit other than bit6 or bit7
    in      bitcnt, USBIN       ;[0] sample stuff bit
    rjmp    unstuff             ;[1]

handle0:
    mov     x2, x1              ;[6] Set x2 to current line state
    ldi     bitcnt, 6           ;[7] reset unstuff counter. 
    lsr     shift               ;[8] shift "0" into the data
    brcs    bit7                ;[9] When after shift C is set, next bit is bit7
    nop                         ;[10]
    rjmp    bitloop             ;[11] 
    
;----------------------------------------------------------------------------
; End of receive loop. Now start handling EOP
;----------------------------------------------------------------------------

macro POP_STANDARD ; 14 cycles
    pop     cnt
    pop     x4
    pop     x3
    pop     x2
    pop     x1
    pop     shift
    pop     bitcnt
    endm
macro POP_RETI     ; 7 cycles
    pop     YH
    pop     YL
    out     SREG, YL
    pop     YL
    endm



#include "asmcommon.inc"

; USB spec says:
; idle = J
; J = (D+ = 0), (D- = 1)
; K = (D+ = 1), (D- = 0)
; Spec allows 7.5 bit times from EOP to SOP for replies
; 7.5 bit times is 100 cycles. This implementation arrives a bit later at se0
; then specified in the include file but there is plenty of time

bitstuffN:
    eor     x1, x4          ;[8]
    ldi     x2, 0           ;[9]
    nop2                    ;[10]
    out     USBOUT, x1      ;[12] <-- out
    rjmp    didStuffN       ;[0]
    
bitstuff7:
    eor     x1, x4          ;[6]
    ldi     x2, 0           ;[7] Carry is zero due to brcc
    rol     shift           ;[8] compensate for ror shift at branch destination
    nop2                    ;[9]
    rjmp    didStuff7       ;[11]

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
;We don't match the transfer rate exactly (don't insert leap cycles every third
;byte) because the spec demands only 1.5% precision anyway.
usbSendAndReti:             ; 12 cycles until SOP
    in      x2, USBDDR      ;[-12]
    ori     x2, USBMASK     ;[-11]
    sbi     USBOUT, USBMINUS;[-10] prepare idle state; D+ and D- must have been 0 (no pullups)
    in      x1, USBOUT      ;[-8] port mirror for tx loop
    out     USBDDR, x2      ;[-7] <- acquire bus
; need not init x2 (bitstuff history) because sync starts with 0
    ldi     x4, USBMASK     ;[-6] exor mask
    ldi     shift, 0x80     ;[-5] sync byte is first byte sent
txByteLoop:
    ldi     bitcnt, 0x49    ;[-4]        [10] binary 01001001
txBitLoop:
    sbrs    shift, 0        ;[-3] [10]   [11]
    eor     x1, x4          ;[-2] [11]   [12]
    out     USBOUT, x1      ;[-1] [12]   [13]   <-- out N
    ror     shift           ;[0]  [13]   [14]
    ror     x2              ;[1]
didStuffN:
    nop2                    ;[2]
    nop                     ;[4]
    cpi     x2, 0xfc        ;[5]
    brcc    bitstuffN       ;[6]
    lsr     bitcnt          ;[7]
    brcc    txBitLoop       ;[8]
    brne    txBitLoop       ;[9]

    sbrs    shift, 0        ;[10]
    eor     x1, x4          ;[11]
didStuff7:
    out     USBOUT, x1      ;[-1] [13] <-- out 7
    ror     shift           ;[0] [14]
    ror     x2              ;[1]
    nop                     ;[2]
    cpi     x2, 0xfc        ;[3]
    brcc    bitstuff7       ;[4]
    ld      shift, y+       ;[5]
    dec     cnt             ;[7]
    brne    txByteLoop      ;[8]
;make SE0:
    cbr     x1, USBMASK     ;[9] prepare SE0 [spec says EOP may be 25 to 30 cycles]
    lds     x2, usbNewDeviceAddr;[10]
    lsl     x2              ;[12] we compare with left shifted address
    out     USBOUT, x1      ;[13] <-- out SE0 -- from now 2 bits = 22 cycles until bus idle
    subi    YL, 20 + 2      ;[0] Only assign address on data packets, not ACK/NAK in x3
    sbci    YH, 0           ;[1]
;2006-03-06: moved transfer of new address to usbDeviceAddr from C-Code to asm:
;set address only after data packet was sent, not after handshake
    breq    skipAddrAssign  ;[2]
    sts     usbDeviceAddr, x2; if not skipped: SE0 is one cycle longer
skipAddrAssign:
;end of usbDeviceAddress transfer
    ldi     x2, 1<<USB_INTR_PENDING_BIT;[4] int0 occurred during TX -- clear pending flag
    USB_STORE_PENDING(x2)   ;[5]
    ori     x1, USBIDLE     ;[6]
    in      x2, USBDDR      ;[7]
    cbr     x2, USBMASK     ;[8] set both pins to input
    mov     x3, x1          ;[9]
    cbr     x3, USBMASK     ;[10] configure no pullup on both pins
    ldi     x4, 5           ;[11]
se0Delay:
    dec     x4              ;[12] [15] [18] [21] [24]
    brne    se0Delay        ;[13] [16] [19] [22] [25]
    out     USBOUT, x1      ;[26] <-- out J (idle) -- end of SE0 (EOP signal)
    out     USBDDR, x2      ;[27] <-- release bus now
    out     USBOUT, x3      ;[28] <-- ensure no pull-up resistors are active
    rjmp    doReturn
