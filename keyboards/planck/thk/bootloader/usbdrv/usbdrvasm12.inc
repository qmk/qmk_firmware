/* Name: usbdrvasm12.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2004-12-29
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 12 MHz version of the asssembler part of the USB driver. It
requires a 12 MHz crystal (not a ceramic resonator and not a calibrated RC
oscillator).

See usbdrv.h for a description of the entire driver.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!


Timing constraints according to spec (in bit times):
timing subject                                      min max    CPUcycles
---------------------------------------------------------------------------
EOP of OUT/SETUP to sync pattern of DATA0 (both rx) 2   16     16-128
EOP of IN to sync pattern of DATA0 (rx, then tx)    2   7.5    16-60
DATAx (rx) to ACK/NAK/STALL (tx)                    2   7.5    16-60
*/

;Software-receiver engine. Strict timing! Don't change unless you can preserve timing!
;interrupt response time: 4 cycles + insn running = 7 max if interrupts always enabled
;max allowable interrupt latency: 34 cycles -> max 25 cycles interrupt disable
;max stack usage: [ret(2), YL, SREG, YH, shift, x1, x2, x3, cnt, x4] = 11 bytes
;Numbers in brackets are maximum cycles since SOF.
USB_INTR_VECTOR:
;order of registers pushed: YL, SREG [sofError], YH, shift, x1, x2, x3, cnt
    push    YL              ;2 [35] push only what is necessary to sync with edge ASAP
    in      YL, SREG        ;1 [37]
    push    YL              ;2 [39]
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
;The following code results in a sampling window of 1/4 bit which meets the spec.
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
foundK:
;{3, 5} after falling D- edge, average delay: 4 cycles [we want 4 for center sampling]
;we have 1 bit time for setup purposes, then sample again. Numbers in brackets
;are cycles from center of first sync (double K) bit after the instruction
    push    YH                  ;2 [2]
    lds     YL, usbInputBufOffset;2 [4]
    clr     YH                  ;1 [5]
    subi    YL, lo8(-(usbRxBuf));1 [6]
    sbci    YH, hi8(-(usbRxBuf));1 [7]

    sbis    USBIN, USBMINUS ;1 [8] we want two bits K [sample 1 cycle too early]
    rjmp    haveTwoBitsK    ;2 [10]
    pop     YH              ;2 [11] undo the push from before
    rjmp    waitForK        ;2 [13] this was not the end of sync, retry
haveTwoBitsK:
;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
    push    shift           ;2 [16]
    push    x1              ;2 [12]
    push    x2              ;2 [14]

    in      x1, USBIN       ;1 [17] <-- sample bit 0
    ldi     shift, 0xff     ;1 [18]
    bst     x1, USBMINUS    ;1 [19]
    bld     shift, 0        ;1 [20]
    push    x3              ;2 [22]
    push    cnt             ;2 [24]
    
    in      x2, USBIN       ;1 [25] <-- sample bit 1
    ser     x3              ;1 [26] [inserted init instruction]
    eor     x1, x2          ;1 [27]
    bst     x1, USBMINUS    ;1 [28]
    bld     shift, 1        ;1 [29]
    ldi     cnt, USB_BUFSIZE;1 [30] [inserted init instruction]
    rjmp    rxbit2          ;2 [32]

;----------------------------------------------------------------------------
; Receiver loop (numbers in brackets are cycles within byte after instr)
;----------------------------------------------------------------------------

unstuff0:               ;1 (branch taken)
    andi    x3, ~0x01   ;1 [15]
    mov     x1, x2      ;1 [16] x2 contains last sampled (stuffed) bit
    in      x2, USBIN   ;1 [17] <-- sample bit 1 again
    ori     shift, 0x01 ;1 [18]
    rjmp    didUnstuff0 ;2 [20]

unstuff1:               ;1 (branch taken)
    mov     x2, x1      ;1 [21] x1 contains last sampled (stuffed) bit
    andi    x3, ~0x02   ;1 [22]
    ori     shift, 0x02 ;1 [23]
    nop                 ;1 [24]
    in      x1, USBIN   ;1 [25] <-- sample bit 2 again
    rjmp    didUnstuff1 ;2 [27]

unstuff2:               ;1 (branch taken)
    andi    x3, ~0x04   ;1 [29]
    ori     shift, 0x04 ;1 [30]
    mov     x1, x2      ;1 [31] x2 contains last sampled (stuffed) bit
    nop                 ;1 [32]
    in      x2, USBIN   ;1 [33] <-- sample bit 3
    rjmp    didUnstuff2 ;2 [35]

unstuff3:               ;1 (branch taken)
    in      x2, USBIN   ;1 [34] <-- sample stuffed bit 3 [one cycle too late]
    andi    x3, ~0x08   ;1 [35]
    ori     shift, 0x08 ;1 [36]
    rjmp    didUnstuff3 ;2 [38]

unstuff4:               ;1 (branch taken)
    andi    x3, ~0x10   ;1 [40]
    in      x1, USBIN   ;1 [41] <-- sample stuffed bit 4
    ori     shift, 0x10 ;1 [42]
    rjmp    didUnstuff4 ;2 [44]

unstuff5:               ;1 (branch taken)
    andi    x3, ~0x20   ;1 [48]
    in      x2, USBIN   ;1 [49] <-- sample stuffed bit 5
    ori     shift, 0x20 ;1 [50]
    rjmp    didUnstuff5 ;2 [52]

unstuff6:               ;1 (branch taken)
    andi    x3, ~0x40   ;1 [56]
    in      x1, USBIN   ;1 [57] <-- sample stuffed bit 6
    ori     shift, 0x40 ;1 [58]
    rjmp    didUnstuff6 ;2 [60]

; extra jobs done during bit interval:
; bit 0:    store, clear [SE0 is unreliable here due to bit dribbling in hubs]
; bit 1:    se0 check
; bit 2:    overflow check
; bit 3:    recovery from delay [bit 0 tasks took too long]
; bit 4:    none
; bit 5:    none
; bit 6:    none
; bit 7:    jump, eor
rxLoop:
    eor     x3, shift   ;1 [0] reconstruct: x3 is 0 at bit locations we changed, 1 at others
    in      x1, USBIN   ;1 [1] <-- sample bit 0
    st      y+, x3      ;2 [3] store data
    ser     x3          ;1 [4]
    nop                 ;1 [5]
    eor     x2, x1      ;1 [6]
    bst     x2, USBMINUS;1 [7]
    bld     shift, 0    ;1 [8]
    in      x2, USBIN   ;1 [9] <-- sample bit 1 (or possibly bit 0 stuffed)
    andi    x2, USBMASK ;1 [10]
    breq    se0         ;1 [11] SE0 check for bit 1
    andi    shift, 0xf9 ;1 [12]
didUnstuff0:
    breq    unstuff0    ;1 [13]
    eor     x1, x2      ;1 [14]
    bst     x1, USBMINUS;1 [15]
    bld     shift, 1    ;1 [16]
rxbit2:
    in      x1, USBIN   ;1 [17] <-- sample bit 2 (or possibly bit 1 stuffed)
    andi    shift, 0xf3 ;1 [18]
    breq    unstuff1    ;1 [19] do remaining work for bit 1
didUnstuff1:
    subi    cnt, 1      ;1 [20]
    brcs    overflow    ;1 [21] loop control
    eor     x2, x1      ;1 [22]
    bst     x2, USBMINUS;1 [23]
    bld     shift, 2    ;1 [24]
    in      x2, USBIN   ;1 [25] <-- sample bit 3 (or possibly bit 2 stuffed)
    andi    shift, 0xe7 ;1 [26]
    breq    unstuff2    ;1 [27]
didUnstuff2:
    eor     x1, x2      ;1 [28]
    bst     x1, USBMINUS;1 [29]
    bld     shift, 3    ;1 [30]
didUnstuff3:
    andi    shift, 0xcf ;1 [31]
    breq    unstuff3    ;1 [32]
    in      x1, USBIN   ;1 [33] <-- sample bit 4
    eor     x2, x1      ;1 [34]
    bst     x2, USBMINUS;1 [35]
    bld     shift, 4    ;1 [36]
didUnstuff4:
    andi    shift, 0x9f ;1 [37]
    breq    unstuff4    ;1 [38]
    nop2                ;2 [40]
    in      x2, USBIN   ;1 [41] <-- sample bit 5
    eor     x1, x2      ;1 [42]
    bst     x1, USBMINUS;1 [43]
    bld     shift, 5    ;1 [44]
didUnstuff5:
    andi    shift, 0x3f ;1 [45]
    breq    unstuff5    ;1 [46]
    nop2                ;2 [48]
    in      x1, USBIN   ;1 [49] <-- sample bit 6
    eor     x2, x1      ;1 [50]
    bst     x2, USBMINUS;1 [51]
    bld     shift, 6    ;1 [52]
didUnstuff6:
    cpi     shift, 0x02 ;1 [53]
    brlo    unstuff6    ;1 [54]
    nop2                ;2 [56]
    in      x2, USBIN   ;1 [57] <-- sample bit 7
    eor     x1, x2      ;1 [58]
    bst     x1, USBMINUS;1 [59]
    bld     shift, 7    ;1 [60]
didUnstuff7:
    cpi     shift, 0x04 ;1 [61]
    brsh    rxLoop      ;2 [63] loop control
unstuff7:
    andi    x3, ~0x80   ;1 [63]
    ori     shift, 0x80 ;1 [64]
    in      x2, USBIN   ;1 [65] <-- sample stuffed bit 7
    nop                 ;1 [66]
    rjmp    didUnstuff7 ;2 [68]

macro POP_STANDARD ; 12 cycles
    pop     cnt
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

;----------------------------------------------------------------------------
; Transmitting data
;----------------------------------------------------------------------------

txByteLoop:
txBitloop:
stuffN1Delay:                   ;     [03]
    ror     shift               ;[-5] [11] [59]
    brcc    doExorN1            ;[-4]      [60]
    subi    x4, 1               ;[-3]
    brne    commonN1            ;[-2]
    lsl     shift               ;[-1] compensate ror after rjmp stuffDelay
    nop                         ;[00] stuffing consists of just waiting 8 cycles
    rjmp    stuffN1Delay        ;[01] after ror, C bit is reliably clear

sendNakAndReti:                 ;0 [-19] 19 cycles until SOP
    ldi     x3, USBPID_NAK      ;1 [-18]
    rjmp    usbSendX3           ;2 [-16]
sendAckAndReti:                 ;0 [-19] 19 cycles until SOP
    ldi     x3, USBPID_ACK      ;1 [-18]
    rjmp    usbSendX3           ;2 [-16]
sendCntAndReti:                 ;0 [-17] 17 cycles until SOP
    mov     x3, cnt             ;1 [-16]
usbSendX3:                      ;0 [-16]
    ldi     YL, 20              ;1 [-15] 'x3' is R20
    ldi     YH, 0               ;1 [-14]
    ldi     cnt, 2              ;1 [-13]
;   rjmp    usbSendAndReti      fallthrough

; USB spec says:
; idle = J
; J = (D+ = 0), (D- = 1) or USBOUT = 0x01
; K = (D+ = 1), (D- = 0) or USBOUT = 0x02
; Spec allows 7.5 bit times from EOP to SOP for replies (= 60 cycles)

;usbSend:
;pointer to data in 'Y'
;number of bytes in 'cnt' -- including sync byte
;uses: x1...x2, x4, shift, cnt, Y [x1 = mirror USBOUT, x2 = USBMASK, x4 = bitstuff cnt]
;Numbers in brackets are time since first bit of sync pattern is sent (start of instruction)
usbSendAndReti:
    in      x2, USBDDR          ;[-12] 12 cycles until SOP
    ori     x2, USBMASK         ;[-11]
    sbi     USBOUT, USBMINUS    ;[-10] prepare idle state; D+ and D- must have been 0 (no pullups)
    out     USBDDR, x2          ;[-8] <--- acquire bus
    in      x1, USBOUT          ;[-7] port mirror for tx loop
    ldi     shift, 0x40         ;[-6] sync byte is first byte sent (we enter loop after ror)
    ldi     x2, USBMASK         ;[-5]
    push    x4                  ;[-4]
doExorN1:
    eor     x1, x2              ;[-2] [06] [62]
    ldi     x4, 6               ;[-1] [07] [63]
commonN1:
stuffN2Delay:
    out     USBOUT, x1          ;[00] [08] [64] <--- set bit
    ror     shift               ;[01]
    brcc    doExorN2            ;[02]
    subi    x4, 1               ;[03]
    brne    commonN2            ;[04]
    lsl     shift               ;[05] compensate ror after rjmp stuffDelay
    rjmp    stuffN2Delay        ;[06] after ror, C bit is reliably clear
doExorN2:
    eor     x1, x2              ;[04] [12]
    ldi     x4, 6               ;[05] [13]
commonN2:
    nop                         ;[06] [14]
    subi    cnt, 171            ;[07] [15] trick: (3 * 171) & 0xff = 1
    out     USBOUT, x1          ;[08] [16] <--- set bit
    brcs    txBitloop           ;[09]      [25] [41]

stuff6Delay:
    ror     shift               ;[42] [50]
    brcc    doExor6             ;[43]
    subi    x4, 1               ;[44]
    brne    common6             ;[45]
    lsl     shift               ;[46] compensate ror after rjmp stuffDelay
    nop                         ;[47] stuffing consists of just waiting 8 cycles
    rjmp    stuff6Delay         ;[48] after ror, C bit is reliably clear
doExor6:
    eor     x1, x2              ;[45] [53]
    ldi     x4, 6               ;[46]
common6:
stuff7Delay:
    ror     shift               ;[47] [55]
    out     USBOUT, x1          ;[48] <--- set bit
    brcc    doExor7             ;[49]
    subi    x4, 1               ;[50]
    brne    common7             ;[51]
    lsl     shift               ;[52] compensate ror after rjmp stuffDelay
    rjmp    stuff7Delay         ;[53] after ror, C bit is reliably clear
doExor7:
    eor     x1, x2              ;[51] [59]
    ldi     x4, 6               ;[52]
common7:
    ld      shift, y+           ;[53]
    tst     cnt                 ;[55]
    out     USBOUT, x1          ;[56] <--- set bit
    brne    txByteLoop          ;[57]

;make SE0:
    cbr     x1, USBMASK         ;[58] prepare SE0 [spec says EOP may be 15 to 18 cycles]
    lds     x2, usbNewDeviceAddr;[59]
    lsl     x2                  ;[61] we compare with left shifted address
    subi    YL, 2 + 20          ;[62] Only assign address on data packets, not ACK/NAK in x3
    sbci    YH, 0               ;[63]
    out     USBOUT, x1          ;[00] <-- out SE0 -- from now 2 bits = 16 cycles until bus idle
;2006-03-06: moved transfer of new address to usbDeviceAddr from C-Code to asm:
;set address only after data packet was sent, not after handshake
    breq    skipAddrAssign      ;[01]
    sts     usbDeviceAddr, x2   ; if not skipped: SE0 is one cycle longer
skipAddrAssign:
;end of usbDeviceAddress transfer
    ldi     x2, 1<<USB_INTR_PENDING_BIT;[03] int0 occurred during TX -- clear pending flag
    USB_STORE_PENDING(x2)       ;[04]
    ori     x1, USBIDLE         ;[05]
    in      x2, USBDDR          ;[06]
    cbr     x2, USBMASK         ;[07] set both pins to input
    mov     x3, x1              ;[08]
    cbr     x3, USBMASK         ;[09] configure no pullup on both pins
    pop     x4                  ;[10]
    nop2                        ;[12]
    nop2                        ;[14]
    out     USBOUT, x1          ;[16] <-- out J (idle) -- end of SE0 (EOP signal)
    out     USBDDR, x2          ;[17] <-- release bus now
    out     USBOUT, x3          ;[18] <-- ensure no pull-up resistors are active
    rjmp    doReturn
