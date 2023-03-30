/**
 * Copyright (c) 2020 Mark Owen https://www.quinapalus.com .
 *
 * Raspberry Pi (Trading) Ltd (Licensor) hereby grants to you a non-exclusive license to use the software solely on a
 * Raspberry Pi Pico device. No other use is permitted under the terms of this license.
 *
 * This software is also available from the copyright owner under GPLv2 licence.
 *
 * THIS SOFTWARE IS PROVIDED BY THE LICENSOR AND COPYRIGHT OWNER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE LICENSOR OR COPYRIGHT OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "pico/asm_helper.S"

.syntax unified
.cpu cortex-m0plus
.thumb

.macro double_section name
// todo separate flag for shims?
#if PICO_DOUBLE_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

double_section double_table_shim_on_use_helper
regular_func double_table_shim_on_use_helper
    push {r0-r2, lr}
    mov r0, ip
#ifndef NDEBUG
    // sanity check to make sure we weren't called by non (shimmable_) table_tail_call macro
    cmp r0, #0
    bne 1f
    bkpt #0
#endif
1:
    ldrh r1, [r0]
    lsrs r2, r1, #8
    adds r0, #2
    cmp r2, #0xdf
    bne 1b
    uxtb r1, r1 // r1 holds table offset
    lsrs r2, r0, #2
    bcc 1f
    // unaligned
    ldrh r2, [r0, #0]
    ldrh r0, [r0, #2]
    lsls r0, #16
    orrs r0, r2
    b 2f
1:
    ldr r0, [r0]
2:
    ldr r2, =sd_table
    str r0, [r2, r1]
    str r0, [sp, #12]
    pop {r0-r2, pc}

#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
// Note that the V1 ROM has no double support, so this is basically the identical
// library, and shim inter-function calls do not bother to redirect back thru the
// wrapper functions

.equ use_hw_div,1
.equ IOPORT       ,0xd0000000
.equ DIV_UDIVIDEND,0x00000060
.equ DIV_UDIVISOR ,0x00000064
.equ DIV_QUOTIENT ,0x00000070
.equ DIV_CSR      ,0x00000078

@ Notation:
@ rx:ry means the concatenation of rx and ry with rx having the less significant bits

.equ debug,0
.macro mdump k
.if debug
 push {r0-r3}
 push {r14}
 push {r0-r3}
 bl osp
 movs r0,#\k
 bl o1ch
 pop {r0-r3}
 bl dump
 bl osp
 bl osp
 ldr r0,[r13]
 bl o8hex                      @ r14
 bl onl
 pop {r0}
 mov r14,r0
 pop {r0-r3}
.endif
.endm


@ IEEE double in ra:rb ->
@ mantissa in ra:rb 12Q52 (53 significant bits) with implied 1 set
@ exponent in re
@ sign in rs
@ trashes rt
.macro mdunpack ra,rb,re,rs,rt
 lsrs \re,\rb,#20              @ extract sign and exponent
 subs \rs,\re,#1
 lsls \rs,#20
 subs \rb,\rs                  @ clear sign and exponent in mantissa; insert implied 1
 lsrs \rs,\re,#11              @ sign
 lsls \re,#21
 lsrs \re,#21                  @ exponent
 beq l\@_1                     @ zero exponent?
 adds \rt,\re,#1
 lsrs \rt,#11
 beq l\@_2                     @ exponent != 0x7ff? then done
l\@_1:
 movs \ra,#0
 movs \rb,#1
 lsls \rb,#20
 subs \re,#128
 lsls \re,#12
l\@_2:
.endm

@ IEEE double in ra:rb ->
@ signed mantissa in ra:rb 12Q52 (53 significant bits) with implied 1
@ exponent in re
@ trashes rt0 and rt1
@ +zero, +denormal -> exponent=-0x80000
@ -zero, -denormal -> exponent=-0x80000
@ +Inf, +NaN -> exponent=+0x77f000
@ -Inf, -NaN -> exponent=+0x77e000
.macro mdunpacks ra,rb,re,rt0,rt1
 lsrs \re,\rb,#20              @ extract sign and exponent
 lsrs \rt1,\rb,#31             @ sign only
 subs \rt0,\re,#1
 lsls \rt0,#20
 subs \rb,\rt0                 @ clear sign and exponent in mantissa; insert implied 1
 lsls \re,#21
 bcc l\@_1                     @ skip on positive
 mvns \rb,\rb                  @ negate mantissa
 negs \ra,\ra
 bcc l\@_1
 adds \rb,#1
l\@_1:
 lsrs \re,#21
 beq l\@_2                     @ zero exponent?
 adds \rt0,\re,#1
 lsrs \rt0,#11
 beq l\@_3                     @ exponent != 0x7ff? then done
 subs \re,\rt1
l\@_2:
 movs \ra,#0
 lsls \rt1,#1                  @ +ve: 0  -ve: 2
 adds \rb,\rt1,#1              @ +ve: 1  -ve: 3
 lsls \rb,#30                  @ create +/-1 mantissa
 asrs \rb,#10
 subs \re,#128
 lsls \re,#12
l\@_3:
.endm

double_section WRAPPER_FUNC_NAME(__aeabi_dsub)

# frsub first because it is the only one that needs alignment
regular_func drsub_shim
    push {r0-r3}
    pop {r0-r1}
    pop {r2-r3}
    // fall thru

regular_func dsub_shim
 push {r4-r7,r14}
 movs r4,#1
 lsls r4,#31
 eors r3,r4                    @ flip sign on second argument
 b da_entry                    @ continue in dadd

.align 2
double_section dadd_shim
regular_func dadd_shim
 push {r4-r7,r14}
da_entry:
 mdunpacks r0,r1,r4,r6,r7
 mdunpacks r2,r3,r5,r6,r7
 subs r7,r5,r4                 @ ye-xe
 subs r6,r4,r5                 @ xe-ye
 bmi da_ygtx
@ here xe>=ye: need to shift y down r6 places
 mov r12,r4                    @ save exponent
 cmp r6,#32
 bge da_xrgty                  @ xe rather greater than ye?
 adds r7,#32
 movs r4,r2
 lsls r4,r4,r7                 @ rounding bit + sticky bits
da_xgty0:
 movs r5,r3
 lsls r5,r5,r7
 lsrs r2,r6
 asrs r3,r6
 orrs r2,r5
da_add:
 adds r0,r2
 adcs r1,r3
da_pack:
@ here unnormalised signed result (possibly 0) is in r0:r1 with exponent r12, rounding + sticky bits in r4
@ Note that if a large normalisation shift is required then the arguments were close in magnitude and so we
@ cannot have not gone via the xrgty/yrgtx paths. There will therefore always be enough high bits in r4
@ to provide a correct continuation of the exact result.
@ now pack result back up
 lsrs r3,r1,#31                @ get sign bit
 beq 1f                        @ skip on positive
 mvns r1,r1                    @ negate mantissa
 mvns r0,r0
 movs r2,#0
 negs r4,r4
 adcs r0,r2
 adcs r1,r2
1:
 mov r2,r12                    @ get exponent
 lsrs r5,r1,#21
 bne da_0                      @ shift down required?
 lsrs r5,r1,#20
 bne da_1                      @ normalised?
 cmp r0,#0
 beq da_5                      @ could mantissa be zero?
da_2:
 adds r4,r4
 adcs r0,r0
 adcs r1,r1
 subs r2,#1                    @ adjust exponent
 lsrs r5,r1,#20
 beq da_2
da_1:
 lsls r4,#1                    @ check rounding bit
 bcc da_3
da_4:
 adds r0,#1                    @ round up
 bcc 2f
 adds r1,#1
2:
 cmp r4,#0                     @ sticky bits zero?
 bne da_3
 lsrs r0,#1                    @ round to even
 lsls r0,#1
da_3:
 subs r2,#1
 bmi da_6
 adds r4,r2,#2                 @ check if exponent is overflowing
 lsrs r4,#11
 bne da_7
 lsls r2,#20                   @ pack exponent and sign
 add r1,r2
 lsls r3,#31
 add r1,r3
 pop {r4-r7,r15}

da_7:
@ here exponent overflow: return signed infinity
 lsls r1,r3,#31
 ldr r3,=0x7ff00000
 orrs r1,r3
 b 1f
da_6:
@ here exponent underflow: return signed zero
 lsls r1,r3,#31
1:
 movs r0,#0
 pop {r4-r7,r15}

da_5:
@ here mantissa could be zero
 cmp r1,#0
 bne da_2
 cmp r4,#0
 bne da_2
@ inputs must have been of identical magnitude and opposite sign, so return +0
 pop {r4-r7,r15}

da_0:
@ here a shift down by one place is required for normalisation
 adds r2,#1                    @ adjust exponent
 lsls r6,r0,#31                @ save rounding bit
 lsrs r0,#1
 lsls r5,r1,#31
 orrs r0,r5
 lsrs r1,#1
 cmp r6,#0
 beq da_3
 b da_4

da_xrgty:                      @ xe>ye and shift>=32 places
 cmp r6,#60
 bge da_xmgty                  @ xe much greater than ye?
 subs r6,#32
 adds r7,#64

 movs r4,r2
 lsls r4,r4,r7                 @ these would be shifted off the bottom of the sticky bits
 beq 1f
 movs r4,#1
1:
 lsrs r2,r2,r6
 orrs r4,r2
 movs r2,r3
 lsls r3,r3,r7
 orrs r4,r3
 asrs r3,r2,#31                @ propagate sign bit
 b da_xgty0

da_ygtx:
@ here ye>xe: need to shift x down r7 places
 mov r12,r5                    @ save exponent
 cmp r7,#32
 bge da_yrgtx                  @ ye rather greater than xe?
 adds r6,#32
 movs r4,r0
 lsls r4,r4,r6                 @ rounding bit + sticky bits
da_ygtx0:
 movs r5,r1
 lsls r5,r5,r6
 lsrs r0,r7
 asrs r1,r7
 orrs r0,r5
 b da_add

da_yrgtx:
 cmp r7,#60
 bge da_ymgtx                  @ ye much greater than xe?
 subs r7,#32
 adds r6,#64

 movs r4,r0
 lsls r4,r4,r6                 @ these would be shifted off the bottom of the sticky bits
 beq 1f
 movs r4,#1
1:
 lsrs r0,r0,r7
 orrs r4,r0
 movs r0,r1
 lsls r1,r1,r6
 orrs r4,r1
 asrs r1,r0,#31                @ propagate sign bit
 b da_ygtx0

da_ymgtx:                      @ result is just y
 movs r0,r2
 movs r1,r3
da_xmgty:                      @ result is just x
 movs r4,#0                    @ clear sticky bits
 b da_pack

.ltorg

@ equivalent of UMULL
@ needs five temporary registers
@ can have rt3==rx, in which case rx trashed
@ can have rt4==ry, in which case ry trashed
@ can have rzl==rx
@ can have rzh==ry
@ can have rzl,rzh==rt3,rt4
.macro mul32_32_64 rx,ry,rzl,rzh,rt0,rt1,rt2,rt3,rt4
                               @   t0   t1   t2   t3   t4
                               @                  (x)  (y)
 uxth \rt0,\rx                 @   xl
 uxth \rt1,\ry                 @        yl
 muls \rt0,\rt1                @  xlyl=L
 lsrs \rt2,\rx,#16             @             xh
 muls \rt1,\rt2                @       xhyl=M0
 lsrs \rt4,\ry,#16             @                       yh
 muls \rt2,\rt4                @           xhyh=H
 uxth \rt3,\rx                 @                   xl
 muls \rt3,\rt4                @                  xlyh=M1
 adds \rt1,\rt3                @      M0+M1=M
 bcc l\@_1                     @ addition of the two cross terms can overflow, so add carry into H
 movs \rt3,#1                  @                   1
 lsls \rt3,#16                 @                0x10000
 adds \rt2,\rt3                @             H'
l\@_1:
                               @   t0   t1   t2   t3   t4
                               @                 (zl) (zh)
 lsls \rzl,\rt1,#16            @                  ML
 lsrs \rzh,\rt1,#16            @                       MH
 adds \rzl,\rt0                @                  ZL
 adcs \rzh,\rt2                @                       ZH
.endm

@ SUMULL: x signed, y unsigned
@ in table below ¯ means signed variable
@ needs five temporary registers
@ can have rt3==rx, in which case rx trashed
@ can have rt4==ry, in which case ry trashed
@ can have rzl==rx
@ can have rzh==ry
@ can have rzl,rzh==rt3,rt4
.macro muls32_32_64 rx,ry,rzl,rzh,rt0,rt1,rt2,rt3,rt4
                               @   t0   t1   t2   t3   t4
                               @                 ¯(x)  (y)
 uxth \rt0,\rx                 @   xl
 uxth \rt1,\ry                 @        yl
 muls \rt0,\rt1                @  xlyl=L
 asrs \rt2,\rx,#16             @            ¯xh
 muls \rt1,\rt2                @      ¯xhyl=M0
 lsrs \rt4,\ry,#16             @                       yh
 muls \rt2,\rt4                @          ¯xhyh=H
 uxth \rt3,\rx                 @                   xl
 muls \rt3,\rt4                @                 xlyh=M1
 asrs \rt4,\rt1,#31            @                      M0sx   (M1 sign extension is zero)
 adds \rt1,\rt3                @      M0+M1=M
 movs \rt3,#0                  @                    0
 adcs \rt4,\rt3                @                      ¯Msx
 lsls \rt4,#16                 @                    ¯Msx<<16
 adds \rt2,\rt4                @             H'

                               @   t0   t1   t2   t3   t4
                               @                 (zl) (zh)
 lsls \rzl,\rt1,#16            @                  M~
 lsrs \rzh,\rt1,#16            @                       M~
 adds \rzl,\rt0                @                  ZL
 adcs \rzh,\rt2                @                      ¯ZH
.endm

@ SSMULL: x signed, y signed
@ in table below ¯ means signed variable
@ needs five temporary registers
@ can have rt3==rx, in which case rx trashed
@ can have rt4==ry, in which case ry trashed
@ can have rzl==rx
@ can have rzh==ry
@ can have rzl,rzh==rt3,rt4
.macro muls32_s32_64 rx,ry,rzl,rzh,rt0,rt1,rt2,rt3,rt4
                               @   t0   t1   t2   t3   t4
                               @                 ¯(x)  (y)
 uxth \rt0,\rx                 @   xl
 uxth \rt1,\ry                 @        yl
 muls \rt0,\rt1                @  xlyl=L
 asrs \rt2,\rx,#16             @            ¯xh
 muls \rt1,\rt2                @      ¯xhyl=M0
 asrs \rt4,\ry,#16             @                      ¯yh
 muls \rt2,\rt4                @          ¯xhyh=H
 uxth \rt3,\rx                 @                   xl
 muls \rt3,\rt4                @                ¯xlyh=M1
 adds \rt1,\rt3                @     ¯M0+M1=M
 asrs \rt3,\rt1,#31            @                  Msx
 bvc l\@_1                     @
 mvns \rt3,\rt3                @                 ¯Msx        flip sign extension bits if overflow
l\@_1:
 lsls \rt3,#16                 @                    ¯Msx<<16
 adds \rt2,\rt3                @             H'

                               @   t0   t1   t2   t3   t4
                               @                 (zl) (zh)
 lsls \rzl,\rt1,#16            @                  M~
 lsrs \rzh,\rt1,#16            @                       M~
 adds \rzl,\rt0                @                  ZL
 adcs \rzh,\rt2                @                      ¯ZH
.endm

@ can have rt2==rx, in which case rx trashed
@ can have rzl==rx
@ can have rzh==rt1
.macro square32_64 rx,rzl,rzh,rt0,rt1,rt2
                               @   t0   t1   t2   zl   zh
 uxth \rt0,\rx                 @   xl
 muls \rt0,\rt0                @ xlxl=L
 uxth \rt1,\rx                 @        xl
 lsrs \rt2,\rx,#16             @             xh
 muls \rt1,\rt2                @      xlxh=M
 muls \rt2,\rt2                @           xhxh=H
 lsls \rzl,\rt1,#17            @                  ML
 lsrs \rzh,\rt1,#15            @                       MH
 adds \rzl,\rt0                @                  ZL
 adcs \rzh,\rt2                @                       ZH
.endm

double_section dmul_shim
 regular_func dmul_shim
 push {r4-r7,r14}
 mdunpack r0,r1,r4,r6,r5
 mov r12,r4
 mdunpack r2,r3,r4,r7,r5
 eors r7,r6                    @ sign of result
 add r4,r12                    @ exponent of result
 push {r0-r2,r4,r7}

@ accumulate full product in r12:r5:r6:r7
 mul32_32_64 r0,r2, r0,r5, r4,r6,r7,r0,r5    @ XL*YL
 mov r12,r0                    @ save LL bits

 mul32_32_64 r1,r3, r6,r7, r0,r2,r4,r6,r7    @ XH*YH

 pop {r0}                      @ XL
 mul32_32_64 r0,r3, r0,r3, r1,r2,r4,r0,r3    @ XL*YH
 adds r5,r0
 adcs r6,r3
 movs r0,#0
 adcs r7,r0

 pop {r1,r2}                   @ XH,YL
 mul32_32_64 r1,r2, r1,r2, r0,r3,r4, r1,r2   @ XH*YL
 adds r5,r1
 adcs r6,r2
 movs r0,#0
 adcs r7,r0

@ here r5:r6:r7 holds the product [1..4) in Q(104-32)=Q72, with extra LSBs in r12
 pop {r3,r4}                   @ exponent in r3, sign in r4
 lsls r1,r7,#11
 lsrs r2,r6,#21
 orrs r1,r2
 lsls r0,r6,#11
 lsrs r2,r5,#21
 orrs r0,r2
 lsls r5,#11                   @ now r5:r0:r1 Q83=Q(51+32), extra LSBs in r12
 lsrs r2,r1,#20
 bne 1f                        @ skip if in range [2..4)
 adds r5,r5                    @ shift up so always [2..4) Q83, i.e. [1..2) Q84=Q(52+32)
 adcs r0,r0
 adcs r1,r1
 subs r3,#1                    @ correct exponent
1:
 ldr r6,=0x3ff
 subs r3,r6                    @ correct for exponent bias
 lsls r6,#1                    @ 0x7fe
 cmp r3,r6
 bhs dm_0                      @ exponent over- or underflow
 lsls r5,#1                    @ rounding bit to carry
 bcc 1f                        @ result is correctly rounded
 adds r0,#1
 movs r6,#0
 adcs r1,r6                    @ round up
 mov r6,r12                    @ remaining sticky bits
 orrs r5,r6
 bne 1f                        @ some sticky bits set?
 lsrs r0,#1
 lsls r0,#1                    @ round to even
1:
 lsls r3,#20
 adds r1,r3
dm_2:
 lsls r4,#31
 add r1,r4
 pop {r4-r7,r15}

@ here for exponent over- or underflow
dm_0:
 bge dm_1                      @ overflow?
 adds r3,#1                    @ would-be zero exponent?
 bne 1f
 adds r0,#1
 bne 1f                        @ all-ones mantissa?
 adds r1,#1
 lsrs r7,r1,#21
 beq 1f
 lsrs r1,#1
 b dm_2
1:
 lsls r1,r4,#31
 movs r0,#0
 pop {r4-r7,r15}

@ here for exponent overflow
dm_1:
 adds r6,#1                    @ 0x7ff
 lsls r1,r6,#20
 movs r0,#0
 b dm_2

.ltorg

@ Approach to division y/x is as follows.
@
@ First generate u1, an approximation to 1/x to about 29 bits. Multiply this by the top
@ 32 bits of y to generate a0, a first approximation to the result (good to 28 bits or so).
@ Calculate the exact remainder r0=y-a0*x, which will be about 0. Calculate a correction
@ d0=r0*u1, and then write a1=a0+d0. If near a rounding boundary, compute the exact
@ remainder r1=y-a1*x (which can be done using r0 as a basis) to determine whether to
@ round up or down.
@
@ The calculation of 1/x is as given in dreciptest.c. That code verifies exhaustively
@ that | u1*x-1 | < 10*2^-32.
@
@ More precisely:
@
@ x0=(q16)x;
@ x1=(q30)x;
@ y0=(q31)y;
@ u0=(q15~)"(0xffffffffU/(unsigned int)roundq(x/x_ulp))/powq(2,16)"(x0); // q15 approximation to 1/x; "~" denotes rounding rather than truncation
@ v=(q30)(u0*x1-1);
@ u1=(q30)u0-(q30~)(u0*v);
@
@ a0=(q30)(u1*y0);
@ r0=(q82)y-a0*x;
@ r0x=(q57)r0;
@ d0=r0x*u1;
@ a1=d0+a0;
@
@ Error analysis
@
@ Use Greek letters to represent the errors introduced by rounding and truncation.
@
@               r₀ = y - a₀x
@                  = y - [ u₁ ( y - α ) - β ] x    where 0 ≤ α < 2^-31, 0 ≤ β < 2^-30
@                  = y ( 1 - u₁x ) + ( u₁α + β ) x
@
@     Hence
@
@       | r₀ / x | < 2 * 10*2^-32 + 2^-31 + 2^-30
@                  = 26*2^-32
@
@               r₁ = y - a₁x
@                  = y - a₀x - d₀x
@                  = r₀ - d₀x
@                  = r₀ - u₁ ( r₀ - γ ) x    where 0 ≤ γ < 2^-57
@                  = r₀ ( 1 - u₁x ) + u₁γx
@
@     Hence
@
@       | r₁ / x | < 26*2^-32 * 10*2^-32 + 2^-57
@                  = (260+128)*2^-64
@                  < 2^-55
@
@ Empirically it seems to be nearly twice as good as this.
@
@ To determine correctly whether the exact remainder calculation can be skipped we need a result
@ accurate to < 0.25ulp. In the case where x>y the quotient will be shifted up one place for normalisation
@ and so 1ulp is 2^-53 and so the calculation above suffices.

double_section ddiv_shim
 regular_func ddiv_shim
 push {r4-r7,r14}
ddiv0:                         @ entry point from dtan
 mdunpack r2,r3,r4,r7,r6       @ unpack divisor

.if use_hw_div

 movs r5,#IOPORT>>24
 lsls r5,#24
 movs r6,#0
 mvns r6,r6
 str r6,[r5,#DIV_UDIVIDEND]
 lsrs r6,r3,#4                 @ x0=(q16)x
 str r6,[r5,#DIV_UDIVISOR]
@ if there are not enough cycles from now to the read of the quotient for
@ the divider to do its stuff we need a busy-wait here

.endif

@ unpack dividend by hand to save on register use
 lsrs r6,r1,#31
 adds r6,r7
 mov r12,r6                    @ result sign in r12b0; r12b1 trashed
 lsls r1,#1
 lsrs r7,r1,#21                @ exponent
 beq 1f                        @ zero exponent?
 adds r6,r7,#1
 lsrs r6,#11
 beq 2f                        @ exponent != 0x7ff? then done
1:
 movs r0,#0
 movs r1,#0
 subs r7,#64                   @ less drastic fiddling of exponents to get 0/0, Inf/Inf correct
 lsls r7,#12
2:
 subs r6,r7,r4
 lsls r6,#2
 add r12,r12,r6                @ (signed) exponent in r12[31..8]
 subs r7,#1                    @ implied 1
 lsls r7,#21
 subs r1,r7
 lsrs r1,#1

.if use_hw_div

 ldr r6,[r5,#DIV_QUOTIENT]
 adds r6,#1
 lsrs r6,#1

.else

@ this is not beautiful; could be replaced by better code that uses knowledge of divisor range
 push {r0-r3}
 movs r0,#0
 mvns r0,r0
 lsrs r1,r3,#4                 @ x0=(q16)x
 bl __aeabi_uidiv              @ !!! this could (but apparently does not) trash R12
 adds r6,r0,#1
 lsrs r6,#1
 pop {r0-r3}

.endif

@ here
@ r0:r1 y mantissa
@ r2:r3 x mantissa
@ r6    u0, first approximation to 1/x Q15
@ r12: result sign, exponent

 lsls r4,r3,#10
 lsrs r5,r2,#22
 orrs r5,r4                    @ x1=(q30)x
 muls r5,r6                    @ u0*x1 Q45
 asrs r5,#15                   @ v=u0*x1-1 Q30
 muls r5,r6                    @ u0*v Q45
 asrs r5,#14
 adds r5,#1
 asrs r5,#1                    @ round u0*v to Q30
 lsls r6,#15
 subs r6,r5                    @ u1 Q30

@ here
@ r0:r1 y mantissa
@ r2:r3 x mantissa
@ r6    u1, second approximation to 1/x Q30
@ r12: result sign, exponent

 push {r2,r3}
 lsls r4,r1,#11
 lsrs r5,r0,#21
 orrs r4,r5                    @ y0=(q31)y
 mul32_32_64 r4,r6, r4,r5, r2,r3,r7,r4,r5  @ y0*u1 Q61
 adds r4,r4
 adcs r5,r5                    @ a0=(q30)(y0*u1)

@ here
@ r0:r1 y mantissa
@ r5    a0, first approximation to y/x Q30
@ r6    u1, second approximation to 1/x Q30
@ r12   result sign, exponent

 ldr r2,[r13,#0]               @ xL
 mul32_32_64 r2,r5, r2,r3, r1,r4,r7,r2,r3  @ xL*a0
 ldr r4,[r13,#4]               @ xH
 muls r4,r5                    @ xH*a0
 adds r3,r4                    @ r2:r3 now x*a0 Q82
 lsrs r2,#25
 lsls r1,r3,#7
 orrs r2,r1                    @ r2 now x*a0 Q57; r7:r2 is x*a0 Q89
 lsls r4,r0,#5                 @ y Q57
 subs r0,r4,r2                 @ r0x=y-x*a0 Q57 (signed)

@ here
@ r0  r0x Q57
@ r5  a0, first approximation to y/x Q30
@ r4  yL  Q57
@ r6  u1 Q30
@ r12 result sign, exponent

 muls32_32_64 r0,r6, r7,r6, r1,r2,r3, r7,r6   @ r7:r6 r0x*u1 Q87
 asrs r3,r6,#25
 adds r5,r3
 lsls r3,r6,#7                 @ r3:r5 a1 Q62 (but bottom 7 bits are zero so 55 bits of precision after binary point)
@ here we could recover another 7 bits of precision (but not accuracy) from the top of r7
@ but these bits are thrown away in the rounding and conversion to Q52 below

@ here
@ r3:r5  a1 Q62 candidate quotient [0.5,2) or so
@ r4     yL Q57
@ r12    result sign, exponent

 movs r6,#0
 adds r3,#128                  @ for initial rounding to Q53
 adcs r5,r5,r6
 lsrs  r1,r5,#30
 bne dd_0
@ here candidate quotient a1 is in range [0.5,1)
@ so 30 significant bits in r5

 lsls r4,#1                    @ y now Q58
 lsrs r1,r5,#9                 @ to Q52
 lsls r0,r5,#23
 lsrs r3,#9                    @ 0.5ulp-significance bit in carry: if this is 1 we may need to correct result
 orrs r0,r3
 bcs dd_1
 b dd_2
dd_0:
@ here candidate quotient a1 is in range [1,2)
@ so 31 significant bits in r5

 movs r2,#4
 add r12,r12,r2                @ fix exponent; r3:r5 now effectively Q61
 adds r3,#128                  @ complete rounding to Q53
 adcs r5,r5,r6
 lsrs r1,r5,#10
 lsls r0,r5,#22
 lsrs r3,#10                   @ 0.5ulp-significance bit in carry: if this is 1 we may need to correct result
 orrs r0,r3
 bcc dd_2
dd_1:

@ here
@ r0:r1  rounded result Q53 [0.5,1) or Q52 [1,2), but may not be correctly rounded-to-nearest
@ r4     yL Q58 or Q57
@ r12    result sign, exponent
@ carry set

 adcs r0,r0,r0
 adcs r1,r1,r1                 @ z Q53 with 1 in LSB
 lsls r4,#16                   @ Q105-32=Q73
 ldr r2,[r13,#0]               @ xL Q52
 ldr r3,[r13,#4]               @ xH Q20

 movs r5,r1                    @ zH Q21
 muls r5,r2                    @ zH*xL Q73
 subs r4,r5
 muls r3,r0                    @ zL*xH Q73
 subs r4,r3
 mul32_32_64 r2,r0, r2,r3, r5,r6,r7,r2,r3  @ xL*zL
 negs r2,r2                    @ borrow from low half?
 sbcs r4,r3                    @ y-xz Q73 (remainder bits 52..73)

 cmp r4,#0

 bmi 1f
 movs r2,#0                    @ round up
 adds r0,#1
 adcs r1,r2
1:
 lsrs r0,#1                    @ shift back down to Q52
 lsls r2,r1,#31
 orrs r0,r2
 lsrs r1,#1
dd_2:
 add r13,#8
 mov r2,r12
 lsls r7,r2,#31                @ result sign
 asrs r2,#2                    @ result exponent
 ldr r3,=0x3fd
 adds r2,r3
 ldr r3,=0x7fe
 cmp r2,r3
 bhs dd_3                      @ over- or underflow?
 lsls r2,#20
 adds r1,r2                    @ pack exponent
dd_5:
 adds r1,r7                    @ pack sign
 pop {r4-r7,r15}

dd_3:
 movs r0,#0
 cmp r2,#0
 bgt dd_4                      @ overflow?
 movs r1,r7
 pop {r4-r7,r15}

dd_4:
 adds r3,#1                    @ 0x7ff
 lsls r1,r3,#20
 b dd_5

.section SECTION_NAME(dsqrt_shim)
/*
Approach to square root x=sqrt(y) is as follows.

First generate a3, an approximation to 1/sqrt(y) to about 30 bits. Multiply this by y
to give a4~sqrt(y) to about 28 bits and a remainder r4=y-a4^2. Then, because
d sqrt(y) / dy = 1 / (2 sqrt(y)) let d4=r4*a3/2 and then the value a5=a4+d4 is
a better approximation to sqrt(y). If this is near a rounding boundary we
compute an exact remainder y-a5*a5 to decide whether to round up or down.

The calculation of a3 and a4 is as given in dsqrttest.c. That code verifies exhaustively
that | 1 - a3a4 | < 10*2^-32, | r4 | < 40*2^-32 and | r4/y | < 20*2^-32.

More precisely, with "y" representing y truncated to 30 binary places:

u=(q3)y;                          // 24-entry table
a0=(q8~)"1/sqrtq(x+x_ulp/2)"(u);  // first approximation from table
p0=(q16)(a0*a0) * (q16)y;
r0=(q20)(p0-1);
dy0=(q15)(r0*a0);                 // Newton-Raphson correction term
a1=(q16)a0-dy0/2;                 // good to ~9 bits

p1=(q19)(a1*a1)*(q19)y;
r1=(q23)(p1-1);
dy1=(q15~)(r1*a1);                // second Newton-Raphson correction
a2x=(q16)a1-dy1/2;                // good to ~16 bits
a2=a2x-a2x/1t16;                  // prevent overflow of a2*a2 in 32 bits

p2=(a2*a2)*(q30)y;                // Q62
r2=(q36)(p2-1+1t-31);
dy2=(q30)(r2*a2);                 // Q52->Q30
a3=(q31)a2-dy2/2;                 // good to about 30 bits
a4=(q30)(a3*(q30)y+1t-31);        // good to about 28 bits

Error analysis

          r₄ = y - a₄²
          d₄ = 1/2 a₃r₄
          a₅ = a₄ + d₄
          r₅ = y - a₅²
             = y - ( a₄ + d₄ )²
             = y - a₄² - a₃a₄r₄ - 1/4 a₃²r₄²
             = r₄ - a₃a₄r₄ - 1/4 a₃²r₄²

      | r₅ | < | r₄ | | 1 - a₃a₄ | + 1/4 r₄²

          a₅ = √y √( 1 - r₅/y )
             = √y ( 1 - 1/2 r₅/y + ... )

So to first order (second order being very tiny)

     √y - a₅ = 1/2 r₅/y

and

 | √y - a₅ | < 1/2 ( | r₄/y | | 1 - a₃a₄ | + 1/4 r₄²/y )

From dsqrttest.c (conservatively):

             < 1/2 ( 20*2^-32 * 10*2^-32 + 1/4 * 40*2^-32*20*2^-32 )
             = 1/2 ( 200 + 200 ) * 2^-64
             < 2^-56

Empirically we see about 1ulp worst-case error including rounding at Q57.

To determine correctly whether the exact remainder calculation can be skipped we need a result
accurate to < 0.25ulp at Q52, or 2^-54.
*/

dq_2:
 bge dq_3                      @ +Inf?
 movs r1,#0
 b dq_4

dq_0:
 lsrs r1,#31
 lsls r1,#31                   @ preserve sign bit
 lsrs r2,#21                   @ extract exponent
 beq dq_4                      @ -0? return it
 asrs r1,#11                   @ make -Inf
 b dq_4

dq_3:
 ldr r1,=0x7ff
 lsls r1,#20                   @ return +Inf
dq_4:
 movs r0,#0
dq_1:
 bx r14

.align 2
regular_func dsqrt_shim
 lsls r2,r1,#1
 bcs dq_0                      @ negative?
 lsrs r2,#21                   @ extract exponent
 subs r2,#1
 ldr r3,=0x7fe
 cmp r2,r3
 bhs dq_2                      @ catches 0 and +Inf
 push {r4-r7,r14}
 lsls r4,r2,#20
 subs r1,r4                    @ insert implied 1
 lsrs r2,#1
 bcc 1f                        @ even exponent? skip
 adds r0,r0,r0                 @ odd exponent: shift up mantissa
 adcs r1,r1,r1
1:
 lsrs r3,#2
 adds r2,r3
 lsls r2,#20
 mov r12,r2                    @ save result exponent

@ here
@ r0:r1  y mantissa Q52 [1,4)
@ r12    result exponent
.equ drsqrtapp_minus_8, (drsqrtapp-8)
 adr r4,drsqrtapp_minus_8      @ first eight table entries are never accessed because of the mantissa's leading 1
 lsrs r2,r1,#17                @ y Q3
 ldrb r2,[r4,r2]               @ initial approximation to reciprocal square root a0 Q8
 lsrs r3,r1,#4                 @ first Newton-Raphson iteration
 muls r3,r2
 muls r3,r2                    @  i32 p0=a0*a0*(y>>14);          // Q32
 asrs r3,r3,#12                @  i32 r0=p0>>12;                 // Q20
 muls r3,r2
 asrs r3,#13                   @  i32 dy0=(r0*a0)>>13;           // Q15
 lsls r2,#8
 subs r2,r3                    @  i32 a1=(a0<<8)-dy0;         // Q16

 movs r3,r2
 muls r3,r3
 lsrs r3,#13
 lsrs r4,r1,#1
 muls r3,r4                    @  i32 p1=((a1*a1)>>11)*(y>>11);  // Q19*Q19=Q38
 asrs r3,#15                   @  i32 r1=p1>>15;                 // Q23
 muls r3,r2
 asrs r3,#23
 adds r3,#1
 asrs r3,#1                    @  i32 dy1=(r1*a1+(1<<23))>>24;   // Q23*Q16=Q39; Q15
 subs r2,r3                    @  i32 a2=a1-dy1;                 // Q16
 lsrs r3,r2,#16
 subs r2,r3                    @  if(a2>=0x10000) a2=0xffff; to prevent overflow of a2*a2

@ here
@ r0:r1 y mantissa
@ r2    a2 ~ 1/sqrt(y) Q16
@ r12   result exponent

 movs r3,r2
 muls r3,r3
 lsls r1,#10
 lsrs r4,r0,#22
 orrs r1,r4                    @ y Q30
 mul32_32_64 r1,r3, r4,r3, r5,r6,r7,r4,r3   @  i64 p2=(ui64)(a2*a2)*(ui64)y;  // Q62 r4:r3
 lsls r5,r3,#6
 lsrs r4,#26
 orrs r4,r5
 adds r4,#0x20                 @  i32 r2=(p2>>26)+0x20;          // Q36 r4
 uxth r5,r4
 muls r5,r2
 asrs r4,#16
 muls r4,r2
 lsrs r5,#16
 adds r4,r5
 asrs r4,#6                    @ i32 dy2=((i64)r2*(i64)a2)>>22; // Q36*Q16=Q52; Q30
 lsls r2,#15
 subs r2,r4

@ here
@ r0    y low bits
@ r1    y Q30
@ r2    a3 ~ 1/sqrt(y) Q31
@ r12   result exponent

 mul32_32_64 r2,r1, r3,r4, r5,r6,r7,r3,r4
 adds r3,r3,r3
 adcs r4,r4,r4
 adds r3,r3,r3
 movs r3,#0
 adcs r3,r4                    @ ui32 a4=((ui64)a3*(ui64)y+(1U<<31))>>31; // Q30

@ here
@ r0    y low bits
@ r1    y Q30
@ r2    a3 Q31 ~ 1/sqrt(y)
@ r3    a4 Q30 ~ sqrt(y)
@ r12   result exponent

 square32_64 r3, r4,r5, r6,r5,r7
 lsls r6,r0,#8
 lsrs r7,r1,#2
 subs r6,r4
 sbcs r7,r5                    @ r4=(q60)y-a4*a4

@ by exhaustive testing, r4 = fffffffc0e134fdc .. 00000003c2bf539c Q60

 lsls r5,r7,#29
 lsrs r6,#3
 adcs r6,r5                    @ r4 Q57 with rounding
 muls32_32_64 r6,r2, r6,r2, r4,r5,r7,r6,r2    @ d4=a3*r4/2 Q89
@ r4+d4 is correct to 1ULP at Q57, tested on ~9bn cases including all extreme values of r4 for each possible y Q30

 adds r2,#8
 asrs r2,#5                    @ d4 Q52, rounded to Q53 with spare bit in carry

@ here
@ r0    y low bits
@ r1    y Q30
@ r2    d4 Q52, rounded to Q53
@ C flag contains d4_b53
@ r3    a4 Q30

 bcs dq_5

 lsrs r5,r3,#10                @ a4 Q52
 lsls r4,r3,#22

 asrs r1,r2,#31
 adds r0,r2,r4
 adcs r1,r5                    @ a4+d4

 add r1,r12                    @ pack exponent
 pop {r4-r7,r15}

.ltorg


@ round(sqrt(2^22./[68:8:252]))
drsqrtapp:
.byte 0xf8,0xeb,0xdf,0xd6,0xcd,0xc5,0xbe,0xb8
.byte 0xb2,0xad,0xa8,0xa4,0xa0,0x9c,0x99,0x95
.byte 0x92,0x8f,0x8d,0x8a,0x88,0x85,0x83,0x81

dq_5:
@ here we are near a rounding boundary, C is set
 adcs r2,r2,r2                 @ d4 Q53+1ulp
 lsrs r5,r3,#9
 lsls r4,r3,#23                @ r4:r5 a4 Q53
 asrs r1,r2,#31
 adds r4,r2,r4
 adcs r5,r1                    @ r4:r5 a5=a4+d4 Q53+1ulp
 movs r3,r5
 muls r3,r4
 square32_64 r4,r1,r2,r6,r2,r7
 adds r2,r3
 adds r2,r3                    @ r1:r2 a5^2 Q106
 lsls r0,#22                   @ y Q84

 negs r1,r1
 sbcs r0,r2                    @ remainder y-a5^2
 bmi 1f                        @ y<a5^2: no need to increment a5
 movs r3,#0
 adds r4,#1
 adcs r5,r3                    @ bump a5 if over rounding boundary
1:
 lsrs r0,r4,#1
 lsrs r1,r5,#1
 lsls r5,#31
 orrs r0,r5
 add r1,r12
 pop {r4-r7,r15}

@ "scientific" functions start here

@ double-length CORDIC rotation step

@ r0:r1   ω
@ r6      32-i (complementary shift)
@ r7      i (shift)
@ r8:r9   x
@ r10:r11 y
@ r12     coefficient pointer

@ an option in rotation mode would be to compute the sequence of σ values
@ in one pass, rotate the initial vector by the residual ω and then run a
@ second pass to compute the final x and y. This would relieve pressure
@ on registers and hence possibly be faster. The same trick does not work
@ in vectoring mode (but perhaps one could work to single precision in
@ a first pass and then double precision in a second pass?).

double_section dcordic_vec_step
 regular_func dcordic_vec_step
 mov r2,r12
 ldmia r2!,{r3,r4}
 mov r12,r2
 mov r2,r11
 cmp r2,#0
 blt 1f
 b 2f

double_section dcordic_rot_step
 regular_func dcordic_rot_step
 mov r2,r12
 ldmia r2!,{r3,r4}
 mov r12,r2
 cmp r1,#0
 bge 1f
2:
@ ω<0 / y>=0
@ ω+=dω
@ x+=y>>i, y-=x>>i
 adds r0,r3
 adcs r1,r4

 mov r3,r11
 asrs r3,r7
 mov r4,r11
 lsls r4,r6
 mov r2,r10
 lsrs r2,r7
 orrs r2,r4                    @ r2:r3 y>>i, rounding in carry
 mov r4,r8
 mov r5,r9                     @ r4:r5 x
 adcs r2,r4
 adcs r3,r5                    @ r2:r3 x+(y>>i)
 mov r8,r2
 mov r9,r3

 mov r3,r5
 lsls r3,r6
 asrs r5,r7
 lsrs r4,r7
 orrs r4,r3                    @ r4:r5 x>>i, rounding in carry
 mov r2,r10
 mov r3,r11
 sbcs r2,r4
 sbcs r3,r5                    @ r2:r3 y-(x>>i)
 mov r10,r2
 mov r11,r3
 bx r14


@ ω>0 / y<0
@ ω-=dω
@ x-=y>>i, y+=x>>i
1:
 subs r0,r3
 sbcs r1,r4

 mov r3,r9
 asrs r3,r7
 mov r4,r9
 lsls r4,r6
 mov r2,r8
 lsrs r2,r7
 orrs r2,r4                    @ r2:r3 x>>i, rounding in carry
 mov r4,r10
 mov r5,r11                    @ r4:r5 y
 adcs r2,r4
 adcs r3,r5                    @ r2:r3 y+(x>>i)
 mov r10,r2
 mov r11,r3

 mov r3,r5
 lsls r3,r6
 asrs r5,r7
 lsrs r4,r7
 orrs r4,r3                    @ r4:r5 y>>i, rounding in carry
 mov r2,r8
 mov r3,r9
 sbcs r2,r4
 sbcs r3,r5                    @ r2:r3 x-(y>>i)
 mov r8,r2
 mov r9,r3
 bx r14

@ convert packed double in r0:r1 to signed/unsigned 32/64-bit integer/fixed-point value in r0:r1 [with r2 places after point], with rounding towards -Inf
@ fixed-point versions only work with reasonable values in r2 because of the way dunpacks works

double_section double2int_shim
 regular_func double2int_shim
 movs r2,#0                    @ and fall through
regular_func double2fix_shim
 push {r14}
 adds r2,#32
 bl double2fix64_shim
 movs r0,r1
 pop {r15}

double_section double2uint_shim
 regular_func double2uint_shim
 movs r2,#0                    @ and fall through
regular_func double2ufix_shim
 push {r14}
 adds r2,#32
 bl double2ufix64_shim
 movs r0,r1
 pop {r15}

double_section double2int64_shim
 regular_func double2int64_shim
 movs r2,#0                    @ and fall through
regular_func double2fix64_shim
 push {r14}
 bl d2fix

 asrs r2,r1,#31
 cmp r2,r3
 bne 1f                        @ sign extension bits fail to match sign of result?
 pop {r15}
1:
 mvns r0,r3
 movs r1,#1
 lsls r1,#31
 eors r1,r1,r0                 @ generate extreme fixed-point values
 pop {r15}

double_section double2uint64_shim 
 regular_func double2uint64_shim
 movs r2,#0                    @ and fall through
regular_func double2ufix64_shim
 asrs r3,r1,#20                @ negative? return 0
 bmi ret_dzero
@ and fall through

@ convert double in r0:r1 to signed fixed point in r0:r1:r3, r2 places after point, rounding towards -Inf
@ result clamped so that r3 can only be 0 or -1
@ trashes r12
.thumb_func
d2fix:
 push {r4,r14}
 mov r12,r2
 bl dunpacks
 asrs r4,r2,#16
 adds r4,#1
 bge 1f
 movs r1,#0                    @ -0 -> +0
1:
 asrs r3,r1,#31
 ldr r4, =d2fix_a
 bx r4
 
ret_dzero:
 movs r0,#0
 movs r1,#0
 bx r14
 
.weak d2fix_a // weak because it exists in float code too
.thumb_func
d2fix_a:
@ here
@ r0:r1 two's complement mantissa
@ r2    unbaised exponent
@ r3    mantissa sign extension bits
 add r2,r12                    @ exponent plus offset for required binary point position
 subs r2,#52                   @ required shift
 bmi 1f                        @ shift down?
@ here a shift up by r2 places
 cmp r2,#12                    @ will clamp?
 bge 2f
 movs r4,r0
 lsls r1,r2
 lsls r0,r2
 negs r2,r2
 adds r2,#32                   @ complementary shift
 lsrs r4,r2
 orrs r1,r4
 pop {r4,r15}
2:
 mvns r0,r3
 mvns r1,r3                    @ overflow: clamp to extreme fixed-point values
 pop {r4,r15}
1:
@ here a shift down by -r2 places
 adds r2,#32
 bmi 1f                        @ long shift?
 mov r4,r1
 lsls r4,r2
 negs r2,r2
 adds r2,#32                   @ complementary shift
 asrs r1,r2
 lsrs r0,r2
 orrs r0,r4
 pop {r4,r15}
1:
@ here a long shift down
 movs r0,r1
 asrs r1,#31                   @ shift down 32 places
 adds r2,#32
 bmi 1f                        @ very long shift?
 negs r2,r2
 adds r2,#32
 asrs r0,r2
 pop {r4,r15}
1:
 movs r0,r3                    @ result very near zero: use sign extension bits
 movs r1,r3
 pop {r4,r15}

double_section double2float_shim
 regular_func double2float_shim
 lsls r2,r1,#1
 lsrs r2,#21                   @ exponent
 ldr r3,=0x3ff-0x7f
 subs r2,r3                    @ fix exponent bias
 ble 1f                        @ underflow or zero
 cmp r2,#0xff
 bge 2f                        @ overflow or infinity
 lsls r2,#23                   @ position exponent of result
 lsrs r3,r1,#31
 lsls r3,#31
 orrs r2,r3                    @ insert sign
 lsls r3,r0,#3                 @ rounding bits
 lsrs r0,#29
 lsls r1,#12
 lsrs r1,#9
 orrs r0,r1                    @ assemble mantissa
 orrs r0,r2                    @ insert exponent and sign
 lsls r3,#1
 bcc 3f                        @ no rounding
 beq 4f                        @ all sticky bits 0?
5:
 adds r0,#1
3:
 bx r14
4:
 lsrs r3,r0,#1                 @ odd? then round up
 bcs 5b
 bx r14
1:
 beq 6f                        @ check case where value is just less than smallest normal
7:
 lsrs r0,r1,#31
 lsls r0,#31
 bx r14
6:
 lsls r2,r1,#12                @ 20 1:s at top of mantissa?
 asrs r2,#12
 adds r2,#1
 bne 7b
 lsrs r2,r0,#29                @ and 3 more 1:s?
 cmp r2,#7
 bne 7b
 movs r2,#1                    @ return smallest normal with correct sign
 b 8f
2:
 movs r2,#0xff
8:
 lsrs r0,r1,#31                @ return signed infinity
 lsls r0,#8
 adds r0,r2
 lsls r0,#23
 bx r14

double_section x2double_shims
@ convert signed/unsigned 32/64-bit integer/fixed-point value in r0:r1 [with r2 places after point] to packed double in r0:r1, with rounding

.align 2
regular_func uint2double_shim
 movs r1,#0                    @ and fall through
regular_func ufix2double_shim
 movs r2,r1
 movs r1,#0
 b ufix642double_shim

.align 2
regular_func int2double_shim
 movs r1,#0                    @ and fall through
regular_func fix2double_shim
 movs r2,r1
 asrs r1,r0,#31                @ sign extend
 b fix642double_shim

.align 2
regular_func uint642double_shim
 movs r2,#0                    @ and fall through
regular_func ufix642double_shim
 movs r3,#0
 b uf2d

.align 2
regular_func int642double_shim
 movs r2,#0                    @ and fall through
regular_func fix642double_shim
 asrs r3,r1,#31                @ sign bit across all bits
 eors r0,r3
 eors r1,r3
 subs r0,r3
 sbcs r1,r3
uf2d:
 push {r4,r5,r14}
 ldr r4,=0x432
 subs r2,r4,r2                 @ form biased exponent
@ here
@ r0:r1 unnormalised mantissa
@ r2 -Q (will become exponent)
@ r3 sign across all bits
 cmp r1,#0
 bne 1f                        @ short normalising shift?
 movs r1,r0
 beq 2f                        @ zero? return it
 movs r0,#0
 subs r2,#32                   @ fix exponent
1:
 asrs r4,r1,#21
 bne 3f                        @ will need shift down (and rounding?)
 bcs 4f                        @ normalised already?
5:
 subs r2,#1
 adds r0,r0                    @ shift up
 adcs r1,r1
 lsrs r4,r1,#21
 bcc 5b
4:
 ldr r4,=0x7fe
 cmp r2,r4
 bhs 6f                        @ over/underflow? return signed zero/infinity
7:
 lsls r2,#20                   @ pack and return
 adds r1,r2
 lsls r3,#31
 adds r1,r3
2:
 pop {r4,r5,r15}
6:                             @ return signed zero/infinity according to unclamped exponent in r2
 mvns r2,r2
 lsrs r2,#21
 movs r0,#0
 movs r1,#0
 b 7b

3:
@ here we need to shift down to normalise and possibly round
 bmi 1f                        @ already normalised to Q63?
2:
 subs r2,#1
 adds r0,r0                    @ shift up
 adcs r1,r1
 bpl 2b
1:
@ here we have a 1 in b63 of r0:r1
 adds r2,#11                   @ correct exponent for subsequent shift down
 lsls r4,r0,#21                @ save bits for rounding
 lsrs r0,#11
 lsls r5,r1,#21
 orrs r0,r5
 lsrs r1,#11
 lsls r4,#1
 beq 1f                        @ sticky bits are zero?
8:
 movs r4,#0
 adcs r0,r4
 adcs r1,r4
 b 4b
1:
 bcc 4b                        @ sticky bits are zero but not on rounding boundary
 lsrs r4,r0,#1                 @ increment if odd (force round to even)
 b 8b


.ltorg

double_section dunpacks
 regular_func dunpacks
 mdunpacks r0,r1,r2,r3,r4
 ldr r3,=0x3ff
 subs r2,r3                    @ exponent without offset
 bx r14

@ r0:r1  signed mantissa Q52
@ r2     unbiased exponent < 10 (i.e., |x|<2^10)
@ r4     pointer to:
@          - divisor reciprocal approximation r=1/d Q15
@          - divisor d Q62  0..20
@          - divisor d Q62 21..41
@          - divisor d Q62 42..62
@ returns:
@ r0:r1  reduced result y Q62, -0.6 d < y < 0.6 d (better in practice)
@ r2     quotient q (number of reductions)
@ if exponent >=10, returns r0:r1=0, r2=1024*mantissa sign
@ designed to work for 0.5<d<2, in particular d=ln2 (~0.7) and d=π/2 (~1.6)
double_section dreduce
 regular_func dreduce
 adds r2,#2                    @ e+2
 bmi 1f                        @ |x|<0.25, too small to need adjustment
 cmp r2,#12
 bge 4f
2:
 movs r5,#17
 subs r5,r2                    @ 15-e
 movs r3,r1                    @ Q20
 asrs r3,r5                    @ x Q5
 adds r2,#8                    @ e+10
 adds r5,#7                    @ 22-e = 32-(e+10)
 movs r6,r0
 lsrs r6,r5
 lsls r0,r2
 lsls r1,r2
 orrs r1,r6                    @ r0:r1 x Q62
 ldmia r4,{r4-r7}
 muls r3,r4                    @ rx Q20
 asrs r2,r3,#20
 movs r3,#0
 adcs r2,r3                    @ rx Q0 rounded = q; for e.g. r=1.5 |q|<1.5*2^10
 muls r5,r2                    @ qd in pieces: L Q62
 muls r6,r2                    @               M Q41
 muls r7,r2                    @               H Q20
 lsls r7,#10
 asrs r4,r6,#11
 lsls r6,#21
 adds r6,r5
 adcs r7,r4
 asrs r5,#31
 adds r7,r5                    @ r6:r7 qd Q62
 subs r0,r6
 sbcs r1,r7                    @ remainder Q62
 bx r14
4:
 movs r2,#12                   @ overflow: clamp to +/-1024
 movs r0,#0
 asrs r1,#31
 lsls r1,#1
 adds r1,#1
 lsls r1,#20
 b 2b

1:
 lsls r1,#8
 lsrs r3,r0,#24
 orrs r1,r3
 lsls r0,#8                    @ r0:r1 Q60, to be shifted down -r2 places
 negs r3,r2
 adds r2,#32                   @ shift down in r3, complementary shift in r2
 bmi 1f                        @ long shift?
2:
 movs r4,r1
 asrs r1,r3
 lsls r4,r2
 lsrs r0,r3
 orrs r0,r4
 movs r2,#0                    @ rounding
 adcs r0,r2
 adcs r1,r2
 bx r14

1:
 movs r0,r1                    @ down 32 places
 asrs r1,#31
 subs r3,#32
 adds r2,#32
 bpl 2b
 movs r0,#0                    @ very long shift? return 0
 movs r1,#0
 movs r2,#0
 bx r14

double_section dtan_shim
 regular_func dtan_shim
 push {r4-r7,r14}
 bl push_r8_r11
 bl dsincos_internal
 mov r12,r0                    @ save ε
 bl dcos_finish
 push {r0,r1}
 mov r0,r12
 bl dsin_finish
 pop {r2,r3}
 bl pop_r8_r11
 b ddiv0                       @ compute sin θ/cos θ

double_section dcos_shim
 regular_func dcos_shim
 push {r4-r7,r14}
 bl push_r8_r11
 bl dsincos_internal
 bl dcos_finish
 b 1f

double_section dsin_shim
 regular_func dsin_shim
 push {r4-r7,r14}
 bl push_r8_r11
 bl dsincos_internal
 bl dsin_finish
1:
 bl pop_r8_r11
 pop {r4-r7,r15}

double_section dsincos_shim

 @ Note that this function returns in r0-r3
 regular_func dsincos_shim

 push {r4-r7,r14}
 bl push_r8_r11
 bl dsincos_internal
 mov r12,r0                    @ save ε
 bl dcos_finish
 push {r0,r1}
 mov r0,r12
 bl dsin_finish
 pop {r2,r3}
 bl pop_r8_r11
 pop {r4-r7,r15}

double_section dtrig_guts

@ unpack double θ in r0:r1, range reduce and calculate ε, cos α and sin α such that
@ θ=α+ε and |ε|≤2^-32
@ on return:
@ r0:r1   ε (residual ω, where θ=α+ε) Q62, |ε|≤2^-32 (so fits in r0)
@ r8:r9   cos α Q62
@ r10:r11 sin α Q62
.align 2
.thumb_func
dsincos_internal:
 push {r14}
 bl dunpacks
 adr r4,dreddata0
 bl dreduce

 movs r4,#0
 ldr r5,=0x9df04dbb           @ this value compensates for the non-unity scaling of the CORDIC rotations
 ldr r6,=0x36f656c5
 lsls r2,#31
 bcc 1f
@ quadrant 2 or 3
 mvns r6,r6
 negs r5,r5
 adcs r6,r4
1:
 lsls r2,#1
 bcs 1f
@ even quadrant
 mov r10,r4
 mov r11,r4
 mov r8,r5
 mov r9,r6
 b 2f
1:
@ odd quadrant
 mov r8,r4
 mov r9,r4
 mov r10,r5
 mov r11,r6
2:
 adr r4,dtab_cc
 mov r12,r4
 movs r7,#1
 movs r6,#31
1:
 bl dcordic_rot_step
 adds r7,#1
 subs r6,#1
 cmp r7,#33
 bne 1b
 pop {r15}

dcos_finish:
@ here
@ r0:r1   ε (residual ω, where θ=α+ε) Q62, |ε|≤2^-32 (so fits in r0)
@ r8:r9   cos α Q62
@ r10:r11 sin α Q62
@ and we wish to calculate cos θ=cos(α+ε)~cos α - ε sin α
 mov r1,r11
@ mov r2,r10
@ lsrs r2,#31
@ adds r1,r2                    @ rounding improves accuracy very slightly
 muls32_s32_64 r0,r1, r2,r3, r4,r5,r6,r2,r3
@ r2:r3   ε sin α Q(62+62-32)=Q92
 mov r0,r8
 mov r1,r9
 lsls r5,r3,#2
 asrs r3,r3,#30
 lsrs r2,r2,#30
 orrs r2,r5
 sbcs r0,r2                    @ include rounding
 sbcs r1,r3
 movs r2,#62
 b fix642double_shim

dsin_finish:
@ here
@ r0:r1   ε (residual ω, where θ=α+ε) Q62, |ε|≤2^-32 (so fits in r0)
@ r8:r9   cos α Q62
@ r10:r11 sin α Q62
@ and we wish to calculate sin θ=sin(α+ε)~sin α + ε cos α
 mov r1,r9
 muls32_s32_64 r0,r1, r2,r3, r4,r5,r6,r2,r3
@ r2:r3   ε cos α Q(62+62-32)=Q92
 mov r0,r10
 mov r1,r11
 lsls r5,r3,#2
 asrs r3,r3,#30
 lsrs r2,r2,#30
 orrs r2,r5
 adcs r0,r2                    @ include rounding
 adcs r1,r3
 movs r2,#62
 b fix642double_shim

.ltorg
.align 2
dreddata0:
.word 0x0000517d               @ 2/π Q15
.word 0x0014611A               @ π/2 Q62=6487ED5110B4611A split into 21-bit pieces
.word 0x000A8885
.word 0x001921FB


.align 2
regular_func datan2_shim
@ r0:r1 y
@ r2:r3 x
 push {r4-r7,r14}
 bl push_r8_r11
 ldr r5,=0x7ff00000
 movs r4,r1
 ands r4,r5                    @ y==0?
 beq 1f
 cmp r4,r5                     @ or Inf/NaN?
 bne 2f
1:
 lsrs r1,#20                   @ flush
 lsls r1,#20
 movs r0,#0
2:
 movs r4,r3
 ands r4,r5                    @ x==0?
 beq 1f
 cmp r4,r5                     @ or Inf/NaN?
 bne 2f
1:
 lsrs r3,#20                   @ flush
 lsls r3,#20
 movs r2,#0
2:
 movs r6,#0                    @ quadrant offset
 lsls r5,#11                   @ constant 0x80000000
 cmp r3,#0
 bpl 1f                        @ skip if x positive
 movs r6,#2
 eors r3,r5
 eors r1,r5
 bmi 1f                        @ quadrant offset=+2 if y was positive
 negs r6,r6                    @ quadrant offset=-2 if y was negative
1:
@ now in quadrant 0 or 3
 adds r7,r1,r5                 @ r7=-r1
 bpl 1f
@ y>=0: in quadrant 0
 cmp r1,r3
 ble 2f                        @ y<~x so 0≤θ<~π/4: skip
 adds r6,#1
 eors r1,r5                    @ negate x
 b 3f                          @ and exchange x and y = rotate by -π/2
1:
 cmp r3,r7
 bge 2f                        @ -y<~x so -π/4<~θ≤0: skip
 subs r6,#1
 eors r3,r5                    @ negate y and ...
3:
 movs r7,r0                    @ exchange x and y
 movs r0,r2
 movs r2,r7
 movs r7,r1
 movs r1,r3
 movs r3,r7
2:
@ here -π/4<~θ<~π/4
@ r6 has quadrant offset
 push {r6}
 cmp r2,#0
 bne 1f
 cmp r3,#0
 beq 10f                       @ x==0 going into division?
 lsls r4,r3,#1
 asrs r4,#21
 adds r4,#1
 bne 1f                        @ x==Inf going into division?
 lsls r4,r1,#1
 asrs r4,#21
 adds r4,#1                    @ y also ±Inf?
 bne 10f
 subs r1,#1                    @ make them both just finite
 subs r3,#1
 b 1f

10:
 movs r0,#0
 movs r1,#0
 b 12f

1:
 bl ddiv_shim
 movs r2,#62
 bl double2fix64_shim
@ r0:r1 y/x
 mov r10,r0
 mov r11,r1
 movs r0,#0                    @ ω=0
 movs r1,#0
 mov r8,r0
 movs r2,#1
 lsls r2,#30
 mov r9,r2                     @ x=1

 adr r4,dtab_cc
 mov r12,r4
 movs r7,#1
 movs r6,#31
1:
 bl dcordic_vec_step
 adds r7,#1
 subs r6,#1
 cmp r7,#33
 bne 1b
@ r0:r1   atan(y/x) Q62
@ r8:r9   x residual Q62
@ r10:r11 y residual Q62
 mov r2,r9
 mov r3,r10
 subs r2,#12                   @ this makes atan(0)==0
@ the following is basically a division residual y/x ~ atan(residual y/x)
 movs r4,#1
 lsls r4,#29
 movs r7,#0
2:
 lsrs r2,#1
 movs r3,r3                    @ preserve carry
 bmi 1f
 sbcs r3,r2
 adds r0,r4
 adcs r1,r7
 lsrs r4,#1
 bne 2b
 b 3f
1:
 adcs r3,r2
 subs r0,r4
 sbcs r1,r7
 lsrs r4,#1
 bne 2b
3:
 lsls r6,r1,#31
 asrs r1,#1
 lsrs r0,#1
 orrs r0,r6                    @ Q61

12:
 pop {r6}

 cmp r6,#0
 beq 1f
 ldr r4,=0x885A308D           @ π/2 Q61
 ldr r5,=0x3243F6A8
 bpl 2f
 mvns r4,r4                    @ negative quadrant offset
 mvns r5,r5
2:
 lsls r6,#31
 bne 2f                        @ skip if quadrant offset is ±1
 adds r0,r4
 adcs r1,r5
2:
 adds r0,r4
 adcs r1,r5
1:
 movs r2,#61
 bl fix642double_shim

 bl pop_r8_r11
 pop {r4-r7,r15}

.ltorg

dtab_cc:
.word 0x61bb4f69, 0x1dac6705   @ atan 2^-1 Q62
.word 0x96406eb1, 0x0fadbafc   @ atan 2^-2 Q62
.word 0xab0bdb72, 0x07f56ea6   @ atan 2^-3 Q62
.word 0xe59fbd39, 0x03feab76   @ atan 2^-4 Q62
.word 0xba97624b, 0x01ffd55b   @ atan 2^-5 Q62
.word 0xdddb94d6, 0x00fffaaa   @ atan 2^-6 Q62
.word 0x56eeea5d, 0x007fff55   @ atan 2^-7 Q62
.word 0xaab7776e, 0x003fffea   @ atan 2^-8 Q62
.word 0x5555bbbc, 0x001ffffd   @ atan 2^-9 Q62
.word 0xaaaaadde, 0x000fffff   @ atan 2^-10 Q62
.word 0xf555556f, 0x0007ffff   @ atan 2^-11 Q62
.word 0xfeaaaaab, 0x0003ffff   @ atan 2^-12 Q62
.word 0xffd55555, 0x0001ffff   @ atan 2^-13 Q62
.word 0xfffaaaab, 0x0000ffff   @ atan 2^-14 Q62
.word 0xffff5555, 0x00007fff   @ atan 2^-15 Q62
.word 0xffffeaab, 0x00003fff   @ atan 2^-16 Q62
.word 0xfffffd55, 0x00001fff   @ atan 2^-17 Q62
.word 0xffffffab, 0x00000fff   @ atan 2^-18 Q62
.word 0xfffffff5, 0x000007ff   @ atan 2^-19 Q62
.word 0xffffffff, 0x000003ff   @ atan 2^-20 Q62
.word 0x00000000, 0x00000200   @ atan 2^-21 Q62 @ consider optimising these
.word 0x00000000, 0x00000100   @ atan 2^-22 Q62
.word 0x00000000, 0x00000080   @ atan 2^-23 Q62
.word 0x00000000, 0x00000040   @ atan 2^-24 Q62
.word 0x00000000, 0x00000020   @ atan 2^-25 Q62
.word 0x00000000, 0x00000010   @ atan 2^-26 Q62
.word 0x00000000, 0x00000008   @ atan 2^-27 Q62
.word 0x00000000, 0x00000004   @ atan 2^-28 Q62
.word 0x00000000, 0x00000002   @ atan 2^-29 Q62
.word 0x00000000, 0x00000001   @ atan 2^-30 Q62
.word 0x80000000, 0x00000000   @ atan 2^-31 Q62
.word 0x40000000, 0x00000000   @ atan 2^-32 Q62

double_section dexp_guts
regular_func dexp_shim
 push {r4-r7,r14}
 bl dunpacks
 adr r4,dreddata1
 bl dreduce
 cmp r1,#0
 bge 1f
 ldr r4,=0xF473DE6B
 ldr r5,=0x2C5C85FD           @ ln2 Q62
 adds r0,r4
 adcs r1,r5
 subs r2,#1
1:
 push {r2}
 movs r7,#1                    @ shift
 adr r6,dtab_exp
 movs r2,#0
 movs r3,#1
 lsls r3,#30                   @ x=1 Q62

3:
 ldmia r6!,{r4,r5}
 mov r12,r6
 subs r0,r4
 sbcs r1,r5
 bmi 1f

 negs r6,r7
 adds r6,#32                   @ complementary shift
 movs r5,r3
 asrs r5,r7
 movs r4,r3
 lsls r4,r6
 movs r6,r2
 lsrs r6,r7                    @ rounding bit in carry
 orrs r4,r6
 adcs r2,r4
 adcs r3,r5                    @ x+=x>>i
 b 2f

1:
 adds r0,r4                    @ restore argument
 adcs r1,r5
2:
 mov r6,r12
 adds r7,#1
 cmp r7,#33
 bne 3b

@ here
@ r0:r1   ε (residual x, where x=a+ε) Q62, |ε|≤2^-32 (so fits in r0)
@ r2:r3   exp a Q62
@ and we wish to calculate exp x=exp a exp ε~(exp a)(1+ε)
 muls32_32_64 r0,r3, r4,r1, r5,r6,r7,r4,r1
@ r4:r1 ε exp a Q(62+62-32)=Q92
 lsrs r4,#30
 lsls r0,r1,#2
 orrs r0,r4
 asrs r1,#30
 adds r0,r2
 adcs r1,r3

 pop {r2}
 negs r2,r2
 adds r2,#62
 bl fix642double_shim                 @ in principle we can pack faster than this because we know the exponent
 pop {r4-r7,r15}

.ltorg

.align 2
regular_func dln_shim
 push {r4-r7,r14}
 lsls r7,r1,#1
 bcs 5f                        @ <0 ...
 asrs r7,#21
 beq 5f                        @ ... or =0? return -Inf
 adds r7,#1
 beq 6f                        @ Inf/NaN? return +Inf
 bl dunpacks
 push {r2}
 lsls r1,#9
 lsrs r2,r0,#23
 orrs r1,r2
 lsls r0,#9
@ r0:r1 m Q61 = m/2 Q62 0.5≤m/2<1

 movs r7,#1                    @ shift
 adr r6,dtab_exp
 mov r12,r6
 movs r2,#0
 movs r3,#0                    @ y=0 Q62

3:
 negs r6,r7
 adds r6,#32                   @ complementary shift
 movs r5,r1
 asrs r5,r7
 movs r4,r1
 lsls r4,r6
 movs r6,r0
 lsrs r6,r7
 orrs r4,r6                    @ x>>i, rounding bit in carry
 adcs r4,r0
 adcs r5,r1                    @ x+(x>>i)

 lsrs r6,r5,#30
 bne 1f                        @ x+(x>>i)>1?
 movs r0,r4
 movs r1,r5                    @ x+=x>>i
 mov r6,r12
 ldmia r6!,{r4,r5}
 subs r2,r4
 sbcs r3,r5

1:
 movs r4,#8
 add r12,r4
 adds r7,#1
 cmp r7,#33
 bne 3b
@ here:
@ r0:r1 residual x, nearly 1 Q62
@ r2:r3 y ~ ln m/2 = ln m - ln2 Q62
@ result is y + ln2 + ln x ~ y + ln2 + (x-1)
 lsls r1,#2
 asrs r1,#2                    @ x-1
 adds r2,r0
 adcs r3,r1

 pop {r7}
@ here:
@ r2:r3 ln m/2 = ln m - ln2 Q62
@ r7    unbiased exponent
.equ dreddata1_plus_4, (dreddata1+4)
 adr r4,dreddata1_plus_4
 ldmia r4,{r0,r1,r4}
 adds r7,#1
 muls r0,r7                    @ Q62
 muls r1,r7                    @ Q41
 muls r4,r7                    @ Q20
 lsls r7,r1,#21
 asrs r1,#11
 asrs r5,r1,#31
 adds r0,r7
 adcs r1,r5
 lsls r7,r4,#10
 asrs r4,#22
 asrs r5,r1,#31
 adds r1,r7
 adcs r4,r5
@ r0:r1:r4 exponent*ln2 Q62
 asrs r5,r3,#31
 adds r0,r2
 adcs r1,r3
 adcs r4,r5
@ r0:r1:r4 result Q62
 movs r2,#62
1:
 asrs r5,r1,#31
 cmp r4,r5
 beq 2f                        @ r4 a sign extension of r1?
 lsrs r0,#4                    @ no: shift down 4 places and try again
 lsls r6,r1,#28
 orrs r0,r6
 lsrs r1,#4
 lsls r6,r4,#28
 orrs r1,r6
 asrs r4,#4
 subs r2,#4
 b 1b
2:
 bl fix642double_shim
 pop {r4-r7,r15}

5:
 ldr r1,=0xfff00000
 movs r0,#0
 pop {r4-r7,r15}

6:
 ldr r1,=0x7ff00000
 movs r0,#0
 pop {r4-r7,r15}

.ltorg

.align 2
dreddata1:
.word 0x0000B8AA               @ 1/ln2 Q15
.word 0x0013DE6B               @ ln2 Q62 Q62=2C5C85FDF473DE6B split into 21-bit pieces
.word 0x000FEFA3
.word 0x000B1721

dtab_exp:
.word 0xbf984bf3, 0x19f323ec   @ log 1+2^-1 Q62
.word 0xcd4d10d6, 0x0e47fbe3   @ log 1+2^-2 Q62
.word 0x8abcb97a, 0x0789c1db   @ log 1+2^-3 Q62
.word 0x022c54cc, 0x03e14618   @ log 1+2^-4 Q62
.word 0xe7833005, 0x01f829b0   @ log 1+2^-5 Q62
.word 0x87e01f1e, 0x00fe0545   @ log 1+2^-6 Q62
.word 0xac419e24, 0x007f80a9   @ log 1+2^-7 Q62
.word 0x45621781, 0x003fe015   @ log 1+2^-8 Q62
.word 0xa9ab10e6, 0x001ff802   @ log 1+2^-9 Q62
.word 0x55455888, 0x000ffe00   @ log 1+2^-10 Q62
.word 0x0aa9aac4, 0x0007ff80   @ log 1+2^-11 Q62
.word 0x01554556, 0x0003ffe0   @ log 1+2^-12 Q62
.word 0x002aa9ab, 0x0001fff8   @ log 1+2^-13 Q62
.word 0x00055545, 0x0000fffe   @ log 1+2^-14 Q62
.word 0x8000aaaa, 0x00007fff   @ log 1+2^-15 Q62
.word 0xe0001555, 0x00003fff   @ log 1+2^-16 Q62
.word 0xf80002ab, 0x00001fff   @ log 1+2^-17 Q62
.word 0xfe000055, 0x00000fff   @ log 1+2^-18 Q62
.word 0xff80000b, 0x000007ff   @ log 1+2^-19 Q62
.word 0xffe00001, 0x000003ff   @ log 1+2^-20 Q62
.word 0xfff80000, 0x000001ff   @ log 1+2^-21 Q62
.word 0xfffe0000, 0x000000ff   @ log 1+2^-22 Q62
.word 0xffff8000, 0x0000007f   @ log 1+2^-23 Q62
.word 0xffffe000, 0x0000003f   @ log 1+2^-24 Q62
.word 0xfffff800, 0x0000001f   @ log 1+2^-25 Q62
.word 0xfffffe00, 0x0000000f   @ log 1+2^-26 Q62
.word 0xffffff80, 0x00000007   @ log 1+2^-27 Q62
.word 0xffffffe0, 0x00000003   @ log 1+2^-28 Q62
.word 0xfffffff8, 0x00000001   @ log 1+2^-29 Q62
.word 0xfffffffe, 0x00000000   @ log 1+2^-30 Q62
.word 0x80000000, 0x00000000   @ log 1+2^-31 Q62
.word 0x40000000, 0x00000000   @ log 1+2^-32 Q62


#endif
