/* Copyright 2024 @ Grabshell (https://grabshell.site/)
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
#include "user_lib_comm.h"

#if DIS_G_SENSOR_SWITCH
#    define DI_GS_KEY KC_DI_GSENSOR_EN
#else
#    define DI_GS_KEY KC_TRNS
#endif

#if TEST_SLEEP_KEY
#    define TS_SL_KEY KC_TEST_SLEEP
#else
#    define TS_SL_KEY KC_TRNS
#endif

// MIDI CC codes for generic on/off switches (80, 81, 82, 83)
// Off: 0-63
// On:  64-127
#ifdef MIDI_ENABLE
#    define MIDI_CC_OFF 0
#    define MIDI_CC_ON 127
extern MidiDevice    midi_device;
extern midi_config_t midi_config;
#endif

// Example implementation
#define EXAMPLE_ENABLE
#define TIMER_DIFF_KEYMAP(a, b) ((a) >= (b) ? (a) - (b) : 0xffff + 1 - (b) + (a))

enum layer_names {
    _BASE,
    _FnLay,
    NONE1,
    NONE2
};

report_mouse_t pointing_device_driver_get_report_user(report_mouse_t mouse_report);

/*
   _BASE / Default Key Map
   ┌─────┬─────┬─────┬─────┬─────┬─────┐      ┌─────┬─────┬─────┬───────┬┬───────┬─────┬─────┐─────┐      ┌─────┬─────┬─────┬─────┬─────┬─────┐
   │ ESC │  1  │  2  │  3  │  4  │  5  │      │     │ ALT │ -_  │       ││       │ =+  │ ALT │     │      │  6  │  7  │  8  │  9  │  0  │ `~  │
   ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐├─────┴┐────┴┐────┴┐      ││      ┌┴────┌┴────┌┴─────┤┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   │ BS  │  Q  │  W  │  E  │  R  │  T  │     ││ TAB  │ GUI │ [{  │      ││      │ ]}  │ GUI │ ENT  ││     │  Y  │  U  │  I  │  O  │  P  │ -_  │
   └─────┼─────┼─────┼─────┼─────┼─────┤Shift│├──────┴┐────┴┐────┴┐     ││     ┌┴────┌┴────┌┴──────┤│Shift├─────┼─────┼─────┼─────┼─────┼─────┘
         │  A  │  S  │  D  │  F  │  G  │     ││ _FnLay│ CTL │ \|  │     ││     │ '"  │ -_  │ _FnLay││     │  H  │  J  │  K  │  L  │ ;:  │
         ├─────┼─────┼─────┼─────┼─────┼─────┘├───────┴─────┴─────┘     ││     ╰─────┴─────┴───────┤╰─────┼─────┼─────┼─────┼─────┼─────┤
         │  Z  │  X  │  C  │  V  │  B  │      ├──────╮╭─────────╮       ││                  ╭──────┤      │  N  │  M  │ ,<  │ .>  │ /?  │
         └─────┴─────┴─────┴─────┴─────┘      │ BTN1 ││         │Toggle ││     Track        │ BTN1 │      └─────┴─────┴─────┴─────┴─────┘
                    Back Left                 ├──────┤│ JOY_BTN │Switch ││      Ball        │──────┤          Back Right
                                              │ BTN2 │╰─────────┘       ││                  │ BTN2 │
                                              ├──────┤╭─────────╮╭──────┤├──────┬─────┬─────│──────┤
                                              │ PGUP ││ enc sw  ││ PGDN ││ LEFT │ UP  │DOWN │RIGHT │
                                              ├──────┘╰─────────┘╰──────┤├──────┴─────┴─────┴──────┤
                                              ╰────── Frent Left ───────┴┴────── Frent Right ──────┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,	      	        KC_SPC,	    KC_LALT,    KC_MINS,            KC_EQL,	    KC_RALT,    KC_SPC,           	    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GRV,
    KC_BSPC,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LSFT,    KC_TAB,	    KC_LGUI,	KC_LBRC,	        KC_RBRC,	KC_RGUI,    KC_ENT,     KC_RSFT,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_MINS,
                KC_A,       KC_S,       KC_D,       KC_F,       KC_G,	      	        MO(_FnLay),	KC_LCTL,	KC_BSLS,	        KC_QUOT,    KC_RCTL,    MO(_FnLay),             KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,
                KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,	      	        KC_BTN1,	JOY_BTN,    XXXXXXX,               	                    KC_BTN2,                KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,
                 	                 	                 	                            KC_BTN2,	                 	                 	                KC_BTN1,
                	                 	                 	                            KC_PGUP,	KC_BTN3,	KC_PGDN,   KC_LEFT, KC_UP,      KC_DOWN,    KC_RIGHT
    ),
    [_FnLay] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    RGB_TOG,	      	    KC_TRNS,    KC_TRNS,    KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_DEL,	    KC_TRNS,    KC_UP,      KC_TRNS,    KC_MUTE,    RGB_MOD,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_7,       KC_8,     KC_9,      KC_PEQL,   KC_PPLS,   KC_TRNS,
                KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_VOLD,    RGB_HUI,	            KC_TRNS,	KC_TRNS,    DI_GS_KEY,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_4,       KC_5,     KC_6,      KC_0,	    KC_PAST,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_VOLU,    RGB_HUD,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_1,       KC_2,     KC_3,      KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_HOME,	KC_TRNS,    KC_END,    KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
    [NONE1] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,	KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	            KC_TRNS,	KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,	KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_TRNS,	KC_TRNS,	KC_TRNS,   KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
    [NONE2] = LAYOUT(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,	KC_TRNS,   	        KC_TRNS,	KC_TRNS,    KC_TRNS,	           	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,    KC_TRNS,	KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	            KC_TRNS,	KC_TRNS,    KC_TRNS,	        KC_TRNS,	KC_TRNS,    KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,	KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,	      	    KC_TRNS,	KC_TRNS,    KC_TRNS,    	                 	        KC_TRNS,	            KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                 	                 	                 	                            KC_TRNS,	                 	                 	                KC_TRNS,
                	                 	                 	                            KC_TRNS,	KC_TRNS,	KC_TRNS,   KC_TRNS, KC_TRNS,	KC_TRNS,    KC_TRNS
    ),
};

/* function name: custom_layer_active
 *
 * This function will be called during layer activity, and users can set the sensor mode in this function
 * If there is an operation sensor code, it needs to return true
 */
bool custom_layer_active(layer_state_t state) {
    return false;
}

/* function name: pointing_device_driver_get_report_custom
 *
 * This function will be called everytime, and users can change the pointing device in this function
 * If there is an operation sensor code, it needs to return mouse_report
 */
report_mouse_t pointing_device_driver_get_report_custom(report_mouse_t mouse_report){
    return mouse_report;
}

/* function name: process_record_user
 *
 * This function will be called during keycode activity, and the user can set the sensor mode in this function
 * If there is an operation sensor code, it needs to return true
 */
extern joy_btn_t joy_btm_con;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef MIDI_ENABLE
        case MIDI_CC80: {
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_ON);
            } else {
                midi_send_cc(&midi_device, midi_config.channel, 80, MIDI_CC_OFF);
            }
            return false;
        } break;
#endif
#ifdef EXAMPLE_ENABLE // example
        case JOY_BTN:
        {
            if (get_joystick_mode() == ARROW_MODE) {
                if (record->event.pressed) {
                    register_code(KC_BTN3);
                } else {
                    unregister_code(KC_BTN3);
                }
                return false;
            }

            if (get_joystick_mode() == GAME_MODE) {
                if (record->event.pressed) {
                    register_joystick_button(JS_0 - JS_0);
                    joy_btm_con.joy_pass_key_code = JS_0;
                    joy_btm_con.joy_pass_key_flag = 1;
                } else {
                    if (joy_btm_con.joy_pass_key_flag) {
                        joy_btm_con.joy_pass_key_flag = 0;
                        unregister_joystick_button(joy_btm_con.joy_pass_key_code - JS_0);
                    }
                }
                return false;
            }
        } break;
#endif
    }
    return true;
}

/* function name: dip_switch_update_user
 *
 * This function will be called during toggle switch activity, and the user can set the sensor mode in this function
 * If there is an operation sensor code, it needs to return true
 */
bool dip_switch_update_user(uint8_t index, bool active) {
#ifdef EXAMPLE_ENABLE
    switch (index) {
        case 0: {
            if (!active) {  // toggle switch up
                set_joystick_mode(MOUSE_MODE);
                set_joy_point_change_flag(1);
                set_paw_motton_mode(PAW_MOUSE_MODE);
                return false;
            } else {        // toggle switch down
                set_joystick_mode(ARROW_MODE);
                set_joy_point_change_flag(1);
                set_paw_motton_mode(PAW_SCROLL_MODE);
                return false;
            }
        } break;
    }
#endif
    return true;
}

/* function name: housekeeping_task_user
 *
 * This function gets called at the end of all QMK processing, before starting the next iteration
 */
void housekeeping_task_user(void) {
#ifdef EXTERN_I2C_ENABLE
    if (extern_i2c_powerup_delay()) {
        extern_i2c_example();
    }
#endif

#ifdef EXAMPLE_ENABLE
    static uint16_t last_timer = 0xffff;
    uint16_t        temp_timer;
    int16_t         lis2mdl_x, lis2mdl_y, lis2mdl_z;
    int16_t         acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, temp_t;
    temp_timer = timer_read();

    if (last_timer == 0xffff) {
        last_timer = temp_timer;
    }
    if (TIMER_DIFF_KEYMAP(temp_timer, last_timer) > 1000) {
        last_timer = temp_timer;
        Get_Lis2mdl_XYZ(&lis2mdl_x, &lis2mdl_y, &lis2mdl_z);
        getTemp(&temp_t);
        GetAccel(&acc_x, &acc_y, &acc_z);
        GetGyro(&gyro_x, &gyro_y, &gyro_z);
    }
#endif
}
