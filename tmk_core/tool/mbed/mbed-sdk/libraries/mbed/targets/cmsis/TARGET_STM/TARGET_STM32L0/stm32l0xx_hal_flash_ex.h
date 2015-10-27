/**
  ******************************************************************************
  * @file    stm32l0xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of FLash HAL Extension module.
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
#ifndef __STM32L0xx_HAL_FLASH_EX_H
#define __STM32L0xx_HAL_FLASH_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @{
  */ 

/** @defgroup FLASHEx_Exported_Types FLASH Exported Types
  * @{
  */  

/**
  * @brief  FLASH Option Bytes PROGRAM structure definition
  */
typedef struct
{
  uint32_t OptionType;  /*!< OptionType: Option byte to be configured.
                             This parameter can be a value of @ref FLASHEx_Option_Type */

  uint32_t WRPState;    /*!< WRPState: Write protection activation or deactivation.
                             This parameter can be a value of @ref FLASHEx_WRP_State */

  uint32_t WRPSector;   /*!< WRPSector: This bitfield specifies the sector (s) which are write protected.
                             This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection */

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
  uint32_t WRPSector2;  /*!< WRPSector2 : This bitfield specifies the sector(s) upper Sector31 which are write protected.
                             This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection2 */
#endif

  uint8_t RDPLevel;     /*!< RDPLevel: Set the read protection level.
                             This parameter can be a value of @ref FLASHEx_Option_Bytes_Read_Protection */

  uint8_t BORLevel;     /*!< BORLevel: Set the BOR Level.
                             This parameter can be a value of @ref FLASHEx_Option_Bytes_BOR_Level */

  uint8_t USERConfig;   /*!< USERConfig: Program the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
                             This parameter can be a combination of @ref FLASHEx_Option_Bytes_IWatchdog, 
                             @ref FLASHEx_Option_Bytes_nRST_STOP and @ref FLASHEx_Option_Bytes_nRST_STDBY */
                              
  uint8_t BOOTBit1Config; /*!< BOOT1Config: Together with input pad Boot0, this bit selects the boot source, flash, ram or system memory
                               This parameter can be a value of @ref FLASHEx_Option_Bytes_BOOTBit1 */
                              
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH Advanced Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;         /*!< OptionType: Option byte to be configured for extension .
                                    This parameter can be a value of @ref FLASHEx_OptionAdv_Type */
                               
  uint8_t PCROPState;          /*!< PCROPState: PCROP activation or deactivation.
                                    This parameter can be a value of @ref FLASHEx_PCROP_State */
 
  uint32_t PCROPSector;        /*!< PCROPSector : This bitfield specifies the sector(s) which are read/write protected.
                                    This parameter can be a combination of @ref FLASHEx_Option_Bytes_PC_ReadWrite_Protection */

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
  uint32_t PCROPSector2;       /*!< PCROPSector : This bitfield specifies the sector(s) upper Sector31 which are read/write protected.
                                    This parameter can be a combination of @ref FLASHEx_Option_Bytes_PC_ReadWrite_Protection2 */

  uint8_t  BootConfig;         /*!< BootConfig: specifies Option bytes for boot config.
                                    This parameter can be a value of @ref FLASHEx_Option_Bytes_BOOT_BANK */
#endif /* if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
} FLASH_AdvOBProgramInitTypeDef;

/**
  * @}
  */ 

/** @defgroup FLASHEx_Exported_Constants FLASHEx Exported Constants
  * @{
  */  

/** @defgroup FLASHEx_Type_Erase FLASHEx_Type_Erase
  * @{
  */  
#define FLASH_TYPEERASE_PAGES       ((uint32_t)0x00)  /*!< Page erase only */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Type FLASHEx Option Type
  * @{
  */
#define OPTIONBYTE_WRP        ((uint32_t)0x01)  /*!< WRP option byte configuration */
#define OPTIONBYTE_RDP        ((uint32_t)0x02)  /*!< RDP option byte configuration */
#define OPTIONBYTE_USER       ((uint32_t)0x04)  /*!< USER option byte configuration */
#define OPTIONBYTE_BOR        ((uint32_t)0x08)  /*!< BOR option byte configuration */
#define OPTIONBYTE_BOOT_BIT1  ((uint32_t)0x10)  /*!< BOOT PIN1 option byte configuration*/
/**
  * @}
  */

/** @defgroup FLASHEx_WRP_State FLASHEx WRP State
  * @{
  */
#define OB_WRPSTATE_DISABLE      ((uint32_t)0x00)  /*!< Disable the write protection of the desired sectors */
#define OB_WRPSTATE_ENABLE       ((uint32_t)0x01)  /*!< Enable the write protection of the desired sectors */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_ReadWrite_Mask FLASHEx Option Bytes Write Mask
  * @{
  */ 
#define WRP_MASK_LOW          ((uint32_t)0x0000FFFF)
#define WRP_MASK_HIGH         ((uint32_t)0xFFFF0000)
/**
  * @}
  */

#if defined (STM32L031xx) || defined (STM32L041xx) 
/** @defgroup FLASHEx_Option_Bytes_Write_Protection FLASHEx Option Bytes Write Protection
  * @{
  */
#define OB_WRP_Pages0to31          ((uint32_t)0x00000001) /* Write protection of Sector0 */
#define OB_WRP_Pages32to63         ((uint32_t)0x00000002) /* Write protection of Sector1 */
#define OB_WRP_Pages64to95         ((uint32_t)0x00000004) /* Write protection of Sector2 */
#define OB_WRP_Pages96to127        ((uint32_t)0x00000008) /* Write protection of Sector3 */
#define OB_WRP_Pages128to159       ((uint32_t)0x00000010) /* Write protection of Sector4 */
#define OB_WRP_Pages160to191       ((uint32_t)0x00000020) /* Write protection of Sector5 */
#define OB_WRP_Pages192to223       ((uint32_t)0x00000040) /* Write protection of Sector6 */
#define OB_WRP_Pages224to255       ((uint32_t)0x00000080) /* Write protection of Sector7 */
#define OB_WRP_AllPages            ((uint32_t)0x000000FF) /*!< Write protection of all Sectors */
/**
  * @}
  */
#elif defined (STM32L051xx) || defined (STM32L052xx) || defined (STM32L053xx) || defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx)
/** @defgroup FLASHEx_Option_Bytes_Write_Protection FLASHEx Option Bytes Write Protection
  * @{
  */
#define OB_WRP_Pages0to31          ((uint32_t)0x00000001) /* Write protection of Sector0 */
#define OB_WRP_Pages32to63         ((uint32_t)0x00000002) /* Write protection of Sector1 */
#define OB_WRP_Pages64to95         ((uint32_t)0x00000004) /* Write protection of Sector2 */
#define OB_WRP_Pages96to127        ((uint32_t)0x00000008) /* Write protection of Sector3 */
#define OB_WRP_Pages128to159       ((uint32_t)0x00000010) /* Write protection of Sector4 */
#define OB_WRP_Pages160to191       ((uint32_t)0x00000020) /* Write protection of Sector5 */
#define OB_WRP_Pages192to223       ((uint32_t)0x00000040) /* Write protection of Sector6 */
#define OB_WRP_Pages224to255       ((uint32_t)0x00000080) /* Write protection of Sector7 */
#define OB_WRP_Pages256to287       ((uint32_t)0x00000100) /* Write protection of Sector8 */
#define OB_WRP_Pages288to319       ((uint32_t)0x00000200) /* Write protection of Sector9 */
#define OB_WRP_Pages320to351       ((uint32_t)0x00000400) /* Write protection of Sector10 */
#define OB_WRP_Pages352to383       ((uint32_t)0x00000800) /* Write protection of Sector11 */
#define OB_WRP_Pages384to415       ((uint32_t)0x00001000) /* Write protection of Sector12 */
#define OB_WRP_Pages416to447       ((uint32_t)0x00002000) /* Write protection of Sector13 */
#define OB_WRP_Pages448to479       ((uint32_t)0x00004000) /* Write protection of Sector14 */
#define OB_WRP_Pages480to511       ((uint32_t)0x00008000) /* Write protection of Sector15 */
#define OB_WRP_AllPages            ((uint32_t)0x0000FFFF) /*!< Write protection of all Sectors */
/**
  * @}
  */

#elif defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
/** @defgroup FLASHEx_Option_Bytes_Write_Protection FLASHEx Option Bytes Write ProtectionP
  * @{
  */
#define OB_WRP_Pages0to31          ((uint32_t)0x00000001) /* Write protection of Sector0 */
#define OB_WRP_Pages32to63         ((uint32_t)0x00000002) /* Write protection of Sector1 */
#define OB_WRP_Pages64to95         ((uint32_t)0x00000004) /* Write protection of Sector2 */
#define OB_WRP_Pages96to127        ((uint32_t)0x00000008) /* Write protection of Sector3 */
#define OB_WRP_Pages128to159       ((uint32_t)0x00000010) /* Write protection of Sector4 */
#define OB_WRP_Pages160to191       ((uint32_t)0x00000020) /* Write protection of Sector5 */
#define OB_WRP_Pages192to223       ((uint32_t)0x00000040) /* Write protection of Sector6 */
#define OB_WRP_Pages224to255       ((uint32_t)0x00000080) /* Write protection of Sector7 */
#define OB_WRP_Pages256to287       ((uint32_t)0x00000100) /* Write protection of Sector8 */
#define OB_WRP_Pages288to319       ((uint32_t)0x00000200) /* Write protection of Sector9 */
#define OB_WRP_Pages320to351       ((uint32_t)0x00000400) /* Write protection of Sector10 */
#define OB_WRP_Pages352to383       ((uint32_t)0x00000800) /* Write protection of Sector11 */
#define OB_WRP_Pages384to415       ((uint32_t)0x00001000) /* Write protection of Sector12 */
#define OB_WRP_Pages416to447       ((uint32_t)0x00002000) /* Write protection of Sector13 */
#define OB_WRP_Pages448to479       ((uint32_t)0x00004000) /* Write protection of Sector14 */
#define OB_WRP_Pages480to511       ((uint32_t)0x00008000) /* Write protection of Sector15 */
#define OB_WRP_Pages512to543       ((uint32_t)0x00010000) /* Write protection of Sector16 */
#define OB_WRP_Pages544to575       ((uint32_t)0x00020000) /* Write protection of Sector17 */
#define OB_WRP_Pages576to607       ((uint32_t)0x00040000) /* Write protection of Sector18 */
#define OB_WRP_Pages608to639       ((uint32_t)0x00080000) /* Write protection of Sector19 */
#define OB_WRP_Pages640to671       ((uint32_t)0x00100000) /* Write protection of Sector20 */
#define OB_WRP_Pages672to703       ((uint32_t)0x00200000) /* Write protection of Sector21 */
#define OB_WRP_Pages704to735       ((uint32_t)0x00400000) /* Write protection of Sector22 */
#define OB_WRP_Pages736to767       ((uint32_t)0x00800000) /* Write protection of Sector23 */
#define OB_WRP_Pages768to799       ((uint32_t)0x01000000) /* Write protection of Sector24 */
#define OB_WRP_Pages800to831       ((uint32_t)0x02000000) /* Write protection of Sector25 */
#define OB_WRP_Pages832to863       ((uint32_t)0x04000000) /* Write protection of Sector26 */
#define OB_WRP_Pages864to895       ((uint32_t)0x08000000) /* Write protection of Sector27 */
#define OB_WRP_Pages896to927       ((uint32_t)0x10000000) /* Write protection of Sector28 */
#define OB_WRP_Pages928to959       ((uint32_t)0x20000000) /* Write protection of Sector29 */
#define OB_WRP_Pages960to991       ((uint32_t)0x40000000) /* Write protection of Sector30 */
#define OB_WRP_Pages992to1023      ((uint32_t)0x80000000) /* Write protection of Sector31 */
#define OB_WRP_AllPages            ((uint32_t)0xFFFFFFFF) /*!<Write  protection of all Sectors */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_Write_Protection2 FLASHEx Option Bytes Write Protection
  * @{
  */
#define OB_WRP2_Pages1024to1055    ((uint32_t)0x00000001) /* Write protection of Sector32 */
#define OB_WRP2_Pages1056to1087    ((uint32_t)0x00000002) /* Write protection of Sector33 */
#define OB_WRP2_Pages1088to1119    ((uint32_t)0x00000004) /* Write protection of Sector34 */
#define OB_WRP2_Pages1120to1151    ((uint32_t)0x00000008) /* Write protection of Sector35 */
#define OB_WRP2_Pages1152to1183    ((uint32_t)0x00000010) /* Write protection of Sector36 */
#define OB_WRP2_Pages1184to1215    ((uint32_t)0x00000020) /* Write protection of Sector37 */
#define OB_WRP2_Pages1216to1247    ((uint32_t)0x00000040) /* Write protection of Sector38 */
#define OB_WRP2_Pages1248to1279    ((uint32_t)0x00000080) /* Write protection of Sector39 */
#define OB_WRP2_Pages1280to1311    ((uint32_t)0x00000100) /* Write protection of Sector40 */
#define OB_WRP2_Pages1312to1343    ((uint32_t)0x00000200) /* Write protection of Sector41 */
#define OB_WRP2_Pages1344to1375    ((uint32_t)0x00000400) /* Write protection of Sector42 */
#define OB_WRP2_Pages1376to1407    ((uint32_t)0x00000800) /* Write protection of Sector43 */
#define OB_WRP2_Pages1408to1439    ((uint32_t)0x00001000) /* Write protection of Sector44 */
#define OB_WRP2_Pages1440to1471    ((uint32_t)0x00002000) /* Write protection of Sector45 */
#define OB_WRP2_Pages1472to1503    ((uint32_t)0x00004000) /* Write protection of Sector46 */
#define OB_WRP2_Pages1504to1535    ((uint32_t)0x00008000) /* Write protection of Sector47 */
#define OB_WRP2_AllPages           ((uint32_t)0x0000FFFF) /*!< Write protection of all Sectors WRP2 */
/**
  * @}
  */
#endif /* STM32L071xx || STM32L072xx || (STM32L073xx) || (STM32L081xx) || (STM32L082xx) || (STM32L083xx) */ 

/** @defgroup FLASHEx_Option_Bytes_Read_Protection FLASHEx Option Bytes Read Protection
  * @{
  */ 
#define OB_RDP_LEVEL0         ((uint8_t)0xAA)
#define OB_RDP_LEVEL1         ((uint8_t)0xBB)
#define OB_RDP_LEVEL2         ((uint8_t)0xCC) /* Warning: When enabling read protection level 2 
                                                it is no more possible to go back to level 1 or 0 */
/**
  * @}
  */ 

/** @defgroup FLASHEx_Option_Bytes_BOR_Level FLASHEx Option Bytes BOR Level
  * @{
  */
#define OB_BOR_OFF            ((uint8_t)0x00) /*!< BOR is disabled at power down, the reset is asserted when the VDD 
                                              power supply reaches the PDR(Power Down Reset) threshold (1.5V) */
#define OB_BOR_LEVEL1         ((uint8_t)0x08) /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply    */
#define OB_BOR_LEVEL2         ((uint8_t)0x09) /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply    */
#define OB_BOR_LEVEL3         ((uint8_t)0x0A) /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply    */
#define OB_BOR_LEVEL4         ((uint8_t)0x0B) /*!< BOR Reset threshold levels for 2.55V - 2.65V VDD power supply  */
#define OB_BOR_LEVEL5         ((uint8_t)0x0C) /*!< BOR Reset threshold levels for 2.8V - 2.9V VDD power supply    */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_IWatchdog FLASHEx Option Bytes IWatchdog
  * @{
  */
#define OB_IWDG_SW            ((uint8_t)0x10)  /*!< Software WDG selected */
#define OB_IWDG_HW            ((uint8_t)0x00)  /*!< Hardware WDG selected */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_nRST_STOP FLASHEx Option Bytes nRST_STOP
  * @{
  */
#define OB_STOP_NORST         ((uint8_t)0x20) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST           ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_nRST_STDBY FLASHEx Option Bytes nRST_STDBY
  * @{
  */
#define OB_STDBY_NORST        ((uint8_t)0x40) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST          ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
/**
  * @}
  */


/** @defgroup FLASHEx_PCROP_State
  * @{
  */ 
#define OB_PCROP_STATE_DISABLE    ((uint8_t)0x00)  /*!< Disable PCROP */
#define OB_PCROP_STATE_ENABLE     ((uint8_t)0x01)  /*!< Enable PCROP */
/**
  * @}
  */


/** @defgroup FLASHEx_OptionAdv_Type
  * @{
  */ 
#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
#define OPTIONBYTE_PCROP            ((uint32_t)0x01)  /*!< PCROP option byte configuration*/
#define OPTIONBYTE_BOOTCONFIG       ((uint32_t)0x02)  /*!< BOOTConfig option byte configuration, boot from bank 2*/
#else /* if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
#define OPTIONBYTE_PCROP            ((uint32_t)0x01)  /*!< PCROP option byte configuration*/
#endif /* if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
/**
  * @}
  */

#if defined (STM32L031xx) || defined (STM32L041xx) 
/** @defgroup FLASHEx_Option_Bytes_PC_ReadWrite_Protection FLASHEx Option Bytes PC Read/Write Protection
  * @{
  */
#define OB_PCROP_Pages0to31          ((uint32_t)0x00000001) /* PC Read/Write protection of Sector0 */
#define OB_PCROP_Pages32to63         ((uint32_t)0x00000002) /* PC Read/Write protection of Sector1 */
#define OB_PCROP_Pages64to95         ((uint32_t)0x00000004) /* PC Read/Write protection of Sector2 */
#define OB_PCROP_Pages96to127        ((uint32_t)0x00000008) /* PC Read/Write protection of Sector3 */
#define OB_PCROP_Pages128to159       ((uint32_t)0x00000010) /* PC Read/Write protection of Sector4 */
#define OB_PCROP_Pages160to191       ((uint32_t)0x00000020) /* PC Read/Write protection of Sector5 */
#define OB_PCROP_Pages192to223       ((uint32_t)0x00000040) /* PC Read/Write protection of Sector6 */
#define OB_PCROP_Pages224to255       ((uint32_t)0x00000080) /* PC Read/Write protection of Sector7 */
#define OB_PCROP_AllPages            ((uint32_t)0x000000FF) /*!< PC Read/Write protection of all Sectors */
/**
  * @}
  */
#elif defined (STM32L051xx) || defined (STM32L052xx) || defined (STM32L053xx) || defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx)
/** @defgroup FLASHEx_Option_Bytes_PC_ReadWrite_Protection FLASHEx Option Bytes PC Read/Write Protection
  * @{
  */
#define OB_PCROP_Pages0to31          ((uint32_t)0x00000001) /* PC Read/Write protection of Sector0 */
#define OB_PCROP_Pages32to63         ((uint32_t)0x00000002) /* PC Read/Write protection of Sector1 */
#define OB_PCROP_Pages64to95         ((uint32_t)0x00000004) /* PC Read/Write protection of Sector2 */
#define OB_PCROP_Pages96to127        ((uint32_t)0x00000008) /* PC Read/Write protection of Sector3 */
#define OB_PCROP_Pages128to159       ((uint32_t)0x00000010) /* PC Read/Write protection of Sector4 */
#define OB_PCROP_Pages160to191       ((uint32_t)0x00000020) /* PC Read/Write protection of Sector5 */
#define OB_PCROP_Pages192to223       ((uint32_t)0x00000040) /* PC Read/Write protection of Sector6 */
#define OB_PCROP_Pages224to255       ((uint32_t)0x00000080) /* PC Read/Write protection of Sector7 */
#define OB_PCROP_Pages256to287       ((uint32_t)0x00000100) /* PC Read/Write protection of Sector8 */
#define OB_PCROP_Pages288to319       ((uint32_t)0x00000200) /* PC Read/Write protection of Sector9 */
#define OB_PCROP_Pages320to351       ((uint32_t)0x00000400) /* PC Read/Write protection of Sector10 */
#define OB_PCROP_Pages352to383       ((uint32_t)0x00000800) /* PC Read/Write protection of Sector11 */
#define OB_PCROP_Pages384to415       ((uint32_t)0x00001000) /* PC Read/Write protection of Sector12 */
#define OB_PCROP_Pages416to447       ((uint32_t)0x00002000) /* PC Read/Write protection of Sector13 */
#define OB_PCROP_Pages448to479       ((uint32_t)0x00004000) /* PC Read/Write protection of Sector14 */
#define OB_PCROP_Pages480to511       ((uint32_t)0x00008000) /* PC Read/Write protection of Sector15 */
#define OB_PCROP_AllPages            ((uint32_t)0x0000FFFF) /*!< PC Read/Write protection of all Sectors */
/**
  * @}
  */
#endif

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
/** @defgroup FLASHEx_Option_Bytes_PC_ReadWrite_Protection FLASHEx Option Bytes PC Read/Write Protection
  * @{
  */
#define OB_PCROP_Pages0to31          ((uint32_t)0x00000001) /* PC Read/Write protection of Sector0 */
#define OB_PCROP_Pages32to63         ((uint32_t)0x00000002) /* PC Read/Write protection of Sector1 */
#define OB_PCROP_Pages64to95         ((uint32_t)0x00000004) /* PC Read/Write protection of Sector2 */
#define OB_PCROP_Pages96to127        ((uint32_t)0x00000008) /* PC Read/Write protection of Sector3 */
#define OB_PCROP_Pages128to159       ((uint32_t)0x00000010) /* PC Read/Write protection of Sector4 */
#define OB_PCROP_Pages160to191       ((uint32_t)0x00000020) /* PC Read/Write protection of Sector5 */
#define OB_PCROP_Pages192to223       ((uint32_t)0x00000040) /* PC Read/Write protection of Sector6 */
#define OB_PCROP_Pages224to255       ((uint32_t)0x00000080) /* PC Read/Write protection of Sector7 */
#define OB_PCROP_Pages256to287       ((uint32_t)0x00000100) /* PC Read/Write protection of Sector8 */
#define OB_PCROP_Pages288to319       ((uint32_t)0x00000200) /* PC Read/Write protection of Sector9 */
#define OB_PCROP_Pages320to351       ((uint32_t)0x00000400) /* PC Read/Write protection of Sector10 */
#define OB_PCROP_Pages352to383       ((uint32_t)0x00000800) /* PC Read/Write protection of Sector11 */
#define OB_PCROP_Pages384to415       ((uint32_t)0x00001000) /* PC Read/Write protection of Sector12 */
#define OB_PCROP_Pages416to447       ((uint32_t)0x00002000) /* PC Read/Write protection of Sector13 */
#define OB_PCROP_Pages448to479       ((uint32_t)0x00004000) /* PC Read/Write protection of Sector14 */
#define OB_PCROP_Pages480to511       ((uint32_t)0x00008000) /* PC Read/Write protection of Sector15 */
#define OB_PCROP_Pages512to543       ((uint32_t)0x00010000) /* PC Read/Write protection of Sector16 */
#define OB_PCROP_Pages544to575       ((uint32_t)0x00020000) /* PC Read/Write protection of Sector17 */
#define OB_PCROP_Pages576to607       ((uint32_t)0x00040000) /* PC Read/Write protection of Sector18 */
#define OB_PCROP_Pages608to639       ((uint32_t)0x00080000) /* PC Read/Write protection of Sector19 */
#define OB_PCROP_Pages640to671       ((uint32_t)0x00100000) /* PC Read/Write protection of Sector20 */
#define OB_PCROP_Pages672to703       ((uint32_t)0x00200000) /* PC Read/Write protection of Sector21 */
#define OB_PCROP_Pages704to735       ((uint32_t)0x00400000) /* PC Read/Write protection of Sector22 */
#define OB_PCROP_Pages736to767       ((uint32_t)0x00800000) /* PC Read/Write protection of Sector23 */
#define OB_PCROP_Pages768to799       ((uint32_t)0x01000000) /* PC Read/Write protection of Sector24 */
#define OB_PCROP_Pages800to831       ((uint32_t)0x02000000) /* PC Read/Write protection of Sector25 */
#define OB_PCROP_Pages832to863       ((uint32_t)0x04000000) /* PC Read/Write protection of Sector26 */
#define OB_PCROP_Pages864to895       ((uint32_t)0x08000000) /* PC Read/Write protection of Sector27 */
#define OB_PCROP_Pages896to927       ((uint32_t)0x10000000) /* PC Read/Write protection of Sector28 */
#define OB_PCROP_Pages928to959       ((uint32_t)0x20000000) /* PC Read/Write protection of Sector29 */
#define OB_PCROP_Pages960to991       ((uint32_t)0x40000000) /* PC Read/Write protection of Sector30 */
#define OB_PCROP_Pages992to1023      ((uint32_t)0x80000000) /* PC Read/Write protection of Sector31 */
#define OB_PCROP_AllPages            ((uint32_t)0xFFFFFFFF) /*!<PC Read/Write  protection of all Sectors */
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_ReadWrite_Protection2 FLASHEx Option Bytes Read Write Protection
  * @{
  */
#define OB_PCROP2_Pages1024to1055    ((uint32_t)0x00000001) /* PC Read/Write protection of Sector32 */
#define OB_PCROP2_Pages1056to1087    ((uint32_t)0x00000002) /* PC Read/Write protection of Sector33 */
#define OB_PCROP2_Pages1088to1119    ((uint32_t)0x00000004) /* PC Read/Write protection of Sector34 */
#define OB_PCROP2_Pages1120to1151    ((uint32_t)0x00000008) /* PC Read/Write protection of Sector35 */
#define OB_PCROP2_Pages1152to1183    ((uint32_t)0x00000010) /* PC Read/Write protection of Sector36 */
#define OB_PCROP2_Pages1184to1215    ((uint32_t)0x00000020) /* PC Read/Write protection of Sector37 */
#define OB_PCROP2_Pages1216to1247    ((uint32_t)0x00000040) /* PC Read/Write protection of Sector38 */
#define OB_PCROP2_Pages1248to1279    ((uint32_t)0x00000080) /* PC Read/Write protection of Sector39 */
#define OB_PCROP2_Pages1280to1311    ((uint32_t)0x00000100) /* PC Read/Write protection of Sector40 */
#define OB_PCROP2_Pages1312to1343    ((uint32_t)0x00000200) /* PC Read/Write protection of Sector41 */
#define OB_PCROP2_Pages1344to1375    ((uint32_t)0x00000400) /* PC Read/Write protection of Sector42 */
#define OB_PCROP2_Pages1376to1407    ((uint32_t)0x00000800) /* PC Read/Write protection of Sector43 */
#define OB_PCROP2_Pages1408to1439    ((uint32_t)0x00001000) /* PC Read/Write protection of Sector44 */
#define OB_PCROP2_Pages1440to1471    ((uint32_t)0x00002000) /* PC Read/Write protection of Sector45 */
#define OB_PCROP2_Pages1472to1503    ((uint32_t)0x00004000) /* PC Read/Write protection of Sector46 */
#define OB_PCROP2_Pages1504to1535    ((uint32_t)0x00008000) /* PC Read/Write protection of Sector47 */
#define OB_PCROP2_AllPages           ((uint32_t)0x0000FFFF) /*!< PC Read/Write protection of all Sectors PCROP2 */
/**
  * @}
  */
#endif /* if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
  
/** @defgroup FLASHEx_Option_Bytes_BOOTBit1
  * @{
  */
#define OB_BOOT_BIT1_RESET      (uint8_t)(0x00) /*!< BOOT Bit 1 Reset */
#define OB_BOOT_BIT1_SET        (uint8_t)(0x01) /*!< BOOT Bit 1 Set */
/**
  * @}
  */

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
/** @defgroup FLASHEx_Option_Bytes_BOOT_BANK FLASHEx Option Bytes BOOT BANK
  * @{
  */
#define OB_BOOT_BANK1                 ((uint8_t)0x00) /*!<  At startup, if boot pin 0 and BOOT1 bit are set in boot from user Flash position
                                                            and this parameter is selected the device will boot from Bank 2 
                                                            or Bank 1, depending on the activation of the bank */
#define OB_BOOT_BANK2                 (uint8_t)(0x01) /*!< At startup, if boot pin 0 and BOOT1 bit are set in boot from user Flash position
                                                            and this parameter is selected the device will boot from Bank1(Default) */
/**
  * @}
  */
#endif /* if STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */

/** @defgroup FLASHEx_Type_Program_Data FLASHEx Type Program Data
  * @{
  */
#define FLASH_TYPEPROGRAMDATA_BYTE            ((uint32_t)0x00)  /*!< Program byte (8-bit) at a specified address.*/
#define FLASH_TYPEPROGRAMDATA_HALFWORD        ((uint32_t)0x01)  /*!< Program a half-word (16-bit) at a specified address.*/
#define FLASH_TYPEPROGRAMDATA_WORD            ((uint32_t)0x02)  /*!< Program a word (32-bit) at a specified address.*/

/* Aliases for compatibility with the V1.0.0 package */
#define FLASH_TYPEPROGRAM_BYTE           FLASH_TYPEPROGRAMDATA_BYTE
#define FLASH_TYPEPROGRAM_HALFWORD       FLASH_TYPEPROGRAMDATA_HALFWORD
/**
  * @}
  */

/** @defgroup FLASHEx_Address FLASHEx Address
  * @{
  */
#define FLASH_NBPAGES_MAX (FLASH_SIZE / FLASH_PAGE_SIZE)
/**
  * @}
  */ 
    
/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Macros macros to control FLASH features 
 *  @brief 
 *  @{
 */
 
/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__: FLASH Latency                   
  *         This parameter can be one of the following values:
  *           @arg FLASH_LATENCY_0:  FLASH Zero Latency cycle
  *           @arg FLASH_LATENCY_1:  FLASH One Latency cycle
  * @retval none
  */ 
#define __HAL_FLASH_SET_LATENCY(__LATENCY__) \
                  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(__LATENCY__))

/**
  * @brief  Enable/Disable the FLASH prefetch buffer.
  * @retval none
  */ 
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()  CLEAR_BIT((FLASH->ACR), FLASH_ACR_PRFTEN)
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   SET_BIT((FLASH->ACR), FLASH_ACR_PRFTEN)

/**
  * @brief  Enable/Disable the FLASH Buffer cache.
  * @retval none
  */ 
#define __HAL_FLASH_BUFFER_CACHE_ENABLE()      SET_BIT((FLASH->ACR), FLASH_ACR_DISAB_BUF)
#define __HAL_FLASH_BUFFER_CACHE_DISABLE()   CLEAR_BIT((FLASH->ACR), FLASH_ACR_DISAB_BUF)

/**
  * @brief  Enable/Disable the FLASH preread buffer.
  * @retval none
  */ 
#define __HAL_FLASH_PREREAD_BUFFER_ENABLE()      SET_BIT((FLASH->ACR), FLASH_ACR_PRE_READ)
#define __HAL_FLASH_PREREAD_BUFFER_DISABLE()   CLEAR_BIT((FLASH->ACR), FLASH_ACR_PRE_READ)

/**
  * @brief  Enable/Disable the FLASH power down during Sleep mode.
  * @retval none
  */ 
#define __HAL_FLASH_SLEEP_POWERDOWN_ENABLE()     SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)
#define __HAL_FLASH_SLEEP_POWERDOWN_DISABLE()  CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Enable the Flash Run power down mode.
  * @note   Writing this bit  to 0 this bit, automatically the keys are
  *         loss and a new unlock sequence is necessary to re-write it to 1.
  */
#define __HAL_FLASH_POWER_DOWN_ENABLE() do { FLASH->PDKEYR = FLASH_PDKEY1;    \
                                             FLASH->PDKEYR = FLASH_PDKEY2;    \
                                             SET_BIT((FLASH->ACR), FLASH_ACR_RUN_PD);  \
                                           } while (0)

/**
  * @brief  Disable the Flash Run power down mode.
  * @note   Writing this bit  to 0 this bit, automatically the keys are
  *         loss and a new unlock sequence is necessary to re-write it to 1.
  */
#define __HAL_FLASH_POWER_DOWN_DISABLE() do { FLASH->PDKEYR = FLASH_PDKEY1;    \
                                              FLASH->PDKEYR = FLASH_PDKEY2;    \
                                              CLEAR_BIT((FLASH->ACR), FLASH_ACR_RUN_PD);  \
                                            } while (0)
                                            
/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 FLASH Memory Erasing functions
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group2 Option Bytes Programming functions
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
HAL_StatusTypeDef HAL_FLASHEx_AdvOBProgram (FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
void              HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void);
HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void);
/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group3 DATA EEPROM Programming functions
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Unlock(void);
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Lock(void);
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Erase(uint32_t Address);
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data);
void              HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram(void);
void              HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram(void);

/**
  * @}
  */

/**
  * @}
  */ 
  
/** @addtogroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */
#define IS_FLASH_TYPEERASE(__VALUE__)  (((__VALUE__) == FLASH_TYPEERASE_PAGES))

#define IS_OPTIONBYTE(__VALUE__) (((__VALUE__) <= (OPTIONBYTE_WRP  | OPTIONBYTE_RDP | \
                                                  OPTIONBYTE_USER | OPTIONBYTE_BOR | OPTIONBYTE_BOOT_BIT1)))

#define IS_WRPSTATE(__VALUE__)   (((__VALUE__) == OB_WRPSTATE_DISABLE) || \
                                  ((__VALUE__) == OB_WRPSTATE_ENABLE))

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))

#define IS_OB_RDP(__LEVEL__) (((__LEVEL__) == OB_RDP_LEVEL0)||\
                             ((__LEVEL__) == OB_RDP_LEVEL1)||\
                             ((__LEVEL__) == OB_RDP_LEVEL2))

#define IS_OB_BOR_LEVEL(__LEVEL__)  ( ((__LEVEL__) == OB_BOR_OFF)     || \
                                      ((__LEVEL__) == OB_BOR_LEVEL1)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL2)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL3)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL4)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL5))

#define IS_OB_IWDG_SOURCE(__SOURCE__)  (((__SOURCE__) == OB_IWDG_SW) || ((__SOURCE__) == OB_IWDG_HW))

#define IS_OB_STOP_SOURCE(__SOURCE__)  (((__SOURCE__) == OB_STOP_NORST) || ((__SOURCE__) == OB_STOP_RST))

#define IS_OB_STDBY_SOURCE(__SOURCE__) (((__SOURCE__) == OB_STDBY_NORST) || ((__SOURCE__) == OB_STDBY_RST))

#define IS_PCROPSTATE(VALUE)(((VALUE) == OB_PCROP_STATE_DISABLE) || \
                             ((VALUE) == OB_PCROP_STATE_ENABLE))
  
#define IS_OB_PCROP(__PAGE__)       (((__PAGE__) != 0x0000000))

#define IS_OB_BOOT1(__BOOT_BIT1__)  (((__BOOT_BIT1__) == OB_BOOT_BIT1_RESET) || ((__BOOT_BIT1__) == OB_BOOT_BIT1_SET))

#define IS_TYPEPROGRAMDATA(__VALUE__)   (((__VALUE__) == FLASH_TYPEPROGRAMDATA_BYTE) || \
                                         ((__VALUE__) == FLASH_TYPEPROGRAMDATA_HALFWORD) || \
                                         ((__VALUE__) == FLASH_TYPEPROGRAMDATA_WORD))

#define IS_NBPAGES(__PAGES__) (((__PAGES__) >= 1) && ((__PAGES__) <= FLASH_NBPAGES_MAX)) 

#if defined (STM32L071xx) || defined (STM32L072xx) || defined (STM32L073xx) || defined (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
#define IS_OBEX(__VALUE__)(((__VALUE__) <= (OPTIONBYTE_PCROP  | OPTIONBYTE_BOOTCONFIG)))
#define IS_OB_BOOT_BANK(__BANK__)     (((__BANK__) == OB_BOOT_BANK2) || ((__BANK__) == OB_BOOT_BANK1))
#define IS_FLASH_DATA_ADDRESS(__ADDRESS__)          (((__ADDRESS__) >= DATA_EEPROM_BASE) && ((__ADDRESS__) <= DATA_EEPROM_BANK2_END))
#define IS_FLASH_DATA_BANK1_ADDRESS(__ADDRESS__)    (((__ADDRESS__) >= DATA_EEPROM_BASE) && ((__ADDRESS__) <= DATA_EEPROM_BANK1_END))
#define IS_FLASH_DATA_BANK2_ADDRESS(__ADDRESS__)    (((__ADDRESS__) >= DATA_EEPROM_BANK2_BASE) && ((__ADDRESS__) <= DATA_EEPROM_BANK2_END))
#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)       (((__ADDRESS__) >= FLASH_BASE)       && ((__ADDRESS__) <  (FLASH_BASE + FLASH_SIZE)))
#define IS_FLASH_PROGRAM_BANK1_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= FLASH_BASE)       && ((__ADDRESS__) <  (FLASH_BASE + (FLASH_SIZE >> 1))))
#define IS_FLASH_PROGRAM_BANK2_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= FLASH_BANK2_BASE) && ((__ADDRESS__) <  (FLASH_BASE + FLASH_SIZE)))
#else
#define IS_OBEX(VALUE)((VALUE) == OPTIONBYTE_PCROP)  
#define IS_FLASH_DATA_ADDRESS(__ADDRESS__)          (((__ADDRESS__) >= DATA_EEPROM_BASE) && ((__ADDRESS__) <= DATA_EEPROM_END))
#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)       (((__ADDRESS__) >= FLASH_BASE)       && ((__ADDRESS__) <  (FLASH_BASE + FLASH_SIZE)))
#endif
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

#endif /* __STM32L0xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

