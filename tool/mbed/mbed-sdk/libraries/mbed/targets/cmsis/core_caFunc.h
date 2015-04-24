/**************************************************************************//**
 * @file     core_caFunc.h
 * @brief    CMSIS Cortex-A Core Function Access Header File
 * @version  V3.10
 * @date     9 May 2013
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2009 - 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#ifndef __CORE_CAFUNC_H__
#define __CORE_CAFUNC_H__


/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */

#if   defined ( __CC_ARM ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#if (__ARMCC_VERSION < 400677)
  #error "Please use ARM Compiler Toolchain V4.0.677 or later!"
#endif

#define MODE_USR 0x10
#define MODE_FIQ 0x11
#define MODE_IRQ 0x12
#define MODE_SVC 0x13
#define MODE_MON 0x16
#define MODE_ABT 0x17
#define MODE_HYP 0x1A
#define MODE_UND 0x1B
#define MODE_SYS 0x1F

/** \brief  Get APSR Register

    This function returns the content of the APSR Register.

    \return               APSR Register value
 */
__STATIC_INLINE uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __ASM("apsr");
  return(__regAPSR);
}


/** \brief  Get CPSR Register

    This function returns the content of the CPSR Register.

    \return               CPSR Register value
 */
__STATIC_INLINE uint32_t __get_CPSR(void)
{
  register uint32_t __regCPSR          __ASM("cpsr");
  return(__regCPSR);
}

/** \brief  Set Stack Pointer

    This function assigns the given value to the current stack pointer.

    \param [in]    topOfStack  Stack Pointer value to set
 */
register uint32_t __regSP              __ASM("sp");
__STATIC_INLINE void __set_SP(uint32_t topOfStack)
{
    __regSP = topOfStack;
}


/** \brief  Get link register

    This function returns the value of the link register

    \return    Value of link register
 */
register uint32_t __reglr         __ASM("lr");
__STATIC_INLINE uint32_t __get_LR(void)
{
  return(__reglr);
}

/** \brief  Set link register

    This function sets the value of the link register

    \param [in]    lr  LR value to set
 */
__STATIC_INLINE void __set_LR(uint32_t lr)
{
  __reglr = lr;
}

/** \brief  Set Process Stack Pointer

    This function assigns the given value to the USR/SYS Stack Pointer (PSP).

    \param [in]    topOfProcStack  USR/SYS Stack Pointer value to set
 */
__STATIC_ASM void __set_PSP(uint32_t topOfProcStack)
{
    ARM
    PRESERVE8

    BIC     R0, R0, #7  ;ensure stack is 8-byte aligned
    MRS     R1, CPSR
    CPS     #MODE_SYS   ;no effect in USR mode
    MOV     SP, R0
    MSR     CPSR_c, R1  ;no effect in USR mode
    ISB
    BX      LR

}

/** \brief  Set User Mode

    This function changes the processor state to User Mode

    \param [in]    topOfProcStack  USR/SYS Stack Pointer value to set
 */
__STATIC_ASM void __set_CPS_USR(void)
{
    ARM 

    CPS  #MODE_USR  
    BX   LR
}


/** \brief  Enable FIQ

    This function enables FIQ interrupts by clearing the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __enable_fault_irq                __enable_fiq


/** \brief  Disable FIQ

    This function disables FIQ interrupts by setting the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __disable_fault_irq               __disable_fiq


/** \brief  Get FPSCR

    This function returns the current value of the Floating Point Status/Control register.

    \return               Floating Point Status/Control register value
 */
__STATIC_INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  register uint32_t __regfpscr         __ASM("fpscr");
  return(__regfpscr);
#else
   return(0);
#endif
}


/** \brief  Set FPSCR

    This function assigns the given value to the Floating Point Status/Control register.

    \param [in]    fpscr  Floating Point Status/Control value to set
 */
__STATIC_INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  register uint32_t __regfpscr         __ASM("fpscr");
  __regfpscr = (fpscr);
#endif
}

/** \brief  Get FPEXC

    This function returns the current value of the Floating Point Exception Control register.

    \return               Floating Point Exception Control register value
 */
__STATIC_INLINE uint32_t __get_FPEXC(void)
{
#if (__FPU_PRESENT == 1)
  register uint32_t __regfpexc         __ASM("fpexc");
  return(__regfpexc);
#else
   return(0);
#endif
}


/** \brief  Set FPEXC

    This function assigns the given value to the Floating Point Exception Control register.

    \param [in]    fpscr  Floating Point Exception Control value to set
 */
__STATIC_INLINE void __set_FPEXC(uint32_t fpexc)
{
#if (__FPU_PRESENT == 1)
  register uint32_t __regfpexc         __ASM("fpexc");
  __regfpexc = (fpexc);
#endif
}

/** \brief  Get CPACR

    This function returns the current value of the Coprocessor Access Control register.

    \return               Coprocessor Access Control register value
 */
__STATIC_INLINE uint32_t __get_CPACR(void)
{
    register uint32_t __regCPACR         __ASM("cp15:0:c1:c0:2");
    return __regCPACR;
}

/** \brief  Set CPACR

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    cpacr  Coporcessor Acccess Control value to set
 */
__STATIC_INLINE void __set_CPACR(uint32_t cpacr)
{
    register uint32_t __regCPACR         __ASM("cp15:0:c1:c0:2");
    __regCPACR = cpacr;
    __ISB();
}

/** \brief  Get CBAR

    This function returns the value of the Configuration Base Address register.

    \return               Configuration Base Address register value
 */
__STATIC_INLINE uint32_t __get_CBAR() {
    register uint32_t __regCBAR         __ASM("cp15:4:c15:c0:0");
    return(__regCBAR);
}

/** \brief  Get TTBR0

    This function returns the value of the Configuration Base Address register.

    \return               Translation Table Base Register 0 value
 */
__STATIC_INLINE uint32_t __get_TTBR0() {
    register uint32_t __regTTBR0        __ASM("cp15:0:c2:c0:0");
    return(__regTTBR0);
}

/** \brief  Set TTBR0

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    ttbr0  Translation Table Base Register 0 value to set
 */
__STATIC_INLINE void __set_TTBR0(uint32_t ttbr0) {
    register uint32_t __regTTBR0        __ASM("cp15:0:c2:c0:0");
    __regTTBR0 = ttbr0;
    __ISB();
}

/** \brief  Get DACR

    This function returns the value of the Domain Access Control Register.

    \return               Domain Access Control Register value
 */
__STATIC_INLINE uint32_t __get_DACR() {
    register uint32_t __regDACR         __ASM("cp15:0:c3:c0:0");
    return(__regDACR);
}

/** \brief  Set DACR

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    dacr   Domain Access Control Register value to set
 */
__STATIC_INLINE void __set_DACR(uint32_t dacr) {
    register uint32_t __regDACR         __ASM("cp15:0:c3:c0:0");
    __regDACR = dacr;
    __ISB();
}

/******************************** Cache and BTAC enable  ****************************************************/

/** \brief  Set SCTLR

    This function assigns the given value to the System Control Register.

    \param [in]    sctlr  System Control Register, value to set
 */
__STATIC_INLINE void __set_SCTLR(uint32_t sctlr)
{
    register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
    __regSCTLR = sctlr;
}

/** \brief  Get SCTLR

    This function returns the value of the System Control Register.

    \return               System Control Register value
 */
__STATIC_INLINE uint32_t __get_SCTLR() {
    register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
    return(__regSCTLR);
}

/** \brief  Enable Caches

    Enable Caches
 */
__STATIC_INLINE void __enable_caches(void) {
    // Set I bit 12 to enable I Cache
    // Set C bit  2 to enable D Cache
    __set_SCTLR( __get_SCTLR() | (1 << 12) | (1 << 2));
}

/** \brief  Disable Caches

    Disable Caches
 */
__STATIC_INLINE void __disable_caches(void) {
    // Clear I bit 12 to disable I Cache
    // Clear C bit  2 to disable D Cache
    __set_SCTLR( __get_SCTLR() & ~(1 << 12) & ~(1 << 2));
    __ISB();
}

/** \brief  Enable BTAC

    Enable BTAC
 */
__STATIC_INLINE void __enable_btac(void) {
    // Set Z bit 11 to enable branch prediction
    __set_SCTLR( __get_SCTLR() | (1 << 11));
    __ISB();
}

/** \brief  Disable BTAC

    Disable BTAC
 */
__STATIC_INLINE void __disable_btac(void) {
    // Clear Z bit 11 to disable branch prediction
    __set_SCTLR( __get_SCTLR() & ~(1 << 11));
}


/** \brief  Enable MMU

    Enable MMU
 */
__STATIC_INLINE void __enable_mmu(void) {
    // Set M bit 0 to enable the MMU
    // Set AFE bit to enable simplified access permissions model
    // Clear TRE bit to disable TEX remap and A bit to disable strict alignment fault checking
    __set_SCTLR( (__get_SCTLR() & ~(1 << 28) & ~(1 << 1)) | 1 | (1 << 29));
    __ISB();
}

/** \brief  Enable MMU

    Enable MMU
 */
__STATIC_INLINE void __disable_mmu(void) {
    // Clear M bit 0 to disable the MMU
    __set_SCTLR( __get_SCTLR() & ~1);
    __ISB();
}

/******************************** TLB maintenance operations ************************************************/
/** \brief  Invalidate the whole tlb

    TLBIALL. Invalidate the whole tlb
 */

__STATIC_INLINE void __ca9u_inv_tlb_all(void) {
    register uint32_t __TLBIALL         __ASM("cp15:0:c8:c7:0");
    __TLBIALL = 0;
    __DSB();
    __ISB();
}

/******************************** BTB maintenance operations ************************************************/
/** \brief  Invalidate entire branch predictor array

    BPIALL. Branch Predictor Invalidate All.
 */

__STATIC_INLINE void __v7_inv_btac(void) {
    register uint32_t __BPIALL          __ASM("cp15:0:c7:c5:6");
    __BPIALL  = 0;
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new state
}


/******************************** L1 cache operations ******************************************************/

/** \brief  Invalidate the whole I$

    ICIALLU. Instruction Cache Invalidate All to PoU
 */
__STATIC_INLINE void __v7_inv_icache_all(void) {
    register uint32_t __ICIALLU         __ASM("cp15:0:c7:c5:0");
    __ICIALLU = 0;
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new I cache state
}

/** \brief  Clean D$ by MVA

    DCCMVAC. Data cache clean by MVA to PoC
 */
__STATIC_INLINE void __v7_clean_dcache_mva(void *va) {
    register uint32_t __DCCMVAC         __ASM("cp15:0:c7:c10:1");
    __DCCMVAC = (uint32_t)va;
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief  Invalidate D$ by MVA

    DCIMVAC. Data cache invalidate by MVA to PoC
 */
__STATIC_INLINE void __v7_inv_dcache_mva(void *va) {
    register uint32_t __DCIMVAC         __ASM("cp15:0:c7:c6:1");
    __DCIMVAC = (uint32_t)va;
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief  Clean and Invalidate D$ by MVA

    DCCIMVAC. Data cache clean and invalidate by MVA to PoC
 */
__STATIC_INLINE void __v7_clean_inv_dcache_mva(void *va) {
    register uint32_t __DCCIMVAC        __ASM("cp15:0:c7:c14:1");
    __DCCIMVAC = (uint32_t)va;
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief
 * Generic mechanism for cleaning/invalidating the entire data or unified cache to the point of coherency.
 */
#pragma push
#pragma arm
__STATIC_ASM void __v7_all_cache(uint32_t op) {
        ARM 

        PUSH    {R4-R11}

        MRC     p15, 1, R6, c0, c0, 1      // Read CLIDR
        ANDS    R3, R6, #0x07000000        // Extract coherency level
        MOV     R3, R3, LSR #23            // Total cache levels << 1
        BEQ     Finished                   // If 0, no need to clean

        MOV     R10, #0                    // R10 holds current cache level << 1
Loop1   ADD     R2, R10, R10, LSR #1       // R2 holds cache "Set" position
        MOV     R1, R6, LSR R2             // Bottom 3 bits are the Cache-type for this level
        AND     R1, R1, #7                 // Isolate those lower 3 bits
        CMP     R1, #2
        BLT     Skip                       // No cache or only instruction cache at this level

        MCR     p15, 2, R10, c0, c0, 0     // Write the Cache Size selection register
        ISB                                // ISB to sync the change to the CacheSizeID reg
        MRC     p15, 1, R1, c0, c0, 0      // Reads current Cache Size ID register
        AND     R2, R1, #7                 // Extract the line length field
        ADD     R2, R2, #4                 // Add 4 for the line length offset (log2 16 bytes)
        LDR     R4, =0x3FF
        ANDS    R4, R4, R1, LSR #3         // R4 is the max number on the way size (right aligned)
        CLZ     R5, R4                     // R5 is the bit position of the way size increment
        LDR     R7, =0x7FFF
        ANDS    R7, R7, R1, LSR #13        // R7 is the max number of the index size (right aligned)

Loop2   MOV     R9, R4                     // R9 working copy of the max way size (right aligned)

Loop3   ORR     R11, R10, R9, LSL R5       // Factor in the Way number and cache number into R11
        ORR     R11, R11, R7, LSL R2       // Factor in the Set number
        CMP     R0, #0
        BNE     Dccsw
        MCR     p15, 0, R11, c7, c6, 2     // DCISW. Invalidate by Set/Way
        B       cont
Dccsw   CMP     R0, #1
        BNE     Dccisw
        MCR     p15, 0, R11, c7, c10, 2    // DCCSW. Clean by Set/Way
        B       cont
Dccisw  MCR     p15, 0, R11, c7, c14, 2    // DCCISW, Clean and Invalidate by Set/Way
cont    SUBS    R9, R9, #1                 // Decrement the Way number
        BGE     Loop3
        SUBS    R7, R7, #1                 // Decrement the Set number
        BGE     Loop2
Skip    ADD     R10, R10, #2               // increment the cache number
        CMP     R3, R10
        BGT     Loop1

Finished
        DSB
        POP    {R4-R11}
        BX     lr

}
#pragma pop

/** \brief  __v7_all_cache - helper function

 */

/** \brief  Invalidate the whole D$

    DCISW. Invalidate by Set/Way
 */

__STATIC_INLINE void __v7_inv_dcache_all(void) {
    __v7_all_cache(0);
}

/** \brief  Clean the whole D$

    DCCSW. Clean by Set/Way
 */

__STATIC_INLINE void __v7_clean_dcache_all(void) {
    __v7_all_cache(1);
}

/** \brief  Clean and invalidate the whole D$

    DCCISW. Clean and Invalidate by Set/Way
 */

__STATIC_INLINE void __v7_clean_inv_dcache_all(void) {
    __v7_all_cache(2);
}

#include "core_ca_mmu.h"

#elif (defined (__ICCARM__)) /*---------------- ICC Compiler ---------------------*/

#error IAR Compiler support not implemented for Cortex-A

#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/

/* GNU gcc specific functions */

#define MODE_USR 0x10
#define MODE_FIQ 0x11
#define MODE_IRQ 0x12
#define MODE_SVC 0x13
#define MODE_MON 0x16
#define MODE_ABT 0x17
#define MODE_HYP 0x1A
#define MODE_UND 0x1B
#define MODE_SYS 0x1F


__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_irq(void)
{
    __ASM volatile ("cpsie i");
}

/** \brief  Disable IRQ Interrupts

  This function disables IRQ interrupts by setting the I-bit in the CPSR.
  Can only be executed in Privileged modes.
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __disable_irq(void)
{
    uint32_t result;

    __ASM volatile ("mrs %0, cpsr" : "=r" (result));
    __ASM volatile ("cpsid i");
    return(result & 0x80);
}


/** \brief  Get APSR Register

    This function returns the content of the APSR Register.

    \return               APSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_APSR(void)
{
#if 1
    uint32_t result;

    __ASM volatile ("mrs %0, apsr" : "=r" (result) );
    return (result);
#else
  register uint32_t __regAPSR          __ASM("apsr");
  return(__regAPSR);
#endif
}


/** \brief  Get CPSR Register

    This function returns the content of the CPSR Register.

    \return               CPSR Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_CPSR(void)
{
#if 1
  register uint32_t __regCPSR;
  __ASM volatile ("mrs %0, cpsr" : "=r" (__regCPSR));
#else
  register uint32_t __regCPSR          __ASM("cpsr");
#endif
  return(__regCPSR);
}

#if 0
/** \brief  Set Stack Pointer

    This function assigns the given value to the current stack pointer.

    \param [in]    topOfStack  Stack Pointer value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_SP(uint32_t topOfStack)
{
    register uint32_t __regSP       __ASM("sp");
    __regSP = topOfStack;
}
#endif

/** \brief  Get link register

    This function returns the value of the link register

    \return    Value of link register
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_LR(void)
{
  register uint32_t __reglr         __ASM("lr");
  return(__reglr);
}

#if 0
/** \brief  Set link register

    This function sets the value of the link register

    \param [in]    lr  LR value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_LR(uint32_t lr)
{
  register uint32_t __reglr         __ASM("lr");
  __reglr = lr;
}
#endif

/** \brief  Set Process Stack Pointer

    This function assigns the given value to the USR/SYS Stack Pointer (PSP).

    \param [in]    topOfProcStack  USR/SYS Stack Pointer value to set
 */
extern void __set_PSP(uint32_t topOfProcStack);

/** \brief  Set User Mode

    This function changes the processor state to User Mode

    \param [in]    topOfProcStack  USR/SYS Stack Pointer value to set
 */
extern void __set_CPS_USR(void);

/** \brief  Enable FIQ

    This function enables FIQ interrupts by clearing the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __enable_fault_irq                __enable_fiq


/** \brief  Disable FIQ

    This function disables FIQ interrupts by setting the F-bit in the CPSR.
    Can only be executed in Privileged modes.
 */
#define __disable_fault_irq               __disable_fiq


/** \brief  Get FPSCR

    This function returns the current value of the Floating Point Status/Control register.

    \return               Floating Point Status/Control register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
#if 1
    uint32_t result;

    __ASM volatile ("vmrs %0, fpscr" : "=r" (result) );
    return (result);
#else
  register uint32_t __regfpscr         __ASM("fpscr");
  return(__regfpscr);
#endif
#else
   return(0);
#endif
}


/** \brief  Set FPSCR

    This function assigns the given value to the Floating Point Status/Control register.

    \param [in]    fpscr  Floating Point Status/Control value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
#if 1
    __ASM volatile ("vmsr fpscr, %0" : : "r" (fpscr) );
#else
  register uint32_t __regfpscr         __ASM("fpscr");
  __regfpscr = (fpscr);
#endif
#endif
}

/** \brief  Get FPEXC

    This function returns the current value of the Floating Point Exception Control register.

    \return               Floating Point Exception Control register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_FPEXC(void)
{
#if (__FPU_PRESENT == 1)
#if 1
    uint32_t result;

    __ASM volatile ("vmrs %0, fpexc" : "=r" (result));
    return (result);
#else
  register uint32_t __regfpexc         __ASM("fpexc");
  return(__regfpexc);
#endif
#else
   return(0);
#endif
}


/** \brief  Set FPEXC

    This function assigns the given value to the Floating Point Exception Control register.

    \param [in]    fpscr  Floating Point Exception Control value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_FPEXC(uint32_t fpexc)
{
#if (__FPU_PRESENT == 1)
#if 1
    __ASM volatile ("vmsr fpexc, %0" : : "r" (fpexc));
#else
  register uint32_t __regfpexc         __ASM("fpexc");
  __regfpexc = (fpexc);
#endif
#endif
}

/** \brief  Get CPACR

    This function returns the current value of the Coprocessor Access Control register.

    \return               Coprocessor Access Control register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_CPACR(void)
{
#if 1
    register uint32_t __regCPACR;
    __ASM volatile ("mrc p15, 0, %0, c1, c0, 2" : "=r" (__regCPACR));
#else
    register uint32_t __regCPACR         __ASM("cp15:0:c1:c0:2");
#endif
    return __regCPACR;
}

/** \brief  Set CPACR

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    cpacr  Coporcessor Acccess Control value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_CPACR(uint32_t cpacr)
{
#if 1
    __ASM volatile ("mcr p15, 0, %0, c1, c0, 2" : : "r" (cpacr));
#else
    register uint32_t __regCPACR         __ASM("cp15:0:c1:c0:2");
    __regCPACR = cpacr;
#endif
    __ISB();
}

/** \brief  Get CBAR

    This function returns the value of the Configuration Base Address register.

    \return               Configuration Base Address register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_CBAR() {
#if 1
    register uint32_t __regCBAR;
    __ASM volatile ("mrc p15, 4, %0, c15, c0, 0" : "=r" (__regCBAR));
#else
    register uint32_t __regCBAR         __ASM("cp15:4:c15:c0:0");
#endif
    return(__regCBAR);
}

/** \brief  Get TTBR0

    This function returns the value of the Configuration Base Address register.

    \return               Translation Table Base Register 0 value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_TTBR0() {
#if 1
    register uint32_t __regTTBR0;
    __ASM volatile ("mrc p15, 0, %0, c2, c0, 0" : "=r" (__regTTBR0));
#else
    register uint32_t __regTTBR0        __ASM("cp15:0:c2:c0:0");
#endif
    return(__regTTBR0);
}

/** \brief  Set TTBR0

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    ttbr0  Translation Table Base Register 0 value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_TTBR0(uint32_t ttbr0) {
#if 1
	__ASM volatile ("mcr p15, 0, %0, c2, c0, 0" : : "r" (ttbr0));
#else
    register uint32_t __regTTBR0        __ASM("cp15:0:c2:c0:0");
    __regTTBR0 = ttbr0;
#endif
    __ISB();
}

/** \brief  Get DACR

    This function returns the value of the Domain Access Control Register.

    \return               Domain Access Control Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_DACR() {
#if 1
    register uint32_t __regDACR;
    __ASM volatile ("mrc p15, 0, %0, c3, c0, 0" : "=r" (__regDACR));
#else
    register uint32_t __regDACR         __ASM("cp15:0:c3:c0:0");
#endif
    return(__regDACR);
}

/** \brief  Set DACR

    This function assigns the given value to the Coprocessor Access Control register.

    \param [in]    dacr   Domain Access Control Register value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_DACR(uint32_t dacr) {
#if 1
	__ASM volatile ("mcr p15, 0, %0, c3, c0, 0" : : "r" (dacr));
#else
    register uint32_t __regDACR         __ASM("cp15:0:c3:c0:0");
    __regDACR = dacr;
#endif
    __ISB();
}

/******************************** Cache and BTAC enable  ****************************************************/

/** \brief  Set SCTLR

    This function assigns the given value to the System Control Register.

    \param [in]    sctlr  System Control Register, value to set
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_SCTLR(uint32_t sctlr)
{
#if 1
	__ASM volatile ("mcr p15, 0, %0, c1, c0, 0" : : "r" (sctlr));
#else
    register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
    __regSCTLR = sctlr;
#endif
}

/** \brief  Get SCTLR

    This function returns the value of the System Control Register.

    \return               System Control Register value
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_SCTLR() {
#if 1
	register uint32_t __regSCTLR;
	__ASM volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (__regSCTLR));
#else
    register uint32_t __regSCTLR         __ASM("cp15:0:c1:c0:0");
#endif
    return(__regSCTLR);
}

/** \brief  Enable Caches

    Enable Caches
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_caches(void) {
    // Set I bit 12 to enable I Cache
    // Set C bit  2 to enable D Cache
    __set_SCTLR( __get_SCTLR() | (1 << 12) | (1 << 2));
}

/** \brief  Disable Caches

    Disable Caches
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_caches(void) {
    // Clear I bit 12 to disable I Cache
    // Clear C bit  2 to disable D Cache
    __set_SCTLR( __get_SCTLR() & ~(1 << 12) & ~(1 << 2));
    __ISB();
}

/** \brief  Enable BTAC

    Enable BTAC
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_btac(void) {
    // Set Z bit 11 to enable branch prediction
    __set_SCTLR( __get_SCTLR() | (1 << 11));
    __ISB();
}

/** \brief  Disable BTAC

    Disable BTAC
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_btac(void) {
    // Clear Z bit 11 to disable branch prediction
    __set_SCTLR( __get_SCTLR() & ~(1 << 11));
}


/** \brief  Enable MMU

    Enable MMU
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __enable_mmu(void) {
    // Set M bit 0 to enable the MMU
    // Set AFE bit to enable simplified access permissions model
    // Clear TRE bit to disable TEX remap and A bit to disable strict alignment fault checking
    __set_SCTLR( (__get_SCTLR() & ~(1 << 28) & ~(1 << 1)) | 1 | (1 << 29));
    __ISB();
}

/** \brief  Enable MMU

    Enable MMU
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __disable_mmu(void) {
    // Clear M bit 0 to disable the MMU
    __set_SCTLR( __get_SCTLR() & ~1);
    __ISB();
}

/******************************** TLB maintenance operations ************************************************/
/** \brief  Invalidate the whole tlb

    TLBIALL. Invalidate the whole tlb
 */

__attribute__( ( always_inline ) ) __STATIC_INLINE void __ca9u_inv_tlb_all(void) {
#if 1
	__ASM volatile ("mcr p15, 0, %0, c8, c7, 0" : : "r" (0));
#else
    register uint32_t __TLBIALL         __ASM("cp15:0:c8:c7:0");
    __TLBIALL = 0;
#endif
    __DSB();
    __ISB();
}

/******************************** BTB maintenance operations ************************************************/
/** \brief  Invalidate entire branch predictor array

    BPIALL. Branch Predictor Invalidate All.
 */

__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_inv_btac(void) {
#if 1
	__ASM volatile ("mcr p15, 0, %0, c7, c5, 6" : : "r" (0));
#else
    register uint32_t __BPIALL          __ASM("cp15:0:c7:c5:6");
    __BPIALL  = 0;
#endif
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new state
}


/******************************** L1 cache operations ******************************************************/

/** \brief  Invalidate the whole I$

    ICIALLU. Instruction Cache Invalidate All to PoU
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_inv_icache_all(void) {
#if 1
	__ASM volatile ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));
#else
    register uint32_t __ICIALLU         __ASM("cp15:0:c7:c5:0");
    __ICIALLU = 0;
#endif
    __DSB();     //ensure completion of the invalidation
    __ISB();     //ensure instruction fetch path sees new I cache state
}

/** \brief  Clean D$ by MVA

    DCCMVAC. Data cache clean by MVA to PoC
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_clean_dcache_mva(void *va) {
#if 1
    __ASM volatile ("mcr p15, 0, %0, c7, c10, 1" : : "r" ((uint32_t)va));
#else
    register uint32_t __DCCMVAC         __ASM("cp15:0:c7:c10:1");
    __DCCMVAC = (uint32_t)va;
#endif
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief  Invalidate D$ by MVA

    DCIMVAC. Data cache invalidate by MVA to PoC
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_inv_dcache_mva(void *va) {
#if 1
    __ASM volatile ("mcr p15, 0, %0, c7, c6, 1" : : "r" ((uint32_t)va));
#else
    register uint32_t __DCIMVAC         __ASM("cp15:0:c7:c6:1");
    __DCIMVAC = (uint32_t)va;
#endif
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief  Clean and Invalidate D$ by MVA

    DCCIMVAC. Data cache clean and invalidate by MVA to PoC
 */
__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_clean_inv_dcache_mva(void *va) {
#if 1
    __ASM volatile ("mcr p15, 0, %0, c7, c14, 1" : : "r" ((uint32_t)va));
#else
    register uint32_t __DCCIMVAC        __ASM("cp15:0:c7:c14:1");
    __DCCIMVAC = (uint32_t)va;
#endif
    __DMB();     //ensure the ordering of data cache maintenance operations and their effects
}

/** \brief
 * Generic mechanism for cleaning/invalidating the entire data or unified cache to the point of coherency.
 */

/** \brief  __v7_all_cache - helper function

 */

extern void __v7_all_cache(uint32_t op);


/** \brief  Invalidate the whole D$

    DCISW. Invalidate by Set/Way
 */

__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_inv_dcache_all(void) {
    __v7_all_cache(0);
}

/** \brief  Clean the whole D$

    DCCSW. Clean by Set/Way
 */

__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_clean_dcache_all(void) {
    __v7_all_cache(1);
}

/** \brief  Clean and invalidate the whole D$

    DCCISW. Clean and Invalidate by Set/Way
 */

__attribute__( ( always_inline ) ) __STATIC_INLINE void __v7_clean_inv_dcache_all(void) {
    __v7_all_cache(2);
}

#include "core_ca_mmu.h"

#elif (defined (__TASKING__)) /*--------------- TASKING Compiler -----------------*/

#error TASKING Compiler support not implemented for Cortex-A

#endif

/*@} end of CMSIS_Core_RegAccFunctions */


#endif /* __CORE_CAFUNC_H__ */
