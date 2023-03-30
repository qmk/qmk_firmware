/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"

#if SIO_DIV_CSR_READY_LSB == 0
.equ SIO_DIV_CSR_READY_SHIFT_FOR_CARRY, 1
#else
need to change SHIFT above
#endif
#if SIO_DIV_CSR_DIRTY_LSB == 1
.equ SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY, 2
#else
need to change SHIFT above
#endif

// SIO_BASE ptr in r2; pushes r4-r7, lr to stack
.macro save_div_state_and_lr
// originally we did this, however a) it uses r3, and b) the push and dividend/divisor
// readout takes 8 cycles, c) any IRQ which uses the divider will necessarily put the
// data back, which will immediately make it ready
//
//    // ldr r3, [r2, #SIO_DIV_CSR_OFFSET]
//    // // wait for results as we can't save signed-ness of operation
//    // 1:
//    //     lsrs r3, #SIO_DIV_CSR_READY_SHIFT_FOR_CARRY
//    //     bcc 1b

// 6 cycle push + 2 ldr ensures the 8 cycle delay before remainder and quotient are ready
push {r4, r5, r6, r7, lr}
// note we must read quotient last, and since it isn't the last reg, we'll not use ldmia!
ldr r4, [r2, #SIO_DIV_UDIVIDEND_OFFSET]
ldr r5, [r2, #SIO_DIV_UDIVISOR_OFFSET]
ldr r7, [r2, #SIO_DIV_REMAINDER_OFFSET]
ldr r6, [r2, #SIO_DIV_QUOTIENT_OFFSET]
.endm

// restores divider state from r4-r7, then pops them and pc
.macro restore_div_state_and_return
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

// note we are not use STM not because it can be restarted due to interrupt which is harmless, more because this is 1 cycle IO space
//      and so 4 reads is cheaper (and we don't have to adjust r2)
// note also, that we must restore via UDIVI* rather than SDIVI* to prevent the quotient/remainder being negated on read based
//      on the signs of the inputs
str r4, [r2, #SIO_DIV_UDIVIDEND_OFFSET]
str r5, [r2, #SIO_DIV_UDIVISOR_OFFSET]
str r7, [r2, #SIO_DIV_REMAINDER_OFFSET]
str r6, [r2, #SIO_DIV_QUOTIENT_OFFSET]
pop {r4, r5, r6, r7, pc}
.endm