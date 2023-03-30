/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Here to organize documentation order

/**
 * \defgroup hardware Hardware APIs
 * This group of libraries provides a thin and efficient C API / abstractions to access the RP2040 hardware without having to read and write
 * hardware registers directly.
 * @{
 * \defgroup hardware_adc hardware_adc
 * \defgroup hardware_base hardware_base
 * \defgroup hardware_claim hardware_claim
 * \defgroup hardware_clocks hardware_clocks
 * \defgroup hardware_divider hardware_divider
 * \defgroup hardware_dma hardware_dma
 * \defgroup hardware_exception hardware_exception
 * \defgroup hardware_flash hardware_flash
 * \defgroup hardware_gpio hardware_gpio
 * \defgroup hardware_i2c hardware_i2c
 * \defgroup hardware_interp hardware_interp
 * \defgroup hardware_irq hardware_irq
 * \defgroup hardware_pio hardware_pio
 * \defgroup hardware_pll hardware_pll
 * \defgroup hardware_pwm hardware_pwm
 * \defgroup hardware_resets hardware_resets
 * \defgroup hardware_rtc hardware_rtc
 * \defgroup hardware_spi hardware_spi
 * \defgroup hardware_sync hardware_sync
 * \defgroup hardware_timer hardware_timer
 * \defgroup hardware_uart hardware_uart
 * \defgroup hardware_vreg hardware_vreg
 * \defgroup hardware_watchdog hardware_watchdog
 * \defgroup hardware_xosc hardware_xosc
 * @}
 *
 * \defgroup high_level High Level APIs
 * This group of libraries provide higher level functionality that isn't hardware related or provides a richer
 * set of functionality above the basic hardware interfaces
 * @{
 * \defgroup pico_async_context pico_async_context
 * \defgroup pico_multicore pico_multicore
 * \defgroup pico_i2c_slave pico_i2c_slave
 * \defgroup pico_rand pico_rand
 * \defgroup pico_stdlib pico_stdlib
 * \defgroup pico_sync pico_sync
 * \defgroup pico_time pico_time
 * \defgroup pico_unique_id pico_unique_id
 * \defgroup pico_util pico_util
 * @}
 *
 * \defgroup third_party Third-party Libraries
 * Third party libraries for implementing high level functionality.
 * @{
 * \defgroup tinyusb_device tinyusb_device
 * \defgroup tinyusb_host tinyusb_host
 * @}
 *
 * \defgroup networking Networking Libraries
 * Functions for implementing networking
 * @{
 * \defgroup pico_btstack pico_btstack
 * \defgroup pico_lwip pico_lwip
 * \defgroup pico_cyw43_driver pico_cyw43_driver
 * \defgroup pico_cyw43_arch pico_cyw43_arch
 * @}
 *
 * \defgroup runtime Runtime Infrastructure
 * Libraries that are used to provide efficient implementation of certain
 * language level and C library functions, as well as CMake INTERFACE libraries
 * abstracting the compilation and link steps in the SDK
 * @{
 * \defgroup boot_stage2 boot_stage2
 * \defgroup pico_base pico_base
 * \defgroup pico_binary_info pico_binary_info
 * \defgroup pico_bit_ops pico_bit_ops
 * \defgroup pico_bootrom pico_bootrom
 * \defgroup pico_bootsel_via_double_reset pico_bootsel_via_double_reset
 * \defgroup pico_cxx_options pico_cxx_options
 * \defgroup pico_divider pico_divider
 * \defgroup pico_double pico_double
 * \defgroup pico_float pico_float
 * \defgroup pico_int64_ops pico_int64_ops
 * \defgroup pico_malloc pico_malloc
 * \defgroup pico_mem_ops pico_mem_ops
 * \defgroup pico_platform pico_platform
 * \defgroup pico_printf pico_printf
 * \defgroup pico_runtime pico_runtime
 * \defgroup pico_stdio pico_stdio
 * \defgroup pico_standard_link pico_standard_link
 * @}
 *
 * \defgroup misc External API Headers
 * Headers for interfaces that are shared with code outside of the SDK
 * @{
 * \defgroup boot_picoboot boot_picoboot
 * \defgroup boot_uf2 boot_uf2
 * @}
*/
