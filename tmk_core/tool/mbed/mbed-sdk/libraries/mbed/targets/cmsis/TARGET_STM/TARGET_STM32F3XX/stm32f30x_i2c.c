/**
  ******************************************************************************
  * @file    stm32f30x_i2c.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Inter-Integrated circuit (I2C):
  *           + Initialization and Configuration
  *           + Communications handling
  *           + SMBUS management
  *           + I2C registers management
  *           + Data transfers management
  *           + DMA transfers management
  *           + Interrupts and flags management
  *
  *  @verbatim
 ============================================================================
                     ##### How to use this driver #####
 ============================================================================
   [..]
   (#) Enable peripheral clock using RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2Cx, ENABLE)
       function for I2C1 or I2C2.
   (#) Enable SDA, SCL  and SMBA (when used) GPIO clocks using 
       RCC_AHBPeriphClockCmd() function. 
   (#) Peripherals alternate function: 
       (++) Connect the pin to the desired peripherals' Alternate 
            Function (AF) using GPIO_PinAFConfig() function.
       (++) Configure the desired pin in alternate function by:
            GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
       (++) Select the type, OpenDrain and speed via 
            GPIO_PuPd, GPIO_OType and GPIO_Speed members
       (++) Call GPIO_Init() function.
   (#) Program the Mode, Timing , Own address, Ack and Acknowledged Address 
       using the I2C_Init() function.
   (#) Optionally you can enable/configure the following parameters without
       re-initialization (i.e there is no need to call again I2C_Init() function):
       (++) Enable the acknowledge feature using I2C_AcknowledgeConfig() function.
       (++) Enable the dual addressing mode using I2C_DualAddressCmd() function.
       (++) Enable the general call using the I2C_GeneralCallCmd() function.
       (++) Enable the clock stretching using I2C_StretchClockCmd() function.
       (++) Enable the PEC Calculation using I2C_CalculatePEC() function.
       (++) For SMBus Mode: 
            (+++) Enable the SMBusAlert pin using I2C_SMBusAlertCmd() function.
   (#) Enable the NVIC and the corresponding interrupt using the function
       I2C_ITConfig() if you need to use interrupt mode.
   (#) When using the DMA mode 
      (++) Configure the DMA using DMA_Init() function.
      (++) Active the needed channel Request using I2C_DMACmd() function.
   (#) Enable the I2C using the I2C_Cmd() function.
   (#) Enable the DMA using the DMA_Cmd() function when using DMA mode in the 
       transfers.
   [..]        
   (@) When using I2C in Fast Mode Plus, SCL and SDA pin 20mA current drive capability
       must be enabled by setting the driving capability control bit in SYSCFG.
       
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
#include "stm32f30x_i2c.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C 
  * @brief I2C driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define CR1_CLEAR_MASK          ((uint32_t)0x00CFE0FF)  /*<! I2C CR1 clear register Mask */
#define CR2_CLEAR_MASK          ((uint32_t)0x07FF7FFF)  /*<! I2C CR2 clear register Mask */
#define TIMING_CLEAR_MASK       ((uint32_t)0xF0FFFFFF)  /*<! I2C TIMING clear register Mask */
#define ERROR_IT_MASK           ((uint32_t)0x00003F00)  /*<! I2C Error interrupt register Mask */
#define TC_IT_MASK              ((uint32_t)0x000000C0)  /*<! I2C TC interrupt register Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */


/** @defgroup I2C_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim   
 ===============================================================================
           ##### Initialization and Configuration functions #####
 ===============================================================================
    [..] This section provides a set of functions allowing to initialize the I2C Mode,
         I2C Timing, I2C filters, I2C Addressing mode, I2C OwnAddress1.

    [..] The I2C_Init() function follows the I2C configuration procedures (these procedures 
         are available in reference manual).
         
    [..] When the Software Reset is performed using I2C_SoftwareResetCmd() function, the internal
         states machines are reset and communication control bits, as well as status bits come 
         back to their reset value.
         
    [..] Before enabling Stop mode using I2C_StopModeCmd() I2C Clock source must be set to
         HSI and Digital filters must be disabled.
         
    [..] Before enabling Own Address 2 via I2C_DualAddressCmd() function, OA2 and mask should be
         configured using I2C_OwnAddress2Config() function.
         
    [..] I2C_SlaveByteControlCmd() enable Slave byte control that allow user to get control of 
         each byte in slave mode when NBYTES is set to 0x01. 
             
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  if (I2Cx == I2C1)
  {
    /* Enable I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else
  {
    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_ANALOG_FILTER(I2C_InitStruct->I2C_AnalogFilter));
  assert_param(IS_I2C_DIGITAL_FILTER(I2C_InitStruct->I2C_DigitalFilter));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

  /* Disable I2Cx Peripheral */
  I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);

  /*---------------------------- I2Cx FILTERS Configuration ------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR1;
  /* Clear I2Cx CR1 register */
  tmpreg &= CR1_CLEAR_MASK;
  /* Configure I2Cx: analog and digital filter */
  /* Set ANFOFF bit according to I2C_AnalogFilter value */
  /* Set DFN bits according to I2C_DigitalFilter value */
  tmpreg |= (uint32_t)I2C_InitStruct->I2C_AnalogFilter |(I2C_InitStruct->I2C_DigitalFilter << 8);
  
  /* Write to I2Cx CR1 */
  I2Cx->CR1 = tmpreg;

  /*---------------------------- I2Cx TIMING Configuration -------------------*/
  /* Configure I2Cx: Timing */
  /* Set TIMINGR bits according to I2C_Timing */
  /* Write to I2Cx TIMING */
  I2Cx->TIMINGR = I2C_InitStruct->I2C_Timing & TIMING_CLEAR_MASK;

  /* Enable I2Cx Peripheral */
  I2Cx->CR1 |= I2C_CR1_PE;

  /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
  /* Clear tmpreg local variable */
  tmpreg = 0;
  /* Clear OAR1 register */
  I2Cx->OAR1 = (uint32_t)tmpreg;
  /* Clear OAR2 register */
  I2Cx->OAR2 = (uint32_t)tmpreg;
  /* Configure I2Cx: Own Address1 and acknowledged address */
  /* Set OA1MODE bit according to I2C_AcknowledgedAddress value */
  /* Set OA1 bits according to I2C_OwnAddress1 value */
  tmpreg = (uint32_t)((uint32_t)I2C_InitStruct->I2C_AcknowledgedAddress | \
                      (uint32_t)I2C_InitStruct->I2C_OwnAddress1);
  /* Write to I2Cx OAR1 */
  I2Cx->OAR1 = tmpreg;
  /* Enable Own Address1 acknowledgement */
  I2Cx->OAR1 |= I2C_OAR1_OA1EN;

  /*---------------------------- I2Cx MODE Configuration ---------------------*/
  /* Configure I2Cx: mode */
  /* Set SMBDEN and SMBHEN bits according to I2C_Mode value */
  tmpreg = I2C_InitStruct->I2C_Mode;
  /* Write to I2Cx CR1 */
  I2Cx->CR1 |= tmpreg;

  /*---------------------------- I2Cx ACK Configuration ----------------------*/
  /* Get the I2Cx CR2 value */
  tmpreg = I2Cx->CR2;
  /* Clear I2Cx CR2 register */
  tmpreg &= CR2_CLEAR_MASK;
  /* Configure I2Cx: acknowledgement */
  /* Set NACK bit according to I2C_Ack value */
  tmpreg |= I2C_InitStruct->I2C_Ack;
  /* Write to I2Cx CR2 */
  I2Cx->CR2 = tmpreg;
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values --------------*/
  /* Initialize the I2C_Timing member */
  I2C_InitStruct->I2C_Timing = 0;
  /* Initialize the I2C_AnalogFilter member */
  I2C_InitStruct->I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  /* Initialize the I2C_DigitalFilter member */
  I2C_InitStruct->I2C_DigitalFilter = 0;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR1 |= I2C_CR1_PE;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);
  }
}


/**
  * @brief  Enables or disables the specified I2C software reset.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Disable peripheral */
  I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PE);

  /* Perform a dummy read to delay the disable of peripheral for minimum
     3 APB clock cycles to perform the software reset functionality */
  *(__IO uint32_t *)(uint32_t)I2Cx; 

  /* Enable peripheral */
  I2Cx->CR1 |= I2C_CR1_PE;
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_ERRI: Error interrupt mask
  *     @arg I2C_IT_TCI: Transfer Complete interrupt mask
  *     @arg I2C_IT_STOPI: Stop Detection interrupt mask
  *     @arg I2C_IT_NACKI: Not Acknowledge received interrupt mask
  *     @arg I2C_IT_ADDRI: Address Match interrupt mask  
  *     @arg I2C_IT_RXI: RX interrupt mask
  *     @arg I2C_IT_TXI: TX interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint32_t I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CR1 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_IT);
  }
}

/**
  * @brief  Enables or disables the I2C Clock stretching.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Clock stretching.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable clock stretching */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_NOSTRETCH);    
  }
  else
  {
    /* Disable clock stretching  */
    I2Cx->CR1 |= I2C_CR1_NOSTRETCH;
  }
}

/**
  * @brief  Enables or disables I2C wakeup from stop mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx stop mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StopModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable wakeup from stop mode */
    I2Cx->CR1 |= I2C_CR1_WUPEN;   
  }
  else
  {
    /* Disable wakeup from stop mode */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_WUPEN); 
  }
}

/**
  * @brief  Enables or disables the I2C own address 2.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C own address 2.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable own address 2 */
    I2Cx->OAR2 |= I2C_OAR2_OA2EN;
  }
  else
  {
    /* Disable own address 2 */
    I2Cx->OAR2 &= (uint32_t)~((uint32_t)I2C_OAR2_OA2EN);
  }
}    

/**
  * @brief  Configures the I2C slave own address 2 and mask.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 2 mask to be programmed.
  *   This parameter can be one of the following values:
  *     @arg I2C_OA2_NoMask: no mask.
  *     @arg I2C_OA2_Mask01: OA2[1] is masked and don't care.
  *     @arg I2C_OA2_Mask02: OA2[2:1] are masked and don't care.
  *     @arg I2C_OA2_Mask03: OA2[3:1] are masked and don't care.
  *     @arg I2C_OA2_Mask04: OA2[4:1] are masked and don't care.
  *     @arg I2C_OA2_Mask05: OA2[5:1] are masked and don't care.
  *     @arg I2C_OA2_Mask06: OA2[6:1] are masked and don't care.
  *     @arg I2C_OA2_Mask07: OA2[7:1] are masked and don't care.
  * @retval None
  */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_OWN_ADDRESS2(Address));
  assert_param(IS_I2C_OWN_ADDRESS2_MASK(Mask));
  
  /* Get the old register value */
  tmpreg = I2Cx->OAR2;

  /* Reset I2Cx OA2 bit [7:1] and OA2MSK bit [1:0]  */
  tmpreg &= (uint32_t)~((uint32_t)(I2C_OAR2_OA2 | I2C_OAR2_OA2MSK));

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)(((uint32_t)Address & I2C_OAR2_OA2) | \
            (((uint32_t)Mask << 8) & I2C_OAR2_OA2MSK)) ;

  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}

/**
  * @brief  Enables or disables the I2C general call mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable general call mode */
    I2Cx->CR1 |= I2C_CR1_GCEN;
  }
  else
  {
    /* Disable general call mode */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_GCEN);
  }
} 

/**
  * @brief  Enables or disables the I2C slave byte control.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C slave byte control.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_SlaveByteControlCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable slave byte control */
    I2Cx->CR1 |= I2C_CR1_SBC;
  }
  else
  {
    /* Disable slave byte control */
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_SBC);
  }
}

/**
  * @brief  Configures the slave address to be transmitted after start generation.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @note   This function should be called before generating start condition.  
  * @retval None
  */
void I2C_SlaveAddressConfig(I2C_TypeDef* I2Cx, uint16_t Address)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SLAVE_ADDRESS(Address));
               
  /* Get the old register value */
  tmpreg = I2Cx->CR2;

  /* Reset I2Cx SADD bit [9:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_CR2_SADD);

  /* Set I2Cx SADD */
  tmpreg |= (uint32_t)((uint32_t)Address & I2C_CR2_SADD);

  /* Store the new register value */
  I2Cx->CR2 = tmpreg;
}
  
/**
  * @brief  Enables or disables the I2C 10-bit addressing mode for the master.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C 10-bit addressing mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @note   This function should be called before generating start condition.  
  * @retval None
  */
void I2C_10BitAddressingModeCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable 10-bit addressing mode */
    I2Cx->CR2 |= I2C_CR2_ADD10;
  }
  else
  {
    /* Disable 10-bit addressing mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_ADD10);
  }
} 

/**
  * @}
  */


/** @defgroup I2C_Group2 Communications handling functions
 *  @brief   Communications handling functions 
 *
@verbatim
 ===============================================================================
                  ##### Communications handling functions #####
 ===============================================================================  
    [..] This section provides a set of functions that handles I2C communication.
    
    [..] Automatic End mode is enabled using I2C_AutoEndCmd() function. When Reload
         mode is enabled via I2C_ReloadCmd() AutoEnd bit has no effect.
         
    [..] I2C_NumberOfBytesConfig() function set the number of bytes to be transferred,
         this configuration should be done before generating start condition in master 
         mode.
         
    [..] When switching from master write operation to read operation in 10Bit addressing
         mode, master can only sends the 1st 7 bits of the 10 bit address, followed by 
         Read direction by enabling HEADR bit using I2C_10BitAddressHeader() function.        
         
    [..] In master mode, when transferring more than 255 bytes Reload mode should be used
         to handle communication. In the first phase of transfer, Nbytes should be set to 
         255. After transferring these bytes TCR flag is set and I2C_TransferHandling()
         function should be called to handle remaining communication.
         
    [..] In master mode, when software end mode is selected when all data is transferred
         TC flag is set I2C_TransferHandling() function should be called to generate STOP
         or generate ReStart.                      
             
@endverbatim
  * @{
  */
  
/**
  * @brief  Enables or disables the I2C automatic end mode (stop condition is 
  *         automatically sent when nbytes data are transferred).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C automatic end mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @note   This function has effect if Reload mode is disabled.   
  * @retval None
  */
void I2C_AutoEndCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Auto end mode */
    I2Cx->CR2 |= I2C_CR2_AUTOEND;
  }
  else
  {
    /* Disable Auto end mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_AUTOEND);
  }
} 

/**
  * @brief  Enables or disables the I2C nbytes reload mode.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the nbytes reload mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ReloadCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Auto Reload mode */
    I2Cx->CR2 |= I2C_CR2_RELOAD;
  }
  else
  {
    /* Disable Auto Reload mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_RELOAD);
  }
}

/**
  * @brief  Configures the number of bytes to be transmitted/received.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Number_Bytes: specifies the number of bytes to be programmed.
  * @retval None
  */
void I2C_NumberOfBytesConfig(I2C_TypeDef* I2Cx, uint8_t Number_Bytes)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->CR2;

  /* Reset I2Cx Nbytes bit [7:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_CR2_NBYTES);

  /* Set I2Cx Nbytes */
  tmpreg |= (uint32_t)(((uint32_t)Number_Bytes << 16 ) & I2C_CR2_NBYTES);

  /* Store the new register value */
  I2Cx->CR2 = tmpreg;
}  
  
/**
  * @brief  Configures the type of transfer request for the master.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_Direction: specifies the transfer request direction to be programmed.
  *    This parameter can be one of the following values:
  *     @arg I2C_Direction_Transmitter: Master request a write transfer
  *     @arg I2C_Direction_Receiver: Master request a read transfer 
  * @retval None
  */
void I2C_MasterRequestConfig(I2C_TypeDef* I2Cx, uint16_t I2C_Direction)
{
/* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));
  
  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction == I2C_Direction_Transmitter)
  {
    /* Request a write Transfer */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_RD_WRN);
  }
  else
  {
    /* Request a read Transfer */
    I2Cx->CR2 |= I2C_CR2_RD_WRN;
  }
}  
  
/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CR2 |= I2C_CR2_START;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_START);
  }
}  
  
/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR2 |= I2C_CR2_STOP;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_STOP);
  }
}  

/**
  * @brief  Enables or disables the I2C 10-bit header only mode with read direction.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2C 10-bit header only mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @note   This mode can be used only when switching from master transmitter mode 
  *         to master receiver mode.        
  * @retval None
  */
void I2C_10BitAddressHeaderCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable 10-bit header only mode */
    I2Cx->CR2 |= I2C_CR2_HEAD10R;
  }
  else
  {
    /* Disable 10-bit header only mode */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_HEAD10R);
  }
}    

/**
  * @brief  Generates I2C communication Acknowledge.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the Acknowledge.
  *   This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable ACK generation */
    I2Cx->CR2 &= (uint32_t)~((uint32_t)I2C_CR2_NACK);    
  }
  else
  {
    /* Enable NACK generation */
    I2Cx->CR2 |= I2C_CR2_NACK;
  }
}

/**
  * @brief  Returns the I2C slave matched address .
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the slave matched address .
  */
uint8_t I2C_GetAddressMatched(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  return (uint8_t)(((uint32_t)I2Cx->ISR & I2C_ISR_ADDCODE) >> 16) ;
}

/**
  * @brief  Returns the I2C slave received request.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the received request.
  */
uint16_t I2C_GetTransferDirection(I2C_TypeDef* I2Cx)
{
  uint32_t tmpreg = 0;
  uint16_t direction = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  tmpreg = (uint32_t)(I2Cx->ISR & I2C_ISR_DIR);
  
  /* If write transfer is requested */
  if (tmpreg == 0)
  {
    /* write transfer is requested */
    direction = I2C_Direction_Transmitter;
  }
  else
  {
    /* Read transfer is requested */
    direction = I2C_Direction_Receiver;
  }  
  return direction;
}

/**
  * @brief  Handles I2Cx communication when starting transfer or during transfer (TC or TCR flag are set).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Number_Bytes: specifies the number of bytes to be programmed.
  *   This parameter must be a value between 0 and 255.
  * @param  ReloadEndMode: new state of the I2C START condition generation.
  *   This parameter can be one of the following values:
  *     @arg I2C_Reload_Mode: Enable Reload mode .
  *     @arg I2C_AutoEnd_Mode: Enable Automatic end mode.
  *     @arg I2C_SoftEnd_Mode: Enable Software end mode.
  * @param  StartStopMode: new state of the I2C START condition generation.
  *   This parameter can be one of the following values:
  *     @arg I2C_No_StartStop: Don't Generate stop and start condition.
  *     @arg I2C_Generate_Stop: Generate stop condition (Number_Bytes should be set to 0).
  *     @arg I2C_Generate_Start_Read: Generate Restart for read request.
  *     @arg I2C_Generate_Start_Write: Generate Restart for write request.
  * @retval None
  */
void I2C_TransferHandling(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SLAVE_ADDRESS(Address));  
  assert_param(IS_RELOAD_END_MODE(ReloadEndMode));
  assert_param(IS_START_STOP_MODE(StartStopMode));
    
  /* Get the CR2 register value */
  tmpreg = I2Cx->CR2;
  
  /* clear tmpreg specific bits */
  tmpreg &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP));
  
  /* update tmpreg */
  tmpreg |= (uint32_t)(((uint32_t)Address & I2C_CR2_SADD) | (((uint32_t)Number_Bytes << 16 ) & I2C_CR2_NBYTES) | \
            (uint32_t)ReloadEndMode | (uint32_t)StartStopMode);
  
  /* update CR2 register */
  I2Cx->CR2 = tmpreg;  
}  

/**
  * @}
  */


/** @defgroup I2C_Group3 SMBUS management functions
 *  @brief   SMBUS management functions 
 *
@verbatim
 ===============================================================================
                      ##### SMBUS management functions #####
 ===============================================================================   
    [..] This section provides a set of functions that handles SMBus communication
         and timeouts detection.
    
    [..] The SMBus Device default address (0b1100 001) is enabled by calling I2C_Init()
         function and setting I2C_Mode member of I2C_InitTypeDef() structure to 
         I2C_Mode_SMBusDevice.
         
    [..] The SMBus Host address (0b0001 000) is enabled by calling I2C_Init()
         function and setting I2C_Mode member of I2C_InitTypeDef() structure to 
         I2C_Mode_SMBusHost.         
         
    [..] The Alert Response Address (0b0001 100) is enabled using I2C_SMBusAlertCmd()
         function.
         
    [..] To detect cumulative SCL stretch in master and slave mode, TIMEOUTB should be 
         configured (in accordance to SMBus specification) using I2C_TimeoutBConfig() 
         function then I2C_ExtendedClockTimeoutCmd() function should be called to enable
         the detection.
         
    [..] SCL low timeout is detected by configuring TIMEOUTB using I2C_TimeoutBConfig()
         function followed by the call of I2C_ClockTimeoutCmd(). When adding to this 
         procedure the call of I2C_IdleClockTimeoutCmd() function, Bus Idle condition 
         (both SCL and SDA high) is detected also.                
                          
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables I2C SMBus alert.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx SMBus alert.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SMBusAlertCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable SMBus alert */
    I2Cx->CR1 |= I2C_CR1_ALERTEN;   
  }
  else
  {
    /* Disable SMBus alert */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_ALERTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Clock Timeout (SCL Timeout detection).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx clock Timeout.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TIMOUTEN;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMOUTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Extended Clock Timeout (SCL cumulative Timeout detection).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Extended clock Timeout.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ExtendedClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TEXTEN;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TEXTEN); 
  }
}

/**
  * @brief  Enables or disables I2C Idle Clock Timeout (Bus idle SCL and SDA 
  *         high detection).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Idle clock Timeout.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_IdleClockTimeoutCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable Clock Timeout */
    I2Cx->TIMEOUTR |= I2C_TIMEOUTR_TIDLE;   
  }
  else
  {
    /* Disable Clock Timeout */    
    I2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIDLE); 
  }
}

/**
  * @brief  Configures the I2C Bus Timeout A (SCL Timeout when TIDLE = 0 or Bus 
  *   idle SCL and SDA high when TIDLE = 1).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Timeout: specifies the TimeoutA to be programmed. 
  * @retval None
  */
void I2C_TimeoutAConfig(I2C_TypeDef* I2Cx, uint16_t Timeout)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_TIMEOUT(Timeout));
    
  /* Get the old register value */
  tmpreg = I2Cx->TIMEOUTR;

  /* Reset I2Cx TIMEOUTA bit [11:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMEOUTA);

  /* Set I2Cx TIMEOUTA */
  tmpreg |= (uint32_t)((uint32_t)Timeout & I2C_TIMEOUTR_TIMEOUTA) ;

  /* Store the new register value */
  I2Cx->TIMEOUTR = tmpreg;
}

/**
  * @brief  Configures the I2C Bus Timeout B (SCL cumulative Timeout).
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Timeout: specifies the TimeoutB to be programmed. 
  * @retval None
  */
void I2C_TimeoutBConfig(I2C_TypeDef* I2Cx, uint16_t Timeout)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_TIMEOUT(Timeout));

  /* Get the old register value */
  tmpreg = I2Cx->TIMEOUTR;

  /* Reset I2Cx TIMEOUTB bit [11:0] */
  tmpreg &= (uint32_t)~((uint32_t)I2C_TIMEOUTR_TIMEOUTB);

  /* Set I2Cx TIMEOUTB */
  tmpreg |= (uint32_t)(((uint32_t)Timeout << 16) & I2C_TIMEOUTR_TIMEOUTB) ;

  /* Store the new register value */
  I2Cx->TIMEOUTR = tmpreg;
}

/**
  * @brief  Enables or disables I2C PEC calculation.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable PEC calculation */
    I2Cx->CR1 |= I2C_CR1_PECEN;   
  }
  else
  {
    /* Disable PEC calculation */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR1_PECEN); 
  }
}

/**
  * @brief  Enables or disables I2C PEC transmission/reception request.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_PECRequestCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable PEC transmission/reception request */
    I2Cx->CR1 |= I2C_CR2_PECBYTE;   
  }
  else
  {
    /* Disable PEC transmission/reception request */    
    I2Cx->CR1 &= (uint32_t)~((uint32_t)I2C_CR2_PECBYTE); 
  }
}

/**
  * @brief  Returns the I2C PEC.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the PEC .
  */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the slave matched address in the SR1 register */
  return (uint8_t)((uint32_t)I2Cx->PECR & I2C_PECR_PEC);
}

/**
  * @}
  */  
  
  
/** @defgroup I2C_Group4 I2C registers management functions
 *  @brief   I2C registers management functions 
 *
@verbatim
 ===============================================================================
                ##### I2C registers management functions #####
 ===============================================================================  
    [..] This section provides a functions that allow user the management of 
         I2C registers.
         
@endverbatim
  * @{
  */

  /**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_Register: specifies the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_Register_CR1: CR1 register.
  *     @arg I2C_Register_CR2: CR2 register.
  *     @arg I2C_Register_OAR1: OAR1 register.
  *     @arg I2C_Register_OAR2: OAR2 register.
  *     @arg I2C_Register_TIMINGR: TIMING register.
  *     @arg I2C_Register_TIMEOUTR: TIMEOUTR register.
  *     @arg I2C_Register_ISR: ISR register.
  *     @arg I2C_Register_ICR: ICR register.
  *     @arg I2C_Register_PECR: PECR register.
  *     @arg I2C_Register_RXDR: RXDR register.
  *     @arg I2C_Register_TXDR: TXDR register.
  * @retval The value of the read register.
  */
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t)I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint32_t *) tmp);
}

/**
  * @}
  */  
  
/** @defgroup I2C_Group5 Data transfers management functions
 *  @brief   Data transfers management functions 
 *
@verbatim
 ===============================================================================
                ##### Data transfers management functions #####
 =============================================================================== 
    [..] This subsection provides a set of functions allowing to manage 
         the I2C data transfers.
         
    [..] The read access of the I2C_RXDR register can be done using 
         the I2C_ReceiveData() function and returns the received value.
         Whereas a write access to the I2C_TXDR can be done using I2C_SendData()
         function and stores the written data into TXDR.
@endverbatim
  * @{
  */  
  
/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Write in the DR register the data to be sent */
  I2Cx->TXDR = (uint8_t)Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->RXDR;
}  

/**
  * @}
  */ 
  
  
/** @defgroup I2C_Group6 DMA transfers management functions
 *  @brief   DMA transfers management functions 
 *
@verbatim
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================  
    [..] This section provides two functions that can be used only in DMA mode.
    [..] In DMA Mode, the I2C communication can be managed by 2 DMA Channel 
         requests:
         (#) I2C_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) I2C_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState);
@endverbatim
  * @{
  */  
    
/**
  * @brief  Enables or disables the I2C DMA interface.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_DMAReq: specifies the I2C DMA transfer request to be enabled or disabled. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_DMAReq_Tx: Tx DMA transfer request
  *     @arg I2C_DMAReq_Rx: Rx DMA transfer request
  * @param  NewState: new state of the selected I2C DMA transfer request.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMACmd(I2C_TypeDef* I2Cx, uint32_t I2C_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_DMA_REQ(I2C_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CR1 |= I2C_DMAReq;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CR1 &= (uint32_t)~I2C_DMAReq;
  }
}
/**
  * @}
  */  


/** @defgroup I2C_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim
 ===============================================================================
             ##### Interrupts and flags management functions  #####
 =============================================================================== 
    [..] This section provides functions allowing to configure the I2C Interrupts 
         sources and check or clear the flags or pending bits status.
         The user should identify which mode will be used in his application to manage 
         the communication: Polling mode, Interrupt mode or DMA mode(refer I2C_Group6) .

  *** Polling Mode ***
  ====================
    [..] In Polling Mode, the I2C communication can be managed by 15 flags:
        (#) I2C_FLAG_TXE: to indicate the status of Transmit data register empty flag.
        (#) I2C_FLAG_TXIS: to indicate the status of Transmit interrupt status flag .
        (#) I2C_FLAG_RXNE: to indicate the status of Receive data register not empty flag.
        (#) I2C_FLAG_ADDR: to indicate the status of Address matched flag (slave mode).
        (#) I2C_FLAG_NACKF: to indicate the status of NACK received flag.
        (#) I2C_FLAG_STOPF: to indicate the status of STOP detection flag.
        (#) I2C_FLAG_TC: to indicate the status of Transfer complete flag(master mode).
        (#) I2C_FLAG_TCR: to indicate the status of Transfer complete reload flag.
        (#) I2C_FLAG_BERR: to indicate the status of Bus error flag.
        (#) I2C_FLAG_ARLO: to indicate the status of Arbitration lost flag.
        (#) I2C_FLAG_OVR: to indicate the status of Overrun/Underrun flag.
        (#) I2C_FLAG_PECERR: to indicate the status of PEC error in reception flag.
        (#) I2C_FLAG_TIMEOUT: to indicate the status of Timeout or Tlow detection flag.
        (#) I2C_FLAG_ALERT: to indicate the status of SMBus Alert flag.
        (#) I2C_FLAG_BUSY: to indicate the status of Bus busy flag.

    [..] In this Mode it is advised to use the following functions:
        (+) FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
        (+) void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);

    [..]
        (@)Do not use the BUSY flag to handle each data transmission or reception.It is 
           better to use the TXIS and RXNE flags instead.

  *** Interrupt Mode ***
  ======================
    [..] In Interrupt Mode, the I2C communication can be managed by 7 interrupt sources
         and 15 pending bits: 
    [..] Interrupt Source:
        (#) I2C_IT_ERRI: specifies the interrupt source for the Error interrupt.
        (#) I2C_IT_TCI: specifies the interrupt source for the Transfer Complete interrupt.
        (#) I2C_IT_STOPI: specifies the interrupt source for the Stop Detection interrupt.
        (#) I2C_IT_NACKI: specifies the interrupt source for the Not Acknowledge received interrupt.
        (#) I2C_IT_ADDRI: specifies the interrupt source for the Address Match interrupt.  
        (#) I2C_IT_RXI: specifies the interrupt source for the RX interrupt.
        (#) I2C_IT_TXI: specifies the interrupt source for the TX interrupt.

    [..] Pending Bits:
        (#) I2C_IT_TXIS: to indicate the status of Transmit interrupt status flag.
        (#) I2C_IT_RXNE: to indicate the status of Receive data register not empty flag.
        (#) I2C_IT_ADDR: to indicate the status of Address matched flag (slave mode).
        (#) I2C_IT_NACKF: to indicate the status of NACK received flag.
        (#) I2C_IT_STOPF: to indicate the status of STOP detection flag.
        (#) I2C_IT_TC: to indicate the status of Transfer complete flag (master mode).
        (#) I2C_IT_TCR: to indicate the status of Transfer complete reload flag.
        (#) I2C_IT_BERR: to indicate the status of Bus error flag.
        (#) I2C_IT_ARLO: to indicate the status of Arbitration lost flag.
        (#) I2C_IT_OVR: to indicate the status of Overrun/Underrun flag.
        (#) I2C_IT_PECERR: to indicate the status of PEC error in reception flag.
        (#) I2C_IT_TIMEOUT: to indicate the status of Timeout or Tlow detection flag.
        (#) I2C_IT_ALERT: to indicate the status of SMBus Alert flag.

    [..] In this Mode it is advised to use the following functions:
         (+) void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
         (+) ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);

@endverbatim
  * @{
  */  

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to check. 
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_TXE: Transmit data register empty
  *     @arg I2C_FLAG_TXIS: Transmit interrupt status
  *     @arg I2C_FLAG_RXNE: Receive data register not empty
  *     @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *     @arg I2C_FLAG_NACKF: NACK received flag
  *     @arg I2C_FLAG_STOPF: STOP detection flag
  *     @arg I2C_FLAG_TC: Transfer complete (master mode)
  *     @arg I2C_FLAG_TCR: Transfer complete reload
  *     @arg I2C_FLAG_BERR: Bus error
  *     @arg I2C_FLAG_ARLO: Arbitration lost
  *     @arg I2C_FLAG_OVR: Overrun/Underrun
  *     @arg I2C_FLAG_PECERR: PEC error in reception
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_FLAG_ALERT: SMBus Alert
  *     @arg I2C_FLAG_BUSY: Bus busy
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t tmpreg = 0;
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));
  
  /* Get the ISR register value */
  tmpreg = I2Cx->ISR;
  
  /* Get flag status */
  tmpreg &= I2C_FLAG;
  
  if(tmpreg != 0)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  return bitstatus;
}  
  
/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_ADDR: Address matched (slave mode)
  *     @arg I2C_FLAG_NACKF: NACK received flag
  *     @arg I2C_FLAG_STOPF: STOP detection flag
  *     @arg I2C_FLAG_BERR: Bus error
  *     @arg I2C_FLAG_ARLO: Arbitration lost
  *     @arg I2C_FLAG_OVR: Overrun/Underrun
  *     @arg I2C_FLAG_PECERR: PEC error in reception
  *     @arg I2C_FLAG_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_FLAG_ALERT: SMBus Alert
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{ 
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

  /* Clear the selected flag */
  I2Cx->ICR = I2C_FLAG;
  }

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_IT_TXIS: Transmit interrupt status
  *     @arg I2C_IT_RXNE: Receive data register not empty
  *     @arg I2C_IT_ADDR: Address matched (slave mode)
  *     @arg I2C_IT_NACKF: NACK received flag
  *     @arg I2C_IT_STOPF: STOP detection flag
  *     @arg I2C_IT_TC: Transfer complete (master mode)
  *     @arg I2C_IT_TCR: Transfer complete reload
  *     @arg I2C_IT_BERR: Bus error
  *     @arg I2C_IT_ARLO: Arbitration lost
  *     @arg I2C_IT_OVR: Overrun/Underrun
  *     @arg I2C_IT_PECERR: PEC error in reception
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_IT_ALERT: SMBus Alert
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  uint32_t tmpreg = 0;
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  /* If Error interrupt */
  if((uint32_t)(I2C_IT & ERROR_IT_MASK))
  {
    enablestatus = (uint32_t)((I2C_CR1_ERRIE) & (I2Cx->CR1));
  }
  /* If TC interrupt */
  else if((uint32_t)(I2C_IT & TC_IT_MASK))
  {
    enablestatus = (uint32_t)((I2C_CR1_TCIE) & (I2Cx->CR1));
  }
  else
  {
    enablestatus = (uint32_t)((I2C_IT) & (I2Cx->CR1));
  }
  
  /* Get the ISR register value */
  tmpreg = I2Cx->ISR;

  /* Get flag status */
  tmpreg &= I2C_IT;

  /* Check the status of the specified I2C flag */
  if((tmpreg != RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }

  /* Return the I2C_IT status */
  return bitstatus;
}
  
/**
  * @brief  Clears the I2Cx's interrupt pending bits.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_IT_ADDR: Address matched (slave mode)
  *     @arg I2C_IT_NACKF: NACK received flag
  *     @arg I2C_IT_STOPF: STOP detection flag
  *     @arg I2C_IT_BERR: Bus error
  *     @arg I2C_IT_ARLO: Arbitration lost
  *     @arg I2C_IT_OVR: Overrun/Underrun
  *     @arg I2C_IT_PECERR: PEC error in reception
  *     @arg I2C_IT_TIMEOUT: Timeout or Tlow detection flag
  *     @arg I2C_IT_ALERT: SMBus Alert
  * @retval The new state of I2C_IT (SET or RESET).
  */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));

  /* Clear the selected flag */
  I2Cx->ICR = I2C_IT;
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
