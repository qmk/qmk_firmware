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

#if !defined(__FSL_SIM_HAL_K22F51212_H__)
#define __FSL_SIM_HAL_K22F51212_H__

/*! @addtogroup sim_hal*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief SIM USB clock source */
typedef enum _sim_usb_clock_source
{
    kSimUsbSrcClkIn,       /* USB CLKIN Clock */
    kSimUsbSrcPllFllSel    /* clock as selected by SOPT2[PLLFLLSEL] */
} sim_usb_clock_source_t;

/*! @brief SIM LPUART clock source */
typedef enum _sim_lpuart_clock_source
{
    kSimLpuartSrcNone,        /* Clock disabled */
    kSimLpuartSrcPllFllSel,   /* Clock as selected by SOPT2[PLLFLLSEL] */
    kSimLpuartSrcOscErclk,    /* OscErClk with special divider */
    kSimLpuartSrcMcgIrclk     /* MCGIRCLK */
} sim_lpuart_clock_source_t;

/*! @brief SIM PLLFLLSEL clock source select */
typedef enum _sim_pllfll_clock_sel
{
    kSimPllFllSelFll,       /* Fll clock */
    kSimPllFllSelPll,        /* Pll0 clock */
    kSimPllFllSelNone,      /* reserved */
    kSimPllFllSelIrc        /* IRC 48Mhz */
} sim_pllfll_clock_sel_t;

/*! @brief SIM OSC32KSEL clock source select */
typedef enum _sim_osc32k_clock_sel
{
    kSimOsc32kSelOsc32k,      /* OSC 32k clock */
    kSimOsc32kSelReserved,    /* Reserved */
    kSimOsc32kSelRtc32k,      /* RTC 32k clock */
    kSimOsc32kSelLpo          /* LPO clock */
} sim_osc32k_clock_sel_t;

/*! @brief SIM TRACESEL clock source select */
typedef enum _sim_trace_clock_sel
{
    kSimTraceMcgoutClk,       /* MCG out clock */
    kSimTraceCoreClk          /* core clock */
} sim_trace_clock_sel_t;

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _sim_clkout_clock_sel
{
    kSimClkoutFlexbusClk,       /* Flexbus clock */
    kSimClkoutReserved,         /* Reserved */
    kSimClkoutFlashClk,         /* Flash clock */
    kSimClkoutLpoClk,           /* LPO clock */
    kSimClkoutMcgIrcClk,        /* MCG out clock */
    kSimClkoutRtc32kClk,        /* RTC 32k clock */
    kSimClkoutOscErClk,
    KsimClkoutIrcClk
} sim_clkout_clock_sel_t;

/*! @brief SIM RTCCLKOUTSEL clock source select */
typedef enum _sim_rtcclkout_clock_sel
{
    kSimRtcClkout1hzClk,       /* 1Hz clock */
    kSimRtcClkout32kClk        /* 32KHz clock */
} sim_rtcclkout_clock_sel_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name IP related clock feature APIs*/
/*@{*/

/*!
 * @brief Enable the clock for DMA module.
 *
 * This function enables the clock for DMA moudle.
 * @param instance module device instance
 */
void SIM_HAL_EnableDmaClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for DMA module.
 *
 * This function disables the clock for DMA moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDmaClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DMA module.
 *
 * This function will get the clock gate state for DMA moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDmaGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for DMAMUX module.
 *
 * This function enables the clock for DMAMUX moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableDmamuxClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for DMAMUX module.
 *
 * This function disables the clock for DMAMUX moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDmamuxClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DMAMUX module.
 *
 * This function will get the clock gate state for DMAMUX moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDmamuxGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for PORT module.
 *
 * This function enables the clock for PORT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePortClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for PORT module.
 *
 * This function disables the clock for PORT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePortClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PORT module.
 *
 * This function will get the clock gate state for PORT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPortGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for EWM module.
 *
 * This function enables the clock for EWM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableEwmClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for EWM module.
 *
 * This function disables the clock for EWM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableEwmClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for EWM module.
 *
 * This function will get the clock gate state for EWM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetEwmGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for FLEXBUS module.
 *
 * This function enables the clock for FLEXBUS moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFlexbusClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for FLEXBUS module.
 *
 * This function disables the clock for FLEXBUS moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFlexbusClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FLEXBUS module.
 *
 * This function will get the clock gate state for FLEXBUS moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFlexbusGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for FTF module.
 *
 * This function enables the clock for FTF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFtfClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for FTF module.
 *
 * This function disables the clock for FTF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFtfClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FTF module.
 *
 * This function will get the clock gate state for FTF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFtfGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for CRC module.
 *
 * This function enables the clock for CRC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableCrcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for CRC module.
 *
 * This function disables the clock for CRC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableCrcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for CRC module.
 *
 * This function will get the clock gate state for CRC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetCrcGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for RNGA module.
 *
 * This function enables the clock for RNGA moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableRngaClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for RNGA module.
 *
 * This function disables the clock for RNGA moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableRngaClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for RNGA module.
 *
 * This function will get the clock gate state for RNGA moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetRngaGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for ADC module.
 *
 * This function enables the clock for ADC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableAdcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for ADC module.
 *
 * This function disables the clock for ADC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableAdcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for ADC module.
 *
 * This function will get the clock gate state for ADC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetAdcGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for CMP module.
 *
 * This function enables the clock for CMP moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableCmpClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for CMP module.
 *
 * This function disables the clock for CMP moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableCmpClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for CMP module.
 *
 * This function will get the clock gate state for CMP moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetCmpGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for DAC module.
 *
 * This function enables the clock for DAC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableDacClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for DAC module.
 *
 * This function disables the clock for DAC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableDacClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for DAC module.
 *
 * This function will get the clock gate state for DAC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetDacGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for VREF module.
 *
 * This function enables the clock for VREF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableVrefClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for VREF module.
 *
 * This function disables the clock for VREF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableVrefClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for VREF module.
 *
 * This function will get the clock gate state for VREF moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetVrefGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for SAI module.
 *
 * This function enables the clock for SAI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableSaiClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for SAI module.
 *
 * This function disables the clock for SAI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableSaiClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for SAI module.
 *
 * This function will get the clock gate state for SAI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetSaiGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for PDB module.
 *
 * This function enables the clock for PDB moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePdbClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for PDB module.
 *
 * This function disables the clock for PDB moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePdbClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PDB module.
 *
 * This function will get the clock gate state for PDB moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPdbGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for FTM module.
 *
 * This function enables the clock for FTM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableFtmClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for FTM module.
 *
 * This function disables the clock for FTM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableFtmClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for FTM module.
 *
 * This function will get the clock gate state for FTM moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetFtmGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for PIT module.
 *
 * This function enables the clock for PIT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnablePitClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for PIT module.
 *
 * This function disables the clock for PIT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisablePitClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for PIT module.
 *
 * This function will get the clock gate state for PIT moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetPitGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for LPTIMER module.
 *
 * This function enables the clock for LPTIMER moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableLptimerClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for LPTIMER module.
 *
 * This function disables the clock for LPTIMER moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableLptimerClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for LPTIMER module.
 *
 * This function will get the clock gate state for LPTIMER moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetLptimerGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for RTC module.
 *
 * This function enables the clock for RTC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableRtcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for RTC module.
 *
 * This function disables the clock for RTC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableRtcClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for RTC module.
 *
 * This function will get the clock gate state for RTC moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetRtcGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for USBFS module.
 *
 * This function enables the clock for USBFS moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableUsbClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for USBFS module.
 *
 * This function disables the clock for USBFS moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableUsbClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for USB module.
 *
 * This function will get the clock gate state for USB moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetUsbGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for SPI module.
 *
 * This function enables the clock for SPI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableSpiClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for SPI module.
 *
 * This function disables the clock for SPI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableSpiClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for SPI module.
 *
 * This function will get the clock gate state for SPI moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetSpiGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for I2C module.
 *
 * This function enables the clock for I2C moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableI2cClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for I2C module.
 *
 * This function disables the clock for I2C moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableI2cClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for I2C module.
 *
 * This function will get the clock gate state for I2C moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetI2cGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for UART module.
 *
 * This function enables the clock for UART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableUartClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for UART module.
 *
 * This function disables the clock for UART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableUartClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for UART module.
 *
 * This function will get the clock gate state for UART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetUartGateCmd(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Enable the clock for LPUART module.
 *
 * This function enables the clock for LPUART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_EnableLpuartClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Disable the clock for LPUART module.
 *
 * This function disables the clock for LPUART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 */
void SIM_HAL_DisableLpuartClock(uint32_t baseAddr, uint32_t instance);

/*!
 * @brief Get the the clock gate state for LPUART module.
 *
 * This function will get the clock gate state for LPUART moudle.
 *
 * @param baseAddr Base address for current SIM instance.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool SIM_HAL_GetLpuartGateCmd(uint32_t baseAddr, uint32_t instance);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* __FSL_SIM_HAL_K22F51212_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

