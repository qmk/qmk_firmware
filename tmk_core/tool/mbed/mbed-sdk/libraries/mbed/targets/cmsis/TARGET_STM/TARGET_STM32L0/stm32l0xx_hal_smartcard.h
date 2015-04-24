/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smartcard.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of SMARTCARD HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __STM32L0xx_HAL_SMARTCARD_H
#define __STM32L0xx_HAL_SMARTCARD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup SMARTCARD SMARTCARD
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief SMARTCARD Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< Configures the SmartCard communication baud rate.
                                           The baud rate register is computed using the following formula:
                                              Baud Rate Register = ((PCLKx) / ((hsc->Init.BaudRate))) */
                                           
  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter @ref SMARTCARD_Word_Length can only be set to 9 (8 data + 1 parity bits). */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits @ref SMARTCARD_Stop_Bits. 
                                           Only 1.5 stop bits are authorized in SmartCard mode. */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref SMARTCARD_Parity
                                           @note The parity is enabled by default (PCE is forced to 1).
                                                 Since the WordLength is forced to 8 bits + parity, M is
                                                 forced to 1 and the parity bit is the 9th bit. */
 
  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref SMARTCARD_Mode */

  uint32_t CLKPolarity;               /*!< Specifies the steady state of the serial clock.
                                           This parameter can be a value of @ref SMARTCARD_Clock_Polarity */

  uint32_t CLKPhase;                  /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref SMARTCARD_Clock_Phase */

  uint32_t CLKLastBit;                /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                           data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                           This parameter can be a value of @ref SMARTCARD_Last_Bit */
                                             
  uint32_t OneBitSampling;            /*!< Specifies wether a single sample or three samples' majority vote is selected.
                                           Selecting the single sample method increases the receiver tolerance to clock
                                           deviations. This parameter can be a value of @ref SMARTCARD_OneBit_Sampling */

  uint32_t  Prescaler;                 /*!< Specifies the SmartCard Prescaler */
  
  uint32_t  GuardTime;                 /*!< Specifies the SmartCard Guard Time */
  
  uint32_t NACKState;                  /*!< Specifies whether the SmartCard NACK transmission is enabled
                                            in case of parity error.
                                            This parameter can be a value of @ref SMARTCARD_NACK_Enable */ 
                                           
  uint32_t TimeOutEnable;              /*!< Specifies whether the receiver timeout is enabled. 
                                            This parameter can be a value of @ref SMARTCARD_Timeout_Enable*/
  
  uint32_t TimeOutValue;               /*!< Specifies the receiver time out value in number of baud blocks: 
                                            it is used to implement the Character Wait Time (CWT) and 
                                            Block Wait Time (BWT). It is coded over 24 bits. */ 
                                           
  uint32_t BlockLength;                /*!< Specifies the SmartCard Block Length in T=1 Reception mode.
                                            This parameter can be any value from 0x0 to 0xFF */ 
                                           
  uint32_t AutoRetryCount;              /*!< Specifies the SmartCard auto-retry count (number of retries in
                                             receive and transmit mode). When set to 0, retransmission is 
                                             disabled. Otherwise, its maximum value is 7 (before signalling
                                             an error) */  

}SMARTCARD_InitTypeDef;

/** 
  * @brief  SMARTCARD advanced features initalization structure definition  
  */
typedef struct
{
  uint32_t AdvFeatureInit;            /*!< Specifies which advanced SMARTCARD features is initialized. Several
                                           advanced features may be initialized at the same time. This parameter 
                                           can be a value of @ref SMARTCARD_Advanced_Features_Initialization_Type */

  uint32_t TxPinLevelInvert;          /*!< Specifies whether the TX pin active level is inverted.
                                           This parameter can be a value of @ref SMARTCARD_Tx_Inv  */

  uint32_t RxPinLevelInvert;          /*!< Specifies whether the RX pin active level is inverted.
                                           This parameter can be a value of @ref SMARTCARD_Rx_Inv  */

  uint32_t DataInvert;                /*!< Specifies whether data are inverted (positive/direct logic
                                           vs negative/inverted logic).
                                           This parameter can be a value of @ref SMARTCARD_Data_Inv */

  uint32_t Swap;                      /*!< Specifies whether TX and RX pins are swapped.   
                                           This parameter can be a value of @ref SMARTCARD_Rx_Tx_Swap */

  uint32_t OverrunDisable;            /*!< Specifies whether the reception overrun detection is disabled.   
                                           This parameter can be a value of @ref SMARTCARD_Overrun_Disable */

  uint32_t DMADisableonRxError;       /*!< Specifies whether the DMA is disabled in case of reception error.     
                                           This parameter can be a value of @ref SMARTCARD_DMA_Disable_on_Rx_Error */

  uint32_t MSBFirst;                  /*!< Specifies whether MSB is sent first on UART line.      
                                           This parameter can be a value of @ref SMARTCARD_MSB_First */
}SMARTCARD_AdvFeatureInitTypeDef;

/** 
  * @brief HAL State structures definition  
  */ 
typedef enum
{
  HAL_SMARTCARD_STATE_RESET             = 0x00,    /*!< Peripheral is not yet Initialized */
  HAL_SMARTCARD_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use */
  HAL_SMARTCARD_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing */
  HAL_SMARTCARD_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission and Reception process is ongoing */ 
  HAL_SMARTCARD_STATE_TIMEOUT           = 0x03,    /*!< Timeout state */
  HAL_SMARTCARD_STATE_ERROR             = 0x04     /*!< Error */
}HAL_SMARTCARD_StateTypeDef;

/** 
  * @brief  HAL SMARTCARD Error Code definition
  */

#define HAL_SMARTCARD_ERROR_NONE      ((uint32_t)0x00)    /*!< No error                */
#define HAL_SMARTCARD_ERROR_PE        ((uint32_t)0x01)    /*!< Parity error            */
#define HAL_SMARTCARD_ERROR_NE        ((uint32_t)0x02)    /*!< Noise error             */
#define HAL_SMARTCARD_ERROR_FE        ((uint32_t)0x04)    /*!< frame error             */
#define HAL_SMARTCARD_ERROR_ORE       ((uint32_t)0x08)    /*!< Overrun error           */
#define HAL_SMARTCARD_ERROR_DMA       ((uint32_t)0x10)    /*!< DMA transfer error      */
#define HAL_SMARTCARD_ERROR_RTO       ((uint32_t)0x20)    /*!< Receiver TimeOut error  */


/**
  * @brief  SMARTCARD clock sources definition
  */
typedef enum
{
  SMARTCARD_CLOCKSOURCE_PCLK1      = 0x00,    /*!< PCLK1 clock source  */
  SMARTCARD_CLOCKSOURCE_PCLK2      = 0x01,    /*!< PCLK2 clock source  */
  SMARTCARD_CLOCKSOURCE_HSI        = 0x02,    /*!< HSI clock source    */
  SMARTCARD_CLOCKSOURCE_SYSCLK     = 0x04,    /*!< SYSCLK clock source */
  SMARTCARD_CLOCKSOURCE_LSE        = 0x08     /*!< LSE clock source    */
}SMARTCARD_ClockSourceTypeDef;

/** 
  * @brief  SMARTCARD handle Structure definition
  */
typedef struct
{
  USART_TypeDef                   *Instance;        /* USART registers base address                          */

  SMARTCARD_InitTypeDef           Init;             /* SmartCard communication parameters                    */

  SMARTCARD_AdvFeatureInitTypeDef AdvancedInit;     /* SmartCard advanced features initialization parameters */

  uint8_t                         *pTxBuffPtr;      /* Pointer to SmartCard Tx transfer Buffer               */

  uint16_t                        TxXferSize;       /* SmartCard Tx Transfer size                            */

  uint16_t                        TxXferCount;      /* SmartCard Tx Transfer Counter                         */

  uint8_t                         *pRxBuffPtr;      /* Pointer to SmartCard Rx transfer Buffer               */

  uint16_t                        RxXferSize;       /* SmartCard Rx Transfer size                            */

  uint16_t                        RxXferCount;      /* SmartCard Rx Transfer Counter                         */

  DMA_HandleTypeDef               *hdmatx;          /* SmartCard Tx DMA Handle parameters                    */

  DMA_HandleTypeDef               *hdmarx;          /* SmartCard Rx DMA Handle parameters                    */

  HAL_LockTypeDef                 Lock;             /* Locking object                                        */

  __IO HAL_SMARTCARD_StateTypeDef State;            /* SmartCard communication state                          */

  __IO uint32_t                   ErrorCode;        /* SmartCard Error code                                   */

}SMARTCARD_HandleTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup SMARTCARD_Exported_Constants SMARTCARD Exported Constants
  * @{
  */

/** @defgroup SMARTCARD_Word_Length SMARTCARD Word Length
  * @{
  */
#define SMARTCARD_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M_0)
#define IS_SMARTCARD_WORD_LENGTH(LENGTH) ((LENGTH) == SMARTCARD_WORDLENGTH_9B) 
/**
  * @}
  */
  
/** @defgroup SMARTCARD_Stop_Bits SMARTCARD Stop Bits
  * @{
  */
#define SMARTCARD_STOPBITS_1_5                   ((uint32_t)(USART_CR2_STOP))
#define IS_SMARTCARD_STOPBITS(STOPBITS) ((STOPBITS) == SMARTCARD_STOPBITS_1_5)
/**
  * @}
  */   

/** @defgroup SMARTCARD_Parity SMARTCARD Parity
  * @{
  */ 
#define SMARTCARD_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define SMARTCARD_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 
#define IS_SMARTCARD_PARITY(PARITY) (((PARITY) == SMARTCARD_PARITY_EVEN) || \
                                     ((PARITY) == SMARTCARD_PARITY_ODD))
/**
  * @}
  */ 

/** @defgroup SMARTCARD_Mode SMARTCARD Mode
  * @{
  */ 
#define SMARTCARD_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define SMARTCARD_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define SMARTCARD_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE |USART_CR1_RE))
#define IS_SMARTCARD_MODE(MODE) ((((MODE) & (uint32_t)0xFFF3) == 0x00) && ((MODE) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup SMARTCARD_Clock_Polarity SMARTCARD Clock Polarity
  * @{
  */
#define SMARTCARD_POLARITY_LOW                   ((uint32_t)0x0000)
#define SMARTCARD_POLARITY_HIGH                  ((uint32_t)USART_CR2_CPOL)
#define IS_SMARTCARD_POLARITY(CPOL) (((CPOL) == SMARTCARD_POLARITY_LOW) || ((CPOL) == SMARTCARD_POLARITY_HIGH))
/**
  * @}
  */ 

/** @defgroup SMARTCARD_Clock_Phase SMARTCARD Clock Phase
  * @{
  */
#define SMARTCARD_PHASE_1EDGE                    ((uint32_t)0x0000)
#define SMARTCARD_PHASE_2EDGE                    ((uint32_t)USART_CR2_CPHA)
#define IS_SMARTCARD_PHASE(CPHA) (((CPHA) == SMARTCARD_PHASE_1EDGE) || ((CPHA) == SMARTCARD_PHASE_2EDGE))
/**
  * @}
  */

/** @defgroup SMARTCARD_Last_Bit SMARTCARD Last Bit
  * @{
  */
#define SMARTCARD_LASTBIT_DISABLE                ((uint32_t)0x0000)
#define SMARTCARD_LASTBIT_ENABLE                 ((uint32_t)USART_CR2_LBCL)
#define IS_SMARTCARD_LASTBIT(LASTBIT) (((LASTBIT) == SMARTCARD_LASTBIT_DISABLE) || \
                                       ((LASTBIT) == SMARTCARD_LASTBIT_ENABLE))
/**
  * @}
  */

/** @defgroup SMARTCARD_OneBit_Sampling SMARTCARD OneBit Sampling
  * @{
  */
#define SMARTCARD_ONE_BIT_SAMPLE_DISABLE    ((uint32_t)0x0000)
#define SMARTCARD_ONE_BIT_SAMPLE_ENABLE     ((uint32_t)USART_CR3_ONEBIT)
#define IS_SMARTCARD_ONE_BIT_SAMPLE(ONEBIT) (((ONEBIT) == SMARTCARD_ONE_BIT_SAMPLE_DISABLE) || \
                                              ((ONEBIT) == SMARTCARD_ONE_BIT_SAMPLE_ENABLE))
/**
  * @}
  */  


/** @defgroup SMARTCARD_NACK_Enable SMARTCARD NACK Enable
  * @{
  */
#define SMARTCARD_NACK_ENABLE            ((uint32_t)USART_CR3_NACK)
#define SMARTCARD_NACK_DISABLE           ((uint32_t)0x0000)
#define IS_SMARTCARD_NACK(NACK) (((NACK) == SMARTCARD_NACK_ENABLE) || \
                                       ((NACK) == SMARTCARD_NACK_DISABLE))
/**
  * @}
  */

/** @defgroup SMARTCARD_Timeout_Enable SMARTCARD Timeout Enable
  * @{
  */
#define SMARTCARD_TIMEOUT_DISABLE      ((uint32_t)0x00000000)
#define SMARTCARD_TIMEOUT_ENABLE       ((uint32_t)USART_CR2_RTOEN)
#define IS_SMARTCARD_TIMEOUT(TIMEOUT) (((TIMEOUT) == SMARTCARD_TIMEOUT_DISABLE) || \
                                       ((TIMEOUT) == SMARTCARD_TIMEOUT_ENABLE))
/**
  * @}
  */
  
/** @defgroup SMARTCARD_DMA_Requests SMARTCARD DMA Requests
  * @{
  */

#define SMARTCARD_DMAREQ_TX                    ((uint32_t)USART_CR3_DMAT)
#define SMARTCARD_DMAREQ_RX                    ((uint32_t)USART_CR3_DMAR)

/**
  * @}
  */

/** @defgroup SMARTCARD_Advanced_Features_Initialization_Type SMARTCARD Advanced Features Initialization
  * @{
  */
#define SMARTCARD_ADVFEATURE_NO_INIT                 ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_TXINVERT_INIT           ((uint32_t)0x00000001)
#define SMARTCARD_ADVFEATURE_RXINVERT_INIT           ((uint32_t)0x00000002)
#define SMARTCARD_ADVFEATURE_DATAINVERT_INIT         ((uint32_t)0x00000004)
#define SMARTCARD_ADVFEATURE_SWAP_INIT               ((uint32_t)0x00000008)
#define SMARTCARD_ADVFEATURE_RXOVERRUNDISABLE_INIT   ((uint32_t)0x00000010)
#define SMARTCARD_ADVFEATURE_DMADISABLEONERROR_INIT  ((uint32_t)0x00000020)
#define SMARTCARD_ADVFEATURE_MSBFIRST_INIT           ((uint32_t)0x00000080)
#define IS_SMARTCARD_ADVFEATURE_INIT(INIT)           ((INIT) <= (SMARTCARD_ADVFEATURE_NO_INIT | \
                                                            SMARTCARD_ADVFEATURE_TXINVERT_INIT | \
                                                            SMARTCARD_ADVFEATURE_RXINVERT_INIT | \
                                                            SMARTCARD_ADVFEATURE_DATAINVERT_INIT | \
                                                            SMARTCARD_ADVFEATURE_SWAP_INIT | \
                                                            SMARTCARD_ADVFEATURE_RXOVERRUNDISABLE_INIT | \
                                                            SMARTCARD_ADVFEATURE_DMADISABLEONERROR_INIT   | \
                                                            SMARTCARD_ADVFEATURE_MSBFIRST_INIT))  
/**
  * @}
  */

/** @defgroup SMARTCARD_Tx_Inv SMARTCARD Tx Inv
  * @{
  */
#define SMARTCARD_ADVFEATURE_TXINV_DISABLE   ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_TXINV_ENABLE    ((uint32_t)USART_CR2_TXINV)
#define IS_SMARTCARD_ADVFEATURE_TXINV(TXINV) (((TXINV) == SMARTCARD_ADVFEATURE_TXINV_DISABLE) || \
                                         ((TXINV) == SMARTCARD_ADVFEATURE_TXINV_ENABLE))
/**
  * @}
  */

/** @defgroup SMARTCARD_Rx_Inv SMARTCARD Rx Inv
  * @{
  */
#define SMARTCARD_ADVFEATURE_RXINV_DISABLE   ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_RXINV_ENABLE    ((uint32_t)USART_CR2_RXINV)
#define IS_SMARTCARD_ADVFEATURE_RXINV(RXINV) (((RXINV) == SMARTCARD_ADVFEATURE_RXINV_DISABLE) || \
                                         ((RXINV) == SMARTCARD_ADVFEATURE_RXINV_ENABLE))
/**
  * @}
  */

/** @defgroup SMARTCARD_Data_Inv SMARTCARD Data Inv
  * @{
  */
#define SMARTCARD_ADVFEATURE_DATAINV_DISABLE     ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_DATAINV_ENABLE      ((uint32_t)USART_CR2_DATAINV)
#define IS_SMARTCARD_ADVFEATURE_DATAINV(DATAINV) (((DATAINV) == SMARTCARD_ADVFEATURE_DATAINV_DISABLE) || \
                                             ((DATAINV) == SMARTCARD_ADVFEATURE_DATAINV_ENABLE))
/**
  * @}
  */ 
  
/** @defgroup SMARTCARD_Rx_Tx_Swap SMARTCARD Rx Tx Swap
  * @{
  */
#define SMARTCARD_ADVFEATURE_SWAP_DISABLE   ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_SWAP_ENABLE    ((uint32_t)USART_CR2_SWAP)
#define IS_SMARTCARD_ADVFEATURE_SWAP(SWAP) (((SWAP) == SMARTCARD_ADVFEATURE_SWAP_DISABLE) || \
                                       ((SWAP) == SMARTCARD_ADVFEATURE_SWAP_ENABLE))
/**
  * @}
  */ 

/** @defgroup SMARTCARD_Overrun_Disable SMARTCARD Overrun Enabling
  * @{
  */
#define SMARTCARD_ADVFEATURE_OVERRUN_ENABLE   ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_OVERRUN_DISABLE  ((uint32_t)USART_CR3_OVRDIS)
#define IS_SMARTCARD_OVERRUN(OVERRUN)         (((OVERRUN) == SMARTCARD_ADVFEATURE_OVERRUN_ENABLE) || \
                                          ((OVERRUN) == SMARTCARD_ADVFEATURE_OVERRUN_DISABLE))
/**
  * @}
  */  

/** @defgroup SMARTCARD_DMA_Disable_on_Rx_Error SMARTCARD DMA on Rx Error
  * @{
  */
#define SMARTCARD_ADVFEATURE_DMA_ENABLEONRXERROR       ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_DMA_DISABLEONRXERROR      ((uint32_t)USART_CR3_DDRE)
#define IS_SMARTCARD_ADVFEATURE_DMAONRXERROR(DMA)      (((DMA) == SMARTCARD_ADVFEATURE_DMA_ENABLEONRXERROR) || \
                                                   ((DMA) == SMARTCARD_ADVFEATURE_DMA_DISABLEONRXERROR))
/**
  * @}
  */  

/** @defgroup SMARTCARD_MSB_First SMARTCARD MSB First
  * @{
  */
#define SMARTCARD_ADVFEATURE_MSBFIRST_DISABLE      ((uint32_t)0x00000000)
#define SMARTCARD_ADVFEATURE_MSBFIRST_ENABLE       ((uint32_t)USART_CR2_MSBFIRST)
#define IS_SMARTCARD_ADVFEATURE_MSBFIRST(MSBFIRST) (((MSBFIRST) == SMARTCARD_ADVFEATURE_MSBFIRST_DISABLE) || \
                                               ((MSBFIRST) == SMARTCARD_ADVFEATURE_MSBFIRST_ENABLE))
/**
  * @}
  */  

/** @defgroup SMARTCARD_Flags SMARTCARD Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define SMARTCARD_FLAG_REACK                     ((uint32_t)0x00400000)
#define SMARTCARD_FLAG_TEACK                     ((uint32_t)0x00200000)
#define SMARTCARD_FLAG_BUSY                      ((uint32_t)0x00010000)
#define SMARTCARD_FLAG_EOBF                      ((uint32_t)0x00001000)
#define SMARTCARD_FLAG_RTOF                      ((uint32_t)0x00000800)
#define SMARTCARD_FLAG_TXE                       ((uint32_t)0x00000080)
#define SMARTCARD_FLAG_TC                        ((uint32_t)0x00000040)
#define SMARTCARD_FLAG_RXNE                      ((uint32_t)0x00000020)
#define SMARTCARD_FLAG_ORE                       ((uint32_t)0x00000008)
#define SMARTCARD_FLAG_NE                        ((uint32_t)0x00000004)
#define SMARTCARD_FLAG_FE                        ((uint32_t)0x00000002)
#define SMARTCARD_FLAG_PE                        ((uint32_t)0x00000001)
/**
  * @}
  */

/** @defgroup SMARTCARD_Interrupt_definition SMARTCARD Interrupt definition
  *        Elements values convention: 0000ZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  * @{
  */
  
#define SMARTCARD_IT_PE                          ((uint16_t)0x0028)
#define SMARTCARD_IT_TXE                         ((uint16_t)0x0727)
#define SMARTCARD_IT_TC                          ((uint16_t)0x0626)
#define SMARTCARD_IT_RXNE                        ((uint16_t)0x0525)

#define SMARTCARD_IT_ERR                         ((uint16_t)0x0060)
#define SMARTCARD_IT_ORE                         ((uint16_t)0x0300)
#define SMARTCARD_IT_NE                          ((uint16_t)0x0200)
#define SMARTCARD_IT_FE                          ((uint16_t)0x0100)

#define SMARTCARD_IT_EOB                         ((uint16_t)0x0C3B)
#define SMARTCARD_IT_RTO                         ((uint16_t)0x0B3A)
/**
  * @}
  */ 


/** @defgroup SMARTCARD_IT_CLEAR_Flags SMARTCARD IT CLEAR Flags
  * @{
  */
#define SMARTCARD_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag */          
#define SMARTCARD_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag */         
#define SMARTCARD_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag */        
#define SMARTCARD_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag */         
#define SMARTCARD_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag */
#define SMARTCARD_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag */ 
#define SMARTCARD_CLEAR_RTOF                      USART_ICR_RTOCF           /*!< Receiver Time Out Clear Flag */     
#define SMARTCARD_CLEAR_EOBF                      USART_ICR_EOBCF           /*!< End Of Block Clear Flag */          
/**
  * @}
  */

/** @defgroup SMARTCARD_Request_Parameters SMARTCARD Request Parameters
  * @{
  */        
#define SMARTCARD_RXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request */ 
#define SMARTCARD_TXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
#define IS_SMARTCARD_REQUEST_PARAMETER(PARAM) (((PARAM) == SMARTCARD_RXDATA_FLUSH_REQUEST) || \
                                               ((PARAM) == SMARTCARD_TXDATA_FLUSH_REQUEST))   
/**
  * @}
  */
  
  
/** @defgroup SMARTCARD_CR3_SCAR_CNT_LSB_POS SMARTCARD CR3 LSB Position
  * @{
  */
#define SMARTCARD_CR3_SCARCNT_LSB_POS            ((uint32_t) 17)
/**
  * @}
  */
  
/** @defgroup SMARTCARD_GTPR_GT_LSBPOS SMARTCARD GTPR GT LSB Position
  * @{
  */
#define SMARTCARD_GTPR_GT_LSB_POS            ((uint32_t) 8)
/**
  * @}
  */ 
  
/** @defgroup SMARTCARD_RTOR_BLEN_LSBPOS SMARTCARD RTOR BLEN LSB Position
  * @{
  */
#define SMARTCARD_RTOR_BLEN_LSB_POS          ((uint32_t) 24)
/**
  * @}
  */    
 
/** @defgroup SMARTCARD_Interruption_Mask SMARTCARD Interruption Mask
  * @{
  */ 
#define SMARTCARD_IT_MASK  ((uint16_t)0x001F)  
/**
  * @}
  */
    
/**
  * @}
  */    
    
/* Exported macro ------------------------------------------------------------*/
/** @defgroup SMARTCARD_Exported_Macros SMARTCARD Exported Macros
  * @{
  */

/** @brief Reset SMARTCARD handle state
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2
  * @retval None
  */
#define __HAL_SMARTCARD_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SMARTCARD_STATE_RESET)

/** @brief  Flushs the Smartcard DR register 
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_FLUSH_DRREGISTER(__HANDLE__)                                 \
    do{                                                                              \
      SET_BIT((__HANDLE__)->Instance->RQR, SMARTCARD_RXDATA_FLUSH_REQUEST); \
      SET_BIT((__HANDLE__)->Instance->RQR, SMARTCARD_TXDATA_FLUSH_REQUEST); \
      } while(0)

/** @brief  Clears the specified SMARTCARD pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg SMARTCARD_CLEAR_PEF
  *            @arg SMARTCARD_CLEAR_FEF
  *            @arg SMARTCARD_CLEAR_NEF
  *            @arg SMARTCARD_CLEAR_OREF
  *            @arg SMARTCARD_CLEAR_IDLEF
  *            @arg SMARTCARD_CLEAR_TCF
  *            @arg SMARTCARD_CLEAR_RTOF
  *            @arg SMARTCARD_CLEAR_EOBF
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = ~(__FLAG__))

/** @brief  Clear the SMARTCARD PE pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_PEFLAG(__HANDLE__)   __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__,SMARTCARD_CLEAR_PEF)


/** @brief  Clear the SMARTCARD FE pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_FEFLAG(__HANDLE__)   __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__,SMARTCARD_CLEAR_FEF)

/** @brief  Clear the SMARTCARD NE pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_NEFLAG(__HANDLE__)   __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__,SMARTCARD_CLEAR_NEF)

/** @brief  Clear the SMARTCARD ORE pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_OREFLAG(__HANDLE__)   __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__,SMARTCARD_CLEAR_OREF)

/** @brief  Clear the SMARTCARD IDLE pending flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_IDLEFLAG(__HANDLE__)   __HAL_SMARTCARD_CLEAR_FLAG(__HANDLE__,SMARTCARD_CLEAR_IDLEF)

/** @brief  Checks whether the specified Smartcard flag is set or not.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg SMARTCARD_FLAG_REACK: Receive enable ackowledge flag
  *            @arg SMARTCARD_FLAG_TEACK: Transmit enable ackowledge flag
  *            @arg SMARTCARD_FLAG_BUSY:  Busy flag
  *            @arg SMARTCARD_FLAG_EOBF:  End of block flag   
  *            @arg SMARTCARD_FLAG_RTOF:  Receiver timeout flag
  *            @arg SMARTCARD_FLAG_TXE:   Transmit data register empty flag
  *            @arg SMARTCARD_FLAG_TC:    Transmission Complete flag
  *            @arg SMARTCARD_FLAG_RXNE:  Receive data register not empty flag
  *            @arg SMARTCARD_FLAG_ORE:   OverRun Error flag
  *            @arg SMARTCARD_FLAG_NE:    Noise Error flag
  *            @arg SMARTCARD_FLAG_FE:    Framing Error flag
  *            @arg SMARTCARD_FLAG_PE:    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SMARTCARD_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))

/** @brief  Enables the specified SmartCard interrupt.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __INTERRUPT__: specifies the SMARTCARD interrupt to enable.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_EOBF: End Of Block interrupt
  *            @arg SMARTCARD_IT_RTOF: Receive TimeOut interrupt
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  *            @arg SMARTCARD_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_SMARTCARD_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((((uint8_t)(__INTERRUPT__)) >> 5) == 1)? ((__HANDLE__)->Instance->CR1 |= (1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))): \
                                                        ((((uint8_t)(__INTERRUPT__)) >> 5) == 2)? ((__HANDLE__)->Instance->CR2 |= (1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))): \
                                                        ((__HANDLE__)->Instance->CR3 |= (1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))))
/** @brief  Disables the specified SmartCard interrupt.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __INTERRUPT__: specifies the SMARTCARD interrupt to enable.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_EOBF: End Of Block interrupt
  *            @arg SMARTCARD_IT_RTOF: Receive TimeOut interrupt
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  *            @arg SMARTCARD_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_SMARTCARD_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((((uint8_t)(__INTERRUPT__)) >> 5) == 1)? ((__HANDLE__)->Instance->CR1 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))): \
                                                        ((((uint8_t)(__INTERRUPT__)) >> 5) == 2)? ((__HANDLE__)->Instance->CR2 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))): \
                                                        ((__HANDLE__)->Instance->CR3 &= ~ ((uint32_t)1 << ((__INTERRUPT__) & SMARTCARD_IT_MASK))))

/** @brief  Checks whether the specified SmartCard interrupt has occurred or not.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT__: specifies the SMARTCARD interrupt to check.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_EOBF: End Of Block interrupt
  *            @arg SMARTCARD_IT_RTOF: Receive TimeOut interrupt  
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_ORE:  OverRun Error interrupt
  *            @arg SMARTCARD_IT_NE:   Noise Error interrupt
  *            @arg SMARTCARD_IT_FE:   Framing Error interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_SMARTCARD_GET_IT(__HANDLE__, __IT__) ((__HANDLE__)->Instance->ISR & ((uint32_t)1 << ((__IT__)>> 0x08))) 

/** @brief  Checks whether the specified SmartCard interrupt interrupt source is enabled.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT__: specifies the SMARTCARD interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_IT_EOBF: End Of Block interrupt
  *            @arg SMARTCARD_IT_RTOF: Receive TimeOut interrupt  
  *            @arg SMARTCARD_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg SMARTCARD_IT_TC:   Transmission complete interrupt
  *            @arg SMARTCARD_IT_RXNE: Receive Data register not empty interrupt
  *            @arg SMARTCARD_IT_ORE:  OverRun Error interrupt
  *            @arg SMARTCARD_IT_NE:   Noise Error interrupt
  *            @arg SMARTCARD_IT_FE:   Framing Error interrupt
  *            @arg SMARTCARD_IT_PE:   Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_SMARTCARD_GET_IT_SOURCE(__HANDLE__, __IT__) ((((((uint8_t)(__IT__)) >> 5) == 1)? (__HANDLE__)->Instance->CR1:(((((uint8_t)(__IT__)) >> 5) == 2)? \
                                                               (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & ((uint32_t)1 << \
                                                               (((uint16_t)(__IT__)) & SMARTCARD_IT_MASK)))


/** @brief  Clears the specified SMARTCARD ISR flag, in setting the proper ICR register flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __IT_CLEAR__: specifies the interrupt clear register flag that needs to be set
  *                       to clear the corresponding interrupt
  *          This parameter can be one of the following values:
  *            @arg USART_CLEAR_PEF: Parity Error Clear Flag
  *            @arg USART_CLEAR_FEF: Framing Error Clear Flag
  *            @arg USART_CLEAR_NEF: Noise detected Clear Flag
  *            @arg USART_CLEAR_OREF: OverRun Error Clear Flag
  *            @arg USART_CLEAR_TCF: Transmission Complete Clear Flag
  *            @arg USART_CLEAR_RTOF: Receiver Time Out Clear Flag
  *            @arg USART_CLEAR_EOBF: End Of Block Clear Flag 
  * @retval None
  */
#define __HAL_SMARTCARD_CLEAR_IT(__HANDLE__, __IT_CLEAR__) ((__HANDLE__)->Instance->ICR = (uint32_t)(__IT_CLEAR__)) 

/** @brief  Set a specific SMARTCARD request flag.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __REQ__: specifies the request flag to set
  *          This parameter can be one of the following values:  
  *            @arg SMARTCARD_RXDATA_FLUSH_REQUEST: Receive Data flush Request 
  *            @arg SMARTCARD_TXDATA_FLUSH_REQUEST: Transmit data flush Request 
  *
  * @retval None
  */ 
#define __HAL_SMARTCARD_SEND_REQ(__HANDLE__, __REQ__) ((__HANDLE__)->Instance->RQR |= (uint32_t)(__REQ__)) 

/** @brief  Enables the SMARTCARD one bit sample method
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Disables the SMARTCARD one bit sample method
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  * @retval None
  */
#define __HAL_SMARTCARD_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT))

/** @brief  Enable the USART associated to the SMARTCARD Handle
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */ 

#define __HAL_SMARTCARD_ENABLE(__HANDLE__)               ( (__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable the USART associated to the SMARTCARD Handle
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @retval None
  */
#define __HAL_SMARTCARD_DISABLE(__HANDLE__)              ( (__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)

/** @brief  Macros to enable or disable the SmartCard DMA request.
  * @param  __HANDLE__: specifies the SMARTCARD Handle.
  *         The Handle Instance which can be USART1 or USART2.
  * @param  __REQUEST__: specifies the SmartCard DMA request.
  *          This parameter can be one of the following values:
  *            @arg SMARTCARD_DMAREQ_TX: SmartCard DMA transmit request
  *            @arg SMARTCARD_DMAREQ_RX: SmartCard DMA receive request
  */
#define __HAL_SMARTCARD_DMA_REQUEST_ENABLE(__HANDLE__, __REQUEST__)    ((__HANDLE__)->Instance->CR3 |=  (__REQUEST__))
#define __HAL_SMARTCARD_DMA_REQUEST_DISABLE(__HANDLE__, __REQUEST__)   ((__HANDLE__)->Instance->CR3 &=  ~(__REQUEST__))

/** @brief  Check the Baud rate range. The maximum Baud Rate is derived from the 
  *         maximum clock on F3 (i.e. 72 MHz) divided by the oversampling used 
  *         on the SMARTCARD (i.e. 16) 
  * @param  __BAUDRATE__: Baud rate set by the configuration function.
  * @retval Test result (TRUE or FALSE) 
  */ 
#define IS_SMARTCARD_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 4500001)

/** @brief  Check the block length range. The maximum SMARTCARD block length is 0xFF.
  * @param  __LENGTH__: block length.
  * @retval Test result (TRUE or FALSE) 
  */
#define IS_SMARTCARD_BLOCKLENGTH(__LENGTH__) ((__LENGTH__) <= 0xFF)

/** @brief  Check the receiver timeout value. The maximum SMARTCARD receiver timeout 
  *         value is 0xFFFFFF.
  * @param  __TIMEOUTVALUE__: receiver timeout value.
  * @retval Test result (TRUE or FALSE) 
  */
#define IS_SMARTCARD_TIMEOUT_VALUE(__TIMEOUTVALUE__)    ((__TIMEOUTVALUE__) <= 0xFFFFFF)

/** @brief  Check the SMARTCARD autoretry counter value. The maximum number of 
  *         retransmissions is 0x7.
  * @param  __COUNT__: number of retransmissions
  * @retval Test result (TRUE or FALSE) 
  */
#define IS_SMARTCARD_AUTORETRY_COUNT(__COUNT__)         ((__COUNT__) <= 0x7)

/**
  * @}
  */ 

/* Include SMARTCARD HAL Extension module */
#include "stm32l0xx_hal_smartcard_ex.h"
/* Exported functions --------------------------------------------------------*/
/** @defgroup SMARTCARD_Exported_Functions SMARTCARD Exported Functions
  * @{
  */
/* Initialization/de-initialization functions  **********************************/
/** @defgroup SMARTCARD_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @{
 */
HAL_StatusTypeDef HAL_SMARTCARD_Init(SMARTCARD_HandleTypeDef *hsc);
HAL_StatusTypeDef HAL_SMARTCARD_DeInit(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_MspInit(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_MspDeInit(SMARTCARD_HandleTypeDef *hsc);
/**
  * @}
  */

/* IO operation functions *******************************************************/
/** @defgroup SMARTCARD_Exported_Functions_Group2 IO operation functions
 *  @{
 */
HAL_StatusTypeDef HAL_SMARTCARD_Transmit(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SMARTCARD_Receive(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Receive_IT(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Transmit_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SMARTCARD_Receive_DMA(SMARTCARD_HandleTypeDef *hsc, uint8_t *pData, uint16_t Size);
void HAL_SMARTCARD_IRQHandler(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_TxCpltCallback(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_RxCpltCallback(SMARTCARD_HandleTypeDef *hsc);
void HAL_SMARTCARD_ErrorCallback(SMARTCARD_HandleTypeDef *hsc);
/**
  * @}
  */
/* IO operation functions *******************************************************/
/** @defgroup SMARTCARD_Exported_Functions_Group3 Peripheral State functions
 *  @{
 */
/* Peripheral State functions  **************************************************/
HAL_SMARTCARD_StateTypeDef HAL_SMARTCARD_GetState(SMARTCARD_HandleTypeDef *hsc);
uint32_t HAL_SMARTCARD_GetError(SMARTCARD_HandleTypeDef *hsc);
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

#endif /* __STM32L0xx_HAL_SMARTCARD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

