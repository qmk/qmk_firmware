// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "hal.h"
#include "bootloader.h"
#include "pico/bootrom.h"

#if !defined(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED)
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U
#else
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK (1U << RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED)
#endif

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}
void bootloader_jump(void) {
    reset_usb_boot(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK, 0U);
}

void enter_bootloader_mode_if_requested(void) {}

#if defined(RP2040_BOOTLOADER_DOUBLE_TAP_RESET)
#    if !defined(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT)
#        define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#    endif

// Needs to be located in a RAM section that is never initialized on boot to
// preserve its value on reset
static volatile uint32_t __attribute__((section(".ram0.bootloader_magic"))) magic_location;
const uint32_t magic_token = 0xCAFEB0BA;

// We can not use the __early_init / enter_bootloader_mode_if_requested hook as
// we depend on an already initialized system with usable memory regions and
// populated function pointer tables to the optimized math functions in the
// bootrom. This function is called just prior to main.
void __late_init(void) {
    // All clocks have to be enabled before jumping to the bootloader function,
    // otherwise the bootrom will be stuck infinitely.
    clocks_init();

    if (magic_location != magic_token) {
        magic_location = magic_token;
        // ChibiOS is not initialized at this point, so sleeping is only
        // possible via busy waiting. The internal timer peripheral is running
        // at this point with a precision of 1us.
        chSysPolledDelayX(MS2RTC(1 * MHZ, RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT));
        magic_location = 0;
        return;
    }

    magic_location = 0;
    reset_usb_boot(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK, 0U);
}

#endif
