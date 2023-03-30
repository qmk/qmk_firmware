/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : CLOCKS
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_CLOCKS_DEFINED
#define HARDWARE_REGS_CLOCKS_DEFINED
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT0_CTRL_OFFSET _u(0x00000000)
#define CLOCKS_CLK_GPOUT0_CTRL_BITS   _u(0x00131de0)
#define CLOCKS_CLK_GPOUT0_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_GPOUT0_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_GPOUT0_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_BITS   _u(0x00001000)
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_MSB    _u(12)
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_LSB    _u(12)
#define CLOCKS_CLK_GPOUT0_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_GPOUT0_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_GPOUT0_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_BITS                 _u(0x000001e0)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_MSB                  _u(8)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x0)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x1)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x2)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x3)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    _u(0x4)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x5)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS        _u(0x6)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_USB        _u(0x7)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_ADC        _u(0x8)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_RTC        _u(0x9)
#define CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_REF        _u(0xa)
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT0_DIV_OFFSET _u(0x00000004)
#define CLOCKS_CLK_GPOUT0_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT0_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT0_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_GPOUT0_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_GPOUT0_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_GPOUT0_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_GPOUT0_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT0_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_GPOUT0_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT0_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_GPOUT0_SELECTED_OFFSET _u(0x00000008)
#define CLOCKS_CLK_GPOUT0_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT0_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_GPOUT0_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_GPOUT0_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_GPOUT0_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT1_CTRL_OFFSET _u(0x0000000c)
#define CLOCKS_CLK_GPOUT1_CTRL_BITS   _u(0x00131de0)
#define CLOCKS_CLK_GPOUT1_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_GPOUT1_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_GPOUT1_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_BITS   _u(0x00001000)
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_MSB    _u(12)
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_LSB    _u(12)
#define CLOCKS_CLK_GPOUT1_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_GPOUT1_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_GPOUT1_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_BITS                 _u(0x000001e0)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_MSB                  _u(8)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x0)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x1)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x2)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x3)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    _u(0x4)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x5)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_SYS        _u(0x6)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_USB        _u(0x7)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_ADC        _u(0x8)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_RTC        _u(0x9)
#define CLOCKS_CLK_GPOUT1_CTRL_AUXSRC_VALUE_CLK_REF        _u(0xa)
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT1_DIV_OFFSET _u(0x00000010)
#define CLOCKS_CLK_GPOUT1_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT1_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT1_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_GPOUT1_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_GPOUT1_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_GPOUT1_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_GPOUT1_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT1_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_GPOUT1_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT1_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_GPOUT1_SELECTED_OFFSET _u(0x00000014)
#define CLOCKS_CLK_GPOUT1_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT1_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_GPOUT1_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_GPOUT1_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_GPOUT1_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT2_CTRL_OFFSET _u(0x00000018)
#define CLOCKS_CLK_GPOUT2_CTRL_BITS   _u(0x00131de0)
#define CLOCKS_CLK_GPOUT2_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_GPOUT2_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_GPOUT2_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_BITS   _u(0x00001000)
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_MSB    _u(12)
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_LSB    _u(12)
#define CLOCKS_CLK_GPOUT2_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_GPOUT2_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_GPOUT2_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc_ph
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_BITS                 _u(0x000001e0)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_MSB                  _u(8)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x0)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x1)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x2)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x3)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x4)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x5)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_SYS        _u(0x6)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_USB        _u(0x7)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_ADC        _u(0x8)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_RTC        _u(0x9)
#define CLOCKS_CLK_GPOUT2_CTRL_AUXSRC_VALUE_CLK_REF        _u(0xa)
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT2_DIV_OFFSET _u(0x0000001c)
#define CLOCKS_CLK_GPOUT2_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT2_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT2_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_GPOUT2_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_GPOUT2_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_GPOUT2_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_GPOUT2_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT2_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_GPOUT2_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT2_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_GPOUT2_SELECTED_OFFSET _u(0x00000020)
#define CLOCKS_CLK_GPOUT2_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT2_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_GPOUT2_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_GPOUT2_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_GPOUT2_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_GPOUT3_CTRL_OFFSET _u(0x00000024)
#define CLOCKS_CLK_GPOUT3_CTRL_BITS   _u(0x00131de0)
#define CLOCKS_CLK_GPOUT3_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_GPOUT3_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_GPOUT3_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_DC50
// Description : Enables duty cycle correction for odd divisors
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_BITS   _u(0x00001000)
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_MSB    _u(12)
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_LSB    _u(12)
#define CLOCKS_CLK_GPOUT3_CTRL_DC50_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_GPOUT3_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_GPOUT3_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
//               0x3 -> clksrc_pll_usb
//               0x4 -> rosc_clksrc_ph
//               0x5 -> xosc_clksrc
//               0x6 -> clk_sys
//               0x7 -> clk_usb
//               0x8 -> clk_adc
//               0x9 -> clk_rtc
//               0xa -> clk_ref
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_BITS                 _u(0x000001e0)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_MSB                  _u(8)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x0)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x1)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x2)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x3)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x4)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x5)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_SYS        _u(0x6)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_USB        _u(0x7)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_ADC        _u(0x8)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_RTC        _u(0x9)
#define CLOCKS_CLK_GPOUT3_CTRL_AUXSRC_VALUE_CLK_REF        _u(0xa)
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_GPOUT3_DIV_OFFSET _u(0x00000028)
#define CLOCKS_CLK_GPOUT3_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT3_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_GPOUT3_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_GPOUT3_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_GPOUT3_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_GPOUT3_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_GPOUT3_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_GPOUT3_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_GPOUT3_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_GPOUT3_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_GPOUT3_SELECTED_OFFSET _u(0x0000002c)
#define CLOCKS_CLK_GPOUT3_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_GPOUT3_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_GPOUT3_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_GPOUT3_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_GPOUT3_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_REF_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_REF_CTRL_OFFSET _u(0x00000030)
#define CLOCKS_CLK_REF_CTRL_BITS   _u(0x00000063)
#define CLOCKS_CLK_REF_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_gpin0
//               0x2 -> clksrc_gpin1
#define CLOCKS_CLK_REF_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_BITS                 _u(0x00000060)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_MSB                  _u(6)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x0)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x1)
#define CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x2)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_CTRL_SRC
// Description : Selects the clock source glitchlessly, can be changed
//               on-the-fly
//               0x0 -> rosc_clksrc_ph
//               0x1 -> clksrc_clk_ref_aux
//               0x2 -> xosc_clksrc
#define CLOCKS_CLK_REF_CTRL_SRC_RESET                    "-"
#define CLOCKS_CLK_REF_CTRL_SRC_BITS                     _u(0x00000003)
#define CLOCKS_CLK_REF_CTRL_SRC_MSB                      _u(1)
#define CLOCKS_CLK_REF_CTRL_SRC_LSB                      _u(0)
#define CLOCKS_CLK_REF_CTRL_SRC_ACCESS                   "RW"
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_ROSC_CLKSRC_PH     _u(0x0)
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_CLKSRC_CLK_REF_AUX _u(0x1)
#define CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC        _u(0x2)
// =============================================================================
// Register    : CLOCKS_CLK_REF_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_REF_DIV_OFFSET _u(0x00000034)
#define CLOCKS_CLK_REF_DIV_BITS   _u(0x00000300)
#define CLOCKS_CLK_REF_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_REF_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_REF_DIV_INT_RESET  _u(0x1)
#define CLOCKS_CLK_REF_DIV_INT_BITS   _u(0x00000300)
#define CLOCKS_CLK_REF_DIV_INT_MSB    _u(9)
#define CLOCKS_CLK_REF_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_REF_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_REF_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               The glitchless multiplexer does not switch instantaneously (to
//               avoid glitches), so software should poll this register to wait
//               for the switch to complete. This register contains one decoded
//               bit for each of the clock sources enumerated in the CTRL SRC
//               field. At most one of these bits will be set at any time,
//               indicating that clock is currently present at the output of the
//               glitchless mux. Whilst switching is in progress, this register
//               may briefly show all-0s.
#define CLOCKS_CLK_REF_SELECTED_OFFSET _u(0x00000038)
#define CLOCKS_CLK_REF_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_REF_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_REF_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_REF_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_REF_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_SYS_CTRL_OFFSET _u(0x0000003c)
#define CLOCKS_CLK_SYS_CTRL_BITS   _u(0x000000e1)
#define CLOCKS_CLK_SYS_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_sys
//               0x1 -> clksrc_pll_usb
//               0x2 -> rosc_clksrc
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_BITS                 _u(0x000000e0)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_MSB                  _u(7)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x0)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x1)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    _u(0x2)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x3)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x4)
#define CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x5)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_CTRL_SRC
// Description : Selects the clock source glitchlessly, can be changed
//               on-the-fly
//               0x0 -> clk_ref
//               0x1 -> clksrc_clk_sys_aux
#define CLOCKS_CLK_SYS_CTRL_SRC_RESET                    _u(0x0)
#define CLOCKS_CLK_SYS_CTRL_SRC_BITS                     _u(0x00000001)
#define CLOCKS_CLK_SYS_CTRL_SRC_MSB                      _u(0)
#define CLOCKS_CLK_SYS_CTRL_SRC_LSB                      _u(0)
#define CLOCKS_CLK_SYS_CTRL_SRC_ACCESS                   "RW"
#define CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF            _u(0x0)
#define CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX _u(0x1)
// =============================================================================
// Register    : CLOCKS_CLK_SYS_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_SYS_DIV_OFFSET _u(0x00000040)
#define CLOCKS_CLK_SYS_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_SYS_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_SYS_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_SYS_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_SYS_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_SYS_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_SYS_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_SYS_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_SYS_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_SYS_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_SYS_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_SYS_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               The glitchless multiplexer does not switch instantaneously (to
//               avoid glitches), so software should poll this register to wait
//               for the switch to complete. This register contains one decoded
//               bit for each of the clock sources enumerated in the CTRL SRC
//               field. At most one of these bits will be set at any time,
//               indicating that clock is currently present at the output of the
//               glitchless mux. Whilst switching is in progress, this register
//               may briefly show all-0s.
#define CLOCKS_CLK_SYS_SELECTED_OFFSET _u(0x00000044)
#define CLOCKS_CLK_SYS_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_SYS_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_SYS_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_SYS_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_SYS_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_PERI_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_PERI_CTRL_OFFSET _u(0x00000048)
#define CLOCKS_CLK_PERI_CTRL_BITS   _u(0x00000ce0)
#define CLOCKS_CLK_PERI_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_PERI_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_PERI_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_PERI_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_PERI_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_PERI_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_PERI_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_PERI_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_PERI_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_PERI_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_PERI_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_PERI_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clk_sys
//               0x1 -> clksrc_pll_sys
//               0x2 -> clksrc_pll_usb
//               0x3 -> rosc_clksrc_ph
//               0x4 -> xosc_clksrc
//               0x5 -> clksrc_gpin0
//               0x6 -> clksrc_gpin1
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_BITS                 _u(0x000000e0)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_MSB                  _u(7)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS        _u(0x0)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x1)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x2)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x3)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x4)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x5)
#define CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x6)
// =============================================================================
// Register    : CLOCKS_CLK_PERI_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_PERI_SELECTED_OFFSET _u(0x00000050)
#define CLOCKS_CLK_PERI_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_PERI_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_PERI_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_PERI_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_PERI_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_USB_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_USB_CTRL_OFFSET _u(0x00000054)
#define CLOCKS_CLK_USB_CTRL_BITS   _u(0x00130ce0)
#define CLOCKS_CLK_USB_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_USB_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_USB_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_USB_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_USB_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_USB_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_USB_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_USB_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_USB_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_USB_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_USB_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_USB_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_USB_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_USB_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_USB_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_USB_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_USB_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_USB_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_USB_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_USB_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_USB_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_USB_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_BITS                 _u(0x000000e0)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_MSB                  _u(7)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x0)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x1)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x2)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x3)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x4)
#define CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x5)
// =============================================================================
// Register    : CLOCKS_CLK_USB_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_USB_DIV_OFFSET _u(0x00000058)
#define CLOCKS_CLK_USB_DIV_BITS   _u(0x00000300)
#define CLOCKS_CLK_USB_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_USB_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_USB_DIV_INT_RESET  _u(0x1)
#define CLOCKS_CLK_USB_DIV_INT_BITS   _u(0x00000300)
#define CLOCKS_CLK_USB_DIV_INT_MSB    _u(9)
#define CLOCKS_CLK_USB_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_USB_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_USB_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_USB_SELECTED_OFFSET _u(0x0000005c)
#define CLOCKS_CLK_USB_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_USB_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_USB_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_USB_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_USB_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_ADC_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_ADC_CTRL_OFFSET _u(0x00000060)
#define CLOCKS_CLK_ADC_CTRL_BITS   _u(0x00130ce0)
#define CLOCKS_CLK_ADC_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_ADC_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_ADC_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_ADC_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_ADC_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_ADC_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_ADC_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_ADC_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_ADC_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_ADC_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_ADC_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_ADC_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_ADC_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_ADC_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_ADC_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_ADC_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_ADC_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_BITS                 _u(0x000000e0)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_MSB                  _u(7)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x0)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x1)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x2)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x3)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x4)
#define CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x5)
// =============================================================================
// Register    : CLOCKS_CLK_ADC_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_ADC_DIV_OFFSET _u(0x00000064)
#define CLOCKS_CLK_ADC_DIV_BITS   _u(0x00000300)
#define CLOCKS_CLK_ADC_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_ADC_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_ADC_DIV_INT_RESET  _u(0x1)
#define CLOCKS_CLK_ADC_DIV_INT_BITS   _u(0x00000300)
#define CLOCKS_CLK_ADC_DIV_INT_MSB    _u(9)
#define CLOCKS_CLK_ADC_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_ADC_DIV_INT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_ADC_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_ADC_SELECTED_OFFSET _u(0x00000068)
#define CLOCKS_CLK_ADC_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_ADC_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_ADC_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_ADC_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_ADC_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_RTC_CTRL
// Description : Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_RTC_CTRL_OFFSET _u(0x0000006c)
#define CLOCKS_CLK_RTC_CTRL_BITS   _u(0x00130ce0)
#define CLOCKS_CLK_RTC_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_NUDGE
// Description : An edge on this signal shifts the phase of the output by 1
//               cycle of the input clock
//               This can be done at any time
#define CLOCKS_CLK_RTC_CTRL_NUDGE_RESET  _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_NUDGE_BITS   _u(0x00100000)
#define CLOCKS_CLK_RTC_CTRL_NUDGE_MSB    _u(20)
#define CLOCKS_CLK_RTC_CTRL_NUDGE_LSB    _u(20)
#define CLOCKS_CLK_RTC_CTRL_NUDGE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_PHASE
// Description : This delays the enable signal by up to 3 cycles of the input
//               clock
//               This must be set before the clock is enabled to have any effect
#define CLOCKS_CLK_RTC_CTRL_PHASE_RESET  _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_PHASE_BITS   _u(0x00030000)
#define CLOCKS_CLK_RTC_CTRL_PHASE_MSB    _u(17)
#define CLOCKS_CLK_RTC_CTRL_PHASE_LSB    _u(16)
#define CLOCKS_CLK_RTC_CTRL_PHASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_ENABLE
// Description : Starts and stops the clock generator cleanly
#define CLOCKS_CLK_RTC_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_ENABLE_BITS   _u(0x00000800)
#define CLOCKS_CLK_RTC_CTRL_ENABLE_MSB    _u(11)
#define CLOCKS_CLK_RTC_CTRL_ENABLE_LSB    _u(11)
#define CLOCKS_CLK_RTC_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_KILL
// Description : Asynchronously kills the clock generator
#define CLOCKS_CLK_RTC_CTRL_KILL_RESET  _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_KILL_BITS   _u(0x00000400)
#define CLOCKS_CLK_RTC_CTRL_KILL_MSB    _u(10)
#define CLOCKS_CLK_RTC_CTRL_KILL_LSB    _u(10)
#define CLOCKS_CLK_RTC_CTRL_KILL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_CTRL_AUXSRC
// Description : Selects the auxiliary clock source, will glitch when switching
//               0x0 -> clksrc_pll_usb
//               0x1 -> clksrc_pll_sys
//               0x2 -> rosc_clksrc_ph
//               0x3 -> xosc_clksrc
//               0x4 -> clksrc_gpin0
//               0x5 -> clksrc_gpin1
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_RESET                _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_BITS                 _u(0x000000e0)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_MSB                  _u(7)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_LSB                  _u(5)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_ACCESS               "RW"
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB _u(0x0)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS _u(0x1)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH _u(0x2)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    _u(0x3)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   _u(0x4)
#define CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   _u(0x5)
// =============================================================================
// Register    : CLOCKS_CLK_RTC_DIV
// Description : Clock divisor, can be changed on-the-fly
#define CLOCKS_CLK_RTC_DIV_OFFSET _u(0x00000070)
#define CLOCKS_CLK_RTC_DIV_BITS   _u(0xffffffff)
#define CLOCKS_CLK_RTC_DIV_RESET  _u(0x00000100)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_DIV_INT
// Description : Integer component of the divisor, 0 -> divide by 2^16
#define CLOCKS_CLK_RTC_DIV_INT_RESET  _u(0x000001)
#define CLOCKS_CLK_RTC_DIV_INT_BITS   _u(0xffffff00)
#define CLOCKS_CLK_RTC_DIV_INT_MSB    _u(31)
#define CLOCKS_CLK_RTC_DIV_INT_LSB    _u(8)
#define CLOCKS_CLK_RTC_DIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_RTC_DIV_FRAC
// Description : Fractional component of the divisor
#define CLOCKS_CLK_RTC_DIV_FRAC_RESET  _u(0x00)
#define CLOCKS_CLK_RTC_DIV_FRAC_BITS   _u(0x000000ff)
#define CLOCKS_CLK_RTC_DIV_FRAC_MSB    _u(7)
#define CLOCKS_CLK_RTC_DIV_FRAC_LSB    _u(0)
#define CLOCKS_CLK_RTC_DIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_RTC_SELECTED
// Description : Indicates which SRC is currently selected by the glitchless mux
//               (one-hot).
//               This slice does not have a glitchless mux (only the AUX_SRC
//               field is present, not SRC) so this register is hardwired to
//               0x1.
#define CLOCKS_CLK_RTC_SELECTED_OFFSET _u(0x00000074)
#define CLOCKS_CLK_RTC_SELECTED_BITS   _u(0xffffffff)
#define CLOCKS_CLK_RTC_SELECTED_RESET  _u(0x00000001)
#define CLOCKS_CLK_RTC_SELECTED_MSB    _u(31)
#define CLOCKS_CLK_RTC_SELECTED_LSB    _u(0)
#define CLOCKS_CLK_RTC_SELECTED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_RESUS_CTRL
// Description : None
#define CLOCKS_CLK_SYS_RESUS_CTRL_OFFSET _u(0x00000078)
#define CLOCKS_CLK_SYS_RESUS_CTRL_BITS   _u(0x000111ff)
#define CLOCKS_CLK_SYS_RESUS_CTRL_RESET  _u(0x000000ff)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR
// Description : For clearing the resus after the fault that triggered it has
//               been corrected
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_RESET  _u(0x0)
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_BITS   _u(0x00010000)
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_MSB    _u(16)
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_LSB    _u(16)
#define CLOCKS_CLK_SYS_RESUS_CTRL_CLEAR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_FRCE
// Description : Force a resus, for test purposes only
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_RESET  _u(0x0)
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_BITS   _u(0x00001000)
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_MSB    _u(12)
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_LSB    _u(12)
#define CLOCKS_CLK_SYS_RESUS_CTRL_FRCE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE
// Description : Enable resus
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_RESET  _u(0x0)
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_BITS   _u(0x00000100)
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_MSB    _u(8)
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_LSB    _u(8)
#define CLOCKS_CLK_SYS_RESUS_CTRL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT
// Description : This is expressed as a number of clk_ref cycles
//               and must be >= 2x clk_ref_freq/min_clk_tst_freq
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_RESET  _u(0xff)
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_BITS   _u(0x000000ff)
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_MSB    _u(7)
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_LSB    _u(0)
#define CLOCKS_CLK_SYS_RESUS_CTRL_TIMEOUT_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_CLK_SYS_RESUS_STATUS
// Description : None
#define CLOCKS_CLK_SYS_RESUS_STATUS_OFFSET _u(0x0000007c)
#define CLOCKS_CLK_SYS_RESUS_STATUS_BITS   _u(0x00000001)
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED
// Description : Clock has been resuscitated, correct the error then send
//               ctrl_clear=1
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_RESET  _u(0x0)
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_BITS   _u(0x00000001)
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_MSB    _u(0)
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_LSB    _u(0)
#define CLOCKS_CLK_SYS_RESUS_STATUS_RESUSSED_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_FC0_REF_KHZ
// Description : Reference clock frequency in kHz
#define CLOCKS_FC0_REF_KHZ_OFFSET _u(0x00000080)
#define CLOCKS_FC0_REF_KHZ_BITS   _u(0x000fffff)
#define CLOCKS_FC0_REF_KHZ_RESET  _u(0x00000000)
#define CLOCKS_FC0_REF_KHZ_MSB    _u(19)
#define CLOCKS_FC0_REF_KHZ_LSB    _u(0)
#define CLOCKS_FC0_REF_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_MIN_KHZ
// Description : Minimum pass frequency in kHz. This is optional. Set to 0 if
//               you are not using the pass/fail flags
#define CLOCKS_FC0_MIN_KHZ_OFFSET _u(0x00000084)
#define CLOCKS_FC0_MIN_KHZ_BITS   _u(0x01ffffff)
#define CLOCKS_FC0_MIN_KHZ_RESET  _u(0x00000000)
#define CLOCKS_FC0_MIN_KHZ_MSB    _u(24)
#define CLOCKS_FC0_MIN_KHZ_LSB    _u(0)
#define CLOCKS_FC0_MIN_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_MAX_KHZ
// Description : Maximum pass frequency in kHz. This is optional. Set to
//               0x1ffffff if you are not using the pass/fail flags
#define CLOCKS_FC0_MAX_KHZ_OFFSET _u(0x00000088)
#define CLOCKS_FC0_MAX_KHZ_BITS   _u(0x01ffffff)
#define CLOCKS_FC0_MAX_KHZ_RESET  _u(0x01ffffff)
#define CLOCKS_FC0_MAX_KHZ_MSB    _u(24)
#define CLOCKS_FC0_MAX_KHZ_LSB    _u(0)
#define CLOCKS_FC0_MAX_KHZ_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_DELAY
// Description : Delays the start of frequency counting to allow the mux to
//               settle
//               Delay is measured in multiples of the reference clock period
#define CLOCKS_FC0_DELAY_OFFSET _u(0x0000008c)
#define CLOCKS_FC0_DELAY_BITS   _u(0x00000007)
#define CLOCKS_FC0_DELAY_RESET  _u(0x00000001)
#define CLOCKS_FC0_DELAY_MSB    _u(2)
#define CLOCKS_FC0_DELAY_LSB    _u(0)
#define CLOCKS_FC0_DELAY_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_INTERVAL
// Description : The test interval is 0.98us * 2**interval, but let's call it
//               1us * 2**interval
//               The default gives a test interval of 250us
#define CLOCKS_FC0_INTERVAL_OFFSET _u(0x00000090)
#define CLOCKS_FC0_INTERVAL_BITS   _u(0x0000000f)
#define CLOCKS_FC0_INTERVAL_RESET  _u(0x00000008)
#define CLOCKS_FC0_INTERVAL_MSB    _u(3)
#define CLOCKS_FC0_INTERVAL_LSB    _u(0)
#define CLOCKS_FC0_INTERVAL_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_FC0_SRC
// Description : Clock sent to frequency counter, set to 0 when not required
//               Writing to this register initiates the frequency count
//               0x00 -> NULL
//               0x01 -> pll_sys_clksrc_primary
//               0x02 -> pll_usb_clksrc_primary
//               0x03 -> rosc_clksrc
//               0x04 -> rosc_clksrc_ph
//               0x05 -> xosc_clksrc
//               0x06 -> clksrc_gpin0
//               0x07 -> clksrc_gpin1
//               0x08 -> clk_ref
//               0x09 -> clk_sys
//               0x0a -> clk_peri
//               0x0b -> clk_usb
//               0x0c -> clk_adc
//               0x0d -> clk_rtc
#define CLOCKS_FC0_SRC_OFFSET                       _u(0x00000094)
#define CLOCKS_FC0_SRC_BITS                         _u(0x000000ff)
#define CLOCKS_FC0_SRC_RESET                        _u(0x00000000)
#define CLOCKS_FC0_SRC_MSB                          _u(7)
#define CLOCKS_FC0_SRC_LSB                          _u(0)
#define CLOCKS_FC0_SRC_ACCESS                       "RW"
#define CLOCKS_FC0_SRC_VALUE_NULL                   _u(0x00)
#define CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY _u(0x01)
#define CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY _u(0x02)
#define CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC            _u(0x03)
#define CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC_PH         _u(0x04)
#define CLOCKS_FC0_SRC_VALUE_XOSC_CLKSRC            _u(0x05)
#define CLOCKS_FC0_SRC_VALUE_CLKSRC_GPIN0           _u(0x06)
#define CLOCKS_FC0_SRC_VALUE_CLKSRC_GPIN1           _u(0x07)
#define CLOCKS_FC0_SRC_VALUE_CLK_REF                _u(0x08)
#define CLOCKS_FC0_SRC_VALUE_CLK_SYS                _u(0x09)
#define CLOCKS_FC0_SRC_VALUE_CLK_PERI               _u(0x0a)
#define CLOCKS_FC0_SRC_VALUE_CLK_USB                _u(0x0b)
#define CLOCKS_FC0_SRC_VALUE_CLK_ADC                _u(0x0c)
#define CLOCKS_FC0_SRC_VALUE_CLK_RTC                _u(0x0d)
// =============================================================================
// Register    : CLOCKS_FC0_STATUS
// Description : Frequency counter status
#define CLOCKS_FC0_STATUS_OFFSET _u(0x00000098)
#define CLOCKS_FC0_STATUS_BITS   _u(0x11111111)
#define CLOCKS_FC0_STATUS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_DIED
// Description : Test clock stopped during test
#define CLOCKS_FC0_STATUS_DIED_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_DIED_BITS   _u(0x10000000)
#define CLOCKS_FC0_STATUS_DIED_MSB    _u(28)
#define CLOCKS_FC0_STATUS_DIED_LSB    _u(28)
#define CLOCKS_FC0_STATUS_DIED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_FAST
// Description : Test clock faster than expected, only valid when status_done=1
#define CLOCKS_FC0_STATUS_FAST_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_FAST_BITS   _u(0x01000000)
#define CLOCKS_FC0_STATUS_FAST_MSB    _u(24)
#define CLOCKS_FC0_STATUS_FAST_LSB    _u(24)
#define CLOCKS_FC0_STATUS_FAST_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_SLOW
// Description : Test clock slower than expected, only valid when status_done=1
#define CLOCKS_FC0_STATUS_SLOW_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_SLOW_BITS   _u(0x00100000)
#define CLOCKS_FC0_STATUS_SLOW_MSB    _u(20)
#define CLOCKS_FC0_STATUS_SLOW_LSB    _u(20)
#define CLOCKS_FC0_STATUS_SLOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_FAIL
// Description : Test failed
#define CLOCKS_FC0_STATUS_FAIL_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_FAIL_BITS   _u(0x00010000)
#define CLOCKS_FC0_STATUS_FAIL_MSB    _u(16)
#define CLOCKS_FC0_STATUS_FAIL_LSB    _u(16)
#define CLOCKS_FC0_STATUS_FAIL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_WAITING
// Description : Waiting for test clock to start
#define CLOCKS_FC0_STATUS_WAITING_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_WAITING_BITS   _u(0x00001000)
#define CLOCKS_FC0_STATUS_WAITING_MSB    _u(12)
#define CLOCKS_FC0_STATUS_WAITING_LSB    _u(12)
#define CLOCKS_FC0_STATUS_WAITING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_RUNNING
// Description : Test running
#define CLOCKS_FC0_STATUS_RUNNING_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_RUNNING_BITS   _u(0x00000100)
#define CLOCKS_FC0_STATUS_RUNNING_MSB    _u(8)
#define CLOCKS_FC0_STATUS_RUNNING_LSB    _u(8)
#define CLOCKS_FC0_STATUS_RUNNING_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_DONE
// Description : Test complete
#define CLOCKS_FC0_STATUS_DONE_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_DONE_BITS   _u(0x00000010)
#define CLOCKS_FC0_STATUS_DONE_MSB    _u(4)
#define CLOCKS_FC0_STATUS_DONE_LSB    _u(4)
#define CLOCKS_FC0_STATUS_DONE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_STATUS_PASS
// Description : Test passed
#define CLOCKS_FC0_STATUS_PASS_RESET  _u(0x0)
#define CLOCKS_FC0_STATUS_PASS_BITS   _u(0x00000001)
#define CLOCKS_FC0_STATUS_PASS_MSB    _u(0)
#define CLOCKS_FC0_STATUS_PASS_LSB    _u(0)
#define CLOCKS_FC0_STATUS_PASS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_FC0_RESULT
// Description : Result of frequency measurement, only valid when status_done=1
#define CLOCKS_FC0_RESULT_OFFSET _u(0x0000009c)
#define CLOCKS_FC0_RESULT_BITS   _u(0x3fffffff)
#define CLOCKS_FC0_RESULT_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_RESULT_KHZ
// Description : None
#define CLOCKS_FC0_RESULT_KHZ_RESET  _u(0x0000000)
#define CLOCKS_FC0_RESULT_KHZ_BITS   _u(0x3fffffe0)
#define CLOCKS_FC0_RESULT_KHZ_MSB    _u(29)
#define CLOCKS_FC0_RESULT_KHZ_LSB    _u(5)
#define CLOCKS_FC0_RESULT_KHZ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_FC0_RESULT_FRAC
// Description : None
#define CLOCKS_FC0_RESULT_FRAC_RESET  _u(0x00)
#define CLOCKS_FC0_RESULT_FRAC_BITS   _u(0x0000001f)
#define CLOCKS_FC0_RESULT_FRAC_MSB    _u(4)
#define CLOCKS_FC0_RESULT_FRAC_LSB    _u(0)
#define CLOCKS_FC0_RESULT_FRAC_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_WAKE_EN0
// Description : enable clock in wake mode
#define CLOCKS_WAKE_EN0_OFFSET _u(0x000000a0)
#define CLOCKS_WAKE_EN0_BITS   _u(0xffffffff)
#define CLOCKS_WAKE_EN0_RESET  _u(0xffffffff)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_BITS   _u(0x80000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_MSB    _u(31)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_LSB    _u(31)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_BITS   _u(0x40000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_MSB    _u(30)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_LSB    _u(30)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_BITS   _u(0x20000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_MSB    _u(29)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_LSB    _u(29)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_BITS   _u(0x10000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_MSB    _u(28)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_LSB    _u(28)
#define CLOCKS_WAKE_EN0_CLK_SYS_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_BITS   _u(0x08000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_MSB    _u(27)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_LSB    _u(27)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_BITS   _u(0x04000000)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_MSB    _u(26)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_LSB    _u(26)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_BITS   _u(0x02000000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_MSB    _u(25)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_LSB    _u(25)
#define CLOCKS_WAKE_EN0_CLK_SYS_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_BITS   _u(0x01000000)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_MSB    _u(24)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_LSB    _u(24)
#define CLOCKS_WAKE_EN0_CLK_PERI_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_SIO
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_BITS   _u(0x00800000)
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_MSB    _u(23)
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_LSB    _u(23)
#define CLOCKS_WAKE_EN0_CLK_SYS_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_RTC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_BITS   _u(0x00400000)
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_MSB    _u(22)
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_LSB    _u(22)
#define CLOCKS_WAKE_EN0_CLK_SYS_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_RTC_RTC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_BITS   _u(0x00200000)
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_MSB    _u(21)
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_LSB    _u(21)
#define CLOCKS_WAKE_EN0_CLK_RTC_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_BITS   _u(0x00100000)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_MSB    _u(20)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_LSB    _u(20)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ROM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_BITS   _u(0x00080000)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_MSB    _u(19)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_LSB    _u(19)
#define CLOCKS_WAKE_EN0_CLK_SYS_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_BITS   _u(0x00040000)
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_MSB    _u(18)
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_LSB    _u(18)
#define CLOCKS_WAKE_EN0_CLK_SYS_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PWM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_BITS   _u(0x00020000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_MSB    _u(17)
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_LSB    _u(17)
#define CLOCKS_WAKE_EN0_CLK_SYS_PWM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PSM
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_BITS   _u(0x00010000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_MSB    _u(16)
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_LSB    _u(16)
#define CLOCKS_WAKE_EN0_CLK_SYS_PSM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_BITS   _u(0x00008000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_MSB    _u(15)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_LSB    _u(15)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_USB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_BITS   _u(0x00004000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_MSB    _u(14)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_LSB    _u(14)
#define CLOCKS_WAKE_EN0_CLK_SYS_PLL_SYS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_BITS   _u(0x00002000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_MSB    _u(13)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_LSB    _u(13)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_BITS   _u(0x00001000)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_MSB    _u(12)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_LSB    _u(12)
#define CLOCKS_WAKE_EN0_CLK_SYS_PIO0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_PADS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_BITS   _u(0x00000800)
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_MSB    _u(11)
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_LSB    _u(11)
#define CLOCKS_WAKE_EN0_CLK_SYS_PADS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   _u(0x00000400)
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    _u(10)
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    _u(10)
#define CLOCKS_WAKE_EN0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_BITS   _u(0x00000200)
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_MSB    _u(9)
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_LSB    _u(9)
#define CLOCKS_WAKE_EN0_CLK_SYS_JTAG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_IO
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_BITS   _u(0x00000100)
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_MSB    _u(8)
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_LSB    _u(8)
#define CLOCKS_WAKE_EN0_CLK_SYS_IO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_BITS   _u(0x00000080)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_MSB    _u(7)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_LSB    _u(7)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_BITS   _u(0x00000040)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_MSB    _u(6)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_LSB    _u(6)
#define CLOCKS_WAKE_EN0_CLK_SYS_I2C0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_DMA
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_BITS   _u(0x00000020)
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_MSB    _u(5)
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_LSB    _u(5)
#define CLOCKS_WAKE_EN0_CLK_SYS_DMA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_BITS   _u(0x00000010)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_MSB    _u(4)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_LSB    _u(4)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_BITS   _u(0x00000008)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_MSB    _u(3)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_LSB    _u(3)
#define CLOCKS_WAKE_EN0_CLK_SYS_BUSCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_ADC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_BITS   _u(0x00000004)
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_MSB    _u(2)
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_LSB    _u(2)
#define CLOCKS_WAKE_EN0_CLK_SYS_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_ADC_ADC
// Description : None
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_BITS   _u(0x00000002)
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_MSB    _u(1)
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_LSB    _u(1)
#define CLOCKS_WAKE_EN0_CLK_ADC_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_RESET  _u(0x1)
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_BITS   _u(0x00000001)
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_MSB    _u(0)
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_LSB    _u(0)
#define CLOCKS_WAKE_EN0_CLK_SYS_CLOCKS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_WAKE_EN1
// Description : enable clock in wake mode
#define CLOCKS_WAKE_EN1_OFFSET _u(0x000000a4)
#define CLOCKS_WAKE_EN1_BITS   _u(0x00007fff)
#define CLOCKS_WAKE_EN1_RESET  _u(0x00007fff)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_BITS   _u(0x00004000)
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_MSB    _u(14)
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_LSB    _u(14)
#define CLOCKS_WAKE_EN1_CLK_SYS_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_XIP
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_BITS   _u(0x00002000)
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_MSB    _u(13)
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_LSB    _u(13)
#define CLOCKS_WAKE_EN1_CLK_SYS_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_BITS   _u(0x00001000)
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_MSB    _u(12)
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_LSB    _u(12)
#define CLOCKS_WAKE_EN1_CLK_SYS_WATCHDOG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_BITS   _u(0x00000800)
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_MSB    _u(11)
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_LSB    _u(11)
#define CLOCKS_WAKE_EN1_CLK_USB_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_BITS   _u(0x00000400)
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_MSB    _u(10)
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_LSB    _u(10)
#define CLOCKS_WAKE_EN1_CLK_SYS_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_UART1
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_BITS   _u(0x00000200)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_MSB    _u(9)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_LSB    _u(9)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_PERI_UART1
// Description : None
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_BITS   _u(0x00000100)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_MSB    _u(8)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_LSB    _u(8)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_UART0
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_BITS   _u(0x00000080)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_MSB    _u(7)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_LSB    _u(7)
#define CLOCKS_WAKE_EN1_CLK_SYS_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_PERI_UART0
// Description : None
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_BITS   _u(0x00000040)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_MSB    _u(6)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_LSB    _u(6)
#define CLOCKS_WAKE_EN1_CLK_PERI_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_BITS   _u(0x00000020)
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_MSB    _u(5)
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_LSB    _u(5)
#define CLOCKS_WAKE_EN1_CLK_SYS_TIMER_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_BITS   _u(0x00000010)
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_MSB    _u(4)
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_LSB    _u(4)
#define CLOCKS_WAKE_EN1_CLK_SYS_TBMAN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_BITS   _u(0x00000008)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_MSB    _u(3)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_LSB    _u(3)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSINFO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_BITS   _u(0x00000004)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_MSB    _u(2)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_LSB    _u(2)
#define CLOCKS_WAKE_EN1_CLK_SYS_SYSCFG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_BITS   _u(0x00000002)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_MSB    _u(1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_LSB    _u(1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_WAKE_EN1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_RESET  _u(0x1)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_BITS   _u(0x00000001)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_MSB    _u(0)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_LSB    _u(0)
#define CLOCKS_WAKE_EN1_CLK_SYS_SRAM4_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_SLEEP_EN0
// Description : enable clock in sleep mode
#define CLOCKS_SLEEP_EN0_OFFSET _u(0x000000a8)
#define CLOCKS_SLEEP_EN0_BITS   _u(0xffffffff)
#define CLOCKS_SLEEP_EN0_RESET  _u(0xffffffff)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_BITS   _u(0x80000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_MSB    _u(31)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_LSB    _u(31)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_BITS   _u(0x40000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_MSB    _u(30)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_LSB    _u(30)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_BITS   _u(0x20000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_MSB    _u(29)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_LSB    _u(29)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_BITS   _u(0x10000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_MSB    _u(28)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_LSB    _u(28)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SRAM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_BITS   _u(0x08000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_MSB    _u(27)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_LSB    _u(27)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_BITS   _u(0x04000000)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_MSB    _u(26)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_LSB    _u(26)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_BITS   _u(0x02000000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_MSB    _u(25)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_LSB    _u(25)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_BITS   _u(0x01000000)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_MSB    _u(24)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_LSB    _u(24)
#define CLOCKS_SLEEP_EN0_CLK_PERI_SPI0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_SIO
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_BITS   _u(0x00800000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_MSB    _u(23)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_LSB    _u(23)
#define CLOCKS_SLEEP_EN0_CLK_SYS_SIO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_RTC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_BITS   _u(0x00400000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_MSB    _u(22)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_LSB    _u(22)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_RTC_RTC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_BITS   _u(0x00200000)
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_MSB    _u(21)
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_LSB    _u(21)
#define CLOCKS_SLEEP_EN0_CLK_RTC_RTC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_BITS   _u(0x00100000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_MSB    _u(20)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_LSB    _u(20)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ROM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_BITS   _u(0x00080000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_MSB    _u(19)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_LSB    _u(19)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ROM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_BITS   _u(0x00040000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_MSB    _u(18)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_LSB    _u(18)
#define CLOCKS_SLEEP_EN0_CLK_SYS_RESETS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PWM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_BITS   _u(0x00020000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_MSB    _u(17)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_LSB    _u(17)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PWM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PSM
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_BITS   _u(0x00010000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_MSB    _u(16)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_LSB    _u(16)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PSM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_BITS   _u(0x00008000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_MSB    _u(15)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_LSB    _u(15)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_USB_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_BITS   _u(0x00004000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_MSB    _u(14)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_LSB    _u(14)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PLL_SYS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_BITS   _u(0x00002000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_MSB    _u(13)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_LSB    _u(13)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_BITS   _u(0x00001000)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_MSB    _u(12)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_LSB    _u(12)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PIO0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_PADS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_BITS   _u(0x00000800)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_MSB    _u(11)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_LSB    _u(11)
#define CLOCKS_SLEEP_EN0_CLK_SYS_PADS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   _u(0x00000400)
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    _u(10)
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    _u(10)
#define CLOCKS_SLEEP_EN0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_BITS   _u(0x00000200)
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_MSB    _u(9)
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_LSB    _u(9)
#define CLOCKS_SLEEP_EN0_CLK_SYS_JTAG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_IO
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_BITS   _u(0x00000100)
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_MSB    _u(8)
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_LSB    _u(8)
#define CLOCKS_SLEEP_EN0_CLK_SYS_IO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_BITS   _u(0x00000080)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_MSB    _u(7)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_LSB    _u(7)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_BITS   _u(0x00000040)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_MSB    _u(6)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_LSB    _u(6)
#define CLOCKS_SLEEP_EN0_CLK_SYS_I2C0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_DMA
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_BITS   _u(0x00000020)
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_MSB    _u(5)
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_LSB    _u(5)
#define CLOCKS_SLEEP_EN0_CLK_SYS_DMA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_BITS   _u(0x00000010)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_MSB    _u(4)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_LSB    _u(4)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSFABRIC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_BITS   _u(0x00000008)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_MSB    _u(3)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_LSB    _u(3)
#define CLOCKS_SLEEP_EN0_CLK_SYS_BUSCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_ADC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_BITS   _u(0x00000004)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_MSB    _u(2)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_LSB    _u(2)
#define CLOCKS_SLEEP_EN0_CLK_SYS_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_ADC_ADC
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_BITS   _u(0x00000002)
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_MSB    _u(1)
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_LSB    _u(1)
#define CLOCKS_SLEEP_EN0_CLK_ADC_ADC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_BITS   _u(0x00000001)
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_MSB    _u(0)
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_LSB    _u(0)
#define CLOCKS_SLEEP_EN0_CLK_SYS_CLOCKS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_SLEEP_EN1
// Description : enable clock in sleep mode
#define CLOCKS_SLEEP_EN1_OFFSET _u(0x000000ac)
#define CLOCKS_SLEEP_EN1_BITS   _u(0x00007fff)
#define CLOCKS_SLEEP_EN1_RESET  _u(0x00007fff)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_BITS   _u(0x00004000)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_MSB    _u(14)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_LSB    _u(14)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XOSC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_XIP
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_BITS   _u(0x00002000)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_MSB    _u(13)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_LSB    _u(13)
#define CLOCKS_SLEEP_EN1_CLK_SYS_XIP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_BITS   _u(0x00001000)
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_MSB    _u(12)
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_LSB    _u(12)
#define CLOCKS_SLEEP_EN1_CLK_SYS_WATCHDOG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_BITS   _u(0x00000800)
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_MSB    _u(11)
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_LSB    _u(11)
#define CLOCKS_SLEEP_EN1_CLK_USB_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_BITS   _u(0x00000400)
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_MSB    _u(10)
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_LSB    _u(10)
#define CLOCKS_SLEEP_EN1_CLK_SYS_USBCTRL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_UART1
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_BITS   _u(0x00000200)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_MSB    _u(9)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_LSB    _u(9)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_PERI_UART1
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_BITS   _u(0x00000100)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_MSB    _u(8)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_LSB    _u(8)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_UART0
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_BITS   _u(0x00000080)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_MSB    _u(7)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_LSB    _u(7)
#define CLOCKS_SLEEP_EN1_CLK_SYS_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_PERI_UART0
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_BITS   _u(0x00000040)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_MSB    _u(6)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_LSB    _u(6)
#define CLOCKS_SLEEP_EN1_CLK_PERI_UART0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_BITS   _u(0x00000020)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_MSB    _u(5)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_LSB    _u(5)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TIMER_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_BITS   _u(0x00000010)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_MSB    _u(4)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_LSB    _u(4)
#define CLOCKS_SLEEP_EN1_CLK_SYS_TBMAN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_BITS   _u(0x00000008)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_MSB    _u(3)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_LSB    _u(3)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSINFO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_BITS   _u(0x00000004)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_MSB    _u(2)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_LSB    _u(2)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SYSCFG_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_BITS   _u(0x00000002)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_MSB    _u(1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_LSB    _u(1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM5_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_RESET  _u(0x1)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_BITS   _u(0x00000001)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_MSB    _u(0)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_LSB    _u(0)
#define CLOCKS_SLEEP_EN1_CLK_SYS_SRAM4_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_ENABLED0
// Description : indicates the state of the clock enable
#define CLOCKS_ENABLED0_OFFSET _u(0x000000b0)
#define CLOCKS_ENABLED0_BITS   _u(0xffffffff)
#define CLOCKS_ENABLED0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM3
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_BITS   _u(0x80000000)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_MSB    _u(31)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_LSB    _u(31)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM2
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_BITS   _u(0x40000000)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_MSB    _u(30)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_LSB    _u(30)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_BITS   _u(0x20000000)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_MSB    _u(29)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_LSB    _u(29)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SRAM0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_BITS   _u(0x10000000)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_MSB    _u(28)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_LSB    _u(28)
#define CLOCKS_ENABLED0_CLK_SYS_SRAM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SPI1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_BITS   _u(0x08000000)
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_MSB    _u(27)
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_LSB    _u(27)
#define CLOCKS_ENABLED0_CLK_SYS_SPI1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_PERI_SPI1
// Description : None
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_BITS   _u(0x04000000)
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_MSB    _u(26)
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_LSB    _u(26)
#define CLOCKS_ENABLED0_CLK_PERI_SPI1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SPI0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_BITS   _u(0x02000000)
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_MSB    _u(25)
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_LSB    _u(25)
#define CLOCKS_ENABLED0_CLK_SYS_SPI0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_PERI_SPI0
// Description : None
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_BITS   _u(0x01000000)
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_MSB    _u(24)
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_LSB    _u(24)
#define CLOCKS_ENABLED0_CLK_PERI_SPI0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_SIO
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_SIO_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_SIO_BITS   _u(0x00800000)
#define CLOCKS_ENABLED0_CLK_SYS_SIO_MSB    _u(23)
#define CLOCKS_ENABLED0_CLK_SYS_SIO_LSB    _u(23)
#define CLOCKS_ENABLED0_CLK_SYS_SIO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_RTC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_RTC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_RTC_BITS   _u(0x00400000)
#define CLOCKS_ENABLED0_CLK_SYS_RTC_MSB    _u(22)
#define CLOCKS_ENABLED0_CLK_SYS_RTC_LSB    _u(22)
#define CLOCKS_ENABLED0_CLK_SYS_RTC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_RTC_RTC
// Description : None
#define CLOCKS_ENABLED0_CLK_RTC_RTC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_RTC_RTC_BITS   _u(0x00200000)
#define CLOCKS_ENABLED0_CLK_RTC_RTC_MSB    _u(21)
#define CLOCKS_ENABLED0_CLK_RTC_RTC_LSB    _u(21)
#define CLOCKS_ENABLED0_CLK_RTC_RTC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ROSC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_BITS   _u(0x00100000)
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_MSB    _u(20)
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_LSB    _u(20)
#define CLOCKS_ENABLED0_CLK_SYS_ROSC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ROM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ROM_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_ROM_BITS   _u(0x00080000)
#define CLOCKS_ENABLED0_CLK_SYS_ROM_MSB    _u(19)
#define CLOCKS_ENABLED0_CLK_SYS_ROM_LSB    _u(19)
#define CLOCKS_ENABLED0_CLK_SYS_ROM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_RESETS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_BITS   _u(0x00040000)
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_MSB    _u(18)
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_LSB    _u(18)
#define CLOCKS_ENABLED0_CLK_SYS_RESETS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PWM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PWM_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PWM_BITS   _u(0x00020000)
#define CLOCKS_ENABLED0_CLK_SYS_PWM_MSB    _u(17)
#define CLOCKS_ENABLED0_CLK_SYS_PWM_LSB    _u(17)
#define CLOCKS_ENABLED0_CLK_SYS_PWM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PSM
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PSM_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PSM_BITS   _u(0x00010000)
#define CLOCKS_ENABLED0_CLK_SYS_PSM_MSB    _u(16)
#define CLOCKS_ENABLED0_CLK_SYS_PSM_LSB    _u(16)
#define CLOCKS_ENABLED0_CLK_SYS_PSM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PLL_USB
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_BITS   _u(0x00008000)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_MSB    _u(15)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_LSB    _u(15)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_USB_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PLL_SYS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_BITS   _u(0x00004000)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_MSB    _u(14)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_LSB    _u(14)
#define CLOCKS_ENABLED0_CLK_SYS_PLL_SYS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PIO1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_BITS   _u(0x00002000)
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_MSB    _u(13)
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_LSB    _u(13)
#define CLOCKS_ENABLED0_CLK_SYS_PIO1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PIO0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_BITS   _u(0x00001000)
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_MSB    _u(12)
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_LSB    _u(12)
#define CLOCKS_ENABLED0_CLK_SYS_PIO0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_PADS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_PADS_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_PADS_BITS   _u(0x00000800)
#define CLOCKS_ENABLED0_CLK_SYS_PADS_MSB    _u(11)
#define CLOCKS_ENABLED0_CLK_SYS_PADS_LSB    _u(11)
#define CLOCKS_ENABLED0_CLK_SYS_PADS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_BITS   _u(0x00000400)
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_MSB    _u(10)
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_LSB    _u(10)
#define CLOCKS_ENABLED0_CLK_SYS_VREG_AND_CHIP_RESET_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_JTAG
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_BITS   _u(0x00000200)
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_MSB    _u(9)
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_LSB    _u(9)
#define CLOCKS_ENABLED0_CLK_SYS_JTAG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_IO
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_IO_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_IO_BITS   _u(0x00000100)
#define CLOCKS_ENABLED0_CLK_SYS_IO_MSB    _u(8)
#define CLOCKS_ENABLED0_CLK_SYS_IO_LSB    _u(8)
#define CLOCKS_ENABLED0_CLK_SYS_IO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_I2C1
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_BITS   _u(0x00000080)
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_MSB    _u(7)
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_LSB    _u(7)
#define CLOCKS_ENABLED0_CLK_SYS_I2C1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_I2C0
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_BITS   _u(0x00000040)
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_MSB    _u(6)
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_LSB    _u(6)
#define CLOCKS_ENABLED0_CLK_SYS_I2C0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_DMA
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_DMA_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_DMA_BITS   _u(0x00000020)
#define CLOCKS_ENABLED0_CLK_SYS_DMA_MSB    _u(5)
#define CLOCKS_ENABLED0_CLK_SYS_DMA_LSB    _u(5)
#define CLOCKS_ENABLED0_CLK_SYS_DMA_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_BITS   _u(0x00000010)
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_MSB    _u(4)
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_LSB    _u(4)
#define CLOCKS_ENABLED0_CLK_SYS_BUSFABRIC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_BUSCTRL
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_BITS   _u(0x00000008)
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_MSB    _u(3)
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_LSB    _u(3)
#define CLOCKS_ENABLED0_CLK_SYS_BUSCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_ADC
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_ADC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_ADC_BITS   _u(0x00000004)
#define CLOCKS_ENABLED0_CLK_SYS_ADC_MSB    _u(2)
#define CLOCKS_ENABLED0_CLK_SYS_ADC_LSB    _u(2)
#define CLOCKS_ENABLED0_CLK_SYS_ADC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_ADC_ADC
// Description : None
#define CLOCKS_ENABLED0_CLK_ADC_ADC_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_ADC_ADC_BITS   _u(0x00000002)
#define CLOCKS_ENABLED0_CLK_ADC_ADC_MSB    _u(1)
#define CLOCKS_ENABLED0_CLK_ADC_ADC_LSB    _u(1)
#define CLOCKS_ENABLED0_CLK_ADC_ADC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED0_CLK_SYS_CLOCKS
// Description : None
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_RESET  _u(0x0)
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_BITS   _u(0x00000001)
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_MSB    _u(0)
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_LSB    _u(0)
#define CLOCKS_ENABLED0_CLK_SYS_CLOCKS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_ENABLED1
// Description : indicates the state of the clock enable
#define CLOCKS_ENABLED1_OFFSET _u(0x000000b4)
#define CLOCKS_ENABLED1_BITS   _u(0x00007fff)
#define CLOCKS_ENABLED1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_XOSC
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_BITS   _u(0x00004000)
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_MSB    _u(14)
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_LSB    _u(14)
#define CLOCKS_ENABLED1_CLK_SYS_XOSC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_XIP
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_XIP_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_XIP_BITS   _u(0x00002000)
#define CLOCKS_ENABLED1_CLK_SYS_XIP_MSB    _u(13)
#define CLOCKS_ENABLED1_CLK_SYS_XIP_LSB    _u(13)
#define CLOCKS_ENABLED1_CLK_SYS_XIP_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_WATCHDOG
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_BITS   _u(0x00001000)
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_MSB    _u(12)
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_LSB    _u(12)
#define CLOCKS_ENABLED1_CLK_SYS_WATCHDOG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_USB_USBCTRL
// Description : None
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_BITS   _u(0x00000800)
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_MSB    _u(11)
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_LSB    _u(11)
#define CLOCKS_ENABLED1_CLK_USB_USBCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_USBCTRL
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_BITS   _u(0x00000400)
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_MSB    _u(10)
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_LSB    _u(10)
#define CLOCKS_ENABLED1_CLK_SYS_USBCTRL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_UART1
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_UART1_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_UART1_BITS   _u(0x00000200)
#define CLOCKS_ENABLED1_CLK_SYS_UART1_MSB    _u(9)
#define CLOCKS_ENABLED1_CLK_SYS_UART1_LSB    _u(9)
#define CLOCKS_ENABLED1_CLK_SYS_UART1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_PERI_UART1
// Description : None
#define CLOCKS_ENABLED1_CLK_PERI_UART1_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_PERI_UART1_BITS   _u(0x00000100)
#define CLOCKS_ENABLED1_CLK_PERI_UART1_MSB    _u(8)
#define CLOCKS_ENABLED1_CLK_PERI_UART1_LSB    _u(8)
#define CLOCKS_ENABLED1_CLK_PERI_UART1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_UART0
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_UART0_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_UART0_BITS   _u(0x00000080)
#define CLOCKS_ENABLED1_CLK_SYS_UART0_MSB    _u(7)
#define CLOCKS_ENABLED1_CLK_SYS_UART0_LSB    _u(7)
#define CLOCKS_ENABLED1_CLK_SYS_UART0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_PERI_UART0
// Description : None
#define CLOCKS_ENABLED1_CLK_PERI_UART0_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_PERI_UART0_BITS   _u(0x00000040)
#define CLOCKS_ENABLED1_CLK_PERI_UART0_MSB    _u(6)
#define CLOCKS_ENABLED1_CLK_PERI_UART0_LSB    _u(6)
#define CLOCKS_ENABLED1_CLK_PERI_UART0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_TIMER
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_BITS   _u(0x00000020)
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_MSB    _u(5)
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_LSB    _u(5)
#define CLOCKS_ENABLED1_CLK_SYS_TIMER_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_TBMAN
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_BITS   _u(0x00000010)
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_MSB    _u(4)
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_LSB    _u(4)
#define CLOCKS_ENABLED1_CLK_SYS_TBMAN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SYSINFO
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_BITS   _u(0x00000008)
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_MSB    _u(3)
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_LSB    _u(3)
#define CLOCKS_ENABLED1_CLK_SYS_SYSINFO_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SYSCFG
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_BITS   _u(0x00000004)
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_MSB    _u(2)
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_LSB    _u(2)
#define CLOCKS_ENABLED1_CLK_SYS_SYSCFG_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SRAM5
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_BITS   _u(0x00000002)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_MSB    _u(1)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_LSB    _u(1)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM5_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : CLOCKS_ENABLED1_CLK_SYS_SRAM4
// Description : None
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_RESET  _u(0x0)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_BITS   _u(0x00000001)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_MSB    _u(0)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_LSB    _u(0)
#define CLOCKS_ENABLED1_CLK_SYS_SRAM4_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_INTR
// Description : Raw Interrupts
#define CLOCKS_INTR_OFFSET _u(0x000000b8)
#define CLOCKS_INTR_BITS   _u(0x00000001)
#define CLOCKS_INTR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTR_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTR_CLK_SYS_RESUS_RESET  _u(0x0)
#define CLOCKS_INTR_CLK_SYS_RESUS_BITS   _u(0x00000001)
#define CLOCKS_INTR_CLK_SYS_RESUS_MSB    _u(0)
#define CLOCKS_INTR_CLK_SYS_RESUS_LSB    _u(0)
#define CLOCKS_INTR_CLK_SYS_RESUS_ACCESS "RO"
// =============================================================================
// Register    : CLOCKS_INTE
// Description : Interrupt Enable
#define CLOCKS_INTE_OFFSET _u(0x000000bc)
#define CLOCKS_INTE_BITS   _u(0x00000001)
#define CLOCKS_INTE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTE_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTE_CLK_SYS_RESUS_RESET  _u(0x0)
#define CLOCKS_INTE_CLK_SYS_RESUS_BITS   _u(0x00000001)
#define CLOCKS_INTE_CLK_SYS_RESUS_MSB    _u(0)
#define CLOCKS_INTE_CLK_SYS_RESUS_LSB    _u(0)
#define CLOCKS_INTE_CLK_SYS_RESUS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_INTF
// Description : Interrupt Force
#define CLOCKS_INTF_OFFSET _u(0x000000c0)
#define CLOCKS_INTF_BITS   _u(0x00000001)
#define CLOCKS_INTF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTF_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTF_CLK_SYS_RESUS_RESET  _u(0x0)
#define CLOCKS_INTF_CLK_SYS_RESUS_BITS   _u(0x00000001)
#define CLOCKS_INTF_CLK_SYS_RESUS_MSB    _u(0)
#define CLOCKS_INTF_CLK_SYS_RESUS_LSB    _u(0)
#define CLOCKS_INTF_CLK_SYS_RESUS_ACCESS "RW"
// =============================================================================
// Register    : CLOCKS_INTS
// Description : Interrupt status after masking & forcing
#define CLOCKS_INTS_OFFSET _u(0x000000c4)
#define CLOCKS_INTS_BITS   _u(0x00000001)
#define CLOCKS_INTS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : CLOCKS_INTS_CLK_SYS_RESUS
// Description : None
#define CLOCKS_INTS_CLK_SYS_RESUS_RESET  _u(0x0)
#define CLOCKS_INTS_CLK_SYS_RESUS_BITS   _u(0x00000001)
#define CLOCKS_INTS_CLK_SYS_RESUS_MSB    _u(0)
#define CLOCKS_INTS_CLK_SYS_RESUS_LSB    _u(0)
#define CLOCKS_INTS_CLK_SYS_RESUS_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_CLOCKS_DEFINED
