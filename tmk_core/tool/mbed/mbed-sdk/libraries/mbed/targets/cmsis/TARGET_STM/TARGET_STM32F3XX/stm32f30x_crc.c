/**
  ******************************************************************************
  * @file    stm32f30x_crc.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of CRC computation unit peripheral:
  *            + Configuration of the CRC computation unit
  *            + CRC computation of one/many 32-bit data
  *            + CRC Independent register (IDR) access
  *
  @verbatim
    
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..] 
    (#) Enable CRC AHB clock using RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE)
        function.
    (#) Select the polynomial size: 7-bit, 8-bit, 16-bit or 32-bit.
    (#) Set the polynomial coefficients using CRC_SetPolynomial();  
    (#) If required, select the reverse operation on input data 
        using CRC_ReverseInputDataSelect();  
    (#) If required, enable the reverse operation on output data
        using CRC_ReverseOutputDataCmd(Enable);
    (#) If required, set the initialization remainder value using
        CRC_SetInitRegister();
    (#) use CRC_CalcCRC() function to compute the CRC of a 32-bit data
        or use CRC_CalcBlockCRC() function to compute the CRC if a 32-bit 
        data buffer.

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
#include "stm32f30x_crc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC 
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions
  * @{
  */

/** @defgroup CRC_Group1 Configuration of the CRC computation unit functions
 *  @brief   Configuration of the CRC computation unit functions 
 *
@verbatim
 ===============================================================================
                  ##### CRC configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
  /* Set DR register to reset value */
  CRC->DR = 0xFFFFFFFF;
  /* Set the POL register to the reset value: 0x04C11DB7 */
  CRC->POL = 0x04C11DB7;
  /* Reset IDR register */
  CRC->IDR = 0x00;
  /* Set INIT register to reset value */
  CRC->INIT = 0xFFFFFFFF;
  /* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
}

/**
  * @brief  Resets the CRC calculation unit and sets INIT register content in DR register.
  * @param  None
  * @retval None
  */
void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR |= CRC_CR_RESET;
}

/**
  * @brief  Selects the polynomial size.
  * @param  CRC_PolSize: Specifies the polynomial size.
  *         This parameter can be:
  *          @arg CRC_PolSize_7: 7-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_8: 8-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_16: 16-bit polynomial for CRC calculation
  *          @arg CRC_PolSize_32: 32-bit polynomial for CRC calculation
  * @retval None
  */
void CRC_PolynomialSizeSelect(uint32_t CRC_PolSize)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_POL_SIZE(CRC_PolSize));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset POL_SIZE bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_POLSIZE);
  /* Set the polynomial size */
  tmpcr |= (uint32_t)CRC_PolSize;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Selects the reverse operation to be performed on input data.
  * @param  CRC_ReverseInputData: Specifies the reverse operation on input data.
  *         This parameter can be:
  *          @arg CRC_ReverseInputData_No: No reverse operation is performed
  *          @arg CRC_ReverseInputData_8bits: reverse operation performed on 8 bits
  *          @arg CRC_ReverseInputData_16bits: reverse operation performed on 16 bits
  *          @arg CRC_ReverseInputData_32bits: reverse operation performed on 32 bits
  * @retval None
  */
void CRC_ReverseInputDataSelect(uint32_t CRC_ReverseInputData)
{
  uint32_t tmpcr = 0;

  /* Check the parameter */
  assert_param(IS_CRC_REVERSE_INPUT_DATA(CRC_ReverseInputData));

  /* Get CR register value */
  tmpcr = CRC->CR;

  /* Reset REV_IN bits */
  tmpcr &= (uint32_t)~((uint32_t)CRC_CR_REV_IN);
  /* Set the reverse operation */
  tmpcr |= (uint32_t)CRC_ReverseInputData;

  /* Write to CR register */
  CRC->CR = (uint32_t)tmpcr;
}

/**
  * @brief  Enables or disable the reverse operation on output data.
  *         The reverse operation on output data is performed on 32-bit.
  * @param  NewState: new state of the reverse operation on output data.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRC_ReverseOutputDataCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable reverse operation on output data */
    CRC->CR |= CRC_CR_REV_OUT;
  }
  else
  {
    /* Disable reverse operation on output data */
    CRC->CR &= (uint32_t)~((uint32_t)CRC_CR_REV_OUT);
  }
}

/**
  * @brief  Initializes the INIT register.
  * @note   After resetting CRC calculation unit, CRC_InitValue is stored in DR register
  * @param  CRC_InitValue: Programmable initial CRC value
  * @retval None
  */
void CRC_SetInitRegister(uint32_t CRC_InitValue)
{
  CRC->INIT = CRC_InitValue;
}

/**
  * @brief  Initializes the polynomail coefficients.
  * @param  CRC_Pol: Polynomial to be used for CRC calculation.
  * @retval None
  */
void CRC_SetPolynomial(uint32_t CRC_Pol)
{
  CRC->POL = CRC_Pol;
}

/**
  * @}
  */

/** @defgroup CRC_Group2 CRC computation of one/many 32-bit data functions
 *  @brief   CRC computation of one/many 32-bit data functions
 *
@verbatim
 ===============================================================================
                      ##### CRC computation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRC_Data: data word(32-bit) to compute its CRC
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t CRC_Data)
{
  CRC->DR = CRC_Data;
  
  return (CRC->DR);
}

/**
  * @brief  Computes the 16-bit CRC of a given 16-bit data.
  * @param  CRC_Data: data half-word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint32_t CRC_CalcCRC16bits(uint16_t CRC_Data)
{
  *(uint16_t*)(CRC_BASE) = (uint16_t) CRC_Data;
  
  return (CRC->DR);
}

/**
  * @brief  Computes the 8-bit CRC of a given 8-bit data.
  * @param  CRC_Data: 8-bit data to compute its CRC
  * @retval 8-bit CRC
  */
uint32_t CRC_CalcCRC8bits(uint8_t CRC_Data)
{
  *(uint8_t*)(CRC_BASE) = (uint8_t) CRC_Data;

  return (CRC->DR);
}

/**
  * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  BufferLength: length of the buffer to be computed
  * @retval 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
  uint32_t index = 0;
  
  for(index = 0; index < BufferLength; index++)
  {
    CRC->DR = pBuffer[index];
  }
  return (CRC->DR);
}

/**
  * @brief  Returns the current CRC value.
  * @param  None
  * @retval 32-bit CRC
  */
uint32_t CRC_GetCRC(void)
{
  return (CRC->DR);
}

/**
  * @}
  */

/** @defgroup CRC_Group3 CRC Independent Register (IDR) access functions
 *  @brief   CRC Independent Register (IDR) access (write/read) functions
 *
@verbatim
 ===============================================================================
           ##### CRC Independent Register (IDR) access functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Stores an 8-bit data in the Independent Data(ID) register.
  * @param  CRC_IDValue: 8-bit value to be stored in the ID register 					
  * @retval None
  */
void CRC_SetIDRegister(uint8_t CRC_IDValue)
{
  CRC->IDR = CRC_IDValue;
}

/**
  * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
  * @param  None
  * @retval 8-bit value of the ID register 
  */
uint8_t CRC_GetIDRegister(void)
{
  return (CRC->IDR);
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
