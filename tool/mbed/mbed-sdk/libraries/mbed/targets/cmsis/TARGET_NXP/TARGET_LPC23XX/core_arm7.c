/* mbed Microcontroller Library
 * Copyright (C) 2008-2009 ARM Limited. All rights reserved.
 *
 * ARM7 version of CMSIS-like functionality - not advised for use outside mbed!
 * based on core_cm3.h, V1.20
 */

#include <stdint.h>


/* define compiler specific symbols */
#if defined   ( __CC_ARM   )
  #define __ASM            __asm           /*!< asm keyword for armcc           */
  #define __INLINE         __inline        /*!< inline keyword for armcc        */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm            /*!< asm keyword for iarcc           */
  #define __INLINE        inline           /*!< inline keyword for iarcc. Only avaiable in High optimization mode! */

#elif defined (  __GNUC__  )
  #define __ASM             __asm          /*!< asm keyword for gcc            */
  #define __INLINE          inline         /*!< inline keyword for gcc         */

#elif defined   (  __TASKING__  )
  #define __ASM            __asm           /*!< asm keyword for TASKING Compiler          */
  #define __INLINE         inline          /*!< inline keyword for TASKING Compiler       */

#endif

#if defined ( __CC_ARM   )
/**
 * @brief  Return the Main Stack Pointer (return current ARM7 stack)
 *
 * @param  none
 * @return uint32_t Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */
uint32_t __get_MSP(void)
{
    return __current_sp();
}
#endif
