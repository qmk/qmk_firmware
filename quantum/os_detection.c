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

#ifdef OS_DETECTION_ENABLE

#    include <string.h>
#    include "timer.h"

#    ifdef OS_DETECTION_DEBUG_ENABLE
#        include "eeconfig.h"
#        include "eeprom.h"
#        include "print.h"

#        define STORED_USB_SETUPS 50
#        define EEPROM_USER_OFFSET (uint8_t*)EECONFIG_SIZE

static uint16_t usb_setups[STORED_USB_SETUPS];
#    endif

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

#    ifndef OS_DETECTION_DEBOUNCE
#        define OS_DETECTION_DEBOUNCE 100
#    endif

// 5s should always be more than enough
#    if OS_DETECTION_DEBOUNCE > 5000
#        undef OS_DETECTION_DEBOUNCE
#        define OS_DETECTION_DEBOUNCE 5000
#    endif

#    define OS_DETECTION_DEBOUNCE_ELAPSED 0

typedef uint16_t debounce_counter_t;

static volatile os_variant_t detected_os = OS_UNSURE;
static os_variant_t          reported_os = OS_UNSURE;

// we need to be able to report OS_UNSURE if that is the stable result of the guesses
static bool first_report = true;

// the OS detection might be unstable for a while, "debounce" it
static volatile debounce_counter_t debounce_counter = OS_DETECTION_DEBOUNCE_ELAPSED;
static volatile fast_timer_t       last_time;

void os_detection_task(void) {
    if (debounce_counter != OS_DETECTION_DEBOUNCE_ELAPSED) {
        if (debounce_counter <= timer_elapsed_fast(last_time)) {
            debounce_counter = OS_DETECTION_DEBOUNCE_ELAPSED;
            if (detected_os != reported_os || first_report) {
                process_detected_host_os(detected_os);
            }
        }
    }
}

void process_detected_host_os(os_variant_t os) {
    first_report = false;
    reported_os  = os;
    process_detected_host_os_kb(os);
}

__attribute__((weak)) bool process_detected_host_os_kb(os_variant_t os) {
    return process_detected_host_os_user(os);
}

__attribute__((weak)) bool process_detected_host_os_user(os_variant_t os) {
    return true;
}

// Some collected sequences of wLength can be found in tests.
void make_guess(void) {
    os_variant_t guessed = OS_UNSURE;
    if (setups_data.count >= 3) {
        if (setups_data.cnt_ff >= 2 && setups_data.cnt_04 >= 1) {
            guessed = OS_WINDOWS;
        } else if (setups_data.count == setups_data.cnt_ff) {
            // Linux has 3 packets with 0xFF.
            guessed = OS_LINUX;
        } else if (setups_data.count == 5 && setups_data.last_wlength == 0xFF && setups_data.cnt_ff == 1 && setups_data.cnt_02 == 2) {
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
    // whatever the result, debounce
    debounce_counter = OS_DETECTION_DEBOUNCE;
    detected_os      = guessed;
    last_time        = timer_read_fast();
}

void process_wlength(const uint16_t w_length) {
#    ifdef OS_DETECTION_DEBUG_ENABLE
    usb_setups[setups_data.count] = w_length;
#    endif
    setups_data.count++;
    setups_data.last_wlength = w_length;
    if (w_length == 0x2) {
        setups_data.cnt_02++;
    } else if (w_length == 0x4) {
        setups_data.cnt_04++;
    } else if (w_length == 0xFF) {
        setups_data.cnt_ff++;
    }
    make_guess();
}

os_variant_t detected_host_os(void) {
    return detected_os;
}

void erase_wlength_data(void) {
    memset(&setups_data, 0, sizeof(setups_data));
    detected_os      = OS_UNSURE;
    reported_os      = OS_UNSURE;
    debounce_counter = OS_DETECTION_DEBOUNCE_ELAPSED;
    first_report     = true;
}

#    if defined(SPLIT_KEYBOARD) && defined(SPLIT_DETECTED_OS_ENABLE)
void slave_update_detected_host_os(os_variant_t os) {
    detected_os = os;
}
#    endif

#    ifdef OS_DETECTION_DEBUG_ENABLE
void print_stored_setups(void) {
#        ifdef CONSOLE_ENABLE
    uint8_t cnt = eeprom_read_byte(EEPROM_USER_OFFSET);
    for (uint16_t i = 0; i < cnt; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        xprintf("i: %d, wLength: 0x%02X\n", i, eeprom_read_word(addr));
    }
#        endif
}

void store_setups_in_eeprom(void) {
    eeprom_update_byte(EEPROM_USER_OFFSET, setups_data.count);
    for (uint16_t i = 0; i < setups_data.count; ++i) {
        uint16_t* addr = (uint16_t*)EEPROM_USER_OFFSET + i * sizeof(uint16_t) + sizeof(uint8_t);
        eeprom_update_word(addr, usb_setups[i]);
    }
}

#    endif // OS_DETECTION_DEBUG_ENABLE

#endif
