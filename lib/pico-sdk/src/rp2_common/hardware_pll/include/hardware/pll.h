/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_PLL_H
#define _HARDWARE_PLL_H

#include "pico.h"
#include "hardware/structs/pll.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/pll.h
 *  \defgroup hardware_pll hardware_pll
 *
 * Phase Locked Loop control APIs
 *
 * There are two PLLs in RP2040. They are:
 *   - pll_sys - Used to generate up to a 133MHz system clock
 *   - pll_usb - Used to generate a 48MHz USB reference clock
 *
 * For details on how the PLL's are calculated, please refer to the RP2040 datasheet.
 */

typedef pll_hw_t *PLL;

#define pll_sys pll_sys_hw
#define pll_usb pll_usb_hw

#ifndef PICO_PLL_VCO_MIN_FREQ_MHZ
#define PICO_PLL_VCO_MIN_FREQ_MHZ 750
#endif

#ifndef PICO_PLL_VCO_MAX_FREQ_MHZ
#define PICO_PLL_VCO_MAX_FREQ_MHZ 1600
#endif

/*! \brief Initialise specified PLL.
 *  \ingroup hardware_pll
 * \param pll pll_sys or pll_usb
 * \param ref_div Input clock divider.
 * \param vco_freq  Requested output from the VCO (voltage controlled oscillator)
 * \param post_div1 Post Divider 1 - range 1-7. Must be >= post_div2
 * \param post_div2 Post Divider 2 - range 1-7
 */
void pll_init(PLL pll, uint ref_div, uint vco_freq, uint post_div1, uint post_div2);

/*! \brief Release/uninitialise specified PLL.
 *  \ingroup hardware_pll
 *
 * This will turn off the power to the specified PLL. Note this function does not currently check if
 * the PLL is in use before powering it off so should be used with care.
 *
 * \param pll pll_sys or pll_usb
 */
void pll_deinit(PLL pll);


#ifdef __cplusplus
}
#endif

#endif
