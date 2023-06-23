/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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

// safe range starts at `USER_SAFE_RANGE` instead.

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 C(KC_C), KC_BTN1, KC_BTN3, KC_BTN2, MO(1), KC_BTN4, KC_BTN5, DPI_CONFIG),
    [1] = LAYOUT(
                 RGB_HUI, RGB_MOD, RGB_TOG, RGB_RMOD, MO(1), KC_VOLU, KC_VOLD, QK_BOOT)
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW( KC_WH_D, KC_WH_U ) },
    [1] = { ENCODER_CCW_CW( RGB_HUD, RGB_HUI ) },
};
#endif

#ifdef RGBLIGHT_ENABLE
void eeconkfig_init_user(void) {
    rgblight_enable();
#    ifdef RGBLIGHT_EFFECT_TWINKLE
    rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5);
#    else
    rgblight_mode(RGBLIGHT_MODE_BREATHING + 5);
#    endif
    rgblight_sethsv(HSV_MAGENTA);
}
#endif
