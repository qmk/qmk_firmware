/*
Copyright 2020 Evy Dekkers

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

RGB_MATRIX_EFFECT(AUDIO_VISUALIZATION_COL)
RGB_MATRIX_EFFECT(AUDIO_VISUALIZATION_ROW)


#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
uint8_t global_r_power_state[MATRIX_ROWS];
uint8_t global_c_power_state[MATRIX_COLS];

// bool AUDIO_VISUALIZATION_COL(effect_params_t* params) {
//     // HSV hsv = rgb_matrix_config.hsv;
//     // RGB rgb = hsv_to_rgb(hsv);
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);
//     for (uint8_t i = led_min ; i < led_max; i++) {
//         rgb_matrix_set_color(i, global_r_state[i], global_g_state[i], global_b_state[i]);
//     }
//     return led_max < DRIVER_LED_TOTAL;
// }




static HSV AUDIO_VISUALIZATION_COL_math(HSV hsv, uint8_t i, uint8_t time) {
    // uint8_t cur_row = (uint8_t)((MATRIX_ROWS-1)*g_led_config.point[i].y/64);
    uint8_t cur_col = (uint8_t)((MATRIX_COLS-1)*g_led_config.point[i].x/224);
    uint8_t cur_row2height_index = MATRIX_ROWS - (uint8_t)((MATRIX_ROWS-1)*g_led_config.point[i].y/64) - 1;
    uint8_t max_height_cur_col = (uint8_t)(global_c_power_state[cur_col]*MATRIX_ROWS/10);

    if (max_height_cur_col >= 1 && (max_height_cur_col - 1) >= cur_row2height_index) {
        hsv.h += abs8(g_led_config.point[i].y - k_rgb_matrix_center.y) + (g_led_config.point[i].x - time);
    } else {
        hsv.h = 0;
        hsv.v = 0;
    }
    return hsv;
}

static HSV AUDIO_VISUALIZATION_ROW_math(HSV hsv, uint8_t i, uint8_t time) {
    uint8_t cur_row = (uint8_t)((MATRIX_ROWS-1)*g_led_config.point[i].y/64);
    // uint8_t cur_col2height_index = MATRIX_COLS - (uint8_t)((MATRIX_COLS-1)*g_led_config.point[i].x/224) - 1;
    uint8_t cur_col2height_index = (uint8_t)((MATRIX_COLS-1)*g_led_config.point[i].x/224);

    uint8_t max_height_cur_row = (uint8_t)(global_r_power_state[cur_row]*MATRIX_COLS/10);


    if (max_height_cur_row >= 1 && (max_height_cur_row - 1) >= cur_col2height_index) {
        hsv.h += abs8(g_led_config.point[i].y - k_rgb_matrix_center.y) + (g_led_config.point[i].x - time);
    } else {
        hsv.h = 0;
        hsv.v = 0;
    }
    return hsv;
}
bool AUDIO_VISUALIZATION_COL(effect_params_t* params) {
    // HSV hsv = rgb_matrix_config.hsv;
    // RGB rgb = hsv_to_rgb(hsv);
    return effect_runner_i(params, &AUDIO_VISUALIZATION_COL_math);
}

bool AUDIO_VISUALIZATION_ROW(effect_params_t* params) {
    return effect_runner_i(params, &AUDIO_VISUALIZATION_ROW_math);
}
// static HSV RAINBOW_MOVING_CHEVRON_math(HSV hsv, uint8_t i, uint8_t time) {
//     hsv.h += abs8(g_led_config.point[i].y - k_rgb_matrix_center.y) + (g_led_config.point[i].x - time);
//     return hsv;
// }
// static HSV RAINBOW_BEACON_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
//     hsv.h += ((g_led_config.point[i].y - k_rgb_matrix_center.y) * 2 * cos + (g_led_config.point[i].x - k_rgb_matrix_center.x) * 2 * sin) / 128;
//     return hsv;
// }
// static HSV RAINBOW_PINWHEELS_math(HSV hsv, int8_t sin, int8_t cos, uint8_t i, uint8_t time) {
//     hsv.h += ((g_led_config.point[i].y - k_rgb_matrix_center.y) * 3 * cos + (56 - abs8(g_led_config.point[i].x - k_rgb_matrix_center.x)) * 3 * sin) / 128;
//     return hsv;
// }

// bool RAINBOW_PINWHEELS(effect_params_t* params) { return effect_runner_sin_cos_i(params, &RAINBOW_PINWHEELS_math); }
// bool RAINBOW_BEACON(effect_params_t* params) { return effect_runner_sin_cos_i(params, &RAINBOW_BEACON_math); }
// bool RAINBOW_MOVING_CHEVRON(effect_params_t* params) { return effect_runner_i(params, &RAINBOW_MOVING_CHEVRON_math); }



#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
