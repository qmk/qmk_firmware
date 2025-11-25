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
#ifdef RGB_MATRIX_ENABLE
// LEDs by index
//    0   1   2   3   4   5   6   7   8   9
// 00 LM4 LL4 LK4 LJ4 LI4 LH4 LG4 LF4 LE4 LD4
// 10 LC4 LB4 LA4 LA5 LB5 LC5 LD5 LE5 LG5 LH5
// 20 LI5 LJ5 LK5 LL5 LM5 LO3 LM3 LL3 LK3 LJ3
// 30 LI3 LH3 LG3 LF3 LE3 LD3 LC3 LB3 LA3 LA2
// 40 LB2 LC2 LD2 LE2 LF2 LG2 LH2 LI2 LJ2 LK2
// 50 LL2 LM2 LN2 LO2 LO1 LN1 LM1 LL1 LK1 LJ1
// 60 LI1 LH1 LG1 LF1 LE1 LD1 LC1 LB1 LA1 LA0
// 70 LB0 LC0 LD0 LE0 LF0 LG0 LH0 LI0 LJ0 LK0
// 80 LL0 LM0 LN0 LO0
led_config_t g_led_config = { {
    // Key matrix to LED index
/*    A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   */
/* 0  69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, */
/* 1  68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, */
/* 2  39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, */
/* 3  38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,     25, */
/* 4  12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,      0,     */
/* 5  13, 14, 15, 16, 17,     18,      19, 20, 21,    22, 23, 24  */
    { 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82 },
    { 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55 },
    { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
    { 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 83 },
    { 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 54 },
    { 13, 14, 15, 16, 17, 25, 18, 19, 20, 21, 22, 23, 24, 53 },
}, {
    // LED index to physical position (see leds.sh in `launch' repo)
/* 00 */ {209, 51}, {190, 51}, {171, 51}, {156, 51}, {140, 51}, {125, 51}, {110, 51}, {95, 51}, {80, 51}, {65, 51},
/* 10 */ {49, 51}, {34, 51}, {11, 51}, {8, 64}, {27, 64}, {42, 64}, {57, 64}, {80, 64}, {110, 64}, {133, 64},
/* 20 */ {148, 64}, {167, 64}, {194, 64}, {209, 64}, {224, 64}, {224, 38}, {197, 38}, {178, 38}, {163, 38}, {148, 38},
/* 30 */ {133, 38}, {118, 38}, {103, 38}, {87, 38}, {72, 38}, {57, 38}, {42, 38}, {27, 38}, {8, 38}, {4, 26},
/* 40 */ {23, 26}, {38, 26}, {53, 26}, {68, 26}, {84, 26}, {99, 26}, {114, 26}, {129, 26}, {144, 26}, {159, 26},
/* 50 */ {175, 26}, {190, 26}, {205, 26}, {224, 26}, {224, 13}, {201, 13}, {182, 13}, {167, 13}, {152, 13}, {137, 13},
/* 60 */ {121, 13}, {106, 13}, {91, 13}, {76, 13}, {61, 13}, {46, 13}, {30, 13}, {15, 13}, {0, 13}, {0, 0},
/* 70 */ {15, 0}, {30, 0}, {46, 0}, {61, 0}, {76, 0}, {91, 0}, {106, 0}, {121, 0}, {137, 0}, {152, 0},
/* 80 */ {167, 0}, {182, 0}, {201, 0}, {224, 0}
}, {
    // LED index to flags (set all to LED_FLAG_KEYLIGHT)
    /*   0  1  2  3  4  5  6  7  8  9 */
/* 00 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 10 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 20 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 30 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 40 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 50 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 60 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 70 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 80 */ 4, 4, 4, 4
} };
#endif // RGB_MATRIX_ENABLE

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
