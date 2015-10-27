/**
  ******************************************************************************
  * @file    stm32f3xx_hal_flash.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
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
#ifndef __STM32F3xx_HAL_FLASH_H
#define __STM32F3xx_HAL_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH FLASH HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup FLASH_Exported_Types FLASH Exported Types
  * @{
  */  

/** 
  * @brief FLASH Error source  
  */ 
typedef enum
{ 
  FLASH_ERROR_PG        = 0x01,
  FLASH_ERROR_WRP       = 0x02
} FLASH_ErrorTypeDef;

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;   /*!< TypeErase: Mass erase or page erase.
                             This parameter can be a value of @ref FLASH_Type_Erase */

  uint32_t PageAddress; /*!< PageAdress: Initial FLASH page address to erase when mass erase is disabled
                             This parameter must be a value of @ref FLASHEx_Address */
  
  uint32_t NbPages;     /*!< NbPages: Number of pagess to be erased.
                             This parameter must be a value between 1 and (max number of pages - value of initial page)*/           
                                                          
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Options bytes program structure definition
  */
typedef struct
{
  uint32_t OptionType;  /*!< OptionType: Option byte to be configured.
                             This parameter can be a value of @ref FLASH_OB_Type */

  uint32_t WRPState;    /*!< WRPState: Write protection activation or deactivation.
                             This parameter can be a value of @ref FLASH_OB_WRP_State */

  uint32_t WRPPage;     /*!< WRPSector: specifies the page(s) to be write protected
                             This parameter can be a value of @ref FLASHEx_OB_Write_Protection */

  uint8_t RDPLevel;     /*!< RDPLevel: Set the read protection level..
                             This parameter can be a value of @ref FLASH_OB_Read_Protection */

  uint8_t USERConfig;   /*!< USERConfig: Program the FLASH User Option Byte: 
                             IWDG / STOP / STDBY / BOOT1 / VDDA_ANALOG / SRAM_PARITY / SDADC12_VDD_MONITOR
                             This parameter can be a combination of @ref FLASH_OB_IWatchdog, @ref FLASH_OB_nRST_STOP, 
                             @ref FLASH_OB_nRST_STDBY, @ref FLASH_OB_BOOT1, @ref FLASH_OB_VDDA_Analog_Monitoring,
                             @ref FLASH_OB_SRAM_Parity_Enable and @ref FLASH_OB_SDADC12_VDD_MONITOR */

  uint32_t DATAAddress; /*!< DATAAddress: Address of the option byte DATA to be prgrammed
                             This parameter can be a value of @ref FLASH_OB_Data_Address */
  
  uint8_t DATAData;     /*!< DATAData: Data to be stored in the option byte DATA
                             This parameter can have any value */
  
} FLASH_OBProgramInitTypeDef;

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

  __IO FLASH_ErrorTypeDef     ErrorCode;        /* FLASH error code                    */

} FLASH_ProcessTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASH_Exported_Constants FLASH Exported Constants
  * @{
  */  

/** @defgroup FLASH_Type_Erase FLASH Type Erase
  * @{
  */ 
#define TYPEERASE_PAGES     ((uint32_t)0x00)  /*!<Pages erase only*/
#define TYPEERASE_MASSERASE ((uint32_t)0x01)  /*!<Flash mass erase activation*/

#define IS_TYPEERASE(VALUE) (((VALUE) == TYPEERASE_PAGES) || \
                             ((VALUE) == TYPEERASE_MASSERASE))  
/**
  * @}
  */

/** @defgroup FLASH_Type_Program FLASH Type Program
  * @{
  */ 
#define TYPEPROGRAM_HALFWORD   ((uint32_t)0x01)  /*!<Program a half-word (16-bit) at a specified address.*/
#define TYPEPROGRAM_WORD       ((uint32_t)0x02)  /*!<Program a word (32-bit) at a specified address.*/
#define TYPEPROGRAM_DOUBLEWORD ((uint32_t)0x03)  /*!<Program a double word (64-bit) at a specified address*/

#define IS_TYPEPROGRAM(VALUE)  (((VALUE) == TYPEPROGRAM_HALFWORD) || \
                                ((VALUE) == TYPEPROGRAM_WORD)     || \
                                ((VALUE) == TYPEPROGRAM_DOUBLEWORD))  
/**
  * @}
  */

/** @defgroup FLASH_OB_WRP_State FLASH WRP State
  * @{
  */ 
#define WRPSTATE_DISABLE   ((uint32_t)0x00)  /*!<Disable the write protection of the desired pages*/
#define WRPSTATE_ENABLE    ((uint32_t)0x01)  /*!<Enable the write protection of the desired pagess*/

#define IS_WRPSTATE(VALUE) (((VALUE) == WRPSTATE_DISABLE) || \
                            ((VALUE) == WRPSTATE_ENABLE))  
/**
  * @}
  */

/** @defgroup FLASH_OB_Type FLASH Option Bytes Type
  * @{
  */
#define OPTIONBYTE_WRP       ((uint32_t)0x01)  /*!<WRP option byte configuration*/
#define OPTIONBYTE_RDP       ((uint32_t)0x02)  /*!<RDP option byte configuration*/
#define OPTIONBYTE_USER      ((uint32_t)0x04)  /*!<USER option byte configuration*/
#define OPTIONBYTE_DATA      ((uint32_t)0x08)  /*!<DATA option byte configuration*/

#define IS_OPTIONBYTE(VALUE) (((VALUE) < (OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_DATA)))
/**
  * @}
  */

/** @defgroup FLASH_Latency FLASH Latency
  * @{
  */ 
#define FLASH_LATENCY_0            ((uint8_t)0x0000)    /*!< FLASH Zero Latency cycle */
#define FLASH_LATENCY_1            FLASH_ACR_LATENCY_0  /*!< FLASH One Latency cycle */
#define FLASH_LATENCY_2            FLASH_ACR_LATENCY_1  /*!< FLASH Two Latency cycles */

#define IS_FLASH_LATENCY(LATENCY)  (((LATENCY) == FLASH_LATENCY_0) || \
                                    ((LATENCY) == FLASH_LATENCY_1) || \
                                    ((LATENCY) == FLASH_LATENCY_2))
/**
  * @}
  */ 
  
/** @defgroup FLASH_OB_Data_Address  FLASH Option Byte Data Address
  * @{
  */  
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806)) 
/**
  * @}
  */

/** @defgroup FLASH_OB_Read_Protection FLASH Option Byte Read Protection
  * @{
  */
#define OB_RDP_LEVEL_0             ((uint8_t)0xAA)
#define OB_RDP_LEVEL_1             ((uint8_t)0xBB)
#define OB_RDP_LEVEL_2             ((uint8_t)0xCC) /*!< Warning: When enabling read protection level 2 
                                                      it's no more possible to go back to level 1 or 0 */
#define IS_OB_RDP_LEVEL(LEVEL)     (((LEVEL) == OB_RDP_LEVEL_0)   ||\
                                    ((LEVEL) == OB_RDP_LEVEL_1))/*||\
                                    ((LEVEL) == OB_RDP_LEVEL_2))*/
/**
  * @}
  */ 
  
/** @defgroup FLASH_OB_IWatchdog FLASH Option Byte IWatchdog
  * @{
  */ 
#define OB_IWDG_SW                 ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                 ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE)  (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))
/**
  * @}
  */ 
  
/** @defgroup FLASH_OB_nRST_STOP FLASH Option Byte nRST STOP
  * @{
  */ 
#define OB_STOP_NO_RST             ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE)  (((SOURCE) == OB_STOP_NO_RST) || ((SOURCE) == OB_STOP_RST))
/**
  * @}
  */ 

/** @defgroup FLASH_OB_nRST_STDBY FLASH Option Byte nRST STDBY
  * @{
  */ 
#define OB_STDBY_NO_RST            ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST               ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NO_RST) || ((SOURCE) == OB_STDBY_RST))
/**
  * @}
  */    

/** @defgroup FLASH_OB_BOOT1 FLASH Option Byte BOOT1
  * @{
  */
#define OB_BOOT1_RESET             ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET               ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1)         (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))
/**
  * @}
  */  

/** @defgroup FLASH_OB_VDDA_Analog_Monitoring FLASH Option Byte VDDA Analog Monitoring
  * @{
  */
#define OB_VDDA_ANALOG_ON          ((uint8_t)0x20) /*!< Analog monitoring on VDDA Power source ON */
#define OB_VDDA_ANALOG_OFF         ((uint8_t)0x00) /*!< Analog monitoring on VDDA Power source OFF */
#define IS_OB_VDDA_ANALOG(ANALOG)  (((ANALOG) == OB_VDDA_ANALOG_ON) || ((ANALOG) == OB_VDDA_ANALOG_OFF))
/**
  * @}
  */ 

/** @defgroup FLASH_OB_SRAM_Parity_Enable FLASH Option Byte SRAM Parity Enable
  * @{
  */
#define OB_SRAM_PARITY_SET         ((uint8_t)0x00) /*!< SRAM parity enable set */
#define OB_SRAM_PARITY_RESET       ((uint8_t)0x40) /*!< SRAM parity enable reset */
#define IS_OB_SRAM_PARITY(PARITY)  (((PARITY) == OB_SRAM_PARITY_SET) || ((PARITY) == OB_SRAM_PARITY_RESET))
/**
  * @}
  */ 

/** @defgroup FLASH_OB_SDADC12_VDD_MONITOR FLASH Option Byte SDADC12 VDD MONITOR
  * @{
  */
#define OB_SDADC12_VDD_MONITOR_SET        ((uint8_t)0x80) /*!< SDADC12_VDD power supply supervisor set */
#define OB_SDADC12_VDD_MONITOR_RESET      ((uint8_t)0x00) /*!< SDADC12_VDD power supply supervisor reset */
#define IS_OB_SDADC12_VDD_MONITOR(MONITOR)  (((MONITOR) == OB_SDADC12_VDD_MONITOR_SET) || ((MONITOR) == OB_SDADC12_VDD_MONITOR_RESET))
/**
  * @}
  */

/** @defgroup FLASH_Flag_definition FLASH Flag definition
  * @brief Flag definition
  * @{
  */ 
#define FLASH_FLAG_BSY             FLASH_SR_BSY            /*!< FLASH Busy flag                           */ 
#define FLASH_FLAG_PGERR           FLASH_SR_PGERR          /*!< FLASH Programming error flag    */
#define FLASH_FLAG_WRPERR          FLASH_SR_WRPERR         /*!< FLASH Write protected error flag          */
#define FLASH_FLAG_EOP             FLASH_SR_EOP            /*!< FLASH End of Operation flag               */

#define IS_FLASH_CLEAR_FLAG(FLAG)  ((((FLAG) & (uint32_t)0xFFFFFFC3) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)    (((FLAG) == FLASH_FLAG_BSY)    || ((FLAG) == FLASH_FLAG_PGERR)  || \
                                    ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP))
/**
  * @}
  */
  
/** @defgroup FLASH_Interrupt_definition FLASH Interrupt definition
  * @brief FLASH Interrupt definition
  * @{
  */ 
#define FLASH_IT_EOP               FLASH_CR_EOPIE          /*!< End of FLASH Operation Interrupt source */
#define FLASH_IT_ERR               FLASH_CR_ERRIE  /*!< Error Interrupt source */
#define IS_FLASH_IT(IT)            ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && ((IT) != 0x00000000))
/**
  * @}
  */  

/** @defgroup FLASH_Timeout_definition FLASH Timeout definition
  * @brief FLASH Timeout definition
  * @{
  */ 
#define HAL_FLASH_TIMEOUT_VALUE   ((uint32_t)50000)/* 50 s */
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
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__: FLASH Latency                   
  *         The value of this parameter depend on device used within the same series
  * @retval None
  */ 
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    (FLASH->ACR = (FLASH->ACR&(~FLASH_ACR_LATENCY)) | (__LATENCY__))

/**
  * @brief  Enable the FLASH prefetch buffer.
  * @retval None
  */ 
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()    (FLASH->ACR |= FLASH_ACR_PRFTBE)

/**
  * @brief  Disable the FLASH prefetch buffer.
  * @retval None
  */
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   (FLASH->ACR &= (~FLASH_ACR_PRFTBE))

/**
  * @brief  Enable the FLASH half cycle access.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_ENABLE()  (FLASH->ACR |= FLASH_ACR_HLFCYA)

/**
  * @brief  Disable the FLASH half cycle access.
  * @retval None
  */
#define __HAL_FLASH_HALF_CYCLE_ACCESS_DISABLE() (FLASH->ACR &= (~FLASH_ACR_HLFCYA))

/** @defgroup FLASH_Interrupt FLASH Interrupt
 *  @brief macros to handle FLASH interrupts
 * @{
 */ 

/**
  * @brief  Enable the specified FLASH interrupt.
  * @param  __INTERRUPT__ : FLASH interrupt 
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_ERR: Error Interrupt    
  * @retval none
  */  
#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)  (FLASH->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the specified FLASH interrupt.
  * @param  __INTERRUPT__ : FLASH interrupt 
  *         This parameter can be any combination of the following values:
  *     @arg FLASH_IT_EOP: End of FLASH Operation Interrupt
  *     @arg FLASH_IT_ERR: Error Interrupt    
  * @retval none
  */  
#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  (FLASH->CR &= ~(uint32_t)(__INTERRUPT__))

/**
  * @brief  Get the specified FLASH flag status. 
  * @param  __FLAG__: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *            @arg FLASH_FLAG_EOP   : FLASH End of Operation flag 
  *            @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag 
  *            @arg FLASH_FLAG_PGERR : FLASH Programming error flag
  *            @arg FLASH_FLAG_BSY   : FLASH Busy flag
  * @retval The new state of __FLAG__ (SET or RESET).
  */
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((FLASH->SR & (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the specified FLASH flag.
  * @param  __FLAG__: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *            @arg FLASH_FLAG_EOP   : FLASH End of Operation flag 
  *            @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag 
  *            @arg FLASH_FLAG_PGERR : FLASH Programming error flag 
  * @retval none
  */
#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        (FLASH->SR = (__FLAG__))

/**
  * @}
  */  

/**
  * @}
  */ 

/* Include FLASH HAL Extended module */
#include "stm32f3xx_hal_flash_ex.h"  

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions FLASH Exported Functions
  * @{
  */
  
/** @addtogroup FLASH_Exported_Functions_Group1 Input and Output operation functions
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

/* FLASH IRQ handler method */
void              HAL_FLASH_IRQHandler(void);
/* Callbacks in non blocking modes */ 
void       HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void       HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group2 Peripheral Control functions 
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
/* Option bytes control */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);

/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group3 Peripheral State functions 
  * @{
  */
/* Peripheral State and Error functions ***************************************/
FLASH_ErrorTypeDef HAL_FLASH_GetError(void);

/**
  * @}
  */

/**
  * @}
  */

/* Exported Private function -------------------------------------------------*/
/** @addtogroup FLASH_Exported_Private_Functions FLASH Exported Private Functions
 * @{
 */
/* Erase operations */
void                    FLASH_PageErase(uint32_t PageAddress);
HAL_StatusTypeDef       FLASH_WaitForLastOperation(uint32_t Timeout);

/* Program operations */
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

#endif /* __STM32F3xx_HAL_FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
