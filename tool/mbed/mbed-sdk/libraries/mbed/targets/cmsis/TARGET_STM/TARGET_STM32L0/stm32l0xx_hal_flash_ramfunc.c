/**
  ******************************************************************************
  * @file    stm32l0xx_hal_flash_ramfunc.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   FLASH RAMFUNC driver.
  *          This file provides a Flash firmware functions which should be 
  *          executed from internal SRAM
  *
  *  @verbatim

    *** ARM Compiler ***
    --------------------
    [..] RAM functions are defined using the toolchain options. 
         Functions that are be executed in RAM should reside in a separate
         source module. Using the 'Options for File' dialog you can simply change
         the 'Code / Const' area of a module to a memory space in physical RAM.
         Available memory areas are declared in the 'Target' tab of the 
         Options for Target' dialog.

    *** ICCARM Compiler ***
    -----------------------
    [..] RAM functions are defined using a specific toolchain keyword "__ramfunc".

    *** GNU Compiler ***
    --------------------
    [..] RAM functions are defined using a specific toolchain attribute
         "__attribute__((section(".RamFunc")))".

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

#ifdef HAL_FLASH_MODULE_ENABLED
/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHRamfunc
  * @brief FLASH functions executed from RAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static __RAM_FUNC FLASHRAM_WaitForLastOperation(uint32_t Timeout);
static __RAM_FUNC FLASHRAM_SetErrorCode(void);


/** @addtogroup FLASHRamfunc_Exported_Functions
 *
@verbatim   
 ===============================================================================
                      ##### ramfunc functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions that should be executed from RAM 
    transfers.

@endverbatim
  * @{
  */

/** @addtogroup FLASHRamfunc_Exported_Functions_Group1
  * @{
  */  

/**
  * @brief  Enable  the power down mode during RUN mode.
  * @note   This function can be used only when the user code is running from Internal SRAM.
  * @param  None
  * @retval None
  */
__RAM_FUNC HAL_FLASHEx_EnableRunPowerDown(void)
{
  /* Enable the Power Down in Run mode*/
  __HAL_FLASH_POWER_DOWN_ENABLE();
  return HAL_OK;
}

/**
  * @brief  Disable the power down mode during RUN mode.
  * @note   This function can be used only when the user code is running from Internal SRAM.
  * @param  None
  * @retval None
  */
__RAM_FUNC HAL_FLASHEx_DisableRunPowerDown(void)
{
  /* Disable the Power Down in Run mode*/
  __HAL_FLASH_POWER_DOWN_DISABLE();
  return HAL_OK;  
}

/**
  * @}
  */

/** @addtogroup FLASHRamfunc_Exported_Functions_Group2
 *
@verbatim  
@endverbatim
  * @{
  */

#if defined(STM32L071xx) || defined(STM32L072xx) || defined(STM32L073xx) || defined(STM32L081xx) || defined(STM32L082xx) || defined(STM32L083xx)  
/**
  * @brief  Erases a specified 2 pages in program memory in parallel.
  * @note   This function can be used only for STM32L07xxx/STM32L08xxx  devices.
  *         To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access 
  *         (recommended to protect the FLASH memory against possible unwanted operation).
  * @param  Page_Address1: The page address in program memory to be erased in 
  *         the first Bank (BANK1). This parameter should be between FLASH_BASE
  *         and FLASH_BANK1_END.
  * @param  Page_Address2: The page address in program memory to be erased in 
  *         the second Bank (BANK2). This parameter should be between FLASH_BANK2_BASE
  *         and FLASH_BANK2_END.
  * @note   A Page is erased in the Program memory only if the address to load 
  *         is the start address of a page (multiple of 128 bytes).
  * @retval HAL Status: The returned value can be: 
  *         HAL_ERROR, HAL_OK or HAL_TIMEOUT.
  */
__RAM_FUNC HAL_FLASHEx_EraseParallelPage(uint32_t Page_Address1, uint32_t Page_Address2)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Wait for last operation to be completed */
  status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Proceed to erase the page */
    SET_BIT(FLASH->PECR, FLASH_PECR_PARALLBANK);
    SET_BIT(FLASH->PECR, FLASH_PECR_ERASE);
    SET_BIT(FLASH->PECR, FLASH_PECR_PROG);
  
    /* Write 00000000h to the first word of the first program page to erase */
    *(__IO uint32_t *)Page_Address1 = 0x00000000;
    /* Write 00000000h to the first word of the second program page to erase */    
    *(__IO uint32_t *)Page_Address2 = 0x00000000;    
 
    /* Wait for last operation to be completed */
    status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

    /* If the erase operation is completed, disable the ERASE, PROG and PARALLBANK bits */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_PROG);
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_ERASE);
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_PARALLBANK);
  }     
  /* Return the erasesStatus */
  return status;
}

/**
  * @brief  Programs 2 half pages in program memory in parallel. The half page size is 16 Words.
  * @note   This function can be used only for STM32L07xxx/STM32L08xxx devices.
  * @param  Address1: specifies the first address to be written in the first bank 
  *         (BANK1). This parameter should be between FLASH_BASE and (FLASH_BANK1_END - FLASH_PAGE_SIZE).
  * @param  pBuffer1: pointer to the buffer  containing the data to be  written 
  *         to the first half page in the first bank.
  * @param  Address2: specifies the second address to be written in the second bank
  *         (BANK2). This parameter should be between FLASH_BANK2_BASE and (FLASH_BANK2_END - FLASH_PAGE_SIZE).
  * @param  pBuffer2: pointer to the buffer containing the data to be  written 
  *         to the second half page in the second bank.
  * @note   To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access  
  *         (recommended to protect the FLASH memory against possible unwanted operation).
  * @note   Half page write is possible only from SRAM.
  * @note   A half page is written to the program memory only if the first 
  *         address to load is the start address of a half page (multiple of 64 
  *         bytes) and the 15 remaining words to load are in the same half page.
  * @note   During the Program memory half page write all read operations are 
  *         forbidden (this includes DMA read operations and debugger read 
  *         operations such as breakpoints, periodic updates, etc.).
  * @note   If a PGAERR is set during a Program memory half page write, the 
  *         complete write operation is aborted. Software should then reset the 
  *         FPRG and PROG/DATA bits and restart the write operation from the 
  *         beginning.
  * @retval HAL Status: The returned value can be:  
  *         HAL_ERROR, HAL_OK or HAL_TIMEOUT.
  */
__RAM_FUNC HAL_FLASHEx_ProgramParallelHalfPage(uint32_t Address1, uint32_t* pBuffer1, uint32_t Address2, uint32_t* pBuffer2)
{
  uint32_t count; 
  HAL_StatusTypeDef status;

  /* Wait for last operation to be completed */
  status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
  
  if(status == HAL_OK)
  {
    /* Proceed to program the new half page */
    SET_BIT(FLASH->PECR, FLASH_PECR_PARALLBANK);
    SET_BIT(FLASH->PECR, FLASH_PECR_FPRG);
    SET_BIT(FLASH->PECR, FLASH_PECR_PROG);

 
    /* Wait for last operation to be completed */
    status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

    if(status == HAL_OK)
    {
      /* Write one half page,
         Address1 doesn't need to be increased */ 
      count = 0;

      /* Disable all IRQs */
      __disable_irq();

      while(count < 16)
      {
        *(__IO uint32_t*) Address1 = *pBuffer1;
        pBuffer1++;
        count++;
      }
      
      /* Write the second half page,
         Address2 doesn't need to be increased */ 
      count = 0;
      while(count < 16)
      {
        *(__IO uint32_t*) Address2 = *pBuffer2;
        pBuffer2++;
        count++;
      }

      /* Enable IRQs */
      __enable_irq();
      
      /* Wait for last operation to be completed */
      status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    } 
    /* if the write operation is completed, disable the PROG, FPRG and PARALLBANK bits */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_PROG);
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_FPRG);
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_PARALLBANK);
  }
  /* Return the Write Status */
  return status;
}
#endif /* STM32L071xx || STM32L072xx || STM32L073xx || STM32L081xx || STM32L082xx || STM32L083xx */
  
/**
  * @brief  Program a half page in program memory. 
  * @param  Address: specifies the address to be written.
  * @param  pBuffer: pointer to the buffer  containing the data to be  written to 
  *         the half page.
  * @note   To correctly run this function, the HAL_FLASH_Unlock() function
  *         must be called before.
  *         Call the HAL_FLASH_Lock() to disable the flash memory access  
  *         (recommended to protect the FLASH memory against possible unwanted operation)
  * @note   Half page write is possible only from SRAM.
  * @note   A half page is written to the program memory only if the first 
  *         address to load is the start address of a half page (multiple of 64 
  *         bytes) and the 15 remaining words to load are in the same half page.
  * @note   During the Program memory half page write all read operations are 
  *         forbidden (this includes DMA read operations and debugger read 
  *         operations such as breakpoints, periodic updates, etc.).
  * @note   If a PGAERR is set during a Program memory half page write, the 
  *         complete write operation is aborted. Software should then reset the 
  *         FPRG and PROG/DATA bits and restart the write operation from the 
  *         beginning.
  * @retval HAL Status: The returned value can be:  
  *         HAL_ERROR, HAL_OK or HAL_TIMEOUT. 
  */
__RAM_FUNC HAL_FLASHEx_HalfPageProgram(uint32_t Address, uint32_t *pBuffer)
{
  uint32_t count; 
  HAL_StatusTypeDef status;

  /* Wait for last operation to be completed */
  status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if(status == HAL_OK)
  {
    /* Proceed to program the new half page */
    SET_BIT(FLASH->PECR, FLASH_PECR_FPRG);
    SET_BIT(FLASH->PECR, FLASH_PECR_PROG);


    count = 0;
    /* Write one half page,
       Address doesn't need to be increased */ 

    /* Disable all IRQs */
    __disable_irq();

    while(count < 16)
    {
      *(__IO uint32_t*) Address = *pBuffer;
      pBuffer++;
      count++;
    }

    /* Enable IRQs */
    __enable_irq();
  
    /* Wait for last operation to be completed */
    status = FLASHRAM_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

    /* If the write operation is completed, disable the PROG and FPRG bits */
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_PROG);
    CLEAR_BIT(FLASH->PECR, FLASH_PECR_FPRG);
  }
  /* Return the write status */
  return status;
}

/**
  * @brief  Get the specific FLASH errors flag.
  * @param error pointer is the error value. It can be a mixed of :
  *            @arg HAL_FLASH_ERROR_RD: FLASH Read Protection error flag (PCROP)
  *            @arg HAL_FLASH_ERROR_SIZE: FLASH Programming Parallelism error flag  
  *            @arg HAL_FLASH_ERROR_PGA: FLASH Programming Alignment error flag
  *            @arg HAL_FLASH_ERROR_WRP: FLASH Write protected error flag
  *            @arg HAL_FLASH_ERROR_OPTV: FLASH Option valid error flag 
  *            @arg HAL_FLASH_ERROR_FWWERR: FLASH Write or Errase operation aborted
  *            @arg HAL_FLASH_ERROR_NOTZERO: FLASH Write operation is done in a not-erased region 
  */
__RAM_FUNC HAL_FLASHRAM_GetError(uint32_t * error)
{ 
  *error = ProcFlash.ErrorCode;
  return HAL_OK;  
}



/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASHRamfunc_Private_Functions FLASH RAM Private Functions
  * @{
  */ 

/**
  * @brief  Set the specific FLASH error flag.
  * @param  None
  * @retval None
  */
static __RAM_FUNC FLASHRAM_SetErrorCode(void)
{  
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR))
  { 
    ProcFlash.ErrorCode |= HAL_FLASH_ERROR_WRP;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR))
  { 
    ProcFlash.ErrorCode |= HAL_FLASH_ERROR_PGA;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR))
  { 
    ProcFlash.ErrorCode |= HAL_FLASH_ERROR_SIZE;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR))
  { 
    ProcFlash.ErrorCode |= HAL_FLASH_ERROR_OPTV;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR))
  { 
    ProcFlash.ErrorCode |= HAL_FLASH_ERROR_RD;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_FWWERR))
  { 
   ProcFlash.ErrorCode |= HAL_FLASH_ERROR_FWWERR;
  }
  if(__HAL_FLASH_GET_FLAG(FLASH_FLAG_NOTZEROERR))
  { 
   ProcFlash.ErrorCode |= HAL_FLASH_ERROR_NOTZERO;
  }
  
  /* Errors are now stored, clear errors flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_SIZERR |
                         FLASH_FLAG_OPTVERR | FLASH_FLAG_RDERR | FLASH_FLAG_FWWERR | 
                         FLASH_FLAG_NOTZEROERR);
  return HAL_OK;
} 


/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout: maximum flash operationtimeout
  * @retval HAL status
  */
static __RAM_FUNC FLASHRAM_WaitForLastOperation(uint32_t Timeout)
{ 
    /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
       Even if the FLASH operation fails, the BUSY flag will be reset and an error
       flag will be set */
       
    while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) && (Timeout != 0x00)) 
    { 
      Timeout--;
    }
    
    if(Timeout == 0x00 )
    {
      return HAL_TIMEOUT;
    }
    
    if( (__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR)      != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPTVERR)    != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_SIZERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_FWWERR)     != RESET) || 
        (__HAL_FLASH_GET_FLAG(FLASH_FLAG_NOTZEROERR) != RESET) )
    {
      /*Save the error code*/
      FLASHRAM_SetErrorCode();
      return HAL_ERROR;
    }
  
    /* If there is an error flag set */
    return HAL_OK;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

