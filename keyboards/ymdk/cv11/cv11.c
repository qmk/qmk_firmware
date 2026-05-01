// SPDX-License-Identifier: BSD-2-Clause

#include QMK_KEYBOARD_H
#include <ch.h>
#include "print.h"
#include "timer.h"

/*
 * DAPBoot enters DFU mode when *0x20004000 == 0x544F4F42 ("BOOT").
 * Any other value causes DAPBoot to boot the app. SRAM survives NVIC_SystemReset.
 * DAPBoot drives D+ low itself, so no need to do it here.
 *
 *
 * DO NOT REMOVE THIS, and ensure the "bootmagic" feature is ENABLED.
 * Without these, a buggy firmware will effectively brick your keypad.
 */
void bootloader_jump(void) {
    *((volatile uint32_t *)0x20004000) = 0x544F4F42;  /* "BOOT" — DAPBoot DFU magic */
    NVIC_SystemReset();
}
