// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"
#include "atomic_util.h"
#include "i2clib.h"
#include "i2c_master.h"
#include "kb_config.h"
#include "./drivers/encoder_dynamic_res.h"

extern DeviceList deviceList[MAX_MCP_NUM];
extern uint16_t   nDevices;

#ifdef OLED_ENABLE
DisplayMode display_mode = DisplayMode_Layer;
#endif

static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

kb_config_t kb_config = {0};

uint16_t calc_auto_mouse_timeout_by_kbconfig(uint8_t value) {
    return 100 * value;
}

#ifdef POINTING_DEVICE_ENABLE
bool set_scrolling = false;

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;
#endif

void keyboard_post_init_kb(void) {
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;

    // initialize with the keyboard config data
    eeconfig_read_kb_datablock(&kb_config.raw);
#ifdef POINTING_DEVICE_ENABLE
    modular_adns5050_set_angle(0, kb_config.angle_L);
    modular_adns5050_set_angle(1, kb_config.angle_R);
    set_auto_mouse_timeout(calc_auto_mouse_timeout_by_kbconfig(kb_config.mouse_layer_off_delay_ms));
    modular_adns5050_set_led_off_length(kb_config.trackball_led_off_timeout * 5 * 60 * 1000);
#endif
#ifdef ENCODER_ENABLE
    dynamic_res_encoder_update_res(0, kb_config.re_resolution_1);
    dynamic_res_encoder_update_res(1, kb_config.re_resolution_2);
    dynamic_res_encoder_update_res(2, kb_config.re_resolution_3);
    dynamic_res_encoder_update_res(3, kb_config.re_resolution_4);
    dynamic_res_encoder_update_res(4, kb_config.re_resolution_5);
    dynamic_res_encoder_update_res(5, kb_config.re_resolution_6);
    dynamic_res_encoder_update_res(6, kb_config.re_resolution_7);
    dynamic_res_encoder_update_res(7, kb_config.re_resolution_8);
    dynamic_res_encoder_update_res(8, kb_config.re_resolution_9);
    dynamic_res_encoder_update_res(9, kb_config.re_resolution_10);
    dynamic_res_encoder_update_res(10, kb_config.re_resolution_11);
    dynamic_res_encoder_update_res(11, kb_config.re_resolution_12);
    dynamic_res_encoder_update_res(12, kb_config.re_resolution_13);
    dynamic_res_encoder_update_res(13, kb_config.re_resolution_14);
    dynamic_res_encoder_update_res(14, kb_config.re_resolution_15);
    dynamic_res_encoder_update_res(15, kb_config.re_resolution_16);
#endif

    i2c_init();
    do_scan();

    keyboard_post_init_user();
}

void eeconfig_init_kb(void) {
    memset(&kb_config.raw, 0, sizeof(kb_config));

    // initialization of kb_config
    my_kb_config_init(&kb_config);

    eeconfig_update_kb_datablock(&kb_config.raw);
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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef POINTING_DEVICE_ENABLE
    modular_adns5050_wake_up_all(true);
#endif

// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    uprintf("#device %u\n", sizeof(deviceList));
#endif

    // system keys, but not combo keys
    if (record->event.pressed && record->event.key.row == 0 && record->event.key.col == 0 && record->event.type != COMBO_EVENT) {
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

    // drag scroll
#ifdef POINTING_DEVICE_ENABLE
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling
            set_scrolling = record->event.pressed;
            return false;
    }

#endif

    if (!process_kb_config_modification(&kb_config, keycode, record)) {
        eeconfig_update_kb_datablock(&kb_config.raw);
        switch (keycode) {
            case AUTO_MOUSE_LAYER_P1:
                set_auto_mouse_enable(kb_config.mouse_layer_on);
                break;
            case AUTO_MOUSE_LAYER_OFF_DELAY_P1:
            case AUTO_MOUSE_LAYER_OFF_DELAY_M1:
                set_auto_mouse_timeout(calc_auto_mouse_timeout_by_kbconfig(kb_config.mouse_layer_off_delay_ms));
                break;
            case ANGLE_L_ADJUSTMENT_P1:
            case ANGLE_L_ADJUSTMENT_M1:
            case ANGLE_L_ADJUSTMENT_P30:
            case ANGLE_L_ADJUSTMENT_M30:
                modular_adns5050_set_angle(0, kb_config.angle_L);
                break;
            case ANGLE_R_ADJUSTMENT_P1:
            case ANGLE_R_ADJUSTMENT_M1:
            case ANGLE_R_ADJUSTMENT_P30:
            case ANGLE_R_ADJUSTMENT_M30:
                modular_adns5050_set_angle(1, kb_config.angle_R);
                break;
        }
        return false;
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
    } else if (display_mode == DisplayMode_CONF_0) {
        // debug output of the all kb_config data
        debug_output_kb_config(&kb_config);
        oled_kb_config_output(&kb_config, 0);
    } else if (display_mode == DisplayMode_CONF_1) {
        oled_kb_config_output(&kb_config, 1);
    } else if (display_mode == DisplayMode_CONF_2) {
        oled_kb_config_output(&kb_config, 2);
    } else if (display_mode == DisplayMode_CONF_3) {
        oled_kb_config_output(&kb_config, 3);
    } else if (display_mode == DisplayMode_CONF_4) {
        oled_kb_config_output(&kb_config, 4);
    } else if (display_mode == DisplayMode_VERSION) {
        oled_write_ln_P(PSTR("-- VERSION --"), false);
        oled_write_ln_P(PSTR(FW_VERSION), false);
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
#    ifdef POINTING_DEVICE_ENABLE
    modular_adns5050_wake_up_all(true);
#    endif
    return encoder_update_user(index, clockwise);
}

// override existing weak function
void encoder_driver_task(void) {
    for (uint8_t i = 0; i < NUM_ENCODERS; i++) {
        dynamic_res_encoder_quadrature_handle_read(i, encoder_quadrature_read_pin(i, false), encoder_quadrature_read_pin(i, true));
    }
}
#endif

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_driver_init(void) {
    modular_adns5050_pointing_device_driver.init();
    set_auto_mouse_layer(AUTO_MOUSE_DEFAULT_LAYER); // default
    set_auto_mouse_enable(true);
}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    float          mag     = 0.25 * (kb_config.pointer_speed_magnification + 1);
    float          scr_mag = 0.25 * (kb_config.drag_scroll_speed_magnification + 1);
    report_mouse_t t       = modular_adns5050_pointing_device_driver.get_report(mouse_report);

    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)t.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)t.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        t.h = (int8_t)(scroll_accumulated_h * scr_mag);
        t.v = (int8_t)(scroll_accumulated_v * scr_mag);

        if (kb_config.invert_drag_scroll_y) {
            t.h *= -1;
        }
        if (kb_config.invert_drag_scroll_x) {
            t.v *= -1;
        }

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        t.x = 0;
        t.y = 0;
    } else {
        t.x *= mag;
        t.y *= mag;
    }

    return t;
}
uint16_t pointing_device_driver_get_cpi(void) {
    return modular_adns5050_pointing_device_driver.get_cpi();
}
void pointing_device_driver_set_cpi(uint16_t cpi) {
    modular_adns5050_pointing_device_driver.set_cpi(cpi);
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(get_auto_mouse_layer()) && kb_config.all_keys_are_mouse_keys) {
        return true;
    }

    return is_mouse_record_user(keycode, record);
}
#endif
