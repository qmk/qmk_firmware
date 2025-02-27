/* Copyright 2025 @mawaeg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
    // clang-format off
    /*
     *             ┌────────────┐
     *             │ RGB_MOD    │
     * ┌───┬───┬───┼────────────┤
     * │ 7 │ 8 │ 9 │ RGB_TOGGLE │
     * ├───┼───┼───┼────────────┤
     * │ 4 │ 5 │ 6 │ NUM        │
     * ├───┼───┼───┼────────────┤
     * │ 1 │ 2 │ 3 │ 0          │
     * └───┴───┴───┴────────────┘
     */
        [0] = LAYOUT_numpad_4x4(
                             RGB_MOD,
        KC_P7, KC_P8, KC_P9, RGB_TOG,
        KC_P4, KC_P5, KC_P6, KC_NUM,
        KC_P1, KC_P2, KC_P3, KC_P0
    )
    // clang-format on
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
};
#endif

#ifdef OLED_ENABLE

const char *rgb_matrix_effect_names[] = {
    "None",                             
    "Solid Color",
    "Alphas Mods",
    "Gradient Up/Down",
    "Gradient Left/Right",
    "Breathing",
    "Band Saturation",
    "Band Value",
    "Band Pinwheel Sat",
    "Band Pinwheel Val",
    "Band Spiral Sat",
    "Band Spiral Val",
    "Cycle All",
    "Cycle Left/Right",
    "Cycle Up/Down",
    "Cycle Out/In",
    "Cycle Out/In Dual",
    "Rainbow Chevron",
    "Cycle Pinwheel",
    "Cycle Spiral",
    "Dual Beacon",
    "Rainbow Beacon",
    "Rainbow Pinwheels",
    "Flower Blooming",
    "Raindrops",
    "Jellybean Raindrops",
    "Hue Breathing",
    "Hue Pendulum",
    "Hue Wave",
    "Pixel Fractal",
    "Pixel Flow",
    "Pixel Rain",
    "Typing Heatmap",
    "Digital Rain",
    "Reactive Simple",
    "Reactive",
    "Reactive Wide",
    "Reactive Multiwide",
    "Reactive Cross",
    "Reactive Multicross",
    "Reactive Nexus",
    "Reactive Multinexus",
    "Splash",
    "Multisplash",
    "Solid Splash",
    "Solid Multisplash",
    "Starlight",
    "Starlight Dual Hue",
    "Starlight Dual Sat",
    "Riverflow",
    "Effect Max"
};

bool oled_task_user(void) {

    oled_write_ln_P(PSTR("Mode: "), false);
    oled_write_ln(rgb_matrix_effect_names[rgb_matrix_get_mode()], false);

    oled_write_ln_P(PSTR("RGB Speed: "), false);
    char speedBuffer[4];
    uint8_t speedPercentage = (uint8_t)(((float)rgb_matrix_get_speed() / 255.0) * 100.0);  // Proper float division
    sprintf(speedBuffer, "%d", speedPercentage);
    oled_write(speedBuffer, false);
    oled_write("%  ", false);
    return false;
}
#endif
