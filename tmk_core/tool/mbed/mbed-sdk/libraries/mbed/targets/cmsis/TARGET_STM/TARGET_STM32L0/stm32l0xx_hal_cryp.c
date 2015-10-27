/**
  ******************************************************************************
  * @file    stm32l0xx_hal_cryp.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   CRYP HAL module driver.
  *    
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Cryptography (CRYP) peripheral:
  *           + Initialization and de-initialization functions
  *           + Processing functions by algorithm using polling mode
  *           + Processing functions by algorithm using interrupt mode
  *           + Processing functions by algorithm using DMA mode
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
      The CRYP HAL driver can be used as follows:

      (#)Initialize the CRYP low level resources by implementing the HAL_CRYP_MspInit():
         (##) Enable the CRYP interface clock using __HAL_RCC_AES_CLK_ENABLE()
         (##) In case of using interrupts (e.g. HAL_CRYP_AESECB_Encrypt_IT())
             (+) Configure the CRYP interrupt priority using HAL_NVIC_SetPriority()
             (+) Enable the CRYP IRQ handler using HAL_NVIC_EnableIRQ()
             (+) In CRYP IRQ handler, call HAL_CRYP_IRQHandler()
         (##) In case of using DMA to control data transfer (e.g. HAL_CRYP_AESECB_Encrypt_DMA())
             (+) Enable the DMA1 interface clock using 
                 (++) __HAL_RCC_DMA1_CLK_ENABLE()
             (+) Configure and enable two DMA Channels one for managing data transfer from
                 memory to peripheral (input channel) and another channel for managing data
                 transfer from peripheral to memory (output channel)
             (+) Associate the initialized DMA handle to the CRYP DMA handle
                 using  __HAL_LINKDMA()
             (+) Configure the priority and enable the NVIC for the transfer complete
                 interrupt on the two DMA Streams. The output stream should have higher
                 priority than the input stream.
                 (++) HAL_NVIC_SetPriority()
                 (++) HAL_NVIC_EnableIRQ()
    
      (#)Initialize the CRYP HAL using HAL_CRYP_Init(). This function configures mainly:
         (##) The data type: 1-bit, 8-bit, 16-bit and 32-bit
         (##) The encryption/decryption key.
         (##) The initialization vector (counter). It is not used ECB mode.
    
      (#)Three processing (encryption/decryption) functions are available:
         (##) Polling mode: encryption and decryption APIs are blocking functions
              i.e. they process the data and wait till the processing is finished
              e.g. HAL_CRYP_AESCBC_Encrypt()
         (##) Interrupt mode: encryption and decryption APIs are not blocking functions
              i.e. they process the data under interrupt
              e.g. HAL_CRYP_AESCBC_Encrypt_IT()
         (##) DMA mode: encryption and decryption APIs are not blocking functions
              i.e. the data transfer is ensured by DMA
              e.g. HAL_CRYP_AESCBC_Encrypt_DMA()
    
      (#)When the processing function is called for the first time after HAL_CRYP_Init()
         the CRYP peripheral is initialized and processes the buffer in input.
         At second call, the processing function performs an append of the already
         processed buffer.
         When a new data block is to be processed, call HAL_CRYP_Init() then the
         processing function.
         
      (#)Call HAL_CRYP_DeInit() to deinitialize the CRYP peripheral.

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

#if defined (STM32L041xx) || defined (STM32L061xx) || defined (STM32L062xx) || defined (STM32L063xx) || (STM32L081xx) || defined (STM32L082xx) || defined (STM32L083xx)
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

#ifdef HAL_CRYP_MODULE_ENABLED
/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup CRYP CRYP
  * @brief CRYP HAL module driver.
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup CRYP_Private_Defines CRYP Private Defines
  * @{
  */

#define  CRYP_ALGO_CHAIN_MASK         (AES_CR_MODE | AES_CR_CHMOD)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup CRYP_Private_Functions CRYP Private Functions
  * @{
  */

static HAL_StatusTypeDef  CRYP_EncryptDecrypt_IT(CRYP_HandleTypeDef *hcryp);
static void               CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp, uint8_t *InitVector);
static void               CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint8_t *Key);
static HAL_StatusTypeDef  CRYP_ProcessData(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout);
static void               CRYP_DMAInCplt(DMA_HandleTypeDef *hdma);
static void               CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma);
static void               CRYP_DMAError(DMA_HandleTypeDef *hdma);
static void               CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr);

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @defgroup CRYP_Exported_Functions CRYP Exported Functions
  * @{
  */

/** @defgroup CRYP_Exported_Functions_Group1 Initialization and de-initialization functions 
 *  @brief    Initialization and Configuration functions. 
 *
@verbatim    
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the CRYP according to the specified parameters 
          in the CRYP_InitTypeDef and creates the associated handle
      (+) DeInitialize the CRYP peripheral
      (+) Initialize the CRYP MSP
      (+) DeInitialize CRYP MSP 
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP according to the specified
  *         parameters in the CRYP_InitTypeDef and creates the associated handle.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp)
{ 
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Check the parameters */
  assert_param(IS_AES_ALL_INSTANCE(hcryp->Instance));
  assert_param(IS_CRYP_DATATYPE(hcryp->Init.DataType));
  
  if(hcryp->State == HAL_CRYP_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hcryp->Lock = HAL_UNLOCKED;

    /* Init the low level hardware */
    HAL_CRYP_MspInit(hcryp);
  }
  
  /* Check if AES already enabled */
  if (HAL_IS_BIT_CLR(hcryp->Instance->CR, AES_CR_EN))
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;  

    /* Set the data type*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, hcryp->Init.DataType);
    
    /* Reset CrypInCount and CrypOutCount */
    hcryp->CrypInCount = 0;
    hcryp->CrypOutCount = 0;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Set the default CRYP phase */
    hcryp->Phase = HAL_CRYP_PHASE_READY;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* The Datatype selection must be changed if the AES is disabled. Writing these bits while the AES is */
    /* enabled is forbidden to avoid unpredictable AES behavior.*/

    /* Return function status */
    return HAL_ERROR;
  }

}

/**
  * @brief  DeInitializes the CRYP peripheral. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp)
{
  /* Check the CRYP handle allocation */
  if(hcryp == NULL)
  {
    return HAL_ERROR;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_BUSY;
  
  /* Set the default CRYP phase */
  hcryp->Phase = HAL_CRYP_PHASE_READY;
  
  /* Reset CrypInCount and CrypOutCount */
  hcryp->CrypInCount = 0;
  hcryp->CrypOutCount = 0;
  
  /* Disable the CRYP Peripheral Clock */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* DeInit the low level hardware: CLOCK, NVIC.*/
  HAL_CRYP_MspDeInit(hcryp);
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_RESET;
  
  /* Release Lock */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP MSP.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspInit(CRYP_HandleTypeDef *hcryp)
{
  /* NOTE : This function should not be modified; when the callback is needed, 
            the HAL_CRYP_MspInit can be implemented in the user file */
}

/**
  * @brief  DeInitializes CRYP MSP.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef *hcryp)
{
  /* NOTE : This function should not be modified; when the callback is needed, 
            the HAL_CRYP_MspDeInit can be implemented in the user file */
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group2 AES processing functions 
 *  @brief   processing functions. 
 *
@verbatim   
  ==============================================================================
                      ##### AES processing functions #####
  ==============================================================================  
    [..]  This section provides functions allowing to:
      (+) Encrypt plaintext using AES algorithm in different chaining modes
      (+) Decrypt cyphertext using AES algorithm in different chaining modes
    [..]  Three processing functions are available:
      (+) Polling mode
      (+) Interrupt mode
      (+) DMA mode

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);

  /* Check that data aligned on u32 and Size multiple of 16*/
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if(hcryp->State != HAL_CRYP_STATE_RESET)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_ENCRYPT);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);
	
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if(hcryp->State != HAL_CRYP_STATE_RESET)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CBC mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode
  *         then encrypt pPlainData. The cypher data are available in pCypherData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData, uint32_t Timeout)
{  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if(hcryp->State != HAL_CRYP_STATE_RESET)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Write Plain Data and Get Cypher Data */
    if(CRYP_ProcessData(hcryp, pPlainData, Size, pCypherData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if(hcryp->State != HAL_CRYP_STATE_RESET)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES ECB decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_KEYDERDECRYPT);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Write Cypher Data and Get Plain Data */
    if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if(hcryp->State != HAL_CRYP_STATE_RESET)
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CBC decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_KEYDERDECRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Enable CRYP */
      __HAL_CRYP_ENABLE(hcryp);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Write Cypher Data and Get Plain Data */
    if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
    {
      return HAL_TIMEOUT;
    }
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode
  *         then decrypted pCypherData. The cypher data are available in pPlainData
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Timeout: Specify Timeout value   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData, uint32_t Timeout)
{  
  /* Process Locked */
  __HAL_LOCK(hcryp);
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if initialization phase has already been performed */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->Phase == HAL_CRYP_PHASE_READY))
  {
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Set the key */
    CRYP_SetKey(hcryp, hcryp->Init.pKey);
    
    /* Reset the CHMOD & MODE bits */
    CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
    
    /* Set the CRYP peripheral in AES CTR decryption mode */
    __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_DECRYPT);
    
    /* Set the Initialization Vector */
    CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Set the phase */
    hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
  }
  
  /* Write Cypher Data and Get Plain Data */
  if(CRYP_ProcessData(hcryp, pCypherData, Size, pPlainData, Timeout) != HAL_OK)
  {
    return HAL_TIMEOUT;
  }
  
  /* Change the CRYP state */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hcryp);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode using Interrupt.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_ENCRYPT);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using Interrupt.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CBC mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
   
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode using Interrupt.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pPlainData;
    hcryp->pCrypOutBuffPtr = pCypherData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode using Interrupt.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES ECB decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_KEYDERDECRYPT);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;    
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC decryption mode using IT.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CBC decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_KEYDERDECRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;    
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode using Interrupt.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    /* Get the buffer addresses and sizes */
    hcryp->CrypInCount = Size;
    hcryp->pCrypInBuffPtr = pCypherData;
    hcryp->pCrypOutBuffPtr = pPlainData;
    hcryp->CrypOutCount = Size;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CTR decryption mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_DECRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Enable Interrupts */
    __HAL_CRYP_ENABLE_IT(hcryp, CRYP_IT_CC);
    
    /* Enable CRYP */
    __HAL_CRYP_ENABLE(hcryp);
    
    /* Get the last input data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;    
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    /* Return function status */
    return HAL_ERROR;
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB encryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Set the CRYP peripheral in AES ECB mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_ENCRYPT);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {  
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Set the CRYP peripheral in AES CBC mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR encryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16.
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pPlainData, uint16_t Size, uint8_t *pCypherData)
{
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pPlainData;
    outputaddr = (uint32_t)pCypherData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_ENCRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES ECB decryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESECB_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{  
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES ECB decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_ECB_KEYDERDECRYPT);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CBC encryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16 bytes
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCBC_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Reset the CHMOD & MODE bits */
      CLEAR_BIT(hcryp->Instance->CR, CRYP_ALGO_CHAIN_MASK);
      
      /* Set the CRYP peripheral in AES CBC decryption mode (with key derivation) */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CBC_KEYDERDECRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @brief  Initializes the CRYP peripheral in AES CTR decryption mode using DMA.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pCypherData: Pointer to the cyphertext buffer (aligned on u32)
  * @param  Size: Length of the plaintext buffer, must be a multiple of 16
  * @param  pPlainData: Pointer to the plaintext buffer (aligned on u32)
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYP_AESCTR_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint8_t *pCypherData, uint16_t Size, uint8_t *pPlainData)
{  
  uint32_t inputaddr = 0, outputaddr = 0;
  
  /* Check that data aligned on u32 */
  if((((uint32_t)pPlainData & (uint32_t)0x00000003) != 0) || (((uint32_t)pCypherData & (uint32_t)0x00000003) != 0) || ((Size & (uint16_t)0x000F) != 0))
  {
    /* Process Locked */
    __HAL_UNLOCK(hcryp);

    /* Return function status */
    return HAL_ERROR;
  }
  
  /* Check if HAL_CRYP_Init has been called */
  if ((hcryp->State != HAL_CRYP_STATE_RESET) && (hcryp->State == HAL_CRYP_STATE_READY))
  {
    /* Process Locked */
    __HAL_LOCK(hcryp);
    
    inputaddr  = (uint32_t)pCypherData;
    outputaddr = (uint32_t)pPlainData;
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    
    /* Check if initialization phase has already been performed */
    if(hcryp->Phase == HAL_CRYP_PHASE_READY)
    {
      /* Set the key */
      CRYP_SetKey(hcryp, hcryp->Init.pKey);
      
      /* Set the CRYP peripheral in AES CTR mode */
      __HAL_CRYP_SET_MODE(hcryp, CRYP_CR_ALGOMODE_AES_CTR_DECRYPT);
      
      /* Set the Initialization Vector */
      CRYP_SetInitVector(hcryp, hcryp->Init.pInitVect);
      
      /* Set the phase */
      hcryp->Phase = HAL_CRYP_PHASE_PROCESS;
    }
    
    /* Set the input and output addresses and start DMA transfer */ 
    CRYP_SetDMAConfig(hcryp, inputaddr, Size, outputaddr);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Return function status */
    return HAL_OK;
  }
  else
  {
    /* Release Lock */
    __HAL_UNLOCK(hcryp);
  
    return HAL_ERROR;   
  }
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group3 DMA callback functions 
 *  @brief   DMA callback functions. 
 *
@verbatim   
  ==============================================================================
                      ##### DMA callback functions  #####
  ==============================================================================  
    [..]  This section provides DMA callback functions:
      (+) DMA Input data transfer complete
      (+) DMA Output data transfer complete
      (+) DMA error

@endverbatim
  * @{
  */

/**
  * @brief  CRYP error callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
 __weak void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef *hcryp)
{
  /* NOTE : This function should not be modified; when the callback is needed, 
            the HAL_CRYP_ErrorCallback can be implemented in the user file
   */ 
}

/**
  * @brief  Input transfer completed callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* NOTE : This function should not be modified; when the callback is needed, 
            the HAL_CRYP_InCpltCallback can be implemented in the user file
   */ 
}

/**
  * @brief  Output transfer completed callback.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
__weak void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef *hcryp)
{
  /* NOTE : This function should not be modified; when the callback is needed, 
            the HAL_CRYP_OutCpltCallback can be implemented in the user file
   */ 
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group4 CRYP IRQ handler 
 *  @brief   CRYP IRQ handler.
 *
@verbatim   
  ==============================================================================
                ##### CRYP IRQ handler management #####
  ==============================================================================  
[..]  This section provides CRYP IRQ handler function.

@endverbatim
  * @{
  */

/**
  * @brief  This function handles CRYP interrupt request.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval None
  */
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp)
{
  /* Check if error occurred*/
  if (__HAL_CRYP_GET_IT_SOURCE(hcryp, CRYP_IT_ERR) != RESET)
  {
    if (__HAL_CRYP_GET_FLAG(hcryp,CRYP_FLAG_RDERR) != RESET)
    {
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEARFLAG_RDERR);
    }
    
    if (__HAL_CRYP_GET_FLAG(hcryp,CRYP_FLAG_WRERR) != RESET)
    {
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEARFLAG_WRERR);
    }
    
    if (__HAL_CRYP_GET_FLAG(hcryp,CRYP_FLAG_CCF) != RESET)
    {
      __HAL_CRYP_CLEAR_FLAG(hcryp,CRYP_CLEARFLAG_CCF);
    }
    
    hcryp->State= HAL_CRYP_STATE_ERROR;
    /* Disable Computation Complete Interrupt */
    __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_CC);
    __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_ERR);
    
    HAL_CRYP_ErrorCallback(hcryp);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    return;
  }
  
  /* Check if computation complete interrupt was enabled*/
  if (__HAL_CRYP_GET_IT_SOURCE(hcryp, CRYP_IT_CC) != RESET)
  {
    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEARFLAG_CCF);
  
    CRYP_EncryptDecrypt_IT(hcryp);
  }
}

/**
  * @}
  */

/** @defgroup CRYP_Exported_Functions_Group5 Peripheral State functions 
 *  @brief   Peripheral State functions. 
 *
@verbatim   
  ==============================================================================
                      ##### Peripheral State functions #####
  ==============================================================================  
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the CRYP state.
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL state
  */
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(CRYP_HandleTypeDef *hcryp)
{
  return hcryp->State;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup CRYP_Private_Functions
  * @{
  */

/**
  * @brief  IT function called under interruption context to continue encryption or decryption
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYP_EncryptDecrypt_IT(CRYP_HandleTypeDef *hcryp)
{
  uint32_t inputaddr = 0, outputaddr = 0;

  /* Get the last Output data adress */
  outputaddr = (uint32_t)hcryp->pCrypOutBuffPtr;
  
  /* Read the Output block from the Output Register */
  *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
  outputaddr+=4;
  *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
  outputaddr+=4;
  *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
  outputaddr+=4;
  *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
  
  hcryp->pCrypOutBuffPtr += 16;
  hcryp->CrypOutCount -= 16;
  
  /* Check if all input text is encrypted or decrypted */
  if(hcryp->CrypOutCount == 0)
  {
    /* Disable Computation Complete Interrupt */
    __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_CC);
    __HAL_CRYP_DISABLE_IT(hcryp,CRYP_IT_ERR);
    
    /* Process Unlocked */
    __HAL_UNLOCK(hcryp);
    
    /* Change the CRYP state */
    hcryp->State = HAL_CRYP_STATE_READY;
    
    /* Call computation complete callback */
    HAL_CRYPEx_ComputationCpltCallback(hcryp);
  }
  else /* Process the rest of input text */
  {
    /* Get the last Intput data adress */
    inputaddr = (uint32_t)hcryp->pCrypInBuffPtr;
    
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    hcryp->pCrypInBuffPtr += 16;
    hcryp->CrypInCount -= 16;      
  }
  return HAL_OK;
}
/**
  * @brief  DMA CRYP Input Data process complete callback.
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAInCplt(DMA_HandleTypeDef *hdma)  
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for input request  */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAINEN);
  
  /* Call input data transfer complete callback */
  HAL_CRYP_InCpltCallback(hcryp);
}

/**
  * @brief  DMA CRYP Output Data process complete callback.
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAOutCplt(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  
  /* Disable the DMA transfer for output request by resetting the DMAOUTEN bit
     in the DMACR register */
  CLEAR_BIT(hcryp->Instance->CR, AES_CR_DMAOUTEN);

  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEARFLAG_CCF);

  /* Disable CRYP */
  __HAL_CRYP_DISABLE(hcryp);
  
  /* Change the CRYP state to ready */
  hcryp->State = HAL_CRYP_STATE_READY;
  
  /* Call output data transfer complete callback */
  HAL_CRYP_OutCpltCallback(hcryp);
}

/**
  * @brief  DMA CRYP communication error callback. 
  * @param  hdma: DMA handle
  * @retval None
  */
static void CRYP_DMAError(DMA_HandleTypeDef *hdma)
{
  CRYP_HandleTypeDef* hcryp = (CRYP_HandleTypeDef*)((DMA_HandleTypeDef*)hdma)->Parent;
  hcryp->State= HAL_CRYP_STATE_ERROR;
  HAL_CRYP_ErrorCallback(hcryp);
}

/**
  * @brief  Writes the Key in Key registers. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Key: Pointer to Key buffer
  * @note Key must be written as little endian.
  *         If Key pointer points at address n, 
  *         n[15:0] contains key[96:127], 
  *         (n+4)[15:0] contains key[64:95], 
  *         (n+8)[15:0] contains key[32:63] and 
  *         (n+12)[15:0] contains key[0:31]
  * @retval None
  */
static void CRYP_SetKey(CRYP_HandleTypeDef *hcryp, uint8_t *Key)
{  
  uint32_t keyaddr = (uint32_t)Key;
  
  hcryp->Instance->KEYR3 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR2 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR1 = __REV(*(uint32_t*)(keyaddr));
  keyaddr+=4;
  hcryp->Instance->KEYR0 = __REV(*(uint32_t*)(keyaddr));
}

/**
  * @brief  Writes the InitVector/InitCounter in IV registers. 
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  InitVector: Pointer to InitVector/InitCounter buffer
  * @note Init Vector must be written as little endian.
  *         If Init Vector pointer points at address n, 
  *         n[15:0] contains Vector[96:127], 
  *         (n+4)[15:0] contains Vector[64:95], 
  *         (n+8)[15:0] contains Vector[32:63] and 
  *         (n+12)[15:0] contains Vector[0:31]
  * @retval None
  */
static void CRYP_SetInitVector(CRYP_HandleTypeDef *hcryp, uint8_t *InitVector)
{
  uint32_t ivaddr = (uint32_t)InitVector;
  
  hcryp->Instance->IVR3 = __REV(*(uint32_t*)(ivaddr));
  ivaddr+=4;
  hcryp->Instance->IVR2 = __REV(*(uint32_t*)(ivaddr));
  ivaddr+=4;
  hcryp->Instance->IVR1 = __REV(*(uint32_t*)(ivaddr));
  ivaddr+=4;
  hcryp->Instance->IVR0 = __REV(*(uint32_t*)(ivaddr));
}

/**
  * @brief  Process Data: Writes Input data in polling mode and reads the output data
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  Input: Pointer to the Input buffer
  * @param  Ilength: Length of the Input buffer, must be a multiple of 16.
  * @param  Output: Pointer to the returned buffer
  * @param  Timeout: Specify Timeout value  
  * @retval None
  */
static HAL_StatusTypeDef CRYP_ProcessData(CRYP_HandleTypeDef *hcryp, uint8_t* Input, uint16_t Ilength, uint8_t* Output, uint32_t Timeout)
{
  uint32_t tickstart = 0;
  
  uint32_t index = 0;
  uint32_t inputaddr  = (uint32_t)Input;
  uint32_t outputaddr = (uint32_t)Output;
  
  for(index=0; (index < Ilength); index += 16)
  {
    /* Write the Input block in the Data Input register */
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR  = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    hcryp->Instance->DINR = *(uint32_t*)(inputaddr);
    inputaddr+=4;
    
    /* Get timeout */
    tickstart = HAL_GetTick();
    
    while(HAL_IS_BIT_CLR(hcryp->Instance->SR, AES_SR_CCF))
    {    
      /* Check for the Timeout */
      if(Timeout != HAL_MAX_DELAY)
      {
        if((Timeout == 0)||((HAL_GetTick() - tickstart ) > Timeout))
        {
          /* Change state */
          hcryp->State = HAL_CRYP_STATE_TIMEOUT;
          
          /* Process Unlocked */          
          __HAL_UNLOCK(hcryp);
          
          return HAL_TIMEOUT;
        }
      }
    }
    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEARFLAG_CCF);
    
    /* Read the Output block from the Data Output Register */
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
    outputaddr+=4;
    *(uint32_t*)(outputaddr) = hcryp->Instance->DOUTR;
    outputaddr+=4;
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Set the DMA configuration and start the DMA transfer
  * @param  hcryp: pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  inputaddr: address of the Input buffer
  * @param  Size: Size of the Input buffer, must be a multiple of 16.
  * @param  outputaddr: address of the Output buffer
  * @retval None
  */
static void CRYP_SetDMAConfig(CRYP_HandleTypeDef *hcryp, uint32_t inputaddr, uint16_t Size, uint32_t outputaddr)
{
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmain->XferCpltCallback = CRYP_DMAInCplt;
  /* Set the DMA error callback */
  hcryp->hdmain->XferErrorCallback = CRYP_DMAError;
  
  /* Set the CRYP DMA transfer complete callback */
  hcryp->hdmaout->XferCpltCallback = CRYP_DMAOutCplt;
  /* Set the DMA error callback */
  hcryp->hdmaout->XferErrorCallback = CRYP_DMAError;

  /* Enable the DMA In DMA Stream */
  HAL_DMA_Start_IT(hcryp->hdmain, inputaddr, (uint32_t)&hcryp->Instance->DINR, Size/4);

  /* Enable the DMA Out DMA Stream */
  HAL_DMA_Start_IT(hcryp->hdmaout, (uint32_t)&hcryp->Instance->DOUTR, outputaddr, Size/4);

  /* Enable In and Out DMA requests */
  SET_BIT(hcryp->Instance->CR, (AES_CR_DMAINEN | AES_CR_DMAOUTEN));

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);
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

#endif /* HAL_CRYP_MODULE_ENABLED */
#endif /* STM32L041xx || STM32L061xx || STM32L062xx || STM32L063xx || STM32L081xx || STM32L082xx || STM32L083xx */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

