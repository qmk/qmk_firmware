/**
  ******************************************************************************
  * @file    stm32f3xx_hal_cec.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
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
#ifndef __STM32F3xx_HAL_CEC_H
#define __STM32F3xx_HAL_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

#if defined(STM32F373xC) || defined(STM32F378xx)
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
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
  uint32_t SignalFreeTime;               /*!< Set SFT field, specifies the Signal Free Time.
                                              It can be one of @ref CEC_Signal_Free_Time 
                                              and belongs to the set {0,...,7} where  
                                              0x0 is the default configuration 
                                              else means 0.5 + (SignalFreeTime - 1) nominal data bit periods */

  uint32_t Tolerance;                    /*!< Set RXTOL bit, specifies the tolerance accepted on the received waveforms,
                                              it can be a value of @ref CEC_Tolerance : it is either CEC_STANDARD_TOLERANCE 
                                              or CEC_EXTENDED_TOLERANCE */

  uint32_t BRERxStop;                    /*!< Set BRESTP bit @ref CEC_BRERxStop : specifies whether or not a Bit Rising Error stops the reception. 
                                              CEC_NO_RX_STOP_ON_BRE: reception is not stopped. 
                                              CEC_RX_STOP_ON_BRE:    reception is stopped. */

  uint32_t BREErrorBitGen;               /*!< Set BREGEN bit @ref CEC_BREErrorBitGen : specifies whether or not an Error-Bit is generated on the
                                              CEC line upon Bit Rising Error detection.
                                              CEC_BRE_ERRORBIT_NO_GENERATION: no error-bit generation.
                                              CEC_BRE_ERRORBIT_GENERATION:    error-bit generation if BRESTP is set. */
                                              
  uint32_t LBPEErrorBitGen;              /*!< Set LBPEGEN bit @ref CEC_LBPEErrorBitGen : specifies whether or not an Error-Bit is generated on the
                                              CEC line upon Long Bit Period Error detection.
                                              CEC_LBPE_ERRORBIT_NO_GENERATION:  no error-bit generation. 
                                              CEC_LBPE_ERRORBIT_GENERATION:     error-bit generation. */  
                                              
  uint32_t BroadcastMsgNoErrorBitGen;    /*!< Set BRDNOGEN bit @ref CEC_BroadCastMsgErrorBitGen : allows to avoid an Error-Bit generation on the CEC line
                                              upon an error detected on a broadcast message. 
                                              
                                              It supersedes BREGEN and LBPEGEN bits for a broadcast message error handling. It can take two values:
                                              
                                              1) CEC_BROADCASTERROR_ERRORBIT_GENERATION.
                                                 a) BRE detection: error-bit generation on the CEC line if BRESTP=CEC_RX_STOP_ON_BRE 
                                                    and BREGEN=CEC_BRE_ERRORBIT_NO_GENERATION.
                                                 b) LBPE detection: error-bit generation on the CEC line 
                                                    if LBPGEN=CEC_LBPE_ERRORBIT_NO_GENERATION.
                                                    
                                              2) CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION.
                                                 no error-bit generation in case neither a) nor b) are satisfied. Additionally,
                                                 there is no error-bit generation in case of Short Bit Period Error detection in 
                                                 a broadcast message while LSTN bit is set. */
 
  uint32_t SignalFreeTimeOption;         /*!< Set SFTOP bit @ref CEC_SFT_Option : specifies when SFT timer starts.
                                              CEC_SFT_START_ON_TXSOM SFT:    timer starts when TXSOM is set by software.
                                              CEC_SFT_START_ON_TX_RX_END:  SFT timer starts automatically at the end of message transmission/reception. */

  uint32_t OwnAddress;                   /*!< Set OAR field, specifies CEC device address within a 15-bit long field */
  
  uint32_t ListenMode;                   /*!< Set LSTN bit @ref CEC_Listening_Mode : specifies device listening mode. It can take two values:
  
                                              CEC_REDUCED_LISTENING_MODE: CEC peripheral receives only message addressed to its 
                                                own address (OAR). Messages addressed to different destination are ignored. 
                                                Broadcast messages are always received.
                                                
                                              CEC_FULL_LISTENING_MODE: CEC peripheral receives messages addressed to its own 
                                                address (OAR) with positive acknowledge. Messages addressed to different destination 
                                                are received, but without interfering with the CEC bus: no acknowledge sent.  */

  uint8_t  InitiatorAddress;             /* Initiator address (source logical address, sent in each header) */

}CEC_InitTypeDef;

/** 
  * @brief HAL CEC State structures definition  
  */ 
typedef enum
{
  HAL_CEC_STATE_RESET             = 0x00,    /*!< Peripheral Reset state                              */
  HAL_CEC_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use            */
  HAL_CEC_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing                      */
  HAL_CEC_STATE_BUSY_TX           = 0x03,    /*!< Data Transmission process is ongoing                */
  HAL_CEC_STATE_BUSY_RX           = 0x04,    /*!< Data Reception process is ongoing                   */
  HAL_CEC_STATE_STANDBY_RX        = 0x05,    /*!< IP ready to receive, doesn't prevent IP to transmit */
  HAL_CEC_STATE_TIMEOUT           = 0x06,    /*!< Timeout state                                       */
  HAL_CEC_STATE_ERROR             = 0x07     /*!< State Error                                         */
}HAL_CEC_StateTypeDef;

/** 
  * @brief  HAL Error structures definition  
  */ 
typedef enum
{
  HAL_CEC_ERROR_NONE   = (uint32_t) 0x0,         /*!< no error                      */
  HAL_CEC_ERROR_RXOVR  = CEC_ISR_RXOVR,          /*!< CEC Rx-Overrun                */
  HAL_CEC_ERROR_BRE    = CEC_ISR_BRE,            /*!< CEC Rx Bit Rising Error       */
  HAL_CEC_ERROR_SBPE   = CEC_ISR_SBPE,           /*!< CEC Rx Short Bit period Error */
  HAL_CEC_ERROR_LBPE   = CEC_ISR_LBPE,           /*!< CEC Rx Long Bit period Error  */
  HAL_CEC_ERROR_RXACKE = CEC_ISR_RXACKE,         /*!< CEC Rx Missing Acknowledge    */
  HAL_CEC_ERROR_ARBLST = CEC_ISR_ARBLST,         /*!< CEC Arbitration Lost          */
  HAL_CEC_ERROR_TXUDR  = CEC_ISR_TXUDR,          /*!< CEC Tx-Buffer Underrun        */
  HAL_CEC_ERROR_TXERR  = CEC_ISR_TXERR,          /*!< CEC Tx-Error                  */
  HAL_CEC_ERROR_TXACKE = CEC_ISR_TXACKE          /*!< CEC Tx Missing Acknowledge    */
}
HAL_CEC_ErrorTypeDef;

/** 
  * @brief  CEC handle Structure definition  
  */  
typedef struct
{
  CEC_TypeDef             *Instance;      /* CEC registers base address */
  
  CEC_InitTypeDef         Init;           /* CEC communication parameters */
  
  uint8_t                 *pTxBuffPtr;    /* Pointer to CEC Tx transfer Buffer */
  
  uint16_t                TxXferCount;    /* CEC Tx Transfer Counter */
  
  uint8_t                 *pRxBuffPtr;    /* Pointer to CEC Rx transfer Buffer */
  
  uint16_t                RxXferSize;     /* CEC Rx Transfer size, 0: header received only */
  
  uint32_t                ErrorCode;      /* For errors handling purposes, copy of ISR register 
                                            in case error is reported */
  
  HAL_LockTypeDef         Lock;           /* Locking object */
  
  HAL_CEC_StateTypeDef    State;          /* CEC communication state */
    
}CEC_HandleTypeDef;

/**
 * @}
 */ 

/* Exported constants --------------------------------------------------------*/
/** @defgroup CEC_Exported_Constants CEC Exported Constants
  * @{
  */
     
/** @defgroup CEC_Signal_Free_Time  Signal Free Time setting parameter
  * @{
  */
#define CEC_DEFAULT_SFT                    ((uint32_t)0x00000000)
#define CEC_0_5_BITPERIOD_SFT              ((uint32_t)0x00000001)
#define CEC_1_5_BITPERIOD_SFT              ((uint32_t)0x00000002)
#define CEC_2_5_BITPERIOD_SFT              ((uint32_t)0x00000003)
#define CEC_3_5_BITPERIOD_SFT              ((uint32_t)0x00000004)
#define CEC_4_5_BITPERIOD_SFT              ((uint32_t)0x00000005)
#define CEC_5_5_BITPERIOD_SFT              ((uint32_t)0x00000006)
#define CEC_6_5_BITPERIOD_SFT              ((uint32_t)0x00000007)
#define IS_CEC_SIGNALFREETIME(SFT)         ((SFT) <= CEC_CFGR_SFT)
/**
  * @}
  */

/** @defgroup CEC_Tolerance   Receiver Tolerance
  * @{
  */
#define CEC_STANDARD_TOLERANCE             ((uint32_t)0x00000000)
#define CEC_EXTENDED_TOLERANCE             ((uint32_t)CEC_CFGR_RXTOL)
#define IS_CEC_TOLERANCE(RXTOL)            (((RXTOL) == CEC_STANDARD_TOLERANCE) || \
                                            ((RXTOL) == CEC_EXTENDED_TOLERANCE))
/**
  * @}
  */ 

/** @defgroup CEC_BRERxStop   Reception Stop on Error
  * @{
  */
#define CEC_NO_RX_STOP_ON_BRE             ((uint32_t)0x00000000)
#define CEC_RX_STOP_ON_BRE                ((uint32_t)CEC_CFGR_BRESTP)
#define IS_CEC_BRERXSTOP(BRERXSTOP)       (((BRERXSTOP) == CEC_NO_RX_STOP_ON_BRE) || \
                                           ((BRERXSTOP) == CEC_RX_STOP_ON_BRE))
/**
  * @}
  */            
             
/** @defgroup CEC_BREErrorBitGen   Error Bit Generation if Bit Rise Error reported
  * @{
  */ 
#define CEC_BRE_ERRORBIT_NO_GENERATION     ((uint32_t)0x00000000)
#define CEC_BRE_ERRORBIT_GENERATION        ((uint32_t)CEC_CFGR_BREGEN)
#define IS_CEC_BREERRORBITGEN(ERRORBITGEN) (((ERRORBITGEN) == CEC_BRE_ERRORBIT_NO_GENERATION) || \
                                            ((ERRORBITGEN) == CEC_BRE_ERRORBIT_GENERATION))
/**
  * @}
  */ 
                        
/** @defgroup CEC_LBPEErrorBitGen   Error Bit Generation if Long Bit Period Error reported
  * @{
  */ 
#define CEC_LBPE_ERRORBIT_NO_GENERATION     ((uint32_t)0x00000000)
#define CEC_LBPE_ERRORBIT_GENERATION        ((uint32_t)CEC_CFGR_LBPEGEN)
#define IS_CEC_LBPEERRORBITGEN(ERRORBITGEN) (((ERRORBITGEN) == CEC_LBPE_ERRORBIT_NO_GENERATION) || \
                                             ((ERRORBITGEN) == CEC_LBPE_ERRORBIT_GENERATION))
/**
  * @}
  */    

/** @defgroup CEC_BroadCastMsgErrorBitGen   Error Bit Generation on Broadcast message
  * @{
  */ 
#define CEC_BROADCASTERROR_ERRORBIT_GENERATION     ((uint32_t)0x00000000)
#define CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION  ((uint32_t)CEC_CFGR_BRDNOGEN)
#define IS_CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION(ERRORBITGEN) (((ERRORBITGEN) == CEC_BROADCASTERROR_ERRORBIT_GENERATION) || \
                                                                   ((ERRORBITGEN) == CEC_BROADCASTERROR_NO_ERRORBIT_GENERATION))
/**
  * @}
  */
  
/** @defgroup CEC_SFT_Option         Signal Free Time start option
  * @{
  */ 
#define CEC_SFT_START_ON_TXSOM           ((uint32_t)0x00000000)
#define CEC_SFT_START_ON_TX_RX_END       ((uint32_t)CEC_CFGR_SFTOPT)
#define IS_CEC_SFTOP(SFTOP)              (((SFTOP) == CEC_SFT_START_ON_TXSOM) || \
                                          ((SFTOP) == CEC_SFT_START_ON_TX_RX_END))
/**
  * @}
  */
  
/** @defgroup CEC_Listening_Mode        Listening mode option
  * @{
  */ 
#define CEC_REDUCED_LISTENING_MODE          ((uint32_t)0x00000000)
#define CEC_FULL_LISTENING_MODE             ((uint32_t)CEC_CFGR_LSTN)
#define IS_CEC_LISTENING_MODE(MODE)         (((MODE) == CEC_REDUCED_LISTENING_MODE) || \
                                             ((MODE) == CEC_FULL_LISTENING_MODE))
/**
  * @}
  */

/** @defgroup CEC_ALL_ERROR all RX or TX errors flags in CEC ISR register 
  * @{
  */
#define CEC_ISR_ALL_ERROR              ((uint32_t)CEC_ISR_RXOVR|CEC_ISR_BRE|CEC_ISR_SBPE|CEC_ISR_LBPE|CEC_ISR_RXACKE|\
                                                  CEC_ISR_ARBLST|CEC_ISR_TXUDR|CEC_ISR_TXERR|CEC_ISR_TXACKE)
/**
  * @}
  */

/** @defgroup CEC_IER_ALL_RX all RX errors interrupts enabling flag 
  * @{
  */
#define CEC_IER_RX_ALL_ERR              ((uint32_t)CEC_IER_RXACKEIE|CEC_IER_LBPEIE|CEC_IER_SBPEIE|CEC_IER_BREIE|CEC_IER_RXOVRIE)
/**
  * @}
  */
  
/** @defgroup CEC_IER_ALL_TX all TX errors interrupts enabling flag 
  * @{
  */
#define CEC_IER_TX_ALL_ERR              ((uint32_t)CEC_IER_TXACKEIE|CEC_IER_TXERRIE|CEC_IER_TXUDRIE|CEC_IER_ARBLSTIE)
/**
  * @}
  */  
  
/** @defgroup CEC_OAR_Position    Device Own Address position in CEC CFGR register     
  * @{
  */
#define CEC_CFGR_OAR_LSB_POS            ((uint32_t) 16)
/**
  * @}
  */
  
/** @defgroup CEC_Initiator_Position    Initiator logical address position in message header     
  * @{
  */
#define CEC_INITIATOR_LSB_POS           ((uint32_t) 4)
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
  *        This parameter can be one of the following values:
  *            @arg CEC_ISR_RXBR      : Rx-Byte Received
  *            @arg CEC_ISR_RXEND     : End of Reception
  *            @arg CEC_ISR_RXOVR     : Rx Overrun
  *            @arg CEC_ISR_BRE       : Rx Bit Rising Error
  *            @arg CEC_ISR_SBPE      : Rx Short Bit Period Error
  *            @arg CEC_ISR_LBPE      : Rx Long Bit Period Error
  *            @arg CEC_ISR_RXACKE    : Rx Missing Acknowledge
  *            @arg CEC_ISR_ARBLST    : Arbitration lost
  *            @arg CEC_ISR_TXBR      : Tx-Byte Request
  *            @arg CEC_ISR_TXEND     : End of Transmission   
  *            @arg CEC_ISR_TXUDR     : Tx-buffer Underrun                  
  *            @arg CEC_ISR_TXERR     : Tx Error
  *            @arg CEC_ISR_TXACKE    : Tx Missing Acknowledge
  * @retval ITStatus
  */
#define __HAL_CEC_GET_IT(__HANDLE__, __INTERRUPT__)        ((__HANDLE__)->Instance->ISR & (__INTERRUPT__)) 

/** @brief  Clears the interrupt or status flag when raised (write at 1)
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __FLAG__: specifies the interrupt/status flag to clear.
  *        This parameter can be one of the following values:
  *            @arg CEC_ISR_RXBR      : Rx-Byte Received
  *            @arg CEC_ISR_RXEND     : End of Reception
  *            @arg CEC_ISR_RXOVR     : Rx Overrun
  *            @arg CEC_ISR_BRE       : Rx Bit Rising Error
  *            @arg CEC_ISR_SBPE      : Rx Short Bit Period Error
  *            @arg CEC_ISR_LBPE      : Rx Long Bit Period Error
  *            @arg CEC_ISR_RXACKE    : Rx Missing Acknowledge
  *            @arg CEC_ISR_ARBLST    : Arbitration lost
  *            @arg CEC_ISR_TXBR      : Tx-Byte Request
  *            @arg CEC_ISR_TXEND     : End of Transmission   
  *            @arg CEC_ISR_TXUDR     : Tx-buffer Underrun                  
  *            @arg CEC_ISR_TXERR     : Tx Error
  *            @arg CEC_ISR_TXACKE    : Tx Missing Acknowledge
  * @retval none  
  */
#define __HAL_CEC_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->ISR = (__FLAG__)) 

/** @brief  Enables the specified CEC interrupt.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: specifies the CEC interrupt to enable.
  *          This parameter can be one of the following values:
  *            @arg CEC_IER_RXBRIE         : Rx-Byte Received IT Enable         
  *            @arg CEC_IER_RXENDIE        : End Of Reception IT Enable         
  *            @arg CEC_IER_RXOVRIE        : Rx-Overrun IT Enable               
  *            @arg CEC_IER_BREIE          : Rx Bit Rising Error IT Enable      
  *            @arg CEC_IER_SBPEIE         : Rx Short Bit period Error IT Enable
  *            @arg CEC_IER_LBPEIE         : Rx Long Bit period Error IT Enable 
  *            @arg CEC_IER_RXACKEIE       : Rx Missing Acknowledge IT Enable   
  *            @arg CEC_IER_ARBLSTIE       : Arbitration Lost IT Enable         
  *            @arg CEC_IER_TXBRIE         : Tx Byte Request IT Enable         
  *            @arg CEC_IER_TXENDIE        : End of Transmission IT Enable      
  *            @arg CEC_IER_TXUDRIE        : Tx-Buffer Underrun IT Enable       
  *            @arg CEC_IER_TXERRIE        : Tx-Error IT Enable                 
  *            @arg CEC_IER_TXACKEIE       : Tx Missing Acknowledge IT Enable                   
  * @retval none
  */
#define __HAL_CEC_ENABLE_IT(__HANDLE__, __INTERRUPT__)     ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))  

/** @brief  Disables the specified CEC interrupt.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: specifies the CEC interrupt to disable.
  *          This parameter can be one of the following values:
  *            @arg CEC_IER_RXBRIE         : Rx-Byte Received IT Enable         
  *            @arg CEC_IER_RXENDIE        : End Of Reception IT Enable         
  *            @arg CEC_IER_RXOVRIE        : Rx-Overrun IT Enable               
  *            @arg CEC_IER_BREIE          : Rx Bit Rising Error IT Enable      
  *            @arg CEC_IER_SBPEIE         : Rx Short Bit period Error IT Enable
  *            @arg CEC_IER_LBPEIE         : Rx Long Bit period Error IT Enable 
  *            @arg CEC_IER_RXACKEIE       : Rx Missing Acknowledge IT Enable   
  *            @arg CEC_IER_ARBLSTIE       : Arbitration Lost IT Enable         
  *            @arg CEC_IER_TXBRIE         : Tx Byte Request IT Enable         
  *            @arg CEC_IER_TXENDIE        : End of Transmission IT Enable      
  *            @arg CEC_IER_TXUDRIE        : Tx-Buffer Underrun IT Enable       
  *            @arg CEC_IER_TXERRIE        : Tx-Error IT Enable                 
  *            @arg CEC_IER_TXACKEIE       : Tx Missing Acknowledge IT Enable                   
  * @retval none
  */   
#define __HAL_CEC_DISABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->IER &= (~(__INTERRUPT__)))  

/** @brief  Checks whether or not the specified CEC interrupt is enabled.
  * @param  __HANDLE__: specifies the CEC Handle.
  * @param  __INTERRUPT__: specifies the CEC interrupt to check.
  *          This parameter can be one of the following values:
  *            @arg CEC_IER_RXBRIE         : Rx-Byte Received IT Enable         
  *            @arg CEC_IER_RXENDIE        : End Of Reception IT Enable         
  *            @arg CEC_IER_RXOVRIE        : Rx-Overrun IT Enable               
  *            @arg CEC_IER_BREIE          : Rx Bit Rising Error IT Enable      
  *            @arg CEC_IER_SBPEIE         : Rx Short Bit period Error IT Enable
  *            @arg CEC_IER_LBPEIE         : Rx Long Bit period Error IT Enable 
  *            @arg CEC_IER_RXACKEIE       : Rx Missing Acknowledge IT Enable   
  *            @arg CEC_IER_ARBLSTIE       : Arbitration Lost IT Enable         
  *            @arg CEC_IER_TXBRIE         : Tx Byte Request IT Enable         
  *            @arg CEC_IER_TXENDIE        : End of Transmission IT Enable      
  *            @arg CEC_IER_TXUDRIE        : Tx-Buffer Underrun IT Enable       
  *            @arg CEC_IER_TXERRIE        : Tx-Error IT Enable                 
  *            @arg CEC_IER_TXACKEIE       : Tx Missing Acknowledge IT Enable                   
  * @retval FlagStatus  
  */
#define __HAL_CEC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER & (__INTERRUPT__))

/** @brief  Enables the CEC device
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_ENABLE(__HANDLE__)                   ((__HANDLE__)->Instance->CR |=  CEC_CR_CECEN)

/** @brief  Disables the CEC device
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_DISABLE(__HANDLE__)                  ((__HANDLE__)->Instance->CR &=  ~CEC_CR_CECEN)

/** @brief  Set Transmission Start flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_FIRST_BYTE_TX_SET(__HANDLE__)        ((__HANDLE__)->Instance->CR |=  CEC_CR_TXSOM)

/** @brief  Set Transmission End flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  * If the CEC message consists of only one byte, TXEOM must be set before of TXSOM.  
  */
#define __HAL_CEC_LAST_BYTE_TX_SET(__HANDLE__)         ((__HANDLE__)->Instance->CR |=  CEC_CR_TXEOM)

/** @brief  Get Transmission Start flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval FlagStatus 
  */
#define __HAL_CEC_GET_TRANSMISSION_START_FLAG(__HANDLE__) ((__HANDLE__)->Instance->CR & CEC_CR_TXSOM)

/** @brief  Get Transmission End flag
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval FlagStatus 
  */
#define __HAL_CEC_GET_TRANSMISSION_END_FLAG(__HANDLE__)   ((__HANDLE__)->Instance->CR & CEC_CR_TXEOM)   

/** @brief  Clear OAR register
  * @param  __HANDLE__: specifies the CEC Handle.               
  * @retval none 
  */
#define __HAL_CEC_CLEAR_OAR(__HANDLE__)   CLEAR_BIT((__HANDLE__)->Instance->CFGR, CEC_CFGR_OAR)

/** @brief  Set OAR register (without resetting previously set address in case of multi-address mode)
  *          To reset OAR, __HAL_CEC_CLEAR_OAR() needs to be called beforehand
  * @param  __HANDLE__: specifies the CEC Handle. 
  * @param  __ADDRESS__: Own Address value (CEC logical address is identified by bit position)                   
  * @retval none 
  */
#define __HAL_CEC_SET_OAR(__HANDLE__,__ADDRESS__)   SET_BIT((__HANDLE__)->Instance->CFGR, (__ADDRESS__)<< CEC_CFGR_OAR_LSB_POS)

/** @brief Check CEC device Own Address Register (OAR) setting.
  *        OAR address is written in a 15-bit field within CEC_CFGR register. 
  * @param  __ADDRESS__: CEC own address.               
  * @retval Test result (TRUE or FALSE).
  */
#define IS_CEC_OAR_ADDRESS(__ADDRESS__) ((__ADDRESS__) <= 0x07FFF)  

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
  
#endif /* defined(STM32F373xC) || defined(STM32F378xx) */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32F3xx_HAL_CEC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
