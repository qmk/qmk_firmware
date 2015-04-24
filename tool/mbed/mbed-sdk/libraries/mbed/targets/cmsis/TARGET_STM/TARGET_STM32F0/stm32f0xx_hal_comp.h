/**
  ******************************************************************************
  * @file    stm32f0xx_hal_comp.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Header file of COMP HAL module.
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
#ifndef __STM32F0xx_HAL_COMP_H
#define __STM32F0xx_HAL_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || \
    defined(STM32F091xC) || defined(STM32F098xx)

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal_def.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup COMP COMP HAL Module Driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup COMP_Exported_Types COMP Exported Types
  * @{
  */
    
/** 
  * @brief  COMP Init structure definition  
  */ 
typedef struct
{

  uint32_t InvertingInput;     /*!< Selects the inverting input of the comparator.
                                    This parameter can be a value of @ref COMP_InvertingInput */

  uint32_t NonInvertingInput;  /*!< Selects the non inverting input of the comparator.
                                    This parameter can be a value of @ref COMP_NonInvertingInput */

  uint32_t Output;             /*!< Selects the output redirection of the comparator.
                                    This parameter can be a value of @ref COMP_Output */

  uint32_t OutputPol;          /*!< Selects the output polarity of the comparator.
                                    This parameter can be a value of @ref COMP_OutputPolarity */

  uint32_t Hysteresis;         /*!< Selects the hysteresis voltage of the comparator.
                                    This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t Mode;               /*!< Selects the operating comsumption mode of the comparator
                                    to adjust the speed/consumption.
                                    This parameter can be a value of @ref COMP_Mode */

  uint32_t WindowMode;         /*!< Selects the window mode of the comparator 1 & 2.
                                    This parameter can be a value of @ref COMP_WindowMode */
  
  uint32_t TriggerMode;        /*!< Selects the trigger mode of the comparator (interrupt mode).
                                    This parameter can be a value of @ref COMP_TriggerMode */

}COMP_InitTypeDef;

/** 
  * @brief  COMP Handle Structure definition  
  */ 
typedef struct
{
  COMP_TypeDef                *Instance; /*!< Register base address    */
  COMP_InitTypeDef            Init;      /*!< COMP required parameters */
  HAL_LockTypeDef             Lock;      /*!< Locking object           */
  __IO uint32_t               State;     /*!< COMP communication state 
                                              This parameter can be a value of @ref COMP_State  */
}COMP_HandleTypeDef;

/**
  * @}
  */
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_State COMP State
  * @{
  */
#define HAL_COMP_STATE_RESET             ((uint32_t)0x00000000)    /*!< COMP not yet initialized or disabled             */
#define HAL_COMP_STATE_READY             ((uint32_t)0x00000001)    /*!< COMP initialized and ready for use               */
#define HAL_COMP_STATE_READY_LOCKED      ((uint32_t)0x00000011)    /*!< COMP initialized but the configuration is locked */
#define HAL_COMP_STATE_BUSY              ((uint32_t)0x00000002)    /*!< COMP is running                                  */
#define HAL_COMP_STATE_BUSY_LOCKED       ((uint32_t)0x00000012)    /*!< COMP is running and the configuration is locked  */
/**
  * @}
  */

/** @defgroup COMP_OutputPolarity COMP OutputPolarity
  * @{
  */
#define COMP_OUTPUTPOL_NONINVERTED             ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OUTPUTPOL_INVERTED                COMP_CSR_COMP1POL       /*!< COMP output on GPIO is inverted  */

#define IS_COMP_OUTPUTPOL(POL)  (((POL) == COMP_OUTPUTPOL_NONINVERTED)  || \
                                 ((POL) == COMP_OUTPUTPOL_INVERTED))
/**
  * @}
  */ 

/** @defgroup COMP_Hysteresis COMP Hysteresis
  * @{
  */
#define COMP_HYSTERESIS_NONE                   ((uint32_t)0x00000000)  /*!< No hysteresis */
#define COMP_HYSTERESIS_LOW                    COMP_CSR_COMP1HYST_0    /*!< Hysteresis level low */
#define COMP_HYSTERESIS_MEDIUM                 COMP_CSR_COMP1HYST_1    /*!< Hysteresis level medium */
#define COMP_HYSTERESIS_HIGH                   COMP_CSR_COMP1HYST      /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_HYSTERESIS_NONE)   || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_LOW)    || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_MEDIUM) || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_HIGH))
/**
  * @}
  */

/** @defgroup COMP_Mode COMP Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_MODE_HIGHSPEED                    ((uint32_t)0x00000000) /*!< High Speed */
#define COMP_MODE_MEDIUMSPEED                  COMP_CSR_COMP1MODE_0   /*!< Medium Speed */
#define COMP_MODE_LOWPOWER                     COMP_CSR_COMP1MODE_1   /*!< Low power mode */
#define COMP_MODE_ULTRALOWPOWER                COMP_CSR_COMP1MODE     /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)  (((MODE) == COMP_MODE_HIGHSPEED)     || \
                             ((MODE) == COMP_MODE_MEDIUMSPEED)   || \
                             ((MODE) == COMP_MODE_LOWPOWER)      || \
                             ((MODE) == COMP_MODE_ULTRALOWPOWER))

/**
  * @}
  */

/** @defgroup COMP_InvertingInput COMP InvertingInput
  * @{
  */

#define COMP_INVERTINGINPUT_1_4VREFINT         ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT         COMP_CSR_COMP1INSEL_0                         /*!< 1/2 VREFINT connected to comparator inverting input    */
#define COMP_INVERTINGINPUT_3_4VREFINT         COMP_CSR_COMP1INSEL_1                         /*!< 3/4 VREFINT connected to comparator inverting input    */
#define COMP_INVERTINGINPUT_VREFINT            (COMP_CSR_COMP1INSEL_1|COMP_CSR_COMP1INSEL_0) /*!< VREFINT connected to comparator inverting input        */
#define COMP_INVERTINGINPUT_DAC1               COMP_CSR_COMP1INSEL_2                         /*!< DAC_OUT1 (PA4) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1SWITCHCLOSED   (COMP_CSR_COMP1INSEL_2|COMP_CSR_COMP1SW1)     /*!< DAC_OUT1 (PA4) connected to comparator inverting input 
                                                                                                  and close switch (PA0 for COMP1 only) */
#define COMP_INVERTINGINPUT_DAC2               (COMP_CSR_COMP1INSEL_2|COMP_CSR_COMP1INSEL_0) /*!< DAC_OUT2 (PA5) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO1                (COMP_CSR_COMP1INSEL_2|COMP_CSR_COMP1INSEL_1) /*!< IO (PA0 for COMP1 and PA2 for COMP2) connected to comparator inverting input */

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)          || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1)             || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1SWITCHCLOSED) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC2)             || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO1))
/**
  * @}
  */ 

/** @defgroup COMP_NonInvertingInput COMP NonInvertingInput
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1               ((uint32_t)0x00000000) /*!< I/O1 (PA1 for COMP1, PA3 for COMP2) 
                                                                             connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED  COMP_CSR_COMP1SW1  /*!< DAC ouput connected to comparator COMP1 non inverting input */

#define IS_COMP_NONINVERTINGINPUT(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_IO1) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED))
/**
  * @}
  */

/** @defgroup COMP_Output COMP Output
  * @{
  */

/* Output Redirection common for COMP1 and COMP2 */
#define COMP_OUTPUT_NONE                       ((uint32_t)0x00000000)                          /*!< COMP output isn't connected to other peripherals */
#define COMP_OUTPUT_TIM1BKIN                   COMP_CSR_COMP1OUTSEL_0                          /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1IC1                    COMP_CSR_COMP1OUTSEL_1                          /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM1OCREFCLR               (COMP_CSR_COMP1OUTSEL_1|COMP_CSR_COMP1OUTSEL_0) /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM2IC4                    COMP_CSR_COMP1OUTSEL_2                          /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR               (COMP_CSR_COMP1OUTSEL_2|COMP_CSR_COMP1OUTSEL_0) /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1                    (COMP_CSR_COMP1OUTSEL_2|COMP_CSR_COMP1OUTSEL_1) /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR               COMP_CSR_COMP1OUTSEL                            /*!< COMP output connected to TIM3 OCREF Clear */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR))

/**
  * @}
  */ 

/** @defgroup COMP_OutputLevel COMP OutputLevel
  * @{
  */ 
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OUTPUTLEVEL_LOW                   ((uint32_t)0x00000000)
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OUTPUTLEVEL_HIGH                  COMP_CSR_COMP1OUT
/**
  * @}
  */ 

/** @defgroup COMP_TriggerMode COMP TriggerMode
  * @{
  */
#define COMP_TRIGGERMODE_NONE                  ((uint32_t)0x00000000)  /*!< No External Interrupt trigger detection */
#define COMP_TRIGGERMODE_IT_RISING             ((uint32_t)0x00000001)  /*!< External Interrupt Mode with Rising edge trigger detection */
#define COMP_TRIGGERMODE_IT_FALLING            ((uint32_t)0x00000002)  /*!< External Interrupt Mode with Falling edge trigger detection */
#define COMP_TRIGGERMODE_IT_RISING_FALLING     ((uint32_t)0x00000003)  /*!< External Interrupt Mode with Rising/Falling edge trigger detection */

#define IS_COMP_TRIGGERMODE(MODE)  (((MODE) == COMP_TRIGGERMODE_NONE)       || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING)  || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_FALLING) || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING_FALLING))
/**
  * @}
  */ 

/** @defgroup COMP_WindowMode COMP WindowMode
  * @{
  */
#define COMP_WINDOWMODE_DISABLED               ((uint32_t)0x00000000)  /*!< Window mode disabled */
#define COMP_WINDOWMODE_ENABLED                COMP_CSR_WNDWEN         /*!< Window mode enabled: non inverting input of comparator 2
                                                                            is connected to the non inverting input of comparator 1 (PA1) */

#define IS_COMP_WINDOWMODE(WINDOWMODE) (((WINDOWMODE) == COMP_WINDOWMODE_DISABLED) || \
                                        ((WINDOWMODE) == COMP_WINDOWMODE_ENABLED))
/**
  * @}
  */

/** @defgroup COMP_ExtiLineEvent COMP ExtiLineEvent
  *        Elements values convention: XXXX0000
  *           - XXXX : Interrupt mask in the EMR/IMR/RTSR/FTSR register
  * @{   
  */  
#define COMP_EXTI_LINE_COMP1_EVENT             ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2_EVENT             ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to COMP2 */

/**
  * @}
  */

/** @defgroup COMP_Lock COMP Lock
  * @{   
  */  
#define COMP_LOCK_DISABLE                      ((uint32_t)0x00000000)
#define COMP_LOCK_ENABLE                       COMP_CSR_COMP1LOCK

#define COMP_STATE_BIT_LOCK                    ((uint32_t)0x10)
/**
  * @}
  */ 


/**
  * @}
  */ 
  
/* Exported macros -----------------------------------------------------------*/
/** @defgroup COMP_Exported_Macros COMP Exported Macros
  * @{
  */

/** @brief  Reset COMP handle state
  * @param  __HANDLE__: COMP handle.
  * @retval None
  */
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_COMP_STATE_RESET)

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __FLAG__: specifies the COMP Exti sources to be checked.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent
  * @retval The state of __FLAG__ (SET or RESET).
  */
#define __HAL_COMP_EXTI_GET_FLAG(__FLAG__)  (EXTI->PR & (__FLAG__))
     
/**
  * @brief Clear the COMP Exti flags.
  * @param  __FLAG__: specifies the COMP Exti sources to be cleared.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent
  * @retval None.
  */
#define __HAL_COMP_EXTI_CLEAR_FLAG(__FLAG__)   (EXTI->PR = (__FLAG__))

/**
  * @brief  Enable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_ENABLE_IT(__EXTILINE__)   (EXTI->IMR |= (__EXTILINE__))
                                             
/**
  * @brief  Disable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_DISABLE_IT(__EXTILINE__)  (EXTI->IMR &= ~(__EXTILINE__))

/**
  * @brief  Enable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_ENABLE(__EXTILINE__) (EXTI->RTSR |= (__EXTILINE__))

/**
  * @brief  Disable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_DISABLE(__EXTILINE__) (EXTI->RTSR &= ~(__EXTILINE__))

/**
  * @brief  Enable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_ENABLE(__EXTILINE__) (EXTI->FTSR |= (__EXTILINE__))

/**
  * @brief  Disable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_DISABLE(__EXTILINE__) (EXTI->FTSR &= ~(__EXTILINE__))

/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMP_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__) (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1_EVENT : \
                                                COMP_EXTI_LINE_COMP2_EVENT)
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions COMP Exported Functions
  * @{
  */
/** @addtogroup COMP_Exported_Functions_Group1 Initialization/de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 * @{
 */ 
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef     HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef     HAL_COMP_DeInit (COMP_HandleTypeDef *hcomp);
void                  HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void                  HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group2 I/O operation functions 
 *  @brief   Data transfers functions 
 * @{
 */   
/* IO operation functions *****************************************************/
HAL_StatusTypeDef     HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef     HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef     HAL_COMP_Start_IT(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef     HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp);
void                  HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group3 Peripheral Control functions 
 *  @brief   management functions
 * @{
 */   
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef     HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t              HAL_COMP_GetOutputLevel(COMP_HandleTypeDef *hcomp);

/* Callback in Interrupt mode */
void                  HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/** @addtogroup COMP_Exported_Functions_Group4 Peripheral State functions 
 *  @brief   Peripheral State functions
 * @{
 */   
/* Peripheral State and Error functions ***************************************/
uint32_t HAL_COMP_GetState(COMP_HandleTypeDef *hcomp);
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
  
#endif /* STM32F051x8 || STM32F058xx || */
       /* STM32F071xB || STM32F072xB || STM32F078xx || */
       /* STM32F091xC || STM32F098xx */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_HAL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

