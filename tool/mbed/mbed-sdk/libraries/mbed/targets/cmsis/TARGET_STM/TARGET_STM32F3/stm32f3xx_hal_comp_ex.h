/**
  ******************************************************************************
  * @file    stm32f3xx_hal_comp_ex.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of COMP HAL Extended module.
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
#ifndef __STM32F3xx_HAL_COMP_EX_H
#define __STM32F3xx_HAL_COMP_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @defgroup COMPEx COMP Extended HAL module driver
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/
/** @defgroup COMPEx_Exported_Constants COMP Extended Exported Constants
  * @{
  */

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
   /** @defgroup COMPEx_InvertingInput  COMP Extended InvertingInput (STM32F302xE/STM32F303xE/STM32F398xx/STM32F302xC/STM32F303xC/STM32F358xx Product devices)
  * @{
  */
#define COMP_INVERTINGINPUT_1_4VREFINT       ((uint32_t)0x00000000)                        /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT       COMP_CSR_COMPxINSEL_0                         /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT       COMP_CSR_COMPxINSEL_1                         /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_VREFINT          (COMP_CSR_COMPxINSEL_1|COMP_CSR_COMPxINSEL_0) /*!< VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH1         COMP_CSR_COMPxINSEL_2                         /*!< DAC1_CH1_OUT (PA4) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH2         (COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_0) /*!< DAC1_CH2_OUT (PA5) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO1              (COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_1) /*!< I/O1 (PA0 for COMP1, PA2 for COMP2, PD15 for COMP3, 
                                                                                                PE8 for COMP4, PD13 for COMP5, PD10 for COMP6,
                                                                                                PC0 for COMP7) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO2               COMP_CSR_COMPxINSEL                          /*!< I/O2 (PB12 for COMP3, PB2 for COMP4, PB10 for COMP5,
                                                                                               PB15 for COMP6) connected to comparator inverting input */
/* Aliases for compatibility */
#define COMP_INVERTINGINPUT_DAC1              COMP_INVERTINGINPUT_DAC1_CH1
#define COMP_INVERTINGINPUT_DAC2              COMP_INVERTINGINPUT_DAC1_CH2

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)          || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH1)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH2)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO1)              || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO2))
/**
  * @}
  */ 
#elif defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup COMPEx_InvertingInput COMP Extended InvertingInput (STM32F301x8/STM32F302x8/STM32F318xx Product devices)
  * @{
  */
#define COMP_INVERTINGINPUT_1_4VREFINT     ((uint32_t)0x00000000)                        /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT     COMP_CSR_COMPxINSEL_0                         /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT     COMP_CSR_COMPxINSEL_1                         /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_VREFINT        (COMP_CSR_COMPxINSEL_1|COMP_CSR_COMPxINSEL_0) /*!< VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH1       COMP_CSR_COMPxINSEL_2                         /*!< DAC1_CH1_OUT (PA4) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO1            (COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_1) /*!< I/O1 (PA2 for COMP2, PB2 for COMP4, PB15 for COMP6)
                                                                                              connected to comparator inverting input */
/* Aliases for compatibility */
#define COMP_INVERTINGINPUT_DAC1           COMP_INVERTINGINPUT_DAC1_CH1

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)          || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH1)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO1))
/**
  * @}
  */
#elif defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/** @defgroup COMPEx_InvertingInput COMP Extended InvertingInput (STM32F303x8/STM32F334x8/STM32F328xx Product devices)
  * @{
  */
#define COMP_INVERTINGINPUT_1_4VREFINT     ((uint32_t)0x00000000)                        /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT     COMP_CSR_COMPxINSEL_0                         /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT     COMP_CSR_COMPxINSEL_1                         /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_VREFINT        (COMP_CSR_COMPxINSEL_1|COMP_CSR_COMPxINSEL_0) /*!< VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH1       COMP_CSR_COMPxINSEL_2                         /*!< DAC1_CH1_OUT (PA4) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH2       (COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_0) /*!< DAC1_CH2_OUT (PA5) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO1            (COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_1) /*!< I/O1 (PA2 for COMP2, PB2 for COMP4, PB15 for COMP6)
                                                                                              connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC2_CH1       COMP_CSR_COMPxINSEL_3                         /*!< DAC2_CH1_OUT connected to comparator inverting input */
/* Aliases for compatibility */
#define COMP_INVERTINGINPUT_DAC1           COMP_INVERTINGINPUT_DAC1_CH1
#define COMP_INVERTINGINPUT_DAC2           COMP_INVERTINGINPUT_DAC1_CH2

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)          || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH1)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH2)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO1)              || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC2_CH1))
/**
  * @}
  */
#elif defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup COMPEx_InvertingInput COMP Extended InvertingInput (STM32F373xC/STM32F378xx Product devices)
  * @{
  */
#define COMP_INVERTINGINPUT_1_4VREFINT  ((uint32_t)0x00000000)                        /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_1_2VREFINT  ((uint32_t)COMP_CSR_COMPxINSEL_0)             /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_3_4VREFINT  ((uint32_t)COMP_CSR_COMPxINSEL_1)             /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_VREFINT     ((uint32_t)(COMP_CSR_COMPxINSEL_1|COMP_CSR_COMPxINSEL_0)) /*!< VREFINT connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH1    ((uint32_t)COMP_CSR_COMPxINSEL_2)                         /*!< DAC1_CH1_OUT (PA4) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC1_CH2    ((uint32_t)(COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_0)) /*!< DAC1_CH2_OUT (PA5) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_IO1         ((uint32_t)(COMP_CSR_COMPxINSEL_2|COMP_CSR_COMPxINSEL_1)) /*!< I/O1 (PA0 for COMP1, PA2 for COMP2) connected to comparator inverting input */
#define COMP_INVERTINGINPUT_DAC2_CH1    ((uint32_t)COMP_CSR_COMPxINSEL)                          /*!< DAC2_CH1_OUT connected to comparator inverting input */
/* Aliases for compatibility */
#define COMP_INVERTINGINPUT_DAC1        COMP_INVERTINGINPUT_DAC1_CH1
#define COMP_INVERTINGINPUT_DAC2        COMP_INVERTINGINPUT_DAC1_CH2

#define IS_COMP_INVERTINGINPUT(INPUT) (((INPUT) == COMP_INVERTINGINPUT_1_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_1_2VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_3_4VREFINT)       || \
                                       ((INPUT) == COMP_INVERTINGINPUT_VREFINT)          || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH1)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC1_CH2)         || \
                                       ((INPUT) == COMP_INVERTINGINPUT_IO1)              || \
                                       ((INPUT) == COMP_INVERTINGINPUT_DAC2_CH1))
/**
  * @}
  */
#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx */

#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup COMPEx_NonInvertingInput  COMP Extended NonInvertingInput (STM32F302xC/STM32F303xC/STM32F358xx Product devices)
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1               ((uint32_t)0x00000000) /*!< I/O1 (PA1 for COMP1, PA7 for COMP2, PB14 for COMP3, 
                                                                             PB0 for COMP4, PD12 for COMP5, PD11 for COMP6,
                                                                             PA0 for COMP7) connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_IO2               COMP_CSR_COMPxNONINSEL /*!< I/O2 (PA3 for COMP2, PD14 for COMP3, PE7 for COMP4, PB13 for COMP5,
                                                                             PB11 for COMP6, PC1 for COMP7) connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED  COMP1_CSR_COMP1SW1     /*!< DAC ouput connected to comparator COMP1 non inverting input */

#define IS_COMP_NONINVERTINGINPUT(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_IO1) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_IO2) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED))

/* STM32F302xB/xC, STM32F303xB/xC, STM32F358xx devices comparator instances non inverting source values */
#define IS_COMP_NONINVERTINGINPUT_INSTANCE(INSTANCE, INPUT)    \
   ((((INSTANCE) == COMP1)  &&                                 \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)                || \
     ((INPUT) == COMP_NONINVERTINGINPUT_IO2)                || \
     ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED)))    \
    ||                                                         \
    ((((INPUT) == COMP_NONINVERTINGINPUT_IO1)               || \
      ((INPUT) == COMP_NONINVERTINGINPUT_IO2))))

#define COMP_CSR_COMPxNONINSEL_MASK            (COMP_CSR_COMPxNONINSEL | COMP1_CSR_COMP1SW1) /*!< COMP_CSR_COMPxNONINSEL mask */
/**
  * @}
  */ 
#elif defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup COMPEx_NonInvertingInput COMP Extended NonInvertingInput (STM32F301x8/STM32F302x8/STM32F318xx Product devices)
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1               ((uint32_t)0x00000000) /*!< I/O1 (PA7 for COMP2, PB0 for COMP4, PB11 for COMP6)
                                                                             connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED  COMP2_CSR_COMP2INPDAC  /*!< DAC ouput connected to comparator COMP2 non inverting input */

#define IS_COMP_NONINVERTINGINPUT(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_IO1) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED))

/* STM32F301x6/x8, STM32F302x6/x8, STM32F318xx devices comparator instances non inverting source values */
#define IS_COMP_NONINVERTINGINPUT_INSTANCE(INSTANCE, INPUT)    \
   ((((INSTANCE) == COMP2)  &&                                 \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)                || \
     ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED)))    \
    ||                                                         \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)))

#define COMP_CSR_COMPxNONINSEL_MASK              (COMP2_CSR_COMP2INPDAC) /*!< COMP_CSR_COMPxNONINSEL mask */
/**
  * @}
  */ 
#elif defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup COMPEx_NonInvertingInput COMP Extended NonInvertingInput (STM32F373xC/STM32F378xx Product devices)
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1               ((uint32_t)0x00000000) /*!< I/O1 (PA1 for COMP1, PA3 for COMP2) 
                                                                             connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED  COMP_CSR_COMP1SW1  /*!< DAC ouput connected to comparator COMP1 non inverting input */

#define IS_COMP_NONINVERTINGINPUT(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_IO1) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED))

/* STM32F373xB/xC, STM32F378xx devices comparator instances non inverting source values */
#define IS_COMP_NONINVERTINGINPUT_INSTANCE(INSTANCE, INPUT)    \
   ((((INSTANCE) == COMP1)  &&                                 \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)                || \
     ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED)))    \
    ||                                                         \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)))

#define COMP_CSR_COMPxNONINSEL_MASK              (COMP_CSR_COMP1SW1) /*!< COMP_CSR_COMPxNONINSEL mask */
/**
  * @}
  */
#elif defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx)
/** @defgroup COMPEx_NonInvertingInput  COMP Extended NonInvertingInput (STM32F302xE/STM32F303xE/STM32F398xx Product devices)
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1             ((uint32_t)0x00000000)   /*!< I/O1 (PA1 for COMP1, PA7 for COMP2, PB14 for COMP3, 
                                                                            PB0 for COMP4, PD12 for COMP5, PD11 for COMP6,
                                                                            PA0 for COMP7) connected to comparator non inverting input */
#define COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED COMP1_CSR_COMP1SW1      /*!< DAC ouput connected to comparator COMP1 non inverting input */

#define IS_COMP_NONINVERTINGINPUT(INPUT) (((INPUT) == COMP_NONINVERTINGINPUT_IO1) || \
                                          ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED))

/* STM32F302xE/STM32F303xE/STM32F398xx devices comparator instances non inverting source values */
#define IS_COMP_NONINVERTINGINPUT_INSTANCE(INSTANCE, INPUT)    \
   ((((INSTANCE) == COMP1)  &&                                 \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)                || \
     ((INPUT) == COMP_NONINVERTINGINPUT_DAC1SWITCHCLOSED)))    \
    ||                                                         \
    (((INPUT) == COMP_NONINVERTINGINPUT_IO1)))

#define COMP_CSR_COMPxNONINSEL_MASK            (COMP1_CSR_COMP1SW1) /*!< COMP_CSR_COMPxNONINSEL mask */
/**
  * @}
  */ 
#else
/** @defgroup COMPEx_NonInvertingInput COMP Extended NonInvertingInput (Other Product devices)
  * @{
  */
#define COMP_NONINVERTINGINPUT_IO1             ((uint32_t)0x00000000) /*!< I/O1 (PA7 for COMP2, PB0 for COMP4, PB11 for COMP6) 
                                                                           connected to comparator non inverting input */
/*!< Non inverting input not available */
#define IS_COMP_NONINVERTINGINPUT(INPUT) ((INPUT) == (INPUT))  /*!< Multiple selection not available: check always true */

#define IS_COMP_NONINVERTINGINPUT_INSTANCE(INSTANCE, INPUT) ((INPUT) == (INPUT))   /*!< Multiple selection not available: check always true */

#define COMP_CSR_COMPxNONINSEL_MASK           ((uint32_t)0x00000000) /*!< Mask empty: feature not available */
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx */

#if  defined(STM32F302xC)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F302xC Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                             ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP1, COMP2, COMP4, COMP6 */
#define COMP_OUTPUT_TIM1BKIN                         COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2_BRK2                   ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM1BKIN2                        ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 */
/* Output Redirection common for COMP1 and COMP2 */
#define COMP_OUTPUT_TIM1OCREFCLR                      ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM1IC1                           ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4                           ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR                      ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1                           ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
/* Output Redirection common for COMP1,COMP2 and COMP4 */
#define COMP_OUTPUT_TIM3OCREFCLR                      ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM3IC3                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_OUTPUT_TIM15IC2                          ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM4IC2                           ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR                     ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_COMP6TIM2OCREFCLR                 ((uint32_t)0x00002000)   /*!< COMP6 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR                     ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1                          ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC4                           ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2_BRK2)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC2)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6TIM2OCREFCLR)   || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4))
/**
  * @}
  */ 
#elif  defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F303xC/STM32F358xx Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP1...COMP7 */
#define COMP_OUTPUT_TIM1BKIN              COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2             ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM8BKIN              ((uint32_t)0x00000C00)   /*!< COMP output connected to TIM8 Break Input (BKIN) */
#define COMP_OUTPUT_TIM8BKIN2             ((uint32_t)0x00001000)   /*!< COMP output connected to TIM8 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2   ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 and TIM8 Break Input 2 */
/* Output Redirection common for COMP1, COMP2 and COMP3 */
#define COMP_OUTPUT_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
/* Output Redirection common for COMP1 and COMP2 */
#define COMP_OUTPUT_TIM1IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR          ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1               ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP3 */
#define COMP_OUTPUT_TIM4IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_OUTPUT_TIM3IC2               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM3 Input Capture 2 */
#define COMP_OUTPUT_TIM15IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 Input Capture 1 */
#define COMP_OUTPUT_TIM15BKIN             ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM15 Break Input (BKIN) */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM3IC3               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_OUTPUT_TIM8OCREFCLR          ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_OUTPUT_TIM15IC2              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM4IC2               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP5 */
#define COMP_OUTPUT_TIM2IC1               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 1 */
#define COMP_OUTPUT_TIM8OCREFCLR          ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_OUTPUT_TIM17IC1              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM17 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC3               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 3 */
#define COMP_OUTPUT_TIM16BKIN             ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Break Input (BKIN) */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_TIM8OCREFCLR          ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_OUTPUT_COMP6_TIM2OCREFCLR    ((uint32_t)0x00002000)   /*!< COMP6 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC4               ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */
/* Output Redirection specific to COMP7 */
#define COMP_OUTPUT_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM8OCREFCLR          ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_OUTPUT_TIM2IC3               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 3 */
#define COMP_OUTPUT_TIM1IC2               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM1 Input Capture 2 */
#define COMP_OUTPUT_TIM17OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM17BKIN             ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6_TIM2OCREFCLR)  || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC2)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17OCREFCLR))
/**
  * @}
  */ 
#elif defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F301x8/STM32F302x8/STM32F318xx Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP2, COMP4 and COMP6 */
#define COMP_OUTPUT_TIM1BKIN              COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2             ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
/* Output Redirection specific to COMP2 */
#define COMP_OUTPUT_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM1IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR          ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM15IC2              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_COMP6_TIM2OCREFCLR    ((uint32_t)0x00002000)   /*!< COMP6 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6_TIM2OCREFCLR)  || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC2)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR))
/**
  * @}
  */ 
#elif  defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F303x8/STM32F334x8/STM32F328xx Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP2, COMP4 and COMP6 */
#define COMP_OUTPUT_TIM1BKIN              COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2             ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
/* Output Redirection specific to COMP2 */
#define COMP_OUTPUT_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM1IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR          ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1               ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM3IC3               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_OUTPUT_TIM15IC2              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_COMP6_TIM2OCREFCLR    ((uint32_t)0x00002000)   /*!< COMP6 output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6_TIM2OCREFCLR)  || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC2)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR))
/**
  * @}
  */ 
#elif  defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F373xC/STM32F378xx Product devices)
  * @{
  */
/* Output Redirection common for all comparators COMP1 and COMP2 */
#define COMP_OUTPUT_NONE                  ((uint32_t)0x0000)   /*!< COMP output isn't connected to other peripherals */
#define COMP_OUTPUT_TIM3IC1               ((uint32_t)0x0200)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR          ((uint32_t)0x0300)   /*!< COMP output connected to TIM3 OCREF Clear */
#define COMP_OUTPUT_TIM2IC4               ((uint32_t)0x0400)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR          ((uint32_t)0x0500)   /*!< COMP output connected to TIM2 OCREF Clear */
/* Output Redirection specific to COMP1 */
#define COMP_OUTPUT_TIM15BKIN             ((uint32_t)0x0100)   /*!< COMP output connected to TIM15 Break Input */
#define COMP_OUTPUT_TIM5IC4               ((uint32_t)0x0600)   /*!< COMP output connected to TIM5 Input Capture 4 */
#define COMP_OUTPUT_TIM5OCREFCLR          ((uint32_t)0x0700)   /*!< COMP output connected to TIM5 OCREF Clear */
/* Output Redirection specific to COMP2 */
#define COMP_OUTPUT_TIM16BKIN             ((uint32_t)0x0100)   /*!< COMP output connected to TIM16 Break Input */
#define COMP_OUTPUT_TIM4IC1               ((uint32_t)0x0200)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_OUTPUT_TIM4OCREFCLR          ((uint32_t)0x0300)   /*!< COMP output connected to TIM4 OCREF Clear */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM5IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM5OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16BKIN))
/**
  * @}
  */ 
#elif defined(STM32F302xE)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F302xE Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                             ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP1, COMP2, COMP4, COMP6 */
#define COMP_OUTPUT_TIM1BKIN                         COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2_BRK2                   ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM1BKIN2                        ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 */
/* Output Redirection common for COMP1 and COMP2 */
#define COMP_OUTPUT_TIM1OCREFCLR                      ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM1IC1                           ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4                           ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR                      ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1                           ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR                      ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM3IC3                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_OUTPUT_TIM15IC2                          ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM4IC2                           ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR                     ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_COMP6TIM2OCREFCLR                 ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR                     ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1                          ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC4                           ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2_BRK2)      || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC2)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6TIM2OCREFCLR)   || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4))

/**
  * @}
  */ 
#elif defined(STM32F303xE) || defined(STM32F398xx)
/** @defgroup COMPEx_Output COMP Extended Output (STM32F303xE/STM32F398xx Product devices)
  * @{
  */
#define COMP_OUTPUT_NONE                             ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */
/* Output Redirection common for all comparators COMP1...COMP7 */
#define COMP_OUTPUT_TIM1BKIN                         COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_OUTPUT_TIM1BKIN2                        ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM8BKIN                         ((uint32_t)0x00000C00)   /*!< COMP output connected to TIM8 Break Input (BKIN) */
#define COMP_OUTPUT_TIM8BKIN2                        ((uint32_t)0x00001000)   /*!< COMP output connected to TIM8 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2              ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 and TIM8 Break Input 2 */
#define COMP_OUTPUT_TIM20BKIN                        ((uint32_t)0x00003000)   /*!< COMP output connected to TIM20 Break Input (BKIN) */
#define COMP_OUTPUT_TIM20BKIN2                       ((uint32_t)0x00003400)   /*!< COMP output connected to TIM20 Break Input 2 (BKIN2) */
#define COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2_TIM20BKIN2   ((uint32_t)0x00003800)   /*!< COMP output connected to TIM1 Break Input 2, TIM8 Break Input 2 and TIM20 Break Input 2  */
/* Output Redirection common for COMP1 and COMP2 */
#define COMP_OUTPUT_TIM1OCREFCLR                      ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_OUTPUT_TIM1IC1                           ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_OUTPUT_TIM2IC4                           ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_TIM2OCREFCLR                      ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM3IC1                           ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_TIM3OCREFCLR                      ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */
/* Output Redirection specific to COMP2 */
#define COMP_OUTPUT_TIM20OCREFCLR                     ((uint32_t)0x00003C00)   /*!< COMP output connected to TIM20 OCREF Clear */
/* Output Redirection specific to COMP3 */
#define COMP_OUTPUT_TIM4IC1                           ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_OUTPUT_TIM3IC2                           ((uint32_t)0x00002000)   /*!< COMP output connected to TIM3 Input Capture 2 */
#define COMP_OUTPUT_TIM15IC1                          ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 Input Capture 1 */
#define COMP_OUTPUT_TIM15BKIN                         ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM15 Break Input (BKIN) */
/* Output Redirection specific to COMP4 */
#define COMP_OUTPUT_TIM3IC3                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_OUTPUT_TIM8OCREFCLR                      ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_OUTPUT_TIM15IC2                          ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_OUTPUT_TIM4IC2                           ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_OUTPUT_TIM15OCREFCLR                     ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */
/* Output Redirection specific to COMP5 */
#define COMP_OUTPUT_TIM2IC1                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 1 */
#define COMP_OUTPUT_TIM17IC1                          ((uint32_t)0x00002000)   /*!< COMP output connected to TIM17 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC3                           ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 3 */
#define COMP_OUTPUT_TIM16BKIN                         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Break Input (BKIN) */
/* Output Redirection specific to COMP6 */
#define COMP_OUTPUT_TIM2IC2                           ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_OUTPUT_COMP6TIM2OCREFCLR                 ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_OUTPUT_TIM16OCREFCLR                     ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM16IC1                          ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_OUTPUT_TIM4IC4                           ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */
/* Output Redirection specific to COMP7 */
#define COMP_OUTPUT_TIM2IC3                           ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 3 */
#define COMP_OUTPUT_TIM1IC2                           ((uint32_t)0x00002400)   /*!< COMP output connected to TIM1 Input Capture 2 */
#define COMP_OUTPUT_TIM17OCREFCLR                     ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_OUTPUT_TIM17BKIN                         ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM16 Break Input (BKIN) */
#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_OUTPUT_NONE)                || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_COMP6TIM2OCREFCLR)   || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM20OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8BKIN)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8BKIN2)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM20BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM20BKIN2)          || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1BKIN2_TIM8BKIN2_TIM20BKIN2) || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM8OCREFCLR)        || \
                                ((OUTPUT) == COMP_OUTPUT_TIM3IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM15IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC1)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16IC1)            || \
                                ((OUTPUT) == COMP_OUTPUT_TIM4IC4)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_OUTPUT_TIM2IC3)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM1IC2)             || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17BKIN)           || \
                                ((OUTPUT) == COMP_OUTPUT_TIM17OCREFCLR))
/**
  * @}
  */ 
#endif /* STM32F302xC */

#if  defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup COMPEx_WindowMode COMP Extended WindowMode (STM32F302xC/STM32F303xC/STM32F358xx Product devices)
  * @{
  */
#define COMP_WINDOWMODE_DISABLED               ((uint32_t)0x00000000)  /*!< Window mode disabled */
#define COMP_WINDOWMODE_ENABLED                COMP_CSR_COMPxWNDWEN    /*!< Window mode enabled: non inverting input of comparator X (x=2,4,6)
                                                                            is connected to the non inverting input of comparator X-1 */
#define IS_COMP_WINDOWMODE(WINDOWMODE) (((WINDOWMODE) == COMP_WINDOWMODE_DISABLED) || \
                                        ((WINDOWMODE) == COMP_WINDOWMODE_ENABLED))

#define COMP_CSR_COMPxWNDWEN_MASK              COMP_CSR_COMPxWNDWEN /*!< COMP_CSR_COMPxWNDWEN mask */
/**
  * @}
  */
#elif defined(STM32F373xC) || defined(STM32F378xx)
/** @defgroup COMPEx_WindowMode COMP Extended WindowMode (STM32F373xC/STM32F378xx Product devices)
  * @{
  */
#define COMP_WINDOWMODE_DISABLED               ((uint32_t)0x00000000)  /*!< Window mode disabled */
#define COMP_WINDOWMODE_ENABLED                ((uint32_t)COMP_CSR_COMPxWNDWEN) /*!< Window mode enabled: non inverting input of comparator 2
                                                                            is connected to the non inverting input of comparator 1 (PA1) */
#define IS_COMP_WINDOWMODE(WINDOWMODE) (((WINDOWMODE) == COMP_WINDOWMODE_DISABLED) || \
                                        ((WINDOWMODE) == COMP_WINDOWMODE_ENABLED))

#define COMP_CSR_COMPxWNDWEN_MASK              COMP_CSR_COMPxWNDWEN /*!< COMP_CSR_COMPxWNDWEN mask */
/**
  * @}
  */
#else
/** @defgroup COMPEx_WindowMode COMP Extended WindowMode (Other Product devices)
  * @{
  */
#define COMP_WINDOWMODE_DISABLED               ((uint32_t)0x00000000)  /*!< Window mode disabled (not available) */

#define IS_COMP_WINDOWMODE(WINDOWMODE) ((WINDOWMODE) == (WINDOWMODE)) /*!< Not available: check always true */

#define COMP_CSR_COMPxWNDWEN_MASK              ((uint32_t)0x00000000) /*!< Mask empty: feature not available */
/**
  * @}
  */
#endif /* STM32F302xC || STM32F303xC || STM32F358xx */

/** @defgroup COMPEx_Mode COMP Extended Mode
  * @{
  */
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)

/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_MODE_HIGHSPEED               ((uint32_t)0x00000000) /*!< High Speed */
#define COMP_MODE_MEDIUMSPEED             COMP_CSR_COMPxMODE_0   /*!< Medium Speed */
#define COMP_MODE_LOWPOWER                COMP_CSR_COMPxMODE_1   /*!< Low power mode */
#define COMP_MODE_ULTRALOWPOWER           COMP_CSR_COMPxMODE     /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)  (((MODE) == COMP_MODE_HIGHSPEED)     || \
                             ((MODE) == COMP_MODE_MEDIUMSPEED)   || \
                             ((MODE) == COMP_MODE_LOWPOWER)      || \
                             ((MODE) == COMP_MODE_ULTRALOWPOWER))

#define COMP_CSR_COMPxMODE_MASK           COMP_CSR_COMPxMODE     /*!< COMP_CSR_COMPxMODE Mask */

#else

/*!< Power mode not available */
#define IS_COMP_MODE(MODE)  ((MODE) == (MODE))  /*!< Not available: check always true */

#define COMP_CSR_COMPxMODE_MASK           ((uint32_t)0x00000000) /*!< Mask empty: feature not available */

#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx */
/**
  * @}
  */

/** @defgroup COMPEx_Hysteresis COMP Extended Hysteresis
  * @{
  */
#if defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)

#define COMP_HYSTERESIS_NONE              ((uint32_t)0x00000000)  /*!< No hysteresis */
#define COMP_HYSTERESIS_LOW               COMP_CSR_COMPxHYST_0    /*!< Hysteresis level low */
#define COMP_HYSTERESIS_MEDIUM            COMP_CSR_COMPxHYST_1    /*!< Hysteresis level medium */
#define COMP_HYSTERESIS_HIGH              COMP_CSR_COMPxHYST      /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_HYSTERESIS_NONE)   || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_LOW)    || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_MEDIUM) || \
                                           ((HYSTERESIS) == COMP_HYSTERESIS_HIGH))

#define COMP_CSR_COMPxHYST_MASK           COMP_CSR_COMPxHYST /*!< COMP_CSR_COMPxHYST Mask */

#else

#define COMP_HYSTERESIS_NONE              ((uint32_t)0x00000000)  /*!< No hysteresis */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    ((HYSTERESIS) == (HYSTERESIS)) /*!< Not available: check always true */

#define COMP_CSR_COMPxHYST_MASK           ((uint32_t)0x00000000) /*!< Mask empty: feature not available */

#endif /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F373xC || STM32F378xx */
/**
  * @}
  */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/** @defgroup COMPEx_BlankingSrce  COMP Extended Blanking Source (STM32F301x8/STM32F302x8/STM32F303x8/STM32F334x8/STM32F318xx/STM32F328xx Product devices)
  * @{
  */
/* No blanking source can be selected for all comparators */
#define COMP_BLANKINGSRCE_NONE                 ((uint32_t)0x00000000)    /*!< No blanking source */
/* Blanking source for COMP2 */
#define COMP_BLANKINGSRCE_TIM1OC5              COMP_CSR_COMPxBLANKING_0  /*!< TIM1 OC5 selected as blanking source for compartor */
#define COMP_BLANKINGSRCE_TIM2OC3              COMP_CSR_COMPxBLANKING_1  /*!< TIM2 OC3 selected as blanking source for compartor */
#define COMP_BLANKINGSRCE_TIM3OC3              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM3 OC3 selected as blanking source for compartor */
/* Blanking source for COMP4 */
#define COMP_BLANKINGSRCE_TIM3OC4              COMP_CSR_COMPxBLANKING_0    /*!< TIM3 OC4 selected as blanking source for compartor */
#define COMP_BLANKINGSRCE_TIM15OC1             (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM15 OC1 selected as blanking source for compartor */
/* Blanking source for COMP6 */
#define COMP_BLANKINGSRCE_TIM2OC4              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM2 OC4 selected as blanking source for compartor */
#define COMP_BLANKINGSRCE_TIM15OC2              COMP_CSR_COMPxBLANKING_2    /*!< TIM15 OC2 selected as blanking source for compartor */
#define IS_COMP_BLANKINGSRCE(SOURCE) (((SOURCE) == COMP_BLANKINGSRCE_NONE)     || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM1OC5)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC1) || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC2))

/* STM32F301x6/x8, STM32F302x6/x8, STM32F303x6/x8, STM32F334x4/6/8, STM32F318xx/STM32F328xx devices comparator instances blanking source values */
#define IS_COMP_BLANKINGSRCE_INSTANCE(INSTANCE, BLANKINGSRCE) \
   ((((INSTANCE) == COMP2)  &&                                \
    (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)     ||        \
     ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM1OC5)  ||        \
     ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC3)  ||        \
     ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC3)))          \
    ||                                                        \
    (((INSTANCE) == COMP4) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC1)))        \
    ||                                                        \
    (((INSTANCE) == COMP6) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC2))))

#define COMP_CSR_COMPxBLANKING_MASK            COMP_CSR_COMPxBLANKING /*!< COMP_CSR_COMPxBLANKING mask */

/**
  * @}
  */

/** @defgroup COMPEx_ExtiLineEvent COMP Extended EXTI Line Event (STM32F301x8/STM32F302x8/STM32F303x8/STM32F334x8/STM32F318xx/STM32F328xx Product devices)
  *        Elements values convention: XXXXZYYY
  *           - XXXX : Interrupt mask in the register list where Z equal 0x0
  *           - YYY : Interrupt mask in the register list where Z equal 0x1
  *           - Z  : register index(4bits)
  *                 - 0x0: EMR/IMR/RTSR/FTSR register
  *                 - 0x1: EMR2/IMR2/RTSR2/FTSR2 register
  * @{
  */  
#define COMP_EXTI_LINE_MASK                    ((uint32_t)0xffff0fff)  /*!< Mask on possible line values */
#define COMP_EXTI_LINE_REG_MASK                ((uint32_t)0x00001000)  /*!< Mask on possible register values */
#define COMP_EXTI_LINE_COMP2_EVENT             ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to COMP2 */
#define COMP_EXTI_LINE_COMP4_EVENT             ((uint32_t)0x40000000)  /*!< External interrupt line 30 Connected to COMP4 */
#define COMP_EXTI_LINE_COMP6_EVENT             ((uint32_t)0x00001001)  /*!< External interrupt line 32 Connected to COMP6 */

/**
  * @}
  */
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F302xE) ||\
    defined(STM32F302xC)
/** @defgroup COMPEx_BlankingSrce COMP Extended Blanking Source (STM32F302xE/STM32F302xC Product devices)
  * @{
  */
/* No blanking source can be selected for all comparators */
#define COMP_BLANKINGSRCE_NONE                 ((uint32_t)0x00000000)    /*!< No blanking source */
/* Blanking source common for COMP1 and COMP2 */
#define COMP_BLANKINGSRCE_TIM1OC5              COMP_CSR_COMPxBLANKING_0  /*!< TIM1 OC5 selected as blanking source for compartor */
/* Blanking source common for COMP1 and COMP2 */
#define COMP_BLANKINGSRCE_TIM2OC3              COMP_CSR_COMPxBLANKING_1  /*!< TIM2 OC3 selected as blanking source for compartor */
/* Blanking source common for COMP1 and COMP2 */
#define COMP_BLANKINGSRCE_TIM3OC3              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM3 OC3 selected as blanking source for comparator */
/* Blanking source for COMP4 */
#define COMP_BLANKINGSRCE_TIM3OC4              COMP_CSR_COMPxBLANKING_0    /*!< TIM3 OC4 selected as blanking source for comparator */
#define COMP_BLANKINGSRCE_TIM15OC1             (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM15 OC1 selected as blanking source for comparator */
/* Blanking source for COMP6 */
#define COMP_BLANKINGSRCE_TIM2OC4              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM2 OC4 selected as blanking source for comparator */
#define COMP_BLANKINGSRCE_TIM15OC2              COMP_CSR_COMPxBLANKING_2    /*!< TIM15 OC2 selected as blanking source for comparator */

#define IS_COMP_BLANKINGSRCE(SOURCE) (((SOURCE) == COMP_BLANKINGSRCE_NONE)     || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM1OC5)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC1) || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC2))

/* STM32F302xB/STM32F302xC/STM32F302xE devices comparator instances blanking source values */
#define IS_COMP_BLANKINGSRCE_INSTANCE(INSTANCE, BLANKINGSRCE) \
   (((((INSTANCE) == COMP1) || ((INSTANCE) == COMP2))  &&     \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM1OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC3) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC3)))         \
    ||                                                        \
    (((INSTANCE) == COMP4) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC1)))        \
    ||                                                        \
    (((INSTANCE) == COMP6) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC2))))

#define COMP_CSR_COMPxBLANKING_MASK            COMP_CSR_COMPxBLANKING /*!< COMP_CSR_COMPxBLANKING mask */

/**
  * @}
  */

/** @defgroup COMPEx_ExtiLineEvent COMP Extended EXTI Line Event (STM32F302xC Product devices)
  *        Elements values convention: XXXXZYYY
  *           - XXXX : Interrupt mask in the register list where Z equal 0x0
  *           - YYY : Interrupt mask in the register list where Z equal 0x1
  *           - Z  : register index(4bits)
  *                 - 0x0: EMR/IMR/RTSR/FTSR register
  *                 - 0x1: EMR2/IMR2/RTSR2/FTSR2 register
  * @{
  */  
#define COMP_EXTI_LINE_MASK                    ((uint32_t)0xffff0fff)  /*!< Mask on possible line values */
#define COMP_EXTI_LINE_REG_MASK                ((uint32_t)0x00001000)  /*!< Mask on possible register values */
#define COMP_EXTI_LINE_COMP1_EVENT             ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2_EVENT             ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to COMP2 */
#define COMP_EXTI_LINE_COMP4_EVENT             ((uint32_t)0x40000000)  /*!< External interrupt line 30 Connected to COMP4 */
#define COMP_EXTI_LINE_COMP6_EVENT             ((uint32_t)0x00001001)  /*!< External interrupt line 32 Connected to COMP6 */

/**
  * @}
  */
#endif /* STM32F302xE || */
       /* STM32F302xC    */
   
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/** @defgroup COMPEx_BlankingSrce COMP Extended Blanking Source (STM32F303xE/STM32F398xx/STM32F303xC/STM32F358xx Product devices)
  * @{
  */
/* No blanking source can be selected for all comparators */
#define COMP_BLANKINGSRCE_NONE                 ((uint32_t)0x00000000)    /*!< No blanking source */
/* Blanking source common for COMP1, COMP2, COMP3 and COMP7 */
#define COMP_BLANKINGSRCE_TIM1OC5              COMP_CSR_COMPxBLANKING_0  /*!< TIM1 OC5 selected as blanking source for comparator */
/* Blanking source common for COMP1 and COMP2 */
#define COMP_BLANKINGSRCE_TIM2OC3              COMP_CSR_COMPxBLANKING_1  /*!< TIM2 OC5 selected as blanking source for comparator */
/* Blanking source common for COMP1, COMP2 and COMP5 */
#define COMP_BLANKINGSRCE_TIM3OC3              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM2 OC3 selected as blanking source for comparator */
/* Blanking source common for COMP3 and COMP6 */
#define COMP_BLANKINGSRCE_TIM2OC4              (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM2 OC4 selected as blanking source for comparator */
/* Blanking source common for COMP4, COMP5, COMP6 and COMP7 */
#define COMP_BLANKINGSRCE_TIM8OC5              COMP_CSR_COMPxBLANKING_1  /*!< TIM8 OC5 selected as blanking source for comparator */
/* Blanking source for COMP4 */
#define COMP_BLANKINGSRCE_TIM3OC4              COMP_CSR_COMPxBLANKING_0  /*!< TIM3 OC4 selected as blanking source for comparator */
#define COMP_BLANKINGSRCE_TIM15OC1             (COMP_CSR_COMPxBLANKING_0|COMP_CSR_COMPxBLANKING_1)    /*!< TIM15 OC1 selected as blanking source for comparator */
/* Blanking source common for COMP6 and COMP7 */
#define COMP_BLANKINGSRCE_TIM15OC2             COMP_CSR_COMPxBLANKING_2  /*!< TIM15 OC2 selected as blanking source for comparator */

#define IS_COMP_BLANKINGSRCE(SOURCE) (((SOURCE) == COMP_BLANKINGSRCE_NONE)     || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM1OC5)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC3)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM2OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM8OC5)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM3OC4)  || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC1) || \
                                      ((SOURCE) == COMP_BLANKINGSRCE_TIM15OC2))

/* STM32F303xE/STM32F398xx/STM32F303xB/STM32F303xC/STM32F358xx devices comparator instances blanking source values */
#define IS_COMP_BLANKINGSRCE_INSTANCE(INSTANCE, BLANKINGSRCE) \
   (((((INSTANCE) == COMP1) || ((INSTANCE) == COMP2))  &&     \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM1OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC3) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC3)))         \
    ||                                                        \
    (((INSTANCE) == COMP3) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM1OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC4)))         \
    ||                                                        \
    (((INSTANCE) == COMP4) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM8OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC1)))        \
    ||                                                        \
    (((INSTANCE) == COMP5) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM8OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM3OC3)))         \
    ||                                                        \
    (((INSTANCE) == COMP6) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM8OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM2OC4) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC2)))        \
    ||                                                        \
    (((INSTANCE) == COMP7) &&                                 \
     (((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE)    ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM1OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM8OC5) ||        \
      ((BLANKINGSRCE) == COMP_BLANKINGSRCE_TIM15OC2))))
     
#define COMP_CSR_COMPxBLANKING_MASK            COMP_CSR_COMPxBLANKING /*!< COMP_CSR_COMPxBLANKING mask */

/**
  * @}
  */

/** @defgroup COMPEx_ExtiLineEvent COMP Extended EXTI Line Event (STM32F303xE/STM32F398xx/STM32F303xC/STM32F358xx Product devices)
  *        Elements values convention: XXXXZYYY
  *           - XXXX : Interrupt mask in the register list where Z equal 0x0
  *           - YYY : Interrupt mask in the register list where Z equal 0x1
  *           - Z  : register index(4bits)
  *                 - 0x0: EMR/IMR/RTSR/FTSR register
  *                 - 0x1: EMR2/IMR2/RTSR2/FTSR2 register
  * @{
  */  
#define COMP_EXTI_LINE_MASK                    ((uint32_t)0xffff0fff)  /*!< Mask on possible line values */
#define COMP_EXTI_LINE_REG_MASK                ((uint32_t)0x00001000)  /*!< Mask on possible register values */
#define COMP_EXTI_LINE_COMP1_EVENT             ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2_EVENT             ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to COMP2 */
#define COMP_EXTI_LINE_COMP3_EVENT             ((uint32_t)0x20000000)  /*!< External interrupt line 29 Connected to COMP3 */
#define COMP_EXTI_LINE_COMP4_EVENT             ((uint32_t)0x40000000)  /*!< External interrupt line 30 Connected to COMP4 */
#define COMP_EXTI_LINE_COMP5_EVENT             ((uint32_t)0x80000000)  /*!< External interrupt line 31 Connected to COMP5 */
#define COMP_EXTI_LINE_COMP6_EVENT             ((uint32_t)0x00001001)  /*!< External interrupt line 32 Connected to COMP6 */
#define COMP_EXTI_LINE_COMP7_EVENT             ((uint32_t)0x00001002)  /*!< External interrupt line 33 Connected to COMP7 */

/**
  * @}
  */
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */

#if defined(STM32F373xC) ||defined(STM32F378xx)
/** @defgroup COMPEx_BlankingSrce COMP Extended Blanking Source (STM32F373xC/STM32F378xx Product devices)
  * @{
  */
/* No blanking source can be selected for all comparators */
#define COMP_BLANKINGSRCE_NONE                 ((uint32_t)0x00000000)     /*!< No blanking source */

#define IS_COMP_BLANKINGSRCE(SOURCE) ((SOURCE) == (SOURCE)) /*!< Not available: check always true */

/* STM32F373xB/STM32F373xC/STM32F378xx devices comparator instances blanking source values */
#define IS_COMP_BLANKINGSRCE_INSTANCE(INSTANCE, BLANKINGSRCE) \
   ((((INSTANCE) == COMP1) || ((INSTANCE) == COMP2))  &&     \
     ((BLANKINGSRCE) == COMP_BLANKINGSRCE_NONE))         

#define COMP_CSR_COMPxBLANKING_MASK            ((uint32_t)0x00000000) /*!< Mask empty: feature not available */

/**
  * @}
  */

/** @defgroup COMPEx_ExtiLineEvent COMP Extended EXTI Line Event (STM32F373xC/STM32F378xx Product devices)
  *        Elements values convention: XXXX0000
  *           - XXXX : Interrupt mask in the EMR/IMR/RTSR/FTSR register
  * @{   
  */  
#define COMP_EXTI_LINE_COMP1_EVENT             ((uint32_t)0x00200000)  /*!< External interrupt line 21 Connected to COMP1 */
#define COMP_EXTI_LINE_COMP2_EVENT             ((uint32_t)0x00400000)  /*!< External interrupt line 22 Connected to COMP2 */

/**
  * @}
  */
#endif /* STM32F373xC || STM32F378xx */

#if  defined(STM32F373xC) || defined(STM32F378xx)
/* CSR register reset value */ 
#define COMP_CSR_RESET_VALUE                  ((uint32_t)0x00000000)
#define COMP_CSR_RESET_PARAMETERS_MASK        ((uint32_t)0x00003FFF)
#define COMP_CSR_UPDATE_PARAMETERS_MASK       ((uint32_t)0x00003FFE)
/* CSR COMP1/COMP2 shift */ 
#define COMP_CSR_COMP1_SHIFT                  0U
#define COMP_CSR_COMP2_SHIFT                  16U
#else
/* CSR register reset value */ 
#define COMP_CSR_RESET_VALUE                  ((uint32_t)0x00000000)
#endif /* STM32F373xC || STM32F378xx */
/* CSR masks redefinition for internal use */
#define COMP_CSR_COMPxINSEL_MASK              COMP_CSR_COMPxINSEL   /*!< COMP_CSR_COMPxINSEL Mask */
#define COMP_CSR_COMPxOUTSEL_MASK             COMP_CSR_COMPxOUTSEL  /*!< COMP_CSR_COMPxOUTSEL Mask */  
#define COMP_CSR_COMPxPOL_MASK                COMP_CSR_COMPxPOL     /*!< COMP_CSR_COMPxPOL Mask   */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup USARTEx_Exported_Macros USART Extended Exported Macros
  * @{
  */
#if defined(STM32F373xC) ||defined(STM32F378xx)
/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __FLAG__: specifies the COMP Exti sources to be checked.
  *          This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval The state of __FLAG__ (SET or RESET).
  */
#define __HAL_COMP_EXTI_GET_FLAG(__FLAG__)  (EXTI->PR & (__FLAG__))
     
/**
  * @brief Clear the COMP Exti flags.
  * @param  __FLAG__: specifies the COMP Exti sources to be cleared.
  *          This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_CLEAR_FLAG(__FLAG__)   (EXTI->PR = (__FLAG__))

/**
  * @brief  Enable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_ENABLE_IT(__EXTILINE__)   (EXTI->IMR |= (__EXTILINE__))
                                             
/**
  * @brief  Disable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_DISABLE_IT(__EXTILINE__)  (EXTI->IMR &= ~(__EXTILINE__))

/**
  * @brief  Enable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_ENABLE(__EXTILINE__) (EXTI->RTSR |= (__EXTILINE__))

/**
  * @brief  Disable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_DISABLE(__EXTILINE__) (EXTI->RTSR &= ~(__EXTILINE__))

/**
  * @brief  Enable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_ENABLE(__EXTILINE__) (EXTI->FTSR |= (__EXTILINE__))

/**
  * @brief  Disable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_DISABLE(__EXTILINE__) (EXTI->FTSR &= ~(__EXTILINE__))

/**
  * @brief  Init a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @note   The common output selection is checked versus the COMP instance to set the right output configuration
  * @retval None.
  */                                         
#define COMP_OUTPUT_COMP2_TIM2IC4         ((uint32_t)0x0400)   /*!< COMP2 output connected to TIM2 Input Capture 4 */
#define COMP_OUTPUT_COMP2_TIM2OCREFCLR    ((uint32_t)0x0500)   /*!< COMP2 output connected to TIM4 OCREF Clear */
#define COMP_OUTPUT_COMP2_TIM3IC1         ((uint32_t)0x0600)   /*!< COMP2 output connected to TIM3 Input Capture 1 */
#define COMP_OUTPUT_COMP2_TIM3OCREFCLR    ((uint32_t)0x0700)   /*!< COMP2 output connected to TIM3 OCREF Clear */

#define COMP_INIT(__HANDLE__)                                                  \
        do {                                                                   \
          uint32_t regshift = COMP_CSR_COMP1_SHIFT;                            \
          uint32_t compoutput = (__HANDLE__)->Init.Output;                     \
                                                                               \
          if((__HANDLE__)->Instance == COMP2)                                  \
          {                                                                    \
            regshift = COMP_CSR_COMP2_SHIFT;                                   \
            switch((__HANDLE__)->Init.Output)                                  \
            {                                                                  \
            case COMP_OUTPUT_TIM2IC4:                                          \
              compoutput = COMP_OUTPUT_COMP2_TIM2IC4;                          \
              break;                                                           \
            case COMP_OUTPUT_TIM2OCREFCLR:                                     \
              compoutput = COMP_OUTPUT_COMP2_TIM2OCREFCLR;                     \
              break;                                                           \
            case COMP_OUTPUT_TIM3IC1:                                          \
              compoutput = COMP_OUTPUT_COMP2_TIM3IC1;                          \
              break;                                                           \
            case COMP_OUTPUT_TIM3OCREFCLR:                                     \
              compoutput = COMP_OUTPUT_COMP2_TIM3OCREFCLR;                     \
              break;                                                           \
            default:                                                           \
              break;                                                           \
            }                                                                  \
          }                                                                    \
                                                                               \
          MODIFY_REG(COMP->CSR,                                                \
                     (COMP_CSR_COMPxINSEL  | COMP_CSR_COMPxNONINSEL_MASK |     \
                     COMP_CSR_COMPxOUTSEL  | COMP_CSR_COMPxPOL           |     \
                     COMP_CSR_COMPxHYST    | COMP_CSR_COMPxMODE) << regshift,  \
                     ((__HANDLE__)->Init.InvertingInput    |                   \
                     (__HANDLE__)->Init.NonInvertingInput  |                   \
                     compoutput                            |                   \
                     (__HANDLE__)->Init.OutputPol          |                   \
                     (__HANDLE__)->Init.Hysteresis         |                   \
                     (__HANDLE__)->Init.Mode) << regshift);                    \
                                                                               \
          if((__HANDLE__)->Init.WindowMode != COMP_WINDOWMODE_DISABLED)        \
          {                                                                    \
            COMP->CSR |= COMP_CSR_WNDWEN;                                      \
          }                                                                    \
        } while(0)

/**
  * @brief  DeInit a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_DEINIT(__HANDLE__)                                                \
        do {                                                                   \
          uint32_t regshift = COMP_CSR_COMP1_SHIFT;                            \
                                                                               \
          if((__HANDLE__)->Instance == COMP2)                                  \
          {                                                                    \
            regshift = COMP_CSR_COMP2_SHIFT;                                   \
          }                                                                    \
          MODIFY_REG(COMP->CSR,                                                \
                     COMP_CSR_RESET_PARAMETERS_MASK << regshift,               \
                     COMP_CSR_RESET_VALUE << regshift);                        \
        } while(0)

/**
  * @brief  Start a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_START(__HANDLE__)                                                 \
        do {                                                                   \
          uint32_t regshift = COMP_CSR_COMP1_SHIFT;                            \
                                                                               \
          if((__HANDLE__)->Instance == COMP2)                                  \
          {                                                                    \
            regshift = COMP_CSR_COMP2_SHIFT;                                   \
          }                                                                    \
          SET_BIT(COMP->CSR, (uint32_t)COMP_CSR_COMPxEN << regshift);                    \
        } while(0)

/**
  * @brief  Stop a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_STOP(__HANDLE__)                                                  \
        do {                                                                   \
          uint32_t regshift = COMP_CSR_COMP1_SHIFT;                            \
                                                                               \
          if((__HANDLE__)->Instance == COMP2)                                  \
          {                                                                    \
            regshift = COMP_CSR_COMP2_SHIFT;                                   \
          }                                                                    \
          CLEAR_BIT(COMP->CSR, (uint32_t)COMP_CSR_COMPxEN << regshift);                  \
        } while(0)
  
/**
  * @brief  Lock a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_LOCK(__HANDLE__)                                                  \
        do {                                                                   \
          uint32_t regshift = COMP_CSR_COMP1_SHIFT;                            \
                                                                               \
          if((__HANDLE__)->Instance == COMP2)                                  \
          {                                                                    \
            regshift = COMP_CSR_COMP2_SHIFT;                                   \
          }                                                                    \
          SET_BIT(COMP->CSR, (uint32_t)COMP_CSR_COMPxLOCK << regshift);                  \
        } while(0)

#else
/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be checked.
  *          This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval The state of __FLAG__ (SET or RESET).
  */
#define __HAL_COMP_EXTI_GET_FLAG(__EXTILINE__)     \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->PR2 & (__EXTILINE__)) : (EXTI->PR & (__EXTILINE__)))
     
/**
  * @brief Clear the COMP Exti flags.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be cleared.
  *          This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_CLEAR_FLAG(__EXTILINE__)   \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->PR2 = (__EXTILINE__)) : (EXTI->PR = (__EXTILINE__)))

/**
  * @brief  Enable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_ENABLE_IT(__EXTILINE__)   \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->IMR2 |= (__EXTILINE__)) : (EXTI->IMR |= (__EXTILINE__)))
                                             
/**
  * @brief  Disable the COMP Exti Line.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */
#define __HAL_COMP_EXTI_DISABLE_IT(__EXTILINE__)   \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->IMR2 &= ~(__EXTILINE__)) : (EXTI->IMR &= ~(__EXTILINE__)))

/**
  * @brief  Enable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_ENABLE(__EXTILINE__)   \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->RTSR2 |= (__EXTILINE__)) : (EXTI->RTSR |= (__EXTILINE__)))

/**
  * @brief  Disable the Exti Line rising edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_RISING_IT_DISABLE(__EXTILINE__)   \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->RTSR2 &= ~(__EXTILINE__)) : (EXTI->RTSR &= ~(__EXTILINE__)))

/**
  * @brief  Enable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be enabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_ENABLE(__EXTILINE__)  \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->FTSR2 |= (__EXTILINE__)) : (EXTI->FTSR |= (__EXTILINE__)))

/**
  * @brief  Disable the Exti Line falling edge trigger.
  * @param  __EXTILINE__: specifies the COMP Exti sources to be disabled.
  *         This parameter can be a value of @ref COMPEx_ExtiLineEvent 
  * @retval None.
  */                                         
#define __HAL_COMP_EXTI_FALLING_IT_DISABLE(__EXTILINE__)  \
              ((((__EXTILINE__) & COMP_EXTI_LINE_REG_MASK) != RESET) ? (EXTI->FTSR2 &= ~(__EXTILINE__)) : (EXTI->FTSR &= ~(__EXTILINE__)))


/**
  * @brief  Init a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_INIT(__HANDLE__)                                                                    \
        do {                                                                                     \
          __IO uint32_t     csrreg = 0;                                                          \
                                                                                                 \
          csrreg = READ_REG((__HANDLE__)->Instance->CSR);                                        \
          MODIFY_REG(csrreg, COMP_CSR_COMPxINSEL_MASK, (__HANDLE__)->Init.InvertingInput);       \
          MODIFY_REG(csrreg, COMP_CSR_COMPxNONINSEL_MASK, (__HANDLE__)->Init.NonInvertingInput); \
          MODIFY_REG(csrreg, COMP_CSR_COMPxBLANKING_MASK, (__HANDLE__)->Init.BlankingSrce);      \
          MODIFY_REG(csrreg, COMP_CSR_COMPxOUTSEL_MASK, (__HANDLE__)->Init.Output);              \
          MODIFY_REG(csrreg, COMP_CSR_COMPxPOL_MASK, (__HANDLE__)->Init.OutputPol);              \
          MODIFY_REG(csrreg, COMP_CSR_COMPxHYST_MASK, (__HANDLE__)->Init.Hysteresis);            \
          MODIFY_REG(csrreg, COMP_CSR_COMPxMODE_MASK, (__HANDLE__)->Init.Mode);                  \
          MODIFY_REG(csrreg, COMP_CSR_COMPxWNDWEN_MASK, (__HANDLE__)->Init.WindowMode);          \
          WRITE_REG((__HANDLE__)->Instance->CSR, csrreg);                                        \
        } while(0)

/**
  * @brief  DeInit a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_DEINIT(__HANDLE__)    WRITE_REG((__HANDLE__)->Instance->CSR, COMP_CSR_RESET_VALUE)

/**
  * @brief  Start a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_START(__HANDLE__)     SET_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_COMPxEN)

/**
  * @brief  Stop a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_STOP(__HANDLE__)      CLEAR_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_COMPxEN)

/**
  * @brief  Lock a comparator instance
  * @param  __HANDLE__: specifies the COMP handle
  * @retval None.
  */                                         
#define COMP_LOCK(__HANDLE__)      SET_BIT((__HANDLE__)->Instance->CSR, COMP_CSR_COMPxLOCK)

#endif /* STM32F373xC || STM32F378xx */

#if defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx)
/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMPEx_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__) (((__INSTANCE__) == COMP2) ? COMP_EXTI_LINE_COMP2_EVENT : \
                                                ((__INSTANCE__) == COMP4) ? COMP_EXTI_LINE_COMP4_EVENT : \
                                                COMP_EXTI_LINE_COMP6_EVENT)
#endif /* STM32F301x8 || STM32F302x8 || STM32F318xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMPEx_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__) (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1_EVENT : \
                                                ((__INSTANCE__) == COMP2) ? COMP_EXTI_LINE_COMP2_EVENT : \
                                                ((__INSTANCE__) == COMP4) ? COMP_EXTI_LINE_COMP4_EVENT : \
                                                COMP_EXTI_LINE_COMP6_EVENT)
#endif /* STM32F302xE || */
       /* STM32F302xC    */
   
#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMPEx_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__) (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1_EVENT : \
                                                ((__INSTANCE__) == COMP2) ? COMP_EXTI_LINE_COMP2_EVENT : \
                                                ((__INSTANCE__) == COMP3) ? COMP_EXTI_LINE_COMP3_EVENT : \
                                                ((__INSTANCE__) == COMP4) ? COMP_EXTI_LINE_COMP4_EVENT : \
                                                ((__INSTANCE__) == COMP5) ? COMP_EXTI_LINE_COMP5_EVENT : \
                                                ((__INSTANCE__) == COMP6) ? COMP_EXTI_LINE_COMP6_EVENT : \
                                                COMP_EXTI_LINE_COMP7_EVENT)
#endif /* STM32F303xE || STM32F398xx || */
       /* STM32F303xC || STM32F358xx    */
                                                 
#if defined(STM32F373xC) ||defined(STM32F378xx)
/**
  * @brief  Get the specified EXTI line for a comparator instance
  * @param  __INSTANCE__: specifies the COMP instance.
  * @retval value of @ref COMPEx_ExtiLineEvent
  */
#define __HAL_COMP_GET_EXTI_LINE(__INSTANCE__) (((__INSTANCE__) == COMP1) ? COMP_EXTI_LINE_COMP1_EVENT : \
                                                COMP_EXTI_LINE_COMP2_EVENT)
#endif /* STM32F373xC || STM32F378xx */

/**
  * @}
  */
  
/* Exported functions --------------------------------------------------------*/

/* Initialization and de-initialization functions  ****************************/
/* IO operation functions *****************************************************/
/* Peripheral Control functions ***********************************************/
/* Peripheral State and Error functions ***************************************/

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_HAL_COMP_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
