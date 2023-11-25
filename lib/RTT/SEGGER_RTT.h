/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2019 SEGGER Microcontroller GmbH             *
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
File    : SEGGER_RTT.h
Purpose : Implementation of SEGGER real-time transfer which allows
          real-time communication on targets which support debugger
          memory accesses while the CPU is running.
Revision: $Rev: 25842 $
----------------------------------------------------------------------
*/

#ifndef SEGGER_RTT_H
#define SEGGER_RTT_H

#include "SEGGER_RTT_Conf.h"

/*********************************************************************
*
*       Defines, defaults
*
**********************************************************************
*/

#ifndef RTT_USE_ASM
  //
  // Some cores support out-of-order memory accesses (reordering of memory accesses in the core)
  // For such cores, we need to define a memory barrier to guarantee the order of certain accesses to the RTT ring buffers.
  // Needed for:
  //   Cortex-M7 (ARMv7-M)
  //   Cortex-M23 (ARM-v8M)
  //   Cortex-M33 (ARM-v8M)
  //   Cortex-A/R (ARM-v7A/R)
  //
  // We do not explicitly check for "Embedded Studio" as the compiler in use determines what we support.
  // You can use an external toolchain like IAR inside ES. So there is no point in checking for "Embedded Studio"
  //
  #if (defined __CROSSWORKS_ARM)                  // Rowley Crossworks
    #define _CC_HAS_RTT_ASM_SUPPORT 1
    #if (defined __ARM_ARCH_7M__)                 // Cortex-M3
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
    #elif (defined __ARM_ARCH_7EM__)              // Cortex-M4/M7
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_BASE__)          // Cortex-M23
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_MAIN__)          // Cortex-M33
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined(__ARM_ARCH_8_1M_MAIN__))       // Cortex-M85
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #else
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
    #endif
  #elif (defined __ARMCC_VERSION)
    //
    // ARM compiler
    // ARM compiler V6.0 and later is clang based.
    // Our ASM part is compatible to clang.
    //
    #if (__ARMCC_VERSION >= 6000000)
      #define _CC_HAS_RTT_ASM_SUPPORT 1
    #else
      #define _CC_HAS_RTT_ASM_SUPPORT 0
    #endif
    #if (defined __ARM_ARCH_6M__)                 // Cortex-M0 / M1
      #define _CORE_HAS_RTT_ASM_SUPPORT 0         // No ASM support for this architecture
    #elif (defined __ARM_ARCH_7M__)               // Cortex-M3
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
    #elif (defined __ARM_ARCH_7EM__)              // Cortex-M4/M7
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_BASE__)          // Cortex-M23
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_MAIN__)          // Cortex-M33
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8_1M_MAIN__)        // Cortex-M85
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif ((defined __ARM_ARCH_7A__) || (defined __ARM_ARCH_7R__))  // Cortex-A/R 32-bit ARMv7-A/R
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #else
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
    #endif
  #elif ((defined __GNUC__) || (defined __clang__))
    //
    // GCC / Clang
    //
    #define _CC_HAS_RTT_ASM_SUPPORT 1
    // ARM 7/9: __ARM_ARCH_5__ / __ARM_ARCH_5E__ / __ARM_ARCH_5T__ / __ARM_ARCH_5T__ / __ARM_ARCH_5TE__
    #if (defined __ARM_ARCH_7M__)                 // Cortex-M3
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
    #elif (defined __ARM_ARCH_7EM__)              // Cortex-M4/M7
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1         // Only Cortex-M7 needs a DMB but we cannot distinguish M4 and M7 here...
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_BASE__)          // Cortex-M23
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8M_MAIN__)          // Cortex-M33
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif (defined __ARM_ARCH_8_1M_MAIN__)        // Cortex-M85
      #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #elif ((defined __ARM_ARCH_7A__) || (defined __ARM_ARCH_7R__))  // Cortex-A/R 32-bit ARMv7-A/R
      #define _CORE_NEEDS_DMB           1
      #define RTT__DMB() __asm volatile ("dmb\n" : : :);
    #else
      #define _CORE_HAS_RTT_ASM_SUPPORT 0
    #endif
  #elif ((defined __IASMARM__) || (defined __ICCARM__))
    //
    // IAR assembler/compiler
    //
    #define _CC_HAS_RTT_ASM_SUPPORT 1
    #if (__VER__ < 6300000)
      #define VOLATILE
    #else
      #define VOLATILE volatile
    #endif
    #if (defined __ARM7M__)                            // Needed for old versions that do not know the define yet
      #if (__CORE__ == __ARM7M__)                      // Cortex-M3
        #define _CORE_HAS_RTT_ASM_SUPPORT 1
      #endif
    #endif
    #if (defined __ARM7EM__)
      #if (__CORE__ == __ARM7EM__)                     // Cortex-M4/M7
        #define _CORE_HAS_RTT_ASM_SUPPORT 1
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
    #if (defined __ARM8M_BASELINE__)
      #if (__CORE__ == __ARM8M_BASELINE__)             // Cortex-M23
        #define _CORE_HAS_RTT_ASM_SUPPORT 0
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
    #if (defined __ARM8M_MAINLINE__)
      #if (__CORE__ == __ARM8M_MAINLINE__)             // Cortex-M33
        #define _CORE_HAS_RTT_ASM_SUPPORT 1
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
    #if (defined __ARM8EM_MAINLINE__)
      #if (__CORE__ == __ARM8EM_MAINLINE__)            // Cortex-???
        #define _CORE_HAS_RTT_ASM_SUPPORT 1
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
    #if (defined __ARM7A__)
      #if (__CORE__ == __ARM7A__)                      // Cortex-A 32-bit ARMv7-A
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
    #if (defined __ARM7R__)
      #if (__CORE__ == __ARM7R__)                      // Cortex-R 32-bit ARMv7-R
        #define _CORE_NEEDS_DMB 1
        #define RTT__DMB() asm VOLATILE ("DMB");
      #endif
    #endif
// TBD: __ARM8A__ => Cortex-A 64-bit ARMv8-A
// TBD: __ARM8R__ => Cortex-R 64-bit ARMv8-R
  #else
    //
    // Other compilers
    //
    #define _CC_HAS_RTT_ASM_SUPPORT   0
    #define _CORE_HAS_RTT_ASM_SUPPORT 0
  #endif
  //
  // If IDE and core support the ASM version, enable ASM version by default
  //
  #ifndef _CORE_HAS_RTT_ASM_SUPPORT
    #define _CORE_HAS_RTT_ASM_SUPPORT 0              // Default for unknown cores
  #endif
  #if (_CC_HAS_RTT_ASM_SUPPORT && _CORE_HAS_RTT_ASM_SUPPORT)
    #define RTT_USE_ASM                           (1)
  #else
    #define RTT_USE_ASM                           (0)
  #endif
#endif

#ifndef _CORE_NEEDS_DMB
  #define _CORE_NEEDS_DMB 0
#endif

#ifndef RTT__DMB
  #if _CORE_NEEDS_DMB
    #error "Don't know how to place inline assembly for DMB"
  #else
    #define RTT__DMB()
  #endif
#endif

#ifndef SEGGER_RTT_CPU_CACHE_LINE_SIZE
  #define SEGGER_RTT_CPU_CACHE_LINE_SIZE (0)   // On most target systems where RTT is used, we do not have a CPU cache, therefore 0 is a good default here
#endif

#ifndef SEGGER_RTT_UNCACHED_OFF
  #if SEGGER_RTT_CPU_CACHE_LINE_SIZE
    #error "SEGGER_RTT_UNCACHED_OFF must be defined when setting SEGGER_RTT_CPU_CACHE_LINE_SIZE != 0"
  #else
    #define SEGGER_RTT_UNCACHED_OFF (0)
  #endif
#endif
#if RTT_USE_ASM
  #if SEGGER_RTT_CPU_CACHE_LINE_SIZE
    #error "RTT_USE_ASM is not available if SEGGER_RTT_CPU_CACHE_LINE_SIZE != 0"
  #endif
#endif

#ifndef SEGGER_RTT_ASM  // defined when SEGGER_RTT.h is included from assembly file
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

//
// Determine how much we must pad the control block to make it a multiple of a cache line in size
// Assuming: U8 = 1B
//           U16 = 2B
//           U32 = 4B
//           U8/U16/U32* = 4B
//
#if SEGGER_RTT_CPU_CACHE_LINE_SIZE    // Avoid division by zero in case we do not have any cache
  #define SEGGER_RTT__ROUND_UP_2_CACHE_LINE_SIZE(NumBytes) (((NumBytes + SEGGER_RTT_CPU_CACHE_LINE_SIZE - 1) / SEGGER_RTT_CPU_CACHE_LINE_SIZE) * SEGGER_RTT_CPU_CACHE_LINE_SIZE)
#else
  #define SEGGER_RTT__ROUND_UP_2_CACHE_LINE_SIZE(NumBytes) (NumBytes)
#endif
#define SEGGER_RTT__CB_SIZE                              (16 + 4 + 4 + (SEGGER_RTT_MAX_NUM_UP_BUFFERS * 24) + (SEGGER_RTT_MAX_NUM_DOWN_BUFFERS * 24))
#define SEGGER_RTT__CB_PADDING                           (SEGGER_RTT__ROUND_UP_2_CACHE_LINE_SIZE(SEGGER_RTT__CB_SIZE) - SEGGER_RTT__CB_SIZE)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

//
// Description for a circular buffer (also called "ring buffer")
// which is used as up-buffer (T->H)
//
typedef struct {
  const     char*    sName;         // Optional name. Standard names so far are: "Terminal", "SysView", "J-Scope_t4i4"
            char*    pBuffer;       // Pointer to start of buffer
            unsigned SizeOfBuffer;  // Buffer size in bytes. Note that one byte is lost, as this implementation does not fill up the buffer in order to avoid the problem of being unable to distinguish between full and empty.
            unsigned WrOff;         // Position of next item to be written by either target.
  volatile  unsigned RdOff;         // Position of next item to be read by host. Must be volatile since it may be modified by host.
            unsigned Flags;         // Contains configuration flags. Flags[31:24] are used for validity check and must be zero. Flags[23:2] are reserved for future use. Flags[1:0] = RTT operating mode.
} SEGGER_RTT_BUFFER_UP;

//
// Description for a circular buffer (also called "ring buffer")
// which is used as down-buffer (H->T)
//
typedef struct {
  const     char*    sName;         // Optional name. Standard names so far are: "Terminal", "SysView", "J-Scope_t4i4"
            char*    pBuffer;       // Pointer to start of buffer
            unsigned SizeOfBuffer;  // Buffer size in bytes. Note that one byte is lost, as this implementation does not fill up the buffer in order to avoid the problem of being unable to distinguish between full and empty.
  volatile  unsigned WrOff;         // Position of next item to be written by host. Must be volatile since it may be modified by host.
            unsigned RdOff;         // Position of next item to be read by target (down-buffer).
            unsigned Flags;         // Contains configuration flags. Flags[31:24] are used for validity check and must be zero. Flags[23:2] are reserved for future use. Flags[1:0] = RTT operating mode.
} SEGGER_RTT_BUFFER_DOWN;

//
// RTT control block which describes the number of buffers available
// as well as the configuration for each buffer
//
//
typedef struct {
  char                    acID[16];                                 // Initialized to "SEGGER RTT"
  int                     MaxNumUpBuffers;                          // Initialized to SEGGER_RTT_MAX_NUM_UP_BUFFERS (type. 2)
  int                     MaxNumDownBuffers;                        // Initialized to SEGGER_RTT_MAX_NUM_DOWN_BUFFERS (type. 2)
  SEGGER_RTT_BUFFER_UP    aUp[SEGGER_RTT_MAX_NUM_UP_BUFFERS];       // Up buffers, transferring information up from target via debug probe to host
  SEGGER_RTT_BUFFER_DOWN  aDown[SEGGER_RTT_MAX_NUM_DOWN_BUFFERS];   // Down buffers, transferring information down from host via debug probe to target
#if SEGGER_RTT__CB_PADDING
  unsigned char           aDummy[SEGGER_RTT__CB_PADDING];
#endif
} SEGGER_RTT_CB;

/*********************************************************************
*
*       Global data
*
**********************************************************************
*/
extern SEGGER_RTT_CB _SEGGER_RTT;

/*********************************************************************
*
*       RTT API functions
*
**********************************************************************
*/
#ifdef __cplusplus
  extern "C" {
#endif
int          SEGGER_RTT_AllocDownBuffer         (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_AllocUpBuffer           (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigUpBuffer          (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigDownBuffer        (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_GetKey                  (void);
unsigned     SEGGER_RTT_HasData                 (unsigned BufferIndex);
int          SEGGER_RTT_HasKey                  (void);
unsigned     SEGGER_RTT_HasDataUp               (unsigned BufferIndex);
void         SEGGER_RTT_Init                    (void);
unsigned     SEGGER_RTT_Read                    (unsigned BufferIndex,       void* pBuffer, unsigned BufferSize);
unsigned     SEGGER_RTT_ReadNoLock              (unsigned BufferIndex,       void* pData,   unsigned BufferSize);
int          SEGGER_RTT_SetNameDownBuffer       (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetNameUpBuffer         (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetFlagsDownBuffer      (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_SetFlagsUpBuffer        (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_WaitKey                 (void);
unsigned     SEGGER_RTT_Write                   (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteNoLock             (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteSkipNoLock         (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_ASM_WriteSkipNoLock     (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteString             (unsigned BufferIndex, const char* s);
void         SEGGER_RTT_WriteWithOverwriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_PutChar                 (unsigned BufferIndex, char c);
unsigned     SEGGER_RTT_PutCharSkip             (unsigned BufferIndex, char c);
unsigned     SEGGER_RTT_PutCharSkipNoLock       (unsigned BufferIndex, char c);
unsigned     SEGGER_RTT_GetAvailWriteSpace      (unsigned BufferIndex);
unsigned     SEGGER_RTT_GetBytesInBuffer        (unsigned BufferIndex);
//
// Function macro for performance optimization
//
#define      SEGGER_RTT_HASDATA(n)       (((SEGGER_RTT_BUFFER_DOWN*)((uintptr_t)&_SEGGER_RTT.aDown[n] + SEGGER_RTT_UNCACHED_OFF))->WrOff - ((SEGGER_RTT_BUFFER_DOWN*)((uintptr_t)&_SEGGER_RTT.aDown[n] + SEGGER_RTT_UNCACHED_OFF))->RdOff)

#if RTT_USE_ASM
  #define SEGGER_RTT_WriteSkipNoLock  SEGGER_RTT_ASM_WriteSkipNoLock
#endif

/*********************************************************************
*
*       RTT transfer functions to send RTT data via other channels.
*
**********************************************************************
*/
unsigned     SEGGER_RTT_ReadUpBuffer            (unsigned BufferIndex, void* pBuffer, unsigned BufferSize);
unsigned     SEGGER_RTT_ReadUpBufferNoLock      (unsigned BufferIndex, void* pData, unsigned BufferSize);
unsigned     SEGGER_RTT_WriteDownBuffer         (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteDownBufferNoLock   (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);

#define      SEGGER_RTT_HASDATA_UP(n)    (((SEGGER_RTT_BUFFER_UP*)((uintptr_t)&_SEGGER_RTT.aUp[n] + SEGGER_RTT_UNCACHED_OFF))->WrOff - ((SEGGER_RTT_BUFFER_UP*)((uintptr_t)&_SEGGER_RTT.aUp[n] + SEGGER_RTT_UNCACHED_OFF))->RdOff)   // Access uncached to make sure we see changes made by the J-Link side and all of our changes go into HW directly

/*********************************************************************
*
*       RTT "Terminal" API functions
*
**********************************************************************
*/
int     SEGGER_RTT_SetTerminal        (unsigned char TerminalId);
int     SEGGER_RTT_TerminalOut        (unsigned char TerminalId, const char* s);

/*********************************************************************
*
*       RTT printf functions (require SEGGER_RTT_printf.c)
*
**********************************************************************
*/
int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);
int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);

#ifdef __cplusplus
  }
#endif

#endif // ifndef(SEGGER_RTT_ASM)

//
// For some environments, NULL may not be defined until certain headers are included
//
#ifndef NULL
  #define NULL  ((void*)0)
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

//
// Operating modes. Define behavior if buffer is full (not enough space for entire message)
//
#define SEGGER_RTT_MODE_NO_BLOCK_SKIP         (0)     // Skip. Do not block, output nothing. (Default)
#define SEGGER_RTT_MODE_NO_BLOCK_TRIM         (1)     // Trim: Do not block, output as much as fits.
#define SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL    (2)     // Block: Wait until there is space in the buffer.
#define SEGGER_RTT_MODE_MASK                  (3)

//
// Control sequences, based on ANSI.
// Can be used to control color, and clear the screen
//
#define RTT_CTRL_RESET                "\x1B[0m"         // Reset to default colors
#define RTT_CTRL_CLEAR                "\x1B[2J"         // Clear screen, reposition cursor to top left

#define RTT_CTRL_TEXT_BLACK           "\x1B[2;30m"
#define RTT_CTRL_TEXT_RED             "\x1B[2;31m"
#define RTT_CTRL_TEXT_GREEN           "\x1B[2;32m"
#define RTT_CTRL_TEXT_YELLOW          "\x1B[2;33m"
#define RTT_CTRL_TEXT_BLUE            "\x1B[2;34m"
#define RTT_CTRL_TEXT_MAGENTA         "\x1B[2;35m"
#define RTT_CTRL_TEXT_CYAN            "\x1B[2;36m"
#define RTT_CTRL_TEXT_WHITE           "\x1B[2;37m"

#define RTT_CTRL_TEXT_BRIGHT_BLACK    "\x1B[1;30m"
#define RTT_CTRL_TEXT_BRIGHT_RED      "\x1B[1;31m"
#define RTT_CTRL_TEXT_BRIGHT_GREEN    "\x1B[1;32m"
#define RTT_CTRL_TEXT_BRIGHT_YELLOW   "\x1B[1;33m"
#define RTT_CTRL_TEXT_BRIGHT_BLUE     "\x1B[1;34m"
#define RTT_CTRL_TEXT_BRIGHT_MAGENTA  "\x1B[1;35m"
#define RTT_CTRL_TEXT_BRIGHT_CYAN     "\x1B[1;36m"
#define RTT_CTRL_TEXT_BRIGHT_WHITE    "\x1B[1;37m"

#define RTT_CTRL_BG_BLACK             "\x1B[24;40m"
#define RTT_CTRL_BG_RED               "\x1B[24;41m"
#define RTT_CTRL_BG_GREEN             "\x1B[24;42m"
#define RTT_CTRL_BG_YELLOW            "\x1B[24;43m"
#define RTT_CTRL_BG_BLUE              "\x1B[24;44m"
#define RTT_CTRL_BG_MAGENTA           "\x1B[24;45m"
#define RTT_CTRL_BG_CYAN              "\x1B[24;46m"
#define RTT_CTRL_BG_WHITE             "\x1B[24;47m"

#define RTT_CTRL_BG_BRIGHT_BLACK      "\x1B[4;40m"
#define RTT_CTRL_BG_BRIGHT_RED        "\x1B[4;41m"
#define RTT_CTRL_BG_BRIGHT_GREEN      "\x1B[4;42m"
#define RTT_CTRL_BG_BRIGHT_YELLOW     "\x1B[4;43m"
#define RTT_CTRL_BG_BRIGHT_BLUE       "\x1B[4;44m"
#define RTT_CTRL_BG_BRIGHT_MAGENTA    "\x1B[4;45m"
#define RTT_CTRL_BG_BRIGHT_CYAN       "\x1B[4;46m"
#define RTT_CTRL_BG_BRIGHT_WHITE      "\x1B[4;47m"


#endif

/*************************** End of file ****************************/
