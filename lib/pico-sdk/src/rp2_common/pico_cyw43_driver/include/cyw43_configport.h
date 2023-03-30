/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// This header is included by cyw43_driver to setup its environment

#ifndef _CYW43_CONFIGPORT_H
#define _CYW43_CONFIGPORT_H

#include "pico.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CYW43_HOST_NAME
#define CYW43_HOST_NAME "PicoW"
#endif

#ifndef CYW43_GPIO
#define CYW43_GPIO 1
#endif

#ifndef CYW43_LOGIC_DEBUG
#define CYW43_LOGIC_DEBUG 0
#endif

#ifndef CYW43_USE_OTP_MAC
#define CYW43_USE_OTP_MAC 1
#endif

#ifndef CYW43_NO_NETUTILS
#define CYW43_NO_NETUTILS 1
#endif

#ifndef CYW43_IOCTL_TIMEOUT_US
#define CYW43_IOCTL_TIMEOUT_US 1000000
#endif

#ifndef CYW43_USE_STATS
#define CYW43_USE_STATS 0
#endif

// todo should this be user settable?
#ifndef CYW43_HAL_MAC_WLAN0
#define CYW43_HAL_MAC_WLAN0 0
#endif

#ifndef STATIC
#define STATIC static
#endif

#ifndef CYW43_USE_SPI
#define CYW43_USE_SPI 1
#endif

#ifndef CYW43_SPI_PIO
#define CYW43_SPI_PIO 1
#endif

#ifndef CYW43_CHIPSET_FIRMWARE_INCLUDE_FILE
#if CYW43_ENABLE_BLUETOOTH
#define CYW43_CHIPSET_FIRMWARE_INCLUDE_FILE "wb43439A0_7_95_49_00_combined.h"
#else
#define CYW43_CHIPSET_FIRMWARE_INCLUDE_FILE "w43439A0_7_95_49_00_combined.h"
#endif
#endif

#ifndef CYW43_WIFI_NVRAM_INCLUDE_FILE
#define CYW43_WIFI_NVRAM_INCLUDE_FILE "wifi_nvram_43439.h"
#endif

// Note, these are negated, because cyw43_driver negates them before returning!
#define CYW43_EPERM            (-PICO_ERROR_NOT_PERMITTED) // Operation not permitted
#define CYW43_EIO              (-PICO_ERROR_IO) // I/O error
#define CYW43_EINVAL           (-PICO_ERROR_INVALID_ARG) // Invalid argument
#define CYW43_ETIMEDOUT        (-PICO_ERROR_TIMEOUT) // Connection timed out

#define CYW43_NUM_GPIOS        CYW43_WL_GPIO_COUNT

#define cyw43_hal_pin_obj_t uint

// get the number of elements in a fixed-size array
#define CYW43_ARRAY_SIZE(a) count_of(a)

static inline uint32_t cyw43_hal_ticks_us(void) {
    return time_us_32();
}

static inline uint32_t cyw43_hal_ticks_ms(void) {
    return to_ms_since_boot(get_absolute_time());
}

static inline int cyw43_hal_pin_read(cyw43_hal_pin_obj_t pin) {
    return gpio_get(pin);
}

static inline void cyw43_hal_pin_low(cyw43_hal_pin_obj_t pin) {
    gpio_clr_mask(1 << pin);
}

static inline void cyw43_hal_pin_high(cyw43_hal_pin_obj_t pin) {
    gpio_set_mask(1 << pin);
}

#define CYW43_HAL_PIN_MODE_INPUT           (GPIO_IN)
#define CYW43_HAL_PIN_MODE_OUTPUT          (GPIO_OUT)

#define CYW43_HAL_PIN_PULL_NONE            (0)
#define CYW43_HAL_PIN_PULL_UP              (1)
#define CYW43_HAL_PIN_PULL_DOWN            (2)

static inline void cyw43_hal_pin_config(cyw43_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, __unused uint32_t alt) {
    assert((mode == CYW43_HAL_PIN_MODE_INPUT || mode == CYW43_HAL_PIN_MODE_OUTPUT) && alt == 0);
    gpio_set_dir(pin, mode);
    gpio_set_pulls(pin, pull == CYW43_HAL_PIN_PULL_UP, pull == CYW43_HAL_PIN_PULL_DOWN);
}

void cyw43_hal_get_mac(int idx, uint8_t buf[6]);

void cyw43_hal_generate_laa_mac(int idx, uint8_t buf[6]);


void cyw43_thread_enter(void);

void cyw43_thread_exit(void);

#define CYW43_THREAD_ENTER cyw43_thread_enter();
#define CYW43_THREAD_EXIT cyw43_thread_exit();
#ifndef NDEBUG

void cyw43_thread_lock_check(void);

#define cyw43_arch_lwip_check() cyw43_thread_lock_check()
#define CYW43_THREAD_LOCK_CHECK cyw43_arch_lwip_check();
#else
#define cyw43_arch_lwip_check() ((void)0)
#define CYW43_THREAD_LOCK_CHECK
#endif

void cyw43_await_background_or_timeout_us(uint32_t timeout_us);
// todo not 100% sure about the timeouts here; MP uses __WFI which will always wakeup periodically
#define CYW43_SDPCM_SEND_COMMON_WAIT cyw43_await_background_or_timeout_us(1000);
#define CYW43_DO_IOCTL_WAIT cyw43_await_background_or_timeout_us(1000);

void cyw43_delay_ms(uint32_t ms);

void cyw43_delay_us(uint32_t us);

void cyw43_schedule_internal_poll_dispatch(void (*func)(void));

void cyw43_post_poll_hook(void);

#define CYW43_POST_POLL_HOOK cyw43_post_poll_hook();

#ifdef __cplusplus
}
#endif


#endif