/**
  ******************************************************************************
  * @file    stm32f30x_flash.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the FLASH peripheral:
  *            + FLASH Interface configuration
  *            + FLASH Memory Programming
  *            + Option Bytes Programming
  *            + Interrupts and flags management
  *  
  @verbatim
  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions to configure and program the FLASH 
         memory of all STM32F30x devices. These functions are split in 4 groups:
         (#) FLASH Interface configuration functions: this group includes the
             management of following features:
             (++) Set the latency.
             (++) Enable/Disable the Half Cycle Access.
             (++) Enable/Disable the prefetch buffer.
         (#) FLASH Memory Programming functions: this group includes all needed
             functions to erase and program the main memory:
             (++) Lock and Unlock the FLASH interface.
             (++) Erase function: Erase page, erase all pages.
             (++) Program functions: Half Word and Word write.
         (#) FLASH Option Bytes Programming functions: this group includes all 
             needed functions to manage the Option Bytes:
             (++) Lock and Unlock the Flash Option bytes.
             (++) Launch the Option Bytes loader
             (++) Erase the Option Bytes
             (++) Set/Reset the write protection
             (++) Set the Read protection Level
             (++) Program the user option Bytes
             (++) Set/Reset the BOOT1 bit
             (++) Enable/Disable the VDDA Analog Monitoring
             (++) Enable/Disable the SRAM parity
             (++) Get the user option bytes
             (++) Get the Write protection
             (++) Get the read protection status
         (#) FLASH Interrupts and flags management functions: this group includes 
             all needed functions to:
             (++) Enable/Disable the FLASH interrupt sources.
             (++) Get flags status.
             (++) Clear flags.
             (++) Get FLASH operation status.
             (++) Wait for last FLASH operation.
 
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
#include "stm32f30x_flash.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH 
  * @brief FLASH driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* FLASH Mask */
#define RDPRT_MASK                 ((uint32_t)0x00000002)
#define WRP01_MASK                 ((uint32_t)0x0000FFFF)
#define WRP23_MASK                 ((uint32_t)0xFFFF0000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_Private_Functions
  * @{
  */ 

/** @defgroup FLASH_Group1 FLASH Interface configuration functions
  *  @brief   FLASH Interface configuration functions 
 *

@verbatim   
 ===============================================================================
            ##### FLASH Interface configuration functions #####
 ===============================================================================
    [..] This group includes the following functions:
         (+) void FLASH_SetLatency(uint32_t FLASH_Latency); 
         (+) void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);     
         (+) void FLASH_PrefetchBufferCmd(FunctionalState NewState);
    [..] The unlock sequence is not needed for these functions.
 
@endverbatim
  * @{
  */
 
/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *          This parameter can be one of the following values:
  *            @arg FLASH_Latency_0: FLASH Zero Latency cycle
  *            @arg FLASH_Latency_1: FLASH One Latency cycle
  *            @arg FLASH_Latency_2: FLASH Two Latency cycles      
  * @retval None
  */
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
   uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_FLASH_LATENCY(FLASH_Latency));
  
  /* Read the ACR register */
  tmpreg = FLASH->ACR;  
  
  /* Sets the Latency value */
  tmpreg &= (uint32_t) (~((uint32_t)FLASH_ACR_LATENCY));
  tmpreg |= FLASH_Latency;
  
  /* Write the ACR register */
  FLASH->ACR = tmpreg;
}

/**
  * @brief  Enables or disables the Half cycle flash access.
  * @param  FLASH_HalfCycleAccess: specifies the FLASH Half cycle Access mode.
  *          This parameter can be one of the following values:
  *            @arg FLASH_HalfCycleAccess_Enable: FLASH Half Cycle Enable
  *            @arg FLASH_HalfCycleAccess_Disable: FLASH Half Cycle Disable
  * @retval None
  */
void FLASH_HalfCycleAccessCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
   
  if(NewState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_HLFCYA;
  }
  else
  {
    FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_HLFCYA));
  }
}

/**
  * @brief  Enables or disables the Prefetch Buffer.
  * @param  NewState: new state of the Prefetch Buffer.
  *          This parameter  can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_PrefetchBufferCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
   
  if(NewState != DISABLE)
  {
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  }
  else
  {
    FLASH->ACR &= (uint32_t)(~((uint32_t)FLASH_ACR_PRFTBE));
  }
}

/**
  * @}
  */

/** @defgroup FLASH_Group2 FLASH Memory Programming functions
 *  @brief   FLASH Memory Programming functions
 *
@verbatim   
 ===============================================================================
              ##### FLASH Memory Programming functions #####
 ===============================================================================   
    [..] This group includes the following functions:
         (+) void FLASH_Unlock(void);
         (+) void FLASH_Lock(void);
         (+) FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
         (+) FLASH_Status FLASH_EraseAllPages(void);
         (+) FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
         (+) FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
    [..] Any operation of erase or program should follow these steps:
         (#) Call the FLASH_Unlock() function to enable the FLASH control register 
             program memory access.
         (#) Call the desired function to erase page or program data.
         (#) Call the FLASH_Lock() function to disable the FLASH control register 
             access (recommended to protect the FLASH memory against possible 
             unwanted operation).
    
@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the FLASH control register access
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH Registers access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
  }  
}

/**
  * @brief  Locks the FLASH control register access
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  /* Set the LOCK Bit to lock the FLASH Registers access */
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function
  *         must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation)  
  * @param  Page_Address: The page address in program memory to be erased.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of 1024 bytes).  
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Page_Address));
 
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  { 
    /* If the previous operation is completed, proceed to erase the page */
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR  = Page_Address; 
    FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    /* Disable the PER Bit */
    FLASH->CR &= ~FLASH_CR_PER;
  }
    
  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Erases all FLASH pages.
  * @note   To correctly run this function, the FLASH_Unlock() function
  *         must be called before.
  *         all the FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_EraseAllPages(void)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* if the previous operation is completed, proceed to erase all pages */
     FLASH->CR |= FLASH_CR_MER;
     FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    /* Disable the MER Bit */
    FLASH->CR &= ~FLASH_CR_MER;
  }

  /* Return the Erase Status */
  return status;
}

/**
  * @brief  Programs a word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function
  *         must be called before.
  *         Call the FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation)  
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new first 
    half word */
    FLASH->CR |= FLASH_CR_PG;
  
    *(__IO uint16_t*)Address = (uint16_t)Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
 
    if(status == FLASH_COMPLETE)
    {
      /* If the previous operation is completed, proceed to program the new second 
      half word */
      tmp = Address + 2;

      *(__IO uint16_t*) tmp = Data >> 16;
    
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
        
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
    else
    {
      /* Disable the PG Bit */
      FLASH->CR &= ~FLASH_CR_PG;
    }
  }
   
  /* Return the Program Status */
  return status;
}

/**
  * @brief  Programs a half word at a specified address.
  * @note   To correctly run this function, the FLASH_Unlock() function
  *         must be called before.
  *         Call the FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation) 
  * @param  Address: specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT. 
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;

  /* Check the parameters */
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    /* If the previous operation is completed, proceed to program the new data */
    FLASH->CR |= FLASH_CR_PG;
  
    *(__IO uint16_t*)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    /* Disable the PG Bit */
    FLASH->CR &= ~FLASH_CR_PG;
  } 
  
  /* Return the Program Status */
  return status;
}

/**
  * @}
  */
  
/** @defgroup FLASH_Group3 Option Bytes Programming functions
 *  @brief   Option Bytes Programming functions 
 *
@verbatim   
 ===============================================================================
                ##### Option Bytes Programming functions #####
 ===============================================================================  
    [..] This group includes the following functions:
         (+) void FLASH_OB_Unlock(void);
         (+) void FLASH_OB_Lock(void);
         (+) void FLASH_OB_Erase(void);
         (+) FLASH_Status FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState);
         (+) FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP);
         (+) FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY);
         (+) FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1);
         (+) FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG);
         (+) FLASH_Status FLASH_OB_SRMParityConfig(uint8_t OB_SRAM_Parity);
         (+) FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER);					
         (+) FLASH_Status FLASH_OB_Launch(void);
         (+) uint32_t FLASH_OB_GetUser(void);						
         (+) uint8_t FLASH_OB_GetWRP(void);						
         (+) uint8_t FLASH_OB_GetRDP(void);							
    [..] Any operation of erase or program should follow these steps:
         (#) Call the FLASH_OB_Unlock() function to enable the FLASH option control 
             register access.
         (#) Call one or several functions to program the desired Option Bytes:
             (++) void FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState); 
                  => to Enable/Disable the desired sector write protection.
             (++) FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP) => to set the 
                  desired read Protection Level.
             (++) FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY); 
                  => to configure the user Option Bytes.
 	         (++) FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1); 
                  => to set the boot1 mode
             (++) FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG); 
                  => to Enable/Disable the VDDA monotoring.
             (++) FLASH_Status FLASH_OB_SRMParityConfig(uint8_t OB_SRAM_Parity); 
                  => to Enable/Disable the SRAM Parity check.		 
	         (++) FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER); 
                  => to write all user option bytes: OB_IWDG, OB_STOP, OB_STDBY, 
                     OB_BOOT1, OB_VDDA_ANALOG and OB_VDD_SD12.  
         (#) Once all needed Option Bytes to be programmed are correctly written, 
             call the FLASH_OB_Launch() function to launch the Option Bytes 
             programming process.
         (#@) When changing the IWDG mode from HW to SW or from SW to HW, a system 
              reset is needed to make the change effective.  
         (#) Call the FLASH_OB_Lock() function to disable the FLASH option control 
             register access (recommended to protect the Option Bytes against 
             possible unwanted operations).
    
@endverbatim
  * @{
  */

/**
  * @brief  Unlocks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Unlock(void)
{
  if((FLASH->CR & FLASH_CR_OPTWRE) == RESET)
  { 
    /* Unlocking the option bytes block access */
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;
  }
}

/**
  * @brief  Locks the option bytes block access.
  * @param  None
  * @retval None
  */
void FLASH_OB_Lock(void)
{
  /* Set the OPTWREN Bit to lock the option bytes block access */
  FLASH->CR &= ~FLASH_CR_OPTWRE;
}

/**
  * @brief  Launch the option byte loading.
  * @param  None
  * @retval None
  */
void FLASH_OB_Launch(void)
{
  /* Set the OBL_Launch bit to launch the option byte loading */
  FLASH->CR |= FLASH_CR_OBL_LAUNCH; 
}

/**
  * @brief  Erases the FLASH option bytes.
  * @note   This functions erases all option bytes except the Read protection (RDP). 
  * @param  None
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_Erase(void)
{
  uint16_t rdptmp = OB_RDP_Level_0;

  FLASH_Status status = FLASH_COMPLETE;

  /* Get the actual read protection Option Byte value */ 
  if(FLASH_OB_GetRDP() != RESET)
  {
    rdptmp = 0x00;  
  }

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {   
    /* If the previous operation is completed, proceed to erase the option bytes */
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
       
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;

      /* Restore the last read protection Option Byte value */
      OB->RDP = (uint16_t)rdptmp; 

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
 
      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else
    {
      if (status != FLASH_TIMEOUT)
      {
        /* Disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }  
  }
  /* Return the erase status */
  return status;
}

/**
  * @brief  Write protects the desired pages
  * @note   To correctly run this function, the FLASH_OB_Unlock() function
  *         must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option bytes 
  *         (recommended to protect the FLASH memory against possible unwanted operation)    
  * @param  OB_WRP: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg  value between OB_WRP_Pages0to35 and OB_WRP_Pages60to63
  *     @arg OB_WRP_AllPages
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_EnableWRP(uint32_t OB_WRP)
{
  uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF;
  
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Check the parameters */
  assert_param(IS_OB_WRP(OB_WRP));
    
  OB_WRP = (uint32_t)(~OB_WRP);
  WRP0_Data = (uint16_t)(OB_WRP & OB_WRP0_WRP0);
  WRP1_Data = (uint16_t)((OB_WRP & OB_WRP0_nWRP0) >> 8);
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTPG;

    if(WRP0_Data != 0xFF)
    {
      OB->WRP0 = WRP0_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
    {
      OB->WRP1 = WRP1_Data;
      
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    }
    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  } 
  /* Return the write protection operation Status */
  return status;      
}

/**
  * @brief  Enables or disables the read out protection.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function
  *         must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option bytes 
  *         (recommended to protect the FLASH memory against possible unwanted operation)   
  * @param  FLASH_ReadProtection_Level: specifies the read protection level. 
  *   This parameter can be:
  *     @arg OB_RDP_Level_0: No protection
  *     @arg OB_RDP_Level_1: Read protection of the memory                     
  *     @arg OB_RDP_Level_2: Chip protection
  *     @retval FLASH Status: The returned value can be: 
  * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_RDPConfig(uint8_t OB_RDP)
{
  FLASH_Status status = FLASH_COMPLETE;
  
  /* Check the parameters */
  assert_param(IS_OB_RDP(OB_RDP));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {
    FLASH->CR |= FLASH_CR_OPTER;
    FLASH->CR |= FLASH_CR_STRT;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
      /* If the erase operation is completed, disable the OPTER Bit */
      FLASH->CR &= ~FLASH_CR_OPTER;
      
      /* Enable the Option Bytes Programming operation */
      FLASH->CR |= FLASH_CR_OPTPG;
       
      OB->RDP = OB_RDP;

      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT); 
    
      if(status != FLASH_TIMEOUT)
      {
        /* if the program operation is completed, disable the OPTPG Bit */
        FLASH->CR &= ~FLASH_CR_OPTPG;
      }
    }
    else 
    {
      if(status != FLASH_TIMEOUT)
      {
        /* Disable the OPTER Bit */
        FLASH->CR &= ~FLASH_CR_OPTER;
      }
    }
  }
  /* Return the protection operation Status */
  return status;             
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY.
  * @param  OB_IWDG: Selects the IWDG mode
  *   This parameter can be one of the following values:
  *     @arg OB_IWDG_SW: Software IWDG selected
  *     @arg OB_IWDG_HW: Hardware IWDG selected
  * @param  OB_STOP: Reset event when entering STOP mode.
  *   This parameter can be one of the following values:
  *     @arg OB_STOP_NoRST: No reset generated when entering in STOP
  *     @arg OB_STOP_RST: Reset generated when entering in STOP
  * @param  OB_STDBY: Reset event when entering Standby mode.
  *   This parameter can be one of the following values:
  *     @arg OB_STDBY_NoRST: No reset generated when entering in STANDBY
  *     @arg OB_STDBY_RST: Reset generated when entering in STANDBY
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG, 
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
  assert_param(IS_OB_STOP_SOURCE(OB_STOP));
  assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
           
    OB->USER = (uint8_t)((uint8_t)(OB_IWDG | OB_STOP) | (uint8_t)(OB_STDBY |0xF8));
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the BOOT1. 
  * @param  OB_BOOT1: Set or Reset the BOOT1.
  *   This parameter can be one of the following values:
  *     @arg OB_BOOT1_RESET: BOOT1 Reset
  *     @arg OB_BOOT1_SET: BOOT1 Set
  * @retval None
  */
FLASH_Status FLASH_OB_BOOTConfig(uint8_t OB_BOOT1)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_BOOT1(OB_BOOT1));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
           
	OB->USER = OB_BOOT1|0xEF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the analogue monitoring on VDDA Power source. 
  * @param  OB_VDDA_ANALOG: Selects the analog monitoring on VDDA Power source.
  *   This parameter can be one of the following values:
  *     @arg OB_VDDA_ANALOG_ON: Analog monitoring on VDDA Power source ON
  *     @arg OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source OFF
  * @retval None
  */
FLASH_Status FLASH_OB_VDDAConfig(uint8_t OB_VDDA_ANALOG)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_VDDA_ANALOG(OB_VDDA_ANALOG));

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
           
	OB->USER = OB_VDDA_ANALOG |0xDF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Sets or resets the SRAM partiy.
  * @param  OB_SRAM_Parity: Set or Reset the SRAM partiy enable bit.
  *         This parameter can be one of the following values:
  *             @arg OB_SRAM_PARITY_SET: Set SRAM partiy.
  *             @arg OB_SRAM_PARITY_RESET: Reset SRAM partiy.
  * @retval None
  */
FLASH_Status FLASH_OB_SRAMParityConfig(uint8_t OB_SRAM_Parity)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Check the parameters */
  assert_param(IS_OB_SRAM_PARITY(OB_SRAM_Parity));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 

    OB->USER = OB_SRAM_Parity | 0xBF;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte program Status */
  return status;
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY/ BOOT1 and OB_VDDA_ANALOG.
  * @note   To correctly run this function, the FLASH_OB_Unlock() function
  *         must be called before.
  * @note   Call the FLASH_OB_Lock() to disable the flash control register access and the option bytes 
  *         (recommended to protect the FLASH memory against possible unwanted operation)   
  * @param  OB_USER: Selects all user option bytes
  *   This parameter is a combination of the following values:
  *     @arg OB_IWDG_SW / OB_IWDG_HW: Software / Hardware WDG selected
  *     @arg OB_STOP_NoRST / OB_STOP_RST: No reset / Reset generated when entering in STOP
  *     @arg OB_STDBY_NoRST / OB_STDBY_RST: No reset / Reset generated when entering in STANDBY
  *     @arg OB_BOOT1_RESET / OB_BOOT1_SET: BOOT1 Reset / Set
  *     @arg OB_VDDA_ANALOG_ON / OB_VDDA_ANALOG_OFF: Analog monitoring on VDDA Power source ON / OFF
  * @retval FLASH Status: The returned value can be: 
  * FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_OB_WriteUser(uint8_t OB_USER)
{
  FLASH_Status status = FLASH_COMPLETE; 

  /* Authorize the small information block programming */
  FLASH->OPTKEYR = FLASH_KEY1;
  FLASH->OPTKEYR = FLASH_KEY2;
  
  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
  
  if(status == FLASH_COMPLETE)
  {  
    /* Enable the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
           
	  OB->USER = OB_USER | 0x88;
  
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

    if(status != FLASH_TIMEOUT)
    {
      /* if the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }    
  /* Return the Option Byte program Status */
  return status;

}

/**
  * @brief  Programs a half word at a specified Option Byte Data address.
  * @note    To correctly run this function, the FLASH_OB_Unlock() function
  *           must be called before.
  *          Call the FLASH_OB_Lock() to disable the flash control register access and the option bytes 
  *          (recommended to protect the FLASH memory against possible unwanted operation)
  * @param  Address: specifies the address to be programmed.
  *   This parameter can be 0x1FFFF804 or 0x1FFFF806. 
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be: FLASH_ERROR_PG,
  *         FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
  FLASH_Status status = FLASH_COMPLETE;
  /* Check the parameters */
  assert_param(IS_OB_DATA_ADDRESS(Address));
  status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);

  if(status == FLASH_COMPLETE)
  {
    /* Enables the Option Bytes Programming operation */
    FLASH->CR |= FLASH_CR_OPTPG; 
    *(__IO uint16_t*)Address = Data;
    
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status != FLASH_TIMEOUT)
    {
      /* If the program operation is completed, disable the OPTPG Bit */
      FLASH->CR &= ~FLASH_CR_OPTPG;
    }
  }
  /* Return the Option Byte Data Program Status */
  return status;
}

/**
  * @brief  Returns the FLASH User Option Bytes values.
  * @param  None
  * @retval The FLASH User Option Bytes .
  */
uint8_t FLASH_OB_GetUser(void)
{
  /* Return the User Option Byte */
  return (uint8_t)(FLASH->OBR >> 8);
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes value.
  * @param  None
  * @retval The FLASH Write Protection Option Bytes value
  */
uint32_t FLASH_OB_GetWRP(void)
{
  /* Return the FLASH write protection Register value */
  return (uint32_t)(FLASH->WRPR);
}

/**
  * @brief  Checks whether the FLASH Read out Protection Status is set or not.
  * @param  None
  * @retval FLASH ReadOut Protection Status(SET or RESET)
  */
FlagStatus FLASH_OB_GetRDP(void)
{
  FlagStatus readstatus = RESET;
  
  if ((uint8_t)(FLASH->OBR & (FLASH_OBR_RDPRT1 | FLASH_OBR_RDPRT2)) != RESET)
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
  * @}
  */

/** @defgroup FLASH_Group4 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions
 *
@verbatim   
 ===============================================================================
             ##### Interrupts and flags management functions #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or 
  *         disabled.
  *   This parameter can be any combination of the following values:     
  *     @arg FLASH_IT_EOP: FLASH end of programming Interrupt
  *     @arg FLASH_IT_ERR: FLASH Error Interrupt 
  * @retval None 
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_IT(FLASH_IT)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    FLASH->CR |= FLASH_IT;
  }
  else
  {
    /* Disable the interrupt sources */
    FLASH->CR &= ~(uint32_t)FLASH_IT;
  }
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *   This parameter can be one of the following values:
  *     @arg FLASH_FLAG_BSY: FLASH write/erase operations in progress flag 
  *     @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_EOP: FLASH End of Programming flag        
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

  if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the new state of FLASH_FLAG (SET or RESET) */
  return bitstatus; 
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *   This parameter can be any combination of the following values:
  *     @arg FLASH_FLAG_PGERR: FLASH Programming error flag flag
  *     @arg FLASH_FLAG_WRPERR: FLASH Write protected error flag
  *     @arg FLASH_FLAG_EOP: FLASH End of Programming flag                
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
  /* Check the parameters */
  assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));
  
  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @retval FLASH Status: The returned value can be: 
  *         FLASH_BUSY, FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
  FLASH_Status FLASHstatus = FLASH_COMPLETE;
  
  if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
  {
    FLASHstatus = FLASH_BUSY;
  }
  else 
  {  
    if((FLASH->SR & (uint32_t)FLASH_FLAG_WRPERR)!= (uint32_t)0x00)
    { 
      FLASHstatus = FLASH_ERROR_WRP;
    }
    else 
    {
      if((FLASH->SR & (uint32_t)(FLASH_SR_PGERR)) != (uint32_t)0x00)
      {
        FLASHstatus = FLASH_ERROR_PROGRAM; 
      }
      else
      {
        FLASHstatus = FLASH_COMPLETE;
      }
    }
  }
  /* Return the FLASH Status */
  return FLASHstatus;
}

/**
  * @brief  Waits for a FLASH operation to complete or a TIMEOUT to occur.
  * @param  Timeout: FLASH programming Timeout
  * @retval FLASH Status: The returned value can be: FLASH_BUSY, 
  *         FLASH_ERROR_PROGRAM, FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{ 
  FLASH_Status status = FLASH_COMPLETE;
   
  /* Check for the FLASH Status */
  status = FLASH_GetStatus();
  
  /* Wait for a FLASH operation to complete or a TIMEOUT to occur */
  while((status == FLASH_BUSY) && (Timeout != 0x00))
  {
    status = FLASH_GetStatus();
    Timeout--;
  }
  
  if(Timeout == 0x00 )
  {
    status = FLASH_TIMEOUT;
  }
  /* Return the operation status */
  return status;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
