/**
  ******************************************************************************
  * @file    stm324x9i_eval_sdram.h
  * @author  MCD Application Team
  * @version V2.2.3
  * @date    22-April-2016
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm324x9i_eval_sdram.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
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
#ifndef __STM324x9I_EVAL_SDRAM_H
#define __STM324x9I_EVAL_SDRAM_H

#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
	#undef Red
	#undef Green
	#undef Blue
#endif

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324x9I_EVAL
  * @{
  */
    
/** @addtogroup STM324x9I_EVAL_SDRAM
  * @{
  */    

/** @defgroup STM324x9I_EVAL_SDRAM_Exported_Types STM324x9I EVAL SDRAM Exported Types
  * @{
  */

/** 
  * @brief  SDRAM status structure definition  
  */     
#define   SDRAM_OK         0x00
#define   SDRAM_ERROR      0x01

/**
  * @}
  */ 
  
/** @defgroup STM324x9I_EVAL_SDRAM_Exported_Constants STM324x9I EVAL SDRAM Exported Constants
  * @{
  */ 
#define SDRAM_DEVICE_ADDR  ((gU32)0xC0000000)
#define SDRAM_DEVICE_SIZE  ((gU32)0x800000)  /* SDRAM device size in MBytes */

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8  */
/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_16 */
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_32

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */   

#define REFRESH_COUNT                    ((gU32)0x0569)   /* SDRAM refresh counter (90Mhz SD clock) */
   
#define SDRAM_TIMEOUT     ((gU32)0xFFFF) 

/* DMA definitions for SDRAM DMA transfer */
#define __DMAx_CLK_ENABLE                 __DMA2_CLK_ENABLE
#define SDRAM_DMAx_CHANNEL                DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM                 DMA2_Stream0  
#define SDRAM_DMAx_IRQn                   DMA2_Stream0_IRQn
#define SDRAM_DMAx_IRQHandler             DMA2_Stream0_IRQHandler   
  
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
  
/** @defgroup STM324x9I_EVAL_SDRAM_Exported_Macro STM324x9I EVAL SDRAM Exported Macro
  * @{
  */  
/**
  * @}
  */ 
   
/** @defgroup STM324x9I_EVAL_SDRAM_Exported_Functions STM324x9I EVAL SDRAM Exported Functions
  * @{
  */  
gU8 BSP_SDRAM_Init(void);
void    BSP_SDRAM_Initialization_sequence(gU32 RefreshCount);
gU8 BSP_SDRAM_ReadData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_ReadData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_WriteData(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_WriteData_DMA(gU32 uwStartAddress, gU32 *pData, gU32 uwDataSize);
gU8 BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);
void    BSP_SDRAM_DMA_IRQHandler(void);  
   
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

#endif /* __STM324x9I_EVAL_SDRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
