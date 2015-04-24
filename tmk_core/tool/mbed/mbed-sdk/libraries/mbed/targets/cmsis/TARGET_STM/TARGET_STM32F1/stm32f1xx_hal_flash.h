/**
  ******************************************************************************
  * @file    stm32f1xx_hal_flash.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of Flash HAL module.
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
#ifndef __STM32F1xx_HAL_FLASH_H
#define __STM32F1xx_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"
   
/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */
  
/** @addtogroup FLASH_Private_Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE   ((uint32_t)50000)/* 50 s */
/**
  * @}
  */

/** @addtogroup FLASH_Private_Macros
  * @{
  */

#define IS_FLASH_TYPEPROGRAM(VALUE)  (((VALUE) == FLASH_TYPEPROGRAM_HALFWORD) || \
                                ((VALUE) == FLASH_TYPEPROGRAM_WORD)     || \
                                ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD))  

/**
  * @}
  */  

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */  


/**
  * @brief  FLASH Procedure structure definition
  */
typedef enum 
{
  FLASH_PROC_NONE              = 0, 
  FLASH_PROC_PAGEERASE         = 1,
  FLASH_PROC_MASSERASE         = 2,
  FLASH_PROC_PROGRAMHALFWORD   = 3,
  FLASH_PROC_PROGRAMWORD       = 4,
  FLASH_PROC_PROGRAMDOUBLEWORD = 5
} FLASH_ProcedureTypeDef;

/** 
  * @brief  FLASH handle Structure definition  
  */
typedef struct
{
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing; /* Internal variable to indicate which procedure is ongoing or not in IT context */
  
  __IO uint32_t               DataRemaining;    /* Internal variable to save the remaining pages to erase or half-word to program in IT context */
  
  __IO uint32_t               Address;          /* Internal variable to save address selected for program or erase */
  
  __IO uint64_t               Data;             /* Internal variable to save data to be programmed */

  HAL_LockTypeDef             Lock;             /* FLASH locking object                */

  __IO uint32_t               ErrorCode;        /* FLASH error code                    */

} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */  

/** @defgroup FLASH_Error_Codes FLASH Error Codes
  * @{
  */
 
#define HAL_FLASH_ERROR_NONE      ((uint32_t)0x00)
#define HAL_FLASH_ERROR_PROG        ((uint32_t)0x01)
#define HAL_FLASH_ERROR_WRP       ((uint32_t)0x02)
#define HAL_FLASH_ERROR_OPTV      ((uint32_t)0x04)

/**
  * @}
  */


/** @defgroup FLASH_Type_Program Type Program
  * @{
  */ 
#define FLASH_TYPEPROGRAM_HALFWORD   ((uint32_t)0x01)  /*!<Program a half-word (16-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_WORD       ((uint32_t)0x02)  /*!<Program a word (32-bit) at a specified address.*/
#define FLASH_TYPEPROGRAM_DOUBLEWORD ((uint32_t)0x03)  /*!<Program a double word (64-bit) at a specified address*/

/**
  * @}
  */

/**
  * @}
  */  
  
/* Exported macro ------------------------------------------------------------*/

/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
 *  @brief macros to control FLASH features 
 *  @{
 */
 
/**
  * @brief  Enable the FLASH half cycle access.
  * @note   halfcycle access can only be used with a low-frequency clock of less than
            8 MHz that can be obtained with the use of HSI or HSE but not of PLL.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_ENABLE()  (FLASH->ACR |= FLASH_ACR_HLFCYA)

/**
  * @brief  Disable the FLASH half cycle access.
  * @note   halfcycle access can only be used with a low-frequency clock of less than
            8 MHz that can be obtained with the use of HSI or HSE but not of PLL.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_DISABLE() (FLASH->ACR &= (~FLASH_ACR_HLFCYA))

/**
  * @}
  */ 

/* Include FLASH HAL Extended module */
#include "stm32f1xx_hal_flash_ex.h"  

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */
  
/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

/* FLASH IRQ handler method */
void       HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */ 
void       HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void       HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
  */
/* Peripheral State and Error functions ***************************************/
uint32_t HAL_FLASH_GetError(void);

/**
  * @}
  */

/**
  * @}
  */

/* Private function -------------------------------------------------*/
/** @addtogroup FLASH_Private_Functions
 * @{
 */
void                    FLASH_PageErase(uint32_t PageAddress);
HAL_StatusTypeDef       FLASH_WaitForLastOperation(uint32_t Timeout);
void                    FLASH_SetErrorCode(void);
void                    FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);

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

#endif /* __STM32F1xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

