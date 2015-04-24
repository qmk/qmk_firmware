/**
  ******************************************************************************
  * @file    stm32f30x_usart.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Universal synchronous asynchronous receiver
  *          transmitter (USART):
  *           + Initialization and Configuration
  *           + STOP Mode
  *           + AutoBaudRate
  *           + Data transfers
  *           + Multi-Processor Communication
  *           + LIN mode
  *           + Half-duplex mode
  *           + Smartcard mode
  *           + IrDA mode
  *           + RS485 mode  
  *           + DMA transfers management
  *           + Interrupts and flags management
  *           
  *  @verbatim  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
      [..]
          (#) Enable peripheral clock using RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE)
             function for USART1 or using RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE)
             function for USART2, USART3, UART4 and UART5.
          (#)  According to the USART mode, enable the GPIO clocks using
              RCC_AHBPeriphClockCmd() function. (The I/O can be TX, RX, CTS,
              or and SCLK).
          (#) Peripheral's alternate function:
              (++) Connect the pin to the desired peripherals' Alternate
                   Function (AF) using GPIO_PinAFConfig() function.
              (++) Configure the desired pin in alternate function by:
                   GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
              (++) Select the type, pull-up/pull-down and output speed via
                   GPIO_PuPd, GPIO_OType and GPIO_Speed members.
              (++) Call GPIO_Init() function.
          (#) Program the Baud Rate, Word Length , Stop Bit, Parity, Hardware
             flow control and Mode(Receiver/Transmitter) using the SPI_Init()
             function.
          (#) For synchronous mode, enable the clock and program the polarity,
             phase and last bit using the USART_ClockInit() function.
          (#) Enable the USART using the USART_Cmd() function.
          (#) Enable the NVIC and the corresponding interrupt using the function
             USART_ITConfig() if you need to use interrupt mode.
          (#) When using the DMA mode:
              (++) Configure the DMA using DMA_Init() function.
              (++) Activate the needed channel Request using USART_DMACmd() function.
          (#) Enable the DMA using the DMA_Cmd() function, when using DMA mode.
      [..]
              Refer to Multi-Processor, LIN, half-duplex, Smartcard, IrDA sub-sections
              for more details.

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
#include "stm32f30x_usart.h"
#include "stm32f30x_rcc.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup USART 
  * @brief USART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*!< USART CR1 register clear Mask ((~(uint32_t)0xFFFFE6F3)) */
#define CR1_CLEAR_MASK            ((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
                                              USART_CR1_PS | USART_CR1_TE | \
                                              USART_CR1_RE))

/*!< USART CR2 register clock bits clear Mask ((~(uint32_t)0xFFFFF0FF)) */
#define CR2_CLOCK_CLEAR_MASK      ((uint32_t)(USART_CR2_CLKEN | USART_CR2_CPOL | \
                                              USART_CR2_CPHA | USART_CR2_LBCL))

/*!< USART CR3 register clear Mask ((~(uint32_t)0xFFFFFCFF)) */
#define CR3_CLEAR_MASK            ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/*!< USART Interrupts mask */
#define IT_MASK                   ((uint32_t)0x000000FF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup USART_Private_Functions
  * @{
  */

/** @defgroup USART_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions 
 *
@verbatim 
 ===============================================================================
           ##### Initialization and Configuration functions #####
 ===============================================================================  
  [..]
      This subsection provides a set of functions allowing to initialize the USART 
      in asynchronous and in synchronous modes.
       (+) For the asynchronous mode only these parameters can be configured: 
            (++) Baud Rate.
            (++) Word Length. 
            (++) Stop Bit.
            (++) Parity: If the parity is enabled, then the MSB bit of the data written
                 in the data register is transmitted but is changed by the parity bit.
                 Depending on the frame length defined by the M bit (8-bits or 9-bits),
                 the possible USART frame formats are as listed in the following table:
    [..]
   +-------------------------------------------------------------+     
   |   M bit |  PCE bit  |            USART frame                |
   |---------------------|---------------------------------------|             
   |    0    |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|  
   |    1    |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|  
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+            
    [..]
           (++) Hardware flow control.
           (++) Receiver/transmitter modes.
    [..] The USART_Init() function follows the USART  asynchronous configuration 
         procedure(details for the procedure are available in reference manual.
        (+) For the synchronous mode in addition to the asynchronous mode parameters
            these parameters should be also configured:
            (++) USART Clock Enabled.
            (++) USART polarity.
            (++) USART phase.
            (++) USART LastBit.
    [..] These parameters can be configured using the USART_ClockInit() function.

@endverbatim
  * @{
  */
  
/**
  * @brief  Deinitializes the USARTx peripheral registers to their default reset values.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @retval None
  */
void USART_DeInit(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  if (USARTx == USART1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
  }
  else if (USARTx == USART2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
  }
  else if (USARTx == USART3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
  }
  else if (USARTx == UART4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
  }
  else
  {
    if  (USARTx == UART5)
    {
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    }
  }
}

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         that contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint32_t divider = 0, apbclock = 0, tmpreg = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;
  
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
  
  /* Disable USART */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  
  /*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);
  
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;
  
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
  
  /*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);
  
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
    USART_InitStruct->USART_Mode;
  
  /* Write to USART CR1 */
  USARTx->CR1 = tmpreg;
  
  /*---------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);
  
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  
  /* Write to USART CR3 */
  USARTx->CR3 = tmpreg;
  
  /*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  
  if (USARTx == USART1)
  {
    apbclock = RCC_ClocksStatus.USART1CLK_Frequency;
  }
  else if (USARTx == USART2)
  {
    apbclock = RCC_ClocksStatus.USART2CLK_Frequency;
  }
  else if (USARTx == USART3)
  {
    apbclock = RCC_ClocksStatus.USART3CLK_Frequency;
  }
  else if (USARTx == UART4)
  {
    apbclock = RCC_ClocksStatus.UART4CLK_Frequency;
  }
  else 
  {
    apbclock = RCC_ClocksStatus.UART5CLK_Frequency;
  }  
  
  /* Determine the integer part */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* (divider * 10) computing in case Oversampling mode is 8 Samples */
    divider = (uint32_t)((2 * apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((2 * apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* (divider * 10) computing in case Oversampling mode is 16 Samples */
    divider = (uint32_t)((apbclock) / (USART_InitStruct->USART_BaudRate));
    tmpreg  = (uint32_t)((apbclock) % (USART_InitStruct->USART_BaudRate));
  }
  
  /* round the divider : if fractional part i greater than 0.5 increment divider */
  if (tmpreg >=  (USART_InitStruct->USART_BaudRate) / 2)
  {
    divider++;
  } 
  
  /* Implement the divider in case Oversampling mode is 8 Samples */
  if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
  {
    /* get the LSB of divider and shift it to the right by 1 bit */
    tmpreg = (divider & (uint16_t)0x000F) >> 1;
    
    /* update the divider value */
    divider = (divider & (uint16_t)0xFFF0) | tmpreg;
  }
  
  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)divider;
}

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WordLength_8b;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

/**
  * @brief  Initializes the USARTx peripheral Clock according to the
  *         specified parameters in the USART_ClockInitStruct.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure that contains the configuration information for the specified
  *         USART peripheral.
  * @retval None
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
  assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
  assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));
/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear CLKEN, CPOL, CPHA, LBCL and SSM bits */
  tmpreg &= (uint32_t)~((uint32_t)CR2_CLOCK_CLEAR_MASK);
  /* Configure the USART Clock, CPOL, CPHA, LastBit and SSM ------------*/
  /* Set CLKEN bit according to USART_Clock value */
  /* Set CPOL bit according to USART_CPOL value */
  /* Set CPHA bit according to USART_CPHA value */
  /* Set LBCL bit according to USART_LastBit value */
  tmpreg |= (uint32_t)(USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL | 
                       USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit);
  /* Write to USART CR2 */
  USARTx->CR2 = tmpreg;
}

/**
  * @brief  Fills each USART_ClockInitStruct member with its default value.
  * @param  USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
  USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * @brief  Enables or disables the specified USART peripheral.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART by setting the UE bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_UE;
  }
  else
  {
    /* Disable the selected USART by clearing the UE bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
  }
}

/**
  * @brief  Enables or disables the USART's transmitter or receiver.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_Direction: specifies the USART direction.
  *         This parameter can be any combination of the following values:
  *         @arg USART_Mode_Tx: USART Transmitter
  *         @arg USART_Mode_Rx: USART Receiver
  * @param  NewState: new state of the USART transfer direction.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint32_t USART_DirectionMode, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MODE(USART_DirectionMode));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the USART's transfer interface by setting the TE and/or RE bits 
       in the USART CR1 register */
    USARTx->CR1 |= USART_DirectionMode;
  }
  else
  {
    /* Disable the USART's transfer interface by clearing the TE and/or RE bits
       in the USART CR3 register */
    USARTx->CR1 &= (uint32_t)~USART_DirectionMode;
  }
}

/**
  * @brief  Enables or disables the USART's 8x oversampling mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART 8x oversampling mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @note
  *   This function has to be called before calling USART_Init()
  *   function in order to have correct baudrate Divider value.
  * @retval None
  */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the 8x Oversampling mode by setting the OVER8 bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_OVER8;
  }
  else
  {
    /* Disable the 8x Oversampling mode by clearing the OVER8 bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_OVER8);
  }
}

/**
  * @brief  Enables or disables the USART's one bit sampling method.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART one bit sampling method.
  *         This parameter can be: ENABLE or DISABLE.
  * @note
  *   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the one bit method by setting the ONEBIT bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_ONEBIT;
  }
  else
  {
    /* Disable the one bit method by clearing the ONEBIT bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT);
  }
}

/**
  * @brief  Enables or disables the USART's most significant bit first 
  *         transmitted/received following the start bit.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART most significant bit first
  *         transmitted/received following the start bit.
  *         This parameter can be: ENABLE or DISABLE.
  * @note
  *   This function has to be called before calling USART_Cmd() function. 
  * @retval None
  */
void USART_MSBFirstCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the most significant bit first transmitted/received following the
       start bit by setting the MSBFIRST bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_MSBFIRST;
  }
  else
  {
    /* Disable the most significant bit first transmitted/received following the
       start bit by clearing the MSBFIRST bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_MSBFIRST);
  }
}

/**
  * @brief  Enables or disables the binary data inversion.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new defined levels for the USART data.
  *         This parameter can be: ENABLE or DISABLE.
  *   @arg  ENABLE: Logical data from the data register are send/received in negative
  *         logic. (1=L, 0=H). The parity bit is also inverted.
  *   @arg  DISABLE: Logical data from the data register are send/received in positive
  *         logic. (1=H, 0=L) 
  * @note
  *   This function has to be called before calling USART_Cmd() function. 
  * @retval None
  */
void USART_DataInvCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the binary data inversion feature by setting the DATAINV bit in
       the CR2 register */
    USARTx->CR2 |= USART_CR2_DATAINV;
  }
  else
  {
    /* Disable the binary data inversion feature by clearing the DATAINV bit in
       the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_DATAINV);
  }
}

/**
  * @brief  Enables or disables the Pin(s) active level inversion.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_InvPin: specifies the USART pin(s) to invert.
  *         This parameter can be any combination of the following values:
  *         @arg USART_InvPin_Tx: USART Tx pin active level inversion.
  *         @arg USART_InvPin_Rx: USART Rx pin active level inversion.
  * @param  NewState: new active level status for the USART pin(s).
  *         This parameter can be: ENABLE or DISABLE.
  *          - ENABLE: pin(s) signal values are inverted (Vdd =0, Gnd =1).
  *          - DISABLE: pin(s) signal works using the standard logic levels (Vdd =1, Gnd =0).
  * @note
  *   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_InvPinCmd(USART_TypeDef* USARTx, uint32_t USART_InvPin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_INVERSTION_PIN(USART_InvPin));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the active level inversion for selected pins by setting the TXINV 
       and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 |= USART_InvPin;
  }
  else
  {
    /* Disable the active level inversion for selected requests by clearing the 
       TXINV and/or RXINV bits in the USART CR2 register */
    USARTx->CR2 &= (uint32_t)~USART_InvPin;
  }
}

/**
  * @brief  Enables or disables the swap Tx/Rx pins.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USARTx TX/RX pins pinout.
  *         This parameter can be: ENABLE or DISABLE.
  *         @arg ENABLE: The TX and RX pins functions are swapped.
  *         @arg DISABLE: TX/RX pins are used as defined in standard pinout
  * @note
  *   This function has to be called before calling USART_Cmd() function.
  * @retval None
  */
void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the SWAP feature by setting the SWAP bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_SWAP;
  }
  else
  {
    /* Disable the SWAP feature by clearing the SWAP bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_SWAP);
  }
}

/**
  * @brief  Enables or disables the receiver Time Out feature.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USARTx receiver Time Out.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ReceiverTimeOutCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the receiver time out feature by setting the RTOEN bit in the CR2 
       register */
    USARTx->CR2 |= USART_CR2_RTOEN;
  }
  else
  {
    /* Disable the receiver time out feature by clearing the RTOEN bit in the CR2 
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_RTOEN);
  }
}

/**
  * @brief  Sets the receiver Time Out value.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_ReceiverTimeOut: specifies the Receiver Time Out value.
  * @retval None
  */
void USART_SetReceiverTimeOut(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut)
{    
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_TIMEOUT(USART_ReceiverTimeOut));

  /* Clear the receiver Time Out value by clearing the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_RTO);
  /* Set the receiver Time Out value by setting the RTO[23:0] bits in the RTOR
     register  */
  USARTx->RTOR |= USART_ReceiverTimeOut;
}

/**
  * @brief  Sets the system clock prescaler.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_Prescaler: specifies the prescaler clock.  
  * @note
  *   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Clear the USART prescaler */
  USARTx->GTPR &= USART_GTPR_GT;
  /* Set the USART prescaler */
  USARTx->GTPR |= USART_Prescaler;
}

/**
  * @}
  */


/** @defgroup USART_Group2 STOP Mode functions
 *  @brief   STOP Mode functions
 *
@verbatim
 ===============================================================================
                        ##### STOP Mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         WakeUp from STOP mode.

    [..] The USART is able to WakeUp from Stop Mode if USART clock is set to HSI
         or LSI.
         
    [..] The WakeUp source is configured by calling USART_StopModeWakeUpSourceConfig()
         function.
         
    [..] After configuring the source of WakeUp and before entering in Stop Mode 
         USART_STOPModeCmd() function should be called to allow USART WakeUp.
                           
@endverbatim
  * @{
  */
  
/**
  * @brief  Enables or disables the specified USART peripheral in STOP Mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USARTx peripheral state in stop mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @note
  *   This function has to be called when USART clock is set to HSI or LSE.
  * @retval None
  */
void USART_STOPModeCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected USART in STOP mode by setting the UESM bit in the CR1
       register */
    USARTx->CR1 |= USART_CR1_UESM;
  }
  else
  {
    /* Disable the selected USART in STOP mode by clearing the UE bit in the CR1
       register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UESM);
  }
}

/**
  * @brief  Selects the USART WakeUp method form stop mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_WakeUp: specifies the selected USART wakeup method.
  *         This parameter can be one of the following values:
  *         @arg USART_WakeUpSource_AddressMatch: WUF active on address match.
  *         @arg USART_WakeUpSource_StartBit: WUF active on Start bit detection.
  *         @arg USART_WakeUpSource_RXNE: WUF active on RXNE.
  * @note
  *   This function has to be called before calling USART_Cmd() function.  
  * @retval None
  */
void USART_StopModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_STOPMODE_WAKEUPSOURCE(USART_WakeUpSource));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_WUS);
  USARTx->CR3 |= USART_WakeUpSource;
}

/**
  * @}
  */


/** @defgroup USART_Group3 AutoBaudRate functions
 *  @brief   AutoBaudRate functions 
 *
@verbatim
 ===============================================================================
                       ##### AutoBaudRate functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         the AutoBaudRate detections.
         
    [..] Before Enabling AutoBaudRate detection using USART_AutoBaudRateCmd ()
         The character patterns used to calculate baudrate must be chosen by calling 
         USART_AutoBaudRateConfig() function. These function take as parameter :
        (#)USART_AutoBaudRate_StartBit : any character starting with a bit 1.
        (#)USART_AutoBaudRate_FallingEdge : any character starting with a 10xx bit pattern. 
                          
    [..] At any later time, another request for AutoBaudRate detection can be performed
         using USART_RequestCmd() function.
         
    [..] The AutoBaudRate detection is monitored by the status of ABRF flag which indicate
         that the AutoBaudRate detection is completed. In addition to ABRF flag, the ABRE flag
         indicate that this procedure is completed without success. USART_GetFlagStatus () 
         function should be used to monitor the status of these flags.  
             
@endverbatim
  * @{
  */
  
/**
  * @brief  Enables or disables the Auto Baud Rate.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USARTx auto baud rate.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_AutoBaudRateCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the auto baud rate feature by setting the ABREN bit in the CR2 
       register */
    USARTx->CR2 |= USART_CR2_ABREN;
  }
  else
  {
    /* Disable the auto baud rate feature by clearing the ABREN bit in the CR2 
       register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABREN);
  }
}

/**
  * @brief  Selects the USART auto baud rate method.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_AutoBaudRate: specifies the selected USART auto baud rate method.
  *         This parameter can be one of the following values:
  *         @arg USART_AutoBaudRate_StartBit: Start Bit duration measurement.
  *         @arg USART_AutoBaudRate_FallingEdge: Falling edge to falling edge measurement.
  *         @arg USART_AutoBaudRate_0x7FFrame: 0x7F frame.
  *         @arg USART_AutoBaudRate_0x55Frame: 0x55 frame.
  * @note
  *   This function has to be called before calling USART_Cmd() function. 
  * @retval None
  */
void USART_AutoBaudRateConfig(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_AUTOBAUDRATE_MODE(USART_AutoBaudRate));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ABRMODE);
  USARTx->CR2 |= USART_AutoBaudRate;
}

/**
  * @}
  */


/** @defgroup USART_Group4 Data transfers functions
 *  @brief   Data transfers functions 
 *
@verbatim
 ===============================================================================
                    ##### Data transfers functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage 
         the USART data transfers.
    [..] During an USART reception, data shifts in least significant bit first 
         through the RX pin. When a transmission is taking place, a write instruction to 
         the USART_TDR register stores the data in the shift register.
    [..] The read access of the USART_RDR register can be done using 
         the USART_ReceiveData() function and returns the RDR value.
         Whereas a write access to the USART_TDR can be done using USART_SendData()
         function and stores the written data into TDR.

@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the USARTx peripheral.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  Data: the data to transmit.
  * @retval None
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA(Data)); 

  /* Transmit Data */
  USARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the USARTx peripheral.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @retval The received data.
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Receive Data */
  return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

/**
  * @}
  */

/** @defgroup USART_Group5 MultiProcessor Communication functions
 *  @brief   Multi-Processor Communication functions 
 *
@verbatim   
 ===============================================================================
             ##### Multi-Processor Communication functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         multiprocessor communication.
    [..] For instance one of the USARTs can be the master, its TX output is
         connected to the RX input of the other USART. The others are slaves,
         their respective TX outputs are logically ANDed together and connected 
         to the RX input of the master. USART multiprocessor communication is 
         possible through the following procedure:
         (#) Program the Baud rate, Word length = 9 bits, Stop bits, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Configures the USART address using the USART_SetAddress() function.
         (#) Configures the wake up methode (USART_WakeUp_IdleLine or 
             USART_WakeUp_AddressMark) using USART_WakeUpConfig() function only 
             for the slaves.
         (#) Enable the USART using the USART_Cmd() function.
         (#) Enter the USART slaves in mute mode using USART_ReceiverWakeUpCmd() 
             function.
    [..] The USART Slave exit from mute mode when receive the wake up condition.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the address of the USART node.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_Address: Indicates the address of the USART node.
  * @retval None
  */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  /* Clear the USART address */
  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADD);
  /* Set the USART address node */
  USARTx->CR2 |=((uint32_t)USART_Address << (uint32_t)0x18);
}

/**
  * @brief  Enables or disables the USART's mute mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART mute mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_MuteModeCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the USART mute mode by setting the MME bit in the CR1 register */
    USARTx->CR1 |= USART_CR1_MME;
  }
  else
  {
    /* Disable the USART mute mode by clearing the MME bit in the CR1 register */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_MME);
  }
}

/**
  * @brief  Selects the USART WakeUp method from mute mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_WakeUp: specifies the USART wakeup method.
  *         This parameter can be one of the following values:
  *         @arg USART_WakeUp_IdleLine: WakeUp by an idle line detection
  *         @arg USART_WakeUp_AddressMark: WakeUp by an address mark
  * @retval None
  */
void USART_MuteModeWakeUpConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUp)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_MUTEMODE_WAKEUP(USART_WakeUp));

  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_WAKE);
  USARTx->CR1 |= USART_WakeUp;
}

/**
  * @brief  Configure the the USART Address detection length.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_AddressLength: specifies the USART address length detection.
  *         This parameter can be one of the following values:
  *         @arg USART_AddressLength_4b: 4-bit address length detection 
  *         @arg USART_AddressLength_7b: 7-bit address length detection 
  * @retval None
  */
void USART_AddressDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_AddressLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS_DETECTION(USART_AddressLength));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_ADDM7);
  USARTx->CR2 |= USART_AddressLength;
}

/**
  * @}
  */

/** @defgroup USART_Group6 LIN mode functions
 *  @brief   LIN mode functions 
 *
@verbatim   
 ===============================================================================
                       ##### LIN mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART 
         LIN Mode communication.
    [..] In LIN mode, 8-bit data format with 1 stop bit is required in accordance 
         with the LIN standard.
    [..] Only this LIN Feature is supported by the USART IP:
         (+) LIN Master Synchronous Break send capability and LIN slave break 
             detection capability :  13-bit break generation and 10/11 bit break 
             detection.
    [..] USART LIN Master transmitter communication is possible through the 
         following procedure:
         (#) Program the Baud rate, Word length = 8bits, Stop bits = 1bit, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Enable the LIN mode using the USART_LINCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
         (#) Send the break character using USART_SendBreak() function.
    [..] USART LIN Master receiver communication is possible through the 
         following procedure:
         (#) Program the Baud rate, Word length = 8bits, Stop bits = 1bit, Parity, 
             Mode transmitter or Mode receiver and hardware flow control values 
             using the USART_Init() function.
         (#) Configures the break detection length 
             using the USART_LINBreakDetectLengthConfig() function.
         (#) Enable the LIN mode using the USART_LINCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
         [..]
         (@) In LIN mode, the following bits must be kept cleared:
             (+@) CLKEN in the USART_CR2 register.
             (+@) STOP[1:0], SCEN, HDSEL and IREN in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the USART LIN Break detection length.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_LINBreakDetectLength: specifies the LIN break detection length.
  *         This parameter can be one of the following values:
  *         @arg USART_LINBreakDetectLength_10b: 10-bit break detection
  *         @arg USART_LINBreakDetectLength_11b: 11-bit break detection
  * @retval None
  */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint32_t USART_LINBreakDetectLength)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));

  USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_LBDL);
  USARTx->CR2 |= USART_LINBreakDetectLength;  
}

/**
  * @brief  Enables or disables the USART's LIN mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART LIN mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LIN mode by setting the LINEN bit in the CR2 register */
    USARTx->CR2 |= USART_CR2_LINEN;
  }
  else
  {
    /* Disable the LIN mode by clearing the LINEN bit in the CR2 register */
    USARTx->CR2 &= (uint32_t)~((uint32_t)USART_CR2_LINEN);
  }
}

/**
  * @}
  */

/** @defgroup USART_Group7 Halfduplex mode function
 *  @brief   Half-duplex mode function 
 *
@verbatim   
 ===============================================================================
                   ##### Half-duplex mode function #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         Half-duplex communication.
    [..] The USART can be configured to follow a single-wire half-duplex protocol 
         where the TX and RX lines are internally connected.
    [..] USART Half duplex communication is possible through the following procedure:
         (#) Program the Baud rate, Word length, Stop bits, Parity, Mode transmitter 
             or Mode receiver and hardware flow control values using the USART_Init()
            function.
         (#) Configures the USART address using the USART_SetAddress() function.
         (#) Enable the half duplex mode using USART_HalfDuplexCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
         [..]
         (@) The RX pin is no longer used.
         (@) In Half-duplex mode the following bits must be kept cleared:
             (+@) LINEN and CLKEN bits in the USART_CR2 register.
             (+@) SCEN and IREN bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's Half Duplex communication.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the USART Communication.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_HDSEL;
  }
  else
  {
    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_HDSEL);
  }
}

/**
  * @}
  */


/** @defgroup USART_Group8 Smartcard mode functions
 *  @brief   Smartcard mode functions 
 *
@verbatim   
 ===============================================================================
                     ##### Smartcard mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         Smartcard communication.
    [..] The Smartcard interface is designed to support asynchronous protocol 
         Smartcards as defined in the ISO 7816-3 standard. The USART can provide 
         a clock to the smartcard through the SCLK output. In smartcard mode, 
         SCLK is not associated to the communication but is simply derived from 
         the internal peripheral input clock through a 5-bit prescaler.
    [..] Smartcard communication is possible through the following procedure:
         (#) Configures the Smartcard Prsecaler using the USART_SetPrescaler() 
             function.
         (#) Configures the Smartcard Guard Time using the USART_SetGuardTime() 
             function.
         (#) Program the USART clock using the USART_ClockInit() function as following:
             (++) USART Clock enabled.
             (++) USART CPOL Low.
             (++) USART CPHA on first edge.
             (++) USART Last Bit Clock Enabled.
         (#) Program the Smartcard interface using the USART_Init() function as 
             following:
             (++) Word Length = 9 Bits.
             (++) 1.5 Stop Bit.
             (++) Even parity.
             (++) BaudRate = 12096 baud.
             (++) Hardware flow control disabled (RTS and CTS signals).
             (++) Tx and Rx enabled
         (#) Optionally you can enable the parity error interrupt using 
             the USART_ITConfig() function.
         (#) Enable the Smartcard NACK using the USART_SmartCardNACKCmd() function.
         (#) Enable the Smartcard interface using the USART_SmartCardCmd() function.
         (#) Enable the USART using the USART_Cmd() function.
    [..] 
  Please refer to the ISO 7816-3 specification for more details.
    [..] 
         (@) It is also possible to choose 0.5 stop bit for receiving but it is 
             recommended to use 1.5 stop bits for both transmitting and receiving 
             to avoid switching between the two configurations.
         (@) In smartcard mode, the following bits must be kept cleared:
             (+@) LINEN bit in the USART_CR2 register.
             (+@) HDSEL and IREN bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Sets the specified USART guard time.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3.
  * @param  USART_GuardTime: specifies the guard time.
  * @retval None
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the USART Guard time */
  USARTx->GTPR &= USART_GTPR_PSC;
  /* Set the USART guard time */
  USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * @brief  Enables or disables the USART's Smart Card mode.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3.
  * @param  NewState: new state of the Smart Card mode.
  *         This parameter can be: ENABLE or DISABLE.      
  * @retval None
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the SC mode by setting the SCEN bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_SCEN;
  }
  else
  {
    /* Disable the SC mode by clearing the SCEN bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_SCEN);
  }
}

/**
  * @brief  Enables or disables NACK transmission.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3.
  * @param  NewState: new state of the NACK transmission.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the NACK transmission by setting the NACK bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_NACK;
  }
  else
  {
    /* Disable the NACK transmission by clearing the NACK bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_NACK);
  }
}

/**
  * @brief  Sets the Smart Card number of retries in transmit and receive.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3.
  * @param  USART_AutoCount: specifies the Smart Card auto retry count.
  * @retval None
  */
void USART_SetAutoRetryCount(USART_TypeDef* USARTx, uint8_t USART_AutoCount)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));
  assert_param(IS_USART_AUTO_RETRY_COUNTER(USART_AutoCount));
  /* Clear the USART auto retry count */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_SCARCNT);
  /* Set the USART auto retry count*/
  USARTx->CR3 |= (uint32_t)((uint32_t)USART_AutoCount << 0x11);
}

/**
  * @brief  Sets the Smart Card Block length.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3.
  * @param  USART_BlockLength: specifies the Smart Card block length.
  * @retval None
  */
void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength)
{    
  /* Check the parameters */
  assert_param(IS_USART_123_PERIPH(USARTx));

  /* Clear the Smart card block length */
  USARTx->RTOR &= (uint32_t)~((uint32_t)USART_RTOR_BLEN);
  /* Set the Smart Card block length */
  USARTx->RTOR |= (uint32_t)((uint32_t)USART_BlockLength << 0x18);
}

/**
  * @}
  */

/** @defgroup USART_Group9 IrDA mode functions
 *  @brief   IrDA mode functions 
 *
@verbatim   
 ===============================================================================
                        ##### IrDA mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         IrDA communication.
    [..] IrDA is a half duplex communication protocol. If the Transmitter is busy, 
         any data on the IrDA receive line will be ignored by the IrDA decoder 
         and if the Receiver is busy, data on the TX from the USART to IrDA will 
         not be encoded by IrDA. While receiving data, transmission should be 
         avoided as the data to be transmitted could be corrupted.
    [..] IrDA communication is possible through the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity, 
             Transmitter/Receiver modes and hardware flow control values using 
             the USART_Init() function.
         (#) Configures the IrDA pulse width by configuring the prescaler using  
             the USART_SetPrescaler() function.
         (#) Configures the IrDA  USART_IrDAMode_LowPower or USART_IrDAMode_Normal 
             mode using the USART_IrDAConfig() function.
         (#) Enable the IrDA using the USART_IrDACmd() function.
         (#) Enable the USART using the USART_Cmd() function.         
    [..]
    (@) A pulse of width less than two and greater than one PSC period(s) may or 
        may not be rejected.
    (@) The receiver set up time should be managed by software. The IrDA physical 
        layer specification specifies a minimum of 10 ms delay between 
        transmission and reception (IrDA is a half duplex protocol).
    (@) In IrDA mode, the following bits must be kept cleared:
        (+@) LINEN, STOP and CLKEN bits in the USART_CR2 register.
        (+@) SCEN and HDSEL bits in the USART_CR3 register.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the USART's IrDA interface.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_IrDAMode: specifies the IrDA mode.
  *         This parameter can be one of the following values:
  *         @arg USART_IrDAMode_LowPower
  *         @arg USART_IrDAMode_Normal
  * @retval None
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_IRLP);
  USARTx->CR3 |= USART_IrDAMode;
}

/**
  * @brief  Enables or disables the USART's IrDA interface. 
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the IrDA mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the IrDA mode by setting the IREN bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_IREN;
  }
  else
  {
    /* Disable the IrDA mode by clearing the IREN bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_IREN);
  }
}
/**
  * @}
  */

/** @defgroup USART_Group10 RS485 mode function
 *  @brief   RS485 mode function 
 *
@verbatim  
 ===============================================================================
                        ##### RS485 mode functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to manage the USART
         RS485 flow control.
    [..] RS485 flow control (Driver enable feature) handling is possible through
         the following procedure:
         (#) Program the Baud rate, Word length = 8 bits, Stop bits, Parity, 
             Transmitter/Receiver modes and hardware flow control values using 
             the USART_Init() function.
         (#) Enable the Driver Enable using the USART_DECmd() function.
         (#) Configures the Driver Enable polarity using the USART_DEPolarityConfig()
             function.
         (#) Configures the Driver Enable assertion time using USART_SetDEAssertionTime() 
             function and deassertion time using the USART_SetDEDeassertionTime()
             function.    
         (#) Enable the USART using the USART_Cmd() function.
      [..]  
       (@) The assertion and dessertion times are expressed in sample time units (1/8 or 
            1/16 bit time, depending on the oversampling rate).
       
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's DE functionality.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  NewState: new state of the driver enable mode.
  *         This parameter can be: ENABLE or DISABLE.      
  * @retval None
  */
void USART_DECmd(USART_TypeDef* USARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the DE functionality by setting the DEM bit in the CR3 register */
    USARTx->CR3 |= USART_CR3_DEM;
  }
  else
  {
    /* Disable the DE functionality by clearing the DEM bit in the CR3 register */
    USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEM);
  }
}

/**
  * @brief  Configures the USART's DE polarity
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_DEPolarity: specifies the DE polarity.
  *         This parameter can be one of the following values:
  *         @arg USART_DEPolarity_Low
  *         @arg USART_DEPolarity_High
  * @retval None
  */
void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_POLARITY(USART_DEPolarity));

  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DEP);
  USARTx->CR3 |= USART_DEPolarity;
}

/**
  * @brief  Sets the specified RS485 DE assertion time
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_AssertionTime: specifies the time between the activation of the DE
  *          signal and the beginning of the start bit
  * @retval None
  */
void USART_SetDEAssertionTime(USART_TypeDef* USARTx, uint32_t USART_DEAssertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEAssertionTime)); 

  /* Clear the DE assertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEAT);
  /* Set the new value for the DE assertion time */
  USARTx->CR1 |=((uint32_t)USART_DEAssertionTime << (uint32_t)0x15);
}

/**
  * @brief  Sets the specified RS485 DE deassertion time
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_DeassertionTime: specifies the time between the middle of the last 
  *         stop bit in a transmitted message and the de-activation of the DE signal
  * @retval None
  */
void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DE_ASSERTION_DEASSERTION_TIME(USART_DEDeassertionTime)); 

  /* Clear the DE deassertion time */
  USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_DEDT);
  /* Set the new value for the DE deassertion time */
  USARTx->CR1 |=((uint32_t)USART_DEDeassertionTime << (uint32_t)0x10);
}

/**
  * @}
  */

/** @defgroup USART_Group11 DMA transfers management functions
 *  @brief   DMA transfers management functions
 *
@verbatim   
 ===============================================================================
               ##### DMA transfers management functions #####
 ===============================================================================
    [..] This section provides two functions that can be used only in DMA mode.
    [..] In DMA Mode, the USART communication can be managed by 2 DMA Channel 
         requests:
         (#) USART_DMAReq_Tx: specifies the Tx buffer DMA transfer request.
         (#) USART_DMAReq_Rx: specifies the Rx buffer DMA transfer request.
    [..] In this Mode it is advised to use the following function:
         (+) void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, 
             FunctionalState NewState).
@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the USART's DMA interface.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4.
  * @param  USART_DMAReq: specifies the DMA request.
  *         This parameter can be any combination of the following values:
  *         @arg USART_DMAReq_Tx: USART DMA transmit request
  *         @arg USART_DMAReq_Rx: USART DMA receive request
  * @param  NewState: new state of the DMA Request sources.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint32_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_1234_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    USARTx->CR3 &= (uint32_t)~USART_DMAReq;
  }
}

/**
  * @brief  Enables or disables the USART's DMA interface when reception error occurs.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4.
  * @param  USART_DMAOnError: specifies the DMA status in case of reception error.
  *         This parameter can be any combination of the following values:
  *         @arg USART_DMAOnError_Enable: DMA receive request enabled when the USART DMA  
  *          reception error is asserted.
  *         @arg USART_DMAOnError_Disable: DMA receive request disabled when the USART DMA 
  *          reception error is asserted.
  * @retval None
  */
void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError)
{
  /* Check the parameters */
  assert_param(IS_USART_1234_PERIPH(USARTx));
  assert_param(IS_USART_DMAONERROR(USART_DMAOnError)); 
  
  /* Clear the DMA Reception error detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_DDRE);
  /* Set the new value for the DMA Reception error detection bit */
  USARTx->CR3 |= USART_DMAOnError;
}

/**
  * @}
  */
  
/** @defgroup USART_Group12 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This subsection provides a set of functions allowing to configure the 
         USART Interrupts sources, Requests and check or clear the flags or pending bits status. 
         The user should identify which mode will be used in his application to 
         manage the communication: Polling mode, Interrupt mode.
         
 *** Polling Mode ***
 ====================
    [..] In Polling Mode, the SPI communication can be managed by these flags:
         (#) USART_FLAG_REACK: to indicate the status of the Receive Enable 
             acknowledge flag
         (#) USART_FLAG_TEACK: to indicate the status of the Transmit Enable 
             acknowledge flag.
         (#) USART_FLAG_WUF: to indicate the status of the Wake up flag.
         (#) USART_FLAG_RWU: to indicate the status of the Receive Wake up flag.
         (#) USART_FLAG_SBK: to indicate the status of the Send Break flag.
         (#) USART_FLAG_CMF: to indicate the status of the Character match flag.
         (#) USART_FLAG_BUSY: to indicate the status of the Busy flag.
         (#) USART_FLAG_ABRF: to indicate the status of the Auto baud rate flag.
         (#) USART_FLAG_ABRE: to indicate the status of the Auto baud rate error flag.
         (#) USART_FLAG_EOBF: to indicate the status of the End of block flag.
         (#) USART_FLAG_RTOF: to indicate the status of the Receive time out flag.
         (#) USART_FLAG_nCTSS: to indicate the status of the Inverted nCTS input 
             bit status.
         (#) USART_FLAG_TXE: to indicate the status of the transmit buffer register.
         (#) USART_FLAG_RXNE: to indicate the status of the receive buffer register.
         (#) USART_FLAG_TC: to indicate the status of the transmit operation.
         (#) USART_FLAG_IDLE: to indicate the status of the Idle Line.
         (#) USART_FLAG_CTS: to indicate the status of the nCTS input.
         (#) USART_FLAG_LBD: to indicate the status of the LIN break detection.
         (#) USART_FLAG_NE: to indicate if a noise error occur.
         (#) USART_FLAG_FE: to indicate if a frame error occur.
         (#) USART_FLAG_PE: to indicate if a parity error occur.
         (#) USART_FLAG_ORE: to indicate if an Overrun error occur.
    [..] In this Mode it is advised to use the following functions:
         (+) FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG).
         (+) void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG).
               
 *** Interrupt Mode ***
 ======================
    [..] In Interrupt Mode, the USART communication can be managed by 8 interrupt 
         sources and 10 pending bits:
         (+) Pending Bits:
             (##) USART_IT_WU: to indicate the status of the Wake up interrupt.
             (##) USART_IT_CM: to indicate the status of Character match interrupt.
             (##) USART_IT_EOB: to indicate the status of End of block interrupt.
             (##) USART_IT_RTO: to indicate the status of Receive time out interrupt.
             (##) USART_IT_CTS: to indicate the status of CTS change interrupt.
             (##) USART_IT_LBD: to indicate the status of LIN Break detection interrupt.
             (##) USART_IT_TC: to indicate the status of Transmission complete interrupt.
             (##) USART_IT_IDLE: to indicate the status of IDLE line detected interrupt.
             (##) USART_IT_ORE: to indicate the status of OverRun Error interrupt.
             (##) USART_IT_NE: to indicate the status of Noise Error interrupt.
             (##) USART_IT_FE: to indicate the status of Framing Error interrupt.
             (##) USART_IT_PE: to indicate the status of Parity Error interrupt.  
              
         (+) Interrupt Source:
             (##) USART_IT_WU: specifies the interrupt source for Wake up interrupt.
             (##) USART_IT_CM: specifies the interrupt source for Character match 
                  interrupt.
             (##) USART_IT_EOB: specifies the interrupt source for End of block
                  interrupt.
             (##) USART_IT_RTO: specifies the interrupt source for Receive time-out
                  interrupt.
             (##) USART_IT_CTS: specifies the interrupt source for CTS change interrupt.
             (##) USART_IT_LBD: specifies the interrupt source for LIN Break 
                  detection interrupt.
             (##) USART_IT_TXE: specifies the interrupt source for Tansmit Data 
                  Register empty interrupt.
             (##) USART_IT_TC: specifies the interrupt source for Transmission 
                  complete interrupt.
             (##) USART_IT_RXNE: specifies the interrupt source for Receive Data 
                  register not empty interrupt.
             (##) USART_IT_IDLE: specifies the interrupt source for Idle line 
                  detection interrupt.
             (##) USART_IT_PE: specifies the interrupt source for Parity Error interrupt.
             (##) USART_IT_ERR: specifies the interrupt source for Error interrupt
                  (Frame error, noise error, overrun error)
             -@@- Some parameters are coded in order to use them as interrupt 
                 source or as pending bits.
    [..] In this Mode it is advised to use the following functions:
         (+) void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState).
         (+) ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT).
         (+) void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified USART interrupts.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_IT: specifies the USART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *         @arg USART_IT_IDLE:  Idle line detection interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  *         @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @param  NewState: new state of the specified USARTx interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState)
{
  uint32_t usartreg = 0, itpos = 0, itmask = 0;
  uint32_t usartxbase = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  usartxbase = (uint32_t)USARTx;

  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);

  /* Get the interrupt position */
  itpos = USART_IT & IT_MASK;
  itmask = (((uint32_t)0x01) << itpos);

  if (usartreg == 0x02) /* The IT is in CR2 register */
  {
    usartxbase += 0x04;
  }
  else if (usartreg == 0x03) /* The IT is in CR3 register */
  {
    usartxbase += 0x08;
  }
  else /* The IT is in CR1 register */
  {
  }
  if (NewState != DISABLE)
  {
    *(__IO uint32_t*)usartxbase  |= itmask;
  }
  else
  {
    *(__IO uint32_t*)usartxbase &= ~itmask;
  }
}

/**
  * @brief  Enables the specified USART's Request.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_Request: specifies the USART request.
  *         This parameter can be any combination of the following values:
  *         @arg USART_Request_TXFRQ: Transmit data flush ReQuest
  *         @arg USART_Request_RXFRQ: Receive data flush ReQuest
  *         @arg USART_Request_MMRQ: Mute Mode ReQuest
  *         @arg USART_Request_SBKRQ: Send Break ReQuest
  *         @arg USART_Request_ABRRQ: Auto Baud Rate ReQuest
  * @param  NewState: new state of the DMA interface when reception error occurs.
  *         This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void USART_RequestCmd(USART_TypeDef* USARTx, uint32_t USART_Request, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_REQUEST(USART_Request));
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the USART ReQuest by setting the dedicated request bit in the RQR
       register.*/
    USARTx->RQR |= USART_Request;
  }
  else
  {
    /* Disable the USART ReQuest by clearing the dedicated request bit in the RQR
       register.*/
    USARTx->RQR &= (uint32_t)~USART_Request;
  }
}

/**
  * @brief  Enables or disables the USART's Overrun detection.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_OVRDetection: specifies the OVR detection status in case of OVR error.
  *         This parameter can be any combination of the following values:
  *         @arg USART_OVRDetection_Enable: OVR error detection enabled when the USART OVR error 
  *          is asserted.
  *         @arg USART_OVRDetection_Disable: OVR error detection disabled when the USART OVR error 
  *          is asserted.
  * @retval None
  */
void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_OVRDETECTION(USART_OVRDetection));
  
  /* Clear the OVR detection bit */
  USARTx->CR3 &= (uint32_t)~((uint32_t)USART_CR3_OVRDIS);
  /* Set the new value for the OVR detection bit */
  USARTx->CR3 |= USART_OVRDetection;
}

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg USART_FLAG_REACK:  Receive Enable acknowledge flag.
  *         @arg USART_FLAG_TEACK:  Transmit Enable acknowledge flag.
  *         @arg USART_FLAG_WUF:  Wake up flag.
  *         @arg USART_FLAG_RWU:  Receive Wake up flag.
  *         @arg USART_FLAG_SBK:  Send Break flag.
  *         @arg USART_FLAG_CMF:  Character match flag.
  *         @arg USART_FLAG_BUSY:  Busy flag.
  *         @arg USART_FLAG_ABRF:  Auto baud rate flag.
  *         @arg USART_FLAG_ABRE:  Auto baud rate error flag.
  *         @arg USART_FLAG_EOBF:  End of block flag.
  *         @arg USART_FLAG_RTOF:  Receive time out flag.
  *         @arg USART_FLAG_nCTSS:  Inverted nCTS input bit status.
  *         @arg USART_FLAG_CTS:  CTS Change flag.
  *         @arg USART_FLAG_LBD:  LIN Break detection flag.
  *         @arg USART_FLAG_TXE:  Transmit data register empty flag.
  *         @arg USART_FLAG_TC:  Transmission Complete flag.
  *         @arg USART_FLAG_RXNE:  Receive data register not empty flag.
  *         @arg USART_FLAG_IDLE:  Idle Line detection flag.
  *         @arg USART_FLAG_ORE:  OverRun Error flag.
  *         @arg USART_FLAG_NE:  Noise Error flag.
  *         @arg USART_FLAG_FE:  Framing Error flag.
  *         @arg USART_FLAG_PE:  Parity Error flag.
  * @retval The new state of USART_FLAG (SET or RESET).
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));
  
  if ((USARTx->ISR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the USARTx's pending flags.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_FLAG: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *         @arg USART_FLAG_WUF:  Wake up flag.
  *         @arg USART_FLAG_CMF:  Character match flag.
  *         @arg USART_FLAG_EOBF:  End of block flag.
  *         @arg USART_FLAG_RTOF:  Receive time out flag.
  *         @arg USART_FLAG_CTS:  CTS Change flag.
  *         @arg USART_FLAG_LBD:  LIN Break detection flag.
  *         @arg USART_FLAG_TC:  Transmission Complete flag.
  *         @arg USART_FLAG_IDLE:  IDLE line detected flag.
  *         @arg USART_FLAG_ORE:  OverRun Error flag.
  *         @arg USART_FLAG_NE: Noise Error flag.
  *         @arg USART_FLAG_FE: Framing Error flag.
  *         @arg USART_FLAG_PE:   Parity Errorflag.
  *
  * @note
  *   - RXNE pending bit is cleared by a read to the USART_RDR register 
  *     (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - TC flag can be also cleared by software sequence: a read operation to 
  *     USART_SR register (USART_GetFlagStatus()) followed by a write operation
  *     to USART_TDR register (USART_SendData()).
  *   - TXE flag is cleared by a write to the USART_TDR register 
  *     (USART_SendData()) or by writing 1 to the TXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - SBKF flag is cleared by 1 to the SBKRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
     
  USARTx->ICR = USART_FLAG;
}

/**
  * @brief  Checks whether the specified USART interrupt has occurred or not.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_IT: specifies the USART interrupt source to check.
  *         This parameter can be one of the following values:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TXE:  Tansmit Data Register empty interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_RXNE:  Receive Data register not empty interrupt.
  *         @arg USART_IT_IDLE:  Idle line detection interrupt.
  *         @arg USART_IT_ORE:  OverRun Error interrupt.
  *         @arg USART_IT_NE:  Noise Error interrupt.
  *         @arg USART_IT_FE:  Framing Error interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  * @retval The new state of USART_IT (SET or RESET).
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0, usartreg = 0;
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_GET_IT(USART_IT)); 
  
  /* Get the USART register index */
  usartreg = (((uint16_t)USART_IT) >> 0x08);
  /* Get the interrupt position */
  itmask = USART_IT & IT_MASK;
  itmask = (uint32_t)0x01 << itmask;
  
  if (usartreg == 0x01) /* The IT  is in CR1 register */
  {
    itmask &= USARTx->CR1;
  }
  else if (usartreg == 0x02) /* The IT  is in CR2 register */
  {
    itmask &= USARTx->CR2;
  }
  else /* The IT  is in CR3 register */
  {
    itmask &= USARTx->CR3;
  }
  
  bitpos = USART_IT >> 0x10;
  bitpos = (uint32_t)0x01 << bitpos;
  bitpos &= USARTx->ISR;
  if ((itmask != (uint16_t)RESET)&&(bitpos != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return bitstatus;  
}

/**
  * @brief  Clears the USARTx's interrupt pending bits.
  * @param  USARTx: Select the USART peripheral. This parameter can be one of the 
  *         following values: USART1 or USART2 or USART3 or UART4 or UART5.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be one of the following values:
  *         @arg USART_IT_WU:  Wake up interrupt.
  *         @arg USART_IT_CM:  Character match interrupt.
  *         @arg USART_IT_EOB:  End of block interrupt.
  *         @arg USART_IT_RTO:  Receive time out interrupt.
  *         @arg USART_IT_CTS:  CTS change interrupt.
  *         @arg USART_IT_LBD:  LIN Break detection interrupt.
  *         @arg USART_IT_TC:  Transmission complete interrupt.
  *         @arg USART_IT_IDLE:  IDLE line detected interrupt.
  *         @arg USART_IT_ORE:  OverRun Error interrupt.
  *         @arg USART_IT_NE:  Noise Error interrupt.
  *         @arg USART_IT_FE:  Framing Error interrupt.
  *         @arg USART_IT_PE:  Parity Error interrupt.
  * @note
  *   - RXNE pending bit is cleared by a read to the USART_RDR register 
  *     (USART_ReceiveData()) or by writing 1 to the RXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  *   - TC pending bit can be also cleared by software sequence: a read 
  *     operation to USART_SR register (USART_GetITStatus()) followed by a write 
  *     operation to USART_TDR register (USART_SendData()).
  *   - TXE pending bit is cleared by a write to the USART_TDR register 
  *     (USART_SendData()) or by writing 1 to the TXFRQ in the register USART_RQR
  *     (USART_RequestCmd()).
  * @retval None
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT)
{
  uint32_t bitpos = 0, itmask = 0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT)); 
  
  bitpos = USART_IT >> 0x10;
  itmask = ((uint32_t)0x01 << (uint32_t)bitpos);
  USARTx->ICR = (uint32_t)itmask;
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
