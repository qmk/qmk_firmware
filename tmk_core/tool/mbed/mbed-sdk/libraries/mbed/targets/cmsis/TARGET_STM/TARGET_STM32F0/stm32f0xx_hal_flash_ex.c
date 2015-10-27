/**
  ******************************************************************************
  * @file    stm32f0xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Extended FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *           + Extended Initialization/de-initialization functions
  *           + Extended I/O operation functions
  *           + Extended Peripheral Control functions 
  *           + Extended Peripheral State functions
  *         
  @verbatim
  ==============================================================================
               ##### Flash peripheral extended features  #####
  ==============================================================================
           
                      ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory 
       of all STM32F0xxx devices. It includes
       
        (+) Set/Reset the write protection
        (+) Program the user Option Bytes
        (+) Get the Read protection Level
  
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
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup FLASHEx FLASHEx Extended HAL module driver
  * @brief FLASH Extended HAL module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @addtogroup FLASHEx_Private_Constants FLASHEx Private Constants
  * @{
  */ 
#define HAL_FLASH_TIMEOUT_VALUE   ((uint32_t)50000)/* 50 s */

/**
  * @}
  */
  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @addtogroup FLASHEx_Private_Variables FLASHEx Private Variables
  * @{
  */ 
  
/* Variables used for Erase pages under interruption*/
extern FLASH_ProcessTypeDef pFlash;

/**
  * @}
  */
    
/* Private function prototypes -----------------------------------------------*/
/** @addtogroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */
  
/* Erase operations */
extern void              FLASH_PageErase(uint32_t PageAddress);
static void              FLASH_MassErase(void);

/* Option bytes control */
static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WriteProtectPage);
static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WriteProtectPage);
static HAL_StatusTypeDef FLASH_OB_RDP_LevelConfig(uint8_t ReadProtectLevel);
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t UserConfig);
static HAL_StatusTypeDef FLASH_OB_ProgramData(uint32_t Address, uint8_t Data);
static uint32_t          FLASH_OB_GetWRP(void);
static FlagStatus        FLASH_OB_GetRDP(void);
static uint8_t           FLASH_OB_GetUser(void);

/**
  * @}
  */

/** @defgroup FLASHEx_Extern_Functions FLASHEx Extern Functions
  * @{
  */
/* Private functions ---------------------------------------------------------*/
extern HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);

/**
  * @}
  */

/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported Functions
  * @{
  */

/** @defgroup FLASHEx_Exported_Functions_Group2 Extended I/O operation functions
  * @brief    Extended I/O operation functions
  *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  

@endverbatim
  * @{
  */
/**
  * @brief  Perform a mass erase or erase the specified FLASH memory pages 
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_Lock() should be called after to lock the FLASH interface
  * @param[in]  pEraseInit: pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @param[out]  PageError: pointer to variable  that
  *         contains the configuration information on faulty page in case of error 
  *         (0xFFFFFFFF means that all the pages have been correctly erased)
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint32_t address = 0;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* Check the parameters */
  assert_param(IS_TYPEERASE(pEraseInit->TypeErase));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (pEraseInit->TypeErase == TYPEERASE_MASSERASE)
    {
      /*Mass erase to be done*/
      FLASH_MassErase();

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
      
      /* If the erase operation is completed, disable the MER Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_MER);
    }
    else
    {
      /* Check the parameters */
      assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
      assert_param(IS_FLASH_NB_PAGES(pEraseInit->PageAddress, pEraseInit->NbPages));

      /*Initialization of PageError variable*/
      *PageError = 0xFFFFFFFF;
    
      /* Erase by page by page to be done*/
      for(address = pEraseInit->PageAddress; 
          address < (pEraseInit->PageAddress + (pEraseInit->NbPages)*FLASH_PAGE_SIZE); 
          address += FLASH_PAGE_SIZE)
      {
        FLASH_PageErase(address);

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
   
        /* If the erase operation is completed, disable the PER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

        if (status != HAL_OK) 
        {
          /* In case of error, stop erase procedure and return the faulty address */
          *PageError = address;
          break;
        }
      }
    }
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);

  return status;
}

/**
  * @brief  Perform a mass erase or erase the specified FLASH memory sectors with interrupt enabled
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_Lock() should be called after to lock the FLASH interface
  * @param  pEraseInit: pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process Locked */
  __HAL_LOCK(&pFlash);

  /* If procedure already ongoing, reject the next one */
  if (pFlash.ProcedureOnGoing != FLASH_PROC_NONE)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_TYPEERASE(pEraseInit->TypeErase));

  /* Enable End of FLASH Operation and Error source interrupts */
  __HAL_FLASH_ENABLE_IT((FLASH_IT_EOP | FLASH_IT_ERR));
  
  if (pEraseInit->TypeErase == TYPEERASE_MASSERASE)
  {
    /*Mass erase to be done*/
    pFlash.ProcedureOnGoing = FLASH_PROC_MASSERASE;
    FLASH_MassErase();
  }
  else
  {
    /* Erase by page to be done*/

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
    assert_param(IS_FLASH_NB_PAGES(pEraseInit->PageAddress, pEraseInit->NbPages));

    pFlash.ProcedureOnGoing = FLASH_PROC_PAGEERASE;
    pFlash.DataRemaining = pEraseInit->NbPages;
    pFlash.Address = pEraseInit->PageAddress;

    /*Erase 1st page and wait for IT*/
    FLASH_PageErase(pEraseInit->PageAddress);
  }

  return status;
}

/**
  * @}
  */
    
/** @defgroup FLASHEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the FLASH 
    memory operations.

@endverbatim
  * @{
  */
/**
  * @brief  Erases the FLASH option bytes.
  * @note   This functions erases all option bytes except the Read protection (RDP). 
  *         The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_OB_Unlock() should be called before to unlock the options bytes
  *         The function HAL_FLASH_OB_Launch() should be called after to force the reload of the options bytes 
  *         (system reset will occur)
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_FLASHEx_OBErase(void)
{
  uint8_t rdptmp = OB_RDP_LEVEL_0;
  HAL_StatusTypeDef status = HAL_ERROR;
  FLASH_OBProgramInitTypeDef optionsbytes;

  /* Get the actual read protection Option Byte value */
  HAL_FLASHEx_OBGetConfig(&optionsbytes);
  if(optionsbytes.RDPLevel != RESET)
  {
    rdptmp = OB_RDP_LEVEL_1;  
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE;

    /* If the previous operation is completed, proceed to erase the option bytes */
    SET_BIT(FLASH->CR, FLASH_CR_OPTER);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    
    /* If the erase operation is completed, disable the OPTER Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTER);

    if(status == HAL_OK)
    {
      /* Restore the last read protection Option Byte value */
      optionsbytes.OptionType = OPTIONBYTE_RDP;
      optionsbytes.RDPLevel = rdptmp;
      status = HAL_FLASHEx_OBProgram(&optionsbytes);
    }
  }

  /* Return the erase status */
  return status;
}

/**
  * @brief  Program option bytes
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_OB_Unlock() should be called before to unlock the options bytes
  *         The function HAL_FLASH_OB_Launch() should be called after to force the reload of the options bytes 
  *         (system reset will occur)
  *
  * @param  pOBInit: pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Check the parameters */
  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  /* Write protection configuration */
  if((pOBInit->OptionType & OPTIONBYTE_WRP) == OPTIONBYTE_WRP)
  {
    assert_param(IS_WRPSTATE(pOBInit->WRPState));
    if (pOBInit->WRPState == WRPSTATE_ENABLE)
    {
      /* Enable of Write protection on the selected page */
      status = FLASH_OB_EnableWRP(pOBInit->WRPPage);
    }
    else
    {
      /* Disable of Write protection on the selected page */
      status = FLASH_OB_DisableWRP(pOBInit->WRPPage);
    }
  }

  /* Read protection configuration */
  if((pOBInit->OptionType & OPTIONBYTE_RDP) == OPTIONBYTE_RDP)
  {
    status = FLASH_OB_RDP_LevelConfig(pOBInit->RDPLevel);
  }

  /* USER configuration */
  if((pOBInit->OptionType & OPTIONBYTE_USER) == OPTIONBYTE_USER)
  {
    status = FLASH_OB_UserConfig(pOBInit->USERConfig);
  }

  /* DATA configuration*/
  if((pOBInit->OptionType & OPTIONBYTE_DATA) == OPTIONBYTE_DATA)
  {
    status = FLASH_OB_ProgramData(pOBInit->DATAAddress, pOBInit->DATAData);
  }

  return status;
}

/**
  * @brief  Get the Option byte configuration
  * @param  pOBInit: pointer to an FLASH_OBInitStruct structure that
  *         contains the configuration information for the programming.
  * 
  * @retval None
  */
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER;

  /*Get WRP*/
  pOBInit->WRPPage = FLASH_OB_GetWRP();

  /*Get RDP Level*/
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /*Get USER*/
  pOBInit->USERConfig = FLASH_OB_GetUser();
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
  * @{
  */  

/**
  * @brief  Mass erase of FLASH memory
  * @retval None
  */
static void FLASH_MassErase(void)
{

  /* Clean the error context */
  pFlash.ErrorCode = FLASH_ERROR_NONE;

  /* Proceed to erase all sectors */
  SET_BIT(FLASH->CR, FLASH_CR_MER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
}

/**
  * @brief  Enable the write protection of the desired pages
  * @note   When the memory read protection level is selected (RDP level = 1), 
  *         it is not possible to program or erase the flash page i if CortexM4  
  *         debug features are connected or boot code is executed in RAM, even if nWRPi = 1 
  * 
  * @param  WriteProtectPage: specifies the page(s) to be write protected.
  *         The value of this parameter depend on device used within the same series 
  * @retval HAL status 
  */
static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WriteProtectPage)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F058xx)
  uint16_t WRP0_Data = 0xFFFF;
#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)
  uint16_t WRP1_Data = 0xFFFF;
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx || STM32F051x8 || STM32F042x6 || STM32F048xx || STM32F058xx || STM32F070x6 */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F070xB || STM32F030xC */
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(WriteProtectPage));
    
  WriteProtectPage = (uint32_t)(~WriteProtectPage);
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F058xx)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO31MASK);
#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO63MASK) >> 8);
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx || STM32F051x8 || STM32F042x6 || STM32F048xx || STM32F058xx || STM32F070x6 */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx)|| defined(STM32F030xC)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO15MASK);
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES16TO31MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO47MASK) >> 16);
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO63MASK) >> 24); 
#endif /* STM32F071xB || STM32F072xB || STM32F078xx */
#if defined(STM32F091xC) || defined(STM32F098xx)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO127MASK) >> 24); 
#endif /* STM32F091xC || STM32F098xx */
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F070xB || STM32F030xC */

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE; 

    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 &= WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }

#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC) 
    if((status == HAL_OK) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 &= WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx || STM32F071xB || STM32F070xB ||
          STM32F072xB || STM32F078xx || STM32F091xC || STM32F098xx || STM32F030xC */
          
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)|| defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
    if((status == HAL_OK) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 &= WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 &= WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F070xB || STM32F030xC*/

    /* if the program operation is completed, disable the OPTPG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
  }
  
  return status;
}

/**
  * @brief  Disable the write protection of the desired pages
  * @note   When the memory read protection level is selected (RDP level = 1), 
  *         it is not possible to program or erase the flash page i if CortexM4  
  *         debug features are connected or boot code is executed in RAM, even if nWRPi = 1 
  * 
  * @param  WriteProtectPage: specifies the page(s) to be write unprotected.
  *         The value of this parameter depend on device used within the same series 
  * @retval HAL status 
  */
static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WriteProtectPage)
{
  HAL_StatusTypeDef status = HAL_OK;
#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || defined(STM32F070x6) || \
    defined(STM32F051x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F058xx)
  uint16_t WRP0_Data = 0xFFFF;
#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)
  uint16_t WRP1_Data = 0xFFFF;
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx || STM32F051x8 || STM32F042x6 || STM32F048xx || STM32F058xx || STM32F070x6 */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F070xB || STM32F030xC */
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(WriteProtectPage));

#if defined(STM32F030x6) || defined(STM32F030x8) || defined(STM32F031x6) || defined(STM32F038xx) || STM32F070x6 || \
    defined(STM32F051x8) || defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F058xx)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO31MASK);
#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx)
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO63MASK) >> 8);
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx */
#endif /* STM32F030x6 || STM32F030x8 || STM32F031x6 || STM32F038xx || STM32F051x8 || STM32F042x6 || STM32F048xx || STM32F058xx || STM32F070x6 */

#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO15MASK);
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES16TO31MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO47MASK) >> 16);
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO63MASK) >> 24); 
#endif /* STM32F071xB || STM32F072xB || STM32F078xx */
#if defined(STM32F091xC) || defined(STM32F098xx)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO127MASK) >> 24); 
#endif /* STM32F091xC || STM32F098xx */
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F030xC || STM32F070xB */

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE;
 
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 |= WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }

#if defined(STM32F030x8) || defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
    if((status == HAL_OK) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 |= WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F030x8 || STM32F051x8 || STM32F058xx || STM32F071xB || STM32F070xB ||
          STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F030xC */
          
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F070xB) || \
    defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)
    if((status == HAL_OK) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 |= WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 |= WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F071xB || STM32F072xB || STM32F078xx  || STM32F091xC || STM32F098xx || STM32F070xB || STM32F030xC */

    /* if the program operation is completed, disable the OPTPG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
  } 
  return status;
}

/**
  * @brief  Set the read protection level.
  * @param  ReadProtectLevel: specifies the read protection level.
  *         This parameter can be one of the following values:
  *            @arg OB_RDP_LEVEL_0: No protection
  *            @arg OB_RDP_LEVEL_1: Read protection of the memory
  *            @arg OB_RDP_LEVEL_2: Full chip protection
  *   
  * @note   Warning: When enabling OB_RDP level 2 it's no more possible to go back to level 1 or 0
  *    
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_RDP_LevelConfig(uint8_t ReadProtectLevel)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(ReadProtectLevel));
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  { 
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE;

    /* Enable the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

    WRITE_REG(OB->RDP, ReadProtectLevel);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 

      /* if the program operation is completed, disable the OPTPG Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
    }
  
  return status;
}

/**
  * @brief  Program the FLASH User Option Byte.    
  * @note   Programming of the OB should be performed only after an erase (otherwise PGERR occurs)
  * @param  UserConfig: The FLASH User Option Bytes values: IWDG_SW(Bit0), RST_STOP(Bit1), RST_STDBY(Bit2), BOOT1(Bit4),
  *         VDDA_Analog_Monitoring(Bit5) and SRAM_Parity_Enable(Bit6). 
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t UserConfig)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OB_WDG_SOURCE((UserConfig&OB_WDG_SW)));
  assert_param(IS_OB_STOP_SOURCE((UserConfig&OB_STOP_NO_RST)));
  assert_param(IS_OB_STDBY_SOURCE((UserConfig&OB_STDBY_NO_RST)));
  assert_param(IS_OB_BOOT1((UserConfig&OB_BOOT1_SET)));
  assert_param(IS_OB_VDDA_ANALOG((UserConfig&OB_VDDA_ANALOG_ON)));
  assert_param(IS_OB_SRAM_PARITY((UserConfig&OB_RAM_PARITY_CHECK_RESET)));
#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)|| defined(STM32F070x6)
  assert_param(IS_OB_BOOT_SEL((UserConfig&OB_BOOT_SEL_SET)));
  assert_param(IS_OB_BOOT0((UserConfig&OB_BOOT0_SET)));
#endif /* STM32F042x6 || STM32F048xx || STM32F091xC || STM32F098xx || STM32F030xC || STM32F070x6 */

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {     
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE;
    
    /* Enable the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG); 
           
#if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F091xC) || defined(STM32F098xx) || defined(STM32F030xC)|| defined(STM32F070x6)
    OB->USER = UserConfig;
#else
    OB->USER = (UserConfig | 0x88);
#endif /* STM32F042x6 || STM32F048xx || STM32F091xC || STM32F098xx || STM32F030xC || STM32F070x6 */
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

    /* if the program operation is completed, disable the OPTPG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
  }
  
  return status; 
}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_OB_Unlock() should be called before to unlock the options bytes
  *         The function HAL_FLASH_OB_Launch() should be called after to force the reload of the options bytes 
  *         (system reset will occur)
  *         Programming of the OB should be performed only after an erase (otherwise PGERR occurs)
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be 0x1FFFF804 or 0x1FFFF806. 
  * @param  Data: specifies the data to be programmed.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_ProgramData(uint32_t Address, uint8_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = FLASH_ERROR_NONE;

    /* Enables the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG); 
    *(__IO uint16_t*)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
    
      /* If the program operation is completed, disable the OPTPG Bit */
      CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
    }
  /* Return the Option Byte Data Program Status */
  return status;
}

/**
  * @brief  Return the FLASH Write Protection Option Bytes value.
  * @retval The FLASH Write Protection Option Bytes value
  */
static uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(READ_REG(FLASH->WRPR));
}

/**
  * @brief  Returns the FLASH Read Protection level.
  * @retval FLASH ReadOut Protection Status:
  *           - SET, when OB_RDP_Level_1 or OB_RDP_Level_2 is set
  *           - RESET, when OB_RDP_Level_0 is set
  */
static FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;

  if ((uint8_t)READ_BIT(FLASH->OBR, FLASH_OBR_RDPRT1) != RESET)
  {
    readstatus = SET;
  }

  return readstatus;
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values: IWDG_SW(Bit0), RST_STOP(Bit1), RST_STDBY(Bit2), BOOT1(Bit4),
  *         VDDA_Analog_Monitoring(Bit5) and SRAM_Parity_Enable(Bit6).
  */
static uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(READ_REG(FLASH->OBR) >> 8);
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
