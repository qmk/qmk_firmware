/**
  ******************************************************************************
  * @file    stm32f30x_exti.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the EXTI 
  *          firmware library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F30x_EXTI_H
#define __STM32F30x_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  EXTI mode enumeration  
  */

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/** 
  * @brief  EXTI Trigger enumeration  
  */

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/** 
  * @brief  EXTI Init Structure definition  
  */

typedef struct
{
  uint32_t EXTI_Line;               /*!< Specifies the EXTI lines to be enabled or disabled.
                                         This parameter can be any combination of @ref EXTI_Lines */
   
  EXTIMode_TypeDef EXTI_Mode;       /*!< Specifies the mode for the EXTI lines.
                                         This parameter can be a value of @ref EXTIMode_TypeDef */

  EXTITrigger_TypeDef EXTI_Trigger; /*!< Specifies the trigger signal active edge for the EXTI lines.
                                         This parameter can be a value of @ref EXTITrigger_TypeDef */

  FunctionalState EXTI_LineCmd;     /*!< Specifies the new state of the selected EXTI lines.
                                         This parameter can be set either to ENABLE or DISABLE */
}EXTI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants
  * @{
  */ 
/** @defgroup EXTI_Lines 
  * @{
  */

#define EXTI_Line0       ((uint32_t)0x00)  /*!< External interrupt line 0  */
#define EXTI_Line1       ((uint32_t)0x01)  /*!< External interrupt line 1  */
#define EXTI_Line2       ((uint32_t)0x02)  /*!< External interrupt line 2  */
#define EXTI_Line3       ((uint32_t)0x03)  /*!< External interrupt line 3  */
#define EXTI_Line4       ((uint32_t)0x04)  /*!< External interrupt line 4  */
#define EXTI_Line5       ((uint32_t)0x05)  /*!< External interrupt line 5  */
#define EXTI_Line6       ((uint32_t)0x06)  /*!< External interrupt line 6  */
#define EXTI_Line7       ((uint32_t)0x07)  /*!< External interrupt line 7  */
#define EXTI_Line8       ((uint32_t)0x08)  /*!< External interrupt line 8  */
#define EXTI_Line9       ((uint32_t)0x09)  /*!< External interrupt line 9  */
#define EXTI_Line10      ((uint32_t)0x0A)  /*!< External interrupt line 10 */
#define EXTI_Line11      ((uint32_t)0x0B)  /*!< External interrupt line 11 */
#define EXTI_Line12      ((uint32_t)0x0C)  /*!< External interrupt line 12 */
#define EXTI_Line13      ((uint32_t)0x0D)  /*!< External interrupt line 13 */
#define EXTI_Line14      ((uint32_t)0x0E)  /*!< External interrupt line 14 */
#define EXTI_Line15      ((uint32_t)0x0F)  /*!< External interrupt line 15 */
#define EXTI_Line16      ((uint32_t)0x10)  /*!< External interrupt line 16 
                                                      Connected to the PVD Output */
#define EXTI_Line17      ((uint32_t)0x11)  /*!< Internal interrupt line 17 
                                                      Connected to the RTC Alarm 
                                                      event */
#define EXTI_Line18      ((uint32_t)0x12)  /*!< Internal interrupt line 18 
                                                      Connected to the USB Device
                                                      Wakeup from suspend event */
#define EXTI_Line19      ((uint32_t)0x13)  /*!< Internal interrupt line 19
                                                      Connected to the RTC Tamper
                                                      and Time Stamp events */
#define EXTI_Line20      ((uint32_t)0x14)  /*!< Internal interrupt line 20
                                                      Connected to the RTC wakeup
                                                      event */                                                      
#define EXTI_Line21      ((uint32_t)0x15)  /*!< Internal interrupt line 21
                                                      Connected to the Comparator 1
                                                      event */
#define EXTI_Line22      ((uint32_t)0x16)  /*!< Internal interrupt line 22
                                                      Connected to the Comparator 2
                                                      event */
#define EXTI_Line23      ((uint32_t)0x17)  /*!< Internal interrupt line 23
                                                      Connected to the I2C1 wakeup
                                                      event */
#define EXTI_Line24      ((uint32_t)0x18)  /*!< Internal interrupt line 24
                                                      Connected to the I2C2 wakeup
                                                      event */
#define EXTI_Line25      ((uint32_t)0x19)  /*!< Internal interrupt line 25
                                                      Connected to the USART1 wakeup
                                                      event */
#define EXTI_Line26      ((uint32_t)0x1A)  /*!< Internal interrupt line 26
                                                      Connected to the USART2 wakeup
                                                      event */
#define EXTI_Line27      ((uint32_t)0x1B)  /*!< Internal interrupt line 27
                                                       reserved */
#define EXTI_Line28      ((uint32_t)0x1C)  /*!< Internal interrupt line 28
                                                      Connected to the USART3 wakeup
                                                      event */
#define EXTI_Line29      ((uint32_t)0x1D)  /*!< Internal interrupt line 29
                                                      Connected to the Comparator 3 
                                                      event */
#define EXTI_Line30      ((uint32_t)0x1E)  /*!< Internal interrupt line 30
                                                      Connected to the Comparator 4 
                                                      event */
#define EXTI_Line31      ((uint32_t)0x1F)  /*!< Internal interrupt line 31
                                                      Connected to the Comparator 5 
                                                      event */
#define EXTI_Line32      ((uint32_t)0x20)  /*!< Internal interrupt line 32
                                                      Connected to the Comparator 6 
                                                      event */
#define EXTI_Line33      ((uint32_t)0x21)  /*!< Internal interrupt line 33
                                                      Connected to the Comparator 7 
                                                      event */
#define EXTI_Line34      ((uint32_t)0x22)  /*!< Internal interrupt line 34
                                                      Connected to the USART4 wakeup
                                                      event */
#define EXTI_Line35      ((uint32_t)0x23)  /*!< Internal interrupt line 35
                                                      Connected to the USART5 wakeup
                                                      event */
                                                                                                                                                                                                                                                                                                                                                                                                                                                
#define IS_EXTI_LINE_ALL(LINE) ((LINE) <= 0x23)
#define IS_EXTI_LINE_EXT(LINE) (((LINE) <= 0x16) || (((LINE) == EXTI_Line29) || ((LINE) == EXTI_Line30) || \
                               ((LINE) == EXTI_Line31) || ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33)))

#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) || \
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line29) || \
                                ((LINE) == EXTI_Line30) || ((LINE) == EXTI_Line31) || \
                                ((LINE) == EXTI_Line32) || ((LINE) == EXTI_Line33))
/**
  * @}
  */
 
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Function used to set the EXTI configuration to the default reset state *****/
void EXTI_DeInit(void);

/* Initialization and Configuration functions *********************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);

/* Interrupts and flags management functions **********************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_EXTI_H */
/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
