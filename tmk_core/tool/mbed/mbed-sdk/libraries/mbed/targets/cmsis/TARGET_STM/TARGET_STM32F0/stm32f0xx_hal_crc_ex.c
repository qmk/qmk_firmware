/**
  ******************************************************************************
  * @file    stm32f0xx_hal_crc_ex.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   Extended CRC HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the CRC peripheral:
  *           + Extended initialization functions
  *         
  @verbatim
================================================================================
          ##### Product specific features  #####
================================================================================
   
            ##### How to use this driver #####
================================================================================
    [..]
         (+) Extended initialization
         (+) Set or not user-defined generating
            polynomial other than default one

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

/** @defgroup CRCEx CRCEx Extended HAL Module Driver 
  * @brief CRC Extended HAL module driver
  * @{
  */

#ifdef HAL_CRC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRCEx_Exported_Functions CRCEx Exported Functions
  * @{
  */

/** @defgroup CRCEx_Exported_Functions_Group1 Extended Initialization/de-initialization functions
  * @brief    Extended Initialization and Configuration functions.
  *
@verbatim    
 ===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRC generating polynomial: if programmable polynomial 
          feature is applicable to device, set default or non-default generating 
          polynomial according to hcrc->Init.DefaultPolynomialUse parameter.
          If feature is non-applicable to device in use, HAL_CRCEx_Init straight 
          away reports HAL_OK.
      (+) Set the generating polynomial
 
@endverbatim
  * @{
  */


/**
  * @brief  Extended initialization to set generating polynomial
  * @param  hcrc: CRC handle             
  * @retval HAL status
  */             
HAL_StatusTypeDef HAL_CRCEx_Init(CRC_HandleTypeDef *hcrc)
{
#if defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined (STM32F098xx)
  /* check whether or not non-default generating polynomial has been 
   * picked up by user */
  assert_param(IS_DEFAULT_POLYNOMIAL(hcrc->Init.DefaultPolynomialUse)); 
  if (hcrc->Init.DefaultPolynomialUse == DEFAULT_POLYNOMIAL_ENABLE)
  {
    /* initialize IP with default generating polynomial */
    WRITE_REG(hcrc->Instance->POL, DEFAULT_CRC32_POLY);  
    MODIFY_REG(hcrc->Instance->CR, CRC_CR_POLYSIZE, CRC_POLYLENGTH_32B);
  }
  else
  {
    /* initialize CRC IP with generating polynomial defined by user */
    if (HAL_CRCEx_Polynomial_Set(hcrc, hcrc->Init.GeneratingPolynomial, hcrc->Init.CRCLength) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }
#endif /* defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined (STM32F098xx) */    

   return HAL_OK;
}

/**
  * @brief  Set the Reverse Input data mode.
  * @param  hcrc: CRC handle
  * @param  InputReverseMode: Input Data inversion mode
  *         This parameter can be one of the following values:
  *          @arg CRC_INPUTDATA_NOINVERSION: no change in bit order (default value)
  *          @arg CRC_INPUTDATA_INVERSION_BYTE: Byte-wise bit reversal
  *          @arg CRC_INPUTDATA_INVERSION_HALFWORD: HalfWord-wise bit reversal
  *          @arg CRC_INPUTDATA_INVERSION_WORD: Word-wise bit reversal              
  * @retval HAL status
  */                                   
HAL_StatusTypeDef HAL_CRCEx_Input_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t InputReverseMode)
{  
  /* Check the parameters */
  assert_param(IS_CRC_INPUTDATA_INVERSION_MODE(InputReverseMode));
  
  /* Change CRC peripheral state */
  hcrc->State = HAL_CRC_STATE_BUSY;

  /* set input data inversion mode */
  MODIFY_REG(hcrc->Instance->CR, CRC_CR_REV_IN, InputReverseMode);    
  /* Change CRC peripheral state */
  hcrc->State = HAL_CRC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set the Reverse Output data mode.
  * @param  hcrc: CRC handle
  * @param  OutputReverseMode: Output Data inversion mode
  *         This parameter can be one of the following values:
  *          @arg CRC_OUTPUTDATA_INVERSION_DISABLED: no CRC inversion (default value)
  *          @arg CRC_OUTPUTDATA_INVERSION_ENABLED: bit-level inversion (e.g for a 8-bit CRC: 0xB5 becomes 0xAD)            
  * @retval HAL status
  */                                   
HAL_StatusTypeDef HAL_CRCEx_Output_Data_Reverse(CRC_HandleTypeDef *hcrc, uint32_t OutputReverseMode)
{
  /* Check the parameters */
  assert_param(IS_CRC_OUTPUTDATA_INVERSION_MODE(OutputReverseMode));
  
  /* Change CRC peripheral state */
  hcrc->State = HAL_CRC_STATE_BUSY;

  /* set output data inversion mode */
  MODIFY_REG(hcrc->Instance->CR, CRC_CR_REV_OUT, OutputReverseMode); 
      
  /* Change CRC peripheral state */
  hcrc->State = HAL_CRC_STATE_READY;
  
  /* Return function status */
  return HAL_OK;
}

#if defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F091xC) || defined (STM32F098xx)
/**
  * @brief  Initializes the CRC polynomial if different from default one.
  * @param  hcrc: CRC handle
  * @param  Pol: CRC generating polynomial (7, 8, 16 or 32-bit long)
  *         This parameter is written in normal representation, e.g.
  *         for a polynomial of degree 7, X^7 + X^6 + X^5 + X^2 + 1 is written 0x65 
  *         for a polynomial of degree 16, X^16 + X^12 + X^5 + 1 is written 0x1021     
  * @param  PolyLength: CRC polynomial length 
  *         This parameter can be one of the following values:
  *          @arg CRC_POLYLENGTH_7B: 7-bit long CRC (generating polynomial of degree 7)
  *          @arg CRC_POLYLENGTH_8B: 8-bit long CRC (generating polynomial of degree 8)
  *          @arg CRC_POLYLENGTH_16B: 16-bit long CRC (generating polynomial of degree 16)
  *          @arg CRC_POLYLENGTH_32B: 32-bit long CRC (generating polynomial of degree 32)                
  * @retval HAL status
  */                                   
HAL_StatusTypeDef HAL_CRCEx_Polynomial_Set(CRC_HandleTypeDef *hcrc, uint32_t Pol, uint32_t PolyLength)
{
  uint32_t msb = 31; /* polynomial degree is 32 at most, so msb is initialized to max value */

  /* Check the parameters */
  assert_param(IS_CRC_POL_LENGTH(PolyLength));
  
  /* check polynomial definition vs polynomial size:
   * polynomial length must be aligned with polynomial
   * definition. HAL_ERROR is reported if Pol degree is 
   * larger than that indicated by PolyLength.
   * Look for MSB position: msb will contain the degree of
   *  the second to the largest polynomial member. E.g., for
   *  X^7 + X^6 + X^5 + X^2 + 1, msb = 6. */
  while (((Pol & (1U << msb)) == 0) && (msb-- > 0))
  {}

  switch (PolyLength)
  {
    case CRC_POLYLENGTH_7B:
      if (msb >= HAL_CRC_LENGTH_7B)
      {
        return  HAL_ERROR;
      }
      break;
    case CRC_POLYLENGTH_8B:
      if (msb >= HAL_CRC_LENGTH_8B)
      { 
        return  HAL_ERROR;
      }
      break;
    case CRC_POLYLENGTH_16B:
      if (msb >= HAL_CRC_LENGTH_16B)
      {
        return  HAL_ERROR;
      }
      break;
    case CRC_POLYLENGTH_32B:
      /* no polynomial definition vs. polynomial length issue possible */
      break;      
    default:
      break;
  }

  /* set generating polynomial */
  WRITE_REG(hcrc->Instance->POL, Pol);
  
  /* set generating polynomial size */
  MODIFY_REG(hcrc->Instance->CR, CRC_CR_POLYSIZE, PolyLength);  
  
  /* Return function status */
  return HAL_OK;
}
#endif /* #if defined (STM32F071xB) || defined (STM32F072xB) || defined (STM32F078xx) || defined (STM32F091xC) || defined (STM32F098xx) */

/**
  * @}
  */


/**
  * @}
  */


#endif /* HAL_CRC_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
