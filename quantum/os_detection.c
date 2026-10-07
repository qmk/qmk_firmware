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

#include "os_detection.h"

#include <string.h>
#include "timer.h"
#include "keycode_config.h"
#include "eeconfig.h"
#ifdef OS_DETECTION_KEYBOARD_RESET
#    include "quantum.h"
#endif

#if defined(OS_DETECTION_DEBUG_ENABLE) || defined(OS_DETECTION_BOOT_LOOP_GUARD)
#    include "nvm_eeprom_eeconfig_internal.h"
#    include "eeprom.h"
#    ifdef VIA_ENABLE
#        include "via.h"
#        include "nvm_eeprom_via_internal.h"
#    endif
#endif

#ifdef OS_DETECTION_DEBUG_ENABLE
#    include "print.h"

#    define STORED_USB_SETUPS 50
#    define EEPROM_DEBUG_OFFSET ((uint8_t *)(uintptr_t)(OS_DETECTION_DEBUG_EEPROM_ADDR))
#    define EEPROM_DEBUG_MAGIC 0x4F53

enum {
    OS_DETECTION_DEBUG_REASON_MANUAL,
    OS_DETECTION_DEBUG_REASON_USB_REINIT,
};

// Packed EEPROM layout: uint16_t magic, uint8_t count, uint8_t reason, 50 uint16_t lengths.
STATIC_ASSERT(OS_DETECTION_DEBUG_EEPROM_SIZE == 4 + STORED_USB_SETUPS * sizeof(uint16_t), "OS detection debug EEPROM size is incorrect");
STATIC_ASSERT(OS_DETECTION_DEBUG_EEPROM_SIZE <= TOTAL_EEPROM_BYTE_COUNT && OS_DETECTION_DEBUG_EEPROM_ADDR >= EECONFIG_SIZE && OS_DETECTION_DEBUG_EEPROM_ADDR <= TOTAL_EEPROM_BYTE_COUNT - OS_DETECTION_DEBUG_EEPROM_SIZE, "OS detection debug must fit after core EEPROM settings");
static uint16_t         usb_setups[STORED_USB_SETUPS];
static volatile uint8_t usb_setup_count;
#    if defined(OS_DETECTION_DEBUG_AUTO_STORE) && defined(OS_DETECTION_KEYBOARD_RESET)
static bool stored_setups_valid(void);
static void store_setups(uint8_t reason);
#    endif
#endif

#ifdef OS_DETECTION_BOOT_LOOP_GUARD
#    define EEPROM_GUARD_OFFSET ((uint8_t *)(uintptr_t)(OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR))
#    define EEPROM_GUARD_MAGIC 0x4F47
// Packed EEPROM layout: uint16_t magic, uint8_t count, uint32_t reboot-request uptime.
STATIC_ASSERT(OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_SIZE <= TOTAL_EEPROM_BYTE_COUNT && OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR >= EECONFIG_SIZE && OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR <= TOTAL_EEPROM_BYTE_COUNT - OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_SIZE, "OS detection boot-loop guard must fit after core EEPROM settings");
#    ifdef OS_DETECTION_DEBUG_ENABLE
STATIC_ASSERT(OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR >= OS_DETECTION_DEBUG_EEPROM_ADDR + OS_DETECTION_DEBUG_EEPROM_SIZE || OS_DETECTION_DEBUG_EEPROM_ADDR >= OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR + OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_SIZE, "OS detection boot-loop guard overlaps debug snapshot");
#    endif
static uint8_t           boot_loop_count;
static uint32_t          last_reboot_uptime;
static volatile uint32_t guard_configured_since;

static void store_boot_loop_guard(void) {
    // Commit magic last, matching the diagnostic snapshot's interrupted-write protection.
    eeprom_update_word((uint16_t *)EEPROM_GUARD_OFFSET, 0);
    eeprom_update_byte(EEPROM_GUARD_OFFSET + 2, boot_loop_count);
    eeprom_update_dword((uint32_t *)(EEPROM_GUARD_OFFSET + 3), last_reboot_uptime);
    eeprom_update_word((uint16_t *)EEPROM_GUARD_OFFSET, EEPROM_GUARD_MAGIC);
}
#endif

#ifndef OS_DETECTION_DEBOUNCE
#    define OS_DETECTION_DEBOUNCE 250
#endif

// 2s should always be more than enough (otherwise, you may have other issues)
#if OS_DETECTION_DEBOUNCE > 2000
#    undef OS_DETECTION_DEBOUNCE
#    define OS_DETECTION_DEBOUNCE 2000
#endif

struct setups_data_t {
    uint8_t  count;
    uint8_t  cnt_02;
    uint8_t  cnt_04;
    uint8_t  cnt_ff;
    uint16_t last_wlength;
};

struct setups_data_t setups_data = {
    .count  = 0,
    .cnt_02 = 0,
    .cnt_04 = 0,
    .cnt_ff = 0,
};

static volatile os_variant_t detected_os = OS_UNSURE;
static volatile os_variant_t reported_os = OS_UNSURE;

// we need to be able to report OS_UNSURE if that is the stable result of the guesses
static volatile bool first_report = true;

// to react on USB state changes
static volatile struct usb_device_state current_usb_device_state = {.configure_state = USB_DEVICE_STATE_NO_INIT};

// to reset the keyboard on USB state change
#ifdef OS_DETECTION_KEYBOARD_RESET
#    ifndef OS_DETECTION_RESET_DEBOUNCE
#        define OS_DETECTION_RESET_DEBOUNCE OS_DETECTION_DEBOUNCE
#    endif
// Armed by a stable configured REPORT session, even without an OS fingerprint.
static volatile bool reset_eligible = false;
static volatile bool reset_pending  = false;
#endif

// the OS detection might be unstable for a while, "debounce" it
static volatile bool         debouncing = false;
static volatile fast_timer_t last_time  = 0;

bool process_detected_host_os_modules(os_variant_t os);

#ifdef OS_DETECTION_KEYBOARD_RESET
static bool os_detection_skip_reset_held(void) {
    layer_state_t held_layers = 0;
#    ifndef NO_ACTION_LAYER
    // Account for a held MO(Fn) even when key events cannot yet be processed.
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (!matrix_is_on(row, col)) {
                continue;
            }
            keypos_t key     = {.row = row, .col = col};
            uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(key), key);
            if (keycode >= QK_MOMENTARY && keycode <= QK_MOMENTARY_MAX && QK_MOMENTARY_GET_LAYER(keycode) < MAX_LAYER) {
                held_layers |= (layer_state_t)1 << QK_MOMENTARY_GET_LAYER(keycode);
            }
        }
    }
#    endif
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            if (!matrix_is_on(row, col)) {
                continue;
            }
            keypos_t key   = {.row = row, .col = col};
            uint8_t  layer = layer_switch_get_layer(key);
            // Existing active/default layers take precedence over lower held layers.
            for (int8_t i = MAX_LAYER - 1; i > layer; --i) {
                if ((held_layers & ((layer_state_t)1 << i)) && action_for_key(i, key).code != ACTION_TRANSPARENT) {
                    layer = i;
                    break;
                }
            }
            uint16_t keycode = keymap_key_to_keycode(layer, key);
            if (keycode == OS_DETECTION_SKIP_RESET_KEY || keycode == QK_OS_DETECTION_TOGGLE) {
                return true;
            }
        }
    }
    return false;
}
#endif

void os_detection_task(void) {
    if (keymap_config.os_detection_disabled) {
        return;
    }
#ifdef OS_DETECTION_BOOT_LOOP_GUARD
    if (boot_loop_count > 0 && current_usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED && timer_elapsed32(guard_configured_since) >= OS_DETECTION_BOOT_LOOP_GUARD_REARM_MS) {
        boot_loop_count = 0;
        store_boot_loop_guard();
    }
#endif
#ifdef OS_DETECTION_KEYBOARD_RESET
    // Re-enumerate only from task context, after descriptor/state activity settles.
    if (reset_eligible && reset_pending) {
        if (os_detection_skip_reset_held()) {
            reset_pending  = false;
            reset_eligible = false;
            // Keep the OS-report debounce; forget reset history so release cannot trigger a stale reset.
        } else if (debouncing && timer_elapsed_fast(last_time) >= OS_DETECTION_RESET_DEBOUNCE) {
#    ifdef OS_DETECTION_BOOT_LOOP_GUARD
            if (boot_loop_count >= OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS) {
                reset_pending  = false;
                reset_eligible = false;
                return;
            }
#    endif
#    if defined(OS_DETECTION_DEBUG_ENABLE) && defined(OS_DETECTION_DEBUG_AUTO_STORE)
            if (!stored_setups_valid()) {
                store_setups(OS_DETECTION_DEBUG_REASON_USB_REINIT);
            }
#    endif
            // USB callbacks can cancel or postpone the reset while EEPROM is being written.
            if (!reset_eligible || timer_elapsed_fast(last_time) < OS_DETECTION_RESET_DEBOUNCE) {
                return;
            }
#    ifdef OS_DETECTION_BOOT_LOOP_GUARD
            last_reboot_uptime = timer_read32();
            boot_loop_count    = last_reboot_uptime < OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS ? boot_loop_count + 1 : 0;
            store_boot_loop_guard();
#    endif
            reset_pending  = false;
            reset_eligible = false;
            soft_reset_keyboard();
            return;
        }
    }
    // Do not let OS reporting consume the quiet-period timer while a reset is queued.
    if (reset_pending) {
        return;
    }
    if (current_usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED && current_usb_device_state.protocol == USB_PROTOCOL_REPORT && debouncing && timer_elapsed_fast(last_time) >= OS_DETECTION_DEBOUNCE) {
        reset_eligible = true;
    }
#endif
#ifdef OS_DETECTION_SINGLE_REPORT
    if (!first_report) {
        return;
    }
#endif
    if (current_usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED) {
        // debouncing goes for both the detected OS as well as the USB state
        if (debouncing && timer_elapsed_fast(last_time) >= OS_DETECTION_DEBOUNCE) {
#ifdef OS_DETECTION_KEYBOARD_RESET
            if (os_detection_skip_reset_held()) {
                reset_pending  = false;
                reset_eligible = false;
                // Keep the fingerprint ready to report after the temporary bypass is released.
                return;
            }
#endif
            debouncing = false;
            last_time  = 0;
            if (detected_os != reported_os || first_report) {
                first_report = false;
                reported_os  = detected_os;
                process_detected_host_os_modules(detected_os);
                process_detected_host_os_kb(detected_os);
            }
        }
    }
}

__attribute__((weak)) bool process_detected_host_os_modules(os_variant_t os) {
    return true;
}

__attribute__((weak)) bool process_detected_host_os_kb(os_variant_t detected_os) {
    return process_detected_host_os_user(detected_os);
}

__attribute__((weak)) bool process_detected_host_os_user(os_variant_t detected_os) {
    return true;
}

// Some collected sequences of wLength can be found in tests.
void process_wlength(const uint16_t w_length) {
    if (keymap_config.os_detection_disabled) {
        return;
    }
#ifdef OS_DETECTION_DEBUG_ENABLE
    if (usb_setup_count < STORED_USB_SETUPS) {
        usb_setups[usb_setup_count] = w_length;
        usb_setup_count++;
    }
#endif
    setups_data.count++;
    setups_data.last_wlength = w_length;
    if (w_length == 0x2) {
        setups_data.cnt_02++;
    } else if (w_length == 0x4) {
        setups_data.cnt_04++;
    } else if (w_length == 0xFF) {
        setups_data.cnt_ff++;
    }

    // now try to make a guess
    os_variant_t guessed = OS_UNSURE;
    if (setups_data.count >= 3) {
        if (setups_data.cnt_ff >= 2 && setups_data.cnt_04 >= 1 && setups_data.cnt_02 < 2) {
            guessed = OS_WINDOWS;
        } else if (setups_data.count == setups_data.cnt_ff) {
            // Linux has 3 packets with 0xFF.
            guessed = OS_LINUX;
        } else if (setups_data.count >= 5 && setups_data.last_wlength == 0xFF && setups_data.cnt_ff >= 1 && setups_data.cnt_02 >= 2) {
            guessed = OS_MACOS;
        } else if (setups_data.count == 4 && setups_data.cnt_ff == 0 && setups_data.cnt_02 == 2) {
            // iOS and iPadOS don't have the last 0xFF packet.
            guessed = OS_IOS;
        } else if (setups_data.cnt_ff == 0 && setups_data.cnt_02 == 3 && setups_data.cnt_04 == 1) {
            // This is actually PS5.
            guessed = OS_LINUX;
        } else if (setups_data.cnt_ff >= 1 && setups_data.cnt_02 == 0 && setups_data.cnt_04 == 0) {
            // This is actually Quest 2 or Nintendo Switch.
            guessed = OS_LINUX;
        }
    }

    // only replace the guessed value if not unsure
    if (guessed != OS_UNSURE) {
        detected_os = guessed;
    }

    // whatever the result, debounce
    last_time  = timer_read_fast();
    debouncing = true;
}

os_variant_t detected_host_os(void) {
#ifdef SPLIT_KEYBOARD
    if (!is_keyboard_master()) {
        return detected_os;
    }
#endif
    return keymap_config.os_detection_disabled ? OS_UNSURE : detected_os;
}

void erase_wlength_data(void) {
#ifdef OS_DETECTION_BOOT_LOOP_GUARD
    guard_configured_since = 0;
#endif
    memset(&setups_data, 0, sizeof(setups_data));
#ifdef OS_DETECTION_DEBUG_ENABLE
    memset(usb_setups, 0, sizeof(usb_setups));
    usb_setup_count = 0;
#endif
#ifdef OS_DETECTION_KEYBOARD_RESET
    reset_eligible = false;
    reset_pending  = false;
#endif
    detected_os                              = OS_UNSURE;
    reported_os                              = OS_UNSURE;
    current_usb_device_state.configure_state = USB_DEVICE_STATE_NO_INIT;
    debouncing                               = false;
    last_time                                = 0;
    first_report                             = true;
}

void os_detection_init(void) {
    erase_wlength_data();
#ifdef OS_DETECTION_BOOT_LOOP_GUARD
    boot_loop_count    = 0;
    last_reboot_uptime = 0;
    if (eeprom_read_word((uint16_t *)EEPROM_GUARD_OFFSET) == EEPROM_GUARD_MAGIC) {
        boot_loop_count    = eeprom_read_byte(EEPROM_GUARD_OFFSET + 2);
        last_reboot_uptime = eeprom_read_dword((uint32_t *)(EEPROM_GUARD_OFFSET + 3));
    }
#endif
}

bool os_detection_toggle(void) {
    keymap_config.os_detection_disabled = !keymap_config.os_detection_disabled;
    eeconfig_update_keymap(&keymap_config);
    erase_wlength_data();
    return !keymap_config.os_detection_disabled;
}

void os_detection_notify_usb_device_state_change(struct usb_device_state usb_device_state) {
    if (keymap_config.os_detection_disabled) {
        return;
    }
#ifdef OS_DETECTION_BOOT_LOOP_GUARD
    if (usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED && current_usb_device_state.configure_state != USB_DEVICE_STATE_CONFIGURED) {
        guard_configured_since = timer_read32();
    }
#endif
    // treat this like any other source of instability
    current_usb_device_state = usb_device_state;
    last_time                = timer_read_fast();
    debouncing               = true;

#ifdef OS_DETECTION_KEYBOARD_RESET
    if (current_usb_device_state.protocol == USB_PROTOCOL_BOOT) {
        reset_eligible = false;
        reset_pending  = false;
    } else if (current_usb_device_state.configure_state == USB_DEVICE_STATE_INIT && reset_eligible) {
        // Eligibility comes from the previous stable host, not the new enumeration's REPORT default.
        reset_pending = true;
    }
#endif
}

#ifdef OS_DETECTION_KEYBOARD_RESET
void os_detection_notify_usb_descriptor_request(void) {
    if (!keymap_config.os_detection_disabled) {
        last_time  = timer_read_fast();
        debouncing = true;
    }
}
#endif

#if defined(SPLIT_KEYBOARD) && defined(SPLIT_DETECTED_OS_ENABLE)
void slave_update_detected_host_os(os_variant_t os) {
    detected_os = os;
    last_time   = timer_read_fast();
    debouncing  = true;
}
#endif

#ifdef OS_DETECTION_DEBUG_ENABLE
#    if defined(CONSOLE_ENABLE) || (defined(OS_DETECTION_DEBUG_AUTO_STORE) && defined(OS_DETECTION_KEYBOARD_RESET))
static bool stored_setups_valid(void) {
    return eeprom_read_word((uint16_t *)EEPROM_DEBUG_OFFSET) == EEPROM_DEBUG_MAGIC && eeprom_read_byte(EEPROM_DEBUG_OFFSET + 2) <= STORED_USB_SETUPS && eeprom_read_byte(EEPROM_DEBUG_OFFSET + 3) <= OS_DETECTION_DEBUG_REASON_USB_REINIT;
}
#    endif

void print_stored_setups(void) {
#    ifdef CONSOLE_ENABLE
#        ifdef OS_DETECTION_BOOT_LOOP_GUARD
    xprintf("OS detection reboot guard: %u/%u rapid resets, last request uptime: %lu ms\n", boot_loop_count, OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS, (unsigned long)last_reboot_uptime);
#        endif
    if (!stored_setups_valid()) {
        xprintf("No valid stored OS detection setups\n");
        return;
    }
    uint8_t cnt    = eeprom_read_byte(EEPROM_DEBUG_OFFSET + 2);
    uint8_t reason = eeprom_read_byte(EEPROM_DEBUG_OFFSET + 3);
    xprintf("OS detection snapshot: %u packets, reason: %s\n", cnt, reason == OS_DETECTION_DEBUG_REASON_USB_REINIT ? "USB reinit" : "manual");
    for (uint8_t i = 0; i < cnt; ++i) {
        const uint16_t *addr = (const uint16_t *)(EEPROM_DEBUG_OFFSET + 4 + i * sizeof(uint16_t));
        xprintf("i: %u, wLength: 0x%04X\n", i, eeprom_read_word(addr));
    }
#    endif
}

static void store_setups(uint8_t reason) {
    uint8_t count = usb_setup_count;
    // Commit magic last so an interrupted replacement cannot be mistaken for a complete snapshot.
    eeprom_update_word((uint16_t *)EEPROM_DEBUG_OFFSET, 0);
    eeprom_update_byte(EEPROM_DEBUG_OFFSET + 2, count);
    eeprom_update_byte(EEPROM_DEBUG_OFFSET + 3, reason);
    for (uint8_t i = 0; i < count; ++i) {
        uint16_t *addr = (uint16_t *)(EEPROM_DEBUG_OFFSET + 4 + i * sizeof(uint16_t));
        eeprom_update_word(addr, usb_setups[i]);
    }
    eeprom_update_word((uint16_t *)EEPROM_DEBUG_OFFSET, EEPROM_DEBUG_MAGIC);
}

void store_setups_in_eeprom(void) {
    store_setups(OS_DETECTION_DEBUG_REASON_MANUAL);
}

void clear_stored_setups(void) {
    eeprom_update_word((uint16_t *)EEPROM_DEBUG_OFFSET, 0);
}

#endif // OS_DETECTION_DEBUG_ENABLE
