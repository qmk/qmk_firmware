// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"
#include "atomic_util.h"
#include "i2clib.h"
#include "i2c_master.h"

extern DeviceList deviceList[MAX_MCP_NUM];
extern uint16_t   nDevices;

#ifdef OLED_ENABLE
DisplayMode display_mode = DisplayMode_Layer;
#endif

static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

enum my_keycodes {
    // Next OLED Page
    NEXT_OLED_PAGE = QK_KB_0,
    // Trackball angle
    ROT_R30_1,
    ROT_L30_1,
    ROT_R30_2,
    ROT_L30_2,
    ROT_R2_1,
    ROT_L2_1,
    ROT_R2_2,
    ROT_L2_2,
    // mouse key latency
    MOUSE_LAYER_MS_ADD_100MS,
    MOUSE_LAYER_MS_MINUS_100MS,
    // x0.5, x1 (default), x2, x4
    POINTER_SPEED_MAG_CHANGE,
};

kb_config_t kb_config = {0};

void keyboard_post_init_kb(void) {
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;

    kb_config.raw = eeconfig_read_kb();
    modular_adns5050_set_half_angle(0, kb_config.angle1);
    modular_adns5050_set_half_angle(1, kb_config.angle2);

    i2c_init();
    do_scan();

    keyboard_post_init_user();
}

void eeconfig_init_kb(void) {
    kb_config.raw            = 0;
    kb_config.angle1         = 0;
    kb_config.angle2         = 0;
    kb_config.mouse_layer_ms = 6;
    kb_config.pointer_speed_magnification = 1;
    eeconfig_update_kb(kb_config.raw);

    eeconfig_init_user();
}

void matrix_init_custom(void) {
    // initialize system pins
    ATOMIC_BLOCK_FORCEON {
        for (uint16_t i = 0; i < SYSTEM_KEY_NUM; i++) {
            pin_t dpin = direct_pins[0][i];
            if (dpin != NO_PIN) gpio_set_pin_input_high(dpin);
        }
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t row_data = 0;

    // system pins
    if (current_row == 0) {
        for (uint16_t i = 0; i < SYSTEM_KEY_NUM; i++) {
            pin_t dpin = direct_pins[current_row][i];
            if (dpin != NO_PIN) {
                uint8_t pin_state = gpio_read_pin(dpin);
                row_data |= (matrix_row_t)(0x1 ^ pin_state) << i;
            }
        }
    }

    for (uint16_t i = 0; i < nDevices; i++) {
        // skip if the row is not the target
        if (!(MATRIX_COLS * current_row <= deviceList[i].keymapShift && deviceList[i].keymapShift < MATRIX_COLS * (current_row + 1))) continue;
        uint16_t shift_value = deviceList[i].keymapShift % MATRIX_COLS;

        bool success = change_channel(deviceList[i].ch);
        if (!success) {
            continue;
        }

        Keys_Data data = {};
        if (deviceList[i].type == Type_PCA9557_Keys4 || deviceList[i].type == Type_PCA9557_Keys5) {
            data = read_PCA9557_register(deviceList[i].address);
        } else if (deviceList[i].type == Type_XL9555_Keys4 || deviceList[i].type == Type_XL9555_Keys5) {
            data = read_XL9555_register(deviceList[i].address);
        } else if (deviceList[i].type == Type_PCA9534A_RE_CLICKABLE) {
            data = read_PCA9534A_register(deviceList[i].address);
        } else {
            dprintf("failed to read data. unknown type: %d, ch: %X, addr: %X\n", deviceList[i].type, deviceList[i].ch, deviceList[i].address);
            continue;
        }

        if (data.type == Type_PCA9557_Keys4 || data.type == Type_PCA9557_Keys5 || data.type == Type_XL9555_Keys4 || data.type == Type_XL9555_Keys5) {
            row_data |= (matrix_row_t)data.data[0] << shift_value;
        } else if (deviceList[i].type == Type_PCA9534A_RE_CLICKABLE) {
            // pick lower 3 bits
            row_data |= (matrix_row_t)(((data.data[0] & 0x04) >> 2)) << shift_value;
        } else {
            dprintf("failed to read data. unknown type: %d, ch: %X, addr: %X, data: %X\n", deviceList[i].type, deviceList[i].ch, deviceList[i].address, data.data[0]);
            continue;
        }
    }

    current_matrix[current_row] = row_data;
}

void update_half_angle(uint8_t index, int16_t angle) {
    modular_adns5050_add_half_angle(index, angle);
    if (index == 0) {
        kb_config.angle1 = modular_adns5050_get_half_angle(index);
    }
    if (index == 1) {
        kb_config.angle2 = modular_adns5050_get_half_angle(index);
    }
    eeconfig_update_kb(kb_config.raw);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    modular_adns5050_wake_up_all(true);

// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    uprintf("#device %u\n", sizeof(deviceList));
#endif

    // system keys
    if (record->event.pressed && record->event.key.row == 0 && record->event.key.col == 0) {
        dprintf("GP9 pressed\n");
        display_mode = (display_mode + 1) % DisplayMode_MAX;
#ifdef OLED_ENABLE
        oled_clear();
#endif
        return false;
    }

    // process next oled page
    if (record->event.pressed) {
        switch (keycode) {
            case NEXT_OLED_PAGE:
                display_mode = (display_mode + 1) % DisplayMode_MAX;
#ifdef OLED_ENABLE
                oled_clear();
#endif
                return false;
        }
    }

    // process angle change
    if (record->event.pressed) {
        {
            const uint16_t value = 15;
            switch (keycode) {
                case ROT_R30_1:
                    update_half_angle(0, value);
                    return false;
                case ROT_L30_1:
                    update_half_angle(0, -value);
                    return false;
                case ROT_R30_2:
                    update_half_angle(1, value);
                    return false;
                case ROT_L30_2:
                    update_half_angle(1, -value);
                    return false;
            }
        }
        {
            const uint16_t value = 1;
            switch (keycode) {
                case ROT_R2_1:
                    update_half_angle(0, value);
                    return false;
                case ROT_L2_1:
                    update_half_angle(0, -value);
                    return false;
                case ROT_R2_2:
                    update_half_angle(1, value);
                    return false;
                case ROT_L2_2:
                    update_half_angle(1, -value);
                    return false;
            }
        }
    }

    // process mouse layer ms change
    if (record->event.pressed) {
        switch (keycode) {
            case MOUSE_LAYER_MS_ADD_100MS:
                kb_config.mouse_layer_ms += 1;
                if (kb_config.mouse_layer_ms > 40) kb_config.mouse_layer_ms = 40;
                eeconfig_update_kb(kb_config.raw);
                return false;
            case MOUSE_LAYER_MS_MINUS_100MS:
                kb_config.mouse_layer_ms -= 1;
                // overflow
                if (kb_config.mouse_layer_ms > 40) kb_config.mouse_layer_ms = 0;
                eeconfig_update_kb(kb_config.raw);
                return false;
        }
    }

    // process pointer move speed change
    if (record->event.pressed) {
        switch (keycode) {
            case POINTER_SPEED_MAG_CHANGE:
                kb_config.pointer_speed_magnification += 1;
                if (kb_config.pointer_speed_magnification > 3) kb_config.pointer_speed_magnification = 0;
                eeconfig_update_kb(kb_config.raw);
                return false;
        }
    }

    return process_record_user(keycode, record);
}

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    {
        uint8_t     current_layer = get_highest_layer(layer_state);
        static char type_count_str[7];
        oled_write_P(PSTR("layer: "), false);
        itoa(current_layer, type_count_str, 10);
        oled_write_ln(type_count_str, false);
    }

    if (display_mode == DisplayMode_Layer) {
        // first line
        {
            static char type_count_str[7];
            oled_write_P(PSTR("# Device: "), false);
            itoa(nDevices, type_count_str, 10);
            oled_write_ln(type_count_str, false);
        }

        // second line
        {
            {
                static char type_count_str[7];
                oled_write_P(PSTR(" KEY4: "), false);

                uint16_t keynum = 0;
                for (uint16_t i = 0; i < nDevices; i++) {
                    keynum += (int)(deviceList[i].type == Type_PCA9557_Keys4 || deviceList[i].type == Type_XL9555_Keys4);
                }
                itoa(keynum, type_count_str, 10);
                oled_write_P(type_count_str, false);
                oled_write_P(PSTR(", "), false);
            }
            {
                static char type_count_str[7];
                oled_write_P(PSTR(" KEY5: "), false);

                uint16_t keynum = 0;
                for (uint16_t i = 0; i < nDevices; i++) {
                    keynum += (int)(deviceList[i].type == Type_PCA9557_Keys5 || deviceList[i].type == Type_XL9555_Keys5);
                }
                itoa(keynum, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_ln(PSTR(""), false);
        }

        // third line
        {
            {
                static char type_count_str[7];
                oled_write_P(PSTR(" RE: "), false);

                uint16_t keynum = 0;
                for (uint16_t i = 0; i < nDevices; i++) {
                    keynum += (int)(deviceList[i].type == Type_PCA9534A_RE_CLICKABLE);
                }
                itoa(keynum, type_count_str, 10);
                oled_write_P(type_count_str, false);
                oled_write_P(PSTR(", "), false);
            }
            {
                static char type_count_str[7];
                oled_write_P(PSTR(" TB: "), false);

                uint16_t num = modular_adns5050_get_connected_count();
                itoa(num, type_count_str, 10);
                oled_write_P(type_count_str, false);
            }
            oled_write_ln(PSTR(""), false);
        }
    } else if (display_mode == DisplayMode_EEPROM) {
        oled_write_ln_P(PSTR("-- EEPROM --"), false);
        kb_config.raw = eeconfig_read_kb();
        {
            static char type_count_str[7];
            oled_write_P(PSTR("A1: "), false);
            itoa(kb_config.angle1 * 2, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
        oled_write_P(PSTR(", "), false);
        {
            static char type_count_str[7];
            oled_write_P(PSTR("A2: "), false);
            itoa(kb_config.angle2 * 2, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
        oled_write_P(PSTR(", "), false);
        {
            static char type_count_str[7];
            oled_write_P(PSTR("MD: "), false);
            itoa(kb_config.mouse_layer_ms, type_count_str, 10);
            oled_write_P(type_count_str, false);
            oled_write_P(PSTR("*100ms"), false);
        }
        oled_write_P(PSTR(", "), false);
        {
            static char type_count_str[7];
            oled_write_P(PSTR("MG: "), false);
            itoa(kb_config.pointer_speed_magnification, type_count_str, 10);
            oled_write_P(type_count_str, false);
        }
        oled_write_ln(PSTR(""), false);
    } else {
        oled_write_ln_P(PSTR("-- INVALID MODE --"), false);
    }

    return true;
}
#endif

#ifdef ENCODER_ENABLE
uint8_t encoder_quadrature_read_pin(uint8_t index, bool pad_b) {
    uint8_t target = index;
    for (uint16_t i = 0; i < nDevices; i++) {
        if (deviceList[i].type == Type_PCA9534A_RE_CLICKABLE) {
            // skip if this RE is not the indexed one
            if (target != 0) {
                target--;
                continue;
            }

            bool success = change_channel(deviceList[i].ch);
            if (!success) {
                continue;
            }

            Keys_Data data = read_PCA9534A_register(deviceList[i].address);
            // data -> XXXXX (click) (B) (A)
            if (pad_b) {
                return (data.data[0] & (0x01 << 1)) >> 1;
            } else {
                return (data.data[0] & (0x01 << 0)) >> 0;
            }
        }
    }

    // if reaches
    return 0;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    modular_adns5050_wake_up_all(true);
    return encoder_update_user(index, clockwise);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_driver_init(void) {
    modular_adns5050_pointing_device_driver.init();
}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    uint16_t user_mag = kb_config.pointer_speed_magnification;
    float mag = 0.5;
    for(uint8_t i = 0; i < user_mag; i++) {
        mag *= 2;
    }
    report_mouse_t t = modular_adns5050_pointing_device_driver.get_report(mouse_report);
    t.x *= mag;
    t.y *= mag;
    return t;
}
uint16_t pointing_device_driver_get_cpi(void) {
    return modular_adns5050_pointing_device_driver.get_cpi();
}
void pointing_device_driver_set_cpi(uint16_t cpi) {
    modular_adns5050_pointing_device_driver.set_cpi(cpi);
}
#endif
