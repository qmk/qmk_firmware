/**
  ******************************************************************************
  * @file    stm32f30x_comp.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the COMP firmware 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F30x_COMP_H
#define __STM32F30x_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup COMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  COMP Init structure definition  
  */
  
typedef struct
{

  uint32_t COMP_InvertingInput;     /*!< Selects the inverting input of the comparator.
                                          This parameter can be a value of @ref COMP_InvertingInput */

  uint32_t COMP_NonInvertingInput;  /*!< Selects the non inverting input of the comparator.
                                         This parameter can be a value of @ref COMP_NonInvertingInput */

  uint32_t COMP_Output;             /*!< Selects the output redirection of the comparator.
                                          This parameter can be a value of @ref COMP_Output */

  uint32_t COMP_BlankingSrce;      /*!< Selects the output blanking source of the comparator.
                                          This parameter can be a value of @ref COMP_BlankingSrce */

  uint32_t COMP_OutputPol;         /*!< Selects the output polarity of the comparator.
                                          This parameter can be a value of @ref COMP_OutputPoloarity */

  uint32_t COMP_Hysteresis;        /*!< Selects the hysteresis voltage of the comparator.
                                          This parameter can be a value of @ref COMP_Hysteresis */

  uint32_t COMP_Mode;              /*!< Selects the operating mode of the comparator
                                         and allows to adjust the speed/consumption.
                                         This parameter can be a value of @ref COMP_Mode */
}COMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
   
/** @defgroup COMP_Exported_Constants
  * @{
  */ 

/** @defgroup COMP_Selection
  * @{
  */

#define COMP_Selection_COMP1                    ((uint32_t)0x00000000) /*!< COMP1 Selection */
#define COMP_Selection_COMP2                    ((uint32_t)0x00000004) /*!< COMP2 Selection */
#define COMP_Selection_COMP3                    ((uint32_t)0x00000008) /*!< COMP3 Selection */
#define COMP_Selection_COMP4                    ((uint32_t)0x0000000C) /*!< COMP4 Selection */
#define COMP_Selection_COMP5                    ((uint32_t)0x00000010) /*!< COMP5 Selection */
#define COMP_Selection_COMP6                    ((uint32_t)0x00000014) /*!< COMP6 Selection */
#define COMP_Selection_COMP7                    ((uint32_t)0x00000018) /*!< COMP7 Selection */

#define IS_COMP_ALL_PERIPH(PERIPH) (((PERIPH) == COMP_Selection_COMP1) || \
                                    ((PERIPH) == COMP_Selection_COMP2) || \
                                    ((PERIPH) == COMP_Selection_COMP3) || \
                                    ((PERIPH) == COMP_Selection_COMP4) || \
                                    ((PERIPH) == COMP_Selection_COMP5) || \
                                    ((PERIPH) == COMP_Selection_COMP6) || \
                                    ((PERIPH) == COMP_Selection_COMP7))
 
/**
  * @}
  */ 

/** @defgroup COMP_InvertingInput
  * @{
  */

#define COMP_InvertingInput_1_4VREFINT          ((uint32_t)0x00000000) /*!< 1/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_1_2VREFINT          COMP_CSR_COMPxINSEL_0  /*!< 1/2 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_3_4VREFINT          COMP_CSR_COMPxINSEL_1  /*!< 3/4 VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_VREFINT             ((uint32_t)0x00000030) /*!< VREFINT connected to comparator inverting input */
#define COMP_InvertingInput_DAC1OUT1            COMP_CSR_COMPxINSEL_2  /*!< DAC1_OUT1 (PA4) connected to comparator inverting input */
#define COMP_InvertingInput_DAC1OUT2            ((uint32_t)0x00000050) /*!< DAC1_OUT2 (PA5) connected to comparator inverting input */

#define COMP_InvertingInput_IO1                 ((uint32_t)0x00000060) /*!< I/O1 (PA0 for COMP1, PA2 for COMP2, PD15 for COMP3, 
                                                                            PE8 for COMP4, PD13 for COMP5, PD10 for COMP6,
                                                                            PC0 for COMP7) connected to comparator inverting input */

#define COMP_InvertingInput_IO2                 COMP_CSR_COMPxINSEL    /*!< I/O2 (PB12 for COMP3, PB2 for COMP4, PB10 for COMP5,
                                                                            PB15 for COMP6) connected to comparator inverting input */

#define COMP_InvertingInput_DAC2OUT1            COMP_CSR_COMPxINSEL_3  /*!< DAC2_OUT1 (PA6) connected to comparator inverting input */

#define IS_COMP_INVERTING_INPUT(INPUT) (((INPUT) == COMP_InvertingInput_1_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_1_2VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_3_4VREFINT) || \
                                        ((INPUT) == COMP_InvertingInput_VREFINT)    || \
                                        ((INPUT) == COMP_InvertingInput_DAC1OUT1)   || \
                                        ((INPUT) == COMP_InvertingInput_DAC1OUT2)   || \
                                        ((INPUT) == COMP_InvertingInput_IO1)        || \
                                        ((INPUT) == COMP_InvertingInput_IO2)        || \
                                        ((INPUT) == COMP_InvertingInput_DAC2OUT1))
/**
  * @}
  */ 

/** @defgroup COMP_NonInvertingInput
  * @{
  */

#define COMP_NonInvertingInput_IO1                 ((uint32_t)0x00000000) /*!< I/O1 (PA1 for COMP1, PA7 for COMP2, PB14 for COMP3, 
                                                                               PB0 for COMP4, PD12 for COMP5, PD11 for COMP6,
                                                                               PA0 for COMP7) connected to comparator non inverting input */

#define COMP_NonInvertingInput_IO2                 COMP_CSR_COMPxNONINSEL /*!< I/O2 (PA3 for COMP2, PD14 for COMP3, PE7 for COMP4, PB13 for COMP5,
                                                                               PB11 for COMP6, PC1 for COMP7) connected to comparator non inverting input */

#define IS_COMP_NONINVERTING_INPUT(INPUT) (((INPUT) == COMP_NonInvertingInput_IO1) || \
                                           ((INPUT) == COMP_NonInvertingInput_IO2))
/**
  * @}
  */ 

/** @defgroup COMP_Output
  * @{
  */

#define COMP_Output_None                  ((uint32_t)0x00000000)   /*!< COMP output isn't connected to other peripherals */

/* Output Redirection common for all comparators COMP1...COMP7 */
#define COMP_Output_TIM1BKIN              COMP_CSR_COMPxOUTSEL_0   /*!< COMP output connected to TIM1 Break Input (BKIN) */
#define COMP_Output_TIM1BKIN2             ((uint32_t)0x00000800)   /*!< COMP output connected to TIM1 Break Input 2 (BKIN2) */
#define COMP_Output_TIM8BKIN              ((uint32_t)0x00000C00)   /*!< COMP output connected to TIM8 Break Input (BKIN) */
#define COMP_Output_TIM8BKIN2             ((uint32_t)0x00001000)   /*!< COMP output connected to TIM8 Break Input 2 (BKIN2) */
#define COMP_Output_TIM1BKIN2_TIM8BKIN2   ((uint32_t)0x00001400)   /*!< COMP output connected to TIM1 Break Input 2 and TIM8 Break Input 2 */

/* Output Redirection common for COMP1 and COMP2 */
#define COMP_Output_TIM1OCREFCLR          ((uint32_t)0x00001800)   /*!< COMP output connected to TIM1 OCREF Clear */
#define COMP_Output_TIM1IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM1 Input Capture 1 */
#define COMP_Output_TIM2IC4               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 4 */
#define COMP_Output_TIM2OCREFCLR          ((uint32_t)0x00002400)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM3IC1               ((uint32_t)0x00002800)   /*!< COMP output connected to TIM3 Input Capture 1 */
#define COMP_Output_TIM3OCREFCLR          ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM3 OCREF Clear */

/* Output Redirection specific to COMP2 */
#define COMP_Output_HRTIM1_FLT6           ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT6 */
#define COMP_Output_HRTIM1_EE1_2          ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE1_2*/
#define COMP_Output_HRTIM1_EE6_2          ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE6_2 */

/* Output Redirection specific to COMP3 */
#define COMP_Output_TIM4IC1               ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM4 Input Capture 1 */
#define COMP_Output_TIM3IC2               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM3 Input Capture 2 */
#define COMP_Output_TIM15IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 Input Capture 1 */
#define COMP_Output_TIM15BKIN             ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM15 Break Input (BKIN) */

/* Output Redirection specific to COMP4 */
#define COMP_Output_TIM3IC3               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM3 Input Capture 3 */
#define COMP_Output_TIM8OCREFCLR          ((uint32_t)0x00001C00)   /*!< COMP output connected to TIM8 OCREF Clear */
#define COMP_Output_TIM15IC2              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM15 Input Capture 2 */
#define COMP_Output_TIM4IC2               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 2 */
#define COMP_Output_TIM15OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM15 OCREF Clear */

#define COMP_Output_HRTIM1_FLT7           ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT7 */
#define COMP_Output_HRTIM1_EE2_2          ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE2_2*/
#define COMP_Output_HRTIM1_EE7_2          ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE7_2 */

/* Output Redirection specific to COMP5 */
#define COMP_Output_TIM2IC1               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 1 */
#define COMP_Output_TIM17IC1              ((uint32_t)0x00002000)   /*!< COMP output connected to TIM17 Input Capture 1 */
#define COMP_Output_TIM4IC3               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM4 Input Capture 3 */
#define COMP_Output_TIM16BKIN             ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

/* Output Redirection specific to COMP6 */
#define COMP_Output_TIM2IC2               ((uint32_t)0x00001800)   /*!< COMP output connected to TIM2 Input Capture 2 */
#define COMP_Output_COMP6TIM2OCREFCLR     ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 OCREF Clear */
#define COMP_Output_TIM16OCREFCLR         ((uint32_t)0x00002400)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM16IC1              ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 Input Capture 1 */
#define COMP_Output_TIM4IC4               ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM4 Input Capture 4 */

#define COMP_Output_HRTIM1_FLT8           ((uint32_t)0x00003000)   /*!< COMP output connected to HRTIM1 FLT8 */
#define COMP_Output_HRTIM1_EE3_2          ((uint32_t)0x00003400)   /*!< COMP output connected to HRTIM1 EE3_2*/
#define COMP_Output_HRTIM1_EE8_2          ((uint32_t)0x00003800)   /*!< COMP output connected to HRTIM1 EE8_2 */

/* Output Redirection specific to COMP7 */
#define COMP_Output_TIM2IC3               ((uint32_t)0x00002000)   /*!< COMP output connected to TIM2 Input Capture 3 */
#define COMP_Output_TIM1IC2               ((uint32_t)0x00002400)   /*!< COMP output connected to TIM1 Input Capture 2 */
#define COMP_Output_TIM17OCREFCLR         ((uint32_t)0x00002800)   /*!< COMP output connected to TIM16 OCREF Clear */
#define COMP_Output_TIM17BKIN             ((uint32_t)0x00002C00)   /*!< COMP output connected to TIM16 Break Input (BKIN) */

#define IS_COMP_OUTPUT(OUTPUT) (((OUTPUT) == COMP_Output_None)                || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN)            || \
                                ((OUTPUT) == COMP_Output_TIM1IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM1OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM2IC4)             || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_COMP6TIM2OCREFCLR)   || \
                                ((OUTPUT) == COMP_Output_TIM3IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM3OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM8BKIN)            || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN2)           || \
                                ((OUTPUT) == COMP_Output_TIM8BKIN2)           || \
                                ((OUTPUT) == COMP_Output_TIM2OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM1BKIN2_TIM8BKIN2) || \
                                ((OUTPUT) == COMP_Output_TIM3IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM15BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM8OCREFCLR)        || \
                                ((OUTPUT) == COMP_Output_TIM3IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM15IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM2IC1)             || \
                                ((OUTPUT) == COMP_Output_TIM4IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM16BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM17IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM2IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM16IC1)            || \
                                ((OUTPUT) == COMP_Output_TIM4IC4)             || \
                                ((OUTPUT) == COMP_Output_TIM16OCREFCLR)       || \
                                ((OUTPUT) == COMP_Output_TIM2IC3)             || \
                                ((OUTPUT) == COMP_Output_TIM1IC2)             || \
                                ((OUTPUT) == COMP_Output_TIM17BKIN)           || \
                                ((OUTPUT) == COMP_Output_TIM17OCREFCLR)       || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT6)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE1_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE6_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT7)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE2_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE7_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_FLT8)         || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE3_2)        || \
                                ((OUTPUT) == COMP_Output_HRTIM1_EE8_2))
                                
/**
  * @}
  */ 

/** @defgroup COMP_BlankingSrce
  * @{
  */

/* No blanking source can be selected for all comparators */
#define COMP_BlankingSrce_None                   ((uint32_t)0x00000000)    /*!< No blanking source */

/* Blanking source common for COMP1, COMP2, COMP3 and COMP7 */
#define COMP_BlankingSrce_TIM1OC5                COMP_CSR_COMPxBLANKING_0  /*!< TIM1 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1 and COMP2 */
#define COMP_BlankingSrce_TIM2OC3                COMP_CSR_COMPxBLANKING_1  /*!< TIM2 OC5 selected as blanking source for compartor */

/* Blanking source common for COMP1, COMP2 and COMP5 */
#define COMP_BlankingSrce_TIM3OC3                ((uint32_t)0x000C0000)    /*!< TIM2 OC3 selected as blanking source for compartor */

/* Blanking source common for COMP3 and COMP6 */
#define COMP_BlankingSrce_TIM2OC4                ((uint32_t)0x000C0000)  /*!< TIM2 OC4 selected as blanking source for compartor */

/* Blanking source common for COMP4, COMP5, COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM8OC5                COMP_CSR_COMPxBLANKING_1  /*!< TIM8 OC5 selected as blanking source for compartor */

/* Blanking source for COMP4 */
#define COMP_BlankingSrce_TIM3OC4                COMP_CSR_COMPxBLANKING_0  /*!< TIM3 OC4 selected as blanking source for compartor */
#define COMP_BlankingSrce_TIM15OC1               ((uint32_t)0x000C0000)    /*!< TIM15 OC1 selected as blanking source for compartor */

/* Blanking source common for COMP6 and COMP7 */
#define COMP_BlankingSrce_TIM15OC2               COMP_CSR_COMPxBLANKING_2    /*!< TIM15 OC2 selected as blanking source for compartor */

#define IS_COMP_BLANKING_SOURCE(SOURCE) (((SOURCE) == COMP_BlankingSrce_None)     || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM1OC5)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC3)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC3)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM2OC4)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM8OC5)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM3OC4)  || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC1) || \
                                         ((SOURCE) == COMP_BlankingSrce_TIM15OC2))
/**
  * @}
  */ 

/** @defgroup COMP_OutputPoloarity
  * @{
  */
#define COMP_OutputPol_NonInverted          ((uint32_t)0x00000000)  /*!< COMP output on GPIO isn't inverted */
#define COMP_OutputPol_Inverted             COMP_CSR_COMPxPOL       /*!< COMP output on GPIO is inverted */

#define IS_COMP_OUTPUT_POL(POL) (((POL) == COMP_OutputPol_NonInverted)  || \
                                 ((POL) == COMP_OutputPol_Inverted))

/**
  * @}
  */ 

/** @defgroup COMP_Hysteresis
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the hysteresis level */
#define COMP_Hysteresis_No                         0x00000000           /*!< No hysteresis */
#define COMP_Hysteresis_Low                        COMP_CSR_COMPxHYST_0 /*!< Hysteresis level low */
#define COMP_Hysteresis_Medium                     COMP_CSR_COMPxHYST_1 /*!< Hysteresis level medium */
#define COMP_Hysteresis_High                       COMP_CSR_COMPxHYST   /*!< Hysteresis level high */

#define IS_COMP_HYSTERESIS(HYSTERESIS)    (((HYSTERESIS) == COMP_Hysteresis_No)     || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Low)    || \
                                           ((HYSTERESIS) == COMP_Hysteresis_Medium) || \
                                           ((HYSTERESIS) == COMP_Hysteresis_High))
/**
  * @}
  */

/** @defgroup COMP_Mode
  * @{
  */
/* Please refer to the electrical characteristics in the device datasheet for
   the power consumption values */
#define COMP_Mode_HighSpeed                     0x00000000            /*!< High Speed */
#define COMP_Mode_MediumSpeed                   COMP_CSR_COMPxMODE_0  /*!< Medium Speed */
#define COMP_Mode_LowPower                      COMP_CSR_COMPxMODE_1  /*!< Low power mode */
#define COMP_Mode_UltraLowPower                 COMP_CSR_COMPxMODE    /*!< Ultra-low power mode */

#define IS_COMP_MODE(MODE)    (((MODE) == COMP_Mode_UltraLowPower) || \
                               ((MODE) == COMP_Mode_LowPower)      || \
                               ((MODE) == COMP_Mode_MediumSpeed)   || \
                               ((MODE) == COMP_Mode_HighSpeed))
/**
  * @}
  */

/** @defgroup COMP_OutputLevel
  * @{
  */ 
/* When output polarity is not inverted, comparator output is high when
   the non-inverting input is at a higher voltage than the inverting input */
#define COMP_OutputLevel_High                   COMP_CSR_COMPxOUT
/* When output polarity is not inverted, comparator output is low when
   the non-inverting input is at a lower voltage than the inverting input*/
#define COMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */ 

/** @defgroup COMP_WindowMode
  * @{
  */
#define IS_COMP_WINDOW(WINDOW)  (((WINDOW) == COMP_Selection_COMP2) || \
                                 ((WINDOW) == COMP_Selection_COMP4) || \
                                 ((WINDOW) == COMP_Selection_COMP6))
/**
  * @}
  */

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the COMP configuration to the default reset state ****/
void COMP_DeInit(uint32_t COMP_Selection);

/* Initialization and Configuration functions *********************************/
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct);
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct);
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState);
void COMP_SwitchCmd(uint32_t COMP_Selection, FunctionalState NewState);
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection);

/* Window mode control function ***********************************************/
void COMP_WindowCmd(uint32_t COMP_Selection, FunctionalState NewState);

/* COMP configuration locking function ****************************************/
void COMP_LockConfig(uint32_t COMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_COMP_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
