/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    HAL_CA.C
 *      Purpose: Hardware Abstraction Layer for Cortex-A
 *      Rev.:
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 2012 ARM Limited
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

#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_HAL_CA.h"

/*--------------------------- os_init_context -------------------------------*/

void rt_init_stack (P_TCB p_TCB, FUNCP task_body) {
  /* Prepare TCB and saved context for a first time start of a task. */
  U32 *stk,i,size;

  /* Prepare a complete interrupt frame for first task start */
  size = p_TCB->priv_stack >> 2;
  if (size == 0) {
    size = (U16)os_stackinfo >> 2;
  }
  /* Write to the top of stack. */
  stk = &p_TCB->stack[size];

  /* Auto correct to 8-byte ARM stack alignment. */
  if ((U32)stk & 0x04) {
    stk--;
  }

  stk -= 16;

  /* Initial PC and default CPSR */
  stk[14] = (U32)task_body;
  /* Task run mode is inherited from the startup file. */
  /*  (non-privileged USER or privileged SYSTEM mode)  */
  stk[15] = (os_flags & 1) ? INIT_CPSR_SYS : INIT_CPSR_USER;
  /* Set T-bit if task function in Thumb mode. */
  if ((U32)task_body & 1) {
    stk[15] |= CPSR_T_BIT;
  }
  /* Assign a void pointer to R0. */
  stk[8]  = (U32)p_TCB->msg;
  /* Clear R1-R12,LR registers. */
  for (i = 0; i < 8; i++) {
    stk[i] = 0;
  }
  for (i = 9; i < 14; i++) {
    stk[i] = 0;
  }

  /* Initial Task stack pointer. */
  p_TCB->tsk_stack = (U32)stk;

  /* Task entry point. */
  p_TCB->ptask = task_body;

  /* Set a magic word for checking of stack overflow. */
  p_TCB->stack[0] = MAGIC_WORD;
}


/*--------------------------- rt_ret_val ----------------------------------*/

static __inline U32 *rt_ret_regs (P_TCB p_TCB) {
  /* Get pointer to task return value registers (R0..R3) in Stack */
#if (__TARGET_FPU_VFP)
  if (p_TCB->stack_frame & 0x2) {
    /* Extended Stack Frame: S0-31,FPSCR,Reserved,R4-R11,R0-R3,R12,LR,PC,xPSR */
    return (U32 *)(p_TCB->tsk_stack + 8*4 + 34*4);
  } else {
    /* Basic Stack Frame: R4-R11,R0-R3,R12,LR,PC,xPSR */
    return (U32 *)(p_TCB->tsk_stack + 8*4);
  }
#else
  /* Stack Frame: R4-R11,R0-R3,R12,LR,PC,xPSR */
  return (U32 *)(p_TCB->tsk_stack + 8*4);
#endif
}

void rt_ret_val (P_TCB p_TCB, U32 v0) {
  U32 *ret;

  ret = rt_ret_regs(p_TCB);
  ret[0] = v0;
}

void rt_ret_val2(P_TCB p_TCB, U32 v0, U32 v1) {
  U32 *ret;

  ret = rt_ret_regs(p_TCB);
  ret[0] = v0;
  ret[1] = v1;
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
