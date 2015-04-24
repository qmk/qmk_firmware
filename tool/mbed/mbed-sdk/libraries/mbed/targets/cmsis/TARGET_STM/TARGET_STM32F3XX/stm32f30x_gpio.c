/**
  ******************************************************************************
  * @file    stm32f30x_gpio.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:
  *           + Initialization and Configuration functions
  *           + GPIO Read and Write functions
  *           + GPIO Alternate functions configuration functions
  *
  *  @verbatim


 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..]
    (#) Enable the GPIO AHB clock using RCC_AHBPeriphClockCmd()
    (#) Configure the GPIO pin(s) using GPIO_Init()
        Four possible configuration are available for each pin:
        (++) Input: Floating, Pull-up, Pull-down.
        (++) Output: Push-Pull (Pull-up, Pull-down or no Pull),
                     Open Drain (Pull-up, Pull-down or no Pull).
             In output mode, the speed is configurable: Low, Medium, Fast or High.
        (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull), 
                                 Open Drain (Pull-up, Pull-down or no Pull).
        (++) Analog: required mode when a pin is to be used as ADC channel,
             DAC output or comparator input.
    (#) Peripherals alternate function:
        (++) For ADC, DAC and comparators, configure the desired pin in 
             analog mode using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN
        (++) For other peripherals (TIM, USART...):
             (+++) Connect the pin to the desired peripherals' Alternate 
                   Function (AF) using GPIO_PinAFConfig() function.
             (+++) Configure the desired pin in alternate function mode using
                   GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
             (+++) Select the type, pull-up/pull-down and output speed via 
                   GPIO_PuPd, GPIO_OType and GPIO_Speed members.
             (+++) Call GPIO_Init() function.
    (#) To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
    (#) To set/reset the level of a pin configured in output mode use
        GPIO_SetBits()/GPIO_ResetBits()
    (#) During and just after reset, the alternate functions are not active 
        and the GPIO pins are configured in input floating mode (except JTAG pins).
    (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as 
        general-purpose (PC14 and PC15, respectively) when the LSE
        oscillator is off. The LSE has priority over the GPIO function.
    (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as general-purpose 
        (PF0 and PF1 respectively) when the HSE oscillator is off. The HSE has 
        the priority over the GPIO function.  

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
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions 
  * @{
  */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim
 ===============================================================================
            ##### Initialization and Configuration #####
 ===============================================================================

@endverbatim
  * @{
  */
  
/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset 
  *         values.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if(GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
  }
  else if(GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else if(GPIOx == GPIOC)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
  }
  else if(GPIOx == GPIOD)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
  }
  else if(GPIOx == GPIOE)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOE, DISABLE);
  }
  else
  {
    if(GPIOx == GPIOF)
    {
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, ENABLE);
      RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOF, DISABLE);
    }
  }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified 
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that 
  *         contains the configuration information for the specified GPIO
  *         peripheral.
  * @note   GPIO_Pin: selects the pin to be configured:
  *         GPIO_Pin_0->GPIO_Pin_15 for GPIOA, GPIOB, GPIOC, GPIOD and GPIOE;
  *         GPIO_Pin_0->GPIO_Pin_2, GPIO_Pin_4, GPIO_Pin_6, GPIO_Pin_9 
  *                       and GPIO_Pin_10 for GPIOF.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{ 
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  uint32_t tmpreg = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /*-------------------------- Configure the port pins -----------------------*/
  /*-- GPIO Mode Configuration --*/
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;

    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {
      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
        GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration */
        GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos));
        GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
      }
      
      GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));

      GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

      /* Use temporary variable to update PUPDR register configuration, to avoid 
         unexpected transition in the GPIO pin configuration. */
      tmpreg = GPIOx->PUPDR;
      tmpreg &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
      tmpreg |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
      GPIOx->PUPDR = tmpreg;
    }
  }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  *         The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx: where x can be (A or B or D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0x00010000;
  
  /* Check the parameters */
  assert_param(IS_GPIO_LIST_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  tmp |= GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Reset LCKK bit */
  GPIOx->LCKR =  GPIO_Pin;
  /* Set LCKK bit */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit */
  tmp = GPIOx->LCKR;
  /* Read LCKK bit */
  tmp = GPIOx->LCKR;
}

/**
  * @}
  */
  
/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief    GPIO Read and Write
 *
@verbatim
 ===============================================================================
                  ##### GPIO Read and Write #####
 ===============================================================================  

@endverbatim
  * @{
  */   

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be :
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD or GPIOE;
  *         (0..2, 4, 6, 9..10) for GPIOF.
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @retval The input port pin value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be :
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD or GPIOE;
  *         (0..2, 4, 6, 9..10) for GPIOF.
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if ((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be :
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD or GPIOE;
  *         (0..2, 4, 6, 9..10) for GPIOF.
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BSRR = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be :
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD or GPIOE;
  *         (0..2, 4, 6, 9..10) for GPIOF.
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->BRR = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be :
  *         (0..15) for GPIOA, GPIOB, GPIOC, GPIOD or GPIOE;
  *         (0..2, 4, 6, 9..10) for GPIOF.
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enumeration values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));
  
  if (BitVal != Bit_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = GPIO_Pin ;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data 
  *                  register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  
  GPIOx->ODR = PortVal;
}

/**
  * @}
  */

/** @defgroup GPIO_Group3 GPIO Alternate functions configuration functions
 *  @brief   GPIO Alternate functions configuration functions
 *
@verbatim
 ===============================================================================
          ##### GPIO Alternate functions configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A, B, C, D, E or F) to select the GPIO peripheral.
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *   This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @param  GPIO_AF: selects the pin to be used as Alternate function.  
  *   This parameter can be one of the following value:
  *     @arg GPIO_AF_0:  JTCK-SWCLK, JTDI, JTDO/TRACESW0, JTMS-SWDAT, MCO, NJTRST, 
  *                      TRACED, TRACECK.
  *     @arg GPIO_AF_1:  OUT, TIM2, TIM15, TIM16, TIM17.
  *     @arg GPIO_AF_2:  COMP1_OUT, TIM1, TIM2, TIM3, TIM4, TIM8, TIM15, TIM16.
  *     @arg GPIO_AF_3:  COMP7_OUT, TIM8, TIM15, Touch, HRTIM.
  *     @arg GPIO_AF_4:  I2C1, I2C2, TIM1, TIM8, TIM16, TIM17.
  *     @arg GPIO_AF_5:  IR_OUT, I2S2, I2S3, SPI1, SPI2, TIM8, USART4, USART5
  *     @arg GPIO_AF_6:  IR_OUT, I2S2, I2S3, SPI2, SPI3, TIM1, TIM8
  *     @arg GPIO_AF_7:  AOP2_OUT, CAN, COMP3_OUT, COMP5_OUT, COMP6_OUT, USART1, 
  *                      USART2, USART3.
  *     @arg GPIO_AF_8:  COMP1_OUT, COMP2_OUT, COMP3_OUT, COMP4_OUT, COMP5_OUT, 
  *                      COMP6_OUT.
  *     @arg GPIO_AF_9:  AOP4_OUT, CAN, TIM1, TIM8, TIM15.
  *     @arg GPIO_AF_10: AOP1_OUT, AOP3_OUT, TIM2, TIM3, TIM4, TIM8, TIM17. 
  *     @arg GPIO_AF_11: TIM1, TIM8.
  *     @arg GPIO_AF_12: TIM1, HRTIM.
  *     @arg GPIO_AF_13: HRTIM, AOP2_OUT.
  *     @arg GPIO_AF_14: USBDM, USBDP.
  *     @arg GPIO_AF_15: OUT.             
  * @note  The pin should already been configured in Alternate Function mode(AF)
  *        using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note  Refer to the Alternate function mapping table in the device datasheet 
  *        for the detailed mapping of the system and peripherals alternate 
  *        function I/O pins.
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
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
