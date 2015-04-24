/**
  ******************************************************************************
  * @file    stm32l1xx_hal_flash.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   FLASH HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the internal FLASH memory:
  *            + FLASH Interface configuration
  *            + FLASH Memory Programming
  *            + Interrupts and flags management
  *
  *  @verbatim

  ==============================================================================
                      ##### FLASH peripheral features #####
  ==============================================================================
           
  [..] The Flash memory interface manages CPU AHB I-Code and D-Code accesses 
       to the Flash memory. It implements the erase and program Flash memory operations 
       and the read and write protection mechanisms.
      
  [..] The Flash memory interface accelerates code execution with a system of instruction prefetch. 

  [..] The FLASH main features are:
      (+) Flash memory read operations
      (+) Flash memory program/erase operations
      (+) Read / write protections
      (+) Prefetch on I-Code
      (+) Option Bytes programming
      
            ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure and program the Flash 
     memory of all STM32L1xx devices.

     (#) FLASH Memory Programming functions: this group includes all 
       needed functions to erase and program the main memory:
       (++) Lock and Unlock the Flash interface.
       (++) Erase function: Erase Page.
       (++) Program functions: Fast Word and Half Page(should be 
        executed from internal SRAM).
  
     (#) DATA EEPROM Programming functions: this group includes all 
       needed functions to erase and program the DATA EEPROM memory:
       (++) Lock and Unlock the DATA EEPROM interface.
       (++) Erase function: Erase Byte, erase HalfWord, erase Word, erase 
       Double Word (should be executed from internal SRAM).
       (++) Program functions: Fast Program Byte, Fast Program Half-Word, 
        FastProgramWord, Program Byte, Program Half-Word, 
        Program Word and Program Double-Word (should be executed 
        from internal SRAM).
  
     (#) FLASH Option Bytes Programming functions: this group includes 
       all needed functions to:
       (++) Lock and Unlock the Flash Option bytes.
       (++) Set/Reset the write protection.
       (++) Set the Read protection Level.
       (++) Set the BOR level.
       (++) Program the user option Bytes.
       (++) Launch the Option Bytes loader.
       (++) Get the Write protection.
       (++) Get the read protection status.
       (++) Get the BOR level.
       (++) Get the user option bytes.
       
     (#) Interrupts and flags management functions : 
       (++) Handle FLASH interrupts by calling HAL_FLASH_IRQHandler()
       (++) Wait for last FLASH operation according to its status
       (++) Get error flag status by calling HAL_GetErrorCode()          

    (#) FLASH Interface configuration functions: this group includes 
      the management of following features:
      (++) Enable/Disable the RUN PowerDown mode.
      (++) Enable/Disable the SLEEP PowerDown mode.  
  
    (#) FLASH Peripheral State methods: this group includes 
      the management of following features:
      (++) Wait for the FLASH operation
      (++)  Get the specific FLASH error flag
    
  [..] In addition to these function, this driver includes a set of macros allowing
       to handle the following operations:
      
    (+) Set/Get the latency
    (+) Enable/Disable the prefetch buffer
    (+) Enable/Disable the 64 bit Read Access. 
       (+) Enable/Disable the Flash power-down
       (+) Enable/Disable the FLASH interrupts
       (+) Monitor the FLASH flags status

  ===============================================================================
                 ##### Programming operation functions #####
  ===============================================================================  
     [..]
     This subsection provides a set of functions allowing to manage the FLASH 
     program operations.
  
    [..] The FLASH Memory Programming functions, includes the following functions:
     (+) HAL_FLASH_Unlock(void);
     (+) HAL_FLASH_Lock(void);
     (+) HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
     (+) HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint32_t Data)
    
     [..] Any operation of erase or program should follow these steps:
     (#) Call the HAL_FLASH_Unlock() function to enable the flash control register and 
         program memory access.
     (#) Call the desired function to erase page or program data.
     (#) Call the HAL_FLASH_Lock() to disable the flash program memory access 
        (recommended to protect the FLASH memory against possible unwanted operation).
  
   ==============================================================================
               ##### Option Bytes Programming functions ##### 
   ==============================================================================  
  
     [..] The FLASH_Option Bytes Programming_functions, includes the following functions:
     (+) HAL_FLASH_OB_Unlock(void);
     (+) HAL_FLASH_OB_Lock(void);
     (+) HAL_FLASH_OB_Launch(void);
     (+) HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
     (+) HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
    
     [..] Any operation of erase or program should follow these steps:
     (#) Call the HAL_FLASH_OB_Unlock() function to enable the Flash option control 
         register access.
     (#) Call the following functions to program the desired option bytes.
         (++) HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);      
     (#) Once all needed option bytes to be programmed are correctly written, call the
         HAL_FLASH_OB_Launch(void) function to launch the Option Bytes programming process.
     (#) Call the HAL_FLASH_OB_Lock() to disable the Flash option control register access (recommended
         to protect the option Bytes against possible unwanted operations).
  
  *  @endverbatim
  *                      
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

#ifdef HAL_FLASH_MODULE_ENABLED

/** @defgroup FLASH FLASH
  * @brief FLASH driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup FLASH_Internal_Variables FLASH Internal Variables
  * @{
  */  

/**
  * @brief  Variable used for Program/Erase sectors under interruption 
  */
FLASH_ProcessTypeDef      ProcFlash;


/**
  * @}
  */ 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_Exported_Functions FLASH Exported functions
  * @{
  */
  
/** @defgroup FLASH_Exported_Functions_Group1 Programming operation functions 
 *  @brief   Programming operation functions 
 *
@verbatim
@endverbatim
  * @{
  */
/**
  * @brief  Program word at a specified address
  * @note   To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access
  *         (recommended to protect the FLASH memory against possible unwanted operation).
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                           This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address:  specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_ERROR;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Check the parameters */
  assert_param(IS_TYPEPROGRAMFLASH(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Wait for last operation to be completed */
  status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /*Program word (32-bit) at a specified address.*/
    *(__IO uint32_t *)Address = Data;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(&ProcFlash);

  return status;
}

/**
  * @brief   Program word at a specified address  with interrupt enabled.
  * @param  TypeProgram:  Indicate the way to program at a specified address.
  *                           This parameter can be a value of @ref FLASH_Type_Program
  * @param  Address:  specifies the address to be programmed.
  * @param  Data: specifies the data to be programmed
  * 
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Process Locked */
  __HAL_LOCK(&ProcFlash);

  /* Check the parameters */
  assert_param(IS_TYPEPROGRAMFLASH(TypeProgram));
  assert_param(IS_FLASH_PROGRAM_ADDRESS(Address));

  /* Enable End of FLASH Operation interrupt */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP);
  
  /* Enable Error source interrupt */
  __HAL_FLASH_ENABLE_IT(FLASH_IT_ERR);
  
  /* Clear pending flags (if any) */  
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_MASK);  

  ProcFlash.ProcedureOnGoing = FLASH_PROC_PROGRAM;
  ProcFlash.Address = Address;

  if(TypeProgram == TYPEPROGRAM_WORD)
  {
    /*Program word (32-bit) at a specified address.*/
    *(__IO uint32_t *)Address = Data;
  }
  
  /* Process Unlocked */
  __HAL_UNLOCK(&ProcFlash);
  
  return status;
}

/**
  * @brief  FLASH end of operation interrupt callback
  * @param  ReturnValue: The value saved in this parameter depends on the ongoing procedure
  *                 - Pages Erase: Sector which has been erased 
  *                    (if 0xFFFFFFFF, it means that all the selected sectors have been erased)
  *                 - Program: Address which was selected for data program
  * @retval none
  */
__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FLASH_EndOfOperationCallback could be implemented in the user file
   */ 
}

/**
  * @brief  FLASH operation error interrupt callback
  * @param  ReturnValue: The value saved in this parameter depends on the ongoing procedure
  *                 - Pagess Erase: Sector number which returned an error
  *                 - Program: Address which was selected for data program
  * @retval none
  */
__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_FLASH_OperationErrorCallback could be implemented in the user file
   */ 
}

/**
  * @}
  */  

/** @defgroup FLASH_Exported_Functions_Group2 Peripheral Control functions 
 *  @brief   management functions 
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
  * @brief  Unlock the FLASH control register access
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Unlock(void)  
{
  if((FLASH->PECR & FLASH_PECR_PRGLOCK) != RESET)
  {
    /* Unlocking FLASH_PECR register access*/
    if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET)
    {  
      FLASH->PEKEYR = FLASH_PEKEY1;
      FLASH->PEKEYR = FLASH_PEKEY2;
    }
    
    /* Unlocking the program memory access */
    FLASH->PRGKEYR = FLASH_PRGKEY1;
    FLASH->PRGKEYR = FLASH_PRGKEY2;  
  }
  else
  {
    return HAL_ERROR;
  }
  
  return HAL_OK; 
}

/**
  * @brief  Locks the FLASH control register access
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_Lock(void)
{
  /* Set the PRGLOCK Bit to lock the program memory access */
  SET_BIT(FLASH->PECR, FLASH_PECR_PRGLOCK);
  
  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH Option Control Registers access.
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  if((FLASH->PECR & FLASH_PECR_OPTLOCK) != RESET)
  {
    /* Unlocking FLASH_PECR register access*/
    if((FLASH->PECR & FLASH_PECR_PELOCK) != RESET)
    {  
      /* Unlocking FLASH_PECR register access*/
      FLASH->PEKEYR = FLASH_PEKEY1;
      FLASH->PEKEYR = FLASH_PEKEY2;
    }

    /* Unlocking the option bytes block access */
    FLASH->OPTKEYR = FLASH_OPTKEY1;
    FLASH->OPTKEYR = FLASH_OPTKEY2;
  }
  else
  {
    return HAL_ERROR;
  }  
  
  return HAL_OK;
}

/**
  * @brief  Lock the FLASH Option Control Registers access.
  * @retval HAL_StatusTypeDef HAL Status 
  */
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void)
{
  /* Set the OPTLOCK Bit to lock the option bytes block access */
  SET_BIT(FLASH->PECR, FLASH_PECR_OPTLOCK);

  return HAL_OK;  
}

/**
  * @brief  Launch the option byte loading.
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void)
{
  /* Set the OBL_Launch bit to lauch the option byte loading */
  SET_BIT(FLASH->PECR, FLASH_PECR_OBL_LAUNCH);
  
  /* Wait for last operation to be completed */
  return(FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE));  
}

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions_Group3 Peripheral State and Errors functions 
 *  @brief   Peripheral Errors functions 
 *
@verbatim   
 ===============================================================================
                ##### Peripheral Errors functions #####
 ===============================================================================  
    [..]
    This subsection permit to get in run-time Errors of the FLASH peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Get the specific FLASH error flag.
  * @retval FLASH_ErrorCode: The returned value can be:
  *            @arg FLASH_ERROR_WRP: FLASH Write protected error flag
  *            @arg FLASH_ERROR_PGA: FLASH Programming Alignment error flag
  *            @arg FLASH_ERROR_SIZE: FLASH Size error flag
  *            @arg FLASH_ERROR_OPTV: Option validity error flag
  *            @arg FLASH_ERROR_OPTVUSR: Option UserValidity Error flag (available only Cat.3, Cat.4 and Cat.5 devices)
  *            @arg FLASH_ERROR_RD:   FLASH Read Protection error flag (PCROP) (available only Cat.2 and Cat.3 devices)
  */
FLASH_ErrorTypeDef HAL_FLASH_GetError(void)
{ 
   return ProcFlash.ErrorCode;
}  

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

/**
  * @}
  */


     
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
