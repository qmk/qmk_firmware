/**
  ******************************************************************************
  * @file    stm32f1xx_hal_usart.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of USART HAL module.
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
#ifndef __STM32F1xx_HAL_USART_H
#define __STM32F1xx_HAL_USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup USART_Exported_Types USART Exported Types
  * @{
  */ 


/** 
  * @brief USART Init Structure definition
  */ 
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the Usart communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (16 * (husart->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint32_t Parity;                   /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref USART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint32_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */

  uint32_t CLKPolarity;               /*!< Specifies the steady state of the serial clock.
                                           This parameter can be a value of @ref USART_Clock_Polarity */

  uint32_t CLKPhase;                  /*!< Specifies the clock transition on which the bit capture is made.
                                           This parameter can be a value of @ref USART_Clock_Phase */

  uint32_t CLKLastBit;                /*!< Specifies whether the clock pulse corresponding to the last transmitted
                                           data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                                           This parameter can be a value of @ref USART_Last_Bit */
}USART_InitTypeDef;

/** 
  * @brief HAL State structures definition
  */ 
typedef enum
{
  HAL_USART_STATE_RESET             = 0x00,    /*!< Peripheral is not initialized   */
  HAL_USART_STATE_READY             = 0x01,    /*!< Peripheral Initialized and ready for use */
  HAL_USART_STATE_BUSY              = 0x02,    /*!< an internal process is ongoing */   
  HAL_USART_STATE_BUSY_TX           = 0x12,    /*!< Data Transmission process is ongoing */ 
  HAL_USART_STATE_BUSY_RX           = 0x22,    /*!< Data Reception process is ongoing */
  HAL_USART_STATE_BUSY_TX_RX        = 0x32,    /*!< Data Transmission Reception process is ongoing */
  HAL_USART_STATE_TIMEOUT           = 0x03,    /*!< Timeout state */
  HAL_USART_STATE_ERROR             = 0x04     /*!< Error */
}HAL_USART_StateTypeDef;


/** 
  * @brief  USART handle Structure definition  
  */  
typedef struct
{
  USART_TypeDef                 *Instance;        /*!< USART registers base address        */
  
  USART_InitTypeDef              Init;            /*!< Usart communication parameters      */
  
  uint8_t                       *pTxBuffPtr;      /*!< Pointer to Usart Tx transfer Buffer */
  
  uint16_t                       TxXferSize;      /*!< Usart Tx Transfer size              */
  
  __IO uint16_t                  TxXferCount;     /*!< Usart Tx Transfer Counter           */
  
  uint8_t                       *pRxBuffPtr;      /*!< Pointer to Usart Rx transfer Buffer */
  
  uint16_t                       RxXferSize;      /*!< Usart Rx Transfer size              */
 
  __IO uint16_t                  RxXferCount;     /*!< Usart Rx Transfer Counter           */  
  
  DMA_HandleTypeDef             *hdmatx;          /*!< Usart Tx DMA Handle parameters      */
    
  DMA_HandleTypeDef             *hdmarx;          /*!< Usart Rx DMA Handle parameters      */
  
  HAL_LockTypeDef                Lock;            /*!< Locking object                      */
  
  __IO HAL_USART_StateTypeDef    State;           /*!< Usart communication state           */
  
  __IO uint32_t                  ErrorCode;       /*!< USART Error code                    */
  
}USART_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup USART_Exported_Constants USART Exported constants
  * @{
  */

/** @defgroup USART_Error_Codes USART Error Codes
  * @{
  */
#define HAL_USART_ERROR_NONE      ((uint32_t)0x00)    /*!< No error            */
#define HAL_USART_ERROR_PE        ((uint32_t)0x01)    /*!< Parity error        */
#define HAL_USART_ERROR_NE        ((uint32_t)0x02)    /*!< Noise error         */
#define HAL_USART_ERROR_FE        ((uint32_t)0x04)    /*!< frame error         */
#define HAL_USART_ERROR_ORE       ((uint32_t)0x08)    /*!< Overrun error       */
#define HAL_USART_ERROR_DMA       ((uint32_t)0x10)     /*!< DMA transfer error  */
/**
  * @}
  */

/** @defgroup USART_Word_Length USART Word Length
  * @{
  */
#define USART_WORDLENGTH_8B             ((uint32_t)0x00000000)
#define USART_WORDLENGTH_9B             ((uint32_t)USART_CR1_M)
/**
  * @}
  */

/** @defgroup USART_Stop_Bits USART Number of Stop Bits
  * @{
  */
#define USART_STOPBITS_1                ((uint32_t)0x00000000)
#define USART_STOPBITS_0_5              ((uint32_t)USART_CR2_STOP_0)
#define USART_STOPBITS_2                ((uint32_t)USART_CR2_STOP_1)
#define USART_STOPBITS_1_5              ((uint32_t)(USART_CR2_STOP_0 | USART_CR2_STOP_1))
/**
  * @}
  */ 

/** @defgroup USART_Parity USART Parity
  * @{
  */ 
#define USART_PARITY_NONE               ((uint32_t)0x00000000)
#define USART_PARITY_EVEN               ((uint32_t)USART_CR1_PCE)
#define USART_PARITY_ODD                ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 
/**
  * @}
  */ 

/** @defgroup USART_Mode USART Mode
  * @{
  */ 
#define USART_MODE_RX                   ((uint32_t)USART_CR1_RE)
#define USART_MODE_TX                   ((uint32_t)USART_CR1_TE)
#define USART_MODE_TX_RX                ((uint32_t)(USART_CR1_TE |USART_CR1_RE))

/**
  * @}
  */
    
/** @defgroup USART_Clock USART Clock
  * @{
  */ 
#define USART_CLOCK_DISABLE             ((uint32_t)0x00000000)
#define USART_CLOCK_ENABLE              ((uint32_t)USART_CR2_CLKEN)
/**
  * @}
  */ 

/** @defgroup USART_Clock_Polarity USART Clock Polarity
  * @{
  */
#define USART_POLARITY_LOW              ((uint32_t)0x00000000)
#define USART_POLARITY_HIGH             ((uint32_t)USART_CR2_CPOL)
/**
  * @}
  */ 

/** @defgroup USART_Clock_Phase USART Clock Phase
  * @{
  */
#define USART_PHASE_1EDGE               ((uint32_t)0x00000000)
#define USART_PHASE_2EDGE               ((uint32_t)USART_CR2_CPHA)
/**
  * @}
  */

/** @defgroup USART_Last_Bit USART Last Bit
  * @{
  */
#define USART_LASTBIT_DISABLE           ((uint32_t)0x00000000)
#define USART_LASTBIT_ENABLE            ((uint32_t)USART_CR2_LBCL)
/**
  * @}
  */

/** @defgroup USART_NACK_State USART NACK State
  * @{
  */
#define USART_NACK_ENABLE               ((uint32_t)USART_CR3_NACK)
#define USART_NACK_DISABLE              ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup USART_Flags USART Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the SR register
  * @{
  */

#define USART_FLAG_CTS                  ((uint32_t)USART_SR_CTS)
#define USART_FLAG_LBD                  ((uint32_t)USART_SR_LBD)
#define USART_FLAG_TXE                  ((uint32_t)USART_SR_TXE)
#define USART_FLAG_TC                   ((uint32_t)USART_SR_TC)
#define USART_FLAG_RXNE                 ((uint32_t)USART_SR_RXNE)
#define USART_FLAG_IDLE                 ((uint32_t)USART_SR_IDLE)
#define USART_FLAG_ORE                  ((uint32_t)USART_SR_ORE)
#define USART_FLAG_NE                   ((uint32_t)USART_SR_NE)
#define USART_FLAG_FE                   ((uint32_t)USART_SR_FE)
#define USART_FLAG_PE                   ((uint32_t)USART_SR_PE)
/**
  * @}
  */

/** @defgroup USART_Interrupt_definition USART Interrupts Definition
  *        Elements values convention: 0xY000XXXX
  *           - XXXX  : Interrupt mask (16 bits) in the Y register
  *           - Y  : Interrupt source register (4bits)
  *                 - 0001: CR1 register
  *                 - 0010: CR2 register
  *                 - 0011: CR3 register
  *
  * @{
  */

#define USART_IT_PE                     ((uint32_t)(USART_CR1_REG_INDEX << 28 | USART_CR1_PEIE))
#define USART_IT_TXE                    ((uint32_t)(USART_CR1_REG_INDEX << 28 | USART_CR1_TXEIE))
#define USART_IT_TC                     ((uint32_t)(USART_CR1_REG_INDEX << 28 | USART_CR1_TCIE))
#define USART_IT_RXNE                   ((uint32_t)(USART_CR1_REG_INDEX << 28 | USART_CR1_RXNEIE))
#define USART_IT_IDLE                   ((uint32_t)(USART_CR1_REG_INDEX << 28 | USART_CR1_IDLEIE))

#define USART_IT_LBD                    ((uint32_t)(USART_CR2_REG_INDEX << 28 | USART_CR2_LBDIE))

#define USART_IT_CTS                    ((uint32_t)(USART_CR3_REG_INDEX << 28 | USART_CR3_CTSIE))
#define USART_IT_ERR                    ((uint32_t)(USART_CR3_REG_INDEX << 28 | USART_CR3_EIE))


/**
  * @}
  */

/**
  * @}
  */

    
/* Exported macro ------------------------------------------------------------*/
/** @defgroup USART_Exported_Macros USART Exported Macros
  * @{
  */


/** @brief Reset USART handle state
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_USART_STATE_RESET)

/** @brief  Check whether the specified USART flag is set or not.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg USART_FLAG_TXE:  Transmit data register empty flag
  *            @arg USART_FLAG_TC:   Transmission Complete flag
  *            @arg USART_FLAG_RXNE: Receive data register not empty flag
  *            @arg USART_FLAG_IDLE: Idle Line detection flag
  *            @arg USART_FLAG_ORE:  OverRun Error flag
  *            @arg USART_FLAG_NE:   Noise Error flag
  *            @arg USART_FLAG_FE:   Framing Error flag
  *            @arg USART_FLAG_PE:   Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */

#define __HAL_USART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->SR & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified USART pending flags.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg USART_FLAG_TC:   Transmission Complete flag.
  *            @arg USART_FLAG_RXNE: Receive data register not empty flag.
  *   
  * @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun 
  *          error) and IDLE (Idle line detected) flags are cleared by software 
  *          sequence: a read operation to USART_SR register followed by a read
  *          operation to USART_DR register.
  * @note   RXNE flag can be also cleared by a read to the USART_DR register.
  * @note   TC flag can be also cleared by software sequence: a read operation to 
  *          USART_SR register followed by a write operation to USART_DR register.
  * @note   TXE flag is cleared only by a write to the USART_DR register.
  *   
  * @retval None
  */
#define __HAL_USART_CLEAR_FLAG(__HANDLE__, __FLAG__)  ((__HANDLE__)->Instance->SR = ~(__FLAG__))

/** @brief  Clear the USART PE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_CLEAR_PEFLAG(__HANDLE__) \
do{                                          \
  __IO uint32_t tmpreg;                      \
  tmpreg = (__HANDLE__)->Instance->SR;       \
  tmpreg = (__HANDLE__)->Instance->DR;       \
  UNUSED(tmpreg);                            \
}while(0)


/** @brief  Clear the USART FE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_CLEAR_FEFLAG(__HANDLE__) __HAL_USART_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the USART NE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_CLEAR_NEFLAG(__HANDLE__) __HAL_USART_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the USART ORE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_CLEAR_OREFLAG(__HANDLE__) __HAL_USART_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Clear the USART IDLE pending flag.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */
#define __HAL_USART_CLEAR_IDLEFLAG(__HANDLE__) __HAL_USART_CLEAR_PEFLAG(__HANDLE__)

/** @brief  Enable the specified Usart interrupts.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @param  __INTERRUPT__: specifies the USART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg USART_IT_TC:   Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_PE:   Parity Error interrupt
  *            @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_USART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((((__INTERRUPT__) >> 28) == USART_CR1_REG_INDEX)? ((__HANDLE__)->Instance->CR1 |= ((__INTERRUPT__) & USART_IT_MASK)): \
                                                            (((__INTERRUPT__) >> 28) == USART_CR2_REG_INDEX)? ((__HANDLE__)->Instance->CR2 |=  ((__INTERRUPT__) & USART_IT_MASK)): \
                                                            ((__HANDLE__)->Instance->CR3 |= ((__INTERRUPT__) & USART_IT_MASK)))


/** @brief  Disable the specified Usart interrupts.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @param  __INTERRUPT__: specifies the USART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg USART_IT_TC:   Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_PE:   Parity Error interrupt
  *            @arg USART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_USART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((((__INTERRUPT__) >> 28) == USART_CR1_REG_INDEX)? ((__HANDLE__)->Instance->CR1 &= ~((__INTERRUPT__) & USART_IT_MASK)): \
                                                            (((__INTERRUPT__) >> 28) == USART_CR2_REG_INDEX)? ((__HANDLE__)->Instance->CR2 &= ~((__INTERRUPT__) & USART_IT_MASK)): \
                                                            ((__HANDLE__)->Instance->CR3 &= ~ ((__INTERRUPT__) & USART_IT_MASK)))


    
/** @brief  Check whether the specified Usart interrupt has occurred or not.
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @param  __IT__: specifies the USART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg USART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg USART_IT_TC:  Transmission complete interrupt
  *            @arg USART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg USART_IT_IDLE: Idle line detection interrupt
  *            @arg USART_IT_ERR: Error interrupt
  *            @arg USART_IT_PE: Parity Error interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_USART_GET_IT_SOURCE(__HANDLE__, __IT__) (((((__IT__) >> 28) == USART_CR1_REG_INDEX)? (__HANDLE__)->Instance->CR1:(((((uint32_t)(__IT__)) >> 28) == USART_CR2_REG_INDEX)? \
                                                      (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & (((uint32_t)(__IT__)) & USART_IT_MASK))

/** @brief  Enable USART
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */ 
#define __HAL_USART_ENABLE(__HANDLE__)               SET_BIT((__HANDLE__)->Instance->CR1,(USART_CR1_UE)) 

/** @brief  Disable USART
  * @param  __HANDLE__: specifies the USART Handle.
  *         USART Handle selects the USARTx peripheral (USART availability and x value depending on device).
  * @retval None
  */ 
#define __HAL_USART_DISABLE(__HANDLE__)              CLEAR_BIT((__HANDLE__)->Instance->CR1,(USART_CR1_UE)) 
 

/**
  * @}
  */


/* Private macros --------------------------------------------------------*/
/** @defgroup USART_Private_Macros   USART Private Macros
  * @{
  */

#define USART_CR1_REG_INDEX             1    
#define USART_CR2_REG_INDEX             2    
#define USART_CR3_REG_INDEX             3    

#define USART_DIV(__PCLK__, __BAUD__)                (((__PCLK__)*25)/(4*(__BAUD__)))
#define USART_DIVMANT(__PCLK__, __BAUD__)            (USART_DIV((__PCLK__), (__BAUD__))/100)
#define USART_DIVFRAQ(__PCLK__, __BAUD__)            (((USART_DIV((__PCLK__), (__BAUD__)) - (USART_DIVMANT((__PCLK__), (__BAUD__)) * 100)) * 16 + 50) / 100)
#define USART_BRR(__PCLK__, __BAUD__)                ((USART_DIVMANT((__PCLK__), (__BAUD__)) << 4)|(USART_DIVFRAQ((__PCLK__), (__BAUD__)) & 0x0F))

/** Check USART Baud rate
  *      __BAUDRATE__: Baudrate specified by the user
  *                    The maximum Baud Rate is derived from the maximum clock on APB (i.e. 72 MHz) 
  *                    divided by the smallest oversampling used on the USART (i.e. 16) 
  * return : TRUE or FALSE
  */ 
#define IS_USART_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 4500001)

#define IS_USART_WORD_LENGTH(LENGTH)    (((LENGTH) == USART_WORDLENGTH_8B) || \
                                         ((LENGTH) == USART_WORDLENGTH_9B))

#define IS_USART_STOPBITS(STOPBITS)     (((STOPBITS) == USART_STOPBITS_1) || \
                                         ((STOPBITS) == USART_STOPBITS_0_5) || \
                                         ((STOPBITS) == USART_STOPBITS_1_5) || \
                                         ((STOPBITS) == USART_STOPBITS_2))

#define IS_USART_PARITY(PARITY)         (((PARITY) == USART_PARITY_NONE) || \
                                         ((PARITY) == USART_PARITY_EVEN) || \
                                         ((PARITY) == USART_PARITY_ODD))

#define IS_USART_MODE(MODE)             ((((MODE) & (~((uint32_t)USART_MODE_TX_RX))) == 0x00) && ((MODE) != (uint32_t)0x00000000))

#define IS_USART_CLOCK(CLOCK)           (((CLOCK) == USART_CLOCK_DISABLE) || \
                                         ((CLOCK) == USART_CLOCK_ENABLE))

#define IS_USART_POLARITY(CPOL)         (((CPOL) == USART_POLARITY_LOW) || ((CPOL) == USART_POLARITY_HIGH))

#define IS_USART_PHASE(CPHA)            (((CPHA) == USART_PHASE_1EDGE) || ((CPHA) == USART_PHASE_2EDGE))

#define IS_USART_LASTBIT(LASTBIT)       (((LASTBIT) == USART_LASTBIT_DISABLE) || \
                                         ((LASTBIT) == USART_LASTBIT_ENABLE))

#define IS_USART_NACK_STATE(NACK)       (((NACK) == USART_NACK_ENABLE) || \
                                         ((NACK) == USART_NACK_DISABLE))

/** USART interruptions flag mask
  * 
  */ 
#define USART_IT_MASK  ((uint32_t) USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE | \
                                   USART_CR1_IDLEIE | USART_CR2_LBDIE | USART_CR3_CTSIE | USART_CR3_EIE )

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @addtogroup USART_Exported_Functions USART Exported Functions
  * @{
  */
  
/** @addtogroup USART_Exported_Functions_Group1 Initialization and de-initialization functions 
  * @{
  */

/* Initialization and de-initialization functions  ******************************/
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DeInit(USART_HandleTypeDef *husart);
void HAL_USART_MspInit(USART_HandleTypeDef *husart);
void HAL_USART_MspDeInit(USART_HandleTypeDef *husart);

/**
  * @}
  */

/** @addtogroup USART_Exported_Functions_Group2 IO operation functions 
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_Receive(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_TransmitReceive(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_USART_Transmit_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_Receive_IT(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_TransmitReceive_IT(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData,  uint16_t Size);
HAL_StatusTypeDef HAL_USART_Transmit_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_Receive_DMA(USART_HandleTypeDef *husart, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_TransmitReceive_DMA(USART_HandleTypeDef *husart, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_USART_DMAPause(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DMAResume(USART_HandleTypeDef *husart);
HAL_StatusTypeDef HAL_USART_DMAStop(USART_HandleTypeDef *husart);
void HAL_USART_IRQHandler(USART_HandleTypeDef *husart);
void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_TxHalfCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_RxHalfCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *husart);
void HAL_USART_ErrorCallback(USART_HandleTypeDef *husart);

/**
  * @}
  */

/* Peripheral Control functions ***********************************************/

/** @addtogroup USART_Exported_Functions_Group3 Peripheral State and Errors functions 
  * @{
  */

/* Peripheral State and Error functions ***************************************/
HAL_USART_StateTypeDef HAL_USART_GetState(USART_HandleTypeDef *husart);
uint32_t               HAL_USART_GetError(USART_HandleTypeDef *husart);

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

#endif /* __STM32F1xx_HAL_USART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
