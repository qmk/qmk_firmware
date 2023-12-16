// Copyright 2022 Viatly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
make avalanche/v4:semd:avrdude-split-right
make avalanche/v4:semd:avrdude-split-left
*/

#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "rgb_util.h"
#include "oled_util.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
*/
    [_QWERTY] = LAYOUT(_______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______,
             KC_TAB,  KC_Q, KC_W, KC_E,     KC_R,    KC_T,                                                   KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,    KC_BSPC,
    _______, KC_LSFT, KC_A, KC_S, KC_D,     KC_F,    KC_G,                                                   KC_H,    KC_J,    KC_K,   KC_L,    KC_UP,   SC_QUEST, _______,
             KC_LCTL, KC_Z, KC_X, KC_C,     KC_V,    KC_B,    KC_RGUI,    _______, /**/ _______, CW_TOGG,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_DOWN, KC_RGHT,
                                  _______,  KC_LALT, KC_RGUI, MO(_LOWER), KC_SPC,  /**/ KC_ENT,  MO(_RAISE), KC_RALT, KC_RSFT, KC_LEFT
    ),
/*
 * Lower Layer: Number keys, Symbols, Navigation
 */
    [_LOWER] = LAYOUT(_______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______,
             KC_ESC,  KC_1,    KC_2,     KC_3,     KC_4,    KC_5,                                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_DEL,
    KC_HOME, KC_LSFT, _______, SC_PERCE, SC_AT,    SC_HASH, SC_EXCLA,                                             _______, KC_PGUP, KC_HOME, _______, SC_ASTER, SC_BACKSL, KC_PGDN,
             KC_LCTL, KC_GRV,  KC_TILD,  SC_AMP,   SC_PIPE, SC_DOLL,  KC_RGUI, _______, /**/ _______, _______,    KC_SCLN, KC_PGDN, KC_END,  _______, _______,  _______,
                                         _______,  KC_LALT, KC_RGUI,  _______, KC_SPC,  /**/ KC_ENT,  MO(_RAISE), KC_RALT, KC_RSFT, KC_LEFT

    ),
/*
 * Raise Layer: Keys, more symbols
  */
    [_RAISE] = LAYOUT(_______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______,
             KC_ESC,  KC_EQL,  SC_IQUEST, SC_GEMIN, SC_APROX, SC_SYM1,                                              KC_LBRC, KC_QUOT, SC_OPAR, SC_CPAR, SC_EQUA, KC_DEL,
    KC_PGUP, KC_LSFT, _______, _______,   KC_NUBS,  SC_DIERE, SC_CHAPE,                                             SC_ODAT, SC_CDAT, SC_OKEY, SC_CKEY, KC_RBRC, SC_SLAS, KC_END,
             KC_LCTL, _______, _______,   KC_NUHS,  _______,  _______,  _______,    _______, /**/ _______, _______, KC_MINS, SC_DQUO, SC_COLO, SC_SCOL, KC_SLSH, SC_UNSC,
                                          _______,  KC_LALT,  KC_RGUI,  MO(_LOWER), KC_SPC,  /**/ KC_ENT, _______,  KC_RALT, KC_CAPS, KC_LEFT
    ),
/*
 * Adjust Layer: Function keys, RGB
  */
    [_ADJUST] = LAYOUT(_______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, _______,
             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                           _______, _______, _______, _______, _______, _______,_______,
             _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,  _______, _______, /**/ _______, _______, _______, KC_WAKE, _______
    ),
};

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgb_layers_init();
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    rgb_set_layer_state(state);
#endif
    return state;
}

bool led_update_user(led_t led_state) {
#ifdef RGBLIGHT_ENABLE
    rgb_set_led_state(led_state);
#endif
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
bool oled_task_user(void) {
    render_status();
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code16(LGUI(LSFT(KC_Z)));
    } else {
        tap_code16(LGUI(KC_Z));
    }
    return true;
}
#endif

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_LSFT:
        case KC_SLSH:
        case SC_UNSC:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
