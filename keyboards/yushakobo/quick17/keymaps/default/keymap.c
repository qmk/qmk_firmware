/* Copyright 2020 yushakobo
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
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _CONTROL,
    _PHOTO,
    _PHOTO_SHIFT,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CONTROL = SAFE_RANGE,
    FN,
    MAC,
    WIN,
    PS_CMRL,
    PS_ZIN,
    PS_ZOUT,
    PS_CSHR,
    PS_CROP,
    PS_LLYR,
    PS_UNDO,
    PS_REDO,
    PS_SHIFT,
    PS_LANG,
    FN_LANG1,
    FN_LANG2
};


#define PS_ERSE KC_E
#define PS_MGWD KC_W
#define PS_EYDR KC_I
#define PS_SLCT KC_A
#define PS_HAND KC_H
#define PS_LASS KC_L
#define PS_MRQE KC_M
#define PS_PEN KC_P
#define PS_MOVE KC_V
#define PS_ZOOM KC_Z
#define PS_BRSD KC_LBRC
#define PS_BRSI KC_RBRC
#define PS_BRSP KC_COMM
#define PS_BRSN KC_DOT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_CONTROL] = LAYOUT(
    KC_TAB,  KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, KC_DEL,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_INS,
    KC_LSFT, KC_ESC,  KC_LALT, KC_SPC,  FN,      KC_ENT
),
    [_PHOTO] = LAYOUT(
    KC_ESC,  PS_ERSE, PS_MGWD, PS_EYDR, PS_ZIN,  KC_BSPC,
    PS_CMRL, PS_SLCT, PS_HAND, PS_LASS, PS_MRQE, PS_PEN,
    KC_LSFT, PS_ZOOM, PS_MOVE, KC_LALT, PS_SHIFT,KC_ENT
),
    [_PHOTO_SHIFT] = LAYOUT(
    KC_ESC,  PS_BRSD, PS_BRSI, PS_UNDO, PS_REDO, KC_DEL,
    PS_CMRL, PS_BRSP, PS_BRSN, PS_CSHR, PS_CROP, PS_LLYR,
    KC_LSFT, PS_LANG, CONTROL, _______, _______, _______
),
    [_FN] = LAYOUT(
    FN_LANG1,FN_LANG2,XXXXXXX, RGB_TOG, KC_MNXT, KC_VOLU,
    PHOTO,   CONTROL, KC_NO,   KC_NO,   KC_MPRV, KC_VOLD,
    MAC,     WIN,     KC_NO,   KC_NO,   _______, KC_MUTE
)
};

static bool mac = true;// keymap_config.swap_ctrl_gui
static bool kana = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
}
