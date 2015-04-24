/**
  ******************************************************************************
  * @file    stm32f3xx_hal_opamp.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of OPAMP HAL module.
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
#ifndef __STM32F3xx_HAL_OPAMP_H
#define __STM32F3xx_HAL_OPAMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F302xE) || defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F302xC) || defined(STM32F303xC) || defined(STM32F358xx) || \
    defined(STM32F303x8) || defined(STM32F334x8) || defined(STM32F328xx) || \
    defined(STM32F301x8) || defined(STM32F302x8) || defined(STM32F318xx) 
                  
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup OPAMP_Exported_Types OPAMP Exported Types
  * @{
  */

/** 
  * @brief  OPAMP Init structure definition  
  */
  
typedef struct
{
  uint32_t Mode;                        /*!< Specifies the OPAMP mode
                                             This parameter must be a value of @ref OPAMP_Mode 
                                             mode is either Standalone, - Follower or PGA */
                                    
  uint32_t InvertingInput;              /*!< Specifies the inverting input in Standalone & Pga modes
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInput 
                                                 InvertingInput is either VM0 or VM1
                                               - In PGA mode:          i.e when mode is OPAMP_PGA_MODE
                                                 & in Follower mode    i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter is Not Applicable */ 

  uint32_t NonInvertingInput;           /*!< Specifies the non inverting input of the opamp: 
                                             This parameter must be a value of @ref OPAMP_NonInvertingInput 
                                             NonInvertingInput is either VP0, VP1, VP2 or VP3 */                                   
  
  uint32_t TimerControlledMuxmode;      /*!< Specifies if the Timer controlled Mux mode is enabled or disabled 
                                             This parameter must be a value of @ref OPAMP_TimerControlledMuxmode */

  uint32_t InvertingInputSecondary;     /*!< Specifies the inverting input (secondary) of the opamp when 
                                             TimerControlledMuxmode is enabled 
                                             i.e. when TimerControlledMuxmode is OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE                                             
                                               - In Standalone mode:   i.e when mode is OPAMP_STANDALONE_MODE
                                                 This parameter must be a value of @ref OPAMP_InvertingInputSecondary 
                                                 InvertingInputSecondary is either VM0 or VM1
                                               - In PGA mode:          i.e when mode is OPAMP_PGA_MODE
                                                 & in Follower mode    i.e when mode is OPAMP_FOLLOWER_MODE
                                                 This parameter is Not Applicable */
  
  uint32_t NonInvertingInputSecondary;  /*!< Specifies the non inverting input (secondary) of the opamp when 
                                             TimerControlledMuxmode is enabled 
                                             i.e. when TimerControlledMuxmode is OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE
                                             This parameter must be a value of @ref OPAMP_NonInvertingInputSecondary 
                                             NonInvertingInput is either VP0, VP1, VP2 or VP3 */                                   

  uint32_t PgaConnect;                  /*!< Specifies the inverting pin in PGA mode 
                                             i.e. when mode is OPAMP_PGA_MODE 
                                             This parameter must be a value of @ref OPAMP_PgaConnect 
                                             Either: not connected, connected to VM0, connected to VM1
                                             (VM0 or VM1 are typically used for external filtering) */
                                        
  uint32_t PgaGain;                     /*!< Specifies the gain in PGA mode 
                                             i.e. when mode is OPAMP_PGA_MODE. 
                                             This parameter must be a value of @ref OPAMP_PgaGain (2, 4, 8 or 16 ) */
                                                                                     
  uint32_t UserTrimming;                /*!< Specifies the trimming mode 
                                             This parameter must be a value of @ref OPAMP_UserTrimming 
                                             UserTrimming is either factory or user trimming */
                                        
  uint32_t TrimmingValueP;              /*!< Specifies the offset trimming value (PMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
                                        
  uint32_t TrimmingValueN;              /*!< Specifies the offset trimming value (NMOS)
                                             i.e. when UserTrimming is OPAMP_TRIMMING_USER. 
                                             This parameter must be a number between Min_Data = 1 and Max_Data = 31 */
  
}OPAMP_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 

typedef enum
{
  HAL_OPAMP_STATE_RESET               = 0x00000000, /*!< OPMAP is not yet Initialized          */
  
  HAL_OPAMP_STATE_READY               = 0x00000001, /*!< OPAMP is initialized and ready for use */
  HAL_OPAMP_STATE_CALIBBUSY           = 0x00000002, /*!< OPAMP is enabled in auto calibration mode */
 
  HAL_OPAMP_STATE_BUSY                = 0x00000004, /*!< OPAMP is enabled and running in normal mode */                                                                           
  HAL_OPAMP_STATE_BUSYLOCKED          = 0x00000005, /*!< OPAMP is locked
                                                         only system reset allows reconfiguring the opamp. */
    
}HAL_OPAMP_StateTypeDef;

/** 
  * @brief OPAMP Handle Structure definition to @brief  OPAMP Handle Structure definition 
  */ 
typedef struct
{
  OPAMP_TypeDef       *Instance;                    /*!< OPAMP instance's registers base address   */
  OPAMP_InitTypeDef   Init;                         /*!< OPAMP required parameters */
  HAL_StatusTypeDef Status;                         /*!< OPAMP peripheral status   */
  HAL_LockTypeDef   Lock;                           /*!< Locking object          */
  __IO HAL_OPAMP_StateTypeDef  State;               /*!< OPAMP communication state */
  
} OPAMP_HandleTypeDef;

/** 
  * @brief OPAMP_TrimmingValueTypeDef @brief   definition 
  */ 

typedef  uint32_t OPAMP_TrimmingValueTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Constants OPAMP Exported Constants
  * @{
  */

/** @defgroup CSR_INIT CSR init register Mask 
  * @{
  */
/* Used for Init phase */
#define OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_TRIMOFFSETP \
                                          | OPAMP_CSR_USERTRIM | OPAMP_CSR_PGGAIN | OPAMP_CSR_VPSSEL \
                                          | OPAMP_CSR_VMSSEL | OPAMP_CSR_TCMEN | OPAMP_CSR_VPSEL \
                                          | OPAMP_CSR_VPSEL | OPAMP_CSR_FORCEVP)

/**
  * @}
  */         

/** @defgroup OPAMP_Mode OPAMP Mode
  * @{
  */
#define OPAMP_STANDALONE_MODE            ((uint32_t)0x00000000) /*!< standalone mode */
#define OPAMP_PGA_MODE                   OPAMP_CSR_VMSEL_1      /*!< PGA mode */
#define OPAMP_FOLLOWER_MODE              OPAMP_CSR_VMSEL        /*!< follower mode */


#define IS_OPAMP_FUNCTIONAL_NORMALMODE(INPUT) (((INPUT) == OPAMP_STANDALONE_MODE) || \
                                               ((INPUT) == OPAMP_PGA_MODE) || \
                                               ((INPUT) == OPAMP_FOLLOWER_MODE))
    
/**
  * @}
  */                                        
                                                                             
/** @defgroup OPAMP_NonInvertingInput OPAMP Non Inverting Input
  * @{
  */

#define OPAMP_NONINVERTINGINPUT_VP0         OPAMP_CSR_VPSEL                 /*!< VP0 (PA1 for OPAMP1, PA7 for OPAMP2, PB0 for OPAMP3, PB13 for OPAMP4)
                                                                                  connected to OPAMPx non inverting input */
#define OPAMP_NONINVERTINGINPUT_VP1         ((uint32_t)0x00000000)          /*!< VP1 (PA7 for OPAMP1, PD14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4)
                                                                                  connected to OPAMPx non inverting input */
#define OPAMP_NONINVERTINGINPUT_VP2         OPAMP_CSR_VPSEL_1               /*!< VP2 (PA3 for OPAMP1, PB0 for OPAMP2, PA1 for OPAMP3, PA4 for OPAMP4)
                                                                                  connected to OPAMPx non inverting input */
#define OPAMP_NONINVERTINGINPUT_VP3         OPAMP_CSR_VPSEL_0               /*!< vp3 (PA5 for OPAMP1, PB14 for OPAMP2, PA5 for OPAMP3, PB11 for OPAMP4)
                                                                                  connected to OPAMPx non inverting input */

#define IS_OPAMP_NONINVERTING_INPUT(INPUT) (((INPUT) == OPAMP_NONINVERTINGINPUT_VP0) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_VP1) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_VP2) || \
                                            ((INPUT) == OPAMP_NONINVERTINGINPUT_VP3))

/**
  * @}
  */

/** @defgroup OPAMP_InvertingInput OPAMP Inverting Input
  * @{
  */

#define IOPAMP_INVERTINGINPUT_VM0       ((uint32_t)0x00000000)            /*!< inverting input connected to VM0 */
#define IOPAMP_INVERTINGINPUT_VM1         OPAMP_CSR_VMSEL_0           /*!< inverting input connected to VM1 */

#define IS_OPAMP_INVERTING_INPUT(INPUT) (((INPUT) == IOPAMP_INVERTINGINPUT_VM0) || \
                                         ((INPUT) == IOPAMP_INVERTINGINPUT_VM1))

/**
  * @}
  */

/** @defgroup OPAMP_TimerControlledMuxmode OPAMP Timer Controlled Mux mode
  * @{
  */
 #define OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE ((uint32_t)0x00000000)    /*!< Timer controlled Mux mode disabled */
 #define OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE  OPAMP_CSR_TCMEN           /*!< Timer controlled Mux mode enabled */
 
 #define IS_OPAMP_TIMERCONTROLLED_MUXMODE(MUXMODE) (((MUXMODE) == OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE) || \
                                                    ((MUXMODE) == OPAMP_TIMERCONTROLLEDMUXMODE_ENABLE))
/**
  * @}
  */

 /** @defgroup OPAMP_NonInvertingInputSecondary OPAMP Non Inverting Input Secondary
  * @{
  */

#define OPAMP_SEC_NONINVERTINGINPUT_VP0          OPAMP_CSR_VPSSEL       /*!< VP0 (PA1 for OPAMP1, PA7 for OPAMP2, PB0 for OPAMP3, PB13 for OPAMP4)    
                                                                              connected to OPAMPx non inverting input */                              
#define OPAMP_SEC_NONINVERTINGINPUT_VP1          ((uint32_t)0x00000000) /*!< VP1 (PA7 for OPAMP1, PD14 for OPAMP2, PB13 for OPAMP3, PD11 for OPAMP4)  
                                                                             connected to OPAMPx non inverting input */                               
#define OPAMP_SEC_NONINVERTINGINPUT_VP2          OPAMP_CSR_VPSSEL_1     /*!< VP2 (PA3 for OPAMP1, PB0 for OPAMP2, PA1 for OPAMP3, PA4 for OPAMP4)     
                                                                              connected to OPAMPx non inverting input */                              
#define OPAMP_SEC_NONINVERTINGINPUT_VP3          OPAMP_CSR_VPSSEL_0     /*!< VP3 (PA5 for OPAMP1, PB14 for OPAMP2, PA5 for OPAMP3, PB11 for OPAMP4)   
                                                                              connected to OPAMPx non inverting input */                              

#define IS_OPAMP_SEC_NONINVERTINGINPUT(INPUT) (((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_VP0) || \
                                               ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_VP1) || \
                                               ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_VP2) || \
                                               ((INPUT) == OPAMP_SEC_NONINVERTINGINPUT_VP3))
                                            
/**
  * @}
  */

/** @defgroup OPAMP_InvertingInputSecondary OPAMP Inverting Input Secondary
  * @{
  */

#define OPAMP_SEC_INVERTINGINPUT_VM0          ((uint32_t)0x00000000)    /*!< VM0 (PC5 for OPAMP1 and OPAMP2, PB10 for OPAMP3 and OPAMP4)
                                                                          connected to OPAMPx inverting input */
#define OPAMP_SEC_INVERTINGINPUT_VM1          OPAMP_CSR_VMSSEL         /*!< VM1 (PA3 for OPAMP1, PA5 for OPAMP2, PB2 for OPAMP3, PD8 for OPAMP4)
                                                                         connected to OPAMPx inverting input */

#define IS_OPAMP_SEC_INVERTINGINPUT(INPUT) (((INPUT) == OPAMP_SEC_INVERTINGINPUT_VM0) || \
                                             ((INPUT) == OPAMP_SEC_INVERTINGINPUT_VM1))

/**
  * @}
  */

/** @defgroup OPAMP_PgaConnect OPAMP Pga Connect
  * @{
  */

#define OPAMP_PGACONNECT_NO               ((uint32_t)0x00000000)                    /*!< In PGA mode, the non inverting input is not connected */
#define OPAMP_PGACONNECT_VM0               OPAMP_CSR_PGGAIN_3                       /*!< In PGA mode, the non inverting input is connected to VM0 */
#define OPAMP_PGACONNECT_VM1              (OPAMP_CSR_PGGAIN_2 | OPAMP_CSR_PGGAIN_3) /*!< In PGA mode, the non inverting input is connected to VM1 */

#define IS_OPAMP_PGACONNECT(CONNECT) (((CONNECT) == OPAMP_PGACONNECT_NO)  || \
                                      ((CONNECT) == OPAMP_PGACONNECT_VM0) || \
                                      ((CONNECT) == OPAMP_PGACONNECT_VM1))
/**
  * @}
  */


/** @defgroup OPAMP_PgaGain OPAMP Pga Gain
  * @{
  */

#define OPAMP_PGA_GAIN_2                ((uint32_t)0x00000000)                        /*!< PGA gain =  2 */
#define OPAMP_PGA_GAIN_4                OPAMP_CSR_PGGAIN_0                            /*!< PGA gain =  4 */
#define OPAMP_PGA_GAIN_8                OPAMP_CSR_PGGAIN_1                            /*!< PGA gain =  8 */
#define OPAMP_PGA_GAIN_16              (OPAMP_CSR_PGGAIN_0 | OPAMP_CSR_PGGAIN_1)      /*!< PGA gain = 16 */

#define IS_OPAMP_PGA_GAIN(GAIN) (((GAIN) == OPAMP_PGA_GAIN_2) || \
                                 ((GAIN) == OPAMP_PGA_GAIN_4) || \
                                 ((GAIN) == OPAMP_PGA_GAIN_8) || \
                                 ((GAIN) == OPAMP_PGA_GAIN_16))
/**
  * @}
  */

/** @defgroup OPAMP_UserTrimming OPAMP User Trimming
  * @{
  */

#define OPAMP_TRIMMING_FACTORY        ((uint32_t)0x00000000)                          /*!< Factory trimming */
#define OPAMP_TRIMMING_USER           OPAMP_CSR_USERTRIM                              /*!< User trimming */

#define IS_OPAMP_TRIMMING(TRIMMING) (((TRIMMING) == OPAMP_TRIMMING_FACTORY) || \
                                     ((TRIMMING) == OPAMP_TRIMMING_USER))

/** @defgroup OPAMP_FactoryTrimming OPAMP Factory Trimming
  * @{
  */

#define OPAMP_FACTORYTRIMMING_DUMMY    ((uint32_t)0xFFFFFFFF)                          /*!< Dummy trimming value */

#define OPAMP_FACTORYTRIMMING_N        ((uint32_t)0x00000000)                          /*!< Offset trimming N */
#define OPAMP_FACTORYTRIMMING_P        ((uint32_t)0x00000001)                          /*!< Offset trimming P */

#define IS_OPAMP_FACTORYTRIMMING(TRIMMING) (((TRIMMING) == OPAMP_FACTORYTRIMMING_N) || \
                                             ((TRIMMING) == OPAMP_FACTORYTRIMMING_P))

/**
  * @}
  */ 


/** @defgroup OPAMP_TrimmingValue OPAMP Trimming Value
  * @{
  */

#define IS_OPAMP_TRIMMINGVALUE(TRIMMINGVALUE) ((TRIMMINGVALUE) <= 0x1F)


/**
  * @}
  */ 


/** @defgroup OPAMP_Input OPAMP Input
  * @{
  */

#define OPAMP_INPUT_INVERTING                 ((uint32_t) 24) /*!< Inverting input */
#define OPAMP_INPUT_NONINVERTING              ((uint32_t) 19) /*!< Non inverting input */

#define IS_OPAMP_INPUT(INPUT) (((INPUT) == OPAMP_INPUT_INVERTING) || \
                               ((INPUT) == OPAMP_INPUT_NONINVERTING))
/**
  * @}
  */


/** @defgroup OPAMP_VREF OPAMP VREF
  * @{
  */

#define OPAMP_VREF_3VDDA                    ((uint32_t)0x00000000)  /*!< OPMAP Vref = 3.3% VDDA */
#define OPAMP_VREF_10VDDA                    OPAMP_CSR_CALSEL_0     /*!< OPMAP Vref = 10% VDDA  */
#define OPAMP_VREF_50VDDA                    OPAMP_CSR_CALSEL_1     /*!< OPMAP Vref = 50% VDDA  */
#define OPAMP_VREF_90VDDA                    OPAMP_CSR_CALSEL       /*!< OPMAP Vref = 90% VDDA  */

#define IS_OPAMP_VREF(VREF) (((VREF) == OPAMP_VREF_3VDDA)  || \
                             ((VREF) == OPAMP_VREF_10VDDA) || \
                             ((VREF) == OPAMP_VREF_50VDDA) || \
                             ((VREF) == OPAMP_VREF_90VDDA))

/**
  * @}
  */ 

 /** @defgroup OPAMP_Vref2ADCforCalib OPAMP Vref2ADCforCalib
  */
 
#define OPAMP_VREF_NOTCONNECTEDTO_ADC          ((uint32_t)0x00000000) /*!< VREF not connected to ADC */
#define OPAMP_VREF_CONNECTEDTO_ADC             ((uint32_t)0x00000001) /*!< VREF not connected to ADC */
    
#define IS_OPAMP_ALLOPAMPVREF_CONNECT(CONNECT) (((CONNECT) == OPAMP_VREF_NOTCONNECTEDTO_ADC) || \
                                                ((CONNECT) == OPAMP_VREF_CONNECTEDTO_ADC))
    

 /**
  * @}
  */ 
    
 /**
  * @}
  */ 

/* Exported macros -----------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Macros OPAMP Exported Macros
  * @{
  */

/** @brief Reset OPAMP handle state
  * @param  __HANDLE__: OPAMP handle.
  * @retval None
  */
#define __HAL_OPAMP_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_OPAMP_STATE_RESET)

/**
  * @}
  */ 

/* Include OPAMP HAL Extended module */
#include "stm32f3xx_hal_opamp_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_DeInit (OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp);
void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp);
/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 Input and Output operation functions 
  * @{
  */

/* I/O operation functions  *****************************************************/
HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp);
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp); 

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions 
  * @{
  */

/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp); 

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group4 Peripheral State functions 
  * @{
  */

/* Peripheral State functions  **************************************************/
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp);
OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset);

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

#endif /* STM32F302xE || STM32F303xE || STM32F398xx || */
       /* STM32F302xC || STM32F303xC || STM32F358xx || */
       /* STM32F303x8 || STM32F334x8 || STM32F328xx || */
       /* STM32F301x8 || STM32F302x8 || STM32F318xx    */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_HAL_OPAMP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
