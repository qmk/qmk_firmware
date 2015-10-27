/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RT_HAL_CM.H
 *      Purpose: Hardware Abstraction Layer for Cortex-A definitions
 *      Rev.:    21 Aug 2013
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2013 ARM Germany GmbH
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

/* Definitions */
#define INIT_CPSR_SYS   0x4000001F
#define INIT_CPSR_USER  0x40000010

#define CPSR_T_BIT      0x20
#define CPSR_I_BIT      0x80
#define CPSR_F_BIT      0x40

#define MODE_USR        0x10
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABT        0x17
#define MODE_UND        0x1B
#define MODE_SYS        0x1F

#define MAGIC_WORD      0xE25A2EA5

#include "core_ca9.h"

#if defined (__CC_ARM)          /* ARM Compiler */

#if ((__TARGET_ARCH_7_M || __TARGET_ARCH_7E_M || __TARGET_ARCH_7_A) && !defined(NO_EXCLUSIVE_ACCESS))
 #define __USE_EXCLUSIVE_ACCESS
#else
 #undef  __USE_EXCLUSIVE_ACCESS
#endif

#elif defined (__GNUC__)        /* GNU Compiler */

#undef  __USE_EXCLUSIVE_ACCESS

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
#define __TARGET_FPU_VFP 1
#else
#define __TARGET_FPU_VFP 0
#endif

#define __inline inline
#define __weak   __attribute__((weak))

#elif defined (__ICCARM__)      /* IAR Compiler */

#error IAR Compiler support not implemented for Cortex-A

#endif

static U8 priority = 0xff;

extern const U32 GICDistributor_BASE;
extern const U32 GICInterface_BASE;

/* GIC registers - Distributor */
#define GICD_ICDICER0   (*((volatile U32 *)(GICDistributor_BASE + 0x180))) /* - RW - Interrupt Clear-Enable Registers */
#define GICD_ICDISER0   (*((volatile U32 *)(GICDistributor_BASE + 0x100))) /* - RW - Interrupt Set-Enable Registers */
#define GICD_ICDIPR0    (*((volatile U32 *)(GICDistributor_BASE + 0x400))) /* - RW - Interrupt Priority Registers */
#define GICD_ICDSGIR    (*((volatile U32 *)(GICDistributor_BASE + 0xf00))) /* - RW - Interrupt Software Interrupt Register */
#define GICD_ICDICERx(irq)   *(volatile U32 *)(&GICD_ICDICER0 + irq/32)
#define GICD_ICDISERx(irq)   *(volatile U32 *)(&GICD_ICDISER0 + irq/32)

/* GIC register  - CPU Interface  */
#define GICI_ICCPMR     (*((volatile U32 *)(GICInterface_BASE + 0x004))) /* - RW - Interrupt Priority Mask Register */

#define SGI_PENDSV      0 /* SGI0 */
#define SGI_PENDSV_BIT  ((U32)(1 << (SGI_PENDSV & 0xf)))

//Increase priority filter to prevent timer and PendSV interrupts signaling. Guarantees that interrupts will not be forwarded.
#define OS_LOCK() int irq_dis = __disable_irq();\
                  priority = GICI_ICCPMR; \
                  GICI_ICCPMR = 0xff; \
                  GICI_ICCPMR = GICI_ICCPMR - 1; \
                  __DSB();\
                  if(!irq_dis) __enable_irq(); \

//Restore priority filter. Re-enable timer and PendSV signaling
#define OS_UNLOCK() __DSB(); \
                    GICI_ICCPMR = priority; \

#define OS_PEND_IRQ() GICD_ICDSGIR = 0x0010000 | SGI_PENDSV
#define OS_PEND(fl,p) if(p) OS_PEND_IRQ();
#define OS_UNPEND(fl)

/* HW initialization needs to be done in os_tick_init (void) -RTX_Conf_CM.c-
 * OS_X_INIT enables the IRQ n in the GIC */
#define OS_X_INIT(n) volatile char *reg; \
                     reg = (char *)(&GICD_ICDIPR0 + n / 4); \
                     reg += n % 4; \
                     *reg = (char)0xff; \
                     *reg = *reg - 1; \
                     GICD_ICDISERx(n) = (U32)(1 << n % 32);
#define OS_X_LOCK(n) OS_LOCK()
#define OS_X_UNLOCK(n) OS_UNLOCK()
#define OS_X_PEND_IRQ() OS_PEND_IRQ()
#define OS_X_PEND(fl,p) if(p) OS_X_PEND_IRQ();
#define OS_X_UNPEND(fl)


/* Functions */
#ifdef __USE_EXCLUSIVE_ACCESS
 #define rt_inc(p)     while(__strex((__ldrex(p)+1),p))
 #define rt_dec(p)     while(__strex((__ldrex(p)-1),p))
#else
 #define rt_inc(p)     { int irq_dis = __disable_irq();(*p)++;if(!irq_dis) __enable_irq(); }
 #define rt_dec(p)     { int irq_dis = __disable_irq();(*p)--;if(!irq_dis) __enable_irq(); }
#endif

__inline static U32 rt_inc_qi (U32 size, U8 *count, U8 *first) {
  U32 cnt,c2;
#ifdef __USE_EXCLUSIVE_ACCESS
  do {
    if ((cnt = __ldrex(count)) == size) {
      __clrex();
      return (cnt); }
  } while (__strex(cnt+1, count));
  do {
    c2 = (cnt = __ldrex(first)) + 1;
    if (c2 == size) c2 = 0;
  } while (__strex(c2, first));
#else
  int irq_dis;
  irq_dis = __disable_irq();
  if ((cnt = *count) < size) {
    *count = cnt+1;
    c2 = (cnt = *first) + 1;
    if (c2 == size) c2 = 0;
    *first = c2;
  }
  if(!irq_dis) __enable_irq ();
#endif
  return (cnt);
}

__inline static void rt_systick_init (void) {
  /* Cortex-A doesn't have a Systick. User needs to provide an alternative timer using RTX_Conf_CM configuration */
  /* HW initialization needs to be done in os_tick_init (void) -RTX_Conf_CM.c- */
}

__inline static void rt_svc_init (void) {
  /* Register pendSV - through SGI */
  volatile char *reg;

  reg = (char *)(&GICD_ICDIPR0 + SGI_PENDSV/4);
  reg += SGI_PENDSV % 4;
  /* Write 0xff to read priority level */
  *reg = (char)0xff;
  /* Read priority level and set the lowest possible*/
  *reg = *reg - 1;

  GICD_ICDISERx(SGI_PENDSV) = (U32)SGI_PENDSV_BIT;
}

extern void rt_set_PSP (U32 stack);
extern U32  rt_get_PSP (void);
extern void os_set_env (P_TCB p_TCB);
extern void *_alloc_box (void *box_mem);
extern int  _free_box (void *box_mem, void *box);

extern void rt_init_stack (P_TCB p_TCB, FUNCP task_body);
extern void rt_ret_val  (P_TCB p_TCB, U32 v0);
extern void rt_ret_val2 (P_TCB p_TCB, U32 v0, U32 v1);

extern void dbg_init (void);
extern void dbg_task_notify (P_TCB p_tcb, BOOL create);
extern void dbg_task_switch (U32 task_id);

#define DBG_INIT()
#define DBG_TASK_NOTIFY(p_tcb,create)
#define DBG_TASK_SWITCH(task_id)

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

