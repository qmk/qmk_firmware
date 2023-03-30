/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_CLOCKS_H
#define _HARDWARE_CLOCKS_H

#include "pico.h"
#include "hardware/structs/clocks.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/clocks.h
 *  \defgroup hardware_clocks hardware_clocks
 *
 * Clock Management API
 *
 * This API provides a high level interface to the clock functions.
 *
 * The clocks block provides independent clocks to on-chip and external components. It takes inputs from a variety of clock
 * sources allowing the user to trade off performance against cost, board area and power consumption. From these sources
 * it uses multiple clock generators to provide the required clocks. This architecture allows the user flexibility to start and
 * stop clocks independently and to vary some clock frequencies whilst maintaining others at their optimum frequencies
 *
 * Please refer to the datasheet for more details on the RP2040 clocks.
 *
 * The clock source depends on which clock you are attempting to configure. The first table below shows main clock sources. If
 * you are not setting the Reference clock or the System clock, or you are specifying that one of those two will be using an auxiliary
 * clock source, then you will need to use one of the entries from the subsequent tables.
 *
 * **Main Clock Sources**
 *
 * Source | Reference Clock | System Clock
 * -------|-----------------|---------
 * ROSC      | CLOCKS_CLK_REF_CTRL_SRC_VALUE_ROSC_CLKSRC_PH     |  |
 * Auxiliary | CLOCKS_CLK_REF_CTRL_SRC_VALUE_CLKSRC_CLK_REF_AUX | CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX
 * XOSC      | CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC        |  |
 * Reference |                                                  | CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF
 *
 * **Auxiliary Clock Sources**
 *
 * The auxiliary clock sources available for use in the configure function depend on which clock is being configured. The following table
 * describes the available values that can be used. Note that for clk_gpout[x], x can be 0-3.
 *
 *
 * Aux Source | clk_gpout[x] | clk_ref | clk_sys
 * -----------|------------|---------|--------
 * System PLL | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS |                                                | CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS
 * GPIO in 0  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   | CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0  | CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0
 * GPIO in 1  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   | CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1  | CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1
 * USB PLL    | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB | CLOCKS_CLK_REF_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB| CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB
 * ROSC       | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_ROSC_CLKSRC    |                                                | CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC
 * XOSC       | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    |                                                | CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_ROSC_CLKSRC
 * System clock | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLK_SYS      | | |
 * USB Clock  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLK_USB        | | |
 * ADC clock  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLK_ADC        | | |
 * RTC Clock  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLK_RTC        | | |
 * Ref clock  | CLOCKS_CLK_GPOUTx_CTRL_AUXSRC_VALUE_CLK_REF        | | |
 *
 * Aux Source |  clk_peri | clk_usb | clk_adc
 * -----------|-----------|---------|--------
 * System PLL | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS    | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS
 * GPIO in 0  | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0      | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0   | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0
 * GPIO in 1  | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1      | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1   | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1
 * USB PLL    | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB    | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB
 * ROSC       | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH    | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH
 * XOSC       | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_XOSC_CLKSRC       | CLOCKS_CLK_USB_CTRL_AUXSRC_VALUE_XOSC_CLKSRC    | CLOCKS_CLK_ADC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC
 * System clock | CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS         | | |
 *
 * Aux Source | clk_rtc
 * -----------|----------
 * System PLL |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS
 * GPIO in 0  |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN0
 * GPIO in 1  |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_GPIN1
 * USB PLL    |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_CLKSRC_PLL_USB
 * ROSC       |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_ROSC_CLKSRC_PH
 * XOSC       |  CLOCKS_CLK_RTC_CTRL_AUXSRC_VALUE_XOSC_CLKSRC

 *
 * \section clock_example Example
 * \addtogroup hardware_clocks
 * \include hello_48MHz.c
 */

#define KHZ 1000
#define MHZ 1000000

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_CLOCKS, Enable/disable assertions in the clocks module, type=bool, default=0, group=hardware_clocks
#ifndef PARAM_ASSERTIONS_ENABLED_CLOCKS
#define PARAM_ASSERTIONS_ENABLED_CLOCKS 0
#endif

/*! \brief Initialise the clock hardware
 *  \ingroup hardware_clocks
 *
 *  Must be called before any other clock function.
 */
void clocks_init(void);

/*! \brief Configure the specified clock
 *  \ingroup hardware_clocks
 *
 * See the tables in the description for details on the possible values for clock sources.
 *
 * \param clk_index The clock to configure
 * \param src The main clock source, can be 0.
 * \param auxsrc The auxiliary clock source, which depends on which clock is being set. Can be 0
 * \param src_freq Frequency of the input clock source
 * \param freq Requested frequency
 */
bool clock_configure(enum clock_index clk_index, uint32_t src, uint32_t auxsrc, uint32_t src_freq, uint32_t freq);

/*! \brief Stop the specified clock
 *  \ingroup hardware_clocks
 *
 * \param clk_index The clock to stop
 */
void clock_stop(enum clock_index clk_index);

/*! \brief Get the current frequency of the specified clock
 *  \ingroup hardware_clocks
 *
 * \param clk_index Clock
 * \return Clock frequency in Hz
 */
uint32_t clock_get_hz(enum clock_index clk_index);

/*! \brief Measure a clocks frequency using the Frequency counter.
 *  \ingroup hardware_clocks
 *
 * Uses the inbuilt frequency counter to measure the specified clocks frequency.
 * Currently, this function is accurate to +-1KHz. See the datasheet for more details.
 */
uint32_t frequency_count_khz(uint src);

/*! \brief Set the "current frequency" of the clock as reported by clock_get_hz without actually changing the clock
 *  \ingroup hardware_clocks
 *
 * \see clock_get_hz()
 */
void clock_set_reported_hz(enum clock_index clk_index, uint hz);

/// \tag::frequency_count_mhz[]
static inline float frequency_count_mhz(uint src) {
    return ((float) (frequency_count_khz(src))) / KHZ;
}
/// \end::frequency_count_mhz[]

/*! \brief Resus callback function type.
 *  \ingroup hardware_clocks
 *
 * User provided callback for a resus event (when clk_sys is stopped by the programmer and is restarted for them).
 */
typedef void (*resus_callback_t)(void);

/*! \brief Enable the resus function. Restarts clk_sys if it is accidentally stopped.
 *  \ingroup hardware_clocks
 *
 * The resuscitate function will restart the system clock if it falls below a certain speed (or stops). This
 * could happen if the clock source the system clock is running from stops. For example if a PLL is stopped.
 *
 * \param resus_callback a function pointer provided by the user to call if a resus event happens.
 */
void clocks_enable_resus(resus_callback_t resus_callback);

/*! \brief Output an optionally divided clock to the specified gpio pin.
 *  \ingroup hardware_clocks
 *
 * \param gpio The GPIO pin to output the clock to. Valid GPIOs are: 21, 23, 24, 25. These GPIOs are connected to the GPOUT0-3 clock generators.
 * \param src  The source clock. See the register field CLOCKS_CLK_GPOUT0_CTRL_AUXSRC for a full list. The list is the same for each GPOUT clock generator.
 * \param div_int  The integer part of the value to divide the source clock by. This is useful to not overwhelm the GPIO pin with a fast clock. this is in range of 1..2^24-1.
 * \param div_frac The fractional part of the value to divide the source clock by. This is in range of 0..255 (/256).
 */
void clock_gpio_init_int_frac(uint gpio, uint src, uint32_t div_int, uint8_t div_frac);

/*! \brief Output an optionally divided clock to the specified gpio pin.
 *  \ingroup hardware_clocks
 *
 * \param gpio The GPIO pin to output the clock to. Valid GPIOs are: 21, 23, 24, 25. These GPIOs are connected to the GPOUT0-3 clock generators.
 * \param src  The source clock. See the register field CLOCKS_CLK_GPOUT0_CTRL_AUXSRC for a full list. The list is the same for each GPOUT clock generator.
 * \param div  The float amount to divide the source clock by. This is useful to not overwhelm the GPIO pin with a fast clock.
 */
static inline void clock_gpio_init(uint gpio, uint src, float div)
{
    uint div_int = (uint)div;
    uint8_t frac = (uint8_t)((div - (float)div_int) * (1u << CLOCKS_CLK_GPOUT0_DIV_INT_LSB));
    clock_gpio_init_int_frac(gpio, src, div_int, frac);
}

/*! \brief Configure a clock to come from a gpio input
 *  \ingroup hardware_clocks
 *
 * \param clk_index The clock to configure
 * \param gpio The GPIO pin to run the clock from. Valid GPIOs are: 20 and 22.
 * \param src_freq Frequency of the input clock source
 * \param freq Requested frequency
 */
bool clock_configure_gpin(enum clock_index clk_index, uint gpio, uint32_t src_freq, uint32_t freq);


#ifdef __cplusplus
}
#endif

#endif
