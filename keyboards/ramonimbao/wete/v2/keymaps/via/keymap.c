/* Copyright 2021 Ramon Imbao
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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NO, KC_HOME,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        KC_P4,   KC_P5,   KC_P6,   KC_NO,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
        KC_P0,   KC_NO,   KC_PDOT, KC_NO,   KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RCTL, KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT,
        KC_VOLD, KC_VOLU
    ),
    [1] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______
    ),
};

keyevent_t encoder_ccw = {
    .key = (keypos_t){.row = 12, .col = 0},
    .pressed = false
};

keyevent_t encoder_cw = {
    .key = (keypos_t){.row = 12, .col = 1},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder_ccw)) {
        encoder_ccw.pressed = false;
        encoder_ccw.time = (timer_read() | 1);
        action_exec(encoder_ccw);
    }

    if (IS_PRESSED(encoder_cw)) {
        encoder_cw.pressed = false;
        encoder_cw.time = (timer_read() | 1);
        action_exec(encoder_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        encoder_cw.pressed = true;
        encoder_cw.time = (timer_read() | 1);
        action_exec(encoder_cw);
    } else {
        encoder_ccw.pressed = true;
        encoder_ccw.time = (timer_read() | 1);
        action_exec(encoder_ccw);
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE
// Can probably still be optimized, but I like it as is for clarity
const rgblight_segment_t PROGMEM ll_none[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,1, HSV_OFF},
    {1,1, HSV_OFF},
    {2,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_nl[] = RGBLIGHT_LAYER_SEGMENTS(
    {1,1, HSV_OFF},
    {0,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_cl[] = RGBLIGHT_LAYER_SEGMENTS(
    {2,1, HSV_OFF},
    {0,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_clnl[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_sl[] = RGBLIGHT_LAYER_SEGMENTS(
    {2,1, HSV_OFF},
    {1,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_slnl[] = RGBLIGHT_LAYER_SEGMENTS(
    {1,1, HSV_OFF}
);
const rgblight_segment_t PROGMEM ll_slcl[] = RGBLIGHT_LAYER_SEGMENTS(
    {2,1, HSV_OFF}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    ll_none,
    ll_nl,
    ll_cl,
    ll_clnl,
    ll_sl,
    ll_slnl,
    ll_slcl
);

void keyboard_post_init_kb(void) {
    rgblight_layers = rgb_layers;

    keyboard_post_init_user();
}

bool led_update_kb (led_t led_state) {
    bool res = led_update_user(led_state);

    if (res) {
        uint8_t lock_bits = led_state.scroll_lock << 2 | led_state.caps_lock << 1 | led_state.num_lock;
        for (uint8_t i=0; i<7; i++) {
            rgblight_set_layer_state(i, false);
        }
        if (lock_bits < 7) {
            rgblight_set_layer_state(lock_bits, true);
        }
    }

    return res;
}
#endif
