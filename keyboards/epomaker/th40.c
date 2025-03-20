/* Copyright 2025 EPOMAKER
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
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

#include "../../lib/rdr_lib/rdr_common.h"

void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

led_config_t g_led_config = { {
	{ 0        , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   },
	{ NO_LED   , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       },
	{ 12       , 13       , 14       , 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , NO_LED   },
	{ 23       , 24       , 25       , 26       , 27       , 28       , 29       , 30       , 31       , 32       , 33       , 34       },
	{ 35       , NO_LED   , 36       , 37       , 38       , NO_LED   , 39       , 40       , 41       , 42       , 43       , NO_LED   }
},{
    { 5,  10},  { 24, 10},  { 42, 10},  { 60, 10}, { 78, 10}, { 96, 10}, { 114,10}, { 132, 10}, { 150, 10}, { 168, 10}, { 186, 10},             { 204, 10},
    { 5,  20},  { 27, 20},  { 45, 20},  { 63, 20}, { 81, 20}, { 99, 20}, { 117,20}, { 135, 20}, { 153, 20}, { 171, 20},             { 199, 20},
    { 0,  30},  { 18, 30},  { 36, 30},  { 54, 30}, { 72, 30}, { 90, 30}, { 108,30}, { 126, 30}, { 144, 30}, { 162, 30}, { 180, 30},             { 205, 30},
    { 0,  40},  { 18, 40},  { 36, 40},                        { 70, 40}, { 99, 40}, { 135, 40},                         { 171, 40}, { 189, 40}, { 207, 40},

    { 225,65},  { 225,65},  { 225,65}
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1,       1, 1, 1,    1, 1, 1, 1, 1,

    0,  0,  0
} };

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    User_Led_Show();
    return false;
}

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

void housekeeping_task_user(void) {
    es_chibios_user_idle_loop_hook();
    User_Keyboard_Reset();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    User_Keyboard_Post_Init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    Usb_Change_Mode_Delay = 0;
    Usb_Change_Mode_Wakeup = false;

    return User_process_record_user(keycode, record);
}
