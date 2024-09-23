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
#include "lpm.h"
#include "bhq.h"
#include "outputselect.h"
#include "usb_main.h"

#if defined(BLUETOOTH_BHQ)
#   include "bhq.h"
#   include "km_printf.h"
#   ifdef KM_DEBUG
#       include "km_printf.h"
#   endif
#endif






enum keyboard_user_keycodes {
    BT_1 = QK_USER,
    BT_2,
    BT_3,
    BT_4,
    BT_5,
    BT_6,
    BT_7,
    BT_8,
    BT_9,
    BT_10,
    BT_11,
};
#define BLE_TOG     BT_1    // 切换蓝牙输出 并 开启蓝牙广播（非配对类型）
#define RF_TOG      BT_2    // 切换 2.4ghz输出
#define USB_TOG     BT_3    // 打开USB
#define BL_SW_0     BT_4    // 开启蓝牙通道0（需要打开蓝牙的条件下才行） 短按打开广播 长按开启配对广播
#define BL_SW_1     BT_5    // 开启蓝牙通道1（需要打开蓝牙的条件下才行） 短按打开广播 长按开启配对广播
#define BL_SW_2     BT_6    // 开启蓝牙通道2（需要打开蓝牙的条件下才行） 短按打开广播 长按开启配对广播
// #define BLE_DEL     BT_7    // 删除当前蓝牙绑定
// #define BLE_CLR     BT_8    // 清空所有蓝牙绑定
#define BLE_OFF     BT_9    // 关闭蓝牙连接

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
    QK_GESC, KC_1,    KC_2,     KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSLS, KC_BSPC,
    KC_TAB,  BL_SW_0, BL_SW_1,  BL_SW_2,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,
    KC_CAPS, BLE_TOG, USB_TOG,  KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,     KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,   KC_DEL,
    KC_LCTL, KC_LGUI, KC_LALT,  KC_SPC,   KC_SPC,  KC_SPC,                    KC_SPC,    KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN, KC_RIGHT),
  [1] = LAYOUT_all(
    KC_GRV , KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD, KC_TRNS, CG_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, GU_TOGG,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [2] = LAYOUT_all(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [3] = LAYOUT_all(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

static uint32_t output_mode_press_time = 0;
static uint32_t ble_switch_press_time = 0;
static uint8_t ble_host_index = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    lpm_timer_reset();
    switch (keycode)
    {
        case BLE_TOG:
        {
            if(record->event.pressed)
            {
                output_mode_press_time = timer_read32();
                // gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);
            }
            else 
            {
                // gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
                if(timer_elapsed32(output_mode_press_time) >= 500) 
                {
                    ble_host_index = 0;
                    bhq_OpenBleAdvertising(ble_host_index, 50);
                    set_output(OUTPUT_BLUETOOTH);
                }
            }
            return false;
        }
        case RF_TOG:
        {
            if(record->event.pressed)
            {
                output_mode_press_time = timer_read32();
                // gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);
            }
            else 
            {
                // gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
                if(timer_elapsed32(output_mode_press_time) >= 500) 
                {
                    // TODO: 等待bhq驱动完善
                    set_output(OUTPUT_BLUETOOTH);
                }
            }
            return false;
        }
        case USB_TOG:
        {
            if(record->event.pressed)
            {
                output_mode_press_time = timer_read32();
            }
            else
            {
                if(timer_elapsed32(output_mode_press_time) >= 500) 
                {
                    set_output(OUTPUT_USB);
                }
            }
            return false;
        }
        case BLE_OFF:
        {
            if(record->event.pressed)
            {
                output_mode_press_time = timer_read32();
                // gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);
            }
            else
            {
                // gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
                if(timer_elapsed32(output_mode_press_time) >= 500) 
                {
                    bhq_CloseBleAdvertising();
                }
            }
            return false;
        }
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
            if(record->event.pressed)
            {
                ble_switch_press_time = timer_read32();
                // gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);
            }
            else
            {
                // gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
                switch (keycode)
                {
                    case BL_SW_0:
                        ble_host_index = 0;
                        break;  
                    case BL_SW_1:
                        ble_host_index = 1;
                        break;  
                    case BL_SW_2:
                        ble_host_index = 2;
                        break;  
                }
                if(timer_elapsed32(ble_switch_press_time) >= 500 && timer_elapsed32(ble_switch_press_time) <= 3000)
                {
                    if(where_to_send() == OUTPUT_BLUETOOTH)
                    {
                        bhq_OpenBleAdvertising(ble_host_index, 50);
                    }
                }
                else if(timer_elapsed32(ble_switch_press_time) >= 3000)
                {
                    if(where_to_send() == OUTPUT_BLUETOOTH)
                    {
                        bhq_SetPairingMode(ble_host_index, 50);
                    }
                }
            }
            return false;
    }
    return true;
}

