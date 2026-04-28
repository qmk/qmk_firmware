/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include "../../../lib/rdr_lib/rdr_common.h"

/**********************系统函数***************************/
/*  键盘扫描按键延时 */
void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

/*********************************************************/

led_config_t g_led_config = { {
	{ 0        , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       , 12       , 13       , 14       , 15        },
	{ 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25       , 26       , 27       , 28       , 29       , 30       , 45        },
	{ 31       , 32       , 33       , 34       , 35       , 36       , 37       , 38       , 39       , 40       , 41       , 42       , 43       , 44       , NO_LED   , NO_LED    },
	{ 46       , 47       , 48       , 49       , 50       , 51       , 52       , 53       , 54       , 55       , 56       , 57       , NO_LED   , 58       , 59       , 73        },
	{ 60       , NO_LED   , 61       , 62       , 63       , 64       , 65       , 66       , 67       , 68       , 69       , 70       , NO_LED   , 71       , 72       , NO_LED    },
	{ 74       , 75       , 76       , NO_LED   , NO_LED   , 77       , NO_LED   , NO_LED   , NO_LED   , 78       , 79       , NO_LED   , 80       , 81       , 82       , 83        }
},{
    { 0,  10}, { 15, 10}, { 30, 10}, { 45, 10}, { 60, 10}, { 75, 10}, { 90, 10}, { 105, 10}, { 120, 10}, { 135, 10}, { 150, 10}, { 165, 10}, { 180, 10}, { 195, 10}, { 210, 10}, { 224, 10},
    { 0,  20}, { 15, 20}, { 30, 20}, { 45, 20}, { 60, 20}, { 75, 20}, { 90, 20}, { 105, 20}, { 120, 20}, { 135, 20}, { 150, 20}, { 165, 20}, { 180, 20}, { 203, 20},             { 224, 20},
    { 3,  30}, { 22, 30}, { 37, 30}, { 52, 30}, { 67, 30}, { 82, 30}, { 97, 30}, { 112, 30}, { 127, 30}, { 142, 30}, { 157, 30}, { 172, 30}, { 187, 30}, { 208, 30},             { 224, 30},
    { 3,  40}, { 25, 40}, { 40, 40}, { 55, 40}, { 70, 40}, { 85, 40}, { 100,40}, { 115, 40}, { 130, 40}, { 145, 40}, { 160, 40}, { 175, 40},             { 203, 40},             { 224, 40},
    { 7,  50},            { 34, 50}, { 49, 50}, { 64, 50}, { 79, 50}, { 94, 50}, { 105, 50}, { 124, 50}, { 139, 50}, { 154, 50}, { 169, 50}, { 190, 50},             { 210, 50}, { 224, 40},
    { 0,  60}, { 17, 60}, { 34, 60},                       { 95, 60},                                                { 150, 60}, { 165, 60}, { 180, 60}, { 195, 60}, { 210, 60}, { 224, 60},

    { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}, { 225,65}
}, {
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,      1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,  1,
    1,  1,  1,          1,              1,  1,      1,  1,  1,  1,

    0,  0,  0,  0,  0,  0,  0
} };

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    User_Led_Show();

    return false;
}

/************************休眠*****************************/
void notify_usb_device_state_change_user(enum usb_device_state usb_device_state)  {
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if(usb_device_state == USB_DEVICE_STATE_CONFIGURED) {
            Usb_If_Ok = true;//usb枚举完成
            Usb_If_Ok_Led = true;
            Usb_If_Ok_Delay = 0;
        } else {
            Usb_If_Ok = false;
		    Usb_If_Ok_Led = false;
        }
    } else {
        Usb_If_Ok = false;
	    Usb_If_Ok_Led = false;
    }
}
/*********************************************************/

void housekeeping_task_user(void) {
    User_Keyboard_Reset();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    if(User_State_Fulfill_Flag){
        User_Keyboard_Reset();
        User_State_Fulfill_Flag = 0x00;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {   /*键盘只要有按键按下就会调用此函数*/
    Usb_Change_Mode_Delay = 0;                                      /*只要有按键就不会进入休眠*/
    Usb_Change_Mode_Wakeup = false;

    return Key_Value_Dispose(keycode, record);
}
