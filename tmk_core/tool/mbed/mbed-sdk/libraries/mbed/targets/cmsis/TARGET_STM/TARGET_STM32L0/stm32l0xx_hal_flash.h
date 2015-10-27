/**
  ******************************************************************************
  * @file    stm32l0xx_hal_flash.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of Flash HAL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0XX_HAL_FLASH_H
#define __STM32L0XX_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */  

/**
  * @brief  FLASH Procedure structure definition
  */
typedef enum 
{
  FLASH_PROC_NONE = 0, 
  FLASH_PROC_PAGEERASE,
  FLASH_PROC_PROGRAM
} FLASH_ProcedureTypeDef;

/**
 * @brief FLASH Erase structure definition
 */
 typedef struct
 {
    uint32_t TypeErase;    /*!< TypeErase: Page Erase only.
                             This parameter can be a value of @ref FLASHEx_Type_Erase */
    
    uint32_t PageAddress ; /*!< PageAddress : Initial FLASH address to be erased
                             This parameter must be a value belonging to FLASH Programm address (depending on the devices) */
    
    uint32_t NbPages;      /*!< NbPages: Number of pages to be erased.
                             This parameter must be a value between 1 and (max number of pages - value of Initial page)*/

 } FLASH_EraseInitTypeDef;
/**
  * @}
  */ 
   
   
/** @defgroup FLASH_Private_Types FLASH Private Types
  * @{
  */  

/** 
  * @brief  FLASH handle Structure definition  
  */
typedef struct
{
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing;  /* Internal variable to indicate which procedure is ongoing or not in IT context */
  
  __IO uint32_t               NbPagesToErase;    /* Internal variable to save the remaining sectors to erase in IT context */
  
  __IO uint32_t               Page;              /* Internal variable to define the current sector which is erasing */
  
  __IO uint32_t               Address;           /* Internal variable to save address selected for program */
  
  HAL_LockTypeDef             Lock;              /* FLASH locking object */

  __IO uint32_t               ErrorCode;         /* FLASH error code */

}FLASH_ProcessTypeDef;
/**
  * @}
  */ 

/** @defgroup FLASH_Private_Variables FLASH Private Variables
  * @{
  */  

/**
  * @brief  Variable used for Program/Erase sectors under interruption.
  *     Put as extern as used also in flash_ex.c. 
  */
extern FLASH_ProcessTypeDef ProcFlash;   
/**
  * @}
  */

/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_TIMEOUT_VALUE        ((uint32_t)50000) /* 50 s */
#define FLASH_SIZE_DATA_REGISTER   ((uint32_t)0x1FF8007C)
/**
  * @}
  */


/** @defgroup FLASH_Exported_Constants FLASH Public Constants
  * @{
  */
  
  /**
  * @brief  FLASH size information
  */
#define FLASH_SIZE                 (uint32_t)(*((uint16_t *)FLASH_SIZE_DATA_REGISTER) * 1024)
#define FLASH_PAGE_SIZE            ((uint32_t)128)

/** @defgroup FLASH_Type_Program
  * @{
  */
#define FLASH_TYPEPROGRAM_WORD     ((uint32_t)0x02)  /*!<Program a word (32-bit) at a specified address.*/
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency 
  * @{
  */ 
#define FLASH_LATENCY_0            ((uint8_t)0x00)    /*!< FLASH Zero Latency cycle */
#define FLASH_LATENCY_1            ((uint8_t)0x01)    /*!< FLASH One Latency cycle */
/**
  * @}
  */

/** @defgroup FLASH_Interrupts FLASH Interrupts 
  * @{
  */
#define FLASH_IT_EOP               FLASH_PECR_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_ERR               FLASH_PECR_ERRIE  /*!< Error interrupt source */
/**
  * @}
  */ 

/** @defgroup FLASH_Flags FLASH Flags 
  * @{
  */ 
#define FLASH_FLAG_BSY             FLASH_SR_BSY             /*!< FLASH Busy flag */
#define FLASH_FLAG_EOP             FLASH_SR_EOP             /*!< FLASH End of Programming flag */
#define FLASH_FLAG_ENDHV           FLASH_SR_HVOFF           /*!< FLASH End of High Voltage flag */
#define FLASH_FLAG_READY           FLASH_SR_READY           /*!< FLASH Ready flag after low power mode */
#define FLASH_FLAG_WRPERR          FLASH_SR_WRPERR          /*!< FLASH Write protected error flag */
#define FLASH_FLAG_PGAERR          FLASH_SR_PGAERR          /*!< FLASH Programming Alignment error flag */
#define FLASH_FLAG_SIZERR          FLASH_SR_SIZERR          /*!< FLASH Size error flag  */
#define FLASH_FLAG_OPTVERR         FLASH_SR_OPTVERR         /*!< FLASH Option Validity error flag  */
#define FLASH_FLAG_RDERR           FLASH_SR_RDERR           /*!< FLASH Read protected error flag */
#define FLASH_FLAG_FWWERR          FLASH_SR_FWWERR          /*!< FLASH Write or Errase operation aborted */
#define FLASH_FLAG_NOTZEROERR      FLASH_SR_NOTZEROERR      /*!< FLASH Read protected error flag */
/**
  * @}
  */ 

/** @defgroup FLASH_Error_Code Flash Error Code
  * @{
  */
#define HAL_FLASH_ERROR_NONE    0x00
#define HAL_FLASH_ERROR_RD      0x01
#define HAL_FLASH_ERROR_SIZE    0x02
#define HAL_FLASH_ERROR_PGA     0x04
#define HAL_FLASH_ERROR_WRP     0x08
#define HAL_FLASH_ERROR_OPTV    0x10
#define HAL_FLASH_ERROR_FWWERR  0x20
#define HAL_FLASH_ERROR_NOTZERO 0x40
/**
  * @}
  */

/** @defgroup FLASH_Keys FLASH Keys 
  * @{
  */ 
#define FLASH_PDKEY1               ((uint32_t)0x04152637) /*!< Flash power down key1 */
#define FLASH_PDKEY2               ((uint32_t)0xFAFBFCFD) /*!< Flash power down key2: used with FLASH_PDKEY1 
                                                               to unlock the RUN_PD bit in FLASH_ACR */

#define FLASH_PEKEY1               ((uint32_t)0x89ABCDEF) /*!< Flash program erase key1 */
#define FLASH_PEKEY2               ((uint32_t)0x02030405) /*!< Flash program erase key: used with FLASH_PEKEY2
                                                               to unlock the write access to the FLASH_PECR register and
                                                               data EEPROM */

#define FLASH_PRGKEY1              ((uint32_t)0x8C9DAEBF) /*!< Flash program memory key1 */
#define FLASH_PRGKEY2              ((uint32_t)0x13141516) /*!< Flash program memory key2: used with FLASH_PRGKEY2
                                                               to unlock the program memory */

#define FLASH_OPTKEY1              ((uint32_t)0xFBEAD9C8) /*!< Flash option key1 */
#define FLASH_OPTKEY2              ((uint32_t)0x24252627) /*!< Flash option key2: used with FLASH_OPTKEY1 to
                                                               unlock the write access to the option byte block */
/**
  * @}
  */

/* CMSIS_Legacy */ 
  
#if defined ( __ICCARM__ )
#define InterruptType_ACTLR_DISMCYCINT_Msk         IntType_ACTLR_DISMCYCINT_Msk
#endif

/**
  * @}
  */ 

/** @defgroup FLASH_Exported_Macros FLASH Exported Macros
  * @{
  */  

/** @defgroup FLASH_Interrupt macros to handle FLASH interrupts
  * @{
  */  
/**
  * @brief  Enable/Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ : FLASH interrupt 
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_ERR: Error Interrupt    
  * @retval none
  */ 
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)   ((FLASH->PECR) |= (__INTERRUPT__))
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  ((FLASH->PECR) &= ~(uint32_t)(__INTERRUPT__))

/**
  * @brief  Get the specified FLASH flag status. 
  * @param  __FLAG__: specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *            @arg FLASH_FLAG_BSY   :              FLASH Busy flag
  *     @arg FLASH_FLAG_EOP:         FLASH End of Operation flag
  *     @arg FLASH_FLAG_READY:       FLASH Ready flag after low power mode
  *     @arg FLASH_FLAG_ENDHV:       FLASH End of high voltage flag
  *     @arg FLASH_FLAG_WRPERR:      FLASH Write protected error flag 
  *     @arg FLASH_FLAG_PGAERR:      FLASH Programming Alignment error flag
  *     @arg FLASH_FLAG_SIZERR:      FLASH Size error flag
  *     @arg FLASH_FLAG_OPTVERR:     FLASH Option validity error flag
  *     @arg FLASH_FLAG_RDERR:       FLASH Read protected error flag
  *     @arg FLASH_FLAG_FWWERR:      FLASH Fetch While Write Error flag
  *     @arg FLASH_FLAG_NOTZEROERR:  Not Zero area error flag  
  * @retval The new state of __FLAG__ (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)   (((FLASH->SR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the specified FLASH flag.
  * @param  __FLAG__: specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_EOP:          FLASH End of Operation flag
  *     @arg FLASH_FLAG_WRPERR:       FLASH Write protected error flag 
  *     @arg FLASH_FLAG_PGAERR:       FLASH Programming Alignment error flag 
  *     @arg FLASH_FLAG_SIZERR:       FLASH size error flag    
  *     @arg FLASH_FLAG_OPTVERR:      FLASH Option validity error flag
  *     @arg FLASH_FLAG_RDERR:        FLASH Read protected error flag
  *     @arg FLASH_FLAG_FWWERR:       FLASH Fetch While Write Error flag
  *     @arg FLASH_FLAG_NOTZEROERR:   Not Zero area error flag  
  * @retval None
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)   (FLASH->SR = (__FLAG__)) 

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Include FLASH HAL Extension module */
#include "stm32l0xx_hal_flash_ex.h"
#include "stm32l0xx_hal_flash_ramfunc.h"

/* Exported functions ------------------------------------------------------- */

/** @defgroup FLASH_Exported_Functions  FLASH Exported functions
  * @{
  */

/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions 
  * @{
  */

/** 
  * @brief  FLASH memory functions that can be executed from FLASH.  
  */  
/* Program operation functions  ***********************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t Data);

/* FLASH IRQ handler function   ***********************************************/
void HAL_FLASH_IRQHandler(void);

/* Callbacks in non blocking modes   ******************************************/
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue); 
  
/**
  * @}
  */ 

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Control functions 
  * @{
  */

/* FLASH Memory Programming functions *****************************************/   
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);

/* Option Bytes Programming functions *****************************************/
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);

/**
  * @}
  */ 

/** @defgroup FLASH_Exported_Functions_Group3 Peripheral State and Errors functions 
  * @{
  */
/* Peripheral State methods  **************************************************/
uint32_t HAL_FLASH_GetError(void);

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */

#define IS_FLASH_TYPEPROGRAM(VALUE) ((VALUE) == FLASH_TYPEPROGRAM_WORD)

#define IS_FLASH_LATENCY(__LATENCY__) (((__LATENCY__) == FLASH_LATENCY_0) || \
                                   ((__LATENCY__) == FLASH_LATENCY_1))
/**
  * @}
  */ 


/** @defgroup FLASH_Private_Functions FLASH Private functions
  * @{
  */

/** 
  * @brief  Function used internally by HAL FLASH driver. 
  */  
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);
void              FLASH_ErasePage(uint32_t Page_Address);
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

#endif /* __STM32L0XX_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

