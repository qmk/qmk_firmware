/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of OPAMP HAL Extension module.
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
#ifndef __STM32L1xx_HAL_OPAMP_EX_H
#define __STM32L1xx_HAL_OPAMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)
   
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMPEx
  * @{
  */



/* Exported types ------------------------------------------------------------*/
/* Exported constants ---------------------------------------------------------*/
/** @defgroup OPAMPEx_Exported_Constants OPAMPEx Exported Constants
  * @{
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
#define OPAMP_CSR_OPAXPD_ALL                                                   \
  (OPAMP_CSR_OPA1PD | OPAMP_CSR_OPA2PD | OPAMP_CSR_OPA3PD)
    
#define OPAMP_CSR_OPAXCAL_L_ALL                                                \
  (OPAMP_CSR_OPA1CAL_L | OPAMP_CSR_OPA2CAL_L | OPAMP_CSR_OPA3CAL_L)

#define OPAMP_CSR_OPAXCAL_H_ALL                                                \
  (OPAMP_CSR_OPA1CAL_H | OPAMP_CSR_OPA2CAL_H | OPAMP_CSR_OPA3CAL_H)
    
#define OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS                                      \
  (OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1 | \
   OPAMP_CSR_ANAWSEL1                                                        | \
   OPAMP_CSR_S3SEL2 | OPAMP_CSR_S4SEL2 | OPAMP_CSR_S5SEL2 | OPAMP_CSR_S6SEL2 | \
   OPAMP_CSR_ANAWSEL2 | OPAMP_CSR_S7SEL2                                     | \
   OPAMP_CSR_S3SEL3 | OPAMP_CSR_S4SEL3 | OPAMP_CSR_S5SEL3 | OPAMP_CSR_S6SEL3 | \
   OPAMP_CSR_ANAWSEL3                                                         )
#else
#define OPAMP_CSR_OPAXPD_ALL                                                   \
  (OPAMP_CSR_OPA1PD | OPAMP_CSR_OPA2PD)
    
#define OPAMP_CSR_OPAXCAL_L_ALL                                                \
  (OPAMP_CSR_OPA1CAL_L | OPAMP_CSR_OPA2CAL_L)

#define OPAMP_CSR_OPAXCAL_H_ALL                                                \
  (OPAMP_CSR_OPA1CAL_H | OPAMP_CSR_OPA2CAL_H)
    
#define OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS                                      \
  (OPAMP_CSR_S3SEL1 | OPAMP_CSR_S4SEL1 | OPAMP_CSR_S5SEL1 | OPAMP_CSR_S6SEL1 | \
   OPAMP_CSR_ANAWSEL1                                                        | \
   OPAMP_CSR_S3SEL2 | OPAMP_CSR_S4SEL2 | OPAMP_CSR_S5SEL2 | OPAMP_CSR_S6SEL2 | \
   OPAMP_CSR_ANAWSEL2 | OPAMP_CSR_S7SEL2                                      )
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */
  
/* Exported macro ------------------------------------------------------------*/
    
/** @defgroup OPAMPEx_Exported_Macro OPAMPEx Exported Macro
  * @{
  */
    
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
/**
  * @brief Enable internal analog switch SW1 to connect OPAMP3 ouput to ADC
  * switch matrix (ADC channel VCOMP, channel 26) and COMP1 non-inverting input
  * (OPAMP3 available on STM32L1 devices Cat.4 only).
  * @retval None
  */
#define __HAL_OPAMP_OPAMP3OUT_CONNECT_ADC_COMP1()    __HAL_RI_SWITCH_COMP1_SW1_CLOSE()

/**
  * @brief Disable internal analog switch SW1 to disconnect OPAMP3 ouput from 
  * ADC switch matrix (ADC channel VCOMP, channel 26) and COMP1 non-inverting
  * input.
  * @retval None
  */
#define __HAL_OPAMP_OPAMP3OUT_DISCONNECT_ADC_COMP1() __HAL_RI_SWITCH_COMP1_SW1_OPEN()
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */
    
/**
  * @}
  */
      
/* Private macro -------------------------------------------------------------*/

/** @defgroup OPAMPEx_Private_Macro OPAMPEx Private Macro
  * @{
  */
   
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
/**
  * @brief Get the OPAMP instance in decimal number for further
  * processing needs by HAL OPAMP driver functions.
  * @param __HANDLE__: OPAMP handle
  * @retval "0" for OPAMP1, "1" for OPAMP2, "2" for OPAMP3
  */
#define __OPAMP_INSTANCE_DECIMAL__(__HANDLE__)                                 \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     ((uint32_t)0)                                                             \
     :                                                                         \
     ( ( ((__HANDLE__)->Instance == OPAMP2)                                    \
       )?                                                                      \
        ((uint32_t)1)                                                          \
        :                                                                      \
        ((uint32_t)2)                                                          \
     )                                                                         \
  )
#else
/**
  * @brief Get the OPAMP instance in decimal number for further
  * processing needs by HAL OPAMP driver functions.
  * @param __HANDLE__: OPAMP handle
  * @retval "0" for OPAMP1, "1" for OPAMP2
  */
#define __OPAMP_INSTANCE_DECIMAL__(__HANDLE__)                                 \
  ( ( ((__HANDLE__)->Instance == OPAMP1)                                       \
    )?                                                                         \
     ((uint32_t)0)                                                             \
     :                                                                         \
     ((uint32_t)1)                                                             \
  )
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */
    
/* Exported functions --------------------------------------------------------*/
/** @addtogroup OPAMPEx_Exported_Functions
  * @{
  */

/* I/O operation functions  *****************************************************/
/** @defgroup OPAMPEx_Exported_Functions_Group1 Extended IO operation functions
  * @{
  */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2, OPAMP_HandleTypeDef *hopamp3);
#else
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2);
#endif /* STM32L151xD || STM32L152xD || STM32L162xD */
/**
  * @}
  */
/* Peripheral Control functions  ************************************************/
/** @addtogroup OPAMPEx_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_OPAMPEx_Unlock(OPAMP_HandleTypeDef *hopamp); 

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


#endif /* __STM32L1xx_HAL_OPAMP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
