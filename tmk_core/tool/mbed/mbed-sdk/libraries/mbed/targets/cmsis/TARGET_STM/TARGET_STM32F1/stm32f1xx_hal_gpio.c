/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   GPIO HAL module driver.
  *         This file provides firmware functions to manage the following 
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *         
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral features #####
  ==============================================================================         
  [..] 
  Subject to the specific hardware characteristics of each I/O port listed in the datasheet, each
  port bit of the General Purpose IO (GPIO) Ports, can be individually configured by software
  in several modes:
  (+) Input mode 
  (+) Analog mode
  (+) Output mode
  (+) Alternate function mode
  (+) External interrupt/event lines

  [..]  
  During and just after reset, the alternate functions and external interrupt  
  lines are not active and the I/O ports are configured in input floating mode.
  
  [..]   
  All GPIO pins have weak internal pull-up and pull-down resistors, which can be 
  activated or not.

  [..]
  In Output or Alternate mode, each IO can be configured on open-drain or push-pull
  type and the IO speed can be selected depending on the VDD value.

  [..]  
  All ports have external interrupt/event capability. To use external interrupt 
  lines, the port must be configured in input mode. All available GPIO pins are 
  connected to the 16 external interrupt/event lines from EXTI0 to EXTI15.
  
  [..]  
  The external interrupt/event controller consists of up to 20 edge detectors in connectivity
  line devices, or 19 edge detectors in other devices for generating event/interrupt requests.
  Each input line can be independently configured to select the type (event or interrupt) and
  the corresponding trigger event (rising or falling or both). Each line can also masked
  independently. A pending register maintains the status line of the interrupt requests
 
                     ##### How to use this driver #####
  ==============================================================================  
 [..]             
   (#) Enable the GPIO APB2 clock using the following function : __HAL_GPIOx_CLK_ENABLE(). 
   
   (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
       (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef structure
       (++) Activate Pull-up, Pull-down resistor using "Pull" member from GPIO_InitTypeDef 
            structure.
       (++) In case of Output or alternate function mode selection: the speed is 
            configured through "Speed" member from GPIO_InitTypeDef structure
       (++) Analog mode is required when a pin is to be used as ADC channel 
            or DAC output.
       (++) In case of external interrupt/event selection the "Mode" member from 
            GPIO_InitTypeDef structure select the type (interrupt or event) and 
            the corresponding trigger event (rising or falling or both).
   
   (#) In case of external interrupt/event mode selection, configure NVIC IRQ priority 
       mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it using
       HAL_NVIC_EnableIRQ().
         
   (#) To get the level of a pin configured in input mode use HAL_GPIO_ReadPin().
            
   (#) To set/reset the level of a pin configured in output mode use 
       HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().
  
   (#) To lock pin configuration until next reset use HAL_GPIO_LockPin().
                 
   (#) During and just after reset, the alternate functions are not 
       active and the GPIO pins are configured in input floating mode (except JTAG
       pins).
  
   (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general purpose 
       (PC14 and PC15, respectively) when the LSE oscillator is off. The LSE has 
       priority over the GPIO function.
  
   (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as 
       general purpose PD0 and PD1, respectively, when the HSE oscillator is off. 
       The HSE has priority over the GPIO function.
  
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO HAL module driver
  * @{
  */

#ifdef HAL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
  
#define GPIO_MODE             ((uint32_t)0x00000003)
#define EXTI_MODE             ((uint32_t)0x10000000)
#define GPIO_MODE_IT          ((uint32_t)0x00010000)
#define GPIO_MODE_EVT         ((uint32_t)0x00020000)
#define RISING_EDGE           ((uint32_t)0x00100000) 
#define FALLING_EDGE          ((uint32_t)0x00200000) 
#define GPIO_OUTPUT_TYPE      ((uint32_t)0x00000010) 
#define GPIO_NUMBER           ((uint32_t)16)

/* Definitions for bit manipulation of CRL and CRH register */
#define  GPIO_CR_MODE_INPUT         ((uint32_t)0x00000000) /*!< 00: Input mode (reset state)  */
#define  GPIO_CR_CNF_ANALOG         ((uint32_t)0x00000000) /*!< 00: Analog mode  */
#define  GPIO_CR_CNF_INPUT_FLOATING ((uint32_t)0x00000004) /*!< 01: Floating input (reset state)  */
#define  GPIO_CR_CNF_INPUT_PU_PD    ((uint32_t)0x00000008) /*!< 10: Input with pull-up / pull-down  */
#define  GPIO_CR_CNF_GP_OUTPUT_PP   ((uint32_t)0x00000000) /*!< 00: General purpose output push-pull  */
#define  GPIO_CR_CNF_GP_OUTPUT_OD   ((uint32_t)0x00000004) /*!< 01: General purpose output Open-drain  */
#define  GPIO_CR_CNF_AF_OUTPUT_PP   ((uint32_t)0x00000008) /*!< 10: Alternate function output Push-pull  */
#define  GPIO_CR_CNF_AF_OUTPUT_OD   ((uint32_t)0x0000000C) /*!< 11: Alternate function output Open-drain  */
 
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Exported_Functions GPIO Exported Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization and deinitialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim    
 ===============================================================================
              ##### Initialization and deinitialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize and de-initialize the GPIOs
    to be ready for use.
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position;
  uint32_t ioposition = 0x00;
  uint32_t iocurrent = 0x00;
  uint32_t temp = 0x00;
  uint32_t config = 0x00;
  __IO uint32_t *configregister; /* Store the address of CRL or CRH register based on pin number */
  uint32_t registeroffset = 0; /* offset used during computation of CNF and MODE bits placement inside CRL or CRH register */
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));
  assert_param(IS_GPIO_PULL(GPIO_Init->Pull)); 

  /* Configure the port pins */
  for (position = 0; position < GPIO_NUMBER; position++)
  {
    /* Get the IO position */
    ioposition = ((uint32_t)0x01) << position;
    
    /* Get the current IO position */
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;

    if (iocurrent == ioposition)
    {
      /* Check the Alternate function parameters */
      assert_param(IS_GPIO_AF_INSTANCE(GPIOx));

      /* Based on the required mode, filling config variable with MODEy[1:0] and CNFy[3:2] corresponding bits */
      switch (GPIO_Init->Mode)
      {
        /* If we are configuring the pin in OUTPUT push-pull mode */
        case GPIO_MODE_OUTPUT_PP:
          /* Check the GPIO speed parameter */
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_PP;
          break;
          
        /* If we are configuring the pin in OUTPUT open-drain mode */
        case GPIO_MODE_OUTPUT_OD:
          /* Check the GPIO speed parameter */
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_OD;
          break;
          
        /* If we are configuring the pin in ALTERNATE FUNCTION push-pull mode */
        case GPIO_MODE_AF_PP:
          /* Check the GPIO speed parameter */
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_PP;
          break;
          
        /* If we are configuring the pin in ALTERNATE FUNCTION open-drain mode */
        case GPIO_MODE_AF_OD:
          /* Check the GPIO speed parameter */
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_OD;
          break;
          
        /* If we are configuring the pin in INPUT (also applicable to EVENT and IT mode) */
        case GPIO_MODE_INPUT:
        case GPIO_MODE_IT_RISING:
        case GPIO_MODE_IT_FALLING:
        case GPIO_MODE_IT_RISING_FALLING:
        case GPIO_MODE_EVT_RISING:
        case GPIO_MODE_EVT_FALLING:
        case GPIO_MODE_EVT_RISING_FALLING:
          /* Check the GPIO pull parameter */
          assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
          if(GPIO_Init->Pull == GPIO_NOPULL)
          {  
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_FLOATING;
          }
          else if(GPIO_Init->Pull == GPIO_PULLUP)
          {
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;
            
            /* Set the corresponding ODR bit */
            GPIOx->BSRR = ioposition;
          }
          else /* GPIO_PULLDOWN */
          {
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;
            
            /* Reset the corresponding ODR bit */
            GPIOx->BRR = ioposition;
          }
          break; 
          
        /* If we are configuring the pin in INPUT analog mode */
        case GPIO_MODE_ANALOG:
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_ANALOG;
          break;
        
        /* Parameters are checked with assert_param */
        default:
          break;
      }
      
      /* Check if the current bit belongs to first half or last half of the pin count number
       in order to address CRH or CRL register*/
      configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;
      registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2) : ((position - 8) << 2);
      
      /* Apply the new configuration of the pin to the register */
      MODIFY_REG((*configregister), ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset ), (config << registeroffset));
      
      /*--------------------- EXTI Mode Configuration ------------------------*/
      /* Configure the External Interrupt or event for the current IO */
      if((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE) 
      {
        /* Enable AFIO Clock */
        __HAL_RCC_AFIO_CLK_ENABLE();
        temp = AFIO->EXTICR[position >> 2];
        CLEAR_BIT(temp, ((uint32_t)0x0F) << (4 * (position & 0x03)));
        SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4 * (position & 0x03)));
        AFIO->EXTICR[position >> 2] = temp;
        

        /* Configure the interrupt mask */
        if((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
        {
          SET_BIT(EXTI->IMR, iocurrent); 
        } 
        else
        {
          CLEAR_BIT(EXTI->IMR, iocurrent); 
        } 
        
        /* Configure the event mask */
        if((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
        {
          SET_BIT(EXTI->EMR, iocurrent); 
        } 
        else
        {
          CLEAR_BIT(EXTI->EMR, iocurrent); 
        }
        
        /* Enable or disable the rising trigger */
        if((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
        {
          SET_BIT(EXTI->RTSR, iocurrent); 
        } 
        else
        {
          CLEAR_BIT(EXTI->RTSR, iocurrent); 
        }
        
        /* Enable or disable the falling trigger */
        if((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
        {
          SET_BIT(EXTI->FTSR, iocurrent); 
        } 
        else
        {
          CLEAR_BIT(EXTI->FTSR, iocurrent); 
        }
      }
    }
  }
}

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @retval None
  */
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{ 
  uint32_t position = 0x00;
  uint32_t iocurrent = 0x00;
  uint32_t tmp = 0x00;
  __IO uint32_t *configregister; /* Store the address of CRL or CRH register based on pin number */
  uint32_t registeroffset = 0;
 
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Configure the port pins */
  while ((GPIO_Pin >> position) != 0)
  {
    /* Get current io position */
    iocurrent = (GPIO_Pin) & ((uint32_t)1 << position);

    if (iocurrent)
    {
      /*------------------------- GPIO Mode Configuration --------------------*/
      /* Check if the current bit belongs to first half or last half of the pin count number
       in order to address CRH or CRL register */
      configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;
      registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2) : ((position - 8) << 2);
      
      /* CRL/CRH default value is floating input(0x04) shifted to correct position */
      MODIFY_REG(*configregister, ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset ), GPIO_CRL_CNF0_0 << registeroffset);
      
      /* ODR default value is 0 */
      CLEAR_BIT(GPIOx->ODR, iocurrent);
      
      /*------------------------- EXTI Mode Configuration --------------------*/
      /* Clear the External Interrupt or Event for the current IO */
      
      tmp = AFIO->EXTICR[position >> 2];
      tmp &= (((uint32_t)0x0F) << (4 * (position & 0x03)));
      if(tmp == (GPIO_GET_INDEX(GPIOx) << (4 * (position & 0x03))))
      {
        tmp = ((uint32_t)0x0F) << (4 * (position & 0x03));
        CLEAR_BIT(AFIO->EXTICR[position >> 2], tmp);
          
        /* Clear EXTI line configuration */
        CLEAR_BIT(EXTI->IMR, (uint32_t)iocurrent);
        CLEAR_BIT(EXTI->EMR, (uint32_t)iocurrent);
        
        /* Clear Rising Falling edge configuration */
        CLEAR_BIT(EXTI->RTSR, (uint32_t)iocurrent);
        CLEAR_BIT(EXTI->FTSR, (uint32_t)iocurrent);
      }
    }
    
    position++;
  }
}

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions 
 *  @brief   GPIO Read and Write 
 *
@verbatim   
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the GPIOs.

@endverbatim
  * @{
  */
/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * 
  * @note   This function uses GPIOx_BSRR register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *               
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @param  PinState: specifies the value to be written to the selected bit.
  *          This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_BIT_RESET: to clear the port pin
  *            @arg GPIO_BIT_SET: to set the port pin
  * @retval None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if(PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16;
  }
}

/**
  * @brief  Toggles the specified GPIO pin
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral 
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}

/**
* @brief  Locks GPIO Pins configuration registers.
* @note   The locking mechanism allows the IO configuration to be frozen. When the LOCK sequence
*         has been applied on a port bit, it is no longer possible to modify the value of the port bit until
*         the next reset.
* @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
* @param  GPIO_Pin: specifies the port bit to be locked.
*         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
* @retval None
*/
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = GPIO_LCKR_LCKK;

  /* Check the parameters */
  assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Apply lock key write sequence */
  SET_BIT(tmp, GPIO_Pin);
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
  GPIOx->LCKR = GPIO_Pin;
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;

  if((uint32_t)(GPIOx->LCKR & GPIO_LCKR_LCKK))
  {
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief This function handles EXTI interrupt request.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != RESET) 
  { 
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Callback(GPIO_Pin);
  }
}

/**
  * @brief  EXTI line detection callback
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */ 
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_GPIO_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
