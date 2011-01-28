/* Name: usbdrvasm128.inc
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2008-10-11
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbdrvasm128.inc 758 2009-08-06 10:12:54Z cs $
 */

/* Do not link this file! Link usbdrvasm.S instead, which includes the
 * appropriate implementation!
 */

/*
General Description:
This file is the 12.8 MHz version of the USB driver. It is intended for use
with the internal RC oscillator. Although 12.8 MHz is outside the guaranteed
calibration range of the oscillator, almost all AVRs can reach this frequency.
This version contains a phase locked loop in the receiver routine to cope with
slight clock rate deviations of up to +/- 1%.

See usbdrv.h for a description of the entire driver.

LIMITATIONS
===========
Although it may seem very handy to save the crystal and use the internal
RC oscillator of the CPU, this method (and this module) has some serious
limitations:
(1) The guaranteed calibration range of the oscillator is only 8.1 MHz.
They typical range is 14.5 MHz and most AVRs can actually reach this rate.
(2) Writing EEPROM and Flash may be unreliable (short data lifetime) since
the write procedure is timed from the RC oscillator.
(3) End Of Packet detection (SE0) should be in bit 1, bit it is only checked
if bits 0 and 1 both read as 0 on D- and D+ read as 0 in the middle. This may
cause problems with old hubs which delay SE0 by up to one cycle.
(4) Code size is much larger than that of the other modules.

Since almost all of this code is timing critical, don't change unless you
really know what you are doing! Many parts require not only a maximum number
of CPU cycles, but even an exact number of cycles!

Implementation notes:
======================
min frequency: 67 cycles for 8 bit -> 12.5625 MHz
max frequency: 69.286 cycles for 8 bit -> 12.99 MHz
nominal frequency: 12.77 MHz ( = sqrt(min * max))

sampling positions: (next even number in range [+/- 0.5])
cycle index range: 0 ... 66
bits:
.5, 8.875, 17.25, 25.625, 34, 42.375, 50.75, 59.125
[0/1], [9], [17], [25/+26], [34], [+42/43], [51], [59]

bit number:     0   1   2   3   4   5   6   7
spare cycles    1   2   1   2   1   1   1   0

operations to perform:      duration cycle
                            ----------------
    eor     fix, shift          1 -> 00
    andi    phase, USBMASK      1 -> 08
    breq    se0                 1 -> 16 (moved to 11)
    st      y+, data            2 -> 24, 25
    mov     data, fix           1 -> 33
    ser     data                1 -> 41
    subi    cnt, 1              1 -> 49
    brcs    overflow            1 -> 50

layout of samples and operations:
[##] = sample bit
<##> = sample phase
*##* = operation

0:  *00* [01]  02   03   04  <05>  06   07
1:  *08* [09]  10   11   12  <13>  14   15  *16*
2:  [17]  18   19   20  <21>  22   23
3:  *24* *25* [26]  27   28   29  <30>  31   32
4:  *33* [34]  35   36   37  <38>  39   40
5:  *41* [42]  43   44   45  <46>  47   48
6:  *49* *50* [51]  52   53   54  <55>  56   57   58
7:  [59]  60   61   62  <63>  64   65   66
*****************************************************************************/

/* we prefer positive expressions (do if condition) instead of negative
 * (skip if condition), therefore use defines for skip instructions:
 */
#define ifioclr sbis
#define ifioset sbic
#define ifrclr  sbrs
#define ifrset  sbrc

/* The registers "fix" and "data" swap their meaning during the loop. Use
 * defines to keep their name constant.
 */
#define fix     x2
#define data    x1
#undef phase        /* phase has a default definition to x4 */
#define phase   x3


USB_INTR_VECTOR:
;order of registers pushed: YL, SREG [sofError], YH, shift, x1, x2, x3, cnt, r0
    push    YL              ;2 push only what is necessary to sync with edge ASAP
    in      YL, SREG        ;1
    push    YL              ;2
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
    sbis    USBIN, USBMINUS ;[0]
    rjmp    foundK          ;[1]
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
    push    YH                  ;[2]
    lds     YL, usbInputBufOffset;[4]
    clr     YH                  ;[6]
    subi    YL, lo8(-(usbRxBuf));[7]
    sbci    YH, hi8(-(usbRxBuf));[8]

    sbis    USBIN, USBMINUS     ;[9] we want two bits K [we want to sample at 8 + 4 - 1.5 = 10.5]
    rjmp    haveTwoBitsK        ;[10]
    pop     YH                  ;[11] undo the push from before
    rjmp    waitForK            ;[13] this was not the end of sync, retry
haveTwoBitsK:
;----------------------------------------------------------------------------
; push more registers and initialize values while we sample the first bits:
;----------------------------------------------------------------------------
#define fix     x2
#define data    x1

    push    shift               ;[12]
    push    x1                  ;[14]
    push    x2                  ;[16]
    ldi     shift, 0x80         ;[18] prevent bit-unstuffing but init low bits to 0
    ifioset USBIN, USBMINUS     ;[19] [01] <--- bit 0 [10.5 + 8 = 18.5]
    ori     shift, 1<<0         ;[02]
    push    x3                  ;[03]
    push    cnt                 ;[05]
    push    r0                  ;[07]
    ifioset USBIN, USBMINUS     ;[09] <--- bit 1
    ori     shift, 1<<1         ;[10]
    ser     fix                 ;[11]
    ldi     cnt, USB_BUFSIZE    ;[12]
    mov     data, shift         ;[13]
    lsl     shift               ;[14]
    nop2                        ;[15]
    ifioset USBIN, USBMINUS     ;[17] <--- bit 2
    ori     data, 3<<2          ;[18] store in bit 2 AND bit 3
    eor     shift, data         ;[19] do nrzi decoding
    andi    data, 1<<3          ;[20]
    in      phase, USBIN        ;[21] <- phase
    brne    jumpToEntryAfterSet ;[22] if USBMINS at bit 3 was 1
    nop                         ;[23]
    rjmp    entryAfterClr       ;[24]
jumpToEntryAfterSet:
    rjmp    entryAfterSet       ;[24]

;----------------------------------------------------------------------------
; Receiver loop (numbers in brackets are cycles within byte after instr)
;----------------------------------------------------------------------------
#undef  fix
#define  fix    x1
#undef  data
#define data    x2

bit7IsSet:
    ifrclr  phase, USBMINUS     ;[62] check phase only if D- changed
    lpm                         ;[63]
    in      phase, USBIN        ;[64] <- phase (one cycle too late)
    ori     shift, 1 << 7       ;[65]
    nop                         ;[66]
;;;;rjmp    bit0AfterSet        ; -> [00] == [67] moved block up to save jump
bit0AfterSet:
    eor     fix, shift          ;[00]
#undef  fix
#define fix     x2
#undef  data
#define data    x1  /* we now have result in data, fix is reset to 0xff */
    ifioclr USBIN, USBMINUS     ;[01] <--- sample 0
    rjmp    bit0IsClr           ;[02]
    andi    shift, ~(7 << 0)    ;[03]
    breq    unstuff0s           ;[04]
    in      phase, USBIN        ;[05] <- phase
    rjmp    bit1AfterSet        ;[06]
unstuff0s:
    in      phase, USBIN        ;[06] <- phase (one cycle too late)
    andi    fix, ~(1 << 0)      ;[07]
    ifioclr USBIN, USBMINUS     ;[00]
    ifioset USBIN, USBPLUS      ;[01]
    rjmp    bit0IsClr           ;[02] executed if first expr false or second true
se0AndStore:                    ; executed only if both bits 0
    st      y+, x1              ;[15/17] cycles after start of byte
    rjmp    se0                 ;[17/19]

bit0IsClr:
    ifrset  phase, USBMINUS     ;[04] check phase only if D- changed
    lpm                         ;[05]
    in      phase, USBIN        ;[06] <- phase (one cycle too late)
    ori     shift, 1 << 0       ;[07]
bit1AfterClr:
    andi    phase, USBMASK      ;[08]
    ifioset USBIN, USBMINUS     ;[09] <--- sample 1
    rjmp    bit1IsSet           ;[10]
    breq    se0AndStore         ;[11] if D- was 0 in bits 0 AND 1 and D+ was 0 in between, we have SE0
    andi    shift, ~(7 << 1)    ;[12]
    in      phase, USBIN        ;[13] <- phase
    breq    unstuff1c           ;[14]
    rjmp    bit2AfterClr        ;[15]
unstuff1c:
    andi    fix, ~(1 << 1)      ;[16]
    nop2                        ;[08]
    nop2                        ;[10]
bit1IsSet:
    ifrclr  phase, USBMINUS     ;[12] check phase only if D- changed
    lpm                         ;[13]
    in      phase, USBIN        ;[14] <- phase (one cycle too late)
    ori     shift, 1 << 1       ;[15]
    nop                         ;[16]
bit2AfterSet:
    ifioclr USBIN, USBMINUS     ;[17] <--- sample 2
    rjmp    bit2IsClr           ;[18]
    andi    shift, ~(7 << 2)    ;[19]
    breq    unstuff2s           ;[20]
    in      phase, USBIN        ;[21] <- phase
    rjmp    bit3AfterSet        ;[22]
unstuff2s:
    in      phase, USBIN        ;[22] <- phase (one cycle too late)
    andi    fix, ~(1 << 2)      ;[23]
    nop2                        ;[16]
    nop2                        ;[18]
bit2IsClr:
    ifrset  phase, USBMINUS     ;[20] check phase only if D- changed
    lpm                         ;[21]
    in      phase, USBIN        ;[22] <- phase (one cycle too late)
    ori     shift, 1 << 2       ;[23]
bit3AfterClr:
    st      y+, data            ;[24]
entryAfterClr:
    ifioset USBIN, USBMINUS     ;[26] <--- sample 3
    rjmp    bit3IsSet           ;[27]
    andi    shift, ~(7 << 3)    ;[28]
    breq    unstuff3c           ;[29]
    in      phase, USBIN        ;[30] <- phase
    rjmp    bit4AfterClr        ;[31]
unstuff3c:
    in      phase, USBIN        ;[31] <- phase (one cycle too late)
    andi    fix, ~(1 << 3)      ;[32]
    nop2                        ;[25]
    nop2                        ;[27]
bit3IsSet:
    ifrclr  phase, USBMINUS     ;[29] check phase only if D- changed
    lpm                         ;[30]
    in      phase, USBIN        ;[31] <- phase (one cycle too late)
    ori     shift, 1 << 3       ;[32]
bit4AfterSet:
    mov     data, fix           ;[33] undo this move by swapping defines
#undef  fix
#define fix     x1
#undef  data
#define data    x2
    ifioclr USBIN, USBMINUS     ;[34] <--- sample 4
    rjmp    bit4IsClr           ;[35]
    andi    shift, ~(7 << 4)    ;[36]
    breq    unstuff4s           ;[37]
    in      phase, USBIN        ;[38] <- phase
    rjmp    bit5AfterSet        ;[39]
unstuff4s:
    in      phase, USBIN        ;[39] <- phase (one cycle too late)
    andi    fix, ~(1 << 4)      ;[40]
    nop2                        ;[33]
    nop2                        ;[35]
bit4IsClr:
    ifrset  phase, USBMINUS     ;[37] check phase only if D- changed
    lpm                         ;[38]
    in      phase, USBIN        ;[39] <- phase (one cycle too late)
    ori     shift, 1 << 4       ;[40]
bit5AfterClr:
    ser     data                ;[41]
    ifioset USBIN, USBMINUS     ;[42] <--- sample 5
    rjmp    bit5IsSet           ;[43]
    andi    shift, ~(7 << 5)    ;[44]
    breq    unstuff5c           ;[45]
    in      phase, USBIN        ;[46] <- phase
    rjmp    bit6AfterClr        ;[47]
unstuff5c:
    in      phase, USBIN        ;[47] <- phase (one cycle too late)
    andi    fix, ~(1 << 5)      ;[48]
    nop2                        ;[41]
    nop2                        ;[43]
bit5IsSet:
    ifrclr  phase, USBMINUS     ;[45] check phase only if D- changed
    lpm                         ;[46]
    in      phase, USBIN        ;[47] <- phase (one cycle too late)
    ori     shift, 1 << 5       ;[48]
bit6AfterSet:
    subi    cnt, 1              ;[49]
    brcs    jumpToOverflow      ;[50]
    ifioclr USBIN, USBMINUS     ;[51] <--- sample 6
    rjmp    bit6IsClr           ;[52]
    andi    shift, ~(3 << 6)    ;[53]
    cpi     shift, 2            ;[54]
    in      phase, USBIN        ;[55] <- phase
    brlt    unstuff6s           ;[56]
    rjmp    bit7AfterSet        ;[57]

jumpToOverflow:
    rjmp    overflow

unstuff6s:
    andi    fix, ~(1 << 6)      ;[50]
    lpm                         ;[51]
bit6IsClr:
    ifrset  phase, USBMINUS     ;[54] check phase only if D- changed
    lpm                         ;[55]
    in      phase, USBIN        ;[56] <- phase (one cycle too late)
    ori     shift, 1 << 6       ;[57]
    nop                         ;[58]
bit7AfterClr:
    ifioset USBIN, USBMINUS     ;[59] <--- sample 7
    rjmp    bit7IsSet           ;[60]
    andi    shift, ~(1 << 7)    ;[61]
    cpi     shift, 4            ;[62]
    in      phase, USBIN        ;[63] <- phase
    brlt    unstuff7c           ;[64]
    rjmp    bit0AfterClr        ;[65] -> [00] == [67]
unstuff7c:
    andi    fix, ~(1 << 7)      ;[58]
    nop                         ;[59]
    rjmp    bit7IsSet           ;[60]

bit7IsClr:
    ifrset  phase, USBMINUS     ;[62] check phase only if D- changed
    lpm                         ;[63]
    in      phase, USBIN        ;[64] <- phase (one cycle too late)
    ori     shift, 1 << 7       ;[65]
    nop                         ;[66]
;;;;rjmp    bit0AfterClr        ; -> [00] == [67] moved block up to save jump
bit0AfterClr:
    eor     fix, shift          ;[00]
#undef  fix
#define fix     x2
#undef  data
#define data    x1  /* we now have result in data, fix is reset to 0xff */
    ifioset USBIN, USBMINUS     ;[01] <--- sample 0
    rjmp    bit0IsSet           ;[02]
    andi    shift, ~(7 << 0)    ;[03]
    breq    unstuff0c           ;[04]
    in      phase, USBIN        ;[05] <- phase
    rjmp    bit1AfterClr        ;[06]
unstuff0c:
    in      phase, USBIN        ;[06] <- phase (one cycle too late)
    andi    fix, ~(1 << 0)      ;[07]
    ifioclr USBIN, USBMINUS     ;[00]
    ifioset USBIN, USBPLUS      ;[01]
    rjmp    bit0IsSet           ;[02] executed if first expr false or second true
    rjmp    se0AndStore         ;[03] executed only if both bits 0
bit0IsSet:
    ifrclr  phase, USBMINUS     ;[04] check phase only if D- changed
    lpm                         ;[05]
    in      phase, USBIN        ;[06] <- phase (one cycle too late)
    ori     shift, 1 << 0       ;[07]
bit1AfterSet:
    andi    shift, ~(7 << 1)    ;[08] compensated by "ori shift, 1<<1" if bit1IsClr
    ifioclr USBIN, USBMINUS     ;[09] <--- sample 1
    rjmp    bit1IsClr           ;[10]
    breq    unstuff1s           ;[11]
    nop2                        ;[12] do not check for SE0 if bit 0 was 1
    in      phase, USBIN        ;[14] <- phase (one cycle too late)
    rjmp    bit2AfterSet        ;[15]
unstuff1s:
    in      phase, USBIN        ;[13] <- phase
    andi    fix, ~(1 << 1)      ;[14]
    lpm                         ;[07]
    nop2                        ;[10]
bit1IsClr:
    ifrset  phase, USBMINUS     ;[12] check phase only if D- changed
    lpm                         ;[13]
    in      phase, USBIN        ;[14] <- phase (one cycle too late)
    ori     shift, 1 << 1       ;[15]
    nop                         ;[16]
bit2AfterClr:
    ifioset USBIN, USBMINUS     ;[17] <--- sample 2
    rjmp    bit2IsSet           ;[18]
    andi    shift, ~(7 << 2)    ;[19]
    breq    unstuff2c           ;[20]
    in      phase, USBIN        ;[21] <- phase
    rjmp    bit3AfterClr        ;[22]
unstuff2c:
    in      phase, USBIN        ;[22] <- phase (one cycle too late)
    andi    fix, ~(1 << 2)      ;[23]
    nop2                        ;[16]
    nop2                        ;[18]
bit2IsSet:
    ifrclr  phase, USBMINUS     ;[20] check phase only if D- changed
    lpm                         ;[21]
    in      phase, USBIN        ;[22] <- phase (one cycle too late)
    ori     shift, 1 << 2       ;[23]
bit3AfterSet:
    st      y+, data            ;[24]
entryAfterSet:
    ifioclr USBIN, USBMINUS     ;[26] <--- sample 3
    rjmp    bit3IsClr           ;[27]
    andi    shift, ~(7 << 3)    ;[28]
    breq    unstuff3s           ;[29]
    in      phase, USBIN        ;[30] <- phase
    rjmp    bit4AfterSet        ;[31]
unstuff3s:
    in      phase, USBIN        ;[31] <- phase (one cycle too late)
    andi    fix, ~(1 << 3)      ;[32]
    nop2                        ;[25]
    nop2                        ;[27]
bit3IsClr:
    ifrset  phase, USBMINUS     ;[29] check phase only if D- changed
    lpm                         ;[30]
    in      phase, USBIN        ;[31] <- phase (one cycle too late)
    ori     shift, 1 << 3       ;[32]
bit4AfterClr:
    mov     data, fix           ;[33] undo this move by swapping defines
#undef  fix
#define fix     x1
#undef  data
#define data    x2
    ifioset USBIN, USBMINUS     ;[34] <--- sample 4
    rjmp    bit4IsSet           ;[35]
    andi    shift, ~(7 << 4)    ;[36]
    breq    unstuff4c           ;[37]
    in      phase, USBIN        ;[38] <- phase
    rjmp    bit5AfterClr        ;[39]
unstuff4c:
    in      phase, USBIN        ;[39] <- phase (one cycle too late)
    andi    fix, ~(1 << 4)      ;[40]
    nop2                        ;[33]
    nop2                        ;[35]
bit4IsSet:
    ifrclr  phase, USBMINUS     ;[37] check phase only if D- changed
    lpm                         ;[38]
    in      phase, USBIN        ;[39] <- phase (one cycle too late)
    ori     shift, 1 << 4       ;[40]
bit5AfterSet:
    ser     data                ;[41]
    ifioclr USBIN, USBMINUS     ;[42] <--- sample 5
    rjmp    bit5IsClr           ;[43]
    andi    shift, ~(7 << 5)    ;[44]
    breq    unstuff5s           ;[45]
    in      phase, USBIN        ;[46] <- phase
    rjmp    bit6AfterSet        ;[47]
unstuff5s:
    in      phase, USBIN        ;[47] <- phase (one cycle too late)
    andi    fix, ~(1 << 5)      ;[48]
    nop2                        ;[41]
    nop2                        ;[43]
bit5IsClr:
    ifrset  phase, USBMINUS     ;[45] check phase only if D- changed
    lpm                         ;[46]
    in      phase, USBIN        ;[47] <- phase (one cycle too late)
    ori     shift, 1 << 5       ;[48]
bit6AfterClr:
    subi    cnt, 1              ;[49]
    brcs    overflow            ;[50]
    ifioset USBIN, USBMINUS     ;[51] <--- sample 6
    rjmp    bit6IsSet           ;[52]
    andi    shift, ~(3 << 6)    ;[53]
    cpi     shift, 2            ;[54]
    in      phase, USBIN        ;[55] <- phase
    brlt    unstuff6c           ;[56]
    rjmp    bit7AfterClr        ;[57]
unstuff6c:
    andi    fix, ~(1 << 6)      ;[50]
    lpm                         ;[51]
bit6IsSet:
    ifrclr  phase, USBMINUS     ;[54] check phase only if D- changed
    lpm                         ;[55]
    in      phase, USBIN        ;[56] <- phase (one cycle too late)
    ori     shift, 1 << 6       ;[57]
bit7AfterSet:
    ifioclr USBIN, USBMINUS     ;[59] <--- sample 7
    rjmp    bit7IsClr           ;[60]
    andi    shift, ~(1 << 7)    ;[61]
    cpi     shift, 4            ;[62]
    in      phase, USBIN        ;[63] <- phase
    brlt    unstuff7s           ;[64]
    rjmp    bit0AfterSet        ;[65] -> [00] == [67]
unstuff7s:
    andi    fix, ~(1 << 7)      ;[58]
    nop                         ;[59]
    rjmp    bit7IsClr           ;[60]

macro POP_STANDARD ; 14 cycles
    pop     r0
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
    ror     shift               ;[-5] [11] [63]
    brcc    doExorN1            ;[-4]      [64]
    subi    x3, 1               ;[-3]
    brne    commonN1            ;[-2]
    lsl     shift               ;[-1] compensate ror after rjmp stuffDelay
    nop                         ;[00] stuffing consists of just waiting 8 cycles
    rjmp    stuffN1Delay        ;[01] after ror, C bit is reliably clear

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

; USB spec says:
; idle = J
; J = (D+ = 0), (D- = 1) or USBOUT = 0x01
; K = (D+ = 1), (D- = 0) or USBOUT = 0x02
; Spec allows 7.5 bit times from EOP to SOP for replies (= 60 cycles)

;usbSend:
;pointer to data in 'Y'
;number of bytes in 'cnt' -- including sync byte
;uses: x1...x3, shift, cnt, Y [x1 = mirror USBOUT, x2 = USBMASK, x3 = bitstuff cnt]
;Numbers in brackets are time since first bit of sync pattern is sent (start of instruction)
usbSendAndReti:
    in      x2, USBDDR          ;[-10] 10 cycles until SOP
    ori     x2, USBMASK         ;[-9]
    sbi     USBOUT, USBMINUS    ;[-8] prepare idle state; D+ and D- must have been 0 (no pullups)
    out     USBDDR, x2          ;[-6] <--- acquire bus
    in      x1, USBOUT          ;[-5] port mirror for tx loop
    ldi     shift, 0x40         ;[-4] sync byte is first byte sent (we enter loop after ror)
    ldi     x2, USBMASK         ;[-3]
doExorN1:
    eor     x1, x2              ;[-2] [06] [62]
    ldi     x3, 6               ;[-1] [07] [63]
commonN1:
stuffN2Delay:
    out     USBOUT, x1          ;[00] [08] [64] <--- set bit
    ror     shift               ;[01]
    brcc    doExorN2            ;[02]
    subi    x3, 1               ;[03]
    brne    commonN2            ;[04]
    lsl     shift               ;[05] compensate ror after rjmp stuffDelay
    rjmp    stuffN2Delay        ;[06] after ror, C bit is reliably clear
doExorN2:
    eor     x1, x2              ;[04] [12]
    ldi     x3, 6               ;[05] [13]
commonN2:
    nop2                        ;[06] [14]
    subi    cnt, 171            ;[08] [16] trick: (3 * 171) & 0xff = 1
    out     USBOUT, x1          ;[09] [17] <--- set bit
    brcs    txBitloop           ;[10]      [27] [44]

stuff6Delay:
    ror     shift               ;[45] [53]
    brcc    doExor6             ;[46]
    subi    x3, 1               ;[47]
    brne    common6             ;[48]
    lsl     shift               ;[49] compensate ror after rjmp stuffDelay
    nop                         ;[50] stuffing consists of just waiting 8 cycles
    rjmp    stuff6Delay         ;[51] after ror, C bit is reliably clear
doExor6:
    eor     x1, x2              ;[48] [56]
    ldi     x3, 6               ;[49]
common6:
stuff7Delay:
    ror     shift               ;[50] [58]
    out     USBOUT, x1          ;[51] <--- set bit
    brcc    doExor7             ;[52]
    subi    x3, 1               ;[53]
    brne    common7             ;[54]
    lsl     shift               ;[55] compensate ror after rjmp stuffDelay
    rjmp    stuff7Delay         ;[56] after ror, C bit is reliably clear
doExor7:
    eor     x1, x2              ;[54] [62]
    ldi     x3, 6               ;[55]
common7:
    ld      shift, y+           ;[56]
    nop                         ;[58]
    tst     cnt                 ;[59]
    out     USBOUT, x1          ;[60] [00]<--- set bit
    brne    txByteLoop          ;[61] [01]
;make SE0:
    cbr     x1, USBMASK         ;[02] prepare SE0 [spec says EOP may be 15 to 18 cycles]
    lds     x2, usbNewDeviceAddr;[03]
    lsl     x2                  ;[05] we compare with left shifted address
    subi    YL, 2 + 0           ;[06] Only assign address on data packets, not ACK/NAK in r0
    sbci    YH, 0               ;[07]
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
    lpm                         ;[10]
    lpm                         ;[13]
    out     USBOUT, x1          ;[16] <-- out J (idle) -- end of SE0 (EOP signal)
    out     USBDDR, x2          ;[17] <-- release bus now
    out     USBOUT, x3          ;[18] <-- ensure no pull-up resistors are active
    rjmp    doReturn



/*****************************************************************************
The following PHP script generates a code skeleton for the receiver routine:

<?php

function printCmdBuffer($thisBit)
{
global $cycle;

    $nextBit = ($thisBit + 1) % 8;
    $s = ob_get_contents();
    ob_end_clean();
    $s = str_replace("#", $thisBit, $s);
    $s = str_replace("@", $nextBit, $s);
    $lines = explode("\n", $s);
    for($i = 0; $i < count($lines); $i++){
        $s = $lines[$i];
        if(ereg("\\[([0-9-][0-9])\\]", $s, $regs)){
            $c = $cycle + (int)$regs[1];
            $s = ereg_replace("\\[[0-9-][0-9]\\]", sprintf("[%02d]", $c), $s);
        }
        if(strlen($s) > 0)
            echo "$s\n";
    }
}

function printBit($isAfterSet, $bitNum)
{
    ob_start();
    if($isAfterSet){
?>
    ifioclr USBIN, USBMINUS     ;[00] <--- sample
    rjmp    bit#IsClr           ;[01]
    andi    shift, ~(7 << #)    ;[02]
    breq    unstuff#s           ;[03]
    in      phase, USBIN        ;[04] <- phase
    rjmp    bit@AfterSet        ;[05]
unstuff#s:
    in      phase, USBIN        ;[05] <- phase (one cycle too late)
    andi    fix, ~(1 << #)      ;[06]
    nop2                        ;[-1]
    nop2                        ;[01]
bit#IsClr:
    ifrset  phase, USBMINUS     ;[03] check phase only if D- changed
    lpm                         ;[04]
    in      phase, USBIN        ;[05] <- phase (one cycle too late)
    ori     shift, 1 << #       ;[06]
<?php
    }else{
?>
    ifioset USBIN, USBMINUS     ;[00] <--- sample
    rjmp    bit#IsSet           ;[01]
    andi    shift, ~(7 << #)    ;[02]
    breq    unstuff#c           ;[03]
    in      phase, USBIN        ;[04] <- phase
    rjmp    bit@AfterClr        ;[05]
unstuff#c:
    in      phase, USBIN        ;[05] <- phase (one cycle too late)
    andi    fix, ~(1 << #)      ;[06]
    nop2                        ;[-1]
    nop2                        ;[01]
bit#IsSet:
    ifrclr  phase, USBMINUS     ;[03] check phase only if D- changed
    lpm                         ;[04]
    in      phase, USBIN        ;[05] <- phase (one cycle too late)
    ori     shift, 1 << #       ;[06]
<?php
    }
    printCmdBuffer($bitNum);
}

$bitStartCycles = array(1, 9, 17, 26, 34, 42, 51, 59);
for($i = 0; $i < 16; $i++){
    $bit = $i % 8;
    $emitClrCode = ($i + (int)($i / 8)) % 2;
    $cycle = $bitStartCycles[$bit];
    if($emitClrCode){
        printf("bit%dAfterClr:\n", $bit);
    }else{
        printf("bit%dAfterSet:\n", $bit);
    }
    ob_start();
    echo "    *****                       ;[-1]\n";
    printCmdBuffer($bit);
    printBit(!$emitClrCode, $bit);
    if($i == 7)
        echo "\n";
}

?>
*****************************************************************************/
