// Copyright 2023 Josh Hinnebusch (@hineybush)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
│00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0B │0C │0D ││0E │ │0F │0G │0H │ │0I │0J │0K │0L │
└───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘ └───┴───┴───┴───┘
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐   ┌───────┐
│10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E │ │1F │1G │1H │ │1I │1J │1K │1L │   │1E     │ 2u Backspace
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤ ├───┼───┼───┼───┤   └───────┘                ┌───┐
│20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │2F │2G │2H │ │2I │2J │2K │2L │                            │   │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┼───┤                            │2L │ Numpad "+"
│30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │               │3I │3J │3K │3L │                            │   │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐     ├───┼───┼───┼───┤                            ├───┤
│40      │42 │43 │44 │45 │46 │47 │48 │49 │3A │3B │4C    │4D │     │4G │     │4I │4J │4K │4L │                            │   │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤ ┌───┼───┼───┐ ├───┼───┼───┼───┤                ┌───────┐   │4L │ Numpad Enter
│50  │51  │52  │57                      │5A  │5B  │5C  │5D  │ │5F │5G │5H │ │5I │5J │5K │5L │       Numpad 0 │5J     │   │   │
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───┴───┴───┴───┘                └───────┘   └───┘
                                                 ┌──────────┐
                                    2.75u RShift │4C        │
                                                 └──────────┘
┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
│50   │51 │52   │57                         │5B   │5C │5D   │ Tsangan/WKL
└─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
*/
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_all(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,     KC_F12,     KC_0,                             KC_PSCR, KC_SCRL, KC_PAUS,            KC_MPLY, KC_MNXT, KC_VOLU, KC_VOLD,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,    KC_EQL,     KC_TRNS, KC_BSPC,                 KC_INS,  KC_HOME, KC_PGUP,            KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,    KC_RBRC,    KC_BSLS,                          KC_DEL,  KC_END,  KC_PGDN,            KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,    KC_ENT,                                                                             KC_P4,   KC_P5,   KC_P6,   KC_TRNS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,    MO(1),                                                 KC_UP,                       KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, KC_LGUI, MO(1),   KC_RCTL,                                                                                       KC_LEFT, KC_DOWN, KC_RGHT,            KC_TRNS, KC_P0,   KC_PDOT, KC_TRNS),

  [1] = LAYOUT_all(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS,                                 KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                 KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                   KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                                                       KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};
