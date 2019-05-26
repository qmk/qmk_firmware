/* Copyright 2019 zk-phi
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

#include "haptic.c"
#include "lightshow.c"

enum layers {
    DEFAULT,
    VOLUP,
    VOLDN,
    AMPUP,
    AMPDN,
    VIB
};

enum custom_keycodes {
    KC_AMPUP = SAFE_RANGE,
    KC_AMPDOWN,
    KC_VIBUP,
    KC_VIBDOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        LT(VOLUP, KC_MEDIA_REWIND),
        LT(VOLDN, KC_MEDIA_FAST_FORWARD),
        LT(AMPUP, KC_MEDIA_PLAY_PAUSE),
        LT(AMPDN, KC_MEDIA_PLAY_PAUSE)
    ),
    [VOLUP] = LAYOUT(
        _______, LT(VIB, KC__VOLUP), _______, _______
    ),
    [VOLDN] = LAYOUT(
        LT(VIB, KC__VOLDOWN), _______, _______, _______
    ),
    [AMPUP] = LAYOUT(
        _______, _______, _______, KC_AMPUP
    ),
    [AMPDN] = LAYOUT(
        _______, _______, KC_AMPDOWN, _______
    ),
    [VIB] = LAYOUT(
        _______, _______, KC_VIBDOWN, KC_VIBUP
    )
};

void matrix_scan_user (void) {
    haptic_task();
    lightshow_task();
}

void matrix_init_user (void) {
    haptic_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
          case KC_AMPUP:
            if (lightshow_amp < 10) lightshow_amp += 0.5;
            return false;
          case KC_AMPDOWN:
            if (lightshow_amp > 0) lightshow_amp -= 0.5;
            return false;
          case KC_VIBUP:
            vib_duration += 5;
            return false;
          case KC_VIBDOWN:
            if (vib_duration > 0) vib_duration -= 5;
            return false;
        }
    }
    return true;
}
