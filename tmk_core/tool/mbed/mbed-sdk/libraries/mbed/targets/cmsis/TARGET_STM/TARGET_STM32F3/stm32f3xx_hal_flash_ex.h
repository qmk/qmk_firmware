/**
  ******************************************************************************
  * @file    stm32f3xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of Flash HAL Extended module.
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
#ifndef __STM32F3xx_HAL_FLASH_EX_H
#define __STM32F3xx_HAL_FLASH_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx FLASH Extended HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Constants FLASH Extended Exported Constants
  * @{
  */  
#define FLASH_SIZE_DATA_REGISTER ((uint32_t)0x1FFFF7CC)
#define FLASH_PAGE_SIZE          0x800
/**
  * @}
  */

/** @defgroup FLASHEx_Address FLASH Extended Address
  * @{
  */
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x100) ? \
                                           ((ADDRESS) <= 0x0803FFFF) :  (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x80) ? \
                                           ((ADDRESS) <= 0x0801FFFF) :  ((ADDRESS) <= 0x0800FFFF))))
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0807FFFF))
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define IS_FLASH_PROGRAM_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x40) ? \
                                           ((ADDRESS) <= 0x0800FFFF) :  (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x20) ? \
                                           ((ADDRESS) <= 0x08007FFF) :  ((ADDRESS) <= 0x08003FFF))))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx */
/**
  * @}
  */

/** @defgroup FLASHEx_Nb_Pages FLASH Extended Nb Pages
  * @{
  */
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define IS_FLASH_NB_PAGES(ADDRESS,NBPAGES) (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x100) ? ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x0803FFFF) : \
                                           (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x80)  ? ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x0801FFFF) : \
                                            ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x0800FFFF)))
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define IS_FLASH_NB_PAGES(ADDRESS,NBPAGES) ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x0807FFFF)
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define IS_FLASH_NB_PAGES(ADDRESS,NBPAGES) (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x40) ? ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x0800FFFF) : \
                                           (((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x20) ? ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x08007FFF) : \
                                            ((ADDRESS)+((NBPAGES)*FLASH_PAGE_SIZE)-1 <= 0x08003FFF)))
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx */
/**
  * @}
  */

/** @defgroup FLASHEx_OB_Write_Protection FLASH Extended Option Bytes Write Protection
  * @{
  */
#define OB_WRP_PAGES0TO1               ((uint32_t)0x00000001) /* Write protection of page 0 to 1 */
#define OB_WRP_PAGES2TO3               ((uint32_t)0x00000002) /* Write protection of page 2 to 3 */
#define OB_WRP_PAGES4TO5               ((uint32_t)0x00000004) /* Write protection of page 4 to 5 */
#define OB_WRP_PAGES6TO7               ((uint32_t)0x00000008) /* Write protection of page 6 to 7 */
#define OB_WRP_PAGES8TO9               ((uint32_t)0x00000010) /* Write protection of page 8 to 9 */
#define OB_WRP_PAGES10TO11             ((uint32_t)0x00000020) /* Write protection of page 10 to 11 */
#define OB_WRP_PAGES12TO13             ((uint32_t)0x00000040) /* Write protection of page 12 to 13 */
#define OB_WRP_PAGES14TO15             ((uint32_t)0x00000080) /* Write protection of page 14 to 15 */
#define OB_WRP_PAGES16TO17             ((uint32_t)0x00000100) /* Write protection of page 16 to 17 */
#define OB_WRP_PAGES18TO19             ((uint32_t)0x00000200) /* Write protection of page 18 to 19 */
#define OB_WRP_PAGES20TO21             ((uint32_t)0x00000400) /* Write protection of page 20 to 21 */
#define OB_WRP_PAGES22TO23             ((uint32_t)0x00000800) /* Write protection of page 22 to 23 */
#define OB_WRP_PAGES24TO25             ((uint32_t)0x00001000) /* Write protection of page 24 to 25 */
#define OB_WRP_PAGES26TO27             ((uint32_t)0x00002000) /* Write protection of page 26 to 27 */
#define OB_WRP_PAGES28TO29             ((uint32_t)0x00004000) /* Write protection of page 28 to 29 */
#define OB_WRP_PAGES30TO31             ((uint32_t)0x00008000) /* Write protection of page 30 to 31 */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define OB_WRP_PAGES32TO33             ((uint32_t)0x00010000) /* Write protection of page 32 to 33 */
#define OB_WRP_PAGES34TO35             ((uint32_t)0x00020000) /* Write protection of page 34 to 35 */
#define OB_WRP_PAGES36TO37             ((uint32_t)0x00040000) /* Write protection of page 36 to 37 */
#define OB_WRP_PAGES38TO39             ((uint32_t)0x00080000) /* Write protection of page 38 to 39 */
#define OB_WRP_PAGES40TO41             ((uint32_t)0x00100000) /* Write protection of page 40 to 41 */
#define OB_WRP_PAGES42TO43             ((uint32_t)0x00200000) /* Write protection of page 42 to 43 */
#define OB_WRP_PAGES44TO45             ((uint32_t)0x00400000) /* Write protection of page 44 to 45 */
#define OB_WRP_PAGES46TO47             ((uint32_t)0x00800000) /* Write protection of page 46 to 47 */
#define OB_WRP_PAGES48TO49             ((uint32_t)0x01000000) /* Write protection of page 48 to 49 */
#define OB_WRP_PAGES50TO51             ((uint32_t)0x02000000) /* Write protection of page 50 to 51 */
#define OB_WRP_PAGES52TO53             ((uint32_t)0x04000000) /* Write protection of page 52 to 53 */
#define OB_WRP_PAGES54TO55             ((uint32_t)0x08000000) /* Write protection of page 54 to 55 */
#define OB_WRP_PAGES56TO57             ((uint32_t)0x10000000) /* Write protection of page 56 to 57 */
#define OB_WRP_PAGES58TO59             ((uint32_t)0x20000000) /* Write protection of page 58 to 59 */
#define OB_WRP_PAGES60TO61             ((uint32_t)0x40000000) /* Write protection of page 60 to 61 */
#define OB_WRP_PAGES62TO127            ((uint32_t)0x80000000) /* Write protection of page 62 to 127 */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */ 
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define OB_WRP_PAGES32TO33             ((uint32_t)0x00010000) /* Write protection of page 32 to 33 */
#define OB_WRP_PAGES34TO35             ((uint32_t)0x00020000) /* Write protection of page 34 to 35 */
#define OB_WRP_PAGES36TO37             ((uint32_t)0x00040000) /* Write protection of page 36 to 37 */
#define OB_WRP_PAGES38TO39             ((uint32_t)0x00080000) /* Write protection of page 38 to 39 */
#define OB_WRP_PAGES40TO41             ((uint32_t)0x00100000) /* Write protection of page 40 to 41 */
#define OB_WRP_PAGES42TO43             ((uint32_t)0x00200000) /* Write protection of page 42 to 43 */
#define OB_WRP_PAGES44TO45             ((uint32_t)0x00400000) /* Write protection of page 44 to 45 */
#define OB_WRP_PAGES46TO47             ((uint32_t)0x00800000) /* Write protection of page 46 to 47 */
#define OB_WRP_PAGES48TO49             ((uint32_t)0x01000000) /* Write protection of page 48 to 49 */
#define OB_WRP_PAGES50TO51             ((uint32_t)0x02000000) /* Write protection of page 50 to 51 */
#define OB_WRP_PAGES52TO53             ((uint32_t)0x04000000) /* Write protection of page 52 to 53 */
#define OB_WRP_PAGES54TO55             ((uint32_t)0x08000000) /* Write protection of page 54 to 55 */
#define OB_WRP_PAGES56TO57             ((uint32_t)0x10000000) /* Write protection of page 56 to 57 */
#define OB_WRP_PAGES58TO59             ((uint32_t)0x20000000) /* Write protection of page 58 to 59 */
#define OB_WRP_PAGES60TO61             ((uint32_t)0x40000000) /* Write protection of page 60 to 61 */
#define OB_WRP_PAGES62TO255            ((uint32_t)0x80000000) /* Write protection of page 62 to 255 */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#define OB_WRP_PAGES0TO15MASK          ((uint32_t)0x000000FF)
#define OB_WRP_PAGES16TO31MASK         ((uint32_t)0x0000FF00)

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define OB_WRP_PAGES32TO47MASK         ((uint32_t)0x00FF0000)
#define OB_WRP_PAGES48TO127MASK        ((uint32_t)0xFF000000)
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
#define OB_WRP_PAGES32TO47MASK         ((uint32_t)0x00FF0000)
#define OB_WRP_PAGES48TO255MASK        ((uint32_t)0xFF000000)
#endif /* STM32F302xE || STM32F303xE || STM32F398xx */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define OB_WRP_PAGES32TO47MASK         ((uint32_t)0x00FF0000)
#define OB_WRP_PAGES48TO127MASK        ((uint32_t)0xFF000000)
#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
#define OB_WRP_ALLPAGES                ((uint32_t)0xFFFFFFFF) /*!< Write protection of all pages */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx                   */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
#define OB_WRP_ALLPAGES                ((uint32_t)0x0000FFFF) /*!< Write protection of all pages */
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx    */

#define IS_OB_WRP(PAGE) (((PAGE) != 0x0000000))
/**
  * @}
  */

#if defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup FLASHEx_OB_SDADC12_VDD_MONITOR FLASH Extended Option Bytes SDADC12 VDD MONITOR
  * @{
  */
#define OB_SDACD_VDD_MONITOR_RESET           ((uint8_t)0x00) /*!< SDADC VDD Monitor reset */
#define OB_SDACD_VDD_MONITOR_SET             ((uint8_t)0x80) /*!< SDADC VDD Monitor set */

#define IS_OB_SDACD_VDD_MONITOR(VDD_MONITOR) (((VDD_MONITOR) == OB_SDACD_VDD_MONITOR_SET) || \
                                              ((VDD_MONITOR) == OB_SDACD_VDD_MONITOR_RESET))
/**
  * @}
  */ 
#endif /* STM32F373xC || STM32F378xx */

  
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions FLASH Extended Exported Functions
  * @{
  */
  
/** @addtogroup FLASHEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef  HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef  HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);

/**
  * @}
  */
    
/** @addtogroup FLASHEx_Exported_Functions_Group2 Extended Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef  HAL_FLASHEx_OBErase(void);
HAL_StatusTypeDef  HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void               HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

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

#endif /* __STM32F3xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
