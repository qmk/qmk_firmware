/**
  ******************************************************************************
  * @file    stm32l1xx_hal_comp.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
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
#ifndef __STM32L1xx_HAL_COMP_H
#define __STM32L1xx_HAL_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup COMP
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

  uint32_t InvertingInput;        /*!< Selects the inverting input of the comparator.
                                       This parameter can be a value of @ref COMP_InvertingInput
                                       Note: Inverting input can be changed on the fly, while comparator is running.
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded (On COMP1, inverting input is fixed to Vrefint). */

  uint32_t NonInvertingInput;     /*!< Selects the non inverting input of the comparator.
                                       This parameter can be a value of @ref COMPEx_NonInvertingInput */

  uint32_t Output;                /*!< Selects the output redirection of the comparator.
                                       This parameter can be a value of @ref COMP_Output
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded. */

  uint32_t Mode;                  /*!< Selects the operating consumption mode of the comparator
                                       to adjust the speed/consumption.
                                       This parameter can be a value of @ref COMP_Mode
                                       Note: This feature is available on COMP2 only. If COMP1 is selected, this parameter is discarded. */
                                         
  uint32_t WindowMode;            /*!< Selects the window mode of the 2 comparators.
                                       If enabled, non-inverting inputs of the 2 comparators are connected together and are using inputs of COMP2 only (COMP1 non-inverting input is no more accessible, even from ADC channel VCOMP).
                                       This parameter can be a value of @ref COMP_WindowMode
                                       Note: This feature must be enabled from COMP2 instance. If COMP1 is selected, this parameter is discarded. */

  uint32_t TriggerMode;           /*!< Selects the trigger mode of the comparator when using interruption on EXTI line (interrupt mode).
                                       This parameter can be a value of @ref COMP_TriggerMode
                                       Note: This feature is used with function "HAL_COMP_Start_IT()". In all other functions, this parameter is discarded. */

  uint32_t NonInvertingInputPull; /*!< Selects the internal pulling resistor connected on non inverting input.
                                       This parameter can be a value of @ref COMP_NonInvertingInputPull
                                       Note: To avoid extra power consumption, only one resistor should be enabled at a time.
                                       Note: This feature is available on COMP1 only. If COMP2 is selected, this parameter is discarded. */
  
}COMP_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_COMP_STATE_RESET             = 0x00,    /*!< COMP not yet initialized or disabled             */
  HAL_COMP_STATE_READY             = 0x01,    /*!< COMP initialized and ready for use               */
  HAL_COMP_STATE_READY_LOCKED      = 0x11,    /*!< COMP initialized but the configuration is locked */
  HAL_COMP_STATE_BUSY              = 0x02,    /*!< COMP is running                                  */
  HAL_COMP_STATE_BUSY_LOCKED       = 0x12     /*!< COMP is running and the configuration is locked  */
}HAL_COMP_StateTypeDef;

/** 
  * @brief  COMP Handle Structure definition  
  */ 
typedef struct
{
  COMP_TypeDef       *Instance;       /*!< Register base address    */
  COMP_InitTypeDef   Init;            /*!< COMP required parameters */
  HAL_LockTypeDef    Lock;            /*!< Locking object           */
  __IO HAL_COMP_StateTypeDef  State;  /*!< COMP communication state */
} COMP_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup COMP_Exported_Constants COMP Exported Constants
  * @{
  */

/** @defgroup COMP_Output COMP Output
  * @{
  */
#define COMP_OUTPUT_TIM2IC4                     ((uint32_t)0x00000000)                                      /*!< COMP2 output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR                (                                        COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC4                     (                    COMP_CSR_OUTSEL_1                    ) /*!< COMP2 output connected to TIM3 Input Capture 4 */
#define COMP_OUTPUT_TIM3OCREFCLR                (                    COMP_CSR_OUTSEL_1 | COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM3 OCREF Clear */
#define COMP_OUTPUT_TIM4IC4                     (COMP_CSR_OUTSEL_2                                        ) /*!< COMP2 output connected to TIM4 Input Capture 4 */
#define COMP_OUTPUT_TIM4OCREFCLR                (COMP_CSR_OUTSEL_2                     | COMP_CSR_OUTSEL_0) /*!< COMP2 output connected to TIM4 OCREF Clear */
#define COMP_OUTPUT_TIM10IC1                    (COMP_CSR_OUTSEL_2 | COMP_CSR_OUTSEL_1                    ) /*!< COMP2 output connected to TIM10 Input Capture 1 */
#define COMP_OUTPUT_NONE                        (COMP_CSR_OUTSEL_2 | COMP_CSR_OUTSEL_1 | COMP_CSR_OUTSEL_0) /*!< COMP2 output is not connected to other peripherals */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_TIM2IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4OCREFCLR) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM10IC1)     || \
                                ((OUTPUT) == COMP_OUTPUT_NONE)           )
/**
  * @}
  */ 

/** @defgroup COMP_InvertingInput COMP InvertingInput
  * @{
  */
/* Inverting Input specific to COMP2 */
#define COMP_INVERTINGINPUT_IO                  (                                      COMP_CSR_INSEL_0) /*!< External I/O (COMP2_INM connected to pin PB3) connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_VREFINT             (                   COMP_CSR_INSEL_1                   ) /*!< VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT          (                   COMP_CSR_INSEL_1 | COMP_CSR_INSEL_0) /*!< 3/4 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT          (COMP_CSR_INSEL_2                                      ) /*!< 1/2 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_1_4VREFINT          (COMP_CSR_INSEL_2                    | COMP_CSR_INSEL_0) /*!< 1/4 VREFINT connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_DAC1                (COMP_CSR_INSEL_2 | COMP_CSR_INSEL_1                   ) /*!< DAC_OUT1 (PA4) connected to comparator 2 inverting input */
#define COMP_INVERTINGINPUT_DAC2                (COMP_CSR_INSEL_2 | COMP_CSR_INSEL_1 | COMP_CSR_INSEL_0) /*!< DAC2_OUT (PA5) connected to comparator 2 inverting input */

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_IO)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)    || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT) || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC2)         )
/**
  * @}
  */

/** @defgroup COMP_Mode COMP Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_MODE_LOWSPEED          ((uint32_t)0x00000000)  /*!< Low Speed */
#define COMP_MODE_HIGHSPEED         COMP_CSR_SPEED          /*!< High Speed */

#define IS_COMP_MODE(SPEED)    (((SPEED) == COMP_MODE_LOWSPEED) || \
                                ((SPEED) == COMP_MODE_HIGHSPEED))
/**
  * @}
  */

/** @defgroup COMP_WindowMode COMP WindowMode
  * @{
  */
#define COMP_WINDOWMODE_DISABLED               ((uint32_t)0x00000000)  /*!< Window mode disabled: COMP1 non-inverting input is independant */
#define COMP_WINDOWMODE_ENABLED                COMP_CSR_WNDWE          /*!< Window mode enabled: COMP1 non-inverting input is no more accessible, even from ADC channel VCOMP) (connected to COMP2 non-inverting input) */

#define IS_COMP_WINDOWMODE(WINDOWMODE) (((WINDOWMODE) == COMP_WINDOWMODE_DISABLED) || \
                                        ((WINDOWMODE) == COMP_WINDOWMODE_ENABLED))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel COMP OutputLevel
  * @{
  */ 
/* Comparator output is low when the non-inverting input is at a lower        */
/* voltage than the inverting input.                                          */
#define COMP_OUTPUTLEVEL_LOW                   ((uint32_t)0x00000000)

/* Comparator output is high when the non-inverting input is at a higher      */
/* voltage than the inverting input.                                          */
#define COMP_OUTPUTLEVEL_HIGH                  ((uint32_t)0x00000001)
/**
  * @}
  */ 

/** @defgroup COMP_TriggerMode COMP TriggerMode 
  * @{
  */
#define COMP_TRIGGERMODE_NONE                  ((uint32_t)0x00000000)   /*!< No External Interrupt trigger detection */
#define COMP_TRIGGERMODE_IT_RISING             ((uint32_t)0x00000001)   /*!< External Interrupt Mode with Rising edge trigger detection */
#define COMP_TRIGGERMODE_IT_FALLING            ((uint32_t)0x00000002)   /*!< External Interrupt Mode with Falling edge trigger detection */
#define COMP_TRIGGERMODE_IT_RISING_FALLING     ((uint32_t)0x00000003)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */

#define IS_COMP_TRIGGERMODE(MODE)  (((MODE) == COMP_TRIGGERMODE_NONE)             || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING)        || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_FALLING)       || \
                                    ((MODE) == COMP_TRIGGERMODE_IT_RISING_FALLING)  )
/**
  * @}
  */ 

/** @defgroup COMP_ExtiLineEvent COMP ExtiLineEvent
  * @{
  */
#define COMP_EXTI_LINE_COMP1_EVENT             EXTI_RTSR_TR21  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2_EVENT             EXTI_RTSR_TR22  /*!< External interrupt line 22 Connected to COMP2 */

/**
  * @}
  */

/** @defgroup COMP_NonInvertingInputPull COMP NonInvertingInputPull
  * @{
  */
#define COMP_NONINVERTINGINPUT_NOPULL           ((uint32_t)0x00000000)  /*!< No internal pull-up or pull-down resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_10KPU            COMP_CSR_10KPU          /*!< Internal 10kOhm pull-up resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_10KPD            COMP_CSR_10KPD          /*!< Internal 10kOhm pull-down resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_400KPU           COMP_CSR_400KPU         /*!< Internal 400kOhm pull-up resistor connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_400KPD           COMP_CSR_400KPD         /*!< Internal 400kOhm pull-down resistor connected to comparator non inverting input */

#define IS_COMP_NONINVERTINGINPUTPULL(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_NOPULL) || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_10KPU)  || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_10KPD)  || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_400KPU) || \
                                              ((INPUT) == COMP_NONINVERTINGINPUT_400KPD)   )
/**
  * @}
  */ 

/**
  * @}
  */ 


/* Exported macro ------------------------------------------------------------*/

/** @defgroup COMP_Exported_Macro COMP Exported Macro
  * @{
  */

/** @brief Reset COMP handle state
  * @param  __HANDLE__: COMP handle.
  * @retval None
  */
#define __HAL_COMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_COMP_STATE_RESET)

/**
  * @brief Enables the specified comparator
  * @param  __HANDLE__: COMP handle.
  * @retval None.
  */
#define __HAL_COMP_ENABLE(__HANDLE__)                                          \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     SET_BIT(COMP->CSR, COMP_CSR_CMP1EN)                                       \
     :                                                                         \
     MODIFY_REG(COMP->CSR, COMP_CSR_INSEL, (__HANDLE__)->Init.InvertingInput ) \
  )

/**
  * @brief Disables the specified comparator
  * @param  __HANDLE__: COMP handle.
  * @retval None.
  */
#define __HAL_COMP_DISABLE(__HANDLE__)                                         \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     CLEAR_BIT(COMP->CSR, COMP_CSR_CMP1EN)                                     \
     :                                                                         \
     CLEAR_BIT(COMP->CSR, COMP_CSR_INSEL)                                      \
  )
    
    
/** @brief  Checks whether the specified COMP flag is set or not.
  * @param  __HANDLE__: specifies the COMP Handle.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg COMP_FLAG_LOCK:  lock flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_COMP_GET_FLAG(__HANDLE__, __FLAG__) (READ_BIT((__HANDLE__)->Instance->CSR, (__FLAG__)) == (__FLAG__))   


/**
  * @brief Enable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_ENABLE(__EXTILINE__) (SET_BIT(EXTI->RTSR, (__EXTILINE__)))

/**
  * @brief  Disable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_DISABLE(__EXTILINE__) (CLEAR_BIT(EXTI->RTSR, (__EXTILINE__)))

/**
  * @brief Enable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_ENABLE(__EXTILINE__) (SET_BIT(EXTI->FTSR, (__EXTILINE__)))

/**
  * @brief  Disable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_DISABLE(__EXTILINE__) (CLEAR_BIT(EXTI->FTSR, (__EXTILINE__)))

/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMP_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__)                                 \
  ( ( ((__INSTANCE__) == COMP1)                                                \
    )?                                                                         \
     (COMP_EXTI_LINE_COMP1_EVENT)                                              \
     :                                                                         \
     (COMP_EXTI_LINE_COMP2_EVENT)                                              \
  )
    
/**
  * @brief Enable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_ENABLE_IT(__EXTILINE__) (SET_BIT(EXTI->IMR, (__EXTILINE__)))

/**
  * @brief Disable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_DISABLE_IT(__EXTILINE__) (CLEAR_BIT(EXTI->IMR, (__EXTILINE__)))

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __FLAG__: specifies the COMP Exti sources to be checked.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval The state of __FLAG__ (SET or RESET).
  */
#define __HAL_COMP_EXTI_GET_FLAG(__FLAG__) (READ_BIT(EXTI->PR, (__FLAG__)))
     
/**
  * @brief Clear the COMP Exti flags.
  * @param  __FLAG__: specifies the COMP Exti sources to be cleared.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_CLEAR_FLAG(__FLAG__)   (EXTI->PR = (__FLAG__))

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to trig.
  *          This parameter can be a value of @ref COMP_ExtiLineEvent 
  * @retval None
  */
#define __HAL_COMP_EXTI_GENERATE_SWIT(__EXTILINE__) (SET_BIT(EXTI->SWIER, (__EXTILINE__)))

/**
  * @}
  */ 
    
/* Private macro -------------------------------------------------------------*/

/** @defgroup COMP_Private_Macro COMP Private Macro
  * @{
  */

/**
  * @brief Select the COMP register CSR bit CMPxOUT corresponding to the 
  * selected COMP instance.
  * @param __HANDLE__: COMP handle
  * @retval Comparator register CSR bit COMP_CSR_CMP1OUT or COMP_CSR_CMP2OUT
  */
#define __COMP_CSR_CMPXOUT(__HANDLE__)                                         \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     (COMP_CSR_CMP1OUT)                                                        \
     :                                                                         \
     (COMP_CSR_CMP2OUT)                                                        \
  )

/**
  * @brief Verification of COMP state: enabled or disabled
  * @param __HANDLE__: COMP handle
  * @retval SET (COMP enabled) or RESET (COMP disabled)
  */
#define __COMP_IS_ENABLED(__HANDLE__)                                          \
  ( ( ((__HANDLE__)->Instance == COMP1)                                        \
    )?                                                                         \
     (((READ_BIT(COMP->CSR , COMP_CSR_CMP1EN) == COMP_CSR_CMP1EN)              \
      ) ? SET : RESET)                                                         \
     :                                                                         \
     (((READ_BIT(COMP->CSR , COMP_CSR_INSEL) != RESET)                         \
      ) ? SET : RESET)                                                         \
  )
    
/**
  * @}
  */ 

    
/* Include COMP HAL Extension module */
#include "stm32l1xx_hal_comp_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_Exported_Functions
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
/** @addtogroup COMP_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_DeInit (COMP_HandleTypeDef *hcomp);
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp);
void HAL_COMP_MspDeInit(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* I/O operation functions  *****************************************************/
/** @addtogroup COMP_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Start_IT(COMP_HandleTypeDef *hcomp);
HAL_StatusTypeDef HAL_COMP_Stop_IT(COMP_HandleTypeDef *hcomp);
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral Control functions  ************************************************/
/** @addtogroup COMP_Exported_Functions_Group3
  * @{
  */
HAL_StatusTypeDef HAL_COMP_Lock(COMP_HandleTypeDef *hcomp);
uint32_t HAL_COMP_GetOutputLevel(COMP_HandleTypeDef *hcomp);

/* Callback in Interrupt mode */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
/**
  * @}
  */

/* Peripheral State functions  **************************************************/
/** @addtogroup COMP_Exported_Functions_Group4
  * @{
  */
HAL_COMP_StateTypeDef HAL_COMP_GetState(COMP_HandleTypeDef *hcomp);
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

#endif /* __STM32L1xx_HAL_COMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
