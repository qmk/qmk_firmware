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
#if !defined(__FSL_PMC_HAL_H__)
#define __FSL_PMC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#include "fsl_pmc_features.h"

/*! @addtogroup pmc_hal*/
/*! @{*/

/*! @file fsl_pmc_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Low-Voltage Warning Voltage Select*/
typedef enum _pmc_low_volt_warn_volt_select {
    kPmcLowVoltWarnVoltLowTrip,             /*!< Low trip point selected (VLVW = VLVW1)*/
    kPmcLowVoltWarnVoltMid1Trip,            /*!< Mid 1 trip point selected (VLVW = VLVW2)*/
    kPmcLowVoltWarnVoltMid2Trip,            /*!< Mid 2 trip point selected (VLVW = VLVW3)*/
    kPmcLowVoltWarnVoltHighTrip             /*!< High trip point selected (VLVW = VLVW4)*/
} pmc_low_volt_warn_volt_select_t;

/*! @brief Low-Voltage Detect Voltage Select*/
typedef enum _pmc_low_volt_detect_volt_select {
    kPmcLowVoltDetectVoltLowTrip,           /*!< Low trip point selected (V LVD = V LVDL )*/
    kPmcLowVoltDetectVoltHighTrip,          /*!< High trip point selected (V LVD = V LVDH )*/
} pmc_low_volt_detect_volt_select_t;

/*! @brief interrupt control*/
typedef enum _pmc_int_select {
    kPmcIntLowVoltDetect,                   /*!< Low Voltage Detect Interrupt */
    kPmcIntLowVoltWarn,                     /*!< Low Voltage Warning Interrupt */
} pmc_int_select_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Power Management Controller Control APIs*/
/*@{*/


/*!
 * @brief Enables/Disables low voltage-related interrupts.
 *
 * This function  enables  the interrupt for the low voltage detection, warning, 
 * etc. When enabled, if the LVDF (Low Voltage Detect Flag) is set, a hardware 
 * interrupt occurs.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @param intSelect interrut select
 * @param enable    enable/disable the interrupt
 */
void PMC_HAL_SetLowVoltIntCmd(uint32_t baseAddr, pmc_int_select_t intSelect, bool enable);

/*!
 * @brief Low-Voltage Detect Hardware Reset Enable/Disable (write once)
 *
 * This function enables/disables the  hardware reset for the low voltage 
 * detection. When enabled, if the LVDF (Low Voltage Detect Flag) is set, a 
 * hardware reset occurs. This setting is a write-once-only. Any additional writes 
 * are ignored.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @param enable    enable/disable the LVD hardware reset
 */
static inline void PMC_HAL_SetLowVoltDetectResetCmd(uint32_t baseAddr, bool enable)
{
    BW_PMC_LVDSC1_LVDRE(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Low-Voltage Detect Acknowledge
 *
 * This function acknowledges the low voltage detection errors (write 1 to
 * clear LVDF).
 *
 * @param baseAddr  Base address for current PMC instance.
 */
static inline void PMC_HAL_SetLowVoltDetectAck(uint32_t baseAddr)
{
    BW_PMC_LVDSC1_LVDACK(baseAddr, 1);
}

/*!
 * @brief Low-Voltage Detect Flag Read
 *
 * This function  reads the current LVDF status. If it returns 1, a low
 * voltage event is detected.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return status Current low voltage detect flag
 *                - true: Low-Voltage detected
 *                - false: Low-Voltage not detected
 */
static inline bool PMC_HAL_GetLowVoltDetectFlag(uint32_t baseAddr)
{
    return BR_PMC_LVDSC1_LVDF(baseAddr);
}

/*!
 * @brief Sets the Low-Voltage Detect Voltage Mode
 *
 * This function  sets the low voltage detect voltage select. It  sets
 * the low voltage detect trip point voltage (Vlvd). An application can select
 * either a low-trip or a high-trip point. See a chip reference manual for details.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @param select Voltage select setting defined in pmc_lvdv_select_t
 */
static inline void PMC_HAL_SetLowVoltDetectVoltMode(uint32_t baseAddr, pmc_low_volt_detect_volt_select_t select)
{
    BW_PMC_LVDSC1_LVDV(baseAddr, select);
}

/*!
 * @brief Gets the Low-Voltage Detect Voltage Mode
 *
 * This function  gets the low voltage detect voltage select. It  gets 
 * the low voltage detect trip point voltage (Vlvd). An application can select
 * either a low-trip or a high-trip point. See a chip reference manual for details.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return select Current voltage select setting
 */
static inline pmc_low_volt_detect_volt_select_t PMC_HAL_GetLowVoltDetectVoltMode(uint32_t baseAddr)
{
    return (pmc_low_volt_detect_volt_select_t)BR_PMC_LVDSC1_LVDV(baseAddr);
}

/*!
 * @brief Low-Voltage Warning Acknowledge
 * 
 * This function acknowledges the low voltage warning errors (write 1 to
 * clear LVWF).
 *
 * @param baseAddr  Base address for current PMC instance.
 */
static inline void PMC_HAL_SetLowVoltWarnAck(uint32_t baseAddr)
{
    BW_PMC_LVDSC2_LVWACK(baseAddr, 1);
}

/*!
 * @brief Low-Voltage Warning Flag Read
 *
 * This function polls the current LVWF status. When 1 is returned, it 
 * indicates a low-voltage warning event. LVWF is set when V Supply transitions
 * below the trip point or after reset and V Supply is already below the V LVW.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return status Current LVWF status
 *                  - true: Low-Voltage Warning Flag is set.
 *                  - false: the  Low-Voltage Warning does not happen.
 */
static inline bool PMC_HAL_GetLowVoltWarnFlag(uint32_t baseAddr)
{
    return BR_PMC_LVDSC2_LVWF(baseAddr);
}

/*!
 * @brief Sets the Low-Voltage Warning Voltage Mode.
 *
 * This function  sets the low voltage warning voltage select. It  sets
 * the low voltage warning trip point voltage (Vlvw). An application can select
 * either a low, mid1, mid2 and a high-trip point. See a chip reference manual for 
 * details and the  pmc_lvwv_select_t for supported settings.
 * 
 * @param baseAddr  Base address for current PMC instance.
 * @param select Low voltage warning select setting
 */
static inline void PMC_HAL_SetLowVoltWarnVoltMode(uint32_t baseAddr, pmc_low_volt_warn_volt_select_t select)
{
    BW_PMC_LVDSC2_LVWV(baseAddr, select);
}

/*!
 * @brief Gets the Low-Voltage Warning Voltage Mode.
 *
 * This function  gets the low voltage warning voltage select. It  gets
 * the low voltage warning trip point voltage (Vlvw). See the pmc_lvwv_select_t
 * for  supported settings.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return select Current low voltage warning select setting
 */
static inline pmc_low_volt_warn_volt_select_t PMC_HAL_GetLowVoltWarnVoltMode(uint32_t baseAddr)
{
    return (pmc_low_volt_warn_volt_select_t)BR_PMC_LVDSC2_LVWV(baseAddr);
}

#if FSL_FEATURE_PMC_HAS_BGEN
/*!
 * @brief Enables the Bandgap in the VLPx Operation.
 *
 * This function enables/disables the bandgap in lower power modes
 * (VLPx, * LLS, and VLLSx). When on-chip peripherals require the bandgap voltage 
 * reference in low power modes, set the BGEN to continue to enable
 * the bandgap operation.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @param enable    enable/disable the Bangap.
 */
static inline void PMC_HAL_SetBandgapInLowPowerModeCmd(uint32_t baseAddr, bool enable)
{
    BW_PMC_REGSC_BGEN(baseAddr, enable);
}
#endif

/*!
 * @brief Enables/Disables the Bandgap Buffer.
 *
 * This function  enables/disables the Bandgap buffer.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @param enable    enable/disable the Bangap Buffer.
 */
static inline void PMC_HAL_SetBandgapBufferCmd(uint32_t baseAddr, bool enable)
{
    BW_PMC_REGSC_BGBE(baseAddr, enable);
}

/*!
 * @brief Gets the acknowledge isolation value.
 *
 * This function  reads the Acknowledge Isolation setting that indicates 
 * whether certain peripherals and the I/O pads are in a latched state as 
 * a result of having been in the VLLS mode. 
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return value ACK isolation
 *               0 - Peripherals and I/O pads are in a normal run state.
 *               1 - Certain peripherals and I/O pads are in an isolated and
 *                   latched state.
 */
static inline uint8_t PMC_HAL_GetAckIsolation(uint32_t baseAddr)
{
    return BR_PMC_REGSC_ACKISO(baseAddr);
}

/*!
 * @brief Clears an acknowledge isolation.
 *
 * This function  clears the ACK Isolation flag. Writing one to this setting
 * when it is set releases the I/O pads and certain peripherals to their normal
 * run mode state.
 *
 * @param baseAddr  Base address for current PMC instance.
 */
static inline void PMC_HAL_SetClearAckIsolation(uint32_t baseAddr)
{
    BW_PMC_REGSC_ACKISO(baseAddr, 1);
}

/*!
 * @brief Gets the Regulator regulation status.
 *
 * This function  returns the regulator to a run regulation status. It provides
 * the current status of the internal voltage regulator.
 *
 * @param baseAddr  Base address for current PMC instance.
 * @return value Regulation status
 *               0 - Regulator is in a stop regulation or in transition to/from it.
 *               1 - Regulator is in a run regulation.
 *
 */
static inline uint8_t PMC_HAL_GetRegulatorStatus(uint32_t baseAddr)
{
    return BR_PMC_REGSC_REGONS(baseAddr);
}

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_PMC_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

