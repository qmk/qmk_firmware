/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __FSL_LPTMR_HAL_H__
#define __FSL_LPTMR_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_lptmr_features.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup lptmr_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief LPTMR pin selection.*/
typedef enum _lptmr_pin_select{
    kLptmrPinSelectCmpOut    = 0x0U, /*!< Lptmr Pin is CMP0 output pin.*/
    kLptmrPinSelectLptmrAlt1 = 0x1U, /*!< Lptmr Pin is LPTMR_ALT1 pin.*/
    kLptmrPinSelectLptmrAlt2 = 0x2U, /*!< Lptmr Pin is LPTMR_ALT2 pin.*/
    kLptmrPinSelectLptmrAlt3 = 0x3U  /*!< Lptmr Pin is LPTMR_ALT3 pin.*/
} lptmr_pin_select_t;

/*! @brief LPTMR pin polarity, used while in pluse counter mode.*/
typedef enum _lptmr_pin_polarity{
    kLptmrPinPolarityActiveHigh = 0x0U, /*!< Pulse Counter input source is active-high.*/
    kLptmrPinPolarityActiveLow  = 0x1U /*!< Pulse Counter input source is active-low.*/
} lptmr_pin_polarity_t;

/*! @brief LPTMR timer mode selection.*/
typedef enum _lptmr_timer_mode{
    kLptmrTimerModeTimeCounter = 0x0U, /*!< Time Counter mode.*/
    kLptmrTimerModePluseCounter = 0x1U  /*!< Pulse Counter mode.*/
} lptmr_timer_mode_t;

/*! @brief LPTMR proscaler value.*/
typedef enum _lptmr_prescaler_value{
    kLptmrPrescalerDivide2                     = 0x0U, /*!< Prescaler divide 2, glitch filter invalid.*/
    kLptmrPrescalerDivide4GlichFiltch2         = 0x1U, /*!< Prescaler divide 4, glitch filter 2.*/
    kLptmrPrescalerDivide8GlichFiltch4         = 0x2U, /*!< Prescaler divide 8, glitch filter 4.*/
    kLptmrPrescalerDivide16GlichFiltch8        = 0x3U, /*!< Prescaler divide 16, glitch filter 8.*/
    kLptmrPrescalerDivide32GlichFiltch16       = 0x4U, /*!< Prescaler divide 32, glitch filter 16.*/
    kLptmrPrescalerDivide64GlichFiltch32       = 0x5U, /*!< Prescaler divide 64, glitch filter 32.*/
    kLptmrPrescalerDivide128GlichFiltch64      = 0x6U, /*!< Prescaler divide 128, glitch filter 64.*/
    kLptmrPrescalerDivide256GlichFiltch128     = 0x7U, /*!< Prescaler divide 256, glitch filter 128.*/
    kLptmrPrescalerDivide512GlichFiltch256     = 0x8U, /*!< Prescaler divide 512, glitch filter 256.*/
    kLptmrPrescalerDivide1024GlichFiltch512    = 0x9U, /*!< Prescaler divide 1024, glitch filter 512.*/
    kLptmrPrescalerDivide2048lichFiltch1024    = 0xAU, /*!< Prescaler divide 2048 glitch filter 1024.*/
    kLptmrPrescalerDivide4096GlichFiltch2048   = 0xBU, /*!< Prescaler divide 4096, glitch filter 2048.*/
    kLptmrPrescalerDivide8192GlichFiltch4096   = 0xCU, /*!< Prescaler divide 8192, glitch filter 4096.*/
    kLptmrPrescalerDivide16384GlichFiltch8192  = 0xDU, /*!< Prescaler divide 16384, glitch filter 8192.*/
    kLptmrPrescalerDivide32768GlichFiltch16384 = 0xEU, /*!< Prescaler divide 32768, glitch filter 16384.*/
    kLptmrPrescalerDivide65535GlichFiltch32768 = 0xFU  /*!< Prescaler divide 65535, glitch filter 32768.*/
} lptmr_prescaler_value_t;

/*! @brief LPTMR clock source selection.*/
typedef enum _lptmr_prescaler_clock_source{
    kLptmrPrescalerClockSourceMcgIrcClk = 0x0U, /*!< Clock source is MCGIRCLK.*/
    kLptmrPrescalerClockSourceLpo       = 0x1U, /*!< Clock source is LPO.*/
    kLptmrPrescalerClockSourceErClk32K  = 0x2U, /*!< Clock source is ERCLK32K.*/
    kLptmrPrescalerClockSourceOscErClk  = 0x3U  /*!< Clock source is OSCERCLK.*/
} lptmr_prescaler_clock_source_t;

/*! @brief LPTMR status return codes.*/
typedef enum _lptmr_status {
    kStatus_LPTMR_Success                   = 0x0U, /*!< Succeed. */
    kStatus_LPTMR_NotInitlialized           = 0x1U, /*!< LPTMR is not initialized yet. */
    kStatus_LPTMR_NullArgument              = 0x2U, /*!< Argument is NULL.*/
    kStatus_LPTMR_InvalidPrescalerValue     = 0x3U, /*!< Value 0 is not valid in pulse counter mode. */
    kStatus_LPTMR_InvalidInTimeCounterMode  = 0x4U, /*!< Function can not called in time counter mode. */
    kStatus_LPTMR_InvalidInPluseCounterMode = 0x5U, /*!< Function can not called in pulse counter mode. */
    kStatus_LPTMR_InvalidPlusePeriodCount   = 0x6U, /*!< Pulse period count must be integer multiples of the glitch filter divider. */
    kStatus_LPTMR_TcfNotSet                 = 0x7U, /*!< If LPTMR is enabled, compare register can only altered when TCF is set. */
    kStatus_LPTMR_TimerPeriodUsTooSmall     = 0x8U, /*!< Timer period time is too small for current clock source. */
    kStatus_LPTMR_TimerPeriodUsTooLarge     = 0x9U  /*!< Timer period time is too large for current clock source. */
 } lptmr_status_t;
 
/*******************************************************************************
 ** Variables
 *******************************************************************************/

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPTMR HAL.
 * @{
 */

/*!
 * @brief Enables the LPTMR module operation.
 *
 * @param baseAddr The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_Enable(uint32_t baseAddr)
{
    BW_LPTMR_CSR_TEN(baseAddr, (uint8_t)true);
}

/*!
 * @brief Disables the LPTMR module operation.
 *
 * @param baseAddr The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_Disable(uint32_t baseAddr)
{
    BW_LPTMR_CSR_TEN(baseAddr, (uint8_t)false);
}

/*!
 * @brief Checks whether the LPTMR module is enabled.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @retval true LPTMR module is enabled.
 * @retval false LPTMR module is disabled.
 */
static inline bool LPTMR_HAL_IsEnabled(uint32_t baseAddr)
{
    return (bool)BR_LPTMR_CSR_TEN(baseAddr);
}

/*!
 * @brief Clears the LPTMR interrupt flag if set.
 *
 * @param baseAddr The LPTMR peripheral base address.
 */
static inline void LPTMR_HAL_ClearIntFlag(uint32_t baseAddr)
{
    BW_LPTMR_CSR_TCF(baseAddr, 1);
}

/*!
 * @brief Returns the current LPTMR interrupt flag.
 *
 * @param baseAddr The LPTMR peripheral base address
 * @retval true An interrupt is pending.
 * @retval false No interrupt is pending.
 */
static inline bool LPTMR_HAL_IsIntPending(uint32_t baseAddr)
{
    return ((bool)BR_LPTMR_CSR_TCF(baseAddr));
}

/*!
 * @brief Enables or disables the LPTMR interrupt.
 *
 * @param baseAddr The LPTMR peripheral base address
 * @param enable Pass true to enable LPTMR interrupt
 */
static inline void LPTMR_HAL_SetIntCmd(uint32_t baseAddr,  bool enable)
{
    BW_LPTMR_CSR_TIE(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Returns whether the LPTMR interrupt is enabled.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @retval true LPTMR interrupt is enabled.
 * @retval false LPTMR interrupt is disabled.
 */
static inline bool LPTMR_HAL_GetIntCmd(uint32_t baseAddr)
{
    return ((bool)BR_LPTMR_CSR_TIE(baseAddr));
}

/*!
 * @brief Selects the LPTMR pulse input pin select.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param pinSelect Specifies LPTMR pulse input pin select, see #lptmr_pin_select_t
 */
static inline void LPTMR_HAL_SetPinSelectMode(uint32_t baseAddr,  lptmr_pin_select_t pinSelect)
{
    BW_LPTMR_CSR_TPS(baseAddr, (uint8_t)pinSelect);
}

/*!
 * @brief Returns the LPTMR pulse input pin select.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return LPTMR pulse input pin select, see #lptmr_pin_select_t
 */
static inline lptmr_pin_select_t LPTMR_HAL_GetPinSelectMode(uint32_t baseAddr)
{
    return (lptmr_pin_select_t)BR_LPTMR_CSR_TPS(baseAddr);
}

/*!
 * @brief Selects the LPTMR pulse input pin polarity.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param pinPolarity Specifies LPTMR pulse input pin polarity, see #lptmr_pin_polarity_t
 */
static inline void LPTMR_HAL_SetPinPolarityMode(uint32_t baseAddr,  lptmr_pin_polarity_t pinPolarity)
{
    BW_LPTMR_CSR_TPP(baseAddr, (uint8_t)pinPolarity);
}

/*!
 * @brief Returns the LPTMR pulse input pin polarity.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return LPTMR pulse input pin polarity, see #lptmr_pin_polarity_t
 */
static inline lptmr_pin_polarity_t LPTMR_HAL_GetPinPolarityMode(uint32_t baseAddr)
{
    return (lptmr_pin_polarity_t)BR_LPTMR_CSR_TPP(baseAddr);
}

/*!
 * @brief Enables or disables the LPTMR free running.
 *
 * @param baseAddr The LPTMR peripheral base address
 * @param enable Pass true to enable LPTMR free running
 */
static inline void LPTMR_HAL_SetFreeRunningCmd(uint32_t baseAddr,  bool enable)
{
    BW_LPTMR_CSR_TFC(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Returns whether the LPTMR free running is enabled.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @retval true LPTMR free running is enabled.
 * @retval false LPTMR free running is disabled.
 */
static inline bool LPTMR_HAL_GetFreeRunningCmd(uint32_t baseAddr)
{
    return ((bool)BR_LPTMR_CSR_TFC(baseAddr));
}

/*!
 * @brief Selects the LPTMR working mode.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param timerMode Specifies LPTMR working mode, see #lptmr_timer_mode_t
 */
static inline void LPTMR_HAL_SetTimerModeMode(uint32_t baseAddr,  lptmr_timer_mode_t timerMode)
{
    BW_LPTMR_CSR_TMS(baseAddr, (uint8_t)timerMode);
}

/*!
 * @brief Returns the LPTMR working mode.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return LPTMR working mode, see #lptmr_timer_mode_t
 */
static inline lptmr_timer_mode_t LPTMR_HAL_GetTimerModeMode(uint32_t baseAddr)
{
    return (lptmr_timer_mode_t)BR_LPTMR_CSR_TMS(baseAddr);
}

/*!
 * @brief Selects the LPTMR prescaler value.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param prescaleValue Specifies LPTMR prescaler value, see #lptmr_prescaler_value_t
 */
static inline void LPTMR_HAL_SetPrescalerValueMode(uint32_t baseAddr,  lptmr_prescaler_value_t prescaleValue)
{
    BW_LPTMR_PSR_PRESCALE(baseAddr, (uint8_t)prescaleValue);
}

/*!
 * @brief Returns the LPTMR prescaler value.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return LPTMR prescaler value, see #lptmr_prescaler_value_t
 */
static inline lptmr_prescaler_value_t LPTMR_HAL_GetPrescalerValueMode(uint32_t baseAddr)
{
    return (lptmr_prescaler_value_t)BR_LPTMR_PSR_PRESCALE(baseAddr);
}

/*!
 * @brief Enables or disables the LPTMR prescaler.
 *
 * @param baseAddr The LPTMR peripheral base address
 * @param enable Pass true to enable LPTMR free running
 */
static inline void LPTMR_HAL_SetPrescalerCmd(uint32_t baseAddr,  bool enable)
{
    BW_LPTMR_PSR_PBYP(baseAddr, (uint8_t)(enable == false)); /* 1 means disable prelsaler , 0 means enalbe prescaler */
}

/*!
 * @brief Returns whether the LPTMR prescaler is enabled.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @retval true LPTMR prescaler is enabled.
 * @retval false LPTMR prescaler is disabled.
 */
static inline bool LPTMR_HAL_GetPrescalerCmd(uint32_t baseAddr)
{
    return (bool)(0 == BR_LPTMR_PSR_PBYP(baseAddr)); /* 1 means prelsaler is disabled, 0 means prescaler is enalbed*/
}

/*!
 * @brief Selects the LPTMR clock source.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param prescalerClockSource Specifies LPTMR clock source, see #lptmr_prescaler_clock_source_t
 */
static inline void LPTMR_HAL_SetPrescalerClockSourceMode(uint32_t baseAddr,  lptmr_prescaler_clock_source_t prescalerClockSource)
{
    BW_LPTMR_PSR_PCS(baseAddr, (uint8_t)prescalerClockSource);
}

/*!
 * @brief Gets the LPTMR clock source.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return LPTMR clock source, see #lptmr_prescaler_clock_source_t
 */
static inline lptmr_prescaler_clock_source_t LPTMR_HAL_GetPrescalerClockSourceMode(uint32_t baseAddr)
{
    return (lptmr_prescaler_clock_source_t)BR_LPTMR_PSR_PCS(baseAddr);
}

/*!
 * @brief Sets the LPTMR compare value.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @param compareValue Specifies LPTMR compare value, less than 0xFFFFU
 */
static inline void LPTMR_HAL_SetCompareValue(uint32_t baseAddr,  uint32_t compareValue)
{
    BW_LPTMR_CMR_COMPARE(baseAddr, compareValue & 0xFFFFU);
}

/*!
 * @brief Gets the LPTMR compare value.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return Current LPTMR compare value
 */
static inline uint32_t LPTMR_HAL_GetCompareValue(uint32_t baseAddr)
{
    return (uint32_t)(BR_LPTMR_CMR_COMPARE(baseAddr) & 0xFFFFU);
}

/*!
 * @brief Gets the LPTMR counter value.
 *
 * @param baseAddr The LPTMR peripheral base address.
 * @return Current LPTMR counter value
 */
static inline uint32_t LPTMR_HAL_GetCounterValue(uint32_t baseAddr)
{
    BW_LPTMR_CNR_COUNTER(baseAddr, 0);  /* Must first write to the CNR with any value */
    return (uint32_t)(BR_LPTMR_CNR_COUNTER(baseAddr) & 0xFFFFU);
}

/*!
 * @brief Restores the LPTMR module to reset state.
 *
 * @param baseAddr The LPTMR peripheral base address
 */
void LPTMR_HAL_Init(uint32_t baseAddr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_LPTMR_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

