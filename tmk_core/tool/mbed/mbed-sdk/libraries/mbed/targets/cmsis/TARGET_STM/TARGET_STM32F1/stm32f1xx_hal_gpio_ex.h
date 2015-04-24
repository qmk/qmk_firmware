/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Header file of GPIO HAL Extension module.
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
#ifndef __STM32F1xx_HAL_GPIO_EX_H
#define __STM32F1xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */ 
  
/** @defgroup GPIOEx_EVENTOUT EVENTOUT Cortex Configuration
  * @brief This section propose definition to use the Cortex EVENTOUT signal.
  * @{
  */
  
/** @defgroup GPIOEx_EVENTOUT_PIN EVENTOUT Pin 
  * @{
  */
  
#define AFIO_EVENTOUT_PIN_0  AFIO_EVCR_PIN_PX0 /*!< EVENTOUT on pin 0 */
#define AFIO_EVENTOUT_PIN_1  AFIO_EVCR_PIN_PX1 /*!< EVENTOUT on pin 1 */
#define AFIO_EVENTOUT_PIN_2  AFIO_EVCR_PIN_PX2 /*!< EVENTOUT on pin 2 */
#define AFIO_EVENTOUT_PIN_3  AFIO_EVCR_PIN_PX3 /*!< EVENTOUT on pin 3 */
#define AFIO_EVENTOUT_PIN_4  AFIO_EVCR_PIN_PX4 /*!< EVENTOUT on pin 4 */
#define AFIO_EVENTOUT_PIN_5  AFIO_EVCR_PIN_PX5 /*!< EVENTOUT on pin 5 */
#define AFIO_EVENTOUT_PIN_6  AFIO_EVCR_PIN_PX6 /*!< EVENTOUT on pin 6 */
#define AFIO_EVENTOUT_PIN_7  AFIO_EVCR_PIN_PX7 /*!< EVENTOUT on pin 7 */
#define AFIO_EVENTOUT_PIN_8  AFIO_EVCR_PIN_PX8 /*!< EVENTOUT on pin 8 */
#define AFIO_EVENTOUT_PIN_9  AFIO_EVCR_PIN_PX9 /*!< EVENTOUT on pin 9 */
#define AFIO_EVENTOUT_PIN_10 AFIO_EVCR_PIN_PX10 /*!< EVENTOUT on pin 10 */
#define AFIO_EVENTOUT_PIN_11 AFIO_EVCR_PIN_PX11 /*!< EVENTOUT on pin 11 */
#define AFIO_EVENTOUT_PIN_12 AFIO_EVCR_PIN_PX12 /*!< EVENTOUT on pin 12 */
#define AFIO_EVENTOUT_PIN_13 AFIO_EVCR_PIN_PX13 /*!< EVENTOUT on pin 13 */
#define AFIO_EVENTOUT_PIN_14 AFIO_EVCR_PIN_PX14 /*!< EVENTOUT on pin 14 */
#define AFIO_EVENTOUT_PIN_15 AFIO_EVCR_PIN_PX15 /*!< EVENTOUT on pin 15 */

#define IS_AFIO_EVENTOUT_PIN(__PIN__) (((__PIN__) == AFIO_EVENTOUT_PIN_0) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_1) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_2) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_3) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_4) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_5) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_6) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_7) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_8) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_9) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_10) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_11) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_12) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_13) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_14) || \
                                       ((__PIN__) == AFIO_EVENTOUT_PIN_15))
/**
  * @}
  */ 
  
/** @defgroup GPIOEx_EVENTOUT_PORT EVENTOUT Port
  * @{
  */
  
#define AFIO_EVENTOUT_PORT_A AFIO_EVCR_PORT_PA /*!< EVENTOUT on port A */
#define AFIO_EVENTOUT_PORT_B AFIO_EVCR_PORT_PB /*!< EVENTOUT on port B */
#define AFIO_EVENTOUT_PORT_C AFIO_EVCR_PORT_PC /*!< EVENTOUT on port C */
#define AFIO_EVENTOUT_PORT_D AFIO_EVCR_PORT_PD /*!< EVENTOUT on port D */
#define AFIO_EVENTOUT_PORT_E AFIO_EVCR_PORT_PE /*!< EVENTOUT on port E */

#define IS_AFIO_EVENTOUT_PORT(__PORT__) (((__PORT__) == AFIO_EVENTOUT_PORT_A) || \
                                         ((__PORT__) == AFIO_EVENTOUT_PORT_B) || \
                                         ((__PORT__) == AFIO_EVENTOUT_PORT_C) || \
                                         ((__PORT__) == AFIO_EVENTOUT_PORT_D) || \
                                         ((__PORT__) == AFIO_EVENTOUT_PORT_E))
/**
  * @}
  */
  
/**
  * @}
  */

/** @defgroup GPIOEx_AFIO_AF_REMAPPING Alternate Function Remapping
  * @brief This section propose definition to remap the alternate function to some other port/pins.
  * @{
  */
  
/**
  * @brief Enable the remapping of SPI1 alternate function NSS, SCK, MISO and MOSI.
  * @note  ENABLE: Remap     (NSS/PA15, SCK/PB3, MISO/PB4, MOSI/PB5)
  * @retval None
  */
#define __HAL_AFIO_REMAP_SPI1_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_SPI1_REMAP)

/**
  * @brief Disable the remapping of SPI1 alternate function NSS, SCK, MISO and MOSI.
  * @note  DISABLE: No remap (NSS/PA4,  SCK/PA5, MISO/PA6, MOSI/PA7)
  * @retval None
  */
#define __HAL_AFIO_REMAP_SPI1_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_SPI1_REMAP)

/**
  * @brief Enable the remapping of I2C1 alternate function SCL and SDA.
  * @note  ENABLE: Remap     (SCL/PB8, SDA/PB9)
  * @retval None
  */
#define __HAL_AFIO_REMAP_I2C1_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_I2C1_REMAP)

/**
  * @brief Disable the remapping of I2C1 alternate function SCL and SDA.
  * @note  DISABLE: No remap (SCL/PB6, SDA/PB7)
  * @retval None
  */
#define __HAL_AFIO_REMAP_I2C1_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_I2C1_REMAP)

/**
  * @brief Enable the remapping of USART1 alternate function TX and RX.
  * @note  ENABLE: Remap     (TX/PB6, RX/PB7)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART1_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_USART1_REMAP)

/**
  * @brief Disable the remapping of USART1 alternate function TX and RX.
  * @note  DISABLE: No remap (TX/PA9, RX/PA10)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART1_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_USART1_REMAP)

/**
  * @brief Enable the remapping of USART2 alternate function CTS, RTS, CK, TX and RX.
  * @note  ENABLE: Remap     (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART2_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_USART2_REMAP)

/**
  * @brief Disable the remapping of USART2 alternate function CTS, RTS, CK, TX and RX.
  * @note  DISABLE: No remap (CTS/PA0, RTS/PA1, TX/PA2, RX/PA3, CK/PA4)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART2_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_USART2_REMAP)

/**
  * @brief Enable the remapping of USART3 alternate function CTS, RTS, CK, TX and RX.
  * @note  ENABLE: Full remap     (TX/PD8,  RX/PD9,  CK/PD10, CTS/PD11, RTS/PD12)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART3_ENABLE()  MODIFY_REG(AFIO->MAPR, AFIO_MAPR_USART3_REMAP, AFIO_MAPR_USART3_REMAP_FULLREMAP)

/**
  * @brief Enable the remapping of USART3 alternate function CTS, RTS, CK, TX and RX.
  * @note  PARTIAL: Partial remap (TX/PC10, RX/PC11, CK/PC12, CTS/PB13, RTS/PB14)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART3_PARTIAL() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_USART3_REMAP, AFIO_MAPR_USART3_REMAP_PARTIALREMAP)

/**
  * @brief Disable the remapping of USART3 alternate function CTS, RTS, CK, TX and RX.
  * @note  DISABLE: No remap      (TX/PB10, RX/PB11, CK/PB12, CTS/PB13, RTS/PB14)
  * @retval None
  */
#define __HAL_AFIO_REMAP_USART3_DISABLE() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_USART3_REMAP, AFIO_MAPR_USART3_REMAP_NOREMAP)

/**
  * @brief Enable the remapping of TIM1 alternate function channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN)
  * @note  ENABLE: Full remap     (ETR/PE7,  CH1/PE9, CH2/PE11, CH3/PE13, CH4/PE14, BKIN/PE15, CH1N/PE8,  CH2N/PE10, CH3N/PE12)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM1_ENABLE()  MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM1_REMAP, AFIO_MAPR_TIM1_REMAP_FULLREMAP)

/**
  * @brief Enable the remapping of TIM1 alternate function channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN)
  * @note  PARTIAL: Partial remap (ETR/PA12, CH1/PA8, CH2/PA9,  CH3/PA10, CH4/PA11, BKIN/PA6,  CH1N/PA7,  CH2N/PB0,  CH3N/PB1)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM1_PARTIAL() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM1_REMAP, AFIO_MAPR_TIM1_REMAP_PARTIALREMAP)

/**
  * @brief Disable the remapping of TIM1 alternate function channels 1 to 4, 1N to 3N, external trigger (ETR) and Break input (BKIN)
  * @note  DISABLE: No remap      (ETR/PA12, CH1/PA8, CH2/PA9,  CH3/PA10, CH4/PA11, BKIN/PB12, CH1N/PB13, CH2N/PB14, CH3N/PB15)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM1_DISABLE() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM1_REMAP, AFIO_MAPR_TIM1_REMAP_NOREMAP)

/**
  * @brief Enable the remapping of TIM2 alternate function channels 1 to 4 and external trigger (ETR)
  * @note  ENABLE: Full remap       (CH1/ETR/PA15, CH2/PB3, CH3/PB10, CH4/PB11)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM2_ENABLE()    MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM2_REMAP, AFIO_MAPR_TIM2_REMAP_FULLREMAP)

/**
  * @brief Enable the remapping of TIM2 alternate function channels 1 to 4 and external trigger (ETR)
  * @note  PARTIAL_2: Partial remap (CH1/ETR/PA0,  CH2/PA1, CH3/PB10, CH4/PB11)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM2_PARTIAL_2() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM2_REMAP, AFIO_MAPR_TIM2_REMAP_PARTIALREMAP2)

/**
  * @brief Enable the remapping of TIM2 alternate function channels 1 to 4 and external trigger (ETR)
  * @note  PARTIAL_1: Partial remap (CH1/ETR/PA15, CH2/PB3, CH3/PA2,  CH4/PA3)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM2_PARTIAL_1() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM2_REMAP, AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1)

/**
  * @brief Disable the remapping of TIM2 alternate function channels 1 to 4 and external trigger (ETR)
  * @note  DISABLE: No remap        (CH1/ETR/PA0,  CH2/PA1, CH3/PA2,  CH4/PA3)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM2_DISABLE()   MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM2_REMAP, AFIO_MAPR_TIM2_REMAP_NOREMAP)

/**
  * @brief Enable the remapping of TIM3 alternate function channels 1 to 4
  * @note  ENABLE: Full remap     (CH1/PC6, CH2/PC7, CH3/PC8, CH4/PC9)
  * @note  TIM3_ETR on PE0 is not re-mapped.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM3_ENABLE()  MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM3_REMAP, AFIO_MAPR_TIM3_REMAP_FULLREMAP)

/**
  * @brief Enable the remapping of TIM3 alternate function channels 1 to 4
  * @note  PARTIAL: Partial remap (CH1/PB4, CH2/PB5, CH3/PB0, CH4/PB1)
  * @note  TIM3_ETR on PE0 is not re-mapped.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM3_PARTIAL() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM3_REMAP, AFIO_MAPR_TIM3_REMAP_PARTIALREMAP)

/**
  * @brief Disable the remapping of TIM3 alternate function channels 1 to 4
  * @note  DISABLE: No remap      (CH1/PA6, CH2/PA7, CH3/PB0, CH4/PB1)
  * @note  TIM3_ETR on PE0 is not re-mapped.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM3_DISABLE() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_TIM3_REMAP, AFIO_MAPR_TIM3_REMAP_NOREMAP)

/**
  * @brief Enable the remapping of TIM4 alternate function channels 1 to 4.
  * @note  ENABLE: Full remap (TIM4_CH1/PD12, TIM4_CH2/PD13, TIM4_CH3/PD14, TIM4_CH4/PD15)
  * @note  TIM4_ETR on PE0 is not re-mapped.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM4_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_TIM4_REMAP)

/**
  * @brief Disable the remapping of TIM4 alternate function channels 1 to 4.
  * @note  DISABLE: No remap  (TIM4_CH1/PB6,  TIM4_CH2/PB7,  TIM4_CH3/PB8,  TIM4_CH4/PB9)
  * @note  TIM4_ETR on PE0 is not re-mapped.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM4_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_TIM4_REMAP)

#if defined(AFIO_MAPR_CAN_REMAP_REMAP1)

/**
  * @brief Enable or disable the remapping of CAN alternate function CAN_RX and CAN_TX in devices with a single CAN interface.
  * @note  CASE 1: CAN_RX mapped to PA11, CAN_TX mapped to PA12
  * @retval None
  */
#define __HAL_AFIO_REMAP_CAN1_1() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_CAN_REMAP, AFIO_MAPR_CAN_REMAP_REMAP1)

/**
  * @brief Enable or disable the remapping of CAN alternate function CAN_RX and CAN_TX in devices with a single CAN interface.
  * @note  CASE 2: CAN_RX mapped to PB8,  CAN_TX mapped to PB9 (not available on 36-pin package)
  * @retval None
  */
#define __HAL_AFIO_REMAP_CAN1_2() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_CAN_REMAP, AFIO_MAPR_CAN_REMAP_REMAP2)

/**
  * @brief Enable or disable the remapping of CAN alternate function CAN_RX and CAN_TX in devices with a single CAN interface.
  * @note  CASE 3: CAN_RX mapped to PD0,  CAN_TX mapped to PD1
  * @retval None
  */
#define __HAL_AFIO_REMAP_CAN1_3() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_CAN_REMAP, AFIO_MAPR_CAN_REMAP_REMAP3)
#endif

/**
  * @brief Enable the remapping of PD0 and PD1. When the HSE oscillator is not used 
  *        (application running on internal 8 MHz RC) PD0 and PD1 can be mapped on OSC_IN and 
  *        OSC_OUT. This is available only on 36, 48 and 64 pins packages (PD0 and PD1 are available 
  *        on 100-pin and 144-pin packages, no need for remapping).
  * @note  ENABLE: PD0 remapped on OSC_IN, PD1 remapped on OSC_OUT.
  * @retval None
  */
#define __HAL_AFIO_REMAP_PD01_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_PD01_REMAP)

/**
  * @brief Disable the remapping of PD0 and PD1. When the HSE oscillator is not used 
  *        (application running on internal 8 MHz RC) PD0 and PD1 can be mapped on OSC_IN and 
  *        OSC_OUT. This is available only on 36, 48 and 64 pins packages (PD0 and PD1 are available 
  *        on 100-pin and 144-pin packages, no need for remapping).
  * @note  DISABLE: No remapping of PD0 and PD1
  * @retval None
  */
#define __HAL_AFIO_REMAP_PD01_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_PD01_REMAP)

#if defined(AFIO_MAPR_TIM5CH4_IREMAP)
/**
  * @brief Enable the remapping of TIM5CH4.
  * @note  ENABLE: LSI internal clock is connected to TIM5_CH4 input for calibration purpose.
  * @note  This function is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM5CH4_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_TIM5CH4_IREMAP)

/**
  * @brief Disable the remapping of TIM5CH4.
  * @note  DISABLE: TIM5_CH4 is connected to PA3
  * @note  This function is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM5CH4_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_TIM5CH4_IREMAP)
#endif

#if defined(AFIO_MAPR_ETH_REMAP)
/**
  * @brief Enable the remapping of Ethernet MAC connections with the PHY.
  * @note  ENABLE: Remap     (RX_DV-CRS_DV/PD8, RXD0/PD9, RXD1/PD10, RXD2/PD11, RXD3/PD12)
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ETH_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_ETH_REMAP)

/**
  * @brief Disable the remapping of Ethernet MAC connections with the PHY.
  * @note  DISABLE: No remap (RX_DV-CRS_DV/PA7, RXD0/PC4, RXD1/PC5,  RXD2/PB0,  RXD3/PB1)
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ETH_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_ETH_REMAP)
#endif

#if defined(AFIO_MAPR_CAN2_REMAP)

/**
  * @brief Enable the remapping of CAN2 alternate function CAN2_RX and CAN2_TX.
  * @note  ENABLE: Remap     (CAN2_RX/PB5,  CAN2_TX/PB6)
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_CAN2_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_CAN2_REMAP)

/**
  * @brief Disable the remapping of CAN2 alternate function CAN2_RX and CAN2_TX.
  * @note  DISABLE: No remap (CAN2_RX/PB12, CAN2_TX/PB13)
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_CAN2_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_CAN2_REMAP)
#endif

#if defined(AFIO_MAPR_MII_RMII_SEL)
/**
  * @brief Configures the Ethernet MAC internally for use with an external MII or RMII PHY.
  * @note  ETH_RMII: Configure Ethernet MAC for connection with an RMII PHY
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_ETH_RMII() SET_BIT(AFIO->MAPR, AFIO_MAPR_MII_RMII_SEL)

/**
  * @brief Configures the Ethernet MAC internally for use with an external MII or RMII PHY.
  * @note  ETH_MII: Configure Ethernet MAC for connection with an MII PHY
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_ETH_MII()  CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_MII_RMII_SEL)
#endif

/**
  * @brief Enable the remapping of ADC1_ETRGINJ (ADC 1 External trigger injected conversion).
  * @note  ENABLE: ADC1 External Event injected conversion is connected to TIM8 Channel4.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC1_ETRGINJ_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_ADC1_ETRGINJ_REMAP)

/**
  * @brief Disable the remapping of ADC1_ETRGINJ (ADC 1 External trigger injected conversion).
  * @note  DISABLE: ADC1 External trigger injected conversion is connected to EXTI15
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC1_ETRGINJ_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_ADC1_ETRGINJ_REMAP)

/**
  * @brief Enable the remapping of ADC1_ETRGREG (ADC 1 External trigger regular conversion).
  * @note  ENABLE: ADC1 External Event regular conversion is connected to TIM8 TRG0.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC1_ETRGREG_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_ADC1_ETRGREG_REMAP)

/**
  * @brief Disable the remapping of ADC1_ETRGREG (ADC 1 External trigger regular conversion).
  * @note  DISABLE: ADC1 External trigger regular conversion is connected to EXTI11
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC1_ETRGREG_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_ADC1_ETRGREG_REMAP)

#if defined(AFIO_MAPR_ADC2_ETRGINJ_REMAP)

/**
  * @brief Enable the remapping of ADC2_ETRGREG (ADC 2 External trigger injected conversion).
  * @note  ENABLE: ADC2 External Event injected conversion is connected to TIM8 Channel4.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC2_ETRGINJ_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_ADC2_ETRGINJ_REMAP)

/**
  * @brief Disable the remapping of ADC2_ETRGREG (ADC 2 External trigger injected conversion).
  * @note  DISABLE: ADC2 External trigger injected conversion is connected to EXTI15
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC2_ETRGINJ_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_ADC2_ETRGINJ_REMAP)
#endif

#if defined (AFIO_MAPR_ADC2_ETRGREG_REMAP)

/**
  * @brief Enable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @note  ENABLE: ADC2 External Event regular conversion is connected to TIM8 TRG0.
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC2_ETRGREG_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_ADC2_ETRGREG_REMAP)

/**
  * @brief Disable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @note  DISABLE: ADC2 External trigger regular conversion is connected to EXTI11
  * @retval None
  */
#define __HAL_AFIO_REMAP_ADC2_ETRGREG_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_ADC2_ETRGREG_REMAP)
#endif

/**
  * @brief Enable the Serial wire JTAG configuration
  * @note  ENABLE: Full SWJ (JTAG-DP + SW-DP): Reset State
  * @retval None
  */
#define __HAL_AFIO_REMAP_SWJ_ENABLE()   MODIFY_REG(AFIO->MAPR, AFIO_MAPR_SWJ_CFG, AFIO_MAPR_SWJ_CFG_RESET)

/**
  * @brief Enable the Serial wire JTAG configuration
  * @note  NONJTRST: Full SWJ (JTAG-DP + SW-DP) but without NJTRST
  * @retval None
  */
#define __HAL_AFIO_REMAP_SWJ_NONJTRST() MODIFY_REG(AFIO->MAPR, AFIO_MAPR_SWJ_CFG, AFIO_MAPR_SWJ_CFG_NOJNTRST)

/**
  * @brief Enable the Serial wire JTAG configuration
  * @note  NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  * @retval None
  */
#define __HAL_AFIO_REMAP_SWJ_NOJTAG()   MODIFY_REG(AFIO->MAPR, AFIO_MAPR_SWJ_CFG, AFIO_MAPR_SWJ_CFG_JTAGDISABLE)

/**
  * @brief Disable the Serial wire JTAG configuration
  * @note  DISABLE: JTAG-DP Disabled and SW-DP Disabled
  * @retval None
  */
#define __HAL_AFIO_REMAP_SWJ_DISABLE()  MODIFY_REG(AFIO->MAPR, AFIO_MAPR_SWJ_CFG, AFIO_MAPR_SWJ_CFG_DISABLE)

#if defined(AFIO_MAPR_SPI3_REMAP)

/**
  * @brief Enable the remapping of SPI3 alternate functions SPI3_NSS/I2S3_WS, SPI3_SCK/I2S3_CK, SPI3_MISO, SPI3_MOSI/I2S3_SD.
  * @note  ENABLE: Remap     (SPI3_NSS-I2S3_WS/PA4,  SPI3_SCK-I2S3_CK/PC10, SPI3_MISO/PC11, SPI3_MOSI-I2S3_SD/PC12)
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_SPI3_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_SPI3_REMAP)

/**
  * @brief Disable the remapping of SPI3 alternate functions SPI3_NSS/I2S3_WS, SPI3_SCK/I2S3_CK, SPI3_MISO, SPI3_MOSI/I2S3_SD.
  * @note  DISABLE: No remap (SPI3_NSS-I2S3_WS/PA15, SPI3_SCK-I2S3_CK/PB3,  SPI3_MISO/PB4,  SPI3_MOSI-I2S3_SD/PB5).
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_REMAP_SPI3_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_SPI3_REMAP)
#endif

#if defined(AFIO_MAPR_TIM2ITR1_IREMAP)

/**
  * @brief Control of TIM2_ITR1 internal mapping.
  * @note  TO_USB: Connect USB OTG SOF (Start of Frame) output to TIM2_ITR1 for calibration purposes.
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_TIM2ITR1_TO_USB() SET_BIT(AFIO->MAPR, AFIO_MAPR_TIM2ITR1_IREMAP)

/**
  * @brief Control of TIM2_ITR1 internal mapping.
  * @note  TO_ETH: Connect TIM2_ITR1 internally to the Ethernet PTP output for calibration purposes.
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_TIM2ITR1_TO_ETH() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_TIM2ITR1_IREMAP)
#endif

#if defined(AFIO_MAPR_PTP_PPS_REMAP)

/**
  * @brief Enable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @note  ENABLE: PTP_PPS is output on PB5 pin.
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_ETH_PTP_PPS_ENABLE()  SET_BIT(AFIO->MAPR, AFIO_MAPR_PTP_PPS_REMAP)

/**
  * @brief Disable the remapping of ADC2_ETRGREG (ADC 2 External trigger regular conversion).
  * @note  DISABLE: PTP_PPS not output on PB5 pin.
  * @note  This bit is available only in connectivity line devices and is reserved otherwise.
  * @retval None
  */
#define __HAL_AFIO_ETH_PTP_PPS_DISABLE() CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_PTP_PPS_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM9_REMAP)

/**
  * @brief Enable the remapping of TIM9_CH1 and TIM9_CH2.
  * @note  ENABLE: Remap     (TIM9_CH1 on PE5 and TIM9_CH2 on PE6).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM9_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM9_REMAP)

/**
  * @brief Disable the remapping of TIM9_CH1 and TIM9_CH2.
  * @note  DISABLE: No remap (TIM9_CH1 on PA2 and TIM9_CH2 on PA3).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM9_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM9_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM10_REMAP)

/**
  * @brief Enable the remapping of TIM10_CH1.
  * @note  ENABLE: Remap     (TIM10_CH1 on PF6).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM10_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM10_REMAP)

/**
  * @brief Disable the remapping of TIM10_CH1.
  * @note  DISABLE: No remap (TIM10_CH1 on PB8).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM10_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM10_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM11_REMAP)
/**
  * @brief Enable the remapping of TIM11_CH1.
  * @note  ENABLE: Remap     (TIM11_CH1 on PF7).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM11_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM11_REMAP)

/**
  * @brief Disable the remapping of TIM11_CH1.
  * @note  DISABLE: No remap (TIM11_CH1 on PB9).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM11_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM11_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM13_REMAP)

/**
  * @brief Enable the remapping of TIM13_CH1.
  * @note  ENABLE: Remap     STM32F100:(TIM13_CH1 on PF8). Others:(TIM13_CH1 on PB0).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM13_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM13_REMAP)

/**
  * @brief Disable the remapping of TIM13_CH1.
  * @note  DISABLE: No remap STM32F100:(TIM13_CH1 on PA6). Others:(TIM13_CH1 on PC8).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM13_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM13_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM14_REMAP)

/**
  * @brief Enable the remapping of TIM14_CH1.
  * @note  ENABLE: Remap     STM32F100:(TIM14_CH1 on PB1). Others:(TIM14_CH1 on PF9).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM14_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM14_REMAP)

/**
  * @brief Disable the remapping of TIM14_CH1.
  * @note  DISABLE: No remap STM32F100:(TIM14_CH1 on PC9). Others:(TIM14_CH1 on PA7).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM14_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM14_REMAP)
#endif

#if defined(AFIO_MAPR2_FSMC_NADV_REMAP)

/**
  * @brief Controls the use of the optional FSMC_NADV signal.
  * @note  DISCONNECTED: The NADV signal is not connected. The I/O pin can be used by another peripheral.
  * @retval None
  */
#define __HAL_AFIO_FSMCNADV_DISCONNECTED() SET_BIT(AFIO->MAPR2, AFIO_MAPR2_FSMC_NADV_REMAP)

/**
  * @brief Controls the use of the optional FSMC_NADV signal.
  * @note  CONNECTED: The NADV signal is connected to the output (default).
  * @retval None
  */
#define __HAL_AFIO_FSMCNADV_CONNECTED()    CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_FSMC_NADV_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM15_REMAP)

/**
  * @brief Enable the remapping of TIM15_CH1 and TIM15_CH2.
  * @note  ENABLE: Remap     (TIM15_CH1 on PB14 and TIM15_CH2 on PB15).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM15_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM15_REMAP)

/**
  * @brief Disable the remapping of TIM15_CH1 and TIM15_CH2.
  * @note  DISABLE: No remap (TIM15_CH1 on PA2  and TIM15_CH2 on PA3).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM15_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM15_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM16_REMAP)

/**
  * @brief Enable the remapping of TIM16_CH1.
  * @note  ENABLE: Remap     (TIM16_CH1 on PA6).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM16_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM16_REMAP)

/**
  * @brief Disable the remapping of TIM16_CH1.
  * @note  DISABLE: No remap (TIM16_CH1 on PB8).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM16_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM16_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM17_REMAP)

/**
  * @brief Enable the remapping of TIM17_CH1.
  * @note  ENABLE: Remap     (TIM17_CH1 on PA7).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM17_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM17_REMAP)

/**
  * @brief Disable the remapping of TIM17_CH1.
  * @note  DISABLE: No remap (TIM17_CH1 on PB9).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM17_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM17_REMAP)
#endif

#if defined(AFIO_MAPR2_CEC_REMAP)

/**
  * @brief Enable the remapping of CEC.
  * @note  ENABLE: Remap     (CEC on PB10).
  * @retval None
  */
#define __HAL_AFIO_REMAP_CEC_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_CEC_REMAP)

/**
  * @brief Disable the remapping of CEC.
  * @note  DISABLE: No remap (CEC on PB8).
  * @retval None
  */
#define __HAL_AFIO_REMAP_CEC_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_CEC_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM1_DMA_REMAP)

/**
  * @brief Controls the mapping of the TIM1_CH1 TIM1_CH2 DMA requests onto the DMA1 channels.
  * @note  ENABLE: Remap (TIM1_CH1 DMA request/DMA1 Channel6, TIM1_CH2 DMA request/DMA1 Channel6)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM1DMA_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM1_DMA_REMAP)

/**
  * @brief Controls the mapping of the TIM1_CH1 TIM1_CH2 DMA requests onto the DMA1 channels.
  * @note  DISABLE: No remap (TIM1_CH1 DMA request/DMA1 Channel2, TIM1_CH2 DMA request/DMA1 Channel3).
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM1DMA_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM1_DMA_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM67_DAC_DMA_REMAP)

/**
  * @brief Controls the mapping of the TIM6_DAC1 and TIM7_DAC2 DMA requests onto the DMA1 channels.
  * @note  ENABLE: Remap (TIM6_DAC1 DMA request/DMA1 Channel3, TIM7_DAC2 DMA request/DMA1 Channel4)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM67DACDMA_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM67_DAC_DMA_REMAP)

/**
  * @brief Controls the mapping of the TIM6_DAC1 and TIM7_DAC2 DMA requests onto the DMA1 channels.
  * @note  DISABLE: No remap (TIM6_DAC1 DMA request/DMA2 Channel3, TIM7_DAC2 DMA request/DMA2 Channel4)
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM67DACDMA_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM67_DAC_DMA_REMAP)
#endif

#if defined(AFIO_MAPR2_TIM12_REMAP)

/**
  * @brief Enable the remapping of TIM12_CH1 and TIM12_CH2.
  * @note  ENABLE: Remap     (TIM12_CH1 on PB12 and TIM12_CH2 on PB13).
  * @note  This bit is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM12_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM12_REMAP)

/**
  * @brief Disable the remapping of TIM12_CH1 and TIM12_CH2.
  * @note  DISABLE: No remap (TIM12_CH1 on PC4  and TIM12_CH2 on PC5).
  * @note  This bit is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_TIM12_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_TIM12_REMAP)
#endif

#if defined(AFIO_MAPR2_MISC_REMAP)

/**
  * @brief Miscellaneous features remapping.
  *        This bit is set and cleared by software. It controls miscellaneous features.
  *        The DMA2 channel 5 interrupt position in the vector table.
  *        The timer selection for DAC trigger 3 (TSEL[2:0] = 011, for more details refer to the DAC_CR register).
  * @note  ENABLE: DMA2 channel 5 interrupt is mapped separately at position 60 and TIM15 TRGO event is
  *        selected as DAC Trigger 3, TIM15 triggers TIM1/3.
  * @note  This bit is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_MISC_ENABLE()  SET_BIT(AFIO->MAPR2, AFIO_MAPR2_MISC_REMAP)

/**
  * @brief Miscellaneous features remapping.
  *        This bit is set and cleared by software. It controls miscellaneous features.
  *        The DMA2 channel 5 interrupt position in the vector table.
  *        The timer selection for DAC trigger 3 (TSEL[2:0] = 011, for more details refer to the DAC_CR register).
  * @note  DISABLE: DMA2 channel 5 interrupt is mapped with DMA2 channel 4 at position 59, TIM5 TRGO
  *        event is selected as DAC Trigger 3, TIM5 triggers TIM1/3.
  * @note  This bit is available only in high density value line devices.
  * @retval None
  */
#define __HAL_AFIO_REMAP_MISC_DISABLE() CLEAR_BIT(AFIO->MAPR2, AFIO_MAPR2_MISC_REMAP)
#endif

/**
  * @}
  */ 
  
/**
  * @}
  */
  
/** @defgroup GPIOEx_Private_Macros GPIOEx Private Macros
  * @{
  */
#if defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F102xB) || defined(STM32F103x6)
#define GPIO_GET_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :3U)
#elif defined(STM32F100xB) || defined(STM32F101xB) || defined(STM32F103xB) || defined(STM32F105xC) || defined(STM32F107xC)
#define GPIO_GET_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :\
                                   ((__GPIOx__) == (GPIOD))? 3U :4U)
#elif defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
#define GPIO_GET_INDEX(__GPIOx__) (((__GPIOx__) == (GPIOA))? 0U :\
                                   ((__GPIOx__) == (GPIOB))? 1U :\
                                   ((__GPIOx__) == (GPIOC))? 2U :\
                                   ((__GPIOx__) == (GPIOD))? 3U :\
                                   ((__GPIOx__) == (GPIOE))? 4U :\
                                   ((__GPIOx__) == (GPIOF))? 5U :6U)
#endif

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup GPIOEx_Exported_Functions
  * @{
  */

/** @addtogroup GPIOEx_Exported_Functions_Group1
  * @{
  */
void HAL_GPIOEx_ConfigEventout(uint32_t GPIO_PortSource, uint32_t GPIO_PinSource);
void HAL_GPIOEx_EnableEventout(void);
void HAL_GPIOEx_DisableEventout(void);

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

#endif /* __STM32F1xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
