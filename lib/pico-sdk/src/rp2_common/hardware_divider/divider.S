#include "pico/asm_helper.S"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"

.syntax unified
.cpu cortex-m0plus
.thumb

// tag::hw_div_s32[]
regular_func_with_section hw_divider_divmod_s32
    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_SDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_SDIVISOR_OFFSET]
    b hw_divider_divmod_return
// end::hw_div_s32[]

// tag::hw_div_u32[]
regular_func_with_section hw_divider_divmod_u32
    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_UDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_UDIVISOR_OFFSET]
    b hw_divider_divmod_return
// end::hw_div_u32[]

// Common delay and return section for s32 and u32
.section .text.hw_divider_divmod_return
hw_divider_divmod_return:
    // Branching here is 2 cycles, delay another 6
    b 1f
1:  b 1f
1:  b 1f
1:  // return 64 bit value so we can efficiently return both (note quotient must be read last)
    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr

regular_func_with_section hw_divider_save_state
    ldr r3, =SIO_BASE
    ldr r1, [r3, #SIO_DIV_UDIVIDEND_OFFSET]
    ldr r2, [r3, #SIO_DIV_UDIVISOR_OFFSET]
    stmia r0!, {r1-r2}
    // The 8 cycles needed to guarantee that the result is ready is ensured by the preceeding
    // code of 7 cycles together with any branch to it taking at least 2 cycles.
    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r2, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    stmia r0!, {r1-r2}
    bx lr

regular_func_with_section hw_divider_restore_state
    ldr r3, =SIO_BASE
    ldmia r0!, {r1-r2}
    str r1, [r3, #SIO_DIV_UDIVIDEND_OFFSET]
    str r2, [r3, #SIO_DIV_UDIVISOR_OFFSET]
    ldmia r0!, {r1-r2}
    str r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    str r2, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr
