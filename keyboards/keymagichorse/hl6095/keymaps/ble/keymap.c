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
#include "bhq.h"
#include "outputselect.h"
#include "usb_main.h"

#if defined(BLUETOOTH_BHQ)
#   include "bhq.h"
#   include "battery.h"
#   include "km_printf.h"
#endif

#   if defined(KB_LPM_ENABLED)
#   include "lpm.h"
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
    KC_TAB,  BL_SW_0, BL_SW_1,  RF_TOG,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,      KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLS,
    KC_CAPS, BLE_TOG, USB_TOG,  NK_TOGG,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,  KC_BSLS, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,     KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,   KC_DEL,
    MS_DOWN, KC_VOLU, KC_LALT,  KC_SPC,   KC_SPC,  KC_SPC,                    KC_SPC,    KC_RALT,  MO(1),    KC_LEFT,  KC_DOWN, KC_RIGHT),
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

uint8_t advertSta = 0;
uint8_t connectSta = 0;
uint8_t pairingSta = 0;
uint8_t host_index = 255;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#   if defined(KB_LPM_ENABLED)
    lpm_timer_reset();
#endif
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
                if(timer_elapsed32(output_mode_press_time) >= 300) 
                {
                    ble_host_index = 0;
                    // 打开非配对模式蓝牙广播 10 = 10S
                    bhq_OpenBleAdvertising(ble_host_index, 10);
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
                if(timer_elapsed32(output_mode_press_time) >= 300) 
                {
                    // TODO: 等待bhq驱动完善，这里还是用蓝牙输出来作为qmk的模式切换，在蓝牙模块内会切换成2.4ghz私有连接
                    bhq_switch_rf_easy_kb();
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
                if(timer_elapsed32(output_mode_press_time) >= 300) 
                {
                    // 切换到usb模式 并 关闭蓝牙广播
                    set_output(OUTPUT_USB);
                    bhq_CloseBleAdvertising();
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
                    // 关闭蓝牙广播
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
                // rgblight_blink_layer_repeat(1 , 500, 20);
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
                if(timer_elapsed32(ble_switch_press_time) >= 300 && timer_elapsed32(ble_switch_press_time) <= 1500)
                {
                    // 打开非配对模式蓝牙广播 10 = 10S
                    bhq_OpenBleAdvertising(ble_host_index, 10);
                    set_output(OUTPUT_BLUETOOTH);
                }
                else if(timer_elapsed32(ble_switch_press_time) >= 1500)
                {
                    // 打开 配对模式蓝牙广播 10 = 10S
                    bhq_SetPairingMode(ble_host_index, 10);
                    set_output(OUTPUT_BLUETOOTH);
                }
            }
            return false;
    }
    return true;
}
#if defined(RGBLIGHT_ENABLE) && defined(BLUETOOTH_BHQ) 

const rgblight_segment_t PROGMEM bt_conn1[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_RED} );   // 红
const rgblight_segment_t PROGMEM bt_conn2[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_GREEN} ); // 绿
const rgblight_segment_t PROGMEM bt_conn3[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_BLUE} );  // 蓝
const rgblight_segment_t PROGMEM caps_lock_[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_PURPLE} );  // 紫色
const rgblight_segment_t* const PROGMEM _rgb_layers[] =
    RGBLIGHT_LAYERS_LIST( 
        bt_conn1, bt_conn2,  bt_conn3,caps_lock_
    );


// After initializing the peripheral
void keyboard_post_init_kb(void)
{
    rgblight_disable();
    rgblight_layers = _rgb_layers;
    bhkDevConfigInfo_t model_parma = {
        .vendor_id_source   = 1,
        .verndor_id         = VENDOR_ID,
        .product_id         = PRODUCT_ID,

        .le_connection_interval_min = 10,   // 6 10 上报速度过快更丝滑 功耗更大
        .le_connection_interval_max = 30,
        .le_connection_interval_timeout = 500,
        .tx_poweer = 0x3D,    

#if BHQ_READ_VOLTAGE_ENABLED == TRUE
        .mk_is_read_battery_voltage = TRUE,
        .mk_adc_pga = 1,
        .mk_rvd_r1 = BHQ_R_UPPER,
        .mk_rvd_r2 = BHQ_R_LOWER,
#else
        .mk_is_read_battery_voltage = FALSE,
        .mk_adc_pga = 1,
        .mk_rvd_r1 = 0,
        .mk_rvd_r2 = 0,
#endif
        .sleep_1_s = 30,            // 一级休眠功耗 （蓝牙保持连接 唤醒后发送按键有一定的延时）
        .sleep_2_s = 300,           // 二级休眠功耗（相当于关机模式 蓝牙会断开）

        .bleNameStrLength = strlen(PRODUCT),
        .bleNameStr = PRODUCT
    };

    bhq_ConfigRunParam(model_parma);

}


void rgb_adv_unblink_all_layer(void) {
    for (uint8_t i = 0; i < 3; i++) {
        rgblight_unblink_layer(i);
    }
}


bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    km_printf("led_update_user\r\n");
    return true;
}


// BHQ Status callback
void BHQ_State_Call(uint8_t cmdid, uint8_t *dat) {
    rgblight_disable();
    rgb_adv_unblink_all_layer();


    advertSta = BHQ_GET_BLE_ADVERT_STA(dat[1]);
    connectSta = BHQ_GET_BLE_CONNECT_STA(dat[1]);
    pairingSta = BHQ_GET_BLE_PAIRING_STA(dat[1]);

    km_printf("keymape:cmdid:%d\r\n",cmdid);
    if(cmdid == BHQ_ACK_RUN_STA_CMDID)
    {
        km_printf("[RSSI:%d]\t",dat[0]);
        km_printf("[advertSta: %d]\t", advertSta);
        km_printf("[connectSta: %d]\t", connectSta); // 0 = 断开, 1 = 已连接, 2 = 超时
        km_printf("[pairingSta: %d]\t", pairingSta);
        km_printf("[host_index:%d]\n",dat[2]);
        host_index = dat[2];

        if(host_index == 0)
        {
            km_printf("if host_index 1\r\n");
            // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙配对模式
            if(connectSta != 1 && advertSta == 1 && pairingSta == 1)
            {
                rgblight_blink_layer_repeat(0 , 500, 50);
                km_printf("1\r\n");
            }
            // 蓝牙没有连接 && 蓝牙广播开启  && 蓝牙非配对模式
            else if(connectSta != 1 && advertSta == 1 && pairingSta == 0)
            {
                rgblight_blink_layer_repeat(0 , 2000, 50);
                km_printf("2\r\n");
            }
            // 蓝牙已连接
            if(connectSta == 1)
            {
                rgblight_blink_layer_repeat(0 , 200, 2);
                km_printf("3\r\n");
            }
        }
        // 注释同上的host_index == 0 
        else if(host_index == 1)
        {
            km_printf("if host_index 2\r\n");
            if(connectSta != 1 && advertSta == 1 && pairingSta == 1)
            {
                rgblight_blink_layer_repeat(1 , 500, 50);
                km_printf("4\r\n");
            }
            else if(connectSta != 1 && advertSta == 1 && pairingSta == 0)
            {
                rgblight_blink_layer_repeat(1 , 2000, 50);
                km_printf("5\r\n");
            }
            if(connectSta == 1)
            {
                rgblight_blink_layer_repeat(1 , 200, 2);
                km_printf("6\r\n");
            }
        }    
        else if(host_index == 2)
        {
            km_printf("if host_index 3\r\n");
            if(connectSta != 1 && advertSta == 1 && pairingSta == 1)
            {
                rgblight_blink_layer_repeat(2 , 500, 50);
            }
            else if(connectSta != 1 && advertSta == 1 && pairingSta == 0)
            {
                rgblight_blink_layer_repeat(2 , 2000, 50);
            }
            if(connectSta == 1)
            {
                rgblight_blink_layer_repeat(2 , 200, 2);
            }
        }
        
    }
    else if(cmdid == BHQ_ACK_LED_LOCK_CMDID)
    {
        km_printf("[%s] Num Lock\t", (dat[0] & (1<<0)) ? "*" : " ");
        km_printf("[%s] Caps Lock\t", (dat[0] & (1<<1)) ? "*" : " ");
        km_printf("[%s] Scroll Lock\n", (dat[0] & (1<<2)) ? "*" : " ");
    }
}



// Keyboard level code can override this, but shouldn't need to.
// Controlling custom features should be done by overriding
// via_custom_value_command_kb() instead.
__attribute__((weak)) bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t command_id   = data[0];
    uint8_t i = 0;

    // 此逻辑删除 会失去蓝牙模块升级功能 以及蓝牙改键功能！！！！！！！
    km_printf("cmdid:%02x  length:%d\r\n",command_id,length);
    km_printf("read host app of data \r\n[");
    for (i = 0; i < length; i++)
    {
        km_printf("%02x ",data[i]);
    }
    km_printf("]\r\n");

    if(command_id == 0xF1)
    {
        // cmdid + 2 frame headers 
        // The third one is isack the fourth one is length and the fifth one is data frame
        BHQ_SendCmd(0, &data[4], data[3]);
        return true;
    }
    return false;
}

#endif
