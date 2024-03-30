/* Copyright 2023 Deemen17
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum compaq_keycodes {
    TBMUL = SAFE_RANGE,
    TBMUL_TOG,
    TBSCRL,
    TBSCRL_TOG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsp│Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│Fn │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤
     * │Ctrl │GUI│ Alt │                           │ Alt │GUI│ Ctrl│
     * └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
     */
    [0] = LAYOUT_all(
        TBMUL,  TBMUL_TOG,    TBSCRL,    TBSCRL_TOG,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, KC_RGUI, KC_RCTL
    )

};

bool tb_disable_multiplier = false;
bool tb_scroll = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TBMUL:
            if (record->event.pressed) {
                tb_disable_multiplier = true;
            } else {
                tb_disable_multiplier = false;
            }
            return false;
        case TBMUL_TOG:
            if (record->event.pressed) {
                tb_disable_multiplier = !tb_disable_multiplier;
            }
            return false;
        case TBSCRL:
            if (record->event.pressed) {
                tb_scroll = true;
            } else {
                tb_scroll = false;
            }
            return false;
        case TBSCRL_TOG:
            if (record->event.pressed) {
                tb_scroll = !tb_scroll;
            }
            return false;
    }

    return true;
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (tb_disable_multiplier) {
        mouse_report->x = mouse_report->x / (PS2_MOUSE_X_MULTIPLIER);
        mouse_report->y = mouse_report->y / (PS2_MOUSE_Y_MULTIPLIER);
    }

    if (tb_scroll) {
        mouse_report->v = -mouse_report->y / (PS2_MOUSE_SCROLL_DIVISOR_V);
        mouse_report->h = mouse_report->x / (PS2_MOUSE_SCROLL_DIVISOR_H);
        mouse_report->x = 0;
        mouse_report->y = 0;
    }
}
