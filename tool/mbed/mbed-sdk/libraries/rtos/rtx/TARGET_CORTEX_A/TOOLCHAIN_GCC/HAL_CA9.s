/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    HAL_CA9.c
 *      Purpose: Hardware Abstraction Layer for Cortex-A9
 *      Rev.:    3 Sept 2013
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 2012 - 2013 ARM Limited
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

    .global rt_set_PSP
    .global rt_get_PSP
    .global _alloc_box
    .global _free_box
    .global PendSV_Handler
    .global OS_Tick_Handler

    .EQU CPSR_T_BIT,    0x20
    .EQU CPSR_I_BIT,    0x80
    .EQU CPSR_F_BIT,    0x40

    .EQU MODE_USR,      0x10
    .EQU MODE_FIQ,      0x11
    .EQU MODE_IRQ,      0x12
    .EQU MODE_SVC,      0x13
    .EQU MODE_ABT,      0x17
    .EQU MODE_UND,      0x1B
    .EQU MODE_SYS,      0x1F

    .EQU TCB_TID,        3        /* 'task id' offset                        */
    .EQU TCB_STACKF,    32        /* 'stack_frame' offset                    */
    .EQU TCB_TSTACK,    36        /* 'tsk_stack' offset                      */

    .extern rt_alloc_box
    .extern os_tsk
    .extern GICInterface_BASE
    .extern rt_pop_req
    .extern os_tick_irqack
    .extern rt_systick

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/
    .text
@ For A-class, set USR/SYS stack
@ __asm void rt_set_PSP (U32 stack) {
rt_set_PSP:
        .arm

        MRS     R1, CPSR
        CPS     #MODE_SYS   @no effect in USR mode
        ISB
        MOV     SP, R0
        MSR     CPSR_c, R1  @no effect in USR mode
        ISB
        BX      LR

@ }

@ For A-class, get USR/SYS stack
@ __asm U32 rt_get_PSP (void) {
rt_get_PSP:
        .arm

        MRS     R1, CPSR
        CPS     #MODE_SYS   @no effect in USR mode
        ISB
        MOV     R0, SP
        MSR     CPSR_c, R1  @no effect in USR mode
        ISB
        BX      LR

@ }

/*--------------------------- _alloc_box ------------------------------------*/
@ __asm void *_alloc_box (void *box_mem) {
_alloc_box:
    /* Function wrapper for Unprivileged/Privileged mode. */
        .arm

        LDR     R12,=rt_alloc_box       @ __cpp(rt_alloc_box)
        MRS     R2, CPSR
        LSLS    R2, #28
        BXNE    R12
        SVC     0
        BX      LR
@ }


/*--------------------------- _free_box -------------------------------------*/
@ __asm int _free_box (void *box_mem, void *box) {
_free_box:
   /* Function wrapper for Unprivileged/Privileged mode. */
        .arm

        LDR     R12,=rt_free_box        @ __cpp(rt_free_box)
        MRS     R2, CPSR
        LSLS    R2, #28
        BXNE    R12
        SVC     0
        BX      LR

@ }

/*-------------------------- SVC_Handler -----------------------------------*/

@ #pragma push
@ #pragma arm
@ __asm void SVC_Handler (void) {

        .type   SVC_Handler, %function
        .global SVC_Handler
SVC_Handler:
@         PRESERVE8
        .arm
        .extern  rt_tsk_lock
        .extern  rt_tsk_unlock
        .extern  SVC_Count
        .extern  SVC_Table
        .extern  rt_stk_check
        .extern  FPUEnable

        .EQU    Mode_SVC, 0x13

        SRSDB   SP!, #Mode_SVC         @ Push LR_SVC and SPRS_SVC onto SVC mode stack
        PUSH    {R4}                   @ Push R4 so we can use it as a temp


        MRS     R4,SPSR                @ Get SPSR
        TST     R4,#CPSR_T_BIT         @ Check Thumb Bit
        LDRNEH  R4,[LR,#-2]            @ Thumb: Load Halfword
        BICNE   R4,R4,#0xFF00          @        Extract SVC Number
        LDREQ   R4,[LR,#-4]            @ ARM:   Load Word
        BICEQ   R4,R4,#0xFF000000      @        Extract SVC Number

        /* Lock out systick and re-enable interrupts */
        PUSH    {R0-R3,R12,LR}

        AND     R12, SP, #4            @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R12            @ Adjust stack
        PUSH    {R12, LR}              @ Store stack adjustment and dummy LR to SVC stack

        BLX     rt_tsk_lock
        CPSIE   i

        POP     {R12, LR}              @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R12            @ Unadjust stack

        POP     {R0-R3,R12,LR}

        CMP     R4,#0
        BNE     SVC_User

        MRS     R4,SPSR
        PUSH    {R4}                    @ Push R4 so we can use it as a temp
        AND     R4, SP, #4              @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R4              @ Adjust stack
        PUSH    {R4, LR}                @ Store stack adjustment and dummy LR
        BLX     R12
        POP     {R4, LR}                @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R4              @ Unadjust stack
        POP     {R4}                    @ Restore R4
        MSR     SPSR_cxsf,R4

        /* Here we will be in SVC mode (even if coming in from PendSV_Handler or OS_Tick_Handler) */
Sys_Switch:
        LDR     LR,=os_tsk              @ __cpp(&os_tsk)
        LDM     LR,{R4,LR}              @ os_tsk.run, os_tsk.new
        CMP     R4,LR
        BNE     switching

        PUSH    {R0-R3,R12,LR}

        AND     R12, SP, #4             @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R12             @ Adjust stack
        PUSH    {R12, LR}               @ Store stack adjustment and dummy LR to SVC stack

        CPSID   i
        BLX     rt_tsk_unlock

        POP     {R12, LR}               @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R12             @ Unadjust stack

        POP     {R0-R3,R12,LR}
        POP     {R4}
        RFEFD   SP!                     @ Return from exception, no task switch

switching:
        CLREX
        CMP     R4,#0
        ADDEQ   SP,SP,#12               @ Original R4, LR & SPSR do not need to be popped when we are paging in a different task
        BEQ     SVC_Next                @ Runtask deleted?


        PUSH    {R8-R11} @ R4 and LR already stacked
        MOV     R10,R4                  @ Preserve os_tsk.run
        MOV     R11,LR                  @ Preserve os_tsk.new

        ADD     R8,SP,#16               @ Unstack R4,LR
        LDMIA   R8,{R4,LR}

        SUB     SP,SP,#4                @ Make space on the stack for the next instn
        STMIA   SP,{SP}^                @ Put User SP onto stack
        POP     {R8}                    @ Pop User SP into R8

        MRS     R9,SPSR
        STMDB   R8!,{R9}                @ User CPSR
        STMDB   R8!,{LR}                @ User PC
        STMDB   R8,{LR}^                @ User LR
        SUB     R8,R8,#4                @ No writeback for store of User LR
        STMDB   R8!,{R0-R3,R12}         @ User R0-R3,R12
        MOV     R3,R10                  @ os_tsk.run
        MOV     LR,R11                  @ os_tsk.new
        POP     {R9-R12}
        ADD     SP,SP,#12               @ Fix up SP for unstack of R4, LR & SPSR
        STMDB   R8!,{R4-R7,R9-R12}      @ User R4-R11

        @ If applicable, stack VFP state
        MRC     p15,0,R1,c1,c0,2        @ VFP/NEON access enabled? (CPACR)
        AND     R2,R1,#0x00F00000
        CMP     R2,#0x00F00000
        BNE     no_outgoing_vfp
        VMRS    R2,FPSCR
        STMDB   R8!,{R2,R4}             @ Push FPSCR, maintain 8-byte alignment
        VSTMDB  R8!,{S0-S31}
        LDRB    R2,[R3,#TCB_STACKF]     @ Record in TCB that VFP state is stacked
        ORR     R2,#2
        STRB    R2,[R3,#TCB_STACKF]

no_outgoing_vfp:
        STR     R8,[R3,#TCB_TSTACK]
        MOV     R4,LR

        PUSH    {R4}                    @ Push R4 so we can use it as a temp
        AND     R4, SP, #4              @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R4              @ Adjust stack
        PUSH    {R4, LR}                @ Store stack adjustment and dummy LR to SVC stack

        BLX     rt_stk_check

        POP     {R4, LR}                @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R4              @ Unadjust stack
        POP     {R4}                    @ Restore R4

        MOV     LR,R4

SVC_Next:  @ R4 == os_tsk.run, LR == os_tsk.new, R0-R3, R5-R12 corruptible
        LDR     R1,=os_tsk              @ __cpp(&os_tsk), os_tsk.run = os_tsk.new
        STR     LR,[R1]
        LDRB    R1,[LR,#TCB_TID]        @ os_tsk.run->task_id
        LSL     R1,#8                   @ Store PROCID
        MCR     p15,0,R1,c13,c0,1       @ Write CONTEXTIDR

        LDR     R0,[LR,#TCB_TSTACK]     @ os_tsk.run->tsk_stack

        @ Does incoming task have VFP state in stack?
        LDRB    R3,[LR,#TCB_STACKF]
        TST     R3,#0x2
        MRC     p15,0,R1,c1,c0,2        @ Read CPACR
        ANDEQ   R1,R1,#0xFF0FFFFF       @ Disable VFP access if incoming task does not have stacked VFP state
        ORRNE   R1,R1,#0x00F00000       @ Enable VFP access if incoming task does have stacked VFP state
        MCR     p15,0,R1,c1,c0,2        @ Write CPACR
        BEQ     no_incoming_vfp
        ISB                             @ We only need the sync if we enabled, otherwise we will context switch before next VFP instruction anyway
        VLDMIA  R0!,{S0-S31}
        LDR     R2,[R0]
        VMSR    FPSCR,R2
        ADD     R0,R0,#8

no_incoming_vfp:
        LDR     R1,[R0,#60]             @ Restore User CPSR
        MSR     SPSR_cxsf,R1
        LDMIA   R0!,{R4-R11}            @ Restore User R4-R11
        ADD     R0,R0,#4                @ Restore User R1-R3,R12
        LDMIA   R0!,{R1-R3,R12}
        LDMIA   R0,{LR}^                @ Restore User LR
        ADD     R0,R0,#4                @ No writeback for load to user LR
        LDMIA   R0!,{LR}                @ Restore User PC
        ADD     R0,R0,#4                @ Correct User SP for unstacked user CPSR

        PUSH    {R0}                    @ Push R0 onto stack
        LDMIA   SP,{SP}^                @ Get R0 off stack into User SP
        ADD     SP,SP,#4                @ Put SP back

        LDR     R0,[R0,#-32]            @ Restore R0

        PUSH    {R0-R3,R12,LR}

        AND     R12, SP, #4             @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R12             @ Adjust stack
        PUSH    {R12, LR}               @ Store stack adjustment and dummy LR to SVC stack

        CPSID   i
        BLX     rt_tsk_unlock

        POP     {R12, LR}               @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R12             @ Unadjust stack

        POP     {R0-R3,R12,LR}

        MOVS    PC,LR                   @ Return from exception


        /*------------------- User SVC -------------------------------*/

SVC_User:
        LDR     R12,=SVC_Count
        LDR     R12,[R12]
        CMP     R4,R12                  @ Check for overflow
        BHI     SVC_Done

        LDR     R12,=SVC_Table-4
        LDR     R12,[R12,R4,LSL #2]     @ Load SVC Function Address
        MRS     R4,SPSR                 @ Save SPSR
        PUSH    {R4}                    @ Push R4 so we can use it as a temp
        AND     R4, SP, #4              @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R4              @ Adjust stack
        PUSH    {R4, LR}                @ Store stack adjustment and dummy LR
        BLX     R12                     @ Call SVC Function
        POP     {R4, LR}                @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R4              @ Unadjust stack
        POP     {R4}                    @ Restore R4
        MSR     SPSR_cxsf,R4            @ Restore SPSR

SVC_Done:
        PUSH    {R0-R3,R12,LR}

        PUSH    {R4}                    @ Push R4 so we can use it as a temp
        AND     R4, SP, #4              @ Ensure stack is 8-byte aligned
        SUB     SP, SP, R4              @ Adjust stack
        PUSH    {R4, LR}                @ Store stack adjustment and dummy LR

        CPSID   i
        BLX     rt_tsk_unlock

        POP     {R4, LR}                @ Get stack adjustment & discard dummy LR
        ADD     SP, SP, R4              @ Unadjust stack
        POP     {R4}                    @ Restore R4

        POP     {R0-R3,R12,LR}
        POP     {R4}
        RFEFD   SP!                     @ Return from exception

@ }

@ #pragma pop


@ #pragma push
@ #pragma arm
@ __asm void PendSV_Handler (U32 IRQn) {
PendSV_Handler:
    .arm

    .extern  rt_tsk_lock
    .extern  IRQNestLevel

    ADD     SP,SP,#8 @ fix up stack pointer (R0 has been pushed and will never be popped, R1 was pushed for stack alignment)

    @ Disable systick interrupts, then write EOIR. We want interrupts disabled before we enter the context switcher.
    PUSH    {R0, R1}
    BLX     rt_tsk_lock
    POP     {R0, R1}
    LDR     R1, =GICInterface_BASE      @ __cpp(&GICInterface_BASE)
    LDR     R1, [R1, #0]
    STR     R0, [R1, #0x10]

    LDR     R0, =IRQNestLevel           @ Get address of nesting counter
    LDR     R1, [R0]
    SUB     R1, R1, #1                  @ Decrement nesting counter
    STR     R1, [R0]

    BLX     rt_pop_req                  @ __cpp(rt_pop_req)

    POP     {R1, LR}                @ Get stack adjustment & discard dummy LR
    ADD     SP, SP, R1              @ Unadjust stack

    LDR     R0,[SP,#24]
    MSR     SPSR_cxsf,R0
    POP     {R0-R3,R12}             @ Leave SPSR & LR on the stack
    PUSH    {R4}
    B       Sys_Switch
@ }
@ #pragma pop

@ #pragma push
@ #pragma arm
@ __asm void OS_Tick_Handler (U32 IRQn) {
OS_Tick_Handler:
    .arm

    ADD     SP,SP,#8 @ fix up stack pointer (R0 has been pushed and will never be popped, R1 was pushed for stack alignment)

    PUSH    {R0, R1}
    BLX     rt_tsk_lock
    POP     {R0, R1}
    LDR     R1, =GICInterface_BASE      @ __cpp(&GICInterface_BASE)
    LDR     R1, [R1, #0]
    STR     R0, [R1, #0x10]

    LDR     R0, =IRQNestLevel           @ Get address of nesting counter
    LDR     R1, [R0]
    SUB     R1, R1, #1                  @ Decrement nesting counter
    STR     R1, [R0]

    BLX      os_tick_irqack             @ __cpp(os_tick_irqack)
    BLX      rt_systick                 @ __cpp(rt_systick)

    POP     {R1, LR}                @ Get stack adjustment & discard dummy LR
    ADD     SP, SP, R1              @ Unadjust stack

    LDR     R0,[SP,#24]
    MSR     SPSR_cxsf,R0
    POP     {R0-R3,R12}             @ Leave SPSR & LR on the stack
    PUSH    {R4}
    B       Sys_Switch
@ }
@ #pragma pop

    .global __set_PSP
@ __STATIC_ASM void __set_PSP(uint32_t topOfProcStack)
@ {
__set_PSP:
@     PRESERVE8
    .arm

    BIC     R0, R0, #7  @ensure stack is 8-byte aligned
    MRS     R1, CPSR
    CPS     #MODE_SYS   @no effect in USR mode
    MOV     SP, R0
    MSR     CPSR_c, R1  @no effect in USR mode
    ISB
    BX      LR

@ }

    .global __set_CPS_USR
@ __STATIC_ASM void __set_CPS_USR(void)
@ {
__set_CPS_USR:
    .arm

    CPS  #MODE_USR
    BX   LR
@ }

    .END
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
