/* Copyright 2022 Ruslan Sayfutdinov (@KapJI)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "usb_device_state.h"

#ifndef OS_DETECTION_SKIP_RESET_KEY
#    define OS_DETECTION_SKIP_RESET_KEY QK_OS_DETECTION_SKIP_RESET
#endif

typedef enum {
    OS_UNSURE,
    OS_LINUX,
    OS_WINDOWS,
    OS_MACOS,
    OS_IOS,
} os_variant_t;

void         process_wlength(const uint16_t w_length);
os_variant_t detected_host_os(void);
void         erase_wlength_data(void);
void         os_detection_notify_usb_device_state_change(struct usb_device_state usb_device_state);
#ifdef OS_DETECTION_KEYBOARD_RESET
void os_detection_notify_usb_descriptor_request(void);
#endif

// Call after EEPROM initialization to reset volatile state and load the reboot guard.
void os_detection_init(void);

void os_detection_task(void);
bool os_detection_toggle(void);

bool process_detected_host_os_kb(os_variant_t os);
bool process_detected_host_os_user(os_variant_t os);

#if defined(SPLIT_KEYBOARD) && defined(SPLIT_DETECTED_OS_ENABLE)
void slave_update_detected_host_os(os_variant_t os);
#endif

#ifdef OS_DETECTION_DEBUG_ENABLE
#    define OS_DETECTION_DEBUG_EEPROM_SIZE 104
#    if (defined(DYNAMIC_KEYMAP_ENABLE) || defined(VIA_ENABLE)) && !defined(OS_DETECTION_DEBUG_EEPROM_ADDR)
#        error OS Detection debug with DYNAMIC_KEYMAP or VIA requires a reserved OS_DETECTION_DEBUG_EEPROM_ADDR
#    endif
#    ifndef OS_DETECTION_DEBUG_EEPROM_ADDR
#        define OS_DETECTION_DEBUG_EEPROM_ADDR EECONFIG_SIZE
#    endif
void print_stored_setups(void);
void store_setups_in_eeprom(void);
void clear_stored_setups(void);
#endif

#ifdef OS_DETECTION_BOOT_LOOP_GUARD
#    ifndef OS_DETECTION_KEYBOARD_RESET
#        error OS Detection boot-loop guard requires OS_DETECTION_KEYBOARD_RESET
#    endif
#    define OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_SIZE 7
#    if (defined(DYNAMIC_KEYMAP_ENABLE) || defined(VIA_ENABLE)) && !defined(OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR)
#        error OS Detection boot-loop guard with DYNAMIC_KEYMAP or VIA requires a reserved OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR
#    endif
#    ifndef OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR
#        ifdef OS_DETECTION_DEBUG_ENABLE
#            define OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR (OS_DETECTION_DEBUG_EEPROM_ADDR + OS_DETECTION_DEBUG_EEPROM_SIZE)
#        else
#            define OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR EECONFIG_SIZE
#        endif
#    endif
#    ifndef OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS
#        define OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS 1000
#    endif
#    ifndef OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS
#        define OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS 3
#    endif
#    if OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS < 1 || OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS > 255
#        error OS Detection boot-loop guard reboot limit must be between 1 and 255
#    endif
#    ifndef OS_DETECTION_BOOT_LOOP_GUARD_REARM_MS
#        define OS_DETECTION_BOOT_LOOP_GUARD_REARM_MS 5000
#    endif
#endif
