/* Name: usbdrvasm165.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2007-04-22
 * Tabsize: 4
 * Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * Revision: $Id: usbdrvasm165.inc 740 2009-04-13 18:23:31Z cs $
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 16.5 MHz version of the USB driver. It is intended for the
ATTiny45 and similar controllers running on 16.5 MHz internal RC oscillator.
This version contains a phase locked loop in the receiver routine to cope with
slight clock rate deviations of up to +/- 1%.

See usbdrv.h for a description of the entire driver.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!
*/

;Software-receiver engine. Strict timing! Don't change unless you can preserve timing!
;interrupt response time: 4 cycles + insn running = 7 max if interrupts always enabled
;max allowable interrupt latency: 59 cycles -> max 52 cycles interrupt disable
;max stack usage: [ret(2), r0, SREG, YL, YH, shift, x1, x2, x3, x4, cnt] = 12 bytes
;nominal frequency: 16.5 MHz -> 11 cycles per bit
; 16.3125 MHz < F_CPU < 16.6875 MHz (+/- 1.1%)
; Numbers in brackets are clocks counted from center of last sync bit
; when instruction starts


USB_INTR_VECTOR:
;order of registers pushed: YL, SREG [sofError], r0, YH, shift, x1, x2, x3, x4, cnt
    push    YL                  ;[-23] push only what is necessary to sync with edge ASAP
    in      YL, SREG            ;[-21]
    push    YL                  ;[-20]
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
    sbis    USBIN, USBMINUS     ;[-15]
    rjmp    foundK              ;[-14]
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
foundK:                         ;[-12]
;{3, 5} after falling D- edge, average delay: 4 cycles [we want 5 for center sampling]
;we have 1 bit time for setup purposes, then sample again. Numbers in brackets
;are cycles from center of first sync (double K) bit after the instruction
    push    r0                  ;[-12]
;   [---]                       ;[-11]
    push    YH                  ;[-10]
;   [---]                       ;[-9]
    lds     YL, usbInputBufOffset;[-8]
;   [---]                       ;[-7]
    clr     YH                  ;[-6]
    subi    YL, lo8(-(usbRxBuf));[-5] [rx loop init]
    sbci    YH, hi8(-(usbRxBuf));[-4] [rx loop init]
    mov     r0, x2              ;[-3] [rx loop init]
    sbis    USBIN, USBMINUS     ;[-2] we want two bits K (sample 2 cycles too early)
    rjmp    haveTwoBitsK        ;[-1]
    pop     YH                  ;[0] undo the pushes from before
    pop     r0                  ;[2]
    rjmp    waitForK            ;[4] this was not the end of sync, retry
; The entire loop from waitForK until rjmp waitForK above must not exceed two
; bit times (= 22 cycles).

;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
haveTwoBitsK:               ;[1]
    push    shift           ;[1]
    push    x1              ;[3]
    push    x2              ;[5]
    push    x3              ;[7]
    ldi     shift, 0xff     ;[9] [rx loop init]
    ori     x3, 0xff        ;[10] [rx loop init] == ser x3, clear zero flag

    in      x1, USBIN       ;[11] <-- sample bit 0
    bst     x1, USBMINUS    ;[12]
    bld     shift, 0        ;[13]
    push    x4              ;[14] == phase
;   [---]                   ;[15]
    push    cnt             ;[16]
;   [---]                   ;[17]
    ldi     phase, 0        ;[18] [rx loop init]
    ldi     cnt, USB_BUFSIZE;[19] [rx loop init]
    rjmp    rxbit1          ;[20]
;   [---]                   ;[21]

;----------------------------------------------------------------------------
; Receiver loop (numbers in brackets are cycles within byte after instr)
;----------------------------------------------------------------------------
/*
byte oriented operations done during loop:
bit 0: store data
bit 1: SE0 check
bit 2: overflow check
bit 3: catch up
bit 4: rjmp to achieve conditional jump range
bit 5: PLL
bit 6: catch up
bit 7: jump, fixup bitstuff
; 87 [+ 2] cycles
------------------------------------------------------------------
*/
continueWithBit5:
    in      x2, USBIN       ;[055] <-- bit 5
    eor     r0, x2          ;[056]
    or      phase, r0       ;[057]
    sbrc    phase, USBMINUS ;[058]
    lpm                     ;[059] optional nop3; modifies r0
    in      phase, USBIN    ;[060] <-- phase
    eor     x1, x2          ;[061]
    bst     x1, USBMINUS    ;[062]
    bld     shift, 5        ;[063]
    andi    shift, 0x3f     ;[064]
    in      x1, USBIN       ;[065] <-- bit 6
    breq    unstuff5        ;[066] *** unstuff escape
    eor     phase, x1       ;[067]
    eor     x2, x1          ;[068]
    bst     x2, USBMINUS    ;[069]
    bld     shift, 6        ;[070]
didUnstuff6:                ;[   ]
    in      r0, USBIN       ;[071] <-- phase
    cpi     shift, 0x02     ;[072]
    brlo    unstuff6        ;[073] *** unstuff escape
didUnstuff5:                ;[   ]
    nop2                    ;[074]
;   [---]                   ;[075]
    in      x2, USBIN       ;[076] <-- bit 7
    eor     x1, x2          ;[077]
    bst     x1, USBMINUS    ;[078]
    bld     shift, 7        ;[079]
didUnstuff7:                ;[   ]
    eor     r0, x2          ;[080]
    or      phase, r0       ;[081]
    in      r0, USBIN       ;[082] <-- phase
    cpi     shift, 0x04     ;[083]
    brsh    rxLoop          ;[084]
;   [---]                   ;[085]
unstuff7:                   ;[   ]
    andi    x3, ~0x80       ;[085]
    ori     shift, 0x80     ;[086]
    in      x2, USBIN       ;[087] <-- sample stuffed bit 7
    nop                     ;[088]
    rjmp    didUnstuff7     ;[089]
;   [---]                   ;[090]
                            ;[080]

unstuff5:                   ;[067]
    eor     phase, x1       ;[068]
    andi    x3, ~0x20       ;[069]
    ori     shift, 0x20     ;[070]
    in      r0, USBIN       ;[071] <-- phase
    mov     x2, x1          ;[072]
    nop                     ;[073]
    nop2                    ;[074]
;   [---]                   ;[075]
    in      x1, USBIN       ;[076] <-- bit 6
    eor     r0, x1          ;[077]
    or      phase, r0       ;[078]
    eor     x2, x1          ;[079]
    bst     x2, USBMINUS    ;[080]
    bld     shift, 6        ;[081] no need to check bitstuffing, we just had one
    in      r0, USBIN       ;[082] <-- phase
    rjmp    didUnstuff5     ;[083]
;   [---]                   ;[084]
                            ;[074]

unstuff6:                   ;[074]
    andi    x3, ~0x40       ;[075]
    in      x1, USBIN       ;[076] <-- bit 6 again
    ori     shift, 0x40     ;[077]
    nop2                    ;[078]
;   [---]                   ;[079]
    rjmp    didUnstuff6     ;[080]
;   [---]                   ;[081]
                            ;[071]

unstuff0:                   ;[013]
    eor     r0, x2          ;[014]
    or      phase, r0       ;[015]
    andi    x2, USBMASK     ;[016] check for SE0
    in      r0, USBIN       ;[017] <-- phase
    breq    didUnstuff0     ;[018] direct jump to se0 would be too long
    andi    x3, ~0x01       ;[019]
    ori     shift, 0x01     ;[020]
    mov     x1, x2          ;[021] mov existing sample
    in      x2, USBIN       ;[022] <-- bit 1 again
    rjmp    didUnstuff0     ;[023]
;   [---]                   ;[024]
                            ;[014]

unstuff1:                   ;[024]
    eor     r0, x1          ;[025]
    or      phase, r0       ;[026]
    andi    x3, ~0x02       ;[027]
    in      r0, USBIN       ;[028] <-- phase
    ori     shift, 0x02     ;[029]
    mov     x2, x1          ;[030]
    rjmp    didUnstuff1     ;[031]
;   [---]                   ;[032]
                            ;[022]

unstuff2:                   ;[035]
    eor     r0, x2          ;[036]
    or      phase, r0       ;[037]
    andi    x3, ~0x04       ;[038]
    in      r0, USBIN       ;[039] <-- phase
    ori     shift, 0x04     ;[040]
    mov     x1, x2          ;[041]
    rjmp    didUnstuff2     ;[042]
;   [---]                   ;[043]
                            ;[033]

unstuff3:                   ;[043]
    in      x2, USBIN       ;[044] <-- bit 3 again
    eor     r0, x2          ;[045]
    or      phase, r0       ;[046]
    andi    x3, ~0x08       ;[047]
    ori     shift, 0x08     ;[048]
    nop                     ;[049]
    in      r0, USBIN       ;[050] <-- phase
    rjmp    didUnstuff3     ;[051]
;   [---]                   ;[052]
                            ;[042]

unstuff4:                   ;[053]
    andi    x3, ~0x10       ;[054]
    in      x1, USBIN       ;[055] <-- bit 4 again
    ori     shift, 0x10     ;[056]
    rjmp    didUnstuff4     ;[057]
;   [---]                   ;[058]
                            ;[048]

rxLoop:                     ;[085]
    eor     x3, shift       ;[086] reconstruct: x3 is 0 at bit locations we changed, 1 at others
    in      x1, USBIN       ;[000] <-- bit 0
    st      y+, x3          ;[001]
;   [---]                   ;[002]
    eor     r0, x1          ;[003]
    or      phase, r0       ;[004]
    eor     x2, x1          ;[005]
    in      r0, USBIN       ;[006] <-- phase
    ser     x3              ;[007]
    bst     x2, USBMINUS    ;[008]
    bld     shift, 0        ;[009]
    andi    shift, 0xf9     ;[010]
rxbit1:                     ;[   ]
    in      x2, USBIN       ;[011] <-- bit 1
    breq    unstuff0        ;[012] *** unstuff escape
    andi    x2, USBMASK     ;[013] SE0 check for bit 1
didUnstuff0:                ;[   ] Z only set if we detected SE0 in bitstuff
    breq    se0             ;[014]
    eor     r0, x2          ;[015]
    or      phase, r0       ;[016]
    in      r0, USBIN       ;[017] <-- phase
    eor     x1, x2          ;[018]
    bst     x1, USBMINUS    ;[019]
    bld     shift, 1        ;[020]
    andi    shift, 0xf3     ;[021]
didUnstuff1:                ;[   ]
    in      x1, USBIN       ;[022] <-- bit 2
    breq    unstuff1        ;[023] *** unstuff escape
    eor     r0, x1          ;[024]
    or      phase, r0       ;[025]
    subi    cnt, 1          ;[026] overflow check
    brcs    overflow        ;[027]
    in      r0, USBIN       ;[028] <-- phase
    eor     x2, x1          ;[029]
    bst     x2, USBMINUS    ;[030]
    bld     shift, 2        ;[031]
    andi    shift, 0xe7     ;[032]
didUnstuff2:                ;[   ]
    in      x2, USBIN       ;[033] <-- bit 3
    breq    unstuff2        ;[034] *** unstuff escape
    eor     r0, x2          ;[035]
    or      phase, r0       ;[036]
    eor     x1, x2          ;[037]
    bst     x1, USBMINUS    ;[038]
    in      r0, USBIN       ;[039] <-- phase
    bld     shift, 3        ;[040]
    andi    shift, 0xcf     ;[041]
didUnstuff3:                ;[   ]
    breq    unstuff3        ;[042] *** unstuff escape
    nop                     ;[043]
    in      x1, USBIN       ;[044] <-- bit 4
    eor     x2, x1          ;[045]
    bst     x2, USBMINUS    ;[046]
    bld     shift, 4        ;[047]
didUnstuff4:                ;[   ]
    eor     r0, x1          ;[048]
    or      phase, r0       ;[049]
    in      r0, USBIN       ;[050] <-- phase
    andi    shift, 0x9f     ;[051]
    breq    unstuff4        ;[052] *** unstuff escape
    rjmp    continueWithBit5;[053]
;   [---]                   ;[054]

macro POP_STANDARD ; 16 cycles
    pop     cnt
    pop     x4
    pop     x3
    pop     x2
    pop     x1
    pop     shift
    pop     YH
    pop     r0
    endm
macro POP_RETI     ; 5 cycles
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

bitstuff7:
    eor     x1, x4          ;[4]
    ldi     x2, 0           ;[5]
    nop2                    ;[6] C is zero (brcc)
    rjmp    didStuff7       ;[8]

bitstuffN:
    eor     x1, x4          ;[5]
    ldi     x2, 0           ;[6]
    lpm                     ;[7] 3 cycle NOP, modifies r0
    out     USBOUT, x1      ;[10] <-- out
    rjmp    didStuffN       ;[0]

#define bitStatus   x3

sendNakAndReti:
    ldi     cnt, USBPID_NAK ;[-19]
    rjmp    sendCntAndReti  ;[-18]
sendAckAndReti:
    ldi     cnt, USBPID_ACK ;[-17]
sendCntAndReti:
    mov     r0, cnt         ;[-16]
    ldi     YL, 0           ;[-15] R0 address is 0
    ldi     YH, 0           ;[-14]
    ldi     cnt, 2          ;[-13]
;   rjmp    usbSendAndReti      fallthrough

;usbSend:
;pointer to data in 'Y'
;number of bytes in 'cnt' -- including sync byte [range 2 ... 12]
;uses: x1...x4, shift, cnt, Y
;Numbers in brackets are time since first bit of sync pattern is sent
usbSendAndReti:             ; 12 cycles until SOP
    in      x2, USBDDR      ;[-12]
    ori     x2, USBMASK     ;[-11]
    sbi     USBOUT, USBMINUS;[-10] prepare idle state; D+ and D- must have been 0 (no pullups)
    in      x1, USBOUT      ;[-8] port mirror for tx loop
    out     USBDDR, x2      ;[-7] <- acquire bus
; need not init x2 (bitstuff history) because sync starts with 0
    ldi     x4, USBMASK     ;[-6] exor mask
    ldi     shift, 0x80     ;[-5] sync byte is first byte sent
    ldi     bitStatus, 0xff ;[-4] init bit loop counter, works for up to 12 bytes
byteloop:
bitloop:
    sbrs    shift, 0        ;[8] [-3]
    eor     x1, x4          ;[9] [-2]
    out     USBOUT, x1      ;[10] [-1] <-- out
    ror     shift           ;[0]
    ror     x2              ;[1]
didStuffN:
    cpi     x2, 0xfc        ;[2]
    brcc    bitstuffN       ;[3]
    nop                     ;[4]
    subi    bitStatus, 37   ;[5] 256 / 7 ~=~ 37
    brcc    bitloop         ;[6] when we leave the loop, bitStatus has almost the initial value
    sbrs    shift, 0        ;[7]
    eor     x1, x4          ;[8]
    ror     shift           ;[9]
didStuff7:
    out     USBOUT, x1      ;[10] <-- out
    ror     x2              ;[0]
    cpi     x2, 0xfc        ;[1]
    brcc    bitstuff7       ;[2]
    ld      shift, y+       ;[3]
    dec     cnt             ;[5]
    brne    byteloop        ;[6]
;make SE0:
    cbr     x1, USBMASK     ;[7] prepare SE0 [spec says EOP may be 21 to 25 cycles]
    lds     x2, usbNewDeviceAddr;[8]
    lsl     x2              ;[10] we compare with left shifted address
    out     USBOUT, x1      ;[11] <-- out SE0 -- from now 2 bits = 22 cycles until bus idle
;2006-03-06: moved transfer of new address to usbDeviceAddr from C-Code to asm:
;set address only after data packet was sent, not after handshake
    subi    YL, 2           ;[0] Only assign address on data packets, not ACK/NAK in r0
    sbci    YH, 0           ;[1]
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
    ldi     x4, 4           ;[11]
se0Delay:
    dec     x4              ;[12] [15] [18] [21]
    brne    se0Delay        ;[13] [16] [19] [22]
    out     USBOUT, x1      ;[23] <-- out J (idle) -- end of SE0 (EOP signal)
    out     USBDDR, x2      ;[24] <-- release bus now
    out     USBOUT, x3      ;[25] <-- ensure no pull-up resistors are active
    rjmp    doReturn

