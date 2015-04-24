/**
  ******************************************************************************
  * @file    stm32f30x_usart.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2014
  * @brief   This file contains all the functions prototypes for the USART 
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
#ifndef __STM32F30x_USART_H
#define __STM32F30x_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

   
   
/** 
  * @brief  USART Init Structure definition  
  */ 

typedef struct
{
  uint32_t USART_BaudRate;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

  uint32_t USART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint32_t USART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint32_t USART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint32_t USART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint32_t USART_HardwareFlowControl; /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control*/
} USART_InitTypeDef;

/** 
  * @brief  USART Clock Init Structure definition
  */ 

typedef struct
{
  uint32_t USART_Clock;             /*!< Specifies whether the USART clock is enabled or disabled.
                                         This parameter can be a value of @ref USART_Clock */

  uint32_t USART_CPOL;              /*!< Specifies the steady state of the serial clock.
                                         This parameter can be a value of @ref USART_Clock_Polarity */

  uint32_t USART_CPHA;              /*!< Specifies the clock transition on which the bit capture is made.
                                         This parameter can be a value of @ref USART_Clock_Phase */

  uint32_t USART_LastBit;           /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                         data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                         This parameter can be a value of @ref USART_Last_Bit */
} USART_ClockInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup USART_Exported_Constants
  * @{
  */ 

#define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == UART4) || \
                                     ((PERIPH) == UART5))

#define IS_USART_123_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3))

#define IS_USART_1234_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                      ((PERIPH) == USART2) || \
                                      ((PERIPH) == USART3) || \
                                      ((PERIPH) == UART4))


/** @defgroup USART_Word_Length 
  * @{
  */ 

#define USART_WordLength_8b                  ((uint32_t)0x00000000)
#define USART_WordLength_9b                  USART_CR1_M
#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
                                      ((LENGTH) == USART_WordLength_9b))
/**
  * @}
  */ 

/** @defgroup USART_Stop_Bits 
  * @{
  */ 

#define USART_StopBits_1                     ((uint32_t)0x00000000)
#define USART_StopBits_2                     USART_CR2_STOP_1
#define USART_StopBits_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1)
#define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
                                     ((STOPBITS) == USART_StopBits_2) || \
                                     ((STOPBITS) == USART_StopBits_1_5))
/**
  * @}
  */ 

/** @defgroup USART_Parity 
  * @{
  */ 

#define USART_Parity_No                      ((uint32_t)0x00000000)
#define USART_Parity_Even                    USART_CR1_PCE
#define USART_Parity_Odd                     (USART_CR1_PCE | USART_CR1_PS) 
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No) || \
                                 ((PARITY) == USART_Parity_Even) || \
                                 ((PARITY) == USART_Parity_Odd))
/**
  * @}
  */ 

/** @defgroup USART_Mode 
  * @{
  */ 

#define USART_Mode_Rx                        USART_CR1_RE
#define USART_Mode_Tx                        USART_CR1_TE
#define IS_USART_MODE(MODE) ((((MODE) & (uint32_t)0xFFFFFFF3) == 0x00) && \
                              ((MODE) != (uint32_t)0x00))
/**
  * @}
  */ 

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 

#define USART_HardwareFlowControl_None       ((uint32_t)0x00000000)
#define USART_HardwareFlowControl_RTS        USART_CR3_RTSE
#define USART_HardwareFlowControl_CTS        USART_CR3_CTSE
#define USART_HardwareFlowControl_RTS_CTS    (USART_CR3_RTSE | USART_CR3_CTSE)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == USART_HardwareFlowControl_None) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_CTS) || \
                               ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
/**
  * @}
  */ 

/** @defgroup USART_Clock 
  * @{
  */ 
  
#define USART_Clock_Disable                  ((uint32_t)0x00000000)
#define USART_Clock_Enable                   USART_CR2_CLKEN
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
                               ((CLOCK) == USART_Clock_Enable))
/**
  * @}
  */ 

/** @defgroup USART_Clock_Polarity 
  * @{
  */
  
#define USART_CPOL_Low                       ((uint32_t)0x00000000)
#define USART_CPOL_High                      USART_CR2_CPOL
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))

/**
  * @}
  */ 

/** @defgroup USART_Clock_Phase
  * @{
  */

#define USART_CPHA_1Edge                     ((uint32_t)0x00000000)
#define USART_CPHA_2Edge                     USART_CR2_CPHA
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))

/**
  * @}
  */

/** @defgroup USART_Last_Bit
  * @{
  */

#define USART_LastBit_Disable                ((uint32_t)0x00000000)
#define USART_LastBit_Enable                 USART_CR2_LBCL
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
                                   ((LASTBIT) == USART_LastBit_Enable))
/**
  * @}
  */
  
/** @defgroup USART_DMA_Requests 
  * @{
  */

#define USART_DMAReq_Tx                      USART_CR3_DMAT
#define USART_DMAReq_Rx                      USART_CR3_DMAR
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint32_t)0xFFFFFF3F) == 0x00) && \
                                  ((DMAREQ) != (uint32_t)0x00))

/**
  * @}
  */ 

/** @defgroup USART_DMA_Recception_Error
  * @{
  */

#define USART_DMAOnError_Enable              ((uint32_t)0x00000000)
#define USART_DMAOnError_Disable             USART_CR3_DDRE
#define IS_USART_DMAONERROR(DMAERROR) (((DMAERROR) == USART_DMAOnError_Disable)|| \
                                       ((DMAERROR) == USART_DMAOnError_Enable))
/**
  * @}
  */ 

/** @defgroup USART_MuteMode_WakeUp_methods
  * @{
  */

#define USART_WakeUp_IdleLine                ((uint32_t)0x00000000)
#define USART_WakeUp_AddressMark             USART_CR1_WAKE
#define IS_USART_MUTEMODE_WAKEUP(WAKEUP) (((WAKEUP) == USART_WakeUp_IdleLine) || \
                                          ((WAKEUP) == USART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup USART_Address_Detection
  * @{
  */ 

#define USART_AddressLength_4b               ((uint32_t)0x00000000)
#define USART_AddressLength_7b               USART_CR2_ADDM7
#define IS_USART_ADDRESS_DETECTION(ADDRESS) (((ADDRESS) == USART_AddressLength_4b) || \
                                             ((ADDRESS) == USART_AddressLength_7b))
/**
  * @}
  */ 

/** @defgroup USART_StopMode_WakeUp_methods 
  * @{
  */ 

#define USART_WakeUpSource_AddressMatch      ((uint32_t)0x00000000)
#define USART_WakeUpSource_StartBit          USART_CR3_WUS_1
#define USART_WakeUpSource_RXNE              (uint32_t)(USART_CR3_WUS_0 | USART_CR3_WUS_1)
#define IS_USART_STOPMODE_WAKEUPSOURCE(SOURCE) (((SOURCE) == USART_WakeUpSource_AddressMatch) || \
                                                ((SOURCE) == USART_WakeUpSource_StartBit) || \
                                                ((SOURCE) == USART_WakeUpSource_RXNE))
/**
  * @}
  */ 

/** @defgroup USART_LIN_Break_Detection_Length 
  * @{
  */
  
#define USART_LINBreakDetectLength_10b       ((uint32_t)0x00000000)
#define USART_LINBreakDetectLength_11b       USART_CR2_LBDL
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
                               (((LENGTH) == USART_LINBreakDetectLength_10b) || \
                                ((LENGTH) == USART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power 
  * @{
  */

#define USART_IrDAMode_LowPower              USART_CR3_IRLP
#define USART_IrDAMode_Normal                ((uint32_t)0x00000000)
#define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IrDAMode_LowPower) || \
                                  ((MODE) == USART_IrDAMode_Normal))
/**
  * @}
  */ 

/** @defgroup USART_DE_Polarity 
  * @{
  */

#define USART_DEPolarity_High                ((uint32_t)0x00000000)
#define USART_DEPolarity_Low                 USART_CR3_DEP
#define IS_USART_DE_POLARITY(POLARITY) (((POLARITY) == USART_DEPolarity_Low) || \
                                        ((POLARITY) == USART_DEPolarity_High))
/**
  * @}
  */ 

/** @defgroup USART_Inversion_Pins 
  * @{
  */

#define USART_InvPin_Tx                      USART_CR2_TXINV
#define USART_InvPin_Rx                      USART_CR2_RXINV
#define IS_USART_INVERSTION_PIN(PIN) ((((PIN) & (uint32_t)0xFFFCFFFF) == 0x00) && \
                                       ((PIN) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup USART_AutoBaudRate_Mode 
  * @{
  */

#define USART_AutoBaudRate_StartBit                 ((uint32_t)0x00000000)
#define USART_AutoBaudRate_FallingEdge              USART_CR2_ABRMODE_0
#define USART_AutoBaudRate_0x7FFrame                USART_CR2_ABRMODE_1
#define USART_AutoBaudRate_0x55Frame                (USART_CR2_ABRMODE_0 | USART_CR2_ABRMODE_1)
#define IS_USART_AUTOBAUDRATE_MODE(MODE) (((MODE) == USART_AutoBaudRate_StartBit) || \
                                          ((MODE) == USART_AutoBaudRate_FallingEdge) || \
                                          ((MODE) == USART_AutoBaudRate_0x7FFrame) || \
                                          ((MODE) == USART_AutoBaudRate_0x55Frame))
/**
  * @}
  */

/** @defgroup USART_OVR_DETECTION
  * @{
  */

#define USART_OVRDetection_Enable            ((uint32_t)0x00000000)
#define USART_OVRDetection_Disable           USART_CR3_OVRDIS
#define IS_USART_OVRDETECTION(OVR) (((OVR) == USART_OVRDetection_Enable)|| \
                                    ((OVR) == USART_OVRDetection_Disable))
/**
  * @}
  */ 
/** @defgroup USART_Request 
  * @{
  */

#define USART_Request_ABRRQ                  USART_RQR_ABRRQ
#define USART_Request_SBKRQ                  USART_RQR_SBKRQ
#define USART_Request_MMRQ                   USART_RQR_MMRQ
#define USART_Request_RXFRQ                  USART_RQR_RXFRQ
#define USART_Request_TXFRQ                  USART_RQR_TXFRQ

#define IS_USART_REQUEST(REQUEST) (((REQUEST) == USART_Request_TXFRQ) || \
                                   ((REQUEST) == USART_Request_RXFRQ) || \
                                   ((REQUEST) == USART_Request_MMRQ) || \
                                   ((REQUEST) == USART_Request_SBKRQ) || \
                                   ((REQUEST) == USART_Request_ABRRQ))
/**
  * @}
  */ 

/** @defgroup USART_Flags 
  * @{
  */
#define USART_FLAG_REACK                     USART_ISR_REACK
#define USART_FLAG_TEACK                     USART_ISR_TEACK
#define USART_FLAG_WU                        USART_ISR_WUF
#define USART_FLAG_RWU                       USART_ISR_RWU
#define USART_FLAG_SBK                       USART_ISR_SBKF
#define USART_FLAG_CM                        USART_ISR_CMF
#define USART_FLAG_BUSY                      USART_ISR_BUSY
#define USART_FLAG_ABRF                      USART_ISR_ABRF
#define USART_FLAG_ABRE                      USART_ISR_ABRE
#define USART_FLAG_EOB                       USART_ISR_EOBF
#define USART_FLAG_RTO                       USART_ISR_RTOF
#define USART_FLAG_nCTSS                     USART_ISR_CTS 
#define USART_FLAG_CTS                       USART_ISR_CTSIF
#define USART_FLAG_LBD                       USART_ISR_LBD
#define USART_FLAG_TXE                       USART_ISR_TXE
#define USART_FLAG_TC                        USART_ISR_TC
#define USART_FLAG_RXNE                      USART_ISR_RXNE
#define USART_FLAG_IDLE                      USART_ISR_IDLE
#define USART_FLAG_ORE                       USART_ISR_ORE
#define USART_FLAG_NE                        USART_ISR_NE
#define USART_FLAG_FE                        USART_ISR_FE
#define USART_FLAG_PE                        USART_ISR_PE
#define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
                             ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
                             ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
                             ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
                             ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
                             ((FLAG) == USART_FLAG_nCTSS) || ((FLAG) == USART_FLAG_RTO) || \
                             ((FLAG) == USART_FLAG_EOB) || ((FLAG) == USART_FLAG_ABRE) || \
                             ((FLAG) == USART_FLAG_ABRF) || ((FLAG) == USART_FLAG_BUSY) || \
                             ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_SBK) || \
                             ((FLAG) == USART_FLAG_RWU) || ((FLAG) == USART_FLAG_WU) || \
                             ((FLAG) == USART_FLAG_TEACK)|| ((FLAG) == USART_FLAG_REACK))

#define IS_USART_CLEAR_FLAG(FLAG) (((FLAG) == USART_FLAG_WU) || ((FLAG) == USART_FLAG_TC) || \
                                   ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_ORE) || \
                                   ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE) || \
                                   ((FLAG) == USART_FLAG_LBD) || ((FLAG) == USART_FLAG_CTS) || \
                                   ((FLAG) == USART_FLAG_RTO) || ((FLAG) == USART_FLAG_EOB) || \
                                   ((FLAG) == USART_FLAG_CM) || ((FLAG) == USART_FLAG_PE))
/**
  * @}
  */ 

/** @defgroup USART_Interrupt_definition 
  * @brief USART Interrupt definition
  * USART_IT possible values
  * Elements values convention: 0xZZZZYYXX
  *   XX: Position of the corresponding Interrupt
  *   YY: Register index
  *   ZZZZ: Flag position
  * @{
  */

#define USART_IT_WU                          ((uint32_t)0x00140316)
#define USART_IT_CM                          ((uint32_t)0x0011010E)
#define USART_IT_EOB                         ((uint32_t)0x000C011B)
#define USART_IT_RTO                         ((uint32_t)0x000B011A)
#define USART_IT_PE                          ((uint32_t)0x00000108)
#define USART_IT_TXE                         ((uint32_t)0x00070107)
#define USART_IT_TC                          ((uint32_t)0x00060106)
#define USART_IT_RXNE                        ((uint32_t)0x00050105)
#define USART_IT_IDLE                        ((uint32_t)0x00040104)
#define USART_IT_LBD                         ((uint32_t)0x00080206)
#define USART_IT_CTS                         ((uint32_t)0x0009030A) 
#define USART_IT_ERR                         ((uint32_t)0x00000300)
#define USART_IT_ORE                         ((uint32_t)0x00030300)
#define USART_IT_NE                          ((uint32_t)0x00020300)
#define USART_IT_FE                          ((uint32_t)0x00010300)

#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                                ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                                ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                                ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR) || \
                                ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                                ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))

#define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                             ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                             ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                             ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
                             ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE) || \
                             ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                             ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))

#define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_PE) || \
                               ((IT) == USART_IT_FE) || ((IT) == USART_IT_NE) || \
                               ((IT) == USART_IT_ORE) || ((IT) == USART_IT_IDLE) || \
                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS) || \
                               ((IT) == USART_IT_RTO) || ((IT) == USART_IT_EOB) || \
                               ((IT) == USART_IT_CM) || ((IT) == USART_IT_WU))
/**
  * @}
  */

/** @defgroup USART_Global_definition 
  * @{
  */

#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x005B8D81))
#define IS_USART_DE_ASSERTION_DEASSERTION_TIME(TIME) ((TIME) <= 0x1F)
#define IS_USART_AUTO_RETRY_COUNTER(COUNTER) ((COUNTER) <= 0x7)
#define IS_USART_TIMEOUT(TIMEOUT) ((TIMEOUT) <= 0x00FFFFFF)
#define IS_USART_DATA(DATA) ((DATA) <= 0x1FF)

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DirectionModeCmd(USART_TypeDef* USARTx, uint32_t USART_DirectionMode, FunctionalState NewState);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_MSBFirstCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DataInvCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_InvPinCmd(USART_TypeDef* USARTx, uint32_t USART_InvPin, FunctionalState NewState);
void USART_SWAPPinCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ReceiverTimeOutCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetReceiverTimeOut(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOut);

/* STOP Mode functions ********************************************************/
void USART_STOPModeCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_StopModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource);

/* AutoBaudRate functions *****************************************************/
void USART_AutoBaudRateCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_AutoBaudRateConfig(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate);

/* Data transfers functions ***************************************************/
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);

/* Multi-Processor Communication functions ************************************/
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_MuteModeWakeUpConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUp);
void USART_MuteModeCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_AddressDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_AddressLength);
/* LIN mode functions *********************************************************/
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint32_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Half-duplex mode function **************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* Smartcard mode functions ***************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetAutoRetryCount(USART_TypeDef* USARTx, uint8_t USART_AutoCount);
void USART_SetBlockLength(USART_TypeDef* USARTx, uint8_t USART_BlockLength);

/* IrDA mode functions ********************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, uint32_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);

/* RS485 mode functions *******************************************************/
void USART_DECmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_DEPolarityConfig(USART_TypeDef* USARTx, uint32_t USART_DEPolarity);
void USART_SetDEAssertionTime(USART_TypeDef* USARTx, uint32_t USART_DEAssertionTime);
void USART_SetDEDeassertionTime(USART_TypeDef* USARTx, uint32_t USART_DEDeassertionTime);

/* DMA transfers management functions *****************************************/
void USART_DMACmd(USART_TypeDef* USARTx, uint32_t USART_DMAReq, FunctionalState NewState);
void USART_DMAReceptionErrorConfig(USART_TypeDef* USARTx, uint32_t USART_DMAOnError);

/* Interrupts and flags management functions **********************************/
void USART_ITConfig(USART_TypeDef* USARTx, uint32_t USART_IT, FunctionalState NewState);
void USART_RequestCmd(USART_TypeDef* USARTx, uint32_t USART_Request, FunctionalState NewState);
void USART_OverrunDetectionConfig(USART_TypeDef* USARTx, uint32_t USART_OVRDetection);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint32_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint32_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint32_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint32_t USART_IT);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F30x_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
