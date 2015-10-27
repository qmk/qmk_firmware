/**
  ******************************************************************************
  * @file    stm32f30x_exti.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the EXTI peripheral:
  *           + Initialization and Configuration 
  *           + Interrupts and flags management 
  *
  @verbatim
 ===============================================================================
                          ##### EXTI features #####
 ===============================================================================
    [..] External interrupt/event lines are mapped as following:
         (#) All available GPIO pins are connected to the 16 external 
             interrupt/event lines from EXTI0 to EXTI15.
         (#) EXTI line 16 is connected to the PVD output
         (#) EXTI line 17 is connected to the RTC Alarm event
         (#) EXTI line 18 is connected to USB Device wakeup event  
         (#) EXTI line 19 is connected to the RTC Tamper and TimeStamp events
         (#) EXTI line 20 is connected to the RTC wakeup event  
         (#) EXTI line 21 is connected to the Comparator 1 wakeup event 
         (#) EXTI line 22 is connected to the Comparator 2 wakeup event
         (#) EXTI line 23 is connected to the I2C1 wakeup event
         (#) EXTI line 24 is connected to the I2C2 wakeup event  
         (#) EXTI line 25 is connected to the USART1 wakeup event
         (#) EXTI line 26 is connected to the USART2 wakeup event  
         (#) EXTI line 27 is reserved
         (#) EXTI line 28 is connected to the USART3 wakeup event
         (#) EXTI line 29 is connected to the Comparator 3 event
         (#) EXTI line 30 is connected to the Comparator 4 event
         (#) EXTI line 31 is connected to the Comparator 5 event
         (#) EXTI line 32 is connected to the Comparator 6 event
         (#) EXTI line 33 is connected to the Comparator 7 event
         (#) EXTI line 34 is connected for thr UART4 wakeup event
         (#) EXTI line 35 is connected for the UART5 wakeup event               

                       ##### How to use this driver #####
 ===============================================================================
    [..] In order to use an I/O pin as an external interrupt source, 
         follow steps below:
         (#) Configure the I/O in input mode using GPIO_Init().
         (#) Select the input source pin for the EXTI line using
             SYSCFG_EXTILineConfig().
         (#) Select the mode(interrupt, event) and configure the trigger 
             selection (Rising, falling or both) using EXTI_Init(). For the 
             internal interrupt, the trigger selection is not needed 
             (the active edge is always the rising one).
         (#) Configure NVIC IRQ channel mapped to the EXTI line using NVIC_Init().
         (#) Optionally, you can generate a software interrupt using the function 
             EXTI_GenerateSWInterrupt().
    [..]
    (@) SYSCFG APB clock must be enabled to get write access to SYSCFG_EXTICRx
      registers using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
                
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
#include "stm32f30x_exti.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI 
  * @brief EXTI driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EXTI_LINENONE     ((uint32_t)0x00000)        /* No interrupt selected */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions 
  * @{
  */

/** @defgroup EXTI_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */
    
/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset 
  *         values.
  * @param  None
  * @retval None
  */
void EXTI_DeInit(void)
{
  EXTI->IMR    = 0x1F800000;
  EXTI->EMR    = 0x00000000;
  EXTI->RTSR   = 0x00000000;
  EXTI->FTSR   = 0x00000000;
  EXTI->SWIER  = 0x00000000;
  EXTI->PR     = 0xE07FFFFF;
  EXTI->IMR2   = 0x0000000C;
  EXTI->EMR2   = 0x00000000;
  EXTI->RTSR2  = 0x00000000;
  EXTI->FTSR2  = 0x00000000;
  EXTI->SWIER2 = 0x00000000;
  EXTI->PR2    = 0x00000003;
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  *    EXTI_Line specifies the EXTI line (EXTI0....EXTI35).
  *    EXTI_Mode specifies which EXTI line is used as interrupt or an event.
  *    EXTI_Trigger selects the trigger. When the trigger occurs, interrupt
  *                 pending bit will be set.
  *    EXTI_LineCmd controls (Enable/Disable) the EXTI line.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure that 
  *         contains the configuration information for the EXTI peripheral.
  * @retval None
  */
  

void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE_ALL(EXTI_InitStruct->EXTI_Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

  tmp = (uint32_t)EXTI_BASE;
      
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    /* Clear EXTI line configuration */   
    *(__IO uint32_t *) (((uint32_t) &(EXTI->IMR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) &= ~(uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));   
    *(__IO uint32_t *) (((uint32_t) &(EXTI->EMR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) &= ~(uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
     
    tmp += EXTI_InitStruct->EXTI_Mode + (((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20);

    *(__IO uint32_t *) tmp |= (uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
    
    tmp = (uint32_t)EXTI_BASE;

    /* Clear Rising Falling edge configuration */
    *(__IO uint32_t *) (((uint32_t) &(EXTI->RTSR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) &= ~(uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
    *(__IO uint32_t *) (((uint32_t) &(EXTI->FTSR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) &= ~(uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
    
      /* Select the trigger for the selected interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
    *(__IO uint32_t *) (((uint32_t) &(EXTI->RTSR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) |= (uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
    *(__IO uint32_t *) (((uint32_t) &(EXTI->FTSR)) + ((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20) |= (uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));      
    }
    else
    {
      tmp += EXTI_InitStruct->EXTI_Trigger + (((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20);

      *(__IO uint32_t *) tmp |= (uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
    }
  }
      
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode + (((EXTI_InitStruct->EXTI_Line) >> 5 ) * 0x20);

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~(uint32_t)(1 << (EXTI_InitStruct->EXTI_Line & 0x1F));
  }
         
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  EXTI_Line: specifies the EXTI line on which the software interrupt
  *         will be generated.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..20).
  * @retval None
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_EXT(EXTI_Line));

  *(__IO uint32_t *) (((uint32_t) &(EXTI->SWIER)) + ((EXTI_Line) >> 5 ) * 0x20) |= (uint32_t)(1 << (EXTI_Line & 0x1F));

}

/**
  * @}
  */
  
/** @defgroup EXTI_Group2 Interrupts and flags management functions
 *  @brief    EXTI Interrupts and flags management functions
 *
@verbatim  
 ===============================================================================
              ##### Interrupts and flags management functions #####
 ===============================================================================
    [..]
    This section provides functions allowing to configure the EXTI Interrupts 
    sources and check or clear the flags or pending bits status.
    
@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..20).
  * @retval The new state of EXTI_Line (SET or RESET).                  
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
   
  if ((*(__IO uint32_t *) (((uint32_t) &(EXTI->PR)) + ((EXTI_Line) >> 5 ) * 0x20)& (uint32_t)(1 << (EXTI_Line & 0x1F))) != (uint32_t)RESET)
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
  * @brief  Clears the EXTI's line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..20).
  * @retval None
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_EXT(EXTI_Line));

  *(__IO uint32_t *) (((uint32_t) &(EXTI->PR)) + ((EXTI_Line) >> 5 ) * 0x20) = (1 << (EXTI_Line & 0x1F));  
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..20).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));
  
  if ((*(__IO uint32_t *) (((uint32_t) &(EXTI->PR)) + ((EXTI_Line) >> 5 ) * 0x20)& (uint32_t)(1 << (EXTI_Line & 0x1F))) != (uint32_t)RESET)
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
  * @brief  Clears the EXTI's line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..20).
  * @retval None
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE_EXT(EXTI_Line));
  
  *(__IO uint32_t *) (((uint32_t) &(EXTI->PR)) + ((EXTI_Line) >> 5 ) * 0x20) = (1 << (EXTI_Line & 0x1F));
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
