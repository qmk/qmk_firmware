/**
  ******************************************************************************
  * @file    stm32l1xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the internal FLASH memory:
  *            + FLASH Interface configuration
  *            + FLASH Memory Erasing
  *            + DATA EEPROM Programming/Erasing
  *            + Option Bytes Programming
  *            + Interrupts management
  *    
  *  @verbatim
  ==============================================================================
               ##### Flash peripheral Extended features  #####
  ==============================================================================
           
  [..] Comparing to other products, the FLASH interface for STM32L1xx
       devices contains the following additional features        
       (+) Erase functions
       (+) DATA_EEPROM memory management
       (+) BOOT option bit configuration       
       (+) PCROP protection for all sectors
   
                      ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory 
       of all STM32L1xx. It includes:       
       (+) Full DATA_EEPROM erase and program management
       (+) Boot activation
       (+) PCROP protection configuration and control for all pages
  
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx
  * @brief FLASH HAL Extension module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void               FLASH_SetErrorCode(void);
static void               FLASH_ErasePage(uint32_t PageAddress);

static HAL_StatusTypeDef  FLASH_OB_WRPConfig(FLASH_OBProgramInitTypeDef *pOBInit, FunctionalState NewState);
static void               FLASH_OB_WRPConfigWRP1OrPCROP1(uint32_t WRP1OrPCROP1, FunctionalState NewState);
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
      defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
      defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
static void               FLASH_OB_WRPConfigWRP2OrPCROP2(uint32_t WRP2OrPCROP2, FunctionalState NewState);
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
static void               FLASH_OB_WRPConfigWRP3(uint32_t WRP3, FunctionalState NewState);
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
static void               FLASH_OB_WRPConfigWRP4(uint32_t WRP4, FunctionalState NewState);
#endif /* STM32L151xE || STM32L152xE || STM32L162xE */
static HAL_StatusTypeDef  FLASH_OB_RDPConfig(uint8_t OB_RDP);
static HAL_StatusTypeDef  FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
static HAL_StatusTypeDef  FLASH_OB_BORConfig(uint8_t OB_BOR);
static uint8_t            FLASH_OB_GetRDP(void);
static uint8_t            FLASH_OB_GetUser(void);
static uint8_t            FLASH_OB_GetBOR(void);
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
static HAL_StatusTypeDef  FLASH_OB_PCROPConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit, FunctionalState NewState);
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
static HAL_StatusTypeDef  FLASH_OB_BootConfig(uint8_t OB_BOOT);
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

static HAL_StatusTypeDef  FLASH_DATAEEPROM_FastProgramByte(uint32_t Address, uint8_t Data);
static HAL_StatusTypeDef  FLASH_DATAEEPROM_FastProgramHalfWord(uint32_t Address, uint16_t Data);
static HAL_StatusTypeDef  FLASH_DATAEEPROM_FastProgramWord(uint32_t Address, uint32_t Data);
static HAL_StatusTypeDef  FLASH_DATAEEPROM_ProgramWord(uint32_t Address, uint32_t Data);
static HAL_StatusTypeDef  FLASH_DATAEEPROM_ProgramHalfWord(uint32_t Address, uint16_t Data);
static HAL_StatusTypeDef  FLASH_DATAEEPROM_ProgramByte(uint32_t Address, uint8_t Data);

/* Exported functions ---------------------------------------------------------*/

/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group1 FLASH Memory Erasing functions
 *  @brief   FLASH Memory Erasing functions
 *
@verbatim   
  ==============================================================================
                ##### FLASH Erasing Programming functions ##### 
  ==============================================================================

    [..] The FLASH Memory Erasing functions, includes the following functions:
    (+) HAL_FLASHEx_Erase: return only when erase has been done
    (+) HAL_FLASHEx_Erase_IT: end of erase is done when HAL_FLASH_EndOfOperationCallback is called with parameter
        0xFFFFFFFF

    [..] Any operation of erase should follow these steps:
    (#) Call the HAL_FLASH_Unlock() function to enable the flash control register and 
        program memory access.
    (#) Call the desired function to erase page.
    (#) Call the HAL_FLASH_Lock() to disable the flash program memory access 
       (recommended to protect the FLASH memory against possible unwanted operation).

@endverbatim
  * @{
  */
  
/**
  * @brief  Erase the specified FLASH memory Pages 
  * @note   To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation)
  * @param[in]  pEraseInit: pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @param[out]  PageError: pointer to variable  that
  *         contains the configuration information on faulty sector in case of error 
  *         (0xFFFFFFFF means that all the sectors have been correctly erased)
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t index = 0;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /*Initialization of PageError variable*/
    *PageError = 0xFFFFFFFF;

    /* Check the parameters */
    assert_param(IS_NBPAGES(pEraseInit->NbPages));
    assert_param(IS_TYPEERASE(pEraseInit->TypeErase));
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress + pEraseInit->NbPages * FLASH_PAGE_SIZE - 1));

    /* Erase by sector by sector to be done*/
    for(index = pEraseInit->PageAddress; index < ((pEraseInit->NbPages * FLASH_PAGE_SIZE)+ pEraseInit->PageAddress); index += FLASH_PAGE_SIZE)
    {
      FLASH_ErasePage(index);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

      /* If the erase operation is completed, disable the ERASE Bit */
      CLEAR_BIT(FLASH->PECR, FLASH_PECR_PROG);
      CLEAR_BIT(FLASH->PECR, FLASH_PECR_ERASE);

      if (status != HAL_OK) 
      {
        /* In case of error, stop erase procedure and return the faulty sector*/
        *PageError = index;
        break;
      }
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&ProcFlash);

  return status;
}

/**
  * @brief  Perform a page erase of the specified FLASH memory pages  with interrupt enabled
  * @note   To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  pEraseInit: pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Enable End of FLASH Operation interrupt */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP);
  
  /* Enable Error source interrupt */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_ERR);
  
  /* Clear pending flags (if any) */  
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_MASK);

  /* Check the parameters */
  assert_param(IS_NBPAGES(pEraseInit->NbPages));
  assert_param(IS_TYPEERASE(pEraseInit->TypeErase));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress + pEraseInit->NbPages * FLASH_PAGE_SIZE - 1));

  ProcFlash.ProcedureOnGoing = FLASH_PROC_PAGEERASE;
  ProcFlash.NbPagesToErase = pEraseInit->NbPages;
  ProcFlash.Page = pEraseInit->PageAddress;

  /*Erase 1st page and wait for IT*/
  FLASH_ErasePage(pEraseInit->PageAddress);

  return status;
}

/**
  * @}
  */


/** @defgroup FLASHEx_Exported_Functions_Group2 Option Bytes Programming functions
 *  @brief   Option Bytes Programming functions 
 *
@verbatim   
  ==============================================================================
                ##### Option Bytes Programming functions ##### 
  ==============================================================================  

    [..] Any operation of erase or program should follow these steps:
    (#) Call the HAL_FLASH_OB_Unlock() function to enable the Flash option control 
        register access.
    (#) Call following function to program the desired option bytes.
        (++) HAL_FLASHEx_OBProgram:
         - To Enable/Disable the desired sector write protection.
         - To set the desired read Protection Level.
         - To configure the user option Bytes: IWDG, STOP and the Standby.
         - To Set the BOR level.
    (#) Once all needed option bytes to be programmed are correctly written, call the
        HAL_FLASH_OB_Launch(void) function to launch the Option Bytes programming process.
    (#) Call the HAL_FLASH_OB_Lock() to disable the Flash option control register access (recommended
        to protect the option Bytes against possible unwanted operations).

    [..] Proprietary code Read Out Protection (PcROP):    
    (#) The PcROP sector is selected by using the same option bytes as the Write
        protection (nWRPi bits). As a result, these 2 options are exclusive each other.
    (#) In order to activate the PcROP (change the function of the nWRPi option bits), 
        the SPRMOD option bit must be activated.
    (#) The active value of nWRPi bits is inverted when PCROP mode is active, this
        means: if SPRMOD = 1 and nWRPi = 1 (default value), then the user sector "i"
        is read/write protected.
    (#) To activate PCROP mode for Flash sector(s), you need to call the following function:
        (++) HAL_FLASHEx_AdvOBProgram in selecting sectors to be read/write protected
        (++) HAL_FLASHEx_OB_SelectPCROP to enable the read/write protection
    (#) PcROP is available only in STM32L151xBA, STM32L152xBA, STM32L151xC, STM32L152xC & STM32L162xC devices.

@endverbatim
  * @{
  */

/**
  * @brief  Program option bytes
  * @param  pOBInit: pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /*Write protection configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_WRP) == OPTIONBYTE_WRP)
  {
    assert_param(IS_WRPSTATE(pOBInit->WRPState));
    if (pOBInit->WRPState == WRPSTATE_ENABLE)
    {
      /* Enable of Write protection on the selected Sector*/
      status = FLASH_OB_WRPConfig(pOBInit, ENABLE);
    }
    else
    {
      /* Disable of Write protection on the selected Sector*/
      status = FLASH_OB_WRPConfig(pOBInit, DISABLE);
    }
    if (status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&ProcFlash);
      return status;
    }
  }
  
  /* Read protection configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_RDP) == OPTIONBYTE_RDP)
  {
    status = FLASH_OB_RDPConfig(pOBInit->RDPLevel);
    if (status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&ProcFlash);
      return status;
    }
  }
  
  /* USER  configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_USER) == OPTIONBYTE_USER)
  {
    status = FLASH_OB_UserConfig(pOBInit->USERConfig & OB_IWDG_SW, 
                                 pOBInit->USERConfig & OB_STOP_NORST,
                                 pOBInit->USERConfig & OB_STDBY_NORST);
    if (status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&ProcFlash);
      return status;
    }
  }

  /* BOR Level  configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_BOR) == OPTIONBYTE_BOR)
  {
    status = FLASH_OB_BORConfig(pOBInit->BORLevel);
  } 
  /* Process Unlocked */
  __HAL_UNLOCK(&ProcFlash);

  return status;
}

/**
  * @brief   Get the Option byte configuration
  * @param  pOBInit: pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_BOR;

  /*Get WRP1*/
  pOBInit->WRPSector0To31 = (uint32_t)(FLASH->WRPR1);

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
  /*Get WRP2*/
  pOBInit->WRPSector32To63 = (uint32_t)(FLASH->WRPR2);

#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
  /*Get WRP3*/
  pOBInit->WRPSector64To95 = (uint32_t)(FLASH->WRPR3);

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
  
#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

  /*Get WRP4*/
  pOBInit->WRPSector96To127 = (uint32_t)(FLASH->WRPR4);

#endif /* STM32L151xE || STM32L152xE || STM32L162xE */

  /*Get RDP Level*/
  pOBInit->RDPLevel   = FLASH_OB_GetRDP();

  /*Get USER*/
  pOBInit->USERConfig = FLASH_OB_GetUser();

  /*Get BOR Level*/
  pOBInit->BORLevel   = FLASH_OB_GetBOR();
  
}

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
/**
  * @brief  Program option bytes
  * @note   This function can be used only for Cat2 & Cat3 devices for PCROP and Cat4 & Cat5 for BFB2.
  * @param  pAdvOBInit: pointer to an FLASH_AdvOBProgramInitTypeDef structure that
  *         contains the configuration information for the programming.
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_AdvOBProgram (FLASH_AdvOBProgramInitTypeDef *pAdvOBInit)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Check the parameters */
  assert_param(IS_OBEX(pAdvOBInit->OptionType));

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
    
  /* Cat2 & Cat3 devices only */
  /*Program PCROP option byte*/
  if ((pAdvOBInit->OptionType & OBEX_PCROP) == OBEX_PCROP)
  {
    /* Check the parameters */
    assert_param(IS_PCROPSTATE(pAdvOBInit->PCROPState));
    if (pAdvOBInit->PCROPState == PCROPSTATE_ENABLE)
    {
      /*Enable of Write protection on the selected Sector*/
      status = FLASH_OB_PCROPConfig(pAdvOBInit, ENABLE);
      if (status != HAL_OK)
      {
        return status;
      }
    }
    else
    {
      /*Disable of Write protection on the selected Sector*/ 
      status = FLASH_OB_PCROPConfig(pAdvOBInit, DISABLE);
      if (status != HAL_OK)
      {
        return status;
      }
    }
  }
  
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
    
  /* Cat4 & Cat5 devices only */
  /*Program BOOT config option byte*/
  if ((pAdvOBInit->OptionType & OBEX_BOOTCONFIG) == OBEX_BOOTCONFIG)
  {
    status = FLASH_OB_BootConfig(pAdvOBInit->BootConfig);
  }
  
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

  return status;
}

/**
  * @brief   Get the OBEX byte configuration
  * @note   This function can be used only for Cat2  & Cat3 devices for PCROP and Cat4 & Cat5 for BFB2.
  * @param  pAdvOBInit: pointer to an FLASH_AdvOBProgramInitTypeDef structure that
  *         contains the configuration information for the programming.
  * 
  * @retval None
  */
void HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit)
{
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
      
  pAdvOBInit->OptionType = OBEX_PCROP;

  /*Get PCROP state */
  pAdvOBInit->PCROPState = (FLASH->OBR & FLASH_OBR_SPRMOD) >> POSITION_VAL(FLASH_OBR_SPRMOD);
  
  /*Get PCROP protected sector from 0 to 31 */
  pAdvOBInit->PCROPSector0To31 = FLASH->WRPR1;
  
  #if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

  /*Get PCROP protected sector from 32 to 63 */
  pAdvOBInit->PCROPSector32To63 = FLASH->WRPR2;

  #endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC */
  
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
      
  pAdvOBInit->OptionType = OBEX_BOOTCONFIG;

  /*Get Boot config OB*/
  pAdvOBInit->BootConfig = (FLASH->OBR & 0x80000000) >> 24;

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
}

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

/**
  * @brief  Select the Protection Mode (SPRMOD).
  * @note   This function can be used only for STM32L151xBA, STM32L152xBA, STM32L151xC, STM32L152xC & STM32L162xC devices
  * @note   Once SPRMOD bit is active, unprotection of a protected sector is not possible 
  * @note   Read a protected sector will set RDERR Flag and write a protected sector will set WRPERR Flag
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint16_t tmp1 = 0;
  uint32_t tmp2 = 0;
  uint8_t optiontmp = 0;
  uint16_t optiontmp2 = 0;
  
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  /* Mask RDP Byte */
  optiontmp =  (uint8_t)(*(__IO uint8_t *)(OB_BASE)); 
  
  /* Update Option Byte */
  optiontmp2 = (uint16_t)(OB_PCROP_SELECTED | optiontmp); 
  
  /* calculate the option byte to write */
  tmp1 = (uint16_t)(~(optiontmp2 ));
  tmp2 = (uint32_t)(((uint32_t)((uint32_t)(tmp1) << 16)) | ((uint32_t)optiontmp2));
  
  if(status == HAL_OK)
  {         
    /* program PCRop */
    OB->RDP = tmp2;
  }
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  /* Return the Read protection operation Status */
  return status;            
}

/**
  * @brief  Deselect the Protection Mode (SPRMOD).
  * @note   This function can be used only for STM32L151xBA, STM32L152xBA, STM32L151xC, STM32L152xC & STM32L162xC devices
  * @note   Once SPRMOD bit is active, unprotection of a protected sector is not possible 
  * @note   Read a protected sector will set RDERR Flag and write a protected sector will set WRPERR Flag
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint16_t tmp1 = 0;
  uint32_t tmp2 = 0;
  uint8_t optiontmp = 0;
  uint16_t optiontmp2 = 0;
  
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  /* Mask RDP Byte */
  optiontmp =  (uint8_t)(*(__IO uint8_t *)(OB_BASE)); 
  
  /* Update Option Byte */
  optiontmp2 = (uint16_t)(OB_PCROP_DESELECTED | optiontmp); 
  
  /* calculate the option byte to write */
  tmp1 = (uint16_t)(~(optiontmp2 ));
  tmp2 = (uint32_t)(((uint32_t)((uint32_t)(tmp1) << 16)) | ((uint32_t)optiontmp2));
  
  if(status == HAL_OK)
  {         
    /* program PCRop */
    OB->RDP = tmp2;
  }
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  /* Return the Read protection operation Status */
  return status;            
}

#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions_Group3 DATA EEPROM Programming functions
 *  @brief   DATA EEPROM Programming functions
 *
@verbatim   
 ===============================================================================
                     ##### DATA EEPROM Programming functions ##### 
 ===============================================================================  
 
    [..] Any operation of erase or program should follow these steps:
    (#) Call the HAL_FLASHEx_DATAEEPROM_Unlock() function to enable the data EEPROM access
        and Flash program erase control register access.
    (#) Call the desired function to erase or program data.
    (#) Call the HAL_FLASHEx_DATAEEPROM_Lock() to disable the data EEPROM access
        and Flash program erase control register access(recommended
        to protect the DATA_EEPROM against possible unwanted operation).

@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the data memory and FLASH_PECR register access.
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Unlock(void)
{
  if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET)
  {  
    /* Unlocking the Data memory and FLASH_PECR register access*/
    FLASH->PEKEYR = FLASH_PEKEY1;
    FLASH->PEKEYR = FLASH_PEKEY2;
  }
  else
  {
    return HAL_ERROR;
  }
  return HAL_OK;  
}

/**
  * @brief  Locks the Data memory and FLASH_PECR register access.
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Lock(void)
{
  /* Set the PELOCK Bit to lock the data memory and FLASH_PECR register access */
  SET_BIT(FLASH->PECR, FLASH_PECR_PELOCK);
  
  return HAL_OK;
}

/**
  * @brief  Erase a word in data memory.
  * @param  Address: specifies the address to be erased.
  * @param  TypeErase:  Indicate the way to erase at a specified address.
  *         This parameter can be a value of @ref FLASH_Type_Program
  * @note   To correctly run this function, the DATA_EEPROM_Unlock() function
  *         must be called before.
  *         Call the DATA_EEPROM_Lock() to the data EEPROM access
  *         and Flash program erase control register access(recommended to protect 
  *         the DATA_EEPROM against possible unwanted operation).
  * @retval FLASH Status: The returned value can be: 
  *   FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Erase(uint32_t TypeErase, uint32_t Address)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_TYPEPROGRAMDATA(TypeErase));
  assert_param(IS_FLASH_DATA_ADDRESS(Address));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    if(TypeErase == TYPEERASEDATA_WORD)
    {
      /* Write 00000000h to valid address in the data memory */
      *(__IO uint32_t *) Address = 0x00000000;
    }

    if(TypeErase == TYPEERASEDATA_HALFWORD)
    {
      /* Write 0000h to valid address in the data memory */
      *(__IO uint16_t *) Address = (uint16_t)0x0000;
    }

    if(TypeErase == TYPEERASEDATA_BYTE)
    {
      /* Write 00h to valid address in the data memory */
      *(__IO uint8_t *) Address = (uint8_t)0x00;
    }
  }
   
  /* Return the erase status */
  return status;
}  

/**
  * @brief  Program word at a specified address
  * @note   To correctly run this function, the HAL_FLASH_EEPROM_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASHEx_DATAEEPROM_Unlock() to he data EEPROM access
  *         and Flash program erase control register access(recommended to protect 
  *         the DATA_EEPROM against possible unwanted operation).
  * @note   The function  HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram() can be called before 
  *         this function to configure the Fixed Time Programming.
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *         This parameter can be a value of @ref FLASHEx_Type_Program_Data
  * @param  Address:  specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */

HAL_StatusTypeDef   HAL_FLASHEx_DATAEEPROM_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Check the parameters */
  assert_param(IS_TYPEPROGRAMDATA(TypeProgram));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    if(TypeProgram == TYPEPROGRAMDATA_FASTBYTE)
    {
      /*Program word (8-bit) at a specified address.*/
      FLASH_DATAEEPROM_FastProgramByte(Address, (uint8_t) Data);
    }
    
    if(TypeProgram == TYPEPROGRAMDATA_FASTHALFWORD)
    {
      /*Program word (16-bit) at a specified address.*/
      FLASH_DATAEEPROM_FastProgramHalfWord(Address, (uint16_t) Data);
    }    
    
    if(TypeProgram == TYPEPROGRAMDATA_FASTWORD)
    {
      /*Program word (32-bit) at a specified address.*/
      FLASH_DATAEEPROM_FastProgramWord(Address, (uint32_t) Data);
    }
    
    if(TypeProgram == TYPEPROGRAMDATA_WORD)
    {
      /*Program word (32-bit) at a specified address.*/
      FLASH_DATAEEPROM_ProgramWord(Address, (uint32_t) Data);
    }
       
    if(TypeProgram == TYPEPROGRAMDATA_HALFWORD)
    {
      /*Program word (16-bit) at a specified address.*/
      FLASH_DATAEEPROM_ProgramHalfWord(Address, (uint16_t) Data);
    }
        
    if(TypeProgram == TYPEPROGRAMDATA_BYTE)
    {
      /*Program word (8-bit) at a specified address.*/
      FLASH_DATAEEPROM_ProgramByte(Address, (uint8_t) Data);
    }
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(&ProcFlash);

  return status;
}

/**
  * @brief  Enable DATA EEPROM fixed Time programming (2*Tprog).
  * @retval None
  */
void HAL_FLASHEx_DATAEEPROM_EnableFixedTimeProgram(void)
{
  SET_BIT(FLASH->PECR, FLASH_PECR_FTDW);
}

/**
  * @brief  Disables DATA EEPROM fixed Time programming (2*Tprog).
  * @retval None
  */
void HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram(void)
{
  CLEAR_BIT(FLASH->PECR, FLASH_PECR_FTDW);
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASHEx_Private_Functions FLASHEx Private functions
  * @{
  */

/*
==============================================================================
              ##### FLASH STATIC functions ##### 
==============================================================================
*/

/*
==============================================================================
              FLASH
==============================================================================
*/

/**
  * @brief  Set the specific FLASH error flag.
  * @retval None
  */
static void FLASH_SetErrorCode(void)
{ 
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR) != RESET)
  {
   ProcFlash.ErrorCode = FLASH_ERROR_WRP;
  }
  
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR) != RESET)
  {
   ProcFlash.ErrorCode |= FLASH_ERROR_PGA;
  }
  
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR) != RESET)
  {
    ProcFlash.ErrorCode |= FLASH_ERROR_SIZE;
  }
  
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR) != RESET)
  {
    ProcFlash.ErrorCode |= FLASH_ERROR_OPTV;
  }
  
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR) != RESET)
  {
    ProcFlash.ErrorCode |= FLASH_ERROR_RD;
  }
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERRUSR) != RESET)
  {
    ProcFlash.ErrorCode |= FLASH_ERROR_OPTVUSR;
  }
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
}

/**
  * @brief  Erases a specified page in program memory.
  * @param  PageAddress: The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of 256 bytes).
  * @retval None
  */
static void FLASH_ErasePage(uint32_t PageAddress)
{
  /* Set the ERASE bit */
  SET_BIT(FLASH->PECR, FLASH_PECR_ERASE);

  /* Set PROG bit */
  SET_BIT(FLASH->PECR, FLASH_PECR_PROG);

  /* Write 00000000h to the first word of the program page to erase */
  *(__IO uint32_t *)PageAddress = 0x00000000;
}
  

/*
==============================================================================
              OPTIONS BYTES
==============================================================================
*/
/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the HAL_FLASH_OB_Unlock() function
  *         must be called before.
  * @param  OB_RDP: specifies the read protection level. 
  *   This parameter can be:
  *     @arg OB_RDP_LEVEL0: No protection
  *     @arg OB_RDP_LEVEL1: Read protection of the memory
  *     @arg OB_RDP_LEVEL2: Chip protection
  * 
  *  !!!Warning!!! When enabling OB_RDP_LEVEL2 it's no more possible to go back to level 1 or 0
  *   
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint8_t OB_RDP)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmp1 = 0, tmp2 = 0, sprmod = 0;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP(OB_RDP));
  
  /* According to errata sheet, DocID022054 Rev 5, par2.1.5
  Before setting Level0 in the RDP register, check that the current level is not equal to Level0.
  If the current level is not equal to Level0, Level0 can be activated.
  If the current level is Level0 then the RDP register must not be written again with Level0. */
  tmp1 = (uint32_t)(OB->RDP & 0x000000FF);
  
  if ((tmp1 == OB_RDP_LEVEL0) && (OB_RDP == OB_RDP_LEVEL0))
  {
    /*current level is Level0 then the RDP register must not be written again with Level0. */
    status = HAL_ERROR;
  }
  else 
  {
    /* Mask SPRMOD bit */
    sprmod = (uint32_t)(OB->RDP & 0x00000100);

    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    
    /* calculate the option byte to write */
    tmp1 = (~((uint32_t)(OB_RDP | sprmod)));
    tmp2 = (uint32_t)(((uint32_t)((uint32_t)(tmp1) << 16)) | ((uint32_t)(OB_RDP | sprmod)));
    
    if(status == HAL_OK)
    {         
     /* program read protection level */
      OB->RDP = tmp2;
    }
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  }
     
  /* Return the Read protection operation Status */
  return status;            
}

/**
  * @brief  Programs the FLASH brownout reset threshold level Option Byte.
  * @param  OB_BOR: Selects the brownout reset threshold level.
  *   This parameter can be one of the following values:
  *     @arg OB_BOR_OFF: BOR is disabled at power down, the reset is asserted when the VDD 
  *                      power supply reaches the PDR(Power Down Reset) threshold (1.5V)
  *     @arg OB_BOR_LEVEL1: BOR Reset threshold levels for 1.7V - 1.8V VDD power supply
  *     @arg OB_BOR_LEVEL2: BOR Reset threshold levels for 1.9V - 2.0V VDD power supply
  *     @arg OB_BOR_LEVEL3: BOR Reset threshold levels for 2.3V - 2.4V VDD power supply
  *     @arg OB_BOR_LEVEL4: BOR Reset threshold levels for 2.55V - 2.65V VDD power supply
  *     @arg OB_BOR_LEVEL5: BOR Reset threshold levels for 2.8V - 2.9V VDD power supply
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_BORConfig(uint8_t OB_BOR)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmp = 0, tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_OB_BOR_LEVEL(OB_BOR));

  /* Get the User Option byte register */
  tmp1 = (FLASH->OBR & (FLASH_OBR_USER)) >> 16;
     
  /* Calculate the option byte to write - [0xFF | nUSER | 0x00 | USER]*/
  tmp = (uint32_t)~((OB_BOR | tmp1)) << 16;
  tmp |= (OB_BOR | tmp1);
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Write the BOR Option Byte */            
    OB->USER = tmp; 
  }
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
        
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @retval The FLASH User Option Bytes.
  */
static uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)((FLASH->OBR & FLASH_OBR_USER) >> POSITION_VAL(FLASH_OBR_USER));
}

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @retval FLASH ReadOut Protection
  */
static uint8_t FLASH_OB_GetRDP(void)
{
  return (uint8_t)(FLASH->OBR & FLASH_OBR_RDPRT);
}

/**
  * @brief  Returns the FLASH BOR level.
  * @retval The FLASH User Option Bytes.
  */
static uint8_t FLASH_OB_GetBOR(void)
{
  /* Return the BOR level */
  return (uint8_t)((FLASH->OBR & (uint32_t)FLASH_OBR_BOR_LEV) >> POSITION_VAL(FLASH_OBR_BOR_LEV));
}

/**
  * @brief  Write protects the desired pages of the first 64KB of the Flash.
  * @param  pOBInit: pointer to an FLASH_OBInitStruct structure that
  *         contains WRP parameters.
  * @param  NewState: new state of the specified FLASH Pages Wtite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval HAL_StatusTypeDef
  */
static HAL_StatusTypeDef FLASH_OB_WRPConfig(FLASH_OBProgramInitTypeDef *pOBInit, FunctionalState NewState)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
 
  if(status == HAL_OK)
  {
    /* WRP for sector between 0 to 31 */
    if (pOBInit->WRPSector0To31 != 0)
    {
      FLASH_OB_WRPConfigWRP1OrPCROP1(pOBInit->WRPSector0To31, NewState);
    }
    
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
      defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
      defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
      
    /* Pages for Cat3, Cat4 & Cat5 devices*/
    /* WRP for sector between 32 to 63 */
    if (pOBInit->WRPSector32To63 != 0)
    {
      FLASH_OB_WRPConfigWRP2OrPCROP2(pOBInit->WRPSector32To63, NewState);
    }
    
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
      
    /* Pages for devices with FLASH >= 256KB*/
    /* WRP for sector between 64 to 95 */
    if (pOBInit->WRPSector64To95 != 0)
    {
      FLASH_OB_WRPConfigWRP3(pOBInit->WRPSector64To95, NewState);
    }
    
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

    /* Pages for Cat5 devices*/
    /* WRP for sector between 96 to 127 */
    if (pOBInit->WRPSector96To127 != 0)
    {
      FLASH_OB_WRPConfigWRP4(pOBInit->WRPSector96To127, NewState);
    }
    
#endif /* STM32L151xE || STM32L152xE || STM32L162xE */

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  }

  /* Return the write protection operation Status */
  return status;      
}

#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
/**
  * @brief  Enables the read/write protection (PCROP) of the desired 
  *         sectors.
  * @note   This function can be used only for Cat2 & Cat3 devices
  * @param  pAdvOBInit: pointer to an FLASH_AdvOBProgramInitTypeDef structure that
  *         contains PCROP parameters.
  * @param  NewState: new state of the specified FLASH Pages read/Write protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_PCROPConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit, FunctionalState NewState)
{
  HAL_StatusTypeDef status = HAL_OK;
  FunctionalState pcropstate = DISABLE;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  /* Invert state to use same function of WRP */
  if (NewState == DISABLE)
  {
    pcropstate = ENABLE;
  }
        
  if(status == HAL_OK)
  {
    /* Pages for Cat2 devices*/
    /* PCROP for sector between 0 to 31 */
    if (pAdvOBInit->PCROPSector0To31 != 0)
    {
      FLASH_OB_WRPConfigWRP1OrPCROP1(pAdvOBInit->PCROPSector0To31, pcropstate);
    }
    
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)

    /* Pages for Cat3 devices*/
    /* WRP for sector between 32 to 63 */
    if (pAdvOBInit->PCROPSector32To63 != 0)
    {
      FLASH_OB_WRPConfigWRP2OrPCROP2(pAdvOBInit->PCROPSector32To63, pcropstate);
    }
    
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC  */
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  }

  /* Return the write protection operation Status */
  return status;      
}
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */

/**
  * @brief  Write protects the desired pages of the first 128KB of the Flash.
  * @param  WRP1OrPCROP1: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg  value between OB_WRP1/PCROP1_PAGES0TO15 and OB_WRP1/PCROP1_PAGES496TO511
  *     @arg  OB_WRP1/PCROP1_ALLPAGES
  * @param  NewState: new state of the specified FLASH Pages Wtite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void FLASH_OB_WRPConfigWRP1OrPCROP1(uint32_t WRP1OrPCROP1, FunctionalState NewState)
{
  uint32_t wrp01data = 0, wrp23data = 0;
  
  uint32_t tmp1 = 0, tmp2 = 0;
  
  if (NewState != DISABLE)
  {
    wrp01data = (uint16_t)(((WRP1OrPCROP1 & WRP_MASK_LOW) | OB->WRP01));
    wrp23data = (uint16_t)((((WRP1OrPCROP1 & WRP_MASK_HIGH)>>16 | OB->WRP23))); 
    tmp1 = (uint32_t)(~(wrp01data) << 16)|(wrp01data);
    OB->WRP01 = tmp1;

    tmp2 = (uint32_t)(~(wrp23data) << 16)|(wrp23data);
    OB->WRP23 = tmp2;      
  }
  else
  {
    wrp01data = (uint16_t)(~WRP1OrPCROP1 & (WRP_MASK_LOW & OB->WRP01));
    wrp23data = (uint16_t)((((~WRP1OrPCROP1 & WRP_MASK_HIGH)>>16 & OB->WRP23))); 

    tmp1 = (uint32_t)((~wrp01data) << 16)|(wrp01data);
    OB->WRP01 = tmp1;
    
    tmp2 = (uint32_t)((~wrp23data) << 16)|(wrp23data);
    OB->WRP23 = tmp2;
  }
}

#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
  * @brief  Enable Write protects the desired pages of the second 128KB of the Flash.
  * @note   This function can be used only for Cat3, Cat4  & Cat5 devices.
  * @param  WRP2OrPCROP2: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg  value between OB_WRP2/PCROP2_PAGES512TO527 and OB_WRP2/PCROP2_PAGES1008TO1023
  *     @arg OB_WRP2/PCROP2_ALLPAGES
  * @param  NewState: new state of the specified FLASH Pages Wtite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void FLASH_OB_WRPConfigWRP2OrPCROP2(uint32_t WRP2OrPCROP2, FunctionalState NewState)
{
  uint32_t wrp45data = 0, wrp67data = 0;
  
  uint32_t tmp1 = 0, tmp2 = 0;
  
  if (NewState != DISABLE)
  {
    wrp45data = (uint16_t)(((WRP2OrPCROP2 & WRP_MASK_LOW) | OB->WRP45));
    wrp67data = (uint16_t)((((WRP2OrPCROP2 & WRP_MASK_HIGH)>>16 | OB->WRP67))); 
    tmp1 = (uint32_t)(~(wrp45data) << 16)|(wrp45data);
    OB->WRP45 = tmp1;
    
    tmp2 = (uint32_t)(~(wrp67data) << 16)|(wrp67data);
    OB->WRP67 = tmp2;
  }
  else
  {
    wrp45data = (uint16_t)(~WRP2OrPCROP2 & (WRP_MASK_LOW & OB->WRP45));
    wrp67data = (uint16_t)((((~WRP2OrPCROP2 & WRP_MASK_HIGH)>>16 & OB->WRP67))); 
    
    tmp1 = (uint32_t)((~wrp45data) << 16)|(wrp45data);
    OB->WRP45 = tmp1;
    
    tmp2 = (uint32_t)((~wrp67data) << 16)|(wrp67data);
    OB->WRP67 = tmp2;
  }
}
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
  * @brief  Enable Write protects the desired pages of the third 128KB of the Flash.
  * @note   This function can be used only for STM32L151xD, STM32L152xD, STM32L162xD  & Cat5 devices.
  * @param  WRP3: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg  value between WRP3_PAGES1024TO1039 and OB_WRP3_PAGES1520TO1535
  *     @arg OB_WRP3_ALLPAGES
  * @param  NewState: new state of the specified FLASH Pages Wtite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void FLASH_OB_WRPConfigWRP3(uint32_t WRP3, FunctionalState NewState)
{
  uint32_t wrp89data = 0, wrp1011data = 0;
  
  uint32_t tmp1 = 0, tmp2 = 0;
  
  if (NewState != DISABLE)
  {
    wrp89data = (uint16_t)(((WRP3 & WRP_MASK_LOW) | OB->WRP89));
    wrp1011data = (uint16_t)((((WRP3 & WRP_MASK_HIGH)>>16 | OB->WRP1011))); 
    tmp1 = (uint32_t)(~(wrp89data) << 16)|(wrp89data);
    OB->WRP89 = tmp1;

    tmp2 = (uint32_t)(~(wrp1011data) << 16)|(wrp1011data);
    OB->WRP1011 = tmp2;      
  }
  else
  {
    wrp89data = (uint16_t)(~WRP3 & (WRP_MASK_LOW & OB->WRP89));
    wrp1011data = (uint16_t)((((~WRP3 & WRP_MASK_HIGH)>>16 & OB->WRP1011))); 

    tmp1 = (uint32_t)((~wrp89data) << 16)|(wrp89data);
    OB->WRP89 = tmp1;

    tmp2 = (uint32_t)((~wrp1011data) << 16)|(wrp1011data);
    OB->WRP1011 = tmp2;
  }
}
#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

#if defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
  * @brief  Enable Write protects the desired pages of the Fourth 128KB of the Flash.
  * @note   This function can be used only for Cat5 devices.
  * @param  WRP4: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg  value between OB_WRP4_PAGES1536TO1551 and OB_WRP4_PAGES2032TO2047
  *     @arg OB_WRP4_ALLPAGES
  * @param  NewState: new state of the specified FLASH Pages Wtite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
static void FLASH_OB_WRPConfigWRP4(uint32_t WRP4, FunctionalState NewState)
{
  uint32_t wrp1213data = 0, wrp1415data = 0;
  
  uint32_t tmp1 = 0, tmp2 = 0;
  
  if (NewState != DISABLE)
  {
    wrp1213data = (uint16_t)(((WRP4 & WRP_MASK_LOW) | OB->WRP1213));
    wrp1415data = (uint16_t)((((WRP4 & WRP_MASK_HIGH)>>16 | OB->WRP1415))); 
    tmp1 = (uint32_t)(~(wrp1213data) << 16)|(wrp1213data);
    OB->WRP1213 = tmp1;

    tmp2 = (uint32_t)(~(wrp1415data) << 16)|(wrp1415data);
    OB->WRP1415 = tmp2;      
  }
  else
  {
    wrp1213data = (uint16_t)(~WRP4 & (WRP_MASK_LOW & OB->WRP1213));
    wrp1415data = (uint16_t)((((~WRP4 & WRP_MASK_HIGH)>>16 & OB->WRP1415))); 

    tmp1 = (uint32_t)((~wrp1213data) << 16)|(wrp1213data);
    OB->WRP1213 = tmp1;

    tmp2 = (uint32_t)((~wrp1415data) << 16)|(wrp1415data);
    OB->WRP1415 = tmp2;
  }
}
#endif /* STM32L151xE || STM32L152xE || STM32L162xE */

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @param  OB_IWDG: Selects the WDG mode.
  *   This parameter can be one of the following values:
  *     @arg OB_IWDG_SW: Software WDG selected
  *     @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *   This parameter can be one of the following values:
  *     @arg OB_STOP_NORST: No reset generated when entering in STOP
  *     @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *   This parameter can be one of the following values:
  *     @arg OB_STDBY_NORST: No reset generated when entering in STANDBY
  *     @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
{
  HAL_StatusTypeDef status = HAL_OK; 
  uint32_t tmp = 0, tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Get the User Option byte register */
  tmp1 = (FLASH->OBR & FLASH_OBR_BOR_LEV) >> 16;
  
  /* Calculate the user option byte to write */ 
  tmp = (uint32_t)(((uint32_t)~((uint32_t)((uint32_t)(OB_IWDG) | (uint32_t)(OB_STOP) | (uint32_t)(OB_STDBY) | tmp1))) << 16);
  tmp |= ((uint32_t)(OB_IWDG) | ((uint32_t)OB_STOP) | (uint32_t)(OB_STDBY) | tmp1);
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Write the User Option Byte */              
    OB->USER = tmp; 
  }
  
  /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
       
  /* Return the Option Byte program Status */
  return status;
}

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
/**
  * @brief  Configures to boot from Bank1 or Bank2.
  * @param  OB_BOOT: select the FLASH Bank to boot from.
  *   This parameter can be one of the following values:
  *     @arg OB_BOOT_BANK2: At startup, if boot pins are set in boot from user Flash
  *        position and this parameter is selected the device will boot from Bank2 or Bank1,
  *        depending on the activation of the bank. The active banks are checked in
  *        the following order: Bank2, followed by Bank1.
  *        The active bank is recognized by the value programmed at the base address
  *        of the respective bank (corresponding to the initial stack pointer value
  *        in the interrupt vector table).
  *     @arg OB_BOOT_BANK1: At startup, if boot pins are set in boot from user Flash
  *        position and this parameter is selected the device will boot from Bank1(Default).
  *        For more information, please refer to AN2606 from www.st.com. 
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_BootConfig(uint8_t OB_BOOT)
{
  HAL_StatusTypeDef status = HAL_OK; 
  uint32_t tmp = 0, tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_OB_BOOT_BANK(OB_BOOT));

  /* Get the User Option byte register  and BOR Level*/
  tmp1 = (FLASH->OBR & (FLASH_OBR_nRST_STDBY | FLASH_OBR_nRST_STOP | FLASH_OBR_IWDG_SW | FLASH_OBR_BOR_LEV)) >> 16;
     
  /* Calculate the option byte to write */
  tmp = (uint32_t)~(OB_BOOT | tmp1) << 16;
  tmp |= (OB_BOOT | tmp1);
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Write the BOOT Option Byte */            
    OB->USER = tmp; 
  }
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
       
  /* Return the Option Byte program Status */
  return status;
}

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

/*
==============================================================================
              DATA
==============================================================================
*/

/**
  * @brief  Write a Byte at a specified address in data memory.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @note   This function assumes that the is data word is already erased.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_FastProgramByte(uint32_t Address, uint8_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
  uint32_t tmp = 0, tmpaddr = 0;
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address)); 

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    
  if(status == HAL_OK)
  {
    /* Clear the FTDW bit */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_FTDW);

#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
    /* Possible only on Cat1 devices */
    if(Data != (uint8_t)0x00) 
    {
      /* If the previous operation is completed, proceed to write the new Data */
      *(__IO uint8_t *)Address = Data;
            
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    }
    else
    {
      tmpaddr = Address & 0xFFFFFFFC;
      tmp = * (__IO uint32_t *) tmpaddr;
      tmpaddr = 0xFF << ((uint32_t) (0x8 * (Address & 0x3)));
      tmp &= ~tmpaddr;
      status = HAL_FLASHEx_DATAEEPROM_Erase(TYPEERASEDATA_WORD, Address & 0xFFFFFFFC);
      status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTWORD, (Address & 0xFFFFFFFC), tmp);
    }       
#else /*!Cat1*/ 
    /* If the previous operation is completed, proceed to write the new Data */
    *(__IO uint8_t *)Address = Data;
            
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  }
  /* Return the Write Status */
  return status;
}

/**
  * @brief  Writes a half word at a specified address in data memory.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @note   This function assumes that the is data word is already erased.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_FastProgramHalfWord(uint32_t Address, uint16_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
  uint32_t tmp = 0, tmpaddr = 0;
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    
  if(status == HAL_OK)
  {
    /* Clear the FTDW bit */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_FTDW);

#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
    /* Possible only on Cat1 devices */
    if(Data != (uint16_t)0x0000) 
    {
      /* If the previous operation is completed, proceed to write the new data */
      *(__IO uint16_t *)Address = Data;
  
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    }
    else
    {
      if((Address & 0x3) != 0x3)
      {
        tmpaddr = Address & 0xFFFFFFFC;
        tmp = * (__IO uint32_t *) tmpaddr;
        tmpaddr = 0xFFFF << ((uint32_t) (0x8 * (Address & 0x3)));
        tmp &= ~tmpaddr;        
        status = HAL_FLASHEx_DATAEEPROM_Erase(TYPEERASEDATA_WORD, Address & 0xFFFFFFFC);
        status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTWORD, (Address & 0xFFFFFFFC), tmp);
      }
      else
      {
        HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTBYTE, Address, 0x00);
        HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTBYTE, Address + 1, 0x00);
      }
    }
#else /* !Cat1 */
    /* If the previous operation is completed, proceed to write the new data */
    *(__IO uint16_t *)Address = Data;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  }
  /* Return the Write Status */
  return status;
}

/**
  * @brief  Programs a word at a specified address in data memory.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @note   This function assumes that the is data word is already erased.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_FastProgramWord(uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Clear the FTDW bit */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_FTDW);
  
    /* If the previous operation is completed, proceed to program the new data */    
    *(__IO uint32_t *)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);       
  }
  /* Return the Write Status */
  return status;
}

/**
  * @brief  Write a Byte at a specified address in data memory without erase.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_ProgramByte(uint32_t Address, uint8_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
  uint32_t tmp = 0, tmpaddr = 0;
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address)); 

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
    if(Data != (uint8_t) 0x00)
    {  
      *(__IO uint8_t *)Address = Data;
    
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);

    }
    else
    {
      tmpaddr = Address & 0xFFFFFFFC;
      tmp = * (__IO uint32_t *) tmpaddr;
      tmpaddr = 0xFF << ((uint32_t) (0x8 * (Address & 0x3)));
      tmp &= ~tmpaddr;        
      status = HAL_FLASHEx_DATAEEPROM_Erase(TYPEERASEDATA_WORD, Address & 0xFFFFFFFC);
      status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTWORD, (Address & 0xFFFFFFFC), tmp);
    }
#else /* Not Cat1*/
    *(__IO uint8_t *)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  }
  /* Return the Write Status */
  return status;
}

/**
  * @brief  Writes a half word at a specified address in data memory without erase.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
  uint32_t tmp = 0, tmpaddr = 0;
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
#if defined(STM32L100xB) || defined (STM32L151xB) || defined (STM32L152xB)
    if(Data != (uint16_t)0x0000)
    {
      *(__IO uint16_t *)Address = Data;
   
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
    }
    else
    {
      if((Address & 0x3) != 0x3)
      {
        tmpaddr = Address & 0xFFFFFFFC;
        tmp = * (__IO uint32_t *) tmpaddr;
        tmpaddr = 0xFFFF << ((uint32_t) (0x8 * (Address & 0x3)));
        tmp &= ~tmpaddr;          
        status = HAL_FLASHEx_DATAEEPROM_Erase(TYPEERASEDATA_WORD, Address & 0xFFFFFFFC);
        status = HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTWORD, (Address & 0xFFFFFFFC), tmp);
      }
      else
      {
        HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTBYTE, Address, 0x00);
        HAL_FLASHEx_DATAEEPROM_Program(TYPEPROGRAMDATA_FASTBYTE, Address + 1, 0x00);
      }
    }
#else /* Not Cat1*/
    *(__IO uint16_t *)Address = Data;
   
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
#endif /* STM32L100xB || STM32L151xB || STM32L152xB  */
  }
  /* Return the Write Status */
  return status;
}

/**
  * @brief  Programs a word at a specified address in data memory without erase.
  * @param  Address: specifies the address to be written.
  * @param  Data: specifies the data to be written.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_DATAEEPROM_ProgramWord(uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    *(__IO uint32_t *)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(HAL_FLASH_TIMEOUT_VALUE);
  }
  /* Return the Write Status */
  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH
  * @{
  */ 

/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_Exported_Functions_Group1
 *  @brief   Interrupts  functions
 *
@verbatim   
  ==============================================================================
              ##### Interrupts  functions #####
  ==============================================================================    

@endverbatim
  * @{
  */

/**
  * @brief This function handles FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t temp;
  
  /* If the program operation is completed, disable the PROG Bit */
  CLEAR_BIT(FLASH->PECR, FLASH_PECR_PROG);

  /* If the erase operation is completed, disable the ERASE Bit */
  CLEAR_BIT(FLASH->PECR, FLASH_PECR_ERASE);

  /* Check FLASH End of Operation flag  */
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP) != RESET)
  {
    if(ProcFlash.ProcedureOnGoing == FLASH_PROC_PAGEERASE)
    {
      /*Nb of sector to erased can be decreased*/
      ProcFlash.NbPagesToErase--;

      /* Check if there are still sectors to erase*/
      if(ProcFlash.NbPagesToErase != 0)
      {
        temp = ProcFlash.Page;
        /*Indicate user which sector has been erased*/
        HAL_FLASH_EndOfOperationCallback(temp);

        /* Clear pending flags (if any) */  
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_MASK);  

        /*Increment sector number*/
        temp = ProcFlash.Page + FLASH_PAGE_SIZE;
        ProcFlash.Page = ProcFlash.Page + FLASH_PAGE_SIZE;
        FLASH_ErasePage(temp);
      }
      else
      {
        /*No more sectors to Erase, user callback can be called.*/
        /*Reset Sector and stop Erase sectors procedure*/
        ProcFlash.Page = temp = 0xFFFFFFFF;
        ProcFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(temp);
        /* Clear FLASH End of Operation pending bit */
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
      }
    }
    else 
    {
      if(ProcFlash.ProcedureOnGoing  == FLASH_PROC_PROGRAM)
      {
        /*Program ended. Return the selected address*/
        /* FLASH EOP interrupt user callback */
        HAL_FLASH_EndOfOperationCallback(ProcFlash.Address);
      }
      ProcFlash.ProcedureOnGoing = FLASH_PROC_NONE;
      /* Clear FLASH End of Operation pending bit */
      __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
    }

  }
  
  /* Check FLASH operation error flags */
  if( (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR)     != RESET) || 
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR)     != RESET) || 
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR)     != RESET) || 
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR)      != RESET) || 
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERRUSR) != RESET) || 
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR)    != RESET) )
  {
    if(ProcFlash.ProcedureOnGoing == FLASH_PROC_PAGEERASE)
    {
      /*return the faulty sector*/
      temp = ProcFlash.Page;
      ProcFlash.Page = 0xFFFFFFFF;
    }
    else
    {
      /*retrun the faulty address*/
      temp = ProcFlash.Address;
    }
    
    /*Save the Error code*/
    FLASH_SetErrorCode();

    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(temp);
    
    /* Clear FLASH error pending bits */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_MASK);

    /*Stop the procedure ongoing*/
    ProcFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }
  
  if(ProcFlash.ProcedureOnGoing == FLASH_PROC_NONE)
  {
    /* Disable End of FLASH Operation interrupt */
    __HAL_FLASH_DISABLE_IT(FLASH_IT_EOP);

    /* Disable Error source interrupt */
    __HAL_FLASH_DISABLE_IT(FLASH_IT_ERR);

    /* Process Unlocked */
    __HAL_UNLOCK(&ProcFlash);
  }
    
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASH_Internal_Functions FLASH Internal function
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout: maximum flash operationtimeout
  * @retval HAL status
  */
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{ 
  /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH operation fails, the BUSY flag will be reset and an error
     flag will be set */
    
  uint32_t tickstart = HAL_GetTick();   
     
  while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET) 
  { 
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    } 
  }
  
  if( (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR)     != RESET) || 
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR)     != RESET) || 
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR)     != RESET) || 
#if defined (STM32L151xBA) || defined (STM32L152xBA) || \
    defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC)
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR)      != RESET) || 
#endif /* STM32L151xBA || STM32L152xBA || STM32L151xC || STM32L152xC || STM32L162xC */
#if defined(STM32L100xC) || defined (STM32L151xC) || defined (STM32L152xC) || defined (STM32L162xC) || \
    defined(STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERRUSR) != RESET) || 
#endif /* STM32L100xC || STM32L151xC || STM32L152xC || STM32L162xC || STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */
      (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR)    != RESET) )
  {
    /*Save the error code*/
    FLASH_SetErrorCode();
    return HAL_ERROR;
  }

  /* There is no error flag set */
  return HAL_OK;
}


/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

