/**
  ******************************************************************************
  * @file    stm32f1xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Extended FLASH HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *           + Extended Initialization/de-initialization functions
  *           + Extended I/O operation functions
  *           + Extended Peripheral Control functions 
  *         
  @verbatim
  ==============================================================================
               ##### Flash peripheral extended features  #####
  ==============================================================================
           
                      ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory 
       of all STM32F1xxx devices. It includes
       
        (++) Set/Reset the write protection
        (++) Program the user Option Bytes
        (++) Get the Read protection Level
  
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */
#ifdef HAL_FLASH_MODULE_ENABLED

/** @addtogroup FLASH
  * @{
  */
/** @addtogroup FLASH_Private_Variables
 * @{
 */
/* Variables used for Erase pages under interruption*/
extern FLASH_ProcessTypeDef pFlash;
/**
  * @}
  */

/**
  * @}
  */
  
/** @defgroup FLASHEx FLASHEx
  * @brief FLASH Extended HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Constants FLASHEx Private Constants
 * @{
 */
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASHEx Private Macros
  * @{
  */
/**
  * @}
  */ 

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup FLASHEx_Private_Functions FLASHEx Private Functions
 * @{
 */
/* Erase operations */
static void              FLASH_MassErase(uint32_t Banks);

/* Option bytes control */
static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WriteProtectPage);
static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WriteProtectPage);
static HAL_StatusTypeDef FLASH_OB_RDP_LevelConfig(uint8_t ReadProtectLevel);
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t UserConfig);
static HAL_StatusTypeDef FLASH_OB_ProgramData(uint32_t Address, uint8_t Data);
static uint32_t          FLASH_OB_GetWRP(void);
static FlagStatus        FLASH_OB_GetRDP(void);
static uint8_t           FLASH_OB_GetUser(void);

#if  defined(STM32F101xG) || defined(STM32F103xG) 
/* State operations */
static HAL_StatusTypeDef FLASH_WaitForLastOperationBank2(uint32_t Timeout);
#endif
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Functions FLASHEx Exported Functions
  * @{
  */
  
/** @defgroup FLASHEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @brief      I/O operation functions
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
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
#if  defined(STM32F101xG) || defined(STM32F103xG) 
    if (pEraseInit->Banks == FLASH_BANK_BOTH)
    {
      /* Mass Erase requested for Bank1 and Bank2 */
      /* Wait for last operation to be completed */
      if ((FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK) && \
          (FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK))
      {
        /*Mass erase to be done*/
        FLASH_MassErase(FLASH_BANK_BOTH);
        
        /* Wait for last operation to be completed */
        if ((FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK) && \
            (FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK))
        {
          status = HAL_OK;
        }
        
        /* If the erase operation is completed, disable the MER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_MER);
        CLEAR_BIT(FLASH->CR2, FLASH_CR2_MER);
      }
    }
    else if (pEraseInit->Banks == FLASH_BANK_2)
    {
      /* Mass Erase requested for Bank2 */
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {
        /*Mass erase to be done*/
        FLASH_MassErase(FLASH_BANK_2);
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE);
        
        /* If the erase operation is completed, disable the MER Bit */
        CLEAR_BIT(FLASH->CR2, FLASH_CR2_MER);
      }
    }
    else 
#endif /* STM32F101xG || STM32F103xG */
    {
      /* Mass Erase requested for Bank1 */
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {
        /*Mass erase to be done*/
        FLASH_MassErase(FLASH_BANK_1);
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        
        /* If the erase operation is completed, disable the MER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_MER);
      }
    }
  }
  else
  {
    /* Page Erase is requested */
    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
    assert_param(IS_FLASH_NB_PAGES(pEraseInit->PageAddress, pEraseInit->NbPages));
    
#if  defined(STM32F101xG) || defined(STM32F103xG) 
    /* Page Erase requested on address located on bank2 */
    if(pEraseInit->PageAddress > FLASH_BANK1_END)
    {   
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {
        /*Initialization of PageError variable*/
        *PageError = 0xFFFFFFFF;
        
        /* Erase by page by page to be done*/
        for(address = pEraseInit->PageAddress;
            address < (pEraseInit->PageAddress + (pEraseInit->NbPages)*FLASH_PAGE_SIZE);
            address += FLASH_PAGE_SIZE)
        {
          FLASH_PageErase(address);
          
          /* Wait for last operation to be completed */
          status = FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE);
          
          /* If the erase operation is completed, disable the PER Bit */
          CLEAR_BIT(FLASH->CR2, FLASH_CR2_PER);
          
          if (status != HAL_OK)
          {
            /* In case of error, stop erase procedure and return the faulty address */
            *PageError = address;
            break;
          }
        }
      }
    }
    else
#endif /* STM32F101xG || STM32F103xG */
    {
      /* Page Erase requested on address located on bank1 */
      /* Wait for last operation to be completed */
      if (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE) == HAL_OK)
      {
        if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
        {
          /*Mass erase to be done*/
          FLASH_MassErase(pEraseInit->Banks);
          
          /* Wait for last operation to be completed */
          status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
          
          /* If the erase operation is completed, disable the MER Bit */
          CLEAR_BIT(FLASH->CR, FLASH_CR_MER);
        }
        else
        {
          /*Initialization of PageError variable*/
          *PageError = 0xFFFFFFFF;
          
          /* Erase by page by page to be done*/
          for(address = pEraseInit->PageAddress;
              address < (pEraseInit->PageAddress + (pEraseInit->NbPages)*FLASH_PAGE_SIZE);
              address += FLASH_PAGE_SIZE)
          {
            FLASH_PageErase(address);
            
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
            
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
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  /* Enable End of FLASH Operation and Error source interrupts */
  __HAL_FLASH_ENABLE_IT((FLASH_IT_EOP | FLASH_IT_ERR));

#if  defined(STM32F101xG) || defined(STM32F103xG) 
  /* Enable End of FLASH Operation and Error source interrupts */
  __HAL_FLASH_ENABLE_IT((FLASH_IT_EOP_BANK2 | FLASH_IT_ERR_BANK2));
#endif
  
  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {
    /*Mass erase to be done*/
    pFlash.ProcedureOnGoing = FLASH_PROC_MASSERASE;
    FLASH_MassErase(pEraseInit->Banks);
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
    
/** @defgroup FLASHEx_Exported_Functions_Group2 Extended Peripheral Control functions
  * @brief      Peripheral Control functions
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

  /* Get the actual read protection Option Byte value */
  if(FLASH_OB_GetRDP() != RESET)
  {
    rdptmp = OB_RDP_LEVEL_1;
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* If the previous operation is completed, proceed to erase the option bytes */
    SET_BIT(FLASH->CR, FLASH_CR_OPTER);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

    /* If the erase operation is completed, disable the OPTER Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTER);

    if(status == HAL_OK)
    {
      /* Restore the last read protection Option Byte value */
      status = FLASH_OB_RDP_LevelConfig(rdptmp);
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
    if (pOBInit->WRPState == OB_WRPSTATE_ENABLE)
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

/** @addtogroup FLASHEx_Private_Functions
 * @{
 */

/**
  * @brief  Full erase of FLASH memory Bank 
  * @param  Banks: Banks to be erased
  *          This parameter can be one of the following values:
  *            @arg FLASH_BANK_1: Bank1 to be erased
  *            @arg FLASH_BANK_2: Bank2 to be erased
  *            @arg FLASH_BANK_BOTH: Bank1 and Bank2 to be erased
  *
  * @retval HAL Status
  */
static void FLASH_MassErase(uint32_t Banks)
{
  /* Check the parameters */
  assert_param(IS_FLASH_BANK(Banks));

  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

#if  defined(STM32F101xG) || defined(STM32F103xG) 
  if(Banks == FLASH_BANK_BOTH)
  {
    /* bank1 & bank2 will be erased*/
    SET_BIT(FLASH->CR, FLASH_CR_MER);
    SET_BIT(FLASH->CR2, FLASH_CR2_MER);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
    SET_BIT(FLASH->CR2, FLASH_CR2_STRT);
  }
  else if(Banks == FLASH_BANK_2)
  {
    /*Only bank2 will be erased*/
    SET_BIT(FLASH->CR2, FLASH_CR2_MER);
    SET_BIT(FLASH->CR2, FLASH_CR2_STRT);
  }
  else
  {
#endif /* STM32F101xG || STM32F103xG */
    /*Only bank1 will be erased*/
    SET_BIT(FLASH->CR, FLASH_CR_MER);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  }
#endif /* STM32F101xG || STM32F103xG */
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
  uint16_t WRP0_Data = 0xFFFF;
#if defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB) || \
    defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
    defined(STM32F101xG) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
  uint16_t WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB || */
       /* STM32F100xE || STM32F101xE || STM32F103xE || */
       /* STM32F101xG || STM32F103xG || */
       /* STM32F105xC || STM32F107xC */
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(WriteProtectPage));
    
  WriteProtectPage = (uint32_t)(~WriteProtectPage);
  
  /* Low Density and Medium Density */
#if  defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6) || \
     defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO31MASK);
#endif /* STM32F101x6 || STM32F102x6 || STM32F103x6 || */
       /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
  
/* Medium Density */
#if  defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO63MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES64TO95MASK) >> 16);
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES96TO127MASK) >> 24); 
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
  
/* High Density, XL Density and  Connectivity line devices*/
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
     defined(STM32F101xG) || defined(STM32F103xG) || \
     defined(STM32F105xC) || defined(STM32F107xC)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO15MASK);
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES16TO31MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO47MASK) >> 16);
#endif /* STM32F100xE || STM32F101xE || STM32F103xE */
       /* STM32F101xG || STM32F103xG */
       /* STM32F105xC || STM32F107xC */

/* High Density */
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE)  
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO255MASK) >> 24); 
#endif /* STM32F100xE || STM32F101xE || STM32F103xE */

/* XL Density */
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO511MASK) >> 24); 
#endif /* STM32F101xG || STM32F103xG */
      
/* Connectivity line devices */
#if defined(STM32F105xC) || defined(STM32F107xC)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO127MASK) >> 24); 
#endif /* STM32F105xC || STM32F107xC */

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  { 
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 &= WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }

#if defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB) || \
    defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
    defined(STM32F101xG) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)    

    if((status == HAL_OK) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 &= WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 &= WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 &= WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB || */
       /* STM32F100xE || STM32F101xE || STM32F103xE || */
       /* STM32F101xG || STM32F103xG || */
       /* STM32F105xC || STM32F107xC */

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
  uint16_t WRP0_Data = 0xFFFF;
#if defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB) || \
    defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
    defined(STM32F101xG) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
  uint16_t WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WRP3_Data = 0xFFFF;
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB || */
       /* STM32F100xE || STM32F101xE || STM32F103xE || */
       /* STM32F101xG || STM32F103xG || */
       /* STM32F105xC || STM32F107xC */
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(WriteProtectPage));

  /* Low Density and Medium Density */
#if  defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6) || \
     defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO31MASK);
#endif /* STM32F101x6 || STM32F102x6 || STM32F103x6 || */
       /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
  
/* Medium Density */
#if  defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB)
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO63MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES64TO95MASK) >> 16);
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES96TO127MASK) >> 24); 
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB */
  
/* High Density, XL Density and  Connectivity line devices*/
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
     defined(STM32F101xG) || defined(STM32F103xG) || \
     defined(STM32F105xC) || defined(STM32F107xC)
  WRP0_Data = (uint16_t)(WriteProtectPage & OB_WRP_PAGES0TO15MASK);
  WRP1_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES16TO31MASK) >> 8);
  WRP2_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES32TO47MASK) >> 16);
#endif /* STM32F100xE || STM32F101xE || STM32F103xE */
       /* STM32F101xG || STM32F103xG */
       /* STM32F105xC || STM32F107xC */

/* High Density */
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE)  
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO255MASK) >> 24); 
#endif /* STM32F100xE || STM32F101xE || STM32F103xE */

/* XL Density */
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO511MASK) >> 24); 
#endif /* STM32F101xG || STM32F103xG */
      
/* Connectivity line devices */
#if defined(STM32F105xC) || defined(STM32F107xC)
  WRP3_Data = (uint16_t)((WriteProtectPage & OB_WRP_PAGES48TO127MASK) >> 24); 
#endif /* STM32F105xC || STM32F107xC */
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  { 
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 |= WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }
#if defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F102xB) || defined(STM32F103xB) || \
    defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) || \
    defined(STM32F101xG) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)  
      
    if((status == HAL_OK) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 |= WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP2_Data != 0xFF))
    {
      OB->WRP2 |= WRP2_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }

    if((status == HAL_OK) && (WRP3_Data != 0xFF))
    {
      OB->WRP3 |= WRP3_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    }
#endif /* STM32F100xB || STM32F101xB || STM32F102xB || STM32F103xB ||*/
       /* STM32F100xE || STM32F101xE || STM32F103xE ||*/
       /* STM32F101xG || STM32F103xG ||*/
       /* STM32F105xC || STM32F107xC */

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
  *    
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_RDP_LevelConfig(uint8_t ReadProtectLevel)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP_LEVEL(ReadProtectLevel));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  { 
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
    
    /* Enable the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG);
    
    WRITE_REG(OB->RDP, ReadProtectLevel);
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE); 
    
    /* if the program operation is completed, disable the OPTPG Bit */
    CLEAR_BIT(FLASH->CR, FLASH_CR_OPTPG);
  }
  
  return status;
}

/**
  * @brief  Program the FLASH User Option Byte.    
  * @note   Programming of the OB should be performed only after an erase (otherwise PGERR occurs)
  * @param  UserConfig: The FLASH User Option Bytes values: FLASH_OBR_IWDG_SW(Bit2), 
  *         FLASH_OBR_nRST_STOP(Bit3),FLASH_OBR_nRST_STDBY(Bit4).
  *         And BFBF2(Bit5) for STM32F101xG and STM32F103xG . 
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t UserConfig)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE((UserConfig&OB_IWDG_SW)));
  assert_param(IS_OB_STOP_SOURCE((UserConfig&OB_STOP_NO_RST)));
  assert_param(IS_OB_STDBY_SOURCE((UserConfig&OB_STDBY_NO_RST)));
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  assert_param(IS_OB_BOOT1((UserConfig&OB_BOOT1_SET)));
#endif /* STM32F101xG || STM32F103xG */

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {     
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Enable the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG); 
 
#if  defined(STM32F101xG) || defined(STM32F103xG)
    OB->USER = (UserConfig | 0xF0);
#else
    OB->USER = (UserConfig | 0xF8);
#endif /* STM32F101xG || STM32F103xG */

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

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
  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Clean the error context */
    pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Enables the Option Bytes Programming operation */
    SET_BIT(FLASH->CR, FLASH_CR_OPTPG); 
    *(__IO uint16_t*)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
    
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
  *           - SET, when OB_RDP_LEVEL_1 is set
  *           - RESET, when OB_RDP_LEVEL_0 is set
  */
static FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;

  if (HAL_IS_BIT_SET(FLASH->OBR, FLASH_OBR_RDPRT))
  {
    readstatus = SET;
  }
  else
  {
    readstatus = RESET;
  }
  return readstatus;
}

/**
  * @brief  Return the FLASH User Option Byte value.
  * @retval The FLASH User Option Bytes values: FLASH_OBR_IWDG_SW(Bit2), 
  *         FLASH_OBR_nRST_STOP(Bit3),FLASH_OBR_nRST_STDBY(Bit4).
  *         And FLASH_OBR_BFB2(Bit5) for STM32F101xG and STM32F103xG . 
  */
static uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)((READ_REG(FLASH->OBR) & FLASH_OBR_USER) >> 2);
}

#if  defined(STM32F101xG) || defined(STM32F103xG) 
/**
  * @brief  Wait for a FLASH BANK2 operation to complete.
  * @param  Timeout: maximum flash operationtimeout
  * @retval HAL_StatusTypeDef HAL Status
  */
static HAL_StatusTypeDef FLASH_WaitForLastOperationBank2(uint32_t Timeout)
{ 
  /* Wait for the FLASH BANK2 operation to complete by polling on BUSY flag to be reset.
     Even if the FLASH BANK2 operation fails, the BUSY flag will be reset and an error
     flag will be set */
     
  uint32_t tickstart = HAL_GetTick();
     
  while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY_BANK2)) 
  { 
    if (Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    }
  }
  
  /* Check FLASH End of Operation flag  */
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP_BANK2))
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP_BANK2);
  }

  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR_BANK2) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR_BANK2))
  {
    /*Save the error code*/
    FLASH_SetErrorCode();
    return HAL_ERROR;
  }

  /* If there is an error flag set */
  return HAL_OK;
  
}
#endif /* STM32F101xG || STM32F103xG */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH
  * @{
  */

#if  defined(STM32F101xG) || defined(STM32F103xG) 
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
  */

/**
  * @brief  Unlock the FLASH control register access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  if (HAL_IS_BIT_SET(FLASH->CR, FLASH_CR_LOCK))
  {
    /* Authorize the FLASH BANK1 Registers access */
    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }


  if (HAL_IS_BIT_SET(FLASH->CR2, FLASH_CR2_LOCK))
  {
    /* Authorize the FLASH BANK2 Registers access */
    WRITE_REG(FLASH->KEYR2, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR2, FLASH_KEY2);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK; 
}

/**
  * @brief  Locks the FLASH control register access
  * @retval HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH BANK1 Registers access */
  SET_BIT(FLASH->CR, FLASH_CR_LOCK);

  /* Set the LOCK Bit to lock the FLASH BANK2 Registers access */
  SET_BIT(FLASH->CR2, FLASH_CR2_LOCK);
  
  return HAL_OK;  
}
/**
  * @}
  */

/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
  */

/**
  * @brief  Program halfword, word or double word at a specified address
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_Lock() should be called after to lock the FLASH interface
  *
  * @note   If an erase and a program operations are requested simultaneously,    
  *         the erase operation is performed before the program one.
  *  
  * @note   FLASH should be previously erased before new programmation (only exception to this 
  *         is when 0x0000 is programmed)
  *  
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                       This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address:      Specifies the address to be programmed.
  * @param  Data:         Specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  uint8_t index = 0;
  uint8_t nbiterations = 0;
  
  /* Process Locked */
  __HAL_LOCK(&pFlash);
  
  /* Check the parameters */
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));
  
  if(Address <= FLASH_BANK1_END)
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
  }
  else
  {
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE);
  }
  
  if(status == HAL_OK)
  {
    if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
    {
      /* Program halfword (16-bit) at a specified address. */
      nbiterations = 1;
    }
    else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {
      /* Program word (32-bit = 2*16-bit) at a specified address. */
      nbiterations = 2;
    }
    else
    {
      /* Program double word (64-bit = 4*16-bit) at a specified address. */
      nbiterations = 4;
    }
    
    for (index = 0; index < nbiterations; index++)
    {
      FLASH_Program_HalfWord((Address + (2*index)), (uint16_t)(Data >> (16*index)));
      
      if(Address <= FLASH_BANK1_END)
      {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        
        /* If the program operation is completed, disable the PG Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
      }
      else
      {
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperationBank2((uint32_t)FLASH_TIMEOUT_VALUE);
        
        /* If the program operation is completed, disable the PG Bit */
        CLEAR_BIT(FLASH->CR2, FLASH_CR2_PG);
      }
      /* In case of error, stop programation procedure */
      if (status != HAL_OK)
      {
        break;
      }
    }
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(&pFlash);
  
  return status;
}

/**
  * @brief  Program halfword, word or double word at a specified address  with interrupt enabled.
  * @note   The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface
  *         The function HAL_FLASH_Lock() should be called after to lock the FLASH interface
  *
  * @note   If an erase and a program operations are requested simultaneously,    
  *         the erase operation is performed before the program one.
  *  
  * @param  TypeProgram: Indicate the way to program at a specified address.
  *                      This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address:     Specifies the address to be programmed.
  * @param  Data:        Specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
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
  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  if(Address <= FLASH_BANK1_END)
  {
    /* Enable End of FLASH Operation and Error source interrupts */
    __HAL_FLASH_ENABLE_IT((FLASH_IT_EOP_BANK1 | FLASH_IT_ERR_BANK1));
  }else
  {
    /* Enable End of FLASH Operation and Error source interrupts */
    __HAL_FLASH_ENABLE_IT((FLASH_IT_EOP_BANK2 | FLASH_IT_ERR_BANK2));
  }

  pFlash.Address = Address;
  pFlash.Data = Data;

  if(TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
  {
    pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAMHALFWORD;
    /*Program halfword (16-bit) at a specified address.*/
    pFlash.DataRemaining = 1;
  }
  else if(TypeProgram == FLASH_TYPEPROGRAM_WORD)
  {
    pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAMWORD;
    /*Program word (32-bit : 2*16-bit) at a specified address.*/
    pFlash.DataRemaining = 2;
  }
  else
  {
    pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAMDOUBLEWORD;
    /*Program double word (64-bit : 4*16-bit) at a specified address.*/
    pFlash.DataRemaining = 4;
  }

  /*Program halfword (16-bit) at a specified address.*/
  FLASH_Program_HalfWord(Address, (uint16_t)Data);

  return status;
}

/**
  * @brief This function handles FLASH interrupt request.
  * @retval None
  */
void HAL_FLASH_IRQHandler(void)
{
  uint32_t addresstmp = 0;
 
  /* Check FLASH operation error flags */
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR_BANK1) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR_BANK1) || \
    (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR_BANK2) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR_BANK2)))
  {
    /*Save the Error code*/
    FLASH_SetErrorCode();
    
    /* FLASH error interrupt user callback */
    HAL_FLASH_OperationErrorCallback(pFlash.Address);
    
    /* Reset address and stop the procedure ongoing*/
    pFlash.Address = 0xFFFFFFFF;
    pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }

  /* Check FLASH End of Operation flag  */
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP_BANK1))
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP_BANK1);
    
    /* Process can continue only if no error detected */
    if(pFlash.ProcedureOnGoing != FLASH_PROC_NONE)
    {
      if(pFlash.ProcedureOnGoing == FLASH_PROC_PAGEERASE)
      {
        /* Nb of pages to erased can be decreased */
        pFlash.DataRemaining--;
        
        /* Indicate user which page address has been erased*/
        HAL_FLASH_EndOfOperationCallback(pFlash.Address);
        
        /* Check if there are still pages to erase*/
        if(pFlash.DataRemaining != 0)
        {
          /* Increment page address to next page */
          pFlash.Address += FLASH_PAGE_SIZE;
          addresstmp = pFlash.Address;

          /* Operation is completed, disable the PER Bit */
          CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

          FLASH_PageErase(addresstmp);
        }
        else
        {
          /*No more pages to Erase*/
          
          /*Reset Address and stop Erase pages procedure*/
          pFlash.Address = 0xFFFFFFFF;
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
      else if(pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE)
      {
        /* Operation is completed, disable the MER Bit */
        CLEAR_BIT(FLASH->CR, FLASH_CR_MER);

        /* Stop Mass Erase procedure if no pending mass erase on other bank */
        if (HAL_IS_BIT_CLR(FLASH->CR2, FLASH_CR2_MER))
        {
          /* MassErase ended. Return the selected bank*/
          /* FLASH EOP interrupt user callback */
          HAL_FLASH_EndOfOperationCallback(0);
        
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
      else
      {
        /* Nb of 16-bit data to program can be decreased */
        pFlash.DataRemaining--;
        
        /* Check if there are still 16-bit data to program */
        if(pFlash.DataRemaining != 0)
        {
          /* Increment address to 16-bit */
          pFlash.Address += 2;
          addresstmp = pFlash.Address;
          
          /* Shift to have next 16-bit data */
          pFlash.Data = (pFlash.Data >> 16);
          
          /* Operation is completed, disable the PG Bit */
          CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

          /*Program halfword (16-bit) at a specified address.*/
          FLASH_Program_HalfWord(addresstmp, (uint16_t)pFlash.Data);
        }
        else
        {
          /*Program ended. Return the selected address*/
          /* FLASH EOP interrupt user callback */
          if (pFlash.ProcedureOnGoing == FLASH_PROC_PROGRAMHALFWORD)
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address);
          }
          else if (pFlash.ProcedureOnGoing == FLASH_PROC_PROGRAMWORD)
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address - 2);
          }
          else 
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address - 6);
          }
          
          /* Reset Address and stop Program procedure*/
          pFlash.Address = 0xFFFFFFFF;
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
    }
  }
  
  /* Check FLASH End of Operation flag  */
  if(__HAL_FLASH_GET_FLAG( FLASH_FLAG_EOP_BANK2))
  {
    /* Clear FLASH End of Operation pending bit */
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP_BANK2);
    
    /* Process can continue only if no error detected */
    if(pFlash.ProcedureOnGoing != FLASH_PROC_NONE)
    {
      if(pFlash.ProcedureOnGoing == FLASH_PROC_PAGEERASE)
      {
        /* Nb of pages to erased can be decreased */
        pFlash.DataRemaining--;
        
        /* Indicate user which page address has been erased*/
        HAL_FLASH_EndOfOperationCallback(pFlash.Address);
        
        /* Check if there are still pages to erase*/
        if(pFlash.DataRemaining != 0)
        {
          /* Increment page address to next page */
          pFlash.Address += FLASH_PAGE_SIZE;
          addresstmp = pFlash.Address;

          /* Operation is completed, disable the PER Bit */
          CLEAR_BIT(FLASH->CR2, FLASH_CR2_PER);

          FLASH_PageErase(addresstmp);
        }
        else
        {
          /*No more pages to Erase*/
          
          /*Reset Address and stop Erase pages procedure*/
          pFlash.Address = 0xFFFFFFFF;
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
      else if(pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE)
      {
        /* Operation is completed, disable the MER Bit */
        CLEAR_BIT(FLASH->CR2, FLASH_CR2_MER);

        if (HAL_IS_BIT_CLR(FLASH->CR, FLASH_CR_MER))
        {
          /* MassErase ended. Return the selected bank*/
          /* FLASH EOP interrupt user callback */
          HAL_FLASH_EndOfOperationCallback(0);
        
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
      else
      {
        /* Nb of 16-bit data to program can be decreased */
        pFlash.DataRemaining--;
        
        /* Check if there are still 16-bit data to program */
        if(pFlash.DataRemaining != 0)
        {
          /* Increment address to 16-bit */
          pFlash.Address += 2;
          addresstmp = pFlash.Address;
          
          /* Shift to have next 16-bit data */
          pFlash.Data = (pFlash.Data >> 16);
          
          /* Operation is completed, disable the PG Bit */
          CLEAR_BIT(FLASH->CR2, FLASH_CR2_PG);

          /*Program halfword (16-bit) at a specified address.*/
          FLASH_Program_HalfWord(addresstmp, (uint16_t)pFlash.Data);
        }
        else
        {
          /*Program ended. Return the selected address*/
          /* FLASH EOP interrupt user callback */
          if (pFlash.ProcedureOnGoing == FLASH_PROC_PROGRAMHALFWORD)
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address);
          }
          else if (pFlash.ProcedureOnGoing == FLASH_PROC_PROGRAMWORD)
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address-2);
          }
          else 
          {
            HAL_FLASH_EndOfOperationCallback(pFlash.Address-6);
          }
          
          /* Reset Address and stop Program procedure*/
          pFlash.Address = 0xFFFFFFFF;
          pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
        }
      }
    }
  }
  
  if(pFlash.ProcedureOnGoing == FLASH_PROC_NONE)
  {
    /* Operation is completed, disable the PG, PER and MER Bits for both bank */
    CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_PER | FLASH_CR_MER));
    CLEAR_BIT(FLASH->CR2, (FLASH_CR2_PG | FLASH_CR2_PER | FLASH_CR2_MER));  
  
    /* Disable End of FLASH Operation and Error source interrupts for both banks */
    __HAL_FLASH_DISABLE_IT(FLASH_IT_EOP_BANK1 | FLASH_IT_ERR_BANK1 | FLASH_IT_EOP_BANK2 | FLASH_IT_ERR_BANK2);
    
    /* Process Unlocked */
    __HAL_UNLOCK(&pFlash);
  }
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F101xG || STM32F103xG */

/** @addtogroup FLASH_Private_Functions
 * @{
 */

/**
  * @brief  Program a half-word (16-bit) at a specified address.
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval None
  */
void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
  
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  if(Address <= FLASH_BANK1_END)
  {
#endif /* STM32F101xG || STM32F103xG */
    /* Proceed to program the new data */
    SET_BIT(FLASH->CR, FLASH_CR_PG);
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  }
  else
  {
    /* Proceed to program the new data */
    SET_BIT(FLASH->CR2, FLASH_CR2_PG);
  }
#endif /* STM32F101xG || STM32F103xG */

  /* Write data in the address */
  *(__IO uint16_t*)Address = Data;
}

/**
  * @brief  Set the specific FLASH error flag.
  * @retval None
  */
void FLASH_SetErrorCode(void)
{ 
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR_BANK2))
#else
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR))
#endif /* STM32F101xG || STM32F103xG */
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_WRP;
  }
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR) || __HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR_BANK2))
#else
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGERR))
#endif /* STM32F101xG || STM32F103xG */
  {
     pFlash.ErrorCode |= HAL_FLASH_ERROR_PROG;
  }

  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR))
  {
     pFlash.ErrorCode |= HAL_FLASH_ERROR_OPTV;
     __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
  }

  /* Clear FLASH error pending bits */
#if  defined(STM32F101xG) || defined(STM32F103xG) 
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_WRPERR | FLASH_FLAG_WRPERR_BANK2 | FLASH_FLAG_PGERR | FLASH_FLAG_PGERR_BANK2);
#else
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);
#endif /* STM32F101xG || STM32F103xG */
}  

/**
  * @brief  Erase the specified FLASH memory page
  * @param  PageAddress: FLASH page to erase
  *         The value of this parameter depend on device used within the same series      
  * 
  * @retval None
  */
void FLASH_PageErase(uint32_t PageAddress)
{
  /* Clean the error context */
  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

#if  defined(STM32F101xG) || defined(STM32F103xG) 
  if(PageAddress > FLASH_BANK1_END)
  { 
    /* Proceed to erase the page */
    SET_BIT(FLASH->CR2, FLASH_CR2_PER);
    WRITE_REG(FLASH->AR2, PageAddress);
    SET_BIT(FLASH->CR2, FLASH_CR2_STRT);
  }
  else
#endif /* STM32F101xG || STM32F103xG */
  {
    /* Proceed to erase the page */
    SET_BIT(FLASH->CR, FLASH_CR_PER);
    WRITE_REG(FLASH->AR, PageAddress);
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_FLASH_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
