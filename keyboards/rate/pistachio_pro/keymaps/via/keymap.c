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
    _FN,
    _RESERVE_0,
    _RESERVE_1
};

static uint8_t encoder_state = 0;
static const keypos_t ENC_CW = {.row = 0, .col = 14 };
static const keypos_t ENC_CCW = {.row = 0, .col = 15 };

#define LAYOUT_via( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, ENC_CW, ENC_CCW, k013, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114, k115, k116, k117, \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214, k215, \
    k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, \
    k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412, k413, \
    k500, k501, k502, k503, k504, k505, k506, k507, k508, k509, k510, k511, k512, k513 ) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011, k012, k013, ENC_CW, ENC_CCW, KC_NO, KC_NO }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111, k112, k113, k114,  k115,  k116,  k117  }, \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211, k212, k213, k214,  k215,  KC_NO, KC_NO }, \
    { k300, k301, k302, k303, k304, k305, k306, k307, k308, k309, k310, k311, k312, k313, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k400, k401, k402, k403, k404, k405, k406, k407, k408, k409, k410, k411, k412, k413, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { k500, k501, k502, k503, k504, k505, k506, k507, k508, k509, k510, k511, k512, k513, KC_NO, KC_NO, KC_NO, KC_NO }  \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_via(
      KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,     KC_F6,    KC_F7,    KC_F8,     KC_F9,     KC_F10,     KC_F11,  KC_F12,        KC_VOLU,KC_VOLD,KC_MPLY,
      JP_ZKHK,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    JP_MINS,  JP_CIRC,  JP_YEN,  KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,      KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    JP_AT,    JP_LBRC,                      KC_DEL,  KC_END,  KC_PGDN,
      JP_EISU,       KC_A,    KC_S,   KC_D,   KC_F,   KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    JP_SCLN, JP_COLN,  JP_RBRC,       KC_ENT,
      KC_LSFT,         KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,    KC_M,   JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS,               KC_RSFT,              KC_UP,
      KC_LCTL,  KC_LGUI,  KC_LALT,   JP_MHEN,    KC_SPC,      KC_SPC,      LT(_FN, JP_HENK),    JP_KANA,   KC_RALT,     KC_APP,    KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_via(
      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_VOLU,KC_VOLD,KC_MPLY,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,                        KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4,    KC_5,    KC_6,         KC_TRNS,
      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1,    KC_2,    KC_3,                KC_TRNS,              KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_TRNS,          KC_TRNS,          KC_TRNS,    KC_0,    JP_DOT,    JP_DOT,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RESERVE_0] = LAYOUT_via(
      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_VOLU,KC_VOLD,KC_MPLY,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS,              KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_TRNS,          KC_TRNS,          KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RESERVE_1] = LAYOUT_via(
      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,       KC_VOLU,KC_VOLD,KC_MPLY,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,
      KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,           KC_TRNS,              KC_TRNS,
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_TRNS,          KC_TRNS,          KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
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
void encoder_action_unregister(void) {
    if (encoder_state) {
        keyevent_t encoder_event = (keyevent_t) {
            .key = encoder_state >> 1 ? ENC_CW : ENC_CCW,
            .pressed = false,
            .time = timer_read(),
            .type = KEY_EVENT
        };
        encoder_state = 0;
        action_exec(encoder_event);
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? ENC_CW : ENC_CCW,
        .pressed = true,
        .time = timer_read(),
        .type = KEY_EVENT
    };
    encoder_state = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_user(void) {
    encoder_action_unregister();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
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
