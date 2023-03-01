/* Copyright 2021 Drashna Jael're
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

#include "work_board.h"

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
#    ifdef RGB_MATRIX_ENABLE
#        error Cannot run OLED and Per Key RGB at the same time due to pin conflicts
#    endif
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(3));
    oled_write_P(PSTR("Raise"), layer_state_is(4));
    oled_write_P(PSTR("Adjst"), layer_state_is(5));

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state.num_lock);
    oled_write_P(PSTR("C"), led_usb_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_usb_state.scroll_lock);

    uint8_t modifiers = get_mods() | get_oneshot_mods();
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));

    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);

    return false;
}
#endif

#ifdef VIA_ENABLE
bool via_layout_2u = false;

void via_set_layout_options_kb(uint32_t value) {
    via_layout_2u = (bool)value;
}
#endif

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
#ifdef VIA_ENABLE
    if (via_layout_2u) {
        rgb_matrix_set_color(5, 0, 0, 0);
        rgb_matrix_set_color(7, 0, 0, 0);
    } else {
        rgb_matrix_set_color(6, 0, 0, 0);
    }
#else
    rgb_matrix_set_color(5, 0, 0, 0);
    rgb_matrix_set_color(7, 0, 0, 0);
#endif
    return true;
}

void keyboard_pre_init_kb(void) {
    setPinOutput(B2);
    setPinOutput(B3);
    setPinOutput(B7);

    writePinLow(B2);
    writePinLow(B3);
    writePinLow(B7);

    keyboard_pre_init_user();
}

work_louder_config_t work_louder_config;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_work_rgb(keycode, record)) {
        return false;
    }

    if (keycode == QK_KB_10 && record->event.pressed) {
        work_louder_config.led_level ^= true;
        eeconfig_update_kb(work_louder_config.raw);
        layer_state_set_kb(layer_state);
    }

    return process_record_user(keycode, record);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    writePinLow(B2);
    writePinLow(B3);
    writePinLow(B7);

    state = layer_state_set_user(state);
    if (work_louder_config.led_level) {
        switch (get_highest_layer(state)) {
            case 1:
                writePinHigh(B2);
                break;
            case 2:
                writePinHigh(B3);
                break;
            case 3:
                writePinHigh(B7);
                break;
        }
    }

    return state;
}

#ifdef VIA_ENABLE
void eeconfig_init_kb(void) {
    work_louder_config.raw       = 0;
    work_louder_config.led_level = true;
    eeconfig_update_kb(work_louder_config.raw);
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    work_louder_config.raw = eeconfig_read_user();
    keyboard_post_init_user();
}

enum via_indicator_value {
    id_wl_brightness = 1,
    id_wl_layer, // placeholder
};

void wl_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            work_louder_config.led_level = (bool)*value_data;
            layer_state_set_kb(layer_state);
            break;
            // case id_wl_layer:
            //     layer_move(*value_data);
            //     break;
    }
}

void wl_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            *value_data = work_louder_config.led_level;
            break;
            // case id_wl_layer:
            //     *value_data = get_highest_layer(layer_state);
            //     break;
    }
}

void wl_config_save(void) {
    eeconfig_update_kb(work_louder_config.raw);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                wl_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                wl_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                wl_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
    *command_id = id_unhandled;
}
#endif
