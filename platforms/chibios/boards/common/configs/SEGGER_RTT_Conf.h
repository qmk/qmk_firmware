/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2020 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Conf.h
Purpose : Implementation of SEGGER real-time transfer (RTT) which
          allows real-time communication on targets which support
          debugger memory accesses while the CPU is running.
Revision: $Rev: 24316 $

*/

#ifndef SEGGER_RTT_CONF_H
#define SEGGER_RTT_CONF_H

#ifdef __IAR_SYSTEMS_ICC__
  #include <intrinsics.h>
#endif

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

//
// Take in and set to correct values for Cortex-A systems with CPU cache
//
//#define SEGGER_RTT_CPU_CACHE_LINE_SIZE            (32)          // Largest cache line size (in bytes) in the current system
//#define SEGGER_RTT_UNCACHED_OFF                   (0xFB000000)  // Address alias where RTT CB and buffers can be accessed uncached
//
// Most common case:
// Up-channel 0: RTT
// Up-channel 1: SystemView
//
#ifndef   SEGGER_RTT_MAX_NUM_UP_BUFFERS
  #define SEGGER_RTT_MAX_NUM_UP_BUFFERS             (3)     // Max. number of up-buffers (T->H) available on this target    (Default: 3)
#endif
//
// Most common case:
// Down-channel 0: RTT
// Down-channel 1: SystemView
//
#ifndef   SEGGER_RTT_MAX_NUM_DOWN_BUFFERS
  #define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS           (3)     // Max. number of down-buffers (H->T) available on this target  (Default: 3)
#endif

#ifndef   BUFFER_SIZE_UP
  #define BUFFER_SIZE_UP                            (1024)  // Size of the buffer for terminal output of target, up to host (Default: 1k)
#endif

#ifndef   BUFFER_SIZE_DOWN
  #define BUFFER_SIZE_DOWN                          (16)    // Size of the buffer for terminal input to target from host (Usually keyboard input) (Default: 16)
#endif

#ifndef   SEGGER_RTT_PRINTF_BUFFER_SIZE
  #define SEGGER_RTT_PRINTF_BUFFER_SIZE             (64u)    // Size of buffer for RTT printf to bulk-send chars via RTT     (Default: 64)
#endif

#ifndef   SEGGER_RTT_MODE_DEFAULT
  #define SEGGER_RTT_MODE_DEFAULT                   SEGGER_RTT_MODE_NO_BLOCK_SKIP // Mode for pre-initialized terminal channel (buffer 0)
#endif

/*********************************************************************
*
*       RTT memcpy configuration
*
*       memcpy() is good for large amounts of data,
*       but the overhead is big for small amounts, which are usually stored via RTT.
*       With SEGGER_RTT_MEMCPY_USE_BYTELOOP a simple byte loop can be used instead.
*
*       SEGGER_RTT_MEMCPY() can be used to replace standard memcpy() in RTT functions.
*       This is may be required with memory access restrictions,
*       such as on Cortex-A devices with MMU.
*/
#ifndef   SEGGER_RTT_MEMCPY_USE_BYTELOOP
  #define SEGGER_RTT_MEMCPY_USE_BYTELOOP              0 // 0: Use memcpy/SEGGER_RTT_MEMCPY, 1: Use a simple byte-loop
#endif
//
// Example definition of SEGGER_RTT_MEMCPY to external memcpy with GCC toolchains and Cortex-A targets
//
//#if ((defined __SES_ARM) || (defined __CROSSWORKS_ARM) || (defined __GNUC__)) && (defined (__ARM_ARCH_7A__))
//  #define SEGGER_RTT_MEMCPY(pDest, pSrc, NumBytes)      SEGGER_memcpy((pDest), (pSrc), (NumBytes))
//#endif

//
// Target is not allowed to perform other RTT operations while string still has not been stored completely.
// Otherwise we would probably end up with a mixed string in the buffer.
// If using  RTT from within interrupts, multiple tasks or multi processors, define the SEGGER_RTT_LOCK() and SEGGER_RTT_UNLOCK() function here.
//
// SEGGER_RTT_MAX_INTERRUPT_PRIORITY can be used in the sample lock routines on Cortex-M3/4.
// Make sure to mask all interrupts which can send RTT data, i.e. generate SystemView events, or cause task switches.
// When high-priority interrupts must not be masked while sending RTT data, SEGGER_RTT_MAX_INTERRUPT_PRIORITY needs to be adjusted accordingly.
// (Higher priority = lower priority number)
// Default value for embOS: 128u
// Default configuration in FreeRTOS: configMAX_SYSCALL_INTERRUPT_PRIORITY: ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
// In case of doubt mask all interrupts: 1 << (8 - BASEPRI_PRIO_BITS) i.e. 1 << 5 when 3 bits are implemented in NVIC
// or define SEGGER_RTT_LOCK() to completely disable interrupts.
//
#ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
  #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY         (0x20)   // Interrupt priority to lock on SEGGER_RTT_LOCK on Cortex-M3/4 (Default: 0x20)
#endif

/*********************************************************************
*
*       RTT lock configuration for SEGGER Embedded Studio,
*       Rowley CrossStudio and GCC
*/
#if ((defined(__SES_ARM) || defined(__SES_RISCV) || defined(__CROSSWORKS_ARM) || defined(__GNUC__) || defined(__clang__)) && !defined (__CC_ARM) && !defined(WIN32))
  #if (defined(__ARM_ARCH_6M__) || defined(__ARM_ARCH_8M_BASE__))
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                    unsigned int _SEGGER_RTT__LockState;                                         \
                                  __asm volatile ("mrs   %0, primask  \n\t"                         \
                                                  "movs  r1, #1       \n\t"                         \
                                                  "msr   primask, r1  \n\t"                         \
                                                  : "=r" (_SEGGER_RTT__LockState)                                \
                                                  :                                                 \
                                                  : "r1", "cc"                                      \
                                                  );

    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   primask, %0  \n\t"                         \
                                                  :                                                 \
                                                  : "r" (_SEGGER_RTT__LockState)                                 \
                                                  :                                                 \
                                                  );                                                \
                                }
  #elif (defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_8M_MAIN__))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                    unsigned int _SEGGER_RTT__LockState;                                         \
                                  __asm volatile ("mrs   %0, basepri  \n\t"                         \
                                                  "mov   r1, %1       \n\t"                         \
                                                  "msr   basepri, r1  \n\t"                         \
                                                  : "=r" (_SEGGER_RTT__LockState)                                \
                                                  : "i"(SEGGER_RTT_MAX_INTERRUPT_PRIORITY)          \
                                                  : "r1", "cc"                                      \
                                                  );

    #define SEGGER_RTT_UNLOCK()   __asm volatile ("msr   basepri, %0  \n\t"                         \
                                                  :                                                 \
                                                  : "r" (_SEGGER_RTT__LockState)                                 \
                                                  :                                                 \
                                                  );                                                \
                                }

  #elif (defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__))
    #define SEGGER_RTT_LOCK() {                                                \
                                 unsigned int _SEGGER_RTT__LockState;                       \
                                 __asm volatile ("mrs r1, CPSR \n\t"           \
                                                 "mov %0, r1 \n\t"             \
                                                 "orr r1, r1, #0xC0 \n\t"      \
                                                 "msr CPSR_c, r1 \n\t"         \
                                                 : "=r" (_SEGGER_RTT__LockState)            \
                                                 :                             \
                                                 : "r1", "cc"                  \
                                                 );

    #define SEGGER_RTT_UNLOCK() __asm volatile ("mov r0, %0 \n\t"              \
                                                "mrs r1, CPSR \n\t"            \
                                                "bic r1, r1, #0xC0 \n\t"       \
                                                "and r0, r0, #0xC0 \n\t"       \
                                                "orr r1, r1, r0 \n\t"          \
                                                "msr CPSR_c, r1 \n\t"          \
                                                :                              \
                                                : "r" (_SEGGER_RTT__LockState)              \
                                                : "r0", "r1", "cc"             \
                                                );                             \
                            }
  #elif defined(__riscv) || defined(__riscv_xlen)
    #define SEGGER_RTT_LOCK()  {                                               \
                                 unsigned int _SEGGER_RTT__LockState;                       \
                                 __asm volatile ("csrr  %0, mstatus  \n\t"     \
                                                 "csrci mstatus, 8   \n\t"     \
                                                 "andi  %0, %0,  8   \n\t"     \
                                                 : "=r" (_SEGGER_RTT__LockState)            \
                                                 :                             \
                                                 :                             \
                                                );

  #define SEGGER_RTT_UNLOCK()    __asm volatile ("csrr  a1, mstatus  \n\t"     \
                                                 "or    %0, %0, a1   \n\t"     \
                                                 "csrs  mstatus, %0  \n\t"     \
                                                 :                             \
                                                 : "r"  (_SEGGER_RTT__LockState)            \
                                                 : "a1"                        \
                                                );                             \
                               }
  #else
    #define SEGGER_RTT_LOCK()
    #define SEGGER_RTT_UNLOCK()
  #endif
#endif

/*********************************************************************
*
*       RTT lock configuration for IAR EWARM
*/
#ifdef __ICCARM__
  #if (defined (__ARM6M__)          && (__CORE__ == __ARM6M__))             ||                      \
      (defined (__ARM8M_BASELINE__) && (__CORE__ == __ARM8M_BASELINE__))
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  _SEGGER_RTT__LockState = __get_PRIMASK();                                      \
                                  __set_PRIMASK(1);

    #define SEGGER_RTT_UNLOCK()   __set_PRIMASK(_SEGGER_RTT__LockState);                                         \
                                }
  #elif (defined (__ARM7EM__)         && (__CORE__ == __ARM7EM__))          ||                      \
        (defined (__ARM7M__)          && (__CORE__ == __ARM7M__))           ||                      \
        (defined (__ARM8M_MAINLINE__) && (__CORE__ == __ARM8M_MAINLINE__))  ||                      \
        (defined (__ARM8M_MAINLINE__) && (__CORE__ == __ARM8M_MAINLINE__))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  _SEGGER_RTT__LockState = __get_BASEPRI();                                      \
                                  __set_BASEPRI(SEGGER_RTT_MAX_INTERRUPT_PRIORITY);

    #define SEGGER_RTT_UNLOCK()   __set_BASEPRI(_SEGGER_RTT__LockState);                                         \
                                }
  #elif (defined (__ARM7A__) && (__CORE__ == __ARM7A__))                    ||                      \
        (defined (__ARM7R__) && (__CORE__ == __ARM7R__))
    #define SEGGER_RTT_LOCK() {                                                                     \
                                 unsigned int _SEGGER_RTT__LockState;                                            \
                                 __asm volatile ("mrs r1, CPSR \n\t"                                \
                                                 "mov %0, r1 \n\t"                                  \
                                                 "orr r1, r1, #0xC0 \n\t"                           \
                                                 "msr CPSR_c, r1 \n\t"                              \
                                                 : "=r" (_SEGGER_RTT__LockState)                                 \
                                                 :                                                  \
                                                 : "r1", "cc"                                       \
                                                 );

    #define SEGGER_RTT_UNLOCK() __asm volatile ("mov r0, %0 \n\t"                                   \
                                                "mrs r1, CPSR \n\t"                                 \
                                                "bic r1, r1, #0xC0 \n\t"                            \
                                                "and r0, r0, #0xC0 \n\t"                            \
                                                "orr r1, r1, r0 \n\t"                               \
                                                "msr CPSR_c, r1 \n\t"                               \
                                                :                                                   \
                                                : "r" (_SEGGER_RTT__LockState)                                   \
                                                : "r0", "r1", "cc"                                  \
                                                );                                                  \
                            }
  #endif
#endif

/*********************************************************************
*
*       RTT lock configuration for IAR RX
*/
#ifdef __ICCRX__
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                unsigned long _SEGGER_RTT__LockState;                                            \
                                _SEGGER_RTT__LockState = __get_interrupt_state();                                \
                                __disable_interrupt();

  #define SEGGER_RTT_UNLOCK()   __set_interrupt_state(_SEGGER_RTT__LockState);                                   \
                              }
#endif

/*********************************************************************
*
*       RTT lock configuration for IAR RL78
*/
#ifdef __ICCRL78__
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                __istate_t _SEGGER_RTT__LockState;                                               \
                                _SEGGER_RTT__LockState = __get_interrupt_state();                                \
                                __disable_interrupt();

  #define SEGGER_RTT_UNLOCK()   __set_interrupt_state(_SEGGER_RTT__LockState);                                   \
                              }
#endif

/*********************************************************************
*
*       RTT lock configuration for KEIL ARM
*/
#ifdef __CC_ARM
  #if (defined __TARGET_ARCH_6S_M)
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  register unsigned char _SEGGER_RTT__PRIMASK __asm( "primask");                 \
                                  _SEGGER_RTT__LockState = _SEGGER_RTT__PRIMASK;                                              \
                                  _SEGGER_RTT__PRIMASK = 1u;                                                     \
                                  __schedule_barrier();

    #define SEGGER_RTT_UNLOCK()   _SEGGER_RTT__PRIMASK = _SEGGER_RTT__LockState;                                              \
                                  __schedule_barrier();                                             \
                                }
  #elif (defined(__TARGET_ARCH_7_M) || defined(__TARGET_ARCH_7E_M))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  register unsigned char BASEPRI __asm( "basepri");                 \
                                  _SEGGER_RTT__LockState = BASEPRI;                                              \
                                  BASEPRI = SEGGER_RTT_MAX_INTERRUPT_PRIORITY;                      \
                                  __schedule_barrier();

    #define SEGGER_RTT_UNLOCK()   BASEPRI = _SEGGER_RTT__LockState;                                              \
                                  __schedule_barrier();                                             \
                                }
  #endif
#endif

/*********************************************************************
*
*       RTT lock configuration for TI ARM
*/
#ifdef __TI_ARM__
  #if defined (__TI_ARM_V6M0__)
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  _SEGGER_RTT__LockState = __get_PRIMASK();                                      \
                                  __set_PRIMASK(1);

    #define SEGGER_RTT_UNLOCK()   __set_PRIMASK(_SEGGER_RTT__LockState);                                         \
                                }
  #elif (defined (__TI_ARM_V7M3__) || defined (__TI_ARM_V7M4__))
    #ifndef   SEGGER_RTT_MAX_INTERRUPT_PRIORITY
      #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY   (0x20)
    #endif
    #define SEGGER_RTT_LOCK()   {                                                                   \
                                  unsigned int _SEGGER_RTT__LockState;                                           \
                                  _SEGGER_RTT__LockState = _set_interrupt_priority(SEGGER_RTT_MAX_INTERRUPT_PRIORITY);

    #define SEGGER_RTT_UNLOCK()   _set_interrupt_priority(_SEGGER_RTT__LockState);                               \
                                }
  #endif
#endif

/*********************************************************************
*
*       RTT lock configuration for CCRX
*/
#ifdef __RX
  #include <machine.h>
  #define SEGGER_RTT_LOCK()   {                                                                     \
                                unsigned long _SEGGER_RTT__LockState;                                            \
                                _SEGGER_RTT__LockState = get_psw() & 0x010000;                                   \
                                clrpsw_i();

  #define SEGGER_RTT_UNLOCK()   set_psw(get_psw() | _SEGGER_RTT__LockState);                                     \
                              }
#endif

/*********************************************************************
*
*       RTT lock configuration for embOS Simulation on Windows
*       (Can also be used for generic RTT locking with embOS)
*/
#if defined(WIN32) || defined(SEGGER_RTT_LOCK_EMBOS)

void OS_SIM_EnterCriticalSection(void);
void OS_SIM_LeaveCriticalSection(void);

#define SEGGER_RTT_LOCK()       {                                                                   \
                                  OS_SIM_EnterCriticalSection();

#define SEGGER_RTT_UNLOCK()       OS_SIM_LeaveCriticalSection();                                    \
                                }
#endif

/*********************************************************************
*
*       RTT lock configuration fallback
*/
#ifndef   SEGGER_RTT_LOCK
  #define SEGGER_RTT_LOCK()                // Lock RTT (nestable)   (i.e. disable interrupts)
#endif

#ifndef   SEGGER_RTT_UNLOCK
  #define SEGGER_RTT_UNLOCK()              // Unlock RTT (nestable) (i.e. enable previous interrupt lock state)
#endif

#endif
/*************************** End of file ****************************/
