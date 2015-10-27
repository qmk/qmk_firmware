/**
  ******************************************************************************
  * @file    stm32l0xx_hal_flash_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
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
           
  [..] Comparing to other products, the FLASH interface for STM32L0xx
       devices contains the following additional features        
       (+) Erase functions
       (+) DATA_EEPROM memory management
       (+) BOOT option bit configuration       
       (+) PCROP protection for all sectors
   
                      ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the FLASH memory 
       of all STM32L0xx. It includes:       
       (+) Full DATA_EEPROM erase and program management
       (+) Boot activation
       (+) PCROP protection configuration and control for all sectors
  
  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @brief FLASH HAL Extension module driver
  * @{
  */

#ifdef HAL_FLASH_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef FLASH_OB_RDPConfig(uint8_t OB_RDP);
static HAL_StatusTypeDef FLASH_OB_BORConfig(uint8_t OB_BOR);
static uint8_t           FLASH_OB_GetUser(void);
static uint8_t           FLASH_OB_GetRDP(void);
static uint8_t           FLASH_OB_GetBOR(void);
static uint8_t           FLASH_OB_GetBOOTBit1(void);
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
static HAL_StatusTypeDef FLASH_OB_ProtectedSectorsConfig(uint32_t Sector, uint32_t Sector2, uint32_t NewState);
#else
static HAL_StatusTypeDef FLASH_OB_ProtectedSectorsConfig(uint32_t Sector, uint32_t NewState);
#endif
static HAL_StatusTypeDef  FLASH_OB_PCROPSelectionConfig(uint32_t WPRMOD);
static uint32_t          FLASH_OB_GetWRP(void);
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
static uint32_t          FLASH_OB_GetWRP2(void);
#endif
static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
static HAL_StatusTypeDef FLASH_OB_BOOTBit1Config(uint8_t OB_BOOT_Bit1);
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
static HAL_StatusTypeDef FLASH_OB_BFB2Config(uint8_t OB_BFB2);
#endif
    
/* Exported functions ---------------------------------------------------------*/

/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/** @addtogroup FLASHEx_Exported_Functions_Group1
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
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /*Initialization of PageError variable*/
    *PageError = 0xFFFFFFFF;
      
    /* Check the parameters */
    assert_param(IS_NBPAGES(pEraseInit->NbPages));
    assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
    assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress + pEraseInit->NbPages * FLASH_PAGE_SIZE - 1));

    /* Erase by sector by sector to be done*/
    for(index = pEraseInit->PageAddress; index < ((pEraseInit->NbPages * FLASH_PAGE_SIZE)+ pEraseInit->PageAddress); index += FLASH_PAGE_SIZE)
    {        
      FLASH_ErasePage(index);

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
        
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
  *         (recommended to protect the FLASH memory against possible unwanted operation).
            End of erase is done when HAL_FLASH_EndOfOperationCallback is called with parameter
            0xFFFFFFFF
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

  /* Check the parameters */
  assert_param(IS_NBPAGES(pEraseInit->NbPages));
  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(pEraseInit->PageAddress + pEraseInit->NbPages * FLASH_PAGE_SIZE - 1));

  /* Clean the error context */
  ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
  ProcFlash.ProcedureOnGoing = FLASH_PROC_PAGEERASE;
  ProcFlash.NbPagesToErase = pEraseInit->NbPages;
  ProcFlash.Page = pEraseInit->PageAddress;

  /* Erase 1st page and wait for IT */
  FLASH_ErasePage(pEraseInit->PageAddress);
  return status;
}

/**
  * @}
  */


/** @addtogroup FLASHEx_Exported_Functions_Group2
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
        the WPRMOD option bit must be activated.
    (#) The active value of nWRPi bits is inverted when PCROP mode is active, this
        means: if WPRMOD = 1 and nWRPi = 1 (default value), then the user sector "i"
        is read/write protected.
    (#) To activate PCROP mode for Flash sector(s), you need to call the following function:
        (++) HAL_FLASHEx_AdvOBProgram in selecting sectors to be read/write protected
        (++) HAL_FLASHEx_OB_SelectPCROP to enable the read/write protection
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

  /* Write protection configuration */
  if((pOBInit->OptionType & OPTIONBYTE_WRP) == OPTIONBYTE_WRP)
  {
    assert_param(IS_WRPSTATE(pOBInit->WRPState));
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
    status = FLASH_OB_ProtectedSectorsConfig(pOBInit->WRPSector, pOBInit->WRPSector2, pOBInit->WRPState);
#else
    status = FLASH_OB_ProtectedSectorsConfig(pOBInit->WRPSector, pOBInit->WRPState);
#endif    
    if (status != HAL_OK)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(&ProcFlash);
      return status;
    }
  }

  /* Read protection configuration */
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

  /* USER  configuration */
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

  /* BOR Level  configuration */
  if((pOBInit->OptionType & OPTIONBYTE_BOR) == OPTIONBYTE_BOR)
  {
    status = FLASH_OB_BORConfig(pOBInit->BORLevel);
  } 

  /* Program BOOT Bit1 config option byte */
  if ((pOBInit->OptionType & OPTIONBYTE_BOOT_BIT1) == OPTIONBYTE_BOOT_BIT1)
  {
    status = FLASH_OB_BOOTBit1Config(pOBInit->BOOTBit1Config);
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

  /* Get WRP sector */
  pOBInit->WRPSector = FLASH_OB_GetWRP();

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
  pOBInit->WRPSector2 = FLASH_OB_GetWRP2();
#endif

  /* Get RDP Level */
  pOBInit->RDPLevel = FLASH_OB_GetRDP();

  /* Get USER */
  pOBInit->USERConfig = FLASH_OB_GetUser();

  /* Get BOR Level */
  pOBInit->BORLevel = FLASH_OB_GetBOR();
  
  /* Get BOOT bit 1 config OB */
  pOBInit->BOOTBit1Config = FLASH_OB_GetBOOTBit1();

}

/**
  * @brief  Program option bytes
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

  /* Program PCROP option byte */
  if ((pAdvOBInit->OptionType & OPTIONBYTE_PCROP) == OPTIONBYTE_PCROP)
  {
    /* Check the parameters */
    assert_param(IS_PCROPSTATE(pAdvOBInit->PCROPState));
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
    status = FLASH_OB_ProtectedSectorsConfig(pAdvOBInit->PCROPSector, pAdvOBInit->PCROPSector2, pAdvOBInit->PCROPState);
#else
    status = FLASH_OB_ProtectedSectorsConfig(pAdvOBInit->PCROPSector, pAdvOBInit->PCROPState);
#endif
  }
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
  if ((pAdvOBInit->OptionType & OPTIONBYTE_BOOTCONFIG) == OPTIONBYTE_BOOTCONFIG)
  {
    status = FLASH_OB_BFB2Config(pAdvOBInit->BootConfig);
  }
#endif

  return status;
}

/**
  * @brief   Get the OBEX byte configuration
  * @param  pAdvOBInit: pointer to an FLASH_AdvOBProgramInitTypeDef structure that
  *         contains the configuration information for the programming.
  * 
  * @retval None
  */
void HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit)
{
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
  pAdvOBInit->OptionType = OPTIONBYTE_PCROP| OPTIONBYTE_BOOTCONFIG;
#else
  pAdvOBInit->OptionType = OPTIONBYTE_PCROP;
#endif
  /* Get PCROP state */
  pAdvOBInit->PCROPState = (FLASH->OPTR & FLASH_OPTR_WPRMOD) >> 8;
  /* Get PCROP protected sector */
  pAdvOBInit->PCROPSector = FLASH->WRPR;

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
  /* Get PCROP protected sector */
  pAdvOBInit->PCROPSector2 = FLASH->WRPR2;

  /* Get boot bank config */
  pAdvOBInit->BootConfig = (FLASH->OPTR & FLASH_OPTR_BFB2) >> 23;
#endif
}

/**
  * @brief  Select the Protection Mode (WPRMOD).
  * @note   Once WPRMOD bit is active, unprotection of a protected sector is not possible 
  * @note   Read a protected sector will set RDERR Flag and write a protected sector will set WRPERR Flag
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void)
{
  return (FLASH_OB_PCROPSelectionConfig(1));
}

/**
  * @brief  Deselect the Protection Mode (WPRMOD).
  * @note   Once WPRMOD bit is active, unprotection of a protected sector is not possible 
  * @note   Read a protected sector will set RDERR Flag and write a protected sector will set WRPERR Flag
  * @param  None
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void)
{
  return (FLASH_OB_PCROPSelectionConfig(0));
}

/**
  * @}
  */
  
/** @addtogroup FLASHEx_Exported_Functions_Group3
 *  @brief   DATA EEPROM Programming functions
 *
@verbatim   
 ===============================================================================
                     ##### DATA EEPROM Programming functions ##### 
 ===============================================================================  
 
    [..] The FLASH_DATAEEPROM Programming_Functions, includes the following functions:
        (+) HAL_FLASHEx_DATAEEPROM_Unlock(void);
        (+) HAL_FLASHEx_DATAEEPROM_Lock(void);
        (+) HAL_FLASHEx_DATAEEPROM_Erase(uint32_t Address)
        (+) HAL_FLASHEx_DATAEEPROM_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
   
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
  * @param  None
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Unlock(void)
{
  if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET)
  {  
    /* Unlocking the Data memory and FLASH_PECR register access */
    FLASH->PEKEYR = FLASH_PEKEY1;
    FLASH->PEKEYR = FLASH_PEKEY2;
    return HAL_OK;  
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Locks the Data memory and FLASH_PECR register access.
  * @param  None
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
  * @note   To correctly run this function, the HAL_FLASHEx_DATAEEPROM_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASHEx_DATAEEPROM_Lock() to the data EEPROM access
  *         and Flash program erase control register access(recommended to protect 
  *         the DATA_EEPROM against possible unwanted operation).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Erase(uint32_t Address)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the parameters */
  assert_param(IS_FLASH_DATA_ADDRESS(Address));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Write "00000000h" to valid address in the data memory" */
      *(__IO uint32_t *) Address = 0x00000000;
    }
  return status;
}  

/**
  * @brief  Program word at a specified address
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                           This parameter can be a value of @ref FLASHEx_Type_Program_Data
  * @param  Address:  specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */

HAL_StatusTypeDef HAL_FLASHEx_DATAEEPROM_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Check the parameters */
  assert_param(IS_TYPEPROGRAMDATA(TypeProgram));
  assert_param(IS_FLASH_DATA_ADDRESS(Address));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    if(TypeProgram == FLASH_TYPEPROGRAMDATA_WORD)
    {
      /* Program word (32-bit) at a specified address */
      *(__IO uint32_t *)Address = Data;
    }
    else if(TypeProgram == FLASH_TYPEPROGRAMDATA_HALFWORD)
    {
      /* Program word (16-bit) at a specified address */
      *(__IO uint16_t *)Address = (uint16_t) Data;
    }
    else if(TypeProgram == FLASH_TYPEPROGRAMDATA_BYTE)
    {
      /*Program word (8-bit) at a specified address */
      *(__IO uint8_t *)Address = (uint8_t) Data;
    }
    else
    {
      status = HAL_ERROR;
    }

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
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
  SET_BIT(FLASH->PECR, FLASH_PECR_FIX);
}

/**
  * @brief  Disables DATA EEPROM fixed Time programming (2*Tprog).
  * @retval None
  */
void HAL_FLASHEx_DATAEEPROM_DisableFixedTimeProgram(void)
{
  CLEAR_BIT(FLASH->PECR, FLASH_PECR_FIX);
}

/**
  * @}
  */

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @param  None
  * @retval The FLASH User Option Bytes.
  */
static uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)((FLASH->OPTR & FLASH_OPTR_USER) >> 16);
}

/**
  * @brief  Returns the FLASH Read out Protection Level.
  * @param  None
  * @retval FLASH RDP level.
  */
static uint8_t FLASH_OB_GetRDP(void)
{
  return (uint8_t)(FLASH->OPTR & FLASH_OPTR_RDPROT);
}

/**
  * @brief  Returns the FLASH BOR level.
  * @param  None
  * @retval The BOR level Option Bytes.
  */
static uint8_t FLASH_OB_GetBOR(void)
{
  /* Return the BOR level */
  return (uint8_t)((FLASH->OPTR & (uint32_t)FLASH_OPTR_BOR_LEV) >> 16);
}

/**
  * @brief  Returns the FLASH BOOT bit1 value.
  * @param  None
  * @retval The BOOT bit 1 value Option Bytes.
  */
static uint8_t FLASH_OB_GetBOOTBit1(void)
{
  /* Return the BOR level */
  return (FLASH->OPTR & FLASH_OPTR_BOOT1) >> 31;

}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value.
  */
static uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value.
  */
static uint32_t FLASH_OB_GetWRP2(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR2);
}
#endif /* STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @param  OB_IWDG: Selects the WDG mode.
  *   This parameter can be one of the following values:
  *     @arg OB_IWDG_SW: Software WDG selected
  *     @arg OB_IWDG_HW: Hardware WDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *   This parameter can be one of the following values:
  *     @arg OB_STOP_NoRST: No reset generated when entering in STOP
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
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = (uint32_t) (OB_IWDG | OB_STOP | OB_STDBY);

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Clean the error context */
  ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  /* Get the User Option byte register */
  tmp1 = OB->USER & ((~FLASH_OPTR_USER) >> 16);

  /* Calculate the user option byte to write */ 
  tmp = (~(OB_Bits | tmp1)) << 16;
  tmp |= OB_Bits | tmp1;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
    /* Program OB */
    OB->USER = tmp; 
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }
  return status;
}

/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function
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
  HAL_StatusTypeDef status;
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = (uint32_t) OB_RDP;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP(OB_RDP));
  
  /* Calculate the option byte to write */
  tmp = (OB->RDP & ((~FLASH_OPTR_RDPROT) & 0x0000FFFF)) | OB_Bits; 
  tmp1 = (~tmp << 16) | tmp;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {         
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
    /* Program OB */
    OB->RDP = tmp1;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }
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
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = (uint32_t) OB_BOR;

  /* Check the parameters */
  assert_param(IS_OB_BOR_LEVEL(OB_BOR));

  /* Get the User Option byte register */
  tmp1 = OB->USER & ((~FLASH_OPTR_BOR_LEV) >> 16);

  /* Calculate the user option byte to write */ 
  tmp = (~(OB_Bits | tmp1)) << 16;
  tmp |= OB_Bits | tmp1;
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
    /* Program OB */
    OB->USER = tmp; 
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }
  
  return status;
}

/**
  * @brief  Sets or resets the BOOT bit1 option bit.
  * @param  OB_BOOT_BIT1: Set or Reset the BOOT bit1 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT_BIT1_RESET: BOOT1 option bit reset
  *             @arg OB_BOOT_BIT1_SET: BOOT1 option bit set
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_BOOTBit1Config(uint8_t OB_BOOT_BIT1)
{
  HAL_StatusTypeDef status = HAL_OK; 
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = ((uint32_t) OB_BOOT_BIT1) << 15;

  /* Check the parameters */
  assert_param(IS_OB_BOOT1(OB_BOOT_BIT1));

  /* Get the User Option byte register */
  tmp1 = OB->USER & ((~FLASH_OPTR_BOOT1) >> 16);

  /* Calculate the user option byte to write */ 
  tmp = (~(OB_Bits | tmp1)) << 16;
  tmp |= OB_Bits | tmp1;
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
    /* Program OB */
    OB->USER = tmp; 
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }

  return status;
}

/**
  * @brief  Select the Protection Mode (WPRMOD).
  * @note   Once WPRMOD bit is active, unprotection of a protected sector is not possible 
  * @note   Read a protected sector will set RDERR Flag and write a protected sector will set WRPERR Flag
  * @param  OB_PcROP: Select the Protection Mode of WPR bits. 
  *   This parameter can be:
  *     @arg OB_PCROP_SELECTED: nWRP control the  read&write protection (PcROP) of respective user sectors.
  *     @arg OB_PCROP_DESELECTED: nWRP control the write protection of respective user sectors.
  * @retval HAL status
  */
static HAL_StatusTypeDef FLASH_OB_PCROPSelectionConfig(uint32_t WPRMOD)
{
  HAL_StatusTypeDef status;
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = ((uint32_t) WPRMOD) << 8;

  /* Get the User Option byte register */
  tmp1 = OB->USER & ((~FLASH_OPTR_WPRMOD) >> 16);

  /* Calculate the user option byte to write */ 
  tmp = (~(OB_Bits | tmp1)) << 16;
  tmp |= OB_Bits | tmp1;
  
    /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {         
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;
   /* Program OB */
    OB->RDP = tmp;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }

  return status;
}

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
/**
  * @brief  Sets or resets the BFB2 option bit.
  * @param  BFB2: Set or Reset the BFB2 option bit.
  *          This parameter can be one of the following values:
  *             @arg OB_BOOT_BANK1: BFB2 option bit reset
  *             @arg OB_BOOT_BANK2: BFB2 option bit set
  * @retval None
  */
static HAL_StatusTypeDef FLASH_OB_BFB2Config(uint8_t OB_BFB2)
{
  HAL_StatusTypeDef status = HAL_OK; 
  uint32_t tmp = 0, tmp1 = 0, OB_Bits = ((uint32_t) OB_BFB2) << 7;

  /* Check the parameters */
  assert_param(IS_OB_BOOT_BANK(OB_BFB2));

  /* Get the User Option byte register */
  tmp1 = OB->USER & ((~FLASH_OPTR_BFB2) >> 16);

  /* Calculate the user option byte to write */ 
  tmp = (~(OB_Bits | tmp1)) << 16;
  tmp |= OB_Bits | tmp1;
    
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {  
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    /* Program OB */
    OB->USER = tmp; 

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  }
  return status;
}
#endif

/**
  * @brief  Write Option Byte of the desired pages of the Flash.
  * @param  Sector: specifies the sectors to be write protected.
  * @param  Sector2: specifies the sectors to be write protected only stm32l07xxx and stm32l08xxx devices
  * @param  NewState: new state of the specified FLASH Pages Wite protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval HAL_StatusTypeDef
  */
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
static HAL_StatusTypeDef FLASH_OB_ProtectedSectorsConfig(uint32_t Sector, uint32_t Sector2, uint32_t NewState)
#else
static HAL_StatusTypeDef FLASH_OB_ProtectedSectorsConfig(uint32_t Sector, uint32_t NewState)
#endif
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t WRP_Data = 0;
  uint32_t OB_WRP = Sector;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Clean the error context */
    ProcFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

    if (OB_WRP & 0x0000FFFF)
    {
      if (NewState != OB_WRPSTATE_DISABLE)
      {
        WRP_Data = (uint16_t)(((OB_WRP & WRP_MASK_LOW) | OB->WRP01));
        OB->WRP01 = (uint32_t)(~(WRP_Data) << 16) | (WRP_Data);
      }             
      else
      {
        WRP_Data = (uint16_t)(~OB_WRP & (WRP_MASK_LOW & OB->WRP01));
        OB->WRP01 =  (uint32_t)((~WRP_Data) << 16) | (WRP_Data);
      }
    }
#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
    if (OB_WRP & 0xFFFF0000)
    {
      if (NewState != OB_WRPSTATE_DISABLE)
      {
        WRP_Data = (uint16_t)((((OB_WRP & WRP_MASK_HIGH) >> 16 | OB->WRP23))); 
        OB->WRP23 = (uint32_t)(~(WRP_Data) << 16) | (WRP_Data);
      }             
      else
      {
        WRP_Data = (uint16_t)((((~OB_WRP & WRP_MASK_HIGH) >> 16 & OB->WRP23))); 
        OB->WRP23 = (uint32_t)((~WRP_Data) << 16) | (WRP_Data);
      } 
    }

    OB_WRP = Sector2;
    if (OB_WRP & 0x0000FFFF)
    {
      if (NewState != OB_WRPSTATE_DISABLE)
      {
        WRP_Data = (uint16_t)(((OB_WRP & WRP_MASK_LOW) | OB->WRP45));
        OB->WRP45 =(uint32_t)(~(WRP_Data) << 16) | (WRP_Data);
      }             
      else
      {
        WRP_Data = (uint16_t)(~OB_WRP & (WRP_MASK_LOW & OB->WRP45));
        OB->WRP45 = (uint32_t)((~WRP_Data) << 16) | (WRP_Data);
      }
    }
#endif /* STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
  }
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  /* Return the write protection operation Status */
  return status;      
}

/**
  * @}
  */
#endif /* HAL_FLASH_MODULE_ENABLED */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
