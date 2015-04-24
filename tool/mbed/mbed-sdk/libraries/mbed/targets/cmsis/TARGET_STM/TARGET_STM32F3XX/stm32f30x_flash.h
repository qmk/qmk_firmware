/**
  ******************************************************************************
  * @file    stm32f30x_flash.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the FLASH 
  *          firmware library.
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
#ifndef __STM32F30x_FLASH_H
#define __STM32F30x_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief FLASH Status  
  */ 
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_Exported_Constants
  * @{
  */  

/** @defgroup Flash_Latency 
  * @{
  */ 
#define FLASH_Latency_0                ((uint8_t)0x0000)    /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                FLASH_ACR_LATENCY_0  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                FLASH_ACR_LATENCY_1  /*!< FLASH Two Latency cycles */

#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2))
/**
  * @}
  */ 

/** @defgroup FLASH_Interrupts 
  * @{
  */
   
#define FLASH_IT_EOP                   FLASH_CR_EOPIE  /*!< End of programming interrupt source */
#define FLASH_IT_ERR                   FLASH_CR_ERRIE  /*!< Error interrupt source */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))
/**
  * @}
  */
/** @defgroup FLASH_Address 
  * @{
  */
  
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0803FFFF))

/**
  * @}
  */ 

/** @defgroup FLASH_OB_DATA_ADDRESS 
  * @{
  */  
#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806)) 

/**
  * @}
  */

/** @defgroup Option_Bytes_Write_Protection 
  * @{
  */
  
#define OB_WRP_Pages0to1               ((uint32_t)0x00000001) /* Write protection of page 0 to 1 */
#define OB_WRP_Pages2to3               ((uint32_t)0x00000002) /* Write protection of page 2 to 3 */
#define OB_WRP_Pages4to5               ((uint32_t)0x00000004) /* Write protection of page 4 to 5 */
#define OB_WRP_Pages6to7               ((uint32_t)0x00000008) /* Write protection of page 6 to 7 */
#define OB_WRP_Pages8to9               ((uint32_t)0x00000010) /* Write protection of page 8 to 9 */
#define OB_WRP_Pages10to11             ((uint32_t)0x00000020) /* Write protection of page 10 to 11 */
#define OB_WRP_Pages12to13             ((uint32_t)0x00000040) /* Write protection of page 12 to 13 */
#define OB_WRP_Pages14to15             ((uint32_t)0x00000080) /* Write protection of page 14 to 15 */
#define OB_WRP_Pages16to17             ((uint32_t)0x00000100) /* Write protection of page 16 to 17 */
#define OB_WRP_Pages18to19             ((uint32_t)0x00000200) /* Write protection of page 18 to 19 */
#define OB_WRP_Pages20to21             ((uint32_t)0x00000400) /* Write protection of page 20 to 21 */
#define OB_WRP_Pages22to23             ((uint32_t)0x00000800) /* Write protection of page 22 to 23 */
#define OB_WRP_Pages24to25             ((uint32_t)0x00001000) /* Write protection of page 24 to 25 */
#define OB_WRP_Pages26to27             ((uint32_t)0x00002000) /* Write protection of page 26 to 27 */
#define OB_WRP_Pages28to29             ((uint32_t)0x00004000) /* Write protection of page 28 to 29 */
#define OB_WRP_Pages30to31             ((uint32_t)0x00008000) /* Write protection of page 30 to 31 */
#define OB_WRP_Pages32to33             ((uint32_t)0x00010000) /* Write protection of page 32 to 33 */
#define OB_WRP_Pages34to35             ((uint32_t)0x00020000) /* Write protection of page 34 to 35 */
#define OB_WRP_Pages36to37             ((uint32_t)0x00040000) /* Write protection of page 36 to 37 */
#define OB_WRP_Pages38to39             ((uint32_t)0x00080000) /* Write protection of page 38 to 39 */
#define OB_WRP_Pages40to41             ((uint32_t)0x00100000) /* Write protection of page 40 to 41 */
#define OB_WRP_Pages42to43             ((uint32_t)0x00200000) /* Write protection of page 42 to 43 */
#define OB_WRP_Pages44to45             ((uint32_t)0x00400000) /* Write protection of page 44 to 45 */
#define OB_WRP_Pages46to47             ((uint32_t)0x00800000) /* Write protection of page 46 to 47 */
#define OB_WRP_Pages48to49             ((uint32_t)0x01000000) /* Write protection of page 48 to 49 */
#define OB_WRP_Pages50to51             ((uint32_t)0x02000000) /* Write protection of page 50 to 51 */
#define OB_WRP_Pages52to53             ((uint32_t)0x04000000) /* Write protection of page 52 to 53 */
#define OB_WRP_Pages54to55             ((uint32_t)0x08000000) /* Write protection of page 54 to 55 */
#define OB_WRP_Pages56to57             ((uint32_t)0x10000000) /* Write protection of page 56 to 57 */
#define OB_WRP_Pages58to59             ((uint32_t)0x20000000) /* Write protection of page 58 to 59 */
#define OB_WRP_Pages60to61             ((uint32_t)0x40000000) /* Write protection of page 60 to 61 */
#define OB_WRP_Pages62to127            ((uint32_t)0x80000000) /* Write protection of page 62 to 127 */

#define OB_WRP_AllPages                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

/**
  * @}
  */

/** @defgroup Option_Bytes_Read_Protection 
  * @{
  */ 

/** 
  * @brief  Read Protection Level  
  */ 
#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0xBB)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2 
                                                it's no more possible to go back to level 1 or 0 */

#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
                          ((LEVEL) == OB_RDP_Level_1))/*||\
                          ((LEVEL) == OB_RDP_Level_2))*/
/**
  * @}
  */ 

/** @defgroup Option_Bytes_IWatchdog 
  * @{
  */

#define OB_IWDG_SW                     ((uint8_t)0x01)  /*!< Software IWDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware IWDG selected */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STOP 
  * @{
  */

#define OB_STOP_NoRST                  ((uint8_t)0x02) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup Option_Bytes_nRST_STDBY 
  * @{
  */

#define OB_STDBY_NoRST                 ((uint8_t)0x04) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/**
  * @}
  */
/** @defgroup Option_Bytes_BOOT1
  * @{
  */

#define OB_BOOT1_RESET                 ((uint8_t)0x00) /*!< BOOT1 Reset */
#define OB_BOOT1_SET                   ((uint8_t)0x10) /*!< BOOT1 Set */
#define IS_OB_BOOT1(BOOT1) (((BOOT1) == OB_BOOT1_RESET) || ((BOOT1) == OB_BOOT1_SET))

/**
  * @}
  */  
/** @defgroup Option_Bytes_VDDA_Analog_Monitoring
  * @{
  */

#define OB_VDDA_ANALOG_ON              ((uint8_t)0x20) /*!< Analog monitoring on VDDA Power source ON */
#define OB_VDDA_ANALOG_OFF             ((uint8_t)0x00) /*!< Analog monitoring on VDDA Power source OFF */

#define IS_OB_VDDA_ANALOG(ANALOG) (((ANALOG) == OB_VDDA_ANALOG_ON) || ((ANALOG) == OB_VDDA_ANALOG_OFF))

/**
  * @}
  */ 

/** @defgroup FLASH_Option_Bytes_SRAM_Parity_Enable 
  * @{
  */

#define OB_SRAM_PARITY_SET              ((uint8_t)0x00) /*!< SRAM parity enable Set */
#define OB_SRAM_PARITY_RESET            ((uint8_t)0x40) /*!< SRAM parity enable reset */

#define IS_OB_SRAM_PARITY(PARITY) (((PARITY) == OB_SRAM_PARITY_SET) || ((PARITY) == OB_SRAM_PARITY_RESET))

/**
  * @}
  */ 
      
/** @defgroup FLASH_Flags 
  * @{
  */ 

#define FLASH_FLAG_BSY                 FLASH_SR_BSY     /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR               FLASH_SR_PGERR   /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_EOP                 FLASH_SR_EOP     /*!< FLASH End of Programming flag */
 
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFCB) == 0x00000000) && ((FLAG) != 0x00000000))

#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_BSY) || ((FLAG) == FLASH_FLAG_PGERR) || \
                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_EOP))
/**
  * @}
  */ 
/** @defgroup Timeout_definition 
  * @{
  */ 
#define FLASH_ER_PRG_TIMEOUT         ((uint32_t)0x000B0000)

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

/* FLASH Interface configuration functions ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(FunctionalState NewState);
void FLASH_PrefetchBufferCmd(FunctionalState NewState);

/* FLASH Memory Programming functions *****************************************/   
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

/* Option Bytes Programming functions *****************************************/ 
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_OB_Launch(void);
FLASH_Status FLASH_OB_Erase(void);
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP);
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity);
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
uint8_t FLASH_OB_GetUser(void);
uint32_t FLASH_OB_GetWRP(void);
FlagStatus FLASH_OB_GetRDP(void);

/* Interrupts and flags management functions **********************************/
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_FLASH_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
