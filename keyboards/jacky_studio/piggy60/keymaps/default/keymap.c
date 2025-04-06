// Copyright 2022 The QMK Community (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
 * Check the list of supported LAYOUTS (qmk info jacky_studio/piggy60 -m) to make keymap customization easier.
 * ISO users may wish to start customization from LAYOUT_60_iso_tsangan_hhkb, for instance.
 *
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ Del │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│LT1│
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤
     * │Ctrl │GUI│ Alt │                           │ Alt │GUI│ Ctrl│
     * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
     */
    [0] = LAYOUT_60_ansi_tsangan_split_bs_rshift(
        KC_ESC,         KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,
        KC_TAB,         KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,  
        LT(1,KC_CAPS),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,                   
        KC_LSFT,                  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  LT(1,KC_MUTE),            
        KC_LCTL,        KC_LGUI,  KC_LALT,                                          KC_SPC,                       KC_RALT,            KC_RGUI,  KC_RCTL
    ),
    [1] = LAYOUT_60_ansi_tsangan_split_bs_rshift(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_PSCR,
        KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_PGUP,  KC_HOME,  KC_TRNS,   KC_VOLU,  KC_BRIU,  KC_TRNS,  KC_WH_U,  KC_TRNS,  KC_TRNS,  KC_DEL,
        KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  KC_END,   KC_TRNS,   KC_VOLD,  KC_BRID,  KC_TRNS,  KC_WH_D,  KC_TRNS,            KC_TRNS,
        RM_TOGG,            RM_NEXT,  RM_HUEU,  RM_SATU,  RM_VALU,  RM_SPDU,   KC_TRNS,  KC_MUTE,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                           KC_TRNS,                      KC_TRNS,            KC_TRNS,  KC_TRNS
    )
};
