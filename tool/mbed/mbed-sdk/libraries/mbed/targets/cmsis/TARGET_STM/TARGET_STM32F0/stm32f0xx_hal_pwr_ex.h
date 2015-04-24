/**
  ******************************************************************************
  * @file    stm32f0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of PWR HAL Extension module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_HAL_PWR_EX_H
#define __STM32F0xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup PWREx_Exported_Types PWREx Exported Types
 *  @{
 */

#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel;   /*!< PVDLevel: Specifies the PVD detection level
                            This parameter can be a value of @ref PWREx_PVD_detection_level */

  uint32_t Mode;       /*!< Mode: Specifies the operating mode for the selected pins.
                            This parameter can be a value of @ref PWREx_PVD_Mode */
}PWR_PVDTypeDef;

#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */
/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWREx Exported Constants
  * @{
  */


/** @defgroup PWREx_WakeUp_Pins PWREx Wakeup Pins
  * @{
  */
#if defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || \
    defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC)
#define PWR_WAKEUP_PIN1                     ((uint32_t)0x00)
#define PWR_WAKEUP_PIN2                     ((uint32_t)0x01)
#define PWR_WAKEUP_PIN3                     ((uint32_t)0x02)
#define PWR_WAKEUP_PIN4                     ((uint32_t)0x03)
#define PWR_WAKEUP_PIN5                     ((uint32_t)0x04)
#define PWR_WAKEUP_PIN6                     ((uint32_t)0x05)
#define PWR_WAKEUP_PIN7                     ((uint32_t)0x06)
#define PWR_WAKEUP_PIN8                     ((uint32_t)0x07)

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3) || \
                                ((PIN) == PWR_WAKEUP_PIN4) || \
                                ((PIN) == PWR_WAKEUP_PIN5) || \
                                ((PIN) == PWR_WAKEUP_PIN6) || \
                                ((PIN) == PWR_WAKEUP_PIN7) || \
                                ((PIN) == PWR_WAKEUP_PIN8))
#else 
#define PWR_WAKEUP_PIN1                     ((uint32_t)0x00)
#define PWR_WAKEUP_PIN2                     ((uint32_t)0x01)

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2))
#endif /* defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F070xB) || */
       /* defined (STM32F091xC) || defined (STM32F098xx) || defined (STM32F030xC) */
/**
  * @}
  */

/** @defgroup PWREx_EXTI_Line PWREx EXTI Line
  * @{
  */
#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)

#define PWR_EXTI_LINE_PVD                   ((uint32_t)0x00010000)  /*!< External interrupt line 16 Connected to the PVD EXTI Line */

#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */
      
#if defined (STM32F042x6) || defined (STM32F048xx) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
    defined (STM32F091xC) || defined (STM32F098xx)

#define PWR_EXTI_LINE_VDDIO2                ((uint32_t)0x80000000)  /*!< External interrupt line 31 Connected to the Vddio2 Monitor EXTI Line */

#endif /* defined (STM32F042x6) || defined (STM32F048xx) ||\
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
          defined (STM32F091xC) || defined (STM32F098xx) ||*/
/**
  * @}
  */

#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)
/** @defgroup PWREx_PVD_detection_level PWREx PVD detection level
  * @{
  */
#define PWR_PVDLEVEL_0                      PWR_CR_PLS_LEV0
#define PWR_PVDLEVEL_1                      PWR_CR_PLS_LEV1
#define PWR_PVDLEVEL_2                      PWR_CR_PLS_LEV2
#define PWR_PVDLEVEL_3                      PWR_CR_PLS_LEV3
#define PWR_PVDLEVEL_4                      PWR_CR_PLS_LEV4
#define PWR_PVDLEVEL_5                      PWR_CR_PLS_LEV5
#define PWR_PVDLEVEL_6                      PWR_CR_PLS_LEV6
#define PWR_PVDLEVEL_7                      PWR_CR_PLS_LEV7
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))
/**
  * @}
  */

/** @defgroup PWREx_PVD_Mode PWREx PVD Mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 ((uint32_t)0x00000000)   /*!< basic mode is used */
#define PWR_PVD_MODE_IT_RISING              ((uint32_t)0x00010001)   /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             ((uint32_t)0x00010002)   /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      ((uint32_t)0x00010003)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING           ((uint32_t)0x00020001)   /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_EVENT_FALLING          ((uint32_t)0x00020002)   /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING_FALLING   ((uint32_t)0x00020003)   /*!< Event Mode with Rising/Falling edge trigger detection */

#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_IT_RISING)|| ((MODE) == PWR_PVD_MODE_IT_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_NORMAL))
/**
  * @}
  */
#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */

/** @defgroup PWREx_Flag PWREx Flag
  * @{
  */
#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)

#define PWR_FLAG_WU                         PWR_CSR_WUF
#define PWR_FLAG_SB                         PWR_CSR_SBF
#define PWR_FLAG_PVDO                       PWR_CSR_PVDO
#define PWR_FLAG_VREFINTRDY                 PWR_CSR_VREFINTRDYF
#elif defined (STM32F070x6) || defined (STM32F070xB) || defined (STM32F030xC)
#define PWR_FLAG_WU                         PWR_CSR_WUF
#define PWR_FLAG_SB                         PWR_CSR_SBF
#define PWR_FLAG_VREFINTRDY                 PWR_CSR_VREFINTRDYF
#else
#define PWR_FLAG_WU                         PWR_CSR_WUF
#define PWR_FLAG_SB                         PWR_CSR_SBF

#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */
/**
  * @}
  */

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWREx Exported Macros
  * @{
  */
#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)
/**
  * @brief Enable interrupt on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()      (EXTI->IMR |= (PWR_EXTI_LINE_PVD))

/**
  * @brief Disable interrupt on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()     (EXTI->IMR &= ~(PWR_EXTI_LINE_PVD))

/**
  * @brief Enable event on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()   (EXTI->EMR |= (PWR_EXTI_LINE_PVD))

/**
  * @brief Disable event on PVD Exti Line 16.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()  (EXTI->EMR &= ~(PWR_EXTI_LINE_PVD))

/**
  * @brief  PVD EXTI line configuration: clear falling edge and rising edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_EGDE_TRIGGER()   EXTI->FTSR &= ~(PWR_EXTI_LINE_PVD); \
                                                  EXTI->RTSR &= ~(PWR_EXTI_LINE_PVD)

/**
  * @brief  PVD EXTI line configuration: set falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_SET_FALLING_EGDE_TRIGGER()  EXTI->FTSR |= (PWR_EXTI_LINE_PVD)

/**
  * @brief  PVD EXTI line configuration: set rising edge trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_SET_RISING_EDGE_TRIGGER()   EXTI->RTSR |= (PWR_EXTI_LINE_PVD)

/**
  * @brief Check whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG()       (EXTI->PR & (PWR_EXTI_LINE_PVD))

/**
  * @brief Clear the PVD EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()     (EXTI->PR = (PWR_EXTI_LINE_PVD))

/**
  * @brief Generate a Software interrupt on selected EXTI line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT()  (EXTI->SWIER |= (PWR_EXTI_LINE_PVD))

#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */


#if defined (STM32F042x6) || defined (STM32F048xx) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
    defined (STM32F091xC) || defined (STM32F098xx)
/**
  * @brief Enable interrupt on Vddio2 Monitor Exti Line 31.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_ENABLE_IT()             (EXTI->IMR |= (PWR_EXTI_LINE_VDDIO2))

/**
  * @brief Disable interrupt on Vddio2 Monitor Exti Line 31.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_DISABLE_IT()            (EXTI->IMR &= ~(PWR_EXTI_LINE_VDDIO2))

/**
  * @brief  Vddio2 Monitor EXTI line configuration: clear falling edge and rising edge trigger.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_CLEAR_EGDE_TRIGGER()    EXTI->FTSR &= ~(PWR_EXTI_LINE_VDDIO2); \
                                                      EXTI->RTSR &= ~(PWR_EXTI_LINE_VDDIO2)

/**
  * @brief  Vddio2 Monitor EXTI line configuration: set falling edge trigger.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_SET_FALLING_EGDE_TRIGGER()  EXTI->FTSR |= (PWR_EXTI_LINE_VDDIO2)

/**
  * @brief Check whether the specified VDDIO2 monitor EXTI interrupt flag is set or not.
  * @retval EXTI VDDIO2 Monitor Line Status.
  */
#define __HAL_PWR_VDDIO2_EXTI_GET_FLAG()              (EXTI->PR & (PWR_EXTI_LINE_VDDIO2))

/**
  * @brief Clear the VDDIO2 Monitor EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_CLEAR_FLAG()            (EXTI->PR = (PWR_EXTI_LINE_VDDIO2))

/**
  * @brief Generate a Software interrupt on selected EXTI line.
  * @retval None.
  */
#define __HAL_PWR_VDDIO2_EXTI_GENERATE_SWIT()         (EXTI->SWIER |= (PWR_EXTI_LINE_VDDIO2))


#endif /* defined (STM32F042x6) || defined (STM32F048xx) ||\
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
          defined (STM32F091xC) || defined (STM32F098xx) */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWREx_Exported_Functions PWREx Exported Functions
 *  @{
 */

/** @addtogroup PWREx_Exported_Functions_Group1
  * @{
  */
/* I/O operation functions  ***************************************************/
#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);
#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */

#if defined (STM32F042x6) || defined (STM32F048xx) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
    defined (STM32F091xC) || defined (STM32F098xx)
void HAL_PWR_Vddio2Monitor_IRQHandler(void);
void HAL_PWR_Vddio2MonitorCallback(void);
#endif /* defined (STM32F042x6) || defined (STM32F048xx) || \
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
          defined (STM32F091xC) || defined (STM32F098xx) */

/* Peripheral Control functions  **********************************************/
#if defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || \
    defined (STM32F071xB) || defined (STM32F072xB) || \
    defined (STM32F091xC)
void HAL_PWR_PVDConfig(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);
#endif /* defined (STM32F031x6) || defined (STM32F042x6) || defined (STM32F051x8) || */
       /* defined (STM32F071xB) || defined (STM32F072xB) || */
       /* defined (STM32F091xC) */
       
#if defined (STM32F042x6) || defined (STM32F048xx) || \
    defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
    defined (STM32F091xC) || defined (STM32F098xx)
void HAL_PWR_EnableVddio2Monitor(void);
void HAL_PWR_DisableVddio2Monitor(void);
#endif /* defined (STM32F042x6) || defined (STM32F048xx) || \
          defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || \
          defined (STM32F091xC) || defined (STM32F098xx) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

