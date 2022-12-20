/*
Copyright 2022 imchipwood && deveth0

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define MUTE_HOLD_DELAY 400
static uint16_t mute_hold_timer = 0;

enum custom_keycodes {
    MUTE_TEAMS = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Media Controls
    /------------------------------------------------------------------------------------`
    |             | Media Prev         |    Media Pause    |    Media Next    |         |
    |             |--------------------|-------------------|------------------|---------|
    |             |    Teams - Mute    |                   |                  |         |
    |             |--------------------|-------------------|------------------|---------|
    |             |                    |                   |                  |         |
    |-------------|--------------------|-------------------|------------------|---------|
    |    Mute     |  TT(1)             |                   |                  |  Enter  |
    \------------------------------------------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_MPRV,    KC_MPLY,  KC_MNXT,    KC_NO,
                    KC_NO,      KC_NO,    KC_NO,      KC_NO,
                    MUTE_TEAMS, KC_NO,    KC_NO,      KC_NO,
        KC_MUTE,    TT(1),      KC_NO,    KC_NO,      KC_NO
    ),
    /*
            SUB LAYER  - RGB controls, Modes on encoder
    /-----------------------------------------------------`
    |             | On/Off  | Bright- | Bright+ |  Reset  |
    |             |---------|---------|---------|---------|
    |             |         | Hue-    | Hue+    |         |
    |             |---------|---------|---------|---------|
    |             |         | Sat-    | Sat+    |         |
    |-------------|---------|---------|---------|---------|
    |             |  TT(1)  | Effect- | Effect+ |         |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    RGB_TOG,    RGB_VAD,     RGB_VAI,      QK_BOOT,
                    KC_NO,      RGB_HUD,     RGB_HUI,      KC_NO,
                    KC_NO,      RGB_SAD,     RGB_SAI,      KC_NO,
        KC_NO,      _______,    RGB_SPD,     RGB_SPI,      KC_NO
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // props to https://www.reddit.com/r/olkb/comments/oewbr2/comment/h49z38r
    switch (keycode) {
        case MUTE_TEAMS:
            if (record->event.pressed) {                               // when keycode MUTE_TEAMS is pressed
                mute_hold_timer = timer_read();                        // mark the time the key was pressed
                tap_code16(LCTL(LSFT(KC_M)));                          // tap Ctrl + Shift + M (mute shortcut)
            } else {                                                   // when keycode MUTE_TEAMS is released
                if (timer_elapsed(mute_hold_timer) > MUTE_HOLD_DELAY)  // if held longer than MUTE_HOLD_DELAY
                    tap_code16(LCTL(LSFT(KC_M)));                      // tap the mute shortcut again
            }                                                          // otherwise do nothing
            break;
    }
    return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            // main layer, volume
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        default:
            // rgb control layer, effects
            if (clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
            break;
    }
    return false;
}
