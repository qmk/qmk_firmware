/*
 *  Copyright (C) 2021  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "eeprom.h"

#include "usb_mux.h"

// clang-format off
bool eeprom_is_valid(void) {
    return (
        eeprom_read_word(((void *)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
        eeprom_read_byte(((void *)EEPROM_VERSION_ADDR)) == EEPROM_VERSION
    );
}
// clang-format on

void eeprom_set_valid(bool valid) {
    eeprom_update_word(((void *)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
    eeprom_update_byte(((void *)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}

void bootmagic_lite_reset_eeprom(void) {
    // Set the keyboard-specific EEPROM state as invalid
    eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid
    eeconfig_disable();
}

// The lite version of TMK's bootmagic based on Wilba.
// 100% less potential for accidentally making the keyboard do stupid things.
void bootmagic_lite(void) {
    // Perform multiple scans because debouncing can't be turned off.
    matrix_scan();
#if defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();

    // If the configured key (commonly Esc) is held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    uint8_t row = 0;  // BOOTMAGIC_LITE_ROW;
    uint8_t col = 0;  // BOOTMAGIC_LITE_COLUMN;

    if (matrix_get_row(row) & (1 << col)) {
        bootmagic_lite_reset_eeprom();

        // Jump to bootloader.
        bootloader_jump();
    }
}

void system76_ec_rgb_eeprom(bool write);
void system76_ec_rgb_layer(layer_state_t layer_state);
void system76_ec_unlock(void);
bool system76_ec_is_unlocked(void);

extern rgb_config_t layer_rgb[DYNAMIC_KEYMAP_LAYER_COUNT];

void matrix_init_kb(void) {
    usb_mux_init();

    bootmagic_lite();
    if (!eeprom_is_valid()) {
        dynamic_keymap_reset();
        dynamic_keymap_macro_reset();
        system76_ec_rgb_eeprom(true);
        eeprom_set_valid(true);
    } else {
        system76_ec_rgb_eeprom(false);
    }

    system76_ec_rgb_layer(layer_state);

    matrix_init_user();
}

void housekeeping_task_kb(void) {
    usb_mux_event();
}

#define LEVEL(value) (uint8_t)(((uint16_t)value) * ((uint16_t)RGB_MATRIX_MAXIMUM_BRIGHTNESS) / ((uint16_t)255))

// clang-format off
static const uint8_t levels[] = {
    LEVEL(48),
    LEVEL(72),
    LEVEL(96),
    LEVEL(144),
    LEVEL(192),
    LEVEL(255)
};
// clang-format on

static uint8_t toggle_level = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
extern bool    input_disabled;

static void set_value_all_layers(uint8_t value) {
    if (!system76_ec_is_unlocked()) {
        for (int8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
            layer_rgb[layer].hsv.v = value;
        }
        system76_ec_rgb_layer(layer_state);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (input_disabled) {
        return false;
    }

    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case QK_BOOT:
            if (record->event.pressed) {
                system76_ec_unlock();
            }
#ifdef SYSTEM76_EC
            return false;
#else
            return true;
#endif
        case QK_RGB_MATRIX_VALUE_DOWN:
            if (record->event.pressed) {
                uint8_t level = rgb_matrix_config.hsv.v;
                for (int i = sizeof(levels) - 1; i >= 0; i--) {
                    if (levels[i] < level) {
                        level = levels[i];
                        break;
                    }
                }
                set_value_all_layers(level);
            }
            return false;
        case QK_RGB_MATRIX_VALUE_UP:
            if (record->event.pressed) {
                uint8_t level = rgb_matrix_config.hsv.v;
                for (int i = 0; i < sizeof(levels); i++) {
                    if (levels[i] > level) {
                        level = levels[i];
                        break;
                    }
                }
                set_value_all_layers(level);
            }
            return false;
        case QK_RGB_MATRIX_TOGGLE:
            if (record->event.pressed) {
                uint8_t level = 0;
                if (rgb_matrix_config.hsv.v == 0) {
                    level = toggle_level;
                } else {
                    toggle_level = rgb_matrix_config.hsv.v;
                }
                set_value_all_layers(level);
            }
            return false;
    }

    return true;
}

layer_state_t layer_state_set_kb(layer_state_t layer_state) {
    system76_ec_rgb_layer(layer_state);

    return layer_state_set_user(layer_state);
}

#ifdef CONSOLE_ENABLE
void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;

    keyboard_post_init_user();
}
#endif  // CONSOLE_ENABLE
