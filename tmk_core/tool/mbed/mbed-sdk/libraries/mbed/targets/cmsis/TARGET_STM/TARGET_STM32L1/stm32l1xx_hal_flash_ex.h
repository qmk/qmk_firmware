/**
  ******************************************************************************
  * @file    stm32l1xx_hal_flash.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
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
#ifndef __STM32L1xx_HAL_FLASH_EX_H
#define __STM32L1xx_HAL_FLASH_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** @defgroup FLASHEx_Exported_Types FLASHEx Exported Types
  * @{
  */  

/**
  * @brief  FLASH Erase structure definition
  */
typedef struct
{
  uint32_t TypeErase;   /*!< TypeErase: Page Erase only.
                              This parameter can be a value of @ref FLASHEx_Type_Erase */

  uint32_t PageAddress;     /*!< PageAddress: Initial FLASH address to be erased
                              This parameter must be a value belonging to FLASH Programm address (depending on the devices)  */
  
  uint32_t NbPages; /*!< NbPages: Number of pages to be erased.
                              This parameter must be a value between 1 and (max number of pages - value of Initial page)*/
  
} FLASH_EraseInitTypeDef;

/**
  * @brief  FLASH Option Bytes PROGRAM structure definition
  */
typedef struct
{
  uint32_t  OptionType;     /*!< OptionType: Option byte to be configured.
                              This parameter can be a value of @ref FLASHEx_Option_Type */

  uint32_t  WRPState;      /*!< WRPState: Write protection activation or deactivation.
                              This parameter can be a value of @ref FLASHEx_WRP_State */

  uint32_t  WRPSector0To31;    /*!< WRPSector0To31: specifies the sector(s) which are write protected between Sector 0 to 31
                              This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection1 */  
  
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  uint32_t  WRPSector32To63;    /*!< WRPSector32To63: specifies the sector(s) which are write protected between Sector 32 to 63
                                This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection2 */  
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  uint32_t  WRPSector64To95;    /*!< WRPSector64to95: specifies the sector(s) which are write protected between Sector 64 to 95
                                This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection3 */  
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  uint32_t  WRPSector96To127;    /*!< WRPSector96To127: specifies the sector(s) which are write protected between Sector 96 to 127
                              This parameter can be a combination of @ref FLASHEx_Option_Bytes_Write_Protection4 */  
#endif /* STM32L151xE || STM32L152xE || STM32L162xE */
                              
  uint8_t   RDPLevel;     /*!< RDPLevel: Set the read protection level..
                              This parameter can be a value of @ref FLASHEx_Option_Bytes_Read_Protection */

  uint8_t   BORLevel;     /*!< BORLevel: Set the BOR Level.
                              This parameter can be a value of @ref FLASHEx_Option_Bytes_BOR_Level */
                                
  uint8_t   USERConfig;     /*!< USERConfig: Program the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
                              This parameter can be a combination of @ref FLASHEx_Option_Bytes_IWatchdog, @ref FLASHEx_Option_Bytes_nRST_STOP and @ref FLASHEx_Option_Bytes_nRST_STDBY*/
} FLASH_OBProgramInitTypeDef;

/**
  * @brief  FLASH Advanced Option Bytes Program structure definition
  */
typedef struct
{
  uint32_t OptionType;     /*!< OptionType: Option byte to be configured for extension .
                              This parameter can be a value of @ref FLASHEx_OptionAdv_Type */

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
  uint32_t PCROPState;    /*!< PCROPState: PCROP activation or deactivation.
                              This parameter can be a value of @ref FLASHEx_PCROP_State */

  uint32_t  PCROPSector0To31;    /*!< PCROPSector0To31: specifies the sector(s) set for PCROP
                            This parameter can be a value of @ref FLASHEx_Option_Bytes_PC_ReadWrite_Protection1 */
  
#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
  uint32_t  PCROPSector32To63;    /*!< PCROPSector32To63: specifies the sector(s) set for PCROP
                            This parameter can be a value of @ref FLASHEx_Option_Bytes_PC_ReadWrite_Protection2 */
#endif /* STM32L151xC || STM32L152xC || STM32L162xC */
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */
 
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  uint16_t BootConfig;         /*!< BootConfig: specifies Option bytes for boot config
                                This parameter can be a value of @ref FLASHEx_Option_Bytes_BOOT */
#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE*/
} FLASH_AdvOBProgramInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/


/** @defgroup FLASHEx_Exported_Constants FLASHEx Exported Constants
  * @{
  */  

/** @defgroup FLASHEx_Type_Erase FLASHEx_Type_Erase
  * @{
  */
#define TYPEERASE_PAGES           ((uint32_t)0x00)  /*!<Page erase only*/
 
#define IS_TYPEERASE(__VALUE__)   (((__VALUE__) == TYPEERASE_PAGES))
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Type FLASHEx Option Type
  * @{
  */
#define OPTIONBYTE_WRP            ((uint32_t)0x01)  /*!<WRP option byte configuration*/
#define OPTIONBYTE_RDP            ((uint32_t)0x02)  /*!<RDP option byte configuration*/
#define OPTIONBYTE_USER           ((uint32_t)0x04)  /*!<USER option byte configuration*/
#define OPTIONBYTE_BOR            ((uint32_t)0x08)  /*!<BOR option byte configuration*/

#define IS_OPTIONBYTE(__VALUE__)  (((__VALUE__) < (OPTIONBYTE_WRP|OPTIONBYTE_RDP|OPTIONBYTE_USER|OPTIONBYTE_BOR)))
/**
  * @}
  */

/** @defgroup FLASHEx_WRP_State FLASHEx WRP State
  * @{
  */
#define WRPSTATE_DISABLE        ((uint32_t)0x00)  /*!<Disable the write protection of the desired bank 1 sectors*/
#define WRPSTATE_ENABLE         ((uint32_t)0x01)  /*!<Enable the write protection of the desired bank 1 sectors*/

#define IS_WRPSTATE(__VALUE__)  (((__VALUE__) == WRPSTATE_DISABLE) || \
                                 ((__VALUE__) == WRPSTATE_ENABLE))
/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_Write_Mask FLASHEx Option Bytes Write Mask
  * @{
  */ 
#define WRP_MASK_LOW                 ((uint32_t)0x0000FFFF)
#define WRP_MASK_HIGH                 ((uint32_t)0xFFFF0000)

/**
  * @}
  */ 

/** @defgroup FLASHEx_Option_Bytes_Write_Protection1 FLASHEx Option Bytes Write Protection1
  * @{
  */
  
/* Common pages for Cat1, Cat2, Cat3, Cat4 & Cat5 devices */
#define OB_WRP1_PAGES0TO15    ((uint32_t)0x00000001) /* Write protection of Sector0 */  
#define OB_WRP1_PAGES16TO31   ((uint32_t)0x00000002) /* Write protection of Sector1 */  
#define OB_WRP1_PAGES32TO47   ((uint32_t)0x00000004) /* Write protection of Sector2 */  
#define OB_WRP1_PAGES48TO63   ((uint32_t)0x00000008) /* Write protection of Sector3 */  
#define OB_WRP1_PAGES64TO79   ((uint32_t)0x00000010) /* Write protection of Sector4 */  
#define OB_WRP1_PAGES80TO95   ((uint32_t)0x00000020) /* Write protection of Sector5 */  
#define OB_WRP1_PAGES96TO111  ((uint32_t)0x00000040) /* Write protection of Sector6 */  
#define OB_WRP1_PAGES112TO127 ((uint32_t)0x00000080) /* Write protection of Sector7 */  
#define OB_WRP1_PAGES128TO143 ((uint32_t)0x00000100) /* Write protection of Sector8 */  
#define OB_WRP1_PAGES144TO159 ((uint32_t)0x00000200) /* Write protection of Sector9 */  
#define OB_WRP1_PAGES160TO175 ((uint32_t)0x00000400) /* Write protection of Sector10 */ 
#define OB_WRP1_PAGES176TO191 ((uint32_t)0x00000800) /* Write protection of Sector11 */ 
#define OB_WRP1_PAGES192TO207 ((uint32_t)0x00001000) /* Write protection of Sector12 */ 
#define OB_WRP1_PAGES208TO223 ((uint32_t)0x00002000) /* Write protection of Sector13 */ 
#define OB_WRP1_PAGES224TO239 ((uint32_t)0x00004000) /* Write protection of Sector14 */ 
#define OB_WRP1_PAGES240TO255 ((uint32_t)0x00008000) /* Write protection of Sector15 */ 
#define OB_WRP1_PAGES256TO271 ((uint32_t)0x00010000) /* Write protection of Sector16 */ 
#define OB_WRP1_PAGES272TO287 ((uint32_t)0x00020000) /* Write protection of Sector17 */ 
#define OB_WRP1_PAGES288TO303 ((uint32_t)0x00040000) /* Write protection of Sector18 */ 
#define OB_WRP1_PAGES304TO319 ((uint32_t)0x00080000) /* Write protection of Sector19 */ 
#define OB_WRP1_PAGES320TO335 ((uint32_t)0x00100000) /* Write protection of Sector20 */ 
#define OB_WRP1_PAGES336TO351 ((uint32_t)0x00200000) /* Write protection of Sector21 */ 
#define OB_WRP1_PAGES352TO367 ((uint32_t)0x00400000) /* Write protection of Sector22 */ 
#define OB_WRP1_PAGES368TO383 ((uint32_t)0x00800000) /* Write protection of Sector23 */ 
#define OB_WRP1_PAGES384TO399 ((uint32_t)0x01000000) /* Write protection of Sector24 */ 
#define OB_WRP1_PAGES400TO415 ((uint32_t)0x02000000) /* Write protection of Sector25 */ 
#define OB_WRP1_PAGES416TO431 ((uint32_t)0x04000000) /* Write protection of Sector26 */ 
#define OB_WRP1_PAGES432TO447 ((uint32_t)0x08000000) /* Write protection of Sector27 */ 
#define OB_WRP1_PAGES448TO463 ((uint32_t)0x10000000) /* Write protection of Sector28 */ 
#define OB_WRP1_PAGES464TO479 ((uint32_t)0x20000000) /* Write protection of Sector29 */ 
#define OB_WRP1_PAGES480TO495 ((uint32_t)0x40000000) /* Write protection of Sector30 */ 
#define OB_WRP1_PAGES496TO511 ((uint32_t)0x80000000) /* Write protection of Sector31 */ 
  
#define OB_WRP1_ALLPAGES      ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */
  
/**
  * @}
  */ 

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/** @defgroup FLASHEx_Option_Bytes_Write_Protection2 FLASHEx Option Bytes Write Protection2
  * @{
  */
  
/* Pages for Cat3, Cat4 & Cat5 devices*/
#define OB_WRP2_PAGES512TO527   ((uint32_t)0x00000001) /* Write protection of Sector32 */  
#define OB_WRP2_PAGES528TO543   ((uint32_t)0x00000002) /* Write protection of Sector33 */  
#define OB_WRP2_PAGES544TO559   ((uint32_t)0x00000004) /* Write protection of Sector34 */  
#define OB_WRP2_PAGES560TO575   ((uint32_t)0x00000008) /* Write protection of Sector35 */  
#define OB_WRP2_PAGES576TO591   ((uint32_t)0x00000010) /* Write protection of Sector36 */  
#define OB_WRP2_PAGES592TO607   ((uint32_t)0x00000020) /* Write protection of Sector37 */  
#define OB_WRP2_PAGES608TO623   ((uint32_t)0x00000040) /* Write protection of Sector38 */  
#define OB_WRP2_PAGES624TO639   ((uint32_t)0x00000080) /* Write protection of Sector39 */  
#define OB_WRP2_PAGES640TO655   ((uint32_t)0x00000100) /* Write protection of Sector40 */  
#define OB_WRP2_PAGES656TO671   ((uint32_t)0x00000200) /* Write protection of Sector41 */  
#define OB_WRP2_PAGES672TO687   ((uint32_t)0x00000400) /* Write protection of Sector42 */  
#define OB_WRP2_PAGES688TO703   ((uint32_t)0x00000800) /* Write protection of Sector43 */  
#define OB_WRP2_PAGES704TO719   ((uint32_t)0x00001000) /* Write protection of Sector44 */  
#define OB_WRP2_PAGES720TO735   ((uint32_t)0x00002000) /* Write protection of Sector45 */  
#define OB_WRP2_PAGES736TO751   ((uint32_t)0x00004000) /* Write protection of Sector46 */  
#define OB_WRP2_PAGES752TO767   ((uint32_t)0x00008000) /* Write protection of Sector47 */  
#define OB_WRP2_PAGES768TO783   ((uint32_t)0x00010000) /* Write protection of Sector48 */  
#define OB_WRP2_PAGES784TO799   ((uint32_t)0x00020000) /* Write protection of Sector49 */  
#define OB_WRP2_PAGES800TO815   ((uint32_t)0x00040000) /* Write protection of Sector50 */  
#define OB_WRP2_PAGES816TO831   ((uint32_t)0x00080000) /* Write protection of Sector51 */  
#define OB_WRP2_PAGES832TO847   ((uint32_t)0x00100000) /* Write protection of Sector52 */  
#define OB_WRP2_PAGES848TO863   ((uint32_t)0x00200000) /* Write protection of Sector53 */  
#define OB_WRP2_PAGES864TO879   ((uint32_t)0x00400000) /* Write protection of Sector54 */  
#define OB_WRP2_PAGES880TO895   ((uint32_t)0x00800000) /* Write protection of Sector55 */  
#define OB_WRP2_PAGES896TO911   ((uint32_t)0x01000000) /* Write protection of Sector56 */  
#define OB_WRP2_PAGES912TO927   ((uint32_t)0x02000000) /* Write protection of Sector57 */  
#define OB_WRP2_PAGES928TO943   ((uint32_t)0x04000000) /* Write protection of Sector58 */  
#define OB_WRP2_PAGES944TO959   ((uint32_t)0x08000000) /* Write protection of Sector59 */  
#define OB_WRP2_PAGES960TO975   ((uint32_t)0x10000000) /* Write protection of Sector60 */  
#define OB_WRP2_PAGES976TO991   ((uint32_t)0x20000000) /* Write protection of Sector61 */  
#define OB_WRP2_PAGES992TO1007  ((uint32_t)0x40000000) /* Write protection of Sector62 */
#define OB_WRP2_PAGES1008TO1023 ((uint32_t)0x80000000) /* Write protection of Sector63 */

#define OB_WRP2_ALLPAGES        ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */

/**
  * @}
  */ 

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/** @defgroup FLASHEx_Option_Bytes_Write_Protection3 FLASHEx Option Bytes Write Protection3
  * @{
  */
  
/* Pages for devices with FLASH >= 256KB*/
#define OB_WRP3_PAGES1024TO1039 ((uint32_t)0x00000001) /* Write protection of Sector64 */
#define OB_WRP3_PAGES1040TO1055 ((uint32_t)0x00000002) /* Write protection of Sector65 */
#define OB_WRP3_PAGES1056TO1071 ((uint32_t)0x00000004) /* Write protection of Sector66 */
#define OB_WRP3_PAGES1072TO1087 ((uint32_t)0x00000008) /* Write protection of Sector67 */
#define OB_WRP3_PAGES1088TO1103 ((uint32_t)0x00000010) /* Write protection of Sector68 */
#define OB_WRP3_PAGES1104TO1119 ((uint32_t)0x00000020) /* Write protection of Sector69 */
#define OB_WRP3_PAGES1120TO1135 ((uint32_t)0x00000040) /* Write protection of Sector70 */
#define OB_WRP3_PAGES1136TO1151 ((uint32_t)0x00000080) /* Write protection of Sector71 */
#define OB_WRP3_PAGES1152TO1167 ((uint32_t)0x00000100) /* Write protection of Sector72 */
#define OB_WRP3_PAGES1168TO1183 ((uint32_t)0x00000200) /* Write protection of Sector73 */
#define OB_WRP3_PAGES1184TO1199 ((uint32_t)0x00000400) /* Write protection of Sector74 */
#define OB_WRP3_PAGES1200TO1215 ((uint32_t)0x00000800) /* Write protection of Sector75 */
#define OB_WRP3_PAGES1216TO1231 ((uint32_t)0x00001000) /* Write protection of Sector76 */
#define OB_WRP3_PAGES1232TO1247 ((uint32_t)0x00002000) /* Write protection of Sector77 */
#define OB_WRP3_PAGES1248TO1263 ((uint32_t)0x00004000) /* Write protection of Sector78 */
#define OB_WRP3_PAGES1264TO1279 ((uint32_t)0x00008000) /* Write protection of Sector79 */
#define OB_WRP3_PAGES1280TO1295 ((uint32_t)0x00010000) /* Write protection of Sector80 */
#define OB_WRP3_PAGES1296TO1311 ((uint32_t)0x00020000) /* Write protection of Sector81 */
#define OB_WRP3_PAGES1312TO1327 ((uint32_t)0x00040000) /* Write protection of Sector82 */
#define OB_WRP3_PAGES1328TO1343 ((uint32_t)0x00080000) /* Write protection of Sector83 */
#define OB_WRP3_PAGES1344TO1359 ((uint32_t)0x00100000) /* Write protection of Sector84 */
#define OB_WRP3_PAGES1360TO1375 ((uint32_t)0x00200000) /* Write protection of Sector85 */
#define OB_WRP3_PAGES1376TO1391 ((uint32_t)0x00400000) /* Write protection of Sector86 */
#define OB_WRP3_PAGES1392TO1407 ((uint32_t)0x00800000) /* Write protection of Sector87 */
#define OB_WRP3_PAGES1408TO1423 ((uint32_t)0x01000000) /* Write protection of Sector88 */
#define OB_WRP3_PAGES1424TO1439 ((uint32_t)0x02000000) /* Write protection of Sector89 */
#define OB_WRP3_PAGES1440TO1455 ((uint32_t)0x04000000) /* Write protection of Sector90 */
#define OB_WRP3_PAGES1456TO1471 ((uint32_t)0x08000000) /* Write protection of Sector91 */
#define OB_WRP3_PAGES1472TO1487 ((uint32_t)0x10000000) /* Write protection of Sector92 */
#define OB_WRP3_PAGES1488TO1503 ((uint32_t)0x20000000) /* Write protection of Sector93 */
#define OB_WRP3_PAGES1504TO1519 ((uint32_t)0x40000000) /* Write protection of Sector94 */
#define OB_WRP3_PAGES1520TO1535 ((uint32_t)0x80000000) /* Write protection of Sector95 */

#define OB_WRP3_ALLPAGES        ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */

/**
  * @}
  */ 

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE*/

#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/** @defgroup FLASHEx_Option_Bytes_Write_Protection4 FLASHEx Option Bytes Write Protection4
  * @{
  */
  
/* Pages for Cat5 devices*/
#define OB_WRP4_PAGES1536TO1551 ((uint32_t)0x00000001)/* Write protection of Sector96*/   
#define OB_WRP4_PAGES1552TO1567 ((uint32_t)0x00000002)/* Write protection of Sector97*/   
#define OB_WRP4_PAGES1568TO1583 ((uint32_t)0x00000004)/* Write protection of Sector98*/   
#define OB_WRP4_PAGES1584TO1599 ((uint32_t)0x00000008)/* Write protection of Sector99*/   
#define OB_WRP4_PAGES1600TO1615 ((uint32_t)0x00000010) /* Write protection of Sector100*/ 
#define OB_WRP4_PAGES1616TO1631 ((uint32_t)0x00000020) /* Write protection of Sector101*/ 
#define OB_WRP4_PAGES1632TO1647 ((uint32_t)0x00000040) /* Write protection of Sector102*/ 
#define OB_WRP4_PAGES1648TO1663 ((uint32_t)0x00000080) /* Write protection of Sector103*/ 
#define OB_WRP4_PAGES1664TO1679 ((uint32_t)0x00000100) /* Write protection of Sector104*/ 
#define OB_WRP4_PAGES1680TO1695 ((uint32_t)0x00000200) /* Write protection of Sector105*/ 
#define OB_WRP4_PAGES1696TO1711 ((uint32_t)0x00000400) /* Write protection of Sector106*/ 
#define OB_WRP4_PAGES1712TO1727 ((uint32_t)0x00000800) /* Write protection of Sector107*/ 
#define OB_WRP4_PAGES1728TO1743 ((uint32_t)0x00001000) /* Write protection of Sector108*/ 
#define OB_WRP4_PAGES1744TO1759 ((uint32_t)0x00002000) /* Write protection of Sector109*/ 
#define OB_WRP4_PAGES1760TO1775 ((uint32_t)0x00004000) /* Write protection of Sector110*/ 
#define OB_WRP4_PAGES1776TO1791 ((uint32_t)0x00008000) /* Write protection of Sector111*/ 
#define OB_WRP4_PAGES1792TO1807 ((uint32_t)0x00010000) /* Write protection of Sector112*/ 
#define OB_WRP4_PAGES1808TO1823 ((uint32_t)0x00020000) /* Write protection of Sector113*/ 
#define OB_WRP4_PAGES1824TO1839 ((uint32_t)0x00040000) /* Write protection of Sector114*/ 
#define OB_WRP4_PAGES1840TO1855 ((uint32_t)0x00080000) /* Write protection of Sector115*/ 
#define OB_WRP4_PAGES1856TO1871 ((uint32_t)0x00100000) /* Write protection of Sector116*/ 
#define OB_WRP4_PAGES1872TO1887 ((uint32_t)0x00200000) /* Write protection of Sector117*/ 
#define OB_WRP4_PAGES1888TO1903 ((uint32_t)0x00400000) /* Write protection of Sector118*/ 
#define OB_WRP4_PAGES1904TO1919 ((uint32_t)0x00800000) /* Write protection of Sector119*/ 
#define OB_WRP4_PAGES1920TO1935 ((uint32_t)0x01000000) /* Write protection of Sector120*/ 
#define OB_WRP4_PAGES1936TO1951 ((uint32_t)0x02000000) /* Write protection of Sector121*/ 
#define OB_WRP4_PAGES1952TO1967 ((uint32_t)0x04000000) /* Write protection of Sector122*/ 
#define OB_WRP4_PAGES1968TO1983 ((uint32_t)0x08000000) /* Write protection of Sector123*/ 
#define OB_WRP4_PAGES1984TO1999 ((uint32_t)0x10000000) /* Write protection of Sector124*/ 
#define OB_WRP4_PAGES2000TO2015 ((uint32_t)0x20000000) /* Write protection of Sector125*/ 
#define OB_WRP4_PAGES2016TO2031 ((uint32_t)0x40000000) /* Write protection of Sector126*/ 
#define OB_WRP4_PAGES2032TO2047 ((uint32_t)0x80000000) /* Write protection of Sector127*/ 

#define OB_WRP4_ALLPAGES        ((uint32_t)0xFFFFFFFF) /*!< Write protection of all Sectors */

/**
  * @}
  */ 

#endif /* STM32L151xE || STM32L152xE || STM32L162xE */

/** @defgroup FLASHEx_Option_Bytes_Read_Protection FLASHEx Option Bytes Read Protection
  * @{
  */ 
#define OB_RDP_LEVEL0         ((uint8_t)0xAA)
#define OB_RDP_LEVEL1         ((uint8_t)0xBB)
/*#define OB_RDP_LEVEL2   ((uint8_t)0xCC)*/ /* Warning: When enabling read protection level 2 
                                                it's no more possible to go back to level 1 or 0 */

#define IS_OB_RDP(__LEVEL__)  (((__LEVEL__) == OB_RDP_LEVEL0)||\
                               ((__LEVEL__) == OB_RDP_LEVEL1))/*||\
                          ((__LEVEL__) == OB_RDP_LEVEL2))*/
/**
  * @}
  */ 

/** @defgroup FLASHEx_Option_Bytes_BOR_Level FLASHEx Option Bytes BOR Level
  * @{
  */

#define OB_BOR_OFF       ((uint8_t)0x00) /*!< BOR is disabled at power down, the reset is asserted when the VDD 
                                              power supply reaches the PDR(Power Down Reset) threshold (1.5V) */
#define OB_BOR_LEVEL1    ((uint8_t)0x08) /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply    */
#define OB_BOR_LEVEL2    ((uint8_t)0x09) /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply    */
#define OB_BOR_LEVEL3    ((uint8_t)0x0A) /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply    */
#define OB_BOR_LEVEL4    ((uint8_t)0x0B) /*!< BOR Reset threshold levels for 2.55V - 2.65V VDD power supply  */
#define OB_BOR_LEVEL5    ((uint8_t)0x0C) /*!< BOR Reset threshold levels for 2.8V - 2.9V VDD power supply    */

#define IS_OB_BOR_LEVEL(__LEVEL__)  ( ((__LEVEL__) == OB_BOR_OFF)     || \
                                      ((__LEVEL__) == OB_BOR_LEVEL1)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL2)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL3)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL4)  || \
                                      ((__LEVEL__) == OB_BOR_LEVEL5))

/**
  * @}
  */
  
/** @defgroup FLASHEx_Option_Bytes_IWatchdog FLASHEx Option Bytes IWatchdog
  * @{
  */

#define OB_IWDG_SW                     ((uint8_t)0x10)  /*!< Software WDG selected */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< Hardware WDG selected */

#define IS_OB_IWDG_SOURCE(__SOURCE__) (((__SOURCE__) == OB_IWDG_SW) || ((__SOURCE__) == OB_IWDG_HW))

/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_nRST_STOP FLASHEx Option Bytes nRST_STOP
  * @{
  */

#define OB_STOP_NORST                  ((uint8_t)0x20) /*!< No reset generated when entering in STOP */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< Reset generated when entering in STOP */
#define IS_OB_STOP_SOURCE(__SOURCE__) (((__SOURCE__) == OB_STOP_NORST) || ((__SOURCE__) == OB_STOP_RST))

/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_nRST_STDBY FLASHEx Option Bytes nRST_STDBY
  * @{
  */

#define OB_STDBY_NORST                 ((uint8_t)0x40) /*!< No reset generated when entering in STANDBY */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< Reset generated when entering in STANDBY */
#define IS_OB_STDBY_SOURCE(__SOURCE__) (((__SOURCE__) == OB_STDBY_NORST) || ((__SOURCE__) == OB_STDBY_RST))

/**
  * @}
  */

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
    
/** @defgroup FLASHEx_OptionAdv_Type FLASHEx Option Advanced Type
  * @{
  */ 
  
#define OBEX_PCROP        ((uint32_t)0x01)  /*!<PCROP option byte configuration*/

#define IS_OBEX(__VALUE__)        ((__VALUE__) == OBEX_PCROP)

/**
  * @}
  */

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/** @defgroup FLASHEx_OptionAdv_Type FLASHEx Option Advanced Type
  * @{
  */ 
  
#define OBEX_BOOTCONFIG   ((uint32_t)0x02)  /*!<BOOTConfig option byte configuration*/

#define IS_OBEX(__VALUE__)        ((__VALUE__) == OBEX_BOOTCONFIG)

/**
  * @}
  */

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

/** @defgroup  FLASHEx_PCROP_State FLASHEx PCROP State
  * @{
  */
#define PCROPSTATE_DISABLE        ((uint32_t)0x00)  /*!<Disable PCROP for selected sectors */
#define PCROPSTATE_ENABLE         ((uint32_t)0x01)  /*!<Enable PCROP for selected sectors */
    
#define IS_PCROPSTATE(__VALUE__)  (((__VALUE__) == PCROPSTATE_DISABLE) || \
                                   ((__VALUE__) == PCROPSTATE_ENABLE))  
/**
  * @}
  */

/** @defgroup  FLASHEx_Selection_Protection_Mode FLASHEx Selection Protection Mode
  * @{
  */
#define OB_PCROP_DESELECTED     ((uint16_t)0x0000)            /*!< Disabled PCROP, nWPRi bits used for Write Protection on sector i */
#define OB_PCROP_SELECTED       ((uint16_t)FLASH_OBR_SPRMOD)  /*!< Enable PCROP, nWPRi bits used for PCRoP Protection on sector i   */

/**
  * @}
  */

/** @defgroup FLASHEx_Option_Bytes_PC_ReadWrite_Protection1 FLASHEx Option Bytes PC ReadWrite Protection 1
  * @{
  */
  
/* Common pages for Cat1, Cat2, Cat3, Cat4 & Cat5 devices */
#define OB_PCROP1_PAGES0TO15    ((uint32_t)0x00000001) /* PC Read/Write  protection of Sector0 */  
#define OB_PCROP1_PAGES16TO31   ((uint32_t)0x00000002) /* PC Read/Write  protection of Sector1 */  
#define OB_PCROP1_PAGES32TO47   ((uint32_t)0x00000004) /* PC Read/Write  protection of Sector2 */  
#define OB_PCROP1_PAGES48TO63   ((uint32_t)0x00000008) /* PC Read/Write  protection of Sector3 */  
#define OB_PCROP1_PAGES64TO79   ((uint32_t)0x00000010) /* PC Read/Write  protection of Sector4 */  
#define OB_PCROP1_PAGES80TO95   ((uint32_t)0x00000020) /* PC Read/Write  protection of Sector5 */  
#define OB_PCROP1_PAGES96TO111  ((uint32_t)0x00000040) /* PC Read/Write  protection of Sector6 */  
#define OB_PCROP1_PAGES112TO127 ((uint32_t)0x00000080) /* PC Read/Write  protection of Sector7 */  
#define OB_PCROP1_PAGES128TO143 ((uint32_t)0x00000100) /* PC Read/Write  protection of Sector8 */  
#define OB_PCROP1_PAGES144TO159 ((uint32_t)0x00000200) /* PC Read/Write  protection of Sector9 */  
#define OB_PCROP1_PAGES160TO175 ((uint32_t)0x00000400) /* PC Read/Write  protection of Sector10 */ 
#define OB_PCROP1_PAGES176TO191 ((uint32_t)0x00000800) /* PC Read/Write  protection of Sector11 */ 
#define OB_PCROP1_PAGES192TO207 ((uint32_t)0x00001000) /* PC Read/Write  protection of Sector12 */ 
#define OB_PCROP1_PAGES208TO223 ((uint32_t)0x00002000) /* PC Read/Write  protection of Sector13 */ 
#define OB_PCROP1_PAGES224TO239 ((uint32_t)0x00004000) /* PC Read/Write  protection of Sector14 */ 
#define OB_PCROP1_PAGES240TO255 ((uint32_t)0x00008000) /* PC Read/Write  protection of Sector15 */ 
#define OB_PCROP1_PAGES256TO271 ((uint32_t)0x00010000) /* PC Read/Write  protection of Sector16 */ 
#define OB_PCROP1_PAGES272TO287 ((uint32_t)0x00020000) /* PC Read/Write  protection of Sector17 */ 
#define OB_PCROP1_PAGES288TO303 ((uint32_t)0x00040000) /* PC Read/Write  protection of Sector18 */ 
#define OB_PCROP1_PAGES304TO319 ((uint32_t)0x00080000) /* PC Read/Write  protection of Sector19 */ 
#define OB_PCROP1_PAGES320TO335 ((uint32_t)0x00100000) /* PC Read/Write  protection of Sector20 */ 
#define OB_PCROP1_PAGES336TO351 ((uint32_t)0x00200000) /* PC Read/Write  protection of Sector21 */ 
#define OB_PCROP1_PAGES352TO367 ((uint32_t)0x00400000) /* PC Read/Write  protection of Sector22 */ 
#define OB_PCROP1_PAGES368TO383 ((uint32_t)0x00800000) /* PC Read/Write  protection of Sector23 */ 
#define OB_PCROP1_PAGES384TO399 ((uint32_t)0x01000000) /* PC Read/Write  protection of Sector24 */ 
#define OB_PCROP1_PAGES400TO415 ((uint32_t)0x02000000) /* PC Read/Write  protection of Sector25 */ 
#define OB_PCROP1_PAGES416TO431 ((uint32_t)0x04000000) /* PC Read/Write  protection of Sector26 */ 
#define OB_PCROP1_PAGES432TO447 ((uint32_t)0x08000000) /* PC Read/Write  protection of Sector27 */ 
#define OB_PCROP1_PAGES448TO463 ((uint32_t)0x10000000) /* PC Read/Write  protection of Sector28 */ 
#define OB_PCROP1_PAGES464TO479 ((uint32_t)0x20000000) /* PC Read/Write  protection of Sector29 */ 
#define OB_PCROP1_PAGES480TO495 ((uint32_t)0x40000000) /* PC Read/Write  protection of Sector30 */ 
#define OB_PCROP1_PAGES496TO511 ((uint32_t)0x80000000) /* PC Read/Write  protection of Sector31 */ 
  
#define OB_PCROP1_ALLPAGES      ((uint32_t)0xFFFFFFFF) /*!< PC Read/Write  protection of all Sectors */
  
/**
  * @}
  */ 

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

/** @defgroup FLASHEx_Option_Bytes_PC_ReadWrite_Protection2 FLASHEx Option Bytes PC ReadWrite Protection 2
  * @{
  */
  
/* Pages for Cat3, Cat4 & Cat5 devices*/
#define OB_PCROP2_PAGES512TO527   ((uint32_t)0x00000001) /* PC Read/Write  protection of Sector32 */  
#define OB_PCROP2_PAGES528TO543   ((uint32_t)0x00000002) /* PC Read/Write  protection of Sector33 */  
#define OB_PCROP2_PAGES544TO559   ((uint32_t)0x00000004) /* PC Read/Write  protection of Sector34 */  
#define OB_PCROP2_PAGES560TO575   ((uint32_t)0x00000008) /* PC Read/Write  protection of Sector35 */  
#define OB_PCROP2_PAGES576TO591   ((uint32_t)0x00000010) /* PC Read/Write  protection of Sector36 */  
#define OB_PCROP2_PAGES592TO607   ((uint32_t)0x00000020) /* PC Read/Write  protection of Sector37 */  
#define OB_PCROP2_PAGES608TO623   ((uint32_t)0x00000040) /* PC Read/Write  protection of Sector38 */  
#define OB_PCROP2_PAGES624TO639   ((uint32_t)0x00000080) /* PC Read/Write  protection of Sector39 */  
#define OB_PCROP2_PAGES640TO655   ((uint32_t)0x00000100) /* PC Read/Write  protection of Sector40 */  
#define OB_PCROP2_PAGES656TO671   ((uint32_t)0x00000200) /* PC Read/Write  protection of Sector41 */  
#define OB_PCROP2_PAGES672TO687   ((uint32_t)0x00000400) /* PC Read/Write  protection of Sector42 */  
#define OB_PCROP2_PAGES688TO703   ((uint32_t)0x00000800) /* PC Read/Write  protection of Sector43 */  
#define OB_PCROP2_PAGES704TO719   ((uint32_t)0x00001000) /* PC Read/Write  protection of Sector44 */  
#define OB_PCROP2_PAGES720TO735   ((uint32_t)0x00002000) /* PC Read/Write  protection of Sector45 */  
#define OB_PCROP2_PAGES736TO751   ((uint32_t)0x00004000) /* PC Read/Write  protection of Sector46 */  
#define OB_PCROP2_PAGES752TO767   ((uint32_t)0x00008000) /* PC Read/Write  protection of Sector47 */  
#define OB_PCROP2_PAGES768TO783   ((uint32_t)0x00010000) /* PC Read/Write  protection of Sector48 */  
#define OB_PCROP2_PAGES784TO799   ((uint32_t)0x00020000) /* PC Read/Write  protection of Sector49 */  
#define OB_PCROP2_PAGES800TO815   ((uint32_t)0x00040000) /* PC Read/Write  protection of Sector50 */  
#define OB_PCROP2_PAGES816TO831   ((uint32_t)0x00080000) /* PC Read/Write  protection of Sector51 */  
#define OB_PCROP2_PAGES832TO847   ((uint32_t)0x00100000) /* PC Read/Write  protection of Sector52 */  
#define OB_PCROP2_PAGES848TO863   ((uint32_t)0x00200000) /* PC Read/Write  protection of Sector53 */  
#define OB_PCROP2_PAGES864TO879   ((uint32_t)0x00400000) /* PC Read/Write  protection of Sector54 */  
#define OB_PCROP2_PAGES880TO895   ((uint32_t)0x00800000) /* PC Read/Write  protection of Sector55 */  
#define OB_PCROP2_PAGES896TO911   ((uint32_t)0x01000000) /* PC Read/Write  protection of Sector56 */  
#define OB_PCROP2_PAGES912TO927   ((uint32_t)0x02000000) /* PC Read/Write  protection of Sector57 */  
#define OB_PCROP2_PAGES928TO943   ((uint32_t)0x04000000) /* PC Read/Write  protection of Sector58 */  
#define OB_PCROP2_PAGES944TO959   ((uint32_t)0x08000000) /* PC Read/Write  protection of Sector59 */  
#define OB_PCROP2_PAGES960TO975   ((uint32_t)0x10000000) /* PC Read/Write  protection of Sector60 */  
#define OB_PCROP2_PAGES976TO991   ((uint32_t)0x20000000) /* PC Read/Write  protection of Sector61 */  
#define OB_PCROP2_PAGES992TO1007  ((uint32_t)0x40000000) /* PC Read/Write  protection of Sector62 */
#define OB_PCROP2_PAGES1008TO1023 ((uint32_t)0x80000000) /* PC Read/Write  protection of Sector63 */

#define OB_PCROP2_ALLPAGES        ((uint32_t)0xFFFFFFFF) /*!< PC Read/Write  protection of all Sectors */

/**
  * @}
  */ 

#endif /* STM32L151xC || STM32L152xC || STM32L162xC */

/** @defgroup FLASHEx_Type_Erase_Data FLASHEx Type Erase Data
  * @{
  */
#define TYPEERASEDATA_BYTE            ((uint32_t)0x00)  /*!<Erase byte (8-bit) at a specified address.*/
#define TYPEERASEDATA_HALFWORD        ((uint32_t)0x01)  /*!<Erase a half-word (16-bit) at a specified address.*/
#define TYPEERASEDATA_WORD            ((uint32_t)0x02)  /*!<Erase a word (32-bit) at a specified address.*/

#define IS_TYPEERASEDATA(__VALUE__)   (((__VALUE__) == TYPEERASEDATA_BYTE) || \
                                       ((__VALUE__) == TYPEERASEDATA_HALFWORD) || \
                                       ((__VALUE__) == TYPEERASEDATA_WORD))
/**
  * @}
  */

/** @defgroup FLASHEx_Type_Program_Data FLASHEx Type Program Data
  * @{
  */
#define TYPEPROGRAMDATA_BYTE            ((uint32_t)0x00)  /*!<Program byte (8-bit) at a specified address.*/
#define TYPEPROGRAMDATA_HALFWORD        ((uint32_t)0x01)  /*!<Program a half-word (16-bit) at a specified address.*/
#define TYPEPROGRAMDATA_WORD            ((uint32_t)0x02)  /*!<Program a word (32-bit) at a specified address.*/
#define TYPEPROGRAMDATA_FASTBYTE        ((uint32_t)0x04)  /*!<Fast Program byte (8-bit) at a specified address.*/
#define TYPEPROGRAMDATA_FASTHALFWORD    ((uint32_t)0x08)  /*!<Fast Program a half-word (16-bit) at a specified address.*/
#define TYPEPROGRAMDATA_FASTWORD        ((uint32_t)0x10)  /*!<Fast Program a word (32-bit) at a specified address.*/

#define IS_TYPEPROGRAMDATA(__VALUE__)   (((__VALUE__) == TYPEPROGRAMDATA_BYTE) || \
                                         ((__VALUE__) == TYPEPROGRAMDATA_HALFWORD) || \
                                         ((__VALUE__) == TYPEPROGRAMDATA_WORD) || \
                                         ((__VALUE__) == TYPEPROGRAMDATA_FASTBYTE) || \
                                         ((__VALUE__) == TYPEPROGRAMDATA_FASTHALFWORD) || \
                                         ((__VALUE__) == TYPEPROGRAMDATA_FASTWORD))
/**
  * @}
  */


/** @defgroup FLASHEx_Address FLASHEx Address
  * @{
  */
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || \
   defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA)
     
/******* Devices with FLASH 128K *******/
#define FLASH_NBPAGES_MAX       512 /* 512 pages from page 0 to page 511 */

#elif defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined (STM32L151xCA) || defined (STM32L152xCA) || defined (STM32L162xCA)

/******* Devices with FLASH 256K *******/
#define FLASH_NBPAGES_MAX       1025 /* 1025 pages from page 0 to page 1024 */

#elif defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

/******* Devices with FLASH 384K *******/
#define FLASH_NBPAGES_MAX       1536 /* 1536 pages from page 0 to page 1535 */

#elif defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

/******* Devices with FLASH 512K *******/
#define FLASH_NBPAGES_MAX       2048 /* 2048 pages from page 0 to page 2047 */

#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA */

#define IS_FLASH_DATA_ADDRESS(__ADDRESS__)          (((__ADDRESS__) >= FLASH_EEPROM_BASE) && ((__ADDRESS__) <= FLASH_EEPROM_END))

#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || \
    defined(STM32L100xBA) || defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined (STM32L151xCA) || defined (STM32L152xCA) || defined (STM32L162xCA)

#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)       (((__ADDRESS__) >= FLASH_BASE) && ((__ADDRESS__) <= FLASH_END))  

#else /*STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#define IS_FLASH_PROGRAM_ADDRESS(__ADDRESS__)       (((__ADDRESS__) >= FLASH_BASE) && ((__ADDRESS__) <= FLASH_BANK2_END))  
#define IS_FLASH_PROGRAM_BANK1_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= FLASH_BASE) && ((__ADDRESS__) <= FLASH_BANK1_END))  
#define IS_FLASH_PROGRAM_BANK2_ADDRESS(__ADDRESS__) (((__ADDRESS__) >= FLASH_BANK2_BASE) && ((__ADDRESS__) <= FLASH_BANK2_END))  

#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA || STM32L151xBA || STM32L152xBA  || STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L152xCA || STM32L162xCA */

#define IS_NBPAGES(_PAGES_) (((_PAGES_) >= 1) && ((_PAGES_) <= FLASH_NBPAGES_MAX)) 

/**
  * @}
  */ 

/** @defgroup FLASHEx_Flags FLASHEx Flags
  * @{
  */ 

/* Cat2 & Cat3*/
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
    
#define FLASH_FLAG_RDERR               FLASH_SR_RDERR    /*!< Read protected error flag  */

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

/* Cat3, Cat4 & Cat5*/
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define FLASH_FLAG_OPTVERRUSR          FLASH_SR_OPTVERRUSR /*!< FLASH Option User Validity error flag  */

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/* Cat1*/
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB) || defined (STM32L100xBA)

#define FLASH_FLAG_MASK         ( FLASH_FLAG_EOP        | FLASH_FLAG_ENDHV  | FLASH_FLAG_WRPERR | \
                                  FLASH_FLAG_OPTVERR    | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR)

#endif /* STM32L100xB || STM32L151xB || STM32L152xB || STM32L100xBA */

/* RDERR only for STM32L151xBA & STM32L152xBA (Cat2)*/
#if defined (STM32L151xBA) || defined (STM32L152xBA)

#define FLASH_FLAG_MASK         ( FLASH_FLAG_EOP        | FLASH_FLAG_ENDHV  | FLASH_FLAG_WRPERR | \
                                  FLASH_FLAG_OPTVERR    | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | \
                                  FLASH_FLAG_RDERR)

#endif /* STM32L151xBA || STM32L152xBA */

/* FLASH_FLAG_OPTVERRUSR & RDERR only for STM32L151xC, STM32L152xC & STM32L152xBA (Cat3) */
#if defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

#define FLASH_FLAG_MASK         ( FLASH_FLAG_EOP        | FLASH_FLAG_ENDHV  | FLASH_FLAG_WRPERR | \
                                  FLASH_FLAG_OPTVERR    | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | \
                                  FLASH_FLAG_OPTVERRUSR | FLASH_FLAG_RDERR)

#endif /* STM32L151xC || STM32L152xC || STM32L162xC */

/* FLASH_FLAG_OPTVERRUSR only for STM32L100xC (Cat3) */
#if defined (STM32L100xC)

#define FLASH_FLAG_MASK         ( FLASH_FLAG_EOP        | FLASH_FLAG_ENDHV  | FLASH_FLAG_WRPERR | \
                                  FLASH_FLAG_OPTVERR    | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | \
                                  FLASH_FLAG_OPTVERRUSR)

#endif /* STM32L100xC */

/* Cat4 & Cat5 */
#if defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
#define FLASH_FLAG_MASK         ( FLASH_FLAG_EOP        | FLASH_FLAG_ENDHV  | FLASH_FLAG_WRPERR | \
                                  FLASH_FLAG_OPTVERR    | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR | \
                                  FLASH_FLAG_OPTVERRUSR)

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @}
  */
  
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
/** @defgroup FLASHEx_Option_Bytes_BOOT FLASHEx Option Bytes BOOT
  * @{
  */

#define OB_BOOT_BANK2                 ((uint8_t)0x00) /*!< At startup, if boot pins are set in boot from user Flash position
                                                            and this parameter is selected the device will boot from Bank 2 
                                                            or Bank 1, depending on the activation of the bank */
#define OB_BOOT_BANK1                 ((uint8_t)(FLASH_OBR_nRST_BFB2 >> 16)) /*!< At startup, if boot pins are set in boot from user Flash position
                                                            and this parameter is selected the device will boot from Bank1(Default) */
#define IS_OB_BOOT_BANK(__BANK__)     (((__BANK__) == OB_BOOT_BANK2) || ((__BANK__) == OB_BOOT_BANK1))

/**
  * @}
  */
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup FLASHEx_Exported_Macros FLASHEx Exported Macros
 *  @{
 */
 
/**
  * @brief  Set the FLASH Latency.
  * @param  __LATENCY__: FLASH Latency
  *          This parameter can be one of the following values:
  *            @arg FLASH_LATENCY_0:  FLASH Zero Latency cycle
  *            @arg FLASH_LATENCY_1:  FLASH One Latency cycle
  * @retval none
  */ 
#define __HAL_FLASH_SET_LATENCY(__LATENCY__)  do  { \
                                                  if ((__LATENCY__) == FLASH_LATENCY_1) {__HAL_FLASH_ACC64_ENABLE();} \
                                                  MODIFY_REG((FLASH->ACR), FLASH_ACR_LATENCY, (__LATENCY__)); \
                                              } while(0)

/**
  * @brief  Get the FLASH Latency.
  * @retval FLASH Latency                   
  *          This parameter can be one of the following values:
  *            @arg FLASH_LATENCY_0:  FLASH Zero Latency cycle
  *            @arg FLASH_LATENCY_1:  FLASH One Latency cycle
  */ 
#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))

  /**
  * @brief  Enable the FLASH 64-bit access.
  * @note    Read access 64 bit is used.
  * @note    This bit cannot be written at the same time as the LATENCY and 
  *          PRFTEN bits.
  * @retval none
  */ 
#define __HAL_FLASH_ACC64_ENABLE()    (SET_BIT((FLASH->ACR), FLASH_ACR_ACC64))

  /**
  * @brief  Disable the FLASH 64-bit access.
  * @note     Read access 32 bit is used
  * @note     To reset this bit, the LATENCY should be zero wait state and the 
  *               prefetch off.
  * @retval none
  */ 
#define __HAL_FLASH_ACC64_DISABLE()   (CLEAR_BIT((FLASH->ACR), FLASH_ACR_ACC64))

  /**
  * @brief  Enable the FLASH prefetch buffer.
  * @retval none
  */ 
#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()    do  { __HAL_FLASH_ACC64_ENABLE(); \
                                                  SET_BIT((FLASH->ACR), FLASH_ACR_PRFTEN); \
                                                } while(0)

/**
  * @brief  Disable the FLASH prefetch buffer.
  * @retval none
  */ 
#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()     CLEAR_BIT((FLASH->ACR), FLASH_ACR_PRFTEN)

/**
  * @brief  Enable the FLASH power down during Sleep mode
  * @retval none
  */ 
#define __HAL_FLASH_SLEEP_POWERDOWN_ENABLE()      SET_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Disable the FLASH power down during Sleep mode
  * @retval none
  */ 
#define __HAL_FLASH_SLEEP_POWERDOWN_DISABLE()     CLEAR_BIT(FLASH->ACR, FLASH_ACR_SLEEP_PD)

/**
  * @brief  Macro to enable or disable the Flash Run power down mode.
  * @note   Writing this bit  to 0 this bit, automatically the keys are
  *         loss and a new unlock sequence is necessary to re-write it to 1.
  */

#define __HAL_FLASH_POWER_DOWN_ENABLE() do { FLASH->PDKEYR = FLASH_PDKEY1;    \
                                             FLASH->PDKEYR = FLASH_PDKEY2;    \
                                             SET_BIT((FLASH->ACR), FLASH_ACR_RUN_PD);  \
                                           } while (0)

#define __HAL_FLASH_POWER_DOWN_DISABLE() do { FLASH->PDKEYR = FLASH_PDKEY1;    \
                                              FLASH->PDKEYR = FLASH_PDKEY2;    \
                                             CLEAR_BIT((FLASH->ACR), FLASH_ACR_RUN_PD);  \
                                            } while (0)
                                            
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */

HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);

/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
HAL_StatusTypeDef HAL_FLASHEx_AdvOBProgram (FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
void              HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void);
HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void);

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group3
  * @{
  */

HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Unlock(void);
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Lock(void);

HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Erase(uint32_t TypeErase, uint32_t Address);
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data);
void              HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram(void);
void              HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram(void);

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

#endif /* __STM32L1xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
