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
#ifdef OS_DETECTION_KEYBOARD_RESET
#    include "quantum.h"
#endif

#ifdef OS_DETECTION_DEBUG_ENABLE
#    include "nvm_eeprom_eeconfig_internal.h"
#    include "eeprom.h"
#    include "print.h"

#    define STORED_USB_SETUPS 50
#    define EEPROM_USER_OFFSET (uint8_t*)EECONFIG_SIZE

static uint16_t usb_setups[STORED_USB_SETUPS];
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
static volatile struct usb_device_state maxprev_usb_device_state = {.configure_state = USB_DEVICE_STATE_NO_INIT};

// to reset the keyboard on USB state change
#ifdef OS_DETECTION_KEYBOARD_RESET
#    ifndef OS_DETECTION_RESET_DEBOUNCE
#        define OS_DETECTION_RESET_DEBOUNCE OS_DETECTION_DEBOUNCE
#    endif
static volatile fast_timer_t configured_since = 0;
static volatile bool         reset_pending    = false;
#endif

// the OS detection might be unstable for a while, "debounce" it
static volatile bool         debouncing = false;
static volatile fast_timer_t last_time  = 0;

bool process_detected_host_os_modules(os_variant_t os);

void os_detection_task(void) {
#ifdef OS_DETECTION_KEYBOARD_RESET
    // resetting the keyboard on the USB device state change callback results in instability, so delegate that to this task
    if (reset_pending) {
        soft_reset_keyboard();
    }
    // reset the keyboard if it is stuck in the init state for longer than debounce duration, which can happen with some KVMs
    if (current_usb_device_state.configure_state <= USB_DEVICE_STATE_INIT && maxprev_usb_device_state.configure_state >= USB_DEVICE_STATE_CONFIGURED) {
        if (debouncing && timer_elapsed_fast(last_time) >= OS_DETECTION_DEBOUNCE) {
            soft_reset_keyboard();
        }
        return;
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
#ifdef OS_DETECTION_DEBUG_ENABLE
    usb_setups[setups_data.count] = w_length;
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
        if (setups_data.cnt_ff >= 2 && setups_data.cnt_04 >= 1) {
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
    return detected_os;
}

void erase_wlength_data(void) {
    memset(&setups_data, 0, sizeof(setups_data));
    detected_os                              = OS_UNSURE;
    reported_os                              = OS_UNSURE;
    current_usb_device_state.configure_state = USB_DEVICE_STATE_NO_INIT;
    maxprev_usb_device_state.configure_state = USB_DEVICE_STATE_NO_INIT;
    debouncing                               = false;
    last_time                                = 0;
    first_report                             = true;
}

void os_detection_notify_usb_device_state_change(struct usb_device_state usb_device_state) {
    // treat this like any other source of instability
    if (maxprev_usb_device_state.configure_state < current_usb_device_state.configure_state) {
        maxprev_usb_device_state.configure_state = current_usb_device_state.configure_state;
    }
    current_usb_device_state = usb_device_state;
    last_time                = timer_read_fast();
    debouncing               = true;

#ifdef OS_DETECTION_KEYBOARD_RESET
    if (configured_since == 0 && current_usb_device_state.configure_state == USB_DEVICE_STATE_CONFIGURED) {
        configured_since = timer_read_fast();
    } else if (current_usb_device_state.configure_state == USB_DEVICE_STATE_INIT) {
        // reset the keyboard only if it's been stable for at least debounce duration, to avoid issues with some KVMs
        if (configured_since > 0 && timer_elapsed_fast(configured_since) >= OS_DETECTION_RESET_DEBOUNCE) {
            reset_pending = true;
        }
        configured_since = 0;
    }
#endif
}

#if defined(SPLIT_KEYBOARD) && defined(SPLIT_DETECTED_OS_ENABLE)
void slave_update_detected_host_os(os_variant_t os) {
    detected_os = os;
    last_time   = timer_read_fast();
    debouncing  = true;
}
#endif

#ifdef OS_DETECTION_DEBUG_ENABLE
void print_stored_setups(void) {
#    ifdef CONSOLE_ENABLE
    uint8_t cnt = eeprom_read_byte(EEPROM_USER_OFFSET);
    for (uint16_t i = 0; i < cnt; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        xprintf("i: %d, wLength: 0x%02X\n", i, eeprom_read_word(addr));
    }
#    endif
}

void store_setups_in_eeprom(void) {
    eeprom_update_byte(EEPROM_USER_OFFSET, setups_data.count);
    for (uint16_t i = 0; i < setups_data.count; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        eeprom_update_word(addr, usb_setups[i]);
    }
}

#endif // OS_DETECTION_DEBUG_ENABLE
