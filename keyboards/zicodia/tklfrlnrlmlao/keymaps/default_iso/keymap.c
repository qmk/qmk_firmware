// Copyright 2022 Zicodia (@Zicodia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐┌───┬───┬───┐┌───┬───┬───┐ ┌───┬───┬───┐
     * │ Q ││ W │ E │ R ││ T │ Y │ U │ │ I │ O │ P │
     * └───┘└───┴───┴───┘└───┴───┴───┘ ├───┼───┼───┤
     * ┌───┬───┬───┬───┬───┬───┬─────┐ │ K │ L │ENT│
     * │ A │ S │ D │ F │ G │ H │ J   │ └───┴───┴───┘
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │     ┌───┐
     * │Z/Sf│ X │ C │ V │ B │ N │    │     │UP │
     * ├────┼───┼───┴───┴───┼───┼────┤ ┌───┼───┼───┐
     * │CTRL│ALT│ SPACE     │WIN│MO1 │ │LFT│DWN│RT │
     * └────┴───┴───────────┴───┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_iso(
        KC_Q,        KC_W,      KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,
        KC_A,        KC_S,      KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_ENT,
        SFT_T(KC_Z), KC_X,      KC_C,       KC_V,       KC_B,       KC_N,                               KC_UP,
        KC_LCTL,     KC_LALT,               KC_SPC,                 KC_RGUI,    MO(1),      KC_LEFT,    KC_DOWN,    KC_RGHT
    ),
    /*
     * ┌───┐┌───┬───┬───┐┌───┬───┬───┐ ┌───┬───┬───┐
     * │ 1 ││ 2 │ 3 │ 4 ││ 5 │ 6 │ 7 │ │ 8 │ 9 │ 0 │
     * └───┘└───┴───┴───┘└───┴───┴───┘ ├───┼───┼───┤
     * ┌───┬───┬───┬───┬───┬───┬─────┐ │ [ │ ] │ \ │
     * │TAB│   │   │   │ - │ = │BSPC │ └───┴───┴───┘
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │     ┌───┐
     * │    │   │   │   │   │ ; │    │     │SFT│
     * ├────┼───┼───┴───┴───┼───┼────┤ ┌───┼───┼───┐
     * │    │   │           │MO2│    │ │ , │ . │ / │
     * └────┴───┴───────────┴───┴────┘ └───┴───┴───┘
     */
    [1] = LAYOUT_iso(
        KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,
        KC_TAB,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MINS,    KC_EQL,     KC_BSPC,    KC_LBRC,    KC_RBRC,    KC_BSLS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_SCLN,                            KC_RSFT,
        KC_TRNS,    KC_TRNS,                KC_TRNS,                MO(2),      KC_TRNS,    KC_COMM,    KC_DOT,     KC_SLSH
    ),
    /*
     * ┌───┐┌───┬───┬───┐┌───┬───┬───┐ ┌───┬───┬───┐
     * │ESC││F1 │F2 │F3 ││F4 │F5 │F6 │ │F7 │F8 │F9 │
     * └───┘└───┴───┴───┘└───┴───┴───┘ ├───┼───┼───┤
     * ┌───┬───┬───┬───┬───┬───┬─────┐ │F10│F11│F12│
     * │   │   │   │   │   │   │     │ └───┴───┴───┘
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │     ┌───┐
     * │    │   │   │   │   │   │    │     │   │
     * ├────┼───┼───┴───┴───┼───┼────┤ ┌───┼───┼───┐
     * │    │   │           │   │    │ │   │   │   │
     * └────┴───┴───────────┴───┴────┘ └───┴───┴───┘
     */
    [2] = LAYOUT_iso(
        KC_ESC,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_F10,     KC_F11,     KC_F12,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,                KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    /*
     * ┌───┐┌───┬───┬───┐┌───┬───┬───┐ ┌───┬───┬───┐
     * │   ││   │   │   ││   │   │   │ │   │   │   │
     * └───┘└───┴───┴───┘└───┴───┴───┘ ├───┼───┼───┤
     * ┌───┬───┬───┬───┬───┬───┬─────┐ │   │   │   │
     * │   │   │   │   │   │   │     │ └───┴───┴───┘
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │     ┌───┐
     * │    │   │   │   │   │   │    │     │   │
     * ├────┼───┼───┴───┴───┼───┼────┤ ┌───┼───┼───┐
     * │    │   │           │   │    │ │   │   │   │
     * └────┴───┴───────────┴───┴────┘ └───┴───┴───┘
     */
    [4] = LAYOUT_iso(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,
        KC_TRNS,    KC_TRNS,                KC_TRNS,                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    )
};
