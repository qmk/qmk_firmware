/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of OPAMP HAL module.
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
#ifndef __STM32L1xx_HAL_OPAMP_H
#define __STM32L1xx_HAL_OPAMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup OPAMP_Exported_Types OPAMP Exported Types
  * @{
  */
/** 
  * @brief  OPAMP Init structure definition  
  */
  
typedef struct
{
  uint32_t PowerSupplyRange;            /*!< Specifies the power supply range: above or under 2.4V.
                                             This parameter must be a value of @ref OPAMP_PowerSupplyRange
                                             Caution: This parameter is common to all OPAMP instances: a modification of this parameter for the selected OPAMP impacts the other OPAMP instances. */
  
  uint32_t UserTrimming;                /*!< Specifies the trimming mode 
                                             This parameter must be a value of @ref OPAMP_UserTrimming 
                                             UserTrimming is either factory or user trimming.
                                             Caution: This parameter is common to all OPAMP instances: a modification of this parameter for the selected OPAMP impacts the other OPAMP instances. */
  
  uint32_t Mode;                        /*!< Specifies the OPAMP mode
                                             This parameter must be a value of @ref OPAMP_Mode 
                                             mode is either Standalone or Follower */

  uint32_t InvertingInput;              /*!< Specifies the inverting input in Standalone mode
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInput 
                                                 InvertingInput is either VM0 or VM1
                                               - In Follower mode:     i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter is Not Applicable */ 

  uint32_t NonInvertingInput;           /*!< Specifies the non inverting input of the opamp: 
                                             This parameter must be a value of @ref OPAMP_NonInvertingInput 
                                             NonInvertingInput is either VP0, VP1 or VP2 */                                   

  uint32_t PowerMode;                   /*!< Specifies the power mode Normal or Low-Power.
                                             This parameter must be a value of @ref OPAMP_PowerMode */

  uint32_t TrimmingValueP;              /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden) */

  uint32_t TrimmingValueN;              /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden) */

  uint32_t TrimmingValuePLowPower;      /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden) */

  uint32_t TrimmingValueNLowPower;      /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 0 and Max_Data = 30 (Trimming value 31 is forbidden) */

}OPAMP_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 

typedef enum
{
  HAL_OPAMP_STATE_RESET               = 0x00000000, /*!< OPMAP is not yet Initialized          */
  
  HAL_OPAMP_STATE_READY               = 0x00000001, /*!< OPAMP is initialized and ready for use */
  HAL_OPAMP_STATE_CALIBBUSY           = 0x00000002, /*!< OPAMP is enabled in auto calibration mode */
 
  HAL_OPAMP_STATE_BUSY                = 0x00000004, /*!< OPAMP is enabled and running in normal mode */                                                                           
  HAL_OPAMP_STATE_BUSYLOCKED          = 0x00000005, /*!< OPAMP is locked
                                                         only system reset allows reconfiguring the opamp. */
    
}HAL_OPAMP_StateTypeDef;

/** 
  * @brief  OPAMP Handle Structure definition 
  */ 
typedef struct
{
  OPAMP_TypeDef       *Instance;                    /*!< OPAMP instance's registers base address   */
  OPAMP_InitTypeDef   Init;                         /*!< OPAMP required parameters */
  HAL_StatusTypeDef Status;                         /*!< OPAMP peripheral status   */
  HAL_LockTypeDef   Lock;                           /*!< Locking object          */
  __IO HAL_OPAMP_StateTypeDef  State;               /*!< OPAMP communication state */
  
} OPAMP_HandleTypeDef;

/** 
  * @brief OPAMP_TrimmingValueTypeDef @brief   definition 
  */ 

typedef  uint32_t OPAMP_TrimmingValueTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Constants OPAMP Exported Constants
  * @{
  */

/**
  * OTR register Mask 
  */
#define OPAMP_TRIM_VALUE_MASK   OPAMP_OTR_AO1_OPT_OFFSET_TRIM_LOW
    
/**
  * CSR register Mask 
  */
#define OPAMP_CSR_INSTANCE_OFFSET   ((uint32_t)  8) /* Offset of each OPAMP instance into register CSR */
#define OPAMP_OTR_INSTANCE_OFFSET   ((uint32_t) 10) /* Offset of each OPAMP instance into register OTR */
    
        
/** @defgroup OPAMP_Mode OPAMP Mode
  * @{
  */
#define OPAMP_STANDALONE_MODE            ((uint32_t)0x00000000) /*!< OPAMP standalone mode */
#define OPAMP_FOLLOWER_MODE              ((uint32_t)0x00000001) /*!< OPAMP follower mode */

#define IS_OPAMP_FUNCTIONAL_NORMALMODE(INPUT) (((INPUT) == OPAMP_STANDALONE_MODE) || \
                                               ((INPUT) == OPAMP_FOLLOWER_MODE))
/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInput OPAMP NonInvertingInput
  * @{
  */
#define OPAMP_NONINVERTINGINPUT_VP0      ((uint32_t)0x00000000)  /*!< Comparator non-inverting input connected to dedicated IO pin low-leakage */
#define OPAMP_NONINVERTINGINPUT_DAC_CH1  ((uint32_t)0x00000001)  /*!< Comparator non-inverting input connected internally to DAC channel 1 */
#define OPAMP_NONINVERTINGINPUT_DAC_CH2  ((uint32_t)0x00000002)  /*!< Comparator non-inverting input connected internally to DAC channel 2. Available on OPAMP2 only. */

#define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NONINVERTINGINPUT_VP0)     || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH1) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_DAC_CH2)   )
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput OPAMP InvertingInput
  * @{
  */
#define OPAMP_INVERTINGINPUT_VM0         ((uint32_t)0x00000000)  /*!< Comparator inverting input connected to dedicated IO pin low-leakage */
#define OPAMP_INVERTINGINPUT_VM1         ((uint32_t)0x00000001)  /*!< Comparator inverting input connected to alternative IO pin available on some device packages */

#define OPAMP_INVERTINGINPUT_VINM        OPAMP_INVERTINGINPUT_VM1  /*!< Alternate name for comparator inverting input connected to alternative IO pin available on some device packages */

#define IOPAMP_INVERTINGINPUT_VM0        OPAMP_INVERTINGINPUT_VM0  /* For compatibility with other STM32 devices */
#define IOPAMP_INVERTINGINPUT_VM1        OPAMP_INVERTINGINPUT_VM1  /* For compatibility with other STM32 devices */

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_INVERTINGINPUT_VM0) || \
                                         ((INPUT) == OPAMP_INVERTINGINPUT_VM1)   )
/**
  * @}
  */

/** @defgroup OPAMP_PowerMode OPAMP PowerMode
  * @{
  */
#define OPAMP_POWERMODE_NORMAL        ((uint32_t)0x00000000)
#define OPAMP_POWERMODE_LOWPOWER      ((uint32_t)0x00000001)

#define IS_OPAMP_POWERMODE(TRIMMING) (((TRIMMING) == OPAMP_POWERMODE_NORMAL) || \
                                      ((TRIMMING) == OPAMP_POWERMODE_LOWPOWER) )
/**
  * @}
  */

/** @defgroup OPAMP_PowerSupplyRange OPAMP PowerSupplyRange
  * @{
  */
#define OPAMP_POWERSUPPLY_LOW          ((uint32_t)0x00000000)  /*!< Power supply range low (VDDA lower than 2.4V) */
#define OPAMP_POWERSUPPLY_HIGH         OPAMP_CSR_AOP_RANGE     /*!< Power supply range high (VDDA higher than 2.4V) */

#define IS_OPAMP_POWER_SUPPLY_RANGE(RANGE) (((RANGE) == OPAMP_POWERSUPPLY_LOW) || \
                                            ((RANGE) == OPAMP_POWERSUPPLY_HIGH)  )
/**
  * @}
  */ 

/** @defgroup OPAMP_UserTrimming OPAMP UserTrimming
  * @{
  */
#define OPAMP_TRIMMING_FACTORY        ((uint32_t)0x00000000)                          /*!< Factory trimming */
#define OPAMP_TRIMMING_USER           OPAMP_OTR_OT_USER                               /*!< User trimming */

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_TRIMMING_FACTORY) || \
                                     ((TRIMMING) == OPAMP_TRIMMING_USER))
/**
  * @}
  */

/** @defgroup OPAMP_FactoryTrimming OPAMP FactoryTrimming
  * @{
  */
#define OPAMP_FACTORYTRIMMING_DUMMY    ((uint32_t)0xFFFFFFFF)                           /*!< Dummy value if trimming value could not be retrieved */

#define OPAMP_FACTORYTRIMMING_P        ((uint32_t)0x00000000)                           /*!< Offset trimming P */
#define OPAMP_FACTORYTRIMMING_N        POSITION_VAL(OPAMP_OTR_AO1_OPT_OFFSET_TRIM_HIGH) /*!< Offset trimming N */

#define IS_OPAMP_FACTORYTRIMMING(TRIMMING) (((TRIMMING) == OPAMP_FACTORYTRIMMING_N) || \
                                            ((TRIMMING) == OPAMP_FACTORYTRIMMING_P)   )
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup OPAMP_Private_Constants OPAMP Private Constants
  * @{
  */

/* Offset trimming time: during calibration, minimum time needed between two  */
/* steps to have 1 mV accuracy.                                               */
/* Refer to datasheet, electrical characteristics: parameter tOFFTRIM Typ=1ms.*/
/* Unit: ms.                                                                  */
#define OPAMP_TRIMMING_DELAY               ((uint32_t) 1)

/**
  * @}
  */

    
/* Exported macros -----------------------------------------------------------*/

/** @defgroup OPAMP_Private_Macro OPAMP Private Macro
  * @{
  */
    
/** @brief Reset OPAMP handle state
  * @param  __HANDLE__: OPAMP handle.
  * @retval None
  */
#define __HAL_OPAMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_OPAMP_STATE_RESET)
    
/**
  * @}
  */

    
/* Private macro -------------------------------------------------------------*/

/** @defgroup OPAMP_Private_Macro OPAMP Private Macro
  * @{
  */

/**
  * @brief Select the OPAMP bit OPAxPD (power-down) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_OPAXPD(__HANDLE__)                                         \
  (OPAMP_CSR_OPA1PD << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bit S3SELx (switch 3) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_S3SELX(__HANDLE__)                                         \
  (OPAMP_CSR_S3SEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit S4SELx (switch 4) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_S4SELX(__HANDLE__)                                         \
  (OPAMP_CSR_S4SEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit S5SELx (switch 5) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_S5SELX(__HANDLE__)                                         \
  (OPAMP_CSR_S5SEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit S3SELx (switch 6) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_S6SELX(__HANDLE__)                                         \
  (OPAMP_CSR_S6SEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit OPAxCAL_L (offset calibration for differential 
  * pair P) corresponding to the selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_OPAXCAL_L(__HANDLE__)                                      \
  (OPAMP_CSR_OPA1CAL_L << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bit OPAxCAL_H (offset calibration for differential 
  * pair N) corresponding to the selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_OPAXCAL_H(__HANDLE__)                                      \
  (OPAMP_CSR_OPA1CAL_H << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))

/**
  * @brief Select the OPAMP bit OPAxLPM (low power mode) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_OPAXLPM(__HANDLE__)                                        \
  (OPAMP_CSR_OPA1LPM << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))
    
/**
  * @brief Select the OPAMP bits of all switches corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_ALL_SWITCHES(__HANDLE__)                                   \
  ( ( ((__HANDLE__)->Instance != OPAMP2)                                       \
    )?                                                                         \
     (                                                                         \
       ((OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1) << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))  \
       |                                                                       \
       (OPAMP_CSR_ANAWSEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__)))        \
     )                                                                         \
    :                                                                          \
     (                                                                         \
       ((OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1) << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__) * OPAMP_CSR_INSTANCE_OFFSET))  \
       |                                                                       \
       (OPAMP_CSR_ANAWSEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__)))        \
       |                                                                       \
       (OPAMP_CSR_S7SEL2)                                                      \
     )                                                                         \
  )
    
/**
  * @brief Select the OPAMP bit ANAWSELx (switch SanA) corresponding to the
  * selected OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_ANAWSELX(__HANDLE__)                                       \
  (OPAMP_CSR_ANAWSEL1 << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__)))

/**
  * @brief Select the OPAMP bit OPAxCALOUT in function of the selected 
  * OPAMP instance.
  * @param __HANDLE__: OPAMP handle
  * @retval None
  */
#define __OPAMP_CSR_OPAXCALOUT(__HANDLE__)                                     \
  (OPAMP_CSR_OPA1CALOUT << (__OPAMP_INSTANCE_DECIMAL__(__HANDLE__)))

/**
  * @brief Select the OPAMP trimming bits position value (position of LSB) 
  * in register OPAMP_OTR or register OPAMP_LPOTR in function of the selected
  * OPAMP instance and the transistors differential pair high (PMOS) or 
  * low (NMOS).
  * @param __HANDLE__: OPAMP handle
  * @param __TRIM_HIGH_LOW__: transistors differential pair high or low.
  * Must be a value of @ref OPAMP_FactoryTrimming.
  * @retval None
  */
#define __OPAMP_OFFSET_TRIM_BITSPOSITION(__HANDLE__, __TRIM_HIGH_LOW__)        \
  ((__OPAMP_INSTANCE_DECIMAL__((__HANDLE__)) * OPAMP_OTR_INSTANCE_OFFSET) + (__TRIM_HIGH_LOW__))
    
/**
  * @brief Shift the OPAMP trimming bits to register OPAMP_OTR or register 
  * OPAMP_LPOTR in function of the selected OPAMP instance and the transistors
  * differential pair high (PMOS) or low (NMOS).
  * @param __HANDLE__: OPAMP handle
  * @param __TRIM_HIGH_LOW__: transistors differential pair high or low.
  * Must be a value of @ref OPAMP_FactoryTrimming.
  * @param __TRIMMING_VALUE__: Trimming value
  * @retval None
  */
#define __OPAMP_OFFSET_TRIM_SET(__HANDLE__, __TRIM_HIGH_LOW__, __TRIMMING_VALUE__) \
  ((__TRIMMING_VALUE__) << (__OPAMP_OFFSET_TRIM_BITSPOSITION((__HANDLE__), (__TRIM_HIGH_LOW__))))
    
/**
  * @brief Check that trimming value is within correct range
  * @param TRIMMINGVALUE: OPAMP trimming value
  * @retval None
  */
#define IS_OPAMP_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 0x1E)

/**
  * @}
  */

    
/* Include OPAMP HAL Extension module */
#include "stm32l1xx_hal_opamp_ex.h"

/* Exported functions --------------------------------------------------------*/

/** @addtogroup OPAMP_Exported_Functions
  * @{
  */ 

/** @addtogroup OPAMP_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_DeInit (OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp);
/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group2
  * @{
  */
/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp);
OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset);
/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group3
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp);
/**
  * @}
  */

/** @addtogroup OPAMP_Exported_Functions_Group4
  * @{
  */
/* Peripheral State functions  **************************************************/
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp);
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

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE || STM32L162xC || STM32L152xC || STM32L151xC */
#ifdef __cplusplus
}
#endif

#endif /* __STM32L1xx_HAL_OPAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
