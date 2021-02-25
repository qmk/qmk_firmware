#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"

#include "launch_1.h"
#include "usb_mux.h"
#include "rgb_matrix.h"

#if RGB_MATRIX_ENABLE
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
led_config_t g_led_config = { LAYOUT(
    // Key matrix to LED index
    /*  A   B   C   D   E   F   G   H   I   J   K   L   M   N   O */
/* 0 */ 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
/* 1 */ 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54,
/* 2 */ 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
/* 3 */ 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,     25,
/* 4 */ 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
/* 5 */ 13, 14, 15, 16, 17,     18, 19, 20, 21, 22, 23, 24
), {
    // LED index to physical position (this is a pain, see qmk.sh in launch repo)
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
    return (eeprom_read_word(((void*)EEPROM_MAGIC_ADDR)) == EEPROM_MAGIC &&
            eeprom_read_byte(((void*)EEPROM_VERSION_ADDR)) == EEPROM_VERSION);
}

void eeprom_set_valid(bool valid) {
    eeprom_update_word(((void*)EEPROM_MAGIC_ADDR), valid ? EEPROM_MAGIC : 0xFFFF);
    eeprom_update_byte(((void*)EEPROM_VERSION_ADDR), valid ? EEPROM_VERSION : 0xFF);
}

void eeprom_reset(void) {
    // Set the keyboard specific EEPROM state as invalid.
    eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

void bootmagic_lite(void) {
    // The lite version of TMK's bootmagic.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
    wait_ms(DEBOUNCE);
    wait_ms(DEBOUNCE);
    matrix_scan();

    // If the Esc (matrix 0,0) is held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    if ( matrix_get_row(0) & (1<<0) ) {
        eeprom_reset();
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

static const uint8_t LEVELS[] = {
    48,
    72,
    96,
    144,
    192,
    255
};
static int LEVEL_I = 1;

void set_value_all_layers(uint8_t value) {
    if (!system76_ec_is_unlocked()) {
        for (int8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
            layer_rgb[layer].hsv.v = value;
        }
        system76_ec_rgb_layer(layer_state);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case RESET:
            if (record->event.pressed) {
                system76_ec_unlock();
            }
            return false;
        case RGB_VAD:
            if (record->event.pressed) {
                if (LEVEL_I > 0)
                    LEVEL_I -= 1;
                set_value_all_layers(LEVELS[LEVEL_I]);
            }
            return false;
        case RGB_VAI:
            if (record->event.pressed) {
                if (LEVEL_I < sizeof(LEVELS) - 1)
                    LEVEL_I += 1;
                set_value_all_layers(LEVELS[LEVEL_I]);
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                if (rgb_matrix_config.hsv.v == 0) {
                    set_value_all_layers(LEVELS[LEVEL_I]);
                } else {
                    set_value_all_layers(0);
                }
            }
            return false;
    }

    return process_record_user(keycode, record);
}

layer_state_t layer_state_set_kb(layer_state_t layer_state) {
    system76_ec_rgb_layer(layer_state);

    return layer_state_set_user(layer_state);
}

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
