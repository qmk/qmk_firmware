/**
  ******************************************************************************
  * @file    stm32f30x_syscfg.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the SYSCFG peripheral:
  *           + Remapping the memory mapped at 0x00000000  
  *           + Remapping the DMA channels
  *           + Enabling I2C fast mode plus driving capability for I2C plus
  *           + Remapping USB interrupt line    
  *           + Configuring the EXTI lines connection to the GPIO port
  *           + Configuring the CLASSB requirements
  *   
  @verbatim
  
 ===============================================================================
                      ##### How to use this driver #####
 ===============================================================================
    [..] The SYSCFG registers can be accessed only when the SYSCFG 
         interface APB clock is enabled.
    [..] To enable SYSCFG APB clock use:
         RCC_APBPeriphClockCmd(RCC_APBPeriph_SYSCFG, ENABLE);
  
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
#include "stm32f30x_syscfg.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @defgroup SYSCFG 
  * @brief SYSCFG driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Reset value od SYSCFG_CFGR1 register */
#define CFGR1_CLEAR_MASK            ((uint32_t)0x7C000000)

/* ------------ SYSCFG registers bit address in the alias region -------------*/
#define SYSCFG_OFFSET                (SYSCFG_BASE - PERIPH_BASE)

/* --- CFGR1 Register ---*/
/* Alias word address of USB_IT_RMP bit */
#define CFGR1_OFFSET                 (SYSCFG_OFFSET + 0x00)
#define USBITRMP_BitNumber            0x05
#define CFGR1_USBITRMP_BB            (PERIPH_BB_BASE + (CFGR1_OFFSET * 32) + (USBITRMP_BitNumber * 4))

/* --- CFGR2 Register ---*/
/* Alias word address of BYP_ADDR_PAR bit */
#define CFGR2_OFFSET                 (SYSCFG_OFFSET + 0x18)
#define BYPADDRPAR_BitNumber          0x04
#define CFGR1_BYPADDRPAR_BB          (PERIPH_BB_BASE + (CFGR2_OFFSET * 32) + (BYPADDRPAR_BitNumber * 4))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions
  * @{
  */ 

/** @defgroup SYSCFG_Group1 SYSCFG Initialization and Configuration functions
 *  @brief   SYSCFG Initialization and Configuration functions 
 *
@verbatim
 ===============================================================================
         ##### SYSCFG Initialization and Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the SYSCFG registers to their default reset values.
  * @param  None
  * @retval None
  * @note   MEM_MODE bits are not affected by APB reset.
  *         MEM_MODE bits took the value from the user option bytes.
  */
void SYSCFG_DeInit(void)
{
  /* Reset SYSCFG_CFGR1 register to reset value without affecting MEM_MODE bits */
  SYSCFG->CFGR1 &= SYSCFG_CFGR1_MEM_MODE;
  /* Set FPU Interrupt Enable bits to default value */
  SYSCFG->CFGR1 |= 0x7C000000;
  /* Reset RAM Write protection bits to default value */
  SYSCFG->RCR = 0x00000000;
  /* Set EXTICRx registers to reset value */
  SYSCFG->EXTICR[0] = 0;
  SYSCFG->EXTICR[1] = 0;
  SYSCFG->EXTICR[2] = 0;
  SYSCFG->EXTICR[3] = 0;
  /* Set CFGR2 register to reset value */
  SYSCFG->CFGR2 = 0;
  /* Set CFGR3 register to reset value */
  SYSCFG->CFGR3 = 0;
}

/**
  * @brief  Configures the memory mapping at address 0x00000000.
  * @param  SYSCFG_MemoryRemap: selects the memory remapping.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_MemoryRemap_Flash: Main Flash memory mapped at 0x00000000  
  *     @arg SYSCFG_MemoryRemap_SystemMemory: System Flash memory mapped at 0x00000000
  *     @arg SYSCFG_MemoryRemap_SRAM: Embedded SRAM mapped at 0x00000000
  * @retval None
  */
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap)
{
  uint32_t tmpcfgr1 = 0;

  /* Check the parameter */
  assert_param(IS_SYSCFG_MEMORY_REMAP(SYSCFG_MemoryRemap));

  /* Get CFGR1 register value */
  tmpcfgr1 = SYSCFG->CFGR1;

  /* Clear MEM_MODE bits */
  tmpcfgr1 &= (uint32_t) (~SYSCFG_CFGR1_MEM_MODE);

  /* Set the new MEM_MODE bits value */
  tmpcfgr1 |= (uint32_t) SYSCFG_MemoryRemap;

  /* Set CFGR1 register with the new memory remap configuration */
  SYSCFG->CFGR1 = tmpcfgr1;
}

/**
  * @brief  Configures the DMA channels remapping.
  * @param  SYSCFG_DMARemap: selects the DMA channels remap.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_DMARemap_TIM17: Remap TIM17 DMA requests from DMA1 channel1 to channel2
  *     @arg SYSCFG_DMARemap_TIM16: Remap TIM16 DMA requests from DMA1 channel3 to channel4
  *     @arg SYSCFG_DMARemap_TIM6DAC1Ch1: Remap TIM6/DAC1 DMA requests from DMA2 channel 3 to DMA1 channel 3
  *     @arg SYSCFG_DMARemap_TIM7DAC1Ch2: Remap TIM7/DAC2 DMA requests from DMA2 channel 4 to DMA1 channel 4
  *     @arg SYSCFG_DMARemap_ADC2ADC4: Remap ADC2 and ADC4 DMA requests from DMA2 channel1/channel3 to channel3/channel4
  *     @arg SYSCFG_DMARemap_DAC2Ch1: Remap DAC2 DMA requests to DMA1 channel5
  *     @arg SYSCFG_DMARemapCh2_SPI1_RX: Remap SPI1 RX DMA1 CH2 requests
  *     @arg SYSCFG_DMARemapCh4_SPI1_RX: Remap SPI1 RX DMA CH4 requests        
  *     @arg SYSCFG_DMARemapCh6_SPI1_RX: Remap SPI1 RX DMA CH6 requests       
  *     @arg SYSCFG_DMARemapCh3_SPI1_TX: Remap SPI1 TX DMA CH2 requests      
  *     @arg SYSCFG_DMARemapCh5_SPI1_TX: Remap SPI1 TX DMA CH5 requests       
  *     @arg SYSCFG_DMARemapCh7_SPI1_TX: Remap SPI1 TX DMA CH7 requests       
  *     @arg SYSCFG_DMARemapCh7_I2C1_RX: Remap I2C1 RX DMA CH7 requests
  *     @arg SYSCFG_DMARemapCh3_I2C1_RX: Remap I2C1 RX DMA CH3 requests       
  *     @arg SYSCFG_DMARemapCh5_I2C1_RX: Remap I2C1 RX DMA CH5 requests      
  *     @arg SYSCFG_DMARemapCh6_I2C1_TX: Remap I2C1 TX DMA CH6 requests       
  *     @arg SYSCFG_DMARemapCh2_I2C1_TX: Remap I2C1 TX DMA CH2 requests       
  *     @arg SYSCFG_DMARemapCh4_I2C1_TX: Remap I2C1 TX DMA CH4 requests   
  *     @arg SYSCFG_DMARemapCh4_ADC2: Remap ADC2 DMA1 Ch4 requests    
  *     @arg SYSCFG_DMARemapCh2_ADC2: Remap ADC2 DMA1 Ch2 requests
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be: Enable or Disable.
  * @note   When enabled, DMA channel of the selected peripheral is remapped
  * @note   When disabled, Default DMA channel is mapped to the selected peripheral
  * @note
  *           By default TIM17 DMA requests is mapped to channel 1
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Enable)
  *           to remap TIM17 DMA requests to DMA1 channel 2
  *           use SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemap_TIM17, Disable)
  *           to map TIM17 DMA requests to DMA1 channel 1 (default mapping)
  * @retval None
  */
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_DMA_REMAP(SYSCFG_DMARemap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if ((SYSCFG_DMARemap & 0x80000000)!= 0x80000000)
  {
    if (NewState != DISABLE)
    {
      /* Remap the DMA channel */
      SYSCFG->CFGR1 |= (uint32_t)SYSCFG_DMARemap;
    }
    else
    {
      /* use the default DMA channel mapping */
      SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_DMARemap);
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Remap the DMA channel */
      SYSCFG->CFGR3 |= (uint32_t)SYSCFG_DMARemap;
    }
    else
    {
      /* use the default DMA channel mapping */
      SYSCFG->CFGR3 &= (uint32_t)(~SYSCFG_DMARemap);
    }
  }
}

/**
  * @brief  Configures the remapping capabilities of DAC/TIM triggers.
  * @param  SYSCFG_TriggerRemap: selects the trigger to be remapped.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_TriggerRemap_DACTIM3: Remap DAC trigger from TIM8 to TIM3
  *     @arg SYSCFG_TriggerRemap_TIM1TIM17: Remap TIM1 ITR3 from TIM4 TRGO to TIM17 OC
  *     @arg SYSCFG_TriggerRemap_DACHRTIM1_TRIG1: Remap DAC trigger to HRTIM1 TRIG1
  *     @arg SYSCFG_TriggerRemap_DACHRTIM1_TRIG2: Remap DAC trigger to HRTIM1 TRIG2    
  * @param  NewState: new state of the trigger mapping. 
  *         This parameter can be: ENABLE or DISABLE.
  * @note   ENABLE:  Enable fast mode plus driving capability for selected pin
  * @note   DISABLE: Disable fast mode plus driving capability for selected pin
  * @retval None
  */
void SYSCFG_TriggerRemapConfig(uint32_t SYSCFG_TriggerRemap, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_TRIGGER_REMAP(SYSCFG_TriggerRemap));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if ((SYSCFG_TriggerRemap & 0x80000000)!= 0x80000000)
  {
    if (NewState != DISABLE)
    {
      /* Remap the trigger */
      SYSCFG->CFGR1 |= (uint32_t)SYSCFG_TriggerRemap;
    }
    else
    {
      /* Use the default trigger mapping */
      SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_TriggerRemap);
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Remap the trigger */
      SYSCFG->CFGR3 |= (uint32_t)SYSCFG_TriggerRemap;
    }
    else
    {
      /* Use the default trigger mapping */
      SYSCFG->CFGR3 &= (uint32_t)(~SYSCFG_TriggerRemap);
    }
  }
}

/**
  * @brief  Configures the remapping capabilities of encoder mode.
  * @ note This feature implement the so-called M/T method for measuring speed
  *        and position using quadrature encoders.  
  * @param  SYSCFG_EncoderRemap: selects the remap option for encoder mode.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_EncoderRemap_No: No remap
  *     @arg SYSCFG_EncoderRemap_TIM2: Timer 2 IC1 and IC2 connected to TIM15 IC1 and IC2
  *     @arg SYSCFG_EncoderRemap_TIM3: Timer 3 IC1 and IC2 connected to TIM15 IC1 and IC2
  *     @arg SYSCFG_EncoderRemap_TIM4: Timer 4 IC1 and IC2 connected to TIM15 IC1 and IC2
  * @retval None
  */
void SYSCFG_EncoderRemapConfig(uint32_t SYSCFG_EncoderRemap)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_ENCODER_REMAP(SYSCFG_EncoderRemap));

  /* Reset the encoder mode remapping bits */
  SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_CFGR1_ENCODER_MODE);

  /* Set the selected configuration */
  SYSCFG->CFGR1 |= (uint32_t)(SYSCFG_EncoderRemap);
}

/**
  * @brief  Remaps the USB interrupt lines.
  * @param  NewState: new state of the mapping of USB interrupt lines. 
  *         This parameter can be:
  * @param  ENABLE: Remap the USB interrupt line as following:
  *         @arg  USB Device High Priority (USB_HP) interrupt mapped to line 74.
  *         @arg  USB Device Low Priority (USB_LP) interrupt mapped to line 75.
  *         @arg  USB Wakeup Interrupt (USB_WKUP) interrupt mapped to line 76.
  * @param  DISABLE: Use the default USB interrupt line:
  *         @arg  USB Device High Priority (USB_HP) interrupt mapped to line 19.
  *         @arg  USB Device Low Priority (USB_LP) interrupt mapped to line 20.
  *         @arg  USB Wakeup Interrupt (USB_WKUP) interrupt mapped to line 42.
  * @retval None
  */
void SYSCFG_USBInterruptLineRemapCmd(FunctionalState NewState)
{
  /* Check the parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Remap the USB interupt lines */
  *(__IO uint32_t *) CFGR1_USBITRMP_BB = (uint32_t)NewState;
}

/**
  * @brief  Configures the I2C fast mode plus driving capability.
  * @param  SYSCFG_I2CFastModePlus: selects the pin.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_I2CFastModePlus_PB6: Configure fast mode plus driving capability for PB6
  *     @arg SYSCFG_I2CFastModePlus_PB7: Configure fast mode plus driving capability for PB7
  *     @arg SYSCFG_I2CFastModePlus_PB8: Configure fast mode plus driving capability for PB8
  *     @arg SYSCFG_I2CFastModePlus_PB9: Configure fast mode plus driving capability for PB9
  *     @arg SYSCFG_I2CFastModePlus_I2C1: Configure fast mode plus driving capability for I2C1 pins
  *     @arg SYSCFG_I2CFastModePlus_I2C2: Configure fast mode plus driving capability for I2C2 pins
  * @param  NewState: new state of the DMA channel remapping. 
  *         This parameter can be:
  *     @arg ENABLE: Enable fast mode plus driving capability for selected I2C pin
  *     @arg DISABLE: Disable fast mode plus driving capability for selected I2C pin
  * @note  For I2C1, fast mode plus driving capability can be enabled on all selected
  *        I2C1 pins using SYSCFG_I2CFastModePlus_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaing I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using SYSCFG_I2CFastModePlus_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be enabled
  *        only by using SYSCFG_I2CFastModePlus_I2C2 parameter.
  * @retval None
  */
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SYSCFG_I2C_FMP(SYSCFG_I2CFastModePlus));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable fast mode plus driving capability for selected I2C pin */
    SYSCFG->CFGR1 |= (uint32_t)SYSCFG_I2CFastModePlus;
  }
  else
  {
    /* Disable fast mode plus driving capability for selected I2C pin */
    SYSCFG->CFGR1 &= (uint32_t)(~SYSCFG_I2CFastModePlus);
  }
}

/**
  * @brief  Enables or disables the selected SYSCFG interrupts.
  * @param  SYSCFG_IT: specifies the SYSCFG interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_IT_IXC: Inexact Interrupt
  *     @arg SYSCFG_IT_IDC: Input denormal Interrupt
  *     @arg SYSCFG_IT_OFC: Overflow Interrupt
  *     @arg SYSCFG_IT_UFC: Underflow Interrupt
  *     @arg SYSCFG_IT_DZC: Divide-by-zero Interrupt
  *     @arg SYSCFG_IT_IOC: Invalid operation Interrupt
  * @param  NewState: new state of the specified SYSCFG interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_ITConfig(uint32_t SYSCFG_IT, FunctionalState NewState)  
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SYSCFG_IT(SYSCFG_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected SYSCFG interrupts */
    SYSCFG->CFGR1 |= SYSCFG_IT;
  }
  else
  {
    /* Disable the selected SYSCFG interrupts */
    SYSCFG->CFGR1 &= ((uint32_t)~SYSCFG_IT);
  }
}

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  EXTI_PortSourceGPIOx : selects the GPIO port to be used as source 
  *                                for EXTI lines where x can be (A, B, C, D, E or F).
  * @param  EXTI_PinSourcex: specifies the EXTI line to be configured.
  *         This parameter can be EXTI_PinSourcex where x can be (0..15)
  * @retval None
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex)
{
  uint32_t tmp = 0x00;

  /* Check the parameters */
  assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
  assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));
  
  tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
  SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

/**
  * @brief  Connects the selected parameter to the break input of TIM1.
  * @note   The selected configuration is locked and can be unlocked by system reset
  * @param  SYSCFG_Break: selects the configuration to be connected to break
  *         input of TIM1
  *   This parameter can be any combination of the following values:
  *     @arg SYSCFG_Break_PVD: PVD interrupt is connected to the break input of TIM1.
  *     @arg SYSCFG_Break_SRAMParity: SRAM Parity error is connected to the break input of TIM1.
  *     @arg SYSCFG_Break_HardFault: Lockup output of CortexM4 is connected to the break input of TIM1.
  * @retval None
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
}

/**
  * @brief  Disables the parity check on RAM.
  * @note   Disabling the parity check on RAM locks the configuration bit.
  *         To re-enable the parity check on RAM perform a system reset.  
  * @param  None
  * @retval None
  */
void SYSCFG_BypassParityCheckDisable(void)
{
  /* Disable the adddress parity check on RAM */
  *(__IO uint32_t *) CFGR1_BYPADDRPAR_BB = (uint32_t)0x00000001;
}

/**
  * @brief  Enables the ICODE SRAM write protection.
  * @note   Enabling the ICODE SRAM write protection locks the configuration bit.
  *         To disable the ICODE SRAM write protection perform a system reset.
  * @param  None
  * @retval None
  */
void SYSCFG_SRAMWRPEnable(uint32_t SYSCFG_SRAMWRP)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_PAGE(SYSCFG_SRAMWRP));

  /* Enable the write-protection on the selected ICODE SRAM page */
  SYSCFG->RCR |= (uint32_t)SYSCFG_SRAMWRP;
}

/**
  * @brief  Checks whether the specified SYSCFG flag is set or not.
  * @param  SYSCFG_Flag: specifies the SYSCFG flag to check. 
  *   This parameter can be one of the following values:
  *     @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval The new state of SYSCFG_Flag (SET or RESET).
  */
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  /* Check the status of the specified SPI flag */
  if ((SYSCFG->CFGR2 & SYSCFG_CFGR2_SRAM_PE) != (uint32_t)RESET)
  {
    /* SYSCFG_Flag is set */
    bitstatus = SET;
  }
  else
  {
    /* SYSCFG_Flag is reset */
    bitstatus = RESET;
  }
  /* Return the SYSCFG_Flag status */
  return  bitstatus;
}

/**
  * @brief  Clears the selected SYSCFG flag.
  * @param  SYSCFG_Flag: selects the flag to be cleared.
  *   This parameter can be any combination of the following values:
  *     @arg SYSCFG_FLAG_PE: SRAM parity error flag.
  * @retval None
  */
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag)
{
  /* Check the parameter */
  assert_param(IS_SYSCFG_FLAG(SYSCFG_Flag));

  SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Flag;
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

