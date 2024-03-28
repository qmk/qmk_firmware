/* Copyright 2023 @ Grabshell (https://grabshell.site/)
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

#include "quantum.h"
#include "i2c_master.h"
#include "usb_device_state.h"
#include "lib/lsm6ds3tr-c_reg.h"

////////// Trackball Sensor (FCT3065) mode define ///////////////////////////
#define PAW_NONE_MODE 0     /* no function */
#define PAW_MOUSE_MODE 1    /* ouse curosor */
#define PAW_SCROLL_MODE 2   /* wheel scrolling */

////////// joystick mode define ///////////////////////////
#define WASD_MODE 0         /* WASD keycodes for game */
#define MOUSE_MODE 1        /* mouse curosor */
#define ARROW_MODE 2        /* up,down,left,right keycodes */
#define GAME_MODE 3         /* gamepad joystick */

////////// magnetic / accerelation sensor ///////////////////////////
#define LIS2MDL_ZERO_EN 1   /* clear flag to zero after reading */
#define LSM6DS3TR_ZERO_EN 1 /* clear flag to zero after reading */

#define DIS_G_SENSOR_SWITCH 1
#define TEST_SLEEP_KEY 0

enum custom_keycodes {
    KC_TEST_SLEEP = SAFE_RANGE,
    KC_DI_GSENSOR_EN,
    KC_OS_SWITCH,
    MIDI_CC80,
    JOY_BTN
};

typedef struct {
    uint8_t  joy_pass_key_flag;
    uint16_t joy_pass_key_code;
} joy_btn_t;

layer_state_t  lib_layer_state_set_user(layer_state_t state);
bool           lib_dip_switch_update_user(uint8_t index, bool active);
void           lib_notify_usb_device_state_change_user(enum usb_device_state usb_device_state);
void           lib_user_handle(void);
void           lib_board_init(void);
void           lib_pointing_device_driver_init(void);
report_mouse_t lib_pointing_device_driver_get_report(report_mouse_t mouse_report);
bool           lib_encoder_update_user(uint8_t index, bool clockwise);
void           lib_matrix_init_pins(void);
void           lib_matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter);
void           lib_post_init_user(void);
void           lib_mcu_reset(void);
void           lib_bootloader_jump(void);
void           lib_bootmagic_lite_user(void);
bool           lib_process_record_user(uint16_t keycode, keyrecord_t *record);
bool           via_command_kb_custom(uint8_t *data, uint8_t length);
void           bootloader_jump(void);
void           mcu_reset(void);
bool           custom_layer_active(layer_state_t state);
void           set_paw_motton_mode(uint8_t mode);
uint8_t        get_paw_motton_mode(void);
void           set_joystick_mode(uint8_t mode);
uint8_t        get_joystick_mode(void);
void           set_joy_point_change_flag(uint8_t flag);
uint8_t        get_joy_point_change_flag(void);
report_mouse_t pointing_device_driver_get_report_custom(report_mouse_t mouse_report);

////////// magnetic / accerelation sensor ///////////////////////////
void           GetMotion_User(int8_t *x, int8_t *y);
void           Get_Lis2mdl_XYZ(int16_t *x, int16_t *y, int16_t *z);
void           getTemp(int16_t *t);
void           GetAccel(int16_t *x, int16_t *y, int16_t *z);
void           GetGyro(int16_t *x, int16_t *y, int16_t *z);
void           set_Lsm6ds3tr_dev_sta(uint8_t sta);
bool           init_Lsm6ds3tr_para(void);
i2c_status_t   lsm6ds3tr_c_block_data_update_set(uint8_t val);
i2c_status_t   lsm6ds3tr_c_xl_data_rate_set(lsm6ds3tr_c_odr_xl_t val);
i2c_status_t   lsm6ds3tr_c_gy_data_rate_set(lsm6ds3tr_c_odr_g_t val);
i2c_status_t   lsm6ds3tr_c_xl_full_scale_set(lsm6ds3tr_c_fs_xl_t val);
i2c_status_t   lsm6ds3tr_c_gy_full_scale_set(lsm6ds3tr_c_fs_g_t val);
i2c_status_t   lsm6ds3tr_c_xl_filter_analog_set(lsm6ds3tr_c_bw0_xl_t val);
i2c_status_t   lsm6ds3tr_c_xl_lp2_bandwidth_set(lsm6ds3tr_c_input_composite_t val);
i2c_status_t   lsm6ds3tr_c_gy_band_pass_set(lsm6ds3tr_c_lpf1_sel_g_t val);
