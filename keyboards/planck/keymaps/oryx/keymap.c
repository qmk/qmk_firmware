/* Copyright 2020 ZSA Technology Inc
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

enum planck_keycodes {
    RGB_SLD = EZ_SAFE_RANGE,
};

enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#    define LOWER MO(_LOWER)
#    define RAISE MO(_RAISE)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPC,
    KC_ESCAPE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOTE,
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_ENTER,
    WEBUSB_PAIR,    KC_LCTL,        KC_LALT,        KC_LGUI,        LOWER,          KC_SPACE,       KC_NO,          RAISE,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        _______,
    KC_DELETE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_UNDS,        KC_PLUS,        KC_LCBR,        KC_RCBR,        KC_PIPE,
    _______,        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_NONUS_HASH,  KC_NUBS,KC_HOME,        KC_END,         _______,
    KC_COMMA,       _______, _______, _______, _______, _______, KC_NO,          _______, KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE,KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,           KC_8,           KC_9,           KC_0,           _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINUS,       KC_EQUAL,       KC_LBRC,        KC_RBRC,        KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NONUS_HASH,  KC_NUBS,        KC_PGUP,        KC_PGDN,        _______,
    _______, _______, _______, _______, _______, _______, KC_NO,   _______, KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_DEL,  _______, AU_ON,   AU_OFF,  AU_TOG,  _______, _______, RGB_TOG, RGB_VAI, RGB_VAD, LED_LEVEL, QK_BOOT,
    _______, _______, MU_ON,   MU_OFF,  MU_TOG,  _______, _______, RGB_MOD, RGB_HUI, RGB_HUD, TOGGLE_LAYER_COLOR, _______,
    _______, _______, _______, _______, _______, _______, KC_NO,   _______, _______, _______, _______, _______
  ),

};
// clang-format on

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {{42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {146, 224, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {42, 255, 255}, {32, 255, 234}, {32, 255, 234}, {32, 255, 234}, {32, 255, 234}},

    [1] = {{89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {169, 120, 255}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}, {89, 255, 246}},

    [2] = {{216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {249, 228, 255}, {249, 228, 255}, {249, 228, 255}, {216, 255, 255}, {216, 255, 255}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {216, 255, 255}, {14, 255, 255}, {216, 255, 255}, {216, 255, 255}, {249, 228, 255}, {249, 228, 255}, {249, 228, 255}, {216, 255, 255}, {216, 255, 255}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}, {216, 255, 255}},

};

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            RGB   rgb = hsv_to_rgb(hsv);
            float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (keyboard_config.disable_layer_led) {
        return;
    }
    switch (get_highest_layer(layer_state)) {
        case 1:
            set_layer_color(0);
            break;
        case 2:
            set_layer_color(1);
            break;
        case 3:
            set_layer_color(2);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE) rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
#    ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
#    else
        tap_code(KC_PGDN);
#    endif
    } else {
#    ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
#    else
        tap_code(KC_PGUP);
#    endif
    }
    return true;
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }
