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
#ifndef __FSL_WDOG_HAL_H__
#define __FSL_WDOG_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_wdog_features.h"
#include "fsl_device_registers.h"

/*! 
 * @addtogroup wdog_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

#define WDOG_UNLOCK_VALUE_HIGH (0xC520U)
#define WDOG_UNLOCK_VALUE_LOW (0xD928U)

#define WDOG_REFRESH_VALUE_HIGH (0xA602U)
#define WDOG_REFRESH_VALUE_LOW (0xB480U)

/*! @brief Watchdog clock source selection.*/
typedef enum _wdog_clock_source {
    kWdogClockSourceLpoClock = 0x0U, /*!< Clock source is LPO clock */
    kWdogClockSourceBusClock = 0x1U  /*!< Clock source is Bus clock */
} wdog_clock_source_t;

/*! @brief Define the selection of the clock prescaler*/
typedef enum _wdog_clock_prescaler_value {
    kWdogClockPrescalerValueDevide1 = 0x0U, /*!< Divided by 1 */
    kWdogClockPrescalerValueDevide2 = 0x1U, /*!< Divided by 2 */
    kWdogClockPrescalerValueDevide3 = 0x2U, /*!< Divided by 3 */
    kWdogClockPrescalerValueDevide4 = 0x3U, /*!< Divided by 4 */
    kWdogClockPrescalerValueDevide5 = 0x4U, /*!< Divided by 5 */
    kWdogClockPrescalerValueDevide6 = 0x5U, /*!< Divided by 6 */
    kWdogClockPrescalerValueDevide7 = 0x6U, /*!< Divided by 7 */
    kWdogClockPrescalerValueDevide8 = 0x7U  /*!< Divided by 8 */
} wdog_clock_prescaler_value_t;

/*! @brief Define the common configure */
typedef union _wdog_common_config {
    uint32_t U;
    struct CommonConfig {
        uint32_t wdogEnable:1; /*!< Enable configure, 1 means enable WDOG */
        uint32_t clockSource:1; /*!< Clock source */
        uint32_t interruptEnable:1; /*!< WDOG interrupt configure, 1 means enable interrupt */
        uint32_t windowModeEnable:1; /*!< Window mode configure, 1 means enable window mode */
        uint32_t updateRegisterEnable:1; /*!< 1 means WDOG register can reconfigure by unlock */
        uint32_t workInDebugModeEnable:1; /*!< 1 means WDOG works while CPU in Debug mode */
        uint32_t workInStopModeEnable:1; /*!< 1 means WDOG works while CPU in Debug mode */
        uint32_t workInWaitModeEnable:1; /*!< 1 means WDOG works while CPU in Debug mode */
        uint32_t reserved0:1; /*!< Reserved */
        uint32_t reserved1:1; /*!< Reserved */
        uint32_t testWdog:1; /*!< WDOG enable configure */
        uint32_t testSelect:1; /*!< 0 means quick test, 1 means byte test */
        uint32_t byteSelect:2; /*!< Test byte select */
        uint32_t disableTestWdog:1; /*!< 1 means WDOG test mode is disabled */
        uint32_t reserved2:1;  /*!< Reserved */
        uint32_t reserved3:16;  /*!< Reserved */
    } commonConfig;
} wdog_common_config;


/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name Watchdog HAL.
 * @{
 */

/*!
 * @brief Sets the WDOG common configure.
 *
 * This function is used to set the WDOG common configure.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, the WCT window is still open and
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure that the WDOG_STCTRLH.ALLOWUPDATE is 1 which means that the register update is enabled.
 * The common configuration is controlled by the WDOG_STCTRLH. This is a write-once register and this interface 
 * is used to set all field of the WDOG_STCTRLH registers at the same time. 
 * If only one field needs to be set, the API can be used. These API write to the WDOG_STCTRLH register:
 * #WDOG_HAL_Enable,#WDOG_HAL_Disable,#WDOG_HAL_SetIntCmd,#WDOG_HAL_SetClockSourceMode,#WDOG_HAL_SetWindowModeCmd,
 * #WDOG_HAL_SetRegisterUpdateCmd,#WDOG_HAL_SetWorkInDebugModeCmd,#WDOG_HAL_SetWorkInStopModeCmd,
 * #WDOG_HAL_SetWorkInWaitModeCmd
 *
 * @param baseAddr The WDOG peripheral base address
 * @param commonConfig The common configure of the WDOG 
 */
static inline void WDOG_HAL_SetCommonConfig(uint32_t baseAddr, wdog_common_config commonConfig)
{
    HW_WDOG_STCTRLH_WR(baseAddr,(uint16_t)commonConfig.U);
}

/*!
 * @brief Enables the Watchdog module.
 *
 * This function enables the WDOG.
 * Make sure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_Enable(uint32_t baseAddr)
{
    BW_WDOG_STCTRLH_WDOGEN(baseAddr, (uint8_t)true);
}

/*!
 * @brief Disables the Watchdog module.
 * 
 * This function disables the WDOG.
 * Make sure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_Disable(uint32_t baseAddr)
{
    BW_WDOG_STCTRLH_WDOGEN(baseAddr, (uint8_t)false);
}

/*!
 * @brief Checks whether the WDOG is enabled.
 * 
 * This function checks whether the WDOG is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means WDOG is disabled, true means WODG is enabled.
 *
 */
static inline bool WDOG_HAL_IsEnabled(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_WDOGEN(baseAddr);
}

/*!
 * @brief Enables and disables the Watchdog interrupt.
 *
 * This function enables or disables the WDOG interrupt.
 * Make sure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means disable watchdog interrupt and true means enable watchdog interrupt.
 */
static inline void WDOG_HAL_SetIntCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_IRQRSTEN(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the WDOG interrupt is enabled.
 *
 * This function checks whether the WDOG interrupt is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means interrupt is disabled, true means interrupt is enabled.
 */
static inline bool WDOG_HAL_GetIntCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_IRQRSTEN(baseAddr);
}

/*!
 * @brief Sets the Watchdog clock Source.
 *
 * This function sets the WDOG clock source. There are two clock sources that can be used:
 * the LPO clock and the bus clock.
 * Make sure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param clockSource watchdog clock source, see #wdog_clock_source_t.
 */
static inline void WDOG_HAL_SetClockSourceMode(uint32_t baseAddr,  wdog_clock_source_t clockSource)
{
    BW_WDOG_STCTRLH_CLKSRC(baseAddr, (uint8_t)clockSource);
}

/*!
 * @brief Gets the Watchdog clock Source.
 *
 * This function gets the WDOG clock source. There are two clock sources that can be used:
 * the LPO clock and the bus clock.
 * A Clock Switching Delay time is about 2 clock A cycles plus 2
 * clock B, where clock A and B are the two input clocks to the clock mux.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return watchdog clock source, see #wdog_clock_source_t.
 */
static inline wdog_clock_source_t WDOG_HAL_GetClockSourceMode(uint32_t baseAddr)
{
    return (wdog_clock_source_t)BR_WDOG_STCTRLH_CLKSRC(baseAddr);
}

/*!
 * @brief Enables and disables the Watchdog window mode.
 *
 * This function configures the WDOG window mode.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means disable watchdog window mode. true means enable watchdog window mode.
 */
static inline void WDOG_HAL_SetWindowModeCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_WINEN(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the window mode is enabled.
 *
 * This function checks whether the WDOG window mode is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means window mode is disabled, true means window mode is enabled.
 */
static inline bool WDOG_HAL_GetWindowModeCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_WINEN(baseAddr);
}

/*!
 * @brief Enables and disables the Watchdog write-once-only register update.
 *
 * This function configures the WDOG register update feature. If disabled, it means that
 * all WDOG registers is never  written again unless Power On Reset.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means disable watchdog write-once-only register update.
 *                  true means enable watchdog write-once-only register update.
 */
static inline void WDOG_HAL_SetRegisterUpdateCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_ALLOWUPDATE(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the register update is enabled.
 *
 * This function checks whether the WDOG register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means register update is disabled, true means register update is enabled.
 */
static inline bool WDOG_HAL_GetRegisterUpdateCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_ALLOWUPDATE(baseAddr);
}

/*!
 * @brief Sets whether Watchdog is working while the CPU is in debug mode.
 *
 * This function configures whether the WDOG is enabled in the CPU debug mode. 
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means watchdog is disabled in CPU debug mode.
 *                  true means watchdog is enabled in CPU debug mode.
 */
static inline void WDOG_HAL_SetWorkInDebugModeCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_DBGEN(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the WDOG works while in the CPU debug mode.
 *
 * This function checks whether the WDOG works in the CPU debug mode.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means not work while in CPU debug mode, true means works while in CPU debug mode.
 */
static inline bool WDOG_HAL_GetWorkInDebugModeCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_DBGEN(baseAddr);
}

/*!
 * @brief Sets whether the Watchdog is working while the CPU is in stop mode.
 *
 * This function configures whether the WDOG is enabled in the CPU stop mode. 
 * Make sure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means watchdog is disabled in CPU stop mode.
 *                  true means watchdog is enabled in CPU stop mode.
 */
static inline void WDOG_HAL_SetWorkInStopModeCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_STOPEN(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the WDOG works while in CPU stop mode.
 *
 * This function checks whether the WDOG works in the CPU stop mode.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means not work while in CPU stop mode, true means works while in CPU stop mode.
 */
static inline bool WDOG_HAL_GetWorkInStopModeCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_STOPEN(baseAddr);
}

/*!
 * @brief Sets whether the Watchdog is working while the CPU is in wait mode.
 *
 * This function configures whether the WDOG is enabled in the CPU wait mode. 
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open and that
 * the WDOG_STCTRLH register has not been written in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param enable false means watchdog is disabled in CPU wait mode.
 *                  true means watchdog is enabled in CPU wait mode.
 */
static inline void WDOG_HAL_SetWorkInWaitModeCmd(uint32_t baseAddr,  bool enable)
{
    BW_WDOG_STCTRLH_WAITEN(baseAddr, (uint8_t)enable);
}

/*!
 * @brief Checks whether the WDOG works while in the CPU wait mode.
 *
 * This function checks whether the WDOG works in the CPU wait mode.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return false means not work while in CPU wait mode, true means works while in CPU wait mode.
 */

static inline bool WDOG_HAL_GetWorkInWaitModeCmd(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLH_WAITEN(baseAddr);
}

/*!
 * @brief Gets the Watchdog interrupt status.
 *
 * This function gets the WDOG interrupt flag.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return Watchdog interrupt status, false means interrupt not asserted, true means interrupt asserted.
 */
static inline bool WDOG_HAL_IsIntPending(uint32_t baseAddr)
{
    return (bool)BR_WDOG_STCTRLL_INTFLG(baseAddr);
}

/*!
 * @brief Clears the  Watchdog interrupt flag.
 *
 * This function  clears the WDOG interrupt flag.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_ClearIntFlag(uint32_t baseAddr)
{
    BW_WDOG_STCTRLL_INTFLG(baseAddr, true);
}

/*!
 * @brief Set the Watchdog timeout value.
 *
 * This function sets the WDOG_TOVAL value.
 * It should be ensured that the time-out value for the Watchdog is always greater than
 * 2xWCT time + 20 bus clock cycles.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock , that the WCT window is still open and that
 * this API has not been called in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param timeoutCount watchdog timeout value, count of watchdog clock tick.
 */
static inline void WDOG_HAL_SetTimeoutValue(uint32_t baseAddr,  uint32_t timeoutCount)
{
    HW_WDOG_TOVALH_WR(baseAddr, (uint16_t)((timeoutCount >> 16U) & 0xFFFFU));
    HW_WDOG_TOVALL_WR(baseAddr, (uint16_t)((timeoutCount) & 0xFFFFU));
}

/*!
 * @brief Gets the Watchdog timeout value.
 *
 * This function gets the WDOG_TOVAL value.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return value of register WDOG_TOVAL.
 */
static inline uint32_t WDOG_HAL_GetTimeoutValue(uint32_t baseAddr)
{
    return (uint32_t)((((uint32_t)(HW_WDOG_TOVALH_RD(baseAddr))) << 16U) | (HW_WDOG_TOVALL_RD(baseAddr)));
}

/*!
 * @brief Gets the Watchdog timer output.
 *
 * This function gets the WDOG_TMROUT value.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return Current value of watchdog timer counter.
 */
static inline uint32_t WDOG_HAL_GetTimerOutputValue(uint32_t baseAddr)
{
    return (uint32_t)((((uint32_t)(HW_WDOG_TMROUTH_RD(baseAddr))) << 16U) | (HW_WDOG_TMROUTL_RD(baseAddr)));
}

/*!
 * @brief Sets the Watchdog clock prescaler.
 *
 * This function sets the WDOG clock prescaler.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock , that the WCT window is still open and that
 * this API has not been called in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 * 
 * @param baseAddr The WDOG peripheral base address
 * @param clockPrescaler watchdog clock prescaler, see #wdog_clock_prescaler_value_t.
 */
static inline void WDOG_HAL_SetClockPrescalerValueMode(uint32_t baseAddr,  wdog_clock_prescaler_value_t clockPrescaler)
{
    BW_WDOG_PRESC_PRESCVAL(baseAddr, (uint8_t)clockPrescaler);
}

/*!
 * @brief Gets the Watchdog clock prescaler.
 *
 * This function gets the WDOG clock prescaler.
 * 
 * @param baseAddr The WDOG peripheral base address
 * @return WDOG clock prescaler, see #wdog_clock_prescaler_value_t.
 */
static inline wdog_clock_prescaler_value_t WDOG_HAL_GetClockPrescalerValueMode(uint32_t baseAddr)
{
    return (wdog_clock_prescaler_value_t)BR_WDOG_PRESC_PRESCVAL(baseAddr);
}

/*!
 * @brief Sets the Watchdog window value.
 *
 * This function sets the WDOG_WIN value.
 * Make sure WDOG registers are unlocked by the WDOG_HAL_Unlock , that the WCT window is still open and that
 * this API has not been called in this WCT while this function is called.
 * Make sure WDOG_STCTRLH.ALLOWUPDATE is 1 which means register update is enabled.
 *
 * @param baseAddr The WDOG peripheral base address
 * @param windowValue watchdog window value.
 */
static inline void WDOG_HAL_SetWindowValue(uint32_t baseAddr,  uint32_t windowValue)
{
    HW_WDOG_WINH_WR(baseAddr, (uint16_t)((windowValue>>16U) & 0xFFFFU));
    HW_WDOG_WINL_WR(baseAddr, (uint16_t)((windowValue) & 0xFFFFU));
}

/*!
 * @brief Gets the Watchdog window value.
 *
 * This function gets the WDOG_WIN value.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return watchdog window value.
 */
static inline uint32_t WDOG_HAL_GetWindowValue(uint32_t baseAddr)
{
    return (uint32_t)((((uint32_t)(HW_WDOG_WINH_RD(baseAddr))) << 16U) | (HW_WDOG_WINL_RD(baseAddr)));
}

/*!
 * @brief Unlocks the Watchdog register written.
 * 
 * This function unlocks the WDOG register written.
 * This function must be called before any configuration is set because watchdog register
 * will be locked automatically after a WCT(256 bus cycles).
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_Unlock(uint32_t baseAddr)
{
    HW_WDOG_UNLOCK_WR(baseAddr, WDOG_UNLOCK_VALUE_HIGH);
    HW_WDOG_UNLOCK_WR(baseAddr, WDOG_UNLOCK_VALUE_LOW);
}

/*!
 * @brief Refreshes the Watchdog timer.
 *
 * This function feeds the WDOG.
 * This function should be called before watchdog timer is in timeout. Otherwise, a reset is asserted.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_Refresh(uint32_t baseAddr)
{
    HW_WDOG_REFRESH_WR(baseAddr, WDOG_REFRESH_VALUE_HIGH);
    HW_WDOG_REFRESH_WR(baseAddr, WDOG_REFRESH_VALUE_LOW);
}

/*!
 * @brief Resets the chip using the Watchdog.
 *
 * This function resets the chip using WDOG.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_ResetSystem(uint32_t baseAddr)
{
    HW_WDOG_REFRESH_WR(baseAddr, WDOG_REFRESH_VALUE_HIGH);
    HW_WDOG_REFRESH_WR(baseAddr, 0);
    while(1)
    {
    }
}

/*!
 * @brief Gets the chip reset count that was reset by Watchdog.
 *
 * This function gets the value of the WDOG_RSTCNT.
 *
 * @param baseAddr The WDOG peripheral base address
 * @return Chip reset count that was reset by Watchdog.
 */
static inline uint32_t WDOG_HAL_GetResetCount(uint32_t baseAddr)
{
    return HW_WDOG_RSTCNT_RD(baseAddr);
}

/*!
 * @brief Clears the chip reset count that was reset by Watchdog.
 *
 * This function clears the WDOG_RSTCNT.
 *
 * @param baseAddr The WDOG peripheral base address
 */
static inline void WDOG_HAL_ClearResetCount(uint32_t baseAddr)
{
    HW_WDOG_RSTCNT_WR(baseAddr, 0xFFFFU);
}

/*!
 * @brief Restores the WDOG module to reset value.
 *
 * This function restores the WDOG module to reset value.
 *
 * @param baseAddr The WDOG peripheral base address
 */
void WDOG_HAL_Init(uint32_t baseAddr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_WDOG_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

