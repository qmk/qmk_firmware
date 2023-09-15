// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Thumb Keys
#define L_THUMB LT(_LOWER, KC_ENTER)
#define R_THUMB LT(_RAISE, KC_SPACE)

// Rotary
#define L_ROT KC_MNXT
#define R_ROT KC_MPLY

enum coral_layers {
    _QWRTY,
    _CLMK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum coral_keycodes {
    KC_QWRTY = SAFE_RANGE,
    KC_CLMK,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWRTY] = LAYOUT(
        KC_GRV,  KC_1, KC_2,    KC_3,    KC_4,    KC_5,           /**/        KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_GRV,
        KC_ESC,  KC_Q, KC_W,    KC_E,    KC_R,    KC_T,           /**/        KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,  KC_A, KC_S,    KC_D,    KC_F,    KC_G,           /**/        KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,           /**/        KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                       KC_LGUI, KC_LALT, KC_LCTL, L_THUMB, L_ROT, /**/ R_ROT, R_THUMB, KC_RCTL, KC_RALT, KC_RGUI
    ),
    [_CLMK] = LAYOUT(
        KC_GRV,  KC_1, KC_2,    KC_3,    KC_4,    KC_5,           /**/        KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_GRV,
        KC_ESC,  KC_Q, KC_W,    KC_F,    KC_P,    KC_G,           /**/        KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
        KC_TAB,  KC_A, KC_R,    KC_S,    KC_T,    KC_D,           /**/        KC_H,    KC_N,    KC_E,    KC_I,   KC_O,    KC_QUOT,
        KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,           /**/        KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                       KC_LGUI, KC_LALT, KC_LCTL, L_THUMB, L_ROT, /**/ R_ROT, R_THUMB, KC_RCTL, KC_RALT, KC_RGUI
    ),
    [_LOWER] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            /**/          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             /**/          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          /**/          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,          /**/          KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                          _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______,  _______,                        _______, _______,  _______, _______,  _______,  _______,
        _______, KC_INS,  KC_PSCR, KC_APP,  XXXXXXX,  XXXXXXX,                        KC_PGUP, KC_PRVWD, KC_UP,   KC_NXTWD, KC_DLINE, KC_BSPC,
        _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,  KC_CAPS,                        KC_PGDN, KC_LEFT,  KC_DOWN, KC_RGHT,  KC_DEL,   KC_BSPC,
        _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE, XXXXXXX,                        XXXXXXX, KC_LSTRT, XXXXXXX, KC_LEND,  XXXXXXX,  _______,
                          _______, _______, _______,  _______, _______, /**/ _______, _______, _______,  _______, _______
    ),
    [_ADJUST] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        QK_BOOT, XXXXXXX, KC_QWRTY, KC_CLMK, CG_TOGG, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, CG_TOGG,  XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                          _______,  _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWRTY] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CLMK] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LOWER] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_RAISE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_ADJUST] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWRTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWRTY);
            }
            return false;
        case KC_CLMK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_CLMK);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}
