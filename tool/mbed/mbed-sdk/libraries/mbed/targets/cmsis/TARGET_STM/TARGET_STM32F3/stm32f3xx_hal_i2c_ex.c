/**
  ******************************************************************************
  * @file    stm32f3xx_hal_i2c_ex.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   I2C Extended HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of I2C Extended peripheral:
  *           + Extended features functions
  *         
  @verbatim
  ==============================================================================
               ##### I2C peripheral Extended features  #####
  ==============================================================================
           
  [..] Comparing to other previous devices, the I2C interface for STM32F3XX
       devices contains the following additional features
       
       (+) Possibility to disable or enable Analog Noise Filter
       (+) Use of a configured Digital Noise Filter
       (+) Disable or enable wakeup from Stop mode
   
                     ##### How to use this driver #####
  ==============================================================================
  [..] This driver provides functions to configure Noise Filter
    (#) Configure I2C Analog noise filter using the function HAL_I2CEx_AnalogFilter_Config()
    (#) Configure I2C Digital noise filter using the function HAL_I2CEx_DigitalFilter_Config()
    (#) Configure the enabling or disabling of I2C Wake Up Mode using the functions :
          + HAL_I2CEx_EnableWakeUp()
          + HAL_I2CEx_DisableWakeUp()
  
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

/** @defgroup I2CEx I2C Extended HAL module driver
  * @brief I2C Extended HAL module driver
  * @{
  */

#ifdef HAL_I2C_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2CEx_Exported_Functions I2C Extended Exported Functions
  * @{
  */

/** @defgroup I2CEx_Exported_Functions_Group1 Extended features functions
  * @brief    Extended features functions
  *
@verbatim   
 ===============================================================================
                      ##### Extended features functions #####
 ===============================================================================  
    [..] This section provides functions allowing to:
      (+) Configure Noise Filters 

@endverbatim
  * @{
  */
  
/**
  * @brief  Configures I2C Analog noise filter. 
  * @param  hi2c : pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2Cx peripheral.
  * @param  AnalogFilter : new state of the Analog filter.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2CEx_AnalogFilter_Config(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  assert_param(IS_I2C_ANALOG_FILTER(AnalogFilter));
  
  if((hi2c->State == HAL_I2C_STATE_BUSY) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_RX)
     || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_RX))
  {
    return HAL_BUSY;
  }
  
  /* Process Locked */
  __HAL_LOCK(hi2c);

  hi2c->State = HAL_I2C_STATE_BUSY;
  
  /* Disable the selected I2C peripheral */
  __HAL_I2C_DISABLE(hi2c);    
  
  /* Reset I2Cx ANOFF bit */
  hi2c->Instance->CR1 &= ~(I2C_CR1_ANFOFF);    
  
  /* Set analog filter bit*/
  hi2c->Instance->CR1 |= AnalogFilter;
  
  __HAL_I2C_ENABLE(hi2c); 
  
  hi2c->State = HAL_I2C_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hi2c);

  return HAL_OK; 
}

/**
  * @brief  Configures I2C Digital noise filter. 
  * @param  hi2c : pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2Cx peripheral.
  * @param  DigitalFilter : Coefficient of digital noise filter between 0x00 and 0x0F.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2CEx_DigitalFilter_Config(I2C_HandleTypeDef *hi2c, uint32_t DigitalFilter)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  assert_param(IS_I2C_DIGITAL_FILTER(DigitalFilter));
  
  if((hi2c->State == HAL_I2C_STATE_BUSY) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_RX)
     || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_RX))
  {
    return HAL_BUSY;
  }
  
  /* Process Locked */
  __HAL_LOCK(hi2c);

  hi2c->State = HAL_I2C_STATE_BUSY;
  
  /* Disable the selected I2C peripheral */
  __HAL_I2C_DISABLE(hi2c);  
  
  /* Get the old register value */
  tmpreg = hi2c->Instance->CR1;
  
  /* Reset I2Cx DNF bits [11:8] */
  tmpreg &= ~(I2C_CR1_DFN);
  
  /* Set I2Cx DNF coefficient */
  tmpreg |= DigitalFilter << 8;
  
  /* Store the new register value */
  hi2c->Instance->CR1 = tmpreg;
  
  __HAL_I2C_ENABLE(hi2c); 
  
  hi2c->State = HAL_I2C_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hi2c);

  return HAL_OK; 
}  

/**
  * @brief  Enables I2C wakeup from stop mode.
  * @param  hi2c : pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2Cx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2CEx_EnableWakeUp (I2C_HandleTypeDef *hi2c)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  
  if((hi2c->State == HAL_I2C_STATE_BUSY) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_RX)
     || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_RX))
  {
    return HAL_BUSY;
  }
  
  /* Process Locked */
  __HAL_LOCK(hi2c);

  hi2c->State = HAL_I2C_STATE_BUSY;
  
  /* Disable the selected I2C peripheral */
  __HAL_I2C_DISABLE(hi2c);  
  
  /* Enable wakeup from stop mode */
  hi2c->Instance->CR1 |= I2C_CR1_WUPEN;   
  
  __HAL_I2C_ENABLE(hi2c); 
  
  hi2c->State = HAL_I2C_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hi2c);

  return HAL_OK; 
}  


/**
  * @brief  Disables I2C wakeup from stop mode.
  * @param  hi2c : pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2Cx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2CEx_DisableWakeUp (I2C_HandleTypeDef *hi2c)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  
  if((hi2c->State == HAL_I2C_STATE_BUSY) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_MASTER_BUSY_RX)
     || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_TX) || (hi2c->State == HAL_I2C_STATE_SLAVE_BUSY_RX))
  {
    return HAL_BUSY;
  }
  
  /* Process Locked */
  __HAL_LOCK(hi2c);

  hi2c->State = HAL_I2C_STATE_BUSY;
  
  /* Disable the selected I2C peripheral */
  __HAL_I2C_DISABLE(hi2c);  
  
  /* Enable wakeup from stop mode */
  hi2c->Instance->CR1 &= ~(I2C_CR1_WUPEN);   
  
  __HAL_I2C_ENABLE(hi2c); 
  
  hi2c->State = HAL_I2C_STATE_READY;
  
  /* Process Unlocked */
  __HAL_UNLOCK(hi2c);

  return HAL_OK; 
}  

/**
  * @}
  */  

/**
  * @}
  */

#endif /* HAL_I2C_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
