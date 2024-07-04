/* Copyright 2024 Clear <Clear@163.com>
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
#include <stdint.h>
#include <stdbool.h>

#include "quantum.h"

#include "matrix.h"
#include "timer.h"

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#    include "led.h"
#endif

/**************************** Matrix *********************************/
// 矩阵初始化之前执行
void keyboard_pre_init_kb(void) {
#ifdef RGB_MATRIX_SWITCH_PIN
    gpio_set_pin_output(RGB_MATRIX_SWITCH_PIN);
    gpio_write_pin(RGB_MATRIX_SWITCH_PIN, true);
#endif
}

// 初始化矩阵
void keyboard_post_init_kb(void) {
// 检查灯开关
#ifdef RGBLIGHT_ENABLE
    // Enable the LED layers
    // rgblight_layers = tab_rgb_layers;
    rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
#endif
    keyboard_post_init_user();
}

// 矩阵扫描
void housekeeping_task_kb(void) {
#if defined(RGB_MATRIX_ENABLE) && defined(EEPROM_ENABLE) && defined(RGB_MATRIX_SWITCH_PIN)
    // rgb_matrix 关闭时断电
    if (rgb_matrix_is_enabled() != cp_cfg_led_power_get()) {
        cp_cfg_led_power_toggle();
        gpio_write_pin(RGB_MATRIX_SWITCH_PIN, rgb_matrix_is_enabled());
    }
#endif
}

#ifdef RGB_MATRIX_ENABLE
// rgb动画锁定颜色
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(RBG_INDEX_CAPS, RGB_WHITE);
    }

    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(RBG_INDEX_SCROLL, RGB_WHITE);
    }

    if (layer_state_is(1)) {
        rgb_matrix_set_color(RBG_INDEX_FN, RGB_WHITE);
    }

    return false;
}
#endif
