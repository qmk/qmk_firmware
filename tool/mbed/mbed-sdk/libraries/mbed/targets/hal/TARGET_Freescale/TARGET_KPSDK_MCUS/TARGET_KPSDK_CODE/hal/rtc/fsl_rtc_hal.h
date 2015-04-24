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
#if !defined(__FSL_RTC_HAL_H__)
#define __FSL_RTC_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_rtc_features.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup rtc_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure is used to hold the time in a simple "date" format.
 */
typedef struct RtcDatetime
{
   uint16_t year;    /*!< Range from 1970 to 2099.*/
   uint16_t month;   /*!< Range from 1 to 12.*/
   uint16_t day;     /*!< Range from 1 to 31 (depending on month).*/
   uint16_t hour;    /*!< Range from 0 to 23.*/
   uint16_t minute;  /*!< Range from 0 to 59.*/
   uint8_t second;   /*!< Range from 0 to 59.*/
} rtc_datetime_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name RTC HAL API Functions
 * @{
 */

/*!
 * @brief  Initializes the RTC module.
 *
 * This function enables the RTC oscillator.
 *
 * @param  rtcBaseAddr The RTC base address.
 */
void RTC_HAL_Enable(uint32_t rtcBaseAddr);

/*!
 * @brief  Disables the RTC module.
 *
 * This function disablesS the RTC counter and oscillator.
 *
 * @param  rtcBaseAddr The RTC base address.
 */
void RTC_HAL_Disable(uint32_t rtcBaseAddr);

/*!
 * @brief  Resets the RTC module.
 *
 * This function initiates a soft-reset of the RTC module to reset
 * the RTC registers.
 *
 * @param  rtcBaseAddr The RTC base address..
 */
void RTC_HAL_Init(uint32_t rtcBaseAddr);

/*!
 * @brief  Converts seconds to date time format data structure.
 *
 * @param  seconds holds the date and time information in seconds
 * @param  datetime holds the converted information from seconds in date and time format
 */
void RTC_HAL_ConvertSecsToDatetime(const uint32_t * seconds, rtc_datetime_t * datetime);

/*!
 * @brief  Checks whether the date time structure elements have the information that is within the range.
 *
 * @param  datetime holds the date and time information that needs to be converted to seconds
 */
bool RTC_HAL_IsDatetimeCorrectFormat(const rtc_datetime_t * datetime);

/*!
 * @brief  Converts the date time format data structure to seconds.
 *
 * @param  datetime holds the date and time information that needs to be converted to seconds
 * @param  seconds holds the converted date and time in seconds
 */
void RTC_HAL_ConvertDatetimeToSecs(const rtc_datetime_t * datetime, uint32_t * seconds);

/*!
 * @brief  Sets the RTC date and time according to the given time structure.
 *
 * The function converts the data from the time structure to seconds and writes the seconds
 * value to the RTC register. The RTC counter is started after setting the time.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  datetime [in] Pointer to structure where the date and time
 *         details to set are stored.
 */
void RTC_HAL_SetDatetime(uint32_t rtcBaseAddr, const rtc_datetime_t * datetime);

/*!
 * @brief  Sets the RTC date and time according to the given time provided in seconds.
 *
 * The RTC counter is started after setting the time.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  seconds [in] Time in seconds
 */
void RTC_HAL_SetDatetimeInsecs(uint32_t rtcBaseAddr, const uint32_t seconds);

/*!
 * @brief  Gets the RTC time and stores it in the given time structure.
 *
 * The function reads the value in seconds from the RTC register. It then converts to the
 * time structure which provides the time in date, hour, minutes and seconds.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  datetime [out] pointer to a structure where the date and time details are
 *         stored.
 */
void RTC_HAL_GetDatetime(uint32_t rtcBaseAddr, rtc_datetime_t * datetime);

/*!
 * @brief  Gets the RTC time and returns it in seconds.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  datetime [out] pointer to variable where the RTC time is stored in seconds
 */
void RTC_HAL_GetDatetimeInSecs(uint32_t rtcBaseAddr, uint32_t * seconds);

/*!
 * @brief  Reads the value of the time alarm.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  date [out] pointer to a variable where the alarm date and time
 *         details are stored.
 */
void RTC_HAL_GetAlarm(uint32_t rtcBaseAddr, rtc_datetime_t * date);

/*!
 * @brief  Sets the RTC alarm time and enables the alarm interrupt.
 *
 * The function checks whether the specified alarm time is greater than the present
 * time. If not, the function does not set the alarm and returns an error.
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  date [in] pointer to structure where the alarm date and time
 *         details will be stored at.
 * @return  true: success in setting the RTC alarm\n
 *          false: error in setting the RTC alarm.
 */
bool RTC_HAL_SetAlarm(uint32_t rtcBaseAddr, const rtc_datetime_t * date);

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*-------------------------------------------------------------------------------------------*/
/* RTC Monotonic Counter*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the values of the Monotonic Counter High and Monotonic Counter Low and returns
 *         them as a single value.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  counter [out] pointer to variable where the value is  stored.
 */
void RTC_HAL_GetMonotonicCounter(uint32_t rtcBaseAddr, uint64_t * counter);

/*!
 * @brief  Writes values Monotonic Counter High and Monotonic Counter Low by decomposing
 *         the given single value.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  counter [in] pointer to variable where the value is stored.
 */
void RTC_HAL_SetMonotonicCounter(uint32_t rtcBaseAddr, const uint64_t * counter);

/*!
 * @brief  Increments the Monotonic Counter by one.
 *
 * Increments the Monotonic Counter (registers RTC_MCLR and RTC_MCHR accordingly) by setting
 * the monotonic counter enable (MER[MCE]) and then writing to the RTC_MCLR register. A write to the
 * monotonic counter low that causes it to overflow also increments the monotonic counter high.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: success\n
 *          false: error occurred, either time invalid or monotonic overflow flag was found
 */
bool RTC_HAL_IncrementMonotonicCounter(uint32_t rtcBaseAddr);
#endif
/*! @}*/

/*!
 * @name RTC register access functions
 * @{
 */

/*!
 * @brief  Reads the value of the time seconds counter.
 *
 * The time counter reads as zero if either the SR[TOF] or the SR[TIF] is set.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return contents of the seconds register.
 */
static inline uint32_t RTC_HAL_GetSecsReg(uint32_t rtcBaseAddr)
{
    return BR_RTC_TSR_TSR(rtcBaseAddr);
}

/*!
 * @brief  Writes to the time seconds counter.
 *
 * When the time counter is enabled, the TSR is read only and increments
 * once every second provided the SR[TOF] or SR[TIF] is not set. When the time counter
 * is disabled, the TSR can be read or written. Writing to the TSR when the
 * time counter is disabled clears the SR[TOF] and/or the SR[TIF]. Writing
 * to the TSR register with zero is supported, but not recommended, since the TSR
 * reads as zero when either the SR[TIF] or the SR[TOF] is set (indicating the time is
 * invalid).
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  seconds [in] seconds value.
 *
 */
static inline void RTC_HAL_SetSecsReg(uint32_t rtcBaseAddr, const uint32_t seconds)
{
    HW_RTC_TPR_WR(rtcBaseAddr, (uint32_t)0x00000000U);
    BW_RTC_TSR_TSR(rtcBaseAddr, seconds);
}

/*!
 * @brief  Sets the time alarm and clears the time alarm flag.
 *
 * When the time counter is enabled, the SR[TAF] is set whenever the TAR[TAR]
 * equals the TSR[TSR] and the TSR[TSR] increments. Writing to the TAR
 * clears the SR[TAF].
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  seconds [in] alarm value in seconds.
 */
static inline void RTC_HAL_SetAlarmReg(uint32_t rtcBaseAddr, const uint32_t seconds)
{
    BW_RTC_TAR_TAR(rtcBaseAddr, seconds);
}

/*!
 * @brief  Gets the time alarm register contents.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  contents of the alarm register.
 */
static inline uint32_t RTC_HAL_GetAlarmReg(uint32_t rtcBaseAddr)
{
    return BR_RTC_TAR_TAR(rtcBaseAddr);
}


/*!
 * @brief  Reads the value of the time prescaler.
 *
 * The time counter reads as zero when either the SR[TOF] or the SR[TIF] is set.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  contents of the time prescaler register.
 */
static inline uint16_t RTC_HAL_GetPrescaler(uint32_t rtcBaseAddr)
{
    return BR_RTC_TPR_TPR(rtcBaseAddr);
}

/*!
 * @brief  Sets the time prescaler.
 *
 * When the time counter is enabled, the TPR is read only and increments
 * every 32.768 kHz clock cycle. When the time counter is disabled, the TPR
 * can be read or written. The TSR[TSR] increments when bit 14 of the TPR
 * transitions from a logic one to a logic zero.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  prescale Prescaler value
 */
static inline void RTC_HAL_SetPrescaler(uint32_t rtcBaseAddr, const uint16_t prescale)
{
    BW_RTC_TPR_TPR(rtcBaseAddr, prescale);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Time Compensation*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the time compensation register contents.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return time compensation register contents.
 */
static inline uint32_t RTC_HAL_GetCompensationReg(uint32_t rtcBaseAddr)
{
    return HW_RTC_TCR_RD(rtcBaseAddr);
}

/*!
 * @brief  Writes the value to the RTC TCR register.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  compValue value to be written to the compensation register.
 */
static inline void RTC_HAL_SetCompensationReg(uint32_t rtcBaseAddr, const uint32_t compValue)
{
    HW_RTC_TCR_WR(rtcBaseAddr, compValue);
}

/*!
 * @brief  Reads the current value of the compensation interval counter, which is the field CIC in the RTC TCR register.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  compensation interval value.
 */
static inline uint8_t RTC_HAL_GetCompensationIntervalCounter(uint32_t rtcBaseAddr)
{
    return BR_RTC_TCR_CIC(rtcBaseAddr);
}

/*!
 * @brief  Reads the current value used by the compensation logic for the present second interval.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  time compensation value
 */
static inline uint8_t RTC_HAL_GetTimeCompensationValue(uint32_t rtcBaseAddr)
{
    return BR_RTC_TCR_TCV(rtcBaseAddr);
}

/*!
 * @brief  Reads the compensation interval register.

 * The value is the configured compensation interval in seconds from 1 to 256 to control
 * how frequently the time compensation register  should adjust the
 * number of 32.768 kHz cycles in each second. The value is one
 * less than the number of seconds (for example, zero means a
 * configuration for a compensation interval of one second).
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return compensation interval in seconds.
 */
static inline uint8_t RTC_HAL_GetCompensationIntervalRegister(uint32_t rtcBaseAddr)
{
    return BR_RTC_TCR_CIR(rtcBaseAddr);
}

/*!
 * @brief  Writes the compensation interval.
 *
 * This configures the compensation interval in seconds from 1 to 256 to control
 * how frequently the TCR should adjust the number of 32.768 kHz
 * cycles in each second. The value written should be one less than
 * the number of seconds (for example, write zero to configure for
 * a compensation interval of one second). This register is double
 * buffered and writes do not take affect until the end of the
 * current compensation interval.
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  value the compensation interval value.
 */
static inline void RTC_HAL_SetCompensationIntervalRegister(uint32_t rtcBaseAddr, const uint8_t value)
{
    BW_RTC_TCR_CIR(rtcBaseAddr, value);
}

/*!
 * @brief  Reads the time compensation value which is the configured number
 *         of 32.768 kHz clock cycles in each second.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  time compensation value.
 */
static inline uint8_t RTC_HAL_GetTimeCompensationRegister(uint32_t rtcBaseAddr)
{
    return BR_RTC_TCR_TCR(rtcBaseAddr);
}

/*!
 * @brief  Writes to the field Time Compensation Register (TCR) of the RTC Time Compensation Register (RTC_TCR).
 *
 * Configures the number of 32.768 kHz clock cycles in each second. This register is double
 * buffered and writes do not take affect until the end of the
 * current compensation interval.
 * 80h Time prescaler register overflows every 32896 clock cycles.
 * .. ...\n
 * FFh Time prescaler register overflows every 32769 clock cycles.\n
 * 00h Time prescaler register overflows every 32768 clock cycles.\n
 * 01h Time prescaler register overflows every 32767 clock cycles.\n
 * ... ...\n
 * 7Fh Time prescaler register overflows every 32641 clock cycles.\n
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  comp_value value of the time compensation.
 */
static inline void RTC_HAL_SetTimeCompensationRegister(uint32_t rtcBaseAddr, const uint8_t compValue)
{
    BW_RTC_TCR_TCR(rtcBaseAddr, compValue);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Control*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Enables/disables the oscillator configuration for the 2pF load.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables load\n
 *         false: disables load.
 */
static inline void RTC_HAL_SetOsc2pfLoadCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_SC2P(rtcBaseAddr, enable);
}

/*!
 * @brief  Reads the oscillator 2pF load configure bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 2pF additional load enabled.\n
 *         false: 2pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc2pfLoad(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SC2P(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 4pF load.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables load.\n
 *         false: disables load
 */
static inline void RTC_HAL_SetOsc4pfLoadCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_SC4P(rtcBaseAddr, enable);
}

/*!
 * @brief  Reads the oscillator 4pF load configure bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 4pF additional load enabled.\n
 *         false: 4pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc4pfLoad(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SC4P(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 8pF load.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables load.\n
 *         false: disables load.
 */
static inline void RTC_HAL_SetOsc8pfLoadCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_SC8P(rtcBaseAddr, enable);
}

/*!
 * @brief  Reads the oscillator 8pF load configure bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 8pF additional load enabled.\n
 *         false: 8pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc8pfLoad(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SC8P(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the oscillator configuration for the 16pF load.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables load.\n
 *         false: disables load.
 */
static inline void RTC_HAL_SetOsc16pfLoadCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_SC16P(rtcBaseAddr, enable);
}

/*!
 * @brief  Reads the oscillator 16pF load configure bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 16pF additional load enabled.\n
 *         false: 16pF additional load disabled.
 */
static inline bool RTC_HAL_GetOsc16pfLoad(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SC16P(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the 32 kHz clock output to other peripherals.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables clock out.\n
 *         false: disables clock out.
 */
static inline void RTC_HAL_SetClockOutCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_CLKO(rtcBaseAddr, !enable);
}

/*!
 * @brief  Reads the RTC_CR CLKO bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 32 kHz clock is not output to other peripherals.\n
 *         false: 32 kHz clock is output to other peripherals.
 */
static inline bool RTC_HAL_GetClockOutCmd(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_CLKO(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the oscillator.
 *
 * After enabling, waits for the oscillator startup time before enabling the
 * time counter to allow the 32.768 kHz clock time to stabilize.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables oscillator.\n
 *         false: disables oscillator.
 */
static inline void RTC_HAL_SetOscillatorCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_CR_OSCE(rtcBaseAddr, enable);
/* TODO: Wait for oscillator startup period if enabling the oscillator
    if (enable)
*/

}

/*!
 * @brief  Reads the RTC_CR OSCE bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: 32.768 kHz oscillator is enabled
 *         false: 32.768 kHz oscillator is disabled.
 */
static inline bool RTC_HAL_IsOscillatorEnabled(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_OSCE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the update mode.
 *
 * This mode allows the time counter enable bit in the SR to be written
 * even when the status register is locked.
 * When set, the time counter enable, can always be written if the
 * TIF (Time Invalid Flag) or TOF (Time Overflow Flag) are set or
 * if the time counter enable is clear. For devices with the
 * monotonic counter it allows the monotonic enable to be written
 * when it is locked. When set, the monotonic enable can always be
 * written if the TIF (Time Invalid Flag) or TOF (Time Overflow Flag)
 * are set or if the montonic counter enable is clear.
 * For devices with tamper detect it allows the it to be written
 * when it is locked. When set, the tamper detect can always be
 * written if the TIF (Time Invalid Flag) is clear.
 * Note: Tamper and Monotonic features are not available in all MCUs.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  lock can be true or false\n
 *         true: registers can be written when locked under limited conditions\n
 *         false: registers cannot be written when locked
 */
static inline void RTC_HAL_SetUpdateModeCmd(uint32_t rtcBaseAddr, bool lock)
{
    BW_RTC_CR_UM(rtcBaseAddr, lock);
}

/*!
 * @brief  Reads the RTC_CR update mode bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: Registers can be written when locked under limited conditions.
 *         false: Registers cannot be written when locked.
 */
static inline bool RTC_HAL_GetUpdateMode(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_UM(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the supervisor access.
 *
 * This configures non-supervisor mode write access to all RTC registers and
 * non-supervisor mode read access to RTC tamper/monotonic registers.
 * Note: Tamper and Monotonic features are NOT available in all MCUs.
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  enableRegWrite can be true or false\n
 *         true: non-supervisor mode write accesses are supported.\n
 *         false: non-supervisor mode write accesses are not supported and generate a bus error.
 */
static inline void RTC_HAL_SetSupervisorAccessCmd(uint32_t rtcBaseAddr, bool enableRegWrite)
{
    BW_RTC_CR_SUP(rtcBaseAddr, enableRegWrite);
}

/*!
 * @brief  Reads the RTC_CR SUP bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: Non-supervisor mode write accesses are supported
 *         false: Non-supervisor mode write accesses are not supported.
 */
static inline bool RTC_HAL_GetSupervisorAccess(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SUP(rtcBaseAddr);
}

#if FSL_FEATURE_RTC_HAS_WAKEUP_PIN
/*!
 * @brief  Enables/disables the wakeup pin.
 *
 * Note: The wakeup pin is optional and not available on all devices.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable_wp can be true or false\n
 *         true: enables wakeup-pin, wakeup pin asserts if the
 *               RTC interrupt asserts and the chip is powered down.\n
 *         false: disables wakeup-pin.
 */
static inline void RTC_HAL_SetWakeupPinCmd(uint32_t rtcBaseAddr, bool enableWp)
{
    BW_RTC_CR_WPE(rtcBaseAddr, enableWp);
}

/*!
 * @brief  Reads the RTC_CR WPE bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: Wakeup pin is enabled.
 *         false: Wakeup pin is disabled.
 */
static inline bool RTC_HAL_GetWakeupPin(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_WPE(rtcBaseAddr);
}
#endif

/*!
 * @brief  Performs a software reset on the RTC module.
 *
 * This resets all RTC registers except for the SWR bit and the RTC_WAR and RTC_RAR
 * registers. The SWR bit is cleared after VBAT POR and by software
 * explicitly clearing it.
 * Note: access control features (RTC_WAR and RTC_RAR registers)
 * are not available in all MCUs.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_SoftwareReset(uint32_t rtcBaseAddr)
{
    BW_RTC_CR_SWR(rtcBaseAddr, 1u);
}

/*!
 * @brief  Clears the software reset flag.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_SoftwareResetFlagClear(uint32_t rtcBaseAddr)
{
    BW_RTC_CR_SWR(rtcBaseAddr, 0u);
}

/*!
 * @brief  Reads the RTC_CR SWR bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: SWR is set.
 *         false: SWR is cleared.
 */
static inline bool RTC_HAL_ReadSoftwareResetStatus(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_CR_SWR(rtcBaseAddr);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Status*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the time counter status (enabled/disabled).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: time counter is enabled, time seconds register and time
 *                prescaler register are not writeable, but increment.\n
 *          false: time counter is disabled, time seconds register and
 *                 time prescaler register are writeable, but do not increment.
 */
static inline bool RTC_HAL_IsCounterEnabled(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_SR_TCE(rtcBaseAddr);
}

/*!
 * @brief  Changes the time counter status.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: enables the time counter\n
 *         false: disables the time counter.
 */
static inline void RTC_HAL_EnableCounter(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_SR_TCE(rtcBaseAddr, enable);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*!
 * @brief  Reads the value of the Monotonic Overflow Flag (MOF).
 *
 * This flag is set when the monotonic counter is enabled and the monotonic
 * counter high overflows. The monotonic counter does not increment and 
 * reads as zero when this bit is set. This bit is cleared by writing the monotonic
 * counter high register when the monotonic counter is disabled.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  true: monotonic counter overflow has occurred and monotonic
 *                counter is read as zero.\n
 *          false: No monotonic counter overflow has occurred.
 */
static inline bool RTC_HAL_IsMonotonicCounterOverflow(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_SR_MOF(rtcBaseAddr);
}
#endif

/*!
 * @brief  Checks whether the configured time alarm has occurred.
 *
 * Reads time alarm flag (TAF). This flag is set when the time
 * alarm register (TAR) equals the time seconds register (TSR) and
 * the TSR increments. This flag is cleared by writing the TAR register.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  true: time alarm has occurred.\n
 *          false: no time alarm occurred.
 */
static inline bool RTC_HAL_HasAlarmOccured(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_SR_TAF(rtcBaseAddr);
}

/*!
 * @brief  Checks whether a counter overflow has occurred.
 *
 * Reads the value of RTC Status Register (RTC_SR), field Time
 * Overflow Flag (TOF). This flag is set when the time counter is
 * enabled and overflows. The TSR and TPR do not increment and read
 * as zero when this bit is set. This flag is cleared by writing the
 * TSR register when the time counter is disabled.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  true: time overflow occurred and time counter is zero.\n
 *          false: no time overflow occurred.
 */
static inline bool RTC_HAL_HasCounterOverflowed(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_SR_TOF(rtcBaseAddr);
}

/*!
 * @brief  Checks whether the time has been marked as invalid.
 *
 * Reads the value of RTC Status Register (RTC_SR), field Time
 * Invalid Flag (TIF). This flag is set on VBAT POR or software
 * reset. The TSR and TPR do not increment and read as zero when
 * this bit is set. This flag is cleared by writing the TSR
 * register when the time counter is disabled.
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  true: time is INVALID and time counter is zero.\n
 *          false: time is valid.
 */
static inline bool RTC_HAL_IsTimeInvalid(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_SR_TIF(rtcBaseAddr);
}

/*-------------------------------------------------------------------------------------------*/
/* RTC Lock*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Configures the register lock to other module fields.
 *
 * @param  rtcBaseAddr The RTC base address..
 * @param  bitfields [in] configuration flags:\n
 *  Valid bitfields:\n
 *    LRL: Lock Register Lock \n
 *    SRL: Status Register Lock \n
 *    CRL: Control Register Lock \n
 *    TCL: Time Compensation Lock \n
 *
 * For MCUs that have the Tamper Detect only: \n
 *    TIL: Tamper Interrupt Lock \n
 *    TTL: Tamper Trim Lock \n
 *    TDL: Tamper Detect Lock \n
 *    TEL: Tamper Enable Lock \n
 *    TTSL: Tamper Time Seconds Lock \n
 *
 * For MCUs that have the Monotonic Counter only: \n
 *    MCHL: Monotonic Counter High Lock \n
 *    MCLL: Monotonic Counter Low Lock \n
 *    MEL: Monotonic Enable Lock \n
 */
static inline void RTC_HAL_SetLockRegistersCmd(uint32_t rtcBaseAddr, hw_rtc_lr_t bitfields)
{
    uint32_t valid_flags = 0;

    valid_flags |= (BM_RTC_LR_LRL | BM_RTC_LR_SRL | BM_RTC_LR_CRL |
                    BM_RTC_LR_TCL);

#if FSL_FEATURE_RTC_HAS_MONOTONIC
    valid_flags |= (BM_RTC_LR_MCHL | BM_RTC_LR_MCLL | BM_RTC_LR_MEL);
#endif
    HW_RTC_LR_WR(rtcBaseAddr, (bitfields.U) & valid_flags);
}

/*!
 * @brief  Obtains the lock status of the lock register.
 *
 * Reads the value of the field Lock Register Lock (LRL) of the  RTC Lock Register (RTC_LR).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: lock register is not locked and writes complete as normal.\n
 *          false: lock register is locked and writes are ignored.
 */
static inline bool RTC_HAL_GetLockRegLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_LRL(rtcBaseAddr);
}

/*!
 * @brief  Changes the lock status of the lock register.
 *
 * Writes to the field Lock Register Lock (LRL) of the RTC Lock Register (RTC_LR).
 * Once cleared, this can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  lock can be true or false\n
 *         true: Lock register is not locked and writes complete as normal.\n
 *         false: Lock register is locked and writes are ignored.
 */
static inline void RTC_HAL_SetLockRegLock(uint32_t rtcBaseAddr, bool lock)
{
    BW_RTC_LR_LRL(rtcBaseAddr, (uint32_t) lock);
}

/*!
 * @brief  Obtains the state of the status register lock.
 *
 * Reads the value of field Status Register Lock (SRL) of the RTC Lock Register (RTC_LR), which is the field Status Register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Status register is not locked and writes complete as
 *                normal.\n
 *          false: Status register is locked and writes are ignored.
 */
static inline bool RTC_HAL_GetStatusRegLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_SRL(rtcBaseAddr);
}

/*!
 * @brief Changes the state of the status register lock.
 *
 * Writes to the field Status Register Lock (SRL) of the RTC Lock Register (RTC_LR).
 * Once cleared, this can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  lock can be true or false\n
 *         true: Status register is not locked and writes complete as
 *               normal.\n
 *         false: Status register is locked and writes are ignored.
 */
static inline void RTC_HAL_SetStatusRegLock(uint32_t rtcBaseAddr, bool lock)
{
    BW_RTC_LR_SRL(rtcBaseAddr, (uint32_t) lock);
}

/*!
 * @brief  Obtains the state of the control register lock.
 *
 * Reads the field Control Register Lock (CRL)value of the RTC Lock Register (RTC_LR).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Control register is not locked and writes complete as
 *                 normal.\n
 *          false: Control register is locked and writes are ignored.
 */
static inline bool RTC_HAL_GetControlRegLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_CRL(rtcBaseAddr);
}

/*!
 * @brief  Changes the state of the control register lock.
 *
 * Writes to the field Control Register Lock (CRL) of the RTC Lock Register (RTC_LR).
 * Once cleared, this can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  lock can be true or false\n
 *         true: Control register is not locked and writes complete
 *               as normal.\n
 *         false: Control register is locked and writes are ignored.
 */
static inline void RTC_HAL_SetControlRegLock(uint32_t rtcBaseAddr, bool lock)
{
    BW_RTC_LR_CRL(rtcBaseAddr, (uint32_t) lock);
}

/*!
 * @brief  Obtains the state of the time compensation lock.
 *
 * Reads the field Time Compensation Lock (TCL) value of the RTC Lock Register (RTC_LR).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Time compensation register is not locked and writes
 *                complete as normal.\n
 *          false: Time compensation register is locked and writes are
 *                 ignored.
 */
static inline bool RTC_HAL_GetTimeCompLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_TCL(rtcBaseAddr);
}

/*!
 * @brief  Changes the state of the time compensation lock.
 *
 * Writes to the field Time Compensation Lock (TCL) of the RTC Lock Register (RTC_LR).
 * Once cleared, this can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  lock can be true or false\n
 *         true: Time compensation register is not locked and writes
 *               complete as normal.\n
 *         false: Time compensation register is locked and writes are
 *                ignored.
 */
static inline void RTC_HAL_SetTimeCompLock(uint32_t rtcBaseAddr, bool lock)
{
    BW_RTC_LR_TCL(rtcBaseAddr, (uint32_t) lock);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*!
 * @brief  Reads the value of the Monotonic Counter High Lock.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Monotonic counter high register is not locked and writes
 *                complete as normal.\n
 *          false: Monotonic counter high register is locked and writes are
 *                 ignored.
 */
static inline bool RTC_HAL_ReadMonotonicHcounterLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_MCHL(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter High Lock (MCHL) of the RTC Lock Register (RTC_LR).
 *
 * Once done, this flag can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicHcounterLock(uint32_t rtcBaseAddr)
{
    BW_RTC_LR_MCHL(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the value of the Monotonic Counter Low Lock.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Monotonic counter low register is not locked and writes
 *                complete as normal.\n
 *          false: Monotonic counter low register is locked and writes are
 *                 ignored.
 */
static inline bool RTC_HAL_ReadMonotonicLcounterLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_MCLL(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter Low Lock (MCLL) of the RTC Lock Register (RTC_LR).
 *
 * Once done, this flag can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicLcounterLock(uint32_t rtcBaseAddr)
{
    BW_RTC_LR_MCLL(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the value of the Monotonic Enable Lock.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Monotonic enable register is not locked and writes
 *                complete as normal.\n
 *          false: Monotonic enable register is locked and writes are
 *                 ignored.
 */
static inline bool RTC_HAL_ReadMonotonicEnableLock(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_LR_MEL(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the Monotonic Enable Lock field of the RTC Lock Register (RTC_LR).
 *
 * Once done, this flag can only be set by VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicEnableLock(uint32_t rtcBaseAddr)
{
    BW_RTC_LR_MEL(rtcBaseAddr, 0U);
}
#endif

/*-------------------------------------------------------------------------------------------*/
/* RTC Interrupt Enable*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Checks whether the Time Seconds Interrupt is enabled/disabled.
 *
 * Reads the value of field Time Seconds Interrupt Enable (TSIE)of the RTC Interrupt Enable Register (RTC_IER). 
 * The seconds interrupt is an edge-sensitive
 * interrupt with a dedicated interrupt vector. It is generated once a second
 * and requires no software overhead (there is no corresponding status flag to
 * clear).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Seconds interrupt is enabled.\n
 *          false: Seconds interrupt is disabled.
 */
static inline bool RTC_HAL_IsSecsIntEnabled(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_IER_TSIE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the Time Seconds Interrupt.
 *
 * Writes to the field Time Seconds
 * Interrupt Enable (TSIE) of the RTC Interrupt Enable Register (RTC_IER).
 * Note: The seconds interrupt is an edge-sensitive interrupt with a
 * dedicated interrupt vector. It is generated once a second and
 * requires no software overhead (there is no corresponding status
 * flag to clear).
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: Seconds interrupt is enabled.\n
 *         false: Seconds interrupt is disabled.
 */
static inline void RTC_HAL_SetSecsIntCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_IER_TSIE(rtcBaseAddr, (uint32_t) enable);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*!
 * @brief  Checks whether the Monotonic Overflow Interrupt is enabled/disabled.
 *
 * Reads the value of the RTC Interrupt Enable Register (RTC_IER), field
 * Monotonic Overflow Interrupt Enable (MOIE).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Monotonic overflow flag does generate an interrupt.\n
 *          false: Monotonic overflow flag does not generate an interrupt.
 */
static inline bool RTC_HAL_ReadMonotonicOverflowInt(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_IER_MOIE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the Monotonic Overflow Interrupt Enable.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: Monotonic overflow flag does generate an interrupt.\n
 *         false: Monotonic overflow flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetMonotonicOverflowIntCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_IER_MOIE(rtcBaseAddr, (uint32_t)enable);
}

#endif

/*!
 * @brief  Checks whether the Time Alarm Interrupt is enabled/disabled.
 *
 * Reads the field Time Alarm Interrupt Enable (TAIE) value of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Time alarm flag does generate an interrupt.\n
 *          false: Time alarm flag does not generate an interrupt.
 */
static inline bool RTC_HAL_ReadAlarmInt(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_IER_TAIE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the Time Alarm Interrupt.
 *
 * Writes to the field Time Alarm
 * Interrupt Enable (TAIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: Time alarm flag does generate an interrupt.\n
 *         false: Time alarm flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetAlarmIntCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_IER_TAIE(rtcBaseAddr, (uint32_t) enable);
}

/*!
 * @brief  Checks whether the Time Overflow Interrupt is enabled/disabled.
 *
 * Reads the field
 * Time Overflow Interrupt Enable (TOIE) of the value of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address..
 *
 * @return  true: Time overflow flag does generate an interrupt.\n
 *          false: Time overflow flag does not generate an interrupt.
 */
static inline bool RTC_HAL_ReadTimeOverflowInt(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_IER_TOIE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the Time Overflow Interrupt.
 *
 * Writes to the field Time Overflow Interrupt Enable (TOIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: Time overflow flag does generate an interrupt.\n
 *         false: Time overflow flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetTimeOverflowIntCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_IER_TOIE(rtcBaseAddr, (uint32_t) enable);
}

/*!
 * @brief  Checks whether the Time Invalid Interrupt is enabled/disabled.
 *
 * Reads the value of the field Time
 * Invalid Interrupt Enable (TIIE)of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Time invalid flag does generate an interrupt.\n
 *          false: Time invalid flag does not generate an interrupt.
 */
static inline bool RTC_HAL_ReadTimeInvalidInt(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_IER_TIIE(rtcBaseAddr);
}

/*!
 * @brief  Enables/disables the Time Invalid Interrupt.
 *
 * Writes to the field Time Invalid
 * Interrupt Enable (TIIE) of the RTC Interrupt Enable Register (RTC_IER).
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable can be true or false\n
 *         true: Time invalid flag does generate an interrupt.\n
 *         false: Time invalid flag does not generate an interrupt.
 */
static inline void RTC_HAL_SetTimeInvalidIntCmd(uint32_t rtcBaseAddr, bool enable)
{
    BW_RTC_IER_TIIE(rtcBaseAddr, (uint32_t) enable);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*-------------------------------------------------------------------------------------------*/
/* RTC Monotonic Enable*/
/*-------------------------------------------------------------------------------------------*/

/*!
 * @brief  Reads the Monotonic Counter Enable bit.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: This means writing to the monotonic counter increments the counter by one and
 *               the value written is ignored.\n
 *         false: This means writing to the monotonic counter loads the counter with the
 *                value written.
 */
static inline bool RTC_HAL_ReadMonotonicEnable(uint32_t rtcBaseAddr)
{
    /* Reads value of the RTC_MER register, field Monotonic Counter Enable (MCE). */
    return (bool)BR_RTC_MER_MCE(rtcBaseAddr);
}

/*!
 * @brief  Changes the state of Monotonic Counter Enable bit.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  enable value to be written to the MER[MCE] bit\n
 *         true: Set the bit to 1 which means writing to the monotonic counter will increment
 *               the counter by one and the value written will be ignored.\n
 *         false: Set the bit to 0 which means writing to the monotonic counter loads the counter
 *                with the value written.
 */
static inline void RTC_HAL_SetMonotonicEnableCmd(uint32_t rtcBaseAddr, bool enable)
{
    /* Writes to the RTC_MER registers Monotonic Counter Enable (MCE) bit.*/
    BW_RTC_MER_MCE(rtcBaseAddr, (uint32_t) enable);
}

/*!
 * @brief  Reads the values of the Monotonic Counter Low register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  Monotonic Counter Low value.
 */
static inline uint32_t RTC_HAL_GetMonotonicCounterLow(uint32_t rtcBaseAddr)
{
    return BR_RTC_MCLR_MCL(rtcBaseAddr);
}

/*!
 * @brief  Reads the values of the Monotonic Counter High register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  Monotonic Counter High value.
 */
static inline uint32_t RTC_HAL_GetMonotonicCounterHigh(uint32_t rtcBaseAddr)
{
    return BR_RTC_MCHR_MCH(rtcBaseAddr);
}

/*!
 * @brief  Writes values of the Monotonic Counter Low register.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  counter [in] Monotonic Counter Low value to be stored.
 */
static inline void RTC_HAL_SetMonotonicCounterLow(uint32_t rtcBaseAddr, const uint32_t counter)
{
    /* enable writing to the counter*/
    BW_RTC_MER_MCE(rtcBaseAddr, 0U);
    BW_RTC_MCLR_MCL(rtcBaseAddr, counter);
}

/*!
 * @brief  Writes values of the Monotonic Counter High register.
 *
 * @param  rtcBaseAddr The RTC base address
 * @param  counter [in] Monotonic Counter High value to be stored.
 */
static inline void RTC_HAL_SetMonotonicCounterHigh(uint32_t rtcBaseAddr, const uint32_t counter)
{
    /* enable writing to the counter*/
    BW_RTC_MER_MCE(rtcBaseAddr, 0U);
    BW_RTC_MCHR_MCH(rtcBaseAddr, counter);
}

#endif /* FSL_FEATURE_RTC_HAS_MONOTONIC */

#if FSL_FEATURE_RTC_HAS_ACCESS_CONTROL

#if FSL_FEATURE_RTC_HAS_MONOTONIC
/*!
 * @brief  Reads the field Monotonic Counter High Write (MCHW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the monotonic counter high register will complete as normal.\n
 *          false: Writes to the monotonic counter high register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicHcountWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_MCHW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter High Write (MCHW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicHcountWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_MCHW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Monotonic Counter Low Write (MCLW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the monotonic counter low register will complete as normal.\n
 *          false: Writes to the monotonic counter low register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicLcountWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_MCLW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter High Write (MCLW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by  the system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address..
 */
static inline void RTC_HAL_ClearMonotonicLcountWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_MCLW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Monotonic Enable Register Write (MERW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the monotonic enable register will complete as normal.\n
 *          false: Writes to the monotonic enable register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicEnableWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_MERW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter High Write (MERW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicEnableWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_MERW(rtcBaseAddr, 0U);
}
#endif

/*!
 * @brief Reads the field Interrupt Enable Register Write (IERW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: Writes to the interrupt enable register will complete as normal.\n
 *         false: Writes to the interrupt enable register are ignored.
 */
static inline bool RTC_HAL_GetIntEnableWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_IERW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Interrupt Enable Register Write (IERW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearIntEnableWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_IERW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Lock Register Write (LRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the lock register will complete as normal.\n
 *          false: Writes to the lock register are ignored.
 */
static inline bool RTC_HAL_GetLockWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_LRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Lock Register Write (LRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearLockWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_LRW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Status Register Write (SRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the status register completes as normal.\n
 *          false: Writes to the status register are ignored.
 */
static inline bool RTC_HAL_GetStatusWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_SRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Status Register Write (SRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearStatusWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_SRW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Control Register Write (CRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the control register will complete as normal.\n
 *          false: Writes to the control register are ignored.
 */
static inline bool RTC_HAL_GetControlWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_CRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Control Register Write (CRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearControlWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_CRW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Compensation Register Write (TCRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the time compensation register will complete as normal.\n
 *          false: Writes to the time compensation register are ignored.
 */
static inline bool RTC_HAL_GetCompensationWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_TCRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Compensation Register Write (TCRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearCompensationWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_TCRW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Alarm Register Write (TARW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the time alarm register will complete as normal.\n
 *          false: Writes to the time alarm register are ignored.
 */
static inline bool RTC_HAL_GetAlarmWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_TARW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Alarm Register Write (TARW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearAlarmWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_TARW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Prescaler Register Write (TPRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the time prescaler register will complete as normal.\n
 *          false: Writes to the time prescaler register are ignored.
 */
static inline bool RTC_HAL_GetPrescalerWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_TPRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Prescaler Register Write (TPRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearPrescalerWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_TPRW(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Seconds Register Write (TSRW) value of the register RTC_WAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Writes to the time seconds register will complete as normal.\n
 *          false: Writes to the time seconds register are ignored.
 */
static inline bool RTC_HAL_GetSecsWreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_WAR_TSRW(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Seconds Register Write (TSRW) of the RTC_WAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearSecsWreg(uint32_t rtcBaseAddr)
{
    BW_RTC_WAR_TSRW(rtcBaseAddr, 0U);
}

#if FSL_FEATURE_RTC_HAS_MONOTONIC

/*!
 * @brief  Reads the field Monotonic Counter High Read (MCHR) value of the register RTC_RAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return true: Reads to the monotonic counter high register completes as normal.\n
 *         false: Reads to the monotonic counter high register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicHcountRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_MCHR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter High Read (MCHR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicHcountRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_MCHR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Monotonic Counter Low Read (MCLR) value of the register RTC_RAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the monotonic counter low register will complete as normal.\n
 *          false: Reads to the monotonic counter low register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicLcountRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_MCLR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Counter Low Read (MCLR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicLcountRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_MCLR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Monotonic Enable Register Read (MERR) value of the register RTC_RAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the monotonic enable register  completes as normal.\n
 *          false: Reads to the monotonic enable register are ignored.
 */
static inline bool RTC_HAL_GetMonotonicEnableRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_MERR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Monotonic Enable Register Read (MERR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearMonotonicEnableRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_MERR(rtcBaseAddr, 0U);
}

#endif

/*!
 * @brief  Reads the field Interrupt Enable Register Read (IERR) value of the register RTC_RAR.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the interrupt enable register  completes as normal.\n
 *          false: Reads to the interrupt enable register are ignored.
 */
static inline bool RTC_HAL_GetIntEnableRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_IERR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Interrupt Enable Register Read (IERR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearIntEnableRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_IERR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Lock Register Read (LRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the lock register will complete as normal.\n
 *          false: Reads to the lock register are ignored.
 */
static inline bool RTC_HAL_GetLockRreg(uint32_t rtcBaseAddr)
{
  return (bool)BR_RTC_RAR_LRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Lock Register Read (LRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearLockRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_LRR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Status Register Read (SRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the status register  completes as normal.\n
 *          false: Reads to the status register are ignored.
 */
static inline bool RTC_HAL_GetStatusRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_SRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Status Register Read (SRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearStatusRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_SRR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Control Register Read (CRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the control register completes as normal.\n
 *          false: Reads to the control register are ignored.
 */
static inline bool RTC_HAL_GetControlRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_CRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Control Register Read (CRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearControlRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_CRR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Compensation Register Read (TCRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the time compensation register completes as normal.\n
 *          false: Reads to the time compensation register are ignored.
 */
static inline bool RTC_HAL_GetCompensationRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_TCRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Compensation Register Read (TCRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearCompensationRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_TCRR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Alarm Register Read (TARR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the time alarm register completes as normal.\n
 *          false: Reads to the time alarm register are ignored.
 */
static inline bool RTC_HAL_GetAlarmRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_TARR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Alarm Register Read (TARR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearAlarmRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_TARR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Prescaler Register Read (TPRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the time prescaler register completes as normal.\n
 *          false: Reads to the time prescaler register are ignored.
 */
static inline bool RTC_HAL_GetPrescalerRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_TPRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Prescaler Register Read (TPRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearPrescalerRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_TPRR(rtcBaseAddr, 0U);
}

/*!
 * @brief  Reads the field Time Seconds Register Read (TSRR) value of the RTC_RAR register.
 *
 * @param  rtcBaseAddr The RTC base address
 *
 * @return  true: Reads to the time seconds register completes as normal.\n
 *          false: Reads to the time seconds register are ignored.
 */
static inline bool RTC_HAL_GetSecsRreg(uint32_t rtcBaseAddr)
{
    return (bool)BR_RTC_RAR_TSRR(rtcBaseAddr);
}

/*!
 * @brief  Writes 0 to the field Time Seconds Register Read (TSRR) of the RTC_RAR register.
 *
 * Once cleared, this bit is only set by system reset. It is not affected by
 * VBAT POR or software reset.
 *
 * @param  rtcBaseAddr The RTC base address
 */
static inline void RTC_HAL_ClearSecsRreg(uint32_t rtcBaseAddr)
{
    BW_RTC_RAR_TSRR(rtcBaseAddr, 0U);
}

#endif /* FSL_FEATURE_RTC_HAS_ACCESS_CONTROL */

/*! @}*/

#if defined(__cplusplus)
}
#endif


/*! @}*/

#endif /* __FSL_RTC_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

