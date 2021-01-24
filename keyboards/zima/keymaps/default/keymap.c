/* Copyright 2019 Thomas Baart
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

int micstate = 1;

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL };
enum custom_keycodes {
    MICMUTE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MICMUTE:
        if (record->event.pressed) {
            if (micstate == 1){
                SEND_STRING(SS_LCMD(SS_LSFT(SS_TAP(X_F12)))); // shortcut to enable/disable system microphone (macOS) based on an automator (apple)script
                rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);
                micstate = 0;
            }
            else {
                SEND_STRING(SS_LCMD(SS_LSFT(SS_TAP(X_F12)))); // shortcut to enable/disable system microphone (macOS) based on an automator (apple)script
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
                micstate = 1;
            }
        } else {
            // when keycode MICMUTE is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 KC_MUTE,  RGB_MOD,  MICMUTE,
                 KC_P3,  KC_P4,  KC_P5,
                 KC_P6,   KC_P7,  KC_P8,
                 KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK)
};

// Stuff to do at init
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
}
//

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
    render_qmk_logo();
}
#endif

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume UP/DOWN
        if (clockwise) {
            tap_code16(C(KC_VOLU));
        } else {
            tap_code16(C(KC_VOLD));
        }
    }
}
#endif
