/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum tap_dances {
    ENC_TAP
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, QK_KB_9,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        MO(3),   KC_LCTL, KC_LALT, KC_LGUI, TL_LOWR,   KC_SPC,  KC_SPC,  TL_UPPR,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, _______,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END, _______,
        _______, _______, _______, MC_1,    _______, MC_0,    _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, _______,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [_ADJUST] = LAYOUT(
        _______, QK_BOOT, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL,  R_M_TOG,
        _______, _______, MU_NEXT, R_M_TOG, R_M_MOD, _______, _______, _______, _______, R_M_SAI, R_M_HUI, R_M_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, R_M_SAD, R_M_HUD, R_M_RMOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_RAISE]  = { ENCODER_CCW_CW(R_M_RMOD, R_M_MOD) },
    [_ADJUST] = { ENCODER_CCW_CW(R_M_HUI, R_M_HUD) },
};
#endif
// clang-format on

void dance_enc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_MPLY);
    } else if (state->count == 2) {
        register_code(KC_MNXT);
    } else {
        register_code(KC_MPRV);
    }
}

void dance_enc_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_MPLY);
    } else if (state->count == 2) {
        unregister_code(KC_MNXT);
    } else {
        unregister_code(KC_MPRV);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [ENC_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_enc_finished, dance_enc_reset),
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
    };
} work_louder_config_t;

work_louder_config_t work_louder_config;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_KB_9) {
        preprocess_tap_dance(TD(ENC_TAP), record);
        return process_tap_dance(TD(ENC_TAP), record);
    } else if (keycode == QK_KB_10 && record->event.pressed) {
        work_louder_config.led_level ^= true;
        eeconfig_update_user(work_louder_config.raw);
        layer_state_set_kb(layer_state);
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin_low(B2);
    gpio_write_pin_low(B3);
    gpio_write_pin_low(B7);

    if (work_louder_config.led_level) {
        switch (get_highest_layer(state)) {
            case 1:
                gpio_write_pin_high(B2);
                break;
            case 2:
                gpio_write_pin_high(B3);
                break;
            case 3:
                gpio_write_pin_high(B7);
                break;
        }
    }

    return state;
}

void eeconfig_init_user(void) {
    work_louder_config.raw       = 0;
    work_louder_config.led_level = true;
    eeconfig_update_user(work_louder_config.raw);
}

void keyboard_post_init_user(void) {
    work_louder_config.raw = eeconfig_read_user();
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
    eeconfig_update_user(work_louder_config.raw);
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
