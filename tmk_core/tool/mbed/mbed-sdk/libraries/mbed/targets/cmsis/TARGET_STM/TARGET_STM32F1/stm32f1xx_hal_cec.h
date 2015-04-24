/**
  ******************************************************************************
  * @file    stm32f1xx_hal_cec.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of CEC HAL module.
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
#ifndef __STM32F1xx_HAL_CEC_H
#define __STM32F1xx_HAL_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F100xB) || defined(STM32F100xE)
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
  */ 
  
/** @addtogroup CEC_Private_Constants
  * @{
  */
#define IS_CEC_BIT_TIMING_ERROR_MODE(MODE) (((MODE) == CEC_BIT_TIMING_ERROR_MODE_STANDARD) || \
                                        ((MODE) == CEC_BIT_TIMING_ERROR_MODE_ERRORFREE))
#define IS_CEC_BIT_PERIOD_ERROR_MODE(MODE) (((MODE) == CEC_BIT_PERIOD_ERROR_MODE_STANDARD) || \
                                        ((MODE) == CEC_BIT_PERIOD_ERROR_MODE_FLEXIBLE))

/** @brief Check CEC device Own Address Register (OAR) setting.
  * @param  __ADDRESS__: CEC own address.               
  * @retval Test result (TRUE or FALSE).
  */
#define IS_CEC_OAR_ADDRESS(__ADDRESS__) ((__ADDRESS__) <= 0xF)  

/** @brief Check CEC initiator or destination logical address setting.
  *        Initiator and destination addresses are coded over 4 bits. 
  * @param  __ADDRESS__: CEC initiator or logical address.               
  * @retval Test result (TRUE or FALSE).
  */
#define IS_CEC_ADDRESS(__ADDRESS__) ((__ADDRESS__) <= 0xF)    

/** @brief Check CEC message size.
  *       The message size is the payload size: without counting the header, 
  *       it varies from 0 byte (ping operation, one header only, no payload) to 
  *       15 bytes (1 opcode and up to 14 operands following the header). 
  * @param  __SIZE__: CEC message size.               
  * @retval Test result (TRUE or FALSE).
  */
#define IS_CEC_MSGSIZE(__SIZE__) ((__SIZE__) <= 0xF)   

/**
 * @}
 */ 
 
/* Exported types ------------------------------------------------------------*/ 
/** @defgroup CEC_Exported_Types CEC Exported Types
  * @{
  */ 
/** 
  * @brief CEC Init Structure definition  
  */ 
typedef struct
{  
  uint32_t TimingErrorFree; /*!< Configures the CEC Bit Timing Error Mode. 
                                 This parameter can be a value of @ref CEC_BitTimingErrorMode */
  uint32_t PeriodErrorFree; /*!< Configures the CEC Bit Period Error Mode. 
                                 This parameter can be a value of @ref CEC_BitPeriodErrorMode */
  uint8_t  InitiatorAddress; /*!< Initiator address (source logical address, sent in each header) 
                                 This parameter can be a value <= 0xF */
}CEC_InitTypeDef;

/** 
  * @brief HAL CEC State structures definition  
  */ 
typedef enum
{
  HAL_CEC_STATE_RESET             = 0x00,    /*!< Peripheral Reset state                              */
  HAL_CEC_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use            */
  HAL_CEC_STATE_BUSY              = 0x02,    /*!< An internal process is ongoing                      */
  HAL_CEC_STATE_BUSY_TX           = 0x03,    /*!< Data Transmission process is ongoing                */
  HAL_CEC_STATE_BUSY_RX           = 0x04,    /*!< Data Reception process is ongoing                   */
  HAL_CEC_STATE_BUSY_TX_RX        = 0x05,    /*!< Data Transmission and Reception process is ongoing  */
  HAL_CEC_STATE_TIMEOUT           = 0x06,    /*!< Timeout state                                       */
  HAL_CEC_STATE_ERROR             = 0x07     /*!< State Error                                         */
}HAL_CEC_StateTypeDef;

/** 
  * @brief  HAL Error structures definition  
  */ 
typedef enum
{
  HAL_CEC_ERROR_NONE  = (uint32_t) 0x0, /*!< no error */
  HAL_CEC_ERROR_BTE   = CEC_ESR_BTE,    /*!< Bit Timing Error */
  HAL_CEC_ERROR_BPE   = CEC_ESR_BPE,    /*!< Bit Period Error */
  HAL_CEC_ERROR_RBTFE = CEC_ESR_RBTFE,  /*!< Rx Block Transfer Finished Error */
  HAL_CEC_ERROR_SBE   = CEC_ESR_SBE,    /*!< Start Bit Error */
  HAL_CEC_ERROR_ACKE  = CEC_ESR_ACKE,   /*!< Block Acknowledge Error */
  HAL_CEC_ERROR_LINE  = CEC_ESR_LINE,   /*!< Line Error */
  HAL_CEC_ERROR_TBTFE = CEC_ESR_TBTFE,  /*!< Tx Block Transfer Finished Error */
}HAL_CEC_ErrorTypeDef;

/** 
  * @brief  CEC handle Structure definition  
  */  
typedef struct
{
  CEC_TypeDef             *Instance;      /*!< CEC registers base address */
  
  CEC_InitTypeDef         Init;           /*!< CEC communication parameters */
  
  uint8_t                 *pTxBuffPtr;    /*!< Pointer to CEC Tx transfer Buffer */
  
  uint16_t                TxXferCount;    /*!< CEC Tx Transfer Counter */
  
  uint8_t                 *pRxBuffPtr;    /*!< Pointer to CEC Rx transfer Buffer */
  
  uint16_t                RxXferSize;     /*!< CEC Rx Transfer size, 0: header received only */
  
  uint32_t                ErrorCode;      /*!< For errors handling purposes, copy of ESR register in case error is reported */
  
  HAL_LockTypeDef         Lock;           /*!< Locking object */
  
  HAL_CEC_StateTypeDef    State;          /*!< CEC communication state */
    
}CEC_HandleTypeDef;

/**
 * @}
 */ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup CEC_Exported_Constants CEC Exported Constants
  * @{
  */
  
/** @defgroup CEC_BitTimingErrorMode Bit Timing Error Mode
  * @{
  */ 
#define CEC_BIT_TIMING_ERROR_MODE_STANDARD  ((uint32_t)0x00) /*!< Bit timing error Standard Mode */
#define CEC_BIT_TIMING_ERROR_MODE_ERRORFREE CEC_CFGR_BTEM    /*!< Bit timing error Free Mode */
/**
  * @}
  */

/** @defgroup CEC_BitPeriodErrorMode Bit Period Error Mode
  * @{
  */ 
#define CEC_BIT_PERIOD_ERROR_MODE_STANDARD ((uint32_t)0x00) /*!< Bit period error Standard Mode */
#define CEC_BIT_PERIOD_ERROR_MODE_FLEXIBLE CEC_CFGR_BPEM    /*!< Bit period error Flexible Mode */
/**
  * @}
  */ 
  
/** @defgroup CEC_Initiator_Position Initiator logical address position in message header     
  * @{
  */
#define CEC_INITIATOR_LSB_POS           ((uint32_t) 4)
/**
  * @}
  */
/** @defgroup CEC_Interrupts_Definitions  Interrupts definition
  * @{
  */
#define CEC_IT_IE CEC_CFGR_IE
/**
  * @}
  */

/** @defgroup CEC_Flags_Definitions  Flags definition
  * @{
  */
#define CEC_FLAG_TSOM  CEC_CSR_TSOM
#define CEC_FLAG_TEOM  CEC_CSR_TEOM
#define CEC_FLAG_TERR  CEC_CSR_TERR
#define CEC_FLAG_TBTRF CEC_CSR_TBTRF
#define CEC_FLAG_RSOM  CEC_CSR_RSOM
#define CEC_FLAG_REOM  CEC_CSR_REOM
#define CEC_FLAG_RERR  CEC_CSR_RERR
#define CEC_FLAG_RBTF  CEC_CSR_RBTF
/**
  * @}
  */
  
/**
  * @}
  */  
  
/* Exported macros -----------------------------------------------------------*/
/** @defgroup CEC_Exported_Macros CEC Exported Macros
  * @{
  */

/** @brief  Reset CEC handle state
  * @param  __HANDLE__: CEC handle.
  * @retval None
  */
#define __HAL_CEC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_CEC_STATE_RESET)

/** @brief  Checks whether or not the specified CEC interrupt flag is set.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: specifies the interrupt to check.
  *     @arg CEC_FLAG_TERR: Tx Error
  *     @arg CEC_FLAG_TBTF: Tx Block Transfer Finished
  *     @arg CEC_FLAG_RERR: Rx Error
  *     @arg CEC_FLAG_RBTF: Rx Block Transfer Finished
  * @retval ITStatus
  */
#define __HAL_CEC_GET_FLAG(__HANDLE__, __INTERRUPT__) READ_BIT((__HANDLE__)->Instance->CSR,(__INTERRUPT__)) 

/** @brief  Clears the CEC's pending flags.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __FLAG__: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg CEC_CSR_TERR: Tx Error
  *     @arg CEC_CSR_TBTF: Tx Block Transfer Finished
  *     @arg CEC_CSR_RERR: Rx Error
  *     @arg CEC_CSR_RBTF: Rx Block Transfer Finished
  * @retval none  
  */
#define __HAL_CEC_CLEAR_FLAG(__HANDLE__, __FLAG__)                                                                  \
                          do {                                                                                      \
                            uint32_t tmp = 0x0;                                                                     \
                            tmp = (__HANDLE__)->Instance->CSR & 0x2;                                                \
                            (__HANDLE__)->Instance->CSR &= (uint32_t)(((~(uint32_t)(__FLAG__)) & 0xFFFFFFFC) | tmp);\
                          } while(0)
                      
/** @brief  Enables the specified CEC interrupt.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: The CEC interrupt to enable.
  *          This parameter can be:
  *            @arg CEC_IT_IE         : Interrupt Enable                 
  * @retval none
  */
#define __HAL_CEC_ENABLE_IT(__HANDLE__, __INTERRUPT__) SET_BIT((__HANDLE__)->Instance->CFGR, (__INTERRUPT__))

/** @brief  Disables the specified CEC interrupt.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: The CEC interrupt to enable.
  *          This parameter can be:
  *            @arg CEC_IT_IE         : Interrupt Enable                         
  * @retval none
  */   
#define __HAL_CEC_DISABLE_IT(__HANDLE__, __INTERRUPT__) CLEAR_BIT((__HANDLE__)->Instance->CFGR, (__INTERRUPT__))

/** @brief  Checks whether or not the specified CEC interrupt is enabled.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: The CEC interrupt to enable.
  *          This parameter can be:
  *            @arg CEC_IT_IE         : Interrupt Enable                        
  * @retval FlagStatus  
  */
#define __HAL_CEC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) READ_BIT((__HANDLE__)->Instance->CFGR, (__INTERRUPT__))

/** @brief  Enables the CEC device
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_ENABLE(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CFGR, CEC_CFGR_PE)

/** @brief  Disables the CEC device
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_DISABLE(__HANDLE__) CLEAR_BIT((__HANDLE__)->Instance->CFGR, CEC_CFGR_PE)

/** @brief  Set Transmission Start flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_FIRST_BYTE_TX_SET(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CSR, CEC_CSR_TSOM)

/** @brief  Set Transmission End flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none  
  */
#define __HAL_CEC_LAST_BYTE_TX_SET(__HANDLE__) SET_BIT((__HANDLE__)->Instance->CSR, CEC_CSR_TEOM)

/** @brief  Get Transmission Start flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval FlagStatus 
  */
#define __HAL_CEC_GET_TRANSMISSION_START_FLAG(__HANDLE__) READ_BIT((__HANDLE__)->Instance->CSR, CEC_CSR_TSOM)

/** @brief  Get Transmission End flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval FlagStatus 
  */
#define __HAL_CEC_GET_TRANSMISSION_END_FLAG(__HANDLE__) READ_BIT((__HANDLE__)->Instance->CSR, CEC_CSR_TEOM)

/** @brief  Clear OAR register
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_CLEAR_OAR(__HANDLE__)   CLEAR_BIT((__HANDLE__)->Instance->OAR, CEC_OAR_OA)

/** @brief  Set OAR register
  * @param  __HANDLE__: specifies the CEC Handle. 
  * @param  __ADDRESS__: Own Address value.
  * @retval none 
  */
#define __HAL_CEC_SET_OAR(__HANDLE__,__ADDRESS__) MODIFY_REG((__HANDLE__)->Instance->OAR, CEC_OAR_OA, (__ADDRESS__));

/**
  * @}
  */                       

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CEC_Exported_Functions CEC Exported Functions
  * @{
  */
  
/** @addtogroup CEC_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions 
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_CEC_Init(CEC_HandleTypeDef *hcec);
HAL_StatusTypeDef HAL_CEC_DeInit(CEC_HandleTypeDef *hcec);
void HAL_CEC_MspInit(CEC_HandleTypeDef *hcec);
void HAL_CEC_MspDeInit(CEC_HandleTypeDef *hcec);
/**
  * @}
  */

/** @addtogroup CEC_Exported_Functions_Group2 Input and Output operation functions 
  *  @brief CEC Transmit/Receive functions 
  * @{
  */
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_CEC_Transmit(CEC_HandleTypeDef *hcec, uint8_t DestinationAddress, uint8_t *pData, uint32_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_CEC_Receive(CEC_HandleTypeDef *hcec, uint8_t *pData, uint32_t Timeout);
HAL_StatusTypeDef HAL_CEC_Transmit_IT(CEC_HandleTypeDef *hcec, uint8_t DestinationAddress, uint8_t *pData, uint32_t Size);
HAL_StatusTypeDef HAL_CEC_Receive_IT(CEC_HandleTypeDef *hcec, uint8_t *pData);
uint32_t HAL_CEC_GetReceivedFrameSize(CEC_HandleTypeDef *hcec);
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec);
void HAL_CEC_TxCpltCallback(CEC_HandleTypeDef *hcec);
void HAL_CEC_RxCpltCallback(CEC_HandleTypeDef *hcec);
void HAL_CEC_ErrorCallback(CEC_HandleTypeDef *hcec);
/**
  * @}
  */

/** @defgroup CEC_Exported_Functions_Group3 Peripheral Control functions 
  *  @brief   CEC control functions 
  * @{
  */
/* Peripheral State and Error functions ***************************************/
HAL_CEC_StateTypeDef HAL_CEC_GetState(CEC_HandleTypeDef *hcec);
uint32_t HAL_CEC_GetError(CEC_HandleTypeDef *hcec);
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
  
#endif /* defined(STM32F100xB) || defined(STM32F100xE) */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_CEC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
