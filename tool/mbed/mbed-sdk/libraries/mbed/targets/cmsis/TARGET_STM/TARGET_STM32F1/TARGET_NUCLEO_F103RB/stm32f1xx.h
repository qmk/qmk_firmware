/**
  ******************************************************************************
  * @file    stm32f1xx.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    16-December-2014
  * @brief   CMSIS STM32F1xx Device Peripheral Access Layer Header File. 
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *            - Configuration section that allows to select:
  *              - The STM32F1xx device used in the target application
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

/** @addtogroup stm32f1xx
  * @{
  */
    
#ifndef __STM32F1XX_H
#define __STM32F1XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32F1)
#define STM32F1
#endif /* STM32F1 */

/* Uncomment the line below according to the target STM32L device used in your 
   application 
  */

#if !defined (STM32F100xB) && !defined (STM32F100xE) && !defined (STM32F101x6) && \
    !defined (STM32F101xB) && !defined (STM32F101xE) && !defined (STM32F101xG) && !defined (STM32F102x6) && !defined (STM32F102xB) && !defined (STM32F103x6) && \
    !defined (STM32F103xB) && !defined (STM32F103xE) && !defined (STM32F103xG) && !defined (STM32F105xC) && !defined (STM32F107xC)
  /* #define STM32F100xB */   /*!< STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6, STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB, STM32F100RB and STM32F100VB */
  /* #define STM32F100xE */   /*!< STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD, STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE and STM32F100ZE */
  /* #define STM32F101x6 */   /*!< STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6, STM32F101R6 and STM32F101T6 Devices */
  /* #define STM32F101xB */   /*!< STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8, STM32F101CB, STM32F101RB, STM32F101TB and STM32F101VB */
  /* #define STM32F101xE */   /*!< STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD, STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE and STM32F101ZE */ 
  /* #define STM32F101xG */   /*!< STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG, STM32F101VG and STM32F101ZG */
  /* #define STM32F102x6 */   /*!< STM32F102C4, STM32F102R4, STM32F102C6 and STM32F102R6 */
  /* #define STM32F102xB */   /*!< STM32F102C8, STM32F102R8, STM32F102CB and STM32F102RB */
  /* #define STM32F103x6 */   /*!< STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6, STM32F103R6 and STM32F103T6 */
#define STM32F103xB           /*!< STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8, STM32F103CB, STM32F103RB, STM32F103TB and STM32F103VB */
  /* #define STM32F103xE */   /*!< STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD, STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE and STM32F103ZE */
  /* #define STM32F103xG */   /*!< STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG, STM32F103VG and STM32F103ZG */
  /* #define STM32F105xC */   /*!< STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB, STM32F105RC and STM32F105VC */
  /* #define STM32F107xC */   /*!< STM32F107RB, STM32F107VB, STM32F107RC and STM32F107VC */  
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
  * @brief CMSIS Device version number V4.0.0
  */
#define __STM32F1xx_CMSIS_DEVICE_VERSION_MAIN   (0x04) /*!< [31:24] main version */                                  
#define __STM32F1xx_CMSIS_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32F1xx_CMSIS_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F1xx_CMSIS_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F1xx_CMSIS_DEVICE_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32F100xB)
  #include "stm32f100xb.h"
#elif defined(STM32F100xE)
  #include "stm32f100xe.h"
#elif defined(STM32F101x6)
  #include "stm32f101x6.h"
#elif defined(STM32F101xB)
  #include "stm32f101xb.h"
#elif defined(STM32F101xE)
  #include "stm32f101xe.h"
#elif defined(STM32F101xG)
  #include "stm32f101xg.h"
#elif defined(STM32F102x6)
  #include "stm32f102x6.h"
#elif defined(STM32F102xB)
  #include "stm32f102xb.h"
#elif defined(STM32F103x6)
  #include "stm32f103x6.h"
#elif defined(STM32F103xB)
  #include "stm32f103xb.h"
#elif defined(STM32F103xE)
  #include "stm32f103xe.h"
#elif defined(STM32F103xG)
  #include "stm32f103xg.h"
#elif defined(STM32F105xC)
  #include "stm32f105xc.h"
#elif defined(STM32F107xC)
  #include "stm32f107xc.h"
#else
 #error "Please select first the target STM32F1xx device used in your application (in stm32f1xx.h file)"
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
 #include "stm32f1xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32F1xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
