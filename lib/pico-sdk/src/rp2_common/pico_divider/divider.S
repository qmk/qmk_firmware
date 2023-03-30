/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/regs/addressmap.h"
#include "hardware/divider_helper.S"

.syntax unified
.cpu cortex-m0plus
.thumb

// PICO_CONFIG: PICO_DIVIDER_DISABLE_INTERRUPTS, Disable interrupts around division such that divider state need not be saved/restored in exception handlers, default=0, group=pico_divider

#include "pico/asm_helper.S"

// PICO_CONFIG: PICO_DIVIDER_CALL_IDIV0, Whether 32 bit division by zero should call __aeabi_idiv0, default=1, group=pico_divider
#ifndef PICO_DIVIDER_CALL_IDIV0
#define PICO_DIVIDER_CALL_IDIV0 1
#endif

// PICO_CONFIG: PICO_DIVIDER_CALL_IDIV0, Whether 64 bit division by zero should call __aeabi_ldiv0, default=1, group=pico_divider
#ifndef PICO_DIVIDER_CALL_LDIV0
#define PICO_DIVIDER_CALL_LDIV0 1
#endif

// PICO_CONFIG: PICO_DIVIDER_IN_RAM, Whether divider functions should be placed in RAM, default=0, group=pico_divider
.macro div_section name
#if PICO_DIVIDER_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

@ wait 8-n cycles for the hardware divider
.macro wait_div n
.rept (8-\n) / 2
  b 9f
9:
.endr
.if (8-\n) % 2
 nop
.endif
.endm

#if (SIO_DIV_SDIVISOR_OFFSET != SIO_DIV_SDIVIDEND_OFFSET + 4) || (SIO_DIV_QUOTIENT_OFFSET != SIO_DIV_SDIVISOR_OFFSET + 4) || (SIO_DIV_REMAINDER_OFFSET != SIO_DIV_QUOTIENT_OFFSET + 4)
#error register layout has changed - we rely on this order to make sure we save/restore in the right order
#endif

#if !PICO_DIVIDER_DISABLE_INTERRUPTS
.macro save_div_state_and_lr_64
    push {r4, r5, r6, r7, lr}
    ldr r6, =SIO_BASE
    // note we must read quotient last, and since it isn't the last reg, we'll not use ldmia!
    ldr r4, [r6, #SIO_DIV_UDIVIDEND_OFFSET]
    ldr r5, [r6, #SIO_DIV_UDIVISOR_OFFSET]
    // No need to wait before reading result as long as preceeding code takes more than 8 cycles
    ldr r7, [r6, #SIO_DIV_REMAINDER_OFFSET]
    ldr r6, [r6, #SIO_DIV_QUOTIENT_OFFSET]
.endm

.macro restore_div_state_and_return_64
    // writing sdividend (r4), sdivisor (r5), quotient (r6), remainder (r7) in that order
    //
    // it is worth considering what happens if we are interrupted
    //
    // after writing r4: we are DIRTY and !READY
    //    ... interruptor using div will complete based on incorrect inputs, but dividend at least will be
    //        saved/restored correctly and we'll restore the rest ourselves
    // after writing r4, r5: we are DIRTY and !READY
    //    ... interruptor using div will complete based on possibly wrongly signed inputs, but dividend, divisor
    //        at least will be saved/restored correctly and and we'll restore the rest ourselves
    // after writing r4, r5, r6: we are DIRTY and READY
    //    ... interruptor using div will dividend, divisor, quotient registers as is (what we just restored ourselves),
    //        and we'll restore the remainder after the fact

    mov ip, r2
    ldr r2, =SIO_BASE
    // note we are not use STM not because it can be restarted due to interrupt which is harmless, more because this is 1 cycle IO space
    // and so 4 reads is cheaper (and we don't have to adjust r2)
    str r4, [r2, #SIO_DIV_UDIVIDEND_OFFSET]
    str r5, [r2, #SIO_DIV_UDIVISOR_OFFSET]
    str r7, [r2, #SIO_DIV_REMAINDER_OFFSET]
    str r6, [r2, #SIO_DIV_QUOTIENT_OFFSET]
    mov r2, ip
    pop {r4, r5, r6, r7, pc}
.endm

#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */

// since idiv and idivmod only differ by a cycle, we'll make them the same!
div_section WRAPPER_FUNC_NAME(__aeabi_idiv)
.align 2
wrapper_func __aeabi_idiv
wrapper_func __aeabi_idivmod
regular_func div_s32s32
regular_func divmod_s32s32
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    ldr r2, =SIO_BASE
    ldr r3, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r3, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs divmod_s32s32_savestate
regular_func divmod_s32s32_unsafe
#else
// to avoid too much source code spaghetti with restoring interrupts, we make this the same as the other funcs
// in the PICO_DIVIDER_DISABLE_INTERRUPTS case; i.e. it is not a faster function; this seems reasonable as there
// are the hardware_divider functions that can be used instead anyway
regular_func divmod_s32s32_unsafe
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    ldr r2, =SIO_BASE
    mrs r3, PRIMASK
    cpsid i
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */
    str r0, [r2, #SIO_DIV_SDIVIDEND_OFFSET]
    str r1, [r2, #SIO_DIV_SDIVISOR_OFFSET]
    cmp r1, #0
    beq 1f
    wait_div 2
    // return 64 bit value so we can efficiently return both (note read order is important since QUOTIENT must be read last)
    ldr r1, [r2, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r2, #SIO_DIV_QUOTIENT_OFFSET]
#if PICO_DIVIDER_DISABLE_INTERRUPTS
    msr PRIMASK, r3
#endif /* PICO_DIVIDER_DISABLE_INTERRUPTS */
    bx lr
1:
#if PICO_DIVIDER_DISABLE_INTERRUPTS
    msr PRIMASK, r3
#endif /* PICO_DIVIDER_DISABLE_INTERRUPTS */
    push {r2, lr}
    movs r1, #0x80
    lsls r1, #24
    asrs r2, r0, #31
    eors r1, r2
    cmp r0, #0
    beq 1f
    mvns r0, r1
1:
#if PICO_DIVIDER_CALL_IDIV0
    bl __aeabi_idiv0
#endif
    movs r1, #0 // remainder 0
    // need to restore saved r2 as it hold SIO ptr
    pop {r2, pc}
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
.align 2
regular_func divmod_s32s32_savestate
    save_div_state_and_lr
    bl divmod_s32s32_unsafe
    restore_div_state_and_return
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */

// since uidiv and uidivmod only differ by a cycle, we'll make them the same!
div_section WRAPPER_FUNC_NAME(__aeabi_uidiv)
regular_func div_u32u32
regular_func divmod_u32u32
wrapper_func __aeabi_uidiv
wrapper_func __aeabi_uidivmod
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    ldr r2, =SIO_BASE
    ldr r3, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r3, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs divmod_u32u32_savestate
regular_func divmod_u32u32_unsafe
#else
// to avoid too much source code spaghetti with restoring interrupts, we make this the same as the other funcs
// in the PICO_DIVIDER_DISABLE_INTERRUPTS case; i.e. it is not a faster function; this seems reasonable as there
// are the hardware_divider functions that can be used instead anyway
regular_func divmod_u32u32_unsafe
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    ldr r2, =SIO_BASE
    mrs r3, PRIMASK
    cpsid i
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */
    str r0, [r2, #SIO_DIV_UDIVIDEND_OFFSET]
    str r1, [r2, #SIO_DIV_UDIVISOR_OFFSET]
    cmp r1, #0
    beq 1f
    wait_div 2
    // return 64 bit value so we can efficiently return both (note read order is important since QUOTIENT must be read last)
    ldr r1, [r2, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r2, #SIO_DIV_QUOTIENT_OFFSET]
#if PICO_DIVIDER_DISABLE_INTERRUPTS
    msr PRIMASK, r3
#endif /* PICO_DIVIDER_DISABLE_INTERRUPTS */
    bx lr
1:
#if PICO_DIVIDER_DISABLE_INTERRUPTS
    msr PRIMASK, r3
#endif /* PICO_DIVIDER_DISABLE_INTERRUPTS */
    push {r2, lr}
    cmp r0, #0
    beq 1f
    movs r0, #0
    mvns r0, r0
1:
#if PICO_DIVIDER_CALL_IDIV0
    bl __aeabi_idiv0
#endif
    movs r1, #0 // remainder 0
    // need to restore saved r2 as it hold SIO ptr
    pop {r2, pc}
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
.align 2
regular_func divmod_u32u32_savestate
    save_div_state_and_lr
    bl divmod_u32u32_unsafe
    restore_div_state_and_return
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */

div_section WRAPPER_FUNC_NAME(__aeabi_ldiv)

.align 2
wrapper_func __aeabi_ldivmod
regular_func div_s64s64
regular_func divmod_s64s64
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    mov ip, r2
    ldr r2, =SIO_BASE
    ldr r2, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r2, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    mov r2, ip
    bcs divmod_s64s64_savestate
    b divmod_s64s64_unsafe
.align 2
divmod_s64s64_savestate:
    save_div_state_and_lr_64
    bl divmod_s64s64_unsafe
    restore_div_state_and_return_64
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl divmod_s64s64_unsafe
    msr PRIMASK, r4
    pop {r4, pc}
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */

.align 2
wrapper_func __aeabi_uldivmod
regular_func div_u64u64
regular_func divmod_u64u64
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    mov ip, r2
    ldr r2, =SIO_BASE
    ldr r2, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r2, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    mov r2, ip
    bcs divmod_u64u64_savestate
    b divmod_u64u64_unsafe
.align 2
regular_func divmod_u64u64_savestate
    save_div_state_and_lr_64
    bl divmod_u64u64_unsafe
    restore_div_state_and_return_64
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl divmod_u64u64_unsafe
    msr PRIMASK, r4
    pop {r4, pc}
#endif /* !PICO_DIVIDER_DISABLE_INTERRUPTS */

.macro dneg lo,hi
 mvns \hi,\hi
 negs \lo,\lo
 bne l\@_1
 adds \hi,#1
l\@_1:
.endm

.align 2
regular_func divmod_s64s64_unsafe
 cmp r3,#0
 blt 1f
@ here x +ve
 beq 2f                    @ could x be zero?
3:
 cmp r1,#0
 bge divmod_u64u64_unsafe  @ both positive
@ y -ve, x +ve
 push {r14}
 dneg r0,r1
 bl divmod_u64u64_unsafe
 dneg r0,r1
 dneg r2,r3
 pop {r15}

2:
 cmp r2,#0
 bne 3b                    @ back if x not zero

 cmp r0,#0                 @ y==0?
 bne 4f
 cmp r1,#0
 beq 5f                    @ then pass 0 to __aeabi_ldiv0
4:
 movs r0,#0
 lsrs r1,#31
 lsls r1,#31               @ get sign bit
 bne 5f                    @ y -ve? pass -2^63 to __aeabi_ldiv0
 mvns r0,r0
 lsrs r1,r0,#1             @ y +ve: pass 2^63-1 to __aeabi_ldiv0
5:
 push {r14}
#if PICO_DIVIDER_CALL_LDIV0
 bl __aeabi_ldiv0
#endif
 movs r2,#0                @ and return 0 for the remainder
 movs r3,#0
 pop {r15}

1:
@ here x -ve
 push {r14}
 cmp r1,#0
 blt 1f
@ y +ve, x -ve
 dneg r2,r3
 bl divmod_u64u64_unsafe
 dneg r0,r1
 pop {r15}

1:
@ y -ve, x -ve
 dneg r0,r1
 dneg r2,r3
 bl divmod_u64u64_unsafe
 dneg r2,r3
 pop {r15}

regular_func divmod_u64u64_unsafe
 cmp r1,#0
 bne y64                   @ y fits in 32 bits?
 cmp r3,#0                 @ yes; and x?
 bne 1f
 cmp r2,#0
 beq 2f                    @ x==0?
 mov r12,r7
 ldr r7,=SIO_BASE
 str r0,[r7,#SIO_DIV_UDIVIDEND_OFFSET]
 str r2,[r7,#SIO_DIV_UDIVISOR_OFFSET]
 movs r1,#0
 movs r3,#0
 wait_div 2
 ldr r2,[r7,#SIO_DIV_REMAINDER_OFFSET]
 ldr r0,[r7,#SIO_DIV_QUOTIENT_OFFSET]
 mov r7,r12
 bx r14

2:                         @ divide by 0 with y<2^32
 cmp r0,#0                 @ y==0?
 beq 3f                    @ then pass 0 to __aeabi_ldiv0
udiv0:
 ldr r0,=0xffffffff
 movs r1,r0                @ pass 2^64-1 to __aeabi_ldiv0
3:
 push {r14}
#if PICO_DIVIDER_CALL_LDIV0
 bl __aeabi_ldiv0
#endif
 movs r2,#0                @ and return 0 for the remainder
 movs r3,#0
 pop {r15}

1:
 movs r2,r0                @ x>y, so result is 0 remainder y
 movs r3,r1
 movs r0,#0
 movs r1,#0
 bx r14

.ltorg

@ here y occupies more than 32 bits
@ split into cases acccording to the size of x
y64:
 cmp r3,#0
 beq 1f
 b y64_x48                 @ if x does not fit in 32 bits, go to 48- and 64-bit cases
1:
 lsrs r3,r2,#16
 bne y64_x32               @ jump if x is 17..32 bits

@ here x is at most 16 bits

 cmp r2,#0
 beq udiv0                 @ x==0? exit as with y!=0 case above
 push {r7}
 ldr r7,=SIO_BASE
 str r1,[r7,#SIO_DIV_UDIVIDEND_OFFSET]
 str r2,[r7,#SIO_DIV_UDIVISOR_OFFSET]
 wait_div 4
 push {r4, r5}
 lsrs r4,r0,#16
 ldr r3,[r7,#SIO_DIV_REMAINDER_OFFSET] @ r0=y0-q0*x; 0<=r0<x
 ldr r1,[r7,#SIO_DIV_QUOTIENT_OFFSET]  @ q0=y0/x;
 lsls r3,#16
 orrs r3,r4
 str r3,[r7,#SIO_DIV_UDIVIDEND_OFFSET] @ y1=(r0<<16)+(((ui32)y)>>16);
 str r2,[r7,#SIO_DIV_UDIVISOR_OFFSET]  @ must set divisor again, as we do not save/restore regs at all in IRQs if not dirty
 wait_div 1
 uxth r4,r0
 ldr r3,[r7,#SIO_DIV_REMAINDER_OFFSET] @ r1=y1-q1*x; 0<=r1<x
 ldr r5,[r7,#SIO_DIV_QUOTIENT_OFFSET]  @ q1=y1/x;
 lsls r3,#16
 orrs r3,r4
 str r3,[r7,#SIO_DIV_UDIVIDEND_OFFSET] @ y1=(r0<<16)+(((ui32)y)>>16);
 str r2,[r7,#SIO_DIV_UDIVISOR_OFFSET]  @ must set divisor again, as we do not save/restore regs at all in IRQs if not dirty
 wait_div 3
 movs r3,#0
 lsls r4,r5,#16             @ quotient=(q0<<32)+(q1<<16)+q2
 lsrs r5,#16
 ldr r2,[r7,#SIO_DIV_REMAINDER_OFFSET] @ r2=y2-q2*x; 0<=r2<x
 ldr r0,[r7,#SIO_DIV_QUOTIENT_OFFSET]  @ q2=y2/x;
 adds r0,r4
 adcs r1,r5
 pop {r4,r5,r7}
 bx r14

.ltorg

y64_x32:
@ here x is 17..32 bits
 push {r4-r7,r14}
 mov r12,r2                @ save x
 movs r5,#0                @ xsh=0
 lsrs r4,r2,#24
 bne 1f
 lsls r2,#8                @ if(x0<1U<<24) x0<<=8,xsh =8;
 adds r5,#8
1:
 lsrs r4,r2,#28
 bne 1f
 lsls r2,#4                @ if(x0<1U<<28) x0<<=4,xsh+=4;
 adds r5,#4
1:
 lsrs r4,r2,#30
 bne 1f
 lsls r2,#2                @ if(x0<1U<<30) x0<<=2,xsh+=2;
 adds r5,#2
1:
 lsrs r4,r2,#31
 bne 1f
 lsls r2,#1                @ if(x0<1U<<31) x0<<=1,xsh+=1;
 adds r5,#1
1:
@ now 2^31<=x0<2^32, 0<=xsh<16 (amount x is shifted in x0); number of quotient bits to be calculated qb=xsh+33 33<=qb<49
 lsrs r4,r2,#15
 adds r4,#1                @ x1=(x0>>15)+1; 2^16<x1<=2^17

 ldr r7,=SIO_BASE
 str r4,[r7,#SIO_DIV_UDIVISOR_OFFSET]
 ldr r4,=0xffffffff
 str r4,[r7,#SIO_DIV_UDIVIDEND_OFFSET]
 lsrs r6,r1,#16
 uxth r3,r2                @ x0l
 wait_div 2
 ldr r4,[r7,#SIO_DIV_QUOTIENT_OFFSET]  @ r=0xffffffffU/x1; 2^15<=r<2^16 r is a normalised reciprocal of x, guaranteed not an overestimate

@ here
@ r0:r1 y
@ r2    x0
@ r4    r
@ r5    xsh
@ r12   x

 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>48)*r)>>16;
 lsls r7,r6,#13
 mov r14,r7                @ quh=q0<<13

 muls r3,r6                @ x0l*q
 lsrs r7,r3,#15
 lsls r3,#17               @ r3:r7 is (x0l*q)<<17
 subs r0,r3
 sbcs r1,r7                @ y-=(x0l*q)<<17

 lsrs r3,r2,#16            @ x0h
 muls r3,r6                @ q*x0h
 adds r3,r3
 subs r1,r3                @ y-=(x0h*q)<<17

 lsrs r6,r1,#3
 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>35)*r)>>16;
 add r14,r6                @ quh+=q1

 uxth r3,r2                @ x0l
 muls r3,r6                @ x0l*q
 lsrs r7,r3,#28
 lsls r3,#4                @ r3:r7 is (x0l*q)<<4
 subs r0,r3
 sbcs r1,r7                @ y-=(x0l*q)<<4

 lsrs r3,r2,#16            @ x0h
 muls r3,r6                @ x0h*q
 lsrs r7,r3,#12
 lsls r3,#20               @ r3:r7 is (x0h*q)<<4
 subs r0,r3
 sbcs r1,r7                @ y-=(x0h*q)<<4

 lsrs r6,r0,#22
 lsls r7,r1,#10
 orrs r6,r7                @ y>>22
 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>22)*r)>>16;

 cmp r5,#9
 blt last0                 @ if(xsh<9) goto last0;

@ on this path xsh>=9, which means x<2^23
 lsrs r2,#9                @ x0>>9: this shift loses no bits
@ the remainder y-x0*q is guaranteed less than a very small multiple of the remaining quotient
@ bits (at most 6 bits) times x, and so fits in one word
 muls r2,r6                @ x0*q
 subs r0,r2                @ y-x0*q
 lsls r7,r6,#13            @ qul=q<<13
1:
 lsrs r6,r0,#9
 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>9)*r)>>16;

@ here
@ r0 y
@ r2 x0>>9
@ r5 xsh
@ r6 q
@ r7 qul
@ r12 x
@ r14 quh

 movs r3,#22
 subs r3,r5                @ 22-xsh
 lsrs r6,r3                @ q>>=22-xsh
 lsrs r7,r3                @ qul>>=22-xsh
 adds r7,r6                @ qul+=q
 mov r4,r12
 muls r6,r4                @ x*q
 subs r2,r0,r6             @ y-=x*q
 mov r0,r14                @ quh
 adds r5,#4                @ xsh+4
 adds r3,#6                @ 28-xsh
 movs r1,r0
 lsrs r1,r3
 lsls r0,r5                @ r0:r1 is quh<<(4+xsh)
 adds r0,r7
 bcc 1f
2:
 adds r1,#1
1:                         @ qu=((ui64)quh<<(4+xsh))+qul
 cmp r2,r4
 bhs 3f
 movs r3,#0
 pop {r4-r7,r15}

.ltorg

3:
 subs r2,r4
 adds r0,#1
 bcc 1b
 b 2b                      @ while(y>=x) y-=x,qu++;

@ here:
@ r0:r1 y
@ r2 x0
@ r4 r
@ r5 xsh; xsh<9
@ r6 q

last0:
 movs r7,#9
 subs r7,r5                @ 9-xsh
 lsrs r6,r7
 mov r4,r12                @ x
 uxth r2,r4
 muls r2,r6                @ q*xlo
 subs r0,r2
 bcs 1f
 subs r1,#1                @ y-=q*xlo
1:
 lsrs r2,r4,#16            @ xhi
 muls r2,r6                @ q*xhi
 lsrs r3,r2,#16
 lsls r2,#16
 subs r2,r0,r2
 sbcs r1,r3                @ y-q*xhi
 movs r3,r1                @ y now in r2:r3
 mov r0,r14                @ quh
 adds r5,#4                @ xsh+4
 adds r7,#19               @ 28-xsh
 movs r1,r0
 lsrs r1,r7
 lsls r0,r5                @ r0:r1 is quh<<(4+xsh)
 adds r0,r6
 bcc 1f
 adds r1,#1                @ quh<<(xsh+4))+q
1:
 cmp r3,#0                 @ y>=2^32?
 bne 3f
 cmp r2,r4                 @ y>=x?
 bhs 4f
 pop {r4-r7,r15}

3:
 adds r0,#1                @ qu++
 bcc 2f
 adds r1,#1
2:
 subs r2,r4                @ y-=x
 bcs 3b
 subs r3,#1
 bne 3b

1:
 cmp r2,r4
 bhs 4f
 pop {r4-r7,r15}

4:
 adds r0,#1                @ qu++
 bcc 2f
 adds r1,#1
2:
 subs r2,r4                @ y-=x
 b 1b

y64_x48:
@ here x is 33..64 bits
 push {r4-r7,r14}          @ save a copy of x
 lsrs r4,r3,#16
 beq 1f
 b y64_x64                 @ jump if x is 49..64 bits
1:
 push {r2-r3}              @ save a copy of x
@ here x is 33..48 bits
 movs r5,#0                @ xsh=0
 lsrs r4,r3,#8
 bne 1f
 lsls r3,#8
 lsrs r6,r2,#24
 orrs r3,r6
 lsls r2,#8                @ if(x0<1U<<40) x0<<=8,xsh =8;
 adds r5,#8
1:
 lsrs r4,r3,#12
 bne 1f
 lsls r3,#4
 lsrs r6,r2,#28
 orrs r3,r6
 lsls r2,#4                @ if(x0<1U<<44) x0<<=4,xsh+=4;
 adds r5,#4
1:
 lsrs r4,r3,#14
 bne 1f
 lsls r3,#2
 lsrs r6,r2,#30
 orrs r3,r6
 lsls r2,#2                @ if(x0<1U<<46) x0<<=2,xsh+=2;
 adds r5,#2
1:
 lsrs r4,r3,#15
 bne 1f
 adds r2,r2
 adcs r3,r3                @ if(x0<1U<<47) x0<<=1,xsh+=1;
 adds r5,#1
1:
@ now 2^47<=x0<2^48, 0<=xsh<16 (amount x is shifted in x0); number of quotient bits to be calculated qb=xsh+17 17<=qb<33
 movs r4,r3
 adds r7,r2,r2
 adcs r4,r4
 adds r4,#1                @ x1=(ui32)(x0>>31)+1; // 2^16<x1<=2^17

 ldr r7,=SIO_BASE
 str r4,[r7,#SIO_DIV_UDIVISOR_OFFSET]
 ldr r4,=0xffffffff
 str r4,[r7,#SIO_DIV_UDIVIDEND_OFFSET]
 lsrs r6,r1,#16
 wait_div 1
 ldr r4,[r7,#SIO_DIV_QUOTIENT_OFFSET]  @ r=0xffffffffU/x1; 2^15<=r<2^16 r is a normalised reciprocal of x, guaranteed not an overestimate

@ here
@ r0:r1 y
@ r2:r3 x0
@ r4    r
@ r5    xsh 0<=xsh<16

 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>48)*r)>>16;
 lsls r7,r6,#13
 mov r14,r7                @ save q<<13
 uxth r7,r2                @ x0l
 muls r7,r6
 subs r0,r7
 bcs 1f
 subs r1,#1
1:
 subs r0,r7
 bcs 1f
 subs r1,#1
1:
 uxth r7,r3                @ x0h
 muls r7,r6
 subs r1,r7
 subs r1,r7
 lsrs r7,r2,#16            @ x0m
 muls r7,r6
 lsls r6,r7,#17
 lsrs r7,#15
 subs r0,r6
 sbcs r1,r7                @ y-=((ui64)q*x0)<<1;

 lsrs r6,r1,#3             @ y>>35
 muls r6,r4
 lsrs r6,#16               @ q=((ui32)(y>>35)*r)>>16;

 cmp r5,#12
 blt last1                 @ if(xsh<12) goto last1;

 add r14,r6                @ qu<<13+q
 lsrs r2,#12
 lsls r7,r3,#20
 orrs r2,r7
 lsrs r3,#12               @ x0>>12

 uxth r7,r2                @ x0l
 muls r7,r6
 subs r0,r7
 bcs 1f
 subs r1,#1
1:
 uxth r7,r3                @ x0h
 muls r7,r6
 subs r1,r7
 lsrs r7,r2,#16            @ x0m
 muls r7,r6
 lsls r6,r7,#16
 lsrs r7,#16
 subs r0,r6
 sbcs r1,r7                @ y-=((ui64)q*x0)>>12

 lsrs r6,r0,#22
 lsls r7,r1,#10
 orrs r6,r7                @ y>>22
 muls r6,r4
 movs r7,#41
 subs r7,r5
 lsrs r6,r7                @ q=((ui32)(y>>22)*r)>>(16+25-xsh)

 subs r5,#12
 mov r7,r14
 lsls r7,r5
2:
 adds r7,r6                @ qu=(qu<<(xsh-12))+q
 pop {r4,r5}               @ recall x

@ here
@ r0:r1 y
@ r4:r5 x
@ r6 q
@ r7 qu

 uxth r2,r4
 uxth r3,r5
 muls r2,r6                @ xlo*q
 muls r3,r6                @ xhi*q
 subs r0,r2
 sbcs r1,r3
 lsrs r2,r4,#16
 muls r2,r6
 lsrs r3,r2,#16
 lsls r2,#16               @ xm*q
 subs r0,r2
 sbcs r1,r3                @ y-=(ui64)q*x

1:
 movs r2,r0
 movs r3,r1
 adds r7,#1
 subs r0,r4
 sbcs r1,r5                @ while(y>=x) y-=x,qu++;
 bhs 1b
 subs r0,r7,#1             @ correction to qu
 movs r1,#0
 pop {r4-r7,r15}

last1:
@ r0:r1 y
@ r2:r3 x0
@ r5 xsh
@ r6 q

 movs r7,#12
 subs r7,r5
 lsrs r6,r7                @ q>>=12-xsh
 mov r7,r14
 lsrs r7,#13
 lsls r7,r5
 adds r7,r7                @ qu<<(xsh+1)
 b 2b

y64_x64:
@ here x is 49..64 bits
 movs r4,#0                @ q=0 if x>>32==0xffffffff
 adds r5,r3,#1
 beq 1f

 ldr r7,=SIO_BASE
 str r5,[r7,#SIO_DIV_UDIVISOR_OFFSET]
 str r1,[r7,#SIO_DIV_UDIVIDEND_OFFSET]
 wait_div 0
 ldr r4,[r7,#SIO_DIV_QUOTIENT_OFFSET] @ q=(ui32)(y>>32)/((x>>32)+1)
1:
 uxth r5,r2
 uxth r6,r3
 muls r5,r4
 muls r6,r4
 subs r0,r5
 sbcs r1,r6
 lsrs r5,r2,#16
 lsrs r6,r3,#16
 muls r5,r4
 muls r6,r4
 lsls r6,#16
 lsrs r7,r5,#16
 orrs r6,r7
 lsls r5,#16
 subs r0,r5
 sbcs r1,r6                @   y-=(ui64)q*x

 cmp r1,r3                 @   while(y>=x) y-=x,q++
 bhs 1f
3:
 movs r2,r0
 movs r3,r1
 movs r0,r4
 movs r1,#0
 pop {r4-r7,r15}

1:
 bne 2f
 cmp r0,r2
 blo 3b
2:
 subs r0,r2
 sbcs r1,r3
 adds r4,#1
 cmp r1,r3
 blo 3b
 b 1b

div_section divmod_s64s64_rem
regular_func divmod_s64s64_rem
    push {r4, lr}
    bl divmod_s64s64
    ldr r4, [sp, #8]
    stmia r4!, {r2,r3}
    pop {r4, pc}

div_section divmod_u64u64_rem
regular_func divmod_u64u64_rem
    push {r4, lr}
    bl divmod_u64u64
    ldr r4, [sp, #8]
    stmia r4!, {r2,r3}
    pop {r4, pc}
