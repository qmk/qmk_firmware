/* Copyright 2024 @ Grabshell (https://grabshell.site/)

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

#include QMK_KEYBOARD_H
#include "user_lib_comm.h"

#define EXTERN_I2C_ENABLE
#define EXTERN_I2C_ADD_READ 0xA1U  // I2c Device Read  Address
#define EXTERN_I2C_ADD_WRITE 0xA0U // I2c Device Write Address

#define SENSOR_PRINT_USB 1
// If SENSOR_BIG_ENDIAN_MODE is 1, High Byte Sent Before,If 0x1234 is sent in the order of 0x12 0x34
#define SENSOR_BIG_ENDIAN_MODE 0

uint8_t Lis2mdl_Zero_Flag;
uint8_t Lsm6ds3tr_Zero_Flag;
uint8_t Sensor_Transmit_Mode     = SENSOR_BIG_ENDIAN_MODE;
uint8_t Sensor_Print_Usb_Control = SENSOR_PRINT_USB;
uint8_t Extern_I2c_Addr[2]       = {EXTERN_I2C_ADD_READ, EXTERN_I2C_ADD_WRITE};
uint8_t dis_gsersor              = SENSOR_BIG_ENDIAN_MODE;

#ifdef JOYSTICK_ENABLE
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {JOYSTICK_AXIS_IN(C0, 1023, 511, 0), JOYSTICK_AXIS_IN(C1, 0, 511, 1023)};
#endif

extern __attribute__((unused)) i2c_status_t extern_i2c_register_write(uint8_t addr, uint8_t value);
extern __attribute__((unused)) i2c_status_t extern_i2c_register_read(uint8_t addr, uint8_t *value);
extern __attribute__((unused)) i2c_status_t extern_i2c_transmit(uint8_t regaddr, uint8_t *data, uint8_t length);
extern __attribute__((unused)) i2c_status_t extern_i2c_receive(uint8_t regaddr, uint8_t *data, uint8_t length);
extern __attribute__((unused)) uint8_t      extern_i2c_powerup_delay(void);
extern __attribute__((unused)) bool         get_extern_i2c_int_sta(void);

__attribute__((weak)) report_mouse_t pointing_device_driver_get_report_custom(report_mouse_t mouse_report) { return mouse_report; }
__attribute__((weak)) bool custom_layer_active(layer_state_t state) { return false; }

#ifdef RGB_MATRIX_ENABLE

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
//Left side, First row, LED
    {0,   E_6,    D_6,     F_6},
    {0,   B_1,    A_1,     C_1},
    {0,   B_2,    A_2,     C_2},
    {0,   B_3,    A_3,     C_3},
    {0,   B_4,    A_4,     C_4},
    {0,   B_5,    A_5,     C_5},

    {1,   K_1,    J_1,     L_1},
    {1,   K_2,    J_2,     L_2},
    {1,   K_3,    J_3,     L_3},
    {1,   H_3,    G_3,     I_3},
    {1,   H_2,    G_2,     I_2},
    {1,   H_1,    G_1,     I_1},

    {2,   B_1,    A_1,     C_1},
    {2,   B_2,    A_2,     C_2},
    {2,   B_3,    A_3,     C_3},
    {2,   B_4,    A_4,     C_4},
    {2,   B_5,    A_5,     C_5},
    {2,   E_6,    D_6,     F_6},


    {0,   H_6,    G_6,     I_6},
    {0,   E_1,    D_1,     F_1},
    {0,   E_2,    D_2,     F_2},
    {0,   E_3,    D_3,     F_3},
    {0,   E_4,    D_4,     F_4},
    {0,   E_5,    D_5,     F_5},
    {0,   B_6,    A_6,     C_6},

    {1,   E_4,    D_4,     F_4},
    {1,   K_4,    J_4,     L_4},
    {1,   K_5,    J_5,     L_5},
    {1,   K_6,    J_6,     L_6},
    {1,   H_6,    G_6,     I_6},
    {1,   H_5,    G_5,     I_5},
    {1,   H_4,    G_4,     I_4},
    {1,   B_4,    A_4,     C_4},

    {2,   B_6,    A_6,     C_6},
    {2,   E_1,    D_1,     F_1},
    {2,   E_2,    D_2,     F_2},
    {2,   E_3,    D_3,     F_3},
    {2,   E_4,    D_4,     F_4},
    {2,   E_5,    D_5,     F_5},
    {2,   H_6,    G_6,     I_6},


    {0,   H_1,    G_1,     I_1},
    {0,   H_2,    G_2,     I_2},
    {0,   H_3,    G_3,     I_3},
    {0,   H_4,    G_4,     I_4},
    {0,   H_5,    G_5,     I_5},

    {1,   E_3,    D_3,     F_3},
    {1,   K_8,    J_8,     L_8},
    {1,   K_9,    J_9,     L_9},
    {1,   K_10,   J_10,    L_10},
    {1,   H_10,   G_10,    I_10},
    {1,   H_9,    G_9,     I_9},
    {1,   H_8,    G_8,     I_8},
    {1,   B_3,    A_3,     C_3},

    {2,   H_1,    G_1,     I_1},
    {2,   H_2,    G_2,     I_2},
    {2,   H_3,    G_3,     I_3},
    {2,   H_4,    G_4,     I_4},
    {2,   H_5,    G_5,     I_5},


    {0,   K_1,    J_1,     L_1},
    {0,   K_2,    J_2,     L_2},
    {0,   K_3,    J_3,     L_3},
    {0,   K_4,    J_4,     L_4},
    {0,   K_5,    J_5,     L_5},

    {1,   E_1,    D_1,     F_1},
    {1,   K_7,    J_7,     L_7},
    {1,   H_7,    G_7,     I_7},
    {1,   B_1,    A_1,     C_1},

    {2,   K_1,    J_1,     L_1},
    {2,   K_2,    J_2,     L_2},
    {2,   K_3,    J_3,     L_3},
    {2,   K_4,    J_4,     L_4},
    {2,   K_5,    J_5,     L_5},


    {1,   E_2,    D_2,     F_2},
    {1,   E_7,    D_7,     F_7},
    {1,   B_7,    A_7,     C_7},
    {1,   B_2,    A_2,     C_2},

    {1,   E_5,    D_5,     F_5},
    {1,   E_6,    D_6,     F_6},
    {1,   E_9,    D_9,     F_9},
    {1,   E_10,   D_10,    F_10},
    {1,   E_8,    D_8,     F_8},
    {1,   B_10,   A_10,    C_10},
    {1,   B_9,    A_9,     C_9},
    {1,   B_8,    A_8,     C_8},
    {1,   B_6,    A_6,     C_6},
    {1,   B_5,    A_5,     C_5}

};
#if 1
#define N_L   NO_LED
led_config_t g_led_config = { {
  // Key Matrix to LED Index23,  24, 25, 26, 27, 28,
  { 0,   1,   2,   3,  4,  5,  N_L,        6,   7,   8,   N_L, 9,  10, 11, N_L,        12, 13, 14, 15, 16, 17,  N_L},
  { 18,  19,  20,  21, 22, 23, 24,         25,  26,  27,  28,  29, 30, 31, 32,         33,  34, 35, 36, 37, 38, 39},
  { N_L, 40,  41,  42, 43, 44, N_L,        45,  46,  47,  48,  49, 50, 51, 52,         N_L, 53, 54, 55, 56, 57, N_L},
  { N_L, 58,  59, 60, 61,  62, N_L,        63,  65,  N_L, N_L, N_L,N_L,65, 66,         N_L, 67, 68, 69, 70, 71, N_L},
  { N_L, N_L, N_L, N_L, N_L, N_L, N_L,     72,  73,  N_L, N_L, N_L,N_L,74, 75,         N_L, N_L,N_L,N_L,N_L,N_L,N_L},
  { N_L, N_L, N_L, N_L, N_L, N_L,  76,     77,  78,  79,  80,  81, 82, 83, 84,         85,  N_L,N_L,N_L,N_L,N_L,N_L}
}, {
  // LED Index to Physical Position
  // x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION   224/(3-1) * current index
  // y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION   64/(5-1) * current index

  {5,6 }, {15,3}, {25,2 }, {34,1}, {44,3}, {53,5}, {71,28}, {81,28 }, {90,28},  {134,  28}, {143,28}, {152,28}, {171,5 }, {180,3 }, {189,1},{199,2}, {208,3}, {219,15},
  {3,12}, {14,9}, {23,9},  {33,7}, {42,9}, {51,11},{59,15}, {62,37},  {73,34}, {83,34}, {93,34}, {131,34}, {141,34}, {152,34}, {157,37}, {164,14}, {172,10}, {181,8}, {190,6}, {200,7}, {210,8},{220,11},
  {12,15}, {22,14}, {31,13}, {40,15}, {49,17},{67,43},{74,40},{85,40},{95,40}, {129,40},{139,40},{150,40}, {156,43}, {174,16}, {183,14}, {192,13}, {201,14},   {211,15},
  {10,21}, {20,20}, {30,19}, {38,21}, {47,23},{68,48},{80,48},{148,48},{156,48},{175,22}, {185,20},{193,19},{203,20},{213,21},
  {68,52}, {75,53}, {149,53},{155,52},
  {69,57}, {69,61}, {92,60}, {102,60}, {120,60}, {130,60}, {139,60}, {148,60},{155,57},{155,61}
}, {
  // LED Index to Flag
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif
#endif

/*
 * function
 */
void housekeeping_task_kb(void) {
    lib_user_handle();
}

void matrix_init_pins(void) {
    lib_matrix_init_pins();
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    lib_matrix_read_rows_on_col(current_matrix, current_col, row_shifter);
}

void board_init(void) {
    lib_board_init();
    Lis2mdl_Zero_Flag   = LIS2MDL_ZERO_EN;
    Lsm6ds3tr_Zero_Flag = LSM6DS3TR_ZERO_EN;
}

void pointing_device_driver_init(void) {
    lib_pointing_device_driver_init();
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state) {
    lib_notify_usb_device_state_change_user(usb_device_state);
}

void bootmagic_lite(void) {
    lib_bootmagic_lite_user();
}

void bootloader_jump(void) {
    lib_bootloader_jump();
}

void mcu_reset(void) {
    lib_mcu_reset();
}

void keyboard_post_init_kb(void) {
    lib_post_init_user();
}

/*
 * LSM6DS3TR (6DOF IMU) parameter
 */
bool init_Lsm6ds3tr_para(void) {
    /* Enable Block Data Update */
    if (lsm6ds3tr_c_block_data_update_set(PROPERTY_ENABLE) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_xl_data_rate_set(LSM6DS3TR_C_XL_ODR_104Hz) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }
    if (lsm6ds3tr_c_gy_data_rate_set(LSM6DS3TR_C_GY_ODR_104Hz) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_xl_full_scale_set(LSM6DS3TR_C_4g) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_gy_full_scale_set(LSM6DS3TR_C_500dps) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_xl_filter_analog_set(LSM6DS3TR_C_XL_ANA_BW_400Hz) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_xl_lp2_bandwidth_set(LSM6DS3TR_C_XL_LOW_NOISE_LP_ODR_DIV_100) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }

    if (lsm6ds3tr_c_gy_band_pass_set(LSM6DS3TR_C_HP_260mHz_LP1_STRONG) != I2C_STATUS_SUCCESS) {
        set_Lsm6ds3tr_dev_sta(0);
        return false;
    }
    return true;
}

/*
 * user customizable function
 */

#ifdef EXTERN_I2C_ENABLE // example
/* external i2c pin {1:I2C SDA, 2:I2C SCL, 3:interrupt, 4:GND, 5:VCC} */
__attribute__((unused)) uint8_t extern_i2c_example(void) {
    uint8_t      write_buff[16];
    uint8_t      read_buff[16];
    uint8_t      num;
    uint8_t      temp_value;
    i2c_status_t i2c2_ret_sta;
    uint8_t      ret = 0;

    for (num = 0; num < 16; num++) {
        write_buff[num] = num;
        read_buff[num]  = 0;
    }

    if (extern_i2c_register_read(0x32, &temp_value) != I2C_STATUS_SUCCESS) {
        return 0;
    }

    i2c2_ret_sta = extern_i2c_transmit(0, write_buff, 16);
    if (i2c2_ret_sta == I2C_STATUS_SUCCESS) {
        if (extern_i2c_receive(0, read_buff, 16) == I2C_STATUS_SUCCESS) {
            for (num = 0; num < 16; num++) {
                if (read_buff[num] != write_buff[num]) {
                    break;
                }
            }
            if (num == 16) {
                ret = 1;
            } else {
            }
        } else {
        }
    } else {
        if (i2c2_ret_sta == I2C_STATUS_TIMEOUT) {
        } else {
        }
    }
    return ret;
}
#endif

/*
QMK only one sensor can be enabled at a time by POINTING_DEVICE_DRIVER.
You can get two combined mouse_reports of the joystick and trackball sensors using a custom driver.
*/
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    mouse_report = lib_pointing_device_driver_get_report(mouse_report);
    mouse_report = pointing_device_driver_get_report_custom(mouse_report);
    return mouse_report;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    } else if (lib_process_record_user(keycode, record)) {
        return false;
    }
    return true;
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    } else if (lib_dip_switch_update_user(index, active)) {
        return false;
    }

    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    return lib_layer_state_set_user(state);
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    return lib_encoder_update_user(index, clockwise);
}
#endif
