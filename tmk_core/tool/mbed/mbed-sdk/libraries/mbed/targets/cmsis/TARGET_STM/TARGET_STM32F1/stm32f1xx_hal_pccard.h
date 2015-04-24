/**
  ******************************************************************************
  * @file    stm32f1xx_hal_pccard.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of PCCARD HAL module.
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
#ifndef __STM32F1xx_HAL_PCCARD_H
#define __STM32F1xx_HAL_PCCARD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_ll_fsmc.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

#if defined (STM32F101xE) || defined(STM32F103xE) || defined(STM32F101xG) || defined(STM32F103xG)
/** @addtogroup PCCARD
  * @{
  */ 

/** @addtogroup PCCARD_Private_Constants
  * @{
  */
  
#define PCCARD_DEVICE_ADDRESS           FSMC_BANK4
#define PCCARD_ATTRIBUTE_SPACE_ADDRESS  ((uint32_t)(FSMC_BANK4 + 0x08000000))  /* Attribute space size to @0x9BFF FFFF */
#define PCCARD_COMMON_SPACE_ADDRESS     PCCARD_DEVICE_ADDRESS                           /* Common space size to @0x93FF FFFF    */
#define PCCARD_IO_SPACE_ADDRESS         ((uint32_t)(FSMC_BANK4 + 0x0C000000))  /* IO space size to @0x9FFF FFFF        */
#define PCCARD_IO_SPACE_PRIMARY_ADDR    ((uint32_t)(FSMC_BANK4 + 0x0C0001F0))  /* IO space size to @0x9FFF FFFF        */

/* Compact Flash-ATA registers description */
#define ATA_DATA                        ((uint8_t)0x00)    /* Data register */
#define ATA_SECTOR_COUNT                ((uint8_t)0x02)    /* Sector Count register */
#define ATA_SECTOR_NUMBER               ((uint8_t)0x03)    /* Sector Number register */
#define ATA_CYLINDER_LOW                ((uint8_t)0x04)    /* Cylinder low register */
#define ATA_CYLINDER_HIGH               ((uint8_t)0x05)    /* Cylinder high register */
#define ATA_CARD_HEAD                   ((uint8_t)0x06)    /* Card/Head register */
#define ATA_STATUS_CMD                  ((uint8_t)0x07)    /* Status(read)/Command(write) register */
#define ATA_STATUS_CMD_ALTERNATE        ((uint8_t)0x0E)    /* Alternate Status(read)/Command(write) register */
#define ATA_COMMON_DATA_AREA            ((uint16_t)0x0400) /* Start of data area (for Common access only!) */
#define ATA_CARD_CONFIGURATION          ((uint16_t)0x0202) /* Card Configuration and Status Register */

/* Compact Flash-ATA commands */
#define ATA_READ_SECTOR_CMD             ((uint8_t)0x20)
#define ATA_WRITE_SECTOR_CMD            ((uint8_t)0x30)
#define ATA_ERASE_SECTOR_CMD            ((uint8_t)0xC0)
#define ATA_IDENTIFY_CMD                ((uint8_t)0xEC)

/* Compact Flash status */
#define PCCARD_TIMEOUT_ERROR            ((uint8_t)0x60)
#define PCCARD_BUSY                     ((uint8_t)0x80)
#define PCCARD_PROGR                    ((uint8_t)0x01)
#define PCCARD_READY                    ((uint8_t)0x40)

#define PCCARD_SECTOR_SIZE              ((uint32_t)255)    /* In half words */ 
 

/* Compact Flash redefinition */
#define HAL_CF_Read_ID              HAL_PCCARD_Read_ID
#define HAL_CF_Write_Sector         HAL_PCCARD_Write_Sector
#define HAL_CF_Read_Sector          HAL_PCCARD_Read_Sector
#define HAL_CF_Erase_Sector         HAL_PCCARD_Erase_Sector
#define HAL_CF_Reset                HAL_PCCARD_Reset
                                        
#define HAL_CF_GetStatus            HAL_PCCARD_GetStatus
#define HAL_CF_ReadStatus           HAL_PCCARD_ReadStatus
                                        
#define CF_SUCCESS                  HAL_PCCARD_STATUS_SUCCESS
#define CF_ONGOING                  HAL_PCCARD_STATUS_ONGOING
#define CF_ERROR                    HAL_PCCARD_STATUS_ERROR
#define CF_TIMEOUT                  HAL_PCCARD_STATUS_TIMEOUT
#define CF_StatusTypedef            HAL_PCCARD_StatusTypeDef


#define CF_DEVICE_ADDRESS           PCCARD_DEVICE_ADDRESS               
#define CF_ATTRIBUTE_SPACE_ADDRESS  PCCARD_ATTRIBUTE_SPACE_ADDRESS
#define CF_COMMON_SPACE_ADDRESS     PCCARD_COMMON_SPACE_ADDRESS   
#define CF_IO_SPACE_ADDRESS         PCCARD_IO_SPACE_ADDRESS       
#define CF_IO_SPACE_PRIMARY_ADDR    PCCARD_IO_SPACE_PRIMARY_ADDR  

#define CF_TIMEOUT_ERROR            PCCARD_TIMEOUT_ERROR
#define CF_BUSY                     PCCARD_BUSY         
#define CF_PROGR                    PCCARD_PROGR        
#define CF_READY                    PCCARD_READY        

#define CF_SECTOR_SIZE              PCCARD_SECTOR_SIZE

/**
  * @}
  */ 

/* Exported typedef ----------------------------------------------------------*/
/** @defgroup PCCARD_Exported_Types PCCARD Exported Types
  * @{
  */

/** 
  * @brief  HAL PCCARD State structures definition  
  */ 
typedef enum
{
  HAL_PCCARD_STATE_RESET     = 0x00,    /*!< PCCARD peripheral not yet initialized or disabled */
  HAL_PCCARD_STATE_READY     = 0x01,    /*!< PCCARD peripheral ready                           */
  HAL_PCCARD_STATE_BUSY      = 0x02,    /*!< PCCARD peripheral busy                            */   
  HAL_PCCARD_STATE_ERROR     = 0x04     /*!< PCCARD peripheral error                           */
}HAL_PCCARD_StateTypeDef;

typedef enum
{
  HAL_PCCARD_STATUS_SUCCESS = 0,
  HAL_PCCARD_STATUS_ONGOING,
  HAL_PCCARD_STATUS_ERROR,
  HAL_PCCARD_STATUS_TIMEOUT
}HAL_PCCARD_StatusTypeDef;

/** 
  * @brief  FSMC_PCCARD handle Structure definition  
  */   
typedef struct
{
  FSMC_PCCARD_TypeDef           *Instance;              /*!< Register base address for PCCARD device          */
  
  FSMC_PCCARD_InitTypeDef       Init;                   /*!< PCCARD device control configuration parameters   */

  __IO HAL_PCCARD_StateTypeDef State;                  /*!< PCCARD device access state                       */
   
  HAL_LockTypeDef              Lock;                   /*!< PCCARD Lock                                      */ 
 
}PCCARD_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup PCCARD_Exported_Macros PCCARD Exported Macros
  * @{
  */

/** @brief Reset PCCARD handle state
  * @param  __HANDLE__: specifies the PCCARD handle.
  * @retval None
  */
#define __HAL_PCCARD_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_PCCARD_STATE_RESET)
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PCCARD_Exported_Functions PCCARD Exported Functions
  * @{
  */

/** @addtogroup PCCARD_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef  HAL_PCCARD_Init(PCCARD_HandleTypeDef *hpccard, FSMC_NAND_PCC_TimingTypeDef *ComSpaceTiming, FSMC_NAND_PCC_TimingTypeDef *AttSpaceTiming, FSMC_NAND_PCC_TimingTypeDef *IOSpaceTiming);
HAL_StatusTypeDef  HAL_PCCARD_DeInit(PCCARD_HandleTypeDef *hpccard);   
void               HAL_PCCARD_MspInit(PCCARD_HandleTypeDef *hpccard);
void               HAL_PCCARD_MspDeInit(PCCARD_HandleTypeDef *hpccard);
/**
  * @}
  */

/** @addtogroup PCCARD_Exported_Functions_Group2 Input Output and memory functions 
  * @{
  */
/* IO operation functions  *****************************************************/
HAL_StatusTypeDef  HAL_PCCARD_Read_ID(PCCARD_HandleTypeDef *hpccard, uint8_t CompactFlash_ID[], uint8_t *pStatus);
HAL_StatusTypeDef  HAL_PCCARD_Write_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t *pBuffer, uint16_t SectorAddress,  uint8_t *pStatus);
HAL_StatusTypeDef  HAL_PCCARD_Read_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t *pBuffer, uint16_t SectorAddress, uint8_t *pStatus);
HAL_StatusTypeDef  HAL_PCCARD_Erase_Sector(PCCARD_HandleTypeDef *hpccard, uint16_t SectorAddress, uint8_t *pStatus);
HAL_StatusTypeDef  HAL_PCCARD_Reset(PCCARD_HandleTypeDef *hpccard);
void               HAL_PCCARD_IRQHandler(PCCARD_HandleTypeDef *hpccard);
void               HAL_PCCARD_ITCallback(PCCARD_HandleTypeDef *hpccard);

/**
  * @}
  */

/** @defgroup PCCARD_Exported_Functions_Group3 Peripheral State functions 
  * @{
  */
/* PCCARD State functions *******************************************************/
HAL_PCCARD_StateTypeDef  HAL_PCCARD_GetState(PCCARD_HandleTypeDef *hpccard);
HAL_PCCARD_StatusTypeDef HAL_PCCARD_GetStatus(PCCARD_HandleTypeDef *hpccard);
HAL_PCCARD_StatusTypeDef HAL_PCCARD_ReadStatus(PCCARD_HandleTypeDef *hpccard);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

#endif /* STM32F101xE || STM32F103xE || STM32F101xG || STM32F103xG */
/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_PCCARD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
