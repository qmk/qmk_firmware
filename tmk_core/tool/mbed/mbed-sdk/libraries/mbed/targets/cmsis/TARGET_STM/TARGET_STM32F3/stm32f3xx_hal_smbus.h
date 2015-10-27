/**
  ******************************************************************************
  * @file    stm32f3xx_hal_smbus.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    12-Sept-2014
  * @brief   Header file of SMBUS HAL module.
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
#ifndef __STM32F3xx_HAL_SMBUS_H
#define __STM32F3xx_HAL_SMBUS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal_def.h"  

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

/** @addtogroup SMBUS
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 
/** @defgroup SMBUS_Exported_Types SMBUS Exported Types
  * @{
  */

/** 
  * @brief  SMBUS Configuration Structure definition  
  */
typedef struct
{
  uint32_t Timing;                 /*!< Specifies the SMBUS_TIMINGR_register value.
                                     This parameter calculated by referring to SMBUS initialization 
                                            section in Reference manual */
  uint32_t AnalogFilter;           /*!< Specifies if Analog Filter is enable or not.
                                     This parameter can be a a value of @ref SMBUS_Analog_Filter */
    
  uint32_t OwnAddress1;            /*!< Specifies the first device own address.
                                     This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;         /*!< Specifies if 7-bit or 10-bit addressing mode for master is selected.
                                     This parameter can be a value of @ref SMBUS_addressing_mode */

  uint32_t DualAddressMode;        /*!< Specifies if dual addressing mode is selected.
                                     This parameter can be a value of @ref SMBUS_dual_addressing_mode */

  uint32_t OwnAddress2;            /*!< Specifies the second device own address if dual addressing mode is selected
                                     This parameter can be a 7-bit address. */

  uint32_t OwnAddress2Masks;       /*!< Specifies the acknoledge mask address second device own address if dual addressing mode is selected
                                     This parameter can be a value of @ref SMBUS_own_address2_masks. */

  uint32_t GeneralCallMode;        /*!< Specifies if general call mode is selected.
                                     This parameter can be a value of @ref SMBUS_general_call_addressing_mode. */

  uint32_t NoStretchMode;          /*!< Specifies if nostretch mode is selected.
                                     This parameter can be a value of @ref SMBUS_nostretch_mode */

  uint32_t PacketErrorCheckMode;   /*!< Specifies if Packet Error Check mode is selected.
                                     This parameter can be a value of @ref SMBUS_packet_error_check_mode */

  uint32_t PeripheralMode;         /*!< Specifies which mode of Periphal is selected.
                                     This parameter can be a value of @ref SMBUS_peripheral_mode */

  uint32_t SMBusTimeout;           /*!< Specifies the content of the 32 Bits SMBUS_TIMEOUT_register value.
  																		(Enable bits and different timeout values)
                                     This parameter calculated by referring to SMBUS initialization 
                                         section in Reference manual */
} SMBUS_InitTypeDef;

/** 
  * @brief  HAL State structures definition  
  */ 
typedef enum
{
  HAL_SMBUS_STATE_RESET           = 0x00,  /*!< SMBUS not yet initialized or disabled         */
  HAL_SMBUS_STATE_READY           = 0x01,  /*!< SMBUS initialized and ready for use           */
  HAL_SMBUS_STATE_BUSY            = 0x02,  /*!< SMBUS internal process is ongoing             */
  HAL_SMBUS_STATE_MASTER_BUSY_TX  = 0x12,  /*!< Master Data Transmission process is ongoing   */ 
  HAL_SMBUS_STATE_MASTER_BUSY_RX  = 0x22,  /*!< Master Data Reception process is ongoing      */
  HAL_SMBUS_STATE_SLAVE_BUSY_TX   = 0x32,  /*!< Slave Data Transmission process is ongoing    */ 
  HAL_SMBUS_STATE_SLAVE_BUSY_RX   = 0x42,  /*!< Slave Data Reception process is ongoing       */
  HAL_SMBUS_STATE_TIMEOUT         = 0x03,  /*!< Timeout state                                 */  
  HAL_SMBUS_STATE_ERROR           = 0x04,  /*!< Reception process is ongoing                  */      
  HAL_SMBUS_STATE_SLAVE_LISTEN    = 0x08,   /*!< Address Listen Mode is ongoing                */
  /* Aliases for inter STM32 series compatibility */
  HAL_SMBUS_STATE_LISTEN          = HAL_SMBUS_STATE_SLAVE_LISTEN 
}HAL_SMBUS_StateTypeDef;

/** 
  * @brief  HAL SMBUS Error Code structure definition  
  */ 
typedef enum
{
  HAL_SMBUS_ERROR_NONE        = 0x00,    /*!< No error             */
  HAL_SMBUS_ERROR_BERR        = 0x01,    /*!< BERR error           */
  HAL_SMBUS_ERROR_ARLO        = 0x02,    /*!< ARLO error           */   
  HAL_SMBUS_ERROR_ACKF        = 0x04,    /*!< ACKF error           */
  HAL_SMBUS_ERROR_OVR         = 0x08,    /*!< OVR error            */
  HAL_SMBUS_ERROR_HALTIMEOUT  = 0x10,    /*!< Timeout error        */
  HAL_SMBUS_ERROR_BUSTIMEOUT  = 0x20,    /*!< Bus Timeout error    */
  HAL_SMBUS_ERROR_ALERT       = 0x40,    /*!< Alert error          */
  HAL_SMBUS_ERROR_PECERR      = 0x80     /*!< PEC error            */

}HAL_SMBUS_ErrorTypeDef;

/** 
  * @brief  SMBUS handle Structure definition  
  */
typedef struct
{
  I2C_TypeDef                  *Instance;       /*!< SMBUS registers base address       */

  SMBUS_InitTypeDef            Init;            /*!< SMBUS communication parameters     */

  uint8_t                      *pBuffPtr;       /*!< Pointer to SMBUS transfer buffer   */

  uint16_t                     XferSize;        /*!< SMBUS transfer size                */

  __IO uint16_t                XferCount;       /*!< SMBUS transfer counter             */

  __IO uint32_t                XferOptions;     /*!< SMBUS transfer options             */

  __IO HAL_SMBUS_StateTypeDef  PreviousState;   /*!< SMBUS communication Previous tate  */

  HAL_LockTypeDef              Lock;            /*!< SMBUS locking object               */

  __IO HAL_SMBUS_StateTypeDef  State;           /*!< SMBUS communication state          */

  __IO HAL_SMBUS_ErrorTypeDef  ErrorCode;       /*!< SMBUS Error code                   */

}SMBUS_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup SMBUS_Exported_Constants SMBUS Exported Constants
  * @{
  */

/** @defgroup SMBUS_Analog_Filter SMBUS Analog Filter
  * @{
  */
#define SMBUS_ANALOGFILTER_ENABLED              ((uint32_t)0x00000000)
#define SMBUS_ANALOGFILTER_DISABLED             I2C_CR1_ANFOFF

#define IS_SMBUS_ANALOG_FILTER(FILTER)          (((FILTER) == SMBUS_ANALOGFILTER_ENABLED) || \
                                                 ((FILTER) == SMBUS_ANALOGFILTER_DISABLED))
/**
  * @}
  */

/** @defgroup SMBUS_addressing_mode SMBUS addressing mode
  * @{
  */
#define SMBUS_ADDRESSINGMODE_7BIT               ((uint32_t)0x00000001) 
#define SMBUS_ADDRESSINGMODE_10BIT              ((uint32_t)0x00000002)

#define IS_SMBUS_ADDRESSING_MODE(MODE)          (((MODE) == SMBUS_ADDRESSINGMODE_7BIT)  || \
                                                 ((MODE) == SMBUS_ADDRESSINGMODE_10BIT))
/**
  * @}
  */

/** @defgroup SMBUS_dual_addressing_mode SMBUS dual addressing mode
  * @{
  */

#define SMBUS_DUALADDRESS_DISABLED              ((uint32_t)0x00000000)
#define SMBUS_DUALADDRESS_ENABLED               I2C_OAR2_OA2EN

#define IS_SMBUS_DUAL_ADDRESS(ADDRESS)          (((ADDRESS) == SMBUS_DUALADDRESS_DISABLED) || \
                                                 ((ADDRESS) == SMBUS_DUALADDRESS_ENABLED))
/**
  * @}
  */

/** @defgroup SMBUS_own_address2_masks SMBUS own address2 masks
  * @{
  */

#define SMBUS_OA2_NOMASK                        ((uint8_t)0x00)
#define SMBUS_OA2_MASK01                        ((uint8_t)0x01)
#define SMBUS_OA2_MASK02                        ((uint8_t)0x02)
#define SMBUS_OA2_MASK03                        ((uint8_t)0x03)
#define SMBUS_OA2_MASK04                        ((uint8_t)0x04)
#define SMBUS_OA2_MASK05                        ((uint8_t)0x05)
#define SMBUS_OA2_MASK06                        ((uint8_t)0x06)
#define SMBUS_OA2_MASK07                        ((uint8_t)0x07)

#define IS_SMBUS_OWN_ADDRESS2_MASK(MASK)        (((MASK) == SMBUS_OA2_NOMASK)   || \
                                                 ((MASK) == SMBUS_OA2_MASK01)    || \
                                                 ((MASK) == SMBUS_OA2_MASK02)    || \
                                                 ((MASK) == SMBUS_OA2_MASK03)    || \
                                                 ((MASK) == SMBUS_OA2_MASK04)    || \
                                                 ((MASK) == SMBUS_OA2_MASK05)    || \
                                                 ((MASK) == SMBUS_OA2_MASK06)    || \
                                                 ((MASK) == SMBUS_OA2_MASK07))  
/**
  * @}
  */


/** @defgroup SMBUS_general_call_addressing_mode  SMBUS general call addressing mode
  * @{
  */
#define SMBUS_GENERALCALL_DISABLED              ((uint32_t)0x00000000)
#define SMBUS_GENERALCALL_ENABLED               I2C_CR1_GCEN

#define IS_SMBUS_GENERAL_CALL(CALL)             (((CALL) == SMBUS_GENERALCALL_DISABLED) || \
                                                 ((CALL) == SMBUS_GENERALCALL_ENABLED))
/**
  * @}
  */

/** @defgroup SMBUS_nostretch_mode SMBUS nostretch mode
  * @{
  */
#define SMBUS_NOSTRETCH_DISABLED                ((uint32_t)0x00000000)
#define SMBUS_NOSTRETCH_ENABLED                 I2C_CR1_NOSTRETCH

#define IS_SMBUS_NO_STRETCH(STRETCH)            (((STRETCH) == SMBUS_NOSTRETCH_DISABLED) || \
                                                 ((STRETCH) == SMBUS_NOSTRETCH_ENABLED))
/**
  * @}
  */

/** @defgroup SMBUS_packet_error_check_mode SMBUS packet error check mode
  * @{
  */
#define SMBUS_PEC_DISABLED                      ((uint32_t)0x00000000)
#define SMBUS_PEC_ENABLED                       I2C_CR1_PECEN

#define IS_SMBUS_PEC(PEC)                       (((PEC) == SMBUS_PEC_DISABLED) || \
                                                 ((PEC) == SMBUS_PEC_ENABLED))
/**
  * @}
  */

/** @defgroup SMBUS_peripheral_mode SMBUS peripheral mode
  * @{
  */
#define SMBUS_PERIPHERAL_MODE_SMBUS_HOST        (uint32_t)(I2C_CR1_SMBHEN)
#define SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE       (uint32_t)(0x00000000)
#define SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE_ARP   (uint32_t)(I2C_CR1_SMBDEN)

#define IS_SMBUS_PERIPHERAL_MODE(MODE)          (((MODE) == SMBUS_PERIPHERAL_MODE_SMBUS_HOST)   || \
                                                 ((MODE) == SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE)  || \
                                                 ((MODE) == SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE_ARP))
/**
  * @}
  */

/** @defgroup SMBUS_ReloadEndMode_definition  SMBUS ReloadEndMode definition
  * @{
  */

#define  SMBUS_SOFTEND_MODE                     ((uint32_t)0x00000000)
#define  SMBUS_RELOAD_MODE                      I2C_CR2_RELOAD
#define  SMBUS_AUTOEND_MODE                     I2C_CR2_AUTOEND
#define  SMBUS_SENDPEC_MODE                     I2C_CR2_PECBYTE

#define IS_SMBUS_TRANSFER_MODE(MODE)            (((MODE) == SMBUS_RELOAD_MODE)                          || \
                                                 ((MODE) == SMBUS_AUTOEND_MODE)                         || \
                                                 ((MODE) == SMBUS_SOFTEND_MODE)                         || \
                                                 ((MODE) == (SMBUS_RELOAD_MODE | SMBUS_SENDPEC_MODE))   || \
                                                 ((MODE) == (SMBUS_AUTOEND_MODE | SMBUS_SENDPEC_MODE))  || \
                                                 ((MODE) == (SMBUS_AUTOEND_MODE | SMBUS_RELOAD_MODE))   || \
                                                 ((MODE) == (SMBUS_AUTOEND_MODE | SMBUS_SENDPEC_MODE | SMBUS_RELOAD_MODE )))
                               
/**
  * @}
  */

/** @defgroup SMBUS_StartStopMode_definition SMBUS StartStopMode definition
  * @{
  */

#define  SMBUS_NO_STARTSTOP                     ((uint32_t)0x00000000)
#define  SMBUS_GENERATE_STOP                    I2C_CR2_STOP
#define  SMBUS_GENERATE_START_READ              (uint32_t)(I2C_CR2_START | I2C_CR2_RD_WRN)
#define  SMBUS_GENERATE_START_WRITE             I2C_CR2_START
                              
#define IS_SMBUS_TRANSFER_REQUEST(REQUEST)      (((REQUEST) == SMBUS_GENERATE_STOP)             || \
                                                 ((REQUEST) == SMBUS_GENERATE_START_READ)       || \
                                                 ((REQUEST) == SMBUS_GENERATE_START_WRITE)      || \
                                                 ((REQUEST) == SMBUS_NO_STARTSTOP))
                               
/**
  * @}
  */

/** @defgroup SMBUS_XferOptions_definition  SMBUS XferOptions definition
  * @{
  */

#define  SMBUS_FIRST_FRAME                      ((uint32_t)(SMBUS_SOFTEND_MODE))
#define  SMBUS_NEXT_FRAME                       ((uint32_t)(SMBUS_RELOAD_MODE | SMBUS_SOFTEND_MODE))
#define  SMBUS_FIRST_AND_LAST_FRAME_NO_PEC      SMBUS_AUTOEND_MODE 
#define  SMBUS_LAST_FRAME_NO_PEC                SMBUS_AUTOEND_MODE
#define  SMBUS_FIRST_AND_LAST_FRAME_WITH_PEC    ((uint32_t)(SMBUS_AUTOEND_MODE | SMBUS_SENDPEC_MODE))
#define  SMBUS_LAST_FRAME_WITH_PEC              ((uint32_t)(SMBUS_AUTOEND_MODE | SMBUS_SENDPEC_MODE))

#define IS_SMBUS_TRANSFER_OPTIONS_REQUEST(REQUEST)    (((REQUEST) == SMBUS_FIRST_FRAME)                       || \
                                                       ((REQUEST) == SMBUS_NEXT_FRAME)                        || \
                                                       ((REQUEST) == SMBUS_FIRST_AND_LAST_FRAME_NO_PEC)       || \
                                                       ((REQUEST) == SMBUS_LAST_FRAME_NO_PEC)                 || \
                                                       ((REQUEST) == SMBUS_FIRST_AND_LAST_FRAME_WITH_PEC)     || \
                                                       ((REQUEST) == SMBUS_LAST_FRAME_WITH_PEC))

/**
  * @}
  */

/** @defgroup SMBUS_Interrupt_configuration_definition SMBUS Interrupt configuration definition
  * @brief SMBUS Interrupt definition
  *        Elements values convention: 0xXXXXXXXX
  *           - XXXXXXXX  : Interrupt control mask
  * @{
  */
#define SMBUS_IT_ERRI                     I2C_CR1_ERRIE
#define SMBUS_IT_TCI                      I2C_CR1_TCIE
#define SMBUS_IT_STOPI                    I2C_CR1_STOPIE
#define SMBUS_IT_NACKI                    I2C_CR1_NACKIE
#define SMBUS_IT_ADDRI                    I2C_CR1_ADDRIE
#define SMBUS_IT_RXI                      I2C_CR1_RXIE
#define SMBUS_IT_TXI                      I2C_CR1_TXIE
#define SMBUS_IT_TX                       (SMBUS_IT_ERRI | SMBUS_IT_TCI | SMBUS_IT_STOPI | SMBUS_IT_NACKI | SMBUS_IT_TXI)
#define SMBUS_IT_RX                       (SMBUS_IT_ERRI | SMBUS_IT_TCI | SMBUS_IT_NACKI | SMBUS_IT_RXI)
#define SMBUS_IT_ALERT                    (SMBUS_IT_ERRI)
#define SMBUS_IT_ADDR                     (SMBUS_IT_ADDRI | SMBUS_IT_STOPI | SMBUS_IT_NACKI)
/**
  * @}
  */

/** @defgroup SMBUS_Flag_definition SMBUS Flag definition
  * @brief Flag definition
  *        Elements values convention: 0xXXXXYYYY
  *           - XXXXXXXX  : Flag mask
  * @{
  */ 

#define  SMBUS_FLAG_TXE                   I2C_ISR_TXE
#define  SMBUS_FLAG_TXIS                  I2C_ISR_TXIS
#define  SMBUS_FLAG_RXNE                  I2C_ISR_RXNE
#define  SMBUS_FLAG_ADDR                  I2C_ISR_ADDR
#define  SMBUS_FLAG_AF                    I2C_ISR_NACKF
#define  SMBUS_FLAG_STOPF                 I2C_ISR_STOPF
#define  SMBUS_FLAG_TC                    I2C_ISR_TC
#define  SMBUS_FLAG_TCR                   I2C_ISR_TCR
#define  SMBUS_FLAG_BERR                  I2C_ISR_BERR
#define  SMBUS_FLAG_ARLO                  I2C_ISR_ARLO
#define  SMBUS_FLAG_OVR                   I2C_ISR_OVR
#define  SMBUS_FLAG_PECERR                I2C_ISR_PECERR
#define  SMBUS_FLAG_TIMEOUT               I2C_ISR_TIMEOUT
#define  SMBUS_FLAG_ALERT                 I2C_ISR_ALERT
#define  SMBUS_FLAG_BUSY                  I2C_ISR_BUSY
#define  SMBUS_FLAG_DIR                   I2C_ISR_DIR
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ------------------------------------------------------------*/
/** @defgroup SMBUS_Exported_Macros SMBUS Exported Macros
  * @{
  */  
  
/** @brief  Reset SMBUS handle state
  * @param  __HANDLE__: SMBUS handle.
  * @retval None
  */
#define __HAL_SMBUS_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SMBUS_STATE_RESET)

/** @brief  Enable or disable the specified SMBUS interrupts.
  * @param  __HANDLE__: specifies the SMBUS Handle.
  *         This parameter can be SMBUS where x: 1 or 2 to select the SMBUS peripheral.
  * @param  __INTERRUPT__: specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg SMBUS_IT_ERRI: Errors interrupt enable
  *            @arg SMBUS_IT_TCI: Transfer complete interrupt enable
  *            @arg SMBUS_IT_STOPI: STOP detection interrupt enable
  *            @arg SMBUS_IT_NACKI: NACK received interrupt enable
  *            @arg SMBUS_IT_ADDRI: Address match interrupt enable
  *            @arg SMBUS_IT_RXI: RX interrupt enable
  *            @arg SMBUS_IT_TXI: TX interrupt enable
  *   
  * @retval None
  */
  
#define __HAL_SMBUS_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CR1 |= (__INTERRUPT__))
#define __HAL_SMBUS_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->CR1 &= (~(__INTERRUPT__)))
 
/** @brief  Checks if the specified SMBUS interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the SMBUS Handle.
  *         This parameter can be SMBUS where x: 1 or 2 to select the SMBUS peripheral.
  * @param  __INTERRUPT__: specifies the SMBUS interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg SMBUS_IT_ERRI: Errors interrupt enable
  *            @arg SMBUS_IT_TCI: Transfer complete interrupt enable
  *            @arg SMBUS_IT_STOPI: STOP detection interrupt enable
  *            @arg SMBUS_IT_NACKI: NACK received interrupt enable
  *            @arg SMBUS_IT_ADDRI: Address match interrupt enable
  *            @arg SMBUS_IT_RXI: RX interrupt enable
  *            @arg SMBUS_IT_TXI: TX interrupt enable
  *   
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_SMBUS_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR1 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks whether the specified SMBUS flag is set or not.
  * @param  __HANDLE__: specifies the SMBUS Handle.
  *         This parameter can be SMBUS where x: 1 or 2 to select the SMBUS peripheral.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg SMBUS_FLAG_TXE:		Transmit data register empty
  *            @arg SMBUS_FLAG_TXIS:		Transmit interrupt status
  *            @arg SMBUS_FLAG_RXNE:		Receive data register not empty
  *            @arg SMBUS_FLAG_ADDR:		Address matched (slave mode)
  *            @arg SMBUS_FLAG_AF: 	        NACK received flag
  *            @arg SMBUS_FLAG_STOPF: 	        STOP detection flag
  *            @arg SMBUS_FLAG_TC:		Transfer complete (master mode)
  *            @arg SMBUS_FLAG_TCR:		Transfer complete reload
  *            @arg SMBUS_FLAG_BERR:		Bus error
  *            @arg SMBUS_FLAG_ARLO:		Arbitration lost
  *            @arg SMBUS_FLAG_OVR:		Overrun/Underrun            
  *            @arg SMBUS_FLAG_PECERR: 	        PEC error in reception
  *            @arg SMBUS_FLAG_TIMEOUT:         Timeout or Tlow detection flag 
  *            @arg SMBUS_FLAG_ALERT:		SMBus alert
  *            @arg SMBUS_FLAG_BUSY: 		Bus busy
  *            @arg SMBUS_FLAG_DIR: 		Transfer direction (slave mode)
  *   
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define SMBUS_FLAG_MASK  ((uint32_t)0x0001FFFF)
#define __HAL_SMBUS_GET_FLAG(__HANDLE__, __FLAG__) (((((__HANDLE__)->Instance->ISR) & ((__FLAG__) & SMBUS_FLAG_MASK)) == ((__FLAG__) & SMBUS_FLAG_MASK)))
    
/** @brief  Clears the SMBUS pending flags which are cleared by writing 1 in a specific bit.
  * @param  __HANDLE__: specifies the SMBUS Handle.
  *         This parameter can be SMBUS where x: 1 or 2 to select the SMBUS peripheral.
  * @param  __FLAG__: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg SMBUS_FLAG_ADDR:		Address matched (slave mode)
  *            @arg SMBUS_FLAG_AF: 	        NACK received flag
  *            @arg SMBUS_FLAG_STOPF: 	        STOP detection flag
  *            @arg SMBUS_FLAG_BERR:		Bus error
  *            @arg SMBUS_FLAG_ARLO:		Arbitration lost
  *            @arg SMBUS_FLAG_OVR:		Overrun/Underrun            
  *            @arg SMBUS_FLAG_PECERR: 	        PEC error in reception
  *            @arg SMBUS_FLAG_TIMEOUT:         Timeout or Tlow detection flag 
  *            @arg SMBUS_FLAG_ALERT:		SMBus alert
  *   
  * @retval None
  */
#define __HAL_SMBUS_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))
 

#define __HAL_SMBUS_ENABLE(__HANDLE__)                          ((__HANDLE__)->Instance->CR1 |=  I2C_CR1_PE)
#define __HAL_SMBUS_DISABLE(__HANDLE__)                         ((__HANDLE__)->Instance->CR1 &=  ~I2C_CR1_PE)

#define __HAL_SMBUS_RESET_CR1(__HANDLE__)                       ((__HANDLE__)->Instance->CR1 &= (uint32_t)~((uint32_t)(I2C_CR1_SMBHEN | I2C_CR1_SMBDEN | I2C_CR1_PECEN)))
#define __HAL_SMBUS_RESET_CR2(__HANDLE__)                       ((__HANDLE__)->Instance->CR2 &= (uint32_t)~((uint32_t)(I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_RD_WRN)))

#define __HAL_SMBUS_GENERATE_START(__ADDMODE__,__ADDRESS__)     (((__ADDMODE__) == SMBUS_ADDRESSINGMODE_7BIT) ? (uint32_t)((((uint32_t)(__ADDRESS__) & (I2C_CR2_SADD)) | (I2C_CR2_START) | (I2C_CR2_AUTOEND)) & (~I2C_CR2_RD_WRN)) : \
                                                                  (uint32_t)((((uint32_t)(__ADDRESS__) & (I2C_CR2_SADD)) | (I2C_CR2_ADD10) | (I2C_CR2_START)) & (~I2C_CR2_RD_WRN)))

#define __HAL_SMBUS_GET_ADDR_MATCH(__HANDLE__)                  (((__HANDLE__)->Instance->ISR & I2C_ISR_ADDCODE) >> 17)
#define __HAL_SMBUS_GET_DIR(__HANDLE__)                         (((__HANDLE__)->Instance->ISR & I2C_ISR_DIR) >> 16)
#define __HAL_SMBUS_GET_STOP_MODE(__HANDLE__)                   ((__HANDLE__)->Instance->CR2 & I2C_CR2_AUTOEND)
#define __HAL_SMBUS_GET_PEC_MODE(__HANDLE__)                    ((__HANDLE__)->Instance->CR2 & I2C_CR2_PECBYTE)
#define __HAL_SMBUS_GET_ALERT_ENABLED(__HANDLE__)                ((__HANDLE__)->Instance->CR1 & I2C_CR1_ALERTEN)
#define __HAL_SMBUS_GENERATE_NACK(__HANDLE__)                   ((__HANDLE__)->Instance->CR2 |= I2C_CR2_NACK)

#define IS_SMBUS_OWN_ADDRESS1(ADDRESS1)                         ((ADDRESS1) <= (uint32_t)0x000003FF)
#define IS_SMBUS_OWN_ADDRESS2(ADDRESS2)                         ((ADDRESS2) <= (uint16_t)0x00FF)
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMBUS_Exported_Functions SMBUS Exported Functions
  * @{
  */

/** @addtogroup SMBUS_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_SMBUS_Init(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUS_DeInit (SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_MspInit(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_MspDeInit(SMBUS_HandleTypeDef *hsmbus);

/**
  * @}
  */

/** @addtogroup SMBUS_Exported_Functions_Group2 Input and Output operation functions
  * @{
  */

/* IO operation functions  *****************************************************/
/** @addtogroup Blocking_mode_Polling Blocking mode Polling
 * @{
 */
/******* Blocking mode: Polling */
HAL_StatusTypeDef HAL_SMBUS_IsDeviceReady(SMBUS_HandleTypeDef *hsmbus, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
/**
  * @}
  */

/** @addtogroup Non-Blocking_mode_Interrupt Non-Blocking mode Interrupt
 * @{
 */
 /******* Non-Blocking mode: Interrupt */
HAL_StatusTypeDef HAL_SMBUS_Master_Transmit_IT(SMBUS_HandleTypeDef *hsmbus, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_SMBUS_Master_Receive_IT(SMBUS_HandleTypeDef *hsmbus, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_SMBUS_Master_Abort_IT(SMBUS_HandleTypeDef *hsmbus, uint16_t DevAddress);
HAL_StatusTypeDef HAL_SMBUS_Slave_Transmit_IT(SMBUS_HandleTypeDef *hsmbus, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_SMBUS_Slave_Receive_IT(SMBUS_HandleTypeDef *hsmbus, uint8_t *pData, uint16_t Size, uint32_t XferOptions);

HAL_StatusTypeDef HAL_SMBUS_EnableAlert_IT(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUS_DisableAlert_IT(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUS_Slave_Listen_IT(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUS_DisableListen_IT(SMBUS_HandleTypeDef *hsmbus);
/** @defgroup Aliases_Exported_Functions Aliases for Exported Functions 
 * @brief  Aliases for new API and to insure inter STM32 series compatibility
 * @{
 */
/* Aliases for new API and to insure inter STM32 series compatibility */
#define HAL_SMBUS_EnableListen_IT   HAL_SMBUS_Slave_Listen_IT
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
 * @{
 */
 /******* SMBUS IRQHandler and Callbacks used in non blocking modes (Interrupt) */
void HAL_SMBUS_EV_IRQHandler(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_ER_IRQHandler(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_MasterTxCpltCallback(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_MasterRxCpltCallback(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_SlaveTxCpltCallback(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_SlaveRxCpltCallback(SMBUS_HandleTypeDef *hsmbus);
void HAL_SMBUS_SlaveAddrCallback(SMBUS_HandleTypeDef *hsmbus, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_SMBUS_SlaveListenCpltCallback(SMBUS_HandleTypeDef *hsmbus);

/** @addtogroup Aliases_Exported_Functions Aliases for Exported Functions 
 * @brief  Aliases for new API and to insure inter STM32 series compatibility
 * @{
 */
/* Aliases for new API and to insure inter STM32 series compatibility */
#define HAL_SMBUS_AddrCallback         HAL_SMBUS_SlaveAddrCallback
#define HAL_SMBUS_ListenCpltCallback   HAL_SMBUS_SlaveListenCpltCallback
/**
  * @}
  */

void HAL_SMBUS_ErrorCallback(SMBUS_HandleTypeDef *hsmbus);

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SMBUS_Exported_Functions_Group3 Peripheral State and Errors functions 
  * @{
  */

/* Peripheral State and Errors functions  **************************************************/
HAL_SMBUS_StateTypeDef HAL_SMBUS_GetState(SMBUS_HandleTypeDef *hsmbus);
uint32_t               HAL_SMBUS_GetError(SMBUS_HandleTypeDef *hsmbus);

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


#endif /* __STM32F3xx_HAL_SMBUS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
