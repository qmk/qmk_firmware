// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "host.h"

extern int tp_buttons;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MS_BTN1:
        case MS_BTN2:
        case MS_BTN3: {
            uint8_t btn = (keycode == MS_BTN1) ? MOUSE_BTN1 :
                          (keycode == MS_BTN2) ? MOUSE_BTN2 : MOUSE_BTN3;
            if (record->event.pressed) {
                tp_buttons |= btn;
            } else {
                tp_buttons &= ~btn;
            }
            report_mouse_t report = {0};
            report.buttons        = tp_buttons;
            host_mouse_send(&report);
            return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ / │ 6 │ 7 │ 8 │ 9 │ 0 │ - │BSp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │  \  │
     * ├────┬┴──┬┴──┬┴──┬┴──┬┴──┬┴───┬───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────┤
     * │Ctl │ A │ S │ D │ F │ G │  [ │ ]  │ H │ J │ K │ L │ ; │ Ent│
     * ├───┬┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬─┴─┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┤
     * │Sft│ Z │ X │ C │ V │ B │ ← │ ↑ │ → │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┴───┼───┼───┴───┼───┼───┼───┼───┼───┤
     * │CAP│Ctl│Ctl│Alt│Win│ Space │ ↓ │ Space │Win│ ← │ ↓ │ ↑ │ → │
     * └───┴───┴───┴───┴───┴───────┴───┴───────┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_SLSH, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_BSLS,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    MS_BTN2,          MS_BTN3, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PGUP, KC_PGDN, KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE,         MS_BTN1,          KC_SPACE,KC_RGUI, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    )
};
