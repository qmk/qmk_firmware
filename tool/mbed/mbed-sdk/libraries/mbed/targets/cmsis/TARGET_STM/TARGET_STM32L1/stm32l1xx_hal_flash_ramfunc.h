/**
  ******************************************************************************
  * @file    stm32l1xx_hal_flash_ramfunc.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   Header file of FLASH RAMFUNC driver.
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
#ifndef __STM32L1xx_FLASH_RAMFUNC_H
#define __STM32L1xx_FLASH_RAMFUNC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHRamfunc
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 


/* Exported functions --------------------------------------------------------*/

/** @addtogroup FLASHRamfunc_Exported_Functions
  * @{
  */

/*
  * @brief  FLASH memory functions that should be executed from internal SRAM.
  *         These functions are defined inside the "stm32l1xx_hal_flash_ramfunc.c"
  *         file.
  */
  
/** @addtogroup FLASHRamfunc_Exported_Functions_Group1
  * @{
  */

__RAM_FUNC HAL_FLASHEx_EnableRunPowerDown(void);
__RAM_FUNC HAL_FLASHEx_DisableRunPowerDown(void);

/**
  * @}
  */ 

/** @addtogroup FLASHRamfunc_Exported_Functions_Group2
  * @{
  */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD) || \
    defined(STM32L151xE) || defined (STM32L152xE) || defined (STM32L162xE)

__RAM_FUNC HAL_FLASHEx_EraseParallelPage(uint32_t Page_Address1, uint32_t Page_Address2);
__RAM_FUNC HAL_FLASHEx_ProgramParallelHalfPage(uint32_t Address1, uint32_t* pBuffer1, uint32_t Address2, uint32_t* pBuffer2);

#endif /* STM32L151xD || STM32L152xD || STM32L162xD || STM32L151xE || STM32L152xE || STM32L162xE */

__RAM_FUNC HAL_FLASHEx_HalfPageProgram(uint32_t Address, uint32_t* pBuffer);

/**
  * @}
  */ 

/** @addtogroup FLASHRamfunc_Exported_Functions_Group3
  * @{
  */

__RAM_FUNC HAL_FLASHEx_DATAEEPROM_EraseDoubleWord(uint32_t Address);
__RAM_FUNC HAL_FLASHEx_DATAEEPROM_ProgramDoubleWord(uint32_t Address, uint64_t Data);

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

#endif /* __STM32L1xx_FLASH_RAMFUNC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
