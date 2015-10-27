/**
  ******************************************************************************
  * @file    stm32f1xx_hal_spi_ex.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Extended SPI HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities SPI extension peripheral:
  *           + Extended Peripheral Control functions
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED

/** @defgroup SPI_Private_Variables SPI Private Variables
 * @{
 */
/* Variable used to determine if device is impacted by implementation of workaround
   related to wrong CRC errors detection on SPI2. Conditions in which this workaround has to be applied, are:
    - STM32F101CDE/STM32F103CDE
    - Revision ID : Z
    - SPI2
    - In receive only mode, with CRC calculation enabled, at the end of the CRC reception,
      the software needs to check the CRCERR flag. If it is found set, read back the SPI_RXCRC:
        + If the value is 0, the complete data transfer is successful.
        + Otherwise, one or more errors have been detected during the data transfer by CPU or DMA.
      If CRCERR is found reset, the complete data transfer is considered successful.
*/
uint8_t uCRCErrorWorkaroundCheck = 0;
/**
  * @}
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @addtogroup SPI_Exported_Functions
  * @{
  */

/** @addtogroup SPI_Exported_Functions_Group1
 *
  * @{
  */

/**
  * @brief  Initializes the SPI according to the specified parameters 
  *         in the SPI_InitTypeDef and create the associated handle.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if(hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));
  assert_param(IS_SPI_MODE(hspi->Init.Mode));
  assert_param(IS_SPI_DIRECTION_MODE(hspi->Init.Direction));
  assert_param(IS_SPI_DATASIZE(hspi->Init.DataSize));
  assert_param(IS_SPI_CPOL(hspi->Init.CLKPolarity));
  assert_param(IS_SPI_CPHA(hspi->Init.CLKPhase));
  assert_param(IS_SPI_NSS(hspi->Init.NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(hspi->Init.FirstBit));
  assert_param(IS_SPI_TIMODE(hspi->Init.TIMode));
  assert_param(IS_SPI_CRC_CALCULATION(hspi->Init.CRCCalculation));
  assert_param(IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial));

  if(hspi->State == HAL_SPI_STATE_RESET)
  {
    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_SPI_MspInit(hspi);
  }
  
  hspi->State = HAL_SPI_STATE_BUSY;

  /* Disble the selected SPI peripheral */
  __HAL_SPI_DISABLE(hspi);

  /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
  /* Configure : SPI Mode, Communication Mode, Data size, Clock polarity and phase, NSS management,
  Communication speed, First bit and CRC calculation state */
  WRITE_REG(hspi->Instance->CR1, (hspi->Init.Mode | hspi->Init.Direction | hspi->Init.DataSize |
                                  hspi->Init.CLKPolarity | hspi->Init.CLKPhase | (hspi->Init.NSS & SPI_CR1_SSM) |
                                  hspi->Init.BaudRatePrescaler | hspi->Init.FirstBit  | hspi->Init.CRCCalculation) );

  /* Configure : NSS management */
  WRITE_REG(hspi->Instance->CR2, (((hspi->Init.NSS >> 16) & SPI_CR2_SSOE) | hspi->Init.TIMode));

  /*---------------------------- SPIx CRCPOLY Configuration ------------------*/
  /* Configure : CRC Polynomial */
  WRITE_REG(hspi->Instance->CRCPR, hspi->Init.CRCPolynomial);

#if defined (STM32F101x6) || defined (STM32F101xB) || defined (STM32F101xE) || defined (STM32F101xG) || defined (STM32F102x6) || defined (STM32F102xB) || defined (STM32F103x6) || defined (STM32F103xB) || defined (STM32F103xE) || defined (STM32F103xG) || defined (STM32F105xC) || defined (STM32F107xC)
  /* Activate the SPI mode (Make sure that I2SMOD bit in I2SCFGR register is reset) */
  CLEAR_BIT(hspi->Instance->I2SCFGR, SPI_I2SCFGR_I2SMOD);
#endif

#if defined (STM32F101xE) || defined (STM32F103xE)
  /* Check RevisionID value for identifying if Device is Rev Z (0x0001) in order to enable workaround for
     CRC errors wrongly detected */
  /* Pb is that ES_STM32F10xxCDE also identify an issue in Debug registers access while not in Debug mode.
     Revision ID information is only available in Debug mode, so Workaround could not be implemented
     to distinguish Rev Z devices (issue present) from more recent version (issue fixed).
     So, in case of Revison Z F101 or F103 devices, below variable should be assigned to 1 */
  uCRCErrorWorkaroundCheck = 0;
#else
  uCRCErrorWorkaroundCheck = 0;
#endif

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_READY;
  
  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Checks if encountered CRC error could be corresponding to wrongly detected errors 
  *         according to SPI instance, Device type, and revision ID.
  * @param  hspi: pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval CRC error validity (SPI_INVALID_CRC_ERROR or SPI_VALID_CRC_ERROR).  
*/
uint8_t SPI_ISCRCErrorValid(SPI_HandleTypeDef *hspi)
{
#if defined (STM32F101xE) || defined (STM32F103xE)
  /* Check how to handle this CRC error (workaround to be applied or not) */
  /* If CRC errors could be wrongly detected (issue 2.15.2 in STM32F10xxC/D/E silicon limitations ES (DocID14732 Rev 13) */
  if ( (uCRCErrorWorkaroundCheck != 0) && (hspi->Instance == SPI2) )
  {
    if (hspi->Instance->RXCRCR == 0)
    {
      return (SPI_INVALID_CRC_ERROR);
    }
  }
  return (SPI_VALID_CRC_ERROR);
#else
  return (SPI_VALID_CRC_ERROR);
#endif
}
/**
  * @}
  */

#endif /* HAL_SPI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
