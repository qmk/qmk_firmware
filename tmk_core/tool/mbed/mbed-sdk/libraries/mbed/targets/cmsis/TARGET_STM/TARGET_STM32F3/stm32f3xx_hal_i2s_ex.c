/**
  ******************************************************************************
  * @file    stm32f3xx_hal_i2s_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   I2S Extended HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of I2S Extended peripheral:
  *           + Extended features Functions
  *
  @verbatim
  ==============================================================================
                    ##### I2S Extended features #####
  ============================================================================== 
 [..]
    (#) In I2S full duplex mode, each SPI peripheral is able to manage sending and receiving 
        data simultaneously using two data lines. Each SPI peripheral has an extended block 
        called I2Sxext ie. I2S2ext for SPI2 and I2S3ext for SPI3).
    (#) The Extended block is not a full SPI IP, it is used only as I2S slave to
        implement full duplex mode. The Extended block uses the same clock sources
        as its master (refer to the following Figure).

                +-----------------------+
    I2Sx_SCK    |                       |
  ----------+-->|          I2Sx         |------------------->I2Sx_SD(in/out)
         +--|-->|                       |
        |   |   +-----------------------+
        |   |          
 I2S_WS |   |           
 ------>|   |          
        |   |   +-----------------------+
        |   +-->|                       |
        |       |       I2Sx_ext        |------------------->I2Sx_extSD(in/out)
         +----->|                       |
                +-----------------------+

     (#) Both I2Sx and I2Sx_ext can be configured as transmitters or receivers.

     -@- Only I2Sx can deliver SCK and WS to I2Sx_ext in full duplex mode, where 
         I2Sx can be I2S2 or I2S3.

 ===============================================================================
                  ##### How to use this driver #####
 ===============================================================================
 [..]
   Three mode of operations are available within this driver :     
    
   *** Polling mode IO operation ***
   =================================
   [..]    
     (+) Send and receive in the same time an amount of data in blocking mode using HAL_I2S_TransmitReceive() 
  
   *** Interrupt mode IO operation ***    
   ===================================
   [..]    
     (+) Send and receive in the same time an amount of data in non blocking mode using HAL_I2S_TransmitReceive_IT() 
     (+) At transmission end of half transfer HAL_I2S_TxHalfCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_TxHalfCpltCallback 
     (+) At transmission end of transfer HAL_I2S_TxCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_TxCpltCallback
     (+) At reception end of half transfer HAL_I2S_RxHalfCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_RxHalfCpltCallback 
     (+) At reception end of transfer HAL_I2S_RxCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_RxCpltCallback                                      
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can 
         add his own code by customization of function pointer HAL_I2S_ErrorCallback

   *** DMA mode IO operation ***    
   ==============================
   [..] 
     (+) Send and receive an amount of data in non blocking mode (DMA) using HAL_I2S_TransmitReceive_DMA() 
     (+) At transmission end of half transfer HAL_I2S_TxHalfCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_TxHalfCpltCallback 
     (+) At transmission end of transfer HAL_I2S_TxCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_TxCpltCallback
     (+) At reception end of half transfer HAL_I2S_RxHalfCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_RxHalfCpltCallback 
     (+) At reception end of transfer HAL_I2S_RxCpltCallback is executed and user can 
         add his own code by customization of function pointer HAL_I2S_RxCpltCallback                                     
     (+) In case of transfer Error, HAL_I2S_ErrorCallback() function is executed and user can 
         add his own code by customization of function pointer HAL_I2S_ErrorCallback
     (+) Pause the DMA Transfer using HAL_I2S_DMAPause()      
     (+) Resume the DMA Transfer using HAL_I2S_DMAResume()  
     (+) Stop the DMA Transfer using HAL_I2S_DMAStop()  
  
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
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

#ifdef HAL_I2S_MODULE_ENABLED

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)

/** @defgroup I2SEx I2S Extended HAL module driver
  * @brief I2S Extended HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/** @defgroup I2SEx_Private_Typedef I2S Extended Private Typedef
  * @{
  */
typedef enum
{
  I2S_USE_I2S      = 0x00,   /*!< I2Sx should be used           */
  I2S_USE_I2SEXT   = 0x01    /*!< I2Sx_ext should be used       */   
}I2S_UseTypeDef;
/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup I2SEx_Private_Functions I2S Extended Private Functions
  * @{
  */
static void I2S_TxRxDMACplt(DMA_HandleTypeDef *hdma);
static void I2S_TxRxDMAError(DMA_HandleTypeDef *hdma);
static void I2S_FullDuplexTx_IT(I2S_HandleTypeDef *hi2s, I2S_UseTypeDef i2sUsed);
static void I2S_FullDuplexRx_IT(I2S_HandleTypeDef *hi2s, I2S_UseTypeDef i2sUsed);
static HAL_StatusTypeDef I2S_FullDuplexWaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, 
                                                                 uint32_t State, uint32_t Timeout, I2S_UseTypeDef i2sUsed);
/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

/* Exported functions ---------------------------------------------------------*/

/** @addtogroup I2S I2S HAL module driver
  * @{
  */

/** @addtogroup I2S_Exported_Functions I2S Exported Functions
  * @{
  */

/** @addtogroup  I2S_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization/de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and 
          de-initialiaze the I2Sx peripheral in simplex mode:

      (+) User must Implement HAL_I2S_MspInit() function in which he configures 
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function HAL_I2S_Init() to configure the selected device with 
          the selected configuration:
        (++) Mode
        (++) Standard 
        (++) Data Format
        (++) MCLK Output
        (++) Audio frequency
        (++) Polarity

      (+) Call the function HAL_I2S_DeInit() to restore the default configuration 
          of the selected I2Sx periperal. 
@endverbatim
  * @{
  */

/**
  * @brief Initializes the I2S according to the specified parameters 
  *         in the I2S_InitTypeDef and create the associated handle.
  * @param hi2s: I2S handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0, i2sclk = 0;
#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
  RCC_PeriphCLKInitTypeDef rccperiphclkinit;
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */
  
  /* Check the I2S handle allocation */
  if(hi2s == HAL_NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_I2S_ALL_INSTANCE(hi2s->Instance));
  assert_param(IS_I2S_MODE(hi2s->Init.Mode));
  assert_param(IS_I2S_STANDARD(hi2s->Init.Standard));
  assert_param(IS_I2S_DATA_FORMAT(hi2s->Init.DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(hi2s->Init.MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(hi2s->Init.AudioFreq));
  assert_param(IS_I2S_CPOL(hi2s->Init.CPOL));  
  assert_param(IS_I2S_CLOCKSOURCE(hi2s->Init.ClockSource));
  assert_param(IS_I2S_FULLDUPLEX_MODE(hi2s->Init.FullDuplexMode));
  
  hi2s->State = HAL_I2S_STATE_BUSY;
  
  /* Init the low level hardware : GPIO, CLOCK, CORTEX...etc */
  HAL_I2S_MspInit(hi2s);
  
  /*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  hi2s->Instance->I2SCFGR &= ~(SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CKPOL | \
                               SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
                               SPI_I2SCFGR_I2SE | SPI_I2SCFGR_I2SMOD); 
  hi2s->Instance->I2SPR = 0x0002;
  
  /* Get the I2SCFGR register value */
  tmpreg = hi2s->Instance->I2SCFGR;
  
  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(hi2s->Init.AudioFreq == I2S_AUDIOFREQ_DEFAULT)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;   
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) *******************/
    if(hi2s->Init.DataFormat == I2S_DATAFORMAT_16B)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }
    
    /* Get I2S source Clock frequency  ****************************************/
#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
    rccperiphclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;

    /* If an external I2S clock has to be used, the specific define should be set  
    in the project configuration or in the stm32f3xx_conf.h file */
    if(hi2s->Init.ClockSource == I2S_CLOCK_EXTERNAL)
    {    
      /* Set external clock as I2S clock source */
      rccperiphclkinit.I2sClockSelection = RCC_I2SCLKSOURCE_EXT;
      HAL_RCCEx_PeriphCLKConfig(&rccperiphclkinit);

      /* Set the I2S clock to the external clock  value */
      i2sclk = EXTERNAL_CLOCK_VALUE;
    }
    else
    {
      /* Set SYSCLK as I2S clock source */
      rccperiphclkinit.I2sClockSelection = RCC_I2SCLKSOURCE_SYSCLK;
      HAL_RCCEx_PeriphCLKConfig(&rccperiphclkinit);

      /* Get the I2S source clock value */
      i2sclk = HAL_RCC_GetSysClockFreq();
    }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#if defined (STM32F373xC) || defined (STM32F378xx)
    if(hi2s->Instance == SPI1)
    {
      i2sclk = HAL_RCC_GetPCLK2Freq();
    }
    else if((hi2s->Instance == SPI2) || (hi2s->Instance == SPI3))
    {
      i2sclk = HAL_RCC_GetPCLK1Freq();
    }
#endif /* STM32F373xC || STM32F378xx */
    
    /* Compute the Real divider depending on the MCLK output state, with a floating point */
    if(hi2s->Init.MCLKOutput == I2S_MCLKOUTPUT_ENABLE)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((i2sclk / 256) * 10) / hi2s->Init.AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((i2sclk / (32 * packetlength)) *10 ) / hi2s->Init.AudioFreq)) + 5);
    }
    
    /* Remove the flatting point */
    tmp = tmp / 10;  
    
    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);
    
    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);
    
    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t) (i2sodd << 8);
  }
  
  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }
  
  /* Write to SPIx I2SPR register the computed value */
  hi2s->Instance->I2SPR = (uint16_t)((uint16_t)i2sdiv | (uint16_t)(i2sodd | (uint16_t)hi2s->Init.MCLKOutput));
  
  /* Configure the I2S with the I2S_InitStruct values */
  tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(hi2s->Init.Mode | \
                       (uint16_t)(hi2s->Init.Standard | (uint16_t)(hi2s->Init.DataFormat | \
                       (uint16_t)hi2s->Init.CPOL))));
  
  /* Write to SPIx I2SCFGR */  
  hi2s->Instance->I2SCFGR = tmpreg;
  
#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
  if (hi2s->Init.FullDuplexMode == I2S_FULLDUPLEXMODE_ENABLE)
  {
    /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
    I2SxEXT(hi2s->Instance)->I2SCFGR &= ~(SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CKPOL | \
                                          SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC | SPI_I2SCFGR_I2SCFG | \
                                          SPI_I2SCFGR_I2SE | SPI_I2SCFGR_I2SMOD);
    I2SxEXT(hi2s->Instance)->I2SPR = 0x0002;

    /* Get the I2SCFGR register value */
    tmpreg = I2SxEXT(hi2s->Instance)->I2SCFGR;
    
    /* Get the mode to be configured for the extended I2S */
    if((hi2s->Init.Mode == I2S_MODE_MASTER_TX) || (hi2s->Init.Mode == I2S_MODE_SLAVE_TX))
    {
      tmp = I2S_MODE_SLAVE_RX;
    }
    else
    {
      if((hi2s->Init.Mode == I2S_MODE_MASTER_RX) || (hi2s->Init.Mode == I2S_MODE_SLAVE_RX))
      {
        tmp = I2S_MODE_SLAVE_TX;
      }
    }
    
    /* Configure the I2S Slave with the I2S Master parameter values */
    tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(tmp | \
                         (uint16_t)(hi2s->Init.Standard | (uint16_t)(hi2s->Init.DataFormat | \
                         (uint16_t)hi2s->Init.CPOL))));
    
    /* Write to SPIx I2SCFGR */  
    I2SxEXT(hi2s->Instance)->I2SCFGR = tmpreg;
  }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

  hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
  hi2s->State= HAL_I2S_STATE_READY;
  
  return HAL_OK;
}
/**
  * @}
  */

#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
/** @addtogroup  I2S_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */

/**
  * @brief  This function handles I2S/I2Sext interrupt requests in full-duplex mode.
  * @param  hi2s: I2S handle
  * @retval HAL status
  */
void HAL_I2S_FullDuplex_IRQHandler(I2S_HandleTypeDef *hi2s)
{
  __IO uint32_t i2ssr = hi2s->Instance->SR ;
  __IO uint32_t i2sextsr = I2SxEXT(hi2s->Instance)->SR;

  /* Check if the I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX Mode is selected */
  if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
  {
    /* I2S in mode Transmitter -------------------------------------------------*/
    if(((i2ssr & I2S_FLAG_TXE) == I2S_FLAG_TXE) && (__HAL_I2S_GET_IT_SOURCE(hi2s, I2S_IT_TXE) != RESET))
    {
      /* When the I2S mode is configured as I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX,
      the I2S TXE interrupt will be generated to manage the full-duplex transmit phase. */
      I2S_FullDuplexTx_IT(hi2s, I2S_USE_I2S);
    }

    /* I2Sext in mode Receiver -----------------------------------------------*/
    if(((i2sextsr & I2S_FLAG_RXNE) == I2S_FLAG_RXNE) && (__HAL_I2SEXT_GET_IT_SOURCE(hi2s, I2S_IT_RXNE) != RESET))
    {
      /* When the I2S mode is configured as I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX,
      the I2Sext RXNE interrupt will be generated to manage the full-duplex receive phase. */
      I2S_FullDuplexRx_IT(hi2s, I2S_USE_I2SEXT);
    }

    /* I2Sext Overrun error interrupt occured --------------------------------*/
    if(((i2sextsr & I2S_FLAG_OVR) == I2S_FLAG_OVR) && (__HAL_I2SEXT_GET_IT_SOURCE(hi2s, I2S_IT_ERR) != RESET))
    {
      /* Disable RXNE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      /* Disable TXE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      /* Set the I2S State ready */
      hi2s->State = HAL_I2S_STATE_READY;

      /* Set the error code and execute error callback*/
      hi2s->ErrorCode |= HAL_I2S_ERROR_OVR;
      HAL_I2S_ErrorCallback(hi2s);
    }

    /* I2S Underrun error interrupt occured ----------------------------------*/
    if(((i2ssr & I2S_FLAG_UDR) == I2S_FLAG_UDR) && (__HAL_I2S_GET_IT_SOURCE(hi2s, I2S_IT_ERR) != RESET))
    {
      /* Disable TXE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      /* Disable RXNE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      /* Set the I2S State ready */
      hi2s->State = HAL_I2S_STATE_READY;

      /* Set the error code and execute error callback*/
      hi2s->ErrorCode |= HAL_I2S_ERROR_UDR;
      HAL_I2S_ErrorCallback(hi2s);
    }
  }
  /* The I2S_MODE_MASTER_RX or I2S_MODE_SLAVE_RX Mode is selected */
  else
  {
    /* I2Sext in mode Transmitter ----------------------------------------------*/
    if(((i2sextsr & I2S_FLAG_TXE) == I2S_FLAG_TXE) && (__HAL_I2SEXT_GET_IT_SOURCE(hi2s, I2S_IT_TXE) != RESET))
    {
      /* When the I2S mode is configured as I2S_MODE_MASTER_RX or I2S_MODE_SLAVE_RX,
      the I2Sext TXE interrupt will be generated to manage the full-duplex transmit phase. */
      I2S_FullDuplexTx_IT(hi2s, I2S_USE_I2SEXT);
    }

    /* I2S in mode Receiver --------------------------------------------------*/
    if(((i2ssr & I2S_FLAG_RXNE) == I2S_FLAG_RXNE) && (__HAL_I2S_GET_IT_SOURCE(hi2s, I2S_IT_RXNE) != RESET))
    {
      /* When the I2S mode is configured as I2S_MODE_MASTER_RX or I2S_MODE_SLAVE_RX,
      the I2S RXNE interrupt will be generated to manage the full-duplex receive phase. */
      I2S_FullDuplexRx_IT(hi2s, I2S_USE_I2S);
    }

    /* I2S Overrun error interrupt occured -------------------------------------*/
    if(((i2ssr & I2S_FLAG_OVR) == I2S_FLAG_OVR) && (__HAL_I2S_GET_IT_SOURCE(hi2s, I2S_IT_ERR) != RESET))
    {
      /* Disable RXNE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      /* Disable TXE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      /* Set the I2S State ready */
      hi2s->State = HAL_I2S_STATE_READY;

      /* Set the error code and execute error callback*/
      hi2s->ErrorCode |= HAL_I2S_ERROR_OVR;
      HAL_I2S_ErrorCallback(hi2s);
    }

    /* I2Sext Underrun error interrupt occured -------------------------------*/
    if(((i2sextsr & I2S_FLAG_UDR) == I2S_FLAG_UDR) && (__HAL_I2SEXT_GET_IT_SOURCE(hi2s, I2S_IT_ERR) != RESET))
    {
      /* Disable TXE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      /* Disable RXNE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      /* Set the I2S State ready */
      hi2s->State = HAL_I2S_STATE_READY;

      /* Set the error code and execute error callback*/
      hi2s->ErrorCode |= HAL_I2S_ERROR_UDR;
      HAL_I2S_ErrorCallback(hi2s);
    }
  }
}

/**
  * @brief Tx and Rx Transfer completed callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
__weak void HAL_I2S_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I2S_TxRxCpltCallback could be implenetd in the user file
   */
}

/**
  * @}
  */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

/** @addtogroup I2S_Exported_Functions_Group3 Peripheral State and Errors functions
  *  @brief   Peripheral State functions
  *
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */
/**
  * @brief Pauses the audio stream playing from the Media.
  * @param  hi2s : I2S handle
  * @retval None
  */
HAL_StatusTypeDef HAL_I2S_DMAPause(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_BUSY_TX)
  {
    /* Pause the audio file playing by disabling the I2S DMA request */
    hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_TXDMAEN);
  }
  else if(hi2s->State == HAL_I2S_STATE_BUSY_RX)
  {
    /* Pause the audio file playing by disabling the I2S DMA request */
    hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_RXDMAEN);
  }
#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
  else if(hi2s->State == HAL_I2S_STATE_BUSY_TX_RX)
  {
    /* Pause the audio file playing by disabling the I2S DMA request */
    hi2s->Instance->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));
    I2SxEXT(hi2s->Instance)->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));
  }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief Resumes the audio stream playing from the Media.
  * @param  hi2s : I2S handle
  * @retval None
  */
HAL_StatusTypeDef HAL_I2S_DMAResume(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_BUSY_TX)
  {
    /* Enable the I2S DMA request */
    hi2s->Instance->CR2 |= SPI_CR2_TXDMAEN;
  }
  else if(hi2s->State == HAL_I2S_STATE_BUSY_RX)
  {
    /* Enable the I2S DMA request */
    hi2s->Instance->CR2 |= SPI_CR2_RXDMAEN;
  }
#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
  else if(hi2s->State == HAL_I2S_STATE_BUSY_TX_RX)
  {
    /* Pause the audio file playing by disabling the I2S DMA request */
    hi2s->Instance->CR2 |= (SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);
    I2SxEXT(hi2s->Instance)->CR2 |= (SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);

    /* If the I2Sext peripheral is still not enabled, enable it */
    if ((I2SxEXT(hi2s->Instance)->I2SCFGR & SPI_I2SCFGR_I2SE) == 0)
    {
      /* Enable I2Sext peripheral */
      __HAL_I2SEXT_ENABLE(hi2s);
    }
  }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

  /* If the I2S peripheral is still not enabled, enable it */
  if ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SE) == 0)
  {
    /* Enable I2S peripheral */
    __HAL_I2S_ENABLE(hi2s);
  }

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

  return HAL_OK;
}

/**
  * @brief Resumes the audio stream playing from the Media.
  * @param hi2s: I2S handle
  * @retval None
  */
HAL_StatusTypeDef HAL_I2S_DMAStop(I2S_HandleTypeDef *hi2s)
{
  /* Process Locked */
  __HAL_LOCK(hi2s);

  if(hi2s->State == HAL_I2S_STATE_BUSY_TX)
  {
    /* Disable the I2S DMA requests */
    hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_TXDMAEN);

    /* Disable the I2S DMA Channel */
    HAL_DMA_Abort(hi2s->hdmatx);
  }
  else if(hi2s->State == HAL_I2S_STATE_BUSY_RX)
  {
    /* Disable the I2S DMA requests */
    hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_RXDMAEN);

    /* Disable the I2S DMA Channel */
    HAL_DMA_Abort(hi2s->hdmarx);
  }
#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
  else if(hi2s->State == HAL_I2S_STATE_BUSY_TX_RX)
  {
    /* Disable the I2S DMA requests */
    hi2s->Instance->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));
    I2SxEXT(hi2s->Instance)->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));

    /* Disable the I2S DMA Channels */
    HAL_DMA_Abort(hi2s->hdmatx);
    HAL_DMA_Abort(hi2s->hdmarx);

    /* Disable I2Sext peripheral */
    __HAL_I2SEXT_DISABLE(hi2s);
  }
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

  /* Disable I2S peripheral */
  __HAL_I2S_DISABLE(hi2s);

  hi2s->State = HAL_I2S_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hi2s);

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

#if defined (STM32F302xE) || defined (STM32F303xE) || defined (STM32F398xx) || \
    defined (STM32F302xC) || defined (STM32F303xC) || defined (STM32F358xx)
/** @addtogroup I2SEx I2S Extended HAL module driver
  * @brief I2S Extended HAL module driver
  * @{
  */

/** @defgroup I2SEx_Exported_Functions I2S Extended Exported Functions
  * @{
  */

/** @defgroup I2SEx_Exported_Functions_Group1 Extended features functions 
  *  @brief   Extended features functions
  *
@verbatim   
 ===============================================================================
                       ##### Extended features Functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to manage the I2S data 
    transfers.

    (#) There is two mode of transfer:
       (++) Blocking mode: The communication is performed in the polling mode. 
            The status of all data processing is returned by the same function 
            after finishing transfer.  
       (++) No-Blocking mode: The communication is performed using Interrupts 
            or DMA. These functions return the status of the transfer startup.
            The end of the data processing will be indicated through the 
            dedicated I2S IRQ when using Interrupt mode or the DMA IRQ when 
            using DMA mode.

    (#) Blocking mode functions are :
        (++) HAL_I2S_TransmitReceive()
        
    (#) No-Blocking mode functions with Interrupt are:
        (++) HAL_I2S_TransmitReceive_IT()
        (++) HAL_I2SFullDuplex_IRQHandler()

    (#) No-Blocking mode functions with DMA are:
        (++) HAL_I2S_TransmitReceive_DMA()

    (#) A set of Transfer Complete Callbacks are provided in No_Blocking mode:
        (++) HAL_I2S_TxRxCpltCallback()
        (++) HAL_I2S_TxRxErrorCallback()

@endverbatim
  * @{
  */
     
/**
  * @brief Full-Duplex Transmit/Receive data in blocking mode.
  * @param hi2s: I2S handle
  * @param pTxData: a 16-bit pointer to the Transmit data buffer.
  * @param pRxData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @param Timeout: Timeout duration
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size, uint32_t Timeout)
{
  if((pTxData == HAL_NULL ) || (pRxData == HAL_NULL ) || (Size == 0)) 
  {
    return  HAL_ERROR;                                    
  }
  
  /* Check the I2S State */
  if(hi2s->State == HAL_I2S_STATE_READY)
  {  
    /* Check the Data format: When a 16-bit data frame or a 16-bit data frame extended 
       is selected during the I2S configuration phase, the Size parameter means the number
       of 16-bit data length in the transaction and when a 24-bit data frame or a 32-bit data 
       frame is selected the Size parameter means the number of 16-bit data length. */
    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->TxXferSize = (Size << 1);
      hi2s->TxXferCount = (Size << 1);
      hi2s->RxXferSize = (Size << 1);
      hi2s->RxXferCount = (Size << 1);
    }
    else
    {
      hi2s->TxXferSize = Size;
      hi2s->TxXferCount = Size;
      hi2s->RxXferSize = Size;
      hi2s->RxXferCount = Size;
    }
    
    /* Process Locked */
    __HAL_LOCK(hi2s);
    
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;

    /* Set the I2S State busy TX/RX */
    hi2s->State = HAL_I2S_STATE_BUSY_TX_RX;
    
    /* Check if the I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX Mode is selected */
    if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
    { 
      /* Prepare the First Data before enabling the I2S */
      if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX)
      {
        hi2s->Instance->DR = (*pTxData++);
        hi2s->TxXferCount--;
      }
      
      /* Check if the I2S is already enabled: The I2S is kept enabled at the end of transaction
      to avoid the clock de-synchronization between Master and Slave. */ 
      if((hi2s->Instance->I2SCFGR &SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        /* Enable I2Sext(receiver) before enabling I2Sx peripheral */    
        __HAL_I2SEXT_ENABLE(hi2s);
        
        /* Enable I2Sx peripheral */    
        __HAL_I2S_ENABLE(hi2s);
      }
      
      while(hi2s->RxXferCount > 0)
      {
        /* Wait until TXE flag is set */
        if (I2S_FullDuplexWaitFlagStateUntilTimeout(hi2s, I2S_FLAG_TXE, SET, Timeout, I2S_USE_I2S) != HAL_OK)
        {
          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_TIMEOUT;
          HAL_I2S_ErrorCallback(hi2s);
          return HAL_TIMEOUT;
        }

        if (hi2s->TxXferCount > 0)
        {
          /* Check if an underrun occurs */
          if(__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_UDR) == SET) 
          {
            /* Set the I2S State ready */
            hi2s->State = HAL_I2S_STATE_READY; 

            /* Process Unlocked */
            __HAL_UNLOCK(hi2s);

            /* Set the error code and execute error callback*/
            hi2s->ErrorCode |= HAL_I2S_ERROR_UDR;
            HAL_I2S_ErrorCallback(hi2s);

            return HAL_ERROR;
          }

          hi2s->Instance->DR = (*pTxData++);
          hi2s->TxXferCount--;
        }
        
        /* Wait until RXNE flag is set */
        if (I2S_FullDuplexWaitFlagStateUntilTimeout(hi2s, I2S_FLAG_RXNE, SET, Timeout, I2S_USE_I2SEXT) != HAL_OK)
        {
          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_TIMEOUT;
          HAL_I2S_ErrorCallback(hi2s);
          return HAL_TIMEOUT;
        }

        /* Check if an overrun occurs */
        if(__HAL_I2SEXT_GET_FLAG(hi2s, I2S_FLAG_OVR) == SET) 
        {
          /* Set the I2S State ready */
          hi2s->State = HAL_I2S_STATE_READY; 

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);

          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_OVR;
          HAL_I2S_ErrorCallback(hi2s);
      
          return HAL_ERROR;
        }

        (*pRxData++) = I2SxEXT(hi2s->Instance)->DR;
        hi2s->RxXferCount--;	
      }
    }
    /* The I2S_MODE_MASTER_RX or I2S_MODE_SLAVE_RX Mode is selected */
    else
    {
      /* Prepare the First Data before enabling the I2S */
      I2SxEXT(hi2s->Instance)->DR = (*pTxData++);
      hi2s->TxXferCount--;

      /* Check if the I2S is already enabled */ 
      if((hi2s->Instance->I2SCFGR &SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        /* Enable I2S peripheral before the I2Sext*/    
        __HAL_I2S_ENABLE(hi2s);
        
        /* Enable I2Sext(transmitter) after enabling I2Sx peripheral */    
        __HAL_I2SEXT_ENABLE(hi2s);
      }

      /* Check if Master Receiver mode is selected */
      if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_RX)
      {
        /* Clear the Overrun Flag by a read operation on the SPI_DR register followed by a read
        access to the SPI_SR register. */ 
        __HAL_I2S_CLEAR_OVRFLAG(hi2s);        
      }    
      
      while(hi2s->RxXferCount > 0)
      {
        /* Wait until TXE flag is set */
        if (I2S_FullDuplexWaitFlagStateUntilTimeout(hi2s, I2S_FLAG_TXE, SET, Timeout, I2S_USE_I2SEXT) != HAL_OK)
        {
          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_TIMEOUT;
          HAL_I2S_ErrorCallback(hi2s);
          return HAL_TIMEOUT;
        }

        if (hi2s->TxXferCount > 0)
        {
          /* Check if an underrun occurs */
          if(__HAL_I2SEXT_GET_FLAG(hi2s, I2S_FLAG_UDR) == SET) 
          {
            /* Set the I2S State ready */
            hi2s->State = HAL_I2S_STATE_READY; 

            /* Process Unlocked */
            __HAL_UNLOCK(hi2s);

            /* Set the error code and execute error callback*/
            hi2s->ErrorCode |= HAL_I2S_ERROR_UDR;
            HAL_I2S_ErrorCallback(hi2s);

            return HAL_ERROR;
          }

          I2SxEXT(hi2s->Instance)->DR = (*pTxData++);
          hi2s->TxXferCount--;
        }
        
        /* Wait until RXNE flag is set */
        if (I2S_FullDuplexWaitFlagStateUntilTimeout(hi2s, I2S_FLAG_RXNE, SET, Timeout, I2S_USE_I2S) != HAL_OK)
        {
          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_TIMEOUT;
          HAL_I2S_ErrorCallback(hi2s);
          return HAL_TIMEOUT;
        }

        /* Check if an overrun occurs */
        if(__HAL_I2S_GET_FLAG(hi2s, I2S_FLAG_OVR) == SET) 
        {
          /* Set the I2S State ready */
          hi2s->State = HAL_I2S_STATE_READY; 

          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);

          /* Set the error code and execute error callback*/
          hi2s->ErrorCode |= HAL_I2S_ERROR_OVR;
          HAL_I2S_ErrorCallback(hi2s);

          return HAL_ERROR;
        }

        (*pRxData++) = hi2s->Instance->DR;
        hi2s->RxXferCount--;	
      }
    }
    
    /* Set the I2S State ready */
    hi2s->State = HAL_I2S_STATE_READY; 
    
    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);
    
    return HAL_OK;    
  }
  else
  {
    return HAL_BUSY;
  }
}     

/**
  * @brief Full-Duplex Transmit/Receive data in non-blocking mode using Interrupt 
  * @param hi2s: I2S handle
  * @param pTxData: a 16-bit pointer to the Transmit data buffer.
  * @param pRxData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size)
{
  if(hi2s->State == HAL_I2S_STATE_READY)
  {
    if((pTxData == HAL_NULL ) || (pRxData == HAL_NULL ) || (Size == 0)) 
    {
      return  HAL_ERROR;                                    
    }
    
    hi2s->pTxBuffPtr = pTxData;
    hi2s->pRxBuffPtr = pRxData;
    
    /* Check the Data format: When a 16-bit data frame or a 16-bit data frame extended 
       is selected during the I2S configuration phase, the Size parameter means the number
       of 16-bit data length in the transaction and when a 24-bit data frame or a 32-bit data 
       frame is selected the Size parameter means the number of 16-bit data length. */
    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->TxXferSize = (Size << 1);
      hi2s->TxXferCount = (Size << 1);
      hi2s->RxXferSize = (Size << 1);
      hi2s->RxXferCount = (Size << 1);
    }  
    else
    {
      hi2s->TxXferSize = Size;
      hi2s->TxXferCount = Size;
      hi2s->RxXferSize = Size;
      hi2s->RxXferCount = Size;
    }
    
    /* Process Locked */
    __HAL_LOCK(hi2s);
    
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    hi2s->State = HAL_I2S_STATE_BUSY_TX_RX;
    
    /* Check if the I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX Mode is selected */
    if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
    { 
      /* Enable I2Sext RXNE and ERR interrupts */
      __HAL_I2SEXT_ENABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));
      
      /* Enable I2Sx TXE and ERR interrupts */
      __HAL_I2S_ENABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));
      
      /* Check if the I2S is already enabled */ 
      if((hi2s->Instance->I2SCFGR &SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX)
        {
          /* Prepare the First Data before enabling the I2S */
          if(hi2s->TxXferCount != 0)
          {    
            /* Transmit First data */          
            hi2s->Instance->DR = (*hi2s->pTxBuffPtr++);
            hi2s->TxXferCount--;	

            if(hi2s->TxXferCount == 0)
            {    
              /* Disable TXE and ERR interrupt */
              __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

              if(hi2s->RxXferCount == 0)
              {
                /* Disable I2Sext RXNE and ERR interrupt */
                __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_RXNE| I2S_IT_ERR));

                hi2s->State = HAL_I2S_STATE_READY;
                HAL_I2S_TxRxCpltCallback(hi2s);
              }
            }
          }
        }
        /* Enable I2Sext(receiver) before enabling I2Sx peripheral */    
        __HAL_I2SEXT_ENABLE(hi2s);
        
        /* Enable I2Sx peripheral */    
        __HAL_I2S_ENABLE(hi2s);
      }
    }
    /* The I2S_MODE_MASTER_RX or I2S_MODE_SLAVE_RX Mode is selected */ 
    else
    {
      /* Enable I2Sext TXE and ERR interrupts */
      __HAL_I2SEXT_ENABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));
      
      /* Enable I2Sext RXNE and ERR interrupts */
      __HAL_I2S_ENABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));
      
      /* Check if the I2S is already enabled */ 
      if((hi2s->Instance->I2SCFGR &SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        /* Prepare the First Data before enabling the I2S */
        if(hi2s->TxXferCount != 0)
        {    
          /* Transmit First data */          
          I2SxEXT(hi2s->Instance)->DR = (*hi2s->pTxBuffPtr++);
          hi2s->TxXferCount--;	

          if(hi2s->TxXferCount == 0)
          {    
            /* Disable I2Sext TXE and ERR interrupt */
            __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

            if(hi2s->RxXferCount == 0)
            {
              /* Disable RXNE and ERR interrupt */
              __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE| I2S_IT_ERR));

              hi2s->State = HAL_I2S_STATE_READY;
              HAL_I2S_TxRxCpltCallback(hi2s);
            }
          }
        }
        /* Enable I2Sext(transmitter) after enabling I2Sx peripheral */    
        __HAL_I2SEXT_ENABLE(hi2s);

        /* Enable I2S peripheral */    
        __HAL_I2S_ENABLE(hi2s);
      }
    }  
    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY; 
  }
}

/**
  * @brief Full-Duplex Transmit/Receive data in non-blocking mode using DMA  
  * @param hi2s: I2S handle
  * @param pTxData: a 16-bit pointer to the Transmit data buffer.
  * @param pRxData: a 16-bit pointer to the Receive data buffer.
  * @param Size: number of data sample to be sent:
  * @note When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *       configuration phase, the Size parameter means the number of 16-bit data length 
  *       in the transaction and when a 24-bit data frame or a 32-bit data frame is selected 
  *       the Size parameter means the number of 16-bit data length. 
  * @note The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization 
  *       between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2SEx_TransmitReceive_DMA(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size)
{
  uint32_t *tmp;
    
  if((pTxData == HAL_NULL ) || (pRxData == HAL_NULL ) || (Size == 0)) 
  {
    return  HAL_ERROR;                                    
  }

  if(hi2s->State == HAL_I2S_STATE_READY)
  {    
    hi2s->pTxBuffPtr = pTxData;
    hi2s->pRxBuffPtr = pRxData;
    
    /* Check the Data format: When a 16-bit data frame or a 16-bit data frame extended 
       is selected during the I2S configuration phase, the Size parameter means the number
       of 16-bit data length in the transaction and when a 24-bit data frame or a 32-bit data 
       frame is selected the Size parameter means the number of 16-bit data length. */
    if(((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_24B)||\
      ((hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN)) == I2S_DATAFORMAT_32B))
    {
      hi2s->TxXferSize = (Size << 1);
      hi2s->TxXferCount = (Size << 1);
      hi2s->RxXferSize = (Size << 1);
      hi2s->RxXferCount = (Size << 1);
    }  
    else
    {
      hi2s->TxXferSize = Size;
      hi2s->TxXferCount = Size;
      hi2s->RxXferSize = Size;
      hi2s->RxXferCount = Size;
    }
    
    /* Process Locked */
    __HAL_LOCK(hi2s);
    
    hi2s->ErrorCode = HAL_I2S_ERROR_NONE;
    hi2s->State = HAL_I2S_STATE_BUSY_TX_RX;
    
    /* Set the I2S Rx DMA transfer complete callback */
    hi2s->hdmarx->XferCpltCallback = I2S_TxRxDMACplt;
    
    /* Set the DMA error callback */
    hi2s->hdmarx->XferErrorCallback = I2S_TxRxDMAError;
    
    /* Set the I2S Tx DMA transfer complete callback */
    hi2s->hdmatx->XferCpltCallback = I2S_TxRxDMACplt;
    
    /* Set the DMA error callback */
    hi2s->hdmatx->XferErrorCallback = I2S_TxRxDMAError;
    
    /* Check if the I2S_MODE_MASTER_TX or I2S_MODE_SLAVE_TX Mode is selected */
    if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
    {  
      /* Enable the Rx DMA Channel */
      tmp = (uint32_t*)&pRxData;
      HAL_DMA_Start_IT(hi2s->hdmarx, (uint32_t)&I2SxEXT(hi2s->Instance)->DR, *(uint32_t*)tmp, hi2s->RxXferSize);      
      
      /* Enable Rx DMA Request */  
      I2SxEXT(hi2s->Instance)->CR2 |= SPI_CR2_RXDMAEN;
      
      /* Enable the Tx DMA Channel */
      tmp = (uint32_t*)&pTxData;
      HAL_DMA_Start_IT(hi2s->hdmatx, *(uint32_t*)tmp, (uint32_t)&hi2s->Instance->DR, hi2s->TxXferSize);
      
      /* Enable Tx DMA Request */  
      hi2s->Instance->CR2 |= SPI_CR2_TXDMAEN;

      /* Check if the I2S is already enabled */ 
      if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        /* Enable I2Sext(receiver) before enabling I2Sx peripheral */     
        __HAL_I2SEXT_ENABLE(hi2s);
        
        /* Enable I2S peripheral after the I2Sext*/    
        __HAL_I2S_ENABLE(hi2s);
      }
    }
    else
    {
      /* Check if Master Receiver mode is selected */
      if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_RX)
      {
        /* Clear the Overrun Flag by a read operation on the SPI_DR register followed by a read
        access to the SPI_SR register. */ 
        __HAL_I2S_CLEAR_OVRFLAG(hi2s);        
      }

      /* Enable the Tx DMA Channel */
      tmp = (uint32_t*)&pTxData;
      HAL_DMA_Start_IT(hi2s->hdmatx, *(uint32_t*)tmp, (uint32_t)&I2SxEXT(hi2s->Instance)->DR, hi2s->TxXferSize);

      /* Enable Tx DMA Request */  
      I2SxEXT(hi2s->Instance)->CR2 |= SPI_CR2_TXDMAEN;

      /* Enable the Rx DMA Channel */
      tmp = (uint32_t*)&pRxData;
      HAL_DMA_Start_IT(hi2s->hdmarx, (uint32_t)&hi2s->Instance->DR, *(uint32_t*)tmp, hi2s->RxXferSize);      

      /* Enable Rx DMA Request */  
      hi2s->Instance->CR2 |= SPI_CR2_RXDMAEN;

      /* Check if the I2S is already enabled */ 
      if((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SE) != SPI_I2SCFGR_I2SE)
      {
        /* Enable I2Sext(transmitter) before enabling I2Sx peripheral */    
        __HAL_I2SEXT_ENABLE(hi2s);

        /* Enable I2S peripheral after the I2Sext*/    
        __HAL_I2S_ENABLE(hi2s);
      }
    }
    
    /* Process Unlocked */
    __HAL_UNLOCK(hi2s);
    
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @}
  */

/**
  * @}
  */  

/** @addtogroup I2SEx_Private_Functions I2S Extended Private Functions
  * @{
  */

/**
  * @brief DMA I2S transmit receive process complete callback 
  * @param hdma: DMA handle
  * @retval None
  */
static void I2S_TxRxDMACplt(DMA_HandleTypeDef *hdma)   
{
  I2S_HandleTypeDef* hi2s = ( I2S_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  if (hi2s->hdmarx == hdma)
  {
    /* Disable Rx DMA Request */
    if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
    {
      I2SxEXT(hi2s->Instance)->CR2 &= (uint32_t)(~SPI_CR2_RXDMAEN);
    }
    else
    {
      hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_RXDMAEN);
    }

    hi2s->RxXferCount = 0;

    if (hi2s->TxXferCount == 0)
    {
      hi2s->State = HAL_I2S_STATE_READY;

      HAL_I2S_TxRxCpltCallback(hi2s); 
    }
  }
  
  if (hi2s->hdmatx == hdma)
  {
    /* Disable Tx DMA Request */
    if(((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_MASTER_TX) || ((hi2s->Instance->I2SCFGR & SPI_I2SCFGR_I2SCFG) == I2S_MODE_SLAVE_TX))
    {
      hi2s->Instance->CR2 &= (uint32_t)(~SPI_CR2_TXDMAEN);
    }
    else
    {
      I2SxEXT(hi2s->Instance)->CR2 &= (uint32_t)(~SPI_CR2_TXDMAEN);
    }

    hi2s->TxXferCount = 0;

    if (hi2s->RxXferCount == 0)
    {
      hi2s->State = HAL_I2S_STATE_READY;

      HAL_I2S_TxRxCpltCallback(hi2s); 
    }
  }
}
      
/**
  * @brief DMA I2S communication error callback 
  * @param hdma : DMA handle
  * @retval None
  */
static void I2S_TxRxDMAError(DMA_HandleTypeDef *hdma)   
{
  I2S_HandleTypeDef* hi2s = ( I2S_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Disable Rx and Tx DMA Request */
  hi2s->Instance->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));
  I2SxEXT(hi2s->Instance)->CR2 &= (uint32_t)(~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN));

  hi2s->TxXferCount = 0;
  hi2s->RxXferCount = 0;
  
  hi2s->State= HAL_I2S_STATE_READY;
  
  /* Set the error code and execute error callback*/
  hi2s->ErrorCode |= HAL_I2S_ERROR_DMA;
  HAL_I2S_ErrorCallback(hi2s);
}

/**
  * @brief Full-Duplex IT handler transmit function 
  * @param hi2s: I2S handle
  * @param i2sUsed: indicate if I2Sx or I2Sx_ext is concerned
  * @retval None
  */
static void I2S_FullDuplexTx_IT(I2S_HandleTypeDef *hi2s, I2S_UseTypeDef i2sUsed)
{
  if(i2sUsed == I2S_USE_I2S)
  {
    /* Transmit data */          
    hi2s->Instance->DR = (*hi2s->pTxBuffPtr++);
    hi2s->TxXferCount--;	

    if(hi2s->TxXferCount == 0)
    {    
      /* Disable TXE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      if(hi2s->RxXferCount == 0)
      {
        hi2s->State = HAL_I2S_STATE_READY; 
        HAL_I2S_TxRxCpltCallback(hi2s);
      }
    }
  }
  else
  {
    /* Transmit data */          
    I2SxEXT(hi2s->Instance)->DR = (*hi2s->pTxBuffPtr++);
    hi2s->TxXferCount--;	

    if(hi2s->TxXferCount == 0)
    {    
      /* Disable I2Sext TXE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_TXE | I2S_IT_ERR));

      if(hi2s->RxXferCount == 0)
      {
        hi2s->State = HAL_I2S_STATE_READY; 
        HAL_I2S_TxRxCpltCallback(hi2s);
      }
    }
  }
}

/**
  * @brief Full-Duplex IT handler receive function 
  * @param hi2s: I2S handle
  * @param i2sUsed: indicate if I2Sx or I2Sx_ext is concerned
  * @retval None
  */
static void I2S_FullDuplexRx_IT(I2S_HandleTypeDef *hi2s, I2S_UseTypeDef i2sUsed)
{
  if(i2sUsed == I2S_USE_I2S)
  {
    /* Receive data */
    (*hi2s->pRxBuffPtr++) = hi2s->Instance->DR;
    hi2s->RxXferCount--;

    if(hi2s->RxXferCount == 0)
    {    
      /* Disable RXNE and ERR interrupt */
      __HAL_I2S_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      if(hi2s->TxXferCount == 0)
      {
        hi2s->State = HAL_I2S_STATE_READY; 
        HAL_I2S_TxRxCpltCallback(hi2s);
      }
    }
  }
  else
  {
    /* Receive data */          
    (*hi2s->pRxBuffPtr++) = I2SxEXT(hi2s->Instance)->DR;
    hi2s->RxXferCount--;	

    if(hi2s->RxXferCount == 0)
    {      
      /* Disable I2Sext RXNE and ERR interrupt */
      __HAL_I2SEXT_DISABLE_IT(hi2s, (I2S_IT_RXNE | I2S_IT_ERR));

      if(hi2s->TxXferCount == 0)
      {
        hi2s->State = HAL_I2S_STATE_READY; 
        HAL_I2S_TxRxCpltCallback(hi2s);
      }
    }
  }
}

/**
  * @brief This function handles I2S Communication Timeout.
  * @param hi2s: I2S handle
  * @param Flag: Flag checked
  * @param State: Value of the flag expected
  * @param Timeout: Duration of the timeout
  * @param i2sUsed: I2S instance reference
  * @retval HAL status
  */
static HAL_StatusTypeDef I2S_FullDuplexWaitFlagStateUntilTimeout(I2S_HandleTypeDef *hi2s, uint32_t Flag, 
                                                                 uint32_t State, uint32_t Timeout, I2S_UseTypeDef i2sUsed)
{
  uint32_t tickstart = HAL_GetTick();
     
  if(i2sUsed == I2S_USE_I2S)
  {
    while((__HAL_I2S_GET_FLAG(hi2s, Flag)) != State)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Set the I2S State ready */
          hi2s->State= HAL_I2S_STATE_READY;
    
          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);
      
          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {
    while((__HAL_I2SEXT_GET_FLAG(hi2s, Flag)) != State)
    {
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0) || ((HAL_GetTick()-tickstart) > Timeout))
        {
          /* Set the I2S State ready */
          hi2s->State= HAL_I2S_STATE_READY;
    
          /* Process Unlocked */
          __HAL_UNLOCK(hi2s);
      
          return HAL_TIMEOUT;
        }
      }
    }
  }
  
  return HAL_OK;      
}
/**
  * @}
  */

/**
  * @}
  */  
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx    */

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F373xC || STM32F378xx                   */

#endif /* HAL_I2S_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
