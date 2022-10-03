/* Copyright 2021 rate
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
#include <stdio.h>
#include "keymap_japanese.h"
#include "lib/bme280.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
      KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,     KC_F6,    KC_F7,    KC_F8,     KC_F9,     KC_F10,     KC_F11,  KC_F12,                        KC_MPLY,
      KC_ZKHK,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    JP_MINS,  JP_CIRC,  JP_YEN,  KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,      KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    JP_AT,    JP_LBRC,                      KC_DEL,  KC_END,  KC_PGDN,
      KC_ENT,        KC_A,    KC_S,   KC_D,   KC_F,   KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    JP_SCLN, JP_COLN,  JP_RBRC,       KC_ENT,
      KC_LSFT,         KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,    KC_M,   JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS,               KC_RSFT,                KC_UP,
      KC_LCTRL,  KC_LGUI,  KC_LALT,   KC_DEL,    KC_SPC,      KC_SPC,      LT(_FN, KC_ESC),     JP_KANA,   KC_RALT,     KC_APP,     KC_RCTRL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                       KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,                        KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4,    KC_5,    KC_6,         KC_TRNS,
      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1,    KC_2,    KC_3,                KC_TRNS,              KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_TRNS,          KC_TRNS,          KC_TRNS,    KC_0,    JP_DOT,    JP_DOT,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    )
};



/* OLED */
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

static void print_airstate(void) {
    char airstate_str[32];
    double temp;
    double press;
    double hum;

    temp = bme280_getTemp();
    press = bme280_getPress();
    hum = bme280_getHum();

    oled_write_ln_P(PSTR("\nTemp   Press    Hum"), false);
    snprintf(airstate_str, sizeof(airstate_str), "%ddeg  %dhPa  %d%% \n", (int)temp, (int)press, (int)hum );
    oled_write(airstate_str, false);

    return;
}

static keyrecord_t keylog_record;
static void print_keylog(void) {
    char keylog_str[32];

    oled_write_ln_P(PSTR("\nKeylog"), false);
    snprintf(keylog_str, sizeof(keylog_str), "row:%d col:%d", keylog_record.event.key.row, keylog_record.event.key.col );
    oled_write(keylog_str, false);

    return;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    oled_write_ln_P(PSTR("  - PistachioPro -"), false);
    print_airstate();
    print_keylog();

    return false;
}

/* Encoder */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return true;
}

/* Keyboard */
void keyboard_post_init_user(void) {
    bme280_init();
}

void housekeeping_task_user(void) {
    bme280_exec();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keylog_record = *record;
    }

    return true;
}
