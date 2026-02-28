/* Copyright 2020 KemoNine
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
/* Keymap (Base Layer) Default Layer
   * |----------------------------|
   * | 1 | 2  | 3  | 4 |          |
   * | 5 | 6  | 7  | 8 |          |
   * | 9 | 10 | 11 |              |
   * |----------------------------|
   */
[0] = LAYOUT(
  MS_BTN4, MS_BTN2, MS_UP,   MS_BTN1,
  MS_BTN5, MS_LEFT, MS_DOWN, MS_RGHT,
  MS_ACL0, MS_ACL1, MS_ACL2
  )
};

// Standard encoder functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Process encoder rotational movements
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_DOWN);
        } else {
            tap_code(KC_AUDIO_VOL_UP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    return true;
}

// Encoder press / tilt event handling
// the core lynepad implementation will update the below variables on each matrix scan
// Update the various codes below for customizing the tilt / push config

extern int16_t enc1Center;
extern int16_t enc1CenterPrev;
extern int16_t enc2Center;
extern int16_t enc2CenterPrev;
extern int16_t enc2Up;
extern int16_t enc2UpPrev;
extern int16_t enc2Down;
extern int16_t enc2DownPrev;
extern int16_t enc2Left;
extern int16_t enc2LeftPrev;
extern int16_t enc2Right;
extern int16_t enc2RightPrev;

void matrix_scan_user(void) {
    if (enc1Center != enc1CenterPrev) {
        if (enc1Center < ENC_TILT_THRESHOLD) {
        }
        else {
            reset_keyboard();
        }
    }
    if (enc2Center != enc2CenterPrev) {
        if (enc2Center < ENC_TILT_THRESHOLD) {
            register_code16(MS_BTN3);
        }
        else {
            unregister_code16(MS_BTN3);
        }
        /*
         * Encoder sets ALL values when center is pressed so bail out at this point
         * to avoid the rest of the encoder buttons registering events
         */
        return;
    }
    if (enc2Up != enc2UpPrev) {
        if (enc2Up < ENC_TILT_THRESHOLD) {
        }
        else {
            rgblight_increase_val_noeeprom();
        }
    }
    if (enc2Down != enc2DownPrev) {
        if (enc2Down < ENC_TILT_THRESHOLD) {
        }
        else {
            rgblight_decrease_val_noeeprom();
        }
    }
    if (enc2Left != enc2LeftPrev) {
        if (enc2Left < ENC_TILT_THRESHOLD) {
        }
        else {
            rgblight_toggle_noeeprom();
        }
    }
    if (enc2Right != enc2RightPrev) {
        if (enc2Right < ENC_TILT_THRESHOLD) {
        }
        else {
            rgblight_step_noeeprom();
        }
    }
}
