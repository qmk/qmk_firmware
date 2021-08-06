/* Copyright 2020 Regan Palmer
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

enum layers {
  _BASE,
  _RAISE,
  _ADJUST,
  _GAME,
};

#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define GAME TG(_GAME)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_MPLY, KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PSCR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_BSPC,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,          RAISE,            KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL),

    [_RAISE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_ESC,  KC_GRV,  KC_BSLS, KC_UP,   KC_MINS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_TRNS,
        KC_TAB,  KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, ADJUST,  KC_EQL,  KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_ADJUST] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  GAME,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
        RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_GAME] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    GAME, KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PSCR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_BSPC,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,          KC_NO,            KC_SPC,  KC_RGUI, KC_RALT, KC_RCTL)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
	switch (get_highest_layer(layer_state)) {
        case _BASE:
             if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
            break;
        case _RAISE:
            if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
            break;
		case _ADJUST:
			if (clockwise) {
            tap_code(KC_MS_WH_RIGHT);
        } else {
            tap_code(KC_MS_WH_LEFT);
        }
			break;
        case _GAME:
             if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
            break;
    }
    return true;
}

char wpm[10];

void oled_task_user(void) {
    sprintf(wpm, "WPM: %03d", get_current_wpm());

    // Host Keyboard Layer Status
    oled_write_P(PSTR("       rainkeeb \n"), false);
    oled_write_P(PSTR(" Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR(" "), false);
    oled_write(wpm, false);
}
