// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_CLOCKS_H
#define _HARDWARE_STRUCTS_CLOCKS_H

#include "hardware/address_mapped.h"
#include "hardware/regs/clocks.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_clocks
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/clocks.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

/*! \brief Enumeration identifying a hardware clock
 *  \ingroup hardware_clocks
 */
/// \tag::clkenum[]
enum clock_index {
    clk_gpout0 = 0,     ///< GPIO Muxing 0
    clk_gpout1,         ///< GPIO Muxing 1
    clk_gpout2,         ///< GPIO Muxing 2
    clk_gpout3,         ///< GPIO Muxing 3
    clk_ref,            ///< Watchdog and timers reference clock
    clk_sys,            ///< Processors, bus fabric, memory, memory mapped registers
    clk_peri,           ///< Peripheral clock for UART and SPI
    clk_usb,            ///< USB clock
    clk_adc,            ///< ADC clock
    clk_rtc,            ///< Real time clock
    CLK_COUNT
};
/// \end::clkenum[]

/// \tag::clock_hw[]
typedef struct {
    _REG_(CLOCKS_CLK_GPOUT0_CTRL_OFFSET) // CLOCKS_CLK_GPOUT0_CTRL
    // Clock control, can be changed on-the-fly (except for auxsrc)
    // 0x00100000 [20]    : NUDGE (0): An edge on this signal shifts the phase of the output by 1 cycle of the input clock
    // 0x00030000 [17:16] : PHASE (0): This delays the enable signal by up to 3 cycles of the input clock
    // 0x00001000 [12]    : DC50 (0): Enables duty cycle correction for odd divisors
    // 0x00000800 [11]    : ENABLE (0): Starts and stops the clock generator cleanly
    // 0x00000400 [10]    : KILL (0): Asynchronously kills the clock generator
    // 0x000001e0 [8:5]   : AUXSRC (0): Selects the auxiliary clock source, will glitch when switching
    io_rw_32 ctrl;

    _REG_(CLOCKS_CLK_GPOUT0_DIV_OFFSET) // CLOCKS_CLK_GPOUT0_DIV
    // Clock divisor, can be changed on-the-fly
    // 0xffffff00 [31:8]  : INT (1): Integer component of the divisor, 0 -> divide by 2^16
    // 0x000000ff [7:0]   : FRAC (0): Fractional component of the divisor
    io_rw_32 div;

    _REG_(CLOCKS_CLK_GPOUT0_SELECTED_OFFSET) // CLOCKS_CLK_GPOUT0_SELECTED
    // Indicates which SRC is currently selected by the glitchless mux (one-hot)
    io_ro_32 selected;
} clock_hw_t;
/// \end::clock_hw[]

typedef struct {
    _REG_(CLOCKS_CLK_SYS_RESUS_CTRL_OFFSET) // CLOCKS_CLK_SYS_RESUS_CTRL
    // 0x00010000 [16]    : CLEAR (0): For clearing the resus after the fault that triggered it has been corrected
    // 0x00001000 [12]    : FRCE (0): Force a resus, for test purposes only
    // 0x00000100 [8]     : ENABLE (0): Enable resus
    // 0x000000ff [7:0]   : TIMEOUT (0xff): This is expressed as a number of clk_ref cycles
    io_rw_32 ctrl;

    _REG_(CLOCKS_CLK_SYS_RESUS_STATUS_OFFSET) // CLOCKS_CLK_SYS_RESUS_STATUS
    // 0x00000001 [0]     : RESUSSED (0): Clock has been resuscitated, correct the error then send ctrl_clear=1
    io_ro_32 status;
} clock_resus_hw_t;

typedef struct {
    _REG_(CLOCKS_FC0_REF_KHZ_OFFSET) // CLOCKS_FC0_REF_KHZ
    // Reference clock frequency in kHz
    // 0x000fffff [19:0]  : FC0_REF_KHZ (0)
    io_rw_32 ref_khz;

    _REG_(CLOCKS_FC0_MIN_KHZ_OFFSET) // CLOCKS_FC0_MIN_KHZ
    // Minimum pass frequency in kHz
    // 0x01ffffff [24:0]  : FC0_MIN_KHZ (0)
    io_rw_32 min_khz;

    _REG_(CLOCKS_FC0_MAX_KHZ_OFFSET) // CLOCKS_FC0_MAX_KHZ
    // Maximum pass frequency in kHz
    // 0x01ffffff [24:0]  : FC0_MAX_KHZ (0x1ffffff)
    io_rw_32 max_khz;

    _REG_(CLOCKS_FC0_DELAY_OFFSET) // CLOCKS_FC0_DELAY
    // Delays the start of frequency counting to allow the mux to settle
    // 0x00000007 [2:0]   : FC0_DELAY (1)
    io_rw_32 delay;

    _REG_(CLOCKS_FC0_INTERVAL_OFFSET) // CLOCKS_FC0_INTERVAL
    // The test interval is 0
    // 0x0000000f [3:0]   : FC0_INTERVAL (0x8)
    io_rw_32 interval;

    _REG_(CLOCKS_FC0_SRC_OFFSET) // CLOCKS_FC0_SRC
    // Clock sent to frequency counter, set to 0 when not required
    // 0x000000ff [7:0]   : FC0_SRC (0)
    io_rw_32 src;

    _REG_(CLOCKS_FC0_STATUS_OFFSET) // CLOCKS_FC0_STATUS
    // Frequency counter status
    // 0x10000000 [28]    : DIED (0): Test clock stopped during test
    // 0x01000000 [24]    : FAST (0): Test clock faster than expected, only valid when status_done=1
    // 0x00100000 [20]    : SLOW (0): Test clock slower than expected, only valid when status_done=1
    // 0x00010000 [16]    : FAIL (0): Test failed
    // 0x00001000 [12]    : WAITING (0): Waiting for test clock to start
    // 0x00000100 [8]     : RUNNING (0): Test running
    // 0x00000010 [4]     : DONE (0): Test complete
    // 0x00000001 [0]     : PASS (0): Test passed
    io_ro_32 status;

    _REG_(CLOCKS_FC0_RESULT_OFFSET) // CLOCKS_FC0_RESULT
    // Result of frequency measurement, only valid when status_done=1
    // 0x3fffffe0 [29:5]  : KHZ (0)
    // 0x0000001f [4:0]   : FRAC (0)
    io_ro_32 result;
} fc_hw_t;

typedef struct {
    clock_hw_t clk[CLK_COUNT]; // 10

    clock_resus_hw_t resus;

    fc_hw_t fc0;

    _REG_(CLOCKS_WAKE_EN0_OFFSET) // CLOCKS_WAKE_EN0
    // enable clock in wake mode
    // 0x80000000 [31]    : clk_sys_sram3 (1)
    // 0x40000000 [30]    : clk_sys_sram2 (1)
    // 0x20000000 [29]    : clk_sys_sram1 (1)
    // 0x10000000 [28]    : clk_sys_sram0 (1)
    // 0x08000000 [27]    : clk_sys_spi1 (1)
    // 0x04000000 [26]    : clk_peri_spi1 (1)
    // 0x02000000 [25]    : clk_sys_spi0 (1)
    // 0x01000000 [24]    : clk_peri_spi0 (1)
    // 0x00800000 [23]    : clk_sys_sio (1)
    // 0x00400000 [22]    : clk_sys_rtc (1)
    // 0x00200000 [21]    : clk_rtc_rtc (1)
    // 0x00100000 [20]    : clk_sys_rosc (1)
    // 0x00080000 [19]    : clk_sys_rom (1)
    // 0x00040000 [18]    : clk_sys_resets (1)
    // 0x00020000 [17]    : clk_sys_pwm (1)
    // 0x00010000 [16]    : clk_sys_psm (1)
    // 0x00008000 [15]    : clk_sys_pll_usb (1)
    // 0x00004000 [14]    : clk_sys_pll_sys (1)
    // 0x00002000 [13]    : clk_sys_pio1 (1)
    // 0x00001000 [12]    : clk_sys_pio0 (1)
    // 0x00000800 [11]    : clk_sys_pads (1)
    // 0x00000400 [10]    : clk_sys_vreg_and_chip_reset (1)
    // 0x00000200 [9]     : clk_sys_jtag (1)
    // 0x00000100 [8]     : clk_sys_io (1)
    // 0x00000080 [7]     : clk_sys_i2c1 (1)
    // 0x00000040 [6]     : clk_sys_i2c0 (1)
    // 0x00000020 [5]     : clk_sys_dma (1)
    // 0x00000010 [4]     : clk_sys_busfabric (1)
    // 0x00000008 [3]     : clk_sys_busctrl (1)
    // 0x00000004 [2]     : clk_sys_adc (1)
    // 0x00000002 [1]     : clk_adc_adc (1)
    // 0x00000001 [0]     : clk_sys_clocks (1)
    io_rw_32 wake_en0;

    _REG_(CLOCKS_WAKE_EN1_OFFSET) // CLOCKS_WAKE_EN1
    // enable clock in wake mode
    // 0x00004000 [14]    : clk_sys_xosc (1)
    // 0x00002000 [13]    : clk_sys_xip (1)
    // 0x00001000 [12]    : clk_sys_watchdog (1)
    // 0x00000800 [11]    : clk_usb_usbctrl (1)
    // 0x00000400 [10]    : clk_sys_usbctrl (1)
    // 0x00000200 [9]     : clk_sys_uart1 (1)
    // 0x00000100 [8]     : clk_peri_uart1 (1)
    // 0x00000080 [7]     : clk_sys_uart0 (1)
    // 0x00000040 [6]     : clk_peri_uart0 (1)
    // 0x00000020 [5]     : clk_sys_timer (1)
    // 0x00000010 [4]     : clk_sys_tbman (1)
    // 0x00000008 [3]     : clk_sys_sysinfo (1)
    // 0x00000004 [2]     : clk_sys_syscfg (1)
    // 0x00000002 [1]     : clk_sys_sram5 (1)
    // 0x00000001 [0]     : clk_sys_sram4 (1)
    io_rw_32 wake_en1;

    _REG_(CLOCKS_SLEEP_EN0_OFFSET) // CLOCKS_SLEEP_EN0
    // enable clock in sleep mode
    // 0x80000000 [31]    : clk_sys_sram3 (1)
    // 0x40000000 [30]    : clk_sys_sram2 (1)
    // 0x20000000 [29]    : clk_sys_sram1 (1)
    // 0x10000000 [28]    : clk_sys_sram0 (1)
    // 0x08000000 [27]    : clk_sys_spi1 (1)
    // 0x04000000 [26]    : clk_peri_spi1 (1)
    // 0x02000000 [25]    : clk_sys_spi0 (1)
    // 0x01000000 [24]    : clk_peri_spi0 (1)
    // 0x00800000 [23]    : clk_sys_sio (1)
    // 0x00400000 [22]    : clk_sys_rtc (1)
    // 0x00200000 [21]    : clk_rtc_rtc (1)
    // 0x00100000 [20]    : clk_sys_rosc (1)
    // 0x00080000 [19]    : clk_sys_rom (1)
    // 0x00040000 [18]    : clk_sys_resets (1)
    // 0x00020000 [17]    : clk_sys_pwm (1)
    // 0x00010000 [16]    : clk_sys_psm (1)
    // 0x00008000 [15]    : clk_sys_pll_usb (1)
    // 0x00004000 [14]    : clk_sys_pll_sys (1)
    // 0x00002000 [13]    : clk_sys_pio1 (1)
    // 0x00001000 [12]    : clk_sys_pio0 (1)
    // 0x00000800 [11]    : clk_sys_pads (1)
    // 0x00000400 [10]    : clk_sys_vreg_and_chip_reset (1)
    // 0x00000200 [9]     : clk_sys_jtag (1)
    // 0x00000100 [8]     : clk_sys_io (1)
    // 0x00000080 [7]     : clk_sys_i2c1 (1)
    // 0x00000040 [6]     : clk_sys_i2c0 (1)
    // 0x00000020 [5]     : clk_sys_dma (1)
    // 0x00000010 [4]     : clk_sys_busfabric (1)
    // 0x00000008 [3]     : clk_sys_busctrl (1)
    // 0x00000004 [2]     : clk_sys_adc (1)
    // 0x00000002 [1]     : clk_adc_adc (1)
    // 0x00000001 [0]     : clk_sys_clocks (1)
    io_rw_32 sleep_en0;

    _REG_(CLOCKS_SLEEP_EN1_OFFSET) // CLOCKS_SLEEP_EN1
    // enable clock in sleep mode
    // 0x00004000 [14]    : clk_sys_xosc (1)
    // 0x00002000 [13]    : clk_sys_xip (1)
    // 0x00001000 [12]    : clk_sys_watchdog (1)
    // 0x00000800 [11]    : clk_usb_usbctrl (1)
    // 0x00000400 [10]    : clk_sys_usbctrl (1)
    // 0x00000200 [9]     : clk_sys_uart1 (1)
    // 0x00000100 [8]     : clk_peri_uart1 (1)
    // 0x00000080 [7]     : clk_sys_uart0 (1)
    // 0x00000040 [6]     : clk_peri_uart0 (1)
    // 0x00000020 [5]     : clk_sys_timer (1)
    // 0x00000010 [4]     : clk_sys_tbman (1)
    // 0x00000008 [3]     : clk_sys_sysinfo (1)
    // 0x00000004 [2]     : clk_sys_syscfg (1)
    // 0x00000002 [1]     : clk_sys_sram5 (1)
    // 0x00000001 [0]     : clk_sys_sram4 (1)
    io_rw_32 sleep_en1;

    _REG_(CLOCKS_ENABLED0_OFFSET) // CLOCKS_ENABLED0
    // indicates the state of the clock enable
    // 0x80000000 [31]    : clk_sys_sram3 (0)
    // 0x40000000 [30]    : clk_sys_sram2 (0)
    // 0x20000000 [29]    : clk_sys_sram1 (0)
    // 0x10000000 [28]    : clk_sys_sram0 (0)
    // 0x08000000 [27]    : clk_sys_spi1 (0)
    // 0x04000000 [26]    : clk_peri_spi1 (0)
    // 0x02000000 [25]    : clk_sys_spi0 (0)
    // 0x01000000 [24]    : clk_peri_spi0 (0)
    // 0x00800000 [23]    : clk_sys_sio (0)
    // 0x00400000 [22]    : clk_sys_rtc (0)
    // 0x00200000 [21]    : clk_rtc_rtc (0)
    // 0x00100000 [20]    : clk_sys_rosc (0)
    // 0x00080000 [19]    : clk_sys_rom (0)
    // 0x00040000 [18]    : clk_sys_resets (0)
    // 0x00020000 [17]    : clk_sys_pwm (0)
    // 0x00010000 [16]    : clk_sys_psm (0)
    // 0x00008000 [15]    : clk_sys_pll_usb (0)
    // 0x00004000 [14]    : clk_sys_pll_sys (0)
    // 0x00002000 [13]    : clk_sys_pio1 (0)
    // 0x00001000 [12]    : clk_sys_pio0 (0)
    // 0x00000800 [11]    : clk_sys_pads (0)
    // 0x00000400 [10]    : clk_sys_vreg_and_chip_reset (0)
    // 0x00000200 [9]     : clk_sys_jtag (0)
    // 0x00000100 [8]     : clk_sys_io (0)
    // 0x00000080 [7]     : clk_sys_i2c1 (0)
    // 0x00000040 [6]     : clk_sys_i2c0 (0)
    // 0x00000020 [5]     : clk_sys_dma (0)
    // 0x00000010 [4]     : clk_sys_busfabric (0)
    // 0x00000008 [3]     : clk_sys_busctrl (0)
    // 0x00000004 [2]     : clk_sys_adc (0)
    // 0x00000002 [1]     : clk_adc_adc (0)
    // 0x00000001 [0]     : clk_sys_clocks (0)
    io_ro_32 enabled0;

    _REG_(CLOCKS_ENABLED1_OFFSET) // CLOCKS_ENABLED1
    // indicates the state of the clock enable
    // 0x00004000 [14]    : clk_sys_xosc (0)
    // 0x00002000 [13]    : clk_sys_xip (0)
    // 0x00001000 [12]    : clk_sys_watchdog (0)
    // 0x00000800 [11]    : clk_usb_usbctrl (0)
    // 0x00000400 [10]    : clk_sys_usbctrl (0)
    // 0x00000200 [9]     : clk_sys_uart1 (0)
    // 0x00000100 [8]     : clk_peri_uart1 (0)
    // 0x00000080 [7]     : clk_sys_uart0 (0)
    // 0x00000040 [6]     : clk_peri_uart0 (0)
    // 0x00000020 [5]     : clk_sys_timer (0)
    // 0x00000010 [4]     : clk_sys_tbman (0)
    // 0x00000008 [3]     : clk_sys_sysinfo (0)
    // 0x00000004 [2]     : clk_sys_syscfg (0)
    // 0x00000002 [1]     : clk_sys_sram5 (0)
    // 0x00000001 [0]     : clk_sys_sram4 (0)
    io_ro_32 enabled1;

    _REG_(CLOCKS_INTR_OFFSET) // CLOCKS_INTR
    // Raw Interrupts
    // 0x00000001 [0]     : CLK_SYS_RESUS (0)
    io_ro_32 intr;

    _REG_(CLOCKS_INTE_OFFSET) // CLOCKS_INTE
    // Interrupt Enable
    // 0x00000001 [0]     : CLK_SYS_RESUS (0)
    io_rw_32 inte;

    _REG_(CLOCKS_INTF_OFFSET) // CLOCKS_INTF
    // Interrupt Force
    // 0x00000001 [0]     : CLK_SYS_RESUS (0)
    io_rw_32 intf;

    _REG_(CLOCKS_INTS_OFFSET) // CLOCKS_INTS
    // Interrupt status after masking & forcing
    // 0x00000001 [0]     : CLK_SYS_RESUS (0)
    io_ro_32 ints;
} clocks_hw_t;

#define clocks_hw ((clocks_hw_t *)CLOCKS_BASE)

static_assert( CLK_COUNT == 10, "");

#endif
