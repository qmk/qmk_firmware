// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    FN_MO13 = SAFE_RANGE,
    FN_MO23,
};

// more Layer Tap stuff
#define SPC_FN1 LT(1, KC_SPC)
#define SPC_FN2 LT(2, KC_SPC)
#define SPC_FN3 LT(3, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 1
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │BSp│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │ Tab│ A │ S │ D │ F │ G │ H │ J │ K │ L │ Entr │
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──┬┴──┬───┤
     * │ Sft │ Z │ X │ C │ V │ B │ N │ M │ Sft │ ↑ │Del│
     * ├────┬┴──┬┴───┼───┴───┴─┬─┴───┴───┼─┬───┼───┼───┤
     * │Ctrl│Win│ Alt│Space/Fn2│ Fn1/Fn3 │ │ ← │ ↓ │ → │
     * └────┴───┴────┴─────────┴─────────┘ └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,          SPC_FN2,          FN_MO13,                   KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* Layer 2
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ▿ │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │ ▿  │   │   │   │   │-_ │=+ │[{ │]} │\| │  ▿   │
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──┬┴──┬───┤
     * │  ▿  │   │   │;: │'" │,< │.> │/? │  ▿  │PUp│Ins│
     * ├────┬┴──┬┴───┼───┴───┴─┬─┴───┴───┼─┬───┼───┼───┤
     * │ ▿  │ ▿ │ ▿  │   Fn3   │    ▿    │ │Hom│Pdn│End│
     * └────┴───┴────┴─────────┴─────────┘ └───┴───┴───┘
     */
    [1] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,          _______,
        _______,          XXXXXXX, XXXXXXX, KC_SCLN, KC_QUOT, KC_COMM, KC_DOT,  KC_SLSH, _______, KC_PGUP, KC_INS,
        _______, _______, _______,          MO(3),            _______,                   KC_HOME, KC_PGDN, KC_END
    ),

    /* Layer 3
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│ ▿ │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │ ▿  │   │   │   │   │F11│F12│Psc│SLk│Pau│  ▿   │
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──┬┴──┬───┤
     * │  ▿  │   │   │   │   │   │   │   │Menu │Vl+│Mut│
     * ├────┬┴──┬┴───┼───┴───┴─┬─┴───┴───┼─┬───┼───┼───┤
     * │ ▿  │ ▿ │ ▿  │    ▿    │    ▿    │ │Sto│Vl-│Ply│
     * └────┴───┴────┴─────────┴─────────┘ └───┴───┴───┘
     */
    [2] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS,          _______,
        _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  KC_VOLU, KC_MUTE,
        KC_RCTL, KC_RGUI, KC_RALT,          _______,          _______,                   KC_MSTP, KC_VOLD, KC_MPLY
    ),

    /* Layer 4
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ▿ │   │   │   │Rst│   │   │   │   │   │   │ ▿ │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │ ▿  │Tog│Mod│Hu-│Hu+│St-│St+│   │   │   │  ▿   │
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──┬┴──┬───┤
     * │  ▿  │mod│   │   │   │   │NRO│   │     │Br+│   │
     * ├────┬┴──┬┴───┼───┴───┴─┬─┴───┴───┼─┬───┼───┼───┤
     * │ ▿  │ ▿ │ ▿  │    ▿    │    ▿    │ │Sp-│Br-│Sp+│
     * └────┴───┴────┴─────────┴─────────┘ └───┴───┴───┘
     */
    [3] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
        _______,         RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, XXXXXXX, RGB_VAI, XXXXXXX,
        _______, _______, _______,          _______,          _______,                   RGB_SPD, RGB_VAD, RGB_SPI
    ),
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_MO13:
            if (record->event.pressed) {
                layer_on(1);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(1);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
        case FN_MO23:
            if (record->event.pressed) {
                layer_on(2);
                update_tri_layer(1, 2, 3);
            } else {
                layer_off(2);
                update_tri_layer(1, 2, 3);
            }
            return false;
            break;
    }
    return true;
}
