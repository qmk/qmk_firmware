// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum user_keycodes {
    KC_RPDIR = QK_USER_0,
    VIA_RST
};

enum layers{
    WIN_BASE = 0,
    WIN_FN,
    MAC_BASE,
    MAC_FN
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_BASE] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,        KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  KC_F11,      KC_F12,     KC_DEL,
        KC_GRV,   KC_1,         KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,     KC_EQL,     KC_BSPC,  KC_PGUP,
        KC_TAB,   KC_Q,         KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,    KC_LBRC,     KC_RBRC,    KC_BSLS,  KC_PGDN,
        KC_CAPS,  KC_A,         KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT,     KC_ENT,               KC_HOME,
        KC_LSFT,  KC_Z,         KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH, KC_RSFT,                           KC_UP,
        KC_LCTL,  KC_LGUI,      KC_LALT,                                KC_SPC,                                 KC_RGUI, MO(WIN_FN),  KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RIGHT),

    [WIN_FN] = LAYOUT( /* FN */
        QK_BOOT,  KC_BRID,      KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,    _______,
        _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAD,    RGB_VAI,    EE_CLR,    _______,
        _______,  _______,      KC_RPDIR, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,   _______,
        _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,               _______,
        _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                           RGB_TOG,
        _______,  DF(MAC_BASE), _______,                                _______,                                _______,  _______,    _______,    RGB_RMOD,  RGB_TOG,  RGB_MOD),

    [MAC_BASE] = LAYOUT( /* Base */
        KC_ESC,   KC_BRID,      KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,    KC_DEL,
        KC_GRV,   KC_1,         KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,     KC_BSPC,   KC_PGUP,
        KC_TAB,   KC_Q,         KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,   KC_PGDN,
        KC_CAPS,  KC_A,         KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,    KC_ENT,                KC_HOME,
        KC_LSFT,  KC_Z,         KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                           KC_UP,
        KC_LCTL,  KC_LOPTN,     KC_LCMMD,                               KC_SPC,                                 KC_ROPTN, MO(MAC_FN), KC_RCMMD,   KC_LEFT,   KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT( /* FN */
        QK_BOOT,  KC_F1,        KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,     _______,
        _______,  _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    EE_CLR,   _______,
        RGB_TOG,  RGB_VAI,      KC_RPDIR, RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,    _______,  _______,
        _______,  RGB_VAD,      RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,    _______,              _______,
        _______,  _______,      _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,                          RGB_TOG,
        _______,  _______,      DF(WIN_BASE),                           _______,                                _______,  _______,    _______,    RGB_RMOD, RGB_TOG,  RGB_MOD)
};
// clang-format on

typedef union {
  uint32_t raw;
  struct {
    uint8_t dkey_states : 1;
  };
} confinfo_t;

confinfo_t confinfo;
uint32_t peek_close_rgb = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_keychron(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case DF(MAC_BASE): {
            if (record->event.pressed) {
                set_single_persistent_default_layer(MAC_BASE);
                return false;
            }
        } break;
        case DF(WIN_BASE): {
            if (record->event.pressed) {
                set_single_persistent_default_layer(WIN_BASE);
                return false;
            }
        } break;
        case VIA_RST: {
            if (record->event.pressed) {
                #include "via.h"
                via_eeprom_set_valid(false);
                eeconfig_init_via();
            }
        } break;
        case KC_RPDIR: {
            if (record->event.pressed) {
                confinfo.dkey_states = !confinfo.dkey_states;
                peek_close_rgb = timer_read() | 0x10000;
                eeconfig_update_user(confinfo.raw);
            }
        } break;
        case KC_W: {
            if (confinfo.dkey_states) {
                if (record->event.pressed)
                    register_code(KC_UP);
                else
                    unregister_code(KC_UP);
                return false;
            }
        } break;
        case KC_A: {
            if (confinfo.dkey_states) {
                if (record->event.pressed)
                    register_code(KC_LEFT);
                else
                    unregister_code(KC_LEFT);
                return false;
            }
        } break;
        case KC_S: {
            if (confinfo.dkey_states) {
                if (record->event.pressed)
                    register_code(KC_DOWN);
                else
                    unregister_code(KC_DOWN);
                return false;
            }
        } break;
        case KC_D: {
            if (confinfo.dkey_states) {
                if (record->event.pressed)
                    register_code(KC_RIGHT);
                else
                    unregister_code(KC_RIGHT);
                return false;
            }
        } break;
        default: {
            return true;
        }
    }

  return true;
}

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

void matrix_init_user(void) {
    confinfo.raw = eeconfig_read_user();
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (peek_close_rgb & 0x10000) {
        if (timer_elapsed(peek_close_rgb) <= 200) {
            for (uint8_t idx = led_min; idx < led_max; idx++) {
                rgb_matrix_set_color(idx, RGB_OFF);
            }
            return false;
        } else {
            peek_close_rgb = 0;
        }
    }

    if (confinfo.dkey_states == true) {
        rgb_matrix_set_color(31, 0x57, 0x77, 0x77); // KC_W
    }

    if ((get_highest_layer(default_layer_state | layer_state) == WIN_BASE) || (get_highest_layer(default_layer_state | layer_state) == WIN_FN)) {
        rgb_matrix_set_color(72, 0x57, 0x77, 0x77);
    } else if ((get_highest_layer(default_layer_state | layer_state) == MAC_BASE) || (get_highest_layer(default_layer_state | layer_state) == MAC_FN)) {
        rgb_matrix_set_color(73, 0x57, 0x77, 0x77);
    }

    return true;
}
#endif

#if CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};
#endif
