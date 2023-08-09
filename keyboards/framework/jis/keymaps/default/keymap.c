// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "framework.h"

// clang-format off
enum _layers {
  _BASE,
  _FN,
  _FN_LOCK,
  _FM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │Esc  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ Del│
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴┬───┤
     * 15 keys │Z↔H│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ ^ │¥ │Bck│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬┴───┤
     * 13 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ @ │ [ │Entr│
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐   │
     * 14 keys │ Eisū │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ : │ ] │   │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * 13 keys │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ \ │Shift│
     *         ├────┬───┼───┼───┼──┬┴───┴───┴─┬─┴┬──┼───┼───┼───┴┬──┴┬────┤
     *         │    │   │   │   │M │          │H │K │   │   │    │↑  │    │
     * 14 keys │Ctrl│FN │GUI│Alt│u │          │e │↔ │Alt│Ctl│ ←  ├───┤  → │
     *         │    │   │   │   │h │          │n │H │   │   │    │  ↓│    │
     *         └────┴───┴───┴───┴──┴──────────┴──┴──┴───┴───┴────┴───┴────┘
     * 83 total
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        JP_ZKHK, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, JP_CIRC, JP_YEN,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,   KC_LBRC,
        JP_EISU, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_RBRC, KC_ENT,
            KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JP_BSLS,     KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT, JP_MHEN,     KC_SPC,       JP_HENK, JP_KANA, KC_RALT, KC_RCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
    ),
     /*
     * Function layer
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │FN lk│Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Ins │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴┬───┤
     * 15 keys │   │   │   │   │   │   │   │   │   │   │   │   │   │  │   │
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬┴───┤
     * 13 keys │     │   │   │   │   │   │   │   │   │   │Pau│   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐   │
     * 14 keys │      │   │SRq│   │   │   │   │   │ScL│   │   │   │   │   │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * 13 keys │        │   │   │   │   │   │Brk│   │   │   │   │   │     │
     *         ├────┬───┼───┼───┼──┬┴───┴───┴─┬─┴┬──┼───┼───┼───┴┬──┴┬────┤
     *         │    │   │   │   │  │ Toggle   │  │  │   │   │    │PgU│    │
     * 14 keys │    │   │   │   │  │ Backlight│  │  │   │   │Home├───┤End │
     *         │    │   │   │   │  │          │  │  │   │   │    │PgD│    │
     *         └────┴───┴───┴───┴──┴──────────┴──┴──┴───┴───┴────┴───┴────┘
     * 83 total
     */
    [_FN] = LAYOUT(
        FN_LOCK, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, XXXXXXX, KC_PSCR, KC_MSEL, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, _______, _______,
        _______, _______, KC_SYRQ, _______, _______, _______, _______, _______, KC_SCRL, _______, _______, _______, _______, _______,
            _______,      _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______, _______,     _______,
        _______, _______, _______, _______, _______,     BL_STEP,      _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
    // Function lock layer
    // Everything on F-row locked to function layer, except ESC and DEL
    [_FN_LOCK] = LAYOUT(
        _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, XXXXXXX, KC_PSCR, KC_MSEL, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______,
        _______, MO(_FM), _______, _______, _______,     _______,      _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_FN] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, _______, _______,
        _______, _______, KC_SYRQ, _______, _______, _______, _______, _______, KC_SCRL, _______, _______, _______, _______, _______,
            _______,      _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______, _______,     _______,
        _______, _______, _______, _______, _______,     BL_STEP,      _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
};
// clang-format on

// Make sure to keep FN Lock even after reset
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_LOCK:
            if (record->event.pressed) {
                if (layer_state_is(_FN)) {
                    set_single_persistent_default_layer(_FN_LOCK);
                }
                if (layer_state_is(_FM)) {
                    set_single_persistent_default_layer(_BASE);
                }
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}
