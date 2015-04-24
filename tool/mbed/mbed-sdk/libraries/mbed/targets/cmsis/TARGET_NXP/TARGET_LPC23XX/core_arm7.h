/* mbed Microcontroller Library
 * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
 *
 * ARM7 version of CMSIS-like functionality - not advised for use outside mbed!
 * based on core_cm3.h, V1.20
 */

#ifndef __ARM7_CORE_H__
#define __ARM7_CORE_H__

#include "vector_defns.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define __CM3_CMSIS_VERSION_MAIN  (0x01)                                                       /*!< [31:16] CMSIS HAL main version */
#define __CM3_CMSIS_VERSION_SUB   (0x20)                                                       /*!< [15:0]  CMSIS HAL sub version  */
#define __CM3_CMSIS_VERSION       ((__CM3_CMSIS_VERSION_MAIN << 16) | __CM3_CMSIS_VERSION_SUB) /*!< CMSIS HAL version number       */

#define __CORTEX_M                (0x03)                                                       /*!< Cortex core                    */

/**
 *  Lint configuration \n
 *  ----------------------- \n
 *
 *  The following Lint messages will be suppressed and not shown: \n
 *  \n
 *    --- Error 10: --- \n
 *    register uint32_t __regBasePri         __asm("basepri"); \n
 *    Error 10: Expecting ';' \n
 *     \n
 *    --- Error 530: --- \n
 *    return(__regBasePri); \n
 *    Warning 530: Symbol '__regBasePri' (line 264) not initialized \n
 *     \n
 *    --- Error 550: --- \n
 *      __regBasePri = (basePri & 0x1ff); \n
 *    } \n
 *    Warning 550: Symbol '__regBasePri' (line 271) not accessed \n
 *     \n
 *    --- Error 754: --- \n
 *    uint32_t RESERVED0[24]; \n
 *    Info 754: local structure member '<some, not used in the HAL>' (line 109, file ./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 750: --- \n
 *    #define __CM3_CORE_H__ \n
 *    Info 750: local macro '__CM3_CORE_H__' (line 43, file./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 528: --- \n
 *    static __INLINE void NVIC_DisableIRQ(uint32_t IRQn) \n
 *    Warning 528: Symbol 'NVIC_DisableIRQ(unsigned int)' (line 419, file ./cm3_core.h) not referenced \n
 *     \n
 *    --- Error 751: --- \n
 *    } InterruptType_Type; \n
 *    Info 751: local typedef 'InterruptType_Type' (line 170, file ./cm3_core.h) not referenced \n
 * \n
 * \n
 *    Note:  To re-enable a Message, insert a space before 'lint' * \n
 *
 */

/*lint -save */
/*lint -e10  */
/*lint -e530 */
/*lint -e550 */
/*lint -e754 */
/*lint -e750 */
/*lint -e528 */
/*lint -e751 */

#include <stdint.h>                           /* Include standard types */

#if defined ( __CC_ARM   )
/**
 * @brief  Return the Main Stack Pointer (current ARM7 stack)
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
extern uint32_t __get_MSP(void);
#endif


#if defined (__ICCARM__)
  #include <intrinsics.h>                     /* IAR Intrinsics   */
#endif


#ifndef __NVIC_PRIO_BITS
  #define __NVIC_PRIO_BITS    4               /*!< standard definition for NVIC Priority Bits */
#endif

typedef struct
{
  uint32_t IRQStatus;
  uint32_t FIQStatus;
  uint32_t RawIntr;
  uint32_t IntSelect;
  uint32_t IntEnable;
  uint32_t IntEnClr;
  uint32_t SoftInt;
  uint32_t SoftIntClr;
  uint32_t Protection;
  uint32_t SWPriorityMask;
  uint32_t RESERVED0[54];
  uint32_t VectAddr[32];
  uint32_t RESERVED1[32];
  uint32_t VectPriority[32];
  uint32_t RESERVED2[800];
  uint32_t Address;
} NVIC_TypeDef;

#define NVIC_BASE              (0xFFFFF000)
#define NVIC                   ((      NVIC_TypeDef *)       NVIC_BASE)



/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */

#ifdef __cplusplus
#define     __I     volatile                  /*!< defines 'read only' permissions      */
#else
#define     __I     volatile const            /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */





#if defined ( __CC_ARM   )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                       /*!< asm keyword for IAR Compiler           */
  #define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */

#elif defined   (  __GNUC__  )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

#elif defined   (  __TASKING__  )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler       */

#endif


/* ###################  Compiler specific Intrinsics  ########################### */

#if defined ( __CC_ARM   ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq

#define __NOP                             __nop
//#define __WFI                             __wfi
//#define __WFE                             __wfe
//#define __SEV                             __sev
//#define __ISB()                           __isb(0)
//#define __DSB()                           __dsb(0)
//#define __DMB()                           __dmb(0)
//#define __REV                             __rev
//#define __RBIT                            __rbit
#define __LDREXB(ptr)                     ((unsigned char ) __ldrex(ptr))
#define __LDREXH(ptr)                     ((unsigned short) __ldrex(ptr))
#define __LDREXW(ptr)                     ((unsigned int  ) __ldrex(ptr))
#define __STREXB(value, ptr)              __strex(value, ptr)
#define __STREXH(value, ptr)              __strex(value, ptr)
#define __STREXW(value, ptr)              __strex(value, ptr)

#define __disable_irq()         unsigned tmp_IntEnable = LPC_VIC->IntEnable; \
                                LPC_VIC->IntEnClr = 0xffffffff

#define __enable_irq()          LPC_VIC->IntEnable = tmp_IntEnable

#elif (defined (__ICCARM__)) /*------------------ ICC Compiler -------------------*/

#define __enable_irq                              __enable_interrupt        /*!< global Interrupt enable */
#define __disable_irq                             __disable_interrupt       /*!< global Interrupt disable */
#define __NOP                                     __no_operation()          /*!< no operation intrinsic in IAR Compiler */ 

#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/

static __INLINE void __enable_irq() {
    unsigned long temp;
    __asm__ __volatile__("mrs %0, cpsr\n"
                         "bic %0, %0, #0x80\n"
                         "msr cpsr_c, %0"
                         : "=r" (temp)
                         :
                         : "memory");
}

static __INLINE void __disable_irq() {
    unsigned long old,temp;
    __asm__ __volatile__("mrs %0, cpsr\n"
                         "orr %1, %0, #0xc0\n"
                         "msr cpsr_c, %1"
                         : "=r" (old), "=r" (temp)
                         :
                         : "memory");
    // return (old & 0x80) == 0;
}

static __INLINE void __NOP()                      { __ASM volatile ("nop"); }

#elif (defined (__TASKING__)) /*------------------ TASKING Compiler ---------------------*/
/* TASKING carm specific functions */

/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all instrinsics,
 * Including the CMSIS ones.
 */

#endif


/**
 * @brief  Enable Interrupt in NVIC Interrupt Controller
 *
 * @param  IRQn_Type IRQn specifies the interrupt number
 * @return none 
 *
 * Enable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
 NVIC->IntEnable = 1 << (uint32_t)IRQn;
}


/**
 * @brief  Disable the interrupt line for external interrupt specified
 * 
 * @param  IRQn_Type IRQn is the positive number of the external interrupt
 * @return none
 * 
 * Disable a device specific interupt in the NVIC interrupt controller.
 * The interrupt number cannot be a negative value.
 */
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
 NVIC->IntEnClr = 1 << (uint32_t)IRQn;
}

static __INLINE uint32_t __get_IPSR(void)
{
 unsigned i;

 for(i = 0; i < 32; i ++)
   if(NVIC->Address == NVIC->VectAddr[i])
     return i;
 return 1; // 1 is an invalid entry in the interrupt table on LPC2368
}

#ifdef __cplusplus
}
#endif

#endif /* __ARM7_CORE_H__ */

/*lint -restore */
