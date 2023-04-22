// Copyright 2023 Synth-and-Keys (@Synth-and-Keys)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * ----------------------------------------------------------------
    * |        |         |         |     Ctrl+0      |  GUI+Shift+S  |
    * ----------------------------------------------------------------
    * |        |  Mute   |         |      Copy       |     Paste     |
    * ----------------------------------------------------------------
    * |  Prev  |  Pause  |  Next   |                 |               |
    * ----------------------------------------------------------------
    * |  Home  |   Up    |   End   |     Ctrl+T      |    Ctrl+W     |
    * ----------------------------------------------------------------
    * |  Left  |  Down   |  Right  |  Shift+Alt+Tab  |    Alt+Tab    |
    * ----------------------------------------------------------------
     */
    [0] = LAYOUT(
                                             (C(KC_0)),  (G(S(KC_S))),
                   KC_MUTE,                  (C(KC_C)),     (C(KC_V)),
        KC_MPRV,   KC_MPLY,    KC_MNXT,
        KC_HOME,     KC_UP,     KC_END,      (C(KC_T)),     (C(KC_W)),
        KC_LEFT,   KC_DOWN,   KC_RIGHT, (S(C(KC_TAB))),   (C(KC_TAB))
    )
};

    /* LAYER TEMPLATE
    * ------------------------------------
    * |      |      |      |      |      |
    * ------------------------------------
    * |      |      |      |      |      |
    * ------------------------------------
    * |      |      |      |      |      |
    * ------------------------------------
    * |      |      |      |      |      |
    * ------------------------------------
    * |      |      |      |      |      |
    * ------------------------------------
     */