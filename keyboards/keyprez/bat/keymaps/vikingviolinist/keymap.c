// Copyright 2022 Michal Petrik (@Michal Petrik)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST
};

enum custom_keycodes {
    KC_PRVWD,
    KC_NXTWD
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NAV MO(_NAV)
#define ADJUST MO(_ADJUST)
#define ESC_CTL MT(MOD_LCTL, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,       KC_I,       KC_O,    KC_P,    KC_LBRC,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_MUTE,     KC_H,    KC_J,       KC_K,       KC_L,    KC_SCLN, KC_QUOT,
        ESC_CTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,       KC_COMM,    KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, RAISE,   NAV,        KC_LEAD
    ),
    [_LOWER] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_TRNS,     KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS,    KC_TRNS
    ),
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_TRNS,     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NAV] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_PRVWD:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_LEFT);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_LEFT);
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_RIGHT);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_RIGHT);
            }
            break;
    }
    return true;
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      SEND_STRING(SS_LCTRL(SS_LSFT("f")));
    }
    SEQ_ONE_KEY(KC_W) {
      SEND_STRING(SS_LCTRL(SS_LSFT("w")));
    }
  }
}
