/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_WATCHDOG_H
#define _HARDWARE_WATCHDOG_H

#include "pico.h"
#include "hardware/structs/watchdog.h"

/** \file hardware/watchdog.h
 *  \defgroup hardware_watchdog hardware_watchdog
 *
 * Hardware Watchdog Timer API
 *
 * Supporting functions for the Pico hardware watchdog timer.
 *
 * The RP2040 has a built in HW watchdog Timer. This is a countdown timer that can restart parts of the chip if it reaches zero.
 * For example, this can be used to restart the processor if the software running on it gets stuck in an infinite loop
 * or similar. The programmer has to periodically write a value to the watchdog to stop it reaching zero.
 *
 * \subsection watchdog_example Example
 * \addtogroup hardware_watchdog
 * \include hello_watchdog.c
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Define actions to perform at watchdog timeout
 *  \ingroup hardware_watchdog
 *
 * \note If \ref watchdog_start_tick value does not give a 1MHz clock to the watchdog system, then the \p delay_ms
 * parameter will not be in microseconds. See the datasheet for more details.
 *
 * By default the SDK assumes a 12MHz XOSC and sets the \ref watchdog_start_tick appropriately.
 *
 * \param pc If Zero, a standard boot will be performed, if non-zero this is the program counter to jump to on reset.
 * \param sp If \p pc is non-zero, this will be the stack pointer used.
 * \param delay_ms Initial load value. Maximum value 0x7fffff, approximately 8.3s.
 */
void watchdog_reboot(uint32_t pc, uint32_t sp, uint32_t delay_ms);

/*! \brief Start the watchdog tick
 *  \ingroup hardware_watchdog
 *
 * \param cycles This needs to be a divider that when applied to the XOSC input, produces a 1MHz clock. So if the XOSC is
 * 12MHz, this will need to be 12.
 */
void watchdog_start_tick(uint cycles);

/*! \brief Reload the watchdog counter with the amount of time set in watchdog_enable
 *  \ingroup hardware_watchdog
 *
 */
void watchdog_update(void);

/**
 * \brief Enable the watchdog
 * \ingroup hardware_watchdog
 *
 * \note If \ref watchdog_start_tick value does not give a 1MHz clock to the watchdog system, then the \p delay_ms
 * parameter will not be in microseconds. See the datasheet for more details.
 *
 * By default the SDK assumes a 12MHz XOSC and sets the \ref watchdog_start_tick appropriately.
 *
 * This method sets a marker in the watchdog scratch register 4 that is checked by \ref watchdog_enable_caused_reboot.
 * If the device is subsequently reset via a call to watchdog_reboot (including for example by dragging a UF2
 * onto the RPI-RP2), then this value will be cleared, and so \ref watchdog_enable_caused_reboot will
 * return false.
 *
 * \param delay_ms Number of milliseconds before watchdog will reboot without watchdog_update being called. Maximum of 0x7fffff, which is approximately 8.3 seconds
 * \param pause_on_debug If the watchdog should be paused when the debugger is stepping through code
 */
void watchdog_enable(uint32_t delay_ms, bool pause_on_debug);

/**
 * \brief Did the watchdog cause the last reboot?
 * \ingroup hardware_watchdog
 *
 * @return true If the watchdog timer or a watchdog force caused the last reboot
 * @return false If there has been no watchdog reboot since the last power on reset. A power on reset is typically caused by a power cycle or the run pin (reset button) being toggled.
 */
bool watchdog_caused_reboot(void);

/**
 * \brief Did watchdog_enable cause the last reboot?
 * \ingroup hardware_watchdog
 *
 * Perform additional checking along with \ref watchdog_caused_reboot to determine if a watchdog timeout initiated by
 * \ref watchdog_enable caused the last reboot.
 *
 * This method checks for a special value in watchdog scratch register 4 placed there by \ref watchdog_enable.
 * This would not be present if a watchdog reset is initiated by \ref watchdog_reboot or by the RP2040 bootrom
 * (e.g. dragging a UF2 onto the RPI-RP2 drive).
 *
 * @return true If the watchdog timer or a watchdog force caused (see \ref watchdog_caused_reboot) the last reboot
 *              and the watchdog reboot happened after \ref watchdog_enable was called
 * @return false If there has been no watchdog reboot since the last power on reset, or the watchdog reboot was not caused
 *               by a watchdog timeout after \ref watchdog_enable was called.
 *               A power on reset is typically caused by a power cycle or the run pin (reset button) being toggled.
 */
bool watchdog_enable_caused_reboot(void);

/**
 * @brief Returns the number of microseconds before the watchdog will reboot the chip.
 * \ingroup hardware_watchdog
 *
 * @return The number of microseconds before the watchdog will reboot the chip.
 */
uint32_t watchdog_get_count(void);

#ifdef __cplusplus
}
#endif

#endif
