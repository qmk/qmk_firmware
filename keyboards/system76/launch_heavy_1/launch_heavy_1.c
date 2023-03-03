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

#include "launch_heavy_1.h"

#include "usb_mux.h"

#define GPIO_MASK_RESET_USB (1<<3)
#define __ NO_LED

// clang-format off
#ifdef RGB_MATRIX_ENABLE
// LEDs by index
//    0   1   2   3   4   5   6   7   8   9
// 000 LM4 LL4 LK4 LJ4 LI4 LH4 LG4 LF4 LE4 LD4
// 010 LC4 LB4 LA4 LA5 LB5 LC5 LD5 LE5 LG5 LH5
// 020 LI5 LJ5 LK5 LL5 LM5 LO3 LM3 LL3 LK3 LJ3
// 030 LI3 LH3 LG3 LF3 LE3 LD3 LC3 LB3 LA3 LA2
// 040 LB2 LC2 LD2 LE2 LF2 LG2 LH2 LI2 LJ2 LK2
// 050 LL2 LM2 LN2 LO2 LO1 LN1 LM1 LL1 LK1 LJ1
// 060 LI1 LH1 LG1 LF1 LE1 LD1 LC1 LB1 LA1 LA0
// 070 LB0 LC0 LD0 LE0 LF0 LG0 LH0 LI0 LJ0 LK0
// 080 LL0 LM0 LN0 LO0 LD4 LC5 LA5 LA4 LB4 LC4
// 090 LC3 LB3 LA3 LA2 LB2 LC2 LD2 LD1 LC1 LB1
// 100 LA1 LA0 LB0 LC0 LD0
led_config_t g_led_config = { {
    // Key matrix to LED index (HEAVY)
/*      A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   */
/* 0    69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,101,102,103,104, */
/* 1    68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54,100, 99, 98, 97, */
/* 2    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 93, 94, 95, 96, */
/* 3    38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,     25, 92, 91, 90,     */
/* 4    12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,      0,     87, 88, 89, 84, */
/* 5    13, 14, 15, 16, 17,     18,     19, 20, 21,     22, 23, 24, 86,     85      */
    { 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82},
    { 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55},
    { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52},
    { 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25},
    { 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 87},
    { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 86, 85},
    { __, __, __,104,103,102, __, __, __, __, __, __,101, __},
    { __, __, __, 97, 98, 99, __, __, __, __, __, __,100, __},
    { __, __, __, 96, 95, 94, __, __, __, __, __, __, 93, __},
    { __, __, __, __, 90, 91, __, __, __, __, __, __, 92, __},
    { __, __, __, 84, 89, 88, __, __, __, __, __, __, 87, __},
    { __, __, __, __, 85, __, __, __, __, __, __, __, 86, __}
}, {
    // LED index to physical position (this is a pain, see qmk.sh in launch repo)
/* 000 */ {169, 40}, {157, 40}, {144, 40}, {134, 40}, {125, 40}, {115, 40}, {105, 40}, {95, 40}, {85, 40}, {75, 40},
/* 010 */ {65, 40}, {55, 40}, {40, 40}, {37, 50}, {50, 50}, {60, 50}, {70, 50}, {85, 50}, {105, 50}, {120, 50},
/* 020 */ {129, 50}, {142, 50}, {159, 50}, {169, 50}, {179, 50}, {179, 30}, {162, 30}, {149, 30}, {139, 30}, {129, 30},
/* 030 */ {120, 30}, {110, 30}, {100, 30}, {90, 30}, {80, 30}, {70, 30}, {60, 30}, {50, 30}, {37, 30}, {35, 20},
/* 040 */ {47, 20}, {57, 20}, {67, 20}, {77, 20}, {87, 20}, {97, 20}, {107, 20}, {117, 20}, {127, 20}, {137, 20},
/* 050 */ {147, 20}, {157, 20}, {167, 20}, {179, 20}, {179, 10}, {164, 10}, {152, 10}, {142, 10}, {132, 10}, {122, 10},
/* 060 */ {112, 10}, {102, 10}, {92, 10}, {82, 10}, {72, 10}, {62, 10}, {52, 10}, {42, 10}, {32, 10}, {32, 0},
/* 070 */ {42, 0}, {52, 0}, {62, 0}, {72, 0}, {82, 0}, {92, 0}, {102, 0}, {112, 0}, {122, 0}, {132, 0},
/* 080 */ {142, 0}, {152, 0}, {164, 0}, {179, 0}, {224, 45}, {214, 50}, {199, 50}, {194, 40}, {204, 40}, {214, 40},
/* 090 */ {214, 30}, {204, 30}, {194, 30}, {194, 20}, {204, 20}, {214, 20}, {224, 25}, {224, 10}, {214, 10}, {204, 10},
/* 100 */ {194, 10}, {194, 0}, {204, 0}, {214, 0}, {224, 0}
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
/* 80 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/* 90 */ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
/*100 */ 4, 4, 4, 4, 4
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

rgb_config_t layer_rgb[DYNAMIC_KEYMAP_LAYER_COUNT];

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
}

void matrix_scan_kb(void) {
    usb_mux_event();

    matrix_scan_user();
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
        case RGB_VAD:
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
        case RGB_VAI:
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
        case RGB_TOG:
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
void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
}
#endif  // CONSOLE_ENABLE

void bootloader_jump(void) {

    // Disable all peripherals on AT90USB646
    UDCON = 1;
    USBCON = (1<<FRZCLK);  // disable USB
    UCSR1B = 0;
    _delay_ms(5);

    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    ADCSRA = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    TIMSK2 = 0;
    TIMSK3 = 0;
    UCSR1B = 0;
    TWCR   = 0;
    DDRA   = GPIO_MASK_RESET_USB;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    DDRE   = 0;
    DDRF   = 0;
    PORTA  = GPIO_MASK_RESET_USB;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    PORTE  = 0;
    PORTF  = 0;

    // finally, jump to bootloader
    asm volatile("jmp 0xFC00");
}
