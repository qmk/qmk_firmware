/**
  ******************************************************************************
  * @file    stm32f0xx_hal_spi.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-December-2014
  * @brief   SPI HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the SPI peripheral:
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions 
  *           + Peripheral State functions
  *         
  @verbatim
===============================================================================
            ##### How to use this driver #####
 ===============================================================================
    [..]
    The SPI HAL driver can be used as follows:
  
    (#) Declare a SPI_HandleTypeDef handle structure, for example:
        SPI_HandleTypeDef  hspi; 
  
    (#)Initialize the SPI low level resources by implement the HAL_SPI_MspInit ()API:
        (##) Enable the SPIx interface clock 
        (##) SPI pins configuration
            (+++) Enable the clock for the SPI GPIOs 
            (+++) Configure these SPI pins as alternate function push-pull
        (##) NVIC configuration if you need to use interrupt process
            (+++) Configure the SPIx interrupt priority
            (+++) Enable the NVIC SPI IRQ handle
        (##) DMA Configuration if you need to use DMA process
            (+++) Declare a DMA_HandleTypeDef handle structure for the transmit or receive channel
            (+++) Enable the DMAx interface clock using 
            (+++) Configure the DMA handle parameters 
            (+++) Configure the DMA Tx or Rx channel
            (+++) Associate the initilalized hdma_tx handle to the hspi DMA Tx or Rx handle
            (+++) Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA Tx or Rx channel
  
    (#) Program the Mode, BidirectionalMode , Data size, Baudrate Prescaler, NSS 
        management, Clock polarity and phase, FirstBit and CRC configuration in the hspi Init structure.
  
    (#) Initialize the SPI registers by calling the HAL_SPI_Init() API:
        (++) These APIs configures also the low level Hardware GPIO, CLOCK, CORTEX...etc)
            by calling the customed HAL_SPI_MspInit(&hspi) API.
  
    [..]
    Using the HAL it is not possible to reach all supported SPI frequency with the differents SPI Modes,
    the following table resume the max SPI frequency reached with data size 8bits/16bits:
   +-----------------------------------------------------------------------------------------+
   |         |                | 2Lines Fullduplex  |     2Lines RxOnly  |        1Line       |
   | Process | Tranfert mode  |--------------------|--------------------|--------------------|
   |         |                |  Master  |  Slave  |  Master  |  Slave  |  Master  |  Slave  |
   |=========================================================================================|
   |    T    |     Polling    | Fcpu/32  | Fcpu/32 |    NA    |    NA   |    NA    |   NA    |
   |    X    |----------------|----------|---------|----------|---------|----------|---------|
   |    /    |     Interrupt  | Fcpu/32  | Fcpu/32 |    NA    |    NA   |    NA    |   NA    |
   |    R    |----------------|----------|---------|----------|---------|----------|---------|
   |    X    |       DMA      | Fcpu/32  | Fcpu/16 |    NA    |    NA   |    NA    |   NA    |
   |=========|================|==========|=========|==========|=========|==========|=========|
   |         |     Polling    | Fcpu/32  | Fcpu/16 |  Fcpu/16 | Fcpu/16 |  Fcpu/16 | Fcpu/16 |
   |         |----------------|----------|---------|----------|---------|----------|---------|
   |    R    |     Interrupt  | Fcpu/16  | Fcpu/16 |  Fcpu/16 | Fcpu/16 |  Fcpu/16 | Fcpu/16 |
   |    X    |----------------|----------|---------|----------|---------|----------|---------|
   |         |       DMA      |  Fcpu/4  |  Fcpu/8 |  Fcpu/4  |  Fcpu/4 |  Fcpu/8  | Fcpu/16 |
   |=========|================|==========|=========|==========|=========|==========|=========|
   |         |     Polling    | Fcpu/16  | Fcpu/16 |    NA    |    NA   |  Fcpu/16 | Fcpu/16 |
   |         |----------------|----------|---------|----------|---------|----------|---------|
   |    T    |     Interrupt  | Fcpu/32  | Fcpu/16 |    NA    |    NA   |  Fcpu/16 | Fcpu/16 |
   |    X    |----------------|----------|---------|----------|---------|----------|---------|
   |         |       DMA      |  Fcpu/2  | Fcpu/16 |    NA    |    NA   |  Fcpu/8  | Fcpu/16 |
   +-----------------------------------------------------------------------------------------+
  @note The max SPI frequency depend on SPI data size (4bits, 5bits,..., 8bits,...15bits, 16bits),
        SPI mode(2 Lines fullduplex, 2 lines RxOnly, 1 line TX/RX) and Process mode (Polling, IT, DMA).
  @note
   (#) TX/RX processes are HAL_SPI_TransmitReceive(), HAL_SPI_TransmitReceive_IT() and HAL_SPI_TransmitReceive_DMA()
   (#) RX processes are HAL_SPI_Receive(), HAL_SPI_Receive_IT() and HAL_SPI_Receive_DMA()
   (#) TX processes are HAL_SPI_Transmit(), HAL_SPI_Transmit_IT() and HAL_SPI_Transmit_DMA()
  
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

/** @defgroup SPI SPI HAL module driver
  * @brief SPI HAL module driver
  * @{
  */
#ifdef HAL_SPI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup SPI_Private_Constants SPI Private Constants
  * @{
  */
#define SPI_DEFAULT_TIMEOUT 50
#define SPI_FIFO_SIZE       4
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SPI_Private_Functions SPI Private Functions
  * @{
  */

static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAError(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, uint32_t State, uint32_t Timeout);
static HAL_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State, uint32_t Timeout);
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi);
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup SPI_Exported_Functions SPI Exported Functions
  * @{
  */

/** @defgroup SPI_Exported_Functions_Group1 Initialization/de-initialization functions 
 *  @brief    Initialization and Configuration functions 
 *
@verbatim    
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and 
          de-initialiaze the SPIx peripheral:

      (+) User must Implement HAL_SPI_MspInit() function in which he configures 
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function HAL_SPI_Init() to configure the selected device with 
          the selected configuration:
        (++) Mode
        (++) Direction 
        (++) Data Size
        (++) Clock Polarity and Phase
        (++) NSS Management
        (++) BaudRate Prescaler
        (++) FirstBit
        (++) TIMode
        (++) CRC Calculation
        (++) CRC Polynomial if CRC enabled
        (++) CRC Length, used only with Data8 and Data16  
        (++) FIFO reception threshold

      (+) Call the function HAL_SPI_DeInit() to restore the default configuration 
          of the selected SPIx periperal.       
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the SPI according to the specified parameters 
  *         in the SPI_InitTypeDef and create the associated handle.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  uint32_t frxth;
  
  /* Check the SPI handle allocation */
  if(hspi == NULL)
  { 
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));
  assert_param(IS_SPI_MODE(hspi->Init.Mode));
  assert_param(IS_SPI_DIRECTION(hspi->Init.Direction));
  assert_param(IS_SPI_DATASIZE(hspi->Init.DataSize));
  assert_param(IS_SPI_CPOL(hspi->Init.CLKPolarity));
  assert_param(IS_SPI_CPHA(hspi->Init.CLKPhase));
  assert_param(IS_SPI_NSS(hspi->Init.NSS));
  assert_param(IS_SPI_NSSP(hspi->Init.NSSPMode));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(hspi->Init.FirstBit));
  assert_param(IS_SPI_TIMODE(hspi->Init.TIMode));
  assert_param(IS_SPI_CRC_CALCULATION(hspi->Init.CRCCalculation));
  assert_param(IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial));
  assert_param(IS_SPI_CRC_LENGTH(hspi->Init.CRCLength));
  
  hspi->State = HAL_SPI_STATE_BUSY;
  
  /* Init the low level hardware : GPIO, CLOCK, NVIC... */
  HAL_SPI_MspInit(hspi);
  
  /* Disable the selected SPI peripheral */
  __HAL_SPI_DISABLE(hspi);
  
  /* Align by default the rs fifo threshold on the data size */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    frxth = SPI_RXFIFO_THRESHOLD_HF;
  }
  else
  {
    frxth = SPI_RXFIFO_THRESHOLD_QF;
  }
  
  /* CRC calculation is valid only for 16Bit and 8 Bit */
  if(( hspi->Init.DataSize != SPI_DATASIZE_16BIT ) && ( hspi->Init.DataSize != SPI_DATASIZE_8BIT ))
  {
    /* CRC must be disabled */
    hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  }
  
  /* Align the CRC Length on the data size */
  if( hspi->Init.CRCLength == SPI_CRC_LENGTH_DATASIZE)
  {
    /* CRC Lengtht aligned on the data size : value set by default */
    if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
    {
      hspi->Init.CRCLength = SPI_CRC_LENGTH_16BIT;
    }
    else
    {
      hspi->Init.CRCLength = SPI_CRC_LENGTH_8BIT;
    }
  }
  
  /*---------------------------- SPIx CR1 & CR2 Configuration ------------------------*/
  /* Configure : SPI Mode, Communication Mode, Clock polarity and phase, NSS management,
  Communication speed, First bit, CRC calculation state, CRC Length */
  hspi->Instance->CR1 = (hspi->Init.Mode | hspi->Init.Direction | 
                         hspi->Init.CLKPolarity | hspi->Init.CLKPhase | (hspi->Init.NSS & SPI_CR1_SSM) |
                         hspi->Init.BaudRatePrescaler | hspi->Init.FirstBit  | hspi->Init.CRCCalculation);
  
  if( hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT)
  {
    hspi->Instance->CR1|= SPI_CR1_CRCL;
  }
  
  /* Configure : NSS management */
  /* Configure : Rx Fifo Threshold */
  hspi->Instance->CR2 = (((hspi->Init.NSS >> 16) & SPI_CR2_SSOE) | hspi->Init.TIMode | hspi->Init.NSSPMode |
                         hspi->Init.DataSize ) | frxth;
  
  /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Configure : CRC Polynomial */
  hspi->Instance->CRCPR = hspi->Init.CRCPolynomial;
  
  /* Activate the SPI mode (Make sure that I2SMOD bit in I2SCFGR register is reset) */
  hspi->Instance->I2SCFGR &= (uint16_t)(~SPI_I2SCFGR_I2SMOD);
  
  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State= HAL_SPI_STATE_READY;
  
  return HAL_OK;
}

/**
  * @brief  DeInitializes the SPI peripheral 
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if(hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));
  hspi->State = HAL_SPI_STATE_BUSY;
  
  /* check flag before the SPI disable */
  SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FTLVL, SPI_FTLVL_EMPTY, SPI_DEFAULT_TIMEOUT);
  SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_BSY, RESET, SPI_DEFAULT_TIMEOUT);
  SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, SPI_DEFAULT_TIMEOUT);
  
  /* Disable the SPI Peripheral Clock */
  __HAL_SPI_DISABLE(hspi);
  
  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_SPI_MspDeInit(hspi);
  
  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_RESET;
  
  __HAL_UNLOCK(hspi);
    
  return HAL_OK;
}

/**
  * @brief SPI MSP Init
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
 __weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_MspInit could be implenetd in the user file
   */
}

/**
  * @brief SPI MSP DeInit
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
 __weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_MspDeInit could be implenetd in the user file
   */
}

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions_Group2 I/O operation functions 
 *  @brief   Data transfers functions 
 *
@verbatim   
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================  
    This subsection provides a set of functions allowing to manage the SPI
    data transfers.
      
    [..] The SPI supports master and slave mode : 

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode. 
            The HAL status of all data processing is returned by the same function 
            after finishing transfer.  
       (++) Non Blocking mode: The communication is performed using Interrupts 
           or DMA, These APIs return the HAL status.
           The end of the data processing will be indicated through the 
           dedicated SPI IRQ when using Interrupt mode or the DMA IRQ when 
           using DMA mode.
           The HAL_SPI_TxCpltCallback(), HAL_SPI_RxCpltCallback() and HAL_SPI_TxRxCpltCallback() user callbacks 
           will be executed respectivelly at the end of the transmit or Receive process
           The HAL_SPI_ErrorCallback()user callback will be executed when a communication error is detected

    (#) Blocking mode APIs are :
        (++) HAL_SPI_Transmit()in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_Receive() in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_TransmitReceive() in full duplex mode

    (#) Non Blocking mode APIs with Interrupt are :
        (++) HAL_SPI_Transmit_IT()in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_Receive_IT() in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_TransmitReceive_IT()in full duplex mode
        (++) HAL_SPI_IRQHandler()

    (#) Non Blocking mode functions with DMA are :
        (++) HAL_SPI_Transmit_DMA()in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_Receive_DMA() in 1Line (simplex) and 2Lines (full duplex) mode
        (++) HAL_SPI_TransmitReceie_DMA() in full duplex mode

    (#) A set of Transfer Complete Callbacks are provided in Non Blocking mode:
        (++) HAL_SPI_TxCpltCallback()
        (++) HAL_SPI_RxCpltCallback()
        (++) HAL_SPI_ErrorCallback()
        (++) HAL_SPI_TxRxCpltCallback()

@endverbatim
  * @{
  */

/**
  * @brief  Transmit an amount of data in blocking mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData   : pointer to data buffer
  * @param  Size    : amount of data to be sent
  * @param  Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();
  HAL_StatusTypeDef errorcode = HAL_OK;

  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  if(hspi->State != HAL_SPI_STATE_READY) 
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pData == NULL ) || (Size == 0))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Set the transaction information */  
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t*)NULL;
  hspi->RxXferSize  = 0;
  hspi->RxXferCount = 0;

  /* Configure communication direction : 1Line */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_TX(hspi);
  }

  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }

  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
  
  /* Transmit data in 16 Bit mode */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT) 
  {
    /* Transmit data in 16 Bit mode */
    while (hspi->TxXferCount > 0)
    {
      /* Wait until TXE flag is set to send data */
      if((hspi->Instance->SR & SPI_FLAG_TXE) == SPI_FLAG_TXE)
      {
          hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
          hspi->pTxBuffPtr += sizeof(uint16_t);
          hspi->TxXferCount--;
      }
      else
      {
        /* Timeout management */
        if((Timeout == 0) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout))) 
        {
          errorcode = HAL_TIMEOUT;
          goto error;
        }
      }
    }
  }
  /* Transmit data in 8 Bit mode */
  else
  {
    while (hspi->TxXferCount > 0)
    {
      /* Wait until TXE flag is set to send data */
      if((hspi->Instance->SR & SPI_FLAG_TXE) == SPI_FLAG_TXE)
      {
        if(hspi->TxXferCount > 1)
        {
          /* write on the data register in packaing mode */
          hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
          hspi->pTxBuffPtr += sizeof(uint16_t);
          hspi->TxXferCount -= 2;
        }
        else
        {
          *((__IO uint8_t*)&hspi->Instance->DR) = (*hspi->pTxBuffPtr++);
          hspi->TxXferCount--;    
        }
      }
      else
      {
        /* Timeout management */
        if((Timeout == 0) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout))) 
        {
          errorcode = HAL_TIMEOUT;
          goto error;
        }
      }
    }
  }

  /* Enable CRC Transmission */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
     hspi->Instance->CR1|= SPI_CR1_CRCNEXT;
  }

  /* Clear OVERUN flag in 2 Lines communication mode because received is not read */
  if(hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }
    
  if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {   
    errorcode =  HAL_ERROR;
  }

error:
  hspi->State = HAL_SPI_STATE_READY;
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in blocking mode 
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData   : pointer to data buffer
  * @param  Size    : amount of data to be sent
  * @param  Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  __IO uint16_t tmpreg;
  uint32_t tickstart = HAL_GetTick();
  HAL_StatusTypeDef errorcode = HAL_OK;

  if((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    /* the receive process is not supported in 2Lines direction master mode */
    /* in this case we call the transmitReceive process                     */
    /* Process Locked */
    return HAL_SPI_TransmitReceive(hspi,pData,pData,Size,Timeout);
  }
  
  /* Process Locked */
  __HAL_LOCK(hspi);

  if(hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if((pData == NULL ) || (Size == 0))
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;
  hspi->pTxBuffPtr  = (uint8_t*)NULL;
  hspi->TxXferSize  = 0;
  hspi->TxXferCount = 0;

  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
    /* this is done to handle the CRCNEXT before the latest data */
    hspi->RxXferCount--;
  }

  /* Set the Rx Fido thresold */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* set fiforxthresold according the reception data lenght: 16bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  else
  {
    /* set fiforxthresold according the reception data lenght: 8bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }

  /* Configure communication direction 1Line and enabled SPI if needed */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_RX(hspi);
  }

  /* Check if the SPI is already enabled */
  if((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  if(hspi->Init.DataSize <= SPI_DATASIZE_8BIT)
  {
    /* Transfert loop */
    while(hspi->RxXferCount > 0)
    {
      /* Check the RXNE flag */
      if((hspi->Instance->SR & SPI_FLAG_RXNE) == SPI_FLAG_RXNE)
      {
        /* read the received data */
        (*hspi->pRxBuffPtr++)= *(__IO uint8_t *)&hspi->Instance->DR;
        hspi->RxXferCount--;
      }
      else
      {
        /* Timeout manamgement */
        if((Timeout == 0) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout)))
        {
          errorcode = HAL_TIMEOUT;
          goto error;
        }
      }
    }
  }
  else
  {
    /* Transfert loop */
    while(hspi->RxXferCount > 0)
    {
      /* Check the RXNE flag */
      if((hspi->Instance->SR & SPI_FLAG_RXNE) == SPI_FLAG_RXNE)
      {
        *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;
      }
      else
      {
        /* Timeout mamangement */
        if((Timeout == 0) || ((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout))) 
        {
          errorcode = HAL_TIMEOUT;
          goto error;
        }
      }
    }
  }

  /* Handle the CRC Transmission */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    /* freeze the CRC before the latest data */
    hspi->Instance->CR1|= SPI_CR1_CRCNEXT;
    
    /* Read the latest data */
    if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, Timeout) != HAL_OK)
    {
      errorcode = HAL_TIMEOUT;
      goto error;
    }
    
    /* Receive last data in 16 Bit mode */
    if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
    {
      *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
    }
    /* Receive last data in 8 Bit mode */
    else
    {
      *hspi->pRxBuffPtr = *(__IO uint8_t *)&hspi->Instance->DR;
    }
    
    /* Wait until TXE flag */
    if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, Timeout) != HAL_OK)
    {
      /* Flag Error*/
      hspi->ErrorCode|= HAL_SPI_ERROR_FLAG;
    }
    
    if(hspi->Init.DataSize == SPI_DATASIZE_16BIT)
    {
      tmpreg = hspi->Instance->DR;
      UNUSED(tmpreg);
    }
    else
    {
      tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
      UNUSED(tmpreg);
      if((hspi->Init.DataSize == SPI_DATASIZE_8BIT) && (hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT))
      {
        if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, Timeout) != HAL_OK)
        {
          /* Erreur on the CRC reception */
          hspi->ErrorCode|= HAL_SPI_ERROR_FLAG;
        }
        tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
        UNUSED(tmpreg);
      }
    }
  }
  
  /* Check the end of the transaction */
  if(SPI_EndRxTransaction(hspi,Timeout) != HAL_OK)
  {
    errorcode = HAL_TIMEOUT;
    goto error;
  }
  
  /* Check if CRC error occurred */
  if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
  }
 
  if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }
  
error :
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in blocking mode 
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pTxData : pointer to transmission data buffer
  * @param  pRxData : pointer to reception data buffer to be
  * @param  Size    : amount of data to be sent
  * @param  Timeout : Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
__IO uint16_t tmpreg;
  uint32_t tickstart = HAL_GetTick();
  HAL_StatusTypeDef errorcode = HAL_OK;
  
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));
  assert_param(pTxData != NULL);

  /* Process Locked */
  __HAL_LOCK(hspi);

  if(hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pTxData == NULL) || (pRxData == NULL) || (Size == 0))
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  hspi->State       = HAL_SPI_STATE_BUSY_TX_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = pRxData;
  hspi->RxXferCount = Size;
  hspi->RxXferSize  = Size;
  hspi->pTxBuffPtr  = pTxData;
  hspi->TxXferCount = Size;
  hspi->TxXferSize  = Size; 
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* Set the Rx Fido threshold */
  if((hspi->Init.DataSize > SPI_DATASIZE_8BIT) || (hspi->RxXferCount > 1))
  {
    /* set fiforxthreshold according the reception data lenght: 16bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  else
  {
    /* set fiforxthreshold according the reception data lenght: 8bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }
  
  /* Transmit and Receive data in 16 Bit mode */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {  
    while ((hspi->TxXferCount > 0 ) || (hspi->RxXferCount > 0))
    {
      /* Check TXE flag */
      if((hspi->TxXferCount > 0) && ((hspi->Instance->SR & SPI_FLAG_TXE) == SPI_FLAG_TXE))
      {
        hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint16_t);
        hspi->TxXferCount--;
        
        /* Enable CRC Transmission */
        if((hspi->TxXferCount == 0) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED))
        {
          hspi->Instance->CR1|= SPI_CR1_CRCNEXT;
        } 
      }
      
      /* Check RXNE flag */
      if((hspi->RxXferCount > 0) && ((hspi->Instance->SR & SPI_FLAG_RXNE) == SPI_FLAG_RXNE))
      {
        *((uint16_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;
      }
      if((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout))
      {
        errorcode = HAL_TIMEOUT;
        goto error;
      }
    }  
  }
  /* Transmit and Receive data in 8 Bit mode */
  else
  { 
    while((hspi->TxXferCount > 0) || (hspi->RxXferCount > 0))
    {
      /* check TXE flag */
      if((hspi->TxXferCount > 0) && ((hspi->Instance->SR & SPI_FLAG_TXE) == SPI_FLAG_TXE))
      {
        if(hspi->TxXferCount > 1)
        {
          hspi->Instance->DR = *((uint16_t*)hspi->pTxBuffPtr);
          hspi->pTxBuffPtr += sizeof(uint16_t);
          hspi->TxXferCount -= 2;
        } 
        else
        {
          *(__IO uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr++);
          hspi->TxXferCount--;
        }
        
        /* Enable CRC Transmission */
        if((hspi->TxXferCount == 0) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED))
        {
          hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
        }
      }
            
      /* Wait until RXNE flag is reset */
      if((hspi->RxXferCount > 0) && ((hspi->Instance->SR & SPI_FLAG_RXNE) == SPI_FLAG_RXNE))
      {
        if(hspi->RxXferCount > 1)
        {
          *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
          hspi->pRxBuffPtr += sizeof(uint16_t);
          hspi->RxXferCount -= 2;
          if(hspi->RxXferCount <= 1)
          {
            /* set fiforxthresold before to switch on 8 bit data size */
            SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
          }
        }
        else
        {
          (*hspi->pRxBuffPtr++) =  *(__IO uint8_t *)&hspi->Instance->DR;
          hspi->RxXferCount--;
        }
      }
      if((Timeout != HAL_MAX_DELAY) && ((HAL_GetTick()-tickstart) >=  Timeout))
      {
        errorcode = HAL_TIMEOUT;
        goto error;
      }
    }
  }
  
  /* Read CRC from DR to close CRC calculation process */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    /* Wait until TXE flag */
    if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, Timeout) != HAL_OK)
    {  
      /* Erreur on the CRC reception */
      hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
    }
    
    if(hspi->Init.DataSize == SPI_DATASIZE_16BIT)
    {
      tmpreg = hspi->Instance->DR;
      UNUSED(tmpreg);
    }
    else
    {
      tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
      UNUSED(tmpreg);
      if(hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT)
      {
        if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, Timeout) != HAL_OK) 
        {  
          /* Erreur on the CRC reception */
          hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
        }    
        tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
        UNUSED(tmpreg);
      }
    }
  }

  /* Check if CRC error occurred */
  if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
    /* Clear CRC Flag */
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    
    errorcode = HAL_ERROR;
  }
  
  if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {   
    errorcode = HAL_ERROR;
  }

error : 
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit an amount of data in no-blocking mode with Interrupt
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData : pointer to data buffer
  * @param  Size : amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));
  
  /* Process Locked */
  __HAL_LOCK(hspi);

  if((pData == NULL) || (Size == 0)) 
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  if(hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }
 
  /* prepore the transfer */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t*)NULL;
  hspi->RxXferSize  = 0;
  hspi->RxXferCount = 0;
  hspi->RxISR = (void (*)(SPI_HandleTypeDef *))NULL;
  
  /* Set the function for IT treatement */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT )
  {
    hspi->TxISR = SPI_TxISR_16BIT;
  }
  else
  {
    hspi->TxISR = SPI_TxISR_8BIT;
  }
  
  /* Configure communication direction : 1Line */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_TX(hspi);
  }
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);    
  }
  
  /* Enable TXE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi,(SPI_IT_TXE));
  
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }
  
error :
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in no-blocking mode with Interrupt
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData : pointer to data buffer
  * @param  Size : amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;
  
  /* Process Locked */
  __HAL_LOCK(hspi);
  
  if(hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  if((pData == NULL) || (Size == 0))
  { 
    errorcode = HAL_ERROR;
    goto error;
  }
  
  /* Configure communication */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;
  hspi->pTxBuffPtr  = (uint8_t*)NULL;
  hspi->TxXferSize  = 0;
  hspi->TxXferCount = 0;
  
  if((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hspi);
    /* the receive process is not supported in 2Lines direction master mode */
    /* in this we call the transmitReceive process          */
    return HAL_SPI_TransmitReceive_IT(hspi,pData,pData,Size);
  }
  
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    hspi->CRCSize = 1;
    if((hspi->Init.DataSize <= SPI_DATASIZE_8BIT) && (hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT))
    {
      hspi->CRCSize = 2;
    }
  }
  else
  {
    hspi->CRCSize = 0;
  }
  
  hspi->TxISR = (void (*)(SPI_HandleTypeDef *))NULL;
  /* check the data size to adapt Rx threshold and the set the function for IT treatement */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT )
  {
    /* set fiforxthresold according the reception data lenght: 16 bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
    hspi->RxISR = SPI_RxISR_16BIT;
  }
  else
  {
    /* set fiforxthresold according the reception data lenght: 8 bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
    hspi->RxISR = SPI_RxISR_8BIT;
  }
  
  /* Configure communication direction : 1Line */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_RX(hspi);
  }
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* Enable TXE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }
  
error :
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in no-blocking mode with Interrupt 
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pTxData : pointer to transmission data buffer
  * @param  pRxData : pointer to reception data buffer to be
  * @param  Size : amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));
  
  /* Process locked */
  __HAL_LOCK(hspi);
  
  if(!((hspi->State == HAL_SPI_STATE_READY) || \
    ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->State == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pTxData == NULL ) || (pRxData == NULL ) || (Size == 0)) 
  {
    errorcode = HAL_ERROR;                                    
    goto error;
  }
  
  hspi->CRCSize = 0;
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    hspi->CRCSize = 1;
    if((hspi->Init.DataSize <= SPI_DATASIZE_8BIT) && (hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT))
    {
      hspi->CRCSize = 2;
    }
  }
  
  if(hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }
  
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;
  
  /* Set the function for IT treatement */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT )
  {
    hspi->RxISR = SPI_2linesRxISR_16BIT;
    hspi->TxISR = SPI_2linesTxISR_16BIT;       
  }
  else
  {
    hspi->RxISR = SPI_2linesRxISR_8BIT;
    hspi->TxISR = SPI_2linesTxISR_8BIT;
  }
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* check if packing mode is enabled and if there is more than 2 data to receive */
  if((hspi->Init.DataSize > SPI_DATASIZE_8BIT) || (hspi->RxXferCount >= 2))
  {
    /* set fiforxthresold according the reception data lenght: 16 bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  else
  {
    /* set fiforxthresold according the reception data lenght: 8 bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  
  /* Enable TXE, RXNE and ERR interrupt */
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }
  
error :
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit an amount of data in no-blocking mode with DMA
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pData : pointer to data buffer
  * @param  Size : amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{    
  HAL_StatusTypeDef errorcode = HAL_OK;
  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));
  
  /* Process Locked */
  __HAL_LOCK(hspi);
  
  if(hspi->State != HAL_SPI_STATE_READY) 
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pData == NULL) || (Size == 0))
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t*)NULL;
  hspi->RxXferSize  = 0;
  hspi->RxXferCount = 0;
  
  /* Configure communication direction : 1Line */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_TX(hspi);
  }
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* Set the SPI TxDMA Half transfer complete callback */
  hspi->hdmatx->XferHalfCpltCallback = SPI_DMAHalfTransmitCplt;
  
  /* Set the SPI TxDMA transfert complete callback */
  hspi->hdmatx->XferCpltCallback = SPI_DMATransmitCplt;
  
  /* Set the DMA error callback */
  hspi->hdmatx->XferErrorCallback = SPI_DMAError;
  
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX);
  /* packing mode is enabled only if the DMA setting is HALWORD */
  if((hspi->Init.DataSize <= SPI_DATASIZE_8BIT) && (hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD))
  {
    /* Check the even/odd of the data size + crc if enabled */
    if((hspi->TxXferCount & 0x1) == 0)
    {
      CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX);
      hspi->TxXferCount = (hspi->TxXferCount >> 1);
    }
    else
    {
      SET_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX);
      hspi->TxXferCount = (hspi->TxXferCount >> 1) + 1;
    }
  }
  
  /* Enable the Tx DMA channel */
  HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->DR, hspi->TxXferCount);
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }

  /* Enable Tx DMA Request */
  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);
  
error :  
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
 * @brief  Receive an amount of data in no-blocking mode with DMA 
 * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
 *                the configuration information for SPI module.
 * @param  pData : pointer to data buffer
 * @param  Size : amount of data to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;
  
  /* Process Locked */
  __HAL_LOCK(hspi);
  
  if(hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pData == NULL) || (Size == 0))
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;
  hspi->pTxBuffPtr  = (uint8_t*)NULL;
  hspi->TxXferSize  = 0;
  hspi->TxXferCount = 0;
  
  if((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    /* Process Unlocked */
    __HAL_UNLOCK(hspi); 
    /* the receive process is not supported in 2Lines direction master mode */
    /* in this case we call the transmitReceive process                     */
    return HAL_SPI_TransmitReceive_DMA(hspi,pData,pData,Size);
  }
  
  /* Configure communication direction : 1Line */
  if(hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    __HAL_SPI_1LINE_RX(hspi);
  }
  
  /* Reset CRC Calculation */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* packing mode management is enabled by the DMA settings */
  if((hspi->Init.DataSize <= SPI_DATASIZE_8BIT) && (hspi->hdmarx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD))
  {
    /* Restriction the DMA data received is not allowed in this mode */
    errorcode = HAL_ERROR;
    goto error;
  }
  
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMARX);
  if( hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* set fiforxthresold according the reception data lenght: 16bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  else
  {
    /* set fiforxthresold according the reception data lenght: 8bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  
  /* Set the SPI RxDMA Half transfer complete callback */
  hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
  
  /* Set the SPI Rx DMA transfert complete callback */
  hspi->hdmarx->XferCpltCallback = SPI_DMAReceiveCplt;
  
  /* Set the DMA error callback */
  hspi->hdmarx->XferErrorCallback = SPI_DMAError;
  
  /* Enable Rx DMA Request */  
  SET_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);
  
  /* Enable the Rx DMA channel */
  HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->DR, (uint32_t)hspi->pRxBuffPtr, hspi->RxXferCount);
  
  /* Check if the SPI is already enabled */ 
  if((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */    
    __HAL_SPI_ENABLE(hspi);
  }
  
error:
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);  
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in no-blocking mode with DMA 
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param  pTxData : pointer to transmission data buffer
  * @param  pRxData : pointer to reception data buffer
  * @param  Size : amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;
  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));
  
  /* Process locked */
  __HAL_LOCK(hspi);
  
  if(!((hspi->State == HAL_SPI_STATE_READY) ||
      ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->State == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    goto error;
  }
  
  if((pTxData == NULL ) || (pRxData == NULL ) || (Size == 0)) 
  {
    errorcode = HAL_ERROR;
    goto error;
  }
  
  /* check if the transmit Receive function is not called by a receive master */
  if(hspi->State != HAL_SPI_STATE_BUSY_RX)
  {  
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }
  
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;
  
  /* Reset CRC Calculation + increase the rxsize */
  if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
  {
    __HAL_SPI_RESET_CRC(hspi);
  }
  
  /* Reset the threshold bit */
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX | SPI_CR2_LDMARX);
  
  /* the packing mode management is enabled by the DMA settings according the spi data size */
  if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    /* set fiforxthreshold according the reception data lenght: 16bit */
    CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
  }
  else
  {
    /* set fiforxthresold according the reception data lenght: 8bit */
    SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
    
    if(hspi->hdmatx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD)
    {
      if((hspi->TxXferSize & 0x1) == 0x0)
      {
        CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX);
        hspi->TxXferCount = hspi->TxXferCount >> 1;
      }
      else
      {
        SET_BIT(hspi->Instance->CR2, SPI_CR2_LDMATX);
        hspi->TxXferCount = (hspi->TxXferCount >> 1) + 1;
      }
    }
    
    if(hspi->hdmarx->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD)
    {
      /* set fiforxthresold according the reception data lenght: 16bit */
      CLEAR_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);
      
      if((hspi->RxXferCount & 0x1) == 0x0 )
      {
        CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_LDMARX);
        hspi->RxXferCount = hspi->RxXferCount >> 1;
      }
      else
      {
        SET_BIT(hspi->Instance->CR2, SPI_CR2_LDMARX);
        hspi->RxXferCount = (hspi->RxXferCount >> 1) + 1;
      }
    }
  }
  
  /* Set the SPI Rx DMA transfer complete callback if the transfer request is a
     reception request (RXNE) */
  if(hspi->State == HAL_SPI_STATE_BUSY_RX)
  {
    /* Set the SPI Rx DMA Half transfer complete callback */
    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
    hspi->hdmarx->XferCpltCallback = SPI_DMAReceiveCplt;
  }
  else
  {
    /* Set the SPI Rx DMA Half transfer complete callback */
    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
    hspi->hdmarx->XferCpltCallback = SPI_DMATransmitReceiveCplt;
  }
  
  /* Set the DMA error callback */
  hspi->hdmarx->XferErrorCallback = SPI_DMAError;
  
  /* Enable Rx DMA Request */  
  SET_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);
  
  /* Enable the Rx DMA channel */
  HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->DR, (uint32_t) hspi->pRxBuffPtr, hspi->RxXferCount);
  
  /* Set the SPI Tx DMA transfer complete callback as NULL because the communication closing
  is performed in DMA reception complete callback  */
  hspi->hdmatx->XferCpltCallback = (void (*)(DMA_HandleTypeDef *))NULL;
  
  /* Set the DMA error callback */
  hspi->hdmatx->XferErrorCallback = SPI_DMAError;
  
  /* Enable the Tx DMA channel */
  HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->DR, hspi->TxXferCount);
  
  /* Check if the SPI is already enabled */
  if((hspi->Instance->CR1 &SPI_CR1_SPE) != SPI_CR1_SPE)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
  
  /* Enable Tx DMA Request */
  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);
  
error :   
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief Pauses the DMA Transfer.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi)
{
  /* Process Locked */
  __HAL_LOCK(hspi);
  
  /* Disable the SPI DMA Tx & Rx requests */
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  
  return HAL_OK; 
}

/**
  * @brief Resumes the DMA Transfer.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi)
{
  /* Process Locked */
  __HAL_LOCK(hspi);
  
  /* Enable the SPI DMA Tx & Rx requests */
  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  
  return HAL_OK;
}

/**
  * @brief Stops the DMA Transfer.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi)
{
  /* The Lock is not implemented on this API to allow the user application
     to call the HAL SPI API under callbacks HAL_SPI_TxCpltCallback() or HAL_SPI_RxCpltCallback() or HAL_SPI_TxRxCpltCallback():
     when calling HAL_DMA_Abort() API the DMA TX/RX Transfer complete interrupt is generated
     and the correspond call back is executed HAL_SPI_TxCpltCallback() or HAL_SPI_RxCpltCallback() or HAL_SPI_TxRxCpltCallback()
     */
  
  /* Abort the SPI DMA tx channel */
  if(hspi->hdmatx != NULL)
  {
    HAL_DMA_Abort(hspi->hdmatx);
  }
  /* Abort the SPI DMA rx channel */
  if(hspi->hdmarx != NULL)
  {
    HAL_DMA_Abort(hspi->hdmarx);
  }
  
  /* Disable the SPI DMA Tx & Rx requests */
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  hspi->State = HAL_SPI_STATE_READY;
  return HAL_OK;
}

/**
  * @brief  This function handles SPI interrupt request.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval None.
  */
void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
  uint32_t itsource = hspi->Instance->CR2;
  uint32_t itflag   = hspi->Instance->SR;
  
  /* SPI in mode Receiver ----------------------------------------------------*/
  if(((itflag & SPI_FLAG_OVR) == RESET) &&
     ((itflag & SPI_FLAG_RXNE) != RESET) && ((itsource & SPI_IT_RXNE) != RESET))
  {
    hspi->RxISR(hspi);
    return;
  }
  
  /* SPI in mode Tramitter ---------------------------------------------------*/
  if(((itflag & SPI_FLAG_TXE) != RESET) && ((itsource & SPI_IT_TXE) != RESET))
  {   
    hspi->TxISR(hspi);
    return;
  }
  
  /* SPI in Erreur Treatment ---------------------------------------------------*/
  if((itflag & (SPI_FLAG_MODF | SPI_FLAG_OVR | SPI_FLAG_FRE)) != RESET)  
  {
    /* SPI Overrun error interrupt occured -------------------------------------*/
    if((itflag & SPI_FLAG_OVR) != RESET)
    {
      if(hspi->State != HAL_SPI_STATE_BUSY_TX)
      {
        hspi->ErrorCode |= HAL_SPI_ERROR_OVR;
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
      }
      else
      {
        return;
      }
    }
    
    /* SPI Mode Fault error interrupt occured -------------------------------------*/
    if((itflag & SPI_FLAG_MODF) != RESET)
    { 
      hspi->ErrorCode |= HAL_SPI_ERROR_MODF;
      __HAL_SPI_CLEAR_MODFFLAG(hspi);
    }
    
    /* SPI Frame error interrupt occured ----------------------------------------*/
    if((itflag & SPI_FLAG_FRE) != RESET)
    { 
      hspi->ErrorCode |= HAL_SPI_ERROR_FRE;
      __HAL_SPI_CLEAR_FREFLAG(hspi);
    }
    
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE | SPI_IT_TXE | SPI_IT_ERR);
    hspi->State = HAL_SPI_STATE_READY;
    HAL_SPI_ErrorCallback(hspi);
    return;
  }
}

/**
  * @brief Flush the RX fifo.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_FlushRxFifo(SPI_HandleTypeDef *hspi)
{
  __IO uint32_t tmpreg;
  uint8_t  count = 0;
  while((hspi->Instance->SR & SPI_FLAG_FRLVL) !=  SPI_FRLVL_EMPTY)
  {
    count++;
    tmpreg = hspi->Instance->DR;
    UNUSED(tmpreg);
    if(count == SPI_FIFO_SIZE)
    {
      return HAL_TIMEOUT;
    }
  };
  return HAL_OK;
}

/**
  * @brief Tx Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_TxCpltCallback could be implenetd in the user file
   */ 
}

/**
  * @brief Rx Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_RxCpltCallback could be implenetd in the user file
   */
}
  
/**
  * @brief Tx and Rx Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_TxRxCpltCallback could be implenetd in the user file
   */
}

/**
  * @brief Tx Half Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_TxHalfCpltCallback could be implenetd in the user file
   */
}

/**
  * @brief Rx Half Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_RxHalfCpltCallback() could be implenetd in the user file
   */
}

/**
  * @brief Tx and Rx Transfer completed callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
__weak void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_TxRxHalfCpltCallback() could be implenetd in the user file
   */
}

/**
  * @brief SPI error callbacks
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
 __weak void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SPI_ErrorCallback could be implenetd in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions_Group3 Peripheral Control functions 
  * @brief   SPI control functions 
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================  
    [..]
    This subsection provides a set of functions allowing to control the SPI.
     (+) HAL_SPI_GetState() API can be helpful to check in run-time the state of the SPI peripheral. 
     (+) HAL_SPI_GetError() check in run-time Errors occurring during communication
@endverbatim
  * @{
  */

/**
  * @brief  Return the SPI state
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval SPI state
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(SPI_HandleTypeDef *hspi)
{
  return hspi->State;
}

/**
  * @brief  Return the SPI error code
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval SPI Error Code
  */
uint32_t HAL_SPI_GetError(SPI_HandleTypeDef *hspi)
{
  return hspi->ErrorCode;
}

/**
  * @}
  */


/**
  * @}
  */

/** @addtogroup SPI_Private_Functions SPI Private Functions
 *  @brief   Data transfers Private functions 
  * @{
  */

/**
  * @brief DMA SPI transmit process complete callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma) 
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  if((hdma->Instance->CCR & DMA_CCR_CIRC) != DMA_CCR_CIRC)
  {
    /* Disable Tx DMA Request */
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);
    
    /* Clear OVERUN flag in 2 Lines communication mode because received data is not read */
    if(hspi->Init.Direction == SPI_DIRECTION_2LINES)
    {
      __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }
    
    hspi->TxXferCount = 0;
    hspi->State = HAL_SPI_STATE_READY;
    
    if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_TxCpltCallback(hspi);
}

/**
  * @brief DMA SPI receive process complete callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma)   
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  if((hdma->Instance->CCR & DMA_CCR_CIRC) != DMA_CCR_CIRC)
  {
    __IO uint16_t tmpreg;
    
    /* CRC handling */
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      /* Wait until TXE flag */
      if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, SPI_DEFAULT_TIMEOUT) != HAL_OK)
      {
        /* Erreur on the CRC reception */
        hspi->ErrorCode|= HAL_SPI_ERROR_CRC;      
      }
      if(hspi->Init.DataSize > SPI_DATASIZE_8BIT)
      {        
        tmpreg = hspi->Instance->DR;
        UNUSED(tmpreg);
      }
      else
      {
        tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
        UNUSED(tmpreg);
        if(hspi->Init.CRCLength == SPI_CRC_LENGTH_16BIT)
        {
          if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SPI_FLAG_RXNE, SPI_DEFAULT_TIMEOUT) != HAL_OK)
          {
            /* Erreur on the CRC reception */
            hspi->ErrorCode|= HAL_SPI_ERROR_CRC;      
          }
          tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
          UNUSED(tmpreg);
        }
      }
    }
    
    /* Disable Rx/Tx DMA Request (done by default to handle the case master rx direction 2 lines) */
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

    /* Check the end of the transaction */
    SPI_EndRxTransaction(hspi,SPI_DEFAULT_TIMEOUT);
    
    hspi->RxXferCount = 0;
    hspi->State = HAL_SPI_STATE_READY;
    
    /* Check if CRC error occurred */
    if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
    {
      hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
    
    if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_RxCpltCallback(hspi);
}

/**
  * @brief DMA SPI transmit receive process complete callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma)   
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  if((hdma->Instance->CCR & DMA_CCR_CIRC) != DMA_CCR_CIRC)
  {
    __IO int16_t tmpreg;
    /* CRC handling */
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      if((hspi->Init.DataSize == SPI_DATASIZE_8BIT) && (hspi->Init.CRCLength == SPI_CRC_LENGTH_8BIT))
      {        
        if(SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_QUARTER_FULL, SPI_DEFAULT_TIMEOUT) != HAL_OK)
        {
          /* Erreur on the CRC reception */
          hspi->ErrorCode|= HAL_SPI_ERROR_CRC;      
        }
        tmpreg = *(__IO uint8_t *)&hspi->Instance->DR;
        UNUSED(tmpreg);
      }
      else
      {
        if(SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_HALF_FULL, SPI_DEFAULT_TIMEOUT) != HAL_OK)
        {
          /* Erreur on the CRC reception */
          hspi->ErrorCode|= HAL_SPI_ERROR_CRC;      
        }
        tmpreg = hspi->Instance->DR;
        UNUSED(tmpreg);
      }
    }  
    
    /* Disable Rx/Tx DMA Request */
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

    
    hspi->TxXferCount = 0;
    hspi->RxXferCount = 0;
    hspi->State = HAL_SPI_STATE_READY;
    
    /* Check if CRC error occurred */
    if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
    {
      hspi->ErrorCode = HAL_SPI_ERROR_CRC;
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
    
    if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
      HAL_SPI_ErrorCallback(hspi);
      return;
    }
  }
  HAL_SPI_TxRxCpltCallback(hspi);
}

/**
  * @brief DMA SPI half transmit process complete callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  HAL_SPI_TxHalfCpltCallback(hspi);
}

/**
  * @brief DMA SPI half receive process complete callback 
  * @param  hdma: pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  HAL_SPI_RxHalfCpltCallback(hspi);
}

/**
  * @brief DMA SPI Half transmit receive process complete callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma)   
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;

  HAL_SPI_TxRxHalfCpltCallback(hspi);
}

/**
  * @brief DMA SPI communication error callback 
  * @param  hdma : pointer to a DMA_HandleTypeDef structure that contains
  *                the configuration information for the specified DMA module.
  * @retval None.
  */
static void SPI_DMAError(DMA_HandleTypeDef *hdma)   
{
  SPI_HandleTypeDef* hspi = ( SPI_HandleTypeDef* )((DMA_HandleTypeDef* )hdma)->Parent;
  
  /* Stop the disable DMA transfer on SPI side */
  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
 
  hspi->ErrorCode|= HAL_SPI_ERROR_DMA;
  hspi->State = HAL_SPI_STATE_READY;
  HAL_SPI_ErrorCallback(hspi);
}

/**
  * @brief  Rx Handler for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in packing mode */
  if(hspi->RxXferCount > 1)
  {
    *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
    hspi->pRxBuffPtr += sizeof(uint16_t);
    hspi->RxXferCount -= 2;
    if(hspi->RxXferCount == 1)
    {
      /* set fiforxthresold according the reception data lenght: 8bit */
      SET_BIT(hspi->Instance->CR2, SPI_RXFIFO_THRESHOLD);      
    }    
  }
  /* Receive data in 8 Bit mode */
  else
  {
    *hspi->pRxBuffPtr++ = *((__IO uint8_t *)&hspi->Instance->DR);
    hspi->RxXferCount--;
  }
  
  /* check end of the reception */
  if(hspi->RxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->RxISR =  SPI_2linesRxISR_8BITCRC; 
      return;
    }
        
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE); 
    
    if(hspi->TxXferCount == 0)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Rx Handler for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesRxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint8_t tmpreg = *((__IO uint8_t *)&hspi->Instance->DR);
  UNUSED(tmpreg);
  hspi->CRCSize--;
  
  /* check end of the reception */
  if(hspi->CRCSize == 0)
  {
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE); 
    
    if(hspi->TxXferCount == 0)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Tx Handler for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in packing Bit mode */
  if(hspi->TxXferCount >= 2)
  {
    hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
    hspi->pTxBuffPtr += sizeof(uint16_t);
    hspi->TxXferCount -= 2;
  }
  /* Transmit data in 8 Bit mode */
  else
  {        
    *(__IO uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr++);
    hspi->TxXferCount--;
  }
  
  /* check the end of the transmission */
  if(hspi->TxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
    }
    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);
    
    if(hspi->RxXferCount == 0)
    { 
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Rx 16Bit Handler for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 16 Bit mode */
  *((uint16_t*)hspi->pRxBuffPtr) = hspi->Instance->DR;
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;	
  
  if(hspi->RxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->RxISR =  SPI_2linesRxISR_16BITCRC; 
      return;
    }
    
    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE); 
    
    if(hspi->TxXferCount == 0)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Manage the CRC 16bit receive for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesRxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 16 Bit mode */
  __IO uint16_t tmpreg = hspi->Instance->DR;
  UNUSED(tmpreg);
    
  /* Disable RXNE interrupt */
  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE); 
  
  SPI_CloseRxTx_ISR(hspi);
}

/**
  * @brief  Tx Handler for Transmit and Receive in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;
  
  /* Enable CRC Transmission */
  if(hspi->TxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
    }
    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);
    
    if(hspi->RxXferCount == 0)
    { 
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Manage the CRC receive in Interrupt context
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_RxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint8_t tmpreg = *((uint8_t*)&hspi->Instance->DR);
  UNUSED(tmpreg);
  hspi->CRCSize--;
  
  if(hspi->CRCSize == 0)
  { 
    SPI_CloseRx_ISR(hspi);
  }
}

/**
  * @brief  Manage the recieve in Interrupt context
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *hspi->pRxBuffPtr++ = (*(__IO uint8_t *)&hspi->Instance->DR);
  hspi->RxXferCount--;
  
  /* Enable CRC Transmission */
  if((hspi->RxXferCount == 1) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)) 
  {
    hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
  }
  
  if(hspi->RxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->RxISR =  SPI_RxISR_8BITCRC; 
      return;
    }
    SPI_CloseRx_ISR(hspi);
  }
}

/**
  * @brief  Manage the CRC 16bit recieve in Interrupt context
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_RxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint16_t tmpreg;
  
  tmpreg = hspi->Instance->DR;
  UNUSED(tmpreg);
  
  /* Disable RXNE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));
  
  SPI_CloseRx_ISR(hspi);
}

/**
  * @brief  Manage the 16Bit recieve in Interrupt context
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  *((uint16_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;
  
  /* Enable CRC Transmission */
  if((hspi->RxXferCount == 1) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)) 
  {
    hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
  }
  
  if(hspi->RxXferCount == 0)
  {    
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      hspi->RxISR = SPI_RxISR_16BITCRC;
      return;
    }
    SPI_CloseRx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 8Bit transmit in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(__IO uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr++);
  hspi->TxXferCount--;
  
  if(hspi->TxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      /* Enable CRC Transmission */
      hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
    }
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 16Bit transmit in Interrupt mode
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{ 
  /* Transmit data in 16 Bit mode */
  hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;
  
  if(hspi->TxXferCount == 0)
  {
    if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
    {
      /* Enable CRC Transmission */
      hspi->Instance->CR1 |= SPI_CR1_CRCNEXT;
    }
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief This function handles SPI Communication Timeout.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param Flag : SPI flag to check
  * @param State : flag state to check
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, uint32_t State, uint32_t Timeout)
{
  uint32_t tickstart = HAL_GetTick();
     
  while((hspi->Instance->SR & Flag) != State)
  {
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) >= Timeout))
      {
        /* Disable the SPI and reset the CRC: the CRC value should be cleared
        on both master and slave sides in order to resynchronize the master
        and slave for their respective CRC calculation */
        
        /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));
        
        if((hspi->Init.Mode == SPI_MODE_MASTER)&&((hspi->Init.Direction == SPI_DIRECTION_1LINE)||(hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
        {
          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);
        }
        
        /* Reset CRC Calculation */
        if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
        {
          __HAL_SPI_RESET_CRC(hspi);
        }
        
        hspi->State= HAL_SPI_STATE_READY;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hspi);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  return HAL_OK;      
}

/**
  * @brief This function handles SPI Communication Timeout.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param Fifo : Fifo to check
  * @param State : Fifo state to check
  * @param Timeout : Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State, uint32_t Timeout)
{
  __IO uint8_t tmpreg;
  uint32_t tickstart = HAL_GetTick();

  while((hspi->Instance->SR & Fifo) != State)
  {
    if((Fifo == SPI_SR_FRLVL) && (State == SPI_FRLVL_EMPTY))
    {
      tmpreg = *((__IO uint8_t*)&hspi->Instance->DR);
      UNUSED(tmpreg);
    }
    
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0) || ((HAL_GetTick()-tickstart) >= Timeout))
      {
        /* Disable the SPI and reset the CRC: the CRC value should be cleared
                  on both master and slave sides in order to resynchronize the master
                 and slave for their respective CRC calculation */
        
        /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));
        
        if((hspi->Init.Mode == SPI_MODE_MASTER)&&((hspi->Init.Direction == SPI_DIRECTION_1LINE)||(hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
        {
          /* Disable SPI peripheral */
          __HAL_SPI_DISABLE(hspi);
        }
        
        /* Reset CRC Calculation */
        if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLED)
        {
          __HAL_SPI_RESET_CRC(hspi);
        }
        
        hspi->State = HAL_SPI_STATE_READY;
        
        /* Process Unlocked */
        __HAL_UNLOCK(hspi);
        
        return HAL_TIMEOUT;
      }
    }
  }
  
  return HAL_OK;      
}

/**
  * @brief This function handles the check of the RX transaction complete.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @param Timeout : Timeout duration
  * @retval None.
  */
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi,  uint32_t Timeout)
{
  if((hspi->Init.Mode == SPI_MODE_MASTER)&&((hspi->Init.Direction == SPI_DIRECTION_1LINE)||(hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);
    
    if(SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_BSY, RESET, Timeout) != HAL_OK)
    {  
      hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
      return HAL_TIMEOUT;
    }
    if(SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FRLVL, SPI_FRLVL_EMPTY, Timeout) != HAL_OK) 
    {
      hspi->ErrorCode |= HAL_SPI_ERROR_FLAG;
      return HAL_TIMEOUT;
    }
  }  
  return HAL_OK;
}
  
/**
  * @brief This function handles the close of the RXTX transaction.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);
  
  /* Check if CRC error occurred */
  if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    hspi->State = HAL_SPI_STATE_READY;
    hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
    if(hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      if(hspi->State == HAL_SPI_STATE_BUSY_RX)
      {
      	hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_RxCpltCallback(hspi);
      }
      else
      {
      	hspi->State = HAL_SPI_STATE_READY;
        HAL_SPI_TxRxCpltCallback(hspi);
      }      
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;
      HAL_SPI_ErrorCallback(hspi);
    }
  }
}

/**
  * @brief This function handles the close of the RX transaction.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi)
{
    /* Disable RXNE and ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));
    
    /* Check the end of the transaction */
    SPI_EndRxTransaction(hspi,SPI_DEFAULT_TIMEOUT);
    
    hspi->State = HAL_SPI_STATE_READY; 
    
    /* Check if CRC error occurred */
    if(__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
    {
      hspi->ErrorCode|= HAL_SPI_ERROR_CRC;
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
      HAL_SPI_ErrorCallback(hspi);         
    }
    else
    {
      if(hspi->ErrorCode == HAL_SPI_ERROR_NONE)
      {
        HAL_SPI_RxCpltCallback(hspi);         
      }
      else
      {
        HAL_SPI_ErrorCallback(hspi);
      }
    }
}

/**
  * @brief This function handles the close of the TX transaction.
  * @param  hspi : pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for SPI module.
  * @retval None.
  */
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable TXE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));
  
  /* Clear OVERUN flag in 2 Lines communication mode because received is not read */
  if(hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }
  
  hspi->State = HAL_SPI_STATE_READY;
  if(hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
    HAL_SPI_TxCpltCallback(hspi);
  }
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
