/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */
#ifndef TUSB_VERIFY_H_
#define TUSB_VERIFY_H_

#include <stdbool.h>
#include <stdint.h>
#include "tusb_option.h"
#include "tusb_compiler.h"

/*------------------------------------------------------------------*/
/* This file use an advanced macro technique to mimic the default parameter
 * as C++ for the sake of code simplicity. Beware of a headache macro
 * manipulation that you are told to stay away.
 *
 * This contains macros for both VERIFY and ASSERT:
 *
 *   VERIFY: Used when there is an error condition which is not the
 *           fault of the MCU. For example, bounds checking on data
 *           sent to the micro over USB should use this function.
 *           Another example is checking for buffer overflows, where
 *           returning from the active function causes a NAK.
 *
 *   ASSERT: Used for error conditions that are caused by MCU firmware
 *           bugs. This is used to discover bugs in the code more
 *           quickly. One example would be adding assertions in library
 *           function calls to confirm a function's (untainted)
 *           parameters are valid.
 *
 * The difference in behavior is that ASSERT triggers a breakpoint while
 * verify does not.
 *
 *   #define TU_VERIFY(cond)                  if(cond) return false;
 *   #define TU_VERIFY(cond,ret)              if(cond) return ret;
 *
 *   #define TU_VERIFY_HDLR(cond,handler)     if(cond) {handler; return false;}
 *   #define TU_VERIFY_HDLR(cond,ret,handler) if(cond) {handler; return ret;}
 *
 *   #define TU_ASSERT(cond)                  if(cond) {_MESS_FAILED(); TU_BREAKPOINT(), return false;}
 *   #define TU_ASSERT(cond,ret)              if(cond) {_MESS_FAILED(); TU_BREAKPOINT(), return ret;}
 *
 *------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// TU_VERIFY Helper
//--------------------------------------------------------------------+

#if CFG_TUSB_DEBUG
  #include <stdio.h>
  #define _MESS_FAILED()    tu_printf("%s %d: ASSERT FAILED\r\n", __func__, __LINE__)
#else
  #define _MESS_FAILED() do {} while (0)
#endif

// Halt CPU (breakpoint) when hitting error, only apply for Cortex M3, M4, M7, M33
#if defined(__ARM_ARCH_7M__) || defined (__ARM_ARCH_7EM__) || defined(__ARM_ARCH_8M_MAIN__)
  #define TU_BREAKPOINT() do                                                                                \
  {                                                                                                         \
    volatile uint32_t* ARM_CM_DHCSR =  ((volatile uint32_t*) 0xE000EDF0UL); /* Cortex M CoreDebug->DHCSR */ \
    if ( (*ARM_CM_DHCSR) & 1UL ) __asm("BKPT #0\n"); /* Only halt mcu if debugger is attached */            \
  } while(0)

#elif defined(__riscv)
  #define TU_BREAKPOINT() do { __asm("ebreak\n"); } while(0)

#elif defined(_mips)
  #define TU_BREAKPOINT() do { __asm("sdbbp 0"); } while (0)

#else
  #define TU_BREAKPOINT() do {} while (0)
#endif

/*------------------------------------------------------------------*/
/* Macro Generator
 *------------------------------------------------------------------*/

// Helper to implement optional parameter for TU_VERIFY Macro family
#define _GET_3RD_ARG(arg1, arg2, arg3, ...)        arg3
#define _GET_4TH_ARG(arg1, arg2, arg3, arg4, ...)  arg4

/*------------- Generator for TU_VERIFY and TU_VERIFY_HDLR -------------*/
#define TU_VERIFY_DEFINE(_cond, _handler, _ret)  do            \
{                                                              \
  if ( !(_cond) ) { _handler; return _ret;  }                  \
} while(0)

/*------------------------------------------------------------------*/
/* TU_VERIFY
 * - TU_VERIFY_1ARGS : return false if failed
 * - TU_VERIFY_2ARGS : return provided value if failed
 *------------------------------------------------------------------*/
#define TU_VERIFY_1ARGS(_cond)                         TU_VERIFY_DEFINE(_cond, , false)
#define TU_VERIFY_2ARGS(_cond, _ret)                   TU_VERIFY_DEFINE(_cond, , _ret)

#define TU_VERIFY(...)                   _GET_3RD_ARG(__VA_ARGS__, TU_VERIFY_2ARGS, TU_VERIFY_1ARGS, UNUSED)(__VA_ARGS__)


/*------------------------------------------------------------------*/
/* TU_VERIFY WITH HANDLER
 * - TU_VERIFY_HDLR_2ARGS : execute handler, return false if failed
 * - TU_VERIFY_HDLR_3ARGS : execute handler, return provided error if failed
 *------------------------------------------------------------------*/
#define TU_VERIFY_HDLR_2ARGS(_cond, _handler)           TU_VERIFY_DEFINE(_cond, _handler, false)
#define TU_VERIFY_HDLR_3ARGS(_cond, _handler, _ret)     TU_VERIFY_DEFINE(_cond, _handler, _ret)

#define TU_VERIFY_HDLR(...)              _GET_4TH_ARG(__VA_ARGS__, TU_VERIFY_HDLR_3ARGS, TU_VERIFY_HDLR_2ARGS,UNUSED)(__VA_ARGS__)

/*------------------------------------------------------------------*/
/* ASSERT
 * basically TU_VERIFY with TU_BREAKPOINT() as handler
 * - 1 arg : return false if failed
 * - 2 arg : return error if failed
 *------------------------------------------------------------------*/
#define ASSERT_1ARGS(_cond)            TU_VERIFY_DEFINE(_cond, _MESS_FAILED(); TU_BREAKPOINT(), false)
#define ASSERT_2ARGS(_cond, _ret)      TU_VERIFY_DEFINE(_cond, _MESS_FAILED(); TU_BREAKPOINT(), _ret)

#ifndef TU_ASSERT
#define TU_ASSERT(...)             _GET_3RD_ARG(__VA_ARGS__, ASSERT_2ARGS, ASSERT_1ARGS,UNUSED)(__VA_ARGS__)
#endif

/*------------------------------------------------------------------*/
/* ASSERT HDLR
 *------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif /* TUSB_VERIFY_H_ */
