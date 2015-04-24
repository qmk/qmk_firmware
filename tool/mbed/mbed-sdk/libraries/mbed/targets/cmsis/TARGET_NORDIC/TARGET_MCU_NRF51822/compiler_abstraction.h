/* Copyright (c) 2013, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   * Neither the name of Nordic Semiconductor ASA nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _COMPILER_ABSTRACTION_H
#define _COMPILER_ABSTRACTION_H

/*lint ++flb "Enter library region" */

#if defined ( __CC_ARM )
    
    #ifndef __ASM
        #define __ASM               __asm                       /*!< asm keyword for ARM Compiler */
    #endif
    
    #ifndef __INLINE
        #define __INLINE            __inline                    /*!< inline keyword for ARM Compiler */
    #endif
    
    #ifndef __WEAK
        #define __WEAK              __weak                      /*!< weak keyword for ARM Compiler */
    #endif
    
    #define GET_SP()                __current_sp()              /*!> read current SP function for ARM Compiler */
  
#elif defined ( __ICCARM__ )
    
    #ifndef __ASM
        #define __ASM               __asm                       /*!< asm keyword for IAR Compiler */
    #endif
    
    #ifndef __INLINE
        #define __INLINE            inline                      /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
    #endif
    
    #ifndef __WEAK
        #define __WEAK              __weak                      /*!> define weak function for IAR Compiler */
    #endif
    
    #define GET_SP()                __get_SP()                  /*!> read current SP function for IAR Compiler */
    
#elif defined   ( __GNUC__ )
    
    #ifndef __ASM
        #define __ASM               __asm                       /*!< asm keyword for GNU Compiler */
    #endif
    
    #ifndef __INLINE
        #define __INLINE            inline                      /*!< inline keyword for GNU Compiler */
    #endif
    
    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))       /*!< weak keyword for GNU Compiler */
    #endif
    
    #define GET_SP()                gcc_current_sp()            /*!> read current SP function for GNU Compiler */

    static inline unsigned int gcc_current_sp(void)
    {
        register unsigned sp asm("sp");
        return sp;
    }
    
#elif defined   ( __TASKING__ )
        
    #ifndef __ASM        
        #define __ASM               __asm                       /*!< asm keyword for TASKING Compiler */
    #endif
    
    #ifndef __INLINE
        #define __INLINE            inline                      /*!< inline keyword for TASKING Compiler */
    #endif
    
    #ifndef __WEAK
        #define __WEAK              __attribute__((weak))       /*!< weak keyword for TASKING Compiler */
    #endif
    
    #define GET_SP()                __get_MSP()                 /*!> read current SP function for TASKING Compiler */
    
#endif

/*lint --flb "Leave library region" */

#endif
