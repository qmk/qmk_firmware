/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/asm_helper.S"
#include "pico/bootrom/sf_table.h"
#include "hardware/divider_helper.S"

__pre_init __aeabi_float_init, 00020

.syntax unified
.cpu cortex-m0plus
.thumb

.macro float_section name
#if PICO_FLOAT_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

.macro float_wrapper_section func
float_section WRAPPER_FUNC_NAME(\func)
.endm

.macro _float_wrapper_func x
    wrapper_func \x
.endm

.macro wrapper_func_f1 x
   _float_wrapper_func \x
#if PICO_FLOAT_PROPAGATE_NANS
    mov ip, lr
    bl __check_nan_f1
    mov lr, ip
#endif
.endm

.macro wrapper_func_f2 x
   _float_wrapper_func \x
#if PICO_FLOAT_PROPAGATE_NANS
    mov ip, lr
    bl __check_nan_f2
    mov lr, ip
#endif
.endm

.section .text

#if PICO_FLOAT_PROPAGATE_NANS
.thumb_func
__check_nan_f1:
   movs r3, #1
   lsls r3, #24
   lsls r2, r0, #1
   adds r2, r3
   bhi 1f
   bx lr
1:
   bx ip

.thumb_func
__check_nan_f2:
   movs r3, #1
   lsls r3, #24
   lsls r2, r0, #1
   adds r2, r3
   bhi 1f
   lsls r2, r1, #1
   adds r2, r3
   bhi 2f
   bx lr
2:
   mov r0, r1
1:
   bx ip
#endif

.macro table_tail_call SF_TABLE_OFFSET
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
#ifndef NDEBUG
    movs r3, #0
    mov ip, r3
#endif
#endif
    ldr r3, =sf_table
    ldr r3, [r3, #\SF_TABLE_OFFSET]
    bx r3
.endm

.macro shimmable_table_tail_call SF_TABLE_OFFSET shim
    ldr r3, =sf_table
    ldr r3, [r3, #\SF_TABLE_OFFSET]
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    mov ip, pc
#endif
    bx r3
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
.byte \SF_TABLE_OFFSET, 0xdf
.word \shim
#endif
.endm


// note generally each function is in a separate section unless there is fall thru or branching between them
// note fadd, fsub, fmul, fdiv are so tiny and just defer to rom so are lumped together so they can share constant pool

// note functions are word aligned except where they are an odd number of linear instructions

// float FUNC_NAME(__aeabi_fadd)(float, float)         single-precision addition
float_wrapper_section __aeabi_farithmetic
// float FUNC_NAME(__aeabi_frsub)(float x, float y)    single-precision reverse subtraction, y - x

// frsub first because it is the only one that needs alignment
.align 2
wrapper_func __aeabi_frsub
    eors r0, r1
    eors r1, r0
    eors r0, r1
    // fall thru

// float FUNC_NAME(__aeabi_fsub)(float x, float y)     single-precision subtraction, x - y
wrapper_func_f2 __aeabi_fsub
#if PICO_FLOAT_PROPAGATE_NANS
    // we want to return nan for inf-inf or -inf - -inf, but without too much upfront cost
    mov r2, r0
    eors r2, r1
    bmi 1f // different signs
    push {r0, r1, lr}
    bl 1f
    b fdiv_fsub_nan_helper
1:
#endif
    table_tail_call SF_TABLE_FSUB

wrapper_func_f2 __aeabi_fadd
    table_tail_call SF_TABLE_FADD

// float FUNC_NAME(__aeabi_fdiv)(float n, float d)     single-precision division, n / d
wrapper_func_f2 __aeabi_fdiv
#if PICO_FLOAT_PROPAGATE_NANS
    push {r0, r1, lr}
    bl 1f
    b fdiv_fsub_nan_helper
1:
#endif
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    ldr r2, =(SIO_BASE)
    ldr r3, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r3, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs fdiv_save_state
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl fdiv_shim_call
    msr PRIMASK, r4
    pop {r4, pc}
#endif
fdiv_shim_call:
    table_tail_call SF_TABLE_FDIV
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
fdiv_save_state:
    save_div_state_and_lr
    bl fdiv_shim_call
    ldr r2, =(SIO_BASE)
    restore_div_state_and_return
#endif

fdiv_fsub_nan_helper:
#if PICO_FLOAT_PROPAGATE_NANS
    pop {r1, r2}

    // check for infinite op infinite (or rather check for infinite result with both
    // operands being infinite)
    lsls r3, r0, #1
    asrs r3, r3, #24
    adds r3, #1
    beq 2f
    pop {pc}
2:
    lsls r1, #1
    asrs r1, r1, #24
    lsls r2, #1
    asrs r2, r2, #24
    ands r1, r2
    adds r1, #1
    bne 3f
    // infinite to nan
    movs r1, #1
    lsls r1, #22
    orrs r0, r1
3:
    pop {pc}
#endif

// float FUNC_NAME(__aeabi_fmul)(float, float)         single-precision multiplication
wrapper_func_f2 __aeabi_fmul
#if PICO_FLOAT_PROPAGATE_NANS
    push {r0, r1, lr}
    bl 1f
    pop {r1, r2}

    // check for multiplication of infinite by zero (or rather check for infinite result with either
    // operand 0)
    lsls r3, r0, #1
    asrs r3, r3, #24
    adds r3, #1
    beq 2f
    pop {pc}
2:
    ands r1, r2
    bne 3f
    // infinite to nan
    movs r1, #1
    lsls r1, #22
    orrs r0, r1
3:
    pop {pc}
1:
#endif
    table_tail_call SF_TABLE_FMUL

// void FUNC_NAME(__aeabi_cfrcmple)(float, float)         reversed 3-way (<, =, ?>) compare [1], result in PSR ZC flags
float_wrapper_section __aeabi_cfcmple
.align 2
wrapper_func __aeabi_cfrcmple
    push {r0-r2, lr}
    eors r0, r1
    eors r1, r0
    eors r0, r1
    b __aeabi_cfcmple_guts

// NOTE these share an implementation as we have no excepting NaNs.
// void FUNC_NAME(__aeabi_cfcmple)(float, float)         3-way (<, =, ?>) compare [1], result in PSR ZC flags
// void FUNC_NAME(__aeabi_cfcmpeq)(float, float)         non-excepting equality comparison [1], result in PSR ZC flags
.align 2
wrapper_func __aeabi_cfcmple
wrapper_func __aeabi_cfcmpeq
    push {r0-r2, lr}

__aeabi_cfcmple_guts:
    lsls r2,r0,#1
    lsrs r2,#24
    beq 1f
    cmp r2,#0xff
    bne 2f
    lsls r2, r0, #9
    bhi 3f
1:
    lsrs r0,#23     @ clear mantissa if denormal or infinite
    lsls r0,#23
2:
    lsls r2,r1,#1
    lsrs r2,#24
    beq 1f
    cmp r2,#0xff
    bne 2f
    lsls r2, r1, #9
    bhi 3f
1:
    lsrs r1,#23     @ clear mantissa if denormal or infinite
    lsls r1,#23
2:
    movs r2,#1      @ initialise result
    eors r1,r0
    bmi 2f          @ opposite signs? then can proceed on basis of sign of x
    eors r1,r0      @ restore y
    bpl 1f
    cmp r1,r0
    pop {r0-r2, pc}
1:
    cmp r0,r1
    pop {r0-r2, pc}
2:
    orrs r1, r0     @ handle 0/-0
    adds r1, r1     @ note this always sets C
    beq 3f
    mvns r0, r0     @ carry inverse of r0 sign
    adds r0, r0
3:
    pop {r0-r2, pc}


// int FUNC_NAME(__aeabi_fcmpeq)(float, float)         result (1, 0) denotes (=, ?<>) [2], use for C == and !=
float_wrapper_section __aeabi_fcmpeq
.align 2
wrapper_func __aeabi_fcmpeq
    push {lr}
    bl __aeabi_cfcmpeq
    beq 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_fcmplt)(float, float)         result (1, 0) denotes (<, ?>=) [2], use for C <
float_wrapper_section __aeabi_fcmplt
.align 2
wrapper_func __aeabi_fcmplt
    push {lr}
    bl __aeabi_cfcmple
    sbcs r0, r0
    pop {pc}

// int FUNC_NAME(__aeabi_fcmple)(float, float)         result (1, 0) denotes (<=, ?>) [2], use for C <=
float_wrapper_section __aeabi_fcmple
.align 2
wrapper_func __aeabi_fcmple
    push {lr}
    bl __aeabi_cfcmple
    bls 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_fcmpge)(float, float)         result (1, 0) denotes (>=, ?<) [2], use for C >=
float_wrapper_section __aeabi_fcmpge
.align 2
wrapper_func __aeabi_fcmpge
    push {lr}
    // because of NaNs it is better to reverse the args than the result
    bl __aeabi_cfrcmple
    bls 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_fcmpgt)(float, float)         result (1, 0) denotes (>, ?<=) [2], use for C >
float_wrapper_section __aeabi_fcmpgt
wrapper_func __aeabi_fcmpgt
    push {lr}
    // because of NaNs it is better to reverse the args than the result
    bl __aeabi_cfrcmple
    sbcs r0, r0
    pop {pc}

// int FUNC_NAME(__aeabi_fcmpun)(float, float)         result (1, 0) denotes (?, <=>) [2], use for C99 isunordered()
float_wrapper_section __aeabi_fcmpun
wrapper_func __aeabi_fcmpun
   movs r3, #1
   lsls r3, #24
   lsls r2, r0, #1
   adds r2, r3
   bhi 1f
   lsls r2, r1, #1
   adds r2, r3
   bhi 1f
   movs r0, #0
   bx lr
1:
   movs r0, #1
   bx lr


// float FUNC_NAME(__aeabi_ui2f)(unsigned)             unsigned to float (single precision) conversion
float_wrapper_section __aeabi_ui2f
wrapper_func __aeabi_ui2f
        subs r1, r1
        cmp r0, #0
        bne __aeabi_i2f_main
        mov r0, r1
        bx lr

float_wrapper_section __aeabi_i2f
// float FUNC_NAME(__aeabi_i2f)(int)                     integer to float (single precision) conversion
wrapper_func __aeabi_i2f
        lsrs r1, r0, #31
        lsls r1, #31
        bpl 1f
        negs r0, r0
1:
        cmp r0, #0
        beq 7f
__aeabi_i2f_main:

        mov ip, lr
        push {r0, r1}
        ldr r3, =sf_clz_func
        ldr r3, [r3]
        blx r3
        pop {r1, r2}
        lsls r1, r0
        subs r0, #158
        negs r0, r0

        adds r1,#0x80  @ rounding
        bcs 5f         @ tripped carry? then have leading 1 in C as required (and result is even so can ignore sticky bits)

        lsls r3,r1,#24 @ check bottom 8 bits of r1
        beq 6f         @ in rounding-tie case?
        lsls r1,#1     @ remove leading 1
3:
        lsrs r1,#9     @ align mantissa
        lsls r0,#23    @ align exponent
        orrs r0,r2     @ assemble exponent and mantissa
4:
        orrs r0,r1     @ apply sign
1:
        bx ip
5:
        adds r0,#1     @ correct exponent offset
        b 3b
6:
        lsrs r1,#9     @ ensure even result
        lsls r1,#10
        b 3b
7:
        bx lr


// int FUNC_NAME(__aeabi_f2iz)(float)                     float (single precision) to integer C-style conversion [3]
float_wrapper_section __aeabi_f2iz
wrapper_func __aeabi_f2iz
regular_func float2int_z
    lsls r1, r0, #1
    lsrs r2, r1, #24
    movs r3, #0x80
    lsls r3, #24
    cmp r2, #126
    ble 1f
    subs r2, #158
    bge 2f
    asrs r1, r0, #31
    lsls r0, #9
    lsrs r0, #1
    orrs r0, r3
    negs r2, r2
    lsrs r0, r2
    lsls r1, #1
    adds r1, #1
    muls r0, r1
    bx lr
1:
    movs r0, #0
    bx lr
2:
    lsrs r0, #31
    adds r0, r3
    subs r0, #1
    bx lr

    cmn r0, r0
    bcc float2int
    push {lr}
    lsls r0, #1
    lsrs r0, #1
    movs r1, #0
    bl __aeabi_f2uiz
    cmp r0, #0
    bmi 1f
    negs r0, r0
    pop {pc}
1:
    movs r0, #128
    lsls r0, #24
    pop {pc}

float_section float2int
regular_func float2int
    shimmable_table_tail_call SF_TABLE_FLOAT2INT float2int_shim

float_section float2fix
regular_func float2fix
    shimmable_table_tail_call SF_TABLE_FLOAT2FIX float2fix_shim

float_section float2ufix
regular_func float2ufix
    table_tail_call SF_TABLE_FLOAT2UFIX

// unsigned FUNC_NAME(__aeabi_f2uiz)(float)             float (single precision) to unsigned C-style conversion [3]
float_wrapper_section __aeabi_f2uiz
wrapper_func __aeabi_f2uiz
    table_tail_call SF_TABLE_FLOAT2UINT

float_section fix2float
regular_func fix2float
    table_tail_call SF_TABLE_FIX2FLOAT

float_section ufix2float
regular_func ufix2float
    table_tail_call SF_TABLE_UFIX2FLOAT

float_section fix642float
regular_func fix642float
    shimmable_table_tail_call SF_TABLE_FIX642FLOAT fix642float_shim

float_section ufix642float
regular_func ufix642float
    shimmable_table_tail_call SF_TABLE_UFIX642FLOAT ufix642float_shim

// float FUNC_NAME(__aeabi_l2f)(long long)             long long to float (single precision) conversion
float_wrapper_section __aeabi_l2f
1:
    ldr r2, =__aeabi_i2f
    bx r2
wrapper_func __aeabi_l2f
    asrs r2, r0, #31
    cmp r1, r2
    beq 1b
    shimmable_table_tail_call SF_TABLE_INT642FLOAT int642float_shim

// float FUNC_NAME(__aeabi_l2f)(long long)             long long to float (single precision) conversion
float_wrapper_section __aeabi_ul2f
1:
    ldr r2, =__aeabi_ui2f
    bx r2
wrapper_func __aeabi_ul2f
    cmp r1, #0
    beq 1b
    shimmable_table_tail_call SF_TABLE_UINT642FLOAT uint642float_shim

// long long FUNC_NAME(__aeabi_f2lz)(float)             float (single precision) to long long C-style conversion [3]
float_wrapper_section __aeabi_f2lz
wrapper_func __aeabi_f2lz
regular_func float2int64_z
    cmn r0, r0
    bcc float2int64
    push {lr}
    lsls r0, #1
    lsrs r0, #1
    movs r1, #0
    bl float2ufix64
    cmp r1, #0
    bmi 1f
    movs r2, #0
    negs r0, r0
    sbcs r2, r1
    mov r1, r2
    pop {pc}
1:
    movs r1, #128
    lsls r1, #24
    movs r0, #0
    pop {pc}

float_section float2int64
regular_func float2int64
    shimmable_table_tail_call SF_TABLE_FLOAT2INT64 float2int64_shim

float_section float2fix64
regular_func float2fix64
    shimmable_table_tail_call SF_TABLE_FLOAT2FIX64 float2fix64_shim

// unsigned long long FUNC_NAME(__aeabi_f2ulz)(float)     float to unsigned long long C-style conversion [3]
float_wrapper_section __aeabi_f2ulz
wrapper_func __aeabi_f2ulz
    shimmable_table_tail_call SF_TABLE_FLOAT2UINT64 float2uint64_shim

float_section float2ufix64
regular_func float2ufix64
    shimmable_table_tail_call SF_TABLE_FLOAT2UFIX64 float2ufix64_shim

float_wrapper_section __aeabi_f2d
1:
#if PICO_FLOAT_PROPAGATE_NANS
    // copy sign bit and 25 NAN id bits into sign bit and significant ID bits, also setting the high id bit
    asrs r1, r0, #3
    movs r2, #0xf
    lsls r2, #27
    orrs r1, r2
    lsls r0, #25
    bx lr
#endif
wrapper_func __aeabi_f2d
#if PICO_FLOAT_PROPAGATE_NANS
    movs r3, #1
    lsls r3, #24
    lsls r2, r0, #1
    adds r2, r3
    bhi 1b
#endif
    shimmable_table_tail_call SF_TABLE_FLOAT2DOUBLE float2double_shim

float_wrapper_section sqrtf
wrapper_func_f1 sqrtf
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    // check for negative
    asrs r1, r0, #23
    bmi 1f
#endif
    table_tail_call SF_TABLE_FSQRT
#if PICO_FLOAT_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
1:
    mvns r0, r1
    cmp r0, #255
    bne 2f
    // -0 or -Denormal return -0 (0x80000000)
    lsls r0, #31
    bx lr
2:
    // return -Inf (0xff800000)
    asrs r0, r1, #31
    lsls r0, #23
    bx lr
#endif

float_wrapper_section cosf
// note we don't use _f1 since we do an infinity/nan check for outside of range
wrapper_func cosf
    // rom version only works for -128 < angle < 128
    lsls r1, r0, #1
    lsrs r1, #24
    cmp r1, #127 + 7
    bge 1f
2:
    table_tail_call SF_TABLE_FCOS
1:
#if PICO_FLOAT_PROPAGATE_NANS
    // also check for infinites
    cmp r1, #255
    bne 3f
    // infinite to nan
    movs r1, #1
    lsls r1, #22
    orrs r0, r1
    bx lr
3:
#endif
    ldr r1, =0x40c90fdb // 2 * M_PI
    push {lr}
    bl remainderf
    pop {r1}
    mov lr, r1
    b 2b

float_wrapper_section sinf
// note we don't use _f1 since we do an infinity/nan check for outside of range
wrapper_func sinf
    // rom version only works for -128 < angle < 128
    lsls r1, r0, #1
    lsrs r1, #24
    cmp r1, #127 + 7
    bge 1f
2:
    table_tail_call SF_TABLE_FSIN
1:
#if PICO_FLOAT_PROPAGATE_NANS
    // also check for infinites
    cmp r1, #255
    bne 3f
    // infinite to nan
    movs r1, #1
    lsls r1, #22
    orrs r0, r1
    bx lr
3:
#endif
    ldr r1, =0x40c90fdb // 2 * M_PI
    push {lr}
    bl remainderf
    pop {r1}
    mov lr, r1
    b 2b

float_wrapper_section sincosf
// note we don't use _f1 since we do an infinity/nan check for outside of range
wrapper_func sincosf
    push {r1, r2, lr}
    // rom version only works for -128 < angle < 128
    lsls r3, r0, #1
    lsrs r3, #24
    cmp r3, #127 + 7
    bge 3f
2:
    ldr r3, =sf_table
    ldr r3, [r3, #SF_TABLE_FSIN]
    blx r3
    pop {r2, r3}
    str r0, [r2]
    str r1, [r3]
    pop {pc}
#if PICO_FLOAT_PROPAGATE_NANS
.align 2
    pop {pc}
#endif
3:
#if PICO_FLOAT_PROPAGATE_NANS
    // also check for infinites
    cmp r3, #255
    bne 4f
    // infinite to nan
    movs r3, #1
    lsls r3, #22
    orrs r0, r3
    str r0, [r1]
    str r0, [r2]
    add sp, #12
    bx lr
4:
#endif
    ldr r1, =0x40c90fdb // 2 * M_PI
    push {lr}
    bl remainderf
    pop {r1}
    mov lr, r1
    b 2b

float_wrapper_section tanf
// note we don't use _f1 since we do an infinity/nan check for outside of range
wrapper_func tanf
    // rom version only works for -128 < angle < 128
    lsls r1, r0, #1
    lsrs r1, #24
    cmp r1, #127 + 7
    bge ftan_out_of_range
ftan_in_range:
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    ldr r2, =(SIO_BASE)
    ldr r3, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r3, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs ftan_save_state
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl ftan_shim_call
    msr PRIMASK, r4
    pop {r4, pc}
#endif
ftan_shim_call:
    table_tail_call SF_TABLE_FTAN
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
ftan_save_state:
    save_div_state_and_lr
    bl ftan_shim_call
    ldr r2, =(SIO_BASE)
    restore_div_state_and_return
#endif
ftan_out_of_range:
#if PICO_FLOAT_PROPAGATE_NANS
    // also check for infinites
    cmp r1, #255
    bne 3f
    // infinite to nan
    movs r1, #1
    lsls r1, #22
    orrs r0, r1
    bx lr
3:
#endif
    ldr r1, =0x40c90fdb // 2 * M_PI
    push {lr}
    bl remainderf
    pop {r1}
    mov lr, r1
    b ftan_in_range

float_wrapper_section atan2f
wrapper_func_f2 atan2f
    shimmable_table_tail_call SF_TABLE_FATAN2 fatan2_shim

float_wrapper_section expf
wrapper_func_f1 expf
    table_tail_call SF_TABLE_FEXP

float_wrapper_section logf
wrapper_func_f1 logf
    table_tail_call SF_TABLE_FLN
