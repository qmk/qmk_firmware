/**
  ******************************************************************************
  * @file    stm32l1xx.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    5-September-2014
  * @brief   CMSIS STM32L1xx Device Peripheral Access Layer Header File. 
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *            - Configuration section that allows to select:
  *              - The STM32L1xx device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_HAL_DRIVER"
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
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
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l1xx
  * @{
  */
    
#ifndef __STM32L1XX_H
#define __STM32L1XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target STM32L device used in your 
   application 
  */

#if !defined (STM32L100xB) && !defined (STM32L100xBA) && !defined (STM32L100xC) && \
    !defined (STM32L151xB) && !defined (STM32L151xBA) && !defined (STM32L151xC) && !defined (STM32L151xCA) && !defined (STM32L151xD) && !defined (STM32L151xE) && \
    !defined (STM32L152xB) && !defined (STM32L152xBA) && !defined (STM32L152xC) && !defined (STM32L152xCA) && !defined (STM32L152xD) && !defined (STM32L152xE) && \
    !defined (STM32L162xC) && !defined (STM32L162xCA) && !defined (STM32L162xD) && !defined (STM32L162xE)
  /* #define STM32L100xB  */   /*!< STM32L100C6, STM32L100R and STM32L100RB Devices */
  /* #define STM32L100xBA */   /*!< STM32L100C6-A, STM32L100R8-A and STM32L100RB-A Devices */
  /* #define STM32L100xC  */   /*!< STM32L100RC Devices */
  /* #define STM32L151xB  */   /*!< STM32L151C6, STM32L151R6, STM32L151C8, STM32L151R8, STM32L151V8, STM32L151CB, STM32L151RB and STM32L151VB */
  /* #define STM32L151xBA */   /*!< STM32L151C6-A, STM32L151R6-A, STM32L151C8-A, STM32L151R8-A, STM32L151V8-A, STM32L151CB-A, STM32L151RB-A and STM32L151VB-A */ 
  /* #define STM32L151xC  */   /*!< STM32L151CC, STM32L151UC, STM32L151RC and STM32L151VC */
  /* #define STM32L151xCA */   /*!< STM32L151RC-A, STM32L151VC-A, STM32L151QC and STM32L151ZC */
  /* #define STM32L151xD  */   /*!< STM32L151QD, STM32L151RD, STM32L151VD & STM32L151ZD */
  /* #define STM32L151xE  */   /*!< STM32L151QE, STM32L151RE, STM32L151VE and STM32L151ZE */
  /* #define STM32L152xB  */   /*!< STM32L152C6, STM32L152R6, STM32L152C8, STM32L152R8, STM32L152V8, STM32L152CB, STM32L152RB and STM32L152VB */
  /* #define STM32L152xBA */   /*!< STM32L152C6-A, STM32L152R6-A, STM32L152C8-A, STM32L152R8-A, STM32L152V8-A, STM32L152CB-A, STM32L152RB-A and STM32L152VB-A */
#define STM32L152xC    /*!< STM32L152CC, STM32L152UC, STM32L152RC and STM32L152VC */
  /* #define STM32L152xCA */   /*!< STM32L152RC-A, STM32L152VC-A, STM32L152QC and STM32L152ZC */
  /* #define STM32L152xD  */   /*!< STM32L152QD, STM32L152RD, STM32L152VD and STM32L152ZD */  
  /* #define STM32L152xE  */   /*!< STM32L152QE, STM32L152RE, STM32L152VE and STM32L152ZE */
  /* #define STM32L162xC  */   /*!< STM32L162RC and STM32L162VC */
  /* #define STM32L162xCA */   /*!< STM32L162RC-A, STM32L162VC-A, STM32L162QC and STM32L162ZC */
  /* #define STM32L162xD  */   /*!< STM32L162QD, STM32L162RD, STM32L162VD and STM32L162ZD */
  /* #define STM32L162xE  */   /*!< STM32L162RE, STM32L162VE and STM32L162ZE */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
  
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
#define USE_HAL_DRIVER
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number V2.0.0
  */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */                                  
#define __STM32L1xx_CMSIS_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L1xx_CMSIS_DEVICE_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32L100xB)
  #include "stm32l100xb.h"
#elif defined(STM32L100xBA)
  #include "stm32l100xba.h"
#elif defined(STM32L100xC)
  #include "stm32l100xc.h"
#elif defined(STM32L151xB)
  #include "stm32l151xb.h"
#elif defined(STM32L151xBA)
  #include "stm32l151xba.h"
#elif defined(STM32L151xC)
  #include "stm32l151xc.h"
#elif defined(STM32L151xCA)
  #include "stm32l151xca.h"
#elif defined(STM32L151xD)
  #include "stm32l151xd.h"
#elif defined(STM32L151xE)
  #include "stm32l151xe.h"
#elif defined(STM32L152xB)
  #include "stm32l152xb.h"
#elif defined(STM32L152xBA)
  #include "stm32l152xba.h"
#elif defined(STM32L152xC)
  #include "stm32l152xc.h"
#elif defined(STM32L152xCA)
  #include "stm32l152xca.h"
#elif defined(STM32L152xD)
  #include "stm32l152xd.h"
#elif defined(STM32L152xE)
  #include "stm32l152xe.h"
#elif defined(STM32L162xC)
  #include "stm32l162xc.h"
#elif defined(STM32L162xCA)
  #include "stm32l162xca.h"
#elif defined(STM32L162xD)
  #include "stm32l162xd.h"
#elif defined(STM32L162xE)
  #include "stm32l162xe.h"
#else
 #error "Please select first the target STM32L1xx device used in your application (in stm32l1xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */  
typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum 
{
  ERROR = 0, 
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32l1xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L1xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
