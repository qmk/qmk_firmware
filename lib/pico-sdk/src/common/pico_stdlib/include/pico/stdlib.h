/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_STDLIB_H
#define _PICO_STDLIB_H

#include "pico.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file stdlib.h
 *  \defgroup pico_stdlib pico_stdlib
 *
 * Aggregation of a core subset of Raspberry Pi Pico SDK libraries used by most executables along with some additional
 * utility methods. Including pico_stdlib gives you everything you need to get a basic program running
 * which prints to stdout or flashes a LED
 *
 * This library aggregates:
 *   - @ref hardware_uart
 *   - @ref hardware_gpio
 *   - @ref pico_binary_info
 *   - @ref pico_runtime
 *   - @ref pico_platform
 *   - @ref pico_printf
 *   - @ref pico_stdio
 *   - @ref pico_standard_link
 *   - @ref pico_util
 *
 * There are some basic default values used by these functions that will default to
 * usable values, however, they can be customised in a board definition header via
 * config.h or similar
 */

// Note PICO_STDIO_UART, PICO_STDIO_USB, PICO_STDIO_SEMIHOSTING are set by the
// respective INTERFACE libraries, so these defines are set if the library
// is included for the target executable

#if LIB_PICO_STDIO_UART
#include "pico/stdio_uart.h"
#endif

#if LIB_PICO_STDIO_USB
#include "pico/stdio_usb.h"
#endif

#if LIB_PICO_STDIO_SEMIHOSTING
#include "pico/stdio_semihosting.h"
#endif

// PICO_CONFIG: PICO_DEFAULT_LED_PIN, Optionally define a pin that drives a regular LED on the board, group=pico_stdlib

// PICO_CONFIG: PICO_DEFAULT_LED_PIN_INVERTED, 1 if LED is inverted or 0 if not, type=int, default=0, group=pico_stdlib
#ifndef PICO_DEFAULT_LED_PIN_INVERTED
#define PICO_DEFAULT_LED_PIN_INVERTED 0
#endif

// PICO_CONFIG: PICO_DEFAULT_WS2812_PIN, Optionally define a pin that controls data to a WS2812 compatible LED on the board, group=pico_stdlib
// PICO_CONFIG: PICO_DEFAULT_WS2812_POWER_PIN, Optionally define a pin that controls power to a WS2812 compatible LED on the board, group=pico_stdlib

/*! \brief Set up the default UART and assign it to the default GPIO's
 *  \ingroup pico_stdlib
 *
 * By default this will use UART 0, with TX to pin GPIO 0,
 * RX to pin GPIO 1, and the baudrate to 115200
 *
 * Calling this method also initializes stdin/stdout over UART if the
 * @ref pico_stdio_uart library is linked.
 *
 * Defaults can be changed using configuration defines,
 *  PICO_DEFAULT_UART_INSTANCE,
 *  PICO_DEFAULT_UART_BAUD_RATE
 *  PICO_DEFAULT_UART_TX_PIN
 *  PICO_DEFAULT_UART_RX_PIN
 */
void setup_default_uart(void);

/*! \brief Initialise the system clock to 48MHz
 *  \ingroup pico_stdlib
 *
 *  Set the system clock to 48MHz, and set the peripheral clock to match.
 */
void set_sys_clock_48mhz(void);

/*! \brief Initialise the system clock
 *  \ingroup pico_stdlib
 *
 * \param vco_freq The voltage controller oscillator frequency to be used by the SYS PLL
 * \param post_div1 The first post divider for the SYS PLL
 * \param post_div2 The second post divider for the SYS PLL.
 *
 * See the PLL documentation in the datasheet for details of driving the PLLs.
 */
void set_sys_clock_pll(uint32_t vco_freq, uint post_div1, uint post_div2);

/*! \brief Check if a given system clock frequency is valid/attainable
 *  \ingroup pico_stdlib
 *
 * \param freq_khz Requested frequency
 * \param vco_freq_out On success, the voltage controller oscillator frequeucny to be used by the SYS PLL
 * \param post_div1_out On success, The first post divider for the SYS PLL
 * \param post_div2_out On success, The second post divider for the SYS PLL.
 * @return true if the frequency is possible and the output parameters have been written.
 */
bool check_sys_clock_khz(uint32_t freq_khz, uint *vco_freq_out, uint *post_div1_out, uint *post_div2_out);

/*! \brief Attempt to set a system clock frequency in khz
 *  \ingroup pico_stdlib
 *
 * Note that not all clock frequencies are possible; it is preferred that you
 * use src/rp2_common/hardware_clocks/scripts/vcocalc.py to calculate the parameters
 * for use with set_sys_clock_pll
 *
 * \param freq_khz Requested frequency
 * \param required if true then this function will assert if the frequency is not attainable.
 * \return true if the clock was configured
 */
static inline bool set_sys_clock_khz(uint32_t freq_khz, bool required) {
    uint vco, postdiv1, postdiv2;
    if (check_sys_clock_khz(freq_khz, &vco, &postdiv1, &postdiv2)) {
        set_sys_clock_pll(vco, postdiv1, postdiv2);
        return true;
    } else if (required) {
        panic("System clock of %u kHz cannot be exactly achieved", freq_khz);
    }
    return false;
}

#ifdef __cplusplus
}
#endif
#endif
