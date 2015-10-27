/**
  ******************************************************************************
  * @file    stm32f30x_syscfg.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the SYSCFG firmware 
  *          library.
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

/*!< Define to prevent recursive inclusion -----------------------------------*/
#ifndef __STM32F30x_SYSCFG_H
#define __STM32F30x_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/*!< Includes ----------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup SYSCFG_Exported_Constants
  * @{
  */ 
  
/** @defgroup SYSCFG_EXTI_Port_Sources 
  * @{
  */ 
#define EXTI_PortSourceGPIOA       ((uint8_t)0x00)
#define EXTI_PortSourceGPIOB       ((uint8_t)0x01)
#define EXTI_PortSourceGPIOC       ((uint8_t)0x02)
#define EXTI_PortSourceGPIOD       ((uint8_t)0x03)
#define EXTI_PortSourceGPIOE       ((uint8_t)0x04)
#define EXTI_PortSourceGPIOF       ((uint8_t)0x05)

#define IS_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == EXTI_PortSourceGPIOA) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOB) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOC) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOD) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOE) || \
                                         ((PORTSOURCE) == EXTI_PortSourceGPIOF)) 
/**
  * @}
  */

/** @defgroup SYSCFG_EXTI_Pin_sources 
  * @{
  */ 
#define EXTI_PinSource0            ((uint8_t)0x00)
#define EXTI_PinSource1            ((uint8_t)0x01)
#define EXTI_PinSource2            ((uint8_t)0x02)
#define EXTI_PinSource3            ((uint8_t)0x03)
#define EXTI_PinSource4            ((uint8_t)0x04)
#define EXTI_PinSource5            ((uint8_t)0x05)
#define EXTI_PinSource6            ((uint8_t)0x06)
#define EXTI_PinSource7            ((uint8_t)0x07)
#define EXTI_PinSource8            ((uint8_t)0x08)
#define EXTI_PinSource9            ((uint8_t)0x09)
#define EXTI_PinSource10           ((uint8_t)0x0A)
#define EXTI_PinSource11           ((uint8_t)0x0B)
#define EXTI_PinSource12           ((uint8_t)0x0C)
#define EXTI_PinSource13           ((uint8_t)0x0D)
#define EXTI_PinSource14           ((uint8_t)0x0E)
#define EXTI_PinSource15           ((uint8_t)0x0F)

#define IS_EXTI_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == EXTI_PinSource0) || \
                                       ((PINSOURCE) == EXTI_PinSource1) || \
                                       ((PINSOURCE) == EXTI_PinSource2) || \
                                       ((PINSOURCE) == EXTI_PinSource3) || \
                                       ((PINSOURCE) == EXTI_PinSource4) || \
                                       ((PINSOURCE) == EXTI_PinSource5) || \
                                       ((PINSOURCE) == EXTI_PinSource6) || \
                                       ((PINSOURCE) == EXTI_PinSource7) || \
                                       ((PINSOURCE) == EXTI_PinSource8) || \
                                       ((PINSOURCE) == EXTI_PinSource9) || \
                                       ((PINSOURCE) == EXTI_PinSource10) || \
                                       ((PINSOURCE) == EXTI_PinSource11) || \
                                       ((PINSOURCE) == EXTI_PinSource12) || \
                                       ((PINSOURCE) == EXTI_PinSource13) || \
                                       ((PINSOURCE) == EXTI_PinSource14) || \
                                       ((PINSOURCE) == EXTI_PinSource15))
/**
  * @}
  */

/** @defgroup SYSCFG_Memory_Remap_Config 
  * @{
  */ 
#define SYSCFG_MemoryRemap_Flash                ((uint8_t)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((uint8_t)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((uint8_t)0x03)


#define IS_SYSCFG_MEMORY_REMAP(REMAP) (((REMAP) == SYSCFG_MemoryRemap_Flash)        || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SystemMemory) || \
                                       ((REMAP) == SYSCFG_MemoryRemap_SRAM))

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Config 
  * @{
  */ 
#define SYSCFG_DMARemap_TIM17              SYSCFG_CFGR1_TIM17_DMA_RMP        /*!< Remap TIM17 DMA requests from channel1 to channel2 */
#define SYSCFG_DMARemap_TIM16              SYSCFG_CFGR1_TIM16_DMA_RMP        /*!< Remap TIM16 DMA requests from channel3 to channel4 */
#define SYSCFG_DMARemap_ADC2ADC4           SYSCFG_CFGR1_ADC24_DMA_RMP        /*!< Remap ADC2 and ADC4 DMA requests */

#define SYSCFG_DMARemap_TIM6DAC1Ch1        SYSCFG_CFGR1_TIM6DAC1Ch1_DMA_RMP  /* Remap TIM6/DAC1 Ch1 DMA requests */
#define SYSCFG_DMARemap_TIM7DAC1Ch2        SYSCFG_CFGR1_TIM7DAC1Ch2_DMA_RMP  /* Remap TIM7/DAC1 Ch2 DMA requests */
#define SYSCFG_DMARemap_DAC2Ch1            SYSCFG_CFGR1_DAC2Ch1_DMA_RMP      /* Remap DAC2 Ch1 DMA requests */

#define SYSCFG_DMARemapCh2_SPI1_RX         ((uint32_t)0x80000003)            /* Remap SPI1 RX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_SPI1_RX         ((uint32_t)0x80000001)            /* Remap SPI1 RX DMA CH4 requests */
#define SYSCFG_DMARemapCh6_SPI1_RX         ((uint32_t)0x80000002)            /* Remap SPI1 RX DMA CH6 requests */

#define SYSCFG_DMARemapCh3_SPI1_TX         ((uint32_t)0x8000000C)            /* Remap SPI1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh5_SPI1_TX         ((uint32_t)0x80000004)            /* Remap SPI1 TX DMA CH5 requests */
#define SYSCFG_DMARemapCh7_SPI1_TX         ((uint32_t)0x80000008)            /* Remap SPI1 TX DMA CH7 requests */

#define SYSCFG_DMARemapCh7_I2C1_RX         ((uint32_t)0x80000030)            /* Remap I2C1 RX DMA CH7 requests */
#define SYSCFG_DMARemapCh3_I2C1_RX         ((uint32_t)0x80000010)            /* Remap I2C1 RX DMA CH3 requests */
#define SYSCFG_DMARemapCh5_I2C1_RX         ((uint32_t)0x80000020)            /* Remap I2C1 RX DMA CH5 requests */

#define SYSCFG_DMARemapCh6_I2C1_TX         ((uint32_t)0x800000C0)            /* Remap I2C1 TX DMA CH6 requests */
#define SYSCFG_DMARemapCh2_I2C1_TX         ((uint32_t)0x80000040)            /* Remap I2C1 TX DMA CH2 requests */
#define SYSCFG_DMARemapCh4_I2C1_TX         ((uint32_t)0x80000080)            /* Remap I2C1 TX DMA CH4 requests */

#define SYSCFG_DMARemapCh4_ADC2            ((uint32_t)0x80000300)            /* Remap ADC2 DMA1 Ch4 requests */
#define SYSCFG_DMARemapCh2_ADC2            ((uint32_t)0x80000200)            /* Remap ADC2 DMA1 Ch2 requests */

/* SYSCFG_DMA_Remap_Legacy */ 
#define SYSCFG_DMARemap_TIM6DAC1           SYSCFG_DMARemap_TIM6DAC1Ch1       /*!< Remap TIM6/DAC1 DMA requests */
#define SYSCFG_DMARemap_TIM7DAC2           SYSCFG_DMARemap_TIM7DAC1Ch2       /*!< Remap TIM7/DAC2 DMA requests */
    
#define IS_SYSCFG_DMA_REMAP(REMAP) (((REMAP) == SYSCFG_DMARemap_TIM17)    || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM16)    || \
                                    ((REMAP) == SYSCFG_DMARemap_ADC2ADC4) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM6DAC1Ch1) || \
                                    ((REMAP) == SYSCFG_DMARemap_TIM7DAC1Ch2) || \
                                    ((REMAP) == SYSCFG_DMARemap_DAC2Ch1)    || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh6_SPI1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh7_SPI1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh7_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh3_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh5_I2C1_RX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh6_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_I2C1_TX) || \
                                    ((REMAP) == SYSCFG_DMARemapCh4_ADC2)    || \
                                    ((REMAP) == SYSCFG_DMARemapCh2_ADC2))

/**
  * @}
  */

/** @defgroup SYSCFG_Trigger_Remap_Config 
  * @{
  */ 
#define SYSCFG_TriggerRemap_DACTIM3              SYSCFG_CFGR1_DAC1_TRIG1_RMP     /*!< Remap DAC trigger to TIM3 */
#define SYSCFG_TriggerRemap_TIM1TIM17            SYSCFG_CFGR1_TIM1_ITR3_RMP      /*!< Remap TIM1 ITR3 to TIM17 OC */
#define SYSCFG_TriggerRemap_DACHRTIM1_TRIG1      ((uint32_t)0x80010000)          /*!< Remap DAC trigger to HRTIM1 TRIG1 */
#define SYSCFG_TriggerRemap_DACHRTIM1_TRIG2      ((uint32_t)0x80020000)          /*!< Remap DAC trigger to HRTIM1 TRIG2 */

#define IS_SYSCFG_TRIGGER_REMAP(REMAP) (((REMAP) == SYSCFG_TriggerRemap_DACTIM3)         || \
                                        ((REMAP) == SYSCFG_TriggerRemap_DACHRTIM1_TRIG1) || \
                                        ((REMAP) == SYSCFG_TriggerRemap_DACHRTIM1_TRIG2) || \
                                        ((REMAP) == SYSCFG_TriggerRemap_TIM1TIM17))

/**
  * @}
  */

/** @defgroup SYSCFG_EncoderRemap_Config 
  * @{
  */ 
#define SYSCFG_EncoderRemap_No              ((uint32_t)0x00000000)      /*!< No redirection */
#define SYSCFG_EncoderRemap_TIM2            SYSCFG_CFGR1_ENCODER_MODE_0 /*!< Timer 2 IC1 and IC2 connected to TIM15 IC1 and IC2 */
#define SYSCFG_EncoderRemap_TIM3            SYSCFG_CFGR1_ENCODER_MODE_1 /*!< Timer 3 IC1 and IC2 connected to TIM15 IC1 and IC2 */
#define SYSCFG_EncoderRemap_TIM4            SYSCFG_CFGR1_ENCODER_MODE   /*!< Timer 4 IC1 and IC2 connected to TIM15 IC1 and IC2 */

#define IS_SYSCFG_ENCODER_REMAP(REMAP) (((REMAP) == SYSCFG_EncoderRemap_No)    || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM2)  || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM3)  || \
                                        ((REMAP) == SYSCFG_EncoderRemap_TIM4))

/**
  * @}
  */

/** @defgroup SYSCFG_I2C_FastModePlus_Config 
  * @{
  */ 
#define SYSCFG_I2CFastModePlus_PB6       SYSCFG_CFGR1_I2C_PB6_FMP  /*!< Enable Fast Mode Plus on PB6 */
#define SYSCFG_I2CFastModePlus_PB7       SYSCFG_CFGR1_I2C_PB7_FMP  /*!< Enable Fast Mode Plus on PB7 */
#define SYSCFG_I2CFastModePlus_PB8       SYSCFG_CFGR1_I2C_PB8_FMP  /*!< Enable Fast Mode Plus on PB8 */
#define SYSCFG_I2CFastModePlus_PB9       SYSCFG_CFGR1_I2C_PB9_FMP  /*!< Enable Fast Mode Plus on PB9 */
#define SYSCFG_I2CFastModePlus_I2C1      SYSCFG_CFGR1_I2C1_FMP     /*!< Enable Fast Mode Plus on I2C1 pins */
#define SYSCFG_I2CFastModePlus_I2C2      SYSCFG_CFGR1_I2C2_FMP     /*!< Enable Fast Mode Plus on I2C2 pins */

#define IS_SYSCFG_I2C_FMP(PIN) (((PIN) == SYSCFG_I2CFastModePlus_PB6)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB7)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB8)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_PB9)  || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C1) || \
                                ((PIN) == SYSCFG_I2CFastModePlus_I2C2))

/**
  * @}
  */

/** @defgroup SYSCFG_FPU_Interrupt_Config 
  * @{
  */ 
#define SYSCFG_IT_IXC              SYSCFG_CFGR1_FPU_IE_5  /*!< Inexact Interrupt enable (interrupt disabled by default) */
#define SYSCFG_IT_IDC              SYSCFG_CFGR1_FPU_IE_4  /*!< Input denormal Interrupt enable */
#define SYSCFG_IT_OFC              SYSCFG_CFGR1_FPU_IE_3  /*!< Overflow Interrupt enable */
#define SYSCFG_IT_UFC              SYSCFG_CFGR1_FPU_IE_2  /*!< Underflow Interrupt enable */
#define SYSCFG_IT_DZC              SYSCFG_CFGR1_FPU_IE_1  /*!< Divide-by-zero Interrupt enable */
#define SYSCFG_IT_IOC              SYSCFG_CFGR1_FPU_IE_0  /*!< Invalid operation Interrupt enable */

#define IS_SYSCFG_IT(IT) ((((IT) & (uint32_t)0x03FFFFFF) == 0) && ((IT) != 0))

/**
  * @}
  */

/** @defgroup SYSCFG_Lock_Config
  * @{
  */
#define SYSCFG_Break_PVD                     SYSCFG_CFGR2_PVD_LOCK          /*!< Enables and locks the PVD connection with TIM1/8/15/16/17 Break Input and also the PVD_EN and PVDSEL[2:0] bits of the Power Control Interface */
#define SYSCFG_Break_SRAMParity              SYSCFG_CFGR2_SRAM_PARITY_LOCK  /*!< Enables and locks the SRAM_PARITY error signal with Break Input of TIM1/8/15/16/17 */
#define SYSCFG_Break_Lockup                  SYSCFG_CFGR2_LOCKUP_LOCK       /*!< Enables and locks the LOCKUP output of CortexM4 with Break Input of TIM1/8/15/16/17 */

#define IS_SYSCFG_LOCK_CONFIG(CONFIG) (((CONFIG) == SYSCFG_Break_PVD)        || \
                                       ((CONFIG) == SYSCFG_Break_SRAMParity) || \
                                       ((CONFIG) == SYSCFG_Break_Lockup))

/**
  * @}
  */

/** @defgroup SYSCFG_SRAMWRP_Config
  * @{
  */
#define SYSCFG_SRAMWRP_Page0                 SYSCFG_RCR_PAGE0 /*!< ICODE SRAM Write protection page 0 */
#define SYSCFG_SRAMWRP_Page1                 SYSCFG_RCR_PAGE1 /*!< ICODE SRAM Write protection page 1 */
#define SYSCFG_SRAMWRP_Page2                 SYSCFG_RCR_PAGE2 /*!< ICODE SRAM Write protection page 2 */
#define SYSCFG_SRAMWRP_Page3                 SYSCFG_RCR_PAGE3 /*!< ICODE SRAM Write protection page 3 */
#define SYSCFG_SRAMWRP_Page4                 SYSCFG_RCR_PAGE4 /*!< ICODE SRAM Write protection page 4 */
#define SYSCFG_SRAMWRP_Page5                 SYSCFG_RCR_PAGE5 /*!< ICODE SRAM Write protection page 5 */
#define SYSCFG_SRAMWRP_Page6                 SYSCFG_RCR_PAGE6 /*!< ICODE SRAM Write protection page 6 */
#define SYSCFG_SRAMWRP_Page7                 SYSCFG_RCR_PAGE7 /*!< ICODE SRAM Write protection page 7 */

#define IS_SYSCFG_PAGE(PAGE)((((PAGE) & (uint32_t)0xFFFFFF00) == 0x00000000) && ((PAGE) != 0x00000000))

/**
  * @}
  */

/** @defgroup SYSCFG_flags_definition 
  * @{
  */

#define SYSCFG_FLAG_PE               SYSCFG_CFGR2_SRAM_PE

#define IS_SYSCFG_FLAG(FLAG) (((FLAG) == SYSCFG_FLAG_PE))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the SYSCFG configuration to the default reset state **/
void SYSCFG_DeInit(void);

/* SYSCFG configuration functions *********************************************/ 
void SYSCFG_MemoryRemapConfig(uint32_t SYSCFG_MemoryRemap);
void SYSCFG_DMAChannelRemapConfig(uint32_t SYSCFG_DMARemap, FunctionalState NewState);
void SYSCFG_TriggerRemapConfig(uint32_t SYSCFG_TriggerRemap, FunctionalState NewState);
void SYSCFG_EncoderRemapConfig(uint32_t SYSCFG_EncoderRemap);
void SYSCFG_USBInterruptLineRemapCmd(FunctionalState NewState);
void SYSCFG_I2CFastModePlusConfig(uint32_t SYSCFG_I2CFastModePlus, FunctionalState NewState);
void SYSCFG_ITConfig(uint32_t SYSCFG_IT, FunctionalState NewState);
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex);
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break);
void SYSCFG_BypassParityCheckDisable(void);
void SYSCFG_SRAMWRPEnable(uint32_t SYSCFG_SRAMWRP);
FlagStatus SYSCFG_GetFlagStatus(uint32_t SYSCFG_Flag);
void SYSCFG_ClearFlag(uint32_t SYSCFG_Flag);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_SYSCFG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
