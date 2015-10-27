/**
  ******************************************************************************
  * @file    stm32f1xx_hal_i2c.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of I2C HAL module.
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
#ifndef __STM32F1xx_HAL_I2C_H
#define __STM32F1xx_HAL_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */

/** @defgroup I2C_Configuration_Structure_definition I2C Configuration Structure definition
  * @brief  I2C Configuration Structure definition
  * @{
  */
typedef struct
{
  uint32_t ClockSpeed;       /*!< Specifies the clock frequency.
                                  This parameter must be set to a value lower than 400kHz */

  uint32_t DutyCycle;        /*!< Specifies the I2C fast mode duty cycle.
                                  This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

  uint32_t OwnAddress1;      /*!< Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;   /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
                                  This parameter can be a value of @ref I2C_addressing_mode */

  uint32_t DualAddressMode;  /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref I2C_dual_addressing_mode */

  uint32_t OwnAddress2;      /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */

  uint32_t GeneralCallMode;  /*!< Specifies if general call mode is selected.
                                  This parameter can be a value of @ref I2C_general_call_addressing_mode */

  uint32_t NoStretchMode;    /*!< Specifies if nostretch mode is selected.
                                  This parameter can be a value of @ref I2C_nostretch_mode */

}I2C_InitTypeDef;

/** 
  * @}
  */

/** @defgroup HAL_state_structure_definition HAL state structure definition
  * @brief  HAL State structure definition  
  * @{
  */ 

typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00,  /*!< I2C not yet initialized or disabled         */
  HAL_I2C_STATE_READY             = 0x01,  /*!< I2C initialized and ready for use           */
  HAL_I2C_STATE_BUSY              = 0x02,  /*!< I2C internal process is ongoing             */
  HAL_I2C_STATE_BUSY_TX           = 0x12,  /*!< Data Transmission process is ongoing        */
  HAL_I2C_STATE_BUSY_RX           = 0x22,  /*!< Data Reception process is ongoing           */
  HAL_I2C_STATE_MEM_BUSY_TX       = 0x32,  /*!< Memory Data Transmission process is ongoing */
  HAL_I2C_STATE_MEM_BUSY_RX       = 0x42,  /*!< Memory Data Reception process is ongoing    */
  HAL_I2C_STATE_TIMEOUT           = 0x03,  /*!< I2C timeout state                           */
  HAL_I2C_STATE_ERROR             = 0x04   /*!< I2C error state                             */

}HAL_I2C_StateTypeDef;

/** 
  * @}
  */

/** @defgroup I2C_handle_Structure_definition I2C handle Structure definition 
  * @brief  I2C handle Structure definition  
  * @{
  */
typedef struct
{
  I2C_TypeDef                *Instance;  /*!< I2C registers base address     */

  I2C_InitTypeDef            Init;       /*!< I2C communication parameters   */

  uint8_t                    *pBuffPtr;  /*!< Pointer to I2C transfer buffer */

  uint16_t                   XferSize;   /*!< I2C transfer size              */

  __IO uint16_t              XferCount;  /*!< I2C transfer counter           */

  DMA_HandleTypeDef          *hdmatx;    /*!< I2C Tx DMA handle parameters   */

  DMA_HandleTypeDef          *hdmarx;    /*!< I2C Rx DMA handle parameters   */

  HAL_LockTypeDef            Lock;       /*!< I2C locking object             */

  __IO HAL_I2C_StateTypeDef  State;      /*!< I2C communication state        */

  __IO uint32_t              ErrorCode;  /* I2C Error code                   */

}I2C_HandleTypeDef;
/**
  * @}
  */

/**
  * @}
  */  
/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */

/** @defgroup I2C_Error_Codes I2C Error Codes  
  * @{
  */ 
  
#define HAL_I2C_ERROR_NONE      ((uint32_t)0x00)    /*!< No error             */
#define HAL_I2C_ERROR_BERR      ((uint32_t)0x01)    /*!< BERR error           */
#define HAL_I2C_ERROR_ARLO      ((uint32_t)0x02)    /*!< ARLO error           */
#define HAL_I2C_ERROR_AF        ((uint32_t)0x04)    /*!< AF error             */
#define HAL_I2C_ERROR_OVR       ((uint32_t)0x08)    /*!< OVR error            */
#define HAL_I2C_ERROR_DMA       ((uint32_t)0x10)    /*!< DMA transfer error   */
#define HAL_I2C_ERROR_TIMEOUT   ((uint32_t)0x20)     /*!< Timeout error        */

/** 
  * @}
  */



/** @defgroup I2C_duty_cycle_in_fast_mode I2C Duty Cycle
  * @{
  */
#define I2C_DUTYCYCLE_2                 ((uint32_t)0x00000000)
#define I2C_DUTYCYCLE_16_9              I2C_CCR_DUTY
/**
  * @}
  */

/** @defgroup I2C_addressing_mode I2C addressing mode
  * @{
  */
#define I2C_ADDRESSINGMODE_7BIT         ((uint32_t)0x00004000)
#define I2C_ADDRESSINGMODE_10BIT        (I2C_OAR1_ADDMODE | ((uint32_t)0x00004000))
/**
  * @}
  */

/** @defgroup I2C_dual_addressing_mode I2C dual addressing mode
  * @{
  */
#define I2C_DUALADDRESS_DISABLE         ((uint32_t)0x00000000)
#define I2C_DUALADDRESS_ENABLE          I2C_OAR2_ENDUAL
/**
  * @}
  */

/** @defgroup I2C_general_call_addressing_mode I2C general call addressing mode
  * @{
  */
#define I2C_GENERALCALL_DISABLE         ((uint32_t)0x00000000)
#define I2C_GENERALCALL_ENABLE          I2C_CR1_ENGC
/**
  * @}
  */

/** @defgroup I2C_nostretch_mode I2C nostretch mode
  * @{
  */
#define I2C_NOSTRETCH_DISABLE           ((uint32_t)0x00000000)
#define I2C_NOSTRETCH_ENABLE            I2C_CR1_NOSTRETCH
/**
  * @}
  */

/** @defgroup I2C_Memory_Address_Size I2C Memory Address Size
  * @{
  */
#define I2C_MEMADD_SIZE_8BIT            ((uint32_t)0x00000001)
#define I2C_MEMADD_SIZE_16BIT           ((uint32_t)0x00000010)
/**
  * @}
  */

/** @defgroup I2C_Interrupt_configuration_definition I2C Interrupt configuration definition
  * @{
  */
#define I2C_IT_BUF                      I2C_CR2_ITBUFEN
#define I2C_IT_EVT                      I2C_CR2_ITEVTEN
#define I2C_IT_ERR                      I2C_CR2_ITERREN
/**
  * @}
  */

/** @defgroup I2C_Flag_definition I2C Flag definition
  * @brief I2C Interrupt definition
  *           - 0001XXXX  : Flag control mask for SR1 Register
  *           - 0010XXXX  : Flag control mask for SR2 Register
  * @{
  */
#define I2C_FLAG_SMBALERT               ((uint32_t)0x00018000)
#define I2C_FLAG_TIMEOUT                ((uint32_t)0x00014000)
#define I2C_FLAG_PECERR                 ((uint32_t)0x00011000)
#define I2C_FLAG_OVR                    ((uint32_t)0x00010800)
#define I2C_FLAG_AF                     ((uint32_t)0x00010400)
#define I2C_FLAG_ARLO                   ((uint32_t)0x00010200)
#define I2C_FLAG_BERR                   ((uint32_t)0x00010100)
#define I2C_FLAG_TXE                    ((uint32_t)0x00010080)
#define I2C_FLAG_RXNE                   ((uint32_t)0x00010040)
#define I2C_FLAG_STOPF                  ((uint32_t)0x00010010)
#define I2C_FLAG_ADD10                  ((uint32_t)0x00010008)
#define I2C_FLAG_BTF                    ((uint32_t)0x00010004)
#define I2C_FLAG_ADDR                   ((uint32_t)0x00010002)
#define I2C_FLAG_SB                     ((uint32_t)0x00010001)
#define I2C_FLAG_DUALF                  ((uint32_t)0x00100080)
#define I2C_FLAG_SMBHOST                ((uint32_t)0x00100040)
#define I2C_FLAG_SMBDEFAULT             ((uint32_t)0x00100020)
#define I2C_FLAG_GENCALL                ((uint32_t)0x00100010)
#define I2C_FLAG_TRA                    ((uint32_t)0x00100004)
#define I2C_FLAG_BUSY                   ((uint32_t)0x00100002)
#define I2C_FLAG_MSL                    ((uint32_t)0x00100001)
#define I2C_FLAG_MASK                   ((uint32_t)0x0000FFFF)
/**
  * @}
  */

/**
  * @}
  */ 
  
/* Exported macros -----------------------------------------------------------*/

/** @defgroup I2C_Exported_Macros I2C Exported Macros
  * @{
  */

/** @brief Reset I2C handle state
  * @param  __HANDLE__: specifies the I2C Handle.
  * @retval None
  */
#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_I2C_STATE_RESET)

/** @brief  Enable the specified I2C interrupts.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @param  __INTERRUPT__: specifies the interrupt source to enable.
  *         This parameter can be one of the following values:
  *            @arg I2C_IT_BUF: Buffer interrupt enable
  *            @arg I2C_IT_EVT: Event interrupt enable
  *            @arg I2C_IT_ERR: Error interrupt enable
  * @retval None
  */
#define __HAL_I2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (SET_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__)))

/** @brief  Disable the specified I2C interrupts.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @param  __INTERRUPT__: specifies the interrupt source to disable.
  *         This parameter can be one of the following values:
  *            @arg I2C_IT_BUF: Buffer interrupt enable
  *            @arg I2C_IT_EVT: Event interrupt enable
  *            @arg I2C_IT_ERR: Error interrupt enable
  * @retval None
  */
#define __HAL_I2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (CLEAR_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__)))

/** @brief  Checks if the specified I2C interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @param  __INTERRUPT__: specifies the I2C interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg I2C_IT_BUF: Buffer interrupt enable
  *            @arg I2C_IT_EVT: Event interrupt enable
  *            @arg I2C_IT_ERR: Error interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_I2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR2 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified I2C flag is set or not.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg I2C_FLAG_SMBALERT: SMBus Alert flag
  *            @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *            @arg I2C_FLAG_PECERR: PEC error in reception flag
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag
  *            @arg I2C_FLAG_BERR: Bus error flag
  *            @arg I2C_FLAG_TXE: Data register empty flag
  *            @arg I2C_FLAG_RXNE: Data register not empty flag
  *            @arg I2C_FLAG_STOPF: Stop detection flag
  *            @arg I2C_FLAG_ADD10: 10-bit header sent flag
  *            @arg I2C_FLAG_BTF: Byte transfer finished flag
  *            @arg I2C_FLAG_ADDR: Address sent flag
  *                                Address matched flag
  *            @arg I2C_FLAG_SB: Start bit flag
  *            @arg I2C_FLAG_DUALF: Dual flag
  *            @arg I2C_FLAG_SMBHOST: SMBus host header
  *            @arg I2C_FLAG_SMBDEFAULT: SMBus default header
  *            @arg I2C_FLAG_GENCALL: General call header flag
  *            @arg I2C_FLAG_TRA: Transmitter/Receiver flag
  *            @arg I2C_FLAG_BUSY: Bus busy flag
  *            @arg I2C_FLAG_MSL: Master/Slave flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_I2C_GET_FLAG(__HANDLE__, __FLAG__) ((((uint8_t)((__FLAG__) >> 16)) == 0x01)?((((__HANDLE__)->Instance->SR1) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)): \
                                                 ((((__HANDLE__)->Instance->SR2) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)))

/** @brief  Clears the I2C pending flags which are cleared by writing 0 in a specific bit.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @param  __FLAG__: specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg I2C_FLAG_SMBALERT: SMBus Alert flag
  *            @arg I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
  *            @arg I2C_FLAG_PECERR: PEC error in reception flag
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *            @arg I2C_FLAG_BERR: Bus error flag
  * @retval None
  */
#define __HAL_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__)  (__HANDLE__)->Instance->SR1 = (((__HANDLE__)->Instance->SR1) & (~((__FLAG__) & I2C_FLAG_MASK)))

/** @brief  Clears the I2C ADDR pending flag.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @retval None
  */
#define __HAL_I2C_CLEAR_ADDRFLAG(__HANDLE__) \
 do{                                         \
    __IO uint32_t tmpreg;                    \
    tmpreg = (__HANDLE__)->Instance->SR1;    \
    tmpreg = (__HANDLE__)->Instance->SR2;    \
    UNUSED(tmpreg);                          \
}while(0)

/** @brief  Clears the I2C STOPF pending flag.
  * @param  __HANDLE__: specifies the I2C Handle.
  * @retval None
  */
#define __HAL_I2C_CLEAR_STOPFLAG(__HANDLE__)               \
do{                                                        \
    __IO uint32_t tmpreg;                                  \
    tmpreg = (__HANDLE__)->Instance->SR1;                  \
    tmpreg = (__HANDLE__)->Instance->CR1 |= I2C_CR1_PE;    \
    UNUSED(tmpreg);                                        \
}while(0)  

/** @brief  Enable the specified I2C peripheral.
  * @param  __HANDLE__: specifies the I2C Handle. 
  * @retval None
  */
#define __HAL_I2C_ENABLE(__HANDLE__)                             (SET_BIT((__HANDLE__)->Instance->CR1,  I2C_CR1_PE))

/** @brief  Disable the specified I2C peripheral.
  * @param  __HANDLE__: specifies the I2C Handle. 
  * @retval None
  */
#define __HAL_I2C_DISABLE(__HANDLE__)                            (CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE))

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2C_Exported_Functions
  * @{
  */

/** @addtogroup I2C_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
  
/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit (I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

/**
  * @}
  */ 

/** @addtogroup I2C_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */
   
/* IO operation functions  ****************************************************/

 /******* Blocking mode: Polling */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
   
 /******* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
 
 /******* Non-Blocking mode: DMA */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
/**
  * @}
  */ 

/** @addtogroup IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
 * @{
 */   
/******* I2C IRQHandler and Callbacks used in non blocking modes (Interrupt and DMA) */
void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);

/**
  * @}
  */ 

  
/** @addtogroup I2C_Exported_Functions_Group3 Peripheral State and Errors functions
  * @{
  */
  
/* Peripheral State and Errors functions  *************************************/
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
uint32_t             HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);

/**
  * @}
  */

/**
  * @}
  */ 

/* Private constants ---------------------------------------------------------*/
/** @defgroup I2C_Private_Constants I2C Private Constants
  * @{
  */
#define I2C_STANDARD_MODE_MAX_CLK ((uint32_t)100000) /* Standard Clock Up to 100kHz */
#define I2C_FAST_MODE_MAX_CLK     ((uint32_t)400000) /* Fast Clock up to 400kHz */
/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2C_Private_Macro I2C Private Macros
  * @{
  */
#define IS_I2C_ADDRESSING_MODE(ADDRESS) (((ADDRESS) == I2C_ADDRESSINGMODE_7BIT) || \
                                         ((ADDRESS) == I2C_ADDRESSINGMODE_10BIT))

#define IS_I2C_DUAL_ADDRESS(ADDRESS) (((ADDRESS) == I2C_DUALADDRESS_DISABLE) || \
                                      ((ADDRESS) == I2C_DUALADDRESS_ENABLE))

#define IS_I2C_GENERAL_CALL(CALL) (((CALL) == I2C_GENERALCALL_DISABLE) || \
                                   ((CALL) == I2C_GENERALCALL_ENABLE))

#define IS_I2C_MEMADD_SIZE(SIZE) (((SIZE) == I2C_MEMADD_SIZE_8BIT) || \
                                  ((SIZE) == I2C_MEMADD_SIZE_16BIT))

#define IS_I2C_NO_STRETCH(STRETCH) (((STRETCH) == I2C_NOSTRETCH_DISABLE) || \
                                    ((STRETCH) == I2C_NOSTRETCH_ENABLE))

#define IS_I2C_OWN_ADDRESS1(ADDRESS1) (((ADDRESS1) & (uint32_t)(0xFFFFFC00)) == 0)

#define IS_I2C_OWN_ADDRESS2(ADDRESS2) (((ADDRESS2) & (uint32_t)(0xFFFFFF01)) == 0)

#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) > 0) && ((SPEED) <= I2C_FAST_MODE_MAX_CLK))

#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DUTYCYCLE_2) || \
                                  ((CYCLE) == I2C_DUTYCYCLE_16_9))

#define I2C_FREQ_RANGE(__PCLK__)                 ((__PCLK__)/1000000)
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__)  (((__SPEED__) <= I2C_STANDARD_MODE_MAX_CLK) ? ((__FREQRANGE__) + 1) : ((((__FREQRANGE__) * 300) / 1000) + 1))

#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__)            (((((__PCLK__)/((__SPEED__) << 1)) & I2C_CCR_CCR) < 4)? 4:((__PCLK__) / ((__SPEED__) << 1)))
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) (((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? ((__PCLK__) / ((__SPEED__) * 3)) : (((__PCLK__) / ((__SPEED__) * 25)) | I2C_DUTYCYCLE_16_9))
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__)      (((__SPEED__) <= 100000)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & I2C_CCR_CCR) == 0)? 1 : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | I2C_CCR_FS))

#define I2C_MEM_ADD_MSB(__ADDRESS__)             ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0xFF00))) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)             ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))
                                              
#define I2C_7BIT_ADD_WRITE(__ADDRESS__)          ((uint8_t)((__ADDRESS__) & (~I2C_OAR1_ADD0)))
#define I2C_7BIT_ADD_READ(__ADDRESS__)           ((uint8_t)((__ADDRESS__) | I2C_OAR1_ADD0))

#define I2C_10BIT_ADDRESS(__ADDRESS__)           ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))
#define I2C_10BIT_HEADER_WRITE(__ADDRESS__)      ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF0))))
#define I2C_10BIT_HEADER_READ(__ADDRESS__)       ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF1))))
/**
  * @}
  */ 

/* Private Fonctions ---------------------------------------------------------*/
/** @defgroup I2C_Private_Functions I2C Private Functions
  * @{
  */
/* Private functions are defined in stm32f1xx_hal_i2c.c file */
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


#endif /* __STM32F1xx_HAL_I2C_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
