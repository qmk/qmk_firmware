/**
  ******************************************************************************
  * @file    stm32l1xx_hal.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    5-September-2014
  * @brief   This file contains all the functions prototypes for the HAL 
  *          module driver.
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
#ifndef __STM32L1xx_HAL_H
#define __STM32L1xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_conf.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup HAL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */ 

/** @defgroup SYSCFG_Constants SYSCFG: SYStem ConFiG
  * @{
  */ 

/** @defgroup SYSCFG_BootMode Boot Mode
  * @{
  */

#define SYSCFG_BOOT_MAINFLASH          ((uint32_t)0x00000000)
#define SYSCFG_BOOT_SYSTEMFLASH        ((uint32_t)SYSCFG_MEMRMP_BOOT_MODE_0)
#if defined(FSMC_R_BASE)
#define SYSCFG_BOOT_FSMC               ((uint32_t)SYSCFG_MEMRMP_BOOT_MODE_1)
#endif /* FSMC_R_BASE  */
#define SYSCFG_BOOT_SRAM               ((uint32_t)SYSCFG_MEMRMP_BOOT_MODE)

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup RI_Constants RI: Routing Interface
  * @{
  */ 

/** @defgroup RI_InputCapture Input Capture
  * @{
  */ 

#define RI_INPUTCAPTURE_IC1  RI_ICR_IC1    /*!< Input Capture 1 */
#define RI_INPUTCAPTURE_IC2  RI_ICR_IC2    /*!< Input Capture 2 */
#define RI_INPUTCAPTURE_IC3  RI_ICR_IC3    /*!< Input Capture 3 */
#define RI_INPUTCAPTURE_IC4  RI_ICR_IC4    /*!< Input Capture 4 */

/**
  * @}
  */ 
  
/** @defgroup TIM_Select TIM Select
  * @{
  */ 
  
#define TIM_SELECT_NONE  ((uint32_t)0x00000000)    /*!< None selected */
#define TIM_SELECT_TIM2  ((uint32_t)RI_ICR_TIM_0)  /*!< Timer 2 selected */
#define TIM_SELECT_TIM3  ((uint32_t)RI_ICR_TIM_1)  /*!< Timer 3 selected */
#define TIM_SELECT_TIM4  ((uint32_t)RI_ICR_TIM)    /*!< Timer 4 selected */

#define IS_RI_TIM(__TIM__) (((__TIM__) == TIM_SELECT_NONE) || \
                        ((__TIM__) == TIM_SELECT_TIM2) || \
                        ((__TIM__) == TIM_SELECT_TIM3) || \
                        ((__TIM__) == TIM_SELECT_TIM4))

/**
  * @}
  */ 
  
/** @defgroup RI_InputCaptureRouting Input Capture Routing
  * @{
  */ 
                                                          /* TIMx_IC1 TIMx_IC2  TIMx_IC3  TIMx_IC4 */  
#define RI_INPUTCAPTUREROUTING_0   ((uint32_t)0x00000000) /* PA0       PA1      PA2       PA3      */
#define RI_INPUTCAPTUREROUTING_1   ((uint32_t)0x00000001) /* PA4       PA5      PA6       PA7      */
#define RI_INPUTCAPTUREROUTING_2   ((uint32_t)0x00000002) /* PA8       PA9      PA10      PA11     */
#define RI_INPUTCAPTUREROUTING_3   ((uint32_t)0x00000003) /* PA12      PA13     PA14      PA15     */
#define RI_INPUTCAPTUREROUTING_4   ((uint32_t)0x00000004) /* PC0       PC1      PC2       PC3      */
#define RI_INPUTCAPTUREROUTING_5   ((uint32_t)0x00000005) /* PC4       PC5      PC6       PC7      */
#define RI_INPUTCAPTUREROUTING_6   ((uint32_t)0x00000006) /* PC8       PC9      PC10      PC11     */
#define RI_INPUTCAPTUREROUTING_7   ((uint32_t)0x00000007) /* PC12      PC13     PC14      PC15     */
#define RI_INPUTCAPTUREROUTING_8   ((uint32_t)0x00000008) /* PD0       PD1      PD2       PD3      */
#define RI_INPUTCAPTUREROUTING_9   ((uint32_t)0x00000009) /* PD4       PD5      PD6       PD7      */
#define RI_INPUTCAPTUREROUTING_10  ((uint32_t)0x0000000A) /* PD8       PD9      PD10      PD11     */
#define RI_INPUTCAPTUREROUTING_11  ((uint32_t)0x0000000B) /* PD12      PD13     PD14      PD15     */
#define RI_INPUTCAPTUREROUTING_12  ((uint32_t)0x0000000C) /* PE0       PE1      PE2       PE3      */
#define RI_INPUTCAPTUREROUTING_13  ((uint32_t)0x0000000D) /* PE4       PE5      PE6       PE7      */
#define RI_INPUTCAPTUREROUTING_14  ((uint32_t)0x0000000E) /* PE8       PE9      PE10      PE11     */
#define RI_INPUTCAPTUREROUTING_15  ((uint32_t)0x0000000F) /* PE12      PE13     PE14      PE15     */

#define IS_RI_INPUTCAPTURE_ROUTING(__ROUTING__) (((__ROUTING__) == RI_INPUTCAPTUREROUTING_0) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_1) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_2) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_3) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_4) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_5) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_6) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_7) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_8) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_9) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_10) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_11) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_12) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_13) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_14) || \
                                             ((__ROUTING__) == RI_INPUTCAPTUREROUTING_15))

/**
  * @}
  */ 

/** @defgroup RI_IOSwitch IO Switch
  * @{
  */ 
#define RI_ASCR1_REGISTER       ((uint32_t)0x80000000)
/* ASCR1 I/O switch: bit 31 is set to '1' to indicate that the mask is in ASCR1 register */
#define RI_IOSWITCH_CH0         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_0)
#define RI_IOSWITCH_CH1         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_1)
#define RI_IOSWITCH_CH2         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_2)
#define RI_IOSWITCH_CH3         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_3)
#define RI_IOSWITCH_CH4         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_4)
#define RI_IOSWITCH_CH5         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_5)
#define RI_IOSWITCH_CH6         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_6)
#define RI_IOSWITCH_CH7         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_7)
#define RI_IOSWITCH_CH8         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_8)
#define RI_IOSWITCH_CH9         ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_9)
#define RI_IOSWITCH_CH10        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_10)
#define RI_IOSWITCH_CH11        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_11)
#define RI_IOSWITCH_CH12        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_12)
#define RI_IOSWITCH_CH13        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_13)
#define RI_IOSWITCH_CH14        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_14)
#define RI_IOSWITCH_CH15        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_15)
#define RI_IOSWITCH_CH18        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_18)
#define RI_IOSWITCH_CH19        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_19)
#define RI_IOSWITCH_CH20        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_20)
#define RI_IOSWITCH_CH21        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_21)
#define RI_IOSWITCH_CH22        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_22)
#define RI_IOSWITCH_CH23        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_23)
#define RI_IOSWITCH_CH24        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_24)
#define RI_IOSWITCH_CH25        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_25)
#define RI_IOSWITCH_VCOMP       ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_VCOMP) /* VCOMP (ADC channel 26) is an internal switch used to connect selected channel to COMP1 non inverting input */
#if defined (RI_ASCR2_CH1b) /* STM32L1 devices category Cat.4 and Cat.5 */
#define RI_IOSWITCH_CH27        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_27)
#define RI_IOSWITCH_CH28        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_28)
#define RI_IOSWITCH_CH29        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_29)
#define RI_IOSWITCH_CH30        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_30)
#define RI_IOSWITCH_CH31        ((uint32_t)RI_ASCR1_REGISTER | RI_ASCR1_CH_31)
#endif /* RI_ASCR2_CH1b */

/* ASCR2 IO switch: bit 31 is set to '0' to indicate that the mask is in ASCR2 register */  
#define RI_IOSWITCH_GR10_1      ((uint32_t)RI_ASCR2_GR10_1)
#define RI_IOSWITCH_GR10_2      ((uint32_t)RI_ASCR2_GR10_2)
#define RI_IOSWITCH_GR10_3      ((uint32_t)RI_ASCR2_GR10_3)
#define RI_IOSWITCH_GR10_4      ((uint32_t)RI_ASCR2_GR10_4)
#define RI_IOSWITCH_GR6_1       ((uint32_t)RI_ASCR2_GR6_1)
#define RI_IOSWITCH_GR6_2       ((uint32_t)RI_ASCR2_GR6_2)
#define RI_IOSWITCH_GR5_1       ((uint32_t)RI_ASCR2_GR5_1)
#define RI_IOSWITCH_GR5_2       ((uint32_t)RI_ASCR2_GR5_2)
#define RI_IOSWITCH_GR5_3       ((uint32_t)RI_ASCR2_GR5_3)
#define RI_IOSWITCH_GR4_1       ((uint32_t)RI_ASCR2_GR4_1)
#define RI_IOSWITCH_GR4_2       ((uint32_t)RI_ASCR2_GR4_2)
#define RI_IOSWITCH_GR4_3       ((uint32_t)RI_ASCR2_GR4_3)
#if defined (RI_ASCR2_CH0b) /* STM32L1 devices category Cat.3, Cat.4 and Cat.5 */
#define RI_IOSWITCH_CH0b        ((uint32_t)RI_ASCR2_CH0b)
#if defined (RI_ASCR2_CH1b) /* STM32L1 devices category Cat.4 and Cat.5 */
#define RI_IOSWITCH_CH1b        ((uint32_t)RI_ASCR2_CH1b)
#define RI_IOSWITCH_CH2b        ((uint32_t)RI_ASCR2_CH2b)
#define RI_IOSWITCH_CH3b        ((uint32_t)RI_ASCR2_CH3b)
#define RI_IOSWITCH_CH6b        ((uint32_t)RI_ASCR2_CH6b)
#define RI_IOSWITCH_CH7b        ((uint32_t)RI_ASCR2_CH7b)
#define RI_IOSWITCH_CH8b        ((uint32_t)RI_ASCR2_CH8b)
#define RI_IOSWITCH_CH9b        ((uint32_t)RI_ASCR2_CH9b)
#define RI_IOSWITCH_CH10b       ((uint32_t)RI_ASCR2_CH10b)
#define RI_IOSWITCH_CH11b       ((uint32_t)RI_ASCR2_CH11b)
#define RI_IOSWITCH_CH12b       ((uint32_t)RI_ASCR2_CH12b)
#endif /* RI_ASCR2_CH1b */
#define RI_IOSWITCH_GR6_3       ((uint32_t)RI_ASCR2_GR6_3)
#define RI_IOSWITCH_GR6_4       ((uint32_t)RI_ASCR2_GR6_4)
#endif /* RI_ASCR2_CH0b */


#if defined (RI_ASCR2_CH1b) /* STM32L1 devices category Cat.4 and Cat.5 */

#define IS_RI_IOSWITCH(__IOSWITCH__) (((__IOSWITCH__) == RI_IOSWITCH_CH0) || ((__IOSWITCH__) == RI_IOSWITCH_CH1)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH2)     || ((__IOSWITCH__) == RI_IOSWITCH_CH3)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH4)     || ((__IOSWITCH__) == RI_IOSWITCH_CH5)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH6)     || ((__IOSWITCH__) == RI_IOSWITCH_CH7)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH8)     || ((__IOSWITCH__) == RI_IOSWITCH_CH9)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH10)    || ((__IOSWITCH__) == RI_IOSWITCH_CH11)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH12)    || ((__IOSWITCH__) == RI_IOSWITCH_CH13)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH14)    || ((__IOSWITCH__) == RI_IOSWITCH_CH15)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH18)    || ((__IOSWITCH__) == RI_IOSWITCH_CH19)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH20)    || ((__IOSWITCH__) == RI_IOSWITCH_CH21)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH22)    || ((__IOSWITCH__) == RI_IOSWITCH_CH23)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH24)    || ((__IOSWITCH__) == RI_IOSWITCH_CH25)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_VCOMP)   || ((__IOSWITCH__) == RI_IOSWITCH_CH27)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH28)    || ((__IOSWITCH__) == RI_IOSWITCH_CH29)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH30)    || ((__IOSWITCH__) == RI_IOSWITCH_CH31)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_1)  || ((__IOSWITCH__) == RI_IOSWITCH_GR10_2) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_3)  || ((__IOSWITCH__) == RI_IOSWITCH_GR10_4) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR6_1)   || ((__IOSWITCH__) == RI_IOSWITCH_GR6_2)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR6_3)   || ((__IOSWITCH__) == RI_IOSWITCH_GR6_4)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR5_1)   || ((__IOSWITCH__) == RI_IOSWITCH_GR5_2)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR5_3)   || ((__IOSWITCH__) == RI_IOSWITCH_GR4_1)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR4_2)   || ((__IOSWITCH__) == RI_IOSWITCH_GR4_3)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH0b)    || ((__IOSWITCH__) == RI_IOSWITCH_CH1b)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH2b)    || ((__IOSWITCH__) == RI_IOSWITCH_CH3b)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH6b)    || ((__IOSWITCH__) == RI_IOSWITCH_CH7b)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH8b)    || ((__IOSWITCH__) == RI_IOSWITCH_CH9b)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH10b)   || ((__IOSWITCH__) == RI_IOSWITCH_CH11b)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH12b))

#else /* !RI_ASCR2_CH1b */

#if defined (RI_ASCR2_CH0b) /* STM32L1 devices category Cat.3 */

#define IS_RI_IOSWITCH(__IOSWITCH__) (((__IOSWITCH__) == RI_IOSWITCH_CH0) || ((__IOSWITCH__) == RI_IOSWITCH_CH1)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH2)     || ((__IOSWITCH__) == RI_IOSWITCH_CH3)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH4)     || ((__IOSWITCH__) == RI_IOSWITCH_CH5)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH6)     || ((__IOSWITCH__) == RI_IOSWITCH_CH7)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH8)     || ((__IOSWITCH__) == RI_IOSWITCH_CH9)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH10)    || ((__IOSWITCH__) == RI_IOSWITCH_CH11)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH12)    || ((__IOSWITCH__) == RI_IOSWITCH_CH13)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH14)    || ((__IOSWITCH__) == RI_IOSWITCH_CH15)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH18)    || ((__IOSWITCH__) == RI_IOSWITCH_CH19)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH20)    || ((__IOSWITCH__) == RI_IOSWITCH_CH21)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH22)    || ((__IOSWITCH__) == RI_IOSWITCH_CH23)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH24)    || ((__IOSWITCH__) == RI_IOSWITCH_CH25)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_VCOMP)   || ((__IOSWITCH__) == RI_IOSWITCH_GR10_1) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_2)  || ((__IOSWITCH__) == RI_IOSWITCH_GR10_3) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_4)  || ((__IOSWITCH__) == RI_IOSWITCH_GR6_1)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR6_2)   || ((__IOSWITCH__) == RI_IOSWITCH_GR5_1)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR5_2)   || ((__IOSWITCH__) == RI_IOSWITCH_GR5_3)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR4_1)   || ((__IOSWITCH__) == RI_IOSWITCH_GR4_2)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR4_3)   || ((__IOSWITCH__) == RI_IOSWITCH_CH0b))

#else /* !RI_ASCR2_CH0b */  /* STM32L1 devices category Cat.1 and Cat.2 */

#define IS_RI_IOSWITCH(__IOSWITCH__) (((__IOSWITCH__) == RI_IOSWITCH_CH0) || ((__IOSWITCH__) == RI_IOSWITCH_CH1)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH2)     || ((__IOSWITCH__) == RI_IOSWITCH_CH3)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH4)     || ((__IOSWITCH__) == RI_IOSWITCH_CH5)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH6)     || ((__IOSWITCH__) == RI_IOSWITCH_CH7)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH8)     || ((__IOSWITCH__) == RI_IOSWITCH_CH9)    || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH10)    || ((__IOSWITCH__) == RI_IOSWITCH_CH11)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH12)    || ((__IOSWITCH__) == RI_IOSWITCH_CH13)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH14)    || ((__IOSWITCH__) == RI_IOSWITCH_CH15)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH18)    || ((__IOSWITCH__) == RI_IOSWITCH_CH19)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH20)    || ((__IOSWITCH__) == RI_IOSWITCH_CH21)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH22)    || ((__IOSWITCH__) == RI_IOSWITCH_CH23)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_CH24)    || ((__IOSWITCH__) == RI_IOSWITCH_CH25)   || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_VCOMP)   || ((__IOSWITCH__) == RI_IOSWITCH_GR10_1) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_2)  || ((__IOSWITCH__) == RI_IOSWITCH_GR10_3) || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR10_4)  || ((__IOSWITCH__) == RI_IOSWITCH_GR6_1)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR6_2)   || ((__IOSWITCH__) == RI_IOSWITCH_GR5_1)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR5_2)   || ((__IOSWITCH__) == RI_IOSWITCH_GR5_3)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR4_1)   || ((__IOSWITCH__) == RI_IOSWITCH_GR4_2)  || \
                                  ((__IOSWITCH__) == RI_IOSWITCH_GR4_3))

#endif /* RI_ASCR2_CH0b */
#endif /* RI_ASCR2_CH1b */

/**
  * @}
  */

/** @defgroup RI_Pin PIN define
  * @{
  */
#define RI_PIN_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define RI_PIN_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define RI_PIN_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define RI_PIN_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define RI_PIN_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define RI_PIN_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define RI_PIN_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define RI_PIN_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define RI_PIN_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define RI_PIN_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define RI_PIN_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define RI_PIN_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define RI_PIN_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define RI_PIN_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define RI_PIN_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define RI_PIN_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define RI_PIN_ALL               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_RI_PIN(__PIN__) ((__PIN__) != (uint16_t)0x00)

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup DBGMCU_Macros DBGMCU: Debug MCU
  * @{
  */

/** @defgroup DBGMCU_Freeze_Unfreeze Freeze Unfreeze Peripherals in Debug mode 
  * @brief   Freeze/Unfreeze Peripherals in Debug mode 
  * @{
  */
  
/**
  * @brief  TIM2 Peripherals Debug mode 
  */  
#if defined (DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#define __HAL_FREEZE_TIM2_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#define __HAL_UNFREEZE_TIM2_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM2_STOP)
#endif

/**
  * @brief  TIM3 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#define __HAL_FREEZE_TIM3_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#define __HAL_UNFREEZE_TIM3_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM3_STOP)
#endif

/**
  * @brief  TIM4 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM4_STOP)
#define __HAL_FREEZE_TIM4_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM4_STOP)
#define __HAL_UNFREEZE_TIM4_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM4_STOP)
#endif

/**
  * @brief  TIM5 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM5_STOP)
#define __HAL_FREEZE_TIM5_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM5_STOP)
#define __HAL_UNFREEZE_TIM5_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM5_STOP)
#endif

/**
  * @brief  TIM6 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#define __HAL_FREEZE_TIM6_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#define __HAL_UNFREEZE_TIM6_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM6_STOP)
#endif

/**
  * @brief  TIM7 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#define __HAL_FREEZE_TIM7_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#define __HAL_UNFREEZE_TIM7_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_TIM7_STOP)
#endif

/**
  * @brief  RTC Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_RTC_STOP)
#define __HAL_FREEZE_RTC_DBGMCU()             SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_RTC_STOP)
#define __HAL_UNFREEZE_RTC_DBGMCU()           CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_RTC_STOP)
#endif

/**
  * @brief  WWDG Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#define __HAL_FREEZE_WWDG_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#define __HAL_UNFREEZE_WWDG_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_WWDG_STOP)
#endif

/**
  * @brief  IWDG Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#define __HAL_FREEZE_IWDG_DBGMCU()            SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#define __HAL_UNFREEZE_IWDG_DBGMCU()          CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_IWDG_STOP)
#endif

/**
  * @brief  I2C1 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT)
#define __HAL_FREEZE_I2C1_TIMEOUT_DBGMCU()    SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT)
#define __HAL_UNFREEZE_I2C1_TIMEOUT_DBGMCU()  CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT)
#endif

/**
  * @brief  I2C2 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT)
#define __HAL_FREEZE_I2C2_TIMEOUT_DBGMCU()    SET_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT)
#define __HAL_UNFREEZE_I2C2_TIMEOUT_DBGMCU()  CLEAR_BIT(DBGMCU->APB1FZ, DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT)
#endif

/**
  * @brief  TIM9 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB2_FZ_DBG_TIM9_STOP)
#define __HAL_FREEZE_TIM9_DBGMCU()            SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM9_STOP)
#define __HAL_UNFREEZE_TIM9_DBGMCU()          CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM9_STOP)
#endif

/**
  * @brief  TIM10 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB2_FZ_DBG_TIM10_STOP)
#define __HAL_FREEZE_TIM10_DBGMCU()           SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM10_STOP)
#define __HAL_UNFREEZE_TIM10_DBGMCU()         CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM10_STOP)
#endif

/**
  * @brief  TIM11 Peripherals Debug mode 
  */
#if defined (DBGMCU_APB2_FZ_DBG_TIM11_STOP)
#define __HAL_FREEZE_TIM11_DBGMCU()           SET_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM11_STOP)
#define __HAL_UNFREEZE_TIM11_DBGMCU()         CLEAR_BIT(DBGMCU->APB2FZ, DBGMCU_APB2_FZ_DBG_TIM11_STOP)
#endif

/**
  * @brief  Enables or disables the output of internal reference voltage 
  *         (VREFINT) on I/O pin.
  *         The VREFINT output can be routed to any I/O in group 3:
  *          - For Cat.1 and Cat.2 devices: CH8 (PB0) or CH9 (PB1).
  *          - For Cat.3 devices: CH8 (PB0), CH9 (PB1) or CH0b (PB2).
  *          - For Cat.4 and Cat.5 devices: CH8 (PB0), CH9 (PB1), CH0b (PB2), 
  *            CH1b (PF11) or CH2b (PF12).
  *         Note: Comparator peripheral clock must be preliminarility enabled,
  *               either in COMP user function "HAL_COMP_MspInit()" (should be 
  *               done if comparators are used) or by direct clock enable:
  *               Refer to macro "__COMP_CLK_ENABLE()".
  *         Note: In addition with this macro, Vrefint output buffer must be 
  *               connected to the selected I/O pin. Refer to macro
  *               "__HAL_RI_IOSWITCH_CLOSE()".
  * @note  ENABLE: Internal reference voltage connected to I/O group 3
  * @note  DISABLE: Internal reference voltage disconnected from I/O group 3
  * @retval None
  */
#define __HAL_VREFINT_OUT_ENABLE()       SET_BIT(COMP->CSR, COMP_CSR_VREFOUTEN)
#define __HAL_VREFINT_OUT_DISABLE()      CLEAR_BIT(COMP->CSR, COMP_CSR_VREFOUTEN)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SYSCFG_Macros SYSCFG: SYStem ConFiG
  * @{
  */

/** @defgroup SYSCFG_BootModeConfig Boot Mode Configuration
  * @{
  */

/**
  * @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_REMAPMEMORY_FLASH()             CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE)

/** @brief  System Flash memory mapped at 0x00000000
  */
#define __HAL_REMAPMEMORY_SYSTEMFLASH()       MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, SYSCFG_MEMRMP_MEM_MODE_0)

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_REMAPMEMORY_SRAM()              MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, SYSCFG_MEMRMP_MEM_MODE_0 | SYSCFG_MEMRMP_MEM_MODE_1)

#if defined(FSMC_R_BASE)
/** @brief  FSMC Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000
  */
#define __HAL_REMAPMEMORY_FSMC()              MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, SYSCFG_MEMRMP_MEM_MODE_1)

#endif /* FSMC_R_BASE */

/**
  * @brief  Returns the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one 
  *         of the following values:
  *           @arg SYSCFG_BOOT_MAINFLASH
  *           @arg SYSCFG_BOOT_SYSTEMFLASH
  *           @arg SYSCFG_BOOT_FSMC (available only for STM32L151xD, STM32L152xD & STM32L162xD)
  *           @arg SYSCFG_BOOT_SRAM
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()          READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BOOT_MODE)

/**
  * @}
  */

/** @defgroup SYSCFG_USBConfig USB DP line Configuration
  * @{
  */

/**
  * @brief  Control the internal pull-up on USB DP line.
  */
#define __HAL_SYSCFG_USBPULLUP_ENABLE()       SET_BIT(SYSCFG->PMC, SYSCFG_PMC_USB_PU)

#define __HAL_SYSCFG_USBPULLUP_DISABLE()      CLEAR_BIT(SYSCFG->PMC, SYSCFG_PMC_USB_PU)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RI_Macris RI: Routing Interface
  * @{
  */ 

/** @defgroup RI_InputCaputureConfig Input Capture configuration
  * @{
  */ 

/**
  * @brief  Configures the routing interface to map Input Capture 1 of TIMx to a selected I/O pin.
  * @param  __TIMSELECT__: Timer select.
  *   This parameter can be one of the following values:
  *     @arg TIM_SELECT_NONE: No timer selected and default Timer mapping is enabled.
  *     @arg TIM_SELECT_TIM2: Timer 2 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM3: Timer 3 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM4: Timer 4 Input Captures to be routed.
  * @param  __INPUT__: selects which pin to be routed to Input Capture.
  *   This parameter must be a value of @ref RI_InputCaptureRouting
  *     e.g.
  *       __HAL_RI_REMAP_INPUTCAPTURE1(TIM_SELECT_TIM2, RI_INPUTCAPTUREROUTING_1)
  *       allows routing of Input capture IC1 of TIM2 to PA4.
  *       For details about correspondence between RI_INPUTCAPTUREROUTING_x 
  *       and I/O pins refer to the parameters' description in the header file
  *       or refer to the product reference manual.
  * @note Input capture selection bits are not reset by this function.
  *       To reset input capture selection bits, use SYSCFG_RIDeInit() function.
  * @note The I/O should be configured in alternate function mode (AF14) using
  *       GPIO_PinAFConfig() function.
  * @retval None.
  */
#define __HAL_RI_REMAP_INPUTCAPTURE1(__TIMSELECT__, __INPUT__)  \
          do {assert_param(IS_RI_TIM(__TIMSELECT__)); \
              assert_param(IS_RI_INPUTCAPTURE_ROUTING(__INPUT__)); \
              MODIFY_REG(RI->ICR, RI_ICR_TIM, (__TIMSELECT__)); \
              SET_BIT(RI->ICR, RI_INPUTCAPTURE_IC1); \
              MODIFY_REG(RI->ICR, RI_ICR_IC1OS, (__INPUT__) << POSITION_VAL(RI_ICR_IC1OS)); \
          }while(0)

/**
  * @brief  Configures the routing interface to map Input Capture 2 of TIMx to a selected I/O pin.
  * @param  __TIMSELECT__: Timer select.
  *   This parameter can be one of the following values:
  *     @arg TIM_SELECT_NONE: No timer selected and default Timer mapping is enabled.
  *     @arg TIM_SELECT_TIM2: Timer 2 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM3: Timer 3 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM4: Timer 4 Input Captures to be routed.
  * @param  __INPUT__: selects which pin to be routed to Input Capture.
  *   This parameter must be a value of @ref RI_InputCaptureRouting
  * @retval None.
  */
#define __HAL_RI_REMAP_INPUTCAPTURE2(__TIMSELECT__, __INPUT__)  \
          do {assert_param(IS_RI_TIM(__TIMSELECT__)); \
              assert_param(IS_RI_INPUTCAPTURE_ROUTING(__INPUT__)); \
              MODIFY_REG(RI->ICR, RI_ICR_TIM, (__TIMSELECT__)); \
              SET_BIT(RI->ICR, RI_INPUTCAPTURE_IC2); \
              MODIFY_REG(RI->ICR, RI_ICR_IC2OS, (__INPUT__) << POSITION_VAL(RI_ICR_IC2OS)); \
          }while(0)

/**
  * @brief  Configures the routing interface to map Input Capture 3 of TIMx to a selected I/O pin.
  * @param  __TIMSELECT__: Timer select.
  *   This parameter can be one of the following values:
  *     @arg TIM_SELECT_NONE: No timer selected and default Timer mapping is enabled.
  *     @arg TIM_SELECT_TIM2: Timer 2 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM3: Timer 3 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM4: Timer 4 Input Captures to be routed.
  * @param  __INPUT__: selects which pin to be routed to Input Capture.
  *   This parameter must be a value of @ref RI_InputCaptureRouting
  * @retval None.
  */
#define __HAL_RI_REMAP_INPUTCAPTURE3(__TIMSELECT__, __INPUT__)  \
          do {assert_param(IS_RI_TIM(__TIMSELECT__)); \
              assert_param(IS_RI_INPUTCAPTURE_ROUTING(__INPUT__)); \
              MODIFY_REG(RI->ICR, RI_ICR_TIM, (__TIMSELECT__)); \
              SET_BIT(RI->ICR, RI_INPUTCAPTURE_IC3); \
              MODIFY_REG(RI->ICR, RI_ICR_IC3OS, (__INPUT__) << POSITION_VAL(RI_ICR_IC3OS)); \
          }while(0)

/**
  * @brief  Configures the routing interface to map Input Capture 4 of TIMx to a selected I/O pin.
  * @param  __TIMSELECT__: Timer select.
  *   This parameter can be one of the following values:
  *     @arg TIM_SELECT_NONE: No timer selected and default Timer mapping is enabled.
  *     @arg TIM_SELECT_TIM2: Timer 2 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM3: Timer 3 Input Captures to be routed.
  *     @arg TIM_SELECT_TIM4: Timer 4 Input Captures to be routed.
  * @param  __INPUT__: selects which pin to be routed to Input Capture.
  *   This parameter must be a value of @ref RI_InputCaptureRouting
  * @retval None.
  */
#define __HAL_RI_REMAP_INPUTCAPTURE4(__TIMSELECT__, __INPUT__)  \
          do {assert_param(IS_RI_TIM(__TIMSELECT__)); \
              assert_param(IS_RI_INPUTCAPTURE_ROUTING(__INPUT__)); \
              MODIFY_REG(RI->ICR, RI_ICR_TIM, (__TIMSELECT__)); \
              SET_BIT(RI->ICR, RI_INPUTCAPTURE_IC4); \
              MODIFY_REG(RI->ICR, RI_ICR_IC4OS, (__INPUT__) << POSITION_VAL(RI_ICR_IC4OS)); \
          }while(0)

/**
  * @}
  */

/** @defgroup RI_SwitchControlConfig Switch Control configuration
  * @{
  */ 

/**
  * @brief  Enable or disable the switch control mode.
  * @note  ENABLE: ADC analog switches closed if the corresponding 
  *                    I/O switch is also closed.
  *                    When using COMP1, switch control mode must be enabled.
  * @note  DISABLE: ADC analog switches open or controlled by the ADC interface.
  *                    When using the ADC for acquisition, switch control mode 
  *                    must be disabled.
  * @note COMP1 comparator and ADC cannot be used at the same time since 
  *       they share the ADC switch matrix.
  * @retval None
  */
#define __HAL_RI_SWITCHCONTROLMODE_ENABLE()       SET_BIT(RI->ASCR1, RI_ASCR1_SCM)

#define __HAL_RI_SWITCHCONTROLMODE_DISABLE()      CLEAR_BIT(RI->ASCR1, RI_ASCR1_SCM)

/*
  * @brief  Close or Open the routing interface Input Output switches.
  * @param  __IOSWITCH__: selects the I/O analog switch number.
  *   This parameter must be a value of @ref RI_IOSwitch
  * @retval None
  */
#define __HAL_RI_IOSWITCH_CLOSE(__IOSWITCH__) do { assert_param(IS_RI_IOSWITCH(__IOSWITCH__)); \
            if ((__IOSWITCH__) >> 31 != 0 ) \
            { \
              SET_BIT(RI->ASCR1, (__IOSWITCH__) & 0x7FFFFFFF); \
            } \
            else \
            { \
              SET_BIT(RI->ASCR2, (__IOSWITCH__)); \
            } \
          }while(0)

#define __HAL_RI_IOSWITCH_OPEN(__IOSWITCH__) do { assert_param(IS_RI_IOSWITCH(__IOSWITCH__)); \
            if ((__IOSWITCH__) >> 31 != 0 ) \
            { \
              CLEAR_BIT(RI->ASCR1, (__IOSWITCH__) & 0x7FFFFFFF); \
            } \
            else \
            { \
              CLEAR_BIT(RI->ASCR2, (__IOSWITCH__)); \
            } \
          }while(0)

#if defined (COMP_CSR_SW1)
/**
  * @brief  Close or open the internal switch COMP1_SW1.
  *         This switch connects I/O pin PC3 (can be used as ADC channel 13) 
  *         and OPAMP3 ouput to ADC switch matrix (ADC channel VCOMP, channel
  *         26) and COMP1 non-inverting input.
  *         Pin PC3 connection depends on another switch setting, refer to
  *         macro "__HAL_ADC_CHANNEL_SPEED_FAST()".
  * @retval None.
  */
#define __HAL_RI_SWITCH_COMP1_SW1_CLOSE()  SET_BIT(COMP->CSR, COMP_CSR_SW1)

#define __HAL_RI_SWITCH_COMP1_SW1_OPEN()   CLEAR_BIT(COMP->CSR, COMP_CSR_SW1)
#endif /* COMP_CSR_SW1 */

/**
  * @}
  */

/** @defgroup RI_HystConfig Hysteresis Activation and Deactivation
  * @{
  */ 

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports A
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTA_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR1, (__IOPIN__)); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTA_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR1, (__IOPIN__)); \
          } while(0)

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports B
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTB_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR1, (__IOPIN__) << 16 ); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTB_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR1, (__IOPIN__) << 16 ); \
          } while(0)

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports C
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTC_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR2, (__IOPIN__)); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTC_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR2, (__IOPIN__)); \
          } while(0)

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports D
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTD_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR2, (__IOPIN__) << 16 ); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTD_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR2, (__IOPIN__) << 16 ); \
          } while(0)

#if defined (GPIOE_BASE)
    
/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports E
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTE_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR3, (__IOPIN__)); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTE_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR3, (__IOPIN__)); \
          } while(0)

#endif /* GPIOE_BASE */

#if defined(GPIOF_BASE) || defined(GPIOG_BASE)

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports F
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTF_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR3, (__IOPIN__) << 16 ); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTF_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR3, (__IOPIN__) << 16 ); \
          } while(0)

/**
  * @brief  Enable or disable Hysteresis of the input schmitt triger of Ports G
  *         When the I/Os are programmed in input mode by standard I/O port 
  *         registers, the Schmitt trigger and the hysteresis are enabled by default.
  *         When hysteresis is disabled, it is possible to read the 
  *         corresponding port with a trigger level of VDDIO/2.
  *  @param __IOPIN__ : Selects the pin(s) on which to enable or disable hysteresis.
  *   This parameter must be a value of @ref RI_Pin
  * @retval None
  */
#define __HAL_RI_HYSTERIS_PORTG_ON(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            CLEAR_BIT(RI->HYSCR4, (__IOPIN__)); \
          } while(0)

#define __HAL_RI_HYSTERIS_PORTG_OFF(__IOPIN__) do {assert_param(IS_RI_PIN(__IOPIN__)); \
            SET_BIT(RI->HYSCR4, (__IOPIN__)); \
          } while(0)

#endif /* GPIOF_BASE || GPIOG_BASE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup HAL_Exported_Functions
  * @{
  */

/** @addtogroup HAL_Exported_Functions_Group1
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void              HAL_MspInit(void);
void              HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);

/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group2
  * @{
  */

/* Peripheral Control functions  ************************************************/
void              HAL_IncTick(void);
void              HAL_Delay(__IO uint32_t Delay);
uint32_t          HAL_GetTick(void);
void              HAL_SuspendTick(void);
void              HAL_ResumeTick(void);
uint32_t          HAL_GetHalVersion(void);
uint32_t          HAL_GetREVID(void);
uint32_t          HAL_GetDEVID(void);
void              HAL_EnableDBGSleepMode(void);
void              HAL_DisableDBGSleepMode(void);
void              HAL_EnableDBGStopMode(void);
void              HAL_DisableDBGStopMode(void);
void              HAL_EnableDBGStandbyMode(void);
void              HAL_DisableDBGStandbyMode(void);

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

#endif /* __STM32L1xx_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
