/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bootloader.h"

#include <ch.h>
#include "wait.h"
#include "annepro2_ble.h"
#include "ap2_led.h"

#define RAM_MAGIC_LOCATION 0x20001ffc
#define IAP_MAGIC_VALUE 0x0000fab2

__attribute__((weak)) void bootloader_jump(void) {
    // Send msg to shine to boot into IAP
    annepro2SetIAP();

    // wait for shine to boot into IAP
    wait_ms(15);

    // Load ble into IAP
    annepro2_ble_bootload();
    wait_ms(15);

    // Magic key to set keyboard to IAP
    // It’s from reversing original boot loader
    // If value is that it stays in boot loader aka IAP
    *((uint32_t *)RAM_MAGIC_LOCATION) = IAP_MAGIC_VALUE;

    // Load the main MCU into IAP
    __disable_irq();
    NVIC_SystemReset();
}
