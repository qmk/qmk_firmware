/* Copyright 2024 keymagichorse
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
#include "config.h"

#if defined(RGBLIGHT_WS2812)
#    include "ws2812.h"
#endif

#include "bhq_common.h"
#include "wireless.h"
#include "transport.h"
#include "report_buffer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    QK_GESC, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC, KC_HOME,
    KC_TAB,  KC_Q,    KC_W,     KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS, KC_PGUP,
    KC_CAPS, KC_A,    KC_S,     KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_PGDN,
    KC_LSFT, KC_Z,    KC_X,     KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,            KC_DEL,
    KC_LCTL, KC_LGUI, KC_LALT,                              KC_SPC,                      KC_RCTL,  MO(1),    KC_LEFT,  KC_DOWN,          KC_RIGHT),
  [1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, BL_SW_0, BL_SW_1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, USB_TOG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS),
  [2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS),
  [3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS),
};

uint8_t sta = 1;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_bhq(keycode, record);
}


bool led_update_user(led_t led_state) {
    // 如果当前是USB连接，或者是蓝牙/2.4G连接且已配对连接状态
    if( (transport_get() > KB_TRANSPORT_USB && wireless_get() == WT_STATE_CONNECTED) || transport_get() == KB_TRANSPORT_USB)
    {
        km_printf("led_update_user\r\n");
    }
    return true;
}

// 无线蓝牙回调函数
void wireless_ble_hanlde_kb(uint8_t host_index,uint8_t advertSta,uint8_t connectSta,uint8_t pairingSta)
{
    km_printf("wireless_ble_hanlde_kb->host_index: %d\r\n",host_index);
    // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙配对模式
    if(connectSta != 1 && advertSta == 1 && pairingSta == 1)
    {
        // 这里第一个参数使用host_index正好对应_rgb_layers的索引
        km_printf("if 1\n");
    }
    // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙非配对模式
    else if(connectSta != 1 && advertSta == 1 && pairingSta == 0)
    {
        km_printf("if 2\n");
    }
    // 蓝牙已连接
    if(connectSta == 1)
    {
        report_buffer_clear();
        layer_clear();
        km_printf("if 3\n");
    }
}
void wireless_rf24g_hanlde_kb(uint8_t connectSta,uint8_t pairingSta)
{
    if(connectSta == 1)
    {
        report_buffer_clear();
        layer_clear();
        km_printf("if 3\n");
    }
}


__attribute__((weak)) bool via_command_kb(uint8_t *data, uint8_t length) {
    return via_command_bhq(data, length);
}
uint8_t is_sleep = 0;
// 低功耗外围设备电源控制
void lpm_device_power_open(void) 
{
    // rgb_matrix_enable();
    // rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);
    // gpio_set_pin_output(WS2812_POWER_PIN);
    // gpio_write_pin_high(WS2812_POWER_PIN);
    if(is_sleep == 1)
    {
        is_sleep = 0;
        ws2812_init();
        rgb_matrix_enable();
        rgb_matrix_set_suspend_state(false);
    }
    gpio_set_pin_output(WS2812_POWER_PIN);
    gpio_write_pin_high(WS2812_POWER_PIN);
}
//关闭外围设备电源
void lpm_device_power_close(void) 
{
    is_sleep = 1;
    // rgb_matrix_disable();
    // gpio_set_pin_output(WS2812_POWER_PIN);
    // gpio_write_pin_low(WS2812_POWER_PIN);

    rgb_matrix_disable();
    rgb_matrix_set_suspend_state(true);
    gpio_set_pin_output(WS2812_POWER_PIN);
    gpio_write_pin_low(WS2812_POWER_PIN);
}


// After initializing the peripheral
void keyboard_post_init_kb(void)
{
    rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);
    gpio_set_pin_output(WS2812_POWER_PIN);
    gpio_write_pin_high(WS2812_POWER_PIN);
}







// 将未使用的引脚设置为输入模拟 
// PS：在6095中，如果不加以下代码休眠时是102ua。如果加了就是30ua~32ua浮动
void lpm_set_unused_pins_to_input_analog(void)
{
    // 禁用调试功能以降低功耗
    DBGMCU->CR &= ~DBGMCU_CR_DBG_SLEEP;   // 禁用在Sleep模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STOP;    // 禁用在Stop模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STANDBY; // 禁用在Standby模式下的调试
    // 在系统初始化代码中禁用SWD接口
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG);

    palSetLineMode(A0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A7, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A15, PAL_MODE_INPUT_ANALOG); 

    palSetLineMode(B0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B15, PAL_MODE_INPUT_ANALOG); 
}
