/**
  ******************************************************************************
  * @file    stm32l0xx.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Header File. 
  *          This file contains all the peripheral register's definitions, bits 
  *          definitions and memory mapping for STM32L0xx devices.            
  *            
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_HAL_DRIVER"
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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

/** @addtogroup stm32l0xx
  * @{
  */
    
#ifndef __STM32L0xx_H
#define __STM32L0xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32L0)
#define STM32L0
#endif /* STM32L0 */

/* Uncomment the line below according to the target STM32 device used in your
   application 
  */

#if !defined (STM32L051xx) && !defined (STM32L052xx) && !defined (STM32L053xx) && !defined (STM32L061xx) && !defined (STM32L062xx) && !defined (STM32L063xx) \
 && !defined (STM32L071xx) && !defined (STM32L072xx) && !defined (STM32L073xx) && !defined (STM32L081xx) && !defined (STM32L082xx) && !defined (STM32L083xx)
  /* #define STM32L051xx */   /*!< STM32L051K8, STM32L051C6, STM32L051C8, STM32L051R6, STM32L051R8 Devices */
  /* #define STM32L052xx */   /*!< STM32L052K6, STM32L052K8, STM32L052C6, STM32L052C8, STM32L052R6, STM32L052R8 Devices */
#define STM32L053xx           /*!< STM32L053C6, STM32L053C8, STM32L053R6, STM32L053R8 Devices */
  /* #define STM32L061xx */   /*!< */
  /* #define STM32L062xx */   /*!< STM32L062K8 */
  /* #define STM32L063xx */   /*!< STM32L063C8, STM32L063R8 */ 
  /* #define STM32L071xx */   /*!< */
  /* #define STM32L072xx */   /*!< */
  /* #define STM32L073xx */   /*!< STM32L073V8, STM32L073VB, STM32L073RB, STM32L073VZ, STM32L073RZ Devices */
  /* #define STM32L081xx */   /*!< */
  /* #define STM32L082xx */   /*!< */
  /* #define STM32L083xx */   /*!< */ 
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
  * @brief CMSIS Device version number V1.2.0
  */
#define __STM32L0xx_CMSIS_DEVICE_VERSION_MAIN   (0x01) /*!< [31:24] main version */                                  
#define __STM32L0xx_CMSIS_DEVICE_VERSION_SUB1   (0x02) /*!< [23:16] sub1 version */
#define __STM32L0xx_CMSIS_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L0xx_CMSIS_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L0xx_CMSIS_DEVICE_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))
                                             
/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32L031xx)
  #include "stm32l031xx.h"
#elif defined(STM32L041xx)
  #include "stm32l041xx.h"
#elif defined(STM32L051xx)
  #include "stm32l051xx.h"
#elif defined(STM32L052xx)
  #include "stm32l052xx.h"
#elif defined(STM32L053xx)
  #include "stm32l053xx.h"
#elif defined(STM32L062xx)
  #include "stm32l062xx.h"
#elif defined(STM32L063xx)
  #include "stm32l063xx.h"
#elif defined(STM32L061xx)
  #include "stm32l061xx.h"
#elif defined(STM32L071xx)
  #include "stm32l071xx.h"
#elif defined(STM32L072xx)
  #include "stm32l072xx.h"
#elif defined(STM32L073xx)
  #include "stm32l073xx.h"
#elif defined(STM32L082xx)
  #include "stm32l082xx.h"
#elif defined(STM32L083xx)
  #include "stm32l083xx.h"
#elif defined(STM32L081xx)
  #include "stm32l081xx.h"
#else
 #error "Please select first the target STM32L0xx device used in your application (in stm32l0xx.h file)"
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


/** @addtogroup Exported_macro
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32l0xx_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L0xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
