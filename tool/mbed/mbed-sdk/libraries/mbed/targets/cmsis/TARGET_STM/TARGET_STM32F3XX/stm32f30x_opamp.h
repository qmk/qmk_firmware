/**
  ******************************************************************************
  * @file    stm32f30x_opamp.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the operational
  *          amplifiers (OPAMP) firmware library.         
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
#ifndef __STM32F30x_OPAMP_H
#define __STM32F30x_OPAMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  OPAMP Init structure definition  
  */
  
typedef struct
{

  uint32_t OPAMP_InvertingInput;     /*!< Selects the inverting input of the operational amplifier.
                                          This parameter can be a value of @ref OPAMP_InvertingInput */

  uint32_t OPAMP_NonInvertingInput;  /*!< Selects the non inverting input of the operational amplifier.
                                         This parameter can be a value of @ref OPAMP_NonInvertingInput */

}OPAMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Constants
  * @{
  */ 

/** @defgroup OPAMP_Selection
  * @{
  */

#define OPAMP_Selection_OPAMP1                    ((uint32_t)0x00000000) /*!< OPAMP1 Selection */
#define OPAMP_Selection_OPAMP2                    ((uint32_t)0x00000004) /*!< OPAMP2 Selection */
#define OPAMP_Selection_OPAMP3                    ((uint32_t)0x00000008) /*!< OPAMP3 Selection */
#define OPAMP_Selection_OPAMP4                    ((uint32_t)0x0000000C) /*!< OPAMP4 Selection */

#define IS_OPAMP_ALL_PERIPH(PERIPH) (((PERIPH) == OPAMP_Selection_OPAMP1) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP2) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP3) || \
                                     ((PERIPH) == OPAMP_Selection_OPAMP4))
 
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput
  * @{
  */

#define OPAMP_InvertingInput_IO1          ((uint32_t)0x00000000) /*!< IO1 (PC5 for OPAMP1 and OPAMP2, PB10 for OPAMP3 and OPAMP4)
                                                                     connected to OPAMPx inverting input */
#define OPAMP_InvertingInput_IO2          OPAMP_CSR_VMSEL_0      /*!< IO2 (PA3 for OPAMP1, PA5 for OPAMP2, PB2 for OPAMP3, PD8 for OPAMP4)
                                                                      connected to OPAMPx inverting input */
#define OPAMP_InvertingInput_PGA          OPAMP_CSR_VMSEL_1      /*!< Resistor feedback output connected to OPAMPx inverting input (PGA mode) */
#define OPAMP_InvertingInput_Vout         OPAMP_CSR_VMSEL        /*!< Vout connected to OPAMPx inverting input (follower mode) */

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == OPAMP_InvertingInput_IO1) || \
                                         ((INPUT) == OPAMP_InvertingInput_IO2) || \
                                         ((INPUT) == OPAMP_InvertingInput_PGA) || \
                                         ((INPUT) == OPAMP_InvertingInput_Vout))
/**
  * @}
  */

/** @defgroup OPAMP_NonInvertingInput
  * @{
  */

#define OPAMP_NonInvertingInput_IO1          ((uint32_t)0x00000000) /*!< IO1 (PA7 for OPAMP1, PD14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4)
                                                                        connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO2          OPAMP_CSR_VPSEL_0      /*!< IO2 (PA5 for OPAMP1, PB14 for OPAMP2, PA5 for OPAMP3, PB11 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO3          OPAMP_CSR_VPSEL_1      /*!< IO3 (PA3 for OPAMP1, PB0 for OPAMP2, PA1 for OPAMP3, PA4 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */
#define OPAMP_NonInvertingInput_IO4          OPAMP_CSR_VPSEL        /*!< IO4 (PA1 for OPAMP1, PA7 for OPAMP2, PB0 for OPAMP3, PB13 for OPAMP4)
                                                                         connected to OPAMPx non inverting input */

#define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NonInvertingInput_IO1) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO2) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO3) || \
                                            ((INPUT) == OPAMP_NonInvertingInput_IO4))
/**
  * @}
  */

/** @defgroup OPAMP_PGAGain_Config
  * @{
  */

#define OPAMP_OPAMP_PGAGain_2                ((uint32_t)0x00000000)
#define OPAMP_OPAMP_PGAGain_4                OPAMP_CSR_PGGAIN_0
#define OPAMP_OPAMP_PGAGain_8                OPAMP_CSR_PGGAIN_1
#define OPAMP_OPAMP_PGAGain_16               ((uint32_t)0x0000C000)

#define IS_OPAMP_PGAGAIN(GAIN) (((GAIN) == OPAMP_OPAMP_PGAGain_2) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_4) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_8) || \
                                ((GAIN) == OPAMP_OPAMP_PGAGain_16))
/**
  * @}
  */

/** @defgroup OPAMP_PGAConnect_Config
  * @{
  */

#define OPAMP_PGAConnect_No                ((uint32_t)0x00000000)
#define OPAMP_PGAConnect_IO1               OPAMP_CSR_PGGAIN_3
#define OPAMP_PGAConnect_IO2               ((uint32_t)0x00030000)

#define IS_OPAMP_PGACONNECT(CONNECT) (((CONNECT) == OPAMP_PGAConnect_No)  || \
                                      ((CONNECT) == OPAMP_PGAConnect_IO1) || \
                                      ((CONNECT) == OPAMP_PGAConnect_IO2))
/**
  * @}
  */

/** @defgroup OPAMP_SecondaryInvertingInput
  * @{
  */

#define IS_OPAMP_SECONDARY_INVINPUT(INVINPUT) (((INVINPUT) == OPAMP_InvertingInput_IO1) || \
                                               ((INVINPUT) == OPAMP_InvertingInput_IO2))
/**
  * @}
  */

/** @defgroup OPAMP_Input
  * @{
  */

#define OPAMP_Input_Inverting                 ((uint32_t)0x00000018) /*!< Inverting input */
#define OPAMP_Input_NonInverting              ((uint32_t)0x00000013) /*!< Non inverting input */

#define IS_OPAMP_INPUT(INPUT) (((INPUT) == OPAMP_Input_Inverting) || \
                               ((INPUT) == OPAMP_Input_NonInverting))

/**
  * @}
  */ 

/** @defgroup OPAMP_Vref
  * @{
  */

#define OPAMP_Vref_3VDDA                    ((uint32_t)0x00000000) /*!< OPMAP Vref = 3.3% VDDA */
#define OPAMP_Vref_10VDDA                    OPAMP_CSR_CALSEL_0     /*!< OPMAP Vref = 10% VDDA  */
#define OPAMP_Vref_50VDDA                    OPAMP_CSR_CALSEL_1     /*!< OPMAP Vref = 50% VDDA  */
#define OPAMP_Vref_90VDDA                    OPAMP_CSR_CALSEL       /*!< OPMAP Vref = 90% VDDA  */

#define IS_OPAMP_VREF(VREF) (((VREF) == OPAMP_Vref_3VDDA)  || \
                             ((VREF) == OPAMP_Vref_10VDDA) || \
                             ((VREF) == OPAMP_Vref_50VDDA) || \
                             ((VREF) == OPAMP_Vref_90VDDA))

/**
  * @}
  */

/** @defgroup OPAMP_Trimming
  */

#define OPAMP_Trimming_Factory        ((uint32_t)0x00000000) /*!< Factory trimming */
#define OPAMP_Trimming_User           OPAMP_CSR_USERTRIM     /*!< User trimming */

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_Trimming_Factory) || \
                                     ((TRIMMING) == OPAMP_Trimming_User))

/**
  * @}
  */ 

/** @defgroup OPAMP_TrimValue
  * @{
  */

#define IS_OPAMP_TRIMMINGVALUE(VALUE) ((VALUE) <= 0x0000001F) /*!< Trimming value */

/**
  * @}
  */

/** @defgroup OPAMP_OutputLevel
  * @{
  */

#define OPAMP_OutputLevel_High                   OPAMP_CSR_OUTCAL
#define OPAMP_OutputLevel_Low                    ((uint32_t)0x00000000)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the OPAMP configuration to the default reset state ***/
void OPAMP_DeInit(uint32_t OPAMP_Selection);

/* Initialization and Configuration functions *********************************/
void OPAMP_Init(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_StructInit(OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_PGAConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_PGAGain, uint32_t OPAMP_PGAConnect);
void OPAMP_VrefConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Vref);
void OPAMP_VrefConnectADCCmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_TimerControlledMuxConfig(uint32_t OPAMP_Selection, OPAMP_InitTypeDef* OPAMP_InitStruct);
void OPAMP_TimerControlledMuxCmd(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState);
uint32_t OPAMP_GetOutputLevel(uint32_t OPAMP_Selection);

/* Calibration functions ******************************************************/
void OPAMP_VrefConnectNonInvertingInput(uint32_t OPAMP_Selection, FunctionalState NewState);
void OPAMP_OffsetTrimModeSelect(uint32_t OPAMP_Selection, uint32_t OPAMP_Trimming);
void OPAMP_OffsetTrimConfig(uint32_t OPAMP_Selection, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
void OPAMP_StartCalibration(uint32_t OPAMP_Selection, FunctionalState NewState);

/* OPAMP configuration locking function ***************************************/
void OPAMP_LockConfig(uint32_t OPAMP_Selection);

#ifdef __cplusplus
}
#endif

#endif /*__STM32F30x_OPAMP_H */

/**
  * @}
  */ 

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
