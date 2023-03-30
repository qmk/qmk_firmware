/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/asm_helper.S"
#include "pico/bootrom/sf_table.h"
#include "hardware/divider_helper.S"

__pre_init __aeabi_double_init, 00020

.syntax unified
.cpu cortex-m0plus
.thumb

.macro double_section name
#if PICO_DOUBLE_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

.macro _double_wrapper_func x
    wrapper_func \x
.endm

.macro wrapper_func_d1 x
   _double_wrapper_func \x
#if PICO_DOUBLE_PROPAGATE_NANS
    mov ip, lr
    bl __check_nan_d1
    mov lr, ip
#endif
.endm

.macro wrapper_func_d2 x
    _double_wrapper_func \x
#if PICO_DOUBLE_PROPAGATE_NANS
    mov ip, lr
    bl __check_nan_d2
    mov lr, ip
#endif
.endm

.section .text

#if PICO_DOUBLE_PROPAGATE_NANS
.thumb_func
__check_nan_d1:
   movs r3, #1
   lsls r3, #21
   lsls r2, r1, #1
   adds r2, r3
   bhi 1f
   bx lr
1:
   bx ip

.thumb_func
__check_nan_d2:
   push {r0, r2}
   movs r2, #1
   lsls r2, #21
   lsls r0, r1, #1
   adds r0, r2
   bhi 1f
   lsls r0, r3, #1
   adds r0, r2
   bhi 2f
   pop {r0, r2}
   bx lr
2:
   pop {r0, r2}
   mov r0, r2
   mov r1, r3
   bx ip
1:
   pop {r0, r2}
   bx ip
#endif

.macro table_tail_call SF_TABLE_OFFSET
    push {r3, r4}
#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
#ifndef NDEBUG
    movs r3, #0
    mov ip, r3
#endif
#endif
    ldr r3, =sd_table
    ldr r3, [r3, #\SF_TABLE_OFFSET]
    str r3, [sp, #4]
    pop {r3, pc}
.endm

.macro shimmable_table_tail_call SF_TABLE_OFFSET shim
    push {r3, r4}
    ldr r3, =sd_table
    ldr r3, [r3, #\SF_TABLE_OFFSET]
#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    mov ip, pc
#endif
    str r3, [sp, #4]
    pop {r3, pc}
#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
.byte \SF_TABLE_OFFSET, 0xdf
.word \shim
#endif
.endm

.macro double_wrapper_section func
double_section WRAPPER_FUNC_NAME(\func)
.endm

double_section push_r8_r11
regular_func push_r8_r11
 mov r4,r8
 mov r5,r9
 mov r6,r10
 mov r7,r11
 push {r4-r7}
 bx r14

double_section pop_r8_r11
regular_func pop_r8_r11
 pop {r4-r7}
 mov r8,r4
 mov r9,r5
 mov r10,r6
 mov r11,r7
 bx r14

// note generally each function is in a separate section unless there is fall thru or branching between them
// note fadd, fsub, fmul, fdiv are so tiny and just defer to rom so are lumped together so they can share constant pool

// note functions are word aligned except where they are an odd number of linear instructions

// double FUNC_NAME(__aeabi_dadd)(double, double)         double-precision addition
double_wrapper_section __aeabi_darithmetic
// double FUNC_NAME(__aeabi_drsub)(double x, double y)    double-precision reverse subtraction, y - x

// frsub first because it is the only one that needs alignment
.align 2
wrapper_func __aeabi_drsub
    eors r0, r1
    eors r1, r0
    eors r0, r1
    // fall thru

// double FUNC_NAME(__aeabi_dsub)(double x, double y)     double-precision subtraction, x - y
wrapper_func_d2 __aeabi_dsub
#if PICO_DOUBLE_PROPAGATE_NANS
    // we want to return nan for inf-inf or -inf - -inf, but without too much upfront cost
    mov ip, r0
    mov r0, r1
    eors r0, r3
    bmi 1f // different signs
    mov r0, ip
    push {r0-r3, lr}
    bl 2f
    b ddiv_dsub_nan_helper
1:
    mov r0, ip
2:
#endif
   shimmable_table_tail_call SF_TABLE_FSUB dsub_shim

wrapper_func_d2 __aeabi_dadd
   shimmable_table_tail_call SF_TABLE_FADD dadd_shim

// double FUNC_NAME(__aeabi_ddiv)(double n, double d)     double-precision division, n / d
wrapper_func_d2 __aeabi_ddiv
#if PICO_DOUBLE_PROPAGATE_NANS
    push {r0-r3, lr}
    bl 1f
    b ddiv_dsub_nan_helper
1:
#endif
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    mov ip, r2
    ldr r2, =(SIO_BASE)
    ldr r2, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r2, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs ddiv_save_state
    mov r2, ip
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl ddiv_shim_call
    msr PRIMASK, r4
    pop {r4, pc}
#endif
ddiv_shim_call:
    shimmable_table_tail_call SF_TABLE_FDIV ddiv_shim

#if !PICO_DIVIDER_DISABLE_INTERRUPTS
ddiv_save_state:
    ldr r2, =(SIO_BASE)
    save_div_state_and_lr
    mov r2, ip
    bl ddiv_shim_call
    ldr r2, =(SIO_BASE)
    restore_div_state_and_return
#endif

ddiv_dsub_nan_helper:
#if PICO_DOUBLE_PROPAGATE_NANS
    // check for infinite op infinite (or rather check for infinite result with both
    // operands being infinite)
    lsls r2, r1, #1
    asrs r2, r2, #21
    adds r2, #1
    beq 2f
    add sp, #16
    pop {pc}
2:
    ldr r2, [sp, #4]
    ldr r3, [sp, #12]
    lsls r2, #1
    asrs r2, r2, #21
    lsls r3, #1
    asrs r3, r3, #24
    ands r2, r3
    adds r2, #1
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
3:
    add sp, #16
    pop {pc}
#endif

// double FUNC_NAME(__aeabi_dmul)(double, double)         double-precision multiplication
wrapper_func_d2 __aeabi_dmul
#if PICO_DOUBLE_PROPAGATE_NANS
    push {r0-r3, lr}
    bl 1f

    // check for multiplication of infinite by zero (or rather check for infinite result with either
    // operand 0)
    lsls r3, r1, #1
    asrs r3, r3, #21
    adds r3, #1
    beq 2f
    add sp, #16
    pop {pc}
2:
    ldr r2, [sp, #4]
    ldr r3, [sp, #12]
    ands r2, r3
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
3:
    add sp, #16
    pop {pc}
1:
#endif
   shimmable_table_tail_call SF_TABLE_FMUL dmul_shim

// void FUNC_NAME(__aeabi_cdrcmple)(double, double)         reversed 3-way (<, =, ?>) compare [1], result in PSR ZC flags
double_wrapper_section __aeabi_cdcmple

wrapper_func __aeabi_cdrcmple
 push {r0-r7,r14}
    eors r0, r2
    eors r2, r0
    eors r0, r2
    eors r1, r3
    eors r3, r1
    eors r1, r3
    b __aeabi_dfcmple_guts

// NOTE these share an implementation as we have no excepting NaNs.
// void FUNC_NAME(__aeabi_cdcmple)(double, double)         3-way (<, =, ?>) compare [1], result in PSR ZC flags
// void FUNC_NAME(__aeabi_cdcmpeq)(double, double)         non-excepting equality comparison [1], result in PSR ZC flags
@ compare r0:r1 against r2:r3, returning -1/0/1 for <, =, >
@ also set flags accordingly
.align 2
wrapper_func __aeabi_cdcmple
wrapper_func __aeabi_cdcmpeq
 push {r0-r7,r14}
__aeabi_dfcmple_guts:
 ldr r7,=0x7ff                @ flush NaNs and denormals
 lsls r4,r1,#1
 lsrs r4,#21
 beq 1f
 cmp r4,r7
 bne 2f
 lsls r4, r1, #12
 bhi 7f
1:
 movs r0,#0
 lsrs r1,#20
 lsls r1,#20
2:
 lsls r4,r3,#1
 lsrs r4,#21
 beq 1f
 cmp r4,r7
 bne 2f
 lsls r4, r3, #12
 bhi 7f
1:
 movs r2,#0
 lsrs r3,#20
 lsls r3,#20
2:
 movs r6,#1
 eors r3,r1
 bmi 4f                        @ opposite signs? then can proceed on basis of sign of x
 eors r3,r1                    @ restore r3
 bpl 2f
 cmp r3,r1
 bne 7f
1:
 cmp r2,r0
7:
 pop {r0-r7,r15}
2:
 cmp r1,r3
 bne 7b
1:
 cmp r0,r2
 pop {r0-r7,r15}
4:
 orrs r3,r1                    @ make -0==+0
 adds r3,r3
 orrs r3,r0
 orrs r3,r2
 beq 7b
 mvns r1, r1     @ carry inverse of r1 sign
 adds r1, r1
 pop {r0-r7,r15}


// int FUNC_NAME(__aeabi_dcmpeq)(double, double)         result (1, 0) denotes (=, ?<>) [2], use for C == and !=
double_wrapper_section __aeabi_dcmpeq
.align 2
wrapper_func __aeabi_dcmpeq
    push {lr}
    bl __aeabi_cdcmpeq
    beq 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_dcmplt)(double, double)         result (1, 0) denotes (<, ?>=) [2], use for C <
double_wrapper_section __aeabi_dcmplt
.align 2
wrapper_func __aeabi_dcmplt
    push {lr}
    bl __aeabi_cdcmple
    sbcs r0, r0
    pop {pc}

// int FUNC_NAME(__aeabi_dcmple)(double, double)         result (1, 0) denotes (<=, ?>) [2], use for C <=
double_wrapper_section __aeabi_dcmple
.align 2
wrapper_func __aeabi_dcmple
    push {lr}
    bl __aeabi_cdcmple
    bls 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_dcmpge)(double, double)         result (1, 0) denotes (>=, ?<) [2], use for C >=
double_wrapper_section __aeabi_dcmpge
.align 2
wrapper_func __aeabi_dcmpge
    push {lr}
    // because of NaNs it is better to reverse the args than the result
    bl __aeabi_cdrcmple
    bls 1f
    movs r0, #0
    pop {pc}
1:
    movs r0, #1
    pop {pc}

// int FUNC_NAME(__aeabi_dcmpgt)(double, double)         result (1, 0) denotes (>, ?<=) [2], use for C >
double_wrapper_section __aeabi_dcmpgt
wrapper_func __aeabi_dcmpgt
    push {lr}
    // because of NaNs it is better to reverse the args than the result
    bl __aeabi_cdrcmple
    sbcs r0, r0
    pop {pc}

// int FUNC_NAME(__aeabi_dcmpun)(double, double)         result (1, 0) denotes (?, <=>) [2], use for C99 isunordered()
double_wrapper_section __aeabi_dcmpun
wrapper_func __aeabi_dcmpun
   movs r0, #1
   lsls r0, #21
   lsls r2, r1, #1
   adds r2, r0
   bhi 1f
   lsls r2, r3, #1
   adds r2, r0
   bhi 1f
   movs r0, #0
   bx lr
1:
   movs r0, #1
   bx lr

    movs r0, #0
    bx lr

// double FUNC_NAME(__aeabi_ui2d)(unsigned)             unsigned to double (double precision) conversion
double_wrapper_section __aeabi_ui2d
    shimmable_table_tail_call SF_TABLE_UINT2FLOAT uint2double_shim

double_wrapper_section __aeabi_i2d

wrapper_func __aeabi_ui2d
    movs r1, #0
    cmp r0, #0
    bne 2f
1:
    bx lr
// double FUNC_NAME(__aeabi_i2d)(int)                     integer to double (double precision) conversion
wrapper_func __aeabi_i2d
    asrs r1, r0, #31
    eors r0, r1
    subs r0, r1
    beq 1b
    lsls r1, #31
2:
    push {r0, r1, r4, lr}
    ldr r3, =sf_clz_func
    ldr r3, [r3]
    blx r3
    pop {r2, r3}
    adds r4, r0, #1
    lsls r2, r4
    lsls r0, r2, #20
    lsrs r2, #12
    ldr r1,=1055
    subs r1, r4
    lsls r1, #20
    orrs r1, r3
    orrs r1, r2
    pop {r4, pc}

// int FUNC_NAME(__aeabi_d2iz)(double)                     double (double precision) to integer C-style conversion [3]
double_wrapper_section __aeabi_d2iz
wrapper_func __aeabi_d2iz
regular_func double2int_z
    push {r4, lr}
    lsls r4, r1, #1
    lsrs r2, r4, #21
    movs r3, #0x80
    adds r2, r3
    lsls r3, #3
    subs r2, r3
    lsls r3, #21
    cmp r2, #126
    ble 1f
    subs r2, #158
    bge 2f
    asrs r4, r1, #31
    lsls r1, #12
    lsrs r1, #1
    orrs r1, r3
    negs r2, r2
    lsrs r1, r2
    lsls r4, #1
    adds r4, #1
    adds r2, #21
    cmp r2, #32
    bge 3f
    lsrs r0, r2
    orrs r0, r1
    muls r0, r4
    pop {r4, pc}
1:
    movs r0, #0
    pop {r4, pc}
3:
    mov r0, r1
    muls r0, r4
    pop {r4, pc}
2:
    // overflow
    lsrs r0, r1, #31
    adds r0, r3
    subs r0, #1
    pop {r4, pc}

double_section double2int
regular_func double2int
    shimmable_table_tail_call SF_TABLE_FLOAT2INT double2int_shim

// unsigned FUNC_NAME(__aeabi_d2uiz)(double)             double (double precision) to unsigned C-style conversion [3]
double_wrapper_section __aeabi_d2uiz
wrapper_func __aeabi_d2uiz
regular_func double2uint
    shimmable_table_tail_call SF_TABLE_FLOAT2UINT double2uint_shim

double_section fix2double
regular_func fix2double
    shimmable_table_tail_call SF_TABLE_FIX2FLOAT fix2double_shim

double_section ufix2double
regular_func ufix2double
    shimmable_table_tail_call SF_TABLE_UFIX2FLOAT ufix2double_shim

double_section fix642double
regular_func fix642double
    shimmable_table_tail_call SF_TABLE_FIX642FLOAT fix642double_shim

double_section ufix2double
regular_func ufix642double
    shimmable_table_tail_call SF_TABLE_UFIX642FLOAT ufix642double_shim

// double FUNC_NAME(__aeabi_l2d)(long long)             long long to double (double precision) conversion
double_wrapper_section __aeabi_l2d
wrapper_func __aeabi_l2d
    shimmable_table_tail_call SF_TABLE_INT642FLOAT int642double_shim

// double FUNC_NAME(__aeabi_l2f)(long long)             long long to double (double precision) conversion
double_wrapper_section __aeabi_ul2d
wrapper_func __aeabi_ul2d
    shimmable_table_tail_call SF_TABLE_UINT642FLOAT uint642double_shim

// long long FUNC_NAME(__aeabi_d2lz)(double)             double (double precision) to long long C-style conversion [3]
double_wrapper_section __aeabi_d2lz
wrapper_func __aeabi_d2lz
regular_func double2int64_z
    cmn r1, r1
    bcc double2int64
    push {lr}
    lsls r1, #1
    lsrs r1, #1
    movs r2, #0
    bl double2ufix64
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

double_section double2int64
regular_func double2int64
    shimmable_table_tail_call SF_TABLE_FLOAT2INT64 double2int64_shim

// unsigned long long FUNC_NAME(__aeabi_d2ulz)(double)     double to unsigned long long C-style conversion [3]
double_wrapper_section __aeabi_d2ulz
wrapper_func __aeabi_d2ulz
    shimmable_table_tail_call SF_TABLE_FLOAT2UINT64 double2uint64_shim

double_section double2fix64
regular_func double2fix64
    shimmable_table_tail_call SF_TABLE_FLOAT2FIX64 double2fix64_shim

double_section double2ufix64
regular_func double2ufix64
    shimmable_table_tail_call SF_TABLE_FLOAT2UFIX64 double2ufix64_shim

double_section double2fix
regular_func double2fix
    shimmable_table_tail_call SF_TABLE_FLOAT2FIX double2fix_shim

double_section double2ufix
regular_func double2ufix
    shimmable_table_tail_call SF_TABLE_FLOAT2UFIX double2ufix_shim

double_wrapper_section __aeabi_d2f
1:
#if PICO_DOUBLE_PROPAGATE_NANS
    // copy sign bit and 23 NAN id bits into sign bit and significant id bits, also set high id bit

    lsrs r0, #30
    lsls r2, r1, #12
    lsrs r2, #9
    asrs r1, #22
    lsls r1, #22
    orrs r0, r1
    orrs r0, r2
    bx lr
#endif
wrapper_func __aeabi_d2f
#if PICO_DOUBLE_PROPAGATE_NANS
    movs r3, #1
    lsls r3, #21
    lsls r2, r1, #1
    adds r2, r3
    bhi 1b
#endif
    // note double->float in double table at same index as float->double in double table
    shimmable_table_tail_call SF_TABLE_FLOAT2DOUBLE double2float_shim

double_wrapper_section srqt
wrapper_func_d1 sqrt
    shimmable_table_tail_call SF_TABLE_FSQRT dsqrt_shim

double_wrapper_section sincostan_remainder
regular_func sincostan_remainder
    ldr r2, =0x54442D18 // 2 * M_PI
    ldr r3, =0x401921FB
    push {lr}
    // note remainder only uses the divider thru integer divider functions
    // which save and restore themselves
    bl remainder
    pop {pc}

double_wrapper_section cos
#don't use _d1 as we're doing a range check anyway and infinites/nans are bigger than 1024
wrapper_func cos
    // rom version only works for -1024 < angle < 1024
    lsls r2, r1, #2
    bcc 1f
    lsrs r2, #22
    cmp r2, #9
    bge 2f
1:
    shimmable_table_tail_call SF_TABLE_FCOS dcos_shim
2:
#if PICO_DOUBLE_PROPAGATE_NANS
    lsls r2, r1, #1
    asrs r2, #21
    adds r2, #1
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
    bx lr
3:
#endif
    push {lr}
    bl sincostan_remainder
    pop {r2}
    mov lr, r2
    b 1b

double_wrapper_section sin
#don't use _d1 as we're doing a range check anyway and infinites/nans are bigger than 1024
wrapper_func sin
    // rom version only works for -1024 < angle < 1024
    lsls r2, r1, #2
    bcc 1f
    lsrs r2, #22
    cmp r2, #9
    bge 2f
1:
    shimmable_table_tail_call SF_TABLE_FSIN dsin_shim
2:
#if PICO_DOUBLE_PROPAGATE_NANS
    lsls r2, r1, #1
    asrs r2, #21
    adds r2, #1
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
    bx lr
3:
#endif
    push {lr}
    bl sincostan_remainder
    pop {r2}
    mov lr, r2
    b 1b

double_wrapper_section sincos
    // out of line remainder code for abs(angle)>=1024
2:
#if PICO_DOUBLE_PROPAGATE_NANS
    lsls r2, r1, #1
    asrs r2, #21
    adds r2, #1
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
    pop {r4-r5}
    stmia r4!, {r0, r1}
    stmia r5!, {r0, r1}
    pop {r4, r5, pc}
3:
#endif
    push {lr}
    bl sincostan_remainder
    pop {r2}
    mov lr, r2
    b 1f // continue with sincos

wrapper_func sincos
    push {r2-r5, lr}
    // rom version only works for -1024 < angle < 1024
    lsls r2, r1, #2
    bcc 1f
    lsrs r2, #22
    cmp r2, #9
    bge 2b
1:
    bl 2f // call the shim
    pop {r4-r5}
    stmia r4!, {r0, r1}
    stmia r5!, {r2, r3}
    pop {r4, r5, pc}

2:
    shimmable_table_tail_call SF_TABLE_V3_FSINCOS sincos_shim_bootstrap

.thumb_func
sincos_shim_bootstrap:
    push {r2, r3, r4}
    movs r3, #0x13
    ldrb r3, [r3]
#if PICO_DOUBLE_SUPPORT_ROM_V1 && PICO_RP2040_B0_SUPPORTED
    cmp r3, #1
    bne 1f
    ldr r3, =dsincos_shim
    b 2f
#endif
1:
    ldr r3, =dsincos_shim_v2
2:
    ldr r2, =sd_table
    str r3, [r2, #SF_TABLE_V3_FSINCOS]
    str r3, [sp, #8]
    pop {r2, r3, pc}
.thumb_func
dsincos_shim_v2:
     push {r4-r7,r14}
     bl push_r8_r11
     bl v2_rom_dsincos_internal
     mov r12,r0                    @ save ε
     bl v2_rom_dcos_finish
     push {r0,r1}
     mov r0,r12
     bl v2_rom_dsin_finish
     pop {r2,r3}
     bl pop_r8_r11
     pop {r4-r7,r15}
.thumb_func
v2_rom_dsincos_internal:
    push {r0, lr}
    ldr r0, =0x3855
    str r0, [sp, #4]
    pop {r0, pc}
.thumb_func
v2_rom_dcos_finish:
    push {r0, r1}
    ldr r0, =0x389d
    str r0, [sp, #4]
    pop {r0, pc}
.thumb_func
v2_rom_dsin_finish:
    push {r0, r1}
    ldr r0, =0x38d9
    str r0, [sp, #4]
    pop {r0, pc}

double_wrapper_section tan
#don't use _d1 as we're doing a range check anyway and infinites/nans are bigger than 1024
wrapper_func tan
    // rom version only works for -1024 < angle < 1024
    lsls r2, r1, #2
    bcc dtan_in_range
    lsrs r2, #22
    cmp r2, #9
    bge dtan_angle_out_of_range
dtan_in_range:
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
    // to support IRQ usage (or context switch) we must save/restore divider state around call if state is dirty
    mov ip, r2
    ldr r2, =(SIO_BASE)
    ldr r2, [r2, #SIO_DIV_CSR_OFFSET]
    lsrs r2, #SIO_DIV_CSR_DIRTY_SHIFT_FOR_CARRY
    bcs dtan_save_state
    mov r2, ip
#else
    // to avoid worrying about IRQs (or context switches), simply disable interrupts around call
    push {r4, lr}
    mrs r4, PRIMASK
    cpsid i
    bl dtan_shim_call
    msr PRIMASK, r4
    pop {r4, pc}
#endif
dtan_shim_call:
    shimmable_table_tail_call SF_TABLE_FTAN dtan_shim
#if !PICO_DIVIDER_DISABLE_INTERRUPTS
dtan_save_state:
    ldr r2, =(SIO_BASE)
    save_div_state_and_lr
    mov r2, ip
    bl dtan_shim_call
    ldr r2, =(SIO_BASE)
    restore_div_state_and_return
#endif
dtan_angle_out_of_range:
#if PICO_DOUBLE_PROPAGATE_NANS
    lsls r2, r1, #1
    asrs r2, #21
    adds r2, #1
    bne 3f
    // infinite to nan
    movs r2, #1
    lsls r2, #19
    orrs r1, r2
    bx lr
3:
#endif
    push {lr}
    bl sincostan_remainder
    pop {r2}
    mov lr, r2
    b dtan_in_range

double_wrapper_section atan2
wrapper_func_d2 atan2
    shimmable_table_tail_call SF_TABLE_FATAN2 datan2_shim

double_wrapper_section exp
wrapper_func_d1 exp
    shimmable_table_tail_call SF_TABLE_FEXP dexp_shim

double_wrapper_section log
wrapper_func_d1 log
    shimmable_table_tail_call SF_TABLE_FLN dln_shim

