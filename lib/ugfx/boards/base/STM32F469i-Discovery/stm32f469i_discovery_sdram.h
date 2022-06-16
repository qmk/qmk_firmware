/**
  ******************************************************************************
  * @file    stm32469i_discovery_sdram.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    27-January-2017
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_discovery_sdram.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32469I_DISCOVERY_SDRAM_H
#define __STM32469I_DISCOVERY_SDRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_Discovery
  * @{
  */

/** @addtogroup STM32469I-Discovery_SDRAM
  * @{
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Types STM32469I Discovery SDRAM Exported Types
  * @{
  */

/**
  * @brief  SDRAM status structure definition
  */
#define   SDRAM_OK         ((gU8)0x00)
#define   SDRAM_ERROR      ((gU8)0x01)

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Constants STM32469I Discovery SDRAM Exported Constants
  * @{
  */
#define SDRAM_DEVICE_ADDR  ((gU32)0xC0000000)

 /* SDRAM device size in Bytes */
 #define SDRAM_DEVICE_SIZE  ((gU32)0x1000000)

#define SDRAM_MEMORY_WIDTH FMC_SDRAM_MEM_BUS_WIDTH_32
#define SDCLOCK_PERIOD     FMC_SDRAM_CLOCK_PERIOD_2

/* SDRAM refresh counter (90 MHz SD clock) */
#define REFRESH_COUNT       ((gU32)0x0569)
#define  SDRAM_TIMEOUT      ((gU32)0xFFFF)

/* DMA definitions for SDRAM DMA transfer */
#define __DMAx_CLK_ENABLE     __HAL_RCC_DMA2_CLK_ENABLE
#define __DMAx_CLK_DISABLE    __HAL_RCC_DMA2_CLK_DISABLE
#define SDRAM_DMAx_CHANNEL    DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM     DMA2_Stream0
#define SDRAM_DMAx_IRQn       DMA2_Stream0_IRQn
#define SDRAM_DMAx_IRQHandler DMA2_Stream0_IRQHandler


/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((gU16)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((gU16)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((gU16)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((gU16)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((gU16)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((gU16)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((gU16)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((gU16)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((gU16)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((gU16)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((gU16)0x0200)
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Macro STM32469I Discovery SDRAM Exported Macro
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32469I_Discovery_SDRAM_Exported_Functions 
  * @{
  */
gU8 BSP_SDRAM_Init(void);
gU8 BSP_SDRAM_DeInit(void);
void    BSP_SDRAM_Initialization_sequence(gU32 RefreshCount);
gU8 BSP_SDRAM_ReadData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_ReadData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_WriteData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_WriteData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);
void    BSP_SDRAM_DMA_IRQHandler(void);

/* These function can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void    BSP_SDRAM_MspInit(SDRAM_HandleTypeDef  *hsdram, void *Params);
void    BSP_SDRAM_MspDeInit(SDRAM_HandleTypeDef  *hsdram, void *Params);

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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_DISCOVERY_SDRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
