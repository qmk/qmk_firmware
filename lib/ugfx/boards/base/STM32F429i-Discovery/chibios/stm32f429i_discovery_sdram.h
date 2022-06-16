/**
  ******************************************************************************
  * @file    stm32f429i_discovery_sdram.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   This file contains all the functions prototypes for the 
  *          stm324x9i_disco_sdram.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */   

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32429I_DISCO_SDRAM_H
#define __STM32429I_DISCO_SDRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

//FIXME this should not be needed
#define STM32F429_439xx

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/**
  * @brief  FMC SDRAM Bank address
  */   
#define SDRAM_BANK_ADDR     ((gU32)0xD0000000)
  
/**
  * @brief  FMC SDRAM Memory Width
  */  
/* #define SDRAM_MEMORY_WIDTH   FMC_SDMemory_Width_8b  */
#define SDRAM_MEMORY_WIDTH    FMC_SDMemory_Width_16b 

/**
  * @brief  FMC SDRAM CAS Latency
  */  
/* #define SDRAM_CAS_LATENCY   FMC_CAS_Latency_2  */
#define SDRAM_CAS_LATENCY    FMC_CAS_Latency_3

/**
  * @brief  FMC SDRAM Memory clock period
  */  
#define SDCLOCK_PERIOD    FMC_SDClock_Period_2        /* Default configuration used with LCD */
/* #define SDCLOCK_PERIOD    FMC_SDClock_Period_3 */

/**
  * @brief  FMC SDRAM Memory Read Burst feature
  */  
#define SDRAM_READBURST    FMC_Read_Burst_Disable    /* Default configuration used with LCD */
/* #define SDRAM_READBURST    FMC_Read_Burst_Enable  */

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

void  SDRAM_Init(void);
void  SDRAM_InitSequence(void);
void  SDRAM_WriteBuffer(gU32* pBuffer, gU32 uwWriteAddress, gU32 uwBufferSize);
void  SDRAM_ReadBuffer(gU32* pBuffer, gU32 uwReadAddress, gU32 uwBufferSize);

#ifdef __cplusplus
}
#endif

#endif
