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

/* RGB LIGHT **************************************************************/
#ifdef RGBLIGHT_ENABLE
static bool rgblight_process_record_kb(uint16_t keycode) {
    bool is_function_key = true;

    switch (keycode) {
        case RGB_TOG: {
            rgblight_toggle();
        } break; // 灯效开关
        case RGB_MOD: {
            rgblight_step();
        } break; // 灯效顺序切换
        case RGB_RMOD: {
            rgblight_step_reverse();
        } break; // 灯效逆序切换
        case RGB_VAI: {
            rgblight_increase_val();
        } break; // 灯效增加亮度
        case RGB_VAD: {
            rgblight_decrease_val();
        } break; // 灯效降低亮度
        case RGB_HUI: {
            rgblight_increase_hue();
        } break; // 灯效增加色调
        case RGB_HUD: {
            rgblight_decrease_hue();
        } break; // 灯效降低色调
        case RGB_SAI: {
            rgblight_increase_sat();
        } break; // 灯效增加饱和度
        case RGB_SAD: {
            rgblight_decrease_sat();
        } break; // 灯效降低饱和度
        case RGB_SPI: {
            rgblight_increase_speed();
        } break; // 灯效增加速度
        case RGB_SPD: {
            rgblight_decrease_speed();
        } break; // 灯效降低速度
        default: {
            is_function_key = false;
        } break;
    }

    return !is_function_key;
}
#endif // RGBLIGHT_ENABLE

/* RGB MATRIX **************************************************************/
#ifdef RGB_MATRIX_ENABLE
static bool rgb_matrix_process_record_kb(uint16_t keycode) {
    bool is_function_key = true;

    switch (keycode) {
        case RGB_TOG: {
            rgb_matrix_toggle();
        } break; // 灯效开关
        case RGB_MOD: {
            rgb_matrix_step();
        } break; // 灯效顺序切换
        case RGB_RMOD: {
            rgb_matrix_step_reverse();
        } break; // 灯效逆序切换
        case RGB_VAI: {
            rgb_matrix_increase_val();
        } break; // 灯效增加亮度
        case RGB_VAD: {
            rgb_matrix_decrease_val();
        } break; // 灯效降低亮度
        case RGB_HUI: {
            rgb_matrix_increase_hue();
        } break; // 灯效增加色调
        case RGB_HUD: {
            rgb_matrix_decrease_hue();
        } break; // 灯效降低色调
        case RGB_SAI: {
            rgb_matrix_increase_sat();
        } break; // 灯效增加饱和度
        case RGB_SAD: {
            rgb_matrix_decrease_sat();
        } break; // 灯效降低饱和度
        case RGB_SPI: {
            rgb_matrix_increase_speed();
        } break; // 灯效增加速度
        case RGB_SPD: {
            rgb_matrix_decrease_speed();
        } break; // 灯效降低速度
        default: {
            is_function_key = false;
        } break;
    }

    return !is_function_key;
}
#endif // RGB_MATRIX_ENABLE

/**************************** Matrix *********************************/
// 矩阵初始化之前执行
void keyboard_pre_init_kb(void) {
#ifdef RGB_MATRIX_SWITCH_PIN
    gpio_set_pin_output(RGB_MATRIX_SWITCH_PIN);
    gpio_write_pin(RGB_MATRIX_SWITCH_PIN, true);
#endif
}

// 初始化矩阵
void matrix_init_kb(void) {
// 检查灯开关
#ifdef RGBLIGHT_ENABLE
    // Enable the LED layers
    // rgblight_layers = tab_rgb_layers;
    rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
#endif
}

// 矩阵扫描
void matrix_scan_user(void) {
#if defined(RGB_MATRIX_ENABLE) && defined(EEPROM_ENABLE) && defined(RGB_MATRIX_SWITCH_PIN)
    // rgb_matrix 关闭时断电
    if (rgb_matrix_is_enabled() != cp_cfg_led_power_get()) {
        cp_cfg_led_power_toggle();
        gpio_write_pin(RGB_MATRIX_SWITCH_PIN, rgb_matrix_is_enabled());
    }
#endif
}

// 是否为RGB Matrix模式
static bool is_rgb_matrix_type = false;

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) return true;

    // 按键操作
    if (is_rgb_matrix_type) {
#ifdef RGB_MATRIX_ENABLE
        if (!rgb_matrix_process_record_kb(keycode)) {
            return false;
        }
#endif
    } else {
#ifdef RGBLIGHT_ENABLE
        if (!rgblight_process_record_kb(keycode)) {
            return false;
        }
#endif
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
// rgb动画锁定颜色
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
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
