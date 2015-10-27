/**
  ******************************************************************************
  * @file    stm32l0xx_hal_spi.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    06-February-2015
  * @brief   Header file of SPI HAL module.
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
#ifndef __STM32L0xx_HAL_SPI_H
#define __STM32L0xx_HAL_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"  

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SPI_Exported_Types SPI Exported Types
  * @{
  */

/** 
  * @brief  SPI Configuration Structure definition  
  */
typedef struct
{
  uint32_t Mode;               /*!< Specifies the SPI operating mode.
                                    This parameter can be a value of @ref SPI_mode */

  uint32_t Direction;          /*!< Specifies the SPI Directional mode state.
                                    This parameter can be a value of @ref SPI_Direction_mode */

  uint32_t DataSize;           /*!< Specifies the SPI data size.
                                    This parameter can be a value of @ref SPI_data_size */

  uint32_t CLKPolarity;        /*!< Specifies the serial clock steady state.
                                    This parameter can be a value of @ref SPI_Clock_Polarity */

  uint32_t CLKPhase;           /*!< Specifies the clock active edge for the bit capture.
                                    This parameter can be a value of @ref SPI_Clock_Phase */

  uint32_t NSS;                /*!< Specifies whether the NSS signal is managed by
                                    hardware (NSS pin) or by software using the SSI bit.
                                    This parameter can be a value of @ref SPI_Slave_Select_management */

  uint32_t BaudRatePrescaler;  /*!< Specifies the Baud Rate prescaler value which will be
                                    used to configure the transmit and receive SCK clock.
                                    This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                    @note The communication clock is derived from the master
                                    clock. The slave clock does not need to be set */

  uint32_t FirstBit;           /*!< Specifies whether data transfers start from MSB or LSB bit.
                                    This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint32_t TIMode;             /*!< Specifies if the TI mode is enabled or not.
                                    This parameter can be a value of @ref SPI_TI_mode */

  uint32_t CRCCalculation;     /*!< Specifies if the CRC calculation is enabled or not.
                                    This parameter can be a value of @ref SPI_CRC_Calculation */

  uint32_t CRCPolynomial;      /*!< Specifies the polynomial used for the CRC calculation.
                                    This parameter must be a number between Min_Data = 0 and Max_Data = 65535 */

}SPI_InitTypeDef;

/**
  * @brief  HAL SPI State structure definition
  */
typedef enum
{
  HAL_SPI_STATE_RESET      = 0x00,  /*!< SPI not yet initialized or disabled                */
  HAL_SPI_STATE_READY      = 0x01,  /*!< SPI initialized and ready for use                  */
  HAL_SPI_STATE_BUSY       = 0x02,  /*!< SPI process is ongoing                             */
  HAL_SPI_STATE_BUSY_TX    = 0x12,  /*!< Data Transmission process is ongoing               */
  HAL_SPI_STATE_BUSY_RX    = 0x22,  /*!< Data Reception process is ongoing                  */
  HAL_SPI_STATE_BUSY_TX_RX = 0x32,  /*!< Data Transmission and Reception process is ongoing */
  HAL_SPI_STATE_ERROR      = 0x03   /*!< SPI error state                                    */
    
}HAL_SPI_StateTypeDef;

/** 
  * @brief  SPI handle Structure definition
  */
typedef struct __SPI_HandleTypeDef
{
  SPI_TypeDef                *Instance;    /*!< SPI registers base address */

  SPI_InitTypeDef            Init;         /*!< SPI communication parameters */

  uint8_t                    *pTxBuffPtr;  /*!< Pointer to SPI Tx transfer Buffer */

  uint16_t                   TxXferSize;   /*!< SPI Tx transfer size */
  
  uint16_t                   TxXferCount;  /*!< SPI Tx Transfer Counter */

  uint8_t                    *pRxBuffPtr;  /*!< Pointer to SPI Rx transfer Buffer */

  uint16_t                   RxXferSize;   /*!< SPI Rx transfer size */

  uint16_t                   RxXferCount;  /*!< SPI Rx Transfer Counter */

  DMA_HandleTypeDef          *hdmatx;      /*!< SPI Tx DMA handle parameters */

  DMA_HandleTypeDef          *hdmarx;      /*!< SPI Rx DMA handle parameters */

  void                       (*RxISR)(struct __SPI_HandleTypeDef * hspi); /*!< function pointer on Rx ISR */

  void                       (*TxISR)(struct __SPI_HandleTypeDef * hspi); /*!< function pointer on Tx ISR */

  HAL_LockTypeDef            Lock;         /*!< SPI locking object */

  __IO HAL_SPI_StateTypeDef  State;        /*!< SPI communication state */

  __IO  uint32_t             ErrorCode;    /*!< SPI Error code */

}SPI_HandleTypeDef;
/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants SPI Exported Constants
  * @{
  */

/**
  * @defgroup SPI_ErrorCode SPI Error Code
  * @{
  */
#define HAL_SPI_ERROR_NONE      ((uint32_t)0x00)    /*!< No error             */
#define HAL_SPI_ERROR_MODF      ((uint32_t)0x01)    /*!< MODF error           */
#define HAL_SPI_ERROR_CRC       ((uint32_t)0x02)    /*!< CRC error            */
#define HAL_SPI_ERROR_OVR       ((uint32_t)0x04)    /*!< OVR error            */
#define HAL_SPI_ERROR_FRE       ((uint32_t)0x08)    /*!< FRE error            */
#define HAL_SPI_ERROR_DMA       ((uint32_t)0x10)    /*!< DMA transfer error   */
#define HAL_SPI_ERROR_FLAG      ((uint32_t)0x20)     /*!< Flag: RXNE,TXE, BSY  */
/**
  * @}
  */

/** @defgroup SPI_mode SPI mode
  * @{
  */
#define SPI_MODE_SLAVE                  ((uint32_t)0x00000000)
#define SPI_MODE_MASTER                 (SPI_CR1_MSTR | SPI_CR1_SSI)

/**
  * @}
  */

/** @defgroup SPI_Direction_mode SPI Direction mode
  * @{
  */
#define SPI_DIRECTION_2LINES            ((uint32_t)0x00000000)
#define SPI_DIRECTION_2LINES_RXONLY     SPI_CR1_RXONLY
#define SPI_DIRECTION_1LINE             SPI_CR1_BIDIMODE

/**
  * @}
  */

/** @defgroup SPI_data_size SPI data size
  * @{
  */
#define SPI_DATASIZE_8BIT               ((uint32_t)0x00000000)
#define SPI_DATASIZE_16BIT              SPI_CR1_DFF

/**
  * @}
  */ 

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
  * @{
  */
#define SPI_POLARITY_LOW                ((uint32_t)0x00000000)
#define SPI_POLARITY_HIGH               SPI_CR1_CPOL

/**
  * @}
  */

/** @defgroup SPI_Clock_Phase SPI Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE                 ((uint32_t)0x00000000)
#define SPI_PHASE_2EDGE                 SPI_CR1_CPHA

/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management SPI Slave Select management
  * @{
  */
#define SPI_NSS_SOFT                    SPI_CR1_SSM
#define SPI_NSS_HARD_INPUT              ((uint32_t)0x00000000)
#define SPI_NSS_HARD_OUTPUT             ((uint32_t)(SPI_CR2_SSOE << 16))

/**
  * @}
  */ 

/** @defgroup SPI_BaudRate_Prescaler SPI BaudRate Prescaler
  * @{
  */
#define SPI_BAUDRATEPRESCALER_2         ((uint32_t)0x00000000)
#define SPI_BAUDRATEPRESCALER_4         ((uint32_t)SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_8         ((uint32_t)SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_16        ((uint32_t)SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_32        ((uint32_t)SPI_CR1_BR_2)
#define SPI_BAUDRATEPRESCALER_64        ((uint32_t)SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_128       ((uint32_t)SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_256       ((uint32_t)SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)

/**
  * @}
  */ 

/** @defgroup SPI_MSB_LSB_transmission SPI MSB LSB transmission
  * @{
  */
#define SPI_FIRSTBIT_MSB                ((uint32_t)0x00000000)
#define SPI_FIRSTBIT_LSB                SPI_CR1_LSBFIRST

/**
  * @}
  */

/** @defgroup SPI_TI_mode SPI TI mode
  * @{
  */
#define SPI_TIMODE_DISABLE             ((uint32_t)0x00000000)
#define SPI_TIMODE_ENABLE              SPI_CR2_FRF

/**
  * @}
  */

/** @defgroup SPI_CRC_Calculation SPI CRC Calculation
  * @{
  */
#define SPI_CRCCALCULATION_DISABLE     ((uint32_t)0x00000000)
#define SPI_CRCCALCULATION_ENABLE      SPI_CR1_CRCEN

/**
  * @}
  */

/** @defgroup SPI_Interrupt_configuration_definition SPI Interrupt configuration definition
  * @{
  */
#define SPI_IT_TXE                      SPI_CR2_TXEIE
#define SPI_IT_RXNE                     SPI_CR2_RXNEIE
#define SPI_IT_ERR                      SPI_CR2_ERRIE
/**
  * @}
  */

/** @defgroup SPI_Flag_definition SPI Flag definition
  * @{
  */
#define SPI_FLAG_RXNE                   SPI_SR_RXNE
#define SPI_FLAG_TXE                    SPI_SR_TXE
#define SPI_FLAG_CRCERR                 SPI_SR_CRCERR
#define SPI_FLAG_MODF                   SPI_SR_MODF
#define SPI_FLAG_OVR                    SPI_SR_OVR
#define SPI_FLAG_BSY                    SPI_SR_BSY
#define SPI_FLAG_FRE                    SPI_SR_FRE

/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup SPI_Exported_Macros SPI Exported Macros
  * @{
  */

/** @brief Reset SPI handle state
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */
#define __HAL_SPI_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SPI_STATE_RESET)

/** @brief  Enable the specified SPI interrupts.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @param  __INTERRUPT__: specifies the interrupt source to enable.
  *         This parameter can be one of the following values:
  *            @arg SPI_IT_TXE: Tx buffer empty interrupt enable
  *            @arg SPI_IT_RXNE: RX buffer not empty interrupt enable
  *            @arg SPI_IT_ERR: Error interrupt enable
  * @retval None
  */
#define __HAL_SPI_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))

/** @brief  Disable the specified SPI interrupts.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @param  __INTERRUPT__: specifies the interrupt source to disable.
  *         This parameter can be one of the following values:
  *            @arg SPI_IT_TXE: Tx buffer empty interrupt enable
  *            @arg SPI_IT_RXNE: RX buffer not empty interrupt enable
  *            @arg SPI_IT_ERR: Error interrupt enable
  * @retval None
  */
#define __HAL_SPI_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))

/** @brief  Check if the specified SPI interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @param  __INTERRUPT__: specifies the SPI interrupt source to check.
  *          This parameter can be one of the following values:
  *             @arg SPI_IT_TXE: Tx buffer empty interrupt enable
  *             @arg SPI_IT_RXNE: RX buffer not empty interrupt enable
  *             @arg SPI_IT_ERR: Error interrupt enable
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_SPI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR2 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Check whether the specified SPI flag is set or not.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_FLAG_RXNE: Receive buffer not empty flag
  *            @arg SPI_FLAG_TXE: Transmit buffer empty flag
  *            @arg SPI_FLAG_CRCERR: CRC error flag
  *            @arg SPI_FLAG_MODF: Mode fault flag
  *            @arg SPI_FLAG_OVR: Overrun flag
  *            @arg SPI_FLAG_BSY: Busy flag
  *            @arg SPI_FLAG_FRE: Frame format error flag  
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SPI_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the SPI CRCERR pending flag.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */
#define __HAL_SPI_CLEAR_CRCERRFLAG(__HANDLE__) ((__HANDLE__)->Instance->SR = ~(SPI_FLAG_CRCERR))

/** @brief  Clear the SPI MODF pending flag.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral. 
  * @retval None
  */                                            
#define __HAL_SPI_CLEAR_MODFFLAG(__HANDLE__)        \
   do{                                              \
     __IO uint32_t tmpreg;                          \
     tmpreg = (__HANDLE__)->Instance->SR;           \
     (__HANDLE__)->Instance->CR1 &= (~SPI_CR1_SPE); \
     UNUSED(tmpreg);                                \
   } while(0)

/** @brief  Clear the SPI OVR pending flag.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral. 
  * @retval None
  */
#define __HAL_SPI_CLEAR_OVRFLAG(__HANDLE__)         \
   do{                                              \
     __IO uint32_t tmpreg;                          \
     tmpreg = (__HANDLE__)->Instance->DR;           \
     tmpreg = (__HANDLE__)->Instance->SR;           \
     UNUSED(tmpreg);                                \
   } while(0)

/** @brief  Clear the SPI FRE pending flag.
  * @param  __HANDLE__: specifies the SPI handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */
#define __HAL_SPI_CLEAR_FREFLAG(__HANDLE__)         \
   do{                                              \
     __IO uint32_t tmpreg;                          \
     tmpreg = (__HANDLE__)->Instance->SR;           \
     UNUSED(tmpreg);                                \
   } while(0)

/** @brief  Enables the SPI.
  * @param  __HANDLE__: specifies the SPI Handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */                                                 
#define __HAL_SPI_ENABLE(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)
                                                 
/** @brief  Disables the SPI.
  * @param  __HANDLE__: specifies the SPI Handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */                                           
#define __HAL_SPI_DISABLE(__HANDLE__) CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)
/**
  * @}
  */


/* Private macros -----------------------------------------------------------*/
/** @defgroup SPI_Private_Macros SPI Private Macros
  * @{
  */

/** @brief  Checks if SPI Mode parameter is in allowed range.
  * @param  __MODE__: specifies the SPI Mode.
  *         This parameter can be a value of @ref SPI_mode
  * @retval None
  */
#define IS_SPI_MODE(__MODE__) (((__MODE__) == SPI_MODE_SLAVE) || ((__MODE__) == SPI_MODE_MASTER))

/** @brief  Checks if SPI Direction Mode parameter is in allowed range.
  * @param  __MODE__: specifies the SPI Direction Mode.
  *         This parameter can be a value of @ref SPI_Direction_mode
  * @retval None
  */
#define IS_SPI_DIRECTION_MODE(__MODE__) (((__MODE__) == SPI_DIRECTION_2LINES)        || \
                                         ((__MODE__) == SPI_DIRECTION_2LINES_RXONLY) || \
                                         ((__MODE__) == SPI_DIRECTION_1LINE))

/** @brief  Checks if SPI Direction Mode parameter is 1 or 2 lines.
  * @param  __MODE__: specifies the SPI Direction Mode.
  * @retval None
  */
#define IS_SPI_DIRECTION_2LINES_OR_1LINE(__MODE__) (((__MODE__) == SPI_DIRECTION_2LINES)  || \
                                                    ((__MODE__) == SPI_DIRECTION_1LINE))

/** @brief  Checks if SPI Direction Mode parameter is 2 lines.
  * @param  __MODE__: specifies the SPI Direction Mode.
  * @retval None
  */
#define IS_SPI_DIRECTION_2LINES(__MODE__) ((__MODE__) == SPI_DIRECTION_2LINES)

/** @brief  Checks if SPI Data Size parameter is in allowed range.
  * @param  __DATASIZE__: specifies the SPI Data Size.
  *         This parameter can be a value of @ref SPI_data_size
  * @retval None
  */
#define IS_SPI_DATASIZE(__DATASIZE__) (((__DATASIZE__) == SPI_DATASIZE_16BIT) || \
                                       ((__DATASIZE__) == SPI_DATASIZE_8BIT))

/** @brief  Checks if SPI Serial clock steady state parameter is in allowed range.
  * @param  __CPOL__: specifies the SPI serial clock steady state.
  *         This parameter can be a value of @ref SPI_Clock_Polarity
  * @retval None
  */
#define IS_SPI_CPOL(__CPOL__) (((__CPOL__) == SPI_POLARITY_LOW) || \
                               ((__CPOL__) == SPI_POLARITY_HIGH))

/** @brief  Checks if SPI Clock Phase parameter is in allowed range.
  * @param  __CPHA__: specifies the SPI Clock Phase.
  *         This parameter can be a value of @ref SPI_Clock_Phase
  * @retval None
  */
#define IS_SPI_CPHA(__CPHA__) (((__CPHA__) == SPI_PHASE_1EDGE) || \
                               ((__CPHA__) == SPI_PHASE_2EDGE))

/** @brief  Checks if SPI Slave select parameter is in allowed range.
  * @param  __NSS__: specifies the SPI Slave Slelect management parameter.
  *         This parameter can be a value of @ref SPI_Slave_Select_management
  * @retval None
  */
#define IS_SPI_NSS(__NSS__) (((__NSS__) == SPI_NSS_SOFT)       || \
                             ((__NSS__) == SPI_NSS_HARD_INPUT) || \
                             ((__NSS__) == SPI_NSS_HARD_OUTPUT))

/** @brief  Checks if SPI Baudrate prescaler parameter is in allowed range.
  * @param  __PRESCALER__: specifies the SPI Baudrate prescaler.
  *         This parameter can be a value of @ref SPI_BaudRate_Prescaler
  * @retval None
  */
#define IS_SPI_BAUDRATE_PRESCALER(__PRESCALER__) (((__PRESCALER__) == SPI_BAUDRATEPRESCALER_2)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_4)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_8)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_16)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_32)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_64)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_128) || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_256))

/** @brief  Checks if SPI MSB LSB transmission parameter is in allowed range.
  * @param  __BIT__: specifies the SPI MSB LSB transmission (whether data transfer starts from MSB or LSB bit).
  *         This parameter can be a value of @ref SPI_MSB_LSB_transmission
  * @retval None
  */
#define IS_SPI_FIRST_BIT(__BIT__) (((__BIT__) == SPI_FIRSTBIT_MSB) || \
                                   ((__BIT__) == SPI_FIRSTBIT_LSB))

/** @brief  Checks if SPI TI mode parameter is in allowed range.
  * @param  __MODE__: specifies the SPI TI mode.
  *         This parameter can be a value of @ref SPI_TI_mode
  * @retval None
  */
#define IS_SPI_TIMODE(__MODE__) (((__MODE__) == SPI_TIMODE_DISABLE) || \
                                 ((__MODE__) == SPI_TIMODE_ENABLE))
/** @brief  Checks if SPI CRC calculation enabled state is in allowed range.
  * @param  __CALCULATION__: specifies the SPI CRC calculation enable state.
  *         This parameter can be a value of @ref SPI_CRC_Calculation
  * @retval None
  */
#define IS_SPI_CRC_CALCULATION(__CALCULATION__) (((__CALCULATION__) == SPI_CRCCALCULATION_DISABLE) || \
                                                 ((__CALCULATION__) == SPI_CRCCALCULATION_ENABLE))

/** @brief  Checks if SPI polynomial value to be used for the CRC calculation, is in allowed range.
  * @param  __POLYNOMIAL__: specifies the SPI polynomial value to be used for the CRC calculation.
  *         This parameter must be a number between Min_Data = 0 and Max_Data = 65535 
  * @retval None
  */
#define IS_SPI_CRC_POLYNOMIAL(__POLYNOMIAL__) (((__POLYNOMIAL__) >= 0x1) && ((__POLYNOMIAL__) <= 0xFFFF))
/** @brief  Sets the SPI transmit-only mode.
  * @param  __HANDLE__: specifies the SPI Handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */
#define SPI_1LINE_TX(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_BIDIOE)

/** @brief  Sets the SPI receive-only mode.
  * @param  __HANDLE__: specifies the SPI Handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */               
#define SPI_1LINE_RX(__HANDLE__)  CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_BIDIOE) 

/** @brief  Resets the CRC calculation of the SPI.
  * @param  __HANDLE__: specifies the SPI Handle.
  *         This parameter can be SPIx where x: 1 or 2 to select the SPI peripheral.
  * @retval None
  */
#define SPI_RESET_CRC(__HANDLE__) do{CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_CRCEN);\
                                             SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_CRCEN);}while(0)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SPI_Exported_Functions
  * @{
  */

/* Initialization/de-initialization functions  **********************************/
/** @addtogroup SPI_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DeInit (SPI_HandleTypeDef *hspi);
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);
/**
  * @}
  */

/* I/O operation functions  *****************************************************/
/** @addtogroup SPI_Exported_Functions_Group2
  * @{
  */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi);

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
/**
  * @}
  */


/* Peripheral State and Control functions  **************************************/
/** @addtogroup SPI_Exported_Functions_Group3
  * @{
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(SPI_HandleTypeDef *hspi);
uint32_t HAL_SPI_GetError(SPI_HandleTypeDef *hspi);

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

#endif /* __STM32L0xx_HAL_SPI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

