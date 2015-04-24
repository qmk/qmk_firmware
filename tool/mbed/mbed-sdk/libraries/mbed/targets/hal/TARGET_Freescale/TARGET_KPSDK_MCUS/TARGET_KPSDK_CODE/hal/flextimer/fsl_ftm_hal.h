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
#if !defined(__FSL_FTM_HAL_H__)
#define __FSL_FTM_HAL_H__

#include "fsl_device_registers.h"
#include "fsl_ftm_features.h"
#include <stdbool.h>
#include <assert.h>

/*!
 * @addtogroup ftm_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HW_CHAN0 (0U) /*!< Channel number for CHAN0.*/
#define HW_CHAN1 (1U) /*!< Channel number for CHAN1.*/
#define HW_CHAN2 (2U) /*!< Channel number for CHAN2.*/
#define HW_CHAN3 (3U) /*!< Channel number for CHAN3.*/
#define HW_CHAN4 (4U) /*!< Channel number for CHAN4.*/
#define HW_CHAN5 (5U) /*!< Channel number for CHAN5.*/
#define HW_CHAN6 (6U) /*!< Channel number for CHAN6.*/
#define HW_CHAN7 (7U) /*!< Channel number for CHAN7.*/

#define FTM_COMBINE_CHAN_CTRL_WIDTH  (8U)

/*! @brief FlexTimer clock source selection*/
typedef enum _ftm_clock_source
{
    kClock_source_FTM_None = 0,
    kClock_source_FTM_SystemClk,
    kClock_source_FTM_FixedClk,
    kClock_source_FTM_ExternalClk
}ftm_clock_source_t;

/*! @brief FlexTimer counting mode selection */
typedef enum _ftm_counting_mode
{
    kCounting_FTM_UP = 0,
    kCounting_FTM_UpDown
}ftm_counting_mode_t;

/*! @brief FlexTimer pre-scaler factor selection for the clock source*/
typedef enum _ftm_clock_ps
{
    kFtmDividedBy1 = 0,
    kFtmDividedBy2 ,
    kFtmDividedBy4 ,
    kFtmDividedBy8,
    kFtmDividedBy16,
    kFtmDividedBy32,
    kFtmDividedBy64,
    kFtmDividedBy128
}ftm_clock_ps_t;

/*! @brief FlexTimer pre-scaler factor for the deadtime insertion*/
typedef enum _ftm_deadtime_ps
{
    kFtmDivided1 = 1,
    kFtmDivided4 = 2,
    kFtmDivided16 = 3,
}ftm_deadtime_ps_t;

/*! @brief FlexTimer operation mode, capture, output, dual */
typedef enum _ftm_config_mode_t
{
    kFtmInputCapture,
    kFtmOutputCompare,
    kFtmEdgeAlignedPWM,
    kFtmCenterAlignedPWM,
    kFtmCombinedPWM,
    kFtmDualEdgeCapture
}ftm_config_mode_t;

/*! @brief FlexTimer input capture edge mode, rising edge, or falling edge */
typedef enum _ftm_input_capture_edge_mode_t
{
   kFtmRisingEdge = 0,
   kFtmFallingEdge,
   kFtmRisingAndFalling
}ftm_input_capture_edge_mode_t;

/*! @brief FlexTimer output compare edge mode. Toggle, clear or set.*/
typedef enum _ftm_output_compare_edge_mode_t
{
   kFtmToggleOnMatch = 0,
   kFtmClearOnMatch,
   kFtmSetOnMatch
}ftm_output_compare_edge_mode_t;

/*! @brief FlexTimer PWM output pulse mode, high-true or low-true on match up */
typedef enum _ftm_pwm_edge_mode_t
{
    kFtmHighTrue = 0,
    kFtmLowTrue
}ftm_pwm_edge_mode_t;

/*! @brief FlexTimer dual capture edge mode, one shot or continuous */
typedef enum _ftm_dual_capture_edge_mode_t
{
    kFtmOneShout = 0,
    kFtmContinuous
}ftm_dual_capture_edge_mode_t;

/*! @brief FlexTimer quadrature decode modes, phase encode or count and direction mode */
typedef enum _ftm_quad_decode_mode_t
{
    kFtmQuadPhaseEncode = 0,
    kFtmQuadCountAndDir
}ftm_quad_decode_mode_t;

/*! @brief FlexTimer quadrature phase polarities, normal or inverted polarity */
typedef enum _ftm_quad_phase_polarity_t
{
    kFtmQuadPhaseNormal = 0,
    kFtmQuadPhaseInvert
}ftm_quad_phase_polarity_t;

/*! @brief FlexTimer edge mode*/
typedef union _ftm_edge_mode_t
{
    ftm_input_capture_edge_mode_t  input_capture_edge_mode;
    ftm_output_compare_edge_mode_t output_compare_edge_mode;
    ftm_pwm_edge_mode_t            ftm_pwm_edge_mode;
    ftm_dual_capture_edge_mode_t   ftm_dual_capture_edge_mode;
}ftm_edge_mode_t;

/*!
 * @brief FlexTimer driver PWM parameter
 *
 */
typedef struct FtmPwmParam
{
    ftm_config_mode_t mode;          /*!< FlexTimer PWM operation mode */
    ftm_pwm_edge_mode_t edgeMode;    /*!< PWM output mode */
    uint32_t uFrequencyHZ;           /*!< PWM period in Hz */
    uint32_t uDutyCyclePercent;      /*!< PWM pulse width, value should be between 0 to 100
                                          0=inactive signal(0% duty cycle)...
                                          100=active signal (100% duty cycle). */
    uint16_t uFirstEdgeDelayPercent; /*!< Used only in combined PWM mode to generate asymmetrical PWM.
                                          Specifies the delay to the first edge in a PWM period.
                                          If unsure please leave as 0, should be specified as
                                          percentage of the PWM period*/
}ftm_pwm_param_t;

/*! @brief FlexTimer quadrature decode phase parameters */
typedef struct FtmPhaseParam
{
    bool kFtmPhaseInputFilter;      /*!< false: disable phase filter, true: enable phase filter */
    uint32_t kFtmPhaseFilterVal;    /*!< Filter value, used only if phase input filter is enabled */
    ftm_quad_phase_polarity_t kFtmPhasePolarity; /*!< kFtmQuadPhaseNormal or kFtmQuadPhaseInvert */
}ftm_phase_params_t;

/*FTM timer control*/
/*!
 * @brief Sets the FTM clock source.
 *
 * @param ftmBaseAddr The FTM base address
 * @param clock  The FTM peripheral clock selection\n
 *        bits - 00: No clock  01: system clock  10: fixed clock   11: External clock
 */
static inline void FTM_HAL_SetClockSource(uint32_t ftmBaseAddr, ftm_clock_source_t clock)
{
    BW_FTM_SC_CLKS(ftmBaseAddr, clock);
}

/*!
 * @brief Reads the FTM clock source.
 *
 * @param ftmBaseAddr The FTM base address
 *
 * @return  The FTM clock source selection\n
 *          bits - 00: No clock  01: system clock  10: fixed clock   11:External clock
 */
static inline uint8_t FTM_HAL_GetClockSource(uint32_t ftmBaseAddr)
{
    return BR_FTM_SC_CLKS(ftmBaseAddr);
}

/*!
 * @brief Sets the FTM clock divider.
 *
 * @param ftmBaseAddr The FTM base address
 * @param ps  The FTM peripheral clock pre-scale divider
 */
static inline void FTM_HAL_SetClockPs(uint32_t ftmBaseAddr, ftm_clock_ps_t ps)
{
    BW_FTM_SC_PS(ftmBaseAddr, ps);
}

/*!
 * @brief Reads the FTM clock divider.
 *
 * @param ftmBaseAddr The FTM base address
 *
 * @return The FTM clock pre-scale divider
 */
static inline uint8_t FTM_HAL_GetClockPs(uint32_t ftmBaseAddr)
{
    return BR_FTM_SC_PS(ftmBaseAddr);
}

/*!
 * @brief Enables the FTM peripheral timer overflow interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 */
static inline void FTM_HAL_EnableTimerOverflowInt(uint32_t ftmBaseAddr)
{
    HW_FTM_SC_SET(ftmBaseAddr, BM_FTM_SC_TOIE);
}

/*!
 * @brief Disables the FTM peripheral timer overflow interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 */
static inline void FTM_HAL_DisableTimerOverflowInt(uint32_t ftmBaseAddr)
{
     HW_FTM_SC_CLR(ftmBaseAddr, BM_FTM_SC_TOIE);
}

/*!
 * @brief Reads the bit that controls enabling the FTM timer overflow interrupt.
 *
 * @param baseAddr FTM module base address.
 * @retval true if overflow interrupt is enabled, false if not
 */
static inline bool FTM_HAL_IsOverflowIntEnabled(uint32_t baseAddr)
{
    return (bool)(BR_FTM_SC_TOIE(baseAddr));
}

/*!
 * @brief Clears the timer overflow interrupt flag.
 *
 * @param ftmBaseAddr The FTM base address
 */
static inline void FTM_HAL_ClearTimerOverflow(uint32_t ftmBaseAddr)
{
    BW_FTM_SC_TOF(ftmBaseAddr, 0);
}

/*!
 * @brief Returns the FTM peripheral timer overflow interrupt flag.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval true if overflow, false if not
 */
static inline bool FTM_HAL_HasTimerOverflowed(uint32_t ftmBaseAddr)
{
     return BR_FTM_SC_TOF(ftmBaseAddr);
}

/*!
 * @brief Sets the FTM center-aligned PWM select.
 *
 * @param ftmBaseAddr The FTM base address
 * @param mode 1:upcounting mode 0:up_down counting mode
 */
static inline void FTM_HAL_SetCpwms(uint32_t ftmBaseAddr, uint8_t mode)
{
    assert(mode < 2);
    BW_FTM_SC_CPWMS(ftmBaseAddr, mode);
}

/*!
 * @brief Sets the FTM peripheral current counter value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param val  FTM timer counter value to be set
 */
static inline void  FTM_HAL_SetCounter(uint32_t ftmBaseAddr,uint16_t val)
{
    BW_FTM_CNT_COUNT(ftmBaseAddr, val);
}

/*!
 * @brief Returns the FTM peripheral current counter value.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval current FTM timer counter value
 */
static inline uint16_t  FTM_HAL_GetCounter(uint32_t ftmBaseAddr)
{
    return BR_FTM_CNT_COUNT(ftmBaseAddr);
}

/*!
 * @brief Sets the FTM peripheral timer modulo value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param val The value to be set to the timer modulo
 */
static inline void FTM_HAL_SetMod(uint32_t ftmBaseAddr, uint16_t val)
{
    BW_FTM_MOD_MOD(ftmBaseAddr, val);
}

/*!
 * @brief Returns the FTM peripheral counter modulo value.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval FTM timer modulo value
 */
static inline uint16_t  FTM_HAL_GetMod(uint32_t ftmBaseAddr)
{
    return BR_FTM_MOD_MOD(ftmBaseAddr);
}

/*!
 * @brief Sets the FTM peripheral timer counter initial value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param val initial value to be set
 */
static inline void FTM_HAL_SetCounterInitVal(uint32_t ftmBaseAddr, uint16_t val)
{
    BW_FTM_CNTIN_INIT(ftmBaseAddr, val & BM_FTM_CNTIN_INIT);
}

/*!
 * @brief Returns the FTM peripheral counter initial value.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval FTM timer counter initial value
 */
static inline uint16_t  FTM_HAL_GetCounterInitVal(uint32_t ftmBaseAddr)
{
    return BR_FTM_CNTIN_INIT(ftmBaseAddr);
}

/*FTM channel operating mode (Mode, edge and level selection) for capture, output, PWM, combine, dual */
/*!
 * @brief Sets the FTM peripheral timer channel mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param selection The mode to be set valid value MSnB:MSnA :00,01, 10, 11
 */
static inline void FTM_HAL_SetChnMSnBAMode(uint32_t ftmBaseAddr, uint8_t channel, uint8_t selection)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    BW_FTM_CnSC_MSA(ftmBaseAddr, channel, selection & 1);
    BW_FTM_CnSC_MSB(ftmBaseAddr, channel, selection & 2 ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer channel edge level.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param level The rising or falling edge to be set, valid value ELSnB:ELSnA :00,01, 10, 11
 */
static inline void FTM_HAL_SetChnEdgeLevel(uint32_t ftmBaseAddr, uint8_t channel, uint8_t level)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    BW_FTM_CnSC_ELSA(ftmBaseAddr, channel, level & 1 ? 1 : 0);
    BW_FTM_CnSC_ELSB(ftmBaseAddr, channel, level & 2 ? 1 : 0);
}

/*!
 * @brief Gets the FTM peripheral timer channel mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval The MSnB:MSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t FTM_HAL_GetChnMode(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (BR_FTM_CnSC_MSA(ftmBaseAddr, channel)|| (BR_FTM_CnSC_MSB(ftmBaseAddr, channel) << 1));
}

/*!
 * @brief Gets the FTM peripheral timer channel edge level.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval The ELSnB:ELSnA mode value, will be 00,01, 10, 11
 */
static inline uint8_t FTM_HAL_GetChnEdgeLevel(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (BR_FTM_CnSC_ELSA(ftmBaseAddr, channel)|| (BR_FTM_CnSC_ELSB(ftmBaseAddr, channel) << 1));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel DMA.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param val enable or disable
 */
static inline void FTM_HAL_SetChnDmaCmd(uint32_t ftmBaseAddr, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    BW_FTM_CnSC_DMA(ftmBaseAddr, channel,(val? 1 : 0));
}

/*!
 * @brief Returns whether the FTM peripheral timer channel DMA is enabled.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval true if enabled, false if disabled
 */
static inline bool FTM_HAL_IsChnDma(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (BR_FTM_CnSC_DMA(ftmBaseAddr, channel) ? true : false);
}

/*!
 * @brief Enables the FTM peripheral timer channel(n) interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_EnableChnInt(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    BW_FTM_CnSC_CHIE(ftmBaseAddr, channel, 1);
}
/*!
 * @brief Disables the FTM peripheral timer channel(n) interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 */
static inline void FTM_HAL_DisableChnInt(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    BW_FTM_CnSC_CHIE(ftmBaseAddr, channel, 0);
}

/*!
 * @brief Returns whether any event for the FTM peripheral timer channel has occurred.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval true if event occurred, false otherwise.
 */
static inline bool FTM_HAL_HasChnEventOccurred(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (BR_FTM_CnSC_CHF(ftmBaseAddr, channel)) ? true : false;
}

/*FTM channel control*/
/*!
 * @brief Sets the FTM peripheral timer channel counter value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param val counter value to be set
 */
static inline void FTM_HAL_SetChnCountVal(uint32_t ftmBaseAddr, uint8_t channel, uint16_t val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    HW_FTM_CnV_WR(ftmBaseAddr, channel, val);
}

/*!
 * @brief Gets the FTM peripheral timer channel counter value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval val return current channel counter value
 */
static inline uint16_t FTM_HAL_GetChnCountVal(uint32_t ftmBaseAddr, uint8_t channel, uint16_t val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return BR_FTM_CnV_VAL(ftmBaseAddr, channel);
}

/*!
 * @brief Gets the FTM peripheral timer  channel event status.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval val return current channel event status value
 */
static inline uint32_t FTM_HAL_GetChnEventStatus(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    return (HW_FTM_STATUS_RD(ftmBaseAddr)&(1U << channel)) ? true : false;
    /*return BR_FTM_STATUS(ftmBaseAddr, channel);*/
}

/*!
 * @brief Clears the FTM peripheral timer all channel event status.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @retval val return current channel counter value
 */
static inline void FTM_HAL_ClearChnEventStatus(uint32_t ftmBaseAddr, uint8_t channel)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    HW_FTM_STATUS_CLR(ftmBaseAddr, 1U << channel);
}

/*!
 * @brief Sets the FTM peripheral timer channel output mask.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param mask mask to be set 0 or 1, unmasked or masked
 */
static inline void FTM_HAL_SetChnOutputMask(uint32_t ftmBaseAddr, uint8_t channel, bool  mask)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    mask? HW_FTM_OUTMASK_SET(ftmBaseAddr, 1U << channel) : HW_FTM_OUTMASK_CLR(ftmBaseAddr, 1U << channel);
    /* BW_FTM_OUTMASK_CHnOM(ftmBaseAddr, channel,mask); */
}

/*!
 * @brief Sets the FTM peripheral timer channel output initial state 0 or 1.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param state counter value to be set 0 or 1
 */
static inline void FTM_HAL_SetChnOutputInitState(uint32_t ftmBaseAddr, uint8_t channel, uint8_t state)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    HW_FTM_OUTINIT_CLR(ftmBaseAddr, 1U << channel);
    HW_FTM_OUTINIT_SET(ftmBaseAddr, (uint8_t)(state << channel));
}

/*!
 * @brief Sets the FTM peripheral timer channel output polarity.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param pol polarity to be set 0 or 1
 */
static inline void FTM_HAL_SetChnOutputPolarity(uint32_t ftmBaseAddr, uint8_t channel, uint8_t pol)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    HW_FTM_POL_CLR(ftmBaseAddr, 1U << channel);
    HW_FTM_POL_SET(ftmBaseAddr, (uint8_t)(pol << channel));
}
/*!
 * @brief Sets the FTM peripheral timer channel input polarity.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param pol polarity  to be set, 0: active high, 1:active low
 */
static inline void FTM_HAL_SetChnFaultInputPolarity(uint32_t ftmBaseAddr, uint8_t channel, uint8_t pol)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    HW_FTM_FLTPOL_CLR(ftmBaseAddr,  1U << channel);
    HW_FTM_FLTPOL_SET(ftmBaseAddr,  (uint8_t)(pol<<channel));
}


/*Feature mode selection HAL*/
    /*FTM fault control*/
/*!
 * @brief Enables the FTM peripheral timer fault interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 */
static inline void FTM_HAL_EnableFaultInt(uint32_t ftmBaseAddr)
{
    BW_FTM_MODE_FAULTIE(ftmBaseAddr, 1);
}

/*!
 * @brief Disables the FTM peripheral timer fault interrupt.
 *
 * @param ftmBaseAddr The FTM base address
 */
static inline void FTM_HAL_DisableFaultInt(uint32_t ftmBaseAddr)
{
    BW_FTM_MODE_FAULTIE(ftmBaseAddr, 0);
}

/*!
 * @brief Defines the FTM fault control mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param mode, valid options are 1, 2, 3, 4
 */
static inline void FTM_HAL_SetFaultControlMode(uint32_t ftmBaseAddr, uint8_t mode)
{
    BW_FTM_MODE_FAULTM(ftmBaseAddr, mode);
}

/*!
 * @brief Enables or disables the FTM peripheral timer capture test mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true to enable capture test mode, false to disable
 */
static inline void FTM_HAL_SetCaptureTestCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_MODE_CAPTEST(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM write protection.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true: Write-protection is enabled, false: Write-protection is disabled
 */
static inline void FTM_HAL_SetWriteProtectionCmd(uint32_t ftmBaseAddr, bool enable)
{
     enable ? BW_FTM_FMS_WPEN(ftmBaseAddr, 1) : BW_FTM_MODE_WPDIS(ftmBaseAddr, 1);
}

/*!
 * @brief Enables the FTM peripheral timer group.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true: all registers including FTM-specific registers are available
 *                false: only the TPM-compatible registers are available
 */
static inline void FTM_HAL_Enable(uint32_t ftmBaseAddr, bool enable)
{
     assert(BR_FTM_MODE_WPDIS(ftmBaseAddr));
     BW_FTM_MODE_FTMEN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Initializes the channels output.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true: the channels output is initialized according to the state of OUTINIT reg
 *                false: has no effect
 */
static inline void FTM_HAL_SetInitChnOutputCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_MODE_INIT(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer sync mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true: no restriction both software and hardware triggers can be used\n
 *                false: software trigger can only be used for MOD and CnV synch, hardware trigger
 *                       only for OUTMASK and FTM counter synch.
 */
static inline void FTM_HAL_SetPwmSyncMode(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_MODE_PWMSYNC(ftmBaseAddr, enable ? 1 : 0);
}

/*FTM synchronization control*/
/*!
 * @brief Enables or disables the FTM peripheral timer software trigger.
 *
 * @param ftmBaseAddr The FTM base address.
 * @param enable  true: software trigger is selected, false: software trigger is not selected
 */
static inline void FTM_HAL_SetSoftwareTriggerCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNC_SWSYNC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the FTM peripheral timer hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param trigger_num  0, 1, 2 for trigger0, trigger1 and trigger3
 * @param enable true: enable hardware trigger from field trigger_num for PWM synch
 *               false: disable hardware trigger from field trigger_num for PWM synch
 */
void FTM_HAL_SetHardwareTrigger(uint32_t ftmBaseAddr, uint8_t trigger_num, bool enable);

/*!
 * @brief Determines when the OUTMASK register is updated with the value of its buffer.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true if OUTMASK register is updated only by PWM sync\n
 *                false if OUTMASK register is updated in all rising edges of the system clock
 */
static inline void FTM_HAL_SetOutmaskPwmSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNC_SYNCHOM(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Determines if the FTM counter is re-initialized when the selected trigger for
 * synchronization is detected.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to update FTM counter when triggered , false to count normally
 */
static inline void FTM_HAL_SetCountReinitSyncCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNC_REINIT(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM peripheral timer maximum loading points.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to enable maximum loading point, false to disable
 */
static inline void FTM_HAL_SetMaxLoadingCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNC_CNTMAX(ftmBaseAddr, enable ? 1 : 0);
}
/*!
 * @brief Enables or disables the FTM peripheral timer minimum loading points.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to enable minimum loading point, false to disable
 */
static inline void FTM_HAL_SetMinLoadingCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNC_CNTMIN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Combines the channel control.
 *
 * Returns an index for each channel pair.
 *
 * @param channel  The FTM peripheral channel number.
 * @return 0 for channel pair 0 & 1\n
 *         1 for channel pair 2 & 3\n
 *         2 for channel pair 4 & 5\n
 *         3 for channel pair 6 & 7
 */
uint32_t FTM_HAL_GetChnPairIndex(uint8_t channel);

/*!
 * @brief Enables the FTM peripheral timer channel pair fault control.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable fault control, false to disable
 */
static inline  void FTM_HAL_SetDualChnFaultCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr, BM_FTM_COMBINE_FAULTEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr, BM_FTM_COMBINE_FAULTEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair counter PWM sync.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable PWM synchronization, false to disable
 */
static inline void FTM_HAL_SetDualChnPwmSyncCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr, BM_FTM_COMBINE_SYNCEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr, BM_FTM_COMBINE_SYNCEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disabled the FTM peripheral timer channel pair deadtime insertion.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable deadtime insertion, false to disable
 */
static inline void FTM_HAL_SetDualChnDeadtimeCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr,  BM_FTM_COMBINE_DTEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr,  BM_FTM_COMBINE_DTEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel dual edge capture decap.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable dual edge capture mode, false to disable
 */
static inline void FTM_HAL_SetDualChnDecapCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr, BM_FTM_COMBINE_DECAP0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr, BM_FTM_COMBINE_DECAP0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables the FTM peripheral timer dual edge capture mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable dual edge capture, false to disable
 */
static inline void FTM_HAL_SetDualEdgeCaptureCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr,  BM_FTM_COMBINE_DECAPEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr,  BM_FTM_COMBINE_DECAPEN0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair output complement mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable complementary mode, false to disable
 */
static inline void FTM_HAL_SetDualChnCompCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr,  BM_FTM_COMBINE_COMP0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr,  BM_FTM_COMBINE_COMP0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));

}

/*!
 * @brief Enables or disables the FTM peripheral timer channel pair output combine mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number
 * @param enable  True to enable channel pair to combine, false to disable
 */
static inline void FTM_HAL_SetDualChnCombineCmd(uint32_t ftmBaseAddr, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    enable ? HW_FTM_COMBINE_SET(ftmBaseAddr, BM_FTM_COMBINE_COMBINE0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH)):
             HW_FTM_COMBINE_CLR(ftmBaseAddr, BM_FTM_COMBINE_COMBINE0 << (FTM_HAL_GetChnPairIndex(channel) * FTM_COMBINE_CHAN_CTRL_WIDTH));
}

/*FTM dead time insertion control*/
/*!
 * @brief Sets the FTM deadtime divider.
 *
 * @param ftmBaseAddr The FTM base address
 * @param divider  The FTM peripheral prescale divider\n
 *                 0x :divided by 1, 10: divided by 4, 11:divided by 16
 */
static inline void FTM_HAL_SetDeadtimePrescale(uint32_t ftmBaseAddr, ftm_deadtime_ps_t divider)
{
    BW_FTM_DEADTIME_DTPS(ftmBaseAddr, divider);
}

/*!
 * @brief Sets the FTM deadtime value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param count  The FTM peripheral  prescale divider\n
 *               0: no counts inserted, 1: 1 count is inserted, 2: 2 count is inserted....
 */
static inline void FTM_HAL_SetDeadtimeCount(uint32_t ftmBaseAddr, uint8_t count)
{
    BW_FTM_DEADTIME_DTVAL(ftmBaseAddr, count);
}

/*!
* @brief Enables or disables the generation of the trigger when the FTM counter is equal to the CNTIN register.
*
* @param ftmBaseAddr The FTM base address
* @param enable  True to enable, false to disable
*/
static inline void FTM_HAL_SetInitTriggerCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_EXTTRIG_INITTRIGEN(ftmBaseAddr, enable ? 1 : 0);
}

/*FTM external trigger */
/*!
 * @brief Enables or disables the generation of the FTM peripheral timer channel trigger.
 *
 * Enables or disables the when the generation of the FTM peripheral timer channel trigger when the
 * FTM counter is equal to its initial value. Channels 6 and 7 cannot be used as triggers.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel Channel to be enabled,  valid value 0, 1, 2, 3, 4, 5
 * @param val  True to enable, false to disable
 */
void FTM_HAL_SetChnTriggerCmd(uint32_t ftmBaseAddr, uint8_t channel, bool val);

/*!
 * @brief Checks whether any channel trigger event has occurred.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval true if there is a channel trigger event, false if not.
 */
static inline bool FTM_HAL_IsChnTriggerGenerated(uint32_t ftmBaseAddr)
{
    return BR_FTM_EXTTRIG_TRIGF(ftmBaseAddr);
}


/*Fault mode status*/
/*!
 * @brief Gets the FTM detected fault input.
 *
 * This function reads the status for all fault inputs
 *
 * @param ftmBaseAddr The FTM base address
 * @retval Return fault byte
 */
static inline uint8_t FTM_HAL_GetDetectedFaultInput(uint32_t ftmBaseAddr)
{
    return (HW_FTM_FMS(ftmBaseAddr).U & 0x0f);
}
/*!
 * @brief Checks whether the write protection is enabled.
 *
 * @param ftmBaseAddr The FTM base address
 * @retval True if enabled, false if not
 */
static inline bool FTM_HAL_IsWriteProtectionEnabled(uint32_t ftmBaseAddr)
{
    return BR_FTM_FMS_WPEN(ftmBaseAddr) ? true : false;
}

/*Quadrature decoder control*/

/*!
 * @brief Enables the channel quadrature decoder.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetQuadDecoderCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_QDCTRL_QUADEN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the phase A input filter.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable true enables the phase input filter, false disables the filter
 */
static inline void FTM_HAL_SetQuadPhaseAFilterCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_QDCTRL_PHAFLTREN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the phase B input filter.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable true enables the phase input filter, false disables the filter
 */
static inline void FTM_HAL_SetQuadPhaseBFilterCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_QDCTRL_PHBFLTREN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Selects polarity for the quadrature decode phase A input.
 *
 * @param ftmBaseAddr The FTM base address
 * @param mode 0: Normal polarity, 1: Inverted polarity
 */
static inline void FTM_HAL_SetQuadPhaseAPolarity(uint32_t ftmBaseAddr,
                                                           ftm_quad_phase_polarity_t mode)
{
    BW_FTM_QDCTRL_PHAPOL(ftmBaseAddr, mode);
}

/*!
 * @brief Selects polarity for the quadrature decode phase B input.
 *
 * @param ftmBaseAddr The FTM base address
 * @param mode 0: Normal polarity, 1: Inverted polarity
 */
static inline void FTM_HAL_SetQuadPhaseBPolarity(uint32_t ftmBaseAddr,
                                                           ftm_quad_phase_polarity_t mode)
{
    BW_FTM_QDCTRL_PHBPOL(ftmBaseAddr, mode);
}

/*!
 * @brief Sets the encoding mode used in quadrature decoding mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param quadMode 0: Phase A and Phase B encoding mode\n
 *                 1: Count and direction encoding mode
 */
static inline void FTM_HAL_SetQuadMode(uint32_t ftmBaseAddr, ftm_quad_decode_mode_t quadMode)
{
    BW_FTM_QDCTRL_QUADMODE(ftmBaseAddr, quadMode);
}

/*!
 * @brief Gets the FTM counter direction in quadrature mode.
 *
 * @param ftmBaseAddr The FTM base address
 *
 * @retval 1 if counting direction is increasing, 0 if counting direction is decreasing
 */
static inline uint8_t FTM_HAL_GetQuadDir(uint32_t ftmBaseAddr)
{
    return BR_FTM_QDCTRL_QUADMODE(ftmBaseAddr);
}

/*!
 * @brief Gets the Timer overflow direction in quadrature mode.
 *
 * @param ftmBaseAddr The FTM base address
 *
 * @retval 1 if TOF bit was set on the top of counting, o if TOF bit was set on the bottom of counting
 */
static inline uint8_t FTM_HAL_GetQuadTimerOverflowDir(uint32_t ftmBaseAddr)
{
    return BR_FTM_QDCTRL_TOFDIR(ftmBaseAddr);
}

/*!
 * @brief Sets the FTM peripheral timer channel input capture filter value.
 * @param ftmBaseAddr The FTM base address
 * @param channel  The FTM peripheral channel number, only 0,1,2,3, channel 4, 5,6, 7 don't have.
 * @param val  Filter value to be set
 */
void FTM_HAL_SetChnInputCaptureFilter(uint32_t ftmBaseAddr, uint8_t channel, uint8_t val);

/*!
 * @brief Sets the fault input filter value.
 *
 * @param ftmBaseAddr The FTM base address
 * @param val fault input filter value
 */
static inline void FTM_HAL_SetFaultInputFilterVal(uint32_t ftmBaseAddr, uint32_t val)
{
    BW_FTM_FLTCTRL_FFVAL(ftmBaseAddr, val);
}

/*!
 * @brief Enables or disables the fault input filter.
 *
 * @param ftmBaseAddr The FTM base address
 * @param inputNum fault input to be configured, valid value 0, 1, 2, 3
 * @param val  true to enable fault input filter, false to disable fault input filter
 */
static inline void FTM_HAL_SetFaultInputFilterCmd(uint32_t ftmBaseAddr, uint8_t inputNum, bool val)
{
    assert(inputNum < HW_CHAN4);
    val ? HW_FTM_FLTCTRL_SET(ftmBaseAddr, (1U << (inputNum + 4))) :
          HW_FTM_FLTCTRL_CLR(ftmBaseAddr, (1U << (inputNum + 4)));
}

/*!
 * @brief Enables or disables the fault input.
 *
 * @param ftmBaseAddr The FTM base address
 * @param inputNum fault input to be configured, valid value 0, 1, 2, 3
 * @param val  true to enable fault input, false to disable fault input
 */
static inline void FTM_HAL_SetFaultInputCmd(uint32_t ftmBaseAddr, uint8_t inputNum, bool val)
{
    assert(inputNum < HW_CHAN4);
    val ? HW_FTM_FLTCTRL_SET(ftmBaseAddr, (1U << inputNum)) :
          HW_FTM_FLTCTRL_CLR(ftmBaseAddr, (1U << inputNum));
}

/*!
 * @brief Enables or disables the channel invert for a channel pair.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel The FTM peripheral channel number
 * @param val  true to enable channel inverting, false to disable channel inverting
 */
static inline void FTM_HAL_SetDualChnInvertCmd(uint32_t ftmBaseAddr, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);

    val ? HW_FTM_INVCTRL_SET(ftmBaseAddr, (1U << FTM_HAL_GetChnPairIndex(channel))) :
          HW_FTM_INVCTRL_CLR(ftmBaseAddr, (1U << FTM_HAL_GetChnPairIndex(channel)));
}

/*FTM software output control*/
/*!
 * @brief Enables or disables the channel software output control.
 * @param ftmBaseAddr The FTM base address
 * @param channel Channel to be enabled or disabled
 * @param val  true to enable, channel output will be affected by software output control\n
                  false to disable, channel output is unaffected
 */
static inline void FTM_HAL_SetChnSoftwareCtrlCmd(uint32_t ftmBaseAddr, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? HW_FTM_SWOCTRL_SET(ftmBaseAddr, (1U << channel)) :
          HW_FTM_SWOCTRL_CLR(ftmBaseAddr, (1U << channel));
}
/*!
 * @brief Sets the channel software output control value.
 *
 * @param ftmBaseAddr The FTM base address.
 * @param channel Channel to be configured
 * @param val  True to set 1, false to set 0
 */
static inline void FTM_HAL_SetChnSoftwareCtrlVal(uint32_t ftmBaseAddr, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? HW_FTM_SWOCTRL_SET(ftmBaseAddr, (1U << (channel + 8))) :
          HW_FTM_SWOCTRL_CLR(ftmBaseAddr, (1U << (channel + 8)));
}

/*FTM PWM load control*/
/*!
 * @brief Enables or disables the loading of MOD, CNTIN and CV with values of their write buffer.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true to enable, false to disable
 */
static inline void FTM_HAL_SetPwmLoadCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_PWMLOAD_LDOK(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Includes or excludes the channel in the matching process.
 *
 * @param ftmBaseAddr The FTM base address
 * @param channel Channel to be configured
 * @param val  true means include the channel in the matching process\n
 *                false means do not include channel in the matching process
 */
static inline void FTM_HAL_SetPwmLoadChnSelCmd(uint32_t ftmBaseAddr, uint8_t channel, bool val)
{
    assert(channel < FSL_FEATURE_FTM_CHANNEL_COUNT);
    val ? HW_FTM_PWMLOAD_SET(ftmBaseAddr, 1U << channel) : HW_FTM_PWMLOAD_CLR(ftmBaseAddr, 1U << channel);
}

/*FTM configuration*/
/*!
 * @brief Enables or disables the FTM global time base signal generation to other FTM's.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetGlobalTimeBaseOutputCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_CONF_GTBEOUT(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Enables or disables the FTM timer global time base.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  True to enable, false to disable
 */
static inline void FTM_HAL_SetGlobalTimeBaseCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_CONF_GTBEEN(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the BDM mode..
 *
 * @param ftmBaseAddr The FTM base address
 * @param val  FTM behaviour in BDM mode, options are 0,1,2,3
 */
static inline void FTM_HAL_SetBdmMode(uint32_t ftmBaseAddr, uint8_t val)
{
    BW_FTM_CONF_BDMMODE(ftmBaseAddr, val);
}

/*!
 * @brief Sets the FTM timer TOF Frequency
 *
 * @param ftmBaseAddr The FTM base address
 * @param val  Value of the TOF bit set frequency
 */
static inline void FTM_HAL_SetTofFreq(uint32_t ftmBaseAddr, uint8_t val)
{
    BW_FTM_CONF_NUMTOF(ftmBaseAddr, val);
}

/*FTM sync configuration*/
  /*hardware sync*/
/*!
 * @brief Sets the sync mode for the FTM SWOCTRL register when using a hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means the hardware trigger activates register sync\n
 *                false means the hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetSwoctrlHardwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_HWSOC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM INVCTRL register when using a hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means the hardware trigger activates register sync\n
 *                false means the hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetInvctrlHardwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_HWINVC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM OUTMASK register when using a hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetOutmaskHardwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_HWOM(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM MOD, CNTIN and CV registers when using a hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetModCntinCvHardwareSycnModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_HWWRBUF(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM counter register when using a hardware trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means hardware trigger activates register sync\n
 *                false means hardware trigger does not activate register sync.
 */
static inline void FTM_HAL_SetCounterHardwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_HWRSTCNT(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM SWOCTRL register when using a software trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetSwoctrlSoftwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWSOC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM INVCTRL register when using a software trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetInvctrlSoftwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWINVC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM OUTMASK register when using a software trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetOutmaskSoftwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWOM(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets synch mode for FTM MOD, CNTIN and CV registers when using a software trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetModCntinCvSoftwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWWRBUF(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets sync mode for FTM counter register when using a software trigger.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means software trigger activates register sync\n
 *                false means software trigger does not activate register sync.
 */
static inline void FTM_HAL_SetCounterSoftwareSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWRSTCNT(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the PWM synchronization mode to enhanced or legacy.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means use Enhanced PWM synchronization\n
 *                false means to use Legacy mode
 */
static inline void FTM_HAL_SetPwmSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SYNCMODE(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the SWOCTRL register PWM synchronization mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means SWOCTRL register is updated by PWM synch\n
 *                false means SWOCTRL register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetSwoctrlPwmSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_SWOC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the INVCTRL register PWM synchronization mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means INVCTRL register is updated by PWM synch\n
 *                false means INVCTRL register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetInvctrlPwmSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_INVC(ftmBaseAddr, enable ? 1 : 0);
}

/*!
 * @brief Sets the CNTIN register PWM synchronization mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param enable  true means CNTIN register is updated by PWM synch\n
 *                false means CNTIN register is updated at all rising edges of system clock
 */
static inline void FTM_HAL_SetCntinPwmSyncModeCmd(uint32_t ftmBaseAddr, bool enable)
{
    BW_FTM_SYNCONF_CNTINC(ftmBaseAddr, enable ? 1 : 0);
}


/*HAL functionality*/
/*!
 * @brief Resets the FTM registers
 *
 * @param instance The FTM instance number
 * @param ftmBaseAddr The FTM base address
 */
void FTM_HAL_Reset(uint32_t ftmBaseAddr, uint32_t instance);

/*!
 * @brief Initializes the FTM.
 *
 * @param ftmBaseAddr The FTM base address.
 */
void FTM_HAL_Init(uint32_t ftmBaseAddr);

/*Initializes the  5 FTM operating mode, input capture, output compare, PWM output(edge aligned, center-aligned, conbine), dual and quadrature).*/

/*void FTM_HAL_input_capture_mode(uint32_t ftmBaseAddr);*/
/*void FTM_HAL_output_compare_mode(uint32_t ftmBaseAddr);*/

/*!
 * @brief Enables the FTM timer when it is PWM output mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param config PWM configuration parameter
 * @param channel The channel or channel pair number(combined mode).
 */
void FTM_HAL_EnablePwmMode(uint32_t ftmBaseAddr, ftm_pwm_param_t *config, uint8_t channel);

/*!
 * @brief Disables the PWM output mode.
 *
 * @param ftmBaseAddr The FTM base address
 * @param config PWM configuration parameter
 * @param channel The channel or channel pair number(combined mode).
 */
void FTM_HAL_DisablePwmMode(uint32_t ftmBaseAddr, ftm_pwm_param_t *config, uint8_t channel);

/*void FTM_HAL_dual_mode(uint32_t ftmBaseAddr);*/
/*void FTM_HAL_quad_mode(uint32_t ftmBaseAddr);*/


/*void FTM_HAL_set_counting_mode(); //up, up down or free running counting mode*/
/*void FTM_HAL_set_deadtime(uint32_t ftmBaseAddr, uint_32 us);*/

/*! @}*/

#endif /* __FSL_FTM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

