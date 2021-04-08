/* Copyright 2020 Ramon Imbao
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

#include "pattern.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_VOLD, KC_MUTE, KC_VOLU,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_NO,   KC_SPC,           KC_NO,   KC_RALT, KC_RCTL,                   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_all(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______, _______,          _______,  _______, _______,                   _______, _______, _______
    ),
    [2] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______, _______,          _______,  _______, _______,                   _______, _______, _______
    ),
    [3] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______, _______,          _______, _______, _______,                   _______, _______, _______
    ),
};

keyevent_t encoder_ccw = {
    .key = (keypos_t){.row = 6, .col = 0},
    .pressed = false
};

keyevent_t encoder_cw = {
    .key = (keypos_t){.row = 6, .col = 1},
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

#ifdef OLED_DRIVER_ENABLE
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_frame = 0;

#define FRAME_DURATION 50

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        encoder_cw.pressed = true;
        encoder_cw.time = (timer_read() | 1);
        action_exec(encoder_cw);
        anim_sleep = timer_read32();
        oled_on();
    } else {
        encoder_ccw.pressed = true;
        encoder_ccw.time = (timer_read() | 1);
        action_exec(encoder_ccw);
        anim_sleep = timer_read32();
        oled_on();
    }
}

static void render_pattern(void) {
    void animate(void) {
        oled_set_cursor(4, 0);
        oled_write_raw_P(pattern_a[current_frame], 96);
        oled_set_cursor(4, 1);
        oled_write_raw_P(pattern_b[current_frame], 96);
        oled_set_cursor(4, 2);
        oled_write_raw_P(pattern_a[current_frame], 96);

        current_frame = (current_frame + 1) % 32;
    }

    if (get_current_wpm() != 000) {
        oled_on();
        if (timer_elapsed32(anim_timer) > FRAME_DURATION) {
            anim_timer = timer_read32();
            animate();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            oled_on();
            if (timer_elapsed32(anim_timer) > FRAME_DURATION) {
                anim_timer = timer_read32();
                animate();
            }
        }
    }
}

void oled_task_user(void) {
    // Render Herringbone pattern
    render_pattern();
    oled_render();

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 0);
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_set_cursor(0, 1);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_set_cursor(0, 2);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_render();
}
#endif
